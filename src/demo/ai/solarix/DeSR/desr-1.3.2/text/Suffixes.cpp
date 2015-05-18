/*
**  Tanl C++ Library
**  text/Suffixes.h
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

#include "Suffixes.h"
#include <cassert>
#include <algorithm>

using namespace std;

namespace Tanl {
namespace Text {

#define MAX_LINE_LEN 4096

Suffixes::Suffixes(char const* file) {
  ifstream ifs(file);
  load(ifs);
}

Suffixes::Suffixes(string& file) {
  ifstream ifs(file.c_str());
  load(ifs);
}

void Suffixes::load(ifstream& ifs)
{
  char line[MAX_LINE_LEN];
  while (ifs.getline(line, MAX_LINE_LEN)) {
    char* sl = line;
    while (isspace(*sl))
      sl++;
    int len = strlen(sl);
    if (len == 0)		// skip empty or blank lines
      continue;
    char* rev = new char[len+1];
    char* back = sl + len - 1;
    char* s = rev;
    while (back >= sl)
      *s++ = *back--;
    *s = '\0';
    push_back(rev);
  }
  std::sort(begin(), end());
}
/**
 *	Check if @param word ends in one of the suffixes.
 *
 *	@param word	the word to check
 *	@return		pointer to the shortest suffix found, null otherwise.
 */
char const*
Suffixes::match(char const* word)
{
  // specialized version of ::lower_bound
  const_iterator first = begin();
  const_iterator last = end();
  const_iterator middle;
  int len = last - first;
  unsigned char mchar, vchar;
  register const char *smiddle, *suffix;

  char const* revword = word + ::strlen(word) - 1;

  while (len > 0) {
    int half = len / 2;
    middle = first + half;
    // find where middle differs from value
    smiddle = *middle;
    suffix = revword;
    assert (*smiddle);		// blank lines were skipped
    while (suffix >= word &&
	   (mchar = *smiddle) == (vchar = *suffix))
      if (*++smiddle == '\0')
	return suffix;
      else
	--suffix;
    if (mchar < vchar) {
      first = middle + 1;
      len = len - half - 1;
    }
    else
      len = half;
  }
  return 0;			// not found
}

void Suffixes::store(char const* file)
{
	ofstream ofs(file, ios::binary);

  for (const_iterator wit = begin(); wit != end(); wit++)
    ofs << *wit << endl;
}

} // namespace Text
} // namespace Tanl
