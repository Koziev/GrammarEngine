/*
**  DeSR
**  src/Sentence.h
** ----------------------------------------------------------------------
**  Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef DeSR_Sentence_H
#define DeSR_Sentence_H

#include "Token.h"

namespace Tanl {

class Corpus;

/**
 *	@ingroup parser
 */
class Sentence : public std::vector<TreeToken*>
{
 public:
  Language const*	language;
  
  Sentence(Language const* language = 0) :
    language(language)
  { }

  Sentence(Sentence const& other) :
    language(other.language) {
    FOR_EACH (Sentence, other, tit)
      push_back(new TreeToken(**tit));
  }

  virtual ~Sentence();

  bool operator ==(const Sentence& other) {
    if (size() != other.size())
      return false;
    for (size_t i = 0; i < size(); i++)
      if (*(*this)[i] != *other[i])  
	return false;
    return true;
  }
  bool operator !=(const Sentence& other) { return !(*this == other); }

  /** Reverse the sequence of tokens and update links accordingly. */
  void			reverse();

  /**
   *	@return parent of token @c tok.
   */
  TreeToken*	parent(TreeToken* tok) {
    return (tok && tok->linkHead() > 0) ? operator[](tok->linkHead() - 1) : 0;
  }

  /**
   *	Find root from token @c tok.
   */
  TreeToken*	root(TreeToken* tok) {
    while (tok->linkHead() > 0)
      tok = operator[](tok->linkHead() - 1);
    return tok;
  }

  TreeToken*	child(TreeToken* tok, char dir, char POS);

  /**
   * 	Child relative position:
   *	-1	closest left
   *	-i	i-th closest left
   *	INT_MIN	farthest left
   *	+1	closest right
   *	+i	i-th closest right
   *	INT_MAX	farthest right
   */
  TreeToken*	child(TreeToken* tok, int nth);
  
  TreeToken*	leftChild(TreeToken* tok);

  TreeToken*	rightChild(TreeToken* tok);

  /**
   *	Determine if link between @c begin and @c end is non projective.
   *	@return true if there is a link crossing the link between @c begin
   *	and @c end.
   */
  bool		crossing(TreeToken* begin, TreeToken* end);

  std::ostream&	print(std::ostream& os, Corpus const& corpus);

};

std::ostream& operator <<(std::ostream& os, Sentence const&);

} // namespace Tanl

#endif // DeSR_Sentence_H
