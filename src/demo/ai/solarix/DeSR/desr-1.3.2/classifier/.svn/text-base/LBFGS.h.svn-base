/*
**  Tanl
**  classifier/LBFGS.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of Tanl.
**
**  Tanl is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  Tanl is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#ifndef Tanl_Classifier_LBFGS_H
#define Tanl_Classifier_LBFGS_H

#include <float.h>		// DBL_EPSILON

#include "MaxEnt.h"

namespace Tanl {
namespace Classifier {

  /**
   *	L-BFGS algorithm to find the parameters
   *	{alpha1, ..., alphak} of the unique distribution
   *	
   *	   p* = argmax H(p)
   *	             p in P
   *	
   *	where
   *	
   *	P = { p | Epfj = Ep~fj, j = {1, .. , k}}
   *	
   *	S = {(a1, b1), ... , (aN, bN)}, ai in A, bj in B (the trainig set)
   *	
   *	p(x)the model p's probability of x
   *	
   *	p~(x)observerd probability of x in S
   *	
   *	Epfj = SUM p(x) fj(x)
   *	      x in AxB
   *	
   *	Ep~fj = SUM p~(x) fj(x)
   *	      x in AxB
   */
  typedef std::vector<std::vector<std::pair<ClassID, int> > > ContribTable;

  struct  Options {
    int     n;			///< number of parameters
    int     m;			///< number of corrections
    int     niter;		///< number of iterations so far
    int     nfuns;		///< number of function evaluations so far
    int     iflag;
    int     iprint[2]; ///< see the comment in lbfgs.f for usage of this field
    double  eps;		///< tolerance
    double  xtol;
    int	    diagco;
    double* diag;
    double* w;

    Options(int n, double eps) :
      n(0),
      m(5),			// 3 <= m <= 7, see LBFGS_FUN()
      niter(0),
      nfuns(0),
      iflag(0),
      eps(eps),
      xtol(DBL_EPSILON),
      diagco(0),
      diag(0),
      w(0)
    {
      iprint[0] = -1;	  // by default print nothing
      iprint[1] = 0;
    }

    ~Options() {
      delete[] w;
      delete[] diag;
    }
  };

class LBFGS : public MaxEnt
{
public:
  /**
   *	Create and train a model from events from a single EventStream.
   *
   * @param es the EventStream from which to read training events
   * @param iterations max number of iterations to perform
   * @param cutoff discard predicates that do not occur at least this many times in the training set
   * @param eps determines the terminating accuracy
   */
  LBFGS(EventStream& es, int iterations, int cutoff = 0, double eps = 1E-05);

  /**
   *	The EventStream is supplied separately with method read().
   *	This is useful to supply several streams in turn (for instance
   *	data from several files).
   *
   * @param iterations max number of iterations to perform
   * @param cutoff discard predicates that do not occur at least this many times in the training set
   * @param eps determines the terminating accuracy
   */
  LBFGS(int iterations = 50, int cutoff = 0, double eps = 1E-05);

  ~LBFGS() {
    delete[] lambda;
  }

  /**
   *	Train a model on events read with previous calls to read()
   */
  void	train();

  /**
   *	Train a model on events read from @param es.
   */
  void	train(EventStream& es);

  void	save(char const* path);

  void	writeHeader(std::ofstream& ofs);
  void	writeData(std::ofstream& ofs);

protected:

  double*	lambda;	// overrides definition in MaxEnt

private:
  ClassID	estimate(const std::vector<PID>& preds, double probs[]);

  int			numEvents; ///< # of total events

  Options		opt;	///< parameters to LBFGS routine
  ContribTable	contribTable; ///< maps pred to the classes it contributes

};

} // namespace Classifier
} // namespace Tanl

#endif // Tanl_Classifier_LBFGS_H
