// -----------------------------------------------------------------------------
// File SYNTAX.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar engine
// SYNTAX program - syntax analyzer test program
// ѕрограмма "—интаксический анализатор" - консольна€ утилита дл€ интерактивного
// или пакетного тестировани€ модул€ синтаксического анализатор и синтезатора.
//
// 27.03.2009 - добавлена опци€ -timeout XXX дл€ ограничени€ максимального
//              времени, затрачиваемого на анализ одного предложени€.
// 05.06.2009 - добавлена опци€ -morphology, котора€ в паре с -batch позвол€ет
//              тестировать работу фильтра начальных вариаторов в
//              морфологическом анализаторе.
// 19.10.2009 - добавлена опци€ -print_html дл€ вывода результатов пакетной
//              обработки в HTML формате
// 25.11.2011 - добавлена опци€ -allow_incomplete дл€ включени€ режима
//              неполного анализа из командной строки
// 28.06.2012 - в ходе переделок лексера убрал из программы пакетный режим.
// 03.11.2012 - добавлен режим -speak (и директива #speak)
// -----------------------------------------------------------------------------
//
// CD->25.02.2003
// LC->13.08.2013
// --------------

#include <lem/keyboard.h>
#include <lem/startup.h>
#include <lem/solarix/version.h>
#include "syntax.h"

using namespace lem;
using namespace Solarix;

int main( int argc, char *argv[] )
{
 #if LEM_DEBUGGING==1 && defined LEM_MSC
 int m=-1;
// printf( "Enter _CrtSetBreakAlloc argument:" );
// scanf( "%d", &m );
 if( m>0 )
  _CrtSetBreakAlloc(m);


 _CrtSetDbgFlag(
                _CRTDBG_ALLOC_MEM_DF |
//                _CRTDBG_DELAY_FREE_MEM_DF |
//                 _CRTDBG_CHECK_EVERY_128_DF |
                _CRTDBG_LEAK_CHECK_DF
               );

 #endif
 lem::LemInit initer;


 SyntaxShell::RunMode selected_mode = SyntaxShell::SyntaxMode; // по умолчанию запустимс€ в режиме синтаксического разбора.

 
 lem::zbool debug, verbose;
 lem::zbool lazy_lexicon;
 bool show_org_sent=true; // при печати результатов пакетной обработки в файл - печать ли исходное предложение до результата
 lem::Path dictdir;
 lem::UCString language;
 lem::UCString scenario;
 lem::Collect< std::pair<UCString /*tag*/, UCString /*value*/> > tags; // тэги дл€ фильтрации переводов
 lem::Collect< std::pair<UCString /*param*/, UCString /*value*/> > params; // глобальные параметры
 lem::UFString phrase;
 bool AllowIncomplete=false;
 bool AllowFuzzy=false;
 bool AllowReconstructor=false;
 bool AllowModel=false;
 bool Semantics=false;
 int MaxAlt=0;
 int MaxSkipToken=0;

 verbose = true;

 for( int i=1; i<argc; ++i )
  {
   if( lem_eqi(argv[i]+1,"dictdir") )
    {
     lem::Path p( argv[i+1] );
     dictdir = p;
     if( !p.DoesExist() )
      {
       lem::mout->printf( "%vfCError%vn: path [%vfE%us%vn] does not exist\n", p.GetUnicode().c_str() );
       lem::Process::Exit();
      }

     i++; 
    }
   else if( lem_eqi(argv[i]+1,"tag") )
    {
     UCString tag = lem::to_unicode(argv[i+1]).c_str();
     UCString value = lem::to_unicode(argv[i+2]).c_str();
     tags.push_back( std::make_pair( tag, value ) );
     i+=2;
    }
   else if( lem_eqi(argv[i]+1,"param") )
    {
     UCString param = lem::to_unicode(argv[i+1]).c_str();
     UCString value = lem::to_unicode(argv[i+2]).c_str();
     params.push_back( std::make_pair( param, value ) );
     i+=2;
    }
   else if( lem_eqi(argv[i]+1,"phrase") )
    {
     phrase = lem::to_unicode(argv[i+1]);
     i++;
    }
   else if( lem_eqi(argv[i]+1,"verbose") )
    {
     verbose = true;
    }
   else if( lem_eqi(argv[i]+1,"verbose-") )
    {
     verbose = false;
    }
   else if( lem_eqi(argv[i]+1,"language") )
    {
     language = argv[i+1];
     i++; 
    } 
   else if( lem_eqi(argv[i]+1,"morphology") )
    {
     selected_mode = SyntaxShell::MorphologyMode;
    }
   else if( lem_eqi(argv[i]+1,"syntax") )
    {
     selected_mode = SyntaxShell::SyntaxMode;
    }
   else if( lem_eqi(argv[i]+1,"tokenize") )
    {
     selected_mode = SyntaxShell::TokenizerMode;
    }
   else if( lem_eqi(argv[i]+1,"lemmatize") )
    {
     selected_mode = SyntaxShell::LemmatizerMode;
    }
   else if( lem_eqi(argv[i]+1,"speak") )
    {
     selected_mode = SyntaxShell::SpeakerMode;
    }
   else if( lem_eqi(argv[i]+1,"debug") )
    {
     debug=true;
    }
   else if( lem_eqi(argv[i]+1,"lazy_lexicon") )
    {
     lazy_lexicon=true;
    }
   else if( lem_eqi( argv[i]+1,"allow_incomplete") )
    {
     AllowIncomplete=true;
    }
   else if( lem_eqi( argv[i]+1,"disallow_incomplete") )
    {
     AllowIncomplete=false;
    }
   else if( lem_eqi( argv[i]+1,"allow_fuzzy") )
    {
     AllowFuzzy=true;
    }
   else if( lem_eqi( argv[i]+1, "allow_reco") )
    {
     AllowReconstructor=true;
    }
   else if( lem_eqi( argv[i]+1, "allow_model") || lem_eqi( argv[i]+1, "model") )
    {
     AllowModel=true;
    }
   else if( lem_eqi( argv[i]+1, "sem") )
    {
     Semantics=true;
    }
   else if( lem_eqi(argv[i]+1,"maxalt") )
    {
     MaxAlt = lem::to_int(argv[i+1]);
     i++; 
    }
   else if( lem_eqi(argv[i]+1,"maxskiptoken") )
    {
     MaxSkipToken = lem::to_int(argv[i+1]);
     i++; 
    }
   else
    {
     lem::mout->printf( "%vfCError%vn: unknown option [%vfE%s%vn]\n", argv[i] );
     lem::Process::Exit();
    }
  }

 if( verbose )
  mout->printf( "%vf9Solarix %vfESYNTAX%vn parser debugger ver. %s\n", sol_get_version().c_str() );

 try
  {
   SyntaxShell sh;

   sh.dict_dir = dictdir;

   sh.LazyLexicon(lazy_lexicon);
   sh.LoadDictionary();

   sh.SetMode( selected_mode );
   sh.AllowIncomplete(AllowIncomplete);
   sh.AllowFuzzy(AllowFuzzy);
   sh.AllowReconstructor(AllowReconstructor);
   sh.AllowModel(AllowModel);
   sh.SetThesaurusTags(tags);
   sh.SetEnvParams(params);
   sh.SetDebug(debug);
   sh.SetPhrase(phrase);
   sh.SetMaxAlt(MaxAlt);
   sh.SetMaxSkipToken(MaxSkipToken);

   if( Semantics )
    sh.RunSemantics();

   if( !language.empty() )
    sh.SetLanguage(language);

   sh.main_loop();
  }
 catch( const lem::E_BaseException &e )
  {
   mout->printf( "Error: %us\n", e.what() );
  }
 catch( const std::exception &e )
  {
   mout->printf( "Error: %s\n", e.what() );
  }
 catch(...)
  {
   mout->printf( "Error.\n");
  } 

 lem::Leave();

 return 0;
}
