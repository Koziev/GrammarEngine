/*
**  DeSR
**  src/conf_feature.h
** ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
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

#ifndef Parser_conf_feature_H
#define Parser_conf_feature_H

// standard
#include <stdlib.h>
#include <map>

// library
#include "conf/conf.h"
#include "text/strings.h"
#include "text/less.h"		// for map to work on strings

// local
#include "TokenPath.h"

namespace Parser {

/**
 *	Specification of a feature, made up as concatenation of
 *	attributes extracted from tokens.
 *	The token from which the attribute is taken is denoted by a
 *	@see TokenPath, the attribute by its name.
 *	For example:
 *	   LEMMA(leftChild(-1)) POS(0)
 *	defines a feature consisting of the concatenation of the LEMMA of the
 *	left child of token on the stack and the POS of the next input token.
 */
struct FeatureSpec
{
  char const*	attribute;
  TokenPath*	path;
  FeatureSpec*	next;

  FeatureSpec(char const* attr, TokenPath* path) :
    attribute(attr),
    path(path),
    next(0)
  { }

  ~FeatureSpec() {
    delete attribute;
    delete path;
    delete next;
  }

  static FeatureSpec*	parse(char const*& line);

  void			serialize(std::ostream& os) const;

};

inline std::ostream& operator <<(std::ostream& os, const FeatureSpec& d) 
{
  d.serialize(os);
  return os;
}

typedef std::vector<FeatureSpec*> FeatureSpecs;

/**
 *	@ingroup configuration
 *
 *	A conf_feature contains a set of feature specifications.
 *
 */
class conf_features : public IXE::Var<FeatureSpecs>
{
  friend  class conf_single_features;
public:

  conf_features(char const* name,
		IXE::Configuration::Params& params = IXE::Configuration::variables()) :
    IXE::Var<FeatureSpecs>(name, params) { }

  conf_features(char const* name, char const* value,
		IXE::Configuration::Params& params = IXE::Configuration::variables()) :
    IXE::Var<FeatureSpecs>(name, params) {
    parseValue(value);
  }

  ~conf_features() { reset(); }

  /**
   *	Serialize variable so that it can be read back.
   */
  virtual void serialize(std::ostream& os);

protected:
  /**
   *      Parse the line of text, which should have the following syntax:
   *		feature(tokenPath)+
   *		tokenPath : INT | rel(tokenPath)
   *		rel :	leftChild | rightChild | par | prev | next | leftSibling | rightSibling
   *
   *      @param line            The line of text to be parsed.
   */
  virtual void		parseValue(char const*& line);

  virtual void		reset() {
    value.clear();
  }

  static void		add(FeatureSpecs* value, FeatureSpec* fs);

  // don't use hash_map since we want the same order on all platforms
  typedef std::map<char const*, int> FeatureIndex;

public:
  // For back compatibility we must number single features lexicographically.
  // We compute this numbering just once and keep it in an index.
  static FeatureIndex	featureIndex;
};

/**
 *	@ingroup configuration
 *
 *	Backward compatible version of conf_features specifications.
 *
 */
class conf_single_features : public IXE::Var<FeatureSpecs*>
{
public:

  conf_single_features(char const* name, FeatureSpecs* features,
		IXE::Configuration::Params& params = IXE::Configuration::variables()) :
    IXE::Var<FeatureSpecs*>(name, features, params)
  { }

  /**
   *	Serialize variable so that it can be read back.
   */
  virtual void		serialize(std::ostream& os) {
    // do nothing: the value is shared with a conf_features which
    // should be serialized instead.
  }

  virtual void		reset() { }

protected:
  /**
   *      Parse the line of text, which should have the following syntax:
   *		feature tokenPath+
   *		tokenPath : INT | rel(tokenPath)
   *		rel :	leftChild | rightChild | par | prev | next | leftSibling | rightSibling
   *
   *      @param line            The line of text to be parsed.
   */
  virtual void		parseValue(char const*& line);
};

} // namespace Parser

namespace IXE {
  // we will redefine it in conf_feature.cpp
  template<>
    inline void Var<Parser::FeatureSpecs>::serialize(std::ostream& os) { }
}

#endif	/* Parser_conf_feature_H */
