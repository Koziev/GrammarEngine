// -----------------------------------------------------------------------------
// File SPECIFUN.H
//
// (c) Koziev Elijah
//
// Content:
// Специальные (высшие трансцендентные) функции (из разных источников).
// -----------------------------------------------------------------------------
//
// CD->20.01.1996
// LC->28.05.2006
// --------------

#ifndef LEM_SPECIFUN__H
#define LEM_SPECIFUN__H
#pragma once

 #include <lem/polynomial.h>
 #include <lem/vector.h>
 #include <lem/qarray.h>
 #include <lem/math/math.h>

 namespace lem
 {
  namespace Math
  {

   /**************************************************************************
    Функции Бесселя.


    ЛИТЕРАТУРА:
               1. Андре Анго "Математика для радио- и электроинженеров",
                  -М.:"Наука", 1965, глава 7, п.5, стр. 373.

    ИСТОРИЧЕСКАЯ СПРАВКА:

     "Впервые J0 была получена Даниелем Бернулли в 1732 году при изучении
      колебаний однородной тяжелой нити. /.../ современное название и
      подробное описание обширное семейство бесселевых функций получило
      лишь много времени спустя, ибо только в 1824 году Бессель, исследуя
      вопросы, связанные с возмущенем движения планет, детально изучил
      свойства этих функций." - там же, глава 7, стр. 405-406.
   ***************************************************************************/

   REAL BessJ( int n, REAL x, REAL EPS=MACHEPS );
   REAL BessI( int n, REAL x, REAL EPS=MACHEPS );
   REAL BessY( int N, REAL x );
   REAL BessK( int N, REAL x );

   REAL BessY0_nag( REAL X );
   REAL BessY1_nag( REAL X );
   REAL BessJ0_nag( REAL X );
   REAL BessJ1_nag( REAL X );
   REAL BessK0_nag( REAL x );
   REAL BessK1_nag( REAL x );
   REAL BessI0_nag( REAL X );
   REAL BessI1_nag( REAL X );
 
   REAL BessIhalf( REAL n, REAL x );

   REAL besselJ0( REAL x, REAL eps=MACHEPS );
 
   REAL ber_nag( REAL X );
   REAL bei_nag( REAL X );
   REAL ker_nag( REAL X );
   REAL kei_nag( REAL X );

   // #################################################
   // 
   //       Интегральные показательные функциии.
   //

   REAL E1_nag( REAL X );
   REAL E1_fun( REAL x, REAL EPS=MACHEPS*8 );

   // 1. 3-го порядка, по разложению в ряд.
   REAL E3_fun( REAL x );

   // Произвольного порядка n,по разложению в ряд.
   //
   // x - аргумент.
   // n - показатель.
   // EPS - требуемая точность.
   REAL En_fun( REAL x, REAL n, REAL EPS=1e-5 );

   // -----------------------------------




   /*
                      Гамма-функция Эйлера.

    x - аргумент.
 
    Если требуемая точность менее, чем 1e-3, то расчет производится по разложению
    в ряд ( но очень грубо ).

    Если задать точность лучше, чем 1e-3, то расчет будет вестись численным
    интегрированием. В этом случае параметр NN играет роль числа интервалов
    разбиения. Так как интеграл для гамма-функции несобственный, то итерационным
    методом будет произведен подбор верхнего предела так, чтобы подинтегральное
    выражение было меньше EPS.
   */

   REAL Gamma_fun( REAL x, REAL EPS=1.e-3, int NN=10 );

   REAL Gamma_nag( REAL x );
   REAL LNGamma( REAL X );


   /*
             Интегральные синус и косинус.
  
    Если qabs(x)<10, то используется степенной ряд, который достаточно быстро
    сходится. Иначе используется численное интегрирование.

    Параметр EPS имеет смысл только для приближения степенным рядом.

    Для интегрирования NN определяет число подинтервалов на каждый период
    функции sin.
   */

   REAL ISin( REAL x, REAL EPS=1.e-3, int NN=1 );
   REAL ICos( REAL x, REAL EPS=1.e-3, int NN=1 );

   REAL Si_nag( REAL X );
   REAL Ci_nag( REAL X );


   REAL Ai_fun( REAL X );
   REAL Bi_fun( REAL X );
   REAL Ai_prime( REAL X );
   REAL Bi_prime( REAL X );

   REAL erf_series( REAL x, REAL eps=MACHEPS );
   REAL Erf( REAL x );
   REAL Erf_nag( REAL X );
   REAL Erfc_nag( REAL X );

   REAL Chi2_nag( REAL X, int N );
   REAL GetSafeRange(void);
   REAL CumNormDistrib( REAL X );

   REAL Chebyshev_Tncos( int n, REAL x );
   REAL Chebyshev_Tn( int n, REAL x );
   const RPolynome Build_Tn( int n );
   const RVector Chebyshev_Tnz( int n );

   REAL Chebyshev_Uncos( int n, REAL x );
   REAL Chebyshev_Un( int n, REAL x );
   const RPolynome Build_Un( int n );
   const RVector Chebyshev_Unz( int n );

   REAL BernuliNumber( int n );

   REAL Hermit_Hn( int n, REAL x );
   const RPolynome Build_Hn( int n );

   const IntArray BuildChebSeq( int p );
   const RArray BuildTauSeq( const IntArray &THETA, REAL gamma1, REAL gamma2 );

  } // namespace Math 
 } // namespace lem

#endif
// ------------------------ End Of File [SPECIFUN.H] ---------------------------