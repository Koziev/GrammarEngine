#if !defined PatternOptionalPoints__H
#define PatternOptionalPoints__H

#include <lem/containers.h>

namespace Solarix
{
 class SynPatternPoint;
 class PatternOptionalPoints
 {
  private:
   lem::MCollect<SynPatternPoint*> points;

  public:
   PatternOptionalPoints() {}
   PatternOptionalPoints( const PatternOptionalPoints & x );
   ~PatternOptionalPoints();

   void operator=( const PatternOptionalPoints & x );

   bool operator!=( const PatternOptionalPoints & x ) const;
  
   void add( SynPatternPoint * x ) { points.push_back(x); }
   bool empty() const { return points.empty(); }

   void SaveBin( lem::Stream & bin ) const;
   void LoadBin( lem::Stream & bin );
 };
}

#endif
