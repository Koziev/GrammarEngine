/*
**  IXE C++ Library
**  ixe/conf/PatternSet.h
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

#ifndef IXE_PatternSet_H
#define IXE_PatternSet_H

// Settings
#include "platform.h"

// standard
#include <algorithm>			/* for find_if() */
#include <fnmatch.h>			/* for fnmatch(3) */

// local
#include "include/unordered_set.h"
#include "text/strings.h"

using namespace IXE::Text;

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A PatternSet contains a set of shell wildcard patterns.
 *
 * SEE ALSO
 *
 *	International Standards Organization.  "ISO/IEC 9945-2: Information
 *	Technology -- Portable Operating System Interface (POSIX) -- Part 2:
 *	Shell and Utilities," 1993.
 */

// in hash_set use equal_to() from text/strings.h

class PatternSet : public unordered_set<char const*>
{
public:
  typedef unordered_set<char const*> Set;
  typedef Set::key_type		key_type;
  typedef Set::value_type	value_type;
  typedef Set::iterator		iterator;
  typedef Set::const_iterator	const_iterator;

  //
  // find() must be overridden to use our own comparison function.
  //
  iterator find(char const* file_name) {
    return std::find_if(begin(), end(), pattern_match(file_name));
  }
  const_iterator find(char const* file_name) const {
    return std::find_if(begin(), end(), pattern_match(file_name));
  }

  bool matches(char const* file_name) const {
    return find(file_name) != end();
  }

  void insert(value_type const& n) { Set::insert(::strdup(n)); }

  void insert(value_type const& s, size_t n) { Set::insert(strndup(s, n)); }

  ~PatternSet() {
    for (Set::iterator it = begin(); it != end(); it++)
      free((void*)*it);
  }

private:
  class pattern_match : public 
  std::unary_function<value_type const&, bool> {
  public:
    pattern_match(char const* file_name) :
      file_name(file_name) { }
    bool operator ()(value_type const& pattern) const {
      return !::fnmatch(pattern, file_name, 0);
    }
  private:
    char const* const file_name;
  };
};

} // namespace IXE

#endif	/* IXE_PatternSet_H */
