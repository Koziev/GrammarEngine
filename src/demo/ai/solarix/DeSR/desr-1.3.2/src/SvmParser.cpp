/*
**  DeSR
**  src/SvmParser.cpp
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
#include "conf_feature.h"

// IXE library
#include "conf/conf_string.h"
#include "include/unordered_map.h"

// standard
#include <algorithm>
#ifdef _WIN32
#include <functional>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include "lib/strtok_r.h"
#else
#include <ext/functional>
#include <unistd.h>
#endif

#include <iostream>
#include <list>

using namespace std;

#define MAX_LINE_LEN 8196

namespace Parser {

struct SvmConfig : public ParserConfig
{
  SvmConfig(IXE::Configuration::Params& params) :
    ParserConfig(params),	// inclue generic parameters
    svmParams("SvmParams", "-t 1 -d 2 -g 0.2 -c 0.4 -e 0.1"),
    svmSkip("SvmSkip", 0)
  { }

  /** Parameters passed to libSVM. */
  IXE::conf<string>	svmParams;

  /** Temporay: resume skipping these many svm_models, already generated */
  IXE::conf<int>	svmSkip;
};

/** Use composite Action+Deprel as predicted outcome */
extern IXE::conf<bool>	CompositeActions;

extern conf_features	SplitFeature;

/**
 *	@ingroup parser
 *
 *	Parser using an SVM classifier, provided by libsvm.
 */
struct SvmParser : public Parser
{
  SvmParser(char const* modelFile);

  ~SvmParser() {
    for (unsigned i = 0; i < model.size(); i++)
      svm_free_and_destroy_model(&model[i]);
  }

  void		train(SentenceReader* sentenceReader, char const* modelFile);
  Sentence*	parse(Sentence* sentence);
  //void	revise(SentenceReader* sentenceReader, char const* actionFile = 0);

  WordIndex		splits;	///< IDs of split groups
  vector<string>	splitNames; ///< names of all splits
  unordered_map<char, char>	splitGroup; ///< renumbering of grouped splits

  WordIndex		predIndex;
  WordIndex		classIndex;
  vector<string>	classLabels;
  vector<svm_model*>	model;
  SvmConfig		config;

private:
  void	collectEvents(Enumerator<Sentence*>& sentenceReader,
		      char const* modelFile,
		      vector<svm_problem>& problem);

  /**	@return whether model splitting is required. */
  bool		splitModel() { return !config.SplitFeature->empty(); }
};

static char* mkext(char* ext, int i)
{
  ext[0] = '.'; ext[1] = 'a' + i/26; ext[2] = 'a' + (i%26); ext[3] = '\0';
  return ext;
}

SvmParser::SvmParser(char const* modelFile) :
  Parser(predIndex, config),
  config(params)
{
  if (!modelFile)
    return;			// training
  ifstream ifs(modelFile);
  if (!ifs)
    throw IXE::FileError(string("Missing symbols file: ") + modelFile);
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
  // load split labels and groups
  if (!ifs.getline(line, MAX_LINE_LEN))
    throw IXE::FileError(string("Wrong file format: ") + modelFile);
  len = atoi(line);
  n = 0;
  int models = 0;
  int skipGroup = (len != 0);
  while (len--) {
    ifs.getline(line, MAX_LINE_LEN);
    char* next = line;
    // handle special case of empty code (test for ' ' for back compatibility)
    char* code = (line[0] == ' ' || line[0] == '\t') ? (char*)"" : strtok_r(0, " \t", &next);
    splits.insert(code);
    splitNames.push_back(code);
    code = strtok_r(0, " \t", &next);
    int group = atoi(code);
    splitGroup[n] = group;
    models = max(models, group);
    if (group == 0) skipGroup = 0;
    n++;
  }
  models++;
  // read entities
  info.load(ifs);

  model.resize(models);
  for (int i = skipGroup; i < models; i++) {
    char ext[3];
    string modeliFile = string(modelFile) + mkext(ext, i);
    model[i] = svm_load_model(modeliFile.c_str());
    if (!model[i])
      throw IXE::FileError(string("can't open model file ") + modeliFile);
  }
}

/**
 *	@ingroup parser
 *
 *	Constructor for SvmParser
 */
Parser*	SvmParserFactory(char const* modelFile = 0)
{
  SvmParser* p = new SvmParser(modelFile);
  if (modelFile && p->model.empty()) {
    delete p;
    return 0;
  }
  return p;
}

REGISTER_PARSER(SVM, SvmParserFactory);

void parseParameters(svm_parameter& param, char* parameters)
{
  // default values
  param.svm_type = C_SVC;
  param.kernel_type = RBF;
  param.degree = 3;
  param.gamma = 0;	// 1/k
  param.coef0 = 0;
  param.nu = 0.5;
  param.cache_size = 100;
  param.C = 1;
  param.eps = 1e-3;
  param.p = 0.1;
  param.shrinking = 1;
  param.probability = 0;
  param.nr_weight = 0;
  param.weight_label = NULL;
  param.weight = NULL;

  char const* opt = "";
  char* next = parameters;
  // parse options
  while (opt = strtok_r(0, " \t", &next)) {
    if (opt[0] != '-') {
      cerr << "Missing option: " << opt << endl;
      return;
    }
    char* tok = strtok_r(0, " \t", &next);
    if (!tok) {
      cerr << "Missing option value: " << opt << endl;
      return;
    }
    switch (opt[1]) {
    case 's':
      param.svm_type = atoi(tok);
      break;
    case 't':
      param.kernel_type = atoi(tok);
      break;
    case 'd':
      param.degree = atoi(tok);
      break;
    case 'g':
      param.gamma = atof(tok);
      break;
    case 'r':
      param.coef0 = atof(tok);
      break;
    case 'n':
      param.nu = atof(tok);
      break;
    case 'm':
      param.cache_size = atof(tok);
      break;
    case 'c':
      param.C = atof(tok);
      break;
    case 'e':
      param.eps = atof(tok);
      break;
    case 'p':
      param.p = atof(tok);
      break;
    case 'h':
      param.shrinking = atoi(tok);
      break;
    case 'b':
      param.probability = atoi(tok);
      break;
    case 'w':
      ++param.nr_weight;
      param.weight_label = (int *)realloc(param.weight_label,
					  sizeof(int)*param.nr_weight);
      param.weight = (double *)realloc(param.weight,
				       sizeof(double)*param.nr_weight);
      param.weight_label[param.nr_weight-1] = atoi(opt+2);
      param.weight[param.nr_weight-1] = atof(tok);
      break;
    default:
      cerr << "unknown option: " << opt << endl;
      return;
    }
  }
}

int compare_nodes(const void* a, const void* b) {
  return ((svm_node const*)a)->index - ((svm_node const*)b)->index;
}

int MinimumSvmSize = 5000;

void SvmParser::collectEvents(Enumerator<Sentence*>& sentenceReader,
			      char const* modelFile,
			      vector<svm_problem>& problem)
{
  WordIndex		labelIndex;
  vector<string>	labels;

  vector<string>	predLabels;

  // collect events
  list<Tanl::Classifier::Event*>	events;

  WordCounts		predCount; // count predicate occurrences

  WordCounts		splitCount; // count tag where to split
  vector<char>		splitEvents; // assert: no more than 256 splits 

  int evCount = 0;
  Tanl::Classifier::PID pID = 0;
  // create inverted index of predicate names
  // used to create vector of pIDs
  EventStream eventStream(&sentenceReader, &info);

  bool doSplit = splitModel();

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
    // ASSERT: code will always be found
    for (unsigned j = 0; j < ec.size(); j++) {
      string& pred = ec[j];
      // decide whether to retain it (# occurrences > cutoff)
      if (predIndex.find(pred.c_str()) == predIndex.end()) {
	// not yet among those retained
	// increment # of occurrences
	int count = predCount.add(pred);
	if (count >= config.featureCutoff) {
	  predLabels.push_back(pred); // accept it into predLabels
	  predIndex[pred.c_str()] = pID++;
	  predCount.erase(pred);
	}
      }
    }
    if (doSplit) {
      string code = eventStream.splitFeature();
      // collect splits
      char const* ccode = code.c_str();
      if (splits.index(ccode) == -1) {
	splits.insert(ccode);
	splitNames.push_back(ccode);
      }
      // record associated splitcode
      splitEvents.push_back((char)splits[ccode]);
      splitCount.add(code);	// increment count for code
    }
  }
  if (config.verbose)
    cerr << endl;
  // free memory
  predCount.clear();
  predCount = WordCounts();

  // build the problems
  if (doSplit) {
    // group small splits into larger set.
    vector<int> splitNewSize(max(1, (int)splits.size()));
    splitNewSize[0] = 0; // reserved for combined groups
    int models = 1;
    FOR_EACH (WordCounts, splitCount, sit) {
      char splitCode = (char)splits[sit->first.c_str()];
      if (sit->second < MinimumSvmSize || splitCount.size() == 1) {
	splitGroup[splitCode] = 0; // model[0]
	splitNewSize[0] += sit->second;
      } else {
	splitGroup[splitCode] = models;
	splitNewSize[models] = sit->second;
	models++;
      }
    }

    problem.resize(models);
    int skipGroup = splitNewSize[0] == 0;
    problem[0].l = 0;		// so we know if present
    for (int i = skipGroup; i < models; i++) {
      int size = splitNewSize[i];
      problem[i].y = new double[size];
      problem[i].x = new svm_node*[size];
      problem[i].l = 0;
    }
  } else {
    problem.resize(1);
    problem[0].y = new double[evCount];
    problem[0].x = new svm_node*[evCount];
    problem[0].l = 0;
  }
  int nTot = 0;
  Tanl::Classifier::ClassID oID = 0;
  evCount = 0;
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
      int i = 0;
      if (!splitEvents.empty())
	i = splitGroup[splitEvents[evCount]]; // choose model according to tag
      int& ni = problem[i].l;	// next slot
      problem[i].y[ni] = labelIndex[c]; // assigned ID to class name
      // free cutoff features
      preds = (svm_node*)realloc(preds, k * sizeof(svm_node));
      problem[i].x[ni] = preds;
      ni++;			// increments problem[i].l
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
    evCount++;
    delete ev;
  }
  // FIXME: might free space in problem.x for dropped events
  if (config.verbose)
    cerr << endl;

  // write model to file
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
  // dump splitNames and their grouping
  ofs << splitNames.size() << endl;
  FOR_EACH (vector<string>, splitNames, pit)
    ofs << *pit << "\t" << (int)splitGroup[(char)splits[pit->c_str()]] << endl;
  info.save(ofs);
  ofs.close();

  if (config.verbose) {
    cerr << "\t    Number of events: " << evCount << endl;
    cerr << "\t   Number of Classes: " << labels.size() << endl;
    cerr << "\tNumber of Predicates: " << predIndex.size() << endl;
  }

  // free memory
  labels.clear();
  predLabels.clear();
  predIndex.clear();
  predIndex = WordIndex(); // STL map do not deallocate. resize(0) has no effect
  labelIndex.clear();
  labelIndex = WordIndex();
  // clear memory for unfrequent entities
  info.clearRareEntities();
}

void SvmParser::train(SentenceReader* sentenceReader, char const* modelFile)
{
  // collect sentences and replace unfrequent token attributes with UNKNOWN.
  std::deque<Sentence*> sentences = collectSentences(sentenceReader);
  Tanl::SentenceQueueReader sr(sentences);
  vector<svm_problem> problem;
  collectEvents(sr, modelFile, problem);

  // setup parameters
  svm_parameter param;
  parseParameters(param, config.svmParams);
  // redirect stdout to stderr, where libsvm outputs progress info
  if (dup2(fileno(stderr), fileno(stdout)) < 0)
    cerr << "could not redirect stdout to stderr" << endl;
  // perform training
  int models = problem.size();
  int skipGroup = problem[0].l == 0;
  for (int i = skipGroup; i < models; i++) {
    if (i >= config.svmSkip) {
      struct svm_model* model = svm_train(&problem[i], &param);
      // dump model
      char ext[4];
      string modeliFile = string(modelFile) + mkext(ext, i);
      svm_save_model(modeliFile.c_str(), model);
      // free space
      svm_free_and_destroy_model(&model);
    }
    for (int j = problem[i].l - 1; j >= 0 ; j--)
      delete [] problem[i].x[j];
    delete [] problem[i].x;
    delete [] problem[i].y;
  }
  svm_destroy_param(&param);
}

Sentence* SvmParser::parse(Sentence* sentence)
{
  vector<svm_node> nodes(predIndex.size());
  preprocess(sentence);
  ParseState* state = new ParseState(*sentence, &info, predIndex);
  while (state->hasNext()) {
    Tanl::Classifier::Context& preds = *state->next();
    // fill example from context
    sort(preds.begin(), preds.end());
    nodes.resize(preds.size() + 1);
    int j = 0;
    FOR_EACH (vector<Tanl::Classifier::PID>, preds, pit) {
      nodes[j].index = *pit + 1; // features start at 1
      nodes[j++].value = 1.0;
    }
    nodes[preds.size()].index = -1;	// termination
    string code = state->splitFeature;
    int i = splitGroup[splits[code.c_str()]]; // choose model according to tag code
    double prediction = svm_predict(model[i], &nodes[0]);
    string& outcome = classLabels[(int)prediction];
#   ifdef DUMP
    cerr << classIndex[rightOutcome];
    FOR_EACH (vector<Tanl::Classifier::PID>, preds, pit)
      cerr << " " << *pit << ":1";
    cerr << endl;
#   endif
    ParseState* next = state->transition(outcome.c_str());
    if (!next)
      next = state->transition("S");
    state = next;
  }
  Sentence* s = state->getSentence();
  state->prune();
  return s;
}

/*
void SvmParser::revise(SentenceReader* sentenceReader, char const* actionFile)
{
  if (actionFile) {
    // read an action file
    ifstream ifs(actionFile);
    WordIndex predIndex;

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
    int numOutcomes = model.NumOutcomes();
    double* params = new double[numOutcomes];
    int correct = 0;
    int wrong = 0;

    ReviseContextStream contextStream(sentenceReader, model.PredIndex());

    while (contextStream.hasNext()) {
      Tanl::Classifier::Context* context = contextStream.next();
      model.estimate(context, params);
      char const* outcome = model.OutcomeName(model.BestOutcome(params));
      contextStream.actions.push_back(outcome);
    }
  }
}
*/
} // namespace Parser
