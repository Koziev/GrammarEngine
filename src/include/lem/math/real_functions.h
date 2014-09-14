#if !defined(LEM_REAL_FUNCTIONS__H) && !defined(LEM_NOREAL)
#define LEM_REAL_FUNCTIONS__H
#pragma once

// -----------------------------------------------------------------------------
// File REAL_FUNCTIONS.H
//
// (c) Koziev Elijah 1995-2009
//
// Content:
// REAL NUMBERS TYPE SUPPORT.
// Поддержка типа REAL, настройка компилятора на конкретное машинное
// представление.
// -----------------------------------------------------------------------------
//
// CD->18.01.1996
// LC->26.09.2009
// --------------

 #include <lem/config.h>
 #include <lem/minmax.h>
 #include <algorithm>
 #include <lem/math/fp4.h>
 #include <lem/math/fp8.h>
 #include <lem/math/fp10.h>
 #include <lem/math/real.h>

 namespace lem
 {
  namespace Math
  {
   #if defined DEFREAL4

   #define TOREAL(c) c##F

   const REAL4 MAXREAL      = MAXREAL4;
   const REAL4 MINREAL      = MINREAL4;
   const int REALDIGITS     = DIGITS4;
   const REAL4 MINREALEXP   = MINEXP4;
   const REAL4 MAXREALEXP   = MAXEXP4;
   const REAL4 MINREALEXP10 = MINEXP104;
   const REAL4 MAXREALEXP10 = MAXEXP104;
   const REAL4 SQRTMAXREAL  = SQRTMAXREAL4;

  #elif defined DEFREAL10

   #define TOREAL(c) c##L

   const REAL4 MAXREAL      = MAXREAL10;
   const REAL4 MINREAL      = MINREAL10;
   const int REALDIGITS     = DIGITS10;
   const REAL4 MINREALEXP   = MINEXP10;
   const REAL4 MAXREALEXP   = MAXEXP10;
   const REAL4 MINREALEXP10 = MINEXP1010;
   const REAL4 MAXREALEXP10 = MAXEXP1010;
   const REAL4 SQRTMAXREAL  = SQRTMAXREAL10;

  #else

   // По умолчанию определяем REAL как REAL8.
   #define TOREAL(c) TOREAL8(c)

   const REAL8 MAXREAL    = MAXREAL8;
   const REAL8 MINREAL    = MINREAL8;
   #define REAL_TYPE    8
   const int REALDIGITS    =  DIGITS8;
   const int MINREALEXP    =  MINEXP8;
   const int MAXREALEXP    =  MAXEXP8;
   const int MINREALEXP10  = MINEXP108;
   const int MAXREALEXP10  = MAXEXP108;
   const REAL8 SQRTMAXREAL = SQRTMAXREAL8;

  #endif

  inline REAL GetRealMin() { return MINREAL; }
  inline REAL GetRealMax() { return MAXREAL; }

  inline REAL GetRealMaxPow() { return MAXREALEXP10; }
  inline REAL GetRealMinPow() { return MINREALEXP10; }

 //                 ПОДСТАНОВКИ ИМЕН ФУНКЦИЙ

 // ***************************************************
 #if REAL_TYPE==4

  #define qabs(x)       Fabs(x)
  #define qsqrt(x)      Fsqrt(x)
  #define qfloor(x)     Ffloor(x)
  #define qceil(x)      Fceil(x)
  #define qexp(x)       Fexp(x)
  #define qpow(x,n)     Fpow((x),(n))
  #define qmod(x,n)     Fmod((x),(n))
  #define qmodf(x,n)    Fmodf((x),(n))
  #define qrexp(x,y)    Frexp((x),(y))
  #define qldexp(x,y)   Fldexp((x),(y))
  #define qlog(x)       Flog(x)
  #define qlog10(x)     Flog10(x)
  #define qsin(x)       Fsin(x)
  #define qcos(x)       Fcos(x)
  #define qtan(x)       Ftan(x)
  #define qacos(x)      Facos(x)
  #define qasin(x)      Fasin(x)
  #define qatan(x)      Fatan(x)
  #define qsinh(x)      Fsinh(x)
  #define qcosh(x)      Fcosh(x)
  #define qtanh(x)      Ftanh(x)
  #define qcbrt(x)      Fcbrt(x)
  #define qpow2(x)      Fpow2(x)
  #define qpow3(x)      Fpow3(x)
  #define qswap(a,b)    Fswap((a),(b))
  #define qroundi(x)    Froundi(x)
  #define qroundl(x)    Froundl(x)

  inline REAL qmax( REAL x, REAL y ) { return Fmax(x,y); }
  inline REAL qmin( REAL x, REAL y ) { return Fmin(x,y); }
  inline REAL qmin( REAL x, REAL y, REAL z ) { return Fmin(x,y,z); }
  inline REAL qmax( REAL x, REAL y, REAL z ) { return Fmax(x,y,z); }

  inline REAL4 qmin( const REAL *x, int n ) { return Fmin(x,n); }
  inline REAL4 qmax( const REAL *x, int n ) { return Fmax(x,n); }

  inline void qminmax( const REAL *x, int n, REAL &MIN, REAL &MAX )
  { Fminmax(x,n,MIN,MAX); }

  inline void qminmax( const REAL **Z, int NX, int NY, REAL &zmin, REAL &zmax )
  { Fminmax(Z,NX,NY,zmin,zmax); }

  #define RadToGrad(rad) FRadToGrad(rad)
  #define GradToRad(gr)  FGradToRad(gr)

  #define qfrac(x)       Ffrac(x)
  #define qatan2(a,b)    Fatan2((a),(b))

  #define qsec(x)        Fsec(x)
  #define qcosec(x)      Fcosec(x)
  #define qcotan(x)      Fcotan(x)

  #define qacotan(x)     Facotan(x)
  #define qasec(x)       Fasec(x)
  #define qacosec(x)     Facosec(x)

  #define qsech(x)       Fsech(x)
  #define qcosech(x)     Fcosech(x)
  #define qcotanh(x)     Fcotanh(x)

  #define qacosh(x)      Facosh(x)
  #define qasinh(x)      Fasinh(x)
  #define qatanh(x)      Fatanh(x)
  #define qacotanh(x)    Facotanh(x)

  #define qdelta(x,D,M)  Fdelta(x,D,M)

  #define qlerp(a,lo,hi) Flerp(a,lo,hi)
  #define qclip(v,lo,hi) Fclip(v,lo,hi)

 // ***************************************************
 #elif REAL_TYPE==8

  inline REAL qabs( REAL x ) { return Dabs(x); }
  inline REAL qsqrt( REAL x ) { return Dsqrt(x); }
  inline REAL qfloor( REAL x )  { return Dfloor(x); }
  inline REAL qceil( REAL x ) { return Dceil(x); }
  inline REAL qexp( REAL x ) { return Dexp(x); }
  inline REAL qpow( REAL x, REAL8 n ) { return Dpow((x),(n)); }
  inline REAL qmod( REAL x, int n ) { return Dmod((x),(n)); }
  inline REAL qmodf( REAL x, REAL8 *n ) { return Dmodf((x),(n)); }
  inline REAL qrexp( REAL x, int *y ) { return Drexp((x),(y)); }
  inline REAL qldexp( REAL x, int y ) { return Dldexp((x),(y)); }
  inline REAL qlog( REAL x ) { return Dlog(x); }
  inline REAL qlog10( REAL x ) { return Dlog10(x); }
  inline REAL qsin( REAL x ) { return Dsin(x); }
  inline REAL qcos( REAL x ) { return Dcos(x); }
  inline REAL qtan( REAL x ) { return Dtan(x); }
  inline REAL qacos( REAL x ) { return Dacos(x); }
  inline REAL qasin( REAL x ) { return Dasin(x); }
  inline REAL qatan( REAL x ) { return Datan(x); }
  inline REAL qsinh( REAL x ) { return Dsinh(x); }
  inline REAL qcosh( REAL x ) { return Dcosh(x); }
  inline REAL qtanh( REAL x ) { return Dtanh(x); }
  inline REAL qcbrt( REAL x ) { return Dcbrt(x); }
  inline REAL8 qpow2( REAL x ) { return Dpow2(x); }
  inline REAL8 qpow3( REAL x ) { return Dpow3(x); }
  inline int qroundi( REAL x ) { return Droundi(x); }
  inline long qroundl( REAL x ) { return Droundl(x); }

  inline REAL qmax( REAL x, REAL y ) { return _max(x,y); }
  inline REAL qmin( REAL x, REAL y ) { return _min(x,y); }
  inline REAL qmin( REAL x, REAL y, REAL z ) { return _min(x, _min(y,z) ); }
  inline REAL qmax( REAL x, REAL y, REAL z ) { return _max(x, _max(y,z) ); }

  inline REAL qmin( const REAL *x, int n ) { return Dmin(x,n); }
  inline REAL qmax( const REAL *x, int n ) { return Dmax(x,n); }

  inline void qminmax( const REAL *x, int n, REAL &MIN, REAL &MAX )
  { Dminmax(x,n,MIN,MAX); }

  inline void qminmax( const REAL **Z, int NX, int NY, REAL &zmin, REAL &zmax )
  { Dminmax(Z,NX,NY,zmin,zmax); }

  inline REAL RadToGrad( REAL rad) { return DRadToGrad(rad); }
  inline REAL GradToRad( REAL gr) { return  DGradToRad(gr); }

  inline REAL qfrac( REAL x) { return       Dfrac(x); }
  inline REAL qatan2( REAL a, REAL b) { return    Datan2((a),(b)); }

  inline REAL qsec( REAL x) { return        Dsec(x); }
  inline REAL qcosec( REAL x) { return      Dcosec(x); }
  inline REAL qcotan( REAL x) { return      Dcotan(x); }

  inline REAL qacotan( REAL x) { return     Dacotan(x); }
  inline REAL qasec( REAL x) { return       Dasec(x); }
  inline REAL qacosec( REAL x) { return     Dacosec(x); }

  inline REAL qsech( REAL x) { return       Dsech(x); }
  inline REAL qcosech( REAL x) { return     Dcosech(x); }
  inline REAL qcotanh( REAL x) { return     Dcotanh(x); }

  inline REAL qacosh( REAL x) { return      Dacosh(x); }
  inline REAL qasinh( REAL x) { return      Dasinh(x); }
  inline REAL qatanh( REAL x) { return      Datanh(x); }
  inline REAL qacotanh( REAL x) { return    Dacotanh(x); }

  inline REAL qdelta( REAL x, REAL D, REAL M) { return  Ddelta(x,D,M); }

  inline REAL qlerp( REAL a, REAL lo, REAL hi) { return Dlerp(a,lo,hi); }
  inline REAL qclip( REAL v, REAL lo, REAL hi) { return Dclip(v,lo,hi); }

 // ***************************************************
 #elif REAL_TYPE==10

  #define qabs(x)       Labs(x)
  #define qsqrt(x)      Lsqrt(x)
  #define qfloor(x)     Lfloor(x)
  #define qceil(x)      Lceil(x)
  #define qexp(x)       Lexp(x)
  #define qpow(x,n)     Lpow((x),(n))
  #define qmod(x,n)     Lmod((x),(n))
  #define qmodf(x,n)    Lmodf((x),(n))
  #define qrexp(x,y)    Lrexp((x),(y))
  #define qldexp(x,y)   Lldexp((x),(y))
  #define qlog(x)       Llog(x)
  #define qlog10(x)     Llog10(x)
  #define qsin(x)       Lsin(x)
  #define qcos(x)       Lcos(x)
  #define qtan(x)       Ltan(x)
  #define qacos(x)      Lacos(x)
  #define qasin(x)      Lasin(x)
  #define qatan(x)      Latan(x)
  #define qsinh(x)      Lsinh(x)
  #define qcosh(x)      Lcosh(x)
  #define qtanh(x)      Ltanh(x)
  #define qcbrt(x)      Lcbrt(x)
  #define qpow2(x)      Lpow2(x)
  #define qpow3(x)      Lpow3(x)
  #define qswap(a,b)    Lswap((a),(b))
  #define qroundi(x)    Lroundi(x)
  #define qroundl(x)    Lroundl(x)

  inline REAL qmax( REAL x, REAL y ) { return _max(x,y); }
  inline REAL qmin( REAL x, REAL y ) { return _min(x,y); }
  inline REAL qmin( REAL x, REAL y, REAL z ) { return _min(x, _min(y,z) ); }
  inline REAL qmax( REAL x, REAL y, REAL z ) { return _max(x, _max(y,z) ); }

  inline REAL qmin( const REAL *x, int n ) { return Lmin(x,n); }
  inline REAL qmax( const REAL *x, int n ) { return Lmax(x,n); }

  inline void qminmax( const REAL *x, int n, REAL &MIN, REAL &MAX )
  { Lminmax(x,n,MIN,MAX); }

  inline void qminmax( const REAL **Z, int NX, int NY, REAL &zmin, REAL &zmax )
  { Lminmax(Z,NX,NY,zmin,zmax); }

  #define RadToGrad(rad) LRadToGrad(rad)
  #define GradToRad(gr)  LGradToRad(gr)

  #define qfrac(x)       Lfrac(x)
  #define qatan2(a,b)    Latan2((a),(b))

  #define qsec(x)        Lsec(x)
  #define qcosec(x)      Lcosec(x)
  #define qcotan(x)      Lcotan(x)

  #define qacotan(x)     Lacotan(x)
  #define qasec(x)       Lasec(x)
  #define qacosec(x)     Lacosec(x)

  #define qsech(x)       Lsech(x)
  #define qcosech(x)     Lcosech(x)
  #define qcotanh(x)     Lcotanh(x)

  #define qacosh(x)      Lacosh(x)
  #define qasinh(x)      Lasinh(x)
  #define qatanh(x)      Latanh(x)
  #define qacotanh(x)    Lacotanh(x)

  #define qdelta(x,D,M)  Ldelta(x,D,M)

  #define qlerp(a,lo,hi) Llerp(a,lo,hi)
  #define qclip(v,lo,hi) Lclip(v,lo,hi)

 // ***************************************************

  #endif

  extern float get_min_value( const float* );
  extern double get_min_value( const double* );
  extern long double get_min_value( const long double* );
 } // namespace Math
 } // namespace lem

#endif
