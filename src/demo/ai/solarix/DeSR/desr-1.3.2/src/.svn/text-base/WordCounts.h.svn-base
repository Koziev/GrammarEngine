/*
**  DeSR
**  src/WordCounts.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef DeSR_WordCounts_H
#define DeSR_WordCounts_H

// settings
#include "include/unordered_map.h"

// IXE library
#include "lib/strtok_r.h"

// standard
#include <string>
#include <fstream>

namespace Parser {

/**
 *	@ingroup parser
 */
struct WordCounts : public unordered_map<std::string, int> {
  int add(std::string const& w) {
    iterator wcit = find(w);
    // increment # of occurrences
    int count;
    if (wcit == end())
      count = operator[](w) = 1;
    else
      count = ++wcit->second;
    return count;
  }
  int count(std::string const& w) {
    iterator wcit = find(w);
    return (wcit == end()) ? 0 : wcit->second;
  }
};

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

/**
 *	@ingroup parser
 */
class WordFreq : public unordered_map<const char*, float, hash<const char*>, eqstr>
{
public:

  typedef unordered_map<const char*, float, hash<const char*>, eqstr> HashMap;

  /**
   * Load from file containing one n-gram per line.
   */
  WordFreq(char const* file) { load(file); }
  WordFreq(std::string& file) { load(file.c_str()); }

  ~WordFreq() {
    for (iterator it = this->begin(); it != this->end(); ++it) 
      free((void*)it->first);		// allocated by strdup()
  }

  /**
   *	Test for the presence of ngram @a ngram in the set.
   */
  bool	contains(char const* ngram) {
    return this->find(ngram) != this->end();
  }

  /**
   *	Test for the presence of ngram @a ngram in the set.
   */
  bool	contains(std::string const& ngram) {
    return this->find(ngram.c_str()) != this->end();
  }

  /**
   *	Ensure we have our own copy of ngrams.
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
      _Where = this->insert(value_type(_Keyval, mapped_type())).first;
    return _Where->second;
  }

  /**
   * Load from file: one ngram per line.
   */
  void	load(char const* file) {
    std::ifstream ifs(file);
    load(ifs);
  }

  /**
   *	Format: one ngram per line. Each line contains:
   *	   ngram count 
   */
  void	load(std::ifstream& ifs) {
# define MAX_LINE_LEN 4096
    char line[MAX_LINE_LEN];

    while (ifs.getline(line, MAX_LINE_LEN)) {
      char* next = line;
      char const* ngram = strtok_r(0, "\t", &next);
      float count = atof(strtok_r(0, " ", &next));
      insert(std::make_pair(ngram, count));
    }
#  undef MAX_LINE_LEN
  }
};

} // namespace Parser

#endif // DeSR_WordCounts_H
