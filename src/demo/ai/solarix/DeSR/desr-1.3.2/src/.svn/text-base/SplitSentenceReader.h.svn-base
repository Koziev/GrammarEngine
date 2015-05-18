/*
**  DeSR
**  src/SplitSentenceReader.h
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

#ifndef DeSR_SplitSentenceReader_H
#define DeSR_SplitSentenceReader_H

// local
#include "Corpus.h"

#undef yyFlexLexer
#define yyFlexLexer ptbFlexLexer
#include "FlexLexer.h"

#include "Tokenizer.h"

#include "SentenceReader.h"

// library
#include "text/less.h"

// standard
#include <set>

namespace Tanl {

/**
 *	@ingroup parser
 *
 *	Read a plain text file, split into tokens and return one sentence at
 *	a time. 
 */
class SplitSentenceReader : public SentenceReader
{
 public:

  /**
   *	Parameters defininig where to split a sentence.
   */
  struct BoundarySet {
    static char const* defaultBoundaryTokens[];
    static char const* defaultBoundaryFollowers[];

    BoundarySet(char const* boundaryTokens[] = defaultBoundaryTokens,
		char const* boundaryFollowers[] = defaultBoundaryFollowers,
		char const* regionBegin = 0,
		char const* regionEnd = 0) {
      for (char const** scan = boundaryTokens; *scan; scan++)
	boundaries.insert(*scan);
      for (char const** scan = boundaryFollowers; *scan; scan++)
	followers.insert(*scan);
    }

    bool ends(char const* tok) const {
      return boundaries.find(tok) != boundaries.end();
    }

    std::set<char const*>	boundaries;
    std::set<char const*>	followers;
  };
  static BoundarySet const defaultBS;

  /**
   *	Creates a new @c SplitSentenceReader. 
   *	@param is	the stream containing the sentence to read.
   *	@param lang the language of the document.
   */
  SplitSentenceReader(std::istream* is,
		      Corpus* corpus = 0,
		      BoundarySet const* bs = &defaultBS);

  /** Return true if there is another sentence available. */
  bool		MoveNext();

  /**	Restart */
  void		reset() { tokenizer.Reset(); insideRegion = false; }

 private:
  Parser::Tokenizer	tokenizer;
  BoundarySet const*	boundarySet;
  bool		insideRegion;

# ifdef STEMMER
  sb_stemmer* stemmer;
# endif
};

} // namespace Tanl

#endif // DeSR_SplitSentenceReader_H
