/*
**  Tanl C++ Library
**  ixe/text/StringTokenizer.h
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

#ifndef Tanl_Text_StringTokenizer_H
#define Tanl_Text_StringTokenizer_H

#include "platform.h"
#include <string>

namespace Tanl {
namespace Text {

#define MAX_LINE_LEN 4096

  static char const delimiters[] = " \t\r";

class StringTokenizer {

public:
  StringTokenizer() : is(0) { }

  /**
   *	Tokenize into words delimited by @param delim.
   *	Read text from stream
   *
   *	@param is	input stream
   *	@param delim	string of deliminting characters
   */
  StringTokenizer(std::istream& is, char const* delim = delimiters);

  /**
   *	Tokenize into words delimited by @param delim.
   *	Read from text between @param start and @param end.
   *
   *	@param start	string beginning
   *	@param end	string end
   *	@param delim	string of deliminting characters
   */
  StringTokenizer(char const* s, char const* end = 0,
	     char const* delim = delimiters);

  char const*	hasNext();

  char const*	next();

  /**
   *	Return the length of the current token
   */
  int		tokenLength() { return toklen; }

  /**
   *	Return the number of characters before the current token
   */
  int		tokenStart() { return count; }

  /**
   *	Advance count. Used when token had to be split.
   */
  void		advance(int n) { count += n; if (tok) tok += n; toklen -= n; }

protected:

  int		count;		// characters up to token
  int		lineNumber;
  std::istream*	is;
  char		line[MAX_LINE_LEN];
  char const*	tok;		// current token
  int		toklen;		// lenght of current token
  char const*	rest;		// cursor on text
  char const*	end;		// end of text
  char const*	delim;		// delimiters between tokens
};

} // namespace Text
} // namespace Tanl

#endif // Tanl_Text_StringTokenizer_H
