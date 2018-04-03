// -----------------------------------------------------------------------------
// File TEST_FRENCH_MORPHOLOGY.CPP
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Grammar Machine test suite.
//
// API documentation: http://www.solarix.ru/for_developers/api/grammar-engine-api.shtml
// Other samples: http://www.solarix.ru/for_developers/api/grammar-engine-examples.shtml
// Troubleshooting: http://www.solarix.ru/contacts/contacts.shtml
//
// Работа с французским разделом.
//
// 13.02.2009 - первая реализация
// -----------------------------------------------------------------------------
//
// CD->13.02.2009
// LC->22.12.2009
// --------------

#include <iostream>

// Grammar Engine API
// API грамматической машины
#include "..\..\..\..\..\include\lem\solarix\solarix_grammar_engine.h"
#include "..\..\..\..\..\include\lem\solarix\_sg_api.h"

#include <windows.h>

using namespace std;

extern void failed( HGREN hEngine );
extern void wide( const wchar_t *ustr, FILE *f=stdout, int cp=CP_OEMCP );
extern void stem( HGREN hEngine, const wchar_t *Word );
extern void Print_StrList( HGREN hEngine, HGREN_STR hStr );
extern void PrintNode( HGREN_RESPACK hPack, HGREN_TREENODE hNode );
extern void PrintGraph( HGREN_RESPACK hPack, int igraf );
extern bool TestSyntaxAnalysis( HGREN hEngine, const wchar_t *Phrase, bool must_be_complete_analysis );
extern bool TestLink( HGREN hEngine, const wchar_t *Word1, int class1, const wchar_t *Word2, int class2 );


bool ProbeFrench( HGREN hEngine )
{
 const int MAX_LEN = sol_MaxLexemLen(hEngine);

 const int ie1 = sol_FindEntry( hEngine, L"RUSSIE", /*Solarix::API::*/NOUN_fr, /*Solarix::API::*/FRENCH_LANGUAGE );
 if( ie1==-1 )
  {
   cout << "French lexicon is missing.\n";
   return false;
  }

 return true;
}


void Test_French_Morphology( HGREN hEngine )
{
 if( !ProbeFrench(hEngine) )
  return;

 const int MAX_LEN = sol_MaxLexemLen(hEngine);

 const int ie1 = sol_FindEntry( hEngine, L"FRAN\u00C7AIS", /*Solarix::API::*/-1, /*Solarix::API::*/FRENCH_LANGUAGE );

 // Должно быть прилагательное
 if( sol_GetEntryClass( hEngine, ie1 )!=ADJ_fr )
  failed(hEngine);

 HGREN_WCOORD hList1 = sol_ProjectWord( hEngine, L"Fran\u00E7aise", false );
 if( hList1==NULL )
  failed(hEngine);

 bool found=false;
 if( hList1!=NULL )
  {
   const int nproj = sol_CountProjections( hList1 );
   for( int i=0; i<nproj; i++ )
    {
     const int ientry = sol_GetIEntry(hList1,i);
     const int iclass = sol_GetEntryClass(hEngine,ientry);

     if( ientry == ie1 )
      {
       found=true;
       break; 
      }
    }
  }

 sol_DeleteProjections( hList1 );

 if( !found )
  failed(hEngine);

 // ... todo

 return;
}
