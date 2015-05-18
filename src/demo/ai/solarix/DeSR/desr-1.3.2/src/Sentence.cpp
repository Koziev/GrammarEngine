/*
**  DeSR
**  src/Sentence.cpp
** ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
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

#include "Sentence.h"
#include "Corpus.h"

namespace Tanl {

Sentence::~Sentence()
{
  FOR_EACH (std::vector<TreeToken*>, *this, it)
    delete *it;
}

TreeToken* Sentence::child(TreeToken* tok, char dir, char POS)
{
  if (!tok)
    return 0;
  if (dir == '-') {
    // find closest left child with given POS
    FOR_EACH (std::vector<TreeToken*>, tok->left, it) {
      std::string const* attr = (*it)->get("POS");
      if (attr && (*attr)[0] == POS)
	return *it;
    }
    return 0;
  } else {
    // find closest right child with given POS
    FOR_EACH (std::vector<TreeToken*>, tok->right, it) {
      std::string const* attr = (*it)->get("POS");
      if (attr && (*attr)[0] == POS)
	return *it;
    }
    return 0;
  }
}

TreeToken* Sentence::child(TreeToken* tok, int nth)
{
  if (!tok)
    return 0;
  if (nth < 0) {
    if (nth == INT_MIN)
      return tok->left.size() ? tok->left[tok->left.size() - 1] : 0;
    nth = -nth;
    return (0 < nth && nth <= (int)tok->left.size()) ? tok->left[nth - 1] : 0;
  } else {
    if (nth == INT_MAX)
      return tok->right.size() ? tok->right[tok->right.size() - 1] : 0;
    else
      return  (0 < nth && nth <= (int)tok->right.size()) ? tok->right[nth - 1] : 0;
  }
}
  
TreeToken* Sentence::leftChild(TreeToken* tok)
{
  return (tok && tok->left.size()) ? tok->left[0] : 0;
}

TreeToken* Sentence::rightChild(TreeToken* tok)
{
  return (tok && tok->right.size()) ? tok->left[tok->left.size()-1] : 0;
}

void Sentence::reverse()
{
  int i = 0;
  int j = size() - 1;
  for (; i < j; i++, j--) {
    TreeToken* tmpi = operator[](i);
    tmpi->id = j + 1;
    int head = tmpi->linkHead();
    if (head)			// not ROOT
      tmpi->linkHead(size() - head + 1);
    TreeToken* tmpj = operator[](j);
    tmpj->id = i + 1;
    head = tmpj->linkHead();
    if (head)
      tmpj->linkHead(size() - head + 1);
    operator[](i) = tmpj;
    operator[](j) = tmpi;
  }
  if (i == j) {
    TreeToken* tmpi = operator[](i);
    int head = tmpi->linkHead();
    if (head)
      tmpi->linkHead(size() - head + 1);
  }
}

bool Sentence::crossing(TreeToken* begin, TreeToken* end)
{
  int firstID = begin->id;
  int lastID = end->id;
  for (int i = firstID; i < lastID-1; i++) {
    TreeToken* tok = (*this)[i];
    int head = tok->linkHead();
    if (head < firstID || lastID < head)
      return true;
    FOR_EACH (std::vector<TreeToken*>, tok->left, chit) {
      int id = (*chit)->id;
      if (id < firstID || lastID < id)
	return true;
    }
    FOR_EACH (std::vector<TreeToken*>, tok->right, chit) {
      int id = (*chit)->id;
      if (id < firstID || lastID < id)
	return true;
    }
  }
  return false;
}

std::ostream& Sentence::print(std::ostream& os, Corpus const& corpus) {
  corpus.print(os, *this);
  //  os << std::endl;
  return os;
}

std::ostream& operator <<(std::ostream& os, Sentence const& sent)
{
  FOR_EACH (Sentence, sent, tit) {
    (*tit)->printTab(os);
    os << std::endl;
  }
  return os;
}

} // namespace Tanl
