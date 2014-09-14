#include <lem/solarix/LA_RecognitionRule.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/LA_RecognitionRules.h>

using namespace Solarix;


LA_RecognitionRules::LA_RecognitionRules( int _id_language, LexiconStorage *_storage )
 : id_language(_id_language), storage(_storage)
{
 LEM_CHECKIT_Z( storage!=NULL );
}


LA_RecognitionRules::~LA_RecognitionRules(void)
{
 for( lem::Container::size_type i=0; i<rules.size(); ++i )
  delete rules[i];
 
 return;
}


// Правило загружено из хранилища, сохраняем его в своем списке и обновляем
// дополнительные ускоряющие структуры.
void LA_RecognitionRules::Add( LA_RecognitionRule * rule )
{
 LEM_CHECKIT_Z( rule!=NULL );

 rules.push_back(rule);

 if( rule->IsAffix() )
  {
   if( rule->IsSyllab() )
    {
     syllab_affix_rules.insert( std::make_pair( rule->GetHash(), rule ) );
    }
   else
    {
     affix_rules.insert( std::make_pair( rule->GetHash(), rule ) );
    }
  }
 else if( rule->IsPrefix() )
  {
   if( rule->IsSyllab() )
    {
     syllab_prefix_rules.insert( std::make_pair( rule->GetHash(), rule ) );
    }
   else
    {
     prefix_rules.insert( std::make_pair( rule->GetHash(), rule ) );
    }
  }
 else if( rule->IsRegex() )
  {
   rx_rules.push_back(rule);
  }
 else
  {
   LEM_STOPIT;
  }
 
 return;
}


void LA_RecognitionRules::AddResult(
                                    const Solarix::Word_Coord &wc,
                                    lem::Real1 val,
                                    Solarix::LA_ProjectInfo *inf,
                                    lem::MCollect<Solarix::Word_Coord> &found_list,
                                    lem::MCollect<Solarix::ProjScore> &val_list,
                                    lem::PtrCollect<Solarix::LA_ProjectInfo> &inf_list
                                   ) const
{
 // Не допускаем внесения в результаты идентичных проекций.
 for( lem::Container::size_type i=0; i<found_list.size(); ++i )
  {
   if( found_list[i]==wc )
    {
     bool inf_matched=true;

     if( inf==NULL && inf_list[i]!=NULL )
      inf_matched=false;
     else if( inf!=NULL && inf_list[i]==NULL )
      inf_matched=false;
     else if( inf->coords!=inf_list[i]->coords )
      inf_matched=false;
       
     if( inf_matched )
      {
       delete inf;
       return;
      }
    }
  }

 found_list.push_back(wc);
 val_list.push_back(val);
 inf_list.push_back(inf);

 return;
}



bool LA_RecognitionRules::Apply(
                                const lem::UCString &word,
                                lem::Real1 word_rel,
                                lem::MCollect<Solarix::Word_Coord> &found_list,
                                lem::MCollect<Solarix::ProjScore> &val_list,
                                lem::PtrCollect<Solarix::LA_ProjectInfo> &inf_list,
                                LA_RecognitionTrace *trace
                               ) const
{
 bool matched=false;

 typedef RULES::const_iterator IT;

 // Правила, распознающие целые слова, не загружаем сразу из хранилища, так как они нужны очень редко.
 lem::Ptr<Solarix::LS_ResultSet> rs_words( storage->ListRecognitionRulesForWord( id_language, word ) );
 while( rs_words->Fetch() )
  {
   const int id_rule = rs_words->GetInt(0);
   lem::Ptr<LA_RecognitionRule> rule( storage->GetRecognitionRule(id_rule) );

   matched = true;

   LA_ProjectInfo *info = new LA_ProjectInfo();
   info->coords = rule->GetCoords();

   AddResult( Word_Coord( rule->GetEntryKey(), 0 ), word_rel*rule->GetRel(), info, found_list, val_list, inf_list );

   #if defined SOL_DEBUGGING
   if( trace!=NULL )
    {
     trace->Matched( word, &*rule );
    }
   #endif
  }

 if( !matched )
  {
   std::pair<IT,IT> pp = prefix_rules.equal_range( LA_RecognitionRule::CalcHash( word.c_str(), true, false ) );
   for( IT it=pp.first; it!=pp.second; ++it )
    {
     const LA_RecognitionRule *r = it->second;
     if( r->Match(word) )
      {
       matched = true;
 
       LA_ProjectInfo *info = new LA_ProjectInfo();
       info->coords = r->GetCoords();
 
       AddResult( Word_Coord( r->GetEntryKey(), 0 ), word_rel*r->GetRel(), info, found_list, val_list, inf_list );
 
       #if defined SOL_DEBUGGING
       if( trace!=NULL )
        {
         trace->Matched( word, r );
        }
       #endif
      }
    }
 
   pp = affix_rules.equal_range( LA_RecognitionRule::CalcHash( word.c_str(), false, true ) );
   for( IT it=pp.first; it!=pp.second; ++it )
    {
     const LA_RecognitionRule *r = it->second;
     if( r->Match(word) )
      {
       matched = true;
 
       LA_ProjectInfo *info = new LA_ProjectInfo();
       info->coords = r->GetCoords();
 
       AddResult( Word_Coord( r->GetEntryKey(), 0 ), word_rel*r->GetRel(), info, found_list, val_list, inf_list );
 
       #if defined SOL_DEBUGGING
       if( trace!=NULL )
        {
         trace->Matched( word, r );
        }
       #endif
      }
    }
   
   for( lem::Container::size_type i=0; i<rx_rules.size(); ++i )
    {
     const LA_RecognitionRule *r = rx_rules[i];
     if( r->Match(word) )
      {
       matched = true;
 
       LA_ProjectInfo *info = new LA_ProjectInfo();
       info->coords = r->GetCoords();
 
       AddResult( Word_Coord( r->GetEntryKey(), 0 ), word_rel*r->GetRel(), info, found_list, val_list, inf_list );
 
       #if defined SOL_DEBUGGING
       if( trace!=NULL )
        {
         trace->Matched( word, r );
        }
       #endif
      }
    }
  }

 return matched;
}



bool LA_RecognitionRules::ApplyForSyllabs(
                                          const lem::UCString &word,
                                          lem::Real1 word_rel,
                                          const lem::MCollect<lem::UCString> & syllabs,
                                          lem::MCollect<Solarix::Word_Coord> &found_list,
                                          lem::MCollect<Solarix::ProjScore> &val_list,
                                          lem::PtrCollect<Solarix::LA_ProjectInfo> &inf_list,
                                          LA_RecognitionTrace *trace
                                         ) const
{
 bool matched=false;

 typedef RULES::const_iterator IT;

 std::pair<IT,IT> pp = syllab_prefix_rules.equal_range( LA_RecognitionRule::CalcHash( syllabs.front().c_str(), true, false ) );
 for( IT it=pp.first; it!=pp.second; ++it )
  {
   const LA_RecognitionRule *r = it->second;
   if( r->Match(syllabs.front()) )
    {
     matched = true;

     LA_ProjectInfo *info = new LA_ProjectInfo();
     info->coords = r->GetCoords();

     AddResult( Word_Coord( r->GetEntryKey(), 0 ), word_rel*r->GetRel(), info, found_list, val_list, inf_list );

     #if defined SOL_DEBUGGING
     if( trace!=NULL )
      {
       trace->MatchedSyllable( word, syllabs.front(), r );
      }
     #endif
    }
  }

 pp = syllab_affix_rules.equal_range( LA_RecognitionRule::CalcHash( syllabs.back().c_str(), false, true ) );
 for( IT it=pp.first; it!=pp.second; ++it )
  {
   const LA_RecognitionRule *r = it->second;
   if( r->Match(syllabs.back()) )
    {
     matched = true;

     LA_ProjectInfo *info = new LA_ProjectInfo();
     info->coords = r->GetCoords();

     AddResult( Word_Coord( r->GetEntryKey(), 0 ), word_rel*r->GetRel(), info, found_list, val_list, inf_list );

     #if defined SOL_DEBUGGING
     if( trace!=NULL )
      {
       trace->MatchedSyllable( word, syllabs.back(), r );
      }
     #endif
    }
  }
 
 return matched;
}
