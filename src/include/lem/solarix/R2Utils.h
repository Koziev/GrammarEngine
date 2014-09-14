#if !defined RECO2_UTILS__H
 #define RECO2_UTILS__H

 #include <lem/containers.h>

 namespace Reco2
 {
  typedef lem::MCollect<int> ints;
  typedef lem::MCollect<float> floats;

  extern float DistanceToFloat( int distance );
  extern float WeightToFloat( int weight );
  extern void Intersect( const std::set<int> & a, const std::set<int> & b, std::set<int> & res );
  extern void Union( const std::set<int> & a, std::set<int> & b );
 }

#endif
