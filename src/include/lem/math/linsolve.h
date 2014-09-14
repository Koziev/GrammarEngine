// -----------------------------------------------------------------------------
// File LINSOLVE.H
//
// (c) Koziev Elijah
//
// Content:
// Заголовки процедур решения систем линейных уравнений, нахождения
// детерминантов и смежных проблем.
//
// Solution of Linear Algebraic Equations.
//
// 15.03.2008 - добавлена шаблонная процедура для расчета детерминанта матрицы
//              размером 2x2.
// -----------------------------------------------------------------------------
//
// CD->26.12.1995
// LC->15.03.2008
// --------------

#ifndef LEM_LINSOLVE__H
#define LEM_LINSOLVE__H
#pragma once

 #include <lem/qarray.h>
 #include <lem/qmatrix.h>
 #include <lem/math/math.h>
 #include <lem/oformatter.h>
 #include <lem/console_streams.h>

 namespace lem
 {
  namespace Math
  {
   // LU decomposition.
   bool unsymdet( RMatrix &a, IntArray &tra, REAL eps=MACHEPS );
   void unsymsol( const RMatrix &a, RMatrix& b, const IntArray &tra );
   void unsymsol( const RMatrix &a, const RArray& b, const IntArray &tra, RArray &x );

   bool LU_solve( const RMatrix &a, const RArray& b, RArray& x );
   void LU_improve(
                   const RMatrix &a,
                   const RMatrix &LU,
                   const RArray &b,
                   const IntArray &tra,
                   RArray &x
                  );

   // Gauss-Jordan Elimination with Pivoting
   bool gauss_solve( RMatrix& a, RArray& b, RArray& x );
   bool gauss_triangle( RMatrix& A, IntArray& nrow );
 
   bool iter_solve(
                   const RMatrix& a,
                   const RArray& b,
                   RArray& x,
                   int method,
                   REAL EPS,
                   int MAXITER,
                   int *iter,
                   lem::OFormatter &rep=*lem::mout
                  );

    int iter_solve(
                   const RArray& A,
                   const RArray& B,
                   const RArray& C,
                   const RArray& F,
                   RArray& X,
                   int MAXITER=-1,
                   REAL EpsNeeded=1e-5
                  );

    int iter_solve(
                   const RArray& A,
                   const RArray& B,
                   const RArray& C,
                   const RArray& D,
                   const RArray& E,
                   const RArray& F,
                   RArray& X,
                   int MAXITER=-1,
                   REAL EpsNeeded=1e-5
                  );

   REAL compute_divergence(
                           const RMatrix& a,
                           const RArray& b,
                           const RArray& x,
                           RArray& err
                          );

   REAL compute_divergence(
                           const RMatrix& a,
                           const RArray& b,
                           const RArray& x
                          );
 
   extern REAL DetKramer( const RMatrix& a );

   // Детерминант матрицы 2x2
   template <typename T> 
   inline T Det_2x2( T a11, T a12,
                     T a21, T a22 )
   { return a11*a22 - a12*a21; }


   // Детерминант матрицы 3x3
   template <typename T> 
   inline T Det_3x3(
                    T a11, T a12, T a13,
                    T a21, T a22, T a23,
                    T a31, T a32, T a33
                   )
   { return a11*(a22*a33-a32*a23)-a12*(a21*a33-a31*a23)+a13*(a21*a32-a31*a22); }
 
   extern void Triangle( RMatrix &A, int *nrow );
   extern void SolveGauss( RMatrix &A, RArray &B, int *nrow, RArray &X );
 
   // Procedures for tridiagonal matrices solution
   bool RightProgonka(
                      const RArray& P,
                      const RArray& F,
                      REAL h2,
                      REAL y0, REAL yn,
                      RArray& Y
                     );

   REAL ProgonkaDiverg(
                       const RArray& P,
                       const RArray& F,
                       REAL dx2,
                       const RArray& Y,
                       RArray& div
                      );

   bool RightProgonka(
                      const RArray& A,
                      const RArray& C,
                      const RArray& B,
                      const RArray& F,
                      RArray& Y
                     );

   bool RightProgonka(
                      const RArray& A,
                      const RArray& C,
                      const RArray& B,
                      const RArray& F,
                      RArray& alfa,
                      RArray& beta,
                      RArray& Y
                     );

   bool LeftProgonka(
                     const RArray& A,
                     const RArray& C,
                     const RArray& B,
                     const RArray& F,
                     RArray& Y
                    );

   REAL ProgonkaDiverg(
                       const RArray& A,
                       const RArray& B,
                       const RArray& C,
                       const RArray& F,
                       const RArray& Y,
                       RArray& div
                      );

   // Solution for 5-diagonal matrix
   extern bool Progonka5(
                         const RArray& A,
                         const RArray& B,
                         const RArray& C,
                         const RArray& D,
                         const RArray& E,
                         const RArray& F,
                         RArray& Y
                        );
 } // namespace 'Math'
} // namespace lem

#endif
