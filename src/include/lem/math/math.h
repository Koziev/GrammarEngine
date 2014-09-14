// -----------------------------------------------------------------------------
// File MATH.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia
//
// Content:
// Математическая Библиотека для C++. Полностью совместима с ANSI Cfront 2.0,
// несовместимость при наличии таковой особо отмечается, либо происходит
// автоматическая настройка с помощью препроцессорных директив.
// -----------------------------------------------------------------------------
//
// CD->01.12.1994
// LC->27.04.2007
// --------------

#if !defined( LEM_MATH__H ) && !defined( LEM_NOREAL )
#define LEM_MATH__H
#pragma once

 #include <cmath>

 #include <lem/math/math_constants.h>
 #include <lem/math/real_functions.h>
 #include <lem/macros.h>

 #define _ZERO_  TOREAL(0.)
 #define _ONE_  TOREAL(1.)

 namespace lem
 {
  class OFormatter;

  namespace Math
  {

  REAL QPOW( REAL x, int n );
  REAL QPOW( REAL x, REAL n );

 // ------------------------------
 // Returns the signum of argument
 //
 //            / -1, if x<0.
 // signum(x)=|
 //            \  1, if x>0.
 //
 inline REAL lem_signum( REAL x )
 {
  if(x>=_ZERO_) return _ONE_;
  return -_ONE_;
 }

 inline int lem_isignum( REAL x )
 {
  if(x>=_ZERO_) return 1;
  return -1;
 }

 inline REAL lem_sign( REAL x )
 {
  if(x>_ZERO_) return _ONE_;
  if(x<_ZERO_) return -_ONE_;
  return _ZERO_;
 }

 inline REAL qsign( REAL x )
 {
  if(x>_ZERO_) return _ONE_;
  if(x<_ZERO_) return -_ONE_;
  return _ZERO_;
 }
 // ------------------------------


 // Фортрановская заморочка.
 inline REAL qsign( REAL y, REAL x ) { return x>=_ZERO_ ? y : -y; }

 // Возвращает проценты отличия величины yprec от y.
 // Корректно обрабатывает ситуацию yprec=0.
 inline REAL qerr( REAL yprec, REAL y )
 {
  return yprec==_ZERO_ ?
                    qabs(y)*100.
                    :
                    qabs((yprec-y)/yprec)*100.;
 }

 // ----------------------------
 // Быстрая экспонента - в
 // диапазоне 0...1 погрешность
 // менее 0.5e-5.
 inline REAL4 Exp( REAL4 x )
 {
  const REAL4 xx=x*x;

  const REAL4 P = REAL4(12.*xx+120.);
  const REAL4 Q = REAL4( x*(xx+60.) );

  return (P+Q)/(P-Q);
 }

 /*
   Аппроксимация exp(x) для диапазона:  0<=|x|<=ln2, x<=0.
   погрешность < 3e-3.

   ИСТОЧНИК: Абрамовиц, Стиган, "Справочник по специальным функциям", стр.36.

   ЗАМЕЧАНИЯ: Примерно в 16 раз шустрее на 486, нежели стандартная exp.
 */
 inline REAL4 exp3( REAL4 x )
 {
  return 1.F-x*(-0.9664F-0.3536F*x);
 }


 /*
   Аппроксимация exp(x) для диапазона:  0<=|x|<=ln2, x<=0.
   погрешность < 3e-5.

   ИСТОЧНИК: Абрамовиц, Стиган, "Справочник по специальным функциям", стр.36.

   ЗАМЕЧАНИЯ: Примерно в 4 раза шустрее на 486, нежели стандартная exp.
 */
 inline REAL4 exp5( REAL4 x )
 {
  return (((0.0293641F*x-0.1595332F)*x+0.4982926F)*x+0.9998684F)*x+1.F;
 }



 /*
   Аппроксимация exp(x) для диапазона:  0<=|x|<=ln2, x<=0.
   погрешность < 2e-10.

   ИСТОЧНИК: Абрамовиц, Стиган, "Справочник по специальным функциям", стр.37.

   ЗАМЕЧАНИЯ: Примерно в 2 раза шустрее на 486, нежели стандартная exp.
 */
 inline REAL8 exp7( REAL8 x )
 {
  return ((((((0.0001413161*x+0.0013298820)*x+0.0083013598)*x+0.0416573475)*x+0.1666653019)*x+0.4999999206)*x+0.9999999995)*x+1.;
 }


 /*
   Аппроксимация exp10(x) для диапазона:  0<=x<=1.
   погрешность < 7e-4.

   ИСТОЧНИК: Абрамовиц, Стиган, "Справочник по специальным функциям", стр.37.

   ЗАМЕЧАНИЯ: Примерно в 10 раза шустрее на 486, нежели стандартная pow(10,x).
 */
 inline REAL4 exp10_4( REAL4 x )
 {
  return Fpow2((((0.1268089F*x+0.2080030F)*x+0.6774323F)*x+1.1499196F)*x+1.F);
 }

 /*
   Аппроксимация exp10(x) для диапазона:  0<=x<=1.
   погрешность < 5e-8.

   ИСТОЧНИК: Абрамовиц, Стиган, "Справочник по специальным функциям", стр.37.

   ЗАМЕЧАНИЯ: Примерно в 6 раза шустрее на 486, нежели стандартная pow(10,x)
 */
 inline REAL8 exp10_8( REAL8 x )
 {
  return Fpow2( (REAL4) (((((((0.00093264267*x+0.00255491796)*x+0.01742111988)*x+0.07295173666)*x+0.25439357484)*x+0.66273088429)*x+1.15129277603)*x+1.) );
 }

 // ----------------------
 // Формулы комбинаторики.
 // ----------------------

 REAL factorial( int n );   // Обычный факториал n!
 REAL NFF_fun( int x );         // Функция x!!
 REAL Axy_fun( int x, int y );  // Число размещений из y элементов по x
 REAL Cxy_fun( int x, int y );  // Число сочетаний из y элементов по x

 REAL nstirling_fun( int n );   // Факториал по формуле Стирлинга

 extern const REAL MACHEPS;
 REAL compute_mach_eps(void);
 int get_mach_bits(void);
 REAL get_epsilon( REAL x );

 // Одна из аппроксимаций дельта-функции, через производную
 // интеграла ошибок.
 REAL deltafun1( REAL x, REAL alfa );

   inline REAL qpow10( REAL x ) { return QPOW(10.0,x); }

  } // namespaxce Math
 } // namespace 'lem'

#endif
