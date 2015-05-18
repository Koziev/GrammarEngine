/*
**  Tanl C++ Library
**  text/StringTokenizer.cpp
**  ----------------------------------------------------------------------
**  Copyright (c) 2002  Giuseppe Attardi (attardi@di.unipi.it).
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

#include "text/StringTokenizer.h"
#include "text/strings.h"
#include <iostream>

using namespace std;

namespace Tanl {
namespace Text {

StringTokenizer::StringTokenizer(istream& is, char const* delim) :
  count(0),
  lineNumber(0),
  is(&is),
  tok(0),
  toklen(0),
  rest(0),
  end(0),
  delim(delim)
{ }

StringTokenizer::StringTokenizer(char const* s, char const* end,
				 char const* delim) :
  count(0),
  lineNumber(0),
  is(0),			// unused
  tok(0),
  toklen(0),
  rest(s),
  end(end ? end : s + ::strlen(s)),
  delim(delim)
{ }

char const* StringTokenizer::next()
{
  if (hasNext()) {
    char const* res = tok;
    tok = 0;			// consume token, forcing hasNext() to advance
    return res;
  }
  return 0;
}

char const* StringTokenizer::hasNext()
{
  if (tok)
    return tok;
  count += toklen;	// count characters up to end of previous token
  char const* start = rest;
  if (rest && rest < end) { // continue on same line
    if ((tok = next_token(rest, end, delim))) {
      toklen = rest - tok;
      count += tok - start;	// count characters before next token
      return tok;
    }
  } else if (is) {
    if (count) count++;	// (count previous \n)
    while (is->getline(line, MAX_LINE_LEN)) {
      lineNumber++;
      start = rest = line;
      end = rest + is->gcount() - 1; // do not count newline
      if ((tok = next_token(rest, end, delim))) {
	toklen = rest - tok;
	count += tok - start; // count characters before next token
	return tok;
      }
    }
  }
  count += end - start;	// got to the end
  return 0;
}

} // namespace Text
} // namespace Tanl
