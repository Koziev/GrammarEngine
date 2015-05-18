/*
**  IXE C++ Library
**  ixe/conf/PatternMap.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2000  Ideare SpA.
**  Copyright (c) 2000  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef IXE_PatternMap_H
#define IXE_PatternMap_H

// Settings
#include "platform.h"

// standard
#include <algorithm>			/* for find_if() */
#include <fnmatch.h>			/* for fnmatch(3) */
#include <map>

// local
#include "text/less.h"

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A PatternMap maps a shell wildcard pattern to an object of type T.
 *
 * SEE ALSO
 *
 *	International Standards Organization.  "ISO/IEC 9945-2: Information
 *	Technology -- Portable Operating System Interface (POSIX) -- Part 2:
 *	Shell and Utilities," 1993.
 *
 * NOTE
 *
 *	Note that the declaration of std::map has a default "Compare" template
 *	parameter of "less<key_type>" and, since we've included less.h above
 *	that defines "less<char const*>", C-style string comparisons work
 *	properly.
 *
*/

template <class T>
class PatternMap : public std::map<char const*, T>
{
public:
  typedef std::map<char const*, T> Map;
  typedef typename Map::key_type key_type;
  typedef typename Map::value_type value_type;
  typedef typename Map::iterator iterator;
  typedef typename Map::const_iterator const_iterator;

  //
  // find() must be overridden to use our own comparison class.
  //
  iterator find(char const* name) {
    return std::find_if(this->begin(), this->end(), pattern_match(name));
  }
  const_iterator find(char const* name) const {
    return std::find_if(this->begin(), this->end(), pattern_match(name));
  }

  bool matches(char const* name) const {
    return find(name) != this->end();
  }

  void insert(char const* pattern, T const& t) {
    (*this)[pattern] = t;
  }
  void insert(value_type const& n) { Map::insert(n); }
private:
  class pattern_match : public std::unary_function<value_type const&, bool> {
  public:
    pattern_match(char const* name) :
      name(name) { }
    bool operator ()(value_type const& map_node) const {
      return !::fnmatch(map_node.first, name, 0);
    }
  private:
    char const* const name;
  };
};

} // namespace IXE

#endif	/* IXE_PatternMap_H */
