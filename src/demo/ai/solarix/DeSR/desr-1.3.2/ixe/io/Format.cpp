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

// Settings
#include "Format.h"

// standard
#include <stdio.h>
#include <cstdarg>
#ifdef _WIN32
  #include <malloc.h>
  #define alloca	_alloca
  #define vsnprintf _vsnprintf
#else
  #include <alloca.h>
#endif

namespace IXE {
  namespace io {

Format::Format(const char* fmt ...)
{
  va_list argList;
  va_start(argList, fmt);

  // If the string is less than 512 characters, use fixed buffer
  char buffer[512];

  int numChars = vsnprintf(buffer, sizeof(buffer), fmt, argList);

  if (-1 < numChars && numChars < sizeof(buffer)) {
    // Got it on the first try.
    assign(buffer, numChars);
  } else {
    char* stackBuffer = (char*)alloca(numChars+1); // 1 for null

    numChars = vsnprintf(stackBuffer, numChars+1, fmt, argList);
    assign(stackBuffer, numChars);
  }
  va_end(argList);
}

  }
}
