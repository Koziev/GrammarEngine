/*
**  Tanl C++ library
**  text/strings.h
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

#ifndef	Tanl_Text_strings_H
#define	Tanl_Text_strings_H

// settings
#include "platform.h"

// standard
#include <cctype>
#include <cstring>
#include <string>
#include <functional>

#include "text/text.h"
#include "include/unordered_map.h"

#ifndef _GNU_SOURCE
/**
 * Variant of strdup() which copies @c len characters from @c s.
 */
char*			strndup(char const* s, int len);
#endif

namespace Tanl {
namespace Text {

//=============================================================================
/**
 *	String utilities
 */
//=============================================================================

extern void		itoa(long, char*);

			// ensure function semantics: 'c' is expanded once
inline char		to_lower(char c)	{ return (char)tolower(c); }
extern char*		to_lower(char*);
extern std::string&	to_lower(std::string&);
extern void		to_lower(register char* d, register char const* s);

inline char		to_upper(char c)	{ return (char)toupper(c); }
extern char*		to_upper(char*);
extern std::string&	to_upper(std::string&);
extern void		to_upper(register char* d, register char const* s);

char const*		next_token(char const*& start, char const* end,
				   const char* sep);
char const*		next_token(char const*& start, const char* sep,
				   char esc);

std::string		operator+(const std::string s, const int i);
std::string		operator+(const int i, const std::string s);
std::string		operator+(const std::string s, const unsigned i);
std::string		operator+(const unsigned i, const std::string s);

/**
 * Variant of strstr() which limits search to @c count characters in
 *	@c haystack.
 */
char*			strstr(const char* haystack, const char* needle,
			       size_t count);

inline int		strncasecmp(const char* s1, const char* s2)
{
  return ::strncasecmp(s1, s2, ::strlen(s2));
}

/**
 *	Determine whether string @a s1 starts with the sequence in @a init,
 *	disregarding case.
 */
bool			strStartsWith(const char* s1, const char* init);

/**
 *	Test for empty string.
 *	@returns true if string @c s is null or empty.
 */
inline bool		strempty(const char* s)
{
  return !s || (s[0] == '\0');
}

} // namespace Text
} // namespace Tanl

// Used in hash_set, hash_map
namespace std
{
  template <>
  struct equal_to<char const*> :
    public binary_function<char const*, char const*, bool> 
  {
    bool operator()(first_argument_type __x, first_argument_type __y) const {
      return ::strcmp(__x, __y) == 0;
    }
  };
}

#endif	/* Tanl_Text_strings_H */
