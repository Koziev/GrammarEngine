/*
**  DeSR
**  src/MeParser.cpp
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
/// MaxEntropy parser

// Must go first, since it includes <Python.h>
#include "State.h"
#include "Parser.h"
#include "conf/conf_int.h"
#include "EventStream.h"
#include "ReviseEventStream.h"

#ifdef _WIN32
#include "lib/strtok_r.h"
#endif

// ME library
#include "GIS.h"
#include "LBFGS.h"

// standard
#include <math.h>
#include <assert.h>

using namespace std;

namespace Parser {

struct MeConfig : public ParserConfig
{
  MeConfig(IXE::Configuration::Params& params) :
    ParserConfig(params),	// inclue generic parameters
    iterations("MEiter", 60, params)
  { }

  IXE::conf<int>	iterations;
};

// define for using beam search
#define BEAM

/**
 *	@ingroup parser
 *
 *	A Parser using a Maximum Entropy classifier.
 */
struct MeParser : public Parser
{
  MeParser(char const* modelFile);

  void		train(SentenceReader* sentenceReader, char const* modelFile);

  Sentence*	parse(Sentence* sentence);

  void		revise(SentenceReader* sentenceReader, char const* actionFile = 0);

  Tanl::Classifier::MaxEnt	model;

  MeConfig	config;		///< full configuration (inherits from ParseConfig)
};

/**
 *	@ingroup parser
 *
 *	Constructor for MeParser
 */
Parser*	MeParserFactory(char const* modelFile = 0)
{
  return new MeParser(modelFile);
}

REGISTER_PARSER(ME, MeParserFactory);

MeParser::MeParser(char const* modelFile) :
  Parser(model.PredIndex(), config),
  config(params)		// params is inherited from Parser
{
  model.verbose = config.verbose; // FIXME: needed?
  if (!modelFile)
    return;			// training
  ifstream ifs(modelFile, ios::binary);
  if (!ifs)
    throw IXE::FileError(string("Missing model file: ") + modelFile);
  // load header
  config.load(ifs);
  model.load(ifs);
  // read entities
  info.load(ifs);
}

void MeParser::train(SentenceReader* sentenceReader, char const* modelFile)
{
  EventStream eventStream(sentenceReader, &info);
  Tanl::Classifier::LBFGS model(config.iterations, config.featureCutoff);
  if (config.verbose)
    cerr << "Collecting events.." << endl;
  model.read(eventStream);
  ofstream ofs(modelFile, ios::binary | ios::trunc);
  // dump configuration settings
  config.writeHeader(ofs);
  model.train();
  // cant do before train since outcomeLabels is created in train()
  model.writeHeader(ofs);
  model.writeData(ofs);
  // dump entities
  info.save(ofs);
}

#ifdef BEAM
// FIXME: this is duplicated in MlpParser.cpp
/**
 * Insert state @param s in beam vector @param states.
 * Assume insertion is possible, i.e. there is either space in the beam
 * or @c s has better @c lprob than the worst in the beam.
 */
static double addState(ParseState* s, vector<ParseState*>& states)
{
  int size = states.size();
  int beam = states.capacity();
  assert(size < beam || s->lprob < states[size-1]->lprob);
  s->incRef();		// referenced from states
  if (size == 0) {
    states.push_back(s);
    return s->lprob;
  }
  // assume insertion is possible:
  //   double worst = states[size-1]->lprob;
  //   if (size == beam && s->lprob < worst) {
  //     s->prune();
  //     return worst;
  //   }
  TO_EACH (std::vector<ParseState*>, states, it)
    if (s->lprob > (*it)->lprob) {
      if (size == beam) {
	states.back()->decRef();
	states.back()->prune();
	states.back() = s;
      } else
	states.insert(it, s);
      return states.back()->lprob;
    }
  if (size < beam)
    states.push_back(s);
  return states.back()->lprob;
}
#endif

Sentence* MeParser::parse(Sentence* sentence)
{
  int numOutcomes = model.NumOutcomes();
  double* params = new double[numOutcomes];
  preprocess(sentence);
  ParseState* state = new ParseState(*sentence, &info, predIndex);

# ifdef BEAM
  int beam = config.beam;
  vector<ParseState*> currStates; currStates.reserve(beam);
  vector<ParseState*> nextStates; nextStates.reserve(beam);
  vector<ParseState*>* bestStates = &currStates;
  vector<ParseState*>* bestNextStates = &nextStates;
  addState(state, *bestStates);	// calls incRef()

  while (true) {
    int finished = 0;
    int numBest = bestStates->size();
    double worstProb = -numeric_limits<double>::infinity();
    for (int i = 0; i < numBest; i++) {
      state = (*bestStates)[i];
      if (state->hasNext()) {
	Tanl::Classifier::Context& context = *state->next();
	model.estimate(context, params);
	for (int o = 0; o < numOutcomes; o++) {
	  double prob = params[o];
	  if (prob < 1e-4)
	    continue;		// not worth considering
	  double lprob = log(prob) + state->lprob;
	  if (bestNextStates->size() == beam && lprob < worstProb)
	    continue;		// not worth considering
	  char const* outcome = model.OutcomeName(o);
	  ParseState* next = state->transition(outcome);
	  if (!next) // dead end.
	    continue;
	  next->lprob = lprob;
	  worstProb = addState(next, *bestNextStates); // does incRef()
	}
      } else if (bestNextStates->size() < (size_t)beam || state->lprob > worstProb) {
	// already finished: promote to bestNextStates
	worstProb = addState(state, *bestNextStates); // does incRef()
	finished++;
      }
    }
    if (bestNextStates->empty())
      break;			// no advance
    // clear bestStates, purge dead ends
    // purge after cycle, since if bestNextStates->empty()
    // these states will be the outputs and will be pruned later.
    FOR_EACH (std::vector<ParseState*>, *bestStates, it) {
      ParseState* state = (*it);
      state->decRef();		// no longer in bestStates
      state->prune();
    }
    bestStates->clear();
    // swap vectors
    vector<ParseState*>* tmp = bestStates;
    bestStates = bestNextStates;
    bestNextStates = tmp;
    if (finished == numBest)
      break;
  }
  // choose best sentence as output, discard the rest.
  Sentence* s = (*bestStates)[0]->getSentence();
  if (config.ShowPerplexity) {
    double avg = 0.0;
    double min = 1.0;
    double n = 0.0;
    for (ParseState* s = (*bestStates)[0]; s; s = (ParseState*)s->previous) {
      double prob = exp(s->lprob);
      avg += prob;
      if (prob < min)
	min = prob;
      n++;
    }
    avg /= n;
    cout << "<LogLikelihood all=" << (*bestStates)[0]->lprob;
    cout << " avg=" << avg << " min=" << min << " />" << endl;
  }
  FOR_EACH (std::vector<ParseState*>, *bestStates, it) {
    (*it)->decRef();
    (*it)->prune();
  }
# else

  while (state->hasNext()) {
    Tanl::Classifier::Context& context = *state->next();
    model.estimate(context, params);
    int best = model.BestOutcome(params);
    char const* outcome = model.OutcomeName(best);
    ParseState* next = state->transition(outcome);
    if (!next)
      next = state->transition("S");
    state = next;
  }
  Sentence* s = state->getSentence();
  state->prune();
# endif // BEAM

  // free memory
  delete[] params;

  return s;
}

void MeParser::revise(SentenceReader* sentenceReader, char const* actionFile)
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
      Tanl::Classifier::Context& context = *contextStream.next();
      model.estimate(context, params);
      char const* outcome = model.OutcomeName(model.BestOutcome(params));
      contextStream.actions.push_back(outcome);
    }
  }
}

} // namespace Parser
