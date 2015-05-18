/*
**  IXE C++ Library
**  ixe/io/Format.h
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

#ifndef IXE_IO_format_H
#define IXE_IO_format_H

#include <string>
#include <stdarg.h>

namespace IXE {
  namespace io {

/**
 *	A class to perform formatted output
 *
 *  Example of use:
 *  @code
 *  int month = 7, day = 26, year = 76;
 *  std::string name = "Birthday";
 *  Format result("%s = %d-%02d-%02d\n", name.c_str(), month, day, year);
 *  @endcode
 */

struct Format : public std::string
{
  Format(const char* fmt ...);
};

  }
}

#endif // IXE_IO_format_H
