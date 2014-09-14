#if !defined(LEM_REAL8__H) && !defined(LEM_NOREAL)
#define LEM_REAL8__H
#pragma once

// -----------------------------------------------------------------------------
// File LEM_FP8.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2007
//
// Content:
// Declare REAL8 floating point type as the same that 'double' ANSI C type.
//
// IEEE DOUBLE PRECISION floating point type.
// -----------------------------------------------------------------------------
//
// CD->01.07.1995
// LC->07.03.2010
// --------------


 #include <math.h>

 namespace lem
 {
  namespace Math
  {
   typedef double REAL8;
   #define TOREAL8(c) c

   const REAL8 MAXREAL8 = 1.797693e+308;
   const REAL8 MINREAL8 =    2.225074e-308;
   const REAL8 MINREALPOW8 = 308.;
   const REAL8 MAXREALPOW8 = 308.;
   const int DIGITS8 =     15;
   const int MAXEXP8 =     +1024;
   const int MINEXP8 =     -1021;
   const int MAXEXP108 =   +308;
   const int MINEXP108 =   -307;
   const REAL8 SQRTMAXREAL8 = 1.3407807427018e154;

   inline REAL8 Dabs( REAL8 x ) { return fabs(x); }

  inline REAL8 Dsqrt( REAL8 x ) { return sqrt(x); }
  inline REAL8 Dfloor( REAL8 x ) { return floor(x); }
  inline REAL8 Dceil( REAL8 x ) { return ceil(x); }

  inline REAL8 Dexp( REAL8 x ) { return exp(x); }
  inline REAL8 Dpow( REAL8 x, REAL8 n ) { return pow(x,n); }
  inline REAL8 Dpow10( REAL8 n ) { return pow(10.0,n); }
  inline REAL8 Dpow2( REAL8 x ) { return x*x; }
  inline REAL8 Dpow3( REAL8 x ) { return x*x*x; }

  inline REAL8 Dmod( REAL8 x, int n ) { return fmod(x,n); }
  inline REAL8 Dmodf( REAL8 x, REAL8* y ) { return modf(x,y); }
  inline REAL8 Drexp( REAL8 x, int* y ) { return frexp(x,y); }
  inline REAL8 Dldexp( REAL8 x, int y ) { return ldexp(x,y); }

  inline REAL8 Dlog( REAL8 x )   { return      log(x); }
  inline REAL8 Dlog10( REAL8 x ) { return    log10(x); }
  inline REAL8 Dsin( REAL8 x )   { return      sin(x); }
  inline REAL8 Dcos( REAL8 x )   { return      cos(x); }
  inline REAL8 Dtan( REAL8 x )   { return      tan(x); }

  inline REAL8 Dacos( REAL8 x ) { return     acos(x); }
  inline REAL8 Dasin( REAL8 x ) { return     asin(x); }
  inline REAL8 Datan( REAL8 x ) { return     atan(x); }

  inline REAL8 Dsinh( REAL8 x ) { return     sinh(x); }
  inline REAL8 Dcosh( REAL8 x ) { return     cosh(x); }
  inline REAL8 Dtanh( REAL8 x ) { return     tanh(x); }

  // -------------------------------------------------------------
  // Корень кубический - иногда встречается в программах для Unix,
  // хотя в библиотеку С++ для DOS не включен.
  // -------------------------------------------------------------
  inline REAL8 Dcbrt( const REAL8 x )
  { return ( x>0. ? Dpow(x,1./3.) : ( x<0. ? -Dpow(-x, 1./3.) : 0. ) ); }

  // Does correctly round floating point argument to integer result.
  inline int Droundi( const REAL8 x )
  { return x>=0. ? int(x) : int(x-1.); }

  inline long Droundl( const REAL8 x )
  { return x>=0. ? long(x) : long(x-1.); }

  extern REAL8 Dmin( const REAL8 *x, const int n );
  extern REAL8 Dmax( const REAL8 *x, const int n );
  extern void Dminmax( const REAL8 *x, const int n, REAL8 &MIN, REAL8 &MAX );
  extern void Dminmax( const REAL8 **Z, const int NX, const int NY, REAL8 &zmin, REAL8 &zmax );

  // -----------------------------------------
  // Translations of angle-measuring units.
  inline REAL8 DRadToGrad( const REAL8 rad )
  { return rad*57.295779513082320876798155; }

  inline REAL8 DGradToRad( const REAL8 gr )
  { return gr*0.017453292519943295769237; }
  // -----------------------------------------

  // ---------------------------------------------------
  // Возвращает дробную часть числа, со знаком аргуметна
  // ---------------------------------------------------
  inline REAL8 Dfrac( const REAL8 x )
  { return x>0. ? x-Dfloor(x) : x+Dfloor(-x); }

  /****************************************************************************
  Performs a safe arctangent calculation for the two provided numbers.  If the
  denominator is 0.0, atan2 is not called (it results in a floating exception
  on some machines).  Instead, + or - PI/2 is returned.
  ****************************************************************************/
  inline REAL8 Datan2( const REAL8 a, const REAL8 b ) /* operands for tan'(a/b) */
  {
   if( b!=0. )
    return atan2( a, b );
   else
    return a>0. ? 1.570796326794896619231322 : -1.570796326794896619231322;
  }

  // Некоторые редкие тригонометрические и гиперболические
  // функции для действительного аргумента.
  inline REAL8 Dsec( const REAL8 x )    { return 1./Dcos(x);  }
  inline REAL8 Dcosec( const REAL8 x )  { return 1./Dsin(x);  }
  inline REAL8 Dcotan( const REAL8 x )  { return 1./Dtan(x);  }

  inline REAL8 Dasec( const REAL8 x )   { return Dacos(1./x); }
  inline REAL8 Dacosec( const REAL8 x ) { return Dasin(1./x); }
  inline REAL8 Dacotan( const REAL8 x )
  { return x>0. ? Datan(1./x) : 3.14159265+Datan(1./x); }

  inline REAL8 Dsech( const REAL8 x )   { return 1./Dcosh(x); }
  inline REAL8 Dcosech( const REAL8 x ) { return 1./Dsinh(x); }
  inline REAL8 Dcotanh( const REAL8 x ) { return 1./Dtanh(x); }

  inline REAL8 Dacosh( const REAL8 x )   { return Dlog(x+Dsqrt(Dpow2(x)-1.)); }
  inline REAL8 Dasinh( const REAL8 x )   { return Dlog(x+Dsqrt(Dpow2(x)+1.)); }
  inline REAL8 Datanh( const REAL8 x )   { return 0.5*Dlog( (1.+x)/(1.-x) ); }
  inline REAL8 Dasech( const REAL8 x )   { return Dacosh(1./x); }
  inline REAL8 Dacosech( const REAL8 x ) { return Dasinh(1./x); }
  inline REAL8 Dacotanh( const REAL8 x ) { return 0.5*Dlog( (x+1.)/(x-1.) ); }

  //         ПРИБЛИЖЕНИЕ ДЕЛЬТА-ФУНКЦИИ
  inline REAL8 Ddelta( const REAL8 x, const REAL8 D, const REAL8 M )
  { return Dexp(-Dpow2(x-M)/(2.*D)) / Dsqrt(6.283185307179586476925287*D); }

  /* linear interpolation from l (when a=0) to h (when a=1)*/
  /* (equal to (a*h)+((1-a)*l) */
  inline REAL8 Dlerp( const REAL8 a, const REAL8 lo, const REAL8 hi )
  { return lo+(hi-lo)*a; }

  /* clamp the input to the specified range */
  inline REAL8 Dclip( const REAL8 v, const REAL8 lo, const REAL8 hi )
  { return v<lo ? lo : v>hi ? hi : v; }

  } // namespace Math
 } // namespace lem

#endif
