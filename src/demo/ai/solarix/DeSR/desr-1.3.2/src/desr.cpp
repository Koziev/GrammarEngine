/*
**  DeSR
**  src/desr.cpp
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

// local
#include "Parser.h"
#include "EventStream.h"
#include "Corpus.h"
#include "WordCounts.h"
#include "version.h"

// IXE library
#include "Common/OptionStream.h"
#include "io/File.h"
#include "include/Timer.h"

// standard
#include <list>
#ifdef _WIN32
# include <io.h> // _setmode()
# include <fcntl.h>
#endif

using namespace Parser;
using namespace Tanl;
using namespace IXE;
using namespace std;

namespace Parser {

// configuration parameters
char const*	configFileDefault = "desr.conf";

conf<string>	mode("Mode", "parse"); // train, parse, revise
conf<string>	inputFormat("InputFormat", "CoNLL"); // CoNLL, CoNLL08, DgaXML
conf<string>	outputFormat("OutputFormat", "CoNLL"); // CoNLL, DGAXML
conf<bool>	dump("DumpFeatures", false);
conf<bool>	checkStrategy("CheckStrategy", false);
conf<int>	SentenceCutoff("SentenceCutoff", INT_MAX);

/** Parameters to the POS Tagger. If empty, no tagger is used */
conf<string>	PosParameters("PosParameters", "");
}

// command line options
Options::spec const commandOptions[] = {
  "help",	Options::no_arg,  'h', "-h, --help                  : Print this help message",
  "algorithm",	Options::req_arg, 'a', "-a, --algorithm alg         : Learning algorithm [MLP]",
  "beam",	Options::req_arg, 'b', "-b, --beam                  : Beam size [10]",
  "conf",	Options::req_arg, 'c', "-c, --conf                  : Configuration file [desr.conf]",
  "convert",	Options::no_arg,  'C', "-C, --conv                  : Convert from input to output format",
  "dump",	Options::no_arg,  'd', "-d, --dump                  : Dump training features",
  "direction",	Options::no_arg,  'R', "-R, --right-to-left         : Reading direction",
  "format",	Options::req_arg, 'f', "-f, --input-format format   : Input file format [CoNLL]",
  "output",	Options::req_arg, 'F', "-F, --output-format format  : Output file format [CoNLL]",
  "lang",	Options::req_arg, 'l', "-l, --lang lang             : Language to be used [en]",
  "model",	Options::req_arg, 'm', "-m, --model modelFile       : Model file",
  "perplexity",	Options::no_arg,  'p', "-p, --perplexity            : Print perplexity estimates for each sentence",
  "revise",	Options::req_arg,  'r', "-r, --revise model/actions : Revise parse tree according to revision model or actions file",
  "strategy",	Options::no_arg,   's', "-s, --show-strategy        : Show the parsing actions for building the parse trees",
  "train",	Options::no_arg,  't', "-t, --train                 : Train parser from input file",
  "version",	Options::no_arg,  'v', "-v, --version               : Show the program version",
  0
};

ostream& usage(ostream& os = cerr)
{
  os << "Usage: desr [options] [file]" << endl;
  os << "   If file is missing, reads from standard input." << endl;
  return Options::usage(commandOptions, os);
}

/// ======================================================================

// overwrite parameters from command line options
char const* language = 0;
char const* configFile = configFileDefault;
int beam = -1;
bool RightToLeft = false;
bool ShowActions = false;
bool ShowPerplexity = false;

void train(SentenceReader* sentenceReader, char const* modelFile,
	   char const* configFile, char const* algorithm)
{
  ::Parser::Parser* parser = ::Parser::Parser::create(0, algorithm);
  if (parser) {
    // read configuration parameters
    if (IXE::io::File(configFile).exists()) {
      ifstream ifs(configFile);
      parser->config.load(ifs);
    }
    // override CL options
    if (algorithm)
      parser->config.algorithm = algorithm;
    if (language)
      parser->config.lang = language;
    if (RightToLeft)
      parser->config.RightToLeft = true;
    if (ShowActions)
      parser->config.ShowActions = true;
    Timer timer;
    parser->train(sentenceReader, modelFile);
    if (parser->config.verbose) {
      timer.split();	// Stop!
      char buf[20];
      timer.reading(buf, sizeof buf);
      cerr << "Elapsed time: " << buf << endl;
    }
    delete parser;
  }
}

void parse(char const* modelFile, SentenceReader* sentenceReader, Corpus* outCorpus)
{
  ::Parser::Parser* parser = ::Parser::Parser::create(modelFile);
  if (parser) {
    // set CL options
    if (ShowPerplexity)
      parser->config.ShowPerplexity = true;
    if (beam > 0)
      parser->config.beam = beam;
    parser->parse(sentenceReader, outCorpus);
    delete parser;
  }
}

void revise(char const* modelFile, SentenceReader* sentenceReader)
{
  ::Parser::Parser* parser = ::Parser::Parser::create(modelFile);
  if (parser) {
    parser->revise(sentenceReader);
    delete parser;
  }
}

char const* sentenceSeparator = "\n";

void dumpFeatures(SentenceReader* sentenceReader, int sentenceCutoff)
{
# ifdef _WIN32
  _setmode(_fileno(stdout), _O_BINARY); // no \r
# endif

  ::Parser::Parser* parser = ::Parser::Parser::create(0, configFile);
  deque<Sentence*> sentences = parser->collectSentences(sentenceReader);

  GlobalInfo info = parser->info; // where global info gets collected
  delete parser;

  SentenceQueueReader sr(sentences);
  EventStream eventStream(&sr, &info, sentenceCutoff);
  // collect events
  list<Tanl::Classifier::Event*> events;

  WordIndex predIndex;
  WordCounts predCount; // count predicate occurrences

  unsigned pID = 0;
  while (eventStream.hasNext()) {
    Tanl::Classifier::Event* ev = eventStream.next();
    events.push_back(ev);
    std::vector<string>& ec = ev->features; // ec = {p1, ... , pn}
    for (unsigned j = 0; j < ec.size(); j++) {
      string& pred = ec[j];
      // decide whether to retain it (# occurrences > cutoff)
      if (predIndex.find(pred.c_str()) == predIndex.end()) {
	// not yet among those retained
	// increment # of occurrences
	int count = predCount.add(pred);
	if (count >= parser->config.featureCutoff) {
	  predIndex[pred.c_str()] = pID++;
	  predCount.erase(pred);
	}
      }
    }
  }

  while (!events.empty()) {
    Classifier::Event* ev = events.front();
    events.pop_front();
    vector<string>& ec = ev->features; // ec = {p1, ... , pn}
    string line = ev->className;
    bool empty = true;
    for (unsigned j = 0; j < ec.size(); j++) {
      string& pred = ec[j];
      WordIndex::const_iterator pit = predIndex.find(pred.c_str());
      if (pit != predIndex.end()) {
	line += ' ';
	line += pred;
	empty = false;
      }
    }
    if (!empty)
      cout << line << endl;
    if (ev->className == "LROOT") // HACK: print sentence separator
      cout << sentenceSeparator;
    delete ev;
  }
}

void showStrategy(SentenceReader* sentenceReader, Corpus* corpus)
{
  ParserConfig config;
  GlobalInfo info(config);	// where global info gets collected
# ifdef _WIN32
  _setmode(_fileno(stdout), _O_BINARY); // no \r
# endif
  int errors = 0;
  int count = 0;

  while (sentenceReader->MoveNext()) {
    Sentence* sentence = sentenceReader->Current();
    vector<string> actions;
    TrainState ts(*sentence, &info);
    while (ts.hasNext()) {
      Tanl::Classifier::Event* ev = ts.next();
      string& action = ev->className;
      if (checkStrategy)
	actions.push_back(action);
      else
	cout << action << ' ';
      ts.transition(action.c_str());
      delete ev;
    }
    if (checkStrategy) {
      Sentence* out = ts.getSentence();
      if (*sentence != *out) {
	FOR_EACH (vector<string>, actions, it)
	  cout << *it << ' ';
	cout << endl;
	sentence->print(cout, *corpus);
	cout << endl;
	errors++;
      }
      delete out;
      count++;
      if (count % 1000 == 0)
	cerr << '+' << flush;
      else if (count % 100 == 0)
	cerr << '.' << flush;
      delete sentence;
    }
    else
      cout << endl;
  }
  if (checkStrategy)
    cerr << endl
	 << "Correct: " << count - errors << ", Incorrect: " << errors << endl;
}

void convert(SentenceReader* sentenceReader, Corpus* corpus)
{
  while (sentenceReader->MoveNext()) {
    Sentence* sent = sentenceReader->Current();
    corpus->print(cout, *sent);
    cout << endl;
  }
}

enum Mode {
  Train,
  Parse,
  Revise,
  Dump,
  Strategy
};

/// ======================================================================

int main(int argc, char* argv[])
{
  char const* algorithm = 0;
  char const* inputFormat_arg = 0;
  char const* outputFormat_arg = 0;
  string modelFile;
  string modelRevise;
  bool conv_opt = false;
  bool mode_opt = false;
  Mode mode_type = (*mode == "parse") ? Parse : Train;

  ParserConfig config;

  // process options
  OptionStream options(argc, argv, commandOptions);
  for (OptionStream::Option opt; options >> opt;) {
    switch (opt) {
    case 'h':
      usage();
      return -1;
    case 'a':
      algorithm = opt.arg();
      break;
    case 'b':
      beam = atoi(opt.arg());
      break;
    case 'c':
      configFile = opt.arg();
      break;
    case 'C':
      conv_opt = true;
      break;
    case 'd':
      mode_opt = true; mode_type = Dump;
      break;
    case 'f':
      inputFormat_arg = opt.arg();
      break;
    case 'F':
      outputFormat_arg = opt.arg();
      break;
    case 'l':
      language = opt.arg();
      break;
    case 'm':
      modelFile = opt.arg();
      break;
    case 'p':
      ShowPerplexity = true;
      break;
    case 'r':
      mode_opt = true; mode_type = Revise;
      modelRevise = opt.arg();
      break;
    case 'R':
      RightToLeft = true;
      break;
    case 's':
      ShowActions = true;
      break;
    case 't':
      mode_opt = true; mode_type = Train;
      break;
    case 'v':
      cerr << "DeSR version: " << version << endl;
      break;
    }
  }
  argc -= options.shift(), argv += options.shift();

  // determine parser input
  istream* is = 0;

  switch (argc) {
  case 0:
    is = &cin;
    break;
  case 1: {
    char const* inputFile = argv[0];
    IXE::io::File file(inputFile);
    if (!file.exists()) {
      cerr << "No input file: " << inputFile << endl;
      return -1;
    }
    if (!file.length()) {
      cerr << "Empty input file: " << inputFile << endl;
      return -1;
    }
    is = new ifstream(inputFile);
    break;
  }
  default:
    cerr << usage;		// no ()
    return -1;
  }

  if (modelFile.empty() && !mode_opt && !ShowActions) {
    cerr << "Model file is required" << endl;
    cerr << usage;
    return -2;
  }

  // First, parse the config. file (if any); then override variables
  // with options specified on the command line.
  //
  if (IXE::io::File(configFile).exists())
    config.load(configFile);
  else if (configFile != configFileDefault) {
    cerr << "Missing config file: " << configFile << endl;
    return -2;
  }

  if (!mode_opt) {
    if (*mode == "train")
      mode_type = Train;
    else if (*mode == "parse")
      mode_type = Parse;
    else if (*mode == "revise")
      mode_type = Revise;
  }
  // show strategy if not parsing nor training:
  if (modelFile.empty() && (config.ShowActions || ShowActions))
    mode_type = Strategy;

  // in parse mode certain parameters are fixed and stored in the modelFile
  if (mode_type == Parse) {
    // read parameters from modelFile
    ifstream ifs(modelFile.c_str());
    if (!ifs) {
      cerr << "Missing model file: " << modelFile << endl;
      return -3;
    }
    config.load(ifs);
  } else {
  }

  if (inputFormat_arg) inputFormat = inputFormat_arg;
  if (outputFormat_arg) outputFormat = outputFormat_arg;

  Language const* language = Language::get(config.lang->c_str());
  if (language == 0) {
    cerr << "Unknown language: " << *config.lang << endl;
    return -4;
  }
  // Create the Corpus for the requested inputFormat and its
  // associated SentenceReader.
  Corpus* corpus = Corpus::create(*language, inputFormat);
  if (corpus == 0) {
    cerr << "Unknown format: " << *inputFormat << endl;
    return -1;
  }
  Corpus* outCorpus = Corpus::create(*language, outputFormat);
  if (outCorpus == 0) {
    cerr << "Unknown format: " << *outputFormat << endl;
    return -1;
  }
  SentenceReader* sentenceReader = corpus->sentenceReader(is);

  if (conv_opt) {
    Corpus* outCorpus = new CombCorpus(*language, inputFormat->c_str());
    convert(sentenceReader, outCorpus);
    delete outCorpus;
    delete corpus;
    delete sentenceReader;
    return 0;
  }

  try {
    switch (mode_type) {
    case Train:
      // generate model
      if (!algorithm) {
	// get it from configuration parameters
	algorithm = strdup(config.algorithm->c_str());
      }
      train(sentenceReader, modelFile.c_str(), configFile, algorithm);
      if (algorithm)
	free((void*)algorithm);
      break;
    case Dump:
      dumpFeatures(sentenceReader, SentenceCutoff);
      break;
    case Parse: {			// Parsing
      // PosTaggerStub.o provides an empty stub to link instead of
      // the real tagger in configurations when not required
      SentenceReader* basicReader = sentenceReader; // save it for deallocation
      if (PosParameters->size()) {
	PosTagger* posTagger = 0;
	if (!strcmp(basicReader->corpus->language.code(), "en"))
	  posTagger = new PennPosTagger(PosParameters->c_str());
	else
	  posTagger = new PosTagger(PosParameters->c_str());
	sentenceReader = new TaggedSentenceReader(basicReader, posTagger);
      }
      parse(modelFile.c_str(), sentenceReader, outCorpus);
      if (basicReader != sentenceReader)
	delete basicReader;
      break;
    }
    case Revise: {			// Revising
      if (!IXE::io::File(modelRevise.c_str()).exists()) {
	cerr << "No revision model: " << modelRevise << endl;
	return -1;
      }
      revise(modelRevise.c_str(), sentenceReader);
      break;
    }
    case Strategy:
      showStrategy(sentenceReader, corpus);
      break;
    }
  } catch (IXE::Error& e) {
    cerr << "Error: " << e.message() << endl;
  } catch (exception& e) {
    cerr << "Error: " << e.what() << endl;
  }
  if (is != &cin)
    delete is;
  delete sentenceReader;
  delete corpus;
  delete outCorpus;
}
