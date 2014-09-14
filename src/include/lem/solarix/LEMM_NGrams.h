#if !defined LEMM_NGRAMS__H
#define LEMM_NGRAMS__H

#include <lem/tuple.h>

namespace Solarix
{
 struct LEMM_Ngram2
 {
  std::pair<int,int> tags;
  lem::int32_t freq;
 };

 inline bool operator<( const LEMM_Ngram2 & x, const LEMM_Ngram2 & y ) { return x.tags < y.tags; }


 struct LEMM_Ngram3
 {
  lem::triple<int,int,int> tags;
  lem::int32_t freq;
 };

 inline bool operator<( const LEMM_Ngram3 & x, const LEMM_Ngram3 & y ) { return x.tags < y.tags; }


 struct LEMM_Ngram4
 {
  lem::foursome<int,int,int,int> tags;
  lem::int32_t freq;
 };

 inline bool operator<( const LEMM_Ngram4 & x, const LEMM_Ngram4 & y ) { return x.tags < y.tags; }
}

#endif
