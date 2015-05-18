/*
**  Tanl
**  classifier/GIS.h
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

#ifndef Tanl_classifier_GIS_H
#define Tanl_classifier_GIS_H

#include "MaxEnt.h"

namespace Tanl {
namespace Classifier {

  typedef std::vector<std::vector<std::pair<ClassID, double> > > Expected;

  /**
   *	Generalized Iterative Scaling algorithm to find the parameters
   *	{lambda1, ..., lambdak} of the unique distribution
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
   *
   * This version of GIS uses an Exponential prior to mitigate
   * overfitting, and avoids the use of a slack variable
   * (@see: http://www.research.microsoft.com/~joshuago/longexponentialprior.ps).
   *
   * An alternative would be the "Correction Free" GIS algorithm using
   * Gaussian prior smoothing described in [Curran and Clark, 2003]:
   * "Investigating GIS and Smoothing for Maximum Entropy Taggers"
   * (@see http://acl.ldc.upenn.edu/eacl2003/papers/main/p11.pdf).
   *
   */

class GIS : public MaxEnt
{
public:
  /**
   *	Create and train a model from events from a single EventStream.
   *
   *	@param iterations the number of iterations to perform.
   *	@param cutoff discard features occurring less than this value.
   *	@param alpha defines the exponential prior of the lambda values
   *	in MaxEnt models.
   */
  GIS(EventStream& es, int iterations, int cutoff = 0, double alpha = 0.0);

  /**
   *	The EventStream is supplied separately with method read().
   *	This is useful to supply several streams in turn (for instance
   *	data from several files).
   *
   *	@param iterations the number of iterations to perform.
   *	@param cutoff discard features occurring less than this value.
   *	@param alpha defines the exponential prior of the lambda values
   *	in MaxEnt models
   *	(@see: http://research.microsoft.com/en-us/um/people/joshuago/longexponentialprior.pdf).
   */
  GIS(int iterations = 50, int cutoff = 0, double alpha = 0.0);

  /**
   *	Train a model on events read with previous calls to read()
   */
  void	train();

  /**
   *	Train a model on events read from @param es.
   */
  void	train(EventStream& es);

private:
  double	update(Expected& expected, double prob[], int& correct);

  double		alpha;	///< used as exponential prior
  double		cfObservedExpect;

  /** stop running GIS if the log likelihood is smaller than this. */
  static const double LLThreshold; ///< = 0.001;

  static const double NEAR_ZERO; // = 0.01;

};

} // namespace Classifier
} // namespace Tanl

#endif // Tanl_classifier_GIS_H
