/*
**  IXE C++ Library
**  ixe/conf/conf_bool.cpp
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
#include "conf/conf_bool.h"

// standard
#include <iostream>

// local
#include "text/strings.h"

using namespace std;
using namespace Tanl::Text;

namespace IXE {

//=============================================================================
/**
 *
 *      Parse a Boolean value from the line of text.  Acceptable values
 *      (regardless of case) are: f, false, n, no, off, on, t, true, y, yes
 *
 *      @param line            The line of text to be parsed.
 *
 */
//=============================================================================
/* virtual */
void conf<bool>::parseValue(char const*& lines)
{
  char const* line = next_token_line(lines, "\n");
  if (!strncasecmp(line, "false", 5) ||
      !strncasecmp(line, "f", 1) ||
      !strncasecmp(line, "no", 2) ||
      !strncasecmp(line, "n", 1) ||
      !strncasecmp(line, "off", 3) ||
      !strncasecmp(line, "0", 1)) {
      value = false;
      return;
    }
  if (!strncasecmp(line, "true", 4) ||
      !strncasecmp(line, "t", 1) ||
      !strncasecmp(line, "yes", 3) ||
      !strncasecmp(line, "y", 1) ||
      !strncasecmp(line, "on", 2) ||
      !strncasecmp(line, "1", 1)) {
      value = true;
      return;
    }
  LOG(error) << '"' << name() << "\" is not one of: "
	  "false, f, no, n, off, 0, true, t, yes, y, on, 1" << endl;
}

} // namespace IXE
