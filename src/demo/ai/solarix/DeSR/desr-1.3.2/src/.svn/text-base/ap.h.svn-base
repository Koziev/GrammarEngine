/*
**  DeSR
**  src/apa.h
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

#ifndef DeSR_AP_H
#define DeSR_AP_H

#include <vector>
#include <string>

// IXE
#include "text/WordIndex.h"
#include "include/unordered_map.h"

/**
 *	Define this to allow separating planes non passing through origin,
 *	by using affine transformation in homogeneous coordinates.
 */
#define AFFINE

///////////////////////////////////////////
typedef double Float;
typedef unsigned FeatureID;
typedef unsigned Y;		      // labels
typedef std::vector<FeatureID> X;     // vector of features
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
    return (avg_num + alpha * (it - lst_upd)) / it;
  }

  inline void update(int it, Float tau) {
    avg_num += alpha * (it - lst_upd);
    lst_upd = it;
    alpha += tau;
  }

  Fs(): alpha(0), avg_num(0), lst_upd(0) {}
};

/**
 *	Averaged Perceptron Classifier.
 *	@see http://jmlr.csail.mit.edu/papers/volume3/crammer03a/crammer03a.pdf
 *	K. Crammer, Y. Singer, Ultraconservative Online Algorithms for
 *	Multiclass Problems. Journ. of Machine Learning Research, 2003.
 */
class AP {
 public:
  unsigned k;			///< k = |Y|
  unsigned d;			///< d = |X|
  int t;			///< t = current number of iterations

  std::vector<std::string>	labels;
  Tanl::Text::WordIndex		predIndex;

  /**
   *  Train the perceptron with a set of @c cases, performing @c T iterations
   *  through them.
   */
  void	train(Cases& cases, int T);

  /** Train a single case */
  int	train(Case& cas);

  /** @return the highest scoring label */
  Y	predict(X& x);

  /** @return a vector with the scores for all labels */
  std::vector<Float>	scores(X& x);

  /** @return number of features */
  size_t virtual size() { return 0; }

  /** Termination threshold */
  static float	updatePercent;
  /** Control output */
  static bool	verbose;
  /** Split cases into partitions of this maximum size */
  static int	partitionSize;

protected:

  virtual void update(X& x, unsigned yt, std::vector<unsigned>& E) = 0;
  /** Similarity score */
  virtual Float score(unsigned i, X& v) = 0;

  AP(int k = 0, int d = 0) : k(k), d(d), t(0) { }

  /** Load parameters from stream
   * @return true if successful
   */
  virtual bool load(std::istream& is);
};

typedef unordered_map<std::pair<unsigned, unsigned>, Fs> Matrix;

typedef unordered_map<unsigned, Fs> Row;

/**
 * Sparse Average Perceptron
 */
class APS : public AP {
 public:
  APS(int _Y_, int _X_);

  /** Load model from stream */
  APS(std::istream& is) { load(is); }

  void		update(X& x, unsigned yt, std::vector<unsigned>& E);

  /** Dump parameters to stream */
  void		save(std::ostream& os);

  /** Load parameters from stream
   * @return true if successful
   */
  bool		load(std::istream& is);

  size_t	size() { return M.size(); }

private:
  /** Similarity score */
  Float		score(unsigned i, X& v);

  Matrix	M; // Sparse Matrix <Y, X> 
};

/**
 * Sparse Vector Average Perceptron
 */
class APSV : public AP
{
 public:
  APSV() { }

  APSV(int _Y_, int _X_);

  void	update(X& x, unsigned yt, std::vector<unsigned>& E);

  /** Load model from stream */
  APSV(std::istream& is) { load(is); }

  /** Dump parameters to stream */
  void	save(std::ostream& os);

  /** Load parameters from stream
   * @return true if successful
   */
  bool	load(std::istream& is);

  size_t size() {
    size_t tot = 0;
    for (unsigned i = 0; i < M.size(); i++)
      tot += M[i].size();
    return tot;
  }

 private:
  /** Similarity score */
  Float	score(unsigned i, X& v);

  std::vector<Row>	M;
};

/**
 * Dense Average Perceptron
 */
class APD : public AP {
 public:
  APD(int _Y_, int _X_);

  /** Load model from stream */
  APD(std::istream& is) { load(is); }

  void	update(X& _x, unsigned yt, std::vector<unsigned>& E);

  /** Dump parameters to stream */
  void	save(std::ostream& os);

  /** Load parameters from stream
   * @return true if successful
   */
  bool	load(std::istream& is);

 private:
  /** Similarity score */
  Float score(unsigned i, X& v);

  std::vector<std::vector<Fs> > M; // Full Matrix <Y, X> 
};

#endif // DeSR_AP_H
