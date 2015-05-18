/*
**  DeSR
**  src/Token.h
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

#ifndef DeSR_Token_H
#define DeSR_Token_H

// standard
#include <string>
#include <vector>
#include <sstream>
#include <map>

// library
#include "text/RegExp.h"
#include "Common/util.h"	// FOR_EACH

// local
#include "Language.h"
#include "RefCountable.h"
#include "TokenPath.h"
#include "Corpus.h"

namespace Tanl {

/**
 *	@ingroup parser
 *
 *	Represents links to other tokens.
 */
struct TokenLink
{
  TokenLink(int head = -1, char const* label = "") :
    head(head),
    label(label)
  { }

  bool operator ==(const TokenLink& other) const {
    return head == other.head && label == other.label;
  }
  bool operator !=(const TokenLink& other) { return !(*this == other); }

  int		head;
  std::string	label;
};

typedef std::vector<TokenLink> TokenLinks;

/**
 *	@ingroup parser
 *
 *	Represents SGML tags.
 */
struct Tag
{
  Tag(const std::string& xmlTag);

  std::string& operator[](const std::string& key) {
    return attributes[key];
  }

  const std::string open() const {
    std::string tag = "<" + name;
    for (std::map<std::string, std::string>::const_iterator it = attributes.begin();
	 it != attributes.end(); ++it)
      tag += ' ' + it->first + "=\"" + it->second + '"';
    return tag + ">";
  }

  const std::string close() const {
    return "</" + name + ">";
  }

  std::string				name;
  std::map<std::string, std::string>	attributes;
};

/**
 *	@ingroup parser
 *
 *	Represents contexts of the tokens.
 */
struct Context : public RefCountable
{
  Context(const std::string& xmlTag, Context* parent = 0) :
    tag(xmlTag),
    parent(parent)
  {
    if (parent)
      parent->incRef();
  }

  ~Context() {
    if (parent)
      parent->decRef();
  }

  void Dispose() {
    decRef();
  }

  Tag		tag;
  Context*	parent;

};

/**
 *	@ingroup parser
 *
 *	Represents a sentence token (a word in a sentence).
 */
struct Token
{
  /** Compact morphology representation */
  struct Morpho {
    std::string		morph;	///< morphology, split into:
    char		Case;   ///< case
    char		gender; ///< gender
    char		mode;	///< mode
    char		negative; ///< negative
    char		number; ///< number
    char		person; ///< person
    char		tense;	///< tense
    char		aspect;	///< aspect
    char		transitive; ///< transitive
    char		extra[20]; ///< extra morph values

    Morpho(const char* morph = "", size_t morphSize = 0) :
      morph(morph, morphSize),
      Case(0),
      gender(0),
      mode(0),
      negative(0),
      number(0),
      person(0),
      tense(0),
      transitive(0)
    {
      extra[0] = '\0';
    }

    /** set individual morpho features */
    void set(MorphExtractor::Features& mf) {
      Case = mf.Case[0];
      gender = mf.gender[0];
      number = mf.number[0];
      person = mf.person[0];
      mode = mf.mode[0];
      negative = mf.negative[0];
      number = mf.number[0];
      person = mf.person[0];
      tense = mf.tense[0];
      transitive = mf.trans[0];
      int extraLen = sizeof(extra) - 1;
      strncpy(extra, mf.extra, extraLen);
      extra[extraLen] = '\0';
    }
  };

  Token(Token const& tok) :
    form(tok.form),
    morpho(tok.morpho),
    attributes(tok.attributes),
    links(tok.links),
    context(tok.context)
  {
    if (context)
      context->incRef();
  }

  Token(std::string& form, Attributes& attributes, Context* context = 0) :
    form(form),
    attributes(attributes),
    links(1, TokenLink(-1)),
    context(context)
  {
    if (context)
      context->incRef();
  }

  Token(std::string& form, Attributes& attributes, TokenLinks& links, Context* context = 0) :
    form(form),
    attributes(attributes),
    links(links),
    context(context)
  {
    if (context)
      context->incRef();
  }

  Token(Attributes& attributes, Context* context = 0) :
    attributes(attributes),
    links(1, TokenLink(-1)),
    context(context)
  {
    if (context)
      context->incRef();
  }

  Token(std::string& form, AttributeIndex* attributeIndex, Context* context = 0) :
    form(form),
    attributes(attributeIndex),
    links(1, TokenLink(-1)),
    context(context)
  {
    if (context)
      context->incRef();
  }

  Token(char const* form, AttributeIndex* attributeIndex, Context* context = 0) :
    form(form),
    attributes(attributeIndex),
    links(1, TokenLink(-1)),
    context(context)
  {
    if (context)
      context->incRef();
  }

  Token(std::string& form, Corpus& corpus, Context* context = 0);

  Token(AttributeIndex* attributeIndex, Context* context = 0) :
    attributes(attributeIndex),
    links(1, TokenLink(-1)),
    context(context)
  {
    if (context)
      context->incRef();
  }

  ~Token() {
    if (context)
      context->decRef();
  }

  std::string const& operator [](char const* key) {
    return *attributes.get(key);
  }

  /**	@return the attribute associated to key @c key, or 0 if not present. */
  std::string const*	get(char const* key) const {
    return attributes.get(key);
  }

  /**	Add the attribute @c value associated to key @c key. */
  void		set(char const* key, char const* value) {
    attributes.insert(key, value);
  }

  /**	Add the attribute @c value associated to key @c key. */
  void		set(char const* key, std::string const& value) {
    attributes.insert(key, value);
  }

  /**	Add the attribute @c value associated to key @c key. */
  void		set(char const* key, int value) {
    attributes.insert(key, value);
  }

  /**	Get the index of a given attribute @c name. */
  int		attrIndex(char const* name) const {
    std::vector<char const*> const& names = attributes.attributeIndex->names;
    unsigned idx = 0;
    FOR_EACH (std::vector<char const*>, names, it) {
      if (!::strcmp(*it, name))
	break;
      idx++;
    }
    return (idx >= names.size()) ? -1 : (int)idx;
  }

  bool operator ==(const Token& other) {
    return attributes == other.attributes &&
      links == other.links;
  }
  bool operator !=(const Token& other) { return !(*this == other); }

  bool		isNoun(Language const* lang);
  bool		isPreposition(Language const* lang);
  bool		isTime(Language const* lang);
  bool		isLocation(Language const* lang);
  bool		isVerb(Language const* lang);
  std::string const*	lemma() const; // FIXME: should depend on corpus
  void		lemma(std::string const&); // FIXME: should depend on corpus
  std::string const*	pos() const; // FIXME: should depend on corpus
  void		pos(std::string const&); // FIXME: should depend on corpus
  std::string const*	cpos() const; // FIXME: should depend on corpus
  std::string const*	deprel() const; // FIXME: should depend on corpus

  /**	output token in XML format */
  void		print(std::ostream& os, int indent = 0) const;

  std::string	form;		///< word form
  Morpho	morpho;		///< morphology
  Attributes	attributes;	///< additional attributes
  TokenLinks	links;		///< additional links
  Context*	context;	///< context
};

/**
 *	Overloaded insert operator.
 */
std::ostream& operator <<(std::ostream& os, Token const& tok);

/**
 *	@ingroup parser
 *
 *	Token with descendants.
 */
struct TreeToken
{
  TreeToken(std::string& form, AttributeIndex* ai) :
    token(new Token(form, ai))
  { }

  TreeToken(int id, char const* form, AttributeIndex* attributeIndex = 0) :
    token(new Token(form, attributeIndex)),
    id(id)
  { }

  TreeToken(int id, std::string& form, Attributes& attributes,
	    TokenLinks& links) :
    token(new Token(form, attributes, links)),
    id(id)
  { }

  TreeToken(int id, std::string& form, Attributes& attributes) :
    token(new Token(form, attributes)),
    id(id)
  { }

  TreeToken(int id, Token* token) :
    token(new Token(*token)),
    id(id)
  { } 

  TreeToken(TreeToken const& tok) :
    token(new Token(*tok.token)),
    id(tok.id),
    left(tok.left),
    right(tok.right)
  { }

  virtual ~TreeToken() { delete token; }

  Token*			token;
  unsigned			id;
  std::vector<TreeToken*>	left;  ///< list of left child tokens
  std::vector<TreeToken*>	right; ///< list of right child tokens

  /**	@return the form of the token. */
  std::string const&	form() const { return token->form; }

  /**	@return the attribute for key @c key, or 0 if not present. */
  std::string const*	get(char const* key) const {
    return token->get(key);
  }

  /**	@return the predicted attribute for key @c key, or 0 if not present. */
  std::string const*	predicted(char const* key) const {
    // FIXME: should work for all OUTPUT attributes:
    return strcmp(key, "DEPREL") ? token->get(key) : &linkLabel();
  }

  /**	Add the attribute @c value associated to key @c key. */
  void			set(char const* key, char const* value) {
    token->set(key, value);
  }

  /**	Add the attribute @c value associated to key @c key. */
  void			set(char const* key, std::string const& value) {
    token->set(key, value);
  }

  int			linkHead(int i = 0) const {
    return token->links[i].head;
  }
  int			linkHead(int h, int i = 0) {
    return token->links[i].head = h;
  }
  std::string const&	linkLabel(unsigned i = 0) const {
    return token->links[i].label;
  }
  std::string const&	linkLabel(std::string& l, unsigned i = 0) {
    return token->links[i].label = l;
  }
  std::string const&	linkLabel(char const* l, unsigned i = 0) {
    return token->links[i].label = l;
  }

  bool operator ==(const TreeToken& other) { return *token == *other.token; }
  bool operator !=(const TreeToken& other) { return !(*this == other); }

  /**	@return the size of the subtree */
  int	size() {
    int count = 0;
    FOR_EACH (std::vector<TreeToken*>, left, it)
      count += (*it)->size();
    FOR_EACH (std::vector<TreeToken*>, right, it)
      count += (*it)->size();
    return count + 1;
  }

  /**
   *	Get the token following the given path @c tp, through
   *	sentence @c sentence.
   *	@return the token reached throught the path or 0 if not found.
   */
  TreeToken* follow(Parser::TokenPath const& tp, Sentence& sentence);

  int	leftmostDescendant() {
    int lmd = id;
    FOR_EACH (std::vector<TreeToken*>, left, it)
      lmd = MIN(lmd, (*it)->leftmostDescendant());
    return lmd;
  }

  int	rightmostDescendant() {
    int lmd = id;
    FOR_EACH (std::vector<TreeToken*>, right, it)
      lmd = MAX(lmd, (*it)->rightmostDescendant());
    return lmd;
  }

  /**
   *	@return ancestor node with given coarse POS @c pos.
   */
  TreeToken*	ancestorCPos(char const* pos, Sentence& sent);

  /**
   *	@return descendant node with given coarse POS @c pos.
   */
  TreeToken*	descendantCPos(char const* pos) {
    // start from children
    FOR_EACH (std::vector<TreeToken*>, left, it) {
      TreeToken* tokn = *it;
      std::string const* attr = tokn->token->cpos();
      if (attr && *attr == pos)
	return tokn;
      tokn = tokn->descendantCPos(pos);
      if (tokn)
	return tokn;
    }
    FOR_EACH (std::vector<TreeToken*>, right, it) {
      TreeToken* tokn = *it;
      std::string const* attr = tokn->token->cpos();
      if (attr && *attr == pos)
	return tokn;
      tokn = tokn->descendantCPos(pos);
      if (tokn)
	return tokn;
    }
    return 0;
  }

  /**	output token in default XML format */
  // needed because of overloaded alternatives
  void		print(std::ostream& os, int indent = 0) const;

  /**	output token in tab format */
  void		printTab(std::ostream& os);

  void		printTab(std::ostream& os, Corpus const& corpus);

  /**
   *	output in CoNLL 2008 format.
   *	@param preds	contains the IDs of predicate tokens in sentence.
   */
  void		printConll08(std::ostream& os, Corpus const& corpus,
			     std::vector<int>* preds = 0);

  /**
   *	print the leaves of the tree.
   */
  void		printLeaves(std::ostream& os);
};

} // namespace Tanl

#endif // DeSR_Token_H
