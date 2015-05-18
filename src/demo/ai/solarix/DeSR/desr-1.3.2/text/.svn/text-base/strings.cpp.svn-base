/*
**  Tanl C++ library
**  text/strings.cpp
** ----------------------------------------------------------------------
**  Copyright (c) 2002  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
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
#include "text/strings.h"

using namespace std;

#ifndef _GNU_SOURCE
char* strndup(char const* s, int len)
{
  char* res = (char*)malloc(len + 1);
  ::strncpy(res, s, len);
  res[len] = '\0';
  return res;
}
#endif

namespace Tanl {
namespace Text {

bool strStartsWith(const char* s1, const char* init)
{
  for (; *s1 && *init && to_lower(*s1) == to_lower(*init); s1++, init++)
    ;
  return *init == '\0';
}

//=============================================================================
/**
 *
 *      Convert a long integer to a string.
 *
 *      @param n	The long integer to be converted.
 *      @param s	A pointer to the string.
 */
//=============================================================================

void itoa(register long n, register char* s)
{
  char* s0 = s;
  bool const is_neg = n < 0;

  if (is_neg)
    n = -n;
  do
    *s++ = n % 10 + '0';	// generate digits in reverse
  while (n /= 10);
  if (is_neg)
    *s++ = '-';
  *s = '\0';

  // now reverse the string
  for (register char *t = s0; t < s; ++t)
    {
      char const tmp = *--s;
      *s = *t;
      *t = tmp;
    }
}

//=============================================================================
/**
 *      Convert a string to lower case.
 *
 *      @param d	The destination string.
 *      @param s	The string to be converted.
 */
//=============================================================================
void to_lower(register char* d, register char const* s)
{
  while ((*d++ = to_lower(*s++)))
    ;
}

//=============================================================================
/**
 *      Destructively convert a string to lower case.
 *
 *      @param s	The string to be converted.
 *      @return		The same string, after convertion.
 */
//=============================================================================

char* to_lower(register char *s)
{
  for (register char *p = s; (*p = to_lower(*p)); p++) ;
  return s;
}

//=============================================================================
/**
 *
 *      Convert a string to lower case
 *
 *      @param s	The string to be converted.
 *      @return		The modified string converted to lower-case.
 */
//=============================================================================

string& to_lower(string &s)
{
  string::iterator p = s.begin();
  int len = s.length();

  while (len-- > 0) {
    *p = tolower(*p);
    p++;
  }
  return s;
}

//=============================================================================
/**
 *      Convert a string to upper case.
 *
 *      @param d	The destination string.
 *      @param s	The string to be converted.
 */
//=============================================================================
void to_upper(register char* d, register char const* s)
{
  while ((*d++ = to_upper(*s++)))
    ;
}

//=============================================================================
/**
 *      Destructively convert a string to upper case.
 *
 *      @param s	The string to be converted.
 *      @return		The same string, after convertion.
 */
//=============================================================================

char* to_upper(register char *s)
{
  for (register char *p = s; (*p = to_upper(*p)); p++) ;
  return s;
}

//=============================================================================
/**
 *
 *      Convert a string to upper case
 *
 *      @param s	The string to be converted.
 *      @return		The modified string converted to upper-case.
 */
//=============================================================================

string& to_upper(string &s)
{
  string::iterator p = s.begin();
  int len = s.length();

  while (len-- > 0) {
    *p = toupper(*p);
    p++;
  }
  return s;
}

/**
 *	simple string tokenizer.
 *	A token is a sequence of characters delimited by characters
 *	in @param sep.
 *	@param start	the beginning of the text to search
 *	@param end	the end of the text to search
 *	@param sep	sequence of delimiting characters
 *	@return		the start of the first token from @param ptr.
 *	Advances @param start to the end of the token.
 */
char  const* next_token(char const*& start, char const* end, const char* sep)
{
  // skip all letters that are included in the separator string
  while (start < end && strchr(sep, *start))
    ++start;

  if (start == end)
    return 0;

  char const* token = start;

  // scan through the string to find where it ends, it ends on a
  // null byte or a character that exists in the separator string
  while (++start < end && !strchr(sep, *start))
    ;

  return token;			// return the position where the token starts
}

/**
 *	simple string tokenizer, with escape.
 *	if preceded by @param esc.
 *	A token is a sequence of characters delimited
 *	by characters in @param sep except when preceded by @param esc.
 *	@param sep	sequence of delimiting characters
 *	@return		the first token from @param ptr.
 *	Advances ptr to the end of the token.
 *	@param esc	is an escape character for line continuation
 */
char  const* next_token(char const*& ptr, const char* sep, char esc)
{
  // skip all letters that are included in the separator string
  // except when preceded by esc character
  while (*ptr) {
    if (*ptr == esc) {
      ++ptr;
      if (*ptr)
	++ptr;
    } else if (strchr(sep, *ptr))
      ++ptr;
    else
      break;
  }

  if (*ptr) {
    // so this is where the next piece of string starts
    char const* start = ptr++;

    // scan through the string to find where it ends, it ends on a
    // null byte or a character that exists in the separator string
    while (*ptr) {
      if (*ptr == esc) {
	++ptr;
	if (*ptr)
	  ++ptr;
      } else if (strchr(sep, *ptr))
	break;
      else
	++ptr;
    }

    return start;		// return the position where the string starts
  }

  // we ended up on a null byte, there are no more strings to find!
  return 0;
}

char* strstr(const char* haystack, const char* needle, size_t count)
{
  if (!*needle)
    return((char*)haystack);

  char const* end = haystack + count;
  for (char* cp = (char*)haystack; cp < end && *cp; cp++) {
    char* s2 = (char*)needle;

    for (char* s1 = cp; s1 < end && *s1 && *s2 && !(*s1-*s2); s1++, s2++)
      ;

    if (!*s2)
      return(cp);
  }
  return(NULL);
}

// Convenient overloading

std::string operator+(const std::string s, const int i)
{
  char is[32];
  std::string str(s);
  itoa(i, is);
  str.append(is);
  return str;
}

std::string operator+(const int i, const std::string s)
{
  char is[32];
  itoa(i, is);
  std::string str(is);
  str.append(s);
  return str;
}

std::string operator+(const std::string s, const unsigned i)
{
  char is[32];
  std::string str(s);
  itoa(i, is);
  str.append(is);
  return str;
}

std::string operator+(const unsigned i, const std::string s)
{
  char is[32];
  itoa(i, is);
  std::string str(is);
  str.append(s);
  return str;
}

} // namespace Text
} // namespace Tanl
