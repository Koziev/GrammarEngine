// -----------------------------------------------------------------------------
// File LEM_M4X4.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
//  ласс Matrix4x4 - матрица фиксированных размеров 4*4 дл€ использовани€ в
// процедурах машинной графики.
// -----------------------------------------------------------------------------
//
// CD->13.07.1995
// LC->25.02.2007
// --------------

#ifndef LEM_MATR4X4__H
#define LEM_MATR4X4__H
#pragma once

 #include <lem/math/math.h>

 namespace lem
 {
  namespace Math
  {

 class Matrix4x4
 {
  private:
   REAL a[16];

   /*
     ћатрица развернута в вектор:

     a[0]  a[1]  a[2]  a[3]
     a[4]  a[5]  a[6]  a[7]
     a[8]  a[9]  a[10] a[11]
     a[12] a[13] a[14] a[15]
   */

  public:
   Matrix4x4(void) { memset( a, 0, sizeof(a) ); }

   Matrix4x4(
             REAL s11, REAL s12, REAL s13,
             REAL s21, REAL s22, REAL s23,
             REAL s31, REAL s32, REAL s33
            )
   {
    a[0]=s11; a[1]=s12; a[2]=s13;
    a[4]=s21; a[5]=s22; a[6]=s23;
    a[8]=s31; a[9]=s32; a[10]=s33;
    a[3]=a[7]=a[11]=a[12]=a[13]=a[14]=0.;
    a[15]=1.;
    return;
   }

   Matrix4x4(
             REAL s11, REAL s12, REAL s13, REAL s14,
             REAL s21, REAL s22, REAL s23, REAL s24,
             REAL s31, REAL s32, REAL s33, REAL s34,
             REAL s41=0., REAL s42=0., REAL s43=0., REAL s44=1.
            )
   {
    a[0] =s11; a[1] =s12; a[2] =s13; a[3] =s14;
    a[4] =s21; a[5] =s22; a[6] =s23; a[7] =s24;
    a[8] =s31; a[9] =s32; a[10]=s33; a[11]=s34;
    a[12]=s41; a[13]=s42; a[14]=s43; a[15]=s44;
    return;
   }

   // „тобы легко работать с нулевыми и еденичными
   // матрицами (и только дл€ них) позволим преобразовывать
   // числа 0 и 1 в соотв. диагональные матрицы.
   Matrix4x4( REAL c )
   { memset( a, 0, sizeof(a) ); a[0]=a[5]=a[10]=a[15]=c; }

   Matrix4x4& operator*=( const Matrix4x4 &B );

   inline REAL get( int i, int j ) const { return a[i*4+j]; }
   inline void set( int i, int j, const REAL k ) { a[i*4+j]=k; }

   inline REAL lget( int i ) const { return a[i]; }
   inline REAL operator()( int i ) const { return a[i]; }

   friend const Matrix4x4 operator*(
                                    const Matrix4x4 &x,
                                    const Matrix4x4 &b
                                   );

   friend const Matrix4x4 rotate3d(
                                   REAL ax, REAL ay, REAL az,
                                   REAL vdx, REAL vdy, REAL vdz,
                                   REAL alpha
                                  );

   friend const Matrix4x4 rotateOX3d( REAL alpha );
   friend const Matrix4x4 rotateOY3d( REAL alpha );
   friend const Matrix4x4 rotateOZ3d( REAL alpha );
   friend const Matrix4x4 reflectOX3d(void);
   friend const Matrix4x4 reflectOY3d(void);
   friend const Matrix4x4 reflectOZ3d(void);
   friend const Matrix4x4 scale3d(
                                  REAL sx,
                                  REAL sy,
                                  REAL sz,
                                  REAL fpx,
                                  REAL fpy,
                                  REAL fpz
                                 );

   friend const Matrix4x4 translate3d(
                                      REAL dx,
                                      REAL dy,
                                      REAL dz
                                     );

   friend const Matrix4x4 viewmatrix3d(
                                       REAL rho,
                                       REAL theta,
                                       REAL phi
                                      );

   friend const Matrix4x4 DiagMatrix4x4(
                                        REAL x,
                                        REAL y,
                                        REAL z
                                       );
  };

 extern const Matrix4x4 inverse( const Matrix4x4 &in );
 extern const Matrix4x4 adjoint( const Matrix4x4 &in );
 extern REAL determinent( const Matrix4x4 &m );

  } // namespace Math
 } // namespace lem

#endif
// -------------------------- End Of File [LEM_M4X4.H] -------------------------
