/*
**  DeSR
**  src/TokenPath.h
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

#ifndef Parser_TokenPath_H
#define Parser_TokenPath_H

// standard
#include <vector>
#include <string>
#include <iostream>

namespace Parser {

/**
 *	@ingroup parser
 *
 *	Specification of a path from a token, through the sentence.
 *
 *	Syntax:
 *
 *	TP : integer | DIR(TP)
 *	DIR : leftChild | rightChild | parent | leftSibling | rightSibling |
 *	      previous | next | ancestor | leftDescendant | rightDescendant
 */
struct TokenPath
{
  enum Direction {
    leftChild,
    rightChild,
    parent,
    leftSibling,
    rightSibling,
    previous,
    next,
    ancestor,
    leftDescendant,
    rightDescendant
  };

  static char const* Names[];
  /** Get Direction enum. */
  static int direction(std::string& dir);

  TokenPath(int root) :
    root(root)
  { }

  /**	Extend the path with a new leg @c d.   */
  void	add(Direction d) {
    path.push_back(d);
    code += dirCode[d];
  }

  int	length() { return path.size(); }	

  /**	@return the string code of the path */
  char const* Code() const;

  static TokenPath*  parse(char const*& line);

  /**	@return a human readble representation of the path */
  std::ostream& serialize(std::ostream& os) const;

  static char const* const dirCode;

  std::vector<Direction>	path; ///< path to the token
  int		root;		///< the start token position
  std::string	code;		///< code string
};

inline std::ostream& operator <<(std::ostream& s, const TokenPath& d) 
{
  return d.serialize(s);
}

} // namespace Parser

#endif // Parser_TokenPath_H


