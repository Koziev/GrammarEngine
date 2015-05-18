/*
**  IXE C++ Library
**  ixe/conf/conf_set.cpp
** ----------------------------------------------------------------------
**  Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
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

// local
#include "conf/conf_set.h"

// standard
#include <stdlib.h>

namespace IXE {

//=============================================================================
/**
 *      Parse a series of values from a line of text.
 *
 *      @param line            The line of text to be parsed.
 */
//=============================================================================

template <>
void conf_set<std::string>::parseValue(char const*& line)
{
  for (register char const *s; (s = next_token_line(line, " \r\t")); )
    this->value.insert(std::string(s, line - s));
}

template <>
void conf_set<int>::parseValue(char const*& line)
{
  for (register char const *s; (s = next_token_line(line, " \r\t")); )
    this->value.insert(atoi(s));
}

std::ostream& operator <<(std::ostream& os, std::set<std::string>& x)
{
  for (std::set<std::string>::const_iterator it = x.begin(); it != x.end(); ++it)
    os << *it << ' ';
  return os;
}

} // namespace IXE
