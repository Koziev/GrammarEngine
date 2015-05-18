/*
**  Tanl C++ Library
**  text/WordSet.h
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

#ifndef Tanl_Text_WordSet_H
#define Tanl_Text_WordSet_H

#include "include/unordered_set.h"
#include "text/strings.h"

// standard
#include <fstream>
#include <stdlib.h>

namespace Tanl {
namespace Text {

template <class HashType = hash<const char *>,
	  class _Pred = std::equal_to<const char*> >
class WordSetBase :
    public unordered_set<const char*, HashType, _Pred>
{
protected:
  typedef unordered_set<const char*, HashType, _Pred> _Base;

public:

  WordSetBase() { }

  /**
   * Load from file containing one word per line.
   */
  WordSetBase(char const* file);

  WordSetBase(std::string& file);

  ~WordSetBase() {
    for (typename _Base::iterator it = this->begin(); it != this->end(); ++it)
      free((void*)*it);		// allocated by strdup()
  }

  /**
   *	Test for the presence of word @a word in the set.
   */
  bool	contains(char const* word) {
    return this->find(word) != this->end();
  }

  /**
   *	Test for the presence of word @a word in the set.
   */
  bool	contains(std::string const& word) {
    return this->find(word.c_str()) != this->end();
  }

  /**
   *	Ensure we have our own copy of words.
   */
  std::pair<typename _Base::iterator, bool> insert(const char* word) {
    typename _Base::iterator fit = this->find(word);
    return (fit != this->end()) ?
      std::pair<typename _Base::iterator, bool>(fit, false) :
      _Base::insert(::strdup(word));
  }

  /**
   * Store to file: one word per line.
   */
  void	store(char const* file);

  /**
   * Load from file: one word per line.
   */
  void	load(char const* file);

protected:
  void	load(std::ifstream& ifs);
};

  /**
   *	Set of words.
   */

class WordSet : public WordSetBase<>
{
public:
  WordSet() { }
  WordSet(char const* file) :  WordSetBase<>(file) { }
  WordSet(std::string& file) : WordSetBase<>(file) { }
};

/**
 *	Compare strings by normalizing to lowercase and
 *	discarding non alphanumeric characters.
 *	Useful to compare acronyms or other designators.
 */
struct NormEqual
{
  bool operator()(const char* s1, const char* s2) const
  {
    char n1, n2;
    while (n1 = *s1, n2 = *s2, n1 || n2) {
      if (n1 && !isalnum(n1)) {
	++s1;
	continue;
      }
      if (n2 && !isalnum(n2)) {
	++s2;
	continue;
      }
      if (tolower(n1) != tolower(n2))
	break;
      ++s1;
      ++s2;
    }
    return (n1 == '\0') && (n2 == '\0');
  }
};

struct NormHash
{
  size_t operator()(char const* str) const {
    std::string s = str;
    to_lower(s);
    return hash<char const *>()(s.c_str());
  }
};

class NormWordSet : public WordSetBase<NormHash, NormEqual>
{
public:
  NormWordSet() { }
  NormWordSet(char const* file) : WordSetBase<NormHash, NormEqual>(file) { }
  NormWordSet(std::string& file) : WordSetBase<NormHash, NormEqual>(file) { }

  /**
   *	Turn words to lowercase.
   */
  std::pair<_Base::iterator, bool> insert(const char* word) {
    char* lower = (char*)malloc(strlen(word)+1);
    to_lower(lower, word);
    _Base::iterator fit = this->find(lower);
    return (fit != this->end()) ?
      std::pair<_Base::iterator, bool>(fit, false) :
      WordSetBase<NormHash, NormEqual>::insert(lower);
  }

  /**
   *	Test for the presence of word @a word in the set.
   */
  bool	contains(char const* word) {
    return this->find(word) != this->end();
  }

  /**
   *	Test for the presence of word @a word in the set.
   */
  bool	contains(std::string const& word) {
    return this->find(word.c_str()) != this->end();
  }

};

} // Text
} // Tanl

// Mechanism to keep .cpp file separate
#ifndef NON_TEMPLATE
# include "WordSet.cpp"
#endif

#endif // Tanl_Text_WordSet_H
