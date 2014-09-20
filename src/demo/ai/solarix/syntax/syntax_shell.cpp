// -----------------------------------------------------------------------------
// File SYNTAX_SHELL.CPP
//
// (c) by Koziev Elijah ---SOLARIX INTELLECTRONIX Project---
//
// Syntax analyzer test suite (console interactive mode).
//
// 07.01.2008 - добавлен простой пакетный режим, в котором предложения читаются
//              из файла и подбивается статистика успешности анализа.
//
// 24.01.2008 - добавлен режим синтеза по результатам анализа для проверки
//              работы модуля вывода текста. 
// 30.07.2008 - после успешной загрузки словаря выдается краткая сводка по
//              его содержанию - кол-во статей и синтаксических правил.
// 24.01.2009 - для разбивки текста из файла в режиме -batch используется
//              класс SentenceBroker.
// 08.02.2009 - переписывается модуль разбиения строк на предложения и далее на
//              токены - с учетом произвольного набора исключений, задаваемых
//              через словарь.
// 22.03.2009 - для переводов, перефразировки и синтеза отключается печать только
//              самых коротких результирующих вариаторов.
// 14.07.2009 - добавлен режим токенизации, включаемый командой #tokenize
// 28.07.2009 - добавлен код для работы с интерактивным пошаговым отладчиком
// 17.08.2009 - добавлена работа с тэгами тезауруса - опция командной строки
//              -tags и интерактивные команды #tags и #tags-
// 24.08.2009 - при переводе используются только связки, для которых нет тэгов
//              transl_order или значение этого тэга равно 0 или 1 - то есть
//              базовые переводы.  
// 31.08.2009 - добавлены опция командной строки -param и директива #param для
//              задания глобальных параметров, например - флага учета N-грамм
//              в переводчике.
// 20.10.2009 - добавлен вывод в HTML файл результатов морфологического анализа
//              с тегированием словоформ грамматическими классами.
// 26.10.2009 - добавлен вывод в HTML файл результатов синтаксического анализа
//              в виде дерева с использованием символов псевдографики Unicode.
// 25.08.2012 - добавлена опция -sparse
// -----------------------------------------------------------------------------
//
// CD->25.02.2003
// LC->05.09.2014
// --------------

#if !defined SOL_CAA
 #error Syntax analyzer is not available
#endif

#include <lem/keyboard.h>
#include <lem/shell.h>
#include <lem/system_config.h>

#include <lem/solarix/version.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/aa_autom.h>
#include <lem/solarix/sentencebroker.h>
#include <lem/solarix/sg_only_main_translations_tagfilter.h>
#include <lem/solarix/sg_tag_or_null_tagfilter.h>
#include <lem/solarix/print_variator.h>
#include <lem/solarix/ThesaurusTagDefs.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/TreeMatchingExperience.h>
#include <lem/solarix/LA_SynPatternTrees.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/SynPatternTreeNodeMatchingResults.h>
#include <lem/solarix/LemmatizatorStorage.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/MorphologyModels.h>
#include <map>

#include "syntax.h"

using namespace std;
using namespace lem;
using namespace Solarix;

SyntaxShell::SyntaxShell(void)
{
 elapsed.start();
 default_language = UNKNOWN;
 CompleteAnalysisOnly=true;
 EnableFilters=true;
 MaxTimeout=0; // по умолчанию лимита времени нет
 MaxAlt=0; // по умолчанию перебор всех вариантов в нисходящем анализе
 FindFacts=false;
 MaxSkipToken=UNKNOWN; // по умолчанию запрещаем пропускать токены

 run_mode = SyntaxMode;
 
 return;
}


void SyntaxShell::SetMode( RunMode new_mode )
{
 run_mode = new_mode;
 return;
}


void SyntaxShell::LazyLexicon( bool _lazy_lexicon ) 
{
 lazy_lexicon = _lazy_lexicon;
}


void SyntaxShell::LoadDictionary()
{
 nul_tty.Open( lem::Path(NULL_DEVICE) );
 sol_id = new Dictionary( &nul_tty, merr );

 lem::Path dict_path;

 if( !dict_dir.empty() && dict_dir.DoesExist() && !dict_dir.IsFolder() )
  {
   dict_path = dict_dir;
  }
 else
  {
   lem::Path folder(dict_dir);

   // Сначала попробуем найти словарь в текущем каталоге, затем
   // в каталоге ..\bin-windows (или ..\bin-linux), а уже потом
   // спросим пользователя. Это сделано для удобства запуска
   // программы как при отладке, так и в рамках дистрибутива SDK.
   int ivar=0;

   while(true)
    {
     dict_path = folder;
     dict_path.ConcateLeaf(L"dictionary.xml");

     if( dict_path.DoesExist() )
      break;

     ivar++;
     if( ivar==1 )
      {
       #if defined LEM_WINDOWS
        #if defined LEM_64
        folder = lem::Path(L"..\\bin-windows64");
        #else
        folder = lem::Path(L"..\\bin-windows");
        #endif
       #else
        #if defined LEM_64
        folder = lem::Path(L"../bin-linux64");
        #else
        folder = lem::Path(L"../bin-linux");
        #endif
       #endif
      }
     else if( ivar==2 )
      {
       #if defined LEM_WINDOWS
        #if defined LEM_64
        folder = lem::Path(L"..\\..\\..\\..\\bin-windows64");
        #else
        folder = lem::Path(L"..\\..\\..\\..\\bin-windows");
        #endif
       #else
        #if defined LEM_64
        folder = lem::Path(L"../../../../bin-linux64");
        #else
        folder = lem::Path(L"../../../../bin-linux");
        #endif
       #endif
      }
     else if( ivar==3 )
      {
       #if defined LEM_WINDOWS
        #if defined LEM_64
        folder = lem::Path(L".\\bin-windows64");
        #else
        folder = lem::Path(L".\\bin-windows");
        #endif
       #else
        #if defined LEM_64
        folder = lem::Path(L"./bin-linux64");
        #else
        folder = lem::Path(L"./bin-linux");
        #endif
       #endif
      }
     else if( ivar==4 )
      {
       #if defined LEM_WINDOWS
        #if defined LEM_64
        folder.clear();
        #else
        folder = lem::Path(L"..");
        #endif
       #else
        #if defined LEM_64
        folder.clear();
        #else
        folder = lem::Path(L"..");
        #endif
       #endif
      }
     else
      {
       folder = lem::Shell::AskFolder( L"Enter the name of folder containing dictionary files:" );
      }
    }
  }

 mout->printf( "Loading dictionary from %vfA%us%vn...", dict_path.GetUnicode().c_str() );
 mout->flush();

 Load_Options opt;
 opt.affix_table = true;
 opt.load_semnet = true;
 opt.seeker = true;
 opt.ngrams = true;
 opt.lexicon = !lazy_lexicon;


 bool ok=false;

 try
  {
   ok = sol_id->LoadModules( dict_path, opt );
  }
 catch(...)
  {
   ok = false;
  }

 if( !ok )
  {
   mout->printf( "\n\nERROR!\nIncompatible dictionary version\n" );
   lem::Process::Exit();
  }

 mout->printf( " %vfAok%vn\n" );

 lem::MCollect<int> langs;
 default_language = sol_id->GetLanguages(langs);

 transl0_tag = new Solarix::TF_TranslOrderZero(*sol_id);
 transl1_tag = new Solarix::TF_OnlyMainTransl(*sol_id);

 mout->printf( "Enter %vfE#help%vn to read online help.\n" );

 return;
}


void SyntaxShell::SetLanguage( const UCString &lang_name )
{
 if( lang_name.eqi(L"autodetect") || lang_name.eqi(L"auto") )
  {
   // Язык нужно определять для каждой вводимой фразы.
   default_language = UNKNOWN;
   guess_language = true;
  }
 else
  {
   default_language = sol_id->GetSynGram().Find_Language(lang_name);

   // Проверим, что этот язык есть среди определенных в лексиконе
   lem::MCollect<int> langs;
   sol_id->GetLanguages(langs);
   if( langs.find(default_language)==UNKNOWN )
    {
     merr->printf( "\n%vfCError:%vn target language %vfE%us%vn is not available in lexicon", lang_name.c_str() );
     throw E_BaseException();
    }
  }

 return;
}


SyntaxShell::~SyntaxShell(void)
{
 return;
}

const UFString SyntaxShell::enter_cmd( const char *Prompt ) const
{
 UFString str;
 while( str.empty() )
  {
   mout->printf( "%vfF%s", Prompt ); // Command prompt
   str = mkey->ask_ufstring();
   mout->printf( "%vn" );
   str.trim();
  }

 return str;
}

// ****************************************
// Entering the command processing loop.
// ****************************************
void SyntaxShell::main_loop(void)
{
 // Если язык по умолчанию не задан, то запросим его имя с консоли.
 if( default_language==UNKNOWN && !guess_language )
  {
   lem::MCollect<int> langs;
   default_language = sol_id->GetLanguages(langs);
   if( default_language==UNKNOWN || langs.size()>1 )
    {
     while(true)
      {
       mout->printf( "Please select the language:\n" );
       if( langs.empty() )
        {
         lem::Ptr<LanguageEnumerator> lenum( sol_id->GetSynGram().languages().Enumerate() );
         while( lenum->Fetch() )
          langs.push_back( lenum->GetId() );
        }

       for( lem::Container::size_type i=0; i<langs.size(); ++i )
        {
         mout->printf( "[%vfA%d%vn] - %vfE%us%vn\n", i, sol_id->GetSynGram().languages()[langs[i]].GetName().c_str() );
        } 

       mout->printf( "%vfA-1%vn - do not set default language for syntax analysis\n\n?" );
       int ilang = mkey->ask_int();
       if( ilang==UNKNOWN )
        {
         default_language = UNKNOWN;
         break;
        }

       if( ilang>=0 )
        {
         default_language = langs[ilang];
         break;
        }
      } 
    }
  }

 mout->eol();

#if LEM_DEBUGGING==1
//_CrtMemState ms1,ms2,ms3;
#endif

 int ipass=0;
 for(;;ipass++)
  {
   UFString str;

   if( !pre_entered_phrase.empty() )
    {
     str = pre_entered_phrase;
     pre_entered_phrase.clear();
     mout->printf( "\n> %us\n", str.c_str() );
    }
   else
    {
     str = enter_cmd( debugger.IsNull() ? ": " : ":> " );
    }

   if( str==L"#exit" )
    break;

   if( TryCommand(str) )
    continue;

   if( run_mode==TokenizerMode )
    {
     Tokenize(str);
    }
   else if( run_mode==LemmatizerMode )
    {
     Lemmatize(str);
    }
   else if( run_mode==SpeakerMode )
    {
     Speak(str);
    }
   else
    {
     lem::ElapsedTime total_et; total_et.start();
     PerformSyntacticAnalysis(str);
     total_et.stop();
     const int msec_elapsed = total_et.msec();

     if( traceon )
      lem::mout->printf( "Elapsed time: %d millisec\n", msec_elapsed );
    }
  }

 return;
}




void SyntaxShell::ShowHelp(void) const
{
 mout->printf(
             "Commands:\n\n"
             " %vfE#exit%vn         - quit the program\n"
             " %vfE#info%vn         - print the dictionary statistics\n"
             " %vfE#debug%vn        - enable interactive debugger\n"
             " %vfE#nodebug%vn      - disable interactive debugger (default)\n"
             " %vfE#syntax%vn       - syntax analyzer mode (default)\n"
             " %vfE#morphology%vn   - morphology analyzer mode\n"
             " %vfE#tokenize%vn     - tokenizer mode\n"
             " %vfE#lemmatize%vn    - lemmatizer mode\n"
             " %vfE#speak%vn        - text-to-speech mode\n"
             "\n"

             " %vfE#maxalt NN%vn        - beam size (max branching factor)\n"
             " %vfE#maxskiptoken NN%vn  - max number of token to skip\n"           
             " %vfE#allow_incomplete%vn - allow partial analysis\n"
             " %vfE#disallow_incomplete%vn - disallow partial analysis (default)\n"
             " %vfE#disable_filters%vn - disable preliminary and collocation filters\n"
             " %vfE#enable_filters%vn  - enable preliminary and collocation filters\n"
             " %vfE#fuzzyon%vn         - allow fuzzy word recognition\n"
             " %vfE#fuzzyoff%vn        - disallow fuzzy word recognition\n"
             " %vfE#allow_model%vn     - enable language model usage in word tagging\n"
             " %vfE#disallow_model%vn  - disable language model usage\n"

             "\n"

             " %vfE#show%vn         - print the results of analysis\n"
             " %vfE#tree%vn         - print the dependency graph\n"
             " %vfE#recog%vn        - print the word recognitions\n"
             " %vfE#traceon%vn      - trace the rules names while parsing\n"
             " %vfE#traceoff%vn     - do not trace\n"
             "\n"
            );
}



bool SyntaxShell::TryCommand( const lem::UFString &_str )
{
 LEM_CHECKIT_Z( !_str.empty() );

 if( _str==L"#help" || _str==L"?" )
  {
   ShowHelp();
   return true;
  }

 if( _str.front()!=L'#' )
  return false;

 if( _str.eq_beg( L"# " ) )
  return true; // комментарий


 if( _str.eq_beg( L"#timeout" ) )
  {
   lem::MCollect<UCString> toks;
   lem::parse( _str, toks, false );
   MaxTimeout = lem::to_int( toks[1] );
   return true;
  }

 if( _str.eq_beg( L"#maxalt" ) )
  {
   lem::MCollect<UCString> toks;
   lem::parse( _str, toks, false );
   MaxAlt = lem::to_int( toks[1] );
   lem::mout->printf( "MaxAlt=%d\n", MaxAlt );
   return true;
  }

 if( _str.eq_beg( L"#maxskiptoken" ) )
  {
   lem::MCollect<UCString> toks;
   lem::parse( _str, toks, false );
   MaxSkipToken = lem::to_int( toks[1] );

   lem::mout->printf( "MaxSkipToken=%d\n", MaxSkipToken );

   if( MaxSkipToken>0 )
    CompleteAnalysisOnly = false;

   if( MaxAlt==0 || MaxAlt==lem::int_max )
    {
     lem::mout->printf( "Attention: it is highly recommended to use %vfE#maxalt%vn NNN in order to limit the search tree depth\n" );
    }

   return true;
  }

 if( _str.eq_beg( L"#sem" ) )
  {
   lem::MCollect<UCString> toks;
   lem::parse( _str, toks, false );
   FindFacts = lem::to_bool( toks[1] );
   return true;
  }

 if( _str.eqi( L"#info" ) )
  {
   ShowDictionaryInfo();
   return true;
  }

 if( _str.eqi( L"#disconnect" ) )
  {
   sol_id.Delete();
   lem::mout->printf( "Dictionary database is disconnected.\n" );
   return true;
  }

 if( _str.eqi( L"#connect" ) )
  {
   LoadDictionary();
   return true;
  }

 if( _str.eq_begi( L"#tag" ) )
  {
   if( _str==L"#tag-" )
    {
     // Сбрасываем установленный фильтр
     tags_ptr.Delete();
     tags.clear();
     return true;
    }

   lem::Collect<lem::UFString> toks;
   lem::parse( UFString(_str.c_str()+4), toks, L"=" );
   UCString tag_name, tag_value;

   if( toks.size()>0 )
    tag_name = toks[0].c_str();

   if( toks.size()>1 )
    tag_value = toks[1].c_str();

   tag_name.trim();
   tag_value.trim();

   const int itag = sol_id->GetSynGram().Get_Net().FindTag(tag_name);
   if( itag==UNKNOWN )
    {
     lem::mout->printf( "Tag [%vfE%us%vn] not found\n", tag_name.c_str() );
     return true;
    }

   const ThesaurusTag &tt = sol_id->GetSynGram().Get_Net().GetTagDefs()[itag];

   if( tt.CountValues()>0 )
    { 
     int ivalue = tt[tag_value];
     if( ivalue==UNKNOWN )
      {
       lem::mout->printf( "Tag value [%vfE%us%vn] not found\n", tag_value.c_str() );
       return true;
      }
    }

   tags_ptr = new TF_TagOrNullFilter( *sol_id, tag_name, tag_value );
   return true;
  }


 if( _str.eq_begi( L"#param" ) )
  {
   if( _str==L"#param-" )
    {
     // Очищаем список параметров.
     params.clear();
     return true;
    }

   lem::Collect<lem::UFString> toks;
   lem::parse( UFString(_str.c_str()+7), toks, L"=" );
   UCString param_name, param_value;

   if( toks.size()>0 )
    param_name = toks[0].c_str();

   if( toks.size()>1 )
    param_value = toks[1].c_str();

   param_name.trim();
   param_value.trim();

   params.push_back( std::make_pair( param_name, param_value ) );

   return true;
  }



 lem::UFString str = lem::right( _str, _str.length()-1 );

 lem::zbool ret;

 if( str==L"debug" )
  {
   SetDebug(true);
   ret=true;
  }
 else if( str==L"nodebug" )
  {
   SetDebug(false);
   ret=true;
  }
 else if( str==L"traceon" )
  {
   SetDebug(true);
   traceon=true;
   debugger->Trace(true);
   ret=true;
  }
 else if( str==L"traceoff" )
  {
   traceon=false;

   if( debugger.NotNull() )
    debugger->Trace(true);

   ret=true;
  }
 else if( str==L"fuzzyon" )
  {
   allow_fuzzy = true;
   mout->printf( "Fuzzy projection is now %vfAON%vn\n" );
   ret=true;
  }
 else if( str==L"fuzzyoff" )
  {
   allow_fuzzy = false;
   mout->printf( "Fuzzy projection is now %vfDOFF%vn\n" );
   ret=true;
  }
 else if( str=="disable_filters" )
  {
   EnableFilters=false;
   ret = true;
  }
 else if( str=="enable_filters" )
  {
   EnableFilters=true;
   ret = true;
  }
 else if( str=="schedule1" )
  {
   CompleteAnalysisOnly=true;
   UseTopDownThenSparse=true;
   mout->printf( "Workflow=%vfATOP-DOWN, TOP-DOWN INCOMPLETE%vn\n" );
   ret=true;
  }
 else if( str==L"topdown" )
  {
   UseTopDownThenSparse=false;
   CompleteAnalysisOnly=true;
   mout->printf( "%vfAtop-down%vn analyzer is activated\n" );
   ret=true;
  }
 else if( str==L"allow_incomplete" )
  {
   CompleteAnalysisOnly = false;
   mout->printf( "Incomplete analysis is %vfAALLOWED%vn\n" );
   ret=true;
  }
 else if( str==L"disallow_incomplete" )
  {
   CompleteAnalysisOnly = true;
   mout->printf( "Incomplete analysis is %vfDDISALLOWED%vn\n" );
   ret=true;
  }
 else if( str==L"allow_reco" )
  {
   UseReconstructor = true;
   mout->printf( "Token reconstructor is %vfAALLOWED%vn\n" );
   ret=true;
  }
 else if( str==L"disallow_reco" )
  {
   UseReconstructor = false;
   mout->printf( "Token reconstructor is %vfDDISALLOWED%vn\n" );
   ret=true;
  }
 else if( str==L"allow_model" )
  {
   if( sol_id->GetLexAuto().GetModel().GetSequenceLabeler().IsAvailable() || sol_id->GetLexAuto().GetModel().GetClassifier().IsAvailable() )
    {
     ApplyModel = true;
     mout->printf( "Morphology model is enabled\n" );
    }
   else
    {
     mout->printf( "Morphology model is not available\n" );
    }

   ret=true;
  }
 else if( str==L"disallow_model" )
  {
   ApplyModel = false;
   mout->printf( "Morphology model is disabled\n" );
   ret=true;
  }
 else if( str==L"show" )
  {
   if( current_analysis.NotNull() )
    {
     const Res_Pack &pack = current_analysis->GetPack();

     mout->printf( "\nResult pack contains %vfE%d%vn variators:\n", pack.vars().size() );

     if( run_mode==MorphologyMode )
      {
       for( lem::Container::size_type i=0; i<pack.vars().size(); i++ )
        {
         const Variator * var = pack.vars()[i];
         for( lem::Container::size_type k=0; k<var->size(); ++k )
          {
           const Tree_Node & root = var->get(k);
           mout->printf( "%d: ", CastSizeToInt(k) );
           root.Print( *lem::mout, sol_id->GetSynGram(), -1, true );
           mout->eol();
          }

         mout->eol();
         mout->eol();
        }
      }
     else
      {
       for( lem::Container::size_type i=0; i<pack.vars().size(); i++ )
        {
         pack.vars()[i]->PrintV( *mout, sol_id->GetSynGram(), true );
         mout->eol();
         mout->eol();
        }
      }
    }
 
   ret=true;
  }
 else if( str==L"tree" )
  {
   if( current_analysis.NotNull() )
    {
     const Res_Pack &pack = current_analysis->GetPack();
     Solarix::print_syntax_tree( current_analysis->GetString(), current_analysis->GetPack(), *sol_id, *lem::mout, false, true );
    }
 
   ret=true;
  }
 else if( str.eq_beg("recog" ) )
  {
   if( current_analysis.NotNull() )
    {
     lem::mout->eol();
     current_analysis->GetLexer().PrintRecognitions( *lem::mout );
    }
 
   return true;
  }
 else if( str==L"tokenize" )
  {
   SetMode(TokenizerMode);
   ret=true;
  }
 else if( str==L"lemmatize" )
  {
   SetMode(LemmatizerMode);
   ret=true;
  }
 else if( str==L"speak" )
  {
   SetMode(SpeakerMode);
   ret=true;
  }
 else if( str==L"syntax" )
  {
   SetMode(SyntaxMode);
   ret=true;
  }
 else if( str==L"morphology" )
  {
   SetMode(MorphologyMode);
   ret=true;
  }
 else if( str==L"debugger" )
  {
   if( debugger.NotNull() )
    debugger->ManageBreakpoints();

   ret=true;
  }
 else
  {
   lem::mout->printf( "Invalid command %vfC%us%vn\n", str.c_str() );
   ret=true;
  }

 return ret;
}






void SyntaxShell::Exiting(void)
{
 return;
}


// ************************************************
// Выполнение анализа.
//
// Возвращает: true - анализ завершен успешно
//             false - анализ не удалось выполнить.  
// ************************************************
bool SyntaxShell::PerformSyntacticAnalysis( const UFString & str )
{
 TrTrace *trace = debugger.NotNull() ? &*debugger : (TrTrace*)NULL;

 if( debugger.NotNull() )
  {
   trace->StartNewSentence();

   // Запускаемся под отладчиком.
   debugger->BeforePhrase();
  }

 try
  {
   current_analysis = new WrittenTextAnalysisSession( sol_id.get(), trace );
   current_analysis->params.SetLanguageID(default_language);
   current_analysis->params.CompleteAnalysisOnly = CompleteAnalysisOnly;
   current_analysis->params.AllowPrimaryFuzzyWordRecog = allow_fuzzy;
   current_analysis->params.UseTokenReconstruction = UseReconstructor;
   current_analysis->params.UseSparsePatterns = false;
   current_analysis->params.UseTopDownThenSparse = UseTopDownThenSparse;
   current_analysis->params.ApplyModel = ApplyModel;
   current_analysis->params.timeout.max_elapsed_millisecs = MaxTimeout;
   current_analysis->params.timeout.max_alt = MaxAlt;
   current_analysis->params.timeout.max_bottomup_trees = MaxAlt;

   if( MaxSkipToken>=0 )
    {
     current_analysis->params.MaxSkipToken = MaxSkipToken;
     current_analysis->params.SkipOuterToken = MaxSkipToken>0;
    }
   else
    {
     // параметр не задан, поэтому ориентируемся на разрешение неполного анализа.
     current_analysis->params.ConfigureSkipToken();
    }

   current_analysis->params.SkipInnerTokens = false;

   current_analysis->FindFacts = FindFacts;


   if( !EnableFilters )
    {
     // отключаем предварительные фильтры
     current_analysis->params.max_filter_len=0;
     current_analysis->params.ApplyCollocFilters=false;
    }

   if( run_mode==MorphologyMode )
    // Только морфологический анализ
    current_analysis->MorphologicalAnalysis(str);
   else if( run_mode==SyntaxMode )
    // Синтаксический анализ
    current_analysis->SyntacticAnalysis(str);
  }
 catch( const E_BaseException & x )
  {
   merr->printf( "%vfDError occured during analysis:\n%us%vn\n", x.what() );

   if( trace!=NULL )
    {
     merr->printf( "Call stack:\n" );
     trace->PrintStack(*merr);
    }

   return false;
  }
 catch(...)
  {
   merr->printf( "%vfDError occured during analysis.%vn\n" );

   if( trace!=NULL )
    {
     merr->printf( "Call stack:\n" );
     trace->PrintStack(*merr);
    }

   return false;
  }

 if( debugger.NotNull() )
  { 
   debugger->AfterPhrase();
  }

 bool success=false;

 // Print the results of analysis.
 if( current_analysis!=NULL )
  {
   if( run_mode==MorphologyMode )
    {
     Solarix::print_morphology( current_analysis->GetString(), current_analysis->GetPack(), *sol_id, *mout, false );
    }
   else
    {
     for( lem::Container::size_type i=0; i<current_analysis->GetPack().vars().size(); i++ )
      {
       current_analysis->GetPack().vars()[i]->PrintRoots( *mout, false, false );
       mout->eol(); 
      }

     mout->printf( "%vn\n" );
    }
  }

 return success;
}





// *******************************
// Проверка работы лексера.
// *******************************
void SyntaxShell::Tokenize( const UFString &str )
{
 TrTrace *trace = debugger.NotNull() ? &*debugger : (TrTrace*)NULL;

 if( trace!=NULL )
  {
   trace->StartNewSentence();
  }

 current_analysis = new WrittenTextAnalysisSession( sol_id.get(), trace );
 current_analysis->params.SetLanguageID(default_language);
 current_analysis->params.AllowPrimaryFuzzyWordRecog = allow_fuzzy;
 current_analysis->params.UseTokenReconstruction = UseReconstructor;
 current_analysis->params.RecognizeWordforms = false;

 current_analysis->Tokenize(str);

 // Лексер обычно работает в ленивом режиме, но для наглядности отладки мы заставим сейчас
 // его пробежаться по всем токенам и достичь листьев, список которых он вернет в final_tokens.
 lem::MCollect<const LexerTextPos*> final_tokens;
 current_analysis->GetLexer().FetchEnds( current_analysis->GetLexer().GetBeginToken(), final_tokens, current_analysis->GetLexer().GetParams().GetMaxRightLeaves() );

 if( final_tokens.size()==1 )
  lem::mout->printf( "There is %vfE1%vn path:\n" );
 else
  lem::mout->printf( "There are %vfE%d%vn paths:\n", CastSizeToInt(final_tokens.size()) );
 
 // Теперь распечатаем все пути от начального токена до листьев.
 PrintLexerPerformance( current_analysis->GetLexer(), final_tokens );

 if( trace!=NULL )
  {
   trace->ShowLexerPerformance( current_analysis->GetLexer() );
  }
 
 return;
}





void SyntaxShell::Lemmatize( const UFString & str )
{
 lem::MCollect<lem::UCString> words;
 
 Solarix::Sentence sent;
 sent.Parse( str, false, sol_id.get(), default_language, NULL );

 words.push_back( L"~~BEGIN~~" );
 for( int i=0; i<CastSizeToInt(sent.size()); ++i )
  words.push_back( sent.GetWord(i) );
 words.push_back( L"~~END~~" );

 lem::MCollect<lem::UCString> lemmas;
 LemmatizatorStorage & lemm = sol_id->GetLemmatizer();
 lemm.Lemmatize( words, lemmas );

 lem::mout->eol();
 for( lem::Container::size_type i=1; i<lemmas.size()-1; ++i )
  {
   lem::mout->printf( "[%vfE%us%vn] ", lemmas[i].c_str() );
  } 
 lem::mout->eol();
 
 return;
}






void SyntaxShell::Speak( const UFString & phrase )
{
 #if defined SOL_USE_SPEAKER
 Speaker * speaker = sol_id->GetSpeaker();
 speaker->SetDefaultLanguage(default_language);
 speaker->Say( phrase, default_language );
 #endif

 return;
}




void SyntaxShell::PrintLexerPerformance( Solarix::BasicLexer & lexer, const lem::MCollect<const LexerTextPos*> & final_tokens )
{
 for( lem::Container::size_type i=0; i<final_tokens.size(); ++i )
  {
   lem::mout->printf( "#%vf9%d%vn-->", CastSizeToInt(i) );
   PrintLexerPerformance( lexer, final_tokens[i] );
   lem::mout->eol();
  }

 return;
}



void SyntaxShell::PrintLexerPerformance( Solarix::BasicLexer & lexer, const LexerTextPos * token )
{
 // пройдем по цепочке назад и соберем список токенов в порядке от последнего к первому.
 lem::MCollect<const LexerTextPos*> chain;
 chain.push_back( token );
 const LexerTextPos * cur_token = token;
 while( !cur_token->IsBegin() )
  {
   chain.push_back( cur_token->GetPrev() );
   cur_token = cur_token->GetPrev();
  }

 // теперь напечатаем этот список в обратном порядке.
 for( int i=CastSizeToInt(chain.size())-1; i>=0; --i )
  {
   const LexerTextPos * token = chain[i];

   const Word_Form * wordform = token->GetWordform();

   if( token->IsBegin() || token->IsEnd() )
    lem::mout->printf( " %vf6[%vn%vf4%us%vf6]%vn", wordform->GetName()->c_str() );
   else if( wordform->GetEntryKey()==sol_id->GetLexAuto().GetUnknownEntryKey() )
    lem::mout->printf( " %vf6[%vn%vfC%us%vf6]%vn", wordform->GetName()->c_str(), wordform->VersionCount() );
   else if( wordform->VersionCount()>1 )
    lem::mout->printf( " %vf6[%vn%us/%vfF%d%vf6]%vn", wordform->GetName()->c_str(), wordform->VersionCount() );
   else
    lem::mout->printf( " %vf6[%vn%us%vf6]%vn", wordform->GetName()->c_str() );

   if( token->GetScore()<0 )
    lem::mout->printf( "(%vfC%d%vn)", token->GetScore() );
   else if( token->GetScore()>0 )
    lem::mout->printf( "(%vfA%d%vn)", token->GetScore() );
  }
 
 return;
}



// *************************************
// Включаем или отключаем отладчик
// *************************************
void SyntaxShell::SetDebug( bool f )
{
 if( f && !debug )
  {
   mout->printf( "Debugger enabled.\n" );
   debugger = new TrDebugger(&*sol_id);
  }
 else if( !f && debug )
  {
   mout->printf( "Debugger disabled.\n" );
   debugger = NULL;
  }

 sol_id->trace_log = debugger;
 debug = f;

 return;
}





void SyntaxShell::SetThesaurusTags( const lem::Collect< std::pair<UCString /*tag*/, UCString /*value*/> > & Tags )
{
 tags = Tags;

 if( tags.empty() )
  tags_ptr.Delete();
 else 
  tags_ptr = sol_id->GetSynGram().Get_Net().CompileTags( tags );

 return;
}


void SyntaxShell::SetEnvParams( const lem::Collect< std::pair<UCString /*param*/, UCString /*value*/> > & Params )
{
 params = Params;
 return;
}


lem::UFString SyntaxShell::VarToStr( const Solarix::Variator &var ) const
{
 return Solarix::VarToStr( *sol_id, var );
}


void SyntaxShell::ShowDictionaryInfo(void)
{
 const int nentry = sol_id->GetSynGram().GetnEntry();
 mout->printf( "\n--- Dictionary status ---\n\n" );
 mout->printf( "Database version=%s\n", sol_id->GetVersion().string().c_str() );
 mout->printf( "Number of word entries=%d\n", nentry );
 return;
}

void SyntaxShell::SetPhrase( const lem::UFString &x )
{
 pre_entered_phrase = x;
 return;
}


// ------------ ГЕНЕРАТОР

class GeneratorLexer : public BasicLexer
{
 private:
  bool UseNGrams; // использовать N-граммы для фильтрации генерируемых токенов
  lem::MCollect<UCString> words;

  typedef std::map< const LexerTextPos*, int > TOKEN2WORD;
  TOKEN2WORD token2word;

  typedef std::multimap< int, const Word_Form* > INDEX2WORDFORM;
  INDEX2WORDFORM index2wordform;

  void CollectUsedWords( const LexerTextPos * t, lem::MCollect<int> & indeces ) const;

 public:
  GeneratorLexer(
                 const lem::MCollect<UCString> & _words,
                 Solarix::Dictionary * _dict,
                 const TextRecognitionParameters & _params,
                 TrTrace * _trace
                );

  virtual bool Fetch( const LexerTextPos * current, const TokenExpectation * unused, lem::MCollect<const LexerTextPos*> & next );
};


GeneratorLexer::GeneratorLexer(
                               const lem::MCollect<UCString> & _words,
                               Solarix::Dictionary * _dict,
                               const TextRecognitionParameters & _params,
                               TrTrace * _trace
                              )
 : BasicLexer(_dict,_params,_trace), words(_words)
{
 UseNGrams = dict->IsNgramsAvailable();

 for( int index=0; index<words.size(); ++index )
  {
   const lem::UCString & word = words[index];

   //int case_flags = casing_coder->Lower;
   TokenizationTags * tags=NULL;
   lem::Ptr<Word_Form> wf( dict->GetLexAuto().ProjectWord( word, 0, 1, tags, params, trace==NULL ? NULL : trace->RecognizerTrace() ) );
   lem_rub_off(tags);

   // Определим словарные статьи.
   lem::MCollect<int> ekeys;
   for( int i=0; i<wf->VersionCount(); ++i )
    {
     const int ekey = wf->GetVersion(i)->GetEntryKey();
     if( ekeys.find(ekey)==UNKNOWN )
      {
       ekeys.push_back(ekey);

       const SG_Entry & e = dict->GetSynGram().GetEntry(ekey);
       // Из всех форм генерируем отдельные словоформы.
       for( int k=0; k<e.forms().size(); ++k )
        {
         const SG_EntryForm & f = e.forms()[k];

         RC_Lexem name( new Lexem( lem::to_lower(f.name()) ) );
         RC_Lexem normalized_name( new Lexem( f.name() ) );

         const CP_Array & pairs = f.coords();

         Word_Form * wf2 = new Word_Form( name, normalized_name, ekey, pairs, lem::Real1(100) );
         wordforms.push_back( wf2 );

         index2wordform.insert( std::make_pair( index, wf2 ) );
        }
      }
    }
  }

 return;
}


void GeneratorLexer::CollectUsedWords( const LexerTextPos * t, lem::MCollect<int> & indeces ) const
{
 TOKEN2WORD::const_iterator it = token2word.find(t);
 if( it!=token2word.end() )
  indeces.push_back( it->second );

 if( !t->IsBegin() && t->GetPrev()!=NULL )
  CollectUsedWords( t->GetPrev(), indeces );

 return;
}


bool GeneratorLexer::Fetch( const LexerTextPos * current, const TokenExpectation * unused, lem::MCollect<const LexerTextPos*> & next )
{
 if( current==NULL )
  {
   next.push_back( GetBeginToken() );
   return true;
  }

 if( current->IsEnd() )
  {
   return false;
  }

 next.clear();

 // поищем в кэше уже найденные продолжения.
 std::pair<CACHED_EDGES::const_iterator,CACHED_EDGES::const_iterator> p_edges = edges.equal_range(current);
 if( p_edges.first!=p_edges.second )
  {
   for( CACHED_EDGES::const_iterator it=p_edges.first; it!=p_edges.second; ++it )
    {
     next.push_back( it->second );
    }

   return true;
  }

 // Посмотрим, какие токены были перед данным, и какие слова они уже использовали.
 lem::MCollect<int> indeces;
 CollectUsedWords( current, indeces );

/*
#if LEM_DEBUGGING==1
if( current->GetWordform()->GetName()->eqi(L"ловит") )
 {
  lem::mout->printf("!\n");
 }
#endif
*/

 bool token_created=false;
 lem::MCollect<const LexerTextPos*> matched_by_literal_ngrams, matched_by_normalized_ngrams, all_next_tokens;

 lem::Ptr<Ngrams> ngrams;
 lem::UCString prev_lemma;

 if( UseNGrams )
  ngrams = dict->GetNgrams();

 // Теперь неиспользованные ранее слова порождают новые токены.
 for( lem::Container::size_type i=0; i<words.size(); ++i )
  if( indeces.find(i)==UNKNOWN )
   {
    // слово не использовалось.
    typedef INDEX2WORDFORM::const_iterator IT;
    std::pair<IT,IT> p = index2wordform.equal_range( CastSizeToInt(i) );

    for( IT it=p.first; it!=p.second; ++it )
     {
      const Word_Form * wordform = it->second;
      const int word_index = current->IsRealWord() ? current->GetWordIndex()+1 : 0;
      const int start_pos = current->IsRealWord() ? (current->GetStartPosition()+current->GetWordLength()+1) : 0;

      // Нам нужно создать новый вариант этой словоформы.
      Word_Form * wf = new Word_Form( *wordform, true );
      wf->SetOriginPos( word_index );
      wordforms.push_back(wf);

      LexerTextPos * new_token = new LexerTextPos( current, wf, 0, start_pos, wf->GetName()->length(), word_index );
      positions.push_back(new_token);

      all_next_tokens.push_back( new_token );

      token2word.insert( std::make_pair(new_token,CastSizeToInt(i)) );

      token_created = true;

      // Слово сочетается с предыдущим?
      if( UseNGrams && current->IsRealWord() )
       {
        const lem::UCString & prev_word = * current->GetWordform()->GetNormalized();
        const lem::UCString & new_word = * new_token->GetWordform()->GetNormalized();
        
        float w2=0;
        int iw2=0;
        if( ngrams->FindLiteralNGrams( prev_word, new_word, w2, iw2 ) )
         {
          // TODO: использовать частотность подошедшей N-граммы для взвешивания созданных токенов.
          matched_by_literal_ngrams.push_back( new_token );
         }
        else
         {
          if( prev_lemma.empty() )
           {
            const int prev_ekey = current->GetWordform()->GetEntryKey();
            const SG_Entry & prev_e = dict->GetSynGram().GetEntry( prev_ekey );
            prev_lemma = prev_e.GetName();
           }

          const int new_ekey = new_token->GetWordform()->GetEntryKey();
          const SG_Entry & new_e = dict->GetSynGram().GetEntry( new_ekey );
          const lem::UCString & new_lemma = new_e.GetName();

          if( ngrams->FindRawNGrams( prev_lemma, new_lemma, w2, iw2 ) )
           {
            // TODO: использовать частотность подошедшей N-граммы для взвешивания созданных токенов.
            matched_by_normalized_ngrams.push_back( new_token );
           }
         }
       }
     }
   }

 if( !matched_by_literal_ngrams.empty() )
  {
   // найдена по крайней мере одна буквальная 2-грамма, поэтому отбрасываем все неподтвержденные варианты токенов.
   next = matched_by_literal_ngrams;
  }
 else if( !matched_by_normalized_ngrams.empty() )
  {
   next = matched_by_normalized_ngrams;
  }
 else
  {
   next = all_next_tokens;
  }

 for( lem::Container::size_type i=0; i<next.size(); ++i )
  {
   edges.insert( std::make_pair(current, const_cast<LexerTextPos*>( next[i] ) ) );
  }


/*
 #if LEM_DEBUGGING==1
 lem::mout->printf( "%60h-\n" );
 for( lem::Container::size_type i=0; i<next.size(); ++i )
  {
   lem::mout->printf( "FETCHED: %us(%p) -> %us(%p)\n", current->GetWordform()->GetName()->c_str(), current, next[i]->GetWordform()->GetName()->c_str(), next[i] );
  }
 #endif
*/


 if( !token_created )
  {
   // Возвращаем правую границу.
   next.push_back( GetEndToken(current) );
   return true;
  }

 return false;
}
