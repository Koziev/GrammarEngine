/*
**  Tanl C++ Library
**  text/Utf8Utils.cpp: utilities for handling UTF-8
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

#include "Utf8Utils.h"
#include <wchar.h>

namespace Tanl {
namespace Text {

namespace Unicode {

void incUtfPtr(const char*& ptr)
{
  unsigned char c = *ptr;
  if (c < 128) ptr++;
  else if ((c & 0xe0) == 0xc0) ptr += 2;
  else if ((c & 0xf0) == 0xe0) ptr += 3;
  else if ((c & 0xf8) == 0xf0) ptr += 4;
  else ptr++;
}

void decUtfPtr(const char*& ptr, const char* beginptr)
{
  while (ptr > beginptr) {
    if ((*--ptr & 0xc0) != 0x80)
      return;
  }
}

size_t utfDiff(const char* end, const char* begin)
{
  size_t count;
  for (count = 0; begin < end; incUtfPtr(begin))
    ++count;
  return count;
}

bool isAscii(const char* begin, const char* end)
{
  for (; begin < end; ++begin)
    if ((unsigned char)*begin > 127)
      return false;
  return true;
}

UCS2 fetchChar(const char*& it, const char* end)
{
  if (it >= end)
    return 0;
  int char_byte_length;
  int byte_mask = 0;
  if ((unsigned char)*it < 128) { char_byte_length = 1; byte_mask = 0x7f; }
  else if ((*it & 0xe0) == 0xc0) { char_byte_length = 2; byte_mask = 0x1f; }
  else if ((*it & 0xf0) == 0xe0) { char_byte_length = 3; byte_mask = 0x0f; }
  else if ((*it & 0xf8) == 0xf0) { char_byte_length = 4; byte_mask = 0x07; }
  else { char_byte_length = -1; }

  UCS2 ret = it[0] & byte_mask;
  for (int i = 1; i < char_byte_length; ++i) {
    if ((it[i] & 0xc0) != 0x80) {
      ret = 0xFFFF;
      break;
    }
    ret <<= 6;
    ret |= (it[i] & 0x3f);
  }
  it += char_byte_length;
  //  ret = Number::fromLittleEndian(ret);
  return ret;
}

int byteLength(const char* it)
{
  unsigned char c = *((unsigned char*)it);
  if (c < 128) return 1;
  if ((c & 0xe0) == 0xc0) return 2;
  if ((c & 0xf0) == 0xe0) return 3;
  if ((c & 0xf8) == 0xf0) return 4;
  return -1;
}

int utfLength(UCS2 ucc) 
{
  int neededBytes;
  if (ucc < 0x80)
    neededBytes = 1;
  else if (ucc < 0x800)
    neededBytes = 2;
  else
    neededBytes = 3;
  return neededBytes;
}

int utfLength(const UCS2* begin, const UCS2* end)
{
  int len = 0;
  for (const UCS2* it = begin; it < end; ++it)
    len += utfLength(*it);
  return len;
}

int ucLength(const UCS2* ch)
{
  const UCS2* begin = ch;
  while (*ch++ != 0) 
    ;
  return ch - begin - 1;
}

int uc4Length(const UCS4* ptr)
{
  const UCS4* begin = ptr;
  while (*ptr++ != 0) 
    ;
  return ptr - begin - 1;
}

int ToUtf8(byte*& it, byte* end, UCS2 ucc)
{
  static const int firstByteMark[4] = {0x00, 0xC0, 0xE0, 0xF0};
  const int byteMask = 0x3F;
  const int byteMark = 0x80; 
  if (ucc < 0x80) {
    if (end && it >= end)
      return 1;
    *it++ = (unsigned char)ucc;
    return 0;
  }
  int neededBytes = utfLength(ucc);
  if (end && it + neededBytes >= end)
    return neededBytes;
  it += neededBytes;
  byte* tptr = it;
  switch (neededBytes) {
  case 4:	*--tptr = (ucc & byteMask) | byteMark; ucc >>= 6;
  case 3:	*--tptr = (ucc & byteMask) | byteMark; ucc >>= 6;
  case 2:	*--tptr = (ucc & byteMask) | byteMark; ucc >>= 6;
  case 1:	*--tptr =  ucc | firstByteMark[neededBytes-1];
  }
  return 0;
}

int ToUtf8(byte*& it, const size_t max, const UCS2* ucbegin, const size_t len)
{
  byte* end = it + max;
  const UCS2* ucend = ucbegin + len;
  int needed = 0;
  for (const UCS2* uit = ucbegin; uit < ucend; ++uit) {
    int reqired = ToUtf8(it, end, *uit);
    if (reqired > 0)
      needed += reqired;
  }
  return needed;
}

UCS2* ToUc(UCS2* buffer, const char* source, int length)
{
  if (length == -1)
    length = ::strlen(source);
  UCS2* it = buffer;
  for (const char* end = source + length; source < end; ++source, ++it) {
    *it = (UCS2)*source; // FIXME: check for overflow
  }
  *it = 0;
  return buffer;
}

UCS2* ToUc(UCS2* buffer, const UCS4* source, int length)
{
  if (length == -1)
    length = uc4Length(source);
  UCS2* it = buffer;
  for (const UCS4* end = source + length; source < end; ++source, ++it) {
    *it = (UCS2)*source; // FIXME: check for overflow
  }
  *it = 0;
  return buffer;
}

UCS2* ToUc(UCS2* buffer, const wchar_t* source, int length)
{
  if (length == -1)
    length = wcslen(source);
  UCS2* it = buffer;
  for (const wchar_t* end = source + length; source < end; ++source, ++it) {
    *it = (UCS2)*source; // FIXME: check for overflow
  }
  *it = 0;
  return buffer;
}

UCS2* utf8ToUc(UCS2* buffer, const char* source, int length)
{
  UCS2* tptr = buffer;
  const char* sptr = source;
  if (length == -1)
      length = strlen(source);
  for (int i = 0; i < length; ++i, ++sptr, ++tptr) {
    *tptr = *sptr; // FIXME: to implement
  }
  *tptr  = 0;
  return buffer; 
}

} // namespace Unicode
} // namespace Text
} // namespace Tanl
