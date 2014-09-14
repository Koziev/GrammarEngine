#include <lem/solarix/SynPattern.h>
#include <lem/solarix/PatternOptionalPoints.h>

using namespace Solarix;


PatternOptionalPoints::PatternOptionalPoints( const PatternOptionalPoints & x )
{
 for( lem::Container::size_type i=0; i<x.points.size(); ++i )
  points.push_back( new SynPatternPoint( * x.points[i] ) );
}


void PatternOptionalPoints::operator=( const PatternOptionalPoints & x )
{
 for( lem::Container::size_type i=0; i<points.size(); ++i )
  delete points[i];
 points.clear();
 
 for( lem::Container::size_type i=0; i<x.points.size(); ++i )
  points.push_back( new SynPatternPoint( * x.points[i] ) );

 return;
}



PatternOptionalPoints::~PatternOptionalPoints()
{
 for( lem::Container::size_type i=0; i<points.size(); ++i )
  delete points[i];
}


bool PatternOptionalPoints::operator!=( const PatternOptionalPoints & x ) const
{
 if( points.size()!=x.points.size() )
  return false;
 
 for( lem::Container::size_type i=0; i<points.size(); ++i )
  if( !points[i]->Equal( *x.points[i] ) )
   return false;

 return true;
}


void PatternOptionalPoints::SaveBin( lem::Stream & bin ) const
{
 #if defined SOL_SAVEBIN
 bin.write_int( points.size() );
 for( lem::Container::size_type i=0; i<points.size(); ++i )
  points[i]->SaveBin(bin);
 #endif
 return;
}


void PatternOptionalPoints::LoadBin( lem::Stream & bin )
{
 int n = bin.read_int();
 for( int i=0; i<n; ++i )
  {
   SynPatternPoint * p = new SynPatternPoint();
   p->LoadBin(bin);
   points.push_back(p);
  }

 return;
}
