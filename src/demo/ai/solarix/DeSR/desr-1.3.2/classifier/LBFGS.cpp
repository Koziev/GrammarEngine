/*
**  Tanl
**  classifier/Classifier.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of Tanl.
**
**  Tanl is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  Tanl is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#include "LBFGS.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <limits>
#ifdef _WIN32
# define isfinite _finite
#endif

// debug
#include <assert.h>
#include <stdio.h>

#include "lbfgsAlg.h"
#include "include/Timer.h"

using namespace std;
using namespace Tanl::Text;	// WordIndex

#define lbfgs(x, f, g, opt)						\
  ::LBFGS::minimize(opt.n, opt.m, x, f, g, opt.diagco, opt.diag,	\
		  opt.iprint, opt.eps, opt.xtol, opt.w, opt.iflag,	\
		  opt.niter, opt.nfuns)

namespace Tanl {
namespace Classifier {

struct compare1st {
public:
  bool operator()(std::pair<ClassID, int> const& k1,
		  std::pair<ClassID, int> const& k2) {
    return k1 < k2;
  }
};

///////////////////////////////////////////////////////////////////////////////

LBFGS::LBFGS(int iterations, int cutoff, double eps) :
  MaxEnt(iterations, cutoff),
  opt(iterations, eps),
  lambda(0)
{ }

LBFGS::LBFGS(EventStream& es, int iterations, int cutoff, double eps) :
  MaxEnt(iterations, cutoff),
  opt(iterations, eps),
  lambda(0)
{
  train(es);
}

void LBFGS::train(EventStream& es)
{
  read(es);
  train();
}

void LBFGS::train() {
  counter.clear();		// finished reading events
  // Transform @c events into an EventMap of unique events.
  // Also build @c outcomeLabels to be put in the model.
  // Prune events with frequency lower than @c cutoff (0).
  // events are deleted.
  numEvents = buildIndex(events, predIndex, eventMap, outcomeLabels, 0, verbose);

  numTokens = eventMap.size();	// number of unique events
  numPreds = predLabels.size(); // number of predicates
  numOutcomes = outcomeLabels.size(); // number of outcomes

# ifdef SHOWTIME
  Timer timer;
  timer.stop();
  char buffer[80];
  timer.duration(buffer, sizeof(buffer));
  cerr << "buildIndex: " << buffer << endl;
  timer.start();
# endif

  if (numTokens == 0)
    throw EventStreamError("No events in stream");

  // set up feature arrays
  FeatureMap		featSum; // counts the occurrences of each feature

  // calculate observed feature expectations
  // a hash map to hold the value of feature <pred, outcome> pair occured in event list
  // which is the sum of active feature f_i(a,b) in the training set

  // build map: predicate -> set of outcomes
  // i.e., pred1 -> {out1, out2, out3, ...}
  typedef map<PID, set<ClassID> > PredOutcomes;
  PredOutcomes predOutcomes;
  FOR_EACH (EventMap, eventMap, it) {
    ClassID oID = it->first.first;
    int evCount = it->second;
    const vector<PID>& predicates = it->first.second;
    for (unsigned j = 0; j < predicates.size(); j++) {
      PID pid = predicates[j];
      Feature f(pid, oID);
      featSum[f] += evCount;
      predOutcomes[pid].insert(oID);
    }
  }

  // create contribTable: it associates to each predicate pi
  // a vector of pairs <oid, fid>, where oid is a class to which
  // it contributes and fid is the index into lambdas for feature <pi, oid>:
  //   contribTable[pi] = < .. <oid, fid> .. >
  //   lambda[fid] = Ep[pi, oid]
  contribTable.clear();
  contribTable.resize(numPreds);
  int featCount = 0;
  FOR_EACH (PredOutcomes, predOutcomes, it) {
    ContribTable::value_type& contribs = contribTable[it->first];
    FOR_EACH (set<ClassID>, it->second, oit)
      contribs.push_back(make_pair(*oit, featCount++));
  }

  lambda = new double[featCount];
  std::fill(lambda, lambda + featCount, 0.0);

  // Get the observed expectations of the features. Strictly speaking,
  // we should divide the counts by the number of tokens, but because of
  // the way the model's expectations are approximated in the
  // implementation, this is cancelled out when we compute the next
  // iteration of a parameter, making the extra divisions wasteful.
  double* observedExpects = new double[featCount];
  for (PID pid = 0; pid < numPreds; ++pid) {
    ContribTable::value_type& param = contribTable[pid];
    for (size_t j = 0; j < param.size(); ++j) {
      Feature f(pid, param[j].first);
      observedExpects[param[j].second] = - featSum[f];
    }
  }
# ifdef SHOWTIME
  timer.stop();
  timer.duration(buffer, sizeof(buffer));
  cerr << "init: " << buffer << endl;
# endif

  static const double LOG_ZERO = log(DBL_MIN);
  double* prob = new double[numOutcomes];
  double* grad = new double[featCount];
  // prepare opt
  opt.n = featCount;
  opt.diag = new double[featCount];
  opt.w = new double[featCount * (2*opt.m+1) + 2*opt.m];

  while (opt.niter < iterations) {
    // calculate loglikehood and gradient
    double ll = 0.0;
    int correct = 0;
    std::copy(observedExpects, observedExpects + featCount, grad);

    // expected[i, c] = SUM(j, oc(xj) p(c|xj) fi(xj, c))
    // for each (possibly multiple) event
    FOR_EACH (EventMap, eventMap, it) {
      ClassID outcome = it->first.first;
      int evCount = it->second;
      const vector<PID>& xj = it->first.second;
      // prob[c] = p(c|xj)
      ClassID best = estimate(xj, prob);
      if (best == outcome)
	correct += evCount;
      // add contribution of xj to each class according to its probability
      for (unsigned i = 0; i < xj.size(); i++) {
	int pID = xj[i];
	FOR_EACH (ContribTable::value_type, contribTable[pID], cit) {
	  ClassID oid = cit->first;
	  int fid = cit->second;
	  grad[fid] += prob[oid] * evCount;
	}
      }
      assert(isfinite(prob[outcome]));
      double t = log(prob[outcome]);
      ll -= evCount * (isfinite(t) ? t : LOG_ZERO);
    }

    lbfgs(lambda, ll, grad, opt);

    if (verbose) {
      cerr << " " << opt.niter+1 << ". loglikelihood = " << -ll
	   << " correct = " << correct * 100.0 / numEvents << "%" << endl;
    }
    if (opt.iflag < 0)
      throw runtime_error("lbfgs routine returned error: ");
    else if (opt.iflag == 0)
      break;
  }
  delete[] grad;
  delete[] prob;
  delete[] observedExpects;
}

ClassID LBFGS::estimate(const vector<PID>& preds, double prob[])
{
  // p(a|b) = exp(SUM(j=1..k, L_j * f_j(a, b))) / Z
  // where Lj = log(w_j)
  //
  // Here prob[a] = p(a|context)
  //
  std::fill(prob, prob + numOutcomes, 0.0);
  for (unsigned i = 0; i < preds.size(); i++) {
    PID pid = preds[i];
    FOR_EACH (ContribTable::value_type, contribTable[pid], it)
      prob[it->first] += lambda[it->second];
  }
  // normalize
  ClassID best = 0;
  double max_prob = 0.0;
  double sum = 0.0;
  for (ClassID oid = 0; oid < numOutcomes; oid++) {
    prob[oid] = exp(prob[oid]);
    if (!isfinite(prob[oid]))
        prob[oid] = DBL_MAX; // numeric_limits<double>::max();
    sum += prob[oid];
    if (prob[oid] >= max_prob) {
      max_prob = prob[oid];
      best = oid;
    }
  }
  for (ClassID oid = 0; oid < numOutcomes; oid++) {
    prob[oid] /= sum;
  }
  return best;
}

#define HEADER "#txt,maxent"
#define LINE 16384

void LBFGS::save(char const* path)
{
  ofstream ofs(path, ios::binary | ios::trunc);
  writeHeader(ofs);
  writeData(ofs);
}

void LBFGS::writeHeader(ofstream& ofs)
{
  // write header
  ofs << HEADER << endl;

  // write context predicates
  ofs << numPreds << endl;
  for (unsigned i = 0; i < numPreds; ++i)
    ofs << predLabels[i] << endl;
  predLabels.clear();
  predLabels.resize(0);

  // write outcomes
  ofs << numOutcomes << endl;
  for (size_t i = 0; i < numOutcomes; ++i) {
    char const* label = outcomeLabels[i];
    ofs << label << endl;
    free((void*)label);
  }
  outcomeLabels.clear();
  outcomeLabels.resize(0);
}

void LBFGS::writeData(ofstream& ofs)
{
  ofs.precision(20);

  // write feature index map
  size_t featCount = 0;
  for (unsigned i = 0; i < numPreds; ++i) {
    ContribTable::value_type& contrib = contribTable[i];
    ofs << contrib.size();
    FOR_EACH (ContribTable::value_type, contrib, cit) {
      ofs << " " << cit->first;
      featCount++;
    }
    ofs << endl;
  }

  // write theta (i.e. lambda)
  ofs << featCount << endl;
  for (unsigned i = 0; i < featCount; ++i)
    ofs << lambda[i] << endl;
# ifdef DEBUG
  for (int pid = 0; pid < numPreds; ++pid) {
    ContribTable::value_type& contrib = contribTable[pid];
    FOR_EACH (ContribTable::value_type, contrib, cit) {
      char const* outcome = OutcomeName(cit->first);
      string const& pred = PredicateName(pid);
      printf("lambda(%s, %s)=%.4f\n", outcome, pred.c_str(), lambda[cit->second]);
      }
    }
# endif
}

} // namespace Classifier
} // namespace Tanl
