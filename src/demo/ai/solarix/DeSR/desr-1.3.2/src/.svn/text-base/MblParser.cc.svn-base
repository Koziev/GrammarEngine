/*
**  DeSR
**  src/MblParser.cpp
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
/// TiMBL  version

// IXE library
#include "conf/conf_bool.h"
#include "conf/conf_string.h"
#include "text/WordIndex.h"
#include "text/RegExp.h"

// standard
#include <iostream>

#include "Parser.h"
#include "TimblAPI.h"

extern IXE::conf<string>	maxent;
extern IXE::conf<bool>		ShowActions;
extern IXE::conf<string>	outputFormat;

using namespace std;

namespace Parser {

IXE::conf<string>	TimblParams("TimblParams", "-m M -k 5 -w 0 -d ID -L 3 +v s");

struct MblParser : public Parser
{
  void	train(char const* modelFile, SLREventStream& eventStream);
  void	parse(char const* modelFile, SentenceReader* sentenceReader);
};

/**
 *	Constructor for MblParser
 */
Parser*	MblParserFactory(char const*)
{
  return new MblParser();
}

REGISTER_PARSER(MBL, MblParserFactory);

void	MblParser::train(char const* modelFile, SLREventStream& eventStream)
{
  // to be defined
}

//#define NON_PROJECTIVE

struct MblContextStream : public SLREventStream
{
  MblContextStream(SentenceReader* reader) :
    SLREventStream(reader)
  {
    while (reader->hasNext()) {
      delete sentence;
      sentence = reader->next();
      if (sentence->size())
	break;
    }
    input.resize(sentence->size());
    copy(sentence->rbegin(), sentence->rend(), input.begin());
    createActionSequence();
  }

  bool hasNext() {
    if (input.size())
      return true;

    if (ShowActions)
      cerr << endl;
    if (*outputFormat == "CoNLL") { 
      for (int i = 1; i <= sentence->size(); i++)
	FOR_EACH (vector<Token*>, stack, it)
	  (*it)->printCoNLL(cout, 0, i);
      cout << endl;
    } else {
      FOR_EACH (vector<Token*>, stack, it)
	(*it)->print(cout);
      cout << endl;
    }
    while (reader->hasNext()) {
      delete sentence;
      sentence = reader->next();
      if (sentence->size()) {
	clear();
	input.resize(sentence->size());
	copy(sentence->rbegin(), sentence->rend(), input.begin());
	bool res = createActionSequence();
#       ifdef NON_PROJECTIVE
	// consider only sentences with non-projective relations
	FOR_EACH (vector<Action>, actions, ait) {
	  if ((*ait)[0] == 'l' || (*ait)[0] == 'r')
	    return true;
	}
	continue;
#	endif
	return res;
      }
    }
    return false;
  }

  /**
   *	@return next Event
   */
  ME::Event* next()
  {
    Action a = actionIter == actions.end() ? "" : *actionIter;
    ME::Event* ev = new ME::Event(a);
    predicates(ev->predicates);
    return ev;
  }

  // same as SLRContextStream::performAction()
  void	performAction(Action action)
  {
    // don't allow extracted token to survive beyond punctuation
    if (extracted.size() && input.size() &&
	(action[0] == 'S' || action[0] == 'L') &&
	ispunct.test(input.back()->orth))
      action = "I";
    if (ShowActions) {
      cerr << ' ' << action;
      if (strcmp(action, Outcome())) {
	cerr << " (" << Outcome() << ": ";
	if (stack.size())
	  cerr << stack.back()->orth;
	cerr << ", ";
	if (input.size())
	  cerr << input.back()->orth;
	cerr << ")";
      }
    }
    SLREventStream::performAction(action);
  }

  char const*	Outcome() {
    return actionIter != actions.end() ? *actionIter : "";
  }
};

#define MAX_LINE_LEN 256

IXE::Text::RegExp::RegExp featRE("(\\d[<>]?[WLPMDA\\.]|[WLPMDA\\.][<>]?\\d|E[LP]|\\(+)(.*)");

void MblParser::parse(char const* modelFile, SentenceReader* sentenceReader)
{
  ifstream timblFile(modelFile);
  if (!timblFile) {
    cerr << "No such file: " << modelFile << endl;
    return;
  }
  // read attribute names
  string attrFilename = string(modelFile) + ".attr";
  ifstream attrFile(attrFilename.c_str());
  
  WordIndex attrIndex;
  char line[MAX_LINE_LEN];
  int count = 0;
  while (attrFile.getline(line, MAX_LINE_LEN)) {
    attrIndex[line] = count++;
  }

  TimblAPI* model = new TimblAPI("");
  model->SetOptions(TimblParams);
  string file = modelFile;
  model->GetInstanceBase(file);

  int correct = 0;
  int wrong = 0;

  MblContextStream contextStream(sentenceReader);
  string features;
  string outcome;

  IXE::Text::RegExp::MatchPositions matches(3);
  while (contextStream.hasNext()) {
    ME::Event* context = contextStream.next();
    vector<string> types(count, "=");
    // fill example from context
    vector<string>& preds = context->predicates;
    int i = 0;
    FOR_EACH (vector<string>, preds, pit) {
      string const& feat = *pit;
      if (featRE.match(feat, matches) == 3) {
	string type(feat, 0, matches[1].second);
	string value(feat, matches[2].first, matches[2].second - matches[2].first);
	if (value.empty())
	  value = type;
	WordIndex::const_iterator found = attrIndex.find(type.c_str());
	if (found != attrIndex.end())
	  types[found->second] = value;
      }
    }
    features = "";
    FOR_EACH (vector<string>, types, pit)
      features += *pit + '\t';
    features += "??";
    bool r = model->Classify(features, outcome);
    contextStream.performAction(outcome.c_str());
  }
  delete model;
}

} // namespace Parser
