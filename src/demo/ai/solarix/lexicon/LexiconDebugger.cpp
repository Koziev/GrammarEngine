#include <lem/solarix/LA_RecognitionRule.h>
#include <lem/solarix/LA_CropRule.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/SyllabRule.h>
#include <lem/solarix/PartOfSpeech.h>

#include "lexicon.h"

using namespace Solarix;
using namespace lem;

void LexiconDebugger::CropRuleApplied(
                                      const lem::UCString &word_before,
                                      const lem::UCString &word_after,
                                      const LA_CropRule *rule
                                     )
{
 if( trace )
  mout->printf( "Crop rule %vfA%us%vn has been applied: %vfE%us%vn -> %vfE%us%vn\n", rule->GetName().c_str(), word_before.c_str(), word_after.c_str() );

 return;
}


void LexiconDebugger::Matched( const lem::UCString &word, const LA_RecognitionRule *rule )
{
 if( trace )
  {
   mout->printf( "Recognition rule %vfA%us%vn has been applied for %vfE%us%vn rel=%vf9%4.2rf%vn", rule->GetName().c_str(), word.c_str(), rule->GetRel().GetFloat() );

   const Solarix::SG_Entry &e = dict->GetSynGram().GetEntry( rule->GetEntryKey() );
   const int id_class = e.GetClass();
   mout->printf( " %us:%us ", dict->GetSynGram().GetClass(id_class).GetName().c_str(), e.GetName().c_str() );
   rule->GetCoords().SaveTxt( *mout, dict->GetSynGram() );
   mout->printf( "\n" );
  }

 return;
}


void LexiconDebugger::MatchedSyllable( const lem::UCString &word, const lem::UCString &syllable, const LA_RecognitionRule *rule )
{
 if( trace )
  {
   mout->printf( "Recognition rule %vfA%us%vn has been applied for syllable %vfE%us%vn in word %vfE%us%vn rel=%vf9%4.2rf%vn"
    , rule->GetName().c_str(), syllable.c_str(), word.c_str(), rule->GetRel().GetFloat() );

   const Solarix::SG_Entry &e = dict->GetSynGram().GetEntry( rule->GetEntryKey() );
   const int id_class = e.GetClass();
   mout->printf( " %us:%us ", dict->GetSynGram().GetClass(id_class).GetName().c_str(), e.GetName().c_str() );
   rule->GetCoords().SaveTxt( *mout, dict->GetSynGram() );
   mout->printf( "\n" );
  }

 return;
}


void LexiconDebugger::PhoneticRuleProduction( const lem::UCString &source, const lem::UCString &result, lem::Real1 val, const LA_PhoneticRule *rule )
{
 if( trace )
  {
   mout->printf( "Phonetic rule %vfA%us%vn has been applied: %vfE%us%vn -> %vfE%us%vn  rel=%vf9%4.2rf%vn\n",
    rule->GetName().c_str(), source.c_str(), result.c_str(), val.GetFloat() );
  }

 return;
}


void LexiconDebugger::WordSyllabs( const lem::UCString &word, const lem::MCollect<lem::UCString> &slb_list )
{
 if( trace )
  {
   mout->printf( "Word %vfE%us%vn has been split to syllables:", word.c_str() );

   for( int i=0; i<slb_list.size(); i++ )
    lem::mout->printf( " %us", slb_list[i].c_str() );

   mout->eol();
  }

 return;
}



void LexiconDebugger::SyllabicBreakRuleHit(
                                           const SyllabContext & context,
                                           int cursor_pos,
                                           const SyllabRule & rule
                                          )
{
 mout->printf( "Syllabic break rule %vfE%us%vn; context:\n", rule.GetName().c_str() );
 context.Print(*mout);
 mout->printf("\n\n");
 return;
}


void LexiconDebugger::SyllabicBreakRuleApplied(
                                               const SyllabContext & context,
                                               int cursor_pos,
                                               const SyllabRule & rule
                                              )
{
 mout->printf( "result context:\n" );
 context.Print(*mout);
 mout->printf("\n\n");
 return;
}

