/*
**  DeSR
**  MaxEntropy/model/lbfgsAlg.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
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

/** <p> This class contains code for the limited-memory Broyden-Fletcher-Goldfarb-Shanno
  * (LBFGS) algorithm for large-scale multidimensional unconstrained minimization problems.
  * This file is a translation of Fortran code written by Jorge Nocedal.
  *
  * <p> This code is derived from the Fortran program <code>lbfgs.f</code>.
  * The C++ translation was effected mostly mechanically, with some
  * manual clean-up; in particular, array indices start at 0 instead of 1.
  * Most of the comments from the Fortran code have been pasted in here
  * as well.</p>
  *
  * <p> Here's some information on the original LBFGS Fortran source code,
  * available at <a href="http://www.netlib.org/opt/lbfgs_um.shar">
  * http://www.netlib.org/opt/lbfgs_um.shar</a>. This info is taken
  * verbatim from the Netlib blurb on the Fortran source.</p>
  *
  * <pre>
  * 	file    opt/lbfgs_um.shar
  * 	for     unconstrained optimization problems
  * 	alg     limited memory BFGS method
  * 	by      J. Nocedal
  * 	contact nocedal@eecs.nwu.edu
  * 	ref     D. C. Liu and J. Nocedal, ``On the limited memory BFGS method for
  * 	,       large scale optimization methods'' Mathematical Programming 45
  * 	,       (1989), pp. 503-528.
  * 	,       (Postscript file of this paper is available via anonymous ftp
  * 	,       to eecs.nwu.edu in the directory pub/lbfgs/lbfgs_um.)
  * </pre>
  *
  * @author Jorge Nocedal: original Fortran version, including comments
  * (July 1990). Robert Dodier: Java translation, August 1997.
  */

#ifndef DeSR_lbfgsAlg_H
#define DeSR_lbfgsAlg_H

namespace LBFGS {

/** Controls the accuracy of the line search <code>mcsrch</code>. If the
 * function and gradient evaluations are inexpensive with respect
 * to the cost of the iteration (which is sometimes the case when
 * solving very large problems) it may be advantageous to set <code>gtol</code>
 * to a small value. A typical small value is 0.1.  Restriction:
 * <code>gtol</code> should be greater than 1e-4.
 */

static double gtol = 0.9;

 /** Specify lower bound for the step in the line search.
  * The default value is 1e-20. This value need not be modified unless
  * the exponent is too large for the machine being used, or unless
  * the problem is extremely badly scaled (in which case the exponent
  * should be increased).
  */

static double stpmin = 1e-20;

 /** Specify upper bound for the step in the line search.
  * The default value is 1e20. This value need not be modified unless
  * the exponent is too large for the machine being used, or unless
  * the problem is extremely badly scaled (in which case the exponent
  * should be increased).
  */

static double stpmax = 1e20;
	
/** This subroutine solves the unconstrained minimization problem
 * <pre>
 *     min f(x),    x = (x1,x2,...,x_n),
 * </pre>
 * using the limited-memory BFGS method. The routine is especially
 * effective on problems involving a large number of variables. In
 * a typical iteration of this method an approximation <code>Hk</code> to the
 * inverse of the Hessian is obtained by applying <code>m</code> BFGS updates to
 * a diagonal matrix <code>Hk0</code>, using information from the previous M steps.
 * The user specifies the number <code>m</code>, which determines the amount of
 * storage required by the routine. The user may also provide the
 * diagonal matrices <code>Hk0</code> if not satisfied with the default choice.
 * The algorithm is described in "On the limited memory BFGS method
 * for large scale optimization", by D. Liu and J. Nocedal,
 * Mathematical Programming B 45 (1989) 503-528.
 *
 * The user is required to calculate the function value <code>f</code> and its
 * gradient <code>g</code>. In order to allow the user complete control over
 * these computations, reverse  communication is used. The routine
 * must be called repeatedly under the control of the parameter
 * <code>iflag</code>. 
 *
 * The steplength is determined at each iteration by means of the
 * line search routine <code>mcsrch</code>, which is a slight modification of
 * the routine <code>CSRCH</code> written by More' and Thuente.
 *
 * The only variables that are machine-dependent are <code>xtol</code>,
 * <code>stpmin</code> and <code>stpmax</code>.
 *
 *	Progress messages are printed to <code>cerr</code>, and
 * non-fatal error messages are printed to <code>cerr</code>.
 * Fatal errors return error codes, as listed below.
 *
 * @param n The number of variables in the minimization problem.
 *		Restriction: <code>n &gt; 0</code>.
 *
 * @param m The number of corrections used in the BFGS update. 
 *		Values of <code>m</code> less than 3 are not recommended;
 *		large values of <code>m</code> will result in excessive
 *		computing time. <code>3 &lt;= m &lt;= 7</code> is recommended.
 *		Restriction: <code>m &gt; 0</code>.
 *
 * @param x On initial entry this must be set by the user to the values
 *		of the initial estimate of the solution vector. On exit with
 *		<code>iflag = 0</code>, it contains the values of the variables
 *		at the best point found (usually a solution).
 *
 * @param f Before initial entry and on a re-entry with <code>iflag = 1</code>,
 *		it must be set by the user to contain the value of the function
 *		<code>f</code> at the point <code>x</code>.
 *
 * @param g Before initial entry and on a re-entry with <code>iflag = 1</code>,
 *		it must be set by the user to contain the components of the
 *		gradient <code>g</code> at the point <code>x</code>.
 *
 * @param diagco  Set this to <code>true</code> if the user  wishes to
 *		provide the diagonal matrix <code>Hk0</code> at each iteration.
 *		Otherwise it should be set to <code>false</code> in which case
 *		<code>lbfgs</code> will use a default value described below. If
 *		<code>diagco</code> is set to <code>true</code> the routine will
 *		return at each iteration of the algorithm with <code>iflag = 2</code>,
 *		and the diagonal matrix <code>Hk0</code> must be provided in
 *		the array <code>diag</code>.
 *
 * @param diag If <code>diagco = true</code>, then on initial entry or on
 *		re-entry with <code>iflag = 2</code>, <code>diag</code>
 *		must be set by the user to contain the values of the 
 *		diagonal matrix <code>Hk0</code>. Restriction: all elements of
 *		<code>diag</code> must be positive.
 *
 * @param iprint Specifies output generated by <code>lbfgs</code>.
 *		<code>iprint[0]</code> specifies the frequency of the output:
 *		<ul>
 *		<li> <code>iprint[0] &lt; 0</code>: no output is generated,
 *		<li> <code>iprint[0] = 0</code>: output only at first and last iteration,
 *		<li> <code>iprint[0] &gt; 0</code>: output every <code>iprint[0]</code> iterations.
 *		</ul>
 *
 *		<code>iprint[1]</code> specifies the type of output generated:
 *		<ul>
 *		<li> <code>iprint[1] = 0</code>: iteration count, number of function 
 *			evaluations, function value, norm of the gradient, and steplength,
 *		<li> <code>iprint[1] = 1</code>: same as <code>iprint[1]=0</code>, plus vector of
 *			variables and  gradient vector at the initial point,
 *		<li> <code>iprint[1] = 2</code>: same as <code>iprint[1]=1</code>, plus vector of
 *			variables,
 *		<li> <code>iprint[1] = 3</code>: same as <code>iprint[1]=2</code>, plus gradient vector.
 *		</ul>
 *
 *	@param eps Determines the accuracy with which the solution
 *		is to be found. The subroutine terminates when
 *		<pre>
 *            ||G|| &lt; EPS max(1,||X||),
 *		</pre>
 *		where <code>||.||</code> denotes the Euclidean norm.
 *
 *	@param xtol An estimate of the machine precision (e.g. 10e-16 on a
 *		SUN station 3/60). The line search routine will terminate if the
 *		relative width of the interval of uncertainty is less than
 *		<code>xtol</code>.
 *
 * @param iflag This must be set to 0 on initial entry to <code>lbfgs</code>.
 *		A return with <code>iflag &lt; 0</code> indicates an error,
 *		and <code>iflag = 0</code> indicates that the routine has
 *		terminated without detecting errors. On a return with
 *		<code>iflag = 1</code>, the user must evaluate the function
 *		<code>f</code> and gradient <code>g</code>. On a return with
 *		<code>iflag = 2</code>, the user must provide the diagonal matrix
 *		<code>Hk0</code>.
 *
 *		The following negative values of <code>iflag</code>, detecting an error,
 *		are possible:
 *		<ul>
 *		<li> <code>iflag = -1</code> The line search routine
 *			<code>mcsrch</code> failed. One of the following messages
 *			is printed:
 *			<ul>
 *			<li> Improper input parameters.
 *			<li> Relative width of the interval of uncertainty is at
 *				most <code>xtol</code>.
 *			<li> More than 20 function evaluations were required at the
 *				present iteration.
 *			<li> The step is too small.
 *			<li> The step is too large.
 *			<li> Rounding errors prevent further progress. There may not
 *				be  a step which satisfies the sufficient decrease and
 *				curvature conditions. Tolerances may be too small.
 *			</ul>
 *		<li><code>iflag = -2</code> The i-th diagonal element of the diagonal inverse
 *			Hessian approximation, given in DIAG, is not positive.
 *		<li><code>iflag = -3</code> Improper input parameters for LBFGS
 *			(<code>n</code> or <code>m</code> are not positive).
 *		</ul>
 *
 */

void minimize(int n, int m, double* x, double f, double* g,
	      bool diagco, double* diag, int* iprint, double eps,
	      double xtol, double* w, int& iflag, int& niter, int& nfun);

/** Minimize a function along a search direction. This code is
 * a C++ translation of the function <code>MCSRCH</code> from
 * <code>lbfgs.f</code>, which in turn is a slight modification of
 * the subroutine <code>CSRCH</code> of More' and Thuente.
 * This function, in turn, calls <code>mcstep</code>.<p>
 *
 * The C++ translation was effected mostly mechanically, with some
 * manual clean-up; in particular, array indices start at 0 instead of 1.
 * Most of the comments from the Fortran code have been pasted in here
 * as well.<p>
 *
 * The purpose of <code>mcsrch</code> is to find a step which satisfies
 * a sufficient decrease condition and a curvature condition.<p>
 *
 * At each stage this function updates an interval of uncertainty with
 * endpoints <code>stx</code> and <code>sty</code>. The interval of
 * uncertainty is initially chosen so that it contains a
 * minimizer of the modified function
 * <pre>
 *      f(x+stp*s) - f(x) - ftol*stp*(gradf(x)'s).
 * </pre>
 * If a step is obtained for which the modified function
 * has a nonpositive function value and nonnegative derivative,
 * then the interval of uncertainty is chosen so that it
 * contains a minimizer of <code>f(x+stp*s)</code>.<p>
 *
 * The algorithm is designed to find a step which satisfies
 * the sufficient decrease condition
 * <pre>
 *       f(x+stp*s) &lt;= f(X) + ftol*stp*(gradf(x)'s),
 * </pre>
 * and the curvature condition
 * <pre>
 *       abs(gradf(x+stp*s)'s)) &lt;= gtol*abs(gradf(x)'s).
 * </pre>
 * If <code>ftol</code> is less than <code>gtol</code> and if, for example,
 * the function is bounded below, then there is always a step which
 * satisfies both conditions. If no step can be found which satisfies both
 * conditions, then the algorithm usually stops when rounding
 * errors prevent further progress. In this case <code>stp</code> only
 * satisfies the sufficient decrease condition.<p>
 *
 * @author Original Fortran version by Jorge J. More' and David J. Thuente
 *	  as part of the Minpack project, June 1983, Argonne National 
 *   Laboratory. Java translation by Robert Dodier, August 1997.
 *   C++ translation by Giuseppe Attardi, August 2006.
 *
 * @param n The number of variables.
 *
 * @param x On entry this contains the base point for the line search.
 *		On exit it contains <code>x + stp*s</code>.
 *
 * @param f On entry this contains the value of the objective function
 *		at <code>x</code>. On exit it contains the value of the objective
 *		function at <code>x + stp*s</code>.
 *
 * @param g On entry this contains the gradient of the objective function
 *		at <code>x</code>. On exit it contains the gradient at
 *		<code>x + stp*s</code>.
 *
 *	@param s The search direction.
 *
 * @param stp On entry this contains an initial estimate of a satifactory
 *		step length. On exit <code>stp</code> contains the final estimate.
 *
 *	@param ftol Tolerance for the sufficient decrease condition.
 *
 * @param xtol Termination occurs when the relative width of the interval
 *		of uncertainty is at most <code>xtol</code>.
 *
 *	@param maxfev Termination occurs when the number of evaluations of
 *		the objective function is at least <code>maxfev</code> by the end
 *		of an iteration.
 *
 *	@param info This is an output variable, which can have these values:
 *		<ul>
 *		<li><code>info = 0</code> Improper input parameters.
 *		<li><code>info = -1</code> A return is made to compute the function and gradient.
 *		<li><code>info = 1</code> The sufficient decrease condition and
 *			the directional derivative condition hold.
 *		<li><code>info = 2</code> Relative width of the interval of uncertainty
 *			is at most <code>xtol</code>.
 *		<li><code>info = 3</code> Number of function evaluations has reached <code>maxfev</code>.
 *		<li><code>info = 4</code> The step is at the lower bound <code>stpmin</code>.
 *		<li><code>info = 5</code> The step is at the upper bound <code>stpmax</code>.
 *		<li><code>info = 6</code> Rounding errors prevent further progress.
 *			There may not be a step which satisfies the
 *			sufficient decrease and curvature conditions.
 *			Tolerances may be too small.
 *		</ul>
 *
 *	@param nfev On exit, this is set to the number of function evaluations.
 *
 *	@param wa Temporary storage array, of length <code>n</code>.
 */

void mcsrch(int n, double* x, double f, double* g, double* s,
	    double& stp, const double ftol, const double xtol,
	    const int maxfev, int& info, int& nfev, double* wa);

} // namespace LBFGS

#endif // DeSR_lbfgsAlg_H
