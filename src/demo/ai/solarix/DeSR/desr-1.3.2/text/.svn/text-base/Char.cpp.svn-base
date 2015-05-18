/*
**  Tanl C++ Library
**  text/Char.cpp
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

// Local
#include "text/Char.h"

namespace Tanl {
namespace Text {

using namespace Tanl::Text::Unicode;

int Char::ToDigit(int radix)
{
  if (radix < MinRadix || radix > MaxRadix)
      return -1;
  if (ucs >= '0' && ucs <= '9')
    return ucs - '0';
  if (ucs >= 'A' && ucs <= 'Z' && ucs < radix + 'A' - 10)
    return ucs - 'A' + 10;
  if (ucs >= 'a' && ucs <= 'z' && ucs < radix + 'a' - 10)
    return ucs - 'a' + 10;
  return -1;
}

Char Char::ToLower() const
{
  int idx = UnicodeTable[ucs].downcase;
  if (idx == 0)
    return *this;
  return Char(idx);
}

Char Char::ToUpper() const
{
  int idx = UnicodeTable[ucs].upcase;
  if (idx == 0)
    return *this;
  return Char(idx);
}

} // Text
} // Tanl
