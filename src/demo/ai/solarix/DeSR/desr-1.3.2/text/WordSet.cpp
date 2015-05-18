/*
**  IXE C++ Library
**  ixe/text/WordSet.cpp
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

#ifndef IXE_Text_WordSet_H
# define NON_TEMPLATE
# include "text/WordSet.h"
#endif

#ifndef NON_TEMPLATE

using namespace std;

namespace IXE {
namespace Text {

#define MAX_LINE_LEN 4096

template <class _Hash, class _Pred>
WordSetBase<_Hash, _Pred>::WordSetBase(char const* file) {
}

template <class _Hash, class _Pred>
WordSetBase<_Hash, _Pred>::WordSetBase(string& file) {
  load(file.c_str());
}

template <class _Hash, class _Pred>
void WordSetBase<_Hash, _Pred>::load(char const* file)
{
  ifstream ifs(file);
  load(ifs);
}

template <class _Hash, class _Pred>
void WordSetBase<_Hash, _Pred>::load(ifstream& ifs)
{
  char line[MAX_LINE_LEN];

  while (ifs.getline(line, MAX_LINE_LEN))
    insert((char const*)line);
}

template <class _Hash, class _Pred>
void WordSetBase<_Hash, _Pred>::store(char const* file)
{
  ofstream ofs(file);

  for (typename _Base::const_iterator wit = this->begin(); wit != this->end(); ++wit)
    ofs << *wit << endl;
}

} // namespace Text
} // namespace IXE

#endif // NO_TEMPLATE
