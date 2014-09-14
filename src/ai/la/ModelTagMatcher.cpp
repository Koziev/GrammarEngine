#include <lem/quantors.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/MorphologyModels.h>


using namespace Solarix;

ModelTagMatcher::ModelTagMatcher() : id(UNKNOWN)
{}


void ModelTagMatcher::LoadBin( lem::Stream & bin )
{
 bin.read( &id, sizeof(id) );

 ModelCodeBook::LoadUtf8( bin, lexeme );

 lem::int32_t n_lemma;
 bin.read( &n_lemma, sizeof(n_lemma) );
 for( int i=0; i<n_lemma; ++i )
  {
   lem::int32_t e;
   bin.read( &e, sizeof(e) );
   id_lemma.push_back(e);
  }

 lem::int32_t n_pos;
 bin.read( &n_pos, sizeof(n_pos) );
 for( int i=0; i<n_pos; ++i )
  {
   lem::int32_t p;
   bin.read( &p, sizeof(p) );
   pos.push_back(p);
  }

 lem::int32_t n_pair;
 bin.read( &n_pair, sizeof(n_pair) );
 for( int i=0; i<n_pair; ++i )
  {
   lem::int32_t coord_id, state_id;
   bin.read( &coord_id, sizeof(coord_id) );
   bin.read( &state_id, sizeof(state_id) );
   pairs.push_back( Solarix::GramCoordPair( coord_id, state_id ) );
  }

 return;
}


bool ModelTagMatcher::Match( const Word_Form & wf, Solarix::Dictionary & dict ) const
{
 if( !lexeme.empty() )
  {
   if( !lexeme.eqi( *wf.GetName() ) )
    return false;
  }
 else if( !id_lemma.empty() )
  {
   bool m=false;
   for( lem::Container::size_type i=0; i<id_lemma.size(); ++i )
    if( id_lemma[i] == wf.GetEntryKey() )
     {
      m=true;
      break;
     }

   if( !m )
    return false;
  }
 else if( !pos.empty() )
  {
   bool m=false;

   const int ekey = wf.GetEntryKey();
   const SG_Entry & e = dict.GetSynGram().GetEntry(ekey);
   const int wf_pos = e.GetClass();
   
   for( lem::Container::size_type i=0; i<pos.size(); ++i )
    if( pos[i]==wf_pos )
     {
      m=true;
      break;
     }

   if( !m )
    return false;
  }

 if( !pairs.empty() )
  {
   for( lem::Container::size_type i=0; i<pairs.size(); ++i )
   {
    const GramCoordPair & p = pairs[i];
    if( wf.GetPairs().FindOnce(p)!=UNKNOWN )
     continue;

    // для бистабильных координат - состояние 0 равнозначно отсутствию вообще такой пары
    if( dict.GetSynGram().coords()[ p.GetCoord().GetIndex() ].IsBistable() )
     {
      if( wf.GetPairs().FindOnce( p.GetCoord().GetIndex() ) != UNKNOWN )
       return false;
     }
    else
     return false;    
   }
  }

 return true;
}


void ModelTagMatcher::Print( lem::OFormatter & to, Dictionary & dict ) const
{
 if( !lexeme.empty() )
  to.printf( "\"%us\" ", lexeme.c_str() );

 for( lem::Container::size_type i=0; i<id_lemma.size(); ++i )
  {
   int id_entry = id_lemma[i];
   const SG_Entry & e = dict.GetSynGram().GetEntry(id_entry);
   int id_class = e.GetClass();
   const SG_Class & c = dict.GetSynGram().GetClass( id_class );
   to.printf( "%us:%us ", c.GetName().c_str(), e.GetName().c_str() );
  }

 for( lem::Container::size_type i=0; i<pos.size(); ++i )
  {
   const SG_Class & c = dict.GetSynGram().GetClass( pos[i] );
   lem::mout->printf( "%us ", c.GetName().c_str() );
  }

 for( lem::Container::size_type i=0; i<pairs.size(); ++i )
  {
   const Solarix::GramCoordPair & p = pairs[i];
   p.SaveTxt( to, dict.GetSynGram() );
   to.printf( " " );
  }

 return;
}

