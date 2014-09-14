#if !defined LEMM_Compiler__H && defined SOL_LOADTXT
#define LEMM_Compiler__H

#include <algorithm>
#include <lem/noncopyable.h>
#include <lem/integer.h>
#include <lem/containers.h>
#include <lem/solarix/LEMM_NGrams.h>

namespace lem
{
 namespace Iridium
 {
  class Macro_Parser;
 }
}

namespace Solarix
{
 class Dictionary;

 class LEMM_Compiler : lem::NonCopyable
 {
  private:
   int suffix_len;
   lem::MCollect< std::pair<lem::int32_t,lem::UCString> > suffices, words;
   lem::MCollect<LEMM_Ngram2> ngram2, ngram2_1;
   lem::MCollect<LEMM_Ngram3> ngram3, ngram3_1, ngram3_2;
   lem::MCollect<LEMM_Ngram4> ngram4;

   void LoadNGram( lem::Iridium::Macro_Parser & txtfile, Dictionary & dict, lem::MCollect<int> & terms, int order ) const;

  public:
   LEMM_Compiler();
   ~LEMM_Compiler();
   
   void LoadTxt( lem::Iridium::Macro_Parser & txtfile, Dictionary & dict );
   void Prepare();
   void SaveBin( lem::Stream & bin ) const;
   void PrintModelInfo( lem::OFormatter & out ) const;
 };

}


#endif
