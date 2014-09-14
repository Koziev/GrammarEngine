// -----------------------------------------------------------------------------
// File EIGENA.H
//
// (c) Koziev Elijah
//
// Content:
// Процедуры для решения Проблемы Собственных Значений.
// -----------------------------------------------------------------------------
//
// CD->19.12.1995
// LC->15.05.2008
// --------------

#ifndef LEM_EIGENA__H
#define LEM_EIGENA__H
#pragma once

 #include <lem/qarray.h>
 #include <lem/qmatrix.h>
 #include <lem/math/math.h>
 #include <lem/oformatter.h>

 namespace lem
 {
  namespace Math
  {
   extern void elmhes(
                      RMatrix& a,
                      int low,
                      int upp,
                      IntArray& tra
                     );

   extern bool eigen_sym_jackobi( RMatrix &a, RMatrix &s );

   extern void elmbak(
                      RMatrix& a,
                      int low,
                      int upp,
                      int r,
                      IntArray& tra,
                      RMatrix& z
                     );

   extern void elmtrans(
                        const RMatrix& h,
                        int low,
                        int upp,
                        const IntArray& tra,
                        RMatrix& v
                       );

   extern void orthes(
                      RMatrix& a,
                      int low,
                      int upp,
                      REAL tol,
                      RArray& d
                     );
 
   extern void ortrans(
                       RMatrix& h,
                       int low,
                       int upp,
                       RArray& d,
                       RMatrix& v
                      );

   /****************************************************************
     QR алгоритм был разработан Френсисом около 1960 г. Одновременно
     и независимо под названием метода односторонних вращений был
     предложен В.Н.Кублановской.
   *****************************************************************/
   extern bool hqr(
                   RMatrix& a,
                   RArray& wr,
                   RArray& wi,
                   IntArray& cnt,
                   REAL eps=0.
                  );

   extern bool hqr2(
                    RMatrix& h,
                    int low,
                    int upp,
                    REAL macheps,
                    RMatrix &vecs,
                    RArray& wi,
                    RArray& wr,
                    IntArray& cnt
                   );

   extern bool eigen(
                     RMatrix& a,
                     RMatrix& t,
                     int tmx,
                     REAL ep
                    );

   extern bool ComputeEigenValues(
                                  RMatrix& h,
                                  RArray& wr,
                                  RArray& wi
                                 );

   extern bool ComputeEigenVectors(
                                   RMatrix& h,
                                   RArray& wi,
                                   RArray& wr
                                  );

   extern void RowsOrthogonality( const RMatrix &a, OFormatter &s );
   extern void GramSchmidt( RMatrix& a );
   extern bool RiceOrthogonalize( RMatrix& a );

   extern bool EigenJackobi(
                            RMatrix& a,
                            RArray& wr,
                            RArray& wi,
                            REAL eps=compute_mach_eps()
                           );

   extern bool EigenJackobi_Sym(
                                RMatrix &a,
                                RArray &wr,
                                RArray &wi
                               );
  } // namespace Math
 } // namespace lem

#endif
// -------------------------- End Of File [EIGENA.H] ---------------------------
