#if !defined Word2PointMatching__H
 #define Word2PointMatching__H

 namespace Reco2
 {
  struct Word2PointMatching
  {
   bool matches;
   int distance;
   int id_transform;
   float word_rel;

   Word2PointMatching(void) : matches(false), distance(-1), id_transform(-1), word_rel(-1.0F) {}

   Word2PointMatching( int d, int id_tr, float r ) : matches(true), distance(d), id_transform(id_tr), word_rel(r) {}
  };
 }
#endif


