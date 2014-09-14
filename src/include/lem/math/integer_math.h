// -----------------------------------------------------------------------------
// File INTEGER_MATH.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2005
//
// Content:
// Быстрые операции над целочисленными операндами. Также всячая всякина по
// теории чисел.
//
// 02.06.2004 - all functions are enclosed into 'lem' namespace
// -----------------------------------------------------------------------------
//
// CD->22.06.1995
// LC->29.12.2006
// --------------

#ifndef LEM_INTEGER_MATH__H
#define LEM_INTEGER_MATH__H
#pragma once

 namespace lem
 {
  namespace Math
  {

   // Вычисление факториала.
   extern long ifact( int NN );

   // -------------
   // Модуль числа.
   // -------------
   inline int iabs( int a ) { return a>0 ? a : -a; }
   inline long labs( long int a ) { return a>0 ? a : -a; }

   // ---------------------
   // Знак аргумента.
   // ---------------------
   inline int isign( int x )
   { return x<0 ? -1 : ( x ? 1 : 0 ); }

   extern unsigned long lpow2n( unsigned int n );
   extern unsigned int llog2( unsigned long x );

   extern int isqrt( int a );

   inline int ibound_max( int a, int max )
   { return a>max ? max : a; }

   inline int ibound_min( int a, int min )
   { return a<min ? min : a; }

   inline int ibound( int min, int a, int max )
   { return a>max ? max : lem::Math::ibound_min(a,min); }

   inline int ipow2( int x ) { return x*x; }

   // ***********************************************************************
   // Возвращает минимальное число, которое не меньше аргумента x и нацело
   // делится на 4. Эта функция выполняет 'выравнивание на границу двойного
   // слова'.
   // ***********************************************************************
   inline unsigned int ialign4( unsigned int x )
   { return ( x%4 ? (x/4+1)*4: x); }

   // Выравнивание на границу слова.
   inline unsigned int ialign2( unsigned int x )
   { return ( x%2 ? (x/2+1)*2: x); }

   // Выравнивание на границу учетверённого слова.
   inline unsigned int ialign8( unsigned int x )
   { return ( x%8 ? (x/8+1)*8: x); }
 
   // Выравнивание на границу параграфа.
   inline unsigned int ialign16( unsigned int x )
   { return ( x%16 ? (x/16+1)*16: x); } 

   // Целочисленная тригонометрия - очень быстро, хотя и не совсем точно.
   // Используется графической библиотекой. Аргумент - угол в градусах.
   extern int isin( int angle );
   extern int icos( int angle );

   // Результат триг. функций делится на это число для получения
   // результата в стандартном диапазоне [-1,1]
   #define LEM_TRIG_D 10000
   #define LEM_TRIG_DR REAL(LEM_TRIG_D)

   inline long lmod( long a, long b )
   { return a-(a/b)*b; }

   extern bool isprime( long a );

   extern int NODEuclid( int a1, int a2 );

  } // namespace Math

} // namespace lem

#endif
