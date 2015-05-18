/*
**  DeSR
**  src/PosTagger.h
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

#ifndef  DeSR_PosTagger_H
#define  DeSR_PosTagger_H

#include <vector>
#include <map>

#include "text/WordSet.h"
#include "include/error.h"

using namespace Tanl::Text;

namespace Parser {

/**
 *	@ingroup parser
 */
struct Tagged
{
  std::vector<char const*>	words;
  std::vector<char const*>	tags;
  std::vector<char const*>	lemmas;

  ~Tagged() { clear(); }

  void clear() {
    words.clear();
    // no need to clear tags nor lemmas, they are allocated
    // inside TreeTagger.
    tags.clear();
    lemmas.clear();
  }

  size_t	length() { return words.size(); }
};

/**
 *	@ingroup parser
 *
 *	Base class for POS taggers.
 */
struct PosTagger
{
  PosTagger() { }

  /**
   *	Argument @param PosParameters is the name of the parameter file
   *	to be used by the tagger, and produced by training the tagger
   *	on an annotated corpus.
   */
  PosTagger(const char* PosParameters);

  ~PosTagger() {
    tags.clear();		// don't delete, allocated inside TreeTagger
  }

  /**
   *	Perform POS tagging on the sentence represented by the words
   *	in @param sentence, and fill in the corresponding tags and lemmas
   *	@return true if tagging succeded.
   */
  virtual bool	tag(Tagged& sentence);

  /**
   *	Set of tags used
   */
  WordSet	tags;

};

/**
 *	@ingroup parser
 */
struct PennPosTagger : public PosTagger
{
  PennPosTagger(const char* PosParameters);

  /**
   *	Perform POS tagging on the sentence represented by the words
   *	in @param sentence, and fill in the corresponding tags and lemmas
   *	@return true if tagging succeded.
   */
  bool	tag(Tagged& sentence);

  /**
   * Maps TreeTagger POS tags names to Penn POS names
   */
  typedef std::map<std::string, char const*>	PosMap;

  static PosMap	posMap;
  static PosMap	inversePosMap;
};

/**
 *	@ingroup parser
 */
struct PosTaggerError : public std::runtime_error {
   PosTaggerError(std::string const& msg) : std::runtime_error(msg) {}
};

} // namespace TreeTagger

#endif // DeSR_PosTagger_H
