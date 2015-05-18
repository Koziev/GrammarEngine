/*
**  Tanl C++ Library
**  ixe/text/String.h
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

#ifndef _Tanl_String_H
#define _Tanl_String_H

#include "Char.h"
#include "CharBuffer.h"
#include <string>
#include <stdexcept>

namespace Tanl {
namespace Text {

/**
 *	String class
 *	This class stores and manipulates strings of characters defined 
 *	according to ISO10646. 
 */
class String {
  // Do not inherit from std::basic_string. It's not meant to be derived
  // from :-(

public:
  // Can't use Char since MSVC requires a class without constructor to instantiate basic_string<>
  typedef std::basic_string<UCS2> StringType;
  typedef Char CharType;
  // import types from StringType:
  typedef StringType::traits_type traits_type;
  typedef StringType::value_type value_type;
  typedef StringType::size_type size_type;
  typedef StringType::difference_type difference_type;
  typedef StringType::reference reference;
  typedef StringType::const_reference const_reference;
  typedef StringType::pointer pointer;
  typedef StringType::const_pointer const_pointer;
  typedef StringType::iterator iterator;
  typedef StringType::const_iterator const_iterator;
  typedef StringType::reverse_iterator reverse_iterator;
  typedef StringType::const_reverse_iterator const_reverse_iterator;

  static const size_type npos = -1; // MSVC does't like std::string::npos;

  // Constructors:
  String() { }
  String(const String&, const size_type = 0, const size_type = npos);
  String(const CharType*);
  String(const CharType*, const size_type);
  String(const size_type, const CharType);
  template<class InputIterator>
  String(InputIterator, InputIterator);
# ifdef __GNUC__
private:
  struct Rep {
    size_t len, res, ref;
    bool selfish;
  };
public:
  /**
   *	Specialization for CharBuffer<Char>::iterator that uses copy-on-write
   *	to avoid copying.
   */
  String(CharBuffer<Char>::iterator b, CharBuffer<Char>::iterator e) :
    str()
  {
    Rep& rep = *reinterpret_cast<Rep*>(&str);
    rep.len = e - b;
    rep.res = rep.len;		// capacity
    rep.ref = 2;		// reference count: avoid delete
    *((UCS2**)(&rep + 1)) = (UCS2*)b;
  }
# endif

  // copy constructor
  String(const StringType&);
      
  // Destructor:
  ~String() { }
      
  // Size Operations:

  size_type	size() const { return str.size(); }
  size_type	length() const { return str.length(); }
  bool		empty() const { return str.empty(); }
  size_type	max_size() const { return str.max_size(); }
      
  // Capacity Operations:
      
  size_type	capacity() const { return str.capacity(); }
  void		reserve(const size_type l) { str.reserve(l); }
      
  // Comparisons:
  int	compare(const String& s) const { return compare(0, npos, s); }
  int	compare(const size_type, const size_type, const String&) const;
  int	compare(const size_type, const size_type, const String&,
		const size_type, const size_type) const;
  int	compare(const CharType*) const;
  int	compare(const size_type, const size_type, const CharType*) const;
  int	compare(const size_type, const size_type,
	      const CharType*, const size_type) const;
      
  // Character Access
  CharType&	operator[](const size_type p);
  CharType	operator[](const size_type p) const { return str[p]; }
  CharType&	at(const size_type p);
  CharType	at(const size_type p) const { return str.at(p); }
      
  // Generating C-Strings and Character Arrays
      
  // Modify Operations:
  String&	assign(const String& s) { return assign(s, 0, npos); }
  String&	assign(const String&, const size_type, const size_type);
  String&	assign(const CharType*);
  String&	assign(const CharType*, const size_type);
  String&	assign(const size_type, const CharType);

  String&	operator=(const String s) { return assign(s); }
  String&	operator=(const CharType* c) { return assign(c); }
  String&	operator=(CharType c) { return assign(1, c); }
      
  void		swap(String&) throw ();
      
  String&	append(const String& s) { return append(s, 0, npos); }
  String&	append(const String&, const size_type, const size_type);
  String&	append(const CharType*, const size_type);
  String&	append(const CharType*);
  String&	append(const size_type, const CharType);
  template<class InputIterator>
  String&	append(InputIterator, InputIterator);
      
  void		push_back(CharType c) { append(1, c); }
      
  String&	operator+=(const String& s) { return append(s); }
  String&	operator+=(const CharType* c) { return append(c); }
  String&	operator+=(const CharType c) { return append(1, c); }
      
  String&	insert(const size_type p, const String& s)
  { return insert(p, s, 0, npos); }
  String&	insert(const size_type, const String&,
		       const size_type, const size_type);
  String&	insert(const size_type, const CharType*, const size_type);
  String&	insert(const size_type, const CharType*);
  String&	insert(const size_type, const size_type, const CharType);
  void		insert(iterator, const size_type, const CharType);
  iterator	insert(iterator, const CharType);
  void		insert(iterator, iterator, iterator);
      
  void		clear();
  String&	erase();
  String&	erase(const size_type);
  String&	erase(const size_type, const size_type);
  String&	erase(iterator, iterator);

  void		resize(const size_type);
  void		resize(const size_type, CharType);
      
  String&	replace(const size_type p1, const size_type p2, const String& s)
  { return replace(p1, p2, s, 0, npos); }
  String&	replace(iterator, iterator, const String&);
  String&	replace(const size_type, const size_type, const String&,
		  const size_type, const size_type);
  String&	replace(const size_type, const size_type,
		  const CharType*, const size_type);
  String&	replace(iterator, iterator, const CharType*, const size_type);
  String&	replace(const size_type, const size_type, const CharType*);
  String&	replace(iterator, iterator, const CharType*);
  String&	replace(const size_type, const size_type, const size_type, CharType);
  String&	replace(iterator, iterator, const size_type, CharType);
  template<class InputIterator>
  String&	replace(iterator, iterator, InputIterator, InputIterator);
      
  size_type	find(const CharType c) const { return str.find(c); }
  size_type	find(const CharType c, const size_type i)
  { return str.find(c, i); }
  size_type rfind(const CharType c) const { return str.rfind(c); }
  size_type rfind(const CharType c, const size_type i)
  { return str.rfind(c, i); }
      
  size_type	find(const String& s) const { return str.find(s.str); }
  size_type	find(const String& s, const size_type i)
  { return str.find(s.str, i); }
  size_type rfind(const String& s) const { return str.rfind(s.str); }
  size_type rfind(const String& s, const size_type i)
  { return str.rfind(s.str, i); }
      
  size_type	find(const CharType* c) const { return str.find((UCS2*)c); }
  size_type	find(const CharType* c, const size_type i)
  { return str.find((UCS2*)c, i); }
  size_type rfind(const CharType* c) const { return str.rfind((UCS2*)c); }
  size_type rfind(const CharType* c, const size_type i)
  { return str.rfind((UCS2*)c, i); }

  size_type	find(const char* c) const;

  size_type	find(const CharType* c, const size_type i, const size_type l) const
  { return str.find((UCS2*)c, i, l); }
  size_type rfind(const CharType* c, const size_type i, const size_type l)
  { return str.rfind((UCS2*)c, i, l); }
      
  size_type	find_first_of(const String& s) const
  { return str.find_first_of(s.str); }
  size_type	find_first_of(const String& s, const size_type i)
  { return str.find_first_of(s.str, i); }
  size_type	find_first_not_of(const String& s) const
  { return str.find_first_not_of(s.str); }
  size_type	find_first_not_of(const String& s, const size_type i)
  { return str.find_first_not_of(s.str, i); }
      
  size_type	find_first_of(const CharType* c) const
  { return str.find_first_of((UCS2*)c); }
  size_type	find_first_of(const CharType* c, const size_type i)
  { return str.find_first_of((UCS2*)c, i); }
  size_type	find_first_not_of(const CharType* c) const
  { return str.find_first_not_of((UCS2*)c); }
  size_type	find_first_not_of(const CharType* c, const size_type i)
  { return str.find_first_not_of((UCS2*)c, i); }
      
  size_type	find_first_of(const CharType* c, const size_type i,
			  const size_type l) const
  { return str.find_first_of((UCS2*)c, i, l); }
  size_type	find_first_not_of(const CharType* c, const size_type i,
			      const size_type l) const
  { return str.find_first_not_of((UCS2*)c, i, l); }
      
  size_type	find_first_of(const CharType c) const
  { return str.find_first_of(c); }
  size_type	find_first_of(const CharType c, const size_type i)
  { return str.find_first_of(c, i); }
  size_type	find_first_not_of(const CharType c) const
  { return str.find_first_not_of(c); }
  size_type	find_first_not_of(const CharType c, const size_type i)
  { return str.find_first_not_of(c, i); }
      
  size_type	find_last_of(const String& s) const
  { return str.find_last_of(s.str); }
  size_type	find_last_of(const String& s, const size_type i)
  { return str.find_last_of(s.str, i); }
  size_type	find_flast_not_of(const String& s) const
  { return str.find_last_not_of(s.str); }
  size_type	find_last_not_of(const String& s, const size_type i)
  { return str.find_last_not_of(s.str, i); }
      
  size_type	find_last_of(const CharType* c) const
  { return str.find_last_of((UCS2*)c); }
  size_type	find_last_of(const CharType* c, const size_type i)
  { return str.find_last_of((UCS2*)c, i); }
  size_type	find_last_not_of(const CharType* c) const
  { return str.find_last_not_of((UCS2*)c); }
  size_type	find_last_not_of(const CharType* c, const size_type i)
  { return str.find_last_not_of((UCS2*)c, i); }
      
  size_type	find_last_of(const CharType* c, const size_type i,
			 const size_type l) const
  { return str.find_last_of((UCS2*)c, i, l); }
  size_type	find_last_not_of(const CharType* c, const size_type i,
			     const size_type l) const
  { return str.find_last_not_of((UCS2*)c, i, l); }
      
  size_type	find_last_of(const CharType c) const
  { return str.find_last_of(c); }
  size_type	find_last_of(const CharType c, const size_type i)
  { return str.find_last_of(c, i); }
  size_type	find_last_not_of(const CharType c) const
  { return str.find_last_not_of(c); }
  size_type	find_last_not_of(const CharType c, const size_type i)
  { return str.find_last_not_of(c, i); }
      
  // Substrings and String Concatenation:
      
  String substr() const { return String(str.substr()); }
  String substr(const size_type i) const
  { return String(str.substr(i)); }
  String substr(const size_type i, const size_type l) const
  { return String(str.substr(i, l)); }
      
  // Generating Iterators:

  iterator begin() { return str.begin(); }
  const_iterator begin() const { return str.begin(); }
  iterator end() { return str.end(); }
  const_iterator end() const { return str.end(); }
  reverse_iterator rbegin() { return str.rbegin(); }
  const_reverse_iterator rbegin() const { return str.rbegin(); }
  reverse_iterator rend() { return str.rend(); }
  const_reverse_iterator rend() const { return str.rend(); }

  // ------------------------------------------------------------
  // methods *NOT* in basic_string:
  // ------------------------------------------------------------

  // Constructors:
  String(const std::string&, const size_t pos = 0,
         const std::string encoding = "UTF8");
  String(const char*, const std::string encoding = "UTF8");
  String(const char*, const size_t len,
         const std::string encoding = "UTF8");

  // Conversion:

  std::string	convert(const std::string& encoding = "UTF8") const;

  size_t	convert(const char*, const size_t start, const size_t end,
			const std::string& = "UTF8")
    throw (std::length_error);
      
  /**
   *	Checks whether the string starts with the c-string c
   */
  bool		StartsWith(const char* c) const;
  /**
   *	Checks whether the string starts with the c-string c, disregarding case
   */
  bool		StartsWithNoCase(const char* c) const;

  bool		contains(const char* c) const;

  String	ToLower() const;

  String	ToLower();

private:
  StringType	str;
};
  
  inline bool operator==(const String& s1, const String& s2)
  { return 0 == s1.compare(s2); }
  inline bool operator==(const String& s1, const std::string& s2)
  { return 0 == s1.compare(s2); }
  inline bool operator==(const String& s1, const char* s2)
  { return 0 == s1.compare(s2); }
  inline bool operator==(const std::string& s1, const String& s2)
  { return 0 == s2.compare(s1); }
  inline bool operator==(const char* s1, const String& s2)
  { return 0 == s2.compare(s1); }
  inline bool operator!=(const String& s1, const String& s2)
  { return 0 != s1.compare(s2); }
  inline bool operator<(const String& s1, const String& s2)
  { return 0 > s1.compare(s2); }
  inline bool operator>(const String& s1, const String& s2)
  { return 0 < s1.compare(s2); }
  inline bool operator<=(const String& s1, const String& s2)
  { return 0 >= s1.compare(s2); }
  inline bool operator>=(const String& s1, const String& s2)
  { return 0 <=s1.compare(s2); }

  inline String operator+(const String& s1, const String& s2) {
    String r(s1);
    return r.append(s2);
  }
  inline String operator+(const String& s1, String::CharType* c) {
    String r(s1);
    return r.append(c);
  }
  inline String operator+(String::CharType* c, const String& s1) {
    String r(c);
    return r.append(s1);
  }
  inline String operator+(const String& s1, String::CharType c) {
    String r(s1);
    r.push_back(c);
    return r;
  }
  inline String operator+(String::CharType c, const String& s1) {
    String r(1, c);
    return r.append(s1);
  }

} // namespace Text
} // namespace Tanl

namespace std
{
  inline void swap(Tanl::Text::String& a, Tanl::Text::String& b) { a.swap(b); }
    
} // namespace std

#endif // _Tanl_String_H
