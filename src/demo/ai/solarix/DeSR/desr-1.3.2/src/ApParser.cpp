/*
**  DeSR
**  src/ApParser.cpp
**  ----------------------------------------------------------------------
**  Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of DeSR.
**
**  DeSR is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  DeSR is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

// Must go first
#include "State.h"
#include "Parser.h"

#ifdef _WIN32
#include "lib/strtok_r.h"
#endif

// IXE library
#include "conf/conf_int.h"
#include "conf/conf_float.h"
#include "text/WordIndex.h"

#include "ap.h"
#include "EventStream.h"
#include "ReviseEventStream.h"

// standard
#include <list>

// define this for using the full sparse version
//#define APSV APS

using namespace std;

namespace Parser {

struct ApConfig : public ParserConfig
{
  ApConfig(IXE::Configuration::Params& params) :
    ParserConfig(params),	// inclue generic parameters
    apIterations	("ApIterations", 20, params),
    apPercent		("ApPercent", 0.1F, params),
    partitionSize	("ApPartition", 1, params)
  { }

  /** Maximumm number of iterations to perform */
  IXE::conf<int>	apIterations;
  /** Termination threshold */
  IXE::conf<float> apPercent;
  /** Split training cases into partitions of this size */
  IXE::conf<int>	partitionSize;
};

// ======================================================================
// Ap version

/**
 *	@ingroup parser
 *
 *	Parser class using an Averaged Perceptron classifier.
 */
struct ApParser : public Parser
{
  ApParser(char const* modelFile);

  void	train(SentenceReader* sentenceReader, char const* modelFile);
  Sentence* parse(Sentence* sentence);
  void	revise(SentenceReader* sentenceReader, char const* actionFile = 0);

  APSV		ap;		///< model
  int		iter;		///< number of iterations

  ApConfig	config;		///< full configuration (inherits from ParseConfig)
};

/**
 *	@ingroup parser
 *
 *	Constructor for ApParser
 */
Parser*	ApParserFactory(char const* modelFile = 0)
{
  return new ApParser(modelFile);
}

REGISTER_PARSER(AP, ApParserFactory);

ApParser::ApParser(char const* modelFile) :
  Parser(ap.predIndex, config),
  config(params)		// params is inherited from Parser
{
  if (!modelFile)
    return;			// training
  ifstream ifs(modelFile);
  if (!ifs)
    throw IXE::FileError(string("Missing model file: ") + modelFile);
  // load header
  config.load(ifs);
  ap.load(ifs);
  // read entities
  info.load(ifs);
}

void ApParser::train(SentenceReader* sentenceReader, char const* modelFile)
{
  WordIndex		labelIndex;
  vector<string>	labels;

  vector<string>	predLabels;

  // collect events
  list<Tanl::Classifier::Event*>	events;

  WordCounts		predCount; // count predicate occurrences
  int evCount = 0;
  Tanl::Classifier::PID pID = 1;		// leave 0 for bias
  // create inverted index of predicate names
  // used to create vector of pIDs
  EventStream eventStream(sentenceReader, &info);
  while (eventStream.hasNext()) {
    Tanl::Classifier::Event* ev = eventStream.next();
    events.push_back(ev);
    evCount++;		      // count them explicitly, since size() is costly
    if (config.verbose) {
      if (evCount % 10000 == 0)
	cerr << '+' << flush;
      else if (evCount % 1000 == 0)
	cerr << '.' << flush;
    }
    vector<string>& ec = ev->features; // ec = {p1, ... , pn}
    for (unsigned j = 0; j < ec.size(); j++) {
      string& pred = ec[j];
      // decide whether to retain it (# occurrences > cutoff)
      if (predIndex.find(pred.c_str()) == predIndex.end()) {
	// not yet among those retained
	WordCounts::iterator wcit = predCount.find(pred);
	// increment # of occurrences
	int count;
	if (wcit == predCount.end())
	  count = predCount[pred] = 1;
	else
	  count = ++wcit->second;
	if (count >= config.featureCutoff) {
	  predLabels.push_back(pred); // accept it into predLabels
	  predIndex[pred.c_str()] = pID++;
	  predCount.erase(pred);
	}
      }
    }
  }
  if (config.verbose)
    cerr << endl;

  // build cases
  Cases cases;
  cases.reserve(evCount);
  int n = 0;
  Tanl::Classifier::ClassID oID = 0;
  while (!events.empty()) {
    Tanl::Classifier::Event* ev = events.front();
    events.pop_front();
    cases.push_back(Case());
    X& x = cases[n].first;	// features
    // add features
    vector<string>& ec = ev->features; // ec = {p1, ... , pn}
    char const* c = ev->className.c_str();
    for (unsigned j = 0; j < ec.size(); j++) {
      string& pred = ec[j];
      WordIndex::const_iterator pit = predIndex.find(pred.c_str());
      if (pit != predIndex.end()) {
	x.push_back(pit->second);
      }
    }
    if (x.size()) {
      if (labelIndex.find(c) == labelIndex.end()) {
	labelIndex[c] = oID++;
	labels.push_back(c);
      }
      cases[n].second = labelIndex[c];
      n++;
      if (config.verbose) {
	if (n % 10000 == 0)
	  cerr << '+' << flush;
	else if (n % 1000 == 0)
	  cerr << '.' << flush;
      }
      x.push_back(0);		// bias
    }
    delete ev;
  }
  cases.resize(n);
  if (config.verbose)
    cerr << endl;

  int predSize = predLabels.size();
  predSize++;			// bias
  APSV ap(labels.size(), predSize);
  
  ofstream ofs(modelFile, ios::binary | ios::trunc);
  // dump configuration settings
  config.writeHeader(ofs);
  // dump labels
  ofs << labels.size() << endl;
  FOR_EACH (vector<string>, labels, pit)
    ofs << *pit << endl;
  // dump predLabels
  ofs << predLabels.size() << endl;
  FOR_EACH (vector<string>, predLabels, pit)
    ofs << *pit << endl;
  // free memory
  predIndex.clear();
  WordIndex().swap(predIndex); // STL map do not deallocate. resize(0) has no effect
  labelIndex.clear();
  WordIndex().swap(labelIndex);
  // clear memory for unfrequent entities
  info.clearRareEntities();
  // perform training
  ap.train(cases, iter);
  // dump parameters
  ap.save(ofs);
  // dump global info
  info.save(ofs);
}

Sentence* ApParser::parse(Sentence* sentence)
{
  preprocess(sentence);
  ParseState state(*sentence, &info, predIndex);

  while (state.hasNext()) {
    Tanl::Classifier::Context& pIDs = *state.next();
    X x;
    x.push_back(0);		// bias
    // fill example from context
    for (unsigned i = 0; i < pIDs.size(); i++) {
      x.push_back(pIDs[i]);
    }
    Y prediction = ap.predict(x);
    string& outcome = ap.labels[prediction];
    if (!state.transition(outcome.c_str()))
      state.transition("S");
  }
  return state.getSentence();
}

void ApParser::revise(SentenceReader* sentenceReader, char const* actionFile)
{
  if (actionFile) {
    // read an action file
    ifstream ifs(actionFile);

    ReviseContextStream contextStream(sentenceReader, predIndex);

    char line[4000];
    while (contextStream.hasNext()) {
      ++contextStream.cur;
      ifs.getline(line, sizeof(line));
      char* next = line;
      char const* outcome = strtok_r(0, " \t", &next);
      contextStream.actions.push_back(outcome);
    }
  } else {
    ReviseContextStream contextStream(sentenceReader, predIndex);

    while (contextStream.hasNext()) {
      Tanl::Classifier::Context& pIDs = *contextStream.next();
      X x;
      x.push_back(0);		// bias
      // fill example from context
      for (unsigned i = 0; i < pIDs.size(); i++) {
	x.push_back(pIDs[i]);
      }
      FeatureID prediction = ap.predict(x);
      string& outcome = ap.labels[prediction];
      contextStream.actions.push_back(outcome);
    }
  }
}

} // namespace Parser
