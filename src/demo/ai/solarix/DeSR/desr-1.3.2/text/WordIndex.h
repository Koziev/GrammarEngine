/*
**  Tanl C++ library
**  text/WordIndex.h
** ----------------------------------------------------------------------
**  Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef Tanl_Text_WordIndex_H
#define Tanl_Text_WordIndex_H

// settings
#include "include/unordered_map.h"

// standard
#include <string.h>
#include <stdlib.h>

namespace Tanl {
namespace Text {

struct eqstr
{
  typedef const char* first_argument_type;   ///< the type of the first argument
  typedef const char* second_argument_type;  ///< the type of the second argument
  typedef bool result_type;		     ///< type of the return type

  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

struct eqstrcase
{
  typedef const char* first_argument_type;   ///< the type of the first argument
  typedef const char* second_argument_type;  ///< the type of the second argument
  typedef bool result_type;		     ///< type of the return type

  bool operator()(const char* s1, const char* s2) const
  {
    return strcasecmp(s1, s2) == 0;
  }
};

  /**
   *	Associates an ID to each word in a set.
   */
struct WordIndex : public unordered_map<const char*, unsigned, hash<const char*>, eqstr>
{
  static const unsigned None = (unsigned)-1;
  typedef unordered_map<const char*, unsigned, hash<const char*>, eqstr> HashMap;

  WordIndex() { }

  WordIndex(WordIndex const& other) {
    for (WordIndex::const_iterator oit = other.begin();
	 oit != other.end(); ++oit)
      insert(*oit);
  }

  ~WordIndex() { clear(); }

  void clear() {
    for (WordIndex::iterator it = begin(); it != end(); ++it) {
      free((void*)it->first);		// allocated by strdup()
    }
    HashMap::clear();
  }

  /**
   *	Get the index associated to a word @c key.
   *	@return the index associated to the word or @c None if not present.
   */
   mapped_type index(const key_type& key) {
     iterator _Where = this->find(key);
     return (_Where == this->end()) ? None : _Where->second;
   }

  /**
   *	Add a new word.
   */
   mapped_type insert(const key_type& key) {
    iterator _Where = this->find(key);
    if (_Where == this->end()) {
      key_type _Keyval = ::strdup(key);
      mapped_type mapval = this->size();
      HashMap::insert(value_type(_Keyval, mapval));
      return mapval;
    } else
      return _Where->second;
  }

  /**
   *	Ensure we have our own copy of words.
   */
  std::pair<iterator,bool> insert(const value_type& __obj) {
    iterator _Where = this->find(__obj.first);
    key_type _Keyval = (_Where == this->end()) ?
      ::strdup(__obj.first) :
      _Where->first;
    return HashMap::insert(value_type(_Keyval, __obj.second));
  }

  mapped_type& operator[](const key_type& _Keyval) {
    // find element matching _Keyval or insert with default mapped
    iterator _Where = this->find(_Keyval);
    if (_Where == this->end())
      _Where = HashMap::insert(value_type(::strdup(_Keyval), mapped_type())).first;
    return _Where->second;
  }

  WordIndex& operator=(const WordIndex& wi)
  {
    clear();
    for (WordIndex::const_iterator it = wi.begin(); it != wi.end(); ++it)
      insert(*it);
    return *this;
  }

};

} // namespace Text
} // namespace Tanl

#endif // Tanl_Text_WordIndex_H
