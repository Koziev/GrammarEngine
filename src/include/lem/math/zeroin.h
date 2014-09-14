// -----------------------------------------------------------------------------
// File ZEROIN.H
//
// (c) Koziev Elijah
//
// Content:
// Процедуры для поиска корня действительной трансцендентной функции и
// полиномов. Поиск экстремумов.
// -----------------------------------------------------------------------------
//
// CD->18.01.1996
// LC->15.05.2008
// --------------

#ifndef LEM_ZEROIN__H
#define LEM_ZEROIN__H
#pragma once

 #include <lem/qarray.h>
 #include <lem/polynomial.h>
 #include <lem/math/math.h>

 namespace lem
 {
  namespace Math
  {
   typedef REAL(*lem_zero_func)( const REAL x );
 
   extern bool SeparateRootInterval(
                                    REAL x0,
                                    REAL *A,
                                    REAL *B,
                                    lem_zero_func F,
                                    REAL step0=TOREAL(0.),
                                    int MAXITER=lem::Math::GetRealMinPow()
                                   );


   extern REAL BisectionInterval(
                                 REAL A,
                                 REAL B,
                                 lem_zero_func F,
                                 REAL EPS=MACHEPS,
                                 int MAXITER=lem::Math::GetRealMinPow()
                                );

   extern REAL Bisection(
                         REAL X0,
                         lem_zero_func F,
                         REAL EPS=MACHEPS,
                         int MAXITER=lem::Math::GetRealMinPow()
                        );

   extern REAL ZeroIn(
                      REAL A,
                      REAL B,
                      lem_zero_func F,
                      REAL TOL=TOREAL(0.),
                      int MAXITER=-1
                     );

   // ------------------------------------------
   // Нахождение корней полиномов малой степени.
   // ------------------------------------------
   extern int SolveQuadric( const REAL c[3], REAL s[2] );
   extern int SolveCubic(   const REAL c[4], REAL s[3] );
   extern int SolveQuartic( const REAL c[5], REAL s[4] );

   // -------------------------------------------------------------------------
   // Процедура находит все отличные корни для указанного полинома и возвращает
   // их в виде вектора решения.
   // -------------------------------------------------------------------------
   extern const RArray solve_sturm(
                                   const RPolynome &task,
                                   REAL RELERROR=-1.,
                                   int MAXITER=1000
                                  );

   extern void improve_roots(
                             const RPolynome& poly,
                             RArray& roots,
                             int MAXITER=10000,
                             REAL EPS=TOREAL(0.)
                            );

   // A program to solve polinomial equations by Newtons method.
   extern const RArray solve_newton(
                                    const RPolynome &p,
                                    REAL eps=TOREAL(0.),
                                    int MAXITER=1000,
                                    RArray *x0=NULL
                                   );

   // ----------------------------------------------------
   // Нахождение действительных корней полиномов небольших
   // степеней по аналитическим формулам.
   // ----------------------------------------------------
   extern const RArray solve( const RPolynome &c );

   } // namespace Math
 } // namespace lem 

#endif
