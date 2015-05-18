/*
**  IXE C++ Library
**  ixe/text/HtmlTokenizer.cpp
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

#include "text/HtmlTokenizer.h"

#include <istream>
#include <string.h>

using namespace std;

namespace Tanl {
namespace Text {

// include \n
char const HtmlTokenizer::delimitersNL[] = " \t\n\r";

/**
 *	string tokenizer that skips HTML tags.
 *	A token is a sequence of characters delimited by characters
 *	in @param sep.
 *	@param start	the beginning of the text to search
 *	@param end	the end of the text to search
 *	@param sep	sequence of delimiting characters
 *	@return		the start of the first token from @param ptr.
 *	Advances @param start to the end of the token.
 */
static
char  const*
next_token(char const*& start, char const* end, const char* sep)
{
  // skip all letters that are included in the separator string
  while (start < end) {
    if (::strchr(sep, *start))
      ++start;
    else if (*start == '<') {
      while (start < end && *start++ != '>')
	;
    } else
      break;
  }

  if (start == end)
    return 0;

  char const* token = start;

  // scan through the string to find where it ends, it ends on a
  // null byte or a character that exists in the separator string
  while (++start < end && !::strchr(sep, *start))
    ;

  return token;			// return the position where the token starts
}

char const* HtmlTokenizer::next()
{
  if (hasNext()) {
    char const* res = tok;
    tok = 0;			// consume token, forcing hasNext() to advance
    return res;
  }
  return 0;
}

char const* HtmlTokenizer::hasNext()
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
      end = rest + is->gcount() - 1; // discard newline
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
