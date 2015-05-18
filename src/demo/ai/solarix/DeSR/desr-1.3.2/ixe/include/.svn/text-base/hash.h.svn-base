/*
**	IXE
**	include/hash.h
** ----------------------------------------------------------------------
**	Copyright (c) 2009  Giuseppe Attardi (attardi@di.unipi.it)
** ----------------------------------------------------------------------
**
**  This file is part of IXE.
**
**  IXE is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  IXE is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#if !defined(IXE_include_unordered_map_H) && !defined(IXE_include_unordered_set_H)
#warning Do not include this file directly. \
 It gets included by either unordered_map.h or unordered_set.h.
#endif

#ifndef	IXE_include_hash_H
#define	IXE_include_hash_H

/**
 * Brain damage:
 * ext::hash_map does not hash std:string, but hashes char*
 * tr1::unordered_map does not hash char*, but hashes std:string
 */

#if defined(HAVE_STD_UNORDERED_MAP)

using std::hash;

namespace std {

  inline size_t
  __stl_hash_string(const char* __s)
  {
    unsigned long __h = 0;
    for ( ; *__s; ++__s)
      __h = 5 * __h + *__s;
    return size_t(__h);
  }

  template<>
    struct hash<char const*>
    : public std::unary_function<char const*, std::size_t>
    {      
      std::size_t
      operator()(const char const* __s) const
      { return __stl_hash_string(__s); }
    };
}

#elif defined(HAVE_TR1_UNORDERED_MAP)

using std::tr1::hash;

namespace std { namespace tr1 {

  inline size_t
  __stl_hash_string(const char* __s)
  {
    unsigned long __h = 0;
    for ( ; *__s; ++__s)
      __h = 5 * __h + *__s;
    return size_t(__h);
  }

  template<>
    struct hash<char const*>
    : public std::unary_function<char const*, std::size_t>
    {      
      std::size_t
      operator()(const char* __s) const
      { return __stl_hash_string(__s); }
    };
}}

#else

# if defined(HAVE_EXT_HASH_MAP_SET)

#  if __GNUC__ >= 3
#   define HASH_NS __gnu_cxx
#  else
#   define HASH_NS std
#  endif
   using HASH_NS::hash;

# elif (_MSC_VER >= 1400)

#  define HASH_NS stdext
   using HASH_NS::hash;

# else

#  define HASH_NS std
   using HASH_NS::hash;
# endif

#include <string>

namespace HASH_NS {
  template<> struct hash<std::string>
  {
    size_t operator()(const std::string& x) const
    {
      return hash<const char*>()(x.c_str());
    }
  };
}
#endif

#endif // IXE_include_hash_H
