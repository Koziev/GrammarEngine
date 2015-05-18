/*
**  Tanl C++ Library
**  ixe/text/Char.h
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

#ifndef Tanl_Text_Char_h
#define Tanl_Text_Char_h

// standard
#include <cstring>		// For memmove, memset, memchr
#include <cwchar>		// For wmemset
#include <string>
#include <cstdio>		// EOF

#include "text.h"
#include "Unicode.h"

namespace Tanl {
namespace Text {

/**
 *	Representation of Unicode characters
 */
class Char // : public IComparable<Char>
{
public:

  typedef Char		CharType; ///< type of chars to return
  typedef UCS2		CodeUnit; ///< code units out of which the Char is made

  static const int MaxRadix = 36;
  static const int MinRadix = 2;

  static const UCS2 MaxValue = 0xFFFF;
  static const UCS2 MinValue = 0x0000; 

  Char() { }

  Char(UCS2 ucs) : ucs(ucs) { }

  operator UCS2() const { return ucs; }

  //bool operator ==(Char const& other) const { return ucs == (UCS2)other; }
  //bool operator ==(char const& other) const { return ucs == (UCS2)other; }

  //bool operator !=(Char const& other) const { return ucs != (UCS2)other; }
  //bool operator !=(char const& other) const { return ucs != (UCS2)other; }

  //bool operator <(Char const& other) const { return ucs < (UCS2)other; }
  //bool operator <(char const& other) const { return ucs < (UCS2)other; }

  //bool operator <=(Char const& other) const { return ucs <= (UCS2)other; }
  //bool operator <=(char const& other) const { return ucs <= (UCS2)other; }

  //bool operator >(Char const& other) const { return ucs > (UCS2)other; }
  //bool operator >(char const& other) const { return ucs > (UCS2)other; }

  //bool operator >=(Char const& other) const { return ucs >= (UCS2)other; }
  //bool operator >=(char const& other) const { return ucs >= (UCS2)other; }

  /**
   * Compares this Char to another Char, returning an integer that
   * indicates the relationship. 
   * @return a value less than zero if this  object
   *	 null is considered to be less than any instance.
   */
  int	CompareTo(Char const& other) const { return ucs - (UCS2)other; }

  int	CompareCase(Char const& other) const {
    return ToLower().ucs - other.ToLower().ucs; }

  Unicode::Category	GetCategory() const {
    return (Unicode::Category)Unicode::UnicodeTable[ucs].category;
  }

  bool	IsControl() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Control; }

  bool	IsDigit() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Number; }

  bool	IsLetter() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Letter; }

  bool	IsLetterOrDigit() const { return IsDigit() || IsLetter(); }

  bool	IsLower() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Lowercase; }

  bool	IsMark() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Control;
  }

  /** Checks if the character is a punctuation character.*/
  bool	IsPunctuation() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Punctuation;
  }

  /** Checks if the character is a space character.*/
  bool	IsSpace() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Whitespace ||
      ucs == 0x00A0; // "NO-BREAK SPACE"
  }

  bool	IsSymbol() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Symbol;
  }

  bool	IsTitle() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Titlecase;
  }

  bool	IsUpper() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Uppercase;
  }

  /** Checks if the Unicode character is a whitespace character.*/
  bool	IsWhitespace() const {
    return Unicode::UnicodeTable[ucs].flags & Unicode::Whitespace;
  }

  int	ToDigit(int radix);

  Char	ToLower() const;

  Char	ToUpper() const;

  /**
   *	Return the Unicode allocation block that contains the character.
   */
  Unicode::BlockCode	BlockCode() { return Unicode::GetBlockCode(ucs); }

protected:
  UCS2 ucs;
};

/**
 *	This is just a type specifier for use in CharBuffer
 */
class Utf8Char : public Char
{
 public:
  typedef Char		CharType;
  typedef char		CodeUnit; ///< out of which the Char is made
};

/**
 *	This is just a type specifier for use in CharBuffer
 */
class CChar
{
public:
  typedef char		CharType;
  typedef char		CodeUnit; ///< out of which the Char is made
};

} // Text
} // Tanl

namespace std {

#if defined(__GNUC__) && __GNUC__ < 3

struct string_char_traits<Tanl::Text::Char> {

  typedef Tanl::Text::Char	char_type;

  static void assign(char_type& c1, const char_type& c2) { c1 = c2; }
  static bool eq(const char_type& c1, const char_type& c2) {
    return (c1 == c2);
  }
  static bool ne(const char_type& c1, const char_type& c2) {
    return (c1 != c2);
  }
  static bool lt(const char_type& c1, const char_type& c2) {
    return (c1 < c2);
  }
  static char_type eos() { return 0; }
  static bool is_del(char_type a) { return char_type(a).IsSpace(); }
  static int compare(const char_type* s1, const char_type* s2, size_t n) {
    return ::wmemcmp((wchar_t const*)s1, (wchar_t const*)s2, n);
  }
  static size_t length(const char_type* s) {
    size_t i = 0;
    while (!eq(s[i], char_type(0))) ++i;
    return i;
  }
  static char_type* copy(char_type* s1, const char_type* s2, size_t n) {
    return (char_type*)::wmemcpy((wchar_t*)s1, (wchar_t const*)s2, n);
  }
  static char_type* move(char_type* s1, const char_type* s2, size_t n) {
    return (char_type*)::wmemmove((wchar_t*)s1, (wchar_t const*)s2, n);
  }
  static char_type* set(char_type* s, const char_type& c, size_t n) {
    return (char_type*)::wmemset((wchar_t*)(Tanl::Text::UCS2*)s, (Tanl::Text::UCS2)c, n);
  }
};

#else

template<>
struct char_traits<Tanl::Text::Char> {

  typedef Tanl::Text::Char	char_type;
  typedef int			int_type;
  typedef streampos		pos_type;
  typedef streamoff		off_type;
  typedef mbstate_t		state_type;

  static void
  assign(char_type& c1, const char_type& c2) { c1 = c2; }

  // char_type comparison
  static bool
  eq(const char_type& c1, const char_type& c2) {
    return (c1 == c2);
  }

  static bool
  lt(const char_type& c1, const char_type& c2) { return(c1 < c2); }

  // operations on s[n] arrays
  static int
  compare(const char_type* s1, const char_type* s2, size_t n) {
    for (size_t i = 0; i < n; ++i) {
      if (eq(s1[i], s2[i])) continue;
      if (lt(s1[i], s2[i])) return -1;
      else return 1;
    }
    return 0;
  }

  static size_t
  length(const char_type* s) {
    size_t i = 0;
    while (!eq(s[i], char_type(0))) ++i;
    return i;
  }

  static const char_type*
  find(const char_type* s, size_t n, const char_type& c) {
    size_t i = 0;
    while (i < n && !eq(s[i], c)) ++i;
    return s + i;
  }

  static char_type*
  move(char_type* s1, const char_type* s2, size_t n) {
    return static_cast<char_type*>
     (::memmove(s1, s2, n * sizeof(char_type)));
  }

  static char_type*
  copy(char_type* s1, const char_type* s2, size_t n) {
    return static_cast<char_type*>
     (::memcpy(s1, s2, n * sizeof(char_type)));
  }

  static char_type*
  assign(char_type* s, size_t n, char_type a) {
    for (size_t i = 0; i < n; ++i)
      assign(s[i], a);
    return s; 
  }

  static char_type
  to_char_type(const int_type& i) { return char_type(i); }

  static int_type
  to_int_type(const char_type& c) { return (Tanl::Text::UCS2)c; }

  static bool
  eq_int_type(const int_type& i1, const int_type& i2) { return (i1 == i2); }

  static int_type
  eof() { return static_cast<int_type>(EOF); }

  static int_type
  not_eof(const int_type& i) { return (eof() == i) ? !eof() : i; }
};

#endif // __GNUC__

} // namespace std

#endif // Tanl_Text_Char_h
