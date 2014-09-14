// -----------------------------------------------------------------------------
// File FP4.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// Определение типа REAL4 (как float) для внутренних целей мат. пакета.
// IEEE SIGNLE PRECISION floating point type.
//
// 12.04.2007 - для Borland C Builder отсутствующие функции powf и modff
//              заменены на pow и modf 
// -----------------------------------------------------------------------------
//
// CD->29.06.1995
// LC->13.04.2007
// --------------

#if !defined(REAL4__H) && !defined(LEM_NOREAL)
#define REAL4__H
#pragma once

 #include <lem/config.h> 
 #include <math.h>

 namespace lem
 {
  namespace Math
  {
   typedef float REAL4;

   // Макрос для принудительного объявления константы типа REAL4.
   #define TOREAL4(c) c##F

   // Диапазоны
   const REAL4 MAXREAL4    = 3.37e+38F;
   const REAL4 MINREAL4    = 8.43e-37F;
   const int MINREALPOW4 = 37;
   const int MAXREALPOW4 = 38;
   const int DIGITS4     = 6;
   const int MAXEXP4     = +128;
   const int MINEXP4     = -125;
   const int MAXEXP104   = +38;
   const int MINEXP104   = -37;
   const REAL4 SQRTMAXREAL4 = 1.835756e19F;


   // Стандартные ANSI C функции

   inline REAL4 Fabs( REAL4 x ) { return      fabs(x); }

   inline REAL4 Fsqrt( REAL4 x ) { return     sqrt(x); }
   inline REAL4 Ffloor( REAL4 x ) { return    floor(x); }
   inline REAL4 Fceil( REAL4 x ) { return     ceil(x); }

   inline REAL4 Fexp( REAL4 x ) { return      exp(x); }

   #if defined LEM_BORLAND
   inline REAL4 Fpow( REAL4 x, REAL4 n )   { return pow((x),(n));  }
   inline REAL4 Fpow10( REAL4 n )          { return pow(10.0F,n);  }
   inline REAL4 Fmodf( REAL4 x, REAL4 *y ) { double dy=0; double res=modf((x),&dy); *y = dy; return res; }
   #else
   inline REAL4 Fpow( REAL4 x, REAL4 n )   { return powf((x),(n));  }
   inline REAL4 Fpow10( REAL4 n )          { return powf(10.0F,n);  }
   inline REAL4 Fmodf( REAL4 x, REAL4 *y ) { return modff((x),(y)); }
   #endif

   inline REAL4 Fpow2( REAL4 x ) { return     ((x)*(x)); }
   inline REAL4 Fpow3( REAL4 x ) { return    ((x)*(x)*(x)); }

   inline REAL4 Fmod( REAL4 x, REAL4 y ) { return    fmod((x),(y)); }
   inline REAL4 Frexp( REAL4 x, int *y ) { return   frexp((x),(y)); }
   inline REAL4 Fldexp( REAL4 x, int y ) { return  ldexp((x),(y)); }

   inline REAL4 Flog( REAL4 x ) { return      log(x); }
   inline REAL4 Flog10( REAL4 x ) { return    log10(x); }

   inline REAL4 Fsin( REAL4 x ) { return      sin(x); }
   inline REAL4 Fcos( REAL4 x ) { return      cos(x); }
   inline REAL4 Ftan( REAL4 x ) { return      tan(x); }

   inline REAL4 Facos( REAL4 x )  { return    acos(x); }
   inline REAL4 Fasin( REAL4 x )  { return    asin(x); }
   inline REAL4 Fatan( REAL4 x )  { return    atan(x); }

   inline REAL4 Fsinh( REAL4 x )  { return    sinh(x); }
   inline REAL4 Fcosh( REAL4 x )  { return    cosh(x); }
   inline REAL4 Ftanh( REAL4 x )  { return    tanh(x); }

   // -------------------------------------------------------------
   // Корень кубический - иногда встречается в программах для Unix,
   // хотя в библиотеку С++ для DOS не включен.
   // -------------------------------------------------------------
   inline REAL4 Fcbrt( REAL4 x )
   { return REAL4( x>0.F ? Fpow(x,1.F/3.F) : ( x<0.F ? -Fpow(-x, 1.F/3.F) : 0.F ) ); }

   // Does correctly round floating point argument to integer result.
   inline int Froundi( REAL4 x )
   { return x>=0.F ? int(x) : int(x-1.F); }

   inline long Froundl( REAL4 x )
   { return x>=0.F ? long(x) : long(x-1.F); }

   extern REAL4 Fmin( const REAL4 *x, int n );
   extern REAL4 Fmax( const REAL4 *x, int n );
   extern void Fminmax( const REAL4 *x, int n, REAL4 &MIN, REAL4 &MAX );
   extern void Fminmax( const REAL4 **Z, int NX, int NY, REAL4 &zmin, REAL4 &zmax );

   // -----------------------------------------
   // Translations of angle-measuring units.
   inline REAL4 FRadToGrad( REAL4 rad )
   { return REAL4(rad*57.295779513082320876798155F); }

   inline REAL4 FGradToRad( const REAL4 gr )
   { return REAL4(gr*0.017453292519943295769237F); }
   // -----------------------------------------

   // -------------------------------
   // Возвращает дробную часть числа.
   // -------------------------------
   inline REAL4 Ffrac( REAL4 x )
   { return REAL4( x>0. ? x-Ffloor(x) : x+Ffloor(-x) ); }

   /****************************************************************************
   Performs a safe arctangent calculation for the two provided numbers.  If the
   denominator is 0.0, atan2 is not called (it results in a floating exception
   on some machines).  Instead, + or - PI/2 is returned.
   ****************************************************************************/
   inline REAL4 Fatan2( REAL4 a, REAL4 b ) /* operands for tan'(a/b) */
   {
    if( b!=0.F )
     return REAL4(atan2( a, b ));
    else
     return REAL4(a>0.F ? 1.570796326F : -1.570796326F);
   }

   // Некоторые редкие тригонометрические и гиперболические
   // функции для действительного аргумента.
   inline REAL4 Fsec( REAL4 x )    { return REAL4(1.F/Fcos(x));  }
   inline REAL4 Fcosec( REAL4 x )  { return REAL4(1.F/Fsin(x));  }
   inline REAL4 Fcotan( REAL4 x )  { return REAL4(1.F/Ftan(x));  }

   inline REAL4 Fasec( REAL4 x )   { return REAL4(Facos(1.F/x)); }
   inline REAL4 Facosec( REAL4 x ) { return REAL4(Fasin(1.F/x)); }
   inline REAL4 Facotan( REAL4 x )
   { return REAL4(x>0.F ? Fatan(1.F/x) : 3.14159265F+Fatan(1.F/x)); }

   inline REAL4 Fsech( REAL4 x )   { return REAL4(1.F/Fcosh(x)); }
   inline REAL4 Fcosech( REAL4 x ) { return REAL4(1.F/Fsinh(x)); }
   inline REAL4 Fcotanh( REAL4 x ) { return REAL4(1.F/Ftanh(x)); }

   inline REAL4 Facosh( REAL4 x )   { return REAL4(Flog(x+Fsqrt(Fpow2(x)-1.F))); }
   inline REAL4 Fasinh( REAL4 x )   { return REAL4(Flog(x+Fsqrt(Fpow2(x)+1.F))); }
   inline REAL4 Fasech( REAL4 x )   { return REAL4(Facosh(1.F/x)); }
   inline REAL4 Facosech( REAL4 x ) { return REAL4(Fasinh(1.F/x)); }
   inline REAL4 Fatanh( REAL4 x )   { return REAL4(0.5F*Flog( (1.F+x)/(1.F-x) )); }
   inline REAL4 Facotanh( REAL4 x ) { return REAL4(0.5F*Flog( (x+1.F)/(x-1.F) )); }

   // ПРИБЛИЖЕНИЕ ДЕЛЬТА-ФУНКЦИИ
   inline REAL4 Fdelta( REAL4 x, REAL4 D, REAL4 M )
   { return REAL4(Fexp(-Fpow2(x-M)/(2.F*D)) / Fsqrt(6.283185307179586476925287F*D)); }

   /* linear interpolation from l (when a=0) to h (when a=1)*/
   /* (equal to (a*h)+((1-a)*l) */
   inline REAL4 Flerp( REAL4 a, REAL4 lo, REAL4 hi )
   { return lo+(hi-lo)*a; }

   /* clamp the input to the specified range */
   inline REAL4 Fclip( REAL4 v, REAL4 lo, REAL4 hi )
   { return v<lo ? lo : v>hi ? hi : v; }

  } // namespace Math
 } // namespace lem

#endif
