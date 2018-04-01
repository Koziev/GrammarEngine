// -----------------------------------------------------------------------------
// File YC.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://www.wordysoft.com
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// YGRES - dictionary compiler.
// Программа YGRES - КОМПИЛЯТОР СЛОВАРЯ.
//
// ENG: This program translates the text description of the dictionary (in text
//      files) into the binary form and/or SQL script.
//
// RUS: По текстовому описанию Словаря (один или несколько файлов) формирует бинарное
//      представление. Создаваемое представление Словаря значительно ускоряет работу
//      с информацией за счет предварительной обработки и реструктуризации,
//      индексации, бинаризации and so forth.
//
// 15.05.2006 - добавлена опция -outdir=PPP для задания каталога с создаваемыми
//              бинарными файлами словаря.
//
// 27.05.2006 - добавлена опция -ldsize=NNN для задания размера справочника лексем
//
// 23.07.2006 - исправлена работа с путями для совместимости с Linux
//
// 20.11.2006 - изменена схема генерации правил для стеммера и алгоритма рутинга
//
// 26.05.2007 - в версии 3.2 тезаурус сохраняется в отдельном файле.
//
// 23.09.2007 - введена проверка существования каталога -outdir
//
// 11.12.2007 - введена работа с SQL тезаурусом
//
// 30.03.2008 - в файл dictionary.xml вписывается строка <ngrams>.</ngrams> для
//              автозагрузки БД N-грамм
//
// 19.04.2008 - в файл dictionary.xml вписывается блок <ocr>
//
// 27.04.2008 - в файл dictionary.xml вписываются метки версий компилятора Ygres
//              и номер версии словаря.
// 21.01.2009 - экспорт словаря в формате SQL перенесен в утилиту YMAP.
// 05.03.2009 - переименован в Compiler.
// 16.08.2009 - введена инкрементальная компиляция - пересборка только
//              синтаксического анализатора.
// 04.01.2010 - добавлена генерация базы лемматизатора
// 17.03.2010 - если опции -save_seeker, -save_affixes и -save_prefix_searcher
//              не заданы, то в генерируемом XML файле нет соответствующих
//              узлов <seeker>, <affixes>, <prefix_entry_searcher> 
// 29.08.2010 - убираем код поддержки версии LITE
// 13.09.2010 - улучшена трассировка активности в консоли - добавлены сообщения
//              о сохранении отдельных модулей. 
// 26.12.2010 - в dictionary.xml вписывается узел <lemmatizer>
//
// 01.10.2011 - добавлены опции -rebuild_lemmatizer и -rebuild_pes для
//              генерации только лемматизатора и таблиц префиксного поиска.
// 28.03.2018 - рефакторинг кода
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->28.03.2018
// --------------

#include <lem/ustreams.h>
#include <lem/console_application.h>
#include <lem/conversions.h>
#include <lem/macro_parser.h>
#include <lem/logfile.h>
#include <lem/process.h>
#include <lem/shell.h>
#include <lem/startup.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/version.h>
#include <lem/solarix/ygres.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/aa_autom.h>
#include <lem/solarix/LexiconStorage_SQLITE.h>
#include <lem/solarix/ThesaurusStorage_SQLITE.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntries_File.h>


using namespace Solarix;
using namespace lem;
using namespace lem::Iridium;

// ***********************************************
// Описатели допустимых опций командной строки.
// ***********************************************
const char *SolOptTemplate =
"listing:list=1,"
"define:d=2:Fs,"
"version=4,"   // -version
"silent=6,"
"source:s=7,"
"x=8:Fi,"
"help:h=12:FiO,"
"?=102:FiO,"
"optimize:o=14,"
"numerate:n=13,"
"journalize:j=15:Fi,"
"diction:dict=20:Fs,"
"dir=22:Fs,"
"nolinks=30,"
"nosounds=31,"
"sounds=32,"
"save_seeker=33,"
"save_affixes=34,"
"outdir=37:Fs,"
"ldsize=38:Fi,"
"cpp_rules=39,"
"recompile_syntax=40,"
"save_prefix_entry_searcher=41,"
"save_lemmatizer=42,"
"reverse_links=43:Fb,"
"preload=44:Fs,"
"entry_redefinition=45:Fb,"
"save_paradigmas=46,"
"offset=47:Fi,"
"enames=48:Fs,"
"file=49:Fs,"
"rebuild_lemmatizer=50,"
"rebuild_pes=51"
;



static char *defines = NULL;
static bool silence=false;  // Режим тихой компиляции для загрузки из текстового файла.
static bool source=false;   // Печатать в файле листинга лексемы транслируемого файла Словаря так, как их получает транслятор от препроцессора.
static bool lnum=false;     // Печатать в файле листинга номера строк транслируемого файла.
static bool help_him=false; // Требуется вывести краткую справку о правилах использования модуля.
static int help_i=0;        // Затребованный раздел Справки.
static bool do_optimize=false; // Выполнять оптимизацию скомпилированного Словаря.
static SQL_Production sql_version(""); // параметры версии сервера СУБД
static int trace_level=0; // Уровень трассировки работы Системы в Журнале.
static int code_page = UNKNOWN; // Индекс кодовой таблицы для информации в файлах.

static bool allow_links=true;   // Store semantic net links in binary dictionary file (option -nolinks)
static bool allow_sounds=false; // Store sounde records in binary dictionary file (option -nosounds)

static Dictionary_Config dict_cfg;

static bool save_seeker=false;
static bool save_affixes=false;
static bool cpp_rules=false; // компилировать итераторы и продукционные правила в C++ код
static bool recompile_syntax=false; // перекомпиляция только модуля синтаксиса
static bool save_prefix_entry_searcher=false;
static bool save_lemmatizer=false;
static bool rebuild_lemmatizer=false; // пересоздать только лемматизатор
static bool rebuild_pes=false; // пересоздать только таблицу префиксного поиска
static bool reverse_links=true; // генерировать обратные связи для тезауруса
static lem::Path preload_path; // путь dictionary.xml для опции -preload
static bool entry_redefinition=false; // по умолчанию не разрешаем переопределять словарные статьи
static bool save_paradigmas=false; // по умолчанию парадигмы не сохраняются в бинарном словаре
static lem::Path enames_path;

/*************************************************************
 Имя создаваемого бинарного файла Словаря по умолчанию, если
 пользователь не указал другого.
**************************************************************/
static const char *out_bin_name="diction.bin";

static UFString root_dir;
static UFString outdir; // folder to store the result binary files

static MCollect<int> in_names_type;
static Collect<FString> in_names; // list of make files to build the dictionary

static void Help( int help_i );
static void ShowBanner( OFormatter *out=lem::mout, bool verbose=false );
static void Save_Results( Compiler *C );
static void Compile_Project( Compiler *C );
static void Parse_Options( int argc, char *argv[] );
static Compiler *Create_Compiler(void);

#if defined LEM_WINDOWS
int _cdecl main( int argc, char *argv[] )
#else
int main( int argc, char *argv[] )
#endif
{
 lem::LemInit initer;
 boost::posix_time::ptime tm_start = lem::get_time();

 try
  {
   Parse_Options(argc,argv);
  }
 LEM_CATCH;

 if( lem::LogFile::IsOpen() )
  ShowBanner( &*lem::LogFile::logfile, true );


 // Пользователь запросил справку.
 if( help_him )
  {
   Help(help_i);
   return 1;
  }

 std::unique_ptr<Compiler> C( Create_Compiler() );

 #if defined SOL_LOADBIN
 if( recompile_syntax )
  {
   // Надо загрузить скомпилированные ранее модули.
   Path xml_path;

   if( preload_path.empty() )
    {
     xml_path = lem::Path(outdir);
     xml_path.ConcateLeaf( lem::Path(L"dictionary.xml") );
    }
   else
    {
     xml_path = preload_path;
    }

   mout->printf( "Loading dictionary from %vfA%us%vn...", xml_path.GetUnicode().c_str() ); mout->flush();

   Load_Options opt;
   opt.load_semnet=false;
   opt.affix_table=false;
   opt.seeker=false;
   opt.ngrams = false;

   bool ok=false;

   try
    {
     ok = C->sol_id->LoadModules( xml_path, opt );
     C->sol_id->BeforeSyntaxRecompilation();
    }
   catch( const lem::E_BaseException &ex )
    {
     ok = false;
     lem::mout->printf( "Error: %us\n", ex.what() );
    }
   catch( const std::exception &ex )
    {
     ok = false;
     lem::mout->printf( "Error: %s\n", ex.what() );
    }
   catch(...)
    {
     ok = false;
     mout->printf( "\n\nError: incompatible dictionary version or damaged database files\n" );
    }

   if( !ok )
    {
     lem::Process::Exit(1);
    }

   mout->printf( "%vfAOK%vn\n" );
  }
 
 if( !recompile_syntax && !preload_path.empty() )
  {
   mout->printf( "Loading basic dictionary from %vfA%us%vn...", preload_path.GetUnicode().c_str() ); mout->flush();

   Load_Options opt;
   opt.load_semnet=true;
   opt.affix_table=false;
   opt.seeker=false;
   opt.ngrams = false;

   bool ok=false;

   try
    {
     ok = C->sol_id->LoadModules( preload_path, opt );

     lem::Path sqlite_file = lem::Path::GetTmpFilename();
     C->sol_id->GetSynGram().GetStorage().CopyDatabase(sqlite_file);
     LexiconStorage_SQLITE *lexicon_storage = new Solarix::LexiconStorage_SQLITE(sqlite_file.GetUnicode());
     C->sol_id->GetSynGram().SetStorage(lexicon_storage,true);
     C->sol_id->GetLexAuto().SetStorage(lexicon_storage,false);
     C->sol_id->GetAlephAuto().SetStorage(lexicon_storage,false);
     C->sol_id->GetDebugSymbols().SetStorage(lexicon_storage);

     sqlite_file = lem::Path::GetTmpFilename();
     C->sol_id->GetSynGram().Get_Net().GetStorage().CopyDatabase(sqlite_file);
     ThesaurusStorage_SQLITE *thesaurus_storage = new Solarix::ThesaurusStorage_SQLITE(sqlite_file.GetUnicode());
     C->sol_id->GetSynGram().Get_Net().SetStorage(thesaurus_storage,true);

     C->sol_id->PrepareForMerging();
    }
   catch( const lem::E_BaseException &ex )
    {
     ok = false;
     lem::mout->printf( "Error: %us\n", ex.what() );
    }
   catch( const std::exception &ex )
    {
     ok = false;
     lem::mout->printf( "Error: %s\n", ex.what() );
    }
   catch(...)
    {
     ok = false;
     mout->printf( "\n\nError: incompatible dictionary version or damaged database files\n" );
    }

   if( !ok )
    {
     lem::Process::Exit(1);
    }

   mout->printf( "%vfAOK%vn\n" );
  }
 #endif

 if( !rebuild_lemmatizer && !rebuild_pes )
  Compile_Project(&*C);

 Save_Results(&*C);

 boost::posix_time::ptime tm_end = lem::get_time();
 const int elapsed = (tm_end - tm_start).total_seconds();

 mout->printf( "\n%vfADictionary has been built, %d sec elapsed.%vn\n\n", elapsed );

 return 0;
}



void Parse_Options( int argc, char *argv[] )
{
 // Запускаем разбор командной строки.
 ArgOption *oplist = ParseArgList( argc, argv, SolOptTemplate );

 defines = new char[255];
 *defines='\0';

 
 // Просматриваем список указанных опций.
 for( int i=0; i<argc-1; i++ )
  {
   const int code=oplist[i].GetCode();
 

   switch(code)
   {
    case 2:
     {
      // Определение макроса в командной строке через /d??????
      strcat( defines, oplist[i].GetContent() );
      strcat( defines, ";" );
      break;
     }

    case 4:
     ShowBanner();
     exit(1);

    case 6:
     // Silent translation mode.
     silence = true;
     trace_level = 0;
     break;

    case 7:
     // Journalize the source code.
     source=true;
     break;

    case 8:
     // Set code page for text files.
     // Определена кодовая страница для исходников.
     code_page = atoi(oplist[i].GetContent());
     break;


    case 12:
    case 102:
     {
      help_him=true;
      if( strlen(oplist[i].GetContent()) )
       help_i = atoi(oplist[i].GetContent());

      break;
     }

    case 13:
     // Journalize the source code line numbers.
     lnum=true;
     break;

    case 14:
     // Switch the optimizer ON.
     do_optimize = true;
     break;

    case 15:
     // Определен уровень трассировки.
     trace_level = atoi(oplist[i].GetContent());
     break;

    case 20:
     out_bin_name = oplist[i].GetContent();
     break;

    case 22:
     {
      root_dir = oplist[i].GetContent();

      if( !lem::Path::IsPathDelimiter( root_dir.back() ) )
       root_dir += lem::Path::GetPathDelimiter(); 

      break;
     }

    case 30: // -nolinks
     {
      // не сохранять тезаурус в словаре
      allow_links = false;
      break;
     }

    case 31: // -nosounds
     {
      allow_sounds = false;
      break;
     }

    case 32: // -sounds
     {
      allow_sounds = true;
      break;
     }

    case 33: // -save_lexems
     {
      save_seeker = true;
      break;
     }

    case 34: // -save_affixes
     {
      save_affixes = true;
      break;
     } 

    case 37:
     {
      outdir = oplist[i].GetContent();

      lem::Path p(outdir);
      if( !p.DoesExist() )
       {
        mout->printf( "%vfCError%vn: -outdir path %vfE%us%vn does not exist\n", p.GetUnicode().c_str() );
        lem::Process::Exit(-1);
       } 

      break;
     }

    case 38:
     dict_cfg.ldsize = atoi(oplist[i].GetContent());
     break;

    case 39:
     cpp_rules = true;
     break;

    case 40:
     recompile_syntax=true;
     break;

    case 41: // -save_prefix_entry_searcher
     {
      save_prefix_entry_searcher = true;
      break;
     }

    case 42:
     {
      save_lemmatizer = true;
      break;
     }

    case 43:
     {
      reverse_links = lem::to_bool(oplist[i].GetContent());
      break;
     }

    case 44:
     {
      preload_path = lem::Path(oplist[i].GetContent());

      lem::Path p(preload_path);
      if( !p.DoesExist() )
       {
        mout->printf( "%vfCError%vn: -preload path %vfE%us%vn does not exist\n", p.GetUnicode().c_str() );
        lem::Process::Exit(-1);
       } 

      do_optimize = false; // оптимизация правил синтаксического анализа может 
                           // нарушить правильность списков, поэтому отключаем её.

      break;
     }

    case 45:
     {
      entry_redefinition = lem::to_bool(oplist[i].GetContent());
      break;
     }

    case 46:
     {
      save_paradigmas = true;
      break;
     }

    case 47:
     dict_cfg.internal_offset = atoi(oplist[i].GetContent());
     break;

    case 48:
     enames_path = lem::Path(oplist[i].GetContent());
     break;

    case 49:
     {
      in_names_type.push_back(1);
      in_names.push_back( oplist[i].GetContent() );
      break;
     }

    case 50:
     {
      rebuild_lemmatizer=true;
      break;
     }

    case 51:
     {
      rebuild_pes=true;
      break;
     }

    case -1:
     {
      // Параметр считаем именем файла.
      in_names_type.push_back(0);
      in_names.push_back( oplist[i].GetContent() );
      break;
     }

    default:
     {
      help_him=true;
      break;
     }
   }
  }

  
  
 if( trace_level>0 )
  {
   // Open the stream to write the debug messages.
   // Текстовый поток для печати журнала - с сообщениями по ходу работы
   // различных служб Солярис.
   lem::Path jpath(outdir);
   jpath.ConcateLeaf(lem::Path("journal"));
   lem::LogFile::Open(jpath);
  }
 

 // If command line looks wrong give a little help. Also it could happen that
 // user asks 'what can this program do?'.
 // Пользователь чего-то недопонимает?
 if( argc==1 )
  help_him=true;

 return;
}


Compiler *Create_Compiler(void)
{
 OFormatter *nul_tty = new OFormatter( lem::Path(NULL_DEVICE) );
 Compiler *C=NULL;
 if( silence )
  C = new Compiler( *nul_tty, *merr, dict_cfg );
 else
  C = new Compiler( *mout, *merr, dict_cfg );

/*
 lem::Path ini_file( "compiler.ini" );
 C->Read_Ini( ini_file );

 if( code_page!=UNKNOWN )
  C->SetCodeConverter( CodeConverter::getConverter(code_page) );
*/

 if( !silence )
  ShowBanner();

 C->trace_level = trace_level;
 C->defines = defines;
 C->bin_options.parsing =
                        (source ? SRC_BETH_PRINT_SOURCE : 0) |
                        (lnum ? SRC_BETH_PRINT_LINE_NUM : 0) |
                        (silence ? 0 : SRC_BETH_ECHO_PRINT ) |
                        SRC_BETH_JOURNALIZE;

 C->root_dir = root_dir;
 C->bin_options.allow_links = allow_links;
 C->bin_options.allow_sounds = allow_sounds;
 C->bin_options.produce_cpp_rules = cpp_rules;
 C->bin_options.recompile_syntax = recompile_syntax;
 C->bin_options.reverse_links = reverse_links;
 C->bin_options.entry_redefinition = entry_redefinition;

 C->bin_options.lexicon_merging = !recompile_syntax && !preload_path.empty();
 
 if( !enames_path.empty() )
  {
   lem::Char_Stream::UTF8_Reader rdr(enames_path);
   rdr.Read_Beginning();

   lem::UFString line;
   while( !rdr.eof() )
    {
     line.clear();
     rdr.read_line(line);
     if( line.empty() )
      continue;

     if( lem::left(line,2)==L"//" || line.front()==L'#' )
      // Строка комментариев
      continue;

     line.trim();
     line.strip_quotes();
     lem::UCString word = lem::to_upper(line).c_str();
     
     if(
        line.find(L'*')==0 &&
        line.find(L'?')==0 &&
        line.find(L'[')==0 &&
        line.find(L']')==0
       )
      {
       C->bin_options.allowed_enames.insert(word);
      }
     else
      {
       C->bin_options.allowed_emasks.push_back( new lem::UFString(lem::to_upper(line)) );
      }
    }
  } 

 return C;
}


void Compile_Project( Compiler *C )
{
 bool ok = true;

 C->ParadigmasStorage(save_paradigmas);

 // Translate each file list.
 for( Container::size_type i=0; i<in_names.size() && ok; i++ )
  {
   ok = false;

   try
    {
     // Транслируем текстовый файл описания Словаря.
     lem::Path p1(in_names[i]);
     BinaryFile proj( p1, true, false );

     if( in_names_type[i]==0 )
      {
       C->CompileProject( proj );
      }
     else if( in_names_type[i]==1 )
      {
       C->CompileFile( proj );
      }
      
     ok = true;
    }
   LEM_CATCH;

   if( !ok )
    {
     lem::Shell::Error( lem::format_str( "There was an error while compiling the file %s", in_names[i].c_str()) );
     lem::Process::Exit(1);
    }
  }

 mout->printf( "Project has been compiled.\n" );

 ok = false;
 try
  {
   if( !in_names.empty() )
    {
     if( do_optimize )
      {
       mout->printf( "Dictionary optimization commenced.\n" );
       C->Optimize();
      }

     if( save_affixes )
      C->CreateAffixTable();
     else
      C->EmptyAffixTable();

     C->PostCompile( lem::Path(outdir) );
    }

   ok = true;
  }
 LEM_CATCH;

 if( !ok )
  {
   lem::Shell::Error( L"There was an error while compiling the dictionary" );
   lem::Process::Exit(1);
  }

 if( !silence )
  mout->printf( "%vfATranslation completed.%vn\n" );

 return;
}

// **************************************************
// The dictionary is compiled.
// Now it should be stored in the binary disk files.
// **************************************************
void Save_Results( Compiler *C )
{
 bool ok = false;

 try
  {
   if( rebuild_lemmatizer )
    {
     Path lemma_path;
     lemma_path = lem::Path(outdir);
     lemma_path.ConcateLeaf( lem::Path(L"lemmatizer.db") );

     if( !silence )
      {
       mout->printf( "%vfASaving lemmatization engine%vn %us...", lemma_path.GetUnicode().c_str() );
       mout->flush();
      }

     C->SaveLemmatizer(lemma_path,!silence);

     if( !silence )
      mout->printf( "%vfEOK%vn\n" );
    }
   else if( rebuild_pes )
    {
     Path pes_path = lem::Path(outdir);
     pes_path.ConcateLeaf( lem::Path(L"prefix_entry_searcher.db") );

     if( !silence )
      {
       mout->printf( "%vfASaving prefix entry searcher%vn %us...", pes_path.GetUnicode().c_str() );
       mout->flush();
      }

     C->SavePrefixEntrySearcher(pes_path);

     if( !silence )
      mout->printf( "%vfEOK%vn\n" );
    }
   else if( !recompile_syntax )
    {
     Path p_alphabet(outdir);
     p_alphabet.ConcateLeaf( L"alphabet.bin" );
     C->SaveAlphabet( p_alphabet );

     Path p2(outdir);
     p2.ConcateLeaf( lem::Path(out_bin_name) );

     if( !silence )
      {
       mout->printf( "%vfASaving morphology analyzer%vn %us...", p2.GetUnicode().c_str() );
       mout->flush();
      }

     Path p_lexicon(outdir);
     p_lexicon.ConcateLeaf( L"lexicon.db" );

     BinaryWriter bin(p2);
     C->SaveMorphology( bin, p_lexicon );

     if( !silence )
      mout->printf( "%vfEOK%vn\n" );

     Path p3(outdir);
     p3.ConcateLeaf( lem::Path(L"seeker.bin") );

     // Возможно, сохраняем в отдельном файле справочник лексем.
     if( save_seeker )
      {
       BinaryWriter bin3(p3);
       C->SaveSeeker(bin3);
      }


     Path pes_path;
     if( save_prefix_entry_searcher )
      {
       pes_path = lem::Path(outdir);
       pes_path.ConcateLeaf( lem::Path(L"prefix_entry_searcher.db") );

       if( !silence )
        {
         mout->printf( "%vfACreating the prefix entry searcher%vn %us...", pes_path.GetUnicode().c_str() );
         mout->flush();
        }

//       C->SavePrefixEntrySearcher(pes_path);
       lem::Path tmp_pes( lem::Path::GetTmpFilename("tmp") );
       C->SavePrefixEntrySearcher(tmp_pes);
       lem::Path::CopyFile( tmp_pes, pes_path );
       

       if( !silence )
        mout->printf( "%vfEOK%vn\n" );
      }

     Path lemma_path;
     if( save_lemmatizer )
      {
       lemma_path = lem::Path(outdir);
       lemma_path.ConcateLeaf( lem::Path(L"lemmatizer.db") );

       if( !silence )
        {
         mout->printf( "%vfASaving lemmatization engine%vn %us...", lemma_path.GetUnicode().c_str() );
         mout->flush();
        }

       C->SaveLemmatizer(lemma_path,!silence);

       if( !silence )
        mout->printf( "%vfEOK%vn\n" );
      }


     Path p4(outdir);
     p4.ConcateLeaf( lem::Path(L"affixes.bin") );

     if( !silence )
      {
       mout->printf( "%vfASaving stemmer %vn%us%vn", p4.GetUnicode().c_str() );
       mout->flush();
      }

     BinaryWriter bin4(p4);
     C->SaveAffixes(bin4);
     if( !silence )
      mout->printf( " %vfEOK%vn\n" );

     if( save_affixes )
      C->StemmerPrintInfo(*mout);

     // THESAURUS
     Path p51(outdir);
     p51.ConcateLeaf( lem::Path(L"thesaurus.db") );

     if( !silence )
      {
       mout->printf( "%vfASaving thesaurus %vn%us%vn", p51.GetUnicode().c_str() );
       mout->flush();
      }

     C->SaveThesaurusDb(p51);

     if( !silence )
      mout->printf( " %vfEOK%vn\n" );

     // XML file with list if dictionary components
     Path p6(outdir);
     p6.ConcateLeaf( lem::Path(L"dictionary.xml") );

     if( !silence )
      {
       mout->printf( "%vfAWriting XML dictionary catalogue %vn%us%vn", p6.GetUnicode().c_str() );
       mout->flush();
      }

     lem::UFString solarix_version(
      #if defined SOLARIX_PRO
       L"pro"
      #else
       L"free"
      #endif 
                            ); 

  
     XmlFormatter xml(p6);
     xml.WriteBeginning();
     xml.printf(
                "<dataroot>\n"
                " <solarix_version>%us</solarix_version>\n"
                " <dictionary_version>%us</dictionary_version>\n"
                " <alphabet>%us</alphabet>\n"
                " <morphology>%us</morphology>\n"
                " <lexicon_provider>sqlite</lexicon_provider>\n"
                " <lexicon_db>%us</lexicon_db>\n"
                " <thesaurus_provider>sqlite</thesaurus_provider>\n"
                " <thesaurus_db>%us</thesaurus_db>\n"
                , solarix_version.c_str()
                , C->GetDictionary().version.serialize().c_str()  
                , lem::encode_chars_to_xml( p_alphabet.GetFileName() ).c_str()
                , lem::encode_chars_to_xml( p2.GetFileName() ).c_str()
                , lem::encode_chars_to_xml( p_lexicon.GetFileName() ).c_str()
                , lem::encode_chars_to_xml( p51.GetFileName() ).c_str()
               );

     if( save_seeker )
      {
       xml.printf(
                  " <seeker>%us</seeker>\n"
                  , lem::encode_chars_to_xml( p3.GetFileName() ).c_str()
                 );
      }

     if( save_lemmatizer )
      {
       xml.printf(
                  " <reco2_provider>sqlite</reco2_provider>\n"
                  " <reco2_db>reco2.db</reco2_db>\n"
                  " <lemmatizer enabled=\"true\" flags=\"default\" absolute=\"false\">%us</lemmatizer>\n"
                  , lem::encode_chars_to_xml( lemma_path.GetFileName() ).c_str()
                 );
      }

     if( save_affixes )
      {
       xml.printf(
                  " <affixes>%us</affixes>\n"
                  , lem::encode_chars_to_xml( p4.GetFileName() ).c_str()
                 );
      }     


     if( save_prefix_entry_searcher )
      {
       xml.printf(
                  " <prefix_entry_searcher>%us</prefix_entry_searcher>\n"
                  , lem::encode_chars_to_xml( pes_path.GetFileName() ).c_str()
                 );
      }


     xml.printf(
                "%us\n"
                "</dataroot>\n"
                , C->GetDictionaryXmlString().c_str()
               );


     xml.GetStream()->close();
     if( !silence )
      mout->printf( " %vfEOK%vn\n" );
    }
  
   ok = true;
  }
 LEM_CATCH;

 if( !ok )
  {
   lem::Shell::Error( L"There was an error while compiling the dictionary" );
   lem::Process::Exit(1);
  }

 return;
}


static void ShowBanner( OFormatter *out, bool verbose )
{
 out->printf(
             "%vfACompiler%vn version %vfF%s%vn\n"
             , sol_get_version().c_str()
            );

 Print_Project_Info(*out);
 out->eol();

 return;
}

/******************************************************************
 Print brief help pages.
 Вывод коротенькой справульки.
********************************************************************/
static void Help( int help_i )
{
 switch(help_i)
 {
  case 1:
    mout->printf(
                "Options:\n\n"
                "%vfA-d%vn[%vfAefine%vn]%vfEMMM%vn    - define macro %vfEMMM%vn for preprocessor\n"
                "%vfA-silent%vn         - silent run: no banner, no messages\n"
                "%vfA-s%vn[%vfAource%vn]       - print source code of program being compiled into journal\n"
                "%vfA-n%vn[%vfAumerate%vn]     - print numbers of lines of compiled source codes\n"
                "%vfA-o%vn[%vfAptimize%vn]     - optimize dictionary\n"
                "%vfA-x=%vfENNN%vn          - use code page %vfENNN%vn as default for text source code files\n"
                "%vfA-z=%vfENNN%vn          - use code page %vfENNN%vn for console\n"
                "%vfA-j%vn[%vfAournalize%vn]=%vfEN%vn - tracing level: %vfE0%vn - min, %vfE3%vn - max\n"
                "%vfA-dir=%vfEpath%vn       - path to source files to be compiled\n"
		"%vfA-outdir=%vfEpath%vn    - directory to store the dictionary files\n"      
                "%vfA-nolinks%vn        - do not create thesaurus file\n"
                "%vfA-nosounds%vn       - do not store sound records in binary dictiona file\n"
                "%vfA-save_affixes%vn   - create the affixes file for FAIND search engine\n" 
                "%vfA-save_seeker%vn    - write the fast lexicon seeking data file for search engine\n" 
                "%vfA-sql=%vfEversion%vn    - produce SQL script to upload dictionary into SQL DB\n"
                "                   -sql=mysql   - for MySQL\n"
                "                   -sql=oracle  - for Oracle\n"
                "                   -sql=unknown - for generic SQL database\n"  
                );
 
   break;

  case 2:
   mout->printf(
                "Code pages:\n\n"
                "  %vfA866%vn  - cyrillic for MSDOS\n\n"
                "  %vfA1251%vn - cyrillic MS Windows\n\n"
                "  %vfA847%vn  - cyrillic KOI-8 (UNIX)\n\n"
               );
   break;

  case 0:
  default:
   ShowBanner();
   mout->printf(
                "Usage: compiler [%vfA-option%vn] [%vfA-option%vn] ... [%vfEproj_file1%vn] [%vfEproj_file2%vn]\n\n"
                " %vfEproj_file%vn   - name of project file containing list of dictionary source codes\n\n"       
                "Help options:\n\n"
                "  -%vfAh%vn[%vfAelp%vn][=%vfEN%vn] - print help page #%vfEN%vn:\n\n"
                "               %vfE0%vn - currently shown page\n"
                "               %vfE1%vn - all options\n"
                "               %vfE2%vn - code pages (useful for russian users)\n\n"
                "For example: %vfFcompiler -h=1%vn\n\n"
               );
   break;
 }

 return;
}
