#include <lem/WideStringUcs4.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SG_Language.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/SyllabRule.h>

using namespace Solarix;


SyllabContext::SyllabContext( GraphGram &alphabet, const lem::UCString &word, int id_language )
{
 LEM_CHECKIT_Z( id_language!=UNKNOWN );

 const SG_Language &lang = alphabet.GetDict().GetSynGram().languages()[ id_language ];
 const lem::MCollect<int> & id_alphabets = lang.GetAlphabets();

 points.push_back( new SyllabContextLeftBoundary() );

 // Разбираем исходное слово по символам, каждый символ ищем в алфавите и создаем по результатам одну точку контекста 
 lem::WideStringUcs4 ucs4( word.c_str() );
 lem::uint32_t c;
 while( (c=ucs4.Fetch())!=0 )
  {
   const Word_Coord wc = alphabet.entries().FindSymbol( c, id_alphabets );
   if( wc.IsUnknown() )
    {
     SyllabContextUnknownSymbol *point = new SyllabContextUnknownSymbol(c);
     points.push_back(point);
    }
   else
    {
     const GG_Entry &e = alphabet.entries()[ wc.GetEntry() ];
     const int id_class = e.GetClass();

     const GG_EntryForm & f = e.forms()[ wc.GetForm() ];
     lem::MCollect<GramCoordPair> coords = f.dims();
     for( lem::Container::size_type k=0; k<e.attrs().size(); ++k )
      coords.push_back( e.attrs()[k] );

     SyllabContextSymbol *point = new SyllabContextSymbol( c, e.GetName(), wc.GetEntry(), id_class, coords );
     points.push_back(point);
    }
  }

 points.push_back( new SyllabContextRightBoundary() );

 return;
}


void SyllabContext::GetResultSyllabs( lem::MCollect<lem::UCString> & result_syllabs, bool Normalized ) const
{
 for( lem::Container::size_type i=0; i<points.size(); ++i )
  {
   const SyllabContextPoint * p = points[i];
   if( p->IsLeftBoundary() || p->IsRightBoundary() )
    continue;
   
   result_syllabs.push_back( p->BuildSyllab(Normalized) );
  }

 return;
}



SyllabContextPoint* SyllabContext::ExtractPoint( int index )
{
 SyllabContextPoint * point = points[index];
 points[index] = NULL;
 return point;
}



void SyllabContext::Replace( int start_index, int count, lem::MCollect<SyllabContextPoint*> & new_points )
{
 for( int n=0; n<count; ++n )
  points.Remove( start_index );

 for( lem::Container::size_type i=0; i<new_points.size(); ++i )
  {
   const int new_index = start_index + CastSizeToInt(i);
   if( new_index == Count() )
    points.push_back( new_points[i] );
   else
    points.Insert( new_index, new_points[i] );
  }

 return;
}



void SyllabContext::Apply( const SyllabRulesForLanguage & rules, LA_RecognitionTrace *trace )
{
 const int min_len = rules.GetMinLen();
 const int max_len = rules.GetMaxLen();

 int cursor_pos=0;

 while( cursor_pos < Count() )
  {
   const int tail_size = Count()-cursor_pos;
   const int max_ctx_len = std::min( tail_size, max_len );

   bool hit=false;
   for( int ctx_len=max_ctx_len; ctx_len>=min_len; --ctx_len )
    {
     std::pair<SyllabRulesForLanguage::LEN2RULES_IT,SyllabRulesForLanguage::LEN2RULES_IT> it_range = rules.GetRulesForContextLen( ctx_len );
     for( SyllabRulesForLanguage::LEN2RULES_IT it=it_range.first; it!=it_range.second; ++it )
      {
       const SyllabRule & rule = *it->second;

/*
#if LEM_DEBUGGING==1
if( ctx_len==3 && cursor_pos==2 && rule.GetName().eqi(L"SYLLABER_7") )
 {
  lem::mout->eol();

  for( int k=0; k<Count(); ++k )
   lem::mout->printf( "%us ", GetPoint(k).BuildSyllab(false).c_str() );

  lem::mout->eol();
 }
#endif
*/

       if( rule.GetCondition().Check( *this, cursor_pos ) )
        {
         hit=true;

         if( trace!=NULL )
          {
           trace->SyllabicBreakRuleHit( *this, cursor_pos, rule );
          }

         lem::MCollect<SyllabContextPoint*> new_points;
         rule.GetResult().Produce( *this, cursor_pos, new_points );

         Replace( cursor_pos, ctx_len, new_points );

         cursor_pos += rule.GetResult().GetShift();

         if( trace!=NULL )
          {
           trace->SyllabicBreakRuleApplied( *this, cursor_pos, rule );
          }

         break;
        }
      }

     if( hit )
      break;
    }

   if( !hit )
    cursor_pos++;
  }

 return;
}



void SyllabContext::Print( lem::OFormatter &to ) const
{
 for( int k=0; k<Count(); ++k )
  {
   if(k>0) to.printf( ' ' );
   GetPoint(k).Print(to);
  }

 return;
}

