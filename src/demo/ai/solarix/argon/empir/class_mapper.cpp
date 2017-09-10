// -----------------------------------------------------------------------------
// File CLASS_MAPPER.CPP
//
// (c) by Elijah Koziev
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// -----------------------------------------------------------------------------
//
// CD->31.08.2005
// LC->21.11.2010
// --------------

#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/LexemeEnumerator.h>
#include "empir.h"

#if LEM_DEBUGGING==1 && defined LEM_MSC
#include <crtdbg.h>
#endif

using namespace std;
using namespace lem;
using namespace Solarix;

Class_Mapper::Class_Mapper( SynGram &sg )
{
 const int nlex = sg.GetEntries().CountLexemes();
 ld.resize( nlex );
 ilexem_2_ientry.resize( nlex );

 std::map< const Lexem*, int > lex_2_index;
 typedef std::map< const Lexem*, int >::const_iterator ITER2;

 lem::Ptr<LexemeEnumerator> lenum( sg.GetEntries().ListLexemes() );
 int i=0;
 Lexem lex;
 while( lenum->Fetch() )
  {
   lenum->Get(lex);
   ld[i] = lex;
   list.insert( std::make_pair( Calc_Hash( lex ), i ) );
   lex_2_index.insert( std::make_pair( &ld[i], i ) );
   ilexem_2_ientry[i] = UNKNOWN;
   i++;
  }
 lenum.Delete();

 lem::Ptr<WordEntryEnumerator> wenum( sg.GetEntries().ListEntries() );
 while( wenum->Fetch() )
  {
   const int ientry = wenum->GetId();
   const SG_Entry &e = wenum->GetItem();

   for( lem::Container::size_type iform=0; iform<e.forms().size(); iform++ )
    {
     // Указатель на элемент справочника.
     const Lexem *form = &e.forms()[iform].name();
 
     ITER2 it = lex_2_index.find( form );

     if( it!=lex_2_index.end() )
      ilexem_2_ientry[ it->second ] = ientry;
    }
  }

 #if LEM_DEBUGGING==1 && defined LEM_MSC
 LEM_CHECKIT_Z( _CrtCheckMemory() == TRUE );
 #endif

 return;
}

int Class_Mapper::Find_Entry( const UCString &x ) const
{
 std::pair<ITER,ITER> range = list.equal_range( Calc_Hash(x) );

 if( range.first==list.end() )
  return UNKNOWN;

// int ind=0;
 for( ITER i=range.first; i!=range.second; i++/*, ind++*/ )
  {
   int ilexem = i->second;
   const Lexem &ml = ld[ilexem];
   
   if( ml==x )
    return ilexem_2_ientry[ilexem];
  }

 return UNKNOWN;  
}

