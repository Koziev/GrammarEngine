/*
**	Tanl
**	text/Utf8CharIterator.h
** ----------------------------------------------------------------------
**	Copyright (c) 2004  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
**
**  This file is part of Tanl.
**
**  Tanl is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  Tanl is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#ifndef Tanl_Text_Utf8CharIterator_h
#define Tanl_Text_Utf8CharIterator_h

#include "text/Char.h"
#include "text/CharBuffer.h"
#include "text/Utf8Utils.h"

namespace Tanl {
namespace Text {

template <>
class CharBuffer<Utf8Char>::iterator
{
public:

  typedef Char		CharType; ///< returned type
  typedef char		CodeUnit; /// type of the underlining buffer elements
  typedef ptrdiff_t	Distance;

  iterator(CodeUnit const* ptr) :
    ptr(ptr) {}

  CharType	operator *() const { return Unicode::toChar(ptr, ptr + 4); }
  CharType&	operator [](Distance n) const { return *(CharType*)(ptr + n); }

  inline void incPtr() { Unicode::incUtfPtr(ptr); }
  inline void decPtr() { Unicode::decUtfPtr(ptr, ptr - 4);  }

  iterator& operator ++() { incPtr(); return *this; }
  iterator operator ++(int) { iterator t(*this); incPtr(); return t; }

  iterator& operator --() { decPtr(); return *this; }
  iterator operator --(int) { iterator t(*this); decPtr(); return t; }

  iterator&	operator +=(Distance n) { ptr += n; return *this; }
  iterator&	operator -=(Distance n) { ptr -= n; return *this; }

  inline bool	operator ==(iterator const& other) {
    return ptr == other.ptr;
  }

  inline bool	operator !=(iterator const& other) {
    return ptr != other.ptr;
  }

  iterator operator +(int offset) {
    if (offset < 0)
      return operator -(-offset);
    iterator t(*this);
    while (offset-- > 0)
      ++t;
    return t;
  }

  iterator operator -(int offset) {
    if (offset < 0)
      return operator +(-offset);
    iterator t(*this);
    while (offset++ < 0)
      --t;
    return t;
  }

  int operator -(const iterator& other) const { return Unicode::utfDiff(ptr, other.ptr); }
  
  bool operator <(const iterator& other) const { return ptr < other.ptr; }
  bool operator <=(const iterator& other) const { return ptr <= other.ptr; }
  bool operator >(const iterator& other) const { return ptr > other.ptr; }
  bool operator >=(const iterator& other) const { return ptr >= other.ptr; }
  bool operator ==(const iterator& other) const { return ptr == other.ptr; }
  bool operator !=(const iterator& other) const { return ptr != other.ptr; }

private:
  CodeUnit const*	ptr;
};

} // Text
} // namespace Tanl

#endif // Tanl_Text_Utf8CharIterator_h
