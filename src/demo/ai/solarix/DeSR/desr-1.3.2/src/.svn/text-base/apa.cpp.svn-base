/*
**  DeSR
**  src/apa.cpp
**  Averaged Passive-Aggressive multiclass single-label classifier.
**  ----------------------------------------------------------------------
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

#include "apa.h"

// standard
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

bool	APA::verbose = false;
float	APA::updatePercent = 0.5;

Float	APA::C = 100.0;
int	APA::kd = 1;
Float	APA::ka = 0.0;

///////////////////////////////////////////////////////////////////////
// APA INITIALIZATION:

APAS::APAS(int k, int d) :
  APA(k, d)
{
  M.rehash(k * d / 8);
}

APASV::APASV(int k, int d) :
  APA(k, d),
  M(k)
{ }

void APASV::init(int k, int d)
{
  this->k = k;
  this->d = d;
  M.resize(k);
}

///////////////////////////////////////////////////////////////////////
// APA TRAIN:

/**
 * similarity score.
 * score(r, v) = <M_r, v>; r = M row, v = vector
 */
Float APAS::score(unsigned r, X& v) {
  Float ans = 0;
  for (unsigned i = 0; i < v.size(); ++i) {
    pair<unsigned, unsigned> p(r, v[i]);
    Matrix::const_iterator m_i = M.find(p);
    if (m_i != M.end())
      ans += m_i->second.alpha;
  }
  return ka + pow(ans, kd);
}

Float APASV::score(unsigned r, X& v) {
  Float ans = 0;
  Row& Mr = M[r];
  for (unsigned i = 0; i < v.size(); ++i) {
    Row::const_iterator r_i = Mr.find(v[i]);
    if (r_i != Mr.end())
      ans += r_i->second.alpha;
  }
  return ka + pow(ans, kd);
}

// update
void APAS::update(Y y, Float tau, X& x) {
  for (unsigned i = 0; i < x.size(); ++i) {
    pair<unsigned, unsigned> p(y, x[i]);
    M[p].update(t, tau);
  }
}

void APASV::update(Y y, Float tau, X& x) {
  for (unsigned i = 0; i < x.size(); ++i) {
    unsigned xi = x[i];
    M[y][xi].update(t, tau);		// no * x since x is binary
  }
}

/**
 * Produces a permutation of the interval [0..N-1], stored in the vector @c OUT.
 * This is useful for randomizing the processing order of the training data.
 */
void APA::rand_permutation(vector<int>& OUT) {
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
void APA::train(Cases& cases, int T) {
  unsigned _S_ = cases.size();
  if (verbose)
    cerr << "APA::APA(" << k << ", " << d << ")"
	 << " cases = " << _S_ << endl;
  vector<int> perm(_S_);
  for (int it = 0; it < T; ++it) {
    rand_permutation(perm);
    int updates = 0;
    for (int i = 0; i < _S_; ++i) {
      ++t;			// advance epoch
      Case& c = cases[perm[i]];
      X& xt = c.first;
      Y yt = c.second;
      // Find the highest ranked irrelevant label s.
      // The lowest ranked relevant label r = yt (there is just one).
      int s = -1;
      Float score_r = score(yt, xt);
      Float score_s = score_r;
      for (int l = 0; l < k; ++l) {
	if (l != yt) {	// xi in Yt
	  Float xs = score(l, xt);
	  if (xs >= score_s) {
	    s = l;
	    score_s = xs;
	  }
	}
      }
      if (s < 0)
	continue;
      // update r and s rows
      Float loss = margin - (score_r - score_s); // margin == 1
      if (loss > 0.0) {
	updates++;
	int xtNormSq = xt.size();
	Float tau = min(C, loss / xtNormSq);
	update(yt, tau, xt);
	update(s, -tau, xt);
      }
    }
    float updPercent = (100.0 * updates) / _S_;
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
// APA PREDICT:

Y APA::predict(X& x) {
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

APASV::APASV(char const* modelFile)
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

void APAS::save(std::ostream& os)
{
  os.precision(20);
  for (unsigned i = 0; i < k; ++i) {
    os << i;
    for (unsigned j = 0; j < d; ++j) {
      Matrix::const_iterator mit = M.find(make_pair(i, j));
      if (mit != M.end())
	os << ' ' << j << ':' << mit->second.alpha;
    }
    os << endl;
  }
}

bool APAS::load(std::istream& is)
{
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

void APASV::save(std::ostream& os)
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
	float w = M[i][j].alpha; // single float
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
	float w = M[i][j].alpha; // single float
	if (w != 0.0) {
	  os.write((char const*)&j, sizeof(j));
	  os.write((char const*)&w, sizeof(w));
	}
      }
    }
  }
#endif
}

bool APASV::load(std::istream& is)
{
  int c;
  while (is.read((char*)&c, sizeof(c))) {
    int count;
    if (!is.read((char*)&count, sizeof(count))) {
      cerr << "bad file format: count" << endl;
      return false;
    }
    while (count--) {
      int i;
      if (!is.read((char*)&i, sizeof(i))) {
	cerr << "bad file format: i" << endl;
	return false;
      }
      float a;
      if (!is.read((char*)&a, sizeof(a))) {
	cerr << "bad file format: a" << endl;
	return false;
      }
      M[c][i].alpha = a;
    }
  }
  return true;
}
