/*
**  Tanl C++ Library
**  ixe/text/Utf8Utils.h: utilities for handling UTF-8
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

#ifndef Tanl_text_Utf8Utils_h
#define Tanl_text_Utf8Utils_h

// Standard
#include <sys/types.h>
#include <string.h>

#if defined(_WIN32)
# include <tchar.h>
#endif

// local
#include "text.h"
#include "Char.h"

namespace Tanl {
namespace Text {

/**
 * Utilities to handle UTF-8 strings
 */
namespace Unicode
{
  typedef unsigned char byte;

  void incUtfPtr(const char*& ptr);
  void decUtfPtr(const char*& ptr, const char* begin);
  size_t utfDiff(const char* end, const char* begin);
  bool isAscii(const char* begin, const char* end);

  UCS2 fetchChar(const char*& begin, const char* end);
  inline UCS2 toChar(const char* begin, const char* end)
  {
    const char* it = begin;
    return fetchChar(it, end);
  }
  int byteLength(const char* it);
  /**
    return the number of byte a unicode character needs
  */
  int utfLength(UCS2 ch);
  
  /**
    returns the number of bytes a unicode string needs
  */
  int utfLength(const UCS2* begin, const UCS2* end);
  /**
    returns the length of 0 terminated unicode character string
  */
  int ucLength(const UCS2* ch);
  inline int uc2Length(const UCS2* ch) { return ucLength(ch); }
  /**
    returns the length of an 0-terminated UCS4 stream
  */
  int uc4Length(const UCS4* ch);
  /**
   *    writes a Unicode char into the given char buffer.
   *	@param ucc if the character to store.
   *    @param it start position to write.
   *              After the call, @a it will point to next writing position.
   *    @param end end position in buffer, if 0 no checking for end is done.
   *    @return 0 is Ok
   *          > 0 chars needed to encode the given Unicode character
   *          When return value != 0, @a it will not be changed.
   */
  int ToUtf8(byte*& it, byte* end, UCS2 ucc);

  inline int ToUtf8(char*& it, Char c, char* end = 0) {
    return ToUtf8((byte*&)it, (byte*)end, (UCS2)c);
  }
  /**
   *    Writes the given Unicode character range into a char buffer range.
   *    @param it start position to write.
   *    @param max size of buffer, if 0 no checking for end is done.
   *    @return number of bytes written, -1 if error.
   */
  int ToUtf8(byte* it, const size_t max, const UCS2* ucbegin, const size_t len);

  /**
   *    converts an char stream to an UCS2 stream.
   *
   *    buffer must have enough space to get all length + 1 chars
   *    @param buffer target to write
   *    @param source 0 terminated char string
   *    @param length length of source, -1 if 0 terminated string 
   *    @return just the buffer
   */
  UCS2* ToUc(UCS2* buffer, const char* source, int length);
  /**
   *    converts an uc4 character stream to an UCS2 stream.
   *    uc4 chars that cannot be mapped are mapped to 0xFFFF
   *
   *    buffer must have enough space to get all length + 1 chars
   *    @param buffer target to write
   *    @param source 0 terminated UCS4 stream
   *    @param length length of source, -1 if 0 terminated uc4 string 
   *    @return just the buffer
   */
  UCS2* ToUc(UCS2* buffer, const UCS4* source, int length = -1);
  /**
   *    converts a wchar character stream to an UCS2 stream.
   *    wchar chars that cannot be mapped are mapped to 0xFFFF
   *
   *    buffer must have enough space to get all length + 1 chars
   *    @param buffer target to write
   *    @param source 0 terminated UCS4 stream
   *    @param length length of source, -1 if 0 terminated uc4 string 
   *    @return just the buffer
   */
  UCS2* ToUc(UCS2* buffer, const wchar_t* source, int length = -1);
  /**
   *     Convert an UTF-8 stream into Unicode UCS2
   */
  UCS2* utf8ToUc(UCS2* buffer, const char* source, int length = -1);

  inline size_t stringLength(const char* str) { return strlen(str); }
  inline size_t stringLength(const UCS2* str) { return ucLength(str); }
  inline size_t stringLength(const UCS4* str) { return uc4Length(str); }
  
  template <typename ToCharType, typename FromCharType>
  inline ToCharType* convertTo(ToCharType* buffer, const FromCharType* source, int length = -1)
  {
    if (length == -1)
      length = stringLength(source);
    ToCharType* tit = buffer;
    register const FromCharType* fit = source;
    register const FromCharType* end = source + length;
    for (; fit < end; ++tit, ++fit)
      *tit = *fit;
    return buffer;
  }

} // namespace Unicode
} // namespace text
} // namespace Tanl


#endif //Tanl_text_Utf8Utils_h
