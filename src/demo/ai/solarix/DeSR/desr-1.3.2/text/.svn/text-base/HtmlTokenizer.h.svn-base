/*
**  Tanl C++ Library
**  ixe/text/HtmlTokenizer.h
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

#ifndef Tanl_Text_HtmlTokenizer_H
#define Tanl_Text_HtmlTokenizer_H

#include "text/StringTokenizer.h"

using namespace std;

namespace Tanl {
namespace Text {

/**
 *	Similar to StringTokenizer, except that it skips HTML tags
 */

class HtmlTokenizer : public StringTokenizer {

public:

  // include \n
  /**
   *	Default newline delimiters
   */
  static char const delimitersNL[]; // = " \t\n\r";

  HtmlTokenizer() :
    StringTokenizer() { }

  /**
   *	Tokenize into words delimited by @param delim.
   *	Read text from stream
   *
   *	@param is	input stream
   *	@param delim	string of deliminting characters
   */
  HtmlTokenizer(istream& is, char const* delim = delimitersNL) :
    StringTokenizer(is, delim) { }

  /**
   *	Tokenize into words delimited by @param delim.
   *	Read from text between @param start and @param end.
   *
   *	@param start	string beginning
   *	@param end	string end
   *	@param delim	string of deliminting characters
   */
  HtmlTokenizer(char const* s, char const* end = 0,
	     char const* delim = delimitersNL) :
    StringTokenizer(s, end, delim) { }

  /**
   *	@return next token.
   */
  char const*		next();
  /**
   *	Tell whether there is a next token.
   */
  char const*		hasNext();

};

} // namespace Text
} // namespace Tanl

#endif // Tanl_Text_HtmlTokenizer_H
