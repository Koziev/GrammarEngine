/*
**  DeSR
**  src/ap.cpp
**  Average Perceptron Sparse/Dense.
**  ----------------------------------------------------------------------
**  Copyright (c) 2002-2006   Massimiliano Ciaramita (massi@yahoo-inc.com)
**  Copyright (c) 2006	      Giuseppe Attardi (attardi@di.unipi.it).
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

#include "ap.h"

// standard
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

#define BINARY

bool	AP::verbose = false;
int	AP::partitionSize = 500000;
float	AP::updatePercent = 0.1F;

///////////////////////////////////////////////////////////////////////
// AP INITIALIZATION:

APS::APS(int k, int d) :
  AP(k, d)
{
  M.rehash(k * d / 3);
}

APSV::APSV(int k, int d) :
  AP(k, d),
  M(k)
{ }

APD::APD(int k, int d) :
  AP(k, d),
  M(k)
{
  for (int i = 0; i < k; i++)
    M[i].resize(d);
}

///////////////////////////////////////////////////////////////////////
// AP TRAIN:

/**
 * similarity score.
 * score(r, v) = <M_r, v>; r = M row, v = vector
 */
Float APS::score(unsigned r, X& v) {
  Float ans = 0;
  for (unsigned i = 0; i < v.size(); ++i) {
    pair<unsigned, unsigned> p(r, v[i]);
    Matrix::const_iterator m_i = M.find(p);
    if (m_i != M.end())
      ans += m_i->second.alpha;
  }
  return ans;
}

Float APSV::score(unsigned r, X& v) {
  Float ans = 0;
  Row& Mr = M[r];
  for (unsigned i = 0; i < v.size(); ++i) {
    Row::const_iterator r_i = Mr.find(v[i]);
    if (r_i != Mr.end())
      ans += r_i->second.alpha;
  }
  return ans;
}

Float APD::score(unsigned r, X& v) {
  vector<Fs>& m = M[r];
  Float ans = 0;
  for (unsigned i = 0; i < v.size(); ++i)
    ans += m[v[i]].alpha;
  return ans;
}

// update
void APS::update(X& x, unsigned yt, vector<unsigned>& E) {
  unsigned _E_ = E.size();
  Float tau = -1.0 / Float(_E_);
  for (unsigned i = 0; i < x.size(); ++i) {
    pair<unsigned, unsigned> p(yt, x[i]);
    M[p].update(t, 1.0);
    for (unsigned j = 0; j < _E_; ++j) {
      p = make_pair(E[j], x[i]);
      M[p].update(t, tau);
    }
  }
}

void APSV::update(X& x, unsigned yt, vector<unsigned>& E) {
  unsigned _E_ = E.size();
  Float tau = -1.0 / Float(_E_);
  for (unsigned i = 0; i < x.size(); ++i) {
    unsigned xi = x[i];
    M[yt][xi].update(t, 1.0);
    for (unsigned j = 0; j < _E_; ++j) {
      M[E[j]][xi].update(t, tau);
    }
  }
}

void APD::update(X& x, unsigned yt, vector<unsigned>& E) {
  unsigned _E_ = E.size();
  Float tau = -1.0 / Float(_E_);
  for (unsigned i = 0; i < x.size(); ++i) {
    M[yt][x[i]].update(t, 1.0);
    for (unsigned j = 0; j < _E_; ++j)
      M[E[j]][x[i]].update(t, tau);
  }
}

/**
 *	train(<xi, yi>) train the current model on <xi, yi>
 *	@return true if an update was performed.
 */
int AP::train(Case& cas) {
  ++t;				// increment epoch
  X& x = cas.first;
  Y y = cas.second;
  vector<unsigned> E; // { r != y | Mr x >= My x }
  Float score_y = score(y, x);
  for (unsigned r = 0; r < k; ++r) {
    if (r != y) {
      Float scor = score(r, x);
      if (scor >= score_y)
	E.push_back(r);
    }
  }
  if (E.size()) {
    update(x, y, E);
    return E.size();
  }
  return 0;
}


/**
 * Produces a permutation of the interval [0..N-1], stored in the vector @c v.
 * This is useful for randomizing the processing order of the training data.
 * @see http://www.techuser.net/randpermgen.html
 */
// FIXME: share this with MlpParser.cpp
static void rand_permutation(vector<int>& v) {
  size_t N = v.size();
  for (size_t i = 0; i < N; i++)
    v[i] = i;			// initialize to a sequence
  for (size_t i = 0; i < N-1; i++) {
    int r = i + rand() % (N-i); // no need to use high-order bits
    std::swap(v[i], v[r]);
  }
}

#define ONE_PERM
// train(S, T) train M on S, T times
#ifdef ONE_PERM
void AP::train(Cases& cases, int T) {
  unsigned _S_ = cases.size();
  if (verbose)
    cerr << "AP::AP(" << k << ", " << d << ")"
	 << " cases: " << _S_ << endl;
  vector<int> perm(_S_);
  for (int it = 0; it < T; ++it) {
    rand_permutation(perm);
    int updates = 0;
    int errors = 0;
    for (unsigned i = 0; i < _S_; ++i) {
      int delta = train(cases[perm[i]]);
      errors += delta;
      updates += delta > 0;
    }
    float updPercent = (100.0 * updates) / _S_;
    if (verbose)
      cerr << "\tupds_" << it << " = " << updates
	   << " (" << updPercent << "%), errors = " << errors << endl;
    if (updates == 0 || updPercent < updatePercent)
      break;
  }
}
#else
void AP::train(Cases& cases, int T) {
  unsigned _S_ = cases.size();
  if (partitionSize <= 0)
    partitionSize = _S_ + 1;
  int parts = (_S_ + partitionSize - 1) / partitionSize;
  if (verbose)
    cerr << "AP::train() |S| = " << _S_ << " partitions = " << parts << endl;
  int lastPartitionSize = _S_ % partitionSize;
  vector<int> partIndex(parts);
  vector<int> partition(partitionSize);
  vector<int> lastPartition(lastPartitionSize);
  for (int t = 0; t < T; ++t) {
    if (parts == 1)
      partIndex[0] = 0;		// to get an identical random partition series
    else
      rand_permutation(partIndex);
    int updates = 0;
    for (int p = 0; p < parts; p++) {
      int part = partIndex[p];	// select partition
      int partBase = part * partitionSize;
      if (part + 1 == parts) {
	// handle last partition separately
	rand_permutation(lastPartition);
	for (int i = 0; i < lastPartitionSize; ++i)
	  updates += train(cases[partBase + lastPartition[i]]);
      } else {
	rand_permutation(partition);
	for (int i = 0; i < partitionSize; ++i)
	  updates += train(cases[partBase + partition[i]]);
      }
    }
    float updPercent = 100.0 * updates / _S_;
    if (verbose)
      cerr << "\tupds_" << t << " = " << updates
	   << " (" << updPercent << "%)" << endl;
    if (updates == 0 || updPercent < updatePercent)
      break;
  }
}
#endif

///////////////////////////////////////////////////////////////////////
// AP PREDICT:

Y AP::predict(X& x)
{
  Y best_k = 0;
  Float best_score = score(0, x);

  for (unsigned r = 1; r < k; r++) {
    Float score_r = score(r, x);
    if (score_r > best_score) {
      best_score = score_r;
      best_k = r;
    }
  }
  return best_k;
}

vector<Float> AP::scores(X& x)
{
  vector<Float> S;
  for (unsigned r = 0; r < k; r++)
    S.push_back(score(r, x));
  return S;
}

///////////////////////////////////////////////////////////////////////
// SAVE/LOAD

#define MAX_LINE_LEN 8196

bool AP::load(istream& ifs)
{
  char line[MAX_LINE_LEN];
  if (!ifs.getline(line, MAX_LINE_LEN)) {
    cerr << "Bad model file" << endl;
    return false;
  }
  // read labels
  int nl = atoi(line);		// number of labels
  while (nl-- && ifs.getline(line, MAX_LINE_LEN)) {
    labels.push_back(line);
  }
  // read predicates
  if (!ifs.getline(line, MAX_LINE_LEN)) {
    cerr << "Bad model file" << endl;
    return false;
  }
  int np = atoi(line);		// number of predicates
# ifdef AFFINE
  int n = 1; np++;
# else
  int n = 0;
# endif
  while (n < np && ifs.getline(line, MAX_LINE_LEN))
    predIndex[(char const*)line] = n++;
  return true;
}

bool APS::load(istream& is)
{
  if (!AP::load(is))
    return false;
  k = labels.size();
  d = predIndex.size();
  string line;
  while (getline(is, line)) {
    char* cline = (char *)line.c_str();
    int c = strtol(cline, &cline, 10);
    int i;
    float a;
    while (cline && sscanf(cline, " %d:%f", &i, &a)) {
      M[make_pair((unsigned)c, (unsigned)i)].alpha = a;
      cline = strchr(cline + 1, ' ');
    }
  }
  return true;
}

void APS::save(ostream& os)
{
  os.precision(20);
  for (unsigned i = 0; i < k; ++i) {
    os << i;
    for (unsigned j = 0; j < d; ++j) {
      Matrix::const_iterator mit = M.find(make_pair(i, j));
      if (mit != M.end())
	os << ' ' << j << ':' << mit->second.weight(t);
    }
    os << endl;
  }
}

bool APSV::load(istream& is)
{
  if (!AP::load(is))
    return false;
  k = labels.size();
  d = predIndex.size();
  M.resize(k);
#ifdef BINARY
  int c;
  while (is.read((char*)&c, sizeof(c))) {
    if (c == -1)		// terminating -1
      break;
    int count;
    if (!is.read((char*)&count, sizeof(count))) {
      cerr << "bad file format: count" << endl;
      return false;
    }
    int i;
    float a;
    while (count--) {
      if (!is.read((char*)&i, sizeof(i))) {
	cerr << "bad file format: i" << endl;
	return false;
      }
      if (!is.read((char*)&a, sizeof(a))) {
	cerr << "bad file format: a" << endl;
	return false;
      }
      M[c][i].alpha = a;
    }
  }
  return true;
#else
  string line;
  while (getline(is, line)) {
    char* cline = (char *)line.c_str();
    int c = strtol(cline, &cline, 10);
    int i;
    float a;
    while (cline && sscanf(cline, " %d:%f", &i, &a)) {
      M[c][i].alpha = a;
      cline = strchr(cline + 1, ' ');
    }
  }
  return true;
#endif
}

void APSV::save(ostream& os)
{
#ifdef BINARY
  for (unsigned i = 0; i < k; ++i) {
    // count non-zero items
    int count = 0;
    for (Row::const_iterator it = M[i]. begin(); it != M[i].end(); ++it) {
      float w = it->second.weight(t); // single float
      if (w != 0.0)
	count++;
    }
    if (count == 0)
      continue;
    os.write((char const*)&i, sizeof(i));
    os.write((char const*)&count, sizeof(count));
    for (unsigned j = 0; j < d; ++j) {
      if (M[i].find(j) != M[i].end()) {
	float w = M[i][j].weight(t); // single float
	if (w != 0.0) {
	  os.write((char const*)&j, sizeof(j));
	  os.write((char const*)&w, sizeof(w));
	}
      }
    }
  }
  // write terminating -1
  int z = -1;
  os.write((char const*)&z, sizeof(z));
#else
  os.precision(20);
  for (unsigned i = 0; i < k; ++i) {
    for (unsigned j = 0; j < d; ++j) {
      if (j % 100 == 0) {	// break long lines
	if (j)
	  os << endl;
	os << i;
      }
      if (M[i].find(j) != M[i].end()) {
	Float w = M[i][j].weight(t);
	if (w != 0.0)
	  os << ' ' << j << ':' << w;
      }
    }
    os << endl;
  }
#endif
}

bool APD::load(istream& is)
{
  if (!AP::load(is))
    return false;
  string line;
  while (getline(is, line)) {
    char* cline = (char *)line.c_str();
    int c = strtol(cline, &cline, 10);
    int i;
    float a;
    while (cline && sscanf(cline, " %d:%f", &i, &a)) {
      M[c][i].alpha = a;
      cline = strchr(cline + 1, ' ');
    }
  }
  return true;
}

void APD::save(ostream& os)
{
  os.precision(20);
  for (unsigned i = 0; i < k; ++i) {
    os << i;
    for (unsigned j = 0; j < d; ++j) {
      Float w = M[i][j].weight(t);
      if (w != 0.0)
	os << ' ' << j << ':' << w;
    }
    os << endl;
  }
}
