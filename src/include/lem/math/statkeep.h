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
     double amin, amax;
     double SUM, SUM2, SUM3, SUM4;
     long N;

    public:
     Statis(void);

     void add( double y );
     void add_ex( double y );

     inline void operator << ( const double y ) { add(y); }

     inline double min(void)  const { return amin; }
     inline double max(void)  const { return amax; }
     inline double Sum(void)  const { return SUM;  }
     inline double Sum2(void) const { return SUM2; }
  
     inline long GetN(void) const { return N;    }
 
     double M1(void)    const;
     double M2(void)    const;
     double m3(void)    const;
     double m4(void)    const;
     double M4(void)    const;
     double SIGMA(void) const;
     double KA(void)    const;
     double KE(void)    const;
     double Kv(void)    const;
   };

   class StatKeeper : public Statis
   {
    private:
     double amin, amax;
     double SUM, SUM2, SUM3, SUM4;
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

     void add( double x, double y );
     double GetP(void) const;
   };

  } // namespace Math

 } // namespace lem

#endif
