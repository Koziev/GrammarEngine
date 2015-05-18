/*
**  IXE C++ Library
**  ixe/conf/FileType.cpp
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
#include "conf/FileType.h"

// standard
#include <cstdlib>		/* for exit(2) */

// local
#include "text/strings.h"
#include "include/exit_codes.h"

using namespace std;
using namespace IXE::Text;

namespace IXE {

//=============================================================================
/**
 *
 *      Parse a FileType configuration file line.  The format of such a line
 *      is:
 *	<pre>
 *              type	pattern+
 *	</pre>
 *      where "type" is a MIME type and "pattern" is a file pattern
 *
 *      @param line            The line to be parsed.
 *
 */
//=============================================================================

void FileType::parseValue(char const*& line)
{
  char const* type = next_token_line(line, " \r\t");
  if (!type) {
    LOG(error) << "no file type" << endl;
    ::exit(Exit_Config_File);
  }
  type = strndup(type, line - type);
  char const* pattern;
  bool nopattern = true;
  while (pattern = next_token_line(line, " \r\t")) {
    value.insert(strndup(pattern, line - pattern), type);
    nopattern = false;
  }
  if (nopattern) {
    LOG(error) << "no file pattern" << endl;
    ::exit(Exit_Config_File);
  }
}

} // namespace IXE
