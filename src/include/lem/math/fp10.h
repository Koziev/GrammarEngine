// -----------------------------------------------------------------------------
// File LEM_FP10.H
//
// (c) Koziev Elijah
//
// Content:
// Определение специального типа чисел с плавающей точкой "учетверенной"
// точности (REAL10)
// -----------------------------------------------------------------------------
//
// CD->29.06.1995
// LC->07.03.2010
// --------------

#if !defined( REAL10__H ) && !defined(LEM_NOREAL)
 #define REAL10__H

 #include <math.h>

 // Если у компилятора есть проблеммы с типом long double,
 // то определение макроса NOREAL10 приведет к автоматической
 // подмене этого типа на REAL8, то есть double.

 #if !defined LEM_NOREAL10 && defined LEM_WATCOM
  #define LEM_NOREAL10
 #endif
 
 #if defined LEM_BSD
  #define LEM_NOQFUN
 #endif
 

 #if !defined LEM_NOREAL10

  typedef long double REAL10;
  #define TOREAL10(c) c##L

  #define MAXREAL10    1.1e+4392L
  #define MINREAL10    3.4e-4392L
  #define MINREALPOW10 4392.
  #define MAXREALPOW10 4392.
  #define DIGITS10     19
  #define MAXEXP10     +16384
  #define MINEXP10     -16381
  #define MAXEXP1010   +4932
  #define MINEXP1010   -4931

  #define SQRTMAXREAL10 1.04880884817015216e2196L

 #else

  typedef double REAL10;
  #define TOREAL10(c) c

  #define MAXREAL10    1.797693e+308
  #define MINREAL10    2.225074e-308
  #define MINREALPOW10 308.
  #define MAXREALPOW10 308.
  #define DIGITS10     15
  #define MAXEXP10     +1024
  #define MINEXP10     -1021
  #define MAXEXP1010   +308
  #define MINEXP1010   -307

  #define SQRTMAXREAL10 1.3407807427018e154

 #endif

 /*
  Даже если компилятор поддерживает тип long double, он
  может не поддерживать математические функции для этого
  типа, так как это не предусмотрено стандартом ANSI C.
  Такова ситуация, к примеру, с Borland C++ 2.0. В этом
  случае можно определить макрос NOQFUN и для обработки
  REAL10-чисел будет использован аппарат REAL8-функций.
 */

 #if !defined LEM_NOQFUN && !defined LEM_NOREAL10

  #define Labs(x)       fabsl(x)

  #define Lsqrt(x)      sqrtl(x)
  #define Lfloor(x)     floorl(x)
  #define Lceil(x)      ceill(x)

  #define Lexp(x)       expl(x)
  #define Lpow(x,n)     powl((x),(n))
  #define Lpow10(n)     pow10l(n)
  #define Lpow2(x)      ((x)*(x))
  #define Lpow3(x)      ((x)*(x)*(x))

  #define Lmod(x,n)     fmodl((x),(n))
  #define Lmodf(x,n)    modfl((x),(n))
  #define Lrexp(x,y)    frexpl((x),(y))
  #define Lldexp(x,y)   ldexpl((x),(y))

  #define Llog(x)       logl(x)
  #define Lsqrt(x)      sqrtl(x)
  #define Llog10(x)     log10l(x)
   
  #define Lsin(x)       sinl(x)
  #define Lcos(x)       cosl(x)
  #define Ltan(x)       tanl(x)

  #define Lacos(x)      acosl(x)
  #define Lasin(x)      asinl(x)
  #define Latan(x)      atanl(x)

  #define Lsinh(x)      sinhl(x)
  #define Lcosh(x)      coshl(x)
  #define Ltanh(x)      tanhl(x)

  // -------------------------------------------------------------
  // Корень кубический - иногда встречается в программах для Unix,
  // хотя в библиотеку С++ для DOS не включен.
  // -------------------------------------------------------------
  inline REAL10 Lcbrt( const REAL10 x )
  { return ( x>0.L ? Lpow(x,1.L/3.L) : ( x<0.L ? -Lpow(-x, 1.L/3.L) : 0.L ) ); }

  inline void Lswap( REAL10& a, REAL10& b )
  {
   REAL10 c=a;
   a=b;
   b=c;
  }

  // Does correctly round floating point argument to integer result.
 inline int Lroundi( const REAL10 x )
 { return x>=0.L ? int(x) : int(x-1.L); }

 inline long Lroundl( const REAL10 x )
 { return x>=0.L ? long(x) : long(x-1.L); }

  // ---------------------------------
  // These functions find minimums and
  // maximums of the arguments.
  // ---------------------------------
  inline REAL10 Lmax( const REAL10 x, const REAL10 y )
  { return ( x>y ? x : y ); }

  inline REAL10 Lmin( const REAL10 x, const REAL10 y )
  { return ( x<y ? x : y );}

  inline REAL10 Lmin( const REAL10 x, const REAL10 y, const REAL10 z )
  { return Lmin( x, Lmin( y, z ) ); }

  inline REAL10 Lmax( const REAL10 x, const REAL10 y, const REAL10 z )
  { return Lmax( x, Lmax( y, z ) ); }

  extern REAL10 Lmin( const REAL10 *x, const int n );
  extern REAL10 Lmax( const REAL10 *x, const int n );
  extern void Lminmax( const REAL10 *x, const int n, REAL10 &MIN, REAL10 &MAX );
  extern void Lminmax( const REAL10 **Z, const int NX, const int NY, REAL10 &zmin, REAL10 &zmax );

  // -----------------------------------------
  // Translations of angle-measuring units.
  inline REAL10 LRadToGrad( const REAL10 rad )
  { return rad*57.295779513082320876798155L; }

  inline REAL10 LGradToRad( const REAL10 gr )
  { return gr*0.017453292519943295769237L; }
  // -----------------------------------------

  // ---------------------------------------------------
  // Возвращает дробную часть числа, со знаком аргуметна
  // ---------------------------------------------------
  inline REAL10 Lfrac( const REAL10 x )
  { return x>0.L ? x-Lfloor(x) : x+Lfloor(-x); }

  /****************************************************************************
  Performs a safe arctangent calculation for the two provided numbers.  If the
  denominator is 0.0, atan2 is not called (it results in a floating exception
  on some machines).  Instead, + or - PI/2 is returned.
  ****************************************************************************/
  inline REAL10 Latan2( const REAL10 a, const REAL10 b ) /* operands for tan'(a/b) */
  {
   if( b!=0.L )
    return atan2l( a, b );
   else
    return a>0.L ? 1.570796326794896619231322L : -1.570796326794896619231322L;
  }

  // Некоторые редкие тригонометрические и гиперболические
  // функции для действительного аргумента.
  inline REAL10 Lsec( const REAL10 x )    { return 1.L/Lcos(x);  }
  inline REAL10 Lcosec( const REAL10 x )  { return 1.L/Lsin(x);  }
  inline REAL10 Lcotan( const REAL10 x )  { return 1.L/Ltan(x);  }

  inline REAL10 Lasec( const REAL10 x )   { return Lacos(1.L/x); }
  inline REAL10 Lacosec( const REAL10 x ) { return Lasin(1.L/x); }
  inline REAL10 Lacotan( const REAL10 x )
  { return x>0.L ? Latan(1.L/x) : 3.14159265L+Latan(1.L/x); }

  inline REAL10 Lsech( const REAL10 x )   { return 1.L/Lcosh(x); }
  inline REAL10 Lcosech( const REAL10 x ) { return 1.L/Lsinh(x); }
  inline REAL10 Lcotanh( const REAL10 x ) { return 1.L/Ltanh(x); }

  inline REAL10 Lacosh( const REAL10 x )   { return Llog(x+Lsqrt(Lpow2(x)-1.L)); }
  inline REAL10 Lasinh( const REAL10 x )   { return Llog(x+Lsqrt(Lpow2(x)+1.L)); }
  inline REAL10 Lasech( const REAL10 x )   { return Lacosh(1.L/x); }
  inline REAL10 Lacosech( const REAL10 x ) { return Lasinh(1.L/x); }
  inline REAL10 Latanh( const REAL10 x )   { return 0.5L*Llog( (1.L+x)/(1.L-x) ); }
  inline REAL10 Lacotanh( const REAL10 x ) { return 0.5L*Llog( (x+1.L)/(x-1.L) ); }

  //         ПРИБЛИЖЕНИЕ ДЕЛЬТА-ФУНКЦИИ
  inline REAL10 Ldelta( const REAL10 x, const REAL10 D, const REAL10 M )
  { return Lexp(-Lpow2(x-M)/(2.L*D)) / Lsqrt(6.283185307179586476925287L*D); }

 #else // !defined LEM_NOQFUN && !defined LEM_NOREAL10

  #define Labs(x)       fabs(x)

  #define Lsqrt(x)      sqrt(x)
  #define Lfloor(x)     floor(x)
  #define Lceil(x)      ceil(x)

  #define Lexp(x)       exp(x)
  #define Lpow(x,n)     pow((x),(n))
  #define Lpow10(n)     pow10(n)
  #define Lpow2(x)      ((x)*(x))
  #define Lpow3(x)      ((x)*(x)*(x))

  #define Lmod(x,y)     fmod((x),(n))
  #define Lmodf(x,y)    modf((x),(n))
  #define Lrexp(x,y)    frexp((x),(y))
  #define Lldexp(x,y)   ldexp((x),(y))

  #define Llog(x)       log(x)
  #define Llog10(x)     log10(x)
  #define Lsin(x)       sin(x)
  #define Lcos(x)       cos(x)
  #define Ltan(x)       tan(x)

  #define Lacos(x)      acos(x)
  #define Lasin(x)      asin(x)
  #define Latan(x)      atan(x)

  #define Lsinh(x)      sinh(x)
  #define Lcosh(x)      cosh(x)
  #define Ltanh(x)      tanh(x)

  // -------------------------------------------------------------
  // Корень кубический - иногда встречается в программах для Unix,
  // хотя в библиотеку С++ для DOS не включен.
  // -------------------------------------------------------------
  inline REAL10 Lcbrt( const REAL10 x )
  { return ( x>0. ? Lpow(x,1./3.) : ( x<0. ? -Lpow(-x, 1./3.) : 0. ) ); }

  inline void Lswap( REAL10& a, REAL10& b )
  {
   REAL10 c=a;
   a=b;
   b=c;
  }

  // Does correctly round floating point argument to integer result.
  inline int Lroundi( const REAL10 x )
  { return x>=0. ? int(x) : int(x-1.); }

  inline long Lroundl( const REAL10 x )
  { return x>=0. ? long(x) : long(x-1.); }

  // ---------------------------------
  // These functions find minimums and
  // maximums of the arguments.
  // ---------------------------------
  inline REAL10 Lmax( const REAL10 x, const REAL10 y )
  { return ( x>y ? x : y ); }

  inline REAL10 Lmin( const REAL10 x, const REAL10 y )
  { return ( x<y ? x : y );}

  inline REAL10 Lmin( const REAL10 x, const REAL10 y, const REAL10 z )
  { return Lmin( x, Lmin( y, z ) ); }

  inline REAL10 Lmax( const REAL10 x, const REAL10 y, const REAL10 z )
  { return Lmax( x, Lmax( y, z ) ); }

  extern REAL10 Lmin( const REAL10 *x, const int n );
  extern REAL10 Lmax( const REAL10 *x, const int n );
  extern void Lminmax( const REAL10 *x, const int n, REAL10 &MIN, REAL10 &MAX );
  extern void Lminmax( const REAL10 **Z, const int NX, const int NY, REAL10 &zmin, REAL10 &zmax );

  // -----------------------------------------
  // Translations of angle-measuring units.
  inline REAL10 LRadToGrad( const REAL10 rad )
  { return rad*57.295779513082320876798155L; }

  inline REAL10 LGradToRad( const REAL10 gr )
  { return gr*0.017453292519943295769237L; }
  // -----------------------------------------

  // ---------------------------------------------------
  // Возвращает дробную часть числа, со знаком аргуметна
  // ---------------------------------------------------
  inline REAL10 Lfrac( const REAL10 x )
  { return x>0. ? x-Lfloor(x) : x+Lfloor(-x); }

  /****************************************************************************
  Performs a safe arctangent calculation for the two provided numbers.  If the
  denominator is 0.0, atan2 is not called (it results in a floating exception
  on some machines).  Instead, + or - PI/2 is returned.
  ****************************************************************************/
  inline REAL10 Latan2( const REAL10 a, const REAL10 b ) /* operands for tan'(a/b) */
  {
   if( b!=0. )
    return atan2( a, b );
   else
    return a>0. ? 1.570796326794896619231322L : -1.570796326794896619231322L;
  }

  // Некоторые редкие тригонометрические и гиперболические
  // функции для действительного аргумента.
  inline REAL10 Lsec( const REAL10 x )    { return 1./Lcos(x);  }
  inline REAL10 Lcosec( const REAL10 x )  { return 1./Lsin(x);  }
  inline REAL10 Lcotan( const REAL10 x )  { return 1./Ltan(x);  }

  inline REAL10 Lasec( const REAL10 x )   { return Lacos(1./x); }
  inline REAL10 Lacosec( const REAL10 x ) { return Lasin(1./x); }
  inline REAL10 Lacotan( const REAL10 x )
  { return x>0.L ? Latan(1.L/x) : 3.14159265L+Latan(1.L/x); }

  inline REAL10 Lsech( const REAL10 x )   { return 1./Lcosh(x); }
  inline REAL10 Lcosech( const REAL10 x ) { return 1./Lsinh(x); }
  inline REAL10 Lcotanh( const REAL10 x ) { return 1./Ltanh(x); }

  inline REAL10 Lacosh( const REAL10 x )   { return Llog(x+Lsqrt(Lpow2(x)-1.)); }
  inline REAL10 Lasinh( const REAL10 x )   { return Llog(x+Lsqrt(Lpow2(x)+1.)); }
  inline REAL10 Latanh( const REAL10 x )   { return 0.5*Llog( (1.+x)/(1.-x) ); }
  inline REAL10 Lasech( const REAL10 x )   { return Lacosh(1.F/x); }
  inline REAL10 Lacosech( const REAL10 x ) { return Lasinh(1.F/x); }
  inline REAL10 Lacotanh( const REAL10 x ) { return 0.5*Llog( (x+1.)/(x-1.) ); }

  //         ПРИБЛИЖЕНИЕ ДЕЛЬТА-ФУНКЦИИ
  inline REAL10 Ldelta( const REAL10 x, const REAL10 D, const REAL10 M )
  { return Lexp(-Lpow2(x-M)/(2.*D)) / Lsqrt(6.283185307179586476925287L*D); }

 #endif

 /* linear interpolation from l (when a=0) to h (when a=1)*/
 /* (equal to (a*h)+((1-a)*l) */
 inline REAL10 Llerp( const REAL10 a, const REAL10 lo, const REAL10 hi )
 { return lo+(hi-lo)*a; }

 /* clamp the input to the specified range */
 inline REAL10 Lclip( const REAL10 v, const REAL10 lo, const REAL10 hi )
 { return v<lo ? lo : v>hi ? hi : v; }

#endif

