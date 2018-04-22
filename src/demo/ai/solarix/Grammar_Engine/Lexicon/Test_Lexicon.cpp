// -----------------------------------------------------------------------------
// File TEST_LEXICON.CPP
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
// SDK - тесты грамматической машины. Вы можете использовать исходный текст
// программы без ограничений, в том числе копировать фрагменты в свой код без
// указания первоисточника.
//
// Для запуска программы необходимы файлы DLL ГМ и скомпилированного словаря.
//
// Скопируйте файл solarix_grammar_engine.dll из lem\lem-pro\ и файл sqlite.dll
// из lem\lib в текущий каталог проекта.
//
// 08.05.2007 - пример переделан для тестирования отдельной DLL ГМ.
// 14.06.2007 - небольшая переделка из-за изменения формата хранения словаря.
// 29.08.2007 - в отладочной версии линкуемся с "solarix_grammar_engined.dll",
//              в релизной с "solarix_grammar_engine.dll"
// 29.04.2008 - в связи с переносом примеров SDK ГМ в основновной каталог LEM,
//              переделаны пути.
// 11.07.2008 - программа является частью TestSuite проекта, поэтому любая
//              зафиксированная ошибка прерывает работу с установкой кода возврата
//              программы !=0.
// 23.07.2008 - порт под MSVC2005 x64
// 02.12.2008 - программа нормально компилируется и исполняется как с усеченной
//              версией движка (только Грамматический Движок), так и с полной
//              версией (Поисковый Движок).
// 13.02.2009 - добавлены простейшие тесты для французского и испанского
//              разделов. 
// 16.05.2010 - добавлен многопоточный тест для анализаторов.
//
// 03.07.2011 - добавлен анализ параметров командной строки, опция -morph XXX
//              позволяет указать файл эталонных предложений и выполнить его прогон,
//              без запуска других тестов.
//
// 04.07.2011 - переделка теста синтаксического анализатора, эталонные предложения
//              теперь читаются из внешнего текстового файла, тест может быть
//              запущен автономно опцией -syntax XXX
//
// 27.09.2011 - добавлено тестирование режима ленивой загрузки лексикона, включается
//              из командной строки опцией /lazy_lexicon
//
// 09.01.2012 - добавлен автоматический тест слогоделителя по файлу эталонов.
// 08.05.2012 - добавлена опция -threads, запускающая многопоточные тесты для
//              заданных опциями -syntax и -morph эталонных файлов.
// -----------------------------------------------------------------------------
//
// CD->20.06.2005
// LC->08.05.2012
// --------------

#if defined WIN32
#include <windows.h>
#endif

#include <time.h>
#include <iostream>
#include <tchar.h>
#include <assert.h>

#if _DEBUG && defined _MSC_VER
#include <crtdbg.h>
#endif

// Grammar Engine API
// API грамматической машины
#include "..\..\..\..\..\include\lem\solarix\solarix_grammar_engine.h"

using namespace std;

extern void Test_Russian_Morphology( HGREN hEngine, bool use_model );
extern void Test_English_Morphology( HGREN hEngine );
extern void Test_Spanish_Morphology( HGREN hEngine );
extern void Test_French_Morphology( HGREN hEngine );
extern void Test_Ru_En_Translation( HGREN hEngine );
extern void Test_Ja_Ru_Translation( HGREN hEngine );
extern void TestModifications( HGREN hEngine );
extern bool ProbeEnglish( HGREN hEngine );
extern bool ProbeRussian( HGREN hEngine );
extern bool ProbeSpanish( HGREN hEngine );
extern bool ProbeFrench( HGREN hEngine );
extern void Test_NGRAMS( HGREN hEngine );
extern void Test_Phrases( HGREN hEngine );
extern void TestMorphologicalAnalyzer( HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, bool use_model, int thread_no );
extern void TestSyntacticAnalyzer( HGREN hEngine, int id_language, int default_beam_size, const char *filename, bool write_errors, int thread_no );
extern void TestSegmenter( HGREN hEngine, int id_language, const char *filename, bool write_errors, int thread_no );
extern void TestSyllabicBreaks( HGREN hEngine, int id_language, const char *filename, bool write_errors, int thread_no );
extern void Test_Threading( HGREN hEngine, int id_language, const char *infile_morph, const char *infile_syntax );


int CountLanguages( HGREN hEngine )
{
 int n=0;
 if( ProbeEnglish(hEngine) ) n++;
 if( ProbeRussian(hEngine) ) n++;
 if( ProbeSpanish(hEngine) ) n++;
 if( ProbeFrench(hEngine) ) n++;

 return n;
}

extern int fault_count;

extern void print8( const char *utf8 );


static const TCHAR* makepath( const TCHAR *org )
{
 #if defined _M_X64
 const TCHAR *xx = _T("64");
 #else
 const TCHAR *xx = _T("");
 #endif

 const size_t subst_len = _tcslen(xx);

 const TCHAR* subst = _T("?");
 const TCHAR* xxpos = _tcsstr(org,subst);
 if( xxpos==nullptr )
  return org;

 TCHAR* buf = new TCHAR[ _tcslen(org)+subst_len+1 ];
 _tcscpy( buf, org );
 _tcscpy( buf+(xxpos-org), xx );
 _tcscpy( buf+(xxpos-org)+subst_len, xxpos+_tcslen(subst) );


 // Memory leakage does not matter in this test suite
 return buf;
}



static bool exists( const TCHAR *path )
{ return GetFileAttributes(path)!=(DWORD)INVALID_FILE_ATTRIBUTES; }


int main( int argc, const char *argv[] )
{
 #if _DEBUG && defined _MSC_VER
// _CrtSetBreakAlloc(3006);
 _CrtSetDbgFlag(
                _CRTDBG_ALLOC_MEM_DF |
//                _CRTDBG_DELAY_FREE_MEM_DF |
//                _CRTDBG_CHECK_ALWAYS_DF |
                _CRTDBG_LEAK_CHECK_DF
               );
 #endif

 cout << "This is a sample application for the grammar engine Win32 DLL.\n\n";
 cout << "Visit http://solarix.ru/for_developers/api/grammar-engine.shtml    (Russian)\n";
 cout << " or   http://solarix.ru/for_developers/api/grammar-engine-en.shtml (English)\n\n";

 // Первоначальная инициализация движка.
 HGREN hEngine = nullptr;

 int MajorVer, MinorVer, BuildNum;
 int rc = sol_GetVersion( hEngine, &MajorVer, &MinorVer, &BuildNum );

 // http://www.solarix.ru/api/en/sol_CreateGrammarEngine.shtml
 hEngine = sol_CreateGrammarEngine(nullptr);

 // Когда работаем с локальным словарем, надо заранее резервировать память под
 // добавляемые статьи - см. функцию sol_AddWord.
 sol_ReserveLexiconSpace(hEngine,3000000);


 // Грузим морфологию, синтаксис и другие модули.
 // Словарь должен быть уже подготовлен и находится в текущем каталоге. Для
 // подготовки словаря можно запустить один из скриптов в \lem\scripts\dictionary,
 // а затем скопировать созданные файлы из \lem\bin-windows в текущий каталог программы.
 cout << "Loading grammar engine...\n";

 int load_status=0;

 const char *dict_path=nullptr;
 const char *morph_samples=nullptr;
 const char *syntax_samples=nullptr;
 const char *segmenter_samples=nullptr;
 const char *syllabs_samples=nullptr;
 const char *lang_name = nullptr;
 bool lazy_lexicon=false;
 bool test_threads=false;
 bool use_model=false;
 int default_beam_size=0;

 for( int iarg=1; iarg<argc; ++iarg )
  {
   if( strcmp( argv[iarg]+1, "dict" )==0 )
    {
     dict_path = argv[iarg+1];
     iarg++;
    }
   else if( strcmp( argv[iarg]+1, "threads" )==0 )
    {
     test_threads=true;
    }
   else if( strcmp( argv[iarg]+1, "maxalts" )==0 )
    {
     default_beam_size=atoi(argv[iarg+1]);
     iarg++;
    }
   else if( strcmp( argv[iarg]+1, "morph" )==0 )
    {
     morph_samples = argv[iarg+1];
     iarg++;
    }
   else if( strcmp( argv[iarg]+1, "syntax" )==0 )
    {
     syntax_samples = argv[iarg+1];
     iarg++;
    }
   else if( strcmp( argv[iarg]+1, "segmenter" )==0 )
    {
     segmenter_samples = argv[iarg+1];
     iarg++;
    }
   else if( strcmp( argv[iarg]+1, "syllabs" )==0 )
    {
     syllabs_samples = argv[iarg+1];
     iarg++;
    }
   else if( strcmp( argv[iarg]+1, "language" )==0 )
    {
     iarg++;
     lang_name = argv[iarg];
    }
   else if( strcmp( argv[iarg]+1, "lazy_lexicon" )==0 )
    {
     // Режим ленивой подгрузки словарных статей. Не загружаем весь лексикон в оперативку сразу,
     // а будет подгружать по необходимости.
     lazy_lexicon=true;
    }
   else if( strcmp( argv[iarg]+1, "model" )==0 )
    {
     use_model=true;
    }
   else
    {
     printf( "Unknown option: %s\n", argv[iarg] );
     exit(1);
    }
  }

 int InstanceFlags = 0;
 if( lazy_lexicon ) InstanceFlags |= SOL_GREN_LAZY_LEXICON;

 if( dict_path==nullptr )
  {
   #if defined MYSQL_DICTIONARY
   if( exists( makepath(_T("..\\..\\..\\..\\..\\bin-windows?\\dictionary-mysql.xml"))) )
    {
     load_status = sol_LoadDictionaryEx( hEngine, makepath(_T("..\\..\\..\\..\\..\\bin-windows?\\dictionary-mysql.xml")), InstanceFlags );
    }
   else if( exists( _T("..\\..\\..\\..\\..\\dictionary-mysql.xml")) )
    {
     // Вариант для запуска примера из SDK
     load_status = sol_LoadDictionaryEx( hEngine, _T("..\\..\\..\\..\\..\\dictionary-mysql.xml"), InstanceFlags );
    }
   else
    {
     load_status = sol_LoadDictionaryEx( hEngine, _T("dictionary-mysql.xml"), InstanceFlags );
    }
   #else
   if( exists( makepath(_T("..\\..\\..\\..\\..\\bin-windows?\\dictionary.xml"))) )
    {
     // Вариант для конфигурации Development-pro - запуск с отладочной версией DLL ГМ внутри библиотеки LEM
     load_status = sol_LoadDictionaryEx( hEngine, makepath(_T("..\\..\\..\\..\\..\\bin-windows?\\dictionary.xml")), InstanceFlags );
    }
   else if( exists( _T("..\\..\\..\\..\\..\\dictionary.xml")) )
    {
     // Вариант для запуска примера из SDK
     load_status = sol_LoadDictionaryEx( hEngine, _T("..\\..\\..\\..\\..\\dictionary.xml"), InstanceFlags );
    }
   else
    {
     load_status = sol_LoadDictionaryEx( hEngine, _T("dictionary.xml"), InstanceFlags );
    }
   #endif
  }
 else
  {
   load_status = sol_LoadDictionaryExA( hEngine, dict_path, InstanceFlags );
  }

 if( load_status==1 )
  cout << "Engine is loaded OK\n";
 else
  {
   cout << "Error loading dictionary file dictionary.xml\n"
           "You have to download the latest dictionary build\n"
           "from https://github.com/Koziev/GrammarEngine";

   int l = sol_GetErrorLen8(hEngine);
   char *err = new char[ l+1 ];
   *err=0;
   sol_GetError8( hEngine, err, l );
   print8(err);
   return -1;
  }

 // Lexicon statistics.

 if( lazy_lexicon )
  {
   cout << "Dictionary ver." << sol_DictionaryVersion(hEngine) << "\n";
  }
 else
  {
   cout << "Dictionary ver." << sol_DictionaryVersion(hEngine)
        << " contains " << sol_CountEntries(hEngine) << " entries, "
        << sol_CountForms(hEngine) << " wordforms, " 
        << sol_CountLinks(hEngine) << " links\n";
  }

 // maximum length of strings (wordforms, entry names etc.)
 // http://www.solarix.ru/api/en/sol_MaxLexemLen.shtml
 const int MAX_LEN = sol_MaxLexemLen(hEngine);
 cout << "Max lexem length=" << MAX_LEN << " chars\n";


 int id_language=-1;

 if( lang_name!=nullptr )
  {
   id_language = sol_FindLanguage8( hEngine, lang_name );
   if( id_language==-1 )
    {
     printf( "Unknown language [%s]\n", lang_name );
     exit(1);
    }
  }

 sol_SetLanguage( hEngine, id_language );
 
 time_t t1 = time(nullptr);

 const bool write_errors=true;

 if( test_threads )
  {
   Test_Threading( hEngine, id_language, morph_samples, syntax_samples );
  }
 else if( morph_samples!=nullptr )
  {
   TestMorphologicalAnalyzer( hEngine, id_language, default_beam_size, morph_samples, write_errors || !use_model, use_model, -1 );
  }
 else if( syntax_samples!=nullptr )
  {
   TestSyntacticAnalyzer( hEngine, id_language, default_beam_size, syntax_samples, write_errors, -1 );
  }
 else if( segmenter_samples!=nullptr )
  {
   TestSegmenter( hEngine, id_language, segmenter_samples, write_errors, -1 );
  }
 else if( syllabs_samples!=nullptr )
  {
   TestSyllabicBreaks( hEngine, id_language, syllabs_samples, write_errors, -1 );
  }
 else
  {
   // Грамматические тесты для отдельных языков, они сами обнаруживают
   // наличие соответствующих лексиконов в загруженном словаре и
   // исполняются только при наличии нужного.
   Test_Russian_Morphology(hEngine,false);
   Test_English_Morphology(hEngine);
   Test_French_Morphology(hEngine);
   Test_Spanish_Morphology(hEngine);

   // Тест функций для работы с фразовыми статьями
   Test_Phrases(hEngine);

   // Тест демо-базы N-грамм
   Test_NGRAMS(hEngine);

   // Это дополнительный тест для тезауруса - поиск переводов слов.
   Test_Ru_En_Translation(hEngine);

   //TestModifications(hEngine);
  }

 // Free allocated resources, delete the engine instance.
 // http://www.solarix.ru/api/en/sol_DeleteGrammarEngine.shtml
 sol_DeleteGrammarEngine(hEngine);

 cout << "All done";

 time_t t2 = time(nullptr);
 double elapsed = difftime(t2,t1);
 cout << ", elapsed_time=" << elapsed;

 if( fault_count!=0 )
  cout << ", " << fault_count << " fault(s)";

 cout << "\n";

 return fault_count;
}
