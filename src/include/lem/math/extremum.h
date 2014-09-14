// -----------------------------------------------------------------------------
// File EXTREMUM.H
//
// (c) Koziev Elijah
//
// Content:
// Заголовки процедур поиска экстремумов произвольных функций.
// -----------------------------------------------------------------------------
//
// CD->10.02.1996
// LC->15.05.2008
// --------------

#ifndef LEM_EXTREMUM__H
#define LEM_EXTREMUM__H
#pragma once

 #include <lem/qarray.h>
 #include <lem/math/math.h>

 namespace lem
 {
  namespace Math
  {
   typedef REAL(*lem_min_func)( REAL x );
   typedef REAL(*lem_min_func_2d)( REAL x1, REAL x2 );
   typedef bool(*lem_volume_fun_2d)( REAL x1, REAL x2 ); 

   typedef REAL(*lem_min_func_nd)( const RArray& x );
   typedef bool(*lem_volume_fun_nd)( const RArray& x );

   extern REAL FindMinimum(
                           REAL AX,
                           REAL BX,
                           lem_min_func F,
                           REAL TOL
                          );

   extern REAL FindMinBisect(
                             REAL A,
                             REAL B,
                             lem_min_func F,
                             REAL EPS=0.
                            );

   extern void FindMinimum(
                           lem_min_func_2d F,
                           lem_volume_fun_2d V,
                           REAL a1,
                           REAL a2,
                           REAL b1,
                           REAL b2,
                           int ntrials,
                           REAL *X1,
                           REAL *X2
                          );

   extern void FindMinimum(
                           lem_min_func_nd F,
                           lem_volume_fun_nd V,
                           const RArray& a,
                           const RArray& b,
                           int ntrials,
                           int nrecurse,
                           RArray &x
                          );

   extern REAL FindMinSimplex(
                              lem_min_func_nd F,
                              RArray &x,
                              REAL step,
                              REAL AL=1.0,
                              REAL BE=0.5,
                              REAL GA=2.0,
                              REAL EPS=MACHEPS
                             );
				
  } // namespace Math     
 } // namespace lem				     

#endif
// -------------------------- End Of File [EXTREMUM.H] -------------------------
