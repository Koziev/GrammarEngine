/*
**  DeSR
**  src/ReviseEventStream.cpp
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

// local
#include "ReviseEventStream.h"

// library
#include "conf/conf_bool.h"

using namespace std;
using namespace Tanl::Classifier;

// Tanl
using Tanl::TreeToken;
using Tanl::Sentence;

namespace Parser {

IXE::conf<bool>		SecondOrder;

ReviseStream::ReviseStream(Tanl::SentenceReader* reader) :
  reader(reader),
  sentence(0),
  cur(0)
{ }

void ReviseStream::clear()
{
  cur = 0;
  actions.clear();
}

void  ReviseStream::childFeatures(TreeToken* tok, char const* tag,
				  Features& preds)
{
  TreeToken* parent = sentence->parent(tok);
  if (!parent)
    return;
  if (tok->linkHead() == parent->id) {
    char feature[256];
    if (tok->id < parent->id) {
      sprintf(feature, "L%s<%s", tag, tok->token->lemma()->c_str());
      preds.push_back(feature);
      sprintf(feature, "P%s<%s", tag, tok->token->pos()->c_str());
      preds.push_back(feature);
      sprintf(feature, "D%s<%s", tag, tok->token->deprel()->c_str());
      preds.push_back(feature);
    } else {
      sprintf(feature, "L%s>%s", tag, tok->token->lemma()->c_str());
      preds.push_back(feature);
      sprintf(feature, "P%s>%s", tag, tok->token->pos()->c_str());
      preds.push_back(feature);
      sprintf(feature, "D%s>%s", tag, tok->token->deprel()->c_str());
      preds.push_back(feature);
    }
  }
}

void ReviseStream::predicates(Features& preds)
{
  preds.clear();
  TreeToken* tok = (*sentence)[cur];
  TreeToken* parent = sentence->parent(tok);
  TreeToken* grandParent = sentence->parent(parent);
  TreeToken* ggParent = sentence->parent(grandParent);
  char feature[256];
  // token features
  sprintf(feature, "L%s", tok->token->lemma()->c_str());
  preds.push_back(feature);
  sprintf(feature, "P%s", tok->token->pos()->c_str());
  preds.push_back(feature);
  sprintf(feature, "D%s", tok->token->deprel()->c_str());
  preds.push_back(feature);
  childFeatures(tok, "", preds);
  // previous token features
  if (cur > 0) {
    TreeToken* tokn = (*sentence)[cur-1];
    sprintf(feature, "-1L%s", tokn->token->lemma()->c_str());
    preds.push_back(feature);
    sprintf(feature, "-1P%s", tokn->token->pos()->c_str());
    preds.push_back(feature);
    sprintf(feature, "-1D%s", tokn->token->deprel()->c_str());
    preds.push_back(feature);
  }
  // next token features
  if (cur < sentence->size() - 1) {
    TreeToken* tokn = (*sentence)[cur+1];
    sprintf(feature, "+1L%s", tokn->token->lemma()->c_str());
    preds.push_back(feature);
    sprintf(feature, "+1P%s", tokn->token->pos()->c_str());
    preds.push_back(feature);
    sprintf(feature, "+1D%s", tokn->token->deprel()->c_str());
    preds.push_back(feature);
  }
  // token preceding constituent
  int lmd = tok->leftmostDescendant();
  if (lmd > 1) {
    TreeToken* tokn = (*sentence)[lmd - 2]; // after constituent
    sprintf(feature, "<L%s", tokn->token->lemma()->c_str());
    preds.push_back(feature);
    sprintf(feature, "<P%s", tokn->token->pos()->c_str());
    preds.push_back(feature);
    sprintf(feature, "<D%s", tokn->token->deprel()->c_str());
    preds.push_back(feature);
    tokn = sentence->parent(tokn); // its parent
    if (tokn) {
      sprintf(feature, "<-1L%s", tokn->token->lemma()->c_str());
      preds.push_back(feature);
      sprintf(feature, "<-1P%s", tokn->token->pos()->c_str());
      preds.push_back(feature);
      sprintf(feature, "<-1D%s", tokn->token->deprel()->c_str());
      preds.push_back(feature);
    }
  }
  // token following constituent
  unsigned rmd = tok->rightmostDescendant();
  if (rmd < sentence->size()) {
    TreeToken* tokn = (*sentence)[rmd]; // after constituent
    sprintf(feature, ">L%s", tokn->token->lemma()->c_str());
    preds.push_back(feature);
    sprintf(feature, ">P%s", tokn->token->pos()->c_str());
    preds.push_back(feature);
    sprintf(feature, ">D%s", tokn->token->deprel()->c_str());
    preds.push_back(feature);
    tokn = sentence->parent(tokn); // its parent
    if (tokn) {
      sprintf(feature, ">+1L%s", tokn->token->lemma()->c_str());
      preds.push_back(feature);
      sprintf(feature, ">+1P%s", tokn->token->pos()->c_str());
      preds.push_back(feature);
      sprintf(feature, ">+1D%s", tokn->token->deprel()->c_str());
      preds.push_back(feature);
    }
  }
  childFeatures(tok, "", preds);
  // parent features
  if (parent) {
    childFeatures(parent, "u", preds);
    FOR_EACH (Sentence, *sentence, sibl) {
      if ((*sibl)->linkHead() == parent->id) {
	childFeatures(*sibl, "uudd", preds);
	if (grandParent)
	  childFeatures(grandParent, "uu", preds);
      }
    }
  }
  // grand parent features
  if (grandParent) {
    sprintf(feature, "GL%s", tok->token->lemma()->c_str());
    preds.push_back(feature);
    sprintf(feature, "GP%s", tok->token->pos()->c_str());
    preds.push_back(feature);
    sprintf(feature, "GD%s", tok->token->deprel()->c_str());
    preds.push_back(feature);
  }
  // grand-grand parent features
  if (ggParent) {
    sprintf(feature, "GGL%s", tok->token->lemma()->c_str());
    preds.push_back(feature);
    sprintf(feature, "GGP%s", tok->token->pos()->c_str());
    preds.push_back(feature);
    sprintf(feature, "GGD%s", tok->token->deprel()->c_str());
    preds.push_back(feature);
  }
  if (SecondOrder) {
    // add all pairs
    size_t predNo = preds.size();
    for (unsigned i = 0; i < predNo; i++) {
      for (unsigned j = i+1; j < predNo; j++) {
	// combine in alphabetical order
	string combo = (preds[i].compare(preds[j]) < 0) ?
	  preds[i] + '#' + preds[j] : preds[j] + '#' + preds[i];
	preds.push_back(combo.c_str());
      }
    }
  }
}

// ----------------------------------------------------------------------
bool ReviseContextStream::hasNext()
{
  if (sentence) {
    if (cur < sentence->size())
      return true;
    // revise the parse tree according to actions
    revise();
    // print revised parse tree
    sentence->print(cout, *reader->corpus);
    cout << endl;
  }
  while (reader->MoveNext()) {
    delete sentence;
    sentence = reader->Current();
    // build tree
    // FIXME: order might differ for actions l2/r2, E/I 
    FOR_EACH (vector<TreeToken*>, *sentence, it) {
      TreeToken* tok = *it;
      unsigned head = tok->linkHead();
      if (head && tok->id > head) // left arc
	  (*sentence)[head - 1]->right.push_back(tok);
    }
    for (vector<TreeToken*>::reverse_iterator it = sentence->rbegin();
	 it != sentence->rend(); ++it) {
      TreeToken* tok = *it;
      unsigned head = tok->linkHead();
      if (head && tok->id < head) // right arc
	  (*sentence)[head - 1]->left.push_back(tok);
    }
    clear();
    return true;
  }
  return false;
}

Tanl::Classifier::Context* ReviseContextStream::next()
{
  Features preds;
  predicates(preds);		// get contextual predicates
  // convert them to PIDs
  context.clear();
  FOR_EACH (Features, preds, it) {
    if (predIndex.find(it->c_str()) != predIndex.end())
      context.push_back(predIndex[it->c_str()]);
  }
  ++cur;
  return &context;
}

char const* ReviseContextStream::Outcome() { return 0; }

int ReviseContextStream::performAction(TreeToken* tok, int from, char const* action)
{
  int revision = (*sentence)[from]->linkHead();
  if (!strcmp(action, "OK") || !strcmp(action, "-"))
    return revision;		// no change
  TreeToken* to = tok;
  char const* origAction = action;
  while (*action) {
    switch (action[0]) {
    case 'r':			// root
      return 0;
    case 'u':			// up
      to = sentence->parent(to);
      ++action;
      break;
    case 'd': {			// down
      // either nth left/right child (d+n, or d++) or child with POS (d+P)
      if (*++action == 0) {
	to = 0;	// missing offset
	break;
      }
      char* end = (char*)action;
      int nth = strtol(action, &end, 10);
      if (action == end) {
	// no number, must be either --, ++ or +/-POS
	char sign = *action++;
	char POS = *action++;
	switch (POS) {
	case '-':
	  to = (TreeToken*)sentence->child(to, INT_MIN);
	  break;
	case '+':
	  to = (TreeToken*)sentence->child(to, INT_MAX);
	  break;
	case '\0':
	  to = 0;
	  break;
	default:
	  to = (TreeToken*)sentence->child(to, sign, POS);
	}
      } else {
	action = end;
	to = (TreeToken*)sentence->child(to, nth);
      }
      break;
    }
    case '-': {
      // nth token to the left
      int nth = strtol(action, (char**)&action, 10);
      nth = to->id - 1 + nth;
      if (nth >= 0)
	to = (*sentence)[nth];
      else
	to = 0;
      break;
    }
    case '+': {
      // nth token to the right
      unsigned nth = strtol(action, (char**)&action, 10);
      nth += to->id - 1;
      if (nth < sentence->size())
	to = (*sentence)[nth];
      else
	to = 0;
      break;
    }
    case '<': {
      ++action;
      // token to the left of constituent
      int lmd = to->leftmostDescendant();
      if (lmd > 1)
	to = (*sentence)[lmd - 2];
      else
	to = 0;
      break;
    }
    case '>': {
      ++action;
      // token to the right of constituent
      unsigned rmd = to->rightmostDescendant();
      if (rmd < sentence->size())
	to = (*sentence)[rmd];
      else
	to = 0;
      break;
    }
    case 'v': {			// verb up
      ++action;
      // ancestor token with V cpos
      to = (TreeToken*)to->ancestorCPos("V", *sentence);
      break;
    }
    case 'V': {			// verb down
      ++action;
      // descendant token with V cpos
      // FIXME: should skip immediate first: e.g. "is derived"
      to = (TreeToken*)to->descendantCPos("V");
      break;
    }
    case '[': {			// head of previous constituent
      ++action;
      // token to the left of constituent
      int tlc = to->leftmostDescendant() - 1;
      if (tlc == 0) {
	to = 0;
	break;
      }
      to = (*sentence)[tlc-1];
      // find its head
      while (to->rightmostDescendant() == tlc) {
	TreeToken* p = sentence->parent(to);
	if (p)
	  to = p;
	else
	  break;
      }
      break;
    }
    default:
      to = 0;		// no change
    }
    if (to == 0) {
      cerr << "Bad change: " << origAction << " " << tok->token->form << endl;
      return revision;		// no change
    }
  }
  // FIXME: should update the dependency too
  return to->id;
}

void ReviseContextStream::revise()
{
  // collect revisions
  vector<int> revisions;
  int i = 0;
  FOR_EACH (vector<string>, actions, it) {
    char const* action = it->c_str();
    TreeToken* tok = (*sentence)[i];
    int head = performAction(tok, i++, action);
    revisions.push_back(head);
  }
  // perform revisions
  i = 0;
  FOR_EACH (vector<int>, revisions, rit) {
    TreeToken* tok = (*sentence)[i++];
    tok->linkHead(*rit);
  }
}

} // namespace Parser
