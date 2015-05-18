/*
**  Tanl C++ Library
**  ixe/text/StreamTokenizer.h
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

#ifndef Tanl_Text_StreamTokenizer_H
#define Tanl_Text_StreamTokenizer_H

#include "text/StringTokenizer.h"

using namespace std;

namespace Tanl {
namespace Text {

#define MAX_LINE_LEN 4096

class StreamTokenizer : public StringTokenizer {

public:

  StreamTokenizer(istream& is) : StringTokenizer(is) { }

  char const*		hasNext();
  
  /**
   *	Read next line from stream.
   *	@return false	if no more lines
   */
  bool		getline();

};

} // namespace Text
} // namespace Tanl

#endif // Tanl_Text_StreamTokenizer_H
