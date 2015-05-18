/*
**  IXE C++ Library
**  ixe/conf/conf_string.cpp
**  ----------------------------------------------------------------------
**  Copyright (c) 2000  Ideare SpA.
**  Copyright (c) 2000  Giuseppe Attardi (attardi@di.unipi.it).
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

// Settings
#include "conf/conf_string.h"

// standard
#include <iostream>

// local
#include "text/strings.h"

using namespace std;
using namespace Tanl::Text;

namespace IXE {

//=============================================================================
/**
 *      Parse a single string value from the line of text.
 *
 *      @param line            The line of text to be parsed.
 */
//=============================================================================

void conf<string>::parseValue(char const*& line)
{
  if (!line || !*line) {
    value = "";
    return;
  }
  char const* start = line;
  char const* s = next_token_line(line, "\"");
  if (!s) {
    line = start;
    s = next_token_line(line, "\t\r");
    while (*s && *s == ' ') s++;	     // trim leading spaces
    while (line > s && *line == ' ') line--; // trim trailing spaces
  }
  value = string(s, line - s);
}

} // namespace IXE
