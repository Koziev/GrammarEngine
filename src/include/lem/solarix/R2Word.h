#if !defined RECO2_RWord__H
 #define RECO2_RWord__H

 namespace Reco2
 {
  struct RWord
  {
   int id_word;
   int distance;
   int id_transform;

   RWord(void) : id_word(-1), distance(0), id_transform(-1) {}
  };
 }

#endif
