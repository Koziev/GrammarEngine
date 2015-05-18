/*
**  DeSR
**  src/pa.cpp
**  Passive-Aggressive multiclass single-label classifier.
**  ----------------------------------------------------------------------
**  Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
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

#include "pa.h"

#ifdef _WIN32
#include <string>
#endif

// standard
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

bool	PA::verbose = false;
float	PA::updatePercent = 0.5;

///////////////////////////////////////////////////////////////////////
// PA INITIALIZATION:

PAS::PAS(int k, int d) :
  PA(k, d)
{
  M.rehash(k * d / 3);
  if (verbose)
    cerr << "\nPAS::PAS(" << k << ',' << d << ")" << endl;
}

PASV::PASV(int k, int d) :
  PA(k, d),
  M(k)
{
  if (verbose)
    cerr << "\nPASV::PASV(" << k << ',' << d << ")" << endl;
}

void PASV::init(int k, int d)
{
  this->k = k;
  this->d = d;
  M.resize(k);
}

PAD::PAD(int k, int d) :
  PA(k, d),
  M(k)
{
  for (int i = 0; i < k; i++)
    M[i].resize(d);
  if (verbose)
    cerr << "\nPAD::PAD(" << k << "," << d << ")" << endl;
}

///////////////////////////////////////////////////////////////////////
// PA TRAIN:

/**
 * similarity score.
 * score(r, v) = <M_r, v>; r = M row, v = vector
 */
Float PAS::score(unsigned r, X& v) {
  Float ans = 0;
  for (unsigned i = 0; i < v.size(); ++i) {
    pair<unsigned, unsigned> p(r, v[i]);
    Matrix::const_iterator m_i = M.find(p);
    if (m_i != M.end())
      ans += m_i->second;
  }
  return ans;
}

Float PASV::score(unsigned r, X& v) {
  Float ans = 0;
  Row& Mr = M[r];
  for (unsigned i = 0; i < v.size(); ++i) {
    Row::const_iterator r_i = Mr.find(v[i]);
    if (r_i != Mr.end())
      ans += r_i->second;
  }
  return ans;
}

Float PAD::score(unsigned r, X& v) {
  vector<Float>& m = M[r];
  Float ans = 0;
  for (unsigned i = 0; i < v.size(); ++i)
    ans += m[v[i]];
  return ans;
}

// update
void PAS::update(Y y, Float tau, X& x) {
  for (unsigned i = 0; i < x.size(); ++i) {
    pair<unsigned, unsigned> p(y, x[i]);
    M[p] += tau;
  }
}

void PASV::update(Y y, Float tau, X& x) {
  for (unsigned i = 0; i < x.size(); ++i) {
    unsigned xi = x[i];
    M[y][xi] += tau;		// no * x since x is binary
  }
}

void PAD::update(Y y, Float tau, X& x) {
  for (unsigned i = 0; i < x.size(); ++i) {
    M[y][x[i]] += tau;
  }
}

/**
 * Produces a permutation of the interval [0..N-1], stored in the vector @c OUT.
 * This is useful for randomizing the processing order of the training data.
 */
void PA::rand_permutation(vector<int>& OUT) {
  size_t N = OUT.size();
  for (int i = 0; i < N; i++)
    OUT[i] = -1;
  for (int i = 0; i < N; ) {
    int s = int(float(N) * (rand() / (RAND_MAX + 1.0)));
    if (OUT[s] == -1)
      OUT[s] = i++;
  }
}

// train(S, T) train M on S, T times
void PA::train(Cases& cases, int T) {
  unsigned _S_ = cases.size();
  vector<int> perm(_S_);
  for (int t = 0; t < T; ++t) {
    rand_permutation(perm);
    int updates = 0;
    for (int i = 0; i < _S_; ++i) {
      Case& c = cases[perm[i]];
      X& xt = c.first;
      Y yt = c.second;
      // Find the highest ranked irrelevant label s.
      // The lowest ranked relevant label r = yt (there is just one).
      int s = -1;
      Float score_r = score(yt, xt);
      Float score_s = 0.0;
      for (int l = 0; l < k; ++l) {
	if (l != yt) {	// xi in Yt
	  Float xs = score(l, xt);
	  if (xs > score_r && xs > score_s) {
	    s = l;
	    score_s = xs;
	  }
	}
      }
      // update r and s rows
      Float loss = margin - (score_r - score_s);
      // special handling of most popular label (S).
      if (yt == 0)
	loss = 1.0 - (score_r - score_s);
      if (loss > 0.0) {
	updates++;
	int xtNormSq = xt.size();
	Float tau = loss / (2 * xtNormSq);
	update(yt, tau, xt);
	if (s >= 0)
	  update(s, -tau, xt);
      }
    }
    float updPercent = (100.0*updates) / _S_;
    if (verbose)
      cerr << "\tupds_" << t << " = " << updates
	   << " (" << updPercent << "%)" << endl;
    if (updates == 0 || updPercent < updatePercent)
      break;
#  ifdef DEBUG
    save(cerr, true);
#  endif
  }
}

///////////////////////////////////////////////////////////////////////
// PA PREDICT:

Y PA::predict(X& x) {
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

///////////////////////////////////////////////////////////////////////
// SAVE/LOAD

#define MAX_LINE_LEN 8196

PASV::PASV(char const* modelFile)
{
  ifstream ifs(modelFile);
  if (!ifs) {
    cerr << "Missing model file: " << modelFile << endl;
    return;
  }
  char line[MAX_LINE_LEN];
  if (!ifs.getline(line, MAX_LINE_LEN)) {
    cerr << "Bad model file" << endl;
    return;
  }
  // read labels
  int nc = atoi(line);		// number of labels
  int n = nc;
  while (n-- && ifs.getline(line, MAX_LINE_LEN)) {
    labels.push_back(line);
  }
  // read predicates
  if (!ifs.getline(line, MAX_LINE_LEN)) {
    cerr << "Bad model file" << endl;
    return;
  }
  int np = atoi(line);		// number of predicates
  n = 0;
  while (n < np && ifs.getline(line, MAX_LINE_LEN))
    predIndex[(char const*)line] = n++;
  init(nc, np);
  load(ifs);
}

void PAS::save(std::ostream& os)
{
  os.precision(20);
  for (unsigned i = 0; i < k; ++i) {
    os << i;
    for (unsigned j = 0; j < d; ++j) {
      Matrix::const_iterator mit = M.find(make_pair(i, j));
      if (mit != M.end())
	os << ' ' << j << ':' << mit->second;
    }
    os << endl;
  }
}

bool PAS::load(std::istream& is)
{
  string line;
  while (std::getline(is, line)) {
    char* cline = (char *)line.c_str();
    int c = strtol(cline, &cline, 10);
    int i;
    float a;
    while (cline && sscanf(cline, " %d:%f", &i, &a)) {
      M[make_pair((unsigned)c, (unsigned)i)] = a;
      cline = strchr(cline + 1, ' ');
    }
  }
  return true;
}

void PASV::save(std::ostream& os)
{
#ifdef TEXT
  os.precision(3);
  for (unsigned i = 0; i < k; ++i) {
    os << i;
    for (unsigned j = 0; j < d; ++j) {
      if (M[i].find(j) != M[i].end()) {
	float w = M[i][j]; // single float
	if (w != 0.0)
	  os << ' ' << j << ':' << w;
      }
    }
    os << endl;
  }
  return;
#else
  for (unsigned i = 0; i < k; ++i) {
    // count non-zero items
    int count = 0;
    for (unsigned j = 0; j < d; ++j) {
      if (M[i].find(j) != M[i].end()) {
	float w = M[i][j]; // single float
	if (w != 0.0)
	  count++;
      }
    }
    if (count == 0)
      continue;
    os.write((char const*)&i, sizeof(i));
    os.write((char const*)&count, sizeof(count));
    for (unsigned j = 0; j < d; ++j) {
      if (M[i].find(j) != M[i].end()) {
	float w = M[i][j]; // single float
	if (w != 0.0) {
	  os.write((char const*)&j, sizeof(j));
	  os.write((char const*)&w, sizeof(w));
	}
      }
    }
  }
#endif
}

bool PASV::load(std::istream& is)
{
  int c;
  while (is.read((char*)&c, sizeof(c))) {
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
      M[c][i] = a;
    }
  }
  return true;
}

void PAD::save(std::ostream& os)
{
  os.precision(20);
  for (unsigned i = 0; i < k; ++i) {
    os << i;
    for (unsigned j = 0; j < d; ++j) {
      Float w = M[i][j];
      if (w != 0.0)
	os << ' ' << j << ':' << w;
    }
    os << endl;
  }
}

bool PAD::load(std::istream& is)
{
  string line;
  while (getline(is, line)) {
    char* cline = (char *)line.c_str();
    int c = strtol(cline, &cline, 10);
    int i;
    float a;
    while (cline && sscanf(cline, " %d:%f", &i, &a)) {
      M[c][i] = a;
      cline = strchr(cline + 1, ' ');
    }
  }
  return true;
}

#ifdef MESCHACH

PASM::PASM(int k, int d) :
  PA(k, d)
{
  M = sp_get(k, d, 32);
  if (verbose)
    cerr << "\nPASM::PASM(" << k << ',' << d << ")" << endl;
}

void PASM::init(int k, int d)
{
  this->k = k;
  this->d = d;
  sp_resize(M, k, d);
}

Float PASM::score(unsigned r, X& v) {
  Float ans = 0;
  SPROW& Mr = M->row[r];
  for (unsigned i = 0; i < v.size(); ++i) {
    int idx = sprow_idx(Mr, v[i]);
    if (idx >= 0)
      ans += Mr->elt[idx].val;
  }
  return ans;
}

void PASM::update(Y y, Float tau, X& x) {
  for (unsigned i = 0; i < x.size(); ++i) {
    unsigned xi = x[i];
    M[y][xi] += tau;
  }
}
void PASM::save(std::ostream& os)
{
  for (unsigned i = 0; i < k; ++i) {
    // count non-zero items
    int count = 0;
    for (unsigned j = 0; j < d; ++j) {
      if (M[i].find(j) != M[i].end()) {
	float w = M[i][j].weight(t); // single float
	if (w != 0.0)
	  count++;
      }
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
}

bool PASM::load(std::istream& is)
{
  int c;
  while (is.read((char*)&c, sizeof(c))) {
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
      M[c][i] = a;
    }
  }
  return true;
}

#endif
