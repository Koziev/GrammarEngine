// -----------------------------------------------------------------------------
// File LexiconMain.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                https://github.com/Koziev/GrammarEngine
//
// Content:
// SOLARIX Grammar engine
// *** LEXICON ***
//
// Простая утилита администрирования Словаря СОЛЯРИС: вводимые лексемы
// рассматриваются как имена словарных статей, выполняется поиск и выводятся
// результаты поиска: статьи и их существенные признаки.
//
// 23.02.2009 - введен пакетный режим поиска N-грамм из текстового файла - для
//              автоматизации проверок.
// 09.03.2013 - убраны неиспользуемые опции командной строки.
// -----------------------------------------------------------------------------
//
// CD->25.02.2003
// LC->05.04.2018
// --------------

#include <lem/keyboard.h>
#include <lem/startup.h>
#include <lem/solarix/version.h>
#include "LexiconShell.h"

using namespace lem;
using namespace Solarix;


int main( int argc, char *argv[] )
{
 #if LEM_DEBUGGING==1 && defined LEM_MSC
 //_CrtSetBreakAlloc(29025);
 _CrtSetDbgFlag(
                _CRTDBG_ALLOC_MEM_DF |
//                _CRTDBG_DELAY_FREE_MEM_DF |
//                _CRTDBG_CHECK_ALWAYS_DF |
                _CRTDBG_LEAK_CHECK_DF
               );

 #endif

 lem::Init();

 mout->printf( "%vf9Solarix %vfELexicon%vn // %s //\n\n", sol_get_version().c_str() );

 lem::Path dictionary_path;
 lem::MCollect<int> imenu;
 bool show_menu=false;

 for( int i=1; i<argc; ++i )
  {
   if( lem_eq(argv[i]+1,"dictdir") || lem_eq(argv[i]+1,"dict") )
    {
     dictionary_path = lem::Path( argv[++i] );
    }
   else if( lem_eq(argv[i]+1,"menu") )
    {
     FString menu = argv[++i];
     lem::MCollect<lem::CString> words;
     lem::parse( menu, words, false ); 
     for( lem::Container::size_type i=0; i<words.size(); ++i )
      {
       imenu.push_back( lem::to_int(words[i]) );
      } 
    }
   else if( lem_eq(argv[i]+1,"show_menu") )
   {
    show_menu=true;
   }
   else
    {
     mout->printf( "Unknown option [%vfC%s%vn]\n", argv[i] );
     exit(1);
    }
  }

 // Интерактивный режим ввода и обработки команд с консоли.
 // В опциях может быть задан путь прохождения меню в виде -menu n,m,k...
 LexiconShell sh(dictionary_path);
 sh.main_loop(show_menu,imenu);

 lem::Leave();

 return 0;
}
