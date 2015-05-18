/*
**  Tanl C++ Library
**  text/String.cpp
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

#include "String.h"
#include "Encoding.h"
#include "Common/util.h"	// FOR_EACH

namespace Tanl {
namespace Text {

// Constructors:

String::String(const String& s, const size_type p1, const size_type p2) :
  str(s.str, p1, p2)
{ }

String::String(const CharType* c) :
  str((UCS2*)c)
{ }

String::String(const CharType* c, const size_type l) :
  str((UCS2*)c, l)
{ }

String::String(const size_type l, const CharType c) :
  str(l, c)
{ }

String::String(const StringType& s) :
  str(s)
{ }

template<class InputIterator>
String::String(InputIterator b, InputIterator e) :
  str(b, e)
{ }

// members:

int String::compare(const size_type, const size_type, const String&) const
{
  // FIXME:
  return 0;
}

int String::compare(const size_type, const size_type, const String&,
                 const size_type, const size_type) const
{
    // FIXME:
  return 0;
}

int String::compare(const CharType*) const
{
    // FIXME:
  return 0;
}

int String::compare(const size_type, const size_type,
                 const CharType*) const
{
    // FIXME:
  return 0;
}

int String::compare(const size_type, const size_type,
                 const CharType*, const size_type) const
{
    // FIXME:
  return 0;
}

String::CharType& String::operator[](const size_type p)
{
  return *(CharType*)&str[p];
}

String::CharType& String::at(const size_type p)
{
  return *(CharType*)&str.at(p);
}

String&
String::assign(const String& s, const size_type p1, const size_type p2)
{
    str.assign(s.str, p1, p2);
    return *this;
}

String& String::assign(const CharType* c)
{
    str.assign((UCS2*)c);
    return *this;
}

String&
String::assign(const CharType* c, const size_type l)
{
    str.assign((UCS2*)c, l);
    return *this;
}

String&
String::assign(const size_type l, const CharType c)
{
    str.assign(l, c);
    return *this;
}

void String::swap(String& that) throw()
{
  str.swap(that.str);
}

String&
String::append(const String& s, const size_type p1, const size_type p2)
{
  size_type start = str.length();
  str.append(s.str, p1, p2);
  return *this;
}

String&
String::append(const CharType* c, const size_type l)
{
    size_type start = str.length();
    str.append((UCS2*)c, l);
    return *this;
}

String& String::append(const CharType* c)
{
    str.append((UCS2*)c);
    return *this;
}

String&
String::append(const size_type l, const CharType c)
{
    str.append(l, c);
    return *this;
}

String&
String::insert(const size_type p1, const String& s,
            const size_type p2, const size_type p3)
{
    str.insert(p1, s.str, p2, p3);
    return *this;
}

String&
String::insert(const size_type p1,
            const CharType* c, const size_type p2)
{
    str.insert(p1, (UCS2*)c, p2);
    return *this;
}

String&
String::insert(const size_type p1, const CharType* c)
{
    size_type old_length = str.length();
    str.insert(p1, (UCS2*)c);
    return *this;
}

String&
String::insert(const size_type p1, const size_type p2,
            const CharType c)
{
    str.insert(p1, p2, c);
    return *this;
}

String&
String::replace(const size_type p1, const size_type p2,
             const String& s,
             const size_type p3, const size_type p4)
{
    str.replace(p1, p2, s.str, p3, p4);
    return *this;
}

String&
String::replace(const size_type p1, const size_type p2,
             const CharType* c, const size_type l)
{
    str.replace(p1, p2, (UCS2*)c, l);
    return *this;
}

String&
String::replace(const size_type p1,  const size_type p2,
             const CharType* c)
{
    str.replace(p1, p2, (UCS2*)c);
    return *this;
}

String&
String::replace(const size_type p1, const size_type p2,
             const size_type p3, CharType c)
{
    str.replace(p1, p2, p3, c);
    return *this;
}

void String::resize(const size_type l)
{
    str.resize(l);
}

void String::resize(const size_type l, CharType c)
{
    str.resize(l, c);
}

void String::clear()
{
    str.clear();
}

String& String::erase()
{
    str.erase();
    return *this;
}

String& String::erase(const size_type i)
{
    str.erase(i);
    return *this;
}

String& String::erase(const size_type i, const size_type l)
{
    str.erase(i, l);
    return *this;
}

String& String::erase(iterator b, iterator e)
{
  str.erase(b, e);
  return *this;
}

String::String(const std::string& s, const size_t pos,
	       const std::string encoding)
{
  convert(s.data(), pos, s.length(), encoding);
}

String::String(const char* c, const std::string encoding)
{
  convert(c, 0, ::strlen(c), encoding);
}

String::String(const char* c, const size_t len, const std::string encoding)
{
  convert(c, 0, len, encoding);
}

std::string String::convert(const std::string& encoding) const
{
  Encoding const* e = Encoding::get(encoding.c_str());
  Encoding const* ucs2 = Encoding::get("UCS-2");
  size_t clen = size_t(length() * e->maxBytesPerChar);
  char* converted = new char[clen];
  size_t len = e->Encode(ucs2, (char const*)str.data(),
			 length() * sizeof(UCS2), converted, clen);
  std::string result(converted, len);
  delete [] converted;
  return result;
}
    
size_t String::convert(const char* s, const size_t start, const size_t end,
		       const std::string& encoding)
  throw (std::length_error)
{
  clear();
  size_t len = end - start;
  if (len >= max_size())
    throw (std::length_error("Input String too long."));
  Encoding const* e = Encoding::get(encoding.c_str());
  Encoding const* ucs2 = Encoding::get("UCS-2");
  char* converted = new char[len * sizeof(UCS2)];
  size_t clen = ucs2->Encode(e, s + start, len, converted, len * sizeof(UCS2));
  assign((Char*)converted, clen / sizeof(UCS2));
  delete [] converted;
  return clen / sizeof(UCS2);
}

bool String::StartsWith(const char* c) const
{
  UCS2* uc = (UCS2*)c;
  FOR_EACH(StringType, str, cib) {
    if (*uc == 0)
      return false;
    if (*uc++ != *cib)
      return false;
  }
  return false;
}

bool String::StartsWithNoCase(const char* c) const
{
  UCS2* uc = (UCS2*)c;
  FOR_EACH(StringType, str, cib) {
    if (*uc == 0)
      return false;
    if (Char(*uc++).ToLower() != *cib)
      return false;
  }
  return false;
}

bool String::contains(const char* c) const
{
  return find(c) != std::string::npos;
}

String::size_type String::find(const char* c) const {
  FOR_EACH (StringType, str, it) {
    String::const_iterator sit(it);
    const char* s = c;
    for (; *s; s++) {
      if (sit == end())
	return std::string::npos;
      if (*s != *sit++)
	break;
    }
    if (*s == '\0')
      return it - str.begin();
  }
  return std::string::npos;
}

String String::ToLower() const {
  String lower(length(), ' ');
  int i = 0;
  FOR_EACH (StringType, str, it)
    lower[i++] = CharType(*it).ToLower();
  return lower;
}

String String::ToLower() {
  TO_EACH (StringType, str, it)
    *it = CharType(*it).ToLower();
  return *this;
}


} // namespace Text
} // namespace Tanl
