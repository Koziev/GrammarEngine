// -----------------------------------------------------------------------------
// File EMPIR_TEXT_PROCESSOR.CPP
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Реализация класса EmpirTextProcessor - контейнера для специализированых
// обработчиков текста. Класс организует координированную работу по обработке
// поступающих на вход лексем и распечатку в текстовый файл отчета.
//
// 20.08.2006 - добавлено приведение к форме существительного
// 11.01.2008 - при сборе 2грамм прил-сущ и сущ-глагол проверяется согласование,
//              а также фильтруются вспомогательные (служебные) глаголы для
//              русского и английского языков.
// 12.01.2008 - введена опция -outdir для указания каталога для сохранения 
//              файлов отчетов
// 12.05.2008 - для 64-битной версии словарь загружается из bin-windows64
// 07.06.2008 - добавлено накопление несогласованных пар слов по
//              команде -correl_any
// 17.08.2008 - команда -dir допускает список имен каталогов для обработки
// 01.11.2008 - лексемы, начинающиеся с '_' и '.', исключаются из обработки
// 03.11.2008 - введена полная поддержка content-плагинов из поискового движка
// 05.11.2008 - реализация накопления 3-грамм с кэширование, объединения
//              (merging) баз raw Ngrams;
// 11.11.2008 - добавлена распечатка в текстовых файлах не-словарных слов и
//              отсутствующих синонимических связей при накоплении N-грамм (опции
//              -dump_unfound_words и -dump_unfound_synonyms). 
// 19.11.2008 - добавлено накопление пар глагол+управляемый_объект
// 02.01.2009 - если аккуратная сегментация текста не включена (опция -segmentation),
//              то выкидываем из статистики некоторые обломки мультилексем типа
//              didn (от didn't) и русски (от по-русски).
// 03.02.2009 - добавлена опция -cp XXX для явного указания кодировки PLAIN ASCII
//              файлов.
// 20.07.2009 - добавление обработки терта- и пентаграмм.
// 06.04.2010 - добавлена опция -eol_breaks для разбивки текста по строкам.
// 03.01.2011 - добавлена опция -ngram_filter для задания фильтра накапливаемых
//              N-грамм. 
// 05.02.2011 - изменена работа с ошибками парсинга командной строки: вместо
//              печати диагностики в консоль кидаем исключение с подробным
//              описанием.
// 26.02.2011 - добавлена опция -force_cp NNN для принудительного задания кодовой
//              страницы обрабатываемых файлов.
// 25.05.2012 - добавлена проверка доступности файла dictionary.xml с выдачей
//              специальной диагностики, вместо попытки загрузить несуществующий
//              файл и выдачи ошибки о некорректной версии словаря.
// -----------------------------------------------------------------------------
//
// CD->04.09.2002
// LC->24.03.2013
// --------------

#include <lem/system_config.h>
#include <lem/conversions.h>
#include <lem/unicode.h>
#include <lem/reflection.h>
#include <lem/ustreams.h>
#include <lem/logfile.h>
#include <lem/shell.h>
#include <lem/xml_parser.h>

#include <lem/solarix/la_autom.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/version.h>
#include <lem/solarix/sentencebroker.h>
#include <lem/solarix/NGramsStorage_SQLITE.h>
#include <lem/solarix/NGramFilter_AnyInWhiteList.h>
#include <lem/solarix/_sg_api.h>

#include "empir.h"

#if LEM_DEBUGGING==1 && defined LEM_MSC
#include <crtdbg.h>
#endif

using namespace std;


EmpirTextProcessor::EmpirTextProcessor(void)
{
 // По умолчанию для PLAIN ASCII файлов используем текущую кодировку локали пользовательской
 // сессии. Эта страница может быть переопределена в командной строке.
 default_cp = &lem::UI::get_UI().GetSessionCp();

 force_cp = NULL;

 t0 = boost::posix_time::second_clock::local_time(); // Время начала работы
 file_counter=0;

 upload_to_db=true;
 use_disk_cache=true;
 print_ngrams=false;

 prev_line = 0;

 words  = NULL;
 la = NULL;
 #if !defined SOL_NO_AA
// sentan = NULL;
 #endif

 class_mapper = NULL;

 language = All;
 language_sx_code = -1;

 scheme = Undefined;
 run_chars = false;

 #if LEM_DEBUGGING==1 && defined LEM_MSC
 LEM_CHECKIT_Z( _CrtCheckMemory() == TRUE );
 #endif

 Show_Banner();

 return;
}


EmpirTextProcessor::~EmpirTextProcessor(void)
{
 #if !defined SOL_NO_AA
// lem_rub_off(sentan);
 #endif

 lem_rub_off(words);
 lem_rub_off(class_mapper);

 return;
}

void EmpirTextProcessor::Show_Banner(void)
{
 mout->printf(
             "%vfAEMPIRIKA%vn text analyzer v. %vfF%s%vn\n"
             "%vf9http://solarix.ru/for_developers/exercise/la_project.shtml%vn\n\n"
             , sol_get_version().c_str()
            );

 Print_Project_Info(*mout);

 return;
}


// *******************************************
// Распечатка короткой справки о программе.
// *******************************************
void EmpirTextProcessor::Help(void)
{
 mout->printf(
 "\n"
 "Назначение - сбор статистической информации о языке на уровне букв, "
 "слогов, отдельных слов, предложений.\n\n"
 , sol_get_release_info().c_str()
 , sol_get_version().c_str()
 );
}

#if defined LEM_WINDOWS
extern const wchar_t* GetIntegraFolderPath(void);
#endif


void EmpirTextProcessor::LoadConfig( const lem::Path & force_dir )
{

 #if defined FAIND_PLUGINS
 // Нам нужно найти каталог с content-плагинами. Пробуем разные варианты.
 lem::Path content_plugins_path = force_dir;

 if( force_dir.empty() )
  {
   content_plugins_path = lem::Reflection::GetStartupFolder();
   content_plugins_path.ConcateLeaf( L"plugins" );
   content_plugins_path.ConcateLeaf( L"formats" );


   if( !content_plugins_path.DoesExist() )
    {
     content_plugins_path = lem::Path(GetIntegraFolderPath());
     content_plugins_path.ConcateLeaf( L"plugins" );
     content_plugins_path.ConcateLeaf( L"formats" );
    }
  }
 #endif  

 detector = new Solarix::Search_Engine::File_Type_Detector;

 #if defined FAIND_PLUGINS
 if( content_plugins_path.DoesExist() )
  {
   detector->LoadPlugins( content_plugins_path, NULL );
   int ndet = detector->Count();
   lem::mout->printf( "Format handling plugins in [%vfE%us%vn]: %vfA%d%vn\n", content_plugins_path.GetUnicode().c_str(), ndet );
  }
 #endif

 detector->AttachDetectors();

 return;
}


void EmpirTextProcessor::Parse_Command( Collect<UFString> &args )
{
 // Pick up the options related to EMPIR statistical processor. Options for FAIND
 // local crawler are left untouched.

 NGramsCollectorFlags::Flags ngrams_flags=0;

 bool accum_1grams=false;
 bool accum_2grams=true;
 bool accum_3grams=false;
 bool accum_4grams=false;
 bool accum_5grams=false;

 bool clean_ngrams=false;

 UFString segment_n; // метка сегмента для базы N-грамм

 int cache_doc=0, cache_ngrams=0, cache_db=0;

 lem::UFString ngram_filter_type;
 lem::Path ngram_filter_filename;
 lem::Ptr<NGramFilter> ngram_filter;

 lem::Path plugins_folder; // папка, откуда нужно загрузить плагины

 
 // Из списка опций выберем те, которые управляют работой именно статистического
 // блока, оставив без изменений опции поискового движка FAIND (локального паука).
 for( lem::Container::size_type i=1; i<args.size(); i++ )
  if( args[i] == L"-english" )
   {
    language = English;
    language_sx_code = ENGLISH_LANGUAGE;
   } 
  else if( args[i] == L"-russian" )
   {
    language = Russian;
    language_sx_code = RUSSIAN_LANGUAGE;
   } 
  else if( args[i] == L"-french" )
   {
    language = French;
    language_sx_code = FRENCH_LANGUAGE;
   } 
  else if( args[i] == L"-german" )
   {
    language = German;
    language_sx_code = GERMAN_LANGUAGE;
   } /*
  else if( args[i] == L"-italian" )
   {
    language = Italian;
    language_sx_code = ITALIAN_LANGUAGE;
   } */
  else if( args[i] == L"-spanish" )
   {
    language = Spanish;
    language_sx_code = SPANISH_LANGUAGE;
   } 
  else if( args[i]==L"-chars" )
   { 
    // Будет накапливаться статистика о распределении букв и
    // их сочетаний.
    run_chars=true;
   } 
  else if( args[i]==L"-ngrams" )
   {
    scheme=NGrams;
   } 
  else if( args[i]==L"-dump_unfound_words" )
   {
    dump_unfound_words=true;
   } 
  else if( args[i]==L"-dump_unfound_synonyms" )
   {
    dump_unfound_synonyms=true;
   } 
  else if( args[i] == L"-scheme1" )
   {
    scheme=Scheme1;
   } 
  else if( args[i] == L"-lexicon" )
   {
    Set_LexiconProbing();
   } 
  else if( args[i] == L"-tonouns" )
   {
    scheme=ToNouns;
   } 
  else if( args[i] == L"-tokenize" )
   {
    scheme=Tokenize;
   } 
  else if( args[i] == L"-erase_freq1" )
   {
    erase_freq1=true;
   } 
  else if( args[i] == L"-segmentation" )
   {
    segmentation=true;
   } 
  else if( args[i] == L"-lemmatization" )
   {
    lemmatization=true;
   } 
  else if( args[i] == L"-doccache" )
   {
    if( !lem::to_int( args[i+1].c_str(), &cache_doc ) )
     {
      lem::MemFormatter mem;
      mem.printf( "Invalid -doccache argument: must be integer, got [%s]", args[i+1].c_str() );
      throw lem::E_BaseException(mem.string());
     }

    i++;
   } 
  else if( args[i] == L"-segment_n" )
   {
    segment_n = args[i+1];
    i++;
   } 
  else if( args[i] == L"-plugins" )
   {
    plugins_folder = lem::Path(args[i+1]);
    i++;
   } 
  else if( args[i] == L"-source_format" )
   {
    source_format = args[i+1];
    i++;
   } 
  else if( args[i] == L"-ngramscache" )
   {
    if( !lem::to_int( args[i+1].c_str(), &cache_ngrams ) )
     {
      lem::MemFormatter mem;
      mem.printf( "Invalid -ngramscache argument: must be integer, got [%s]", args[i+1].c_str() );
      throw lem::E_BaseException(mem.string());
     }

    i++;
   } 
  else if( args[i] == L"-dbcache" )
   {
    if( !lem::to_int( args[i+1].c_str(), &cache_db ) )
     {
      lem::MemFormatter mem;
      mem.printf( "Invalid -dbcache argument: must be integer, got [%s]", args[i+1].c_str() );
      throw lem::E_BaseException(mem.string());
     }

    i++;
   } 
  else if( args[i] == L"-sentan" )
   {
    scheme = Sentan;
   } 
  else if( args[i] == L"-correl_nn" )
   {
    scheme=NGrams;
    ngrams_flags |= Solarix::NGramsCollectorFlags::Noun_Noun | NGramsCollectorFlags::Covalent2Grams;
   } 
  else if( args[i] == L"-correl_an" )
   {
    scheme=NGrams;
    ngrams_flags |= NGramsCollectorFlags::Adj_Noun | NGramsCollectorFlags::Covalent2Grams;
   } 
  else if( args[i] == L"-correl_nv" )
   {
    scheme=NGrams;
    ngrams_flags |= NGramsCollectorFlags::Noun_Verb | NGramsCollectorFlags::Covalent2Grams;
   } 
  else if( args[i] == L"-correl_vobj" )
   {
    scheme=NGrams;
    ngrams_flags |= NGramsCollectorFlags::Verb_Object | NGramsCollectorFlags::Covalent2Grams;
   } 
  else if( args[i] == L"-correl_advv" )
   {
    scheme=NGrams;
    ngrams_flags |= NGramsCollectorFlags::Adverb_Verb | NGramsCollectorFlags::Covalent2Grams;
   } 
  else if( args[i] == L"-correl_adva" )
   {
    scheme=NGrams;
    ngrams_flags |= NGramsCollectorFlags::Adverb_Adj | NGramsCollectorFlags::Covalent2Grams;
   } 
  else if( args[i] == L"-correl_pn" )
   {
    scheme=NGrams;
    ngrams_flags |= NGramsCollectorFlags::Prepos_Noun | NGramsCollectorFlags::Covalent2Grams;
   } 
  else if( args[i] == L"-correl_any" )
   {
    scheme=NGrams;

    if( accum_1grams )
     ngrams_flags |= NGramsCollectorFlags::Words;

    if( accum_2grams )
     ngrams_flags |= NGramsCollectorFlags::Raw2Grams;

    if( accum_3grams )
     ngrams_flags |= NGramsCollectorFlags::Raw3Grams;

    if( accum_4grams )
     ngrams_flags |= NGramsCollectorFlags::Raw4Grams;

    if( accum_5grams )
     ngrams_flags |= NGramsCollectorFlags::Raw5Grams;
   }
  else if( args[i] == L"-merge" )
   {
    merging = true;
   } 
  else if( args[i] == L"-upload_to_db-" )
   {
    upload_to_db = false;
   } 
  else if( args[i] == L"-upload_to_db" )
   {
    upload_to_db = true;
   } 
  else if( args[i] == L"-use_disk_cache-" )
   {
    use_disk_cache = false;
   } 
  else if( args[i] == L"-use_disk_cache" )
   {
    use_disk_cache = true;
   } 
  else if( args[i] == L"-main_ngrams" )
   {
    main_ngrams = true;
   } 
  else if( args[i] == L"-eol_breaks" )
   {
    // The end of line characters breaks the N-gram accumulation and flush the queue.
    // Обрабатываемые тексты будем разбивать по границам строк.
    eol_breaks = true;
   } 
  else if( args[i] == L"-ngram_filter" )
   {
    ngram_filter_type = args[i+1];
    ngram_filter_filename = lem::Path(args[i+2]);
    i += 2;
   }
  else if( args[i] == L"-1grams" )
   {
    accum_1grams = true;
   } 
  else if( args[i] == L"-1grams-" )
   {
    accum_1grams = false;
   } 
  else if( args[i] == L"-2grams" )
   {
    accum_2grams = true;
   } 
  else if( args[i] == L"-2grams-" )
   {
    accum_2grams = false;
   } 
  else if( args[i] == L"-3grams" )
   {
    accum_3grams = true;
   } 
  else if( args[i] == L"-3grams-" )
   {
    accum_3grams = false;
   } 
  else if( args[i] == L"-4grams" )
   {
    accum_4grams = true;
   } 
  else if( args[i] == L"-4grams-" )
   {
    accum_4grams = false;
   } 
  else if( args[i] == L"-5grams" )
   {
    accum_5grams = true;
   } 
  else if( args[i] == L"-5grams-" )
   {
    accum_5grams = false;
   } 
  else if( args[i] == L"-clean_ngrams" )
   {
    clean_ngrams = true;
   } 
  else if( args[i]==L"-cp" )
   {
    UFString cp_name(args[i+1]);
    cp_name.strip_quotes();
    cp_name.strip_apostrophes();

    try
     {
      default_cp = lem::CodeConverter::getConverter( lem::to_ascii(cp_name) );
     }
    catch(...)
     {
      lem::MemFormatter mem;
      mem.printf( "%vfCERROR:%vn unknown codepage %vfE%us%vn", cp_name.c_str() );
      throw lem::E_BaseException(mem.string());  
     }

    i++;
   }
  else if( args[i]==L"-force_cp" )
   {
    UFString cp_name(args[i+1]);
    cp_name.strip_quotes();
    cp_name.strip_apostrophes();

    try
     {
      if( cp_name==L"utf8" )
       force_cp = new Utf8CodeConverter();
      else
       force_cp = lem::CodeConverter::getConverter( lem::to_ascii(cp_name) );
     }
    catch(...)
     {
      lem::MemFormatter mem;
      mem.printf( "%vfCERROR:%vn unknown codepage %vfE%us%vn", cp_name.c_str() );
      throw lem::E_BaseException(mem.string());  
     }

    i++;
   }
  else if( args[i] == L"-log" )
   {
    // Далее указан файл для записи журнала
    lem::Path log_filename( args[i+1] );
    lem::LogFile::Open(log_filename);
    i++;
   }
  else if( args[i] == L"-file" || args[i]==L"-dir" )
   {
    // Далее указан файл или каталог для обработки
    UFString f(args[i+1]);
    f.strip_quotes();
    f.strip_apostrophes();

    if( f.front()==L'@' )
     {
      // В указанном файле перечислены имена каталогов для обработки
      lem::Path utf8_name( f.c_str()+1 );
      lem::Char_Stream::UTF8_Reader utf8(utf8_name);
      utf8.Read_Beginning();
      while( !utf8.eof() )
       {
        lem::UFString line;
        utf8.read_line(line);
        line.trim(); 
        if( !line.empty() )
         {
          lem::Path p(line);

          if( !p.DoesExist() )
           {
            lem::MemFormatter mem;
            mem.printf( "Error: directory [%us] does not exist", p.GetUnicode().c_str() );
            throw E_BaseException(mem.string());
           }

          scan_folders.push_back(p);
         } 
       }
     }
    else
     {
      lem::Collect<UFString> dirs;
      lem::parse( f, dirs );
  
      if( dirs.empty() )
       {
        lem::MemFormatter mem;
        mem.printf( "Error: list of folder names is empty -dir [%us]", f.c_str() );
        throw E_BaseException(mem.string());
       } 

      for( lem::Container::size_type j=0; j<dirs.size(); j++ )
       {        
        lem::Path p( dirs[j] );
  
        if( !p.IsFolder() )
         {
          if( !p.DoesExist() )
           {
            lem::MemFormatter mem;
            mem.printf( "Error: file [%us] does not exist", p.GetUnicode().c_str() );
            throw E_BaseException(mem.string());
           }

          scan_files.push_back(p);
         }
        else
         {
          if( !p.DoesExist() )
           {
            lem::MemFormatter mem;
            mem.printf( "Error: directory [%us] does not exist", p.GetUnicode().c_str() );
            throw E_BaseException(mem.string());
           }

          scan_folders.push_back(p);
         }
       }
     }

    i++; 
   }
  else if( args[i] == L"-outdir" )
   {
    // Далее указан каталог для записи файлов отчетов
    lem::Path p( args[i+1] );
    if( !p.DoesExist() || !p.IsFolder() )
     {
      lem::MemFormatter mem;
      mem.printf( "Error: -outdir requires name of existing folder, not [%us]", p.GetUnicode().c_str() );
      throw E_BaseException(mem.string());
     }

    outdir = p;
    word_stat.outdir = p;
    #if defined EMPIR_SYLLAB
    syllab_stat.outdir = p;
    #endif
    char_stat.outdir = p;

    i++; 
   }
  else if( args[i] == L"-dictdir" )
   {
    // Далее указан каталог с файлами словаря, либо полное имя dictionary.xml
    lem::Path p( args[i+1] );
    if( !p.DoesExist() )
     {
      lem::MemFormatter mem;
      mem.printf( "Error: -dictdir must be followed by the name of existing folder" );
      throw E_BaseException(mem.string());
     }

    dictdir = p;
    i++; 
   }
  else
   {
    lem::MemFormatter mem;
    mem.printf( "Invalid command %vfC%us%vn", args[i].c_str() );
    throw E_BaseException(mem.string());
   }


 if( !accum_1grams && !accum_2grams && !accum_3grams && !accum_4grams && !accum_5grams )
  {
   if( clean_ngrams )
    {
     lem::MemFormatter mem;
     mem.printf( "Option -clean_ngrams requires any of -1grams, ..., -5grams options to be defined" );
     throw E_BaseException(mem.string());
    }

   if( erase_freq1 )
    {
     lem::MemFormatter mem;
     mem.printf( "Option -erase_ngrams requires any of -1grams, ..., -5grams options to be defined" );
     throw E_BaseException(mem.string());
    }

   if( scheme==NGrams )
    {
     lem::MemFormatter mem;
     mem.printf( "Ngrams assembler requires requires any of -1grams, ..., -5grams options to be defined" );
     throw E_BaseException(mem.string());
    }
  }

 LoadConfig(plugins_folder);

 if( default_cp!=NULL )
  scanning.prefer_cp_list.push_back( default_cp );

 if( force_cp!=NULL )
  scanning.forced_cp = force_cp;

  
 #if defined EMPIR_SYLLAB
 syllab_stat.SetLanguage(language_sx_code);
 #endif    

 try
  {
   // Dictionary is obligatory - do load it now.
   // Загружаем словарь.
   Load_Dictionary();
  }
 catch( const std::exception &e )
  {
   mout->printf( "Loading dictionary error\n%s\n", e.what() );
   exit(1);
  }
 catch( const lem::E_BaseException &e )
  {
   mout->printf( "Loading dictionary error\n%us\n", e.what() );
   exit(1);
  }
 catch( ... )
  {
   mout->printf( "Loading dictionary error\n" );
   exit(1);
  }

 if(lemmatization)
  {
   lemm = lem::Ptr<Solarix::LemmatizatorStorage>( &sol_id->GetLemmatizer(), lem::null_deleter() );
  }

 if( scheme==Tokenize )
  {
   word_merger = new MultiwordMerger( la );

   lem::Path out_filename( GetOutPath(L"tokenization.txt") );
   tokenizer_out = new OUFormatter( out_filename );
  }
 else if( !segmentation )
  {
   merge_words=true;
   word_merger = new MultiwordMerger( la );
  }

// ngrams = new NGramsCollectors(sol_id,lemm);

 if( scheme==Undefined || scheme==Scheme1 )
  {
   Set_Scheme1();
  }
 
 if( scheme == Sentan )
  Set_Sentan();

 if( run_chars )
  NeedsCharStatistics();

 if( scheme==NGrams )
  {
   //bool needs_entry2class = (ngrams_flags & NGramsCollectorFlags::Covalent2Grams ) == NGramsCollectorFlags::Covalent2Grams;
   Set_NGrams( /*needs_entry2class*/ );
  } 

 if( scheme==ToNouns )
  Set_ToNouns();

 if( words!=NULL )
  {
   words->outdir = outdir;
   words->la = la;
  }

 #if !defined SOL_NO_AA
// if( sentan!=NULL )
//  sentan->PrepareStreams();
 #endif

 if( ngrams.NotNull() )
  {
   ngrams->Prepare(
                   outdir,
                   language,
                   ngrams_flags,
                   erase_freq1,
                   segmentation,
                   lemmatization,
                   use_disk_cache,
                   upload_to_db,    
                   to_ascii(segment_n),
                   clean_ngrams
                  );

   if( cache_doc>0 )
    ngrams->SetDocCacheCapacity(cache_doc);

   if( cache_ngrams>0 )
    ngrams->SetNGramsCacheCapacity(cache_ngrams);

   if( cache_db>0 )
    ngrams->SetDBCache(cache_db);

   if( !ngram_filter_filename.empty() )
    {
     if( ngram_filter_type=="any_in_list" )
      {
       NGramFilter_AnyInWhiteList *filter = new NGramFilter_AnyInWhiteList(ngram_filter_filename);
       ngrams->SetFilter(filter); // filter будет удален внутри!
      }
    }

/*
   if( print_ngrams )
    {
     ngrams->PrintNgrams( print_format, print_file );
    }
*/
  }

 if( words!=NULL )
  {
   words->erase_freq1 = erase_freq1; 
   words->segmentation = segmentation;

   if( !segmentation )
    {
     // Если аккуратная сегментация текста не включена по соображениям скорострельности,
     // но принудительно будем выкидывать из собираемой статистики некоторые "обломки"
     // мультилексем.
     switch(language)
     {
      case English:
       words->stopwords.insert( L"S" );   // he's
       words->stopwords.insert( L"T" );   // don't
       words->stopwords.insert( L"D" );   // I'd like to
       words->stopwords.insert( L"DON" ); 
       words->stopwords.insert( L"DIDN" ); 
       words->stopwords.insert( L"DOESN" );
       words->stopwords.insert( L"AREN" );
       words->stopwords.insert( L"WEREN" );
       words->stopwords.insert( L"ISN" );
       words->stopwords.insert( L"WOULDN" );
       words->stopwords.insert( L"SHOULDN" );
       words->stopwords.insert( L"COULDN" );
       words->stopwords.insert( L"RE" ); // We're
       words->stopwords.insert( L"M" );  // I'm
       words->stopwords.insert( L"VE" );  // I've
       words->stopwords.insert( L"WASN" );  // Wasn't
       words->stopwords.insert( L"HASN" );  // Hasn't
       words->stopwords.insert( L"HADN" );  // Hadn't
       words->stopwords.insert( L"AIN" );  // ain't
       words->stopwords.insert( L"LL" ); // I'll
       words->stopwords.insert( L"DR" ); // DR.
       words->stopwords.insert( L"MR" ); // MR.
       break;
   
      case Russian:
       #if defined LEM_WINDOWS
/*
       words->stopwords.insert( L"РУССКИ" );    // по-русски ...
       words->stopwords.insert( L"АНГЛИЙСКИ" );
       words->stopwords.insert( L"ФРАНЦУЗСКИ" );
       words->stopwords.insert( L"НЬЮ" );
       words->stopwords.insert( L"СЕВЕРО" );
       words->stopwords.insert( L"ТОЧЬ" );
*/
       words->stopwords.insert( L"СМ" );
/*
       words->stopwords.insert( L"ЮГО" );
       words->stopwords.insert( L"СВИДАНЬЯ" );
*/
       #endif
       break;
     }
    }
  }

 #if LEM_DEBUGGING==1 && defined LEM_MSC
 LEM_CHECKIT_Z( _CrtCheckMemory() == TRUE );
 #endif

 return;
}

void EmpirTextProcessor::Load_Dictionary(void)
{
 nul_tty.Open( lem::Path(NULL_DEVICE) );

 sol_id = new Dictionary( &nul_tty, merr );

 lem::Path dict_path;

 if( dictdir.IsFolder() )
  { 
   lem::Path folder(dictdir);

   // Сначала попробуем найти словарь в указанном опцией -dictdir каталоге,
   // затем в текущем каталоге, затем в каталоге ..\bin-windows (или ..\bin-linux),
   // а уже потом спросим пользователя.
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
       folder.clear();
      }
     else if( ivar==2 )
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
     else
      {
       mout->printf( "Can not find dictionary configuration file dictionary.xml, please specify it with -dictdir XXXX\n" );
       lem::Process::Exit();
      }
    }
  }
 else
  {
   dict_path = dictdir;
  }
 
 if( !dict_path.DoesExist() )
  {
   mout->printf( "Can not find dictionary configuration file dictionary.xml, please specify it with -dictdir XXXX\n", dict_path.GetUnicode().c_str() );
   lem::Process::Exit();
  }


 mout->printf( "Loading dictionary from %vfA%us%vn...", dict_path.GetUnicode().c_str() ); mout->flush();
 Load_Options opt;
 opt.affix_table = true;
 opt.load_semnet = true;
 opt.seeker = true;
 opt.ngrams = true;
 opt.lemmatizer = true;
 opt.force_lemmatizer_fastest_mode = true; 

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

 sg = &sol_id->GetSynGram();
 la = &sol_id->GetLexAuto();

 #if defined EMPIR_SYLLAB
 syllab_stat.SetSol(&*sol_id);
 #endif
 
 word_stat.SetSol(&*sol_id);

 #if LEM_DEBUGGING==1 && defined LEM_MSC
 LEM_CHECKIT_Z( _CrtCheckMemory() == TRUE );
 #endif

 return;
}


static bool is_digits( const UCString &s )
{
 for( int i=0; i<s.length(); ++i )
  if( !lem::is_udigit(s[i]) )
   return false;

 return true;
}


bool EmpirTextProcessor::AcceptLexem( const UCString &bl ) const
{
 bool process=false;
 // Do process this lexem?
 switch(language)
 { 
  case All: process = true; break;

  case Russian:
   // Only russian words (and numbers and punctuators) are allowed.
   process = !bl.empty() && (are_cyr_only(bl.c_str()) || is_int(bl.c_str()) || is_upunct(bl.front()));
   break;

  case English:
   // Only english words are to be processed.
   process = !bl.empty() && (are_lat_only(bl.c_str()) || is_int(bl.c_str()) || is_upunct(bl.front()));
   break;

  case French:
   process = !bl.empty() && (are_french_only(bl.c_str()) || is_int(bl.c_str()) || is_upunct(bl.front()));
   break;

  case German:
   process = !bl.empty() && (are_german_only(bl.c_str()) || is_int(bl.c_str()) || is_upunct(bl.front()));
   break;

  case Italian:
   process = !bl.empty() && (are_italian_only(bl.c_str()) || is_int(bl.c_str()) || is_upunct(bl.front()));
   break;

  case Spanish:
   process = !bl.empty() && (are_spanish_only(bl.c_str()) || is_int(bl.c_str()) || is_upunct(bl.front()));
   break;
 }

 return process;
}


bool EmpirTextProcessor::ProcessFile(
                                     const lem::Path &filename,
                                     Solarix::Search_Engine::Base_File_Reader * reader,
                                     lem::Stream * raw_file
                                    )
{
 lem::uint64_t src_size = raw_file->fsize64();

 lem::ElapsedTime et;
 et.start();

 int last_perc=0;
 int n_lex=0;
 const int N_GRAD = 10; // Сколько отметок градусника соответствует 100% выполнения

 int size_Kb = src_size/1024;

 // Для очень крупных файлов будем показывать прогресс по 10 пройденных Мб печатью позиции в файле
 bool show_completion_by_Mbs = size_Kb>100000;
 int last_position_Mb=0;


 file_counter++;

 mout->printf(
             "#%W3d %vfE%W20us%vn %W5ud Kb %W25s :"
             , file_counter
             , filename.GetUnicode().c_str()
             , size_Kb
             , reader->get_Format().string().c_str()
            );

 if( lem::LogFile::IsOpen() )
  {
   lem::MemFormatter mem;
   mem.printf( "Start processing file #%d [%us] format=%s\n", file_counter, filename.GetUnicode().c_str(), reader->get_Format().string().c_str() );
   lem::LogFile::Print( mem.string() );
  }

 if( scheme==EmpirTextProcessor::LexiconProbing ) 
  {
   OUFormatter out( GetOutPath(L"unfound_entries.rez") );

   int added=0, rejected=0;

   // Считываем лексемы, одна лексема на отдельной строке.
   lem::UFString line;
   while( !reader->eof() )
    {
     reader->read_line(line);
     line.trim();
     if( line.empty() )
      continue;

     lem::UCString word( line.c_str() );

     // Есть такая статья в лексиконе?

     if( sol_id->GetSynGram().FindEntry(word,ANY_STATE,false)==UNKNOWN )
      {
       out.printf( "[%us]\n", word.c_str() );
       mout->printf( "%vfE%W30us%vn %vfAadded%vn\n", word.c_str() );
       added++;
      }
     else 
      { 
       mout->printf( "%W30us %vfDrejected%vn\n", word.c_str() );
       rejected++;
      } 
    }

   mout->printf( "\nResults: %d word(s) missing, %d found\n", added, rejected );

   return true;
  }
 else if( scheme==Tokenize )
  {
   Solarix::Search_Engine::Base_File_Lexem bl;

   while( !reader->eof() )
    {
     // Retrive the next lexem from the stream
     reader->read(bl);
     //bl.to_upper();
     word_merger->Push(bl.word);
  
     while( word_merger->IsReady() )
      {
       const lem::UCString & token = word_merger->Pop();
       tokenizer_out->printf( "%us\n", token.c_str() );
       n_lex++;
      }
    }

   word_merger->ForceReady();
   while( word_merger->IsReady() )
    {
     const lem::UCString & token = word_merger->Pop();
     tokenizer_out->printf( "%us\n", token.c_str() );
     n_lex++;
    }
  }
 else if( scheme==NGrams || scheme==Scheme1 || scheme==Sentan )
  {
   if( scheme==NGrams )
    BeginDocument();

   try
    {
     if( segmentation )
      {
       if( eol_breaks )
        {
         while( !reader->eof() )
          {
           lem::UFString sentence;
           Solarix::Sentence sent;

           reader->read_line(sentence);
           if( !sentence.trim().empty() )
            {
             // Предложение разбиваем на лексемы.
             sent.clear();
             sent.Parse( sentence, false, sol_id.get(), language_sx_code, NULL );
         
             for( lem::Container::size_type i=0; i<sent.size(); ++i, n_lex++ )
              {
               UCString bl = sent.GetWord(i);
               bl.to_upper();
         
               const bool process=AcceptLexem(bl);
         
               if( process )
                {
                 switch(scheme)
                 {
                  case NGrams: Process2( bl ); break;
         
                  case Sentan:
                   {
                    #if !defined SOL_NO_AA
//                    sentan->Process( bl );
                    #endif
                    break;
                   }
         
                  case Scheme1: Process(bl); break;
                  default: LEM_STOPIT;
                 }
                }
              }

             // Конец предложения - обрываем накопление N-грамм.
             Process2( L"." );
            }
          } 
        }
       else
        {
         UFString text;
         reader->read_whole_text(text);
         lem::Ptr<lem::Char_Stream::WideStream> reader2 = new lem::Char_Stream::UTF16_MemReader(text);
         SentenceBroker broker(reader2,sol_id.get(),language_sx_code);
      
         lem::UFString sentence;
         Solarix::Sentence sent;
         int paragraph_id=-1;
      
         while( broker.Fetch(sentence,paragraph_id) ) 
          {
           // Предложение разбиваем на лексемы.
           sent.clear();
           sent.Parse( sentence, false, sol_id.get(), language_sx_code, NULL );
      
           for( lem::Container::size_type i=0; i<sent.size(); ++i, n_lex++ )
            {
             UCString bl = sent.GetWord(i);
             bl.to_upper();
      
             const bool process=AcceptLexem(bl);
      
             if( process )
              {
               switch(scheme)
               {
                case NGrams: Process2( bl ); break;
      
                case Sentan:
                 {
                  #if !defined SOL_NO_AA
//                  sentan->Process( bl );
                  #endif
                  break;
                 }
      
                case Scheme1: Process(bl); break;
                default: LEM_STOPIT;
               }  
              } 
            }

           Process2( L"." );
          }
        }
      }
     else
      {
       if( source_format==L"google_ngrams" || source_format==L"csv" )
        {
         const wchar_t *FIELD_SEPARATOR = source_format==L"google_ngrams" ? L"\t" : L";";

         UFString line;
         int line_count=0;
         lem::Collect<UFString> columns;
        
         while( !reader->eof() )
          {
           if( !(line_count%100000) && line_count>0 )
            {
             mout->printf( '.' );
             mout->flush();
             ngrams->InternalFlush(true);
            } 

           reader->read_line( line );
           line_count++;
           if( !line.empty() )
            {
             columns.clear();
             lem::parse( line, columns, FIELD_SEPARATOR, false );
             if( columns.size()>1 )
              {
               const int ngram_order = CastSizeToInt(columns.size())-1;

               if( columns.back().length()<10 && lem::is_int(columns.back().c_str()) )
                {
                 const int freq = columns.back().ToInt();

                 bool all_ok=true;
                 for( int i=0; i<ngram_order; ++i )
                  if( columns[i].find(L'\'')!=0 || !AcceptLexem(columns[i].c_str()) || columns[i].length()>=UCString::max_len )
                   {
                    all_ok=false; 
                    break; 
                   }

                 if( all_ok )
                  { 
                   n_lex += ngram_order;

                   switch( ngram_order )
                   {
                    case 2:
                     {
                      ngrams->StoreNGram( columns[0], columns[1], freq );
                      break;
                     }

                    case 3:
                     {
                      ngrams->StoreNGram( columns[0], columns[1], columns[2], freq );
                      break;
                     } 

/*
                    case 4:
                     {
                      ngrams->StoreNGram( columns[0], columns[1], columns[2], columns[3], freq );
                      break;
                     } 

                    case 5:
                     {
                      ngrams->StoreNGram( columns[0], columns[1], columns[2], columns[3], columns[4], freq );
                      break;
                     } 
 */

                    default:
                     {
                      /*LEM_STOPIT;*/
                      break;
                     }
                   }  
                  }
                }
              }  
            }
          } 
        }
       else
        {  
         // Считываем лексемы
         while( !reader->eof() )
          {
           Solarix::Search_Engine::Base_File_Lexem bl;

           // Retrive next lexem from stream
           reader->read(bl);

           const bool process=AcceptLexem(bl.word);

           if( process )
            {
             bool show_perc=false;
             switch(scheme)
             {
              case NGrams:
               {
                if( eol_breaks && bl.line!=prev_line )
                 {
                  // Конец строки - принудительно обрываем накопление предложения. 
                  prev_line = bl.line;
                  Process2( L"." );
                 }
           
                Process2( bl.word );
                show_perc=true;
                break;
               }

              case Sentan:
               {
                #if !defined SOL_NO_AA
//                sentan->Process( bl.word );
                #endif
                break;
               }

              case Scheme1: Process(bl.word); show_perc=true; break;
              default: LEM_STOPIT;
             }  

             if( show_perc )
              { 
               if( !(n_lex++%2048) )
                {
                 if( show_completion_by_Mbs )
                  {
                   lem::uint64_t file_pos_64 = raw_file->tellp64();
                   int current_Mb = file_pos_64 /(1024*1024);

                   if( (current_Mb-last_position_Mb)>10 )
                    {
                     last_position_Mb=current_Mb;

                     mout->printf( "%d Mb...", current_Mb );
                     mout->flush();
                    }
                  }
                 else
                  {
                   // Progress indicator refresh. 
                   // Пришло время пересчитать показания градусника.
                   int new_perc = src_size>0 ? int( (bl.where*N_GRAD)/src_size ) : 0;
                
                   if( new_perc>100 )
                    new_perc=100;
                
                   if( new_perc>last_perc )
                    {
                     mout->printf( "%H.", new_perc-last_perc );
                     mout->flush();
                     last_perc = new_perc;
                    }
                  }
                }
              }
            } 
          }

         if( scheme==Scheme1 )
          Process(L"."); // Сбрасываем буфер накопления мультилексем.
        }
      }

     EndDocument();
    }
   catch( const E_BaseException &x )
    {
//DebugBreak();
     lem::mout->printf( "\nError: %us\n", x.what() );
     if( lem::LogFile::IsOpen() )
      lem::LogFile::Print( lem::format_str( L"Error occured when processing file [%s]: %s\n", filename.GetUnicode().c_str(), x.what() ) );
    }
   catch( const std::exception &x )
    {
//DebugBreak();
     lem::mout->printf( "\nError: %s\n", x.what() );
     if( lem::LogFile::IsOpen() )
      lem::LogFile::Print( lem::format_str( L"Error occured when processing file [%s]: %S\n", filename.GetUnicode().c_str(), x.what() ) );
    }
   catch(...)
    {
//DebugBreak();
     lem::mout->printf( "\nError\n" );
     if( lem::LogFile::IsOpen() )
      lem::LogFile::Print( lem::format_str( L"Error occured when processing file [%s]\n", filename.GetUnicode().c_str() ) );
    }
  }
 else if( scheme==ToNouns )
  {
   OUFormatter out( lem::Path("to_nouns.txt") );

   Solarix::Search_Engine::Base_File_Lexem bl;

   // Считываем лексемы
   while( !reader->eof() )
    {
     // Retrive next lexem from stream
     reader->read(bl);

     // Ищем в словаре
     int ie = GetClassMapper()->Find_Entry( bl.word );
     if( ie!=UNKNOWN )
      { 
       const int iclass = sg->GetEntry( ie ).GetClass();

       if( iclass!=NOUN_ru && 
           iclass!=NOUN_en &&
           iclass!=NOUN_fr &&
           iclass!=NOUN_es )
        {
         out.printf( "%us->", bl.word.c_str() ); 

         // преобразуем в существительное
         const int ikey0 = sg->GetEntry(ie).GetKey(); 
         lem::MCollect<int> iek_list; // список связанных существительных

         if( la->Translate_To_Nouns( ikey0, iek_list ) )
          {
           // НАШЛИ ФОРМУ СУЩЕСТВИТЕЛЬНОГО.
           ie = iek_list.front();//sg->FindEntryIndexByKey( iek_list.front() );
           out.printf( "%us", sg->GetEntry(ie).GetName().c_str() );
          }
        }

       out.eol();
      }

     if( !(n_lex++%2048) )
      {
       // Progress indicator refresh. 
       // Пришло время пересчитать показания градусника.
       int new_perc = int( (bl.where*N_GRAD)/src_size );

       if( new_perc>100 )
        new_perc=100;

       if( new_perc>last_perc )
        {
         mout->printf( "%H.", new_perc-last_perc );
         mout->flush();
         last_perc = new_perc;
        }
      }
    }
  }
 else
  {
   LEM_STOPIT;
  }
   
 mout->printf( "| %vfF%d%vn words %vfAOK%vn\n", n_lex );

 #if LEM_DEBUGGING==1 && defined LEM_MSC
 LEM_CHECKIT_Z( _CrtCheckMemory() == TRUE );
 #endif

 if( lem::LogFile::IsOpen() )
  {
   lem::MemFormatter mem;
   mem.printf( "Completed file #%d [%us], elapsed time=%d sec\n", file_counter, filename.GetUnicode().c_str(), et.sec() );
   lem::LogFile::Print( mem.string() );
  }

 return true;
}



// ****************************************************
// Printing the general statistics report on the files
// were processed.
// Общий отчет всех модулей о результатах обработки.
// ****************************************************
void EmpirTextProcessor::Report(void)
{
 switch(scheme)
 {
  case Scheme1: Report1();        break;
  case NGrams: Report2();        break;
  #if !defined SOL_NO_AA
//  case Sentan:  sentan->Report(); break;
  #endif
 } 
}

void EmpirTextProcessor::Report1(void)
{
 // Open the text file stream for writing report.
 // Открываем текстовый файл для печати отчета.
 lem::Path repp( outdir );
 repp.ConcateLeaf(L"empir.rez");
 OUFormatter rep(repp);
 words->Report(rep,*this);

 if( run_chars )
  {
   #if defined EMPIR_SYLLAB
   syllab_stat.Post_Process(*words);
   #endif

   word_stat.Post_Process();

   char_stat.Report(rep);

   #if defined EMPIR_SYLLAB
   syllab_stat.Report(rep,char_stat);
   #endif

   word_stat.Report(rep);
  }

 // Report is now created.
 // Все трудоемкие операции завершены, отчет записан.
 rep.printf(
            "\n\nThis file has been created by EMPIR program.\n"
            "%d seconds have been elapsed.\n"
            , (boost::posix_time::second_clock::local_time()-t0).total_seconds()
           );

 return;
}



void EmpirTextProcessor::Process2( const UCString &l )
{
 if( l==L'\'' || l==L'"'  || l.front()=='_' )
  return;

 if( merge_words )
  {
   word_merger->Push(l);
  
   while( word_merger->IsReady() )
    {
     ProcessInternal2( word_merger->Pop() );
    }
  }
 else
  {
   ProcessInternal2( l );
  }

 return;
}

void EmpirTextProcessor::ProcessInternal2( const UCString &l )
{
 ngrams->Process(l);

 if( dump_unfound_words )
  {  
   if( sol_id->seeker->Find( l, false )==UNKNOWN )
    ngrams_unfound_words.insert(l);
  }

 if( dump_unfound_synonyms )
  {
   if( l==L'.' || l==L'!' || l==L'?' )
    {
     // Сопоставляем предыдущее и новое предложения
     // Для проверки синонимов должно быть только 1 отличие в словах
     if( cur_sent.size()>1 && prev_sent.size()>1 )
      {
       int nmiss=lem::Math::iabs( CastSizeToInt(cur_sent.size())-CastSizeToInt(prev_sent.size()) );
       int imiss=UNKNOWN;
 
       if( nmiss==0 )
        {     
         for( lem::Container::size_type i=0; i<cur_sent.size(); ++i )
          {
           if( cur_sent.GetWord(i)!=prev_sent.GetWord(i) )
            {
             imiss=CastSizeToInt(i);
             nmiss++;
             if( nmiss>=2 )
              break; 
            }
          }

         if( nmiss==1 )
          {
           const UCString &w1 = prev_sent.GetWord(imiss);
           const UCString &w2 = cur_sent.GetWord(imiss);

           // Эти слова являются синонимами?
           lem::MCollect<int> ies1;

           bool syn_found=false;
 
           la->GetAllProjections( w1, false, ies1 );
           if( !ies1.empty() )
            {
             lem::MCollect<int> ies2;
             la->GetAllProjections( w2, false, ies2 );

             for( lem::Container::size_type k2=0; k2<ies2.size() && !syn_found; ++k2 )
              {
               const int ie2 = ies2[k2];

               for( lem::Container::size_type k1=0; k1<ies1.size() && !syn_found; ++k1 )
                {
                 const int ie1 = ies1[k1];

                 lem::MCollect<int> ek1, ek2;
                 la->Synonymize( sg->GetEntry(ie1).GetKey(), ek1 );
                 la->Synonymize( sg->GetEntry(ie2).GetKey(), ek2 );

                 for( lem::Container::size_type i=0; i<ek1.size(); ++i )
                  {
                   int ie11 = ek1[i];//sg->FindEntryIndexByKey(ek1[i]);
                   if( ie2==ie11 )
                    {
                     syn_found=true;
                     break; 
                    }
                  }
               
                 if( !syn_found ) 
                  for( lem::Container::size_type i=0; i<ek2.size(); ++i )
                   {
                    int ie22 = ek2[i];//sg->FindEntryIndexByKey(ek2[i]);
                    if( ie1==ie22 )
                     {
                      syn_found=true;
                      break; 
                     }
                   }
                }
              } 
            } 

           if( !syn_found )
            {
             // Такой синонимической связи НЕТ.
             ngrams_unfound_synonyms.insert( std::make_pair(w1,w2) );
            }
          }
        }
      }
     
     prev_sent = cur_sent;
     cur_sent.clear();
    }
   else
    {
     cur_sent.AddWord(l);
    }
  }

 return;
}


void EmpirTextProcessor::Report2(void)
{
 ngrams->Report();

 if( dump_unfound_words && !ngrams_unfound_words.empty() )
  {
   lem::Path p(outdir);
   p.ConcateLeaf( L"ngrams_unfound_words.txt" );
   lem::OUFormatter txt(p);
   for( std::set<UCString>::const_iterator it=ngrams_unfound_words.begin(); it!=ngrams_unfound_words.end(); ++it )
    txt.printf( "%us\n", it->c_str() );
  }

 if( dump_unfound_synonyms && !ngrams_unfound_synonyms.empty() )
  {
   lem::Path p(outdir);
   p.ConcateLeaf( L"ngrams_unfound_synonyms.txt" );
   lem::OUFormatter txt(p);
   for( std::set< std::pair<UCString,UCString> >::const_iterator it=ngrams_unfound_synonyms.begin(); it!=ngrams_unfound_synonyms.end(); ++it )
    txt.printf( "%us %us\n", it->first.c_str(), it->second.c_str() );
  }

 return;
}


void EmpirTextProcessor::NeedsCharStatistics(void)
{
 char_stat.SetSol(&*sol_id);
 return;
}


void EmpirTextProcessor::Set_Scheme1(void)
{
 words = new WordProcessor(la,segmentation,language_sx_code);
 scheme=Scheme1;
 return;
}


void EmpirTextProcessor::Set_NGrams()
{
 if( sol_id->IsNgramsAvailable() )
  {
   ngrams = new NGramsCollectors(sol_id,lemm);

   if( !main_ngrams )
    {
     NGramsDBMS * tmp_storage = sol_id->GetNgrams()->GetStorage()->CreateDisconnectedClone();
     NGramsStorage_SQLITE * sqlite_tmp_ctorage = dynamic_cast<NGramsStorage_SQLITE*>(tmp_storage);
     if( sqlite_tmp_ctorage==NULL )
      {
       LEM_STOPIT;
      }

     ngrams->SetStorage( lem::Ptr<NGramsDBMS>(sqlite_tmp_ctorage) );
    }
  }
 else
  {
   throw lem::E_BaseException( L"N-gram database is not available" );
  }

 return;
}

void EmpirTextProcessor::Set_ToNouns(void)
{
// cls_mapper = new Class_Mapper( sol_id->GetSynGram() );
}


void EmpirTextProcessor::Set_Sentan(void)
{
/*
 #if !defined SOL_NO_AA
 sentan = new SentanTextProcessor(&*sol_id);
 sentan->SetScheme1();
 sentan->outdir = outdir;
 #endif
*/
}

void EmpirTextProcessor::Scan(void)
{
 if( merging )
  {
   for( lem::Container::size_type i=0; i<scan_folders.size(); i++ )
    {
     lem::Path dbpath = scan_folders[i];
     ngrams->Merge( dbpath, true );
    }
  }
 else
  {
   for( lem::Container::size_type i=0; i<scan_files.size(); i++ )
    {
     ProcessFile( scan_files[i] );
    }

   lem::mout->printf( "List of folders consists of %d items\n", CastSizeToInt(scan_folders.size()) );

   for( lem::Container::size_type i=0; i<scan_folders.size(); i++ )
    {
     const lem::Path &dir = scan_folders[i];
   
     if( dir.IsFolder() )
      {
       std::vector<lem::Path> files;
       dir.ListFiles( files, true );

       lem::mout->printf( "Start processing %d files in [%us]...\n", CastSizeToInt( files.size() ), dir.GetUnicode().c_str() );

       if( lem::LogFile::IsOpen() )
        {
         lem::MemFormatter mem;
         mem.printf( "There are %d files in folder [%us] to be processed\n", CastSizeToInt(files.size()), dir.GetUnicode().c_str() );
         lem::LogFile::Print( mem.string() );
        }

       for( lem::Container::size_type i=0; i<files.size(); i++ )
        {
         ProcessFile( files[i] );
        }
      }
    }
  }

 EndAll();

 return;
}


void EmpirTextProcessor::ProcessFile( const lem::Path &filename )
{ 
 try
  {
   lem::StreamPtr file( new BinaryReader(filename) );

   lem::Ptr<Solarix::Search_Engine::Base_File_Reader> reader = detector->FindReader(
                                                  scanning,
                                                  filename.GetUnicode(),
                                                  to_upper(filename.GetExtension()),
                                                  file 
                                                 );

   if( reader.NotNull() )
    {
     ProcessFile( filename, &*reader, &*file );
    }
  }
 catch(...)
  {
  }

 return; 
}


void EmpirTextProcessor::Set_LexiconProbing(void)
{
 scheme=LexiconProbing;
 return;
}


lem::Path EmpirTextProcessor::GetOutPath( const wchar_t *filename ) const
{
 lem::Path p(outdir);
 p.ConcateLeaf(filename);
 return p;
}



void EmpirTextProcessor::BeginDocument(void)
{
 ngrams->BeginDocument(true);
 return;
}


void EmpirTextProcessor::EndDocument(void)
{
 if( scheme==Scheme1 )
  words->EndDocument();

 if( scheme==NGrams )
  {
   if( merge_words )
    {
     word_merger->ForceReady();

     while( word_merger->IsReady() )
      {
       ProcessInternal2( word_merger->Pop() );
      }
    }

   ngrams->EndDocument(true);
  }

 return;
}

void EmpirTextProcessor::EndAll(void)
{
 if( ngrams.NotNull() )
  ngrams->EndAll(true);

 return;
}


const Class_Mapper* EmpirTextProcessor::GetClassMapper(void)
{
 if( class_mapper==NULL )
  {
   class_mapper = new Class_Mapper( sol_id->GetSynGram() );
  }

 return class_mapper;
}
