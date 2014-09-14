// -----------------------------------------------------------------------------
// File LEM_HIST.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
//  ласс Histogramma - контейнер дл€ работы с частотными таблицами.
// -----------------------------------------------------------------------------
//
// CD->05.05.1996
// LC->07.04.2007
// --------------

#ifndef LEM_HISTO__H
#define LEM_HISTO__H
#pragma once

 #include <lem/math/real.h>
 #include <lem/math/real_functions.h>
 #include <lem/qarray.h>

 namespace lem
 {
 class OFormatter;

 class Histogramma
 {
  private:
   lem::Math::REAL HISTO_A, HISTO_B, dhisto; // Bounds and step
   int HISTO_N; // Number of intervals
   RArray histo; // Accumulated statistics for intervals

  public:
   Histogramma(void);
   Histogramma( lem::Math::REAL a, lem::Math::REAL b, int n );
   Histogramma( const Histogramma& h );

   Histogramma& operator=( const Histogramma& h );

   inline lem::Math::REAL& operator[]( int i ) { return histo[i]; }
   inline lem::Math::REAL operator[]( int i ) const { return histo[i]; }

   inline lem::Math::REAL GetX( int i ) const { return HISTO_A + dhisto*i; }
   inline lem::Math::REAL GetDX(void) const { return dhisto; }
   inline const RArray& array(void) const { return histo; }
   inline RArray* GetRArrayPtr(void) { return &histo; }
   inline int size(void) const { return CastSizeToInt(histo.size()); }

   inline lem::Math::REAL back(void) const { return histo.back(); }
   inline lem::Math::REAL& back(void) { return histo.back(); }

   inline lem::Math::REAL GetFromX(void) const { return HISTO_A; }
   inline lem::Math::REAL GetToX(void) const { return HISTO_B; }

   int GetIndex( lem::Math::REAL x ) const;

   // ***********************************
   // Register the event with weight==1
   // ***********************************
   void Add( lem::Math::REAL x );
   inline void operator << ( const lem::Math::REAL x ) { Add(x); }

   // ***********************************
   // Register the event with any specified weight <v>
   // ***********************************
   void Add( lem::Math::REAL x, lem::Math::REAL v );

   void Set( lem::Math::REAL x, lem::Math::REAL v );

   void prime( int prime_order=1, int nnode=3 );
   lem::Math::REAL integral(void) const;
   lem::Math::REAL sum_y(void) const;

   lem::Math::REAL GetM1(void) const;

   void Normalize(void);
 };



 extern void report( const Histogramma &hist, OFormatter& rep );
 extern void picture(
                     const Histogramma &hist,
                     OFormatter& rep,
                     int AMPLITUDE,
                     int NTIMEMARKS
                    );
 extern void save_data( const Histogramma &hist, OFormatter& rep );


 inline void Histogramma::Add( lem::Math::REAL x )
 {
  const int id = lem::Math::qroundi( (x-HISTO_A)/dhisto+TOREAL(0.5) );
  if( id>=0 && id<HISTO_N )
   histo[id]++;

  return;
 }

 inline void Histogramma::Add( lem::Math::REAL x, lem::Math::REAL v )
 {
  const int id = lem::Math::qroundi( (x-HISTO_A)/dhisto+TOREAL(0.5) );
  if( id>=0 && id<HISTO_N )
   histo[id]+=v;

  return;
 }


  #if !defined LEM_NOREAL
  class OFormatter;
  extern void print(
                    const RArray& GISTO,
                    lem::Math::REAL GISTO_A,
                    lem::Math::REAL GISTO_B,
                    int AMPLITUDE,
                    int NTIMEMARKS,
                    OFormatter& rep
                   );
  #endif

 } // namespace 'lem'

#endif
// --------------------------- End Of File [LEM_HIST.H] ------------------------
