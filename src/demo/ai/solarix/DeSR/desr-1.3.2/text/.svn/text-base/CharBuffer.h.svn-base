/*
**  Tanl C++ Library
**  ixe/text/CharBuffer.h
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

#ifndef Tanl_Text_CharBuffer_h
#define Tanl_Text_CharBuffer_h

#include <stddef.h>
#include <iterator>

namespace Tanl {
  namespace Text {

/**
 *	A text buffer that provides a random access iterator through it.
 *
 *	This class can be used with various types of characters.
 *
 *	For instance
 *	<dl>
 *	<dt>@c CharBuffer<CChar> </dt><dd> is a buffer consisting of
 *	C characters, and the iterator *() returns the current C character.
 *
 *	<dt>@c CharBuffer<Char> </dt><dd> is a buffer consisting of
 *	Unicode characters, and the @c iterator *() returns the current Unicode
 *	character.
 *
 *	<dt>@c CharBuffer<Utf8> </dt><dd> is a buffer consisting of
 *	Utf8 characters, and the iterator *() returns the current
 *	character converted to Unicode.
 *	</dl>
 *	
 *	CharTraits is a specifier that must define:
 *	<ul>
 *	<li> @c CharType, the type of the characters to return
 *	<li> @c CodeUnits, the type of characters in the buffer
 *	</ul>
 *
 */

template <typename CharTraits>
class CharBuffer
{
public:

  typedef typename CharTraits::CharType	CharType; ///< type of chars to return
  typedef typename CharTraits::CodeUnit	CodeUnit; ///< type of chars in buffer

  typedef CharType* 		pointer;
  typedef const CharType*	const_pointer;
  typedef CharType&		reference;
  typedef const CharType&	const_reference;
  typedef size_t 		size_type;
  typedef ptrdiff_t 		Distance;

  CharBuffer(CharType* start = 0, size_t length = 0) :
    start((CodeUnit*)start),
    length(length)
  { }

  class iterator :
    public std::iterator<std::random_access_iterator_tag, CharType> {

  public:

    /**
     *	The type of the elements of the buffer.
     */
    typedef typename CharTraits::CodeUnit CodeUnit;

    iterator(CodeUnit const* ptr = 0) : ptr(ptr) { }

    // Interface implementation

    CharType	operator *() const { return *ptr; }
    CharType*	operator ->() { return (CharType*)ptr; }

    CharType	operator[](int n) { return *(ptr + n); }
    CharType const operator[](int n) const { return *(ptr + n); }

    iterator&	operator ++() { ++ptr; return *this; }
    iterator&	operator --() { --ptr; return *this; }
    // postfix versions:
    iterator	operator ++(int) { return iterator(ptr++); }
    iterator	operator --(int) { return iterator(ptr--); }
    iterator&	operator +=(int n) { ptr += n; return *this; }
    iterator&	operator -=(int n) { ptr -= n; return *this; }

    iterator	operator +(int n) const { return iterator(ptr + n); }

    iterator	operator -(int n) const { return iterator(ptr - n); }

    Distance	operator -(iterator& other) const { return ptr - other.ptr; }

    bool	operator <(iterator& other) const { return ptr < other.ptr; }
    bool	operator <=(const iterator& other) const {
      return ptr <= other.ptr; }
    bool	operator >(const iterator& other) const {
      return ptr > other.ptr; }
    bool	operator >=(const iterator& other) const {
      return ptr >= other.ptr; }
    bool	operator ==(const iterator& other) const {
      return ptr == other.ptr; }
    bool	operator !=(const iterator& other) const {
      return ptr != other.ptr; }

    operator	CodeUnit const*() const { return ptr; }
    operator	CodeUnit*() const { return (CodeUnit*)ptr;}

    iterator	StartsWith(char const* other, iterator end);

  protected:
    CodeUnit const*	ptr;
  };

  class const_iterator : public iterator {
    public:
    const_iterator(CodeUnit const* ptr = 0) : iterator(ptr)
    { }
  };

  reference	operator[](size_type n) { return *(begin() + n); }

  iterator	begin() { return iterator(start); }
  iterator	end() { return iterator(start + length); }

  const_iterator begin() const { return const_iterator(start); }
  const_iterator end() const { return const_iterator(start + length); }

  Distance	size() { return end() - begin(); }

protected:
  CodeUnit const*	start;		///< start of text
  Distance		length;		///< length of text

};

} // namespace Text
} // namespace Tanl

#endif // Tanl_Text_CharBuffer_h
