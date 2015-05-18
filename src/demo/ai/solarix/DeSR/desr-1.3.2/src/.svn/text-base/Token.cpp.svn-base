/*
**  DeSR
**  src/Token.cpp
**  ----------------------------------------------------------------------
**  Copyright (c) 2005 Giuseppe Attardi (attardi@di.unipi.it).
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
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program. If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#include "platform.h"

#include "Sentence.h"
#include "Corpus.h"

// standard
#include <iostream>
#include <iomanip>

// library
#include "text/strings.h"	// strStartsWith

using namespace std;
using namespace Parser;
using namespace Tanl::Text;

namespace Tanl {

ostream& operator <<(ostream& os, Token const& tok)
{
  os << "<token";
  FOR_EACH (Attributes, tok.attributes, it)
    // iterator returns pointer to values
    os << " " << (*it).first << "=\"" << *(*it).second << '\"';
  return os << " />";
}

void Token::print(ostream& os, int indent) const
{
  os << setw(indent) << "<token";
  for (Attributes::const_iterator fit = attributes.begin();
       fit != attributes.end(); ++fit)
    os << ' ' << (*fit).first << "=\"" << (*fit).second << "\"";
  os << " />" << endl;
}

// ======================================================================
// Tag

static Text::RegExp::Pattern reTag("<(\\w+)\\b[^>]*>");
static Text::RegExp::Pattern reAttribute("(\\w+)\\s*=\\s*\\\"([^\\\"]*)\\\"");

Tag::Tag(const string& xmlTag)
{
  char const* start = xmlTag.c_str();
  Text::RegExp::MatchGroups match(3);
  if (reTag.match(start, match)) {
    name = string(start + match[1].first, match[1].second - match[1].first);
    start += match[1].second;
    while (reAttribute.match(start, match)) {
      string key(start + match[1].first, match[1].second - match[1].first);
      string value(start + match[2].first, match[2].second - match[2].first);
      attributes[key] = value;
      start += match[0].second;
    }
  }
}

//======================================================================
// Token

//#define CONLL08			// FIXME: for the time being
#ifdef CONLL08
static char const* DeprelTag = "DEPREL";
static char const* FormTag = "SPLIT_FORM";
static char const* LemmaTag = "SPLIT_LEMMA";
static char const* PosTag = "PPOSS";
static char const* CPosTag = "";
#else
static char const* DeprelTag = "DEPREL";
static char const* FormTag = "FORM";
static char const* LemmaTag = "LEMMA";
static char const* PosTag = "POSTAG";
static char const* CPosTag = "CPOSTAG";
#endif

Token::Token(string& form, Corpus& corpus, Context* context) :
  form(form),
  attributes(&corpus.index),
  links(1, TokenLink(-1)),
  context(context)
{
  if (context)
    context->incRef();
}

bool Token::isNoun(Language const* lang)
{
  string const* cpos = get(CPosTag);
  if (cpos && *cpos == lang->nounCPos)
    return true;
  string const* pos = get(PosTag);
  return pos && strStartsWith(pos->c_str(), lang->nounCPos);
}

bool Token::isPreposition(Language const* lang)
{
  string const* cpos = get(CPosTag);
  if (cpos && *cpos == lang->prepCPos)
    return true;
  string const* pos = get(PosTag);
  return pos && strStartsWith(pos->c_str(), lang->prepCPos);
}

bool Token::isTime(Language const* lang)
{
  // from gold deprel
  string const* label = get(DeprelTag);
  return label && strStartsWith(label->c_str(), lang->timeDep);
}

bool Token::isLocation(Language const* lang)
{
  // from gold deprel
  string const* label = get(DeprelTag);
  return label && strStartsWith(label->c_str(),lang->locDep);
}

/**
 *	Use either full CPOS, or initial of POS, since some treebanks provide
 *	multiple CPOS, e.g. VV, VB, VH in some editions of English Penn Treebank.
 */
bool Token::isVerb(Language const* lang)
{
  string const* cpos = get(CPosTag);
  if (cpos && *cpos == lang->verbCPos)
    return true;
  string const* pos = get(PosTag);
  return pos && strStartsWith(pos->c_str(), lang->verbCPos);
}

string const* Token::lemma() const
{
  return get(LemmaTag);
}

void Token::lemma(string const& l)
{
  return set(LemmaTag, l);
}

string const* Token::pos() const
{
  return get(PosTag);
}

void Token::pos(string const& p)
{
  return set(PosTag, p);
}

string const* Token::cpos() const
{
  return get(CPosTag);
}

string const* Token::deprel() const
{
  return get(DeprelTag);
}

//======================================================================
// TreeToken

TreeToken* TreeToken::ancestorCPos(char const* pos, Sentence& tokens)
{
  for (int nid = linkHead(); nid != 0; ) {
    TreeToken* tokn = (TreeToken*)tokens[nid-1];
    string const* attr = tokn->get(CPosTag);
    if (attr && *attr == pos)
      return tokn;
    nid = tokn->linkHead();
  }
  return 0;
}

TreeToken* TreeToken::follow(Parser::TokenPath const& tp, Sentence& sentence)
{
  TreeToken* tok = this;
  FOR_EACH(vector<TokenPath::Direction>, tp.path, pit) {
    switch (*pit) {
    case TokenPath::leftChild:
      // move to the furthest left child (as in Nivre), if present
      tok = tok->left.empty() ? 0 : tok->left.front();
      break;

    case TokenPath::rightChild:
      // move to the furthest right child (as in Nivre), if present
      tok = tok->right.empty() ? 0 : tok->right.front();
      break;

    case TokenPath::leftDescendant:
      // move to the leftmost descendant, if present
      if (tok->left.empty())
	tok = 0;
      else
	while (!tok->left.empty())
	  tok = tok->left.front();
      break;

    case TokenPath::rightDescendant:
      // move to the rightmost descendant, if present
      if (tok->right.empty())
	tok = 0;
      else
	while (!tok->right.empty())
	  tok = tok->right.front();
      break;

    case TokenPath::parent:
      if (tok->linkHead() == 0)
	tok = 0;
      else
	tok = sentence[tok->linkHead() - 1];
      break;

    case TokenPath::ancestor:
      if (tok->linkHead() == 0)
	tok = 0;
      else
	while (tok->linkHead())
	  tok = sentence[tok->linkHead() - 1];
      break;

    case TokenPath::leftSibling: {
      if (tok->linkHead() == 0) {
	tok = 0;
	break;
      }
      TreeToken* parent = sentence[tok->linkHead() - 1];
      TreeToken* sibl = 0;
      // find token following tok in left children
      FOR_EACH(vector<TreeToken*>, parent->left, cit) {
	if (*cit == tok) {
	  if (++cit != parent->left.end()) {
	    sibl = *cit;
	    break;
	  }
	}
      }
      if (sibl) {
	tok = sibl;
	break;
      }
      // find token preceding tok in right children
      FOR_EACH(vector<TreeToken*>, parent->right, cit) {
	if (*cit == tok) {
	  tok = 0;
	  break;
	}
	sibl = *cit;
      }
      tok = (tok == 0) ? sibl : 0;
      break;
    }

    case TokenPath::rightSibling: {
      if (tok->linkHead() == 0) {
	tok = 0;
	break;
      }
      TreeToken* parent = sentence[tok->linkHead() - 1];
      TreeToken* sibl = 0;
      // find token following tok in right children
      FOR_EACH(vector<TreeToken*>, parent->right, cit) {
	if (*cit == tok) {
	  if (++cit != parent->left.end()) {
	    sibl = *cit;
	    break;
	  }
	}
      }
      if (sibl) {
	tok = sibl;
	break;
      }
      // find token preceding tok in left children
      FOR_EACH(vector<TreeToken*>, parent->left, cit) {
	if (*cit == tok) {
	  tok = 0;
	  break;
	}
	sibl = *cit;
      }
      tok = (tok == 0) ? sibl : 0;
      break;
    }

    case TokenPath::previous:
      tok = (tok->id > 1) ? sentence[tok->id - 2] : 0;
      break;

    case TokenPath::next:
      tok = (tok->id < sentence.size()) ? sentence[tok->id] : 0;
      break;
    }

    if (!tok) break;
  }
  return tok;
}

void TreeToken::print(ostream& os, int indent) const
{
  Attributes& attributes = token->attributes;
  os << setw(indent) << ' ' << "<tok id=\"" << id
     << "\" form=\"" << attributes.get("FORM")
     << "\" lemma=\"" << attributes.get("LEMMA")
     << "\" cpos=\"" << attributes.get("CPOS")
     << "\" pos=\"" << attributes.get("POS")
     << "\" morph=\"" << attributes.get("FEATS")
     << "\" head=\"" << linkHead() << "\" deprel=\"" << linkLabel() << "\">" << endl;
  indent += 2;
  FOR_EACH (vector<TreeToken*>, left, it)
    (*it)->print(os, indent);
  FOR_EACH (vector<TreeToken*>, right, it)
    (*it)->print(os, indent);
}

void TreeToken::printTab(ostream& os)
{
  Attributes& attributes = token->attributes;
  bool first = true;
  FOR_EACH (vector<char const*>, attributes.attributeIndex->names, it) {
    string const* tag = attributes.get(*it);
    if (first)
      first = false;
    else
      os << "\t";
    os << ((!tag || tag->empty()) ? "_" : *tag);
  }
}

void TreeToken::printTab(ostream& os, Corpus const& corpus)
{
  Attributes& attributes = token->attributes;
  bool first = true;
  FOR_EACH (TokenFields, corpus.tokenFields, it) {
    if (first)
      first = false;
    else
      os << "\t";
    switch (it->role) {
    case TokenField::head:
      os << linkHead(); break;
    case TokenField::deprel:
      os << (linkLabel().empty() ? it->default_ : linkLabel()); break;
    default:
      if (it->use == TokenField::ignore)
	os << it->default_;
      else {
	string const* tag = attributes.get(it->name);
	os << ((!tag || tag->empty()) ? it->default_ : *tag);
    }
    }
  }
}

void TreeToken::printConll08(ostream& os, Corpus const& corpus, vector<int>* preds)
{
  Attributes& attributes = token->attributes;
  TokenFields::const_iterator tfit = corpus.tokenFields.begin();
  TokenLinks::const_iterator tlit = token->links.begin();
  bool first = true;
  FOR_EACH (vector<char const*>, attributes.attributeIndex->names, it) {
    string const* tag = attributes.get(*it);
    if (first)
      first = false;
    else
      os << "\t";
    if (!tfit->link.empty())
      os << tlit->head;
    else if (!tfit->label.empty()) {
      if (tlit != token->links.end()) {
	os << (tlit->label.empty() ? tfit->default_ : tlit->label);
	++tlit;
      }
    } else {
      os << ((!tag || tag->empty()) ? tfit->default_ : *tag);
    }
    ++tfit;
  }
  // print links
# ifdef COMPACT
  preds = 0;
# endif
  if (preds) {
    unsigned predNo = 0;
    for (; tlit != token->links.end(); ++tlit) {
      int head = tlit->head;
      while (head != (*preds)[predNo++])
	os << "\t_";
      os << '\t' << tlit->label;
    }
    while (predNo++ < preds->size())
      os << "\t_";
  } else {
    for (; tlit != token->links.end(); ++tlit)
      os << '\t' << tlit->label << '[' << tlit->head << ']';
  }
}

void TreeToken::printLeaves(ostream& os)
{
  for (vector<TreeToken*>::reverse_iterator it = left.rbegin(); it != left.rend(); ++it)
    (*it)->printLeaves(cout);
  cout << token->form << ' ';
  FOR_EACH (vector<TreeToken*>, right, it)
    (*it)->printLeaves(cout);
}

} // namespace Tanl
