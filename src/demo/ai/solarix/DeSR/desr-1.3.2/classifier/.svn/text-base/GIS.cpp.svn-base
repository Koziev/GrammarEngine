/*
**  Tanl
**  classifier/GIS.cpp
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

#include "GIS.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <algorithm>

// debug
#include <stdio.h>

using namespace std;
using namespace Tanl::Text;	// WordIndex

namespace Tanl {
namespace Classifier {

  const double GIS::NEAR_ZERO = 0.01;
  const double GIS::LLThreshold = 0.001;

  /**
   *	Generalized Iterative Scaling uses an iterative algorithm to find the
   *	correct weights for a conditional exponential classifier.
   *	It initially sets all weights to zero; it then iteratively updates
   *	the weights using the formula:
   *	
   *	lambda[i] := lambda[i] * (E~f[i]/Ef[i]) ^ (1/C)
   *	
   *	Where: 
   *	lambda[i] is the weight of the ith feature. 
   *	C is the correction constant. 
   *	E~f[i] is the sum of the feature values for the ith feature
   *	over training texts. 
   *	Ef[i] is the sum of the feature values for the ith feature that is
   *	predicted by the current model. 
   */

///////////////////////////////////////////////////////////////////////////////

GIS::GIS(int iterations, int cutoff, double alpha) :
  MaxEnt(iterations, cutoff), alpha(alpha)
{ }

GIS::GIS(EventStream& es, int iterations, int cutoff, double alpha) :
  MaxEnt(iterations, cutoff), alpha(alpha)
{
  train(es);
}

void GIS::train(EventStream& es)
{
  read(es);
  train();
}

void GIS::train()
{
  counter.clear();
  // Transform @c events into an EventMap.
  // Also build @c predIndex, @c outcomeLabels to be put in the model.
  // Prune events with frequency lower than @c cutoff (0).
  // events are deleted.
  int numEvents = buildIndex(events, predIndex, eventMap, outcomeLabels, 0,
			     verbose);

  numTokens = eventMap.size();	// number of unique events
  numPreds = predLabels.size(); // number of predicates
  numOutcomes = outcomeLabels.size(); // number of outcomes

  if (numTokens == 0)
    throw EventStreamError("No events in stream");

  // set up feature arrays
  //  p~(b_i) = freq[tID] = eventMap[tID] / numTokens
  //  f_j(a, b) = b.contains(j) && outcome == a
  //  p(a|b_i) = Z * exp(SUM(i, Lj * f_j(a, b)))
  // where Lj = log(w_j)
  //  Ef_j = SUM(i, p~(b_i) * SUM(a, p(a|b_i) * f_j(a, b_i)))
  //
  FeatureMap		logObserved; // log(observed[k] - alpha)

  // Get the observed expectations of the features.
  // Go through all events:
  //  event[n] = (outcomes[n], contexts[n])
  //
  //  observed[j] = SUM(i, fj(ai, bi)) (i.e. count the events having feature j)
  //
  // determine the correction constant (not used)
  // C = max sum_{x,y} f_i(x, y)
  correctionConstant = 0;	// max number of features in any event
  FOR_EACH (EventMap, eventMap, it) {
    int evOccurred = it->second;
    ClassID oID = it->first.first;
    const vector<PID>& predicates = it->first.second;
    for (unsigned j = 0; j < predicates.size(); j++) {
      PID pID = predicates[j];
      Feature f(pID, oID);
      logObserved[f] += evOccurred;
      // initialize also other maps (or find() will fail)
      lambda[f] = 0.0;
    }
    correctionConstant = MAX(correctionConstant, predicates.size());
  }
  double fSharp = correctionConstant;		

  // initialize expected: it associates to each predicate the vector of classes
  // to which it contributes and the corresponding E_p
  Expected expected(numPreds);
  TO_EACH (FeatureMap, lambda, lit) {
    Feature const& f = lit->first;
    expected[f.first].push_back(make_pair(f.second, 0.0));
  }

  // logObserved[i] = log(observed[i] - alpha)
  TO_EACH (FeatureMap, logObserved, oit) {
    oit->second = log(oit->second - alpha);
  }

# ifdef SLACK
  // compute the expected value of correction
  int cfvalSum = 0;
  FOR_EACH (EventMap, eventMap, it) {
    int evOccurred = it->second;
    ClassID oID = it->first.first;
    const vector<PID>& predicates = it->first.second;
    cfvalSum += (correctionConstant - predicates.size()) * evOccurred;
  }
  cfObservedExpect = (cfvalSum == 0) ? log(NEAR_ZERO) : log((double)cfvalSum);
# endif

  /***************** Estimate the model parameters ************************/

  double* prob = new double[numOutcomes];

  double prevSumLogProb = 0.0;
  for (int i = 0; i < iterations; i++) {
    int correct;
    double sumLogProb = update(expected, prob, correct);
    if (verbose)
      cerr << setw(3) << i+1 <<  ": logProb = " << sumLogProb <<
	" correct = " << correct * 100. / numEvents << "%" << endl;
    if (i > 0 && sumLogProb - prevSumLogProb <= LLThreshold)
      break;
    prevSumLogProb = sumLogProb;

    // update lambdas
    // lambda[k] = max(0, lambda[k] + log((observed[k] - alpha)/expected[k]) / fSharp)
    // Go through all k scanning expected:
    for (PID pID = 0; pID < numPreds; pID++) {
      TO_EACH (Expected::value_type, expected[pID], eit) {
	Feature k(pID, eit->first);
#	ifdef SLACK
	lambda[k] += (logObserved[k] - log(eit->second));
#	else
	lambda[k] += (logObserved[k] - log(eit->second)) / fSharp;
	lambda[k] = MAX(0.0, lambda[k]);
#	endif
 	eit->second = 0.0;	// clear for next iteration
      }
	}
  }

  // free memory
  delete[] prob;
  expected.clear();
  logObserved.clear();
  eventMap.clear();
}

/**
 * Compute one iteration of GIS and return log-likelihood.
 */
double GIS::update(Expected& expected, double prob[], int& correct)
{
  // assert: expected[*, *] is assumed to be 0.
  // compute contribution of p(c|b_i) for each feature

  correct = 0;
  double loglikelihood = 0.0;
  double CFMOD = 0.0;
  // expected[i, c] = SUM(j, oc(xj) p(c|xj) fi(xj, c))
  // for each (possibly multiple) event
  FOR_EACH (EventMap, eventMap, it) {
    ClassID outcome = it->first.first;
    int evOccurred = it->second;
    const vector<PID>& xj = it->first.second;
    int oc = it->first.first;
    // prob[c] = p(c|xj)
    ClassID best = estimate(xj, prob);
    if (best == outcome)
      correct += evOccurred;
    // add contribution of xj to each class according to its probability
    for (unsigned i = 0; i < xj.size(); i++) {
      int pID = xj[i];
      TO_EACH (Expected::value_type, expected[pID], eit) {
	ClassID c = eit->first;
	double d = prob[c] * evOccurred;
	eit->second += d; // expected[pID, c]
      }
#     ifdef SLACK
      for (ClassID oid = 0; oid < numOutcomes; oid++) {
	if (lambda.find(Feature(pID, oid)) == lambda.end())
	  CFMOD += prob[oid] * evOccurred;
      }
#     endif
    }
    loglikelihood += log(prob[oc]) * evOccurred;
#   ifdef SLACK
    CFMOD += (correctionConstant - xj.size()) * evOccurred;
#   endif
  }
# ifdef SLACK
  if (CFMOD > 0.0) 
    correctionParam += cfObservedExpect - log(CFMOD);
# endif
  return loglikelihood;
}

} // namespace Classifier
} // namespace Tanl
