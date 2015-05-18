/*
**  DeSR
**  src/apa.h
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

#ifndef DeSR_APA_H
#define DeSR_APA_H

#include <iostream>
#include <vector>

// library
#include "text/WordIndex.h"

///////////////////////////////////////////
typedef double Float;
typedef unsigned FeatureID;
typedef unsigned Y;		      // labels
typedef std::vector<FeatureID> X;     // vector of binary features
typedef std::pair<X, Y> Case;         // (x_i, y_i)
typedef std::vector<Case> Cases;      // (x, y)^N, N = size of training data
///////////////////////////////////////////

/**
 *      Use compact encoding for representing sparse matrix M[i, j]
 *	@see http://www.cris.com/~Ttwang/tech/inthash.htm
 */
BEGIN_NAMESPACE_HASH
  template<> struct hash<std::pair<unsigned, unsigned> > {
    size_t operator()(const std::pair<unsigned, unsigned>& x) const {
      unsigned a = x.first + ~(x.first << 13);
      unsigned b = x.second + ~(x.second << 9);
      a += (b >> 13);
      return a ^ b;
    }
  };
END_NAMESPACE_HASH

class Fs {
 public:
  Float alpha;			///< Weight associated with F
  Float avg_num;		///< Numerator of the average F-value
  int	lst_upd;		///< Iteration number of last update

  /**
   * @return average alpha
   */
  inline Float weight(int it) const {
#ifdef AVG
    return (avg_num + alpha * (it - lst_upd)) / it;
#else
    return alpha;
#endif
  }

  inline void update(int it, Float upd_val) {
    avg_num += alpha * (it - lst_upd);
    lst_upd = it;
    alpha += upd_val;
  }

  Fs(): alpha(0), avg_num(0), lst_upd(0) {}
};

/**
 *	Averaged Passive-Aggressive Classifier.
 *	@see http://jmlr.csail.mit.edu/papers/volume7/crammer06a/crammer06a.pdf
 *	K. Crammer, O. Dekel, J. Keshet, S. Shalev-Shwartz.
 *	Online Passive-Aggressive Algorithms.
 *	Journ. of Machine Learning Research 7, 2006, 551-585.
 */
class APA {
 public:
  unsigned k;			///< k = |Y|
  unsigned d;			///< d = |X|
  int t;			///< t = current number of iterations

  std::vector<std::string>	labels;
  Tanl::Text::WordIndex		predIndex;

  void	train(Cases& cases, int T);

  Y	predict(X& x);

  /** @return number of features */
  size_t virtual size() { }

  /** Dump parameters to stream */
  virtual void	save(std::ostream& os) = 0;

  static Float	C;			///< aggressiveness
  static Float	ka;			///< kernel a<
  static int	kd;			///< kernel degree

  /** Margin */
  Float		margin;

  /** Control output */
  static bool	verbose;
  static float	updatePercent;

protected:
  static void	rand_permutation(std::vector<int>& OUT);

  /***	Compute w[y] += tau * x   */
  virtual void update(Y y, Float tau, X& x) = 0;

  /** Similarity score */
  virtual Float score(unsigned i, X& v) = 0;

  APA(int k = 0, int d = 0) : k(k), d(d), t(0) { }

  /** Load parameters from stream
   * @return true if successful
   */
  virtual bool load(std::istream& is) = 0;

};

typedef unordered_map<std::pair<unsigned, unsigned>, Fs> Matrix;

typedef unordered_map<unsigned, Fs> Row;

/**
 * Sparse Averaged Passive-Aggressive
 */
class APAS : public APA {
 public:
  APAS(int _Y_, int _X_);
  void		update(Y y, Float tau, X& x);

  /** Dump parameters to stream */
  void		save(std::ostream& os);

  /** Load parameters from stream
   * @return true if successful
   */
  bool		load(std::istream& is);

  size_t	size() { return M.size(); }

private:
  void		init(int _Y_, int _X_);

  /** Similarity score */
  Float		score(unsigned i, X& v);

  Matrix	M; // Sparse Matrix <Y, X> 
};

/**
 * Sparse Vector Averaged Passive-Aggressive
 */
class APASV : public APA {
 public:
  APASV() { }

  APASV(int _Y_, int _X_);
  void	update(Y y, Float tau, X& x);

  /** Load model from file */
  APASV(char const* file);

  /** Dump parameters to stream */
  void	save(std::ostream& os);

  /** Load parameters from stream
   * @return true if successful
   */
  bool	load(std::istream& is);

  size_t size() {
    size_t tot = 0;
    for (int i = 0; i < M.size(); i++)
      tot += M[i].size();
    return tot;
  }

 private:
  /** Similarity score */
  Float	score(unsigned i, X& v);

  void	init(int k, int d);

  std::vector<Row>	M;
};

#endif // DeSR_APA_H
