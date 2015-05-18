/*
**  DeSR
**  src/State.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef DeSR_State_H
#define DeSR_State_H

//#define DEBUG

// local
#include "config.h"

#ifdef HAVE_PYTHON
// must go first. See http://docs.python.org/c-api/intro.html#includes
#include <Python.h>
#endif

// IXE library
#include "text/RegExp.h"
#include "text/WordIndex.h"
#include "conf/conf_bool.h"
#include "conf/conf_int.h"
#include "conf/conf_string.h"

// ME library
#include "Classifier.h"

// standard
#include <vector>
#include <limits>		// infinity

// local
#include "Iterator.h"
#include "Sentence.h"
#include "conf_feature.h"
#include "WordCounts.h"

// Tanl
using Tanl::Sentence;
using Tanl::TreeToken;

namespace Parser {

/**
 *	Set of configuration parameters representing the feature model.
 */
struct FeatureConfig : public IXE::Configuration
{
  FeatureConfig(IXE::Configuration::Params& params = IXE::Configuration::variables());

  // feature model
  conf_features		features;
  /** Used for reading old notation of single attribute features. */
  conf_single_features	singleFeatures;

  // parser strategy
  IXE::conf<bool>	arcEager;

  // used to split SVMs.
  conf_features	SplitFeature;

  /** Whether to consider closest or furthest children */
  IXE::conf<bool>	ClosestChildren;

  /** Entity type of child of prepositions: time, location */
  IXE::conf<bool>	PrepChildEntityType;

  IXE::conf<bool>	StackSize;
  IXE::conf<bool>	InputSize;
  IXE::conf<bool>	InPunct;
  IXE::conf<bool>	InQuotes;
  IXE::conf<bool>	VerbCount;
  /** Notice punctuation in children of focus words */
  IXE::conf<bool>	UseChildPunct;
  IXE::conf<int>	PastActions;
  IXE::conf<bool>	WordDistance;
  IXE::conf<bool>	PunctCount;
  /** Notice morphological agreement (same gender or number) in focus words */
  IXE::conf<bool>	MorphoAgreement;
  /** Notice children containing non ASCII letters */
  IXE::conf<bool>	LexChildNonWord;
  /** Connect disconnected nodes to root. */
  IXE::conf<bool>	SingleRoot;

  /** Use composite Action+Deprel as predicted outcome */
  IXE::conf<bool>	CompositeActions;

  // Feature combinations
  IXE::conf<bool>	SecondOrder;

  /** Parse direction */
  IXE::conf<bool>	RightToLeft;

  // Encode features to avoid ambiguities
  IXE::conf<bool>	unambiguous;

  /** Form or lemmas occurring less than LexCutoff are collapsed to Unknown. */
  IXE::conf<int>	 lexCutoff;
  /** model file format version */
  IXE::conf<std::string> fileVersion;
};

typedef char const* Action;

typedef std::vector<std::string> Features; // also Classifier::Features

/**
 *	Stores global information collected while analyzing a corpus.
 */

struct GlobalInfo
{
  WordCounts	timeLemmas;
  WordCounts	locLemmas;

  FeatureConfig*	config;

  /**
   *	Determines when a lemma occurring as both a time and a location entity,
   *	occurs more frequently in one of the two categories.
   */
  static float const freqRatio;

  GlobalInfo(FeatureConfig& config) :
    config(&config)
  { }

  /**
   *	Extract global info from sentence, e.g. @c timeLemmas and @c locLemmas.
   */
  virtual void	extract(Sentence const& sentence);

  /**
   *	Clear memory for unfrequent entities in @c timeLemmas and @c locLemmas.
   */
  void		clearRareEntities();

  /**
   *	Clear all memory.
   */
  void		clear();

  void		save(std::ofstream& ofs);

  void		load(std::ifstream& ifs);

};

/**
 *	Common info to all states while parsing a sentence.
 */
class SentenceInfo
{
 public:

  SentenceInfo(Sentence& sentence, GlobalInfo* info);

  GlobalInfo*		globalInfo; ///< global parse info

  /**	Number of punctuations so far	*/
  std::vector<int>	punctCount;

  /**	Whether within quotes	*/
  std::vector<bool>	inQuotes;

};

/**
 *	@ingroup parser
 *
 *	Parser base state.
 */
class State
{
public:
  /**
   *	Constructor.
   *	@param sentence	the sentence to be parsed.
   *	@param globalInfo, global parse information.
   */
  State(Sentence const& sentence, GlobalInfo* globalInfo);

  State(State const& state) :
    sentenceInfo(state.sentenceInfo),
    sentence(state.sentence.language),
    rootNode(state.rootNode),
    previous(&state),
    verbCount(state.verbCount),
    action(0),
    afterUnshift(state.afterUnshift),
    input(state.input),
    stack(state.stack),
    extracted(state.extracted)
  {
    // shallow copy: transition() will make copies when modifying tokens
    sentence.resize(state.sentence.size());
    std::copy(state.sentence.begin(), state.sentence.end(), sentence.begin());
  }

  virtual ~State() {
    if (!previous || rootNode != previous->rootNode)
      delete rootNode;
    if (!previous) {
      delete sentenceInfo;
    }
  }

  /**	@return whether this is a final state. */
  bool			hasNext();

  /**	Perform action represented by Action @c action.
   *	@return next State, or NULL if action failed.
   */
  State*		transition(Action action);

  /** Perform a Shift action: move token from input to stack */
  State* Shift();

  /** Perform a Unshift action: move token from stack to input */
  State* Unshift();

  /** Perform a Right action: connect top of stack to next input, pop stack */
  State* Right(Action action);

  /** Perform a Left action: connect next input to top of stack, pop input and unshift. */
  State* Left(Action action);

  /** Perform a far right action. */
  State* right(Action action);

  /** Perform a far left action. */
  State* left(char const* action);

  /** Perform a link action. */
  State* DepLink(Action action);

  /** Perform an Extract action: move second stack token to Extracted and shift. */
  State* Extract();

  /** Perform an Insert action: move token from Extracted to input. */
  State* Insert();

  /** Perform a Pop action: remove top element from the stack */
  State* Pop();

  Sentence*		getSentence() {
    Sentence* sen = new Sentence(sentence);
    if (sentenceInfo->globalInfo->config->RightToLeft)
      sen->reverse();
    return sen;
  }

  void			showStatus();

  Sentence		sentence; ///< the sentence parsed so far

  TreeToken*		rootNode; ///< Dummy root node

  /**	Pattern for detecting punctuation:	*/
  static Tanl::Text::RegExp::Pattern	ispunct;

  /**	Pattern for detecting quotes:	*/
  static Tanl::Text::RegExp::Pattern	isOpenQuote;
  /**	Pattern for detecting quotes:	*/
  static Tanl::Text::RegExp::Pattern	isCloseQuote;

  std::string		splitFeature; ///< used to split SVMs

  /**
   *	The previous State in the derivation.
   */
  State const*		previous;

  /**
   *	The action that lead to this state
   */
  Action		action;

  /**
   *	After an Unshift action.
   */
  bool			afterUnshift;

  /**
   *	Stack from which input tokens are extracted
   */
  std::vector<TreeToken*>	input;
  /**
   *	Stack where analyzed tokens are accumulated
   */
  std::vector<TreeToken*>	stack;
  /**
   *	Stack where extracted tokens are accumulated
   */
  std::vector<TreeToken*>	extracted;

  /**	Weird version of ispunct */
  static Tanl::Text::RegExp::Pattern	nonWordAscii;

 protected:

  // Copies only in ParseState; TrainState instead modifies tokens.
  virtual TreeToken*	copy(TreeToken* x) { return x; }

  SentenceInfo*		sentenceInfo;

  /**
   *	Collect features representing context.
   */
  void			predicates(Features& preds, Action action = 0);

  /**	Number of verbs so far	*/
  int			verbCount;

 private:
  void	tokenFeatures(Features& preds);
  void	prepChildEntities(Features& preds);
};

/**
 *	@ingroup parser
 *
 *	Parser training state.
 */
class TrainState : public State, public Iterator<Tanl::Classifier::Event*>
{
 public:

  TrainState(Sentence const& sent, GlobalInfo* info);

  bool			hasNext() { return State::hasNext(); }

  /**
   *	@return the training event, consisting of features representing
   *	the state.
   */
  Tanl::Classifier::Event*	next();

protected:
  /**
   *	Compute next parse action
   */
  Action		nextAction();

  Sentence		annotated; ///< the annotated sentence

  std::vector<int>	dependents; ///< count of dependents of each node
};

/**
 *	@ingroup parser
 *
 *	Parse state.
 *	Provides a stream of Tanl::Classifier::Context's from a Sentence.
 */
class ParseState : public State, public Iterator<Tanl::Classifier::Context*>
{
 public:

  ParseState(Sentence& sent, GlobalInfo* globalInfo, Tanl::Text::WordIndex& predIndex);
 
  ParseState(ParseState& prev) :
    State((State)prev),
    predIndex(prev.predIndex),
    lprob(0),
    refCount(0)
  {
    prev.refCount++;
  }  

  ~ParseState();		// frees state and decrement predecessor

  void		prune();	// frees single branch

  int		incRef() { return ++refCount; }
  int		decRef() { return --refCount; }

  bool		hasNext();
  Tanl::Classifier::Context*	next();

  /**	Perform action represented by string @c action.
   *	@return next ParseState if action was succesfully performed.
   */
  ParseState* 	transition(Action action);

  TreeToken*	copy(TreeToken* x) {
    TreeToken* tok = new TreeToken(*x);
    int id = x->id;
    if (id)
      return sentence[id - 1] = tok;
    else
      return rootNode = tok;
  }

  double	lprob;		///< log probability

 protected:

  Tanl::Text::WordIndex&	predIndex;
  Tanl::Classifier::Context	context;

  int		refCount;	///< how many alternatives refer to this
};

} // namespace Parser

#endif // DeSR_State_H
