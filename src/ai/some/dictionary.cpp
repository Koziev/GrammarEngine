// -----------------------------------------------------------------------------
// File DICTIONARY.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
// Класс Dictionary. Вспомогательные операции по обслуживанию Словаря,
// верхний уровень чтения файлов Словаря. Контейнер для Автоматов Системы.
//
// Класс содержит в себе базовый API для взаимодействия с Грамматической Машиной.
//
// 20.02.2006 - изменен формат сохранения в бинарном виде, в конце записывается
//              доп. информация о версии словаря 
//
// 06.05.2006 - при трансляции словаря в текстовом файле можно командой id=NNN
//              задать версию словаря
//
// 27.10.2006 - перед началом загрузки словаря введена проверка на совместимость 
//              версий кода и словаря. 
//
// 28.09.2007 - правка бага в ~Dictionary(), проявляющемся при нескольких
//              созданных объектах словаря.
//
// 02.10.2007 - введена синхронизация тредов в ctor/dtor
// 03.10.2007 - для эксперимента введена многопточная загрузка модулей словаря
// 03.10.2007 - используется FastFileReader для быстрой загрузки словаря.
// 20.12.2007 - словарь Premium не будет загружаться в версии Pro
// 09.01.2008 - добавлена загрузка справочника N-грамм
// 27.04.2008 - проверка версии словаря перенесена на этап анализа dictionary.xml
// 02.07.2008 - добавлена загрузка OCR движка
// 07.11.2008 - изменен layout бинарного файла словаря
// 06.02.2009 - введена поддержка СУБД FireBird при генерации SQL скрипта словаря
// 20.03.2009 - немного поправлена эхо-печать на консоли при компиляции, чтобы
//              удобнее отображать длинные имена файлов.
// 13.06.2009 - в SQL экспорт словаря добавлены таблицы SG_CLASS_COORD, SG_TAG,
//              SG_TAG_VALUE, SG_LINK_TAG
// 29.01.2010 - правки для поддержки экспорта словаря в SQLite
// 07.02.2010 - расширение поддержки сложных связей - для многословных левых
//              частей заполняется специальная служебная таблица, позволяющая
//              быстро подставлять многословные замены.
// 22.03.2010 - Добавлено поле dic_div для таблиц SG_ENTRY и SG_TENTRY, чтобы
//              организовать работу с основным и пользовательским словарем
//              в рамках одной БД.
// 27.08.2010 - убран столбец SG_ENTRY.I
// 06.01.2011 - добавление ограничений для SQL схемы лемматизатора в FireBird
// 05.02.2011 - добавлена работа с модулем Reconstructor2
// 11.08.2011 - добавлен экспорт таблиц окончаний
// 19.08.2011 - добавлен экспорт таблицы частот словоформ
// 04.09.2011 - добавлен экспорт таблицы опечаток misspelling
// -----------------------------------------------------------------------------
//
// CD->11.10.1995
// LC->23.08.2014
// --------------

#include <lem/system_config.h>
#include <lem/macro_parser.h>
#include <lem/logfile.h>
#include <lem/xml_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/tree_node.h>
#include <lem/solarix/automaton.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/aa_autom.h>
#include <lem/solarix/version.h>
#include <lem/solarix/LexiconStorage_SQLITE.h>
#include <lem/solarix/AlphabetStorage_SQLITE.h>
#include <lem/solarix/ThesaurusStorage_SQLITE.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/WordEntries_SQLite.h>
#include <lem/solarix/NGramsStorage_SQLITE.h>
#include <lem/solarix/Charpos2EntryStorage_SQLITE.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/StartEKeyCounter.h>
#include <lem/solarix/StorageConnections.h>
#include <lem/solarix/Lemmatizator.h>
#include <lem/solarix/LemmatizatorFlags.h>
#include <lem/solarix/LanguageUsage.h>
#include <lem/solarix/LA_UnbreakableRule.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/TextTokenizationRules.h>
#include <lem/solarix/LemmatizatorStorage_SQLITE.h>
#include <lem/solarix/LEMM_Compiler.h>
#include <lem/solarix/MorphologyModels.h>

#if defined SOL_MYSQL_DICTIONARY_STORAGE
#include <lem/solarix/LexiconStorage_MySQL.h>
#include <lem/solarix/ThesaurusStorage_MySQL.h>
#include <lem/solarix/WordEntries_MySQL.h>
#include <lem/solarix/LemmatizatorStorage_MySQL.h>
#include <lem/solarix/AlphabetStorage_MySQL.h>
#include <lem/solarix/Charpos2EntryStorage_MySQL.h>
#endif

#if defined SOL_MYSQL_NGRAMS
#include <lem/solarix/NGramsStorage_MySQL.h>
#endif

#if defined SOL_FIREBIRD_NGRAMS
#include <lem/solarix/NGramsStorage_FireBird.h>
#endif

#if defined SOL_USE_SPEAKER
#include <lem/solarix/Speaker_eSpeak.h>
#endif


// Shorthands... Макросы для удобства доступа к полям...
#define S_ECHO     GetIO().mecho()
#define S_ERR      GetIO().merr()
#define S_JOURNAL  (*lem::LogFile::logfile)


// Somewhere in Windows header this macro is defined. It clashes with
// AddForm member functions, so rub it off.
#undef AddForm

using namespace boost;
using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;


USrcLookUpTable Dictionary::look_up_table;

volatile int Dictionary::counter=0;


#if defined LEM_THREADS
lem::Process::CriticalSection Dictionary::cs_init;
#endif


/**************************************************************************
 Создаем Солярис-процесс. Входные параметры:

  echo - поток (файл) для вывода эхо-сообщений при трансляции.

  err - поток (файл) для печати сообщений об ошибках и предупреждениях
        при трансляции и при работе в режиме Вербальной Машины.

  journal - поток для журнализации. В этом текстовом файле будут
            сохранены сообщения о наиболее важных событиях в работе Системы,
            так что можно будет восстановить причины возможных отказов и так
            далее.

*****************************************************************************/

Dictionary::Dictionary(
                       OFormatter *Echo_Pipe,
                       OFormatter *Err_Pipe,
                       const Dictionary_Config &_cfg
                      )
 : cfg(_cfg), lemmatizer(NULL), debug_symbols(NULL)
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker cs_guard(&cs_init);
 #endif

 counter++;

 Clear();

 nul_stream = NULL;
 if( !Echo_Pipe || !Err_Pipe )
  {
   // One of the echo streams not defined. Let it be NUL stream.
   nul_stream = new OFormatter( lem::Path(NULL_DEVICE) );
  }

 // потоки вывода - для эха, журнализации, ошибок.
 io_env.echo = Echo_Pipe ? Echo_Pipe : nul_stream;
 io_env.err  = Err_Pipe ? Err_Pipe : nul_stream;

 compilation_tracing=0;

 // Загружаем лексические наполнения токенов...
 LoadTokTable();

 #if defined SOL_CAA
 //sol_preset_rnd();
 #endif

 storage = new StorageConnections();
 debug_symbols = new DebugSymbols();

 // Подключаем Автоматы.
 InitA(cfg);
 AttachAutomata();

// ScribbleDown();

 return;
}


void Dictionary::Clear(void)
{
 storage = NULL;

 #if defined SOL_LOADTXT && defined SOL_COMPILER
 lemmatizer_compiler = NULL;
 #endif

 DefaultLanguageID=-2;

 key_counter = START_EKEY_COUNTER;

 // Обнулим список указателей на Автоматы, так что указатели на
 // неподключенные Автоматы останутся равными NULL.
 memset( auto_list, 0, sizeof(auto_list) );
 gg = NULL;
 sg = NULL;
 la = NULL;

 #if !defined SOL_NO_AA
 aa = NULL;
 #endif

 complex_token_list = NULL;
 token_list         = NULL;
 ndelim             = 0;

 io_env.Clear();

 lem_rub_off(lemmatizer);

 return;
}


Dictionary::~Dictionary(void)
{
 Delete();
 return;
}


void Dictionary::AttachAutomata(void)
{
 // Каждый Автомат должен иметь указатель на Словарь.
 for( int i=0; i<SOL_N_AUTOMATA; i++ )
  if( auto_list[i] )
   auto_list[i]->SetDictPtr(this);

 return;
}



void Dictionary::Delete(void)
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker cs_guard(&cs_init);
 #endif

 counter--;

 for( int i1=0; i1<SOL_N_AUTOMATA; i1++ )
  lem_rub_off( auto_list[i1] );

 lem_rub_off(lemmatizer);
 lem_rub_off(debug_symbols);

 #if defined SOL_LOADTXT && defined SOL_COMPILER
 lem_rub_off(lemmatizer_compiler);
 #endif

 #if !defined SOL_NO_NGRAMS
 ngrams.Delete();
 #endif
 affix_table.Delete();
 seeker.Delete();
 #if defined SOL_CAA
 stemmer.Delete();
 #endif


 lem_rub_off(storage);

 if( !counter )
  { 
   if( token_list!=NULL )
    {
     delete[] token_list;
     token_list = NULL;
    }

   if( complex_token_list!=NULL )
    {
     for( int i2=0; i2<SOL_NTOKEN; i2++ )
      delete[] complex_token_list[i2];

     delete[] complex_token_list;
     complex_token_list = NULL;
    }

   ndelim=0;

   if( SOL_UCOMPLEX!=NULL )
    {
     delete[] SOL_UCOMPLEX;
     SOL_UCOMPLEX=NULL;
    }
  }
 
 lem_rub_off(nul_stream);


 for( lem::Container::size_type i=0; i<tokenization_rules.size(); ++i )
  delete tokenization_rules[i];
 tokenization_rules.clear();

 return;
}

// *********************************
// Create the automata...
// *********************************
void Dictionary::InitA( const Dictionary_Config &cfg )
{
 auto_list[SOL_GG_INDEX] = gg = new GraphGram();
 auto_list[SOL_SG_INDEX] = sg = new SynGram(*this,cfg);
 auto_list[SOL_LA_INDEX] = la = new LexicalAutomat();

 #if !defined SOL_NO_AA
 auto_list[SOL_AA_INDEX] = aa = new AlephAutomat();
 #endif

 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void Dictionary::PrepareAfterTranslation( const lem::Path &outdir, const Binarization_Options &opts )
{
 Prepare(outdir,opts);
 return;
}
#endif


/************************************************************************
 Процедура загрузки списка ключевых слов  для парсера.

 Загружается только один набор токенов для всей программы, повторные
 вызовы процедуры будут игнорированы.
*************************************************************************/
void Dictionary::LoadTokTable(void)
{
 if( !!SOL_NDELIM )
  return; // токены уже загружены!

 token_list = new UCString[SOL_NTOKEN];
 complex_token_list = new wchar_t*[SOL_NTOKEN+1];
 memset( complex_token_list, 0, (SOL_NTOKEN+1)*sizeof(void*) );

 // Счетчик для загруженных сложных (многосимвольных) разделителей.
 ndelim=0;

 int i, i_tok=0;

 for( i=0; i<SOL_NTOKEN; i++ )
  {
   const UCString t( sol_toktable[i_tok++] );

   if( t == L'!' )
    {
     const UCString delim( sol_toktable[i_tok++] );

     complex_token_list[ndelim] = new wchar_t[delim.length()+1];
     lem_strcpy( complex_token_list[ndelim], delim.c_str() );
     ndelim++;

     token_list[i] = delim;
     continue;
    }

   // Токен не может иметь пустое лексическое содержимое.
   LEM_CHECKIT_Z( t.length() );
   token_list[i] = t;
  }

 complex_token_list[ndelim] = NULL;
 SOL_COMPLEX = complex_token_list;

 if( look_up_table.empty() )
  {
   vector<UCString> Tokens( token_list, token_list+SOL_NTOKEN );
   look_up_table.Prepare( Tokens );
  }

 SOL_TOKEN         = token_list;
 SOL_NDELIM        = ndelim;
 SOL_LOOK_UP_TABLE = &look_up_table;

 SOL_UCOMPLEX = new UCString[ SOL_NDELIM ];

 for( int j=0; j<SOL_NDELIM; j++ )
  SOL_UCOMPLEX[j] = SOL_COMPLEX[j];

 return;
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
/*************************************************************************
 Подготовка Автоматов к работе в составе Вербальной Машины после загрузки
 из текстового файла Словаря. Смотри текст методов Prepare у Автоматов.
 Аргумент outdir - каталог для сохранения формируемых C++-исходников.
**************************************************************************/
void Dictionary::Prepare( const lem::Path &outdir, const Binarization_Options &opts )
{
 if( lemmatizer_compiler!=NULL )
  lemmatizer_compiler->Prepare();

 if( opts.recompile_syntax )
  {
   GetLexAuto().Prepare(outdir,opts);
   GetAlephAuto().Prepare(outdir,opts);
  }
 else
  {
   for( int i=0; i<SOL_N_AUTOMATA; i++ )
    if( auto_list[i] )
     {
      auto_list[i]->Prepare(outdir,opts);
     }
  }

 return;
}
#endif


/*
// *************************************************************
// Солярис-процесс начал работу - записываем сообщения в журнал.
// *************************************************************
void Dictionary::ScribbleDown(void)
{
 // Заполняем журнал...
 tm_start = boost::posix_time::second_clock::local_time(); // start time

 if( lem::LogFile::IsOpen() )
  S_JOURNAL.printf(
                   "[TIME=%us] SOLARIX version %s\n\n"
                   , to_ustr( tm_start ).c_str()
                   , sol_get_version().c_str()
                  );
 return;
}
*/


#if defined SOL_LOADBIN
// *****************************************************************************
// Попробуем найти для строки соединения connection_string
// её подмену, считая что она представлена как имя узла
// в узле <connections>.
// Это позволяет задать параметры подключения в одном месте,
// и ссылаться на него в нескольких узлах - для лексикона, тезауруса, N-грамм.
// *****************************************************************************
lem::UFString Dictionary::SubstituteConnectionString(
                                                     lem::Xml::Parser &xml,
                                                     const lem::UFString &connection_string
                                                    ) const
{
 LEM_CHECKIT_Z( !connection_string.empty() );

 const lem::Xml::Node* connections = xml.Find_By_Path( L"dataroot.connections" );
 if( connections!=NULL )
  {
   // справочник строк соединения есть, ищем в нем нашу строку.
   for( lem::Container::size_type i=0; i<connections->GetNodes().size(); ++i )
    { 
     const lem::Xml::Node* connection = connections->GetNodes()[i];

     // В атрибутах смотрим имя синонима
     const lem::UFString &cname = connection->GetAttr(L"name");
     if( cname.eqi(connection_string) )
      {
       // нашли, подставляем содержимое узла
       return connection->GetBody();
      }
    }
  }
 
 return connection_string;
}
#endif

#if defined SOL_LOADBIN
bool Dictionary::LoadModules(
                             const lem::Path &_dictionary_xml,
                             const Load_Options &opt
                            )
{
 if( !_dictionary_xml.DoesExist() )
  return false;

 dictionary_xml = _dictionary_xml;
  
 lem::Xml::Parser p;
 p.Load(dictionary_xml);

 // Каталог, в котором находится XML файл, является базовым каталогом для указания
 // всех модулей.
 lem::Path base_path(dictionary_xml);
 base_path.RemoveLastLeaf();
 xml_base_path = base_path;

 // Проверим версию
 bool version_ok=true;

 lem::UFString solarix_version( p.Get_By_Path( L"dataroot.solarix_version" ) );

 lem::UFString sdv(p.Get_By_Path( L"dataroot.dictionary_version" ));
 if( !sdv.empty() && !solarix_version.empty() )
  {
   Solarix::Dictionary::Version dictionary_version(sdv);

   // Проверим, можем ли мы загружать этот словарь.

   // Проверим версию словаря. 0 - всегда версия LITE, начиная с
   // 2 - версии Pro, начиная с 1000 - версии Premium.
   #if defined SOLARIX_PREMIUM
    // Для Premium подходят словари Pro и Premium
    if( dictionary_version.IsFree() )
     {
      version_ok = false;
     }
   #elif defined SOLARIX_PRO
    if( dictionary_version.IsFree() || dictionary_version.IsPremium() )
     {
      version_ok = false;
     }
   #else
    if( dictionary_version.IsPro() )
     {
      version_ok = false;
     }
   #endif

   if( !version_ok )
    {
     // Неподходящая версия словаря, при дальнейшей загрузке
     // могут возникнуть непредсказуемые последствия.
     if( lem::LogFile::IsOpen() )
      {
       lem::LogFile::Print( "Dictionary is not compatible with this grammar engine\n" );
      }

     throw E_BaseException( L"Dictionary is not compatible with this grammar engine" );
    }

   // Версия загружаемого словаря в порядке!
  }
 
 if( !version_ok )
  return false;

 const lem::Xml::Node* abc_provider = p.Find_By_Path( L"dataroot.alphabet_provider" );
 if( abc_provider!=NULL )
  {
   const lem::UFString &provider = abc_provider->GetBody();
   if( provider.eqi(L"sqlite") )
    {
     const lem::Xml::Node* alphabet_db = p.Find_By_Path( L"dataroot.alphabet_db" );
     if( alphabet_db==NULL )
      {
       lem::MemFormatter msg;
       msg.printf( "Invalid [%us] file: alphabet database connection string is missing", dictionary_xml.GetUnicode().c_str() );
       throw E_BaseException(msg.string());
      }
     else
      {
       lem::UFString alphabet_connection_string = BuildSQLiteConnectionString( p, alphabet_db->GetBody(), base_path );
       AlphabetStorage_SQLITE *alphabet_storage = new AlphabetStorage_SQLITE(alphabet_connection_string);
       GetGraphGram().SetStorage(alphabet_storage,true);
      }
    }
   else
    {
     bool connected=false;

     if( storage!=NULL )
      {  
       const lem::Xml::Node* alphabet_db = p.Find_By_Path( L"dataroot.alphabet_db" );
       if( alphabet_db!=NULL )
        {
         lem::UFString connection_string = SubstituteConnectionString( p, alphabet_db->GetBody() );
         StorageConnection *connection = storage->Connect( provider, connection_string );
         if( connection!=NULL )
          {
           #if defined SOL_MYSQL_DICTIONARY_STORAGE
           AlphabetStorage_MySQL *alphabet_storage = new AlphabetStorage_MySQL( (StorageConnection_MySQL*)connection);
           GetGraphGram().SetStorage(alphabet_storage,true);
           connected=true; 
           #endif  
          } 
        }
      }

     if( !connected )
      {
       lem::MemFormatter msg;
       msg.printf( "Can not find lexicon DB provider %us", provider.c_str() );
       throw E_BaseException(msg.string());
      }
    }
  }
 else
  {
   const lem::Xml::Node* alphabet_db = p.Find_By_Path( L"dataroot.alphabet" );
   if( alphabet_db==NULL )
    {
     lem::MemFormatter msg;
     msg.printf( "Invalid [%us] file: alphabet database is missing", dictionary_xml.GetUnicode().c_str() );
     throw E_BaseException(msg.string());
    }
   else
    {
     lem::UFString alphabet_connection_string = BuildSQLiteConnectionString( p, alphabet_db->GetBody(), base_path );
     AlphabetStorage_SQLITE *alphabet_storage = new AlphabetStorage_SQLITE(alphabet_connection_string);
     GetGraphGram().SetStorage(alphabet_storage,true);
    }
  }




 const lem::Xml::Node* nod = p.Find_By_Path( L"dataroot.morphology" );
 if( nod==NULL )
  throw E_BaseException( lem::format_str( L"Incorrect format of dictionary XML file '%ls': missing morphology module", dictionary_xml.GetUnicode().c_str() ).c_str() );

 if( !nod->GetBody().empty() )
  {
   // Для словаря, который полностью размещается в БД и не использует бинарные файлы
   morphology_path = base_path;
   morphology_path.ConcateLeaf( lem::Path(nod->GetBody()) );
   morphology_path = morphology_path.GetAbsolutePath();
  }

 int iattr1 = nod->FindAttr(L"storage");
 if( iattr1!=UNKNOWN )
  {
   const UFString &provider = nod->GetAttrs()[iattr1].second;

   bool connected=false;

   if( storage!=NULL )
    {  
     const lem::Xml::Node* lexicon_db = p.Find_By_Path( L"dataroot.lexicon_db" );
     if( lexicon_db!=NULL )
      {
       if( provider.eqi(L"mysql") )
        {
         lem::UFString connection_string = SubstituteConnectionString( p, lexicon_db->GetBody() );

         StorageConnection *connection = storage->Connect( provider, connection_string );

         #if defined SOL_MYSQL_DICTIONARY_STORAGE
         WordEntries_MySQL *entries = new WordEntries_MySQL( GetSynGram(), (StorageConnection_MySQL*)connection, cfg );
         GetSynGram().SetEntries( entries );
         connected=true;
         #else
         throw lem::E_BaseException( L"MySQL provider is not available in this version of the dictionary" );
         #endif
        }
       else if( provider.eqi(L"sqlite") )
        {
         lem::UFString wordentries_connection_string = BuildSQLiteConnectionString( p, lexicon_db->GetBody(), base_path );
         StorageConnection *connection = storage->Connect( provider, wordentries_connection_string );
         WordEntries_SQLite *entries = new WordEntries_SQLite( GetSynGram(), (StorageConnection_SQLITE*)connection, cfg );
         GetSynGram().SetEntries( entries );
         connected=true; 
        }
      }
    }

   if( !connected )
    {
     lem::MemFormatter msg;
     msg.printf( "Can not find lexicon DB provider %us", provider.c_str() );
     throw E_BaseException(msg.string());
    }
  }
 else
  {
   WordEntries_File *entries = new WordEntries_File( &GetSynGram(), cfg );

   if( !opt.lexicon )
    {
     entries->SetLazyLoad( morphology_path );
     GetLexAuto().SetLazyLoad();
    }

   GetSynGram().SetEntries( entries );
  }

 if( !morphology_path.empty() )
  {
   LoadMorphology( morphology_path, opt );
  }

 const lem::Xml::Node* lexicon_provider = p.Find_By_Path( L"dataroot.lexicon_provider" );
 if( lexicon_provider!=NULL )
  {
   const lem::UFString &provider = lexicon_provider->GetBody();
   if( provider.eqi(L"sqlite") )
    {
     const lem::Xml::Node* lexicon_db = p.Find_By_Path( L"dataroot.lexicon_db" );
     if( lexicon_db==NULL )
      {
       lem::MemFormatter msg;
       msg.printf( "Invalid [%us] file: lexicon database is missing", dictionary_xml.GetUnicode().c_str() );
       throw E_BaseException(msg.string());
      }
     else
      {
       lem::UFString lexicon_connection_string = BuildSQLiteConnectionString( p, lexicon_db->GetBody(), base_path );

       LexiconStorage_SQLITE *lexicon_storage = new LexiconStorage_SQLITE(lexicon_connection_string);
       GetSynGram().SetStorage(lexicon_storage,true);
       GetLexAuto().SetStorage(lexicon_storage,false);
       GetAlephAuto().SetStorage(lexicon_storage,false);
       debug_symbols->SetStorage(lexicon_storage);
      }
    }
   else
    {
     bool connected=false;

     if( storage!=NULL )
      {  
       const lem::Xml::Node* lexicon_db = p.Find_By_Path( L"dataroot.lexicon_db" );
       if( lexicon_db!=NULL )
        {
         lem::UFString connection_string = SubstituteConnectionString( p, lexicon_db->GetBody() );
         StorageConnection *connection = storage->Connect( provider, connection_string );
         if( connection!=NULL )
          {
           #if defined SOL_MYSQL_DICTIONARY_STORAGE
           LexiconStorage_MySQL *lexicon_storage = new LexiconStorage_MySQL( (StorageConnection_MySQL*)connection);
           GetSynGram().SetStorage(lexicon_storage,true);
           GetLexAuto().SetStorage(lexicon_storage,false);
           GetAlephAuto().SetStorage(lexicon_storage,false);
           debug_symbols->SetStorage(lexicon_storage);
           connected=true;
           #endif  
          } 
        }
      }

     if( !connected )
      {
       lem::MemFormatter msg;
       msg.printf( "Can not find lexicon DB provider %us", provider.c_str() );
       throw E_BaseException(msg.string());
      }
    }
  }

 // Получим путь к папке, откуда будем потом при необходимости
 // загружать сегментаторы в виде DLL.
 const lem::Xml::Node* segm_nod = p.Find_By_Path( L"dataroot.segmentation_engines" );
 if( segm_nod==NULL )
  {
   lem::Path segmenters_path = base_path;
   segmenters_path.RemoveLastLeaf();
   SegmenterEngineInfo *info = new SegmenterEngineInfo();
   info->library_path = segmenters_path;
   info->data_path = segmenters_path;
   segmenters_info.push_back(info);
  }
 else
  {
   lem::MCollect<const lem::Xml::Node*> segms = segm_nod->GetNodes(L"segmenter");
   if( segms.empty() )
    {
     lem::UFString p( lem::trim(segm_nod->GetBody()) );
     lem::Path segmenters_path;

     if( segm_nod->FindAttr(L"absolute")!=UNKNOWN && lem::to_bool(segm_nod->GetAttr(L"absolute")) )
      {
       segmenters_path=lem::Path(p).GetAbsolutePath();
      }
     else
      {
       // Путь к сегментатору - относительный к папке с конфигурационным файлом
       segmenters_path = base_path;
       segmenters_path.ConcateLeaf(p);
       segmenters_path = segmenters_path.GetAbsolutePath();
      }

     SegmenterEngineInfo *info = new SegmenterEngineInfo();
     info->library_path = segmenters_path;
     info->data_path = segmenters_path;
     segmenters_info.push_back(info);
    }
   else
    {
     for( lem::Container::size_type i=0; i<segms.size(); ++i )
      {
       SegmenterEngineInfo *info = new SegmenterEngineInfo();

       info->name = segms[i]->Get_By_Path( L"name" );
       info->dll_name = segms[i]->Get_By_Path( L"module" );

       const lem::Xml::Node* n1 = segms[i]->Find_By_Path( L"libpath" );
       if( n1->FindAttr(L"absolute")!=UNKNOWN && lem::to_bool(n1->GetAttr(L"absolute")) )
        {
         info->library_path = lem::Path(segms[i]->Get_By_Path( L"libpath" )).GetAbsolutePath();
        }
       else
        {
         lem::Path x(base_path);
         x.ConcateLeaf(segms[i]->Get_By_Path( L"libpath" ));
         info->library_path = x.GetAbsolutePath();
        }

       const lem::Xml::Node* n2 = segms[i]->Find_By_Path( L"datapath" );
       if( n2->FindAttr(L"absolute")!=UNKNOWN && lem::to_bool(n2->GetAttr(L"absolute")) )
        {
         info->data_path = lem::Path(segms[i]->Get_By_Path( L"datapath" )).GetAbsolutePath();
        }
       else
        {
         lem::Path x(base_path);
         x.ConcateLeaf(segms[i]->Get_By_Path( L"datapath" ));
         info->data_path = x.GetAbsolutePath();
        }        

       info->params = segms[i]->Get_By_Path( L"params" );
       info->params.re_clear();

       segmenters_info.push_back(info);
      }
    }
  }


 if( opt.lemmatizer )
  {
   const lem::Xml::Node* lemmatizer_provider = p.Find_By_Path( L"dataroot.lemmatizer_provider" );
   if( lemmatizer_provider!=NULL )
    {
     bool enabled=true;

     if( lemmatizer_provider->FindAttr(L"enabled")!=UNKNOWN )
      enabled = lem::to_bool(lemmatizer_provider->GetAttr(L"enabled"));

     if( enabled )
      {
       // Лемматизатор располагается в реляционной БД
       const lem::UFString &provider = lemmatizer_provider->GetBody();
       bool connected=false;

       if( storage!=NULL )
        {  
         const lem::Xml::Node* lemmatizer_db = p.Find_By_Path( L"dataroot.lemmatizer_db" );
         if( lemmatizer_db!=NULL )
          {
           lem::UFString connection_string = SubstituteConnectionString( p, lemmatizer_db->GetBody() );

           if( provider.eqi(L"mysql") )
            {
             StorageConnection *connection = storage->Connect( provider, connection_string );
             if( connection!=NULL )
              {
               #if defined SOL_MYSQL_DICTIONARY_STORAGE
               LemmatizatorStorage_MySQL *lemmatizer_storage = new LemmatizatorStorage_MySQL((StorageConnection_MySQL*)connection);
               lemmatizer = lemmatizer_storage;
               connected=true;
               #endif
              } 
            }
           else if( provider.eqi(L"sqlite") )
            {
             lem::UFString lemmatizer_connection_string = BuildSQLiteConnectionString( p, lemmatizer_db->GetBody(), base_path );
             StorageConnection *connection = storage->Connect( provider, lemmatizer_connection_string );
             if( connection!=NULL )
              {
               LemmatizatorStorage_SQLITE *lemmatizer_storage = new LemmatizatorStorage_SQLITE((StorageConnection_SQLITE*)connection);
               lemmatizer = lemmatizer_storage;
               connected=true;
              } 
            }
          }
        }

       if( !connected )
        {
         lem::MemFormatter msg;
         msg.printf( "Can not find lemmatizer DB provider %us", provider.c_str() );
         throw E_BaseException(msg.string());
        }
      } 
    }
   else
    {
     const lem::Xml::Node* lemmatizer_nod = p.Find_By_Path( L"dataroot.lemmatizer" );
     if( lemmatizer_nod!=NULL )
      {
       // Лемматизатор загружаем из NoSQL хранилища

       bool enabled=true;

       if( lemmatizer_nod->FindAttr(L"enabled")!=UNKNOWN )
        enabled = lem::to_bool(lemmatizer_nod->GetAttr(L"enabled"));

       if( enabled )
        {
         lem::Path lemm_path;
         
         if( lemmatizer_nod->FindAttr(L"absolute")!=UNKNOWN && lem::to_bool(lemmatizer_nod->GetAttr(L"absolute")) )
          {
           lemm_path = lem::Path(lemmatizer_nod->GetBody());
          }
         else
          {  
           lemm_path = base_path;
           lemm_path.ConcateLeaf( lem::Path(lemmatizer_nod->GetBody()) );
           lemm_path = lemm_path.GetAbsolutePath();
          }
      
         int lemm_flags = opt.force_lemmatizer_fastest_mode ? LEME_FASTEST : LEME_DEFAULT;
      
         int iattr1 = nod->FindAttr(L"flags");
         if( iattr1!=UNKNOWN )
          {
           const UFString &lflags = nod->GetAttrs()[iattr1].second;
           if( lflags.eqi(L"faster") )
            lemm_flags = LEME_FASTER;
           else if( lflags.eqi(L"fastest") )
            lemm_flags = LEME_FASTEST;
           else if( lflags.eqi(L"default") )
            lemm_flags = LEME_FASTEST;
           else
            {
             lem::MemFormatter mem;
             mem.printf( "Unknown value %us for 'flags' in <lemmatizer>", lflags.c_str() );
             throw E_BaseException(mem.string());
            } 
          } 
      
         Lemmatizator *l = new Lemmatizator();
         l->Load( lem::Path(lemm_path), lemm_flags );
         lemmatizer = l;
        }
      }
    }
  } // if( opt.lemmatizer )


 if( opt.load_semnet )
  {
   // Попробуем подключить тезаурус.

   const lem::Xml::Node* thesaurus_provider = p.Find_By_Path( L"dataroot.thesaurus_provider" );
   if( thesaurus_provider!=NULL )
    {
     const lem::UFString &provider = thesaurus_provider->GetBody();
     if( provider.eqi(L"sqlite") )
      {
       const lem::Xml::Node* thesaurus_db = p.Find_By_Path( L"dataroot.thesaurus_db" );
       if( thesaurus_db==NULL )
        {
         lem::MemFormatter msg;
         msg.printf( "Invalid [%us] file: thesaurus database is missing", dictionary_xml.GetUnicode().c_str() );
         throw E_BaseException(msg.string());
        }
       else
        {
         lem::UFString thesaurus_connection_string = BuildSQLiteConnectionString( p, thesaurus_db->GetBody(), base_path );
         ThesaurusStorage_SQLITE *thesaurus_storage = new ThesaurusStorage_SQLITE(thesaurus_connection_string);
         GetSynGram().Get_Net().SetStorage(thesaurus_storage,true);
        }
      }
     else
      {
       bool connected=false;

       if( storage!=NULL )
        {  
         const lem::Xml::Node* thesaurus_db = p.Find_By_Path( L"dataroot.thesaurus_db" );
         if( thesaurus_db!=NULL )
          {
           lem::UFString connection_string = SubstituteConnectionString( p, thesaurus_db->GetBody() );

           StorageConnection *connection = storage->Connect( provider, connection_string );
           if( connection!=NULL )
            {
             #if defined SOL_MYSQL_DICTIONARY_STORAGE
             ThesaurusStorage_MySQL *thesaurus_storage = new ThesaurusStorage_MySQL((StorageConnection_MySQL*)connection);
             GetSynGram().Get_Net().SetStorage(thesaurus_storage,true);
             connected=true; 
             #endif
            } 
          }
        }

       if( !connected )
        {
         lem::MemFormatter msg;
         msg.printf( "Can not find thesaurus DB provider %us", provider.c_str() );
         throw E_BaseException(msg.string());
        }
      }
    }
  }

 if( opt.affix_table )
  {
   nod = p.Find_By_Path( L"dataroot.affixes" );
   if( nod!=NULL && nod->GetBody().empty()==false )
    { 
     lem::Path affix_path(base_path);
     affix_path.ConcateLeaf( lem::Path(nod->GetBody()) );
     LoadAffixTable(affix_path);
    }
  }
 else
  {
   // Создадим пустую таблицу стеммера
   affix_table = boost::shared_ptr<Solarix::Affix_Table>( new Solarix::Affix_Table() );
  }
  
 if( opt.seeker )
  {
   nod = p.Find_By_Path( L"dataroot.seeker" );
   if( nod!=NULL && nod->GetBody().empty()==false )
    { 
     lem::Path seeker_path(base_path);
     seeker_path.ConcateLeaf( lem::Path(nod->GetBody()) );
     LoadSeeker(seeker_path);
    }
  }

 if( opt.stemmer )
  {
   nod = p.Find_By_Path( L"dataroot.stemmer" );
   if( nod!=NULL && nod->GetBody().empty()==false )
    { 
     lem::Path stemmer_path(base_path);
     stemmer_path.ConcateLeaf( lem::Path(nod->GetBody()) );
     LoadStemmer(stemmer_path);
    }
  }

 #if !defined SOL_NO_NGRAMS
 if( opt.ngrams )
  {
   const lem::Xml::Node* ngrams_provider = p.Find_By_Path( L"dataroot.ngrams_provider" );
   if( ngrams_provider!=NULL )
    {
     const lem::UFString &provider = ngrams_provider->GetBody();
     bool connected=false;
  
     if( storage!=NULL )
      {  
       const lem::Xml::Node* ngrams_db = p.Find_By_Path( L"dataroot.ngrams_db" );
       if( ngrams_db!=NULL )
        {
         lem::UFString connection_string = SubstituteConnectionString( p, ngrams_db->GetBody() );
         if( provider.eqi(L"mysql") )
          { 
           StorageConnection *connection = storage->Connect( provider, connection_string );
           if( connection!=NULL )
            {
             #if defined SOL_MYSQL_NGRAMS
             NGramsStorage_MySQL *ngrams_storage = new NGramsStorage_MySQL((StorageConnection_MySQL*)connection);
             LoadNgrams( lem::Path(), ngrams_storage );
             connected=true; 
             #endif
            }
          }
         else if( provider.eqi(L"firebird") )
          {
           StorageConnection *connection = storage->Connect( provider, connection_string );
           if( connection!=NULL )
            {
             #if defined SOL_FIREBIRD_NGRAMS
             NGramsStorage_MySQL *ngrams_storage = new NGramsStorage_FireBird((StorageConnection_FireBird*)connection);
             LoadNgrams(lem::Path(),ngrams_storage);
             connected=true;
             #endif
            }
          }
         else if( provider.eqi(L"sqlite") )
          {
           lem::UFString ngrams_connection_string = BuildSQLiteConnectionString( p, connection_string, base_path );

           StorageConnection *connection = storage->Connect( provider, ngrams_connection_string );
           if( connection!=NULL )
            {
             NGramsStorage_SQLITE *ngrams_storage = new NGramsStorage_SQLITE();
             LoadNgrams( lem::Path(), ngrams_storage );
             connected=true; 
            }
          } 
        }
      }
  
     if( !connected )
      {
       lem::MemFormatter msg;
       msg.printf( "Can not find ngrams DB provider %us", provider.c_str() );
       throw E_BaseException(msg.string());
      }
    }
   else
    {
     nod = p.Find_By_Path( L"dataroot.ngrams" );

     lem::Path ngrams_path;

     if( nod!=NULL )
      {
       if( nod->FindAttr(L"absolute")!=UNKNOWN && lem::to_bool(nod->GetAttr(L"absolute")) )
        {
         ngrams_path = lem::Path(nod->GetBody());
        }
       else
        {
         // путь к папке с базой N-грамма задан относительно каталога с конфигом.
         ngrams_path = base_path;
         ngrams_path.ConcateLeaf(nod->GetBody());
        }

       LoadNgrams(ngrams_path.GetAbsolutePath(),new NGramsStorage_SQLITE());
      }
    }
  }
 #endif


 const lem::Xml::Node* pes_nod = p.Find_By_Path( L"dataroot.prefix_entry_searcher" );
 if( pes_nod!=NULL )
  {
   prefix_entry_searcher_provider = L"sqlite";
   prefix_entry_searcher_connection_string = BuildSQLiteConnectionString( p, pes_nod->GetBody(), base_path );
  }
 else
  {
   const lem::Xml::Node* pes_provider = p.Find_By_Path( L"dataroot.prefix_entry_searcher_provider" );
   if( pes_provider!=NULL )
    {
     prefix_entry_searcher_provider = pes_provider->GetBody();

     const lem::Xml::Node* pes_db = p.Find_By_Path( L"dataroot.prefix_entry_searcher_db" );
     if( pes_db==NULL )
      {
       lem::MemFormatter err;
       err.printf( "Did not find node 'prefix_entry_searcher_db' in %us", dictionary_xml.GetUnicode().c_str() );
       throw lem::E_BaseException( err.string() );
      }
     else
      {
       if( prefix_entry_searcher_provider.eqi(L"sqlite") )
        {
         prefix_entry_searcher_connection_string = BuildSQLiteConnectionString( p, pes_db->GetBody(), base_path );
        }
       else
        {
         prefix_entry_searcher_connection_string = SubstituteConnectionString( p, pes_db->GetBody() );
        }
      }
    }
  }

 const lem::Xml::Node* model_folder = p.Find_By_Path( L"dataroot.models" );
 if( model_folder!=NULL )
  {
   const lem::Xml::Node * sequence_labeler_folder = model_folder->GetNode( L"sequence_labeler" );
   if( sequence_labeler_folder!=NULL )
    {
     lem::Path model_path = base_path;
     model_path.ConcateLeaf( lem::Path(sequence_labeler_folder->GetBody()) );
     model_path = model_path.GetAbsolutePath();
     GetLexAuto().GetModel().GetSequenceLabeler().SetModelPath(model_path);
    }

   const lem::Xml::Node * classifier_folder = model_folder->GetNode( L"classifier" );
   if( classifier_folder!=NULL )
    {
     lem::Path model_path = base_path;
     model_path.ConcateLeaf( lem::Path(classifier_folder->GetBody()) );
     model_path = model_path.GetAbsolutePath();
     GetLexAuto().GetModel().GetClassifier().SetModelPath(model_path);
    }
  }


 // Ждем окончания загрузки всех модулей
 // ...

 // При необходимости даем возможность автоматам настроить свои таблицы после
 // загрузки словаря.
 for( int i=0; i<SOL_N_AUTOMATA; i++ )
  if( auto_list[i]!=NULL )
   auto_list[i]->DictionaryLoaded();

 return true;
}
#endif


lem::UFString Dictionary::BuildSQLiteConnectionString(
                                                      lem::Xml::Parser &parser,
                                                      const lem::UFString &raw_string,
                                                      const lem::Path &xml_dir
                                                     ) const
{
 lem::UFString connection_string = SubstituteConnectionString( parser, raw_string );

 if( connection_string.eq_begi(L"path=") || connection_string.eq_begi(L"file=") )
  {
   connection_string += ";basedir=";
   connection_string += xml_dir.GetUnicode();
  }
 else
  {
   lem::Path db_path(xml_dir);
   db_path.ConcateLeaf( connection_string );
   connection_string = db_path.GetUnicode();
  }

 return connection_string;
}



#if defined SOL_LOADBIN && defined SOL_COMPILER
void Dictionary::PrepareForMerging(void)
{
 GetSynGram().PrepareForMerging();
 return;
}
#endif


#if defined SOL_LOADBIN && defined SOL_COMPILER
void Dictionary::BeforeSyntaxRecompilation(void)
{
 GetSynGram().GetStorage().DeleteSourceLocations();

 GetGraphGram().BeforeSyntaxRecompilation();
 GetLexAuto().BeforeSyntaxRecompilation();
 GetAlephAuto().BeforeSyntaxRecompilation();

 return;
}
#endif


#if defined SOL_LOADBIN
/*************************************************
 Загрузка информации в Словарь из бинарного файла.
**************************************************/
void Dictionary::LoadMorphology( const lem::Path &morphology_path, const Solarix::Load_Options &opt )
{
 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Loading morphology from [%us]...\n", morphology_path.GetUnicode().c_str() );

 #if defined LEM_WINDOWS
  #if defined LEM_WIN98
  BinaryReader bin(morphology_path);
  #else
  FastFileReader bin(morphology_path);
  #endif
 #else
 BinaryReader bin(morphology_path);
 #endif

 LoadBin(bin,opt);

 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Morphology has been loaded from [%us]\n", morphology_path.GetUnicode().c_str() );

 return;
}
#endif


#if defined SOL_LOADBIN
void Dictionary::LoadAffixTable( const lem::Path &affix_path )
{
 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Loading affixes table from [%us]...\n", affix_path.GetUnicode().c_str() );

 affix_table = boost::shared_ptr<Solarix::Affix_Table>( new Solarix::Affix_Table() );
 BinaryReader afxbin( affix_path );
 affix_table->LoadBin( afxbin );

 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Affixes table has been loaded from [%us]\n", affix_path.GetUnicode().c_str() );

 return;
}
#endif


#if defined SOL_LOADBIN
void Dictionary::LoadSeeker( const lem::Path &seeker_path )
{
 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Loading seeker from [%us]...\n", seeker_path.GetUnicode().c_str() );

 lem::BinaryReader skrbin( seeker_path );
 seeker = boost::shared_ptr<Solarix::LD_Seeker>( GetSynGram().GetEntries().Load_Seeker(skrbin) );

 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Seeker has been loaded from [%us]\n", seeker_path.GetUnicode().c_str() );

 return;
}
#endif


#if defined SOL_LOADBIN
void Dictionary::LoadStemmer( const lem::Path &stemmer_path )
{
 #if defined SOL_CAA
 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Loading stemmer from [%us]...\n", stemmer_path.GetUnicode().c_str() );

 if( !stemmer )
  {
   stemmer = boost::shared_ptr<Solarix::SG_Stemmer>( new Solarix::SG_Stemmer() );
  }

 stemmer->Load( stemmer_path );

 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Stemmer has been loaded from [%us]\n", stemmer_path.GetUnicode().c_str() );
 #endif

 return;
}
#endif

#if defined SOL_LOADBIN && !defined SOL_NO_NGRAMS
void Dictionary::LoadNgrams( const lem::Path &ngrams_path, NGramsDBMS *storage )
{
 #if !defined SOL_NO_NGRAMS
 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Loading ngrams from [%us]...\n", ngrams_path.GetUnicode().c_str() );

 if( !ngrams )
  {
   ngrams = new Solarix::Ngrams(this);
  }

 ngrams->SetStorage(storage);

 if( !ngrams_path.empty() )
  {
   try
    {
     ngrams->Load( ngrams_path );

     if( lem::LogFile::IsOpen() )
      lem::LogFile::logfile->printf( "Ngrams have been loaded from [%us]\n", ngrams_path.GetUnicode().c_str() );
    }
   catch( const E_BaseException & e )
    {
     if( lem::LogFile::IsOpen() )
      lem::LogFile::logfile->printf( "Ngrams load error: %us\n", e.what() );
    }
   catch( ... )
    {
     if( lem::LogFile::IsOpen() )
      lem::LogFile::logfile->printf( "Ngrams load error" );
    }
  }

 #endif

 return;
}
#endif

#if defined SOL_LOADBIN
/*************************************************
 Загрузка информации в Словарь из бинарного файла.
**************************************************/
void Dictionary::LoadBin( lem::Stream &binfile, const Load_Options &opt )
{
 loaded = false;

 // Номер версии словаря записывается в самом конце файла, прочитаем
 // его сразу.
 binfile.seekp( binfile.fsize()-4 );
 binfile.read( &version, sizeof(version) );
 binfile.seekp(0);

 if( Check_Binary_File_Header(binfile,true)!=true )
  {
   return;
  }

// optimized = binfile.read_bool();
 bool dummy = binfile.read_bool();

 // Загружаем таблицу с информацией о сохраненных в файле Автоматах.
 size_t a_begin[SOL_N_AUTOMATA];
 size_t a_end;
 bool a_presence[SOL_N_AUTOMATA];

 binfile.read( a_begin,    sizeof(a_begin)    );
 binfile.read( a_presence, sizeof(a_presence) );
 binfile.read( &a_end,     sizeof(a_end)      );

 for( int i=SOL_N_AUTOMATA-1; i>=0; i-- )
  // Автомат нужно загрузить, если он был сохранен в файле и прикомпилирован
  // в нашей программе.
  if( i!=SOL_GG_INDEX && auto_list[i]!=NULL && a_presence[i] )
   {
    // Перемещаем указатель чтения на начало байтового блока для Автомата.
    binfile.seekp( a_begin[i] );
    auto_list[i]->LoadBin(binfile,opt);
    auto_list[i]->AfterLoadBin();
   }

 // Все Автоматы загружены.

 // Продолжаем загрузку.
 binfile.seekp( a_end );

 binfile.read( &key_counter, sizeof(key_counter) );

 #if defined SOL_CAA
 Initialize();
 #endif

 loaded = true;

 return;
}
#endif



#if defined SOL_SAVEBIN
/*********************************************************************
         Сохранение Словаря Системы в бинарном потоке.

 Перед непосредственно записью содержимого Словаря в поток bin там
 сохраняются некоторые значения, которые помогают зафиксировать
 возникновение такой неприятной ошибки: Словарь был оттранслирован
 16-битным Транслятором, а читается 32-битным, или что-то в этом
 роде. Сохранив сейчас байтовый размер типа int, а также
 константу LEM_CSTRING_LEN, задающую максимальную вместимость класса
 UCString, мы сможем в методе ::LoadBin проконтролировать совпадение
 этих значений.
**********************************************************************/
void Dictionary::SaveBin( lem::Stream &bin ) const
{
 Write_Binary_File_Header(bin);

// bin.write_bool( optimized );
 bin.write_bool( false ); // зарезервировано

 // Формируем таблицу с информацией о сохраненных в файле Автоматах.
 Stream::pos_type table_pos = bin.tellp();

 Stream::pos_type a_begin[SOL_N_AUTOMATA];
 Stream::pos_type a_end;
 bool a_presence[SOL_N_AUTOMATA];

 // Пока вписываем пустую табличку.
 bin.write( a_begin,    sizeof(a_begin)    );
 bin.write( a_presence, sizeof(a_presence) );
 bin.write( &a_end,     sizeof(a_end)      );

 memset( a_presence, 0, sizeof(a_presence) );

 for( int i=SOL_N_AUTOMATA-1; i>=0; i-- )
  if( !!auto_list[i] && i!=SOL_GG_INDEX )
   {
    a_presence[i] = true;
    a_begin[i] = bin.tellp();
    auto_list[i]->SaveBin(bin);
   }

 a_end = bin.tellp();

 bin.write( &key_counter,   sizeof(key_counter)   );
// bin.write( &sol_key_counter, sizeof(sol_key_counter) );

 // Записываем доп. сведения о версии словаря
 bin.write( &version, sizeof(version) );

 lem::Stream::pos_type fullend = bin.tellp();

 // Теперь вписываем заполненную табличку.
 bin.seekp( table_pos );
 bin.write( a_begin,    sizeof(a_begin)    );
 bin.write( a_presence, sizeof(a_presence) );
 bin.write( &a_end,     sizeof(a_end)      );

 // И перемещаем указатель записи для продолжения.
 bin.seekp( fullend );

 return;
}

#endif

#if defined SOL_REPORT
void Dictionary::MapAlphabet( OFormatter &txt )
{
 GetGraphGram().PrintMap(txt);
 return;
}
#endif


#if defined SOL_REPORT
void Dictionary::MapLexicon( OFormatter &txt )
{
 GetSynGram().PrintMap(txt);
 GetLexAuto().PrintMap(txt);
 return;
}
#endif

#if defined SOL_REPORT
void Dictionary::MapTransformer( OFormatter &txt )
{
 GetAlephAuto().PrintMap(txt);
 return;
}
#endif



#if defined SOL_REPORT
/*****************************************************************************
 Данная процедура выполняет работу, аналогичную PrintMap, но информация
 печатается в файл ЛИСТИНГА, кроме того, объём выгружаемых данных значительно
 меньше: просто сведения о загрузке кэшей, потреблении оперативной памяти,
 и так далее.

 Пример использования данной процедуры: программа YMAP.
******************************************************************************/
void Dictionary::Report( OFormatter &dst_stream ) const
{
 for( int i=0; i<SOL_N_AUTOMATA; i++ )
  if( auto_list[i] )
   {
    dst_stream.eol();
    auto_list[i]->Report(dst_stream);
   }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
/***************************************************************************
 После трансляции Словаря из текстового в бинарное представление потребовано
 выполнить оптимизацию получившихся внутренних структур, чтобы повысить
 эффективность работы Системы в режиме Вербальной Машины.
****************************************************************************/
void Dictionary::Optimize(void)
{
 for( int i=0; i<SOL_N_AUTOMATA; i++ )
  if( auto_list[i] )
   auto_list[i]->Optimize();

 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
/***************************************************************************
 Загрузка Словаря из ТЕКСТОВОГО файла, трансляция команд языка ПРИИСК.
 Компиляция конструкций языка Sovereign. Чтение организовано иерархически,
 то есть класс Dictionary читает только имена секций файла и перепоручает
 соответствующим подсистемам (автоматам и грамматикам) разбираться с
 содержимым секций.
****************************************************************************/
void Dictionary::LoadTxt(
                         lem::Stream &src_stream,
                         const MCollect<UCString> &defines,
                         const Binarization_Options &options,
                         const CodeConverter &in_cp,
                         const UFString& root_dir
                        )
{
 // Do force error messages to be printed in journal also.
 if( lem::LogFile::IsOpen() )
  S_ERR.SetDoubler( &(S_JOURNAL) );

 S_ECHO.printf( "%vfE%us%vn...", src_stream.GetName().GetUnicode().c_str() );

 if( GetDebugLevel_ir()>=3 )
  S_ECHO.eol();

 // Translation start time.
 const boost::posix_time::ptime t1 = boost::posix_time::second_clock::local_time();

 Macro_Parser txtfile;

 txtfile.SetDefines(defines);
 txtfile.SetOptions(options.parsing);
 txtfile.SetCodeConverter(&in_cp);
 txtfile.SetRootDir(root_dir);


 if( GetDebugLevel_ir()>=3 )
  txtfile.SetOptions( SRC_BETH_ECHO_PRINT, false );

 MCollect<UCString> Tokens( SOL_TOKEN, SOL_TOKEN+SOL_NTOKEN );
 txtfile.SetTokens( Tokens );

 MCollect<UCString> Delims( SOL_UCOMPLEX, SOL_UCOMPLEX+SOL_NDELIM );
 txtfile.SetComplDelims( Delims );
 txtfile.Set_io( GetIO() );

 txtfile.Open(&src_stream);

 bool load=true;
 while( load && !txtfile.eof() ) /* do until no more input */
  {
   const BethToken t=txtfile.read();

   if( t.string()==L"set" )
    {
     const lem::Iridium::BethToken & opt = txtfile.read();

     if( opt.string()==L"originator" )
      {
       UCString originator = txtfile.read();
       originator.strip(L'"'); 
       SetCurrentOriginator(originator);
      }
     else
      {
       Print_Error(opt,txtfile);
       GetIO().merr().printf(
                             "Invalid parameter name [%vfE%us%vn] for %vfEset%vn directive\n"
                             , opt.string().c_str()
                            );
       throw E_ParserError();
      } 

     continue;
    } 

   if( t.string().eqi(L"version") )
    {
     txtfile.read_it( B_EQUAL );
     version.code = txtfile.read_int();
     continue;
    }

   switch(t.GetToken())
    {
     case B_AUTOMAT:
      {
       const BethToken aut_name=txtfile.read();

       bool parsed=false;

       if( aut_name.eqi( L"lemmatizer" ) )
        {
         parsed = true;

         if( lemmatizer_compiler==NULL )
          lemmatizer_compiler = new LEMM_Compiler();

         lemmatizer_compiler->LoadTxt( txtfile, *this );
        }
       else
        {
         for( int i=0; i<SOL_N_AUTOMATA && !parsed; i++ )
          if( auto_list[i] && auto_list[i]->GetName()==aut_name.string() )
           {
            auto_list[i]->LoadTxt(txtfile,options);
            parsed=true;
           }
        }

       if( !parsed )
        {
         // Секция для неизвестного автомата.
         GetIO().merr().printf(
                               "%vfDUnknown Automaton [%us] section header read%vn\n"
                               , aut_name.string().c_str()
                              );
         Print_Error( aut_name, txtfile );
         throw E_ParserError();
        }

       break;
      }

     case B_EOF_REACHED:
      load = false;
      break;

     default:
      {
       bool parsed=false;
       for( int i=0; i<SOL_N_AUTOMATA && !parsed; i++ )
        if( auto_list[i] && auto_list[i]->ProcessLexem2(t,txtfile,options) )
         {
          parsed=true;
          break;
         }

       if( !parsed )
        {
         GetIO().merr().printf( "%vfDInvalid token [%us]%vn\n", t.string().c_str() );
         Print_Error( t, txtfile );
         throw E_ParserError();
        }
      }
    }
  }

 const boost::posix_time::ptime t2 = boost::posix_time::second_clock::local_time();
 const int et = (t2-t1).total_seconds(); // Translation time elapsed.

 // Сообщение о конце трансляции...
 if( GetDebugLevel_ir()>=3 )
  S_ECHO.printf( "File [%vfE%us%vn] is translated %vfAOK%vn\n", src_stream.GetName().GetUnicode().c_str() );
 else
  S_ECHO.printf( "%64t%vf9%W6d%vn lines %vfAOK%vn\n", txtfile.GetLineCount() );

 S_ERR.ClearDoubler();
 return;
}
#endif




/*
#if defined SOL_CAA
void Dictionary::Squeeze(void)
{
 for( int i=0; i<SOL_N_AUTOMATA; i++ )
  if( auto_list[i] )
   auto_list[i]->Squeeze();

 return;
}
#endif
*/

#if defined SOL_CAA
/*******************************************************************
 Инициализация - подготовка автоматов к работе в режиме Вербальной
 Машины (SOL_CAA).
********************************************************************/
void Dictionary::Initialize(void)
{
 for( int i=0; i<SOL_N_AUTOMATA; i++ )
  if( auto_list[i] )
   auto_list[i]->Initialize();

 return;
}
#endif



/*
#if defined SOL_CAA && !defined SOL_NO_AA
bool Dictionary::GetPhrase( wchar_t **phrase )
{
 *phrase = NULL;

 VA_SpeakSpace *SS = GetSpeakAuto().GetSpacePtr();
 Phrasema *x = SS->PickFromQueue();
 if( x!=NULL )
  {
   // Копируем текстовое представление, игнорируем звуковое...
   const UFString &res = x->GetTxt();
   if( res.length() )
    {
     *phrase = new wchar_t[ res.length()+1 ];
     lem_strcpy( *phrase, res.c_str() );
    }

   delete x;
   return true;
  }

 return false;
}
#endif
*/

#if defined SOL_CAA && !defined SOL_NO_AA
/*******************************************************************
 Отличается от процедуры GetPhrase возвращает также и звуковую
 информацию...
********************************************************************/
/*
bool Dictionary::GetPhraseAndSound(
                                   wchar_t **phrase,
                                   int *n_fragment,
                                   size_t **fragment_size_list,
                                   lem::uint8_t ***fragment_block_list,
                                   int **fragment_vkey_list
                                  )
{
 *phrase = NULL;

 VA_SpeakSpace *SS = GetSpeakAuto().GetSpacePtr();
 Phrasema *x = SS->PickFromQueue();
 if( x!=NULL )
  {
   // Копируем текстовое представление
   const UFString &res = x->GetTxt();
   if( res.length() )
    {
     *phrase = new wchar_t[ res.length()+1 ];
     lem_strcpy( *phrase, res.c_str() );
    }

   // Копируем звуковое представление...

   // Число звуковых фрагментов.
   const int N = x->GetSound().size();

   *n_fragment = N;
   *fragment_size_list  = NULL;
   *fragment_block_list = NULL;
   if(N)
    {
     *fragment_size_list = new size_t[N];
     *fragment_block_list = new uint8_t*[N];
     *fragment_vkey_list = new int[N];

     for( int i=0; i<N; i++ )
      {
       (*fragment_size_list)[i] = x->GetSound().GetSize(i);

       // На самом деле бинарное содержимое звуковых фрагментов может
       // быть не задано, а спецификация содержимого фразы сделана только
       // указанием ключей звуковых фрагментов в Звуковой Граматике.
       if( x->GetSound().GetSize(i) )
        {
         (*fragment_block_list)[i] = new uint8_t[x->GetSound().GetSize(i)];
         memcpy( (*fragment_block_list)[i], x->GetSound().GetBlock(i), x->GetSound().GetSize(i) );
        }
       else
        (*fragment_block_list)[i] = NULL;

       (*fragment_vkey_list)[i] = x->GetSound().Getint(i);
      }
    }

   delete x;
   return true;
  }

 return false;
}
*/
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
/*****************************************************************************
 Трансляция Словаря из текстового файла во внутреннее бинарное представление
 (первая фаза бинаризации Словаря).

  defines - pointer to string containing one or several macros (flags).
            Ignored when NULL. Each macro flag must be followed by
            semicolon ';', like this:

              char Defines[] = "Russian;Normal;Fast_Temp"

  options - OR-combined group of translation control flags. See [api_stat.h]
            header file for list of options available.

 Пример использования данной процедуры: программа YGRES.
******************************************************************************/
void Dictionary::LoadTxt(
                         lem::Stream &txt,
                         const char *defines,
                         const Binarization_Options &options,
                         const CodeConverter &cp,
                         const UFString& root_dir
                        )
{
 MCollect<UCString> def;

 // Predefined macro __SOLARIS__ indicates that the file is being translated
 // by IRIDIUM module, not C++ compiler (can be used if the file is consumed
 // by both IRIDIUM and C++ translators).
 def.push_back( A2U("__SOLARIS__").c_str() );

 #if defined SOLARIX_PRO
 def.push_back( A2U("__PRO__").c_str() );
 #endif

 #if defined SOLARIX_PREMIUM
 def.push_back( A2U("__PREMIUM__").c_str() );
 #endif

 #if !defined SOLARIX_PRO
 def.push_back( A2U("__LITE__").c_str() );
 #endif

 // Разобьем строку defines, содержащую задания макросов, на отдельные
 // элементы. Считаем, что элементы разделены символами ';'. Каждый элемент
 // становится именем макроса-флага. Если defines==NULL, то пропускаем
 // разборку.

 if( !!(defines) )
  {
   int i=0;
   while( !!defines[i] )
    {
     UCString to_add;
     if( defines[i]!=L';' )
      while( !!defines[i] && defines[i]!=L';' )
       to_add += defines[i++];
     else
      i++;

     def.push_back( to_add );
    }
  }

 try
  {
   LoadTxt( txt, def, options, cp, root_dir );
  }
 catch( E_ParserError &x )
  {
   GetIO().merr().printf( "Error detected during dictionary compilation\n" );
   if( !*x.what() )
    GetIO().merr().printf( "%us\n", x.what() );

   throw(x);
  }

 return;
}
#endif


#if defined SOL_CAA
/*********************************************************************
 Делаем попытку спроецировать на Лексикон лексему Word, и возвращаем
 через указатель nproj число удачных проекций. Это проста
 сервисная процедура, введённая в API только для переноса части
 кода модуля Argon внутрь Системы. Вряд ли она пригодится для других
 программ.
**********************************************************************/
void Dictionary::LA_Project_Lexem(
                                  const wchar_t *Word,
                                  int id_language,
                                  int &nproj
                                 )
{
 nproj=0;

 Lexem sl(Word);
 GetLexAuto().TranslateLexem( sl, true );

 RC_Lexem ml( &sl, null_deleter() );

 MCollect<Word_Coord> res;
 MCollect<ProjScore> val_list;
 PtrCollect<LA_ProjectInfo> inf_list;

 GetLexAuto().ProjectWord( ml, res, val_list, inf_list, LexicalAutomat/*::DynformsMode*/::Wordforms, 0, UNKNOWN, NULL );

 nproj = CastSizeToInt(res.size());

 if( res.empty() )
  {
   GetLexAuto().ProjectUnknown( ml, Word, res, val_list, inf_list, id_language, false );
   nproj = CastSizeToInt(res.size());
  }

 return;
}
#endif

#if defined SOL_CAA && !defined SOL_NO_AA
/*
bool Dictionary::VA_Voiced_Lexem( const wchar_t *Word )
{
 bool res=false;

 try
  {
   Lexem res_lex(Word);
   GetLexAuto().TranslateLexem( res_lex, true );
   res = GetSpeakAuto().HasSoundImage(res_lex);
  }
 catch(...)
  {
  }

 return res;
}
*/
#endif

#if defined SOL_CAA && !defined SOL_NO_AA
/*****************************************************************************

 DESCRIPTION: Просим Ядро построить звуковой образ для слова word как можно
              быстрее, возможно - в обход ожидающей обработки информации.
              Если всё пройдёт нормально, то после завершения этой процедуры
              можно вызывать sol_get_phrase_and_sound, извлечь из очереди
              Голосового Автомата бинарные записи со звукообразами и посылать
              звук на воспроизведение обычным путём (см. примеры программы из
              Пакета).

              Данная процедура также может предпринять меры для построени
              звукообраза целого предложения. Если быстрый просмотр символов
              word показывает, что среди них содержаться пробелы или
              пунктуаторы, то будет запущена более сложная и трудоёмка
              процедура.

 SIDE EFFECTS: Так как задействуются все части Вербального Конвейера, то
               будут обновляться все кэшы в разных Автоматах, а это означает,
               что по выходе из процедуры объем потребленной памяти будет
               больше, чем до вызова. Удаление мусора в памяти выполняется по
               инициативе вызывающей программы, через API CALL sol_squeeze.

*****************************************************************************/
/*
void Dictionary::Pronounce( const wchar_t *word )
{
 LEM_CHECKIT_Z(word!=NULL);

 // Анализируем строку word на предмет наличия в ней пробелов
 // или пунктуаторов.
 const int len = lem::lem_strlen(word);
 bool is_sentence=false;

 // Наличие единственного пунктуатора не означает автоматически,
 // что имеем дело с предложением - надо смотреть еще и длину фразы.
 if( len>1 )
  for( int i=0; i<len; i++ )
   if( is_uspace(word[i]) || is_upunct(word[i]) )
    {
     is_sentence = true;
     break;
    }

 if( is_sentence )
  {
   // Да, придется разбивать на лексемы и запускать более сложную
   // процедуру.
   //                               :
   api_pronounce_phrase( word );
   return;
  }

 LexicalAutomat &la = GetLexAuto();

 Lexem sl(word);
 la.TranslateLexem(sl,true);

 RC_Lexem ml( &sl, null_deleter() );

 MCollect<Word_Coord> res;
 MCollect<Real1> val_list;
 lem::PtrCollect<LA_ProjectInfo> prj_extra_inf;

 la.ProjectWord( ml, res, val_list, prj_extra_inf, LexicalAutomat::Wordforms, 0, UNKNOWN, NULL );

 SynGram &sg = GetSynGram();

 const int n = res.size() ? CastSizeToInt(res.size()) : 1;

 // Пытаемся построить звукообраз для одного из вариантов проекции
 // лексемы (список res).
 for( int ie=0; ie<n; ie++ )
  {
   const int entry_key = res.empty() ? UNKNOWN : sg.GetEntry(res[ie].GetEntry()).GetKey();
   const int iform = res.empty() ? UNKNOWN : res[ie].GetForm();

   // Просим Ядро Системы построить звукообраз для слова без заморочек
   // с Time Share Carousel.
   bool built = GetSpeakAuto().BuildSoundForWord(
                                                 word,
                                                 entry_key,
                                                 iform
                                                );

   if(built)
    break;
  }

 return;
}
*/
#endif



// Ключевое поле для обозначения того, что файл создан Системой.
static const char sol_binary_magic_record[]=
 "(c) Elijah Koziev SOLARIX Intellectronix Project www.solarix.ru !15.01.2012!";

/*********************************************************************
 Записываем в бинарный файл (обычно в его заголовок) некоторые поля,
 которые хранят информацию о машинозависимых параметрах. Это позволит
 перед загрузкой информации из бинарного файла проверить возможность
 загрузки.
**********************************************************************/
void Dictionary::Write_Binary_File_Header( lem::Stream &bin ) const
{
 bin.write( sol_binary_magic_record, strlen(sol_binary_magic_record)+1 );

 bin.write_int( CastSizeToInt(sizeof(char)) );
 bin.write_int( CastSizeToInt(sizeof(void*)) );
 bin.write_int( CastSizeToInt(sizeof(long)) );
 bin.write_int( CastSizeToInt(sizeof(int)) );
 bin.write_int( CastSizeToInt(sizeof(wchar_t)) );
 
 // Максимальная вместимость класса CString.
 const lem::int32_t mark3=LEM_CSTRING_LEN;
 bin.write( &mark3, sizeof(mark3) );

 // Признак компиляции Системы с отладочной информацией.
 #if defined DEBUGON
  const lem::int32_t mark4 = 1;
 #else
  const lem::int32_t mark4 = 0;
 #endif
 bin.write( &mark4, sizeof(mark4) );

 // Режим выравнивания полей....
 const lem::int16_t mark5 = static_cast<lem::int16_t>(lem::System_Config::GetAlignmentSize());
 bin.write( &mark5, sizeof(mark5) );

 return;
}


/***************************************************************************
 Проверяем, можем ли мы прочитать бинарный файл без искажений. Предполагаем,
 что до того в бинарный файл была записана служебная информация вызовом
 процедуры sol_write_binary_file_header. Если проверка проваливается и
 аргумент do_stop=true, генерируем исключительную ситуацию. Иначе -
 возвращаем признак успеха проверки.
****************************************************************************/
bool Dictionary::Check_Binary_File_Header(
                                          lem::Stream &bin,
                                          bool do_stop
                                         ) const
{
 char magic_buffer[sizeof(sol_binary_magic_record)+1];
 bin.read( magic_buffer, strlen(sol_binary_magic_record)+1 );

 // -----------------------------------------------------
 // Does the loaded string matches the magic key string?
 // -----------------------------------------------------

  if( !!strcmp(magic_buffer,sol_binary_magic_record) )
  {
   if(do_stop)
    {
     if( lem::LogFile::IsOpen() )
      lem::LogFile::logfile->printf(
                                    "Binary file [%us] has unknown format\n"
                                    , bin.GetName().GetUnicode().c_str()
                                   );

     LEM_STOPIT_A("Dictionary file has unknown or incompatible format");
    }

   return false;
  }

 bool ok=true;

 ok = ok && bin.read_int()==sizeof(char);
 ok = ok && bin.read_int()==sizeof(void*);
 ok = ok && bin.read_int()==sizeof(long);
 ok = ok && bin.read_int()==sizeof(int);
 ok = ok && bin.read_int()==sizeof(wchar_t);

 if( !ok )
  {
   if(do_stop)
    {
     if( lem::LogFile::IsOpen() )
      lem::LogFile::logfile->printf(
                                    "Dictionary file [%us] has been created by incompatible compiler\n"
                                    , bin.GetName().GetUnicode().c_str()
                                   );

     LEM_STOPIT_A("Dictionary file has unknown or incompatible format");
    }

   return false;
  }


 lem::int32_t mark;
 bin.read( &mark, sizeof(mark) );
 if( mark!=LEM_CSTRING_LEN )
  {
   if(do_stop)
    {
     if( lem::LogFile::IsOpen() )
      lem::LogFile::logfile->printf(
                           "Binary file [%us] has been created by incompatible translator\n"
                           , bin.GetName().GetUnicode().c_str()
                          );
     LEM_STOPIT_A("Dictionary file has unknown or incompatible format");
    }

   return false;
  }

 // Проверяем совместимость режима отладки.
 bin.read( &mark, sizeof(mark) );
 #if defined DEBUGON
  lem::int32_t et = 1;
 #else
  lem::int32_t et = 0;
 #endif
 if( mark!=et )
  {
   if(do_stop)
    {
     if( lem::LogFile::IsOpen() )
      lem::LogFile::logfile->printf(
                           "Incompatible debug mode was used by the Translator "
                           "for binary file [%us]\n"
                           , bin.GetName().GetUnicode().c_str()
                          );
     LEM_STOPIT_A("Dictionary file has unknown or incompatible format");
    }

   return false;
  }

 // Проверяем режим выравнивания полей....
 lem::int16_t alig=-1;
 bin.read( &alig, sizeof(alig) );

/*
 if( alig != lem_get_alignment_size() )
  {
   if(do_stop)
    {
     dict.GetIO().merr().printf(
                                "Binary file [%s] - different memory align mode, bin file: %d, current: %d\n"
                                , binfile.GetName().string(), alig, lem_get_alignment_size()
                               );
//     LEM_STOPIT;
    }

   return false;
  }
*/

 return true;
}

/*
#if defined SOL_CAA && !defined SOL_NO_AA
// Исполнение приказа - аргумент является запросом
// к Пролог-машине, поэтому должен заканчиваться символом !
void Dictionary::Execute_Command( const UFString &command )
{
 GetPrologAuto().Process_Predicate( command );
 GetPrologAuto().Allow_Yes_No();
 return;
}
#endif
*/

void Dictionary::CreateEmptySeeker(void)
{
 if( !seeker )
  seeker = boost::shared_ptr<Solarix::LD_Seeker>( new Solarix::LD_Seeker() );
}



#if defined SOL_CAA
// *************************************************************
// Если возможно, усекает аргумент до псевдокорня. Возвращает
// true, если усечение выполнено.
// *************************************************************
bool Dictionary::Stem( UCString &word ) const
{
 if( !!affix_table )
  {
   lem::MCollect<UCString> roots;
   lem::MCollect<float> roots_val;
 
   affix_table->GenerateRoots( word, 0.0, roots, roots_val );

   if( !roots.empty() )
    {
     // Вообще говоря, тут есть выбор - возвращать самый длинный корень или самый короткий.
     int best_len=roots.front().length();
     int ibest=UNKNOWN;

     for( lem::Container::size_type j=1; j<roots.size(); j++ )
      {
       best_len = std::min( best_len, roots[j].length() );
       ibest = j;
      }
     
     if(ibest!=UNKNOWN )
      {
       word = roots[ibest];
       return true;
      }
    }

   if( !!stemmer )
    {
     // Попробуем использовать загруженный стеммер.
     UCString stem;
     if( stemmer->Stem( word, stem ) )
      { 
       word = stem;
       return true; 
      } 
    }
  }

 return false;
}
#endif



#if defined SOL_CAA && defined SOLARIX_PRO
// Определяет количество найденных 2- и 3-грамм
// Возвращает:
//  n2 - кол-во отображений 2-грамм
//  n3 - кол-во отображений 3-грамм
//  unmatched_2_ngrams - кол-во слов, которые не попали ни на одну N-грамму

void Dictionary::MatchNGrams( const lem::MCollect<lem::UCString> &words, int * unmatched_2_ngrams, int * n2, int * n3 )
{
 #if !defined SOL_NO_NGRAMS
 lem::MCollect<int /*bool*/> noise; noise.resize(words.size()); noise.Nullify();
 lem::MCollect<int /*bool*/> match; match.resize(words.size()); match.Nullify();

 std::set<UCString> delims;

 const wchar_t* s[]={
 L".", L",", L";", L":", L"-", L"+", L"=", L"!", L"?", L"$", L"%",
 L"^", L"*", L"(", L")", L"[", L"]", L"<", L">", L"{", L"}", L"\'",
 L"\"",
 #if defined LEM_WINDOWS && !defined LEM_QT
 L"И", L"ИЛИ", L"НО", L"НЕ", L"ДА",
 #endif
 L"AND", L"OR", L"NOT", L"BOTH", L"EITHER", L"NEITHER", L"NOR",
 NULL
 };   

 int j=0;
 while(s[j]!=NULL)
  delims.insert( UCString(s[j++]) );

 for( lem::Container::size_type i=0; i<words.size(); ++i )
  if( delims.find(words[i])!=delims.end() )
   noise[i]=true;

 // Теперь ищем 2-граммы
 if( GetNgrams().NotNull() && !words.empty() )
  {
   Ngrams *ng = &*GetNgrams();
   int iw=0;
   float w=0; 

   for( lem::Container::size_type i=0; i<words.size()-1; ++i )
    {
     if( noise[i]==false && noise[i+1]==false )
      {
       const UCString &left = words[i];
       const UCString &right = words[i+1];

       iw=0;
       w=0.F; 

       if( ng->FindRawNGrams( left, right, w, iw ) )
        {
         if(n2!=NULL)
          (*n2) += iw;

         match[i]   = true;
         match[i+1] = true;
        }
       else
        {
         match[i]   = false;
         match[i+1] = false;
         if( unmatched_2_ngrams!=NULL )
          (*unmatched_2_ngrams)++;
        } 

       if( words.size()>2 && i<words.size()-2 )
        {
         const UCString &right2 = words[i+2];

         if( ng->FindRawNGrams( left, right, right2, w, iw ) )
          {
           if(n3!=NULL)
            (*n3) += iw;
          }
        } 
      }
    }
  }

 #endif

 return; 
}
#endif



Solarix::Dictionary::Version::Version( const lem::UFString &serialized )
{
 if( !lem::to_int( serialized.c_str(), &code, 10 ) )
  throw E_BaseException( L"Incorrect Dictionary::Version code string" );

 return;
}


lem::UFString Solarix::Dictionary::Version::serialize(void) const
{
 return lem::UFString(lem::to_str(code).c_str());
}


lem::CString Solarix::Dictionary::Version::string(void) const
{ return lem::to_str(code); }


#if defined SOL_CAA && !defined SOL_NO_AA
bool Dictionary::UseTokenizerEngineAsSyntan( int id_language )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker( const_cast<lem::Process::CriticalSection*>(&cs_UseTokenizerEngineAsSyntan) );
 #endif

 std::map<int,bool>::const_iterator it = UseTokenizerEngineAsSyntan_List.find(id_language);
 if( it!=UseTokenizerEngineAsSyntan_List.end() )
  {
   return it->second;
  }

 if( id_language!=UNKNOWN )
  {
   bool f=false;

   const SG_Language &lang = GetSynGram().languages()[id_language];
   const int iparam1 = lang.FindParam( L"SegmentationEngine" );
   const int iparam2 = lang.FindParam( L"SyntaxEngine" );

   if( iparam1!=UNKNOWN && iparam2!=UNKNOWN )
    {
     if( lang.GetParam(iparam1).GetValue().eqi( lang.GetParam(iparam2).GetValue() ) )
      {
       f = true;
      }
    }

   UseTokenizerEngineAsSyntan_List.insert( std::make_pair(id_language,f) );
  }

 return false;
}
#endif


#if defined SOL_CAA && !defined SOL_NO_AA
// *************************************************************************
// Возвращается объект, выполняющий сегментацию текста на указанном языке.
// *************************************************************************
lem::Ptr<SentenceTokenizer> Dictionary::GetSentenceTokenizer( int language )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard lock(cs_tokenizer);
 #endif

 // Среди уже созданных токенизаторов попытаемся найти для заданного языка.
 // Само собой, это подразумевает отсутствие состояния у токенизатора, так
 // один объект может обслуживать одновременно несколько потоков.
 std::map<int,Solarix::SentenceTokenizer*> & mutable_sentence_tokenizers =
  const_cast< std::map<int,Solarix::SentenceTokenizer*>& >(sentence_tokenizers);

 lem::PtrCollect<Solarix::SentenceTokenizer> & mutable_tokenizers_ptr =
  const_cast< lem::PtrCollect<Solarix::SentenceTokenizer>& >(tokenizers_ptr);

 std::map< int, SentenceTokenizer* >::iterator it = mutable_sentence_tokenizers.find(language);
 if( it==sentence_tokenizers.end() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(lock);
   #endif
 
   // Будем создавать токенизатор.
   it = mutable_sentence_tokenizers.find(language);
   if( it==sentence_tokenizers.end() )
    {
     // Посмотрим особые метки в описании языка.
     UCString segmentation_flag;
     UCString segmentation_engine;
  
     if( language!=UNKNOWN )
      {
       int iparam = GetSynGram().languages()[language].FindParam( L"segmentation" );
       if( iparam!=UNKNOWN )
        {
         segmentation_flag = GetSynGram().languages()[language].params[iparam]->values.front().c_str();
        } 
  
       iparam = GetSynGram().languages()[language].FindParam( L"segmentationengine" );
       if( iparam!=UNKNOWN )
        {
         segmentation_engine = GetSynGram().languages()[language].params[iparam]->values.front().c_str();
        } 
      }
  
     if( segmentation_flag.empty() || segmentation_flag==L"whitespace" )
      {
       // По умолчанию или при явном указании флага whitespace токенизация
       // выполняется по правилам для главных европейских языков - с разбивкой
       // по пробелам (и другим хинтам).
       EuroSentenceTokenizer * sentence_tokenizer = new EuroSentenceTokenizer(*this,language);
       mutable_tokenizers_ptr.push_back(sentence_tokenizer);
       mutable_sentence_tokenizers.insert( std::make_pair( language, sentence_tokenizer ) );
  
       lem::MCollect<int> id_langs;
       if( language==UNKNOWN || language==ANY_STATE )
        {
         lem::Ptr<LanguageEnumerator> lang_enumerator( GetSynGram().languages().Enumerate() );
         while( lang_enumerator->Fetch() )
          {
           const int id = lang_enumerator->GetId();
           id_langs.push_back(id);
          }
         id_langs.push_back( UNKNOWN );
        }
       else
        {
         id_langs.push_back( language );
         id_langs.push_back( UNKNOWN );
        }
  
       for( lem::Container::size_type i=0; i<id_langs.size(); ++i )
        {
         const int id_lang = id_langs[i];
         lem::Ptr<LS_ResultSet> rs( GetSynGram().GetStorage().ListUnbreakableRules(id_lang) );
         while( rs->Fetch() )
          {
           const int id_rule = rs->GetInt(0);
           lem::Ptr<LA_UnbreakableRule> r( GetSynGram().GetStorage().GetUnbreakableRule(id_rule) );
  
           if( r->IsRegex() )
            {
             sentence_tokenizer->AddRxPattern(r->GetPattern(),*this);
            }
           else
            {
             sentence_tokenizer->AddSimplePattern(r->GetPattern(),*this);
            }
          }
        }
  
       sentence_tokenizer->InitSpecialCases(); 
       return lem::Ptr<Solarix::SentenceTokenizer>(sentence_tokenizer,null_deleter());
      }
     else if( segmentation_flag==L"external" )
      {
       // Ищем параметры для загрузки внешнего модуля
       const SegmenterEngineInfo* info = FindSegmenterInfo(segmentation_engine.c_str());
  
       if( info==NULL )
        {
         lem::MemFormatter mem;
         mem.printf( "Can not find information for segmentation engine [%us]", segmentation_engine.c_str() );
         throw lem::E_BaseException(mem.string());
        }
  
       lem::Path dll_path = info->GetFullPath(segmentation_engine.c_str());
  
       ExternalTokenizer * sentence_tokenizer = new ExternalTokenizer( dll_path, info->data_path, info->params, *this, language );
       mutable_tokenizers_ptr.push_back(sentence_tokenizer);
       mutable_sentence_tokenizers.insert( std::make_pair( language, sentence_tokenizer ) );
       return lem::Ptr<Solarix::SentenceTokenizer>(sentence_tokenizer,null_deleter());
      }
     else if( segmentation_flag==L"dictionary_lookup" )
      {
       // Сегментация для языков, где нет пробелов и других знаков пунктуации (китайский, японский).
       SegmentingSentenceTokenizer * sentence_tokenizer = new SegmentingSentenceTokenizer(*this,language);
       mutable_tokenizers_ptr.push_back(sentence_tokenizer);
       mutable_sentence_tokenizers.insert( std::make_pair( language, sentence_tokenizer ) );
       return lem::Ptr<Solarix::SentenceTokenizer>(sentence_tokenizer,null_deleter());
      }
     else
      {
       LEM_STOPIT;
      }
    }
   else
    {
     return lem::Ptr<Solarix::SentenceTokenizer>(it->second,null_deleter());
    }
  }

 return lem::Ptr<Solarix::SentenceTokenizer>(it->second,null_deleter());
}
#endif


int Dictionary::GetLanguages( lem::MCollect<int> &langs ) 
{
 SynGram &sg = GetSynGram();

 sg.GetLanguageUsage().GetLanguages(langs);
 int res = sg.GetLanguageUsage().GetDefaultInputLanguage();

 return res;
}


int Dictionary::GetDefaultLanguage(void)
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker(&cs_lang);
 #endif

 if( DefaultLanguageID==-2 )
  {
   SynGram &sg = GetSynGram();
   DefaultLanguageID = sg.GetLanguageUsage().GetDefaultInputLanguage();
  }

 return DefaultLanguageID;
}


void Dictionary::SetDefaultLanguage( int id )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker(&cs_lang);
 #endif
 DefaultLanguageID = id;
 return;
}

bool Dictionary::IsPrefixEntrySearcherAvailable(void) const
{
 return !prefix_entry_searcher_connection_string.empty();// || !prefix_entry_searcher_provider.empty();
}


lem::Ptr<PrefixEntrySearcher> Dictionary::GetPrefixEntrySearcher( int max_found_entries )
{
 if( !prefix_entry_searcher_connection_string.empty() )
  {
   #if defined LEM_THREADS
   lem::Process::RWU_ReaderGuard rlock(cs_prefix_entry_searcher);
   #endif

   if( prefix_entry_searcher.IsNull() )
    {
     #if defined LEM_THREADS
     lem::Process::RWU_WriterGuard wlock(rlock);
     #endif

     if( prefix_entry_searcher.IsNull() )
      {
       Charpos2EntryStorage *stg = NULL;

       if( prefix_entry_searcher_provider.eqi(L"mysql") )
        {
         #if defined SOL_MYSQL_DICTIONARY_STORAGE
         StorageConnection *cnx = storage->Connect( prefix_entry_searcher_provider, prefix_entry_searcher_connection_string );
         stg = new Charpos2EntryStorage_MySQL( (StorageConnection_MySQL*)cnx );
         #endif 
        }
       else
        {
         stg = new Charpos2EntryStorage_SQLITE( prefix_entry_searcher_connection_string );
        }
  
       if( storage==NULL )
        {
         lem::MemFormatter mem;
         mem.printf( "Can not load prefix entry searcher, provider=%us", prefix_entry_searcher_provider.c_str() );
         throw lem::E_BaseException( mem.string() );
        }
  
       prefix_entry_searcher = new PrefixEntrySearcher( stg, max_found_entries );
      }
    }
  }

 return prefix_entry_searcher;
}



bool SegmenterEngineInfo::Match( const lem::UFString &segm_name ) const
{
 if( name==L'*' || name.empty() )
  return true;

 return name.eqi(segm_name);
}


lem::Path SegmenterEngineInfo::GetFullPath( const lem::UFString &segm_name ) const
{
 lem::Path p( library_path );

 if( dll_name.empty() )
  p.ConcateLeaf(segm_name);
 else
  p.ConcateLeaf(dll_name);

 return p;
}

const SegmenterEngineInfo* Dictionary::FindSegmenterInfo( const lem::UFString &name ) const
{
 for( lem::Container::size_type i=0; i<segmenters_info.size(); ++i )
  if( segmenters_info[i]->Match(name) )
   return segmenters_info[i];

 return NULL; 
}


bool Dictionary::IsNgramsAvailable(void) const
{
 #if !defined SOL_NO_NGRAMS
 return ngrams.NotNull() && ngrams->IsAvailable();
 #else
 return false;
 #endif
}



#if defined SOL_CAA
TextTokenizationRules * Dictionary::GetTokenizationRules( const lem::MCollect<int> & id_languages )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_tokenization_rules);
 #endif

 for( lem::Container::size_type i=0; i<tokenization_rules.size(); ++i )
  if( tokenization_rules[i]->id_language==id_languages )
   return tokenization_rules[i];

 #if defined LEM_THREADS
 lem::Process::RWU_WriterGuard wlock(rlock);
 #endif

 for( lem::Container::size_type i=0; i<tokenization_rules.size(); ++i )
  if( tokenization_rules[i]->id_language==id_languages )
   return tokenization_rules[i];

 lem::Ptr<SentenceTokenizer> tokenizer = GetSentenceTokenizer( id_languages.front() );

 TextTokenizationRules * rules = new TextTokenizationRules(id_languages,tokenizer.get());

 // заполняем поля rules правилами для указанных языков.

 for( lem::Container::size_type i=0; i<id_languages.size(); ++i )
  {
   const SG_Language & lang = GetSynGram().languages()[id_languages[i]];
   int iparam = lang.FindParam(L"Segmentation");
   if( iparam!=UNKNOWN )
    {
     const lem::UFString & p = lang.GetParam(iparam).GetValue();

     if( p.eqi(L"whitespace") )
      {
       // Пробелы являются естественными границами слов
       rules->segmentation_flag = TextTokenizationRules::Whitespace;
       rules->AddSpaceCharacters( TextTokenizationRules::DefaultSpaceChars );
      }
     else if( p.eqi(L"dictionary_lookup") )
      {
       // Беспробельный текст, границы слов выделяются на основе просмотра лексем
       rules->segmentation_flag = TextTokenizationRules::Streaming;

       // нам понадобится поиск по префиксам слов.
       if( !IsPrefixEntrySearcherAvailable() )
        throw lem::E_BaseException( "Prefix entry lookup table is not available" );

       rules->prefix_lookup = GetPrefixEntrySearcher();
      }
     else if( p.eqi(L"external") )
      {
       // Внешний токенизатор.
       rules->segmentation_flag = TextTokenizationRules::External;
      }
     else
      {
       lem::MemFormatter msg;
       msg.printf( "Unknown segmentation type [%us] for language '%us' id=%d", p.c_str(), lang.GetName().c_str(), id_languages[i] );
       throw lem::E_BaseException( msg.string() );
      }
    }
   else
    {
     lem::MemFormatter msg;
     msg.printf( "Language '%us' id=%d does not have property 'segmentation'", lang.GetName().c_str(), id_languages[i] );
     throw lem::E_BaseException( msg.string() );
    }

   iparam = lang.FindParam(L"WordBrokers");
   if( iparam!=UNKNOWN )
    {
     const lem::UFString & delimiters = lang.GetParam(iparam).GetValue();
     rules->AddDelimiterCharacters(delimiters.c_str());     
    }
  }


 tokenization_rules.push_back(rules);

 return rules;
}
#endif






#if defined SOL_USE_SPEAKER
Speaker* Dictionary::GetSpeaker()
{
 if( speaker.NotNull() )
  return speaker.get();

 lem::Xml::Parser p;
 p.Load(dictionary_xml);

 lem::Path data_folder(xml_base_path);
 
 const lem::Xml::Node* xml_speaker = p.Find_By_Path( L"dataroot.speaker" );
 if( xml_speaker!=NULL )
  {
   data_folder = xml_base_path;
   data_folder.ConcateLeaf( lem::Path( xml_speaker->GetNode(L"folder")->GetBody() ) );
   data_folder = data_folder.GetAbsolutePath();
  }

 speaker = new Speaker_eSpeak(this,data_folder);

 return speaker.get();
}
#endif
