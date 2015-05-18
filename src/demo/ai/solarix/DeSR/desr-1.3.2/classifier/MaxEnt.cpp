/*
**  Tanl
**  classifier/MaxEnt.cpp
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

#include "MaxEnt.h"

// Standard
#include <math.h>
#include <fcntl.h>		/* for open(2), O_RDONLY, etc */
#include <sys/stat.h>		/* for stat(2) */
#ifdef _WIN32
#include <windows.h>
#include <float.h>
#include "lib/strtok_r.h"
#define isinf(x)	(_isnan(x) ? 0 : (_fpclass(x) == _FPCLASS_NINF) ? -1 : (_fpclass(x) == _FPCLASS_PINF) ? 1 : 0)
#else
#include <sys/mman.h>
#endif

#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <assert.h>
#include <limits.h>
#include <algorithm>

using namespace std;

namespace Tanl {
namespace Classifier {

MaxEnt::MaxEnt(char const* file)
{
  ifstream ifs(file);
  load(ifs);
}

MaxEnt::MaxEnt(istream& ifs)
{
  load(ifs);
}

MaxEnt::~MaxEnt()
{
  FOR_EACH (vector<char const*>, outcomeLabels, it)
    free((void*)*it);
}

void MaxEnt::read(EventStream& eventStream)
{
  // create inverted index of predicate names
  // used to create vector of pIDs
  int evCount = events.size();
  while (eventStream.hasNext()) {
    if (verbose) {
      if (++evCount % 10000 == 0)
	cerr << '+' << flush;
      else if (evCount % 1000 == 0)
	cerr << '.' << flush;
    }
    Event* ev = eventStream.next();
    events.push_back(ev);
    readEvent(ev);
  }
}

void MaxEnt::readEvent(Event* ev)
{
# ifdef DEBUG
  cerr << *ev << endl;
# endif
  Features& ec = ev->features;
  // ec = {p1, ... , pn}
  for (unsigned j = 0; j < ec.size(); j++) {
    string& pred = ec[j];
    // decide whether to retain it (# occurrences > cutoff)
    if (predIndex.find(pred.c_str()) == predIndex.end()) {
      // not yet among those retained
      WordCounts::iterator wcit = counter.find(pred);
      // increment # of occurrences
      unsigned count;
      if (wcit == counter.end())
	count = counter[pred] = 1;
      else
	count = ++wcit->second;
      if (count >= cutoff) {
	predLabels.push_back(pred); // accept it into predLabels
	predIndex[pred.c_str()] = pID++;
	counter.erase(pred);
      }
    }
  }
}

#define VISIBLE
#ifdef VISIBLE
#define LOAD(var, type)   is >> var
#define SAVE(ofs, var)    ofs << var << endl;
#else
#define LOAD(var, type)   is.read(line, sizeof(type)); var = *(type*)line;
#define SAVE(ofs, var)    ofs.write((char*)&var, sizeof(var))
#endif

typedef map<vector<ClassID>, vector<PID> > Groups;

/**
 * Format for the GIS maxent (.mem) files.
 * This format can be memory mapped.
 *
 * 1. GIS (model type identifier)
 * 
 * 2. the correction constant (int)
 * 
 * 3. the correction parameter (double)
 * 
 * 4. # of outcomes (int)
 *    - list of outcome names (string)
 * 
 * 5. # of predicates (int)
 *    - list of predicate names (string)
 *
 * 6. parameters
 *    - # of groups (i.e. predicates with same set of outcomes)
 *    - The following repeated for each group
 *      a. group size (gs), # group outcomes
 *	- The following repeated for each outcome:
 *         1. outcome (i)
 *         2. param[n + j, i], for 0 <= j < gs
 *
 * Example of 5. and 6.:
 *	7(# preds)
 *	Sunny(first pred. name)
 *	Happy
 *	Dry
 *	Humid
 *	Sad
 *	Cloudy
 *	Rainy
 *	3(# groups)
 *	1 1(group 1: 1 predicate, 1 outcome)
 *	0(outcome 0)
 *	2.4005893(param[0, 0])
 *	5 2(group 2: 5 predicates, 2 outcomes)
 *	0(outcome 0)
 *	2.1392054(param[1, 0])
 *	-0.3270814(param[2, 0])
 *	0.2927261(param[3, 0])
 *	-1.9319866(param[4, 0])
 *	1.1981091(param[5, 0])
 *	1(outcome 1)
 *	-4.7484765(param[1, 1])
 *	0.3342510(param[2, 1])
 *	-0.3882752(param[3, 1])
 *	2.0065205(param[4, 1])
 *	-2.1725304(param[5, 1])
 *	1 1(group 3: 1 predicate, 1 outcome)
 *	1(outcome 1)
 *	3.5907883(param[6, 1])
 */
void MaxEnt::save(char const* file)
{
  ofstream ofs(file, ios::binary | ios::trunc);

  // the type of model
  SAVE(ofs, "GIS");

  // the correction constant
  SAVE(ofs, correctionConstant);

  // the correction parameter
  SAVE(ofs, correctionParam);

  // the outcome names
  SAVE(ofs, numOutcomes);
  for (ClassID i = 0; i < numOutcomes; i++)
    SAVE(ofs, outcomeLabels[i]);

  // group parameters by outcomes, so that we can write them more compactly
  Groups groups;
  for (PID pid = 0; pid < numPreds; pid++) {
    // collect parameters having the same outcomes
    vector<ClassID> outcomes;
    for (ClassID oid = 0; oid < numOutcomes; oid++) {
      FeatureMap::const_iterator rit = lambda.find(make_pair(pid, oid));
      if (rit != lambda.end())
	outcomes.push_back(oid);
    }
    groups[outcomes].push_back(pid);
  }
  // predicate names ordered according to grouping
  SAVE(ofs, numPreds);
  FOR_EACH (Groups, groups, git) {
    FOR_EACH (vector<PID>, git->second, pids) {
      SAVE(ofs, predLabels[*pids]);
    }
  }
  // # groups
  unsigned numGroups = groups.size();
  SAVE(ofs, numGroups);
  FOR_EACH (Groups, groups, git) {
    // group size
    unsigned gSize = git->second.size();
    SAVE(ofs, gSize);
    // # outcomes in group
    unsigned numOc = git->first.size();
    SAVE(ofs, numOc);
    FOR_EACH (vector<ClassID>, git->first, oids) {
      // outcome
      SAVE(ofs, *oids);
      FOR_EACH (vector<PID>, git->second, pids) {
	double param = lambda[make_pair(*pids, *oids)];
	SAVE(ofs, param);
      }
    }
  }
}

#define LINE 16384

#define HEADER "#txt,maxent"

/**
 * Load model from stream.
 */
void MaxEnt::load(istream& is)
{
  char line[LINE];
  is >> line;
  if (::strncmp(line, HEADER, sizeof(HEADER)-1) == 0) {
    correctionConstant = 1;     // not present in Zhang
    correctionParam = 0.0;
    loadZhang(is);
    return;
  } else if (::strcmp(line, "GIS"))
    throw FileError("wrong file format");

  // the correction constant
  LOAD(correctionConstant, int);

  // the correction parameter
  LOAD(correctionParam, double);

  // the outcome names
  LOAD(numOutcomes, int);
  outcomeLabels.resize(numOutcomes);
  for (ClassID i = 0; i < numOutcomes; i++) {
    is >> line;
    outcomeLabels[i] = strdup(line);
  }

  // the predicate names
  LOAD(numPreds, int);
  predLabels.resize(numPreds);
  for (PID i = 0; i < numPreds; i++) {
    is >> line;
    predIndex[line] = i;	// label -> pID
    predLabels[i] = line;	// pID -> label
  }

  PID pid = 0;
  // read # groups
  int numGroups;
  LOAD(numGroups, int);
  while (numGroups--) {
    // read group size
    int gSize;
    LOAD(gSize, int);
    // read # group outcomes
    int gOutcomes;
    LOAD(gOutcomes, int);
    while (gOutcomes--) {
      // read outcome ID
      ClassID oid;
      LOAD(oid, ClassID);
      for (int i = 0; i < gSize; i++) {
	// read param
	double param;
	LOAD(param, double);
	lambda[make_pair((PID)(pid + i), oid)] = param;
      }
    }
    pid += gSize;
  }
}

void MaxEnt::loadZhang(istream& f)
{
  char line[LINE];

  // skip header comments
  do {
    f.getline(line, LINE);
  } while (line[0] == '\0' || line[0] == '#');

  // read feature names
  numPreds = atoi(line);
  predLabels.resize(numPreds);
  for (size_t i = 0; i < numPreds; ++i) {
    f.getline(line, LINE);
    predIndex[line] = i;	// label -> pID
    predLabels[i] = line; // pID -> label
  }

  // read outcomes
  f.getline(line, LINE);
  numOutcomes = atoi(line);
  outcomeLabels.resize(numOutcomes);
  for (size_t i = 0; i < numOutcomes; ++i) {
    f.getline(line, LINE);
    outcomeLabels[i] = strdup(line);
  }

  // read feature map
  size_t fid = 0;
  vector<pair<ClassID, size_t> > pairs;
  for (unsigned i = 0; i < numPreds; ++i) {
    f.getline(line, LINE);
    char* next = line;
    char const* tok = strtok_r(0, " ", &next);
    // skip count which is only used in binary format
    while ((tok = strtok_r(0, " ", &next))) {
      ClassID oid = atoi(tok);
      pairs.push_back(make_pair(i, oid));
      fid++;
    }
  }

  // load theta (i.e. lambda)
  f.getline(line, LINE);
  int m_n_theta = atoi(line);
  assert(fid == m_n_theta);

  for (int i = 0; i < m_n_theta && f.getline(line, LINE); i++)
    lambda[pairs[i]] = atof(line);
}

/**

 *  The input array contains a set of log probabilities lp1, lp2, lp3 ...
 *  @return  the log of the sum of the probabilities:
 *	log(e^lp1 + e^lp2 + e^lp3 + ...)
 */
double sumLogProb(double logprobs[], int n)
{
  double max = 0;
  int i;
  for (i = 0; i < n; i++) {
    if (i==0 || logprobs[i] > max)
      max = logprobs[i];
  }
  if (isinf(max)) // the largest probability is 0 (log prob= -inf)
    return max;   // return log 0
  double p = 0;
  for (i = 0; i < n; i++) {
    p += exp(logprobs[i] - max);
  }
  return max + log(p);
}

ClassID MaxEnt::estimate(const std::vector<PID>& predicates, double prob[])
{
  // p(a|b) = exp(SUM(j=1..k, L_j * f_j(a, b))) / Z
  // where Lj = log(w_j)
  //
  // Here prob[a] = p(a|context)
  //
  // We must add lambda[pID, oid] for all pID present in event (a, b)
  double iprob = 1.0 / numOutcomes;
  double fSharp = correctionConstant;
  int* numFeats = new int[numOutcomes];
  for (ClassID oid = 0; oid < numOutcomes; oid++) {
#   ifdef SLACK
    prob[oid] = iprob;
    numFeats[oid] = 0;
#   else
    prob[oid] = 0;
#   endif
    for (unsigned i = 0; i < predicates.size(); i++) {
      PID pID = predicates[i];
      FeatureMap::const_iterator rit = lambda.find(make_pair(pID, oid));
      if (rit != lambda.end()) {
#       ifdef SLACK
	prob[oid] += rit->second / fSharp;
	numFeats[oid]++;
#       else
	prob[oid] += rit->second;
#       endif
      }
    }
  }
  // normalize
  ClassID best = 0;
  double max_prob = 0.0;
  double sum = 0.0;
  for (ClassID oid = 0; oid < numOutcomes; oid++) {
#   ifdef SLACK
    prob[oid] = exp(prob[oid] +
		    (1.0 - (double)numFeats[oid] / correctionConstant)
		    * correctionParam);
#   else
    prob[oid] = exp(prob[oid]);
#   endif
    sum += prob[oid];
    if (prob[oid] >= max_prob) {
      max_prob = prob[oid];
      best = oid;
    }
  }
  for (ClassID oid = 0; oid < numOutcomes; oid++) {
    prob[oid] /= sum;
  }

  // free memory
  delete[] numFeats;

  return best;
}

ClassID MaxEnt::BestOutcome(double* ocs) const
{
  ClassID best = 0;
  for (ClassID i = 1; i < numOutcomes; i++)
    if (ocs[i] > ocs[best]) best = i;
  return best;
}

ostream& operator <<(ostream& s, MaxEnt const& m)
{
  FOR_EACH (FeatureMap, m.lambda, fit) {
    Feature const& f = fit->first;
    PID pid = f.first;
    ClassID cid = f.second;
    s << "lambda(" << m.OutcomeName(cid) << ", " << m.PredicateName(pid) << ")="
      << setprecision(4) << fit->second << endl;
  }
  return s;
}

// ======================================================================
struct clearedContext {
  bool operator()(const vector<PID>& c) const {
    return c.empty();
  }
};

struct clearedNumber {
  bool operator()(const unsigned& n) const {
    return n == UINT_MAX;
  }
};

// Build a map of events.
// It consumes and deletes events.
int MaxEnt::buildIndex(list<Event*>& events,
		       Text::WordIndex& predIndex,
		       EventMap& eventMap,
		       vector<char const*>& outcomeLabels,
		       int evCutoff, bool verbose)
{
  vector<PID> pIDs;
  int evCount = 0;
  if (verbose)
    cerr << endl		// end read();
	 << "Building index.." << endl;
  while (!events.empty()) {
    if (verbose) {
      if (++evCount % 10000 == 0)
	cerr << '+' << flush;
      else if (evCount % 1000 == 0)
	cerr << '.' << flush;
    }
    Event* ev = events.front();
    events.pop_front();

    // fill array pIDs with all retained predicate IDs of this event
    pIDs.clear();
    FOR_EACH (Features, ev->features, pit) {
      Text::WordIndex::const_iterator it = predIndex.find(pit->c_str());
      if (it != predIndex.end())
	pIDs.push_back(it->second);
    }

    size_t k = pIDs.size();
    if (k == 0 && !ev->features.empty()) {
      // drop events with no active features
      cerr << "Dropped event [";
      FOR_EACH (Features, ev->features, pit)
	cerr << *pit << " ";
      cerr << "]" << endl;
    } else {
      // add outcome name to outcomeLabels, if not present.
      // Position in outcomeLabels becomes its classID
      ClassName& className = ev->className;
      ClassID ocID = (ClassID)-1;
      FOR_EACH (vector<char const*>, outcomeLabels, cit)
	if (*cit == className) {
	  ocID = cit - outcomeLabels.begin();
	  break;
	}
      if (ocID == (ClassID)-1) { // not found, add it
	ocID = outcomeLabels.size();
	outcomeLabels.push_back(::strdup(className.c_str()));
      }

      // ensure uniqueness
      sort(pIDs.begin(), pIDs.end());
      eventMap[make_pair(ocID, pIDs)]++;
    }
    delete ev;
  }
  if (verbose)
    cerr << endl;
  int numEvents = 0;
  // remove events whose count < evCutoff
  for (EventMap::iterator it = eventMap.begin(); it != eventMap.end(); ) {
    int count = it->second;
    if (count < evCutoff)
      eventMap.erase(it);
    else {
      numEvents += count;
      ++it;
    }
  }
  if (verbose) {
    cerr << "\t    Number of events: " << evCount << endl;
    cerr << "\t       Unique events: " << eventMap.size() << endl;
    cerr << "\t   Number of Classes: " << outcomeLabels.size() << endl;
    cerr << "\tNumber of Predicates: " << predIndex.size() << endl;
  }
  return numEvents;
}

} // namespace Classifier
} // namespace Tanl
