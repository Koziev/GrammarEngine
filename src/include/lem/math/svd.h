// -----------------------------------------------------------------------------
// File SVD.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// —ингул€рное разложение матриц и приложени€.
// -----------------------------------------------------------------------------
//
// CD->26.02.96
// LC->28.10.04
// ------------

#ifndef LEM_SVD__H
#define LEM_SVD__H
#pragma once

 #include <lem/qmatrix.h>
 #include <lem/qarray.h>
 #include <lem/polynomial.h>

 namespace lem
 {
  namespace Math
  {
  extern int SVD(
                 RMatrix& A,
                 bool MATU,
                 bool MATV,
                 RArray& W,
                 RMatrix& U,
                 RMatrix& V
                );

  extern REAL SVD_det( const RMatrix& A );

  extern const RPolynome Approx_SVD(
                                    const RArray& xi,
                                    const RArray& yi,
                                    int NPOLY,
                                    REAL RELERR=0.
                                   );
  } // namespace Math
 } // namespace lem

#endif
// ---------------------------- End Of File [SVD.H] ----------------------------
