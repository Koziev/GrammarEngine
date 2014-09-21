// -----------------------------------------------------------------------------
// File IMB_MATH.H
//
// (c) Koziev Elijah
//
// Content:
// Вспомогательная математика для графического пакета RUBIN.
// -----------------------------------------------------------------------------
//
// CD->01.12.1994
// LC->07.03.2010
// --------------

#if !defined( IMB_MATH__H ) && !defined( LEM_NOREAL )
 #define IMB_MATH__H

 #include <lem/math/real_functions.h>
 #include <lem/minmax.h>

 namespace lem
 {
  namespace Math
  {
   using lem::Math::qabs;

   // Константы, ответственные за обход расчетных
   // погрешностей алгоритма.
   const REAL imb_eps_     = 1.e-5;
   const REAL imb_meps_    = -imb_eps_;
   const REAL imb_oneplus  = 1.+imb_eps_;
   const REAL imb_oneminus = 1.-imb_eps_;

   // -------------------------------------------------------------------------
   // "Обратное" округление. Если аргумент по модулю меньше константы точности
   // _eps_, то результат - значение _eps_. В противном случае аргумент
   // возвращается без изменений. Функция используется для коррекции делителя,
   // когда существует опасность деления на ноль.
   // -------------------------------------------------------------------------
   inline REAL imb_minBound( const REAL x )
   {
    const REAL y = max( imb_eps_, qabs(x) );
    return x<0. ? -y : y;
   }

   // --------------------------
   // Числа, лежащие в пределах
   // [-_eps_,+_eps_] округляются
   // до 0.
   // --------------------------
   inline REAL imb_Zround( const REAL x )
   { return qabs(x)<imb_eps_ ? TOREAL(0.) : x; }

   inline bool imb_is_Z( const REAL x )
   { return qabs(x)<imb_eps_; }

  }

 } // namespace lem

#endif
