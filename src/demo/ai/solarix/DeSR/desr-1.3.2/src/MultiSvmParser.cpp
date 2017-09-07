/*
**  DeSR
**  src/MultiSvmParser.cpp
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
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

/// ======================================================================
/// libSVM version

// Must be first, since it includes <Python.h>
#include "State.h"
#include "Parser.h"
#include "EventStream.h"
#include "svm.h"

// library
#include "conf/conf_string.h"

// standard
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif



#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

#define MAX_LINE_LEN 8196

namespace Parser {

struct MultiSvmConfig : public ParserConfig
{
  MultiSvmConfig(IXE::Configuration::Params& params) :
    ParserConfig(params),	// inclue generic parameters
    svmParams("SvmParams", "-t 1 -d 2 -g 0.2 -c 0.4 -e 0.1"),
    svmSkip("SvmSkip", 0)
  { }

  /** Parameters passed to libSVM. */
  IXE::conf<string>	svmParams;

  /** Temporay: resume skipping these many svm_models, already generated */
  IXE::conf<int>	svmSkip;
};

/**
 *	@ingroup parser
 *
 *	Parser using two SVM classifiers, provided by libsvm, one to predict
 *	the action, one to predict the label.
 */
struct MultiSvmParser : public Parser
{
  MultiSvmParser(char const* modelFile);

  ~MultiSvmParser() {
    for (unsigned i = 0; i < model.size(); i++)
      svm_free_and_destroy_model(&model[i]);
  }

  void	train(SentenceReader* sentenceReader, char const* modelFile);
  Sentence* parse(Sentence* sentence);
  //void	revise(SentenceReader* sentenceReader, char const* actionFile = 0);

  WordIndex		classIndex;
  vector<string>	classLabels;
  vector<struct svm_model*>	model;
  MultiSvmConfig	config;
};

/**
 *	@ingroup parser
 *
 *	Constructor for MultiSvmParser
 */
Parser*	MultiSvmParserFactory(char const* modelFile = 0)
{
  return new MultiSvmParser(modelFile);
}

REGISTER_PARSER(MSVM, MultiSvmParserFactory);

extern void parseParameters(svm_parameter& param, char* parameters);

static int compare_nodes(const void* a, const void* b) {
  return ((svm_node const*)a)->index - ((svm_node const*)b)->index;
}

  static const char* actType = "AD";

  enum ActionType { Shift, Reduce };

MultiSvmParser::MultiSvmParser(char const* modelFile) :
  Parser(predIndex, config),
  config(params)		// params is inherited from Parser
{
  if (!modelFile)
    return;			// training
  ifstream ifs(modelFile);
  if (!ifs)
    throw IXE::FileError(string("Missing model file: ") + modelFile);;
  // load header
  config.load(ifs);
  // load class labels
  char line[MAX_LINE_LEN];
  if (!ifs.getline(line, MAX_LINE_LEN))
      throw IXE::FileError(string("Wrong file format: ") + modelFile);
  int len = atoi(line);
  int n = 0;
  while (len--) {
    if (!ifs.getline(line, MAX_LINE_LEN))
      throw IXE::FileError(string("Wrong file format: ") + modelFile);
    classIndex[(char const*)line] = n++;
    classLabels.push_back(line);
  }
  // load pred labels
  if (!ifs.getline(line, MAX_LINE_LEN))
    throw IXE::FileError(string("Wrong file format: ") + modelFile);
  len = atoi(line);
  n = 0;
  while (len--) {
    if (!ifs.getline(line, MAX_LINE_LEN))
      throw IXE::FileError(string("Wrong file format: ") + modelFile);
    predIndex[(char const*)line] = n++;
  }

  int models = 2;
  model.resize(models);
  for (int i = 0; i < models; i++) {
    string modeliFile = (string(modelFile) + '.') + actType[i];
    model[i] = svm_load_model(modeliFile.c_str());
    if (!model[i])
      throw IXE::FileError(string("can't open model file: ") + modeliFile);
  }
  // read entities
  ifstream ent(modelFile);
  if (!ent)
    throw IXE::FileError(string("Missing entities file: ") + modelFile);
  info.load(ent);
}

void MultiSvmParser::train(SentenceReader* sentenceReader, char const* modelFile)
{
  WordIndex		labelIndex;
  vector<string>	labels;

  vector<string>	predLabels;

  // collect events
  list<Tanl::Classifier::Event*>	events;

  WordCounts		predCount; // count predicate occurrences

  int actionCount[2] = {0, 0};		// count actions
  int prevAction = Shift;		// 

  int evCount = 0;
  Tanl::Classifier::PID pID = 0;
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
    actionCount[prevAction]++;
    char a = toupper(ev->className[0]);
    prevAction = ActionType(a == 'R' || a == 'L');
  }
  if (config.verbose)
    cerr << endl;

  // build problems
  int models = 2;		// 0: action, 1: deplink
  vector<svm_problem> problem(models);
  for (int i = 0; i < models; i++) {
    int size = actionCount[i];
    problem[i].y = new double[size];
    problem[i].x = new svm_node*[size];
    problem[i].l = 0;
  }
  prevAction = Shift;
  int nTot = 0;
  Tanl::Classifier::ClassID oID = 0;
  while (!events.empty()) {
    Tanl::Classifier::Event* ev = events.front();
    events.pop_front();
    char const* c = ev->className.c_str();
    // add features
    vector<string>& ec = ev->features; // ec = {p1, ... , pn}
    svm_node* preds = new svm_node[ec.size()+1];
    unsigned k = 0;
    for (unsigned j = 0; j < ec.size(); j++) {
      string& pred = ec[j];
      WordIndex::const_iterator pit = predIndex.find(pred.c_str());
      if (pit != predIndex.end()) {
	svm_node& node = preds[k++];
	node.index = pit->second + 1; // indexes are numbered from 1
	node.value = 1.0;
      }
    }
    if (k) {
      // sort by node.index
      qsort(preds, k, sizeof(svm_node), compare_nodes);
      // add end of vector
      svm_node& node = preds[k++];
      node.index = -1;
      node.value = 1.0;
      if (labelIndex.find(c) == labelIndex.end()) {
	labelIndex[c] = oID++;
	labels.push_back(c);
      }
      int i = prevAction; // choose model according to previous action
      int& ni = problem[i].l;
      problem[i].y[ni] = labelIndex[c]; // assigned ID to class name
      // free cutoff features
      preds = (svm_node*)realloc(preds, k * sizeof(svm_node));
      problem[i].x[ni] = preds;
      ni++;
      nTot++;
      if (config.verbose) {
	if (nTot % 10000 == 0)
	  cerr << '+' << flush;
	else if (nTot % 1000 == 0)
	  cerr << '.' << flush;
      }
    } else {
      cerr << "Discarded event" << endl;
      delete preds;
    }
    char a = toupper(c[0]);
    prevAction = ActionType(a == 'R' || a == 'L');
    delete ev;
  }
  // FIXME: might free space in problem.x for dropped events
  if (config.verbose)
    cerr << endl;

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
  predIndex = WordIndex(); // STL map do not deallocate. resize(0) has no effect
  labelIndex.clear();
  labelIndex = WordIndex();
  // clear memory for unfrequent entities
  info.clearRareEntities();
  // setup parameters
  svm_parameter param;
  parseParameters(param, config.svmParams);
  // redirect stdout to stderr, where libsvm outputs progress info
  if (dup2(fileno(stderr), fileno(stdout)) < 0)
    cerr << "could not redirect stdout to stderr" << endl;
  // perform training
  for (int i = 0; i < models; i++) {
    struct svm_model* model = svm_train(&problem[i], &param);
    // dump model
    string modeliFile = (string(modelFile) + '.') + actType[i];
    svm_save_model(modeliFile.c_str(), model);
    // free space
    svm_free_and_destroy_model(&model);
    for (int j = problem[i].l - 1; j >= 0 ; j--)
      delete [] problem[i].x[j];
    delete [] problem[i].x;
    delete [] problem[i].y;
  }
  svm_destroy_param(&param);
}

Sentence* MultiSvmParser::parse(Sentence* sentence)
{
  int prevAction = Shift;
  vector<svm_node> nodes(predIndex.size());
  preprocess(sentence);
  ParseState state(*sentence, &info, predIndex);
  while (state.hasNext()) {
    Tanl::Classifier::Context& preds = *state.next();
    // fill example from context
    sort(preds.begin(), preds.end());
    nodes.resize(preds.size() + 1);
    int j = 0;
    FOR_EACH (vector<Tanl::Classifier::PID>, preds, pit) {
      nodes[j].index = *pit + 1; // features start at 1
      nodes[j++].value = 1.0;
    }
    nodes[preds.size()].index = -1;	// termination
    int i = prevAction; // choose model according to previous action
    double prediction = svm_predict(model[i], &nodes[0]);
    string& outcome = classLabels[(int)prediction];
#   ifdef DUMP
    cerr << classIndex[rightOutcome];
    FOR_EACH (vector<Tanl::Classifier::PID>, preds, pit)
      cerr << " " << *pit << ":1";
    cerr << endl;
#   endif
    // update action sequence
    char a = toupper(outcome[0]);
    prevAction = ActionType(a == 'R' || a == 'L');
    if (!state.transition(outcome.c_str())) {
      state.transition("S");
    }
  }
  return state.getSentence();
}

} // namespace Parser
