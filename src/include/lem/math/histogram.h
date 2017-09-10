#ifndef LEM_HISTO__H
#define LEM_HISTO__H
#pragma once

//#include <lem/math/real.h>
// #include <lem/math/real_functions.h>
 #include <lem/qarray.h>

 namespace lem
 {
 class OFormatter;

 class Histogramma
 {
  private:
   double HISTO_A, HISTO_B, dhisto; // Bounds and step
   int HISTO_N; // Number of intervals
   RArray histo; // Accumulated statistics for intervals

  public:
   Histogramma(void);
   Histogramma( double a, double b, int n );
   Histogramma( const Histogramma& h );

   Histogramma& operator=( const Histogramma& h );

   inline double& operator[]( int i ) { return histo[i]; }
   inline double operator[]( int i ) const { return histo[i]; }

   inline double GetX( int i ) const { return HISTO_A + dhisto*i; }
   inline double GetDX(void) const { return dhisto; }
   inline const RArray& array(void) const { return histo; }
   inline RArray* GetRArrayPtr(void) { return &histo; }
   inline int size(void) const { return CastSizeToInt(histo.size()); }

   inline double back(void) const { return histo.back(); }
   inline double& back(void) { return histo.back(); }

   inline double GetFromX(void) const { return HISTO_A; }
   inline double GetToX(void) const { return HISTO_B; }

   int GetIndex( double x ) const;

   // ***********************************
   // Register the event with weight==1
   // ***********************************
   void Add( double x );
   inline void operator << ( const double x ) { Add(x); }

   // ***********************************
   // Register the event with any specified weight <v>
   // ***********************************
   void Add( double x, double v );

   void Set( double x, double v );

   //void prime( int prime_order=1, int nnode=3 );
   double integral(void) const;
   double sum_y(void) const;

   double GetM1(void) const;

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


 inline void Histogramma::Add( double x )
 {
  const int id = int( (x-HISTO_A)/dhisto+0.5 );
  if( id>=0 && id<HISTO_N )
   histo[id]++;

  return;
 }

 inline void Histogramma::Add( double x, double v )
 {
  const int id = int( (x-HISTO_A)/dhisto+0.5 );
  if( id>=0 && id<HISTO_N )
   histo[id]+=v;

  return;
 }


  class OFormatter;
  extern void print(
                    const RArray& GISTO,
                    double GISTO_A,
                    double GISTO_B,
                    int AMPLITUDE,
                    int NTIMEMARKS,
                    OFormatter& rep
                   );

 } // namespace 'lem'

#endif
