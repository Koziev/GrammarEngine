/*
**  IXE C++ Library
**  ixe/text/StreamTokenizer.cpp
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

#include "text/strings.h"
#include "text/StreamTokenizer.h"
#include <iostream>

using namespace std;

namespace Tanl {
namespace Text {

char const* StreamTokenizer::hasNext()
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
  }
  count += end - start;	// got to the end
  return 0;
}

bool StreamTokenizer::getline()
{
  if (count) count++;	// (count previous \n)
  if (is->getline(line, MAX_LINE_LEN)) {
    lineNumber++;
    rest = line;
    end = line + ::strlen(line);
    return true;
  }
  return false;
}

} // namespace Text
} // namespace Tanl

