/*
**  DeSR
**  src/TokenPath.cpp
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

#include "conf/conf.h"		// next_token_line()
#include "TokenPath.h"

// standard
#include <stdlib.h>		// strtol()

using namespace std;

namespace Parser {

char const* const TokenPath::dirCode = "/\\^<>-+!{}";

  char const* TokenPath::Names[] = {
    "leftChild",
    "rightChild",
    "parent",
    "leftSibling",
    "rightSibling",
    "prev",
    "next",
    "anc",
    "leftDesc",
    "rightDesc"
  };

int TokenPath::direction(string& dir)
{
  char const** end = Names + sizeof(Names)/sizeof(char const*);
  for (char const** it = Names; it < end; it++)
    if (*it == dir)
      return (Direction)(it - Names);
  return -1;
}

char const* TokenPath::Code() const
{
  return code.c_str();
}


/**
 * Check whether string @c str occurs at the beginning of line, after
 * any leading blanks.
 */
static bool check(char const*& line, char const* str)
{
  char const* start = line;
  // skip blanks
  char const* tok = IXE::next_token_line(line, " \r\t");
  if (::strstr(tok, str) == tok) {
    line = start + ::strlen(str);
    return true;
  }
  return false;
}

/**
 *	parse next token path specification from @c line. Advance @c line.
 *	@return a TokenPath representing the specified path or 0
 *	if no path specification found.
 */
TokenPath*  TokenPath::parse(char const*& line)
{
  char const* st = IXE::next_token_line(line, " \r\t()");
  if (!st) return 0;
  string tok(st, line - st);
  char* endptr;
  long pos = strtol(tok.c_str(), &endptr, 10);
  if (tok.c_str() != endptr)
    return new TokenPath(pos);
  TokenPath::Direction dir = (TokenPath::Direction)TokenPath::direction(tok);
  if (dir == -1) {
    cerr << "Wrong token specification: " << tok << endl;
    return 0;
  }
  // check open paren
  if (!check(line, "(")) {
    cerr << "Wrong token syntax after: " << tok << " at: " << line << endl;
    return 0;
  }
  TokenPath* tp = parse(line);
  if (!tp)
    return 0;
  tp->add(dir);
  // check closing paren
  if (!check(line, ")")) {
    cerr << "Wrong token syntax after: " << tok << " at: " << line << endl;
    return 0;
  }
  return tp;
}

std::ostream& TokenPath::serialize(ostream& os) const
{
  int depth = 0;
  for (int i = 0; i < path.size(); i++) {
    os << Names[path[i]] << '(';
    depth++;
  }
  os << root;
  while (depth--)
    os << ')';
  return os;
}

} // namespace Parser
