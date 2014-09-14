// -----------------------------------------------------------------------------
// File STATKEEP.H
//
// (c) Koziev Elijah
//
// Content:
//  ласс дл€ простейшей статистической обработки последовательно вычисл€емых
// чисел, а также классы дл€ проверки статистических гипотез.
// -----------------------------------------------------------------------------
//
// CD->19.01.1996
// LC->04.09.2010
// --------------

#ifndef LEM_STAT_KEEPER__H
#define LEM_STAT_KEEPER__H
#pragma once

 #include <lem/math/real.h>

 #undef min
 #undef max

 namespace lem
 {
  class Stream;
  class OFormatter;

  namespace Math
  {

   class Statis
   {
    private:
     REAL amin, amax;
     REAL SUM, SUM2, SUM3, SUM4;
     long N;

    public:
     Statis(void);

     void add( REAL y );
     void add_ex( REAL y );

     inline void operator << ( const REAL y ) { add(y); }

     inline REAL min(void)  const { return amin; }
     inline REAL max(void)  const { return amax; }
     inline REAL Sum(void)  const { return SUM;  }
     inline REAL Sum2(void) const { return SUM2; }
  
     inline long GetN(void) const { return N;    }
 
     REAL M1(void)    const;
     REAL M2(void)    const;
     REAL m3(void)    const;
     REAL m4(void)    const;
     REAL M4(void)    const;
     REAL SIGMA(void) const;
     REAL KA(void)    const;
     REAL KE(void)    const;
     REAL Kv(void)    const;
   };

   class StatKeeper : public Statis
   {
    private:
     REAL amin, amax;
     REAL SUM, SUM2, SUM3, SUM4;
     long N;
 
    public:
     StatKeeper(void);
  
     void SaveBin( lem::Stream& bin ) const;
     void LoadBin( lem::Stream& bin );
   };

   extern void print( const Statis& sk, lem::OFormatter& rep );

   class DSignTest
   {
    private:
     long n,n_minus,n_plus;

    public:
     DSignTest(void) {n=n_minus=n_plus=0; }

     void add( REAL x, REAL y );
     REAL GetP(void) const;
   };

  } // namespace Math

 } // namespace lem

#endif
