// -----------------------------------------------------------------------------
// File TEST_ENGLISH_MORPHOLOGY.CPP
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
// Работа с английским разделом. Загруженный словарь должен содержать английские
// модули - лексикон, синтаксический анализатор. Проверяется отдельно - проекция
// слов на лексикон (как всякие хитрые варианты типа don't, так и просто разные
// словофромы для проверки парадигм - например удвоение последней буквы в
// stop-stopped).
//
// 25.07.2008 - добавлен регрессионный тест
// 23.12.2008 - добавлен тест на проекцию многолексемных словоформ
// 07.01.2009 - добавлен тест тезауруса (грамматические + семантические связи)
// 28.10.2009 - добавлено множество тестов синтаксического анализа на базовые
//              конструкции.  
// -----------------------------------------------------------------------------
//
// CD->14.10.2006
// LC->04.10.2011
// --------------

#include <iostream>
#include <stdio.h>

#if defined WIN32
#include <windows.h>
#endif

// Grammar Engine API
// API грамматической машины
#include "../../../../../include/lem/solarix/solarix_grammar_engine.h"
#include "../../../../../include/lem/solarix/_sg_api.h"

using namespace std;

extern void failed( HGREN hEngine );

#if defined WIN32
extern void wide( const wchar_t *ustr, FILE *f=stdout, int cp=CP_OEMCP );
#else
extern void wide( const wchar_t *ustr, FILE *f=stdout, int cp=0 );
#endif

extern void Print_StrList( HGREN hEngine, HGREN_STR hStr );
extern void PrintNode( HGREN_RESPACK hPack, HGREN_TREENODE hNode );
extern void PrintGraph( HGREN_RESPACK hPack, int igraf );
extern bool TestSyntaxAnalysis( HGREN hEngine, const wchar_t *Phrase, int Language, bool must_be_complete_analysis );
extern bool TestLink( HGREN hEngine, const wchar_t *Word1, int class1, const wchar_t *Word2, int class2 );
extern void TestMorphologicalAnalyzer( HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, bool use_model, int thread_no );
extern void TestSyntacticAnalyzer( HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, int thread_no );
extern void Test_Threading( HGREN hEngine, int id_language, const char *infile_morph, const char *infile_syntax );



int w_to_i( const wchar_t *s )
{
 #if defined WIN32
 return _wtoi(s);
 #else
 return (int)wcstol(s,NULL,10);
 #endif
}


bool is_delim( wchar_t c )
{
 return c==L'.' || c==L'?' || c==L'!';
}

extern bool ProbeEnglish( HGREN hEngine );


void Test_English_Morphology( HGREN hEngine )
{
 // Проверим, что словарь сопровождается корректной версией _sg_api.h
 wchar_t ClassName[64];
 sol_GetClassName( hEngine, NOUN_en, ClassName );
 if( wcscmp( ClassName, L"ENG_NOUN" )!=0 )
  {
   failed(hEngine);
  }

 if( !ProbeEnglish(hEngine) )
  return;

 const int MAX_LEN = sol_MaxLexemLen(hEngine);

 const int ie1 = sol_FindEntry( hEngine, L"MOTHER", /*Solarix::API::*/NOUN_en, /*Solarix::API::*/ENGLISH_LANGUAGE );

 // Должно быть существительное
 if( sol_GetEntryClass( hEngine, ie1 )!=NOUN_en )
  failed(hEngine);

 // Проверяем быстрый поиск двух форм слова
 const int id1 = sol_SeekWord( hEngine, L"DID", false );
 const int id2 = sol_SeekWord( hEngine, L"DONE", false );

 // Возвращенные ID должны совпадать
 printf( "id1=%d id2=%d\n", id1, id2 );
 if( id1!=id2 )
  failed(hEngine);

 if( sol_GetEntryClass( hEngine, id1 )!=VERB_en )
  failed(hEngine);


 // Проверяем поиск словарной статьи по любой грамматической форме
 int id2_0=-1, id2_1=-1, id2_2=-1, id2_3=-1;
 sol_FindWord( hEngine, L"dilly-dally", &id2_0, NULL, NULL );
 sol_FindWord( hEngine, L"dilly-dallies", &id2_1, NULL, NULL );
 sol_FindWord( hEngine, L"dilly-dallying", &id2_2, NULL, NULL );
 sol_FindWord( hEngine, L"dilly-dallied", &id2_3, NULL, NULL );
 if( id2_0!=id2_1 || id2_0!=id2_2 || id2_0!=id2_3 )
  failed(hEngine);
 


 // Получение всех форм слова
 HGREN_STR hStr = sol_FindStrings( hEngine, L"ask" );
 if( hStr==NULL )
  failed(hEngine);
 
 int nstr = sol_CountStrings( hStr );
 if( nstr<1 )
  failed(hEngine);

 Print_StrList(hEngine,hStr);

 // Проекция для многолексемных словоформ и прочих разных случаев, в том числе - проверка
 // образования множественного числа и спряжения английских глаголов.
 const wchar_t *ws[]=
 {
  L"implies",
  L"King's", L"Kings'",
  L"Owner's",
  L"Mother",
  L"Wider", L"Widest",
  L"greater", L"greatest",
  L"louder", L"loudest",
  L"shelves",
  L"DEATHS",
  L"DEPTHS",
  L"BUSHES",
  L"Ashes",
  L"destroyed", L"destroys", L"destroying",
  L"CHEESECLOTHES",
  L"longer", L"longest",
  L"happier", L"happiest",
  L"played", L"plays", L"playing",
  L"stay", L"stays", L"stayed", L"staying",
  L"dye", L"died", L"dying", L"dies",
  L"remembered",
  L"copied",
  L"martyred",
  L"shopping",
  L"ignored", L"ignoring", L"ignors",
  L"stirred",
  L"pass", L"passes", L"passed", L"passing",
  L"buzz", L"buzzes", L"buzzed", L"buzzing",
  L"sum",  L"sums",   L"summed", L"summing",
  L"add",  L"adds",   L"added",  L"adding",
  L"can't",
  L"gave up",
  L"stands up",
  L"isn't",
  L"wouldn't",
  L"shouldn't",
  L"wasn't",
  L"'M",
  L"'RE",
  L"'S",
  L"AREN'T",
  L"ISN'T",
  L"WASN'T",
  L"WEREN'T",
  L"'VE",
  L"'VE",
  L"'VE",
  L"'S",
  L"'D",
  L"ain't",
  L"COULDN'T",
  L"'LL",
  L"don't",
  L"didn't",
  L"doesn't",
  L"haven't",
  L"hadn't",
  L"hasn't",
  L"won't",
  L"edited", L"edits", L"editing",
  L"putting",
  L"patting",
  L"going",
  L"making",
  L"rolling", L"rolls",
  L"raving",
  L"stopping", L"stopped",
  L"granted", L"granting",
  L"fetching", L"fetches",
  L"searches", L"searching",
  L"shopping", 
  L"hanging",
  L"spinning", L"spinning",
  L"skip", L"skipping",
  L"hum", L"humming",
  L"foxes", L"boxes",
  L"arose", L"arisen",
  L"speeches",
  L"berries",
  NULL
 };

 int iw=0;
 while( ws[iw]!=NULL )
  {
   int ientry=-1, iform=-1, iclass=-1;
   int nproj = sol_FindWord( hEngine, ws[iw], &ientry, &iform, &iclass );
   if( nproj<1 )
    failed(hEngine);
   iw++;
  }



 // -------------------- ТЕСТЫ ТОКЕНИЗАТОРА ---------------------

 const wchar_t *tokenizer[]=
 {
  /* ----- предложение -------   --число лексем-- */
  L"don't",                           L"1",
  L"didn't",                          L"1",
  L"doesn't",                         L"1",
  L"I can't dance",                   L"3",
  L"We won't sleep",                  L"3",
  L"pre-exist",                       L"1",
  L"dilly-dally",                     L"1",
  L"ad-lib",                          L"1",
  NULL
 };

 int itok=0;
 while( tokenizer[itok]!=NULL )
  {
   const wchar_t *stok =  tokenizer[itok];
   itok++; 
   HGREN_STR hStr = sol_TokenizeW( hEngine, stok, ENGLISH_LANGUAGE );
   
   int nstr = sol_CountStrings( hStr );
   if( nstr!=w_to_i( tokenizer[itok++] ) )
    { 
     failed(hEngine);
    }

   // Эта процедура освободит список строк сама.
   Print_StrList( hEngine, hStr );
  }


 // Условный номер варианта движка. 0 - Lite, 1 - Pro, 2 - Premium (только для поискового движка)
 const int eversion = sol_GetVersion(hEngine,NULL,NULL,NULL);


 if( eversion>=1 )
  {
   TestLink( hEngine, L"ANSWER", NOUN_en, L"ANSWER", VERB_en );
   TestLink( hEngine, L"ANSWER", VERB_en, L"ANSWER", NOUN_en );

   TestLink( hEngine, L"ARRIVAL", NOUN_en, L"ARRIVE", VERB_en );
   TestLink( hEngine, L"ARRIVE",  VERB_en, L"ARRIVAL", NOUN_en );

   TestLink( hEngine, L"CAT", NOUN_en, L"KITTY", NOUN_en );
   TestLink( hEngine, L"PUSSY", NOUN_en, L"KITTY", NOUN_en );

   TestLink( hEngine, L"DEPART", VERB_en, L"DEPARTURE", NOUN_en );
   TestLink( hEngine, L"DEPARTURE", NOUN_en, L"DEPART", VERB_en );

   TestLink( hEngine, L"DOGGY", ADJ_en, L"DOG", NOUN_en );
  }


 TestSyntacticAnalyzer( hEngine, ENGLISH_LANGUAGE, 30, "syntax-english.txt", true, -1 );
 TestMorphologicalAnalyzer( hEngine, ENGLISH_LANGUAGE, 30, "morph-english.txt", true, false, -1 );


 // Различные многопоточные тесты.
 Test_Threading(hEngine, ENGLISH_LANGUAGE, "morph-english.txt","syntax-english.txt");

 return;
}
