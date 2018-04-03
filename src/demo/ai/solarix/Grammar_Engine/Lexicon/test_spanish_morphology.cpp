// -----------------------------------------------------------------------------
// File TEST_SPANISH_MORPHOLOGY.CPP
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
// Работа с испанским разделом.
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


bool ProbeSpanish( HGREN hEngine )
{
 const int MAX_LEN = sol_MaxLexemLen(hEngine);

 const int ie1 = sol_FindEntry( hEngine, L"RUSIA", /*Solarix::API::*/NOUN_es, /*Solarix::API::*/SPANISH_LANGUAGE );
 if( ie1==-1 )
  {
   cout << "Spanish lexicon is missing.\n";
   return false;
  }

 return true;
}


void Test_Spanish_Morphology( HGREN hEngine )
{
 if( !ProbeSpanish(hEngine) )
  return;

 const int MAX_LEN = sol_MaxLexemLen(hEngine);

 const int ie1 = sol_FindEntry( hEngine, L"ESPA\u00D1A", /*Solarix::API::*/-1, /*Solarix::API::*/SPANISH_LANGUAGE );

 // Должно быть существительное
 if( sol_GetEntryClass( hEngine, ie1 )!=NOUN_es )
  failed(hEngine);

 // ... todo

 return;
}
