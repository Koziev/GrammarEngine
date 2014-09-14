#if !defined RECO2_PatternMatching__H
 #define RECO2_PatternMatching__H

 namespace Reco2
 {
  struct PatternMatching
  {
   int nhit; // сколько фактов совпадения слов учтено в rel
   float rel;
   int match_len; // сколько слов исходного контекста сопоставлено

   PatternMatching(void) : nhit(0), rel(1.0F), match_len(0) {}

   void Merge( PatternMatching *src, float rel_factor, int matched_len2 )
   {
    rel *= (src->rel*rel_factor);
    nhit += src->nhit;
    match_len += matched_len2;
   }
  };
 }

#endif
