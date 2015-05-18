/*
**  DeSR
**  classifier/lbfgsAlg.cpp
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

#include "lbfgsAlg.h"

#include <algorithm>		// min, max
#include <cmath>		// fabs
#include <iostream>

using namespace std;

namespace LBFGS {

#define max3(x, y, z)	max(x, max(y, z))
#define sqr(x)	(x)*(x)

void mcstep(double& stx, double& fx, double& dx, double& sty,
	    double& fy, double& dy, double& stp, double fp, double dp,
	    bool& brackt, double stpmin, double stpmax, int& info)
{
  double p, q, r, s, gamma, theta, stpc, stpq, stpf;
  bool bound;
  info = 0;

  if ((brackt && (stp <= min(stx, sty) || stp >= max(stx, sty)))
      || dx * (stp - stx) >= 0.0 || stpmax < stpmin)
    return;

  // Determine if the derivatives have opposite sign.

  double sgnd = dp * (dx / fabs(dx));

  if (fp > fx) {
    // First case. A higher function value.
    // The minimum is bracketed. If the cubic step is closer
    // to stx than the quadratic step, the cubic step is taken,
    // else the average of the cubic and quadratic steps is taken.

    info = 1;
    bound = true;
    theta = 3 * (fx - fp) / (stp - stx) + dx + dp;
    s = max3(fabs(theta), fabs(dx), fabs(dp));
    gamma = s * sqrt(sqr(theta / s) - (dx / s) * (dp / s));
    if (stp < stx) gamma = - gamma;
    p = (gamma - dx) + theta;
    q = ((gamma - dx) + gamma) + dp;
    r = p/q;
    stpc = stx + r * (stp - stx);
    stpq = stx + ((dx / ((fx - fp) / (stp - stx) + dx)) / 2) * (stp - stx);
    if (fabs(stpc - stx) < fabs(stpq - stx))
      stpf = stpc;
    else
      stpf = stpc + (stpq - stpc) / 2;
    brackt = true;
  } else if (sgnd < 0.0) {
    // Second case. A lower function value and derivatives of
    // opposite sign. The minimum is bracketed. If the cubic
    // step is closer to stx than the quadratic (secant) step,
    // the cubic step is taken, else the quadratic step is taken.

    info = 2;
    bound = false;
    theta = 3 * (fx - fp) / (stp - stx) + dx + dp;
    s = max3(fabs(theta), fabs(dx), fabs(dp));
    gamma = s * sqrt (sqr(theta / s) - (dx / s) * (dp / s));
    if (stp > stx) gamma = - gamma;
    p = (gamma - dp) + theta;
    q = ((gamma - dp) + gamma) + dx;
    r = p/q;
    stpc = stp + r * (stx - stp);
    stpq = stp + (dp / (dp - dx)) * (stx - stp);
    if (fabs(stpc - stp) > fabs(stpq - stp))
      stpf = stpc;
    else 
      stpf = stpq;
    brackt = true;
  } else if (fabs(dp) < fabs(dx)) {
    // Third case. A lower function value, derivatives of the
    // same sign, and the magnitude of the derivative decreases.
    // The cubic step is only used if the cubic tends to infinity
    // in the direction of the step or if the minimum of the cubic
    // is beyond stp. Otherwise the cubic step is defined to be
    // either stpmin or stpmax. The quadratic (secant) step is also
    // computed and if the minimum is bracketed then the the step
    // closest to stx is taken, else the step farthest away is taken.

    info = 3;
    bound = true;
    theta = 3 * (fx - fp) / (stp - stx) + dx + dp;
    s = max3(fabs(theta), fabs(dx), fabs(dp));
    gamma = s * sqrt (max(0.0, sqr(theta / s) - (dx / s) * (dp / s)));
    if (stp > stx)
      gamma = - gamma;
    p = gamma - dp + theta;
    q = gamma + (dx - dp) + gamma;
    r = p/q;
    if (r < 0.0 && gamma != 0.0)
      stpc = stp + r * (stx - stp);
    else if (stp > stx)
      stpc = stpmax;
    else
      stpc = stpmin;
    stpq = stp + (dp / (dp - dx)) * (stx - stp);
    if (brackt) {
      if (fabs(stp - stpc) < fabs(stp - stpq))
	stpf = stpc;
      else
	stpf = stpq;
    } else {
      if (fabs(stp - stpc) > fabs(stp - stpq))
	stpf = stpc;
      else
	stpf = stpq;
    }
  } else {
    // Fourth case. A lower function value, derivatives of the
    // same sign, and the magnitude of the derivative does
    // not decrease. If the minimum is not bracketed, the step
    // is either stpmin or stpmax, else the cubic step is taken.

    info = 4;
    bound = false;
    if (brackt) {
      theta = 3 * (fp - fy) / (sty - stp) + dy + dp;
      s = max3(fabs(theta), fabs(dy), fabs(dp));
      gamma = s * sqrt (sqr(theta / s) - (dy / s) * (dp / s));
      if (stp > sty) gamma = - gamma;
      p = (gamma - dp) + theta;
      q = ((gamma - dp) + gamma) + dy;
      r = p/q;
      stpc = stp + r * (sty - stp);
      stpf = stpc;
    }
    else if (stp > stx)
      stpf = stpmax;
    else
      stpf = stpmin;
  }

  // Update the interval of uncertainty. This update does not
  // depend on the new step or the case analysis above.

  if (fp > fx) {
    sty = stp;
    fy = fp;
    dy = dp;
  } else {
    if (sgnd < 0.0) {
      sty = stx;
      fy = fx;
      dy = dx;
    }
    stx = stp;
    fx = fp;
    dx = dp;
  }

  // Compute the new step and safeguard it.
  stpf = min(stpmax, stpf);
  stpf = max(stpmin, stpf);
  stp = stpf;

  if (brackt && bound) {
    if (sty > stx)
      stp = min(stx + 0.66 * (sty - stx), stp);
    else
      stp = max(stx + 0.66 * (sty - stx ), stp );
  }
}

void mcsrch(int n, double* x, double f, double* g, double* s,
	    double& stp, const double ftol, const double xtol,
	    const int maxfev, int& info, int& nfev, double* wa)
{
  double p5 = 0.5;
  double p66 = 0.66;
  static int xtrapf = 4;
  static int infoc = 0;
  static bool brackt = false;
  static double dginit = 0.0, dgtest, finit, stage1, width, width1;
  static double stmin, stmax, stx, fx, dgx, sty, fy, dgy;

  if (info != -1) {
    infoc = 1;
    if (n <= 0 || stp <= 0 || ftol < 0 || LBFGS::gtol < 0
	|| xtol < 0 || LBFGS::stpmin < 0 || LBFGS::stpmax < LBFGS::stpmin || maxfev <= 0) 
      return;

    // Compute the initial gradient in the search direction
    // and check that s is a descent direction.
    dginit = 0.0;
    for (int j = 0; j < n ; j++) {
      dginit += g[j] * s[j];
    }
    if (dginit >= 0) {
      cerr << "The search direction is not a descent direction." << endl;
      return;
    }

    brackt = false;
    stage1 = true;
    nfev = 0;
    finit = f;
    dgtest = ftol*dginit;
    width = LBFGS::stpmax - LBFGS::stpmin;
    width1 = width/p5;

    for (int j = 0; j < n ; j++) {
      wa[j] = x[j];
    }

    // The variables stx, fx, dgx contain the values of the step,
    // function, and directional derivative at the best step.
    // The variables sty, fy, dgy contain the value of the step,
    // function, and derivative at the other endpoint of
    // the interval of uncertainty.
    // The variables stp, f, dg contain the values of the step,
    // function, and derivative at the current step.

    stx = 0;
    fx = finit;
    dgx = dginit;
    sty = 0;
    fy = finit;
    dgy = dginit;
  }

  while (true) {
    // after first iteration info == 0
    if (info != -1) {
      // Set the minimum and maximum steps to correspond
      // to the present interval of uncertainty.

      if (brackt) {
	stmin = min(stx, sty);
	stmax = max(stx, sty);
      }  else {
	stmin = stx;
	stmax = stp + xtrapf * (stp - stx);
      }

      // Force the step to be within the bounds stpmax and stpmin.

      stp = max(stp, LBFGS::stpmin);
      stp = min(stp, LBFGS::stpmax);

      // If an unusual termination is to occur then let
      // stp be the lowest point obtained so far.

      if ((brackt && (stp <= stmin || stp >= stmax)) || nfev >= maxfev - 1
	  || infoc == 0 || (brackt && stmax - stmin <= xtol * stmax))
	stp = stx;

      // Evaluate the function and gradient at stp
      // and compute the directional derivative.
      // We return to main program to obtain F and G.

      for (int j = 0; j < n ; j++) {
	x[j] = wa[j] + stp * s[j];
      }
      info = -1;
      return;
    }

    info = 0;
    nfev++;
    double dg = 0;
    for (int j = 0; j < n ; j++) {
      dg += g[j] * s[j];
    }

    double ftest1 = finit + stp*dgtest;

    // Test for convergence.

    if ((brackt && (stp <= stmin || stp >= stmax)) || infoc == 0) info = 6;

    if (stp == LBFGS::stpmax && f <= ftest1 && dg <= dgtest) info = 5;

    if (stp == LBFGS::stpmin && (f > ftest1 || dg >= dgtest)) info = 4;

    if (nfev >= maxfev) info = 3;

    if (brackt && stmax - stmin <= xtol * stmax) info = 2;

    if (f <= ftest1 && fabs(dg) <= LBFGS::gtol * (-dginit)) info = 1;

    // Check for termination.

    if (info != 0) return;
    // assert(info == 0);

    // In the first stage we seek a step for which the modified
    // function has a nonpositive value and nonnegative derivative.

    if (stage1 && f <= ftest1 && dg >= min(ftol, LBFGS::gtol) * dginit) stage1 = false;

    // A modified function is used to predict the step only if
    // we have not obtained a step for which the modified
    // function has a nonpositive function value and nonnegative
    // derivative, and if a lower function value has been
    // obtained but the decrease is not sufficient.

    if (stage1 && f <= fx && f > ftest1) {
      // Define the modified function and derivative values.

      double fm = f - stp*dgtest;
      double fxm = fx - stx*dgtest;
      double fym = fy - sty*dgtest;
      double dgm = dg - dgtest;
      double dgxm = dgx - dgtest;
      double dgym = dgy - dgtest;

      // Call cstep to update the interval of uncertainty
      // and to compute the new step.

      mcstep(stx, fxm, dgxm, sty, fym, dgym, stp, fm, dgm, brackt, stmin, stmax, infoc);

      // Reset the function and gradient values for f.

      fx = fxm + stx*dgtest;
      fy = fym + sty*dgtest;
      dgx = dgxm + dgtest;
      dgy = dgym + dgtest;
    } else {
      // Call mcstep to update the interval of uncertainty
      // and to compute the new step.

      mcstep(stx, fx, dgx, sty, fy, dgy, stp, f, dg, brackt, stmin, stmax, infoc);
    }

    // Force a sufficient decrease in the size of the
    // interval of uncertainty.

    if (brackt) {
      if (fabs(sty - stx) >= p66 * width1)
	stp = stx + p5 * (sty - stx);
      width1 = width;
      width = fabs(sty - stx);
    }
  }
}

static void lb1(int* iprint, int iter, int nfun, double gnorm, int n, int m,
		double* x, double f, double* g, double stp, bool finish)
{
  int i;
  if (iter == 0) {
    cerr << "*************************************************" << endl;
    cerr << "  n = " << n << "   number of corrections = " << m << "\n       initial values" << endl;
    cerr << " f =  " << f << "   gnorm =  " << gnorm << endl;
    if (iprint[1] >= 1) {
      cerr << " vector x =";
      for (i = 0; i < n; i++)
	cerr << "  " << x[i];
      cerr << "" << endl;

      cerr << " gradient vector g =";
      for (i = 0; i < n; i++)
	cerr << "  " << g[i];
      cerr << "" << endl;
    }
    cerr << "*************************************************" << endl;
    cerr << "\ti\tnfn\tfunc\tgnorm\tsteplength" << endl;
  } else {
    if ((iprint[0] == 0) && (iter != 1 && !finish)) return;
    if (iprint[0] != 0) {
      if ((iter - 1) % iprint[0] == 0 || finish) {
	if (iprint[1] > 1 && iter > 1)
	  cerr << "\ti\tnfn\tfunc\tgnorm\tsteplength" << endl;
	cerr << "\t" << iter << "\t" << nfun << "\t" << f << "\t" << gnorm << "\t" << stp << endl;
      } else
	return;
    } else {
      if (iprint[1] > 1 && finish)
	cerr << "\ti\tnfn\tfunc\tgnorm\tsteplength" << endl;
      cerr << "\t" << iter << "\t" << nfun << "\t" << f << "\t" << gnorm << "\t" << stp << endl;
    }
    if (iprint[1] == 2 || iprint[1] == 3) {
      if (finish)
	cerr << " final point x =";
      else
	cerr << " vector x =  ";
      for (i = 0; i < n; i++)
	cerr << "  " << x[i];
      cerr << "" << endl;
      if (iprint[1] == 3) {
	cerr << " gradient vector g =";
	for (i = 0; i < n; i++)
	  cerr << "  " << g[i];
	cerr << endl;
      }
    }
    if (finish)
      cerr << " The minimization terminated without detecting errors. iflag = 0" << endl;
  }
  return;
}

static double ddot(int n, double* dx, double* dy)
{
  if (n <= 0) return 0;

  double dtemp = 0;
  int m = n % 5;
  if (m != 0) {
    for (int i = 0; i < m ; i++)
      dtemp = dtemp + dx[i] * dy[i];
    if (n < 5)
      return dtemp;
  }

  for (int i = m; i < n; i += 5) {
    dtemp += dx[i] * dy[i] + dx[i+1] * dy[i+1]
      + dx[i+2] * dy[i+2] + dx[i+3] * dy[i+3]
      + dx[i+4] * dy[i+4];
  }
  return dtemp;
}

static void daxpy(int n, double da, double* dx, double* dy)
{
  if (n <= 0) return;
  if (da == 0) return;

  int m = n % 4;
  if (m != 0) {
    for (int i = 0; i < m; i++)
      dy[i] = dy[i] + da * dx[i];
    if (n < 4) return;
  }

  for (int i = m; i < n ; i += 4) {
    dy[i] = dy[i] + da * dx[i];
    dy[i+1] = dy[i+1] + da * dx[i+1];
    dy[i+2] = dy[i+2] + da * dx[i+2];
    dy[i+3] = dy[i+3] + da * dx[i+3];
  }
}

void minimize(int n, int m, double* x, double f, double* g,
	      bool diagco, double* diag, int* iprint, double eps,
	      double xtol, double* w, int& iflag, int& niter, int& nfuns)
{
  static int iter = 0, maxfev = 0, nfev = 0, nfun = 0, info = 0, point = 0;
  static int bound = 0, cp = 0, npt = 0;
  static double ftol, gnorm, stp, stp1, ys;
  bool finish = false;

  int ispt = n+2*m;
  int iypt = ispt+n*m;

  if (iflag == 0) {
    // Initialize.
    iter = 0;

    if (n <= 0 || m <= 0) {
      iflag = -3;
      cerr << "Improper input parameters (n or m are not positive.)" << endl;
    }

    if (gtol <= 0.0001) {
      cerr << "LBFGS:minimize: gtol is less than or equal to 0.0001. It has been reset to 0.9." << endl;
      gtol = 0.9;
    }

    nfun = 1;
    point = 0;

    if (diagco) {
      for (int i = 0; i < n; i++) {
	if (diag[i] <= 0) {
	  iflag = -2;
	  cerr << "The "<< i << "-th diagonal element of the inverse hessian approximation is not positive." << endl;
	}
      }
    } else {
      for (int i = 0; i < n; i++)
	diag[i] = 1.0;
    }
    /*
     *     The work vector w is divided as follows:
     *     ---------------------------------------
     *     The first N locations are used to store the gradient and
     *         other temporary information.
     *     Locations (N+1)...(N+M) store the scalars rho.
     *     Locations (N+M+1)...(N+2M) store the numbers alpha used
     *         in the formula that computes H*G.
     *     Locations (N+2M+1)...(N+2M+NM) store the last M search
     *         steps.
     *     Locations (N+2M+NM+1)...(N+2M+2NM) store the last M
     *         gradient differences.
     *
     *     The search steps and gradient differences are stored in a
     *     circular order controlled by the parameter POINT.
     */

    for (int i = 0; i < n; i++)
      w[ispt + i] = -g[i] * diag[i];

    gnorm = sqrt(ddot(n, g, g));
    stp1 = 1.0 / gnorm;
    //     Parameters for line search routine
    ftol = 0.0001; 
    maxfev = 20;

    if (iprint[0] >= 0)
      lb1(iprint, iter, nfun, gnorm, n, m, x, f, g, stp, finish);
  }
  niter = iter;
  nfuns = nfun;

  // 80:
  for (bool init = true; true; init = false) {
    if (iflag == 0 || !init) {
      iter++;
      info = 0;
      bound = iter-1;
      if (iter == 1) {
	// 165:
	nfev = 0;
	stp = stp1;
	for (int i = 0; i < n; i++)
	  w[i] = g[i];
      } else {
	if (iter > m)
	  bound = m;
	ys = ddot(n, &w[iypt + npt], &w[ispt + npt]);
	if (!diagco) {
	  double yy = ddot(n, &w[iypt + npt], &w[iypt + npt]);
	  for (int i = 0; i < n; i++)
	    diag[i] = ys / yy;
	} else {
	  iflag = 2;
	  return;
	}
      }
    }
    // 100:
    if (iflag == 2 || !init) {
      if (diagco) {
	for (int i = 0; i < n; i++) {
	  if (diag[i] <= 0) {
	    iflag = -2;
	    cerr << "The " << i << "-th diagonal element of the inverse hessian approximation is not positive." << endl;
	  }
	}
      }
      /*
       *     Compute -H*G using the formula given in: Nocedal, J. 1980,
       *     "Updating quasi-Newton matrices with limited storage",
       *     Mathematics of Computation, Vol.24, No.151, pp. 773-782.
       *     ---------------------------------------------------------
       */
      cp = point;
      if (point == 0) cp = m;
      w[n + cp - 1] = 1.0 / ys;

      for (int i = 0; i < n; i++)
	w[i] = -g[i];

      for (int i = 0; i < bound ; i++) {
	cp--;
	if (cp == -1) cp = m - 1;
	double sq = ddot(n, &w[ispt + cp * n], w);
	int inmc = n+m+cp;
	int iycn = iypt+cp*n;
	w[inmc] = w[n + cp] * sq;
	daxpy(n, -w[inmc], &w[iycn], w);
      }

      for (int i = 0; i < n; i++)
	w[i] = diag[i] * w[i];

      for (int i = 0; i < bound ; i++) {
	double yr = ddot(n, &w[iypt + cp * n], w);
	int inmc = n+m+cp;
	double beta = w[inmc] - w[n + cp] * yr;
	int iscn = ispt+cp*n;
	daxpy(n, beta, &w[iscn], w);
	cp++;
	if (cp == m) cp = 0;
      }

      /*
       *     STORE THE NEW SEARCH DIRECTION
       *     ------------------------------
       */
      for (int i = 0; i < n; i++)
	w[ispt + point * n + i] = w[i];

      // 165:
      nfev = 0;
      stp = 1.0;
      if (iter == 1) stp = stp1;
      for (int i = 0; i < n; i++)
	w[i] = g[i];
    }
    /*
     *     OBTAIN THE ONE-DIMENSIONAL MINIMIZER OF THE FUNCTION 
     *     BY USING THE LINE SEARCH ROUTINE MCSRCH
     *     ----------------------------------------------------
     */
    // 172:
    mcsrch(n, x, f, g, &w[ispt + point * n], stp, ftol, xtol, maxfev, info, nfev, diag);

    if (info == -1) {
      iflag = 1;
      return;
    }

    if (info != 1) {
      iflag = -1;
      cerr << "Line search failed. See documentation of routine mcsrch.\n"
	   << "Error return of line search: info = "
	   << info << " Possible causes: function or gradient are incorrect, or incorrect tolerances." << endl;
    }
    nfun += nfev;

    /*
     *     COMPUTE THE NEW STEP AND GRADIENT CHANGE 
     *     -----------------------------------------
     */
    npt = point*n;
    for (int i = 0; i < n; i++) {
      w[ispt + npt + i] = stp * w[ispt + npt + i];
      w[iypt + npt + i] = g[i] - w[i];
    }
    point++;
    if (point == m) point = 0;

    /*
     *     TERMINATION TEST
     *     ----------------
     */
    gnorm = sqrt(ddot(n, g, g));
    double xnorm = sqrt(ddot(n, x, x));
    xnorm = max(1.0, xnorm);

    finish = (gnorm / xnorm <= eps);

    if (iprint[0] >= 0)
      lb1(iprint, iter, nfun, gnorm, n, m, x, f, g, stp, finish);

    niter = iter;
    nfuns = nfun;
    if (finish) {
      iflag = 0;
      return;
    }
    // goto 80
  }
}


} // namespace LBFGS
