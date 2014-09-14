#ifndef LEM_SEARCH_ENGINE__H
#define LEM_SEARCH_ENGINE__H
#pragma once

// ----------------------------------------------------------------------------
// File SEARCH_ENGINE.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// Content:
// SEARCH ENGINE Core
//
// Структуры для работы поисковых машин.
//
// Crawler - file iterator class (and supporting classes): it recurses
// directories, subdirectories, archives and other file sources, executing
// virtual methods for each file being found.
//
// 28.09.2007 - небольшие правки для компилируемости в MSVC 6.0
// 04.10.2007 - HTTPD компилируется только в версии Premium
// 29.06.2008 - введена поддержка менеджера тэгов для документов
// 06.07.2008 - введена поддержка плагинов Media Info
// ----------------------------------------------------------------------------
//
// CD->09.12.2004
// LC->09.05.2011
// --------------

 #include <lem/config.h>

 #if !defined LEM_WINDOWS && !defined LEM_UNIX
  #include <boost/filesystem/path.hpp>
 #endif

 #if defined FAIND_SIGNALS
 #include <boost/signal.hpp>
 #endif

 #include <lem/ptr_container.h>

 #if defined FAIND_WEB
  #if defined LEM_MFC
   #include <afxwin.h>
  #else 
   #include <windows.h>
  #endif
  #include <wininet.h>
  #include <lem/url.h>
 #endif
 
 #if defined FAIND_SQL
 #include <lem/db.h>
 #include <lem/io_db_stream.h>
 #endif 
 
 #include <lem/ufstring.h>
 #include <lem/zeroed.h>
 #include <lem/cfg_parser.h>
 #include <lem/smart_pointers.h>
 #include <lem/date_time.h>
 #include <lem/math/random.h>
 #include <lem/runtime_checks.h>
 #include <lem/console_application.h>
 #include <lem/logfile.h>

 #include <lem/solarix/file_location.h>
 #include <lem/solarix/se_indexer.h>
 #include <lem/solarix/file_factory.h>



 #include <lem/solarix/se_echo_options.h>
 #include <lem/solarix/se_general_options.h>
 #include <lem/solarix/se_dataset_printer.h>

 #include <lem/solarix/se_context_options.h>
 #include <lem/solarix/se_report.h>

 #include <lem/solarix/se_scan_options.h>
 #include <lem/solarix/se_action_options.h>
 #include <lem/solarix/se_lexer_options.h>
 #include <lem/solarix/search_engine_callbacks.h>

 #include <lem/solarix/se_crawler_operation.h>
 #include <lem/solarix/se_plugin_options.h>
 #include <lem/solarix/se_doc_preprocessor.h>

// #include <lem/solarix/ngrams_collector.h>
 #include <lem/solarix/DocumentTagsCache.h>
 #include <lem/solarix/MediaInfoManager.h>
 #include <lem/solarix/search_engine_query_params.h>
 #include <lem/solarix/se_itag_stream.h>

 #if defined FAIND_IENGINES
 #include <lem/solarix/faind_internal.h>
 #include <lem/solarix/igrammar_engine.h>
 #endif

 #if defined FAIND_HTTPD
  #include <lem/solarix/se_httpd.h>
 #endif

 namespace lem
 {
  namespace Pack
  {
   class IUnpackerFactory;
  }
 }

 namespace Solarix
 {
  namespace Search_Engine
  { 
   using lem::UFString;
   using lem::FString;
   using lem::Collect;
   using lem::Stream;

   class Text;
   class RSE_Table; 
  
  // **************************************
  // Описатель найденной темы документа.
  // **************************************
  class Doc_Topic : public Solarix::Search_Engine::ITagStream
  {
   private:
    lem::PtrCollect< std::pair<UFString /*param*/, UFString /*value*/ > > params;

   public:
    Doc_Topic(void);
    virtual ~Doc_Topic(void) {}

    RSE_Table* GetTable(void) const;

    void LoadBin( lem::Stream &bin );
    void SaveBin( lem::Stream &bin ) const;

    virtual void WriteTag( const UFString &Param, const UFString &Value );

    void Print( OFormatter &dst ) const;

    virtual lem::UFString GetDrawerStr(void) const;
  }; 




  using Solarix::Search_Engine::File_Location;
  using Solarix::Search_Engine::Base_File_Reader;
  using Solarix::Search_Engine::Pattern;
  using Solarix::Search_Engine::Query;
  using Solarix::Search_Engine::Fix_Context;
  using Solarix::Search_Engine::Context_Options;


  extern const UFString filemask_to_regex( const UFString &x );

  #if defined FAIND_PLUGINS
  // ************************************************ 
  // Парсер файлов, загружаемый как плагин (из DLL).
  // ************************************************ 
  class Unpacker_Plugin
  {
   protected:
    lem::Process::Dll hLib;
    lem::Path dllpath;
    void *PluginThis;
  
    friend class Plugin_Archive;

    lem::Collect<UFString> ext_list;

    typedef const wchar_t*(*get_property_func)( void *This, int iProperty, int iSubproperty );
    typedef bool (*set_property_func)( void *This, int iProperty, int iSubproperty, const wchar_t *Value );
    typedef void*(*start_extraction_func)( void *This, const wchar_t *ArchiveName, const PluginOptions *Options );
    typedef const wchar_t*(*extract_next_filename_func)( void *This, void *Context );
    typedef const wchar_t*(*unpack_file_func)( void *This, void *Context, const wchar_t *Filename );
    typedef void(*extraction_complete_func)( void *This, void *Context );
    typedef void*(*constructor_func)(void);
    typedef void(*destructor_func)( void *This );

    constructor_func constructor_ptr;
    destructor_func destructor_ptr;
 
    get_property_func get_property_ptr;
    set_property_func set_property_ptr;

    start_extraction_func start_extraction_ptr;
    extract_next_filename_func extract_next_filename_ptr; 
    unpack_file_func unpack_file_ptr;
    extraction_complete_func extraction_complete_ptr;

    void Clear(void);

   public:
    Unpacker_Plugin(void);
    ~Unpacker_Plugin(void);

    bool Load( const lem::Path &filename );

    virtual const wchar_t* GetDescription(void) const { return get_property_ptr(PluginThis,1,0); }
    inline const lem::Path& GetPath(void) const { return dllpath; }

    inline const lem::Collect<UFString>& ListExtensions(void) const { return ext_list; }
  };
  #else
  typedef void* Unpacker_Plugin;
  #endif





  // Класс для нечеткого сравнения лексем.
  class Fuzzy_Comparator;

  class Query_Root;

  #if defined FAIND_PLUGINS
  // ****************************************************
  // Плагин для доступа к внешним поисковикам,
  // препроцессорам запросов, активным сценариям поиска.
  // ****************************************************
  class Engine_Plugin
  {
   protected:
    typedef enum { SearcherEngine, SimpleSearcherEngine, QueryRewriterEngine, ActiveScriptEngine } PluginSubtype;
    PluginSubtype plugin_subtype;
    lem::UFString name; // условное имя плагина - определяется самим плагином

   private:
    lem::Process::Dll hLib;
    void *PluginThis;
    lem::Path dllpath;

    typedef void*(*constructor_func)(void);
    typedef void(*destructor_func)( void *This );
    typedef const wchar_t*(*get_property_func)( void *This, int iProperty, int iSubproperty );
    typedef bool (*set_property_func)( void *This, int iProperty, int iSubproperty, const wchar_t *Value );
    typedef int(*support_morphology_func)( void *This );
    typedef void*(*search_func)( void *This, void *IIndexManagerPtr, void *IGrammarEnginePtr, const wchar_t *Query, const wchar_t *Params );
    typedef int(*fetch_func)(
                             void *This,
                             void *Results,
                             wchar_t *Title, int TitleSize,
                             wchar_t *Filename, int FilenameSize,
                             wchar_t *Snippet, int SnippetSize,
                             char *SnippetHtml, int SnippetHtmlSize,
                             char *CacheUrl, int CacheUrlSize,
                             double *Rank
                            );
    typedef void(*search_complete_func)( void *This, void *Results );
    typedef int(*get_error_func)( void *This );

    typedef bool (*rewrite_query_func)( void *This, void *ISearchEnginePtr, void *IGrammarEnginePtr, void *QueryDataPtr );
    typedef bool (*simple_search_func)(
                                       void *This,
                                       void *ISearchEnginePtr,
                                       void *IGrammarEnginePtr,
                                       const void *QueryDataPtr,
                                       wchar_t **Result,
                                       int *ResultFormat
                                      );

    typedef void(*free_func)( void *This, void *Ptr );

  
    constructor_func constructor_ptr;
    destructor_func destructor_ptr;
    get_property_func get_property_ptr;
    set_property_func set_property_ptr;
    support_morphology_func support_morphology_ptr;
    search_func search_ptr;
    fetch_func fetch_ptr; 
    get_error_func get_error_ptr;
    search_complete_func search_complete_ptr;
    rewrite_query_func rewrite_query_ptr;
    simple_search_func simple_search_ptr;
    free_func free_ptr; 

    void Free( void *ptr );

   public:
    Engine_Plugin(void);
    virtual ~Engine_Plugin(void);

    inline const UFString& GetName(void) const { return name; }
    virtual const wchar_t* GetDescription(void) const { return get_property_ptr(PluginThis,1,0); }
    inline const lem::Path GetPath(void) const { return dllpath; }

    virtual bool Load( const lem::Path &filename );

    virtual bool IsSearcher(void) const { return plugin_subtype==SearcherEngine; }
    virtual bool IsSimpleSearcher(void) const { return plugin_subtype==SimpleSearcherEngine; }
    virtual bool IsQueryRewriter(void) const { return plugin_subtype==QueryRewriterEngine; } 
    virtual bool IsActiveScriptor(void) const { return plugin_subtype==ActiveScriptEngine; } 

    // Базовый вариант поиск для плагина типа SearcherEngine - получив запрос, плагин
    // выполняет поиск и возвращает список результатов.
    virtual void Search( const Query_Root *q, const UFString &params, Crawler *engine );

    virtual bool RewriteQuery( UFString &pattern, Scan_Options &scanning, Search_Options &flags, Crawler *engine );

    // Вариант поиска для SimpleSearcherEngine - плагин возвращает единственную строку
    // результата в одном из поддерживаемых форматов, которая и отображается.
    virtual bool SimpleSearch( const Query_Root *q, UFString &result, UFString &format, Crawler *engine );
  };
  #endif



  // ***************************************
  // Базовый класс для исполнителей команд.
  // ***************************************
  class CmdExecutor
  {
   public:
    UFString message; // информационное сообщение о выполнении команды
    lem::Collect<UFString> cmd_args; // все опции командной строки, для которых собран исполнитель
    lem::Ptr<Crawler> crawler; // краулер, который будет выполнять поиск/индексирование

    static int count; // DEBUGGING: count of alive (created but not deleted) objects.

   public:
    CmdExecutor(void);
    CmdExecutor( lem::Ptr<Crawler> ptr );

    virtual ~CmdExecutor(void);

    // Выполнение команды
    virtual bool Do(void);

    // Прерываем выполнение поиска или индексирования.
    virtual void Abort( bool terminate_thread );

    // Печать результатов, если таковые есть
    virtual void PrintResults( lem::OFormatter &out );
  };

 

  class Topic_Finder;
  // ******************************************************
  // Класс с парсером команд для движка.
  // ******************************************************
  class CommandParser : public lem::Base_Application
  {
   public:
    // Загруженные из ini-файла опции по умолчанию.

    SQLConnection sql; // подключение к SQL backend, если оно используется
    lem::Ptr<Crawler_Operation> ini_engine_command;
    lem::Ptr<General_Options> generals;

    #if defined FAIND_INDEXER
    // Центр управления индексаторами
    lem::Ptr<IndexManager> index_manager;
    #endif

    // Эталонный краулер, из которого клонируются краулеры для
    // поиска в тредах.
    lem::Ptr<Crawler> template_crawler;

    #if defined FAIND_HTTPD
    // Работающий HTTP-сервер для внешних запросов
    std::auto_ptr<FaindHttpServer> httpd;
    #endif

   protected:
    virtual void CreateTemplateCrawler(void);
    virtual void TryRead( lem::Cfg_Parser::Ini_Parser &ini );
    void SetLogFile( lem::Ptr<OFormatter> file );
    OFormatter& GetLogFile(void);
    inline bool IsLogging(void) { return lem::LogFile::IsOpen(); }

    virtual bool OpenLogFile( const lem::Path &logfilename );
    virtual void CloseLogFile(void);

    virtual void SetLanguages( const FString &langs );

    // Выполняем все необходимые подстановки типа %app_dir%в файловом пути p
    virtual void SubstPathMacros( UFString &p ) const;

    // Проверяет, что i указывает на после-последнего аргумента в командной
    // строке args. Используется при парсинге запросов для проверки
    // корректности некоторых команд.
    void MustBeLastArgument(  const Collect<UFString> &args, int i ) const;

    #if defined SOLARIX_PREMIUM && defined FAIND_THREADS
    lem::Process::Thread *httpThread;
    static void RunHttpServer( const char *Ip, int Port, CommandParser &engine );
    static void RunHttpServerThread_( void *Args );
    #endif

   private:
    virtual void ReadResponse( UFString &x ) const;
    Base_File_Filter::CondType GetFilterCondition(
                                                  const UFString &arg,
                                                  UFString& param
                                                 ) const;

    virtual void ParsePattern(
                              UFString &q_name,
                              UFString &what,
                              Crawler_Operation &operation
                             ) const;

    virtual CmdExecutor* ParseSqlSelect( const UFString &sql, const QueryParams &params ) const;
    virtual CmdExecutor* ParseSqlDrop( const UFString &sql, const QueryParams &params ) const;
    virtual CmdExecutor* ParseSqlDelete( const UFString &sql, const QueryParams &params ) const;
    virtual CmdExecutor* ParseSqlUpdate( const UFString &sql, const QueryParams &params ) const;

    virtual void BeforeParsingCommand( const lem::Collect<UFString> &args, Crawler_Operation& engine_command ) const;
    virtual void AddQuery( Crawler_Operation &operation, Query_Root *q ) const;

    #if defined LEM_WINDOWS && defined FAIND_WEB
    virtual void LoadProxyConfigFromRegistry(void);
    #endif

   public:
    CommandParser(void);

    virtual ~CommandParser(void);
    
    // Позволяет запомнить фактическое расположение исполнимых модулей
    // и плагинов движка.
    virtual void SetProgramPath( const lem::Path &exepath );

    // Set the lem::Stream formatter to print messages (usually the target
    // device is TTY).
    virtual void SetEcho( lem::Ptr<lem::OFormatter> formatter );

    // Возвращает текущий форматтер для эхо-печати
    virtual lem::OFormatter& GetEcho(void) const;

    // Загружаем локализованные строки для движка
    virtual void LoadResources( const lem::Path &filename );

    // Возвращает ссылку на менеджер локализованных ресурсов
    lem::UI::Resource_List& GetResources(void) const;

    // Пытаемся загрузить конфигурационный файл (ini) и возвращаем true
    // в случае успеха.
    virtual bool LoadConfig( const lem::Path &ini );

    // Строка ucmd разбивается на опции (список new_args)
    virtual void SplitArgs( const UFString &ucmd, lem::Collect<UFString> &new_args ) const;

    // Парсим команду и возвращаем исполнитель.
    virtual CmdExecutor* Parse( const lem::Collect<lem::UFString> &args ) const;
    virtual CmdExecutor* Parse( 
                               const lem::Collect<lem::UFString> &args,
                               const QueryParams &params
                              ) const;
    virtual CmdExecutor* Parse( const lem::UFString &ucmd ) const;
    virtual CmdExecutor* Parse(
                               const lem::UFString &ucmd,
                               const QueryParams &params
                              ) const;

    // Парсит команду в формате SELECT .... и другие SQL-like
    virtual CmdExecutor* ParseSqlQuery( const UFString &sql, const QueryParams &params ) const;

    // Парсим команду и заполняем структуру с тэгами задания.
    virtual void Parse(
                       const lem::Collect<UFString> &args,
                       const QueryParams &params,
                       Crawler_Operation &operation
                      ) const;

    virtual void Parse(
                       const lem::UFString &ucmd,
                       const QueryParams &params,
                       Crawler_Operation &operation
                      ) const;

    // Удобная обертка - парсим команду и исполняем ее.
    virtual void Execute( const lem::Collect<lem::UFString> &args ) const;
    virtual void Execute(
                         const lem::Collect<lem::UFString> &args,
                         const QueryParams &params
                        ) const;

    #if defined FAIND_INDEXER
    virtual IndexManager& GetIndexManager(void);
    virtual const IndexManager& GetIndexManager(void) const;
    #endif

    virtual void LoadDictionary( bool verbose );

    virtual int LoadPlugins(void);

    const Solarix::Dictionary& GetDictionary(void) const;
    const Solarix::LD_Seeker& GetSeeker(void) const;

    Solarix::Dictionary& GetDictionary(void);
    Solarix::LD_Seeker& GetSeeker(void);

    #if defined FAIND_DATAMINE
    virtual void PrepareAutoclassifierDatabaseFiles(void) const;
    virtual Topic_Finder& GetTopicFinder(void);
    #endif

    #if defined SOLARIX_PREMIUM && defined FAIND_THREADS
    void RunHttpServerThread( const char *Ip, int Port );
    void RunHttpServerThread(void);
    #endif

    #if defined SOLARIX_PRO
    virtual DocumentTagsCache& GetDocumentTagsCache(void);
    #endif

    #if defined SOLARIX_PRO
    virtual MediaInfoManager& GetMediaInfoManager(void);
    virtual bool GetMediaInfo(
                              const lem::Path &path,
                              lem::UFString &Short,
                              lem::UFString &Long,
                              lem::UFString &Tags,
                              lem::UFString &Image
                             );
    #endif
  };



  class Topic_Finder;
 
  #if defined FAIND_PLUGINS

  class Lexer_Plugin_Processor;
  class Lexer_Plugin
  {
   private:
    lem::UFString name; // условное имя плагина - определяется самим плагином
    lem::Process::Dll hLib;
    void *PluginThis;
    lem::Path dllpath;

    typedef void*(*constructor_func)(void);
    typedef void(*destructor_func)( void *This );
    typedef const wchar_t*(*get_property_func)( void *This, int iProperty, int iSubproperty );
    typedef wchar_t*(*process_func)( void *This, void *IGrammarEnginePtr, const wchar_t *OriginalText, const wchar_t *Parameters );
    typedef void(*free_func)( void *This, wchar_t *Results );
    typedef int(*get_error_func)( void *This );

    constructor_func constructor_ptr;
    destructor_func destructor_ptr;
    get_property_func get_property_ptr;
    process_func process_ptr;
    get_error_func get_error_ptr;
    free_func free_ptr; 

    void Free( wchar_t *ptr );

   public:
    Lexer_Plugin(void);
    ~Lexer_Plugin(void);

    inline const UFString& GetName(void) const { return name; }
    virtual const wchar_t* GetDescription(void) const { return get_property_ptr(PluginThis,1,0); }
    inline const lem::Path GetPath(void) const { return dllpath; }

    lem::UFString* Process( const wchar_t *org, const wchar_t *params, Crawler *engine );

    bool Load( const lem::Path &filename );
    Doc_Preprocessor* GetLexer( const UFString &arg );
  };


  class Lexer_Plugin_Processor : public Doc_Preprocessor
  {
   private:
    Lexer_Plugin *plugin;
    lem::UFString args; // дополнительные аргументы

   public:
    Lexer_Plugin_Processor( Lexer_Plugin *p, const lem::UFString &a );

    virtual Solarix::Search_Engine::Base_File_Reader* GetReader( Solarix::Search_Engine::Base_File_Reader* src_reader, Crawler *crawler ) const;
  };

  class DocPreprocessorManager
  {
   private:
    lem::PtrCollect<Lexer_Plugin> plugins;

   public:
    DocPreprocessorManager(void);
    ~DocPreprocessorManager(void);

    int LoadPlugins( const lem::Path &folder );
    virtual Doc_Preprocessor* create( const lem::UFString &name, const lem::UFString &arg );
    void ListPlugins( lem::Collect< std::pair<lem::UFString,lem::Path> > &list ) const;
  };
  #endif

  // ************************************************************************
  // Search engine file scanner - it loads data from different sources and
  // scans them for pattern matching.
  // 
  // Базовый класс Поисковой Машины - выполняет все основные функции поиска,
  // исключая ввод запроса и вывод результатов.
  // ************************************************************************
  class Crawler
  {
   friend class CommandParser;

   #if defined FAIND_REPORTS
   friend class Broken_HRef_Report;
   friend class HRef_Report;
   #endif
   public:
    static lem::Process::InterlockedInt do_pause; // для быстрого определения состояния 'приостановить индексирование'
    #if defined LEM_THREADS
    static lem::Process::Event pause_evt;
    #endif

   protected:
    static int id_seq; // для генерации уникальных id.
    static int instance_counter; // для подсчета кол-ва созданных объектов Crawler
   
    #if defined LEM_THREADS
    lem::Process::CriticalSection crit_sec; // для исключения одновременной загрузки словаря и 
                                            // и других модулей в разных потоках.
    #endif

    lem::zeroed<bool> clone; // это клон эталонного объекта для многопоточной среды
    Crawler *master_crawler; // корневой объект, от которого порождаются все клоны

    #if defined FAIND_WEB
    MCollect<UFString*> visited_uri; // список посещенных ссылок, чтобы не зацикливаться
    MCollect< std::pair<UFString/*страница*/,UFString/*ссылка*/>* > broken_uri; // список недоступных ссылок
    #endif
   
    // Загруженные из внешних файлов модули
    lem::Ptr<Dictionary> dictionary;     // грамматическая машина
    lem::Ptr<Fuzzy_Comparator> fuzzy_eq; // Алгоритмы для нечеткого сравнения лексем
    lem::Ptr<LD_Seeker> ld_seeker;

    #if defined FAIND_IENGINES
    // Нормально инициализируется только в шаблонном краулере!
    lem::Ptr<Solarix::Faind_Engine> faind;
    lem::Ptr<IGrammarEngine> IGrammarEnginePtr;
    lem::Ptr<ISearchEngine> ISearchEnginePtr;
    #endif
    virtual void CreateIEngines(void);


    #if defined FAIND_INDEXER
    lem::Ptr<IndexManager> idb;
    #endif

    lem::Ptr<OFormatter> null_dev;

    #if defined FAIND_DATAMINE
    lem::Ptr<Topic_Finder> topic_finder;
    #endif

    #if !defined SOL_NO_AA
    //lem::Ptr<Solarix::Text_Processor> tpu;
    #endif

    #if defined SOLARIX_PRO
    lem::Ptr<DocumentTagsCache> document_tags_cache;
    #endif

    #if defined FAIND_REPORTS
    lem::Ptr<Report_Factory> report_maker;
    virtual void PrepareReportFactory(void); 
    virtual Base_Report* CreateReporter( const UFString &name ) const;
    #endif


    #if defined FAIND_PLUGINS
    // загруженные плагины для обработки внешних движков 
    lem::Ptr< PtrCollect<Engine_Plugin> > engines_plugins; 
    virtual lem::Path GetFiletypePluginsFolder(void) const;
    virtual int LoadEnginePlugins( bool ForceReload=false );
    #endif

    lem::Ptr<File_Type_Detector> file_type_detector;

    lem::Ptr<MediaInfoManager> media_info_manager;

    lem::Ptr<lem::Math::RandU> tmp_filename; // генератор случайных имен файлов для кэша распакованных файлов

    typedef std::map<UFString, std::pair< lem::Ptr<lem::Pack::IUnpackerFactory>, lem::CPtr<Unpacker_Plugin> > > ARC_EXT;
    lem::Ptr<ARC_EXT> arc_ext; // File extensions for all supported archives.
    #if defined FAIND_PLUGINS
    lem::Ptr< lem::PtrCollect<Unpacker_Plugin> > arc_plugins; // список загруженных плагинов-распаковщиков
    #endif 


    #if defined FAIND_PLUGINS
    lem::Ptr<DocPreprocessorManager> doc_preprocessor;
    int LoadLexerPlugins( bool ForceReload=false );
    #endif 

    void ExtractDocDescription( const File_Location & doc_name, Fix_Context & dummy_ctx );


    virtual void DoPresetByIni(void);

    virtual void InitializeModules(void);
    virtual void CreateIndexManager(void);
    virtual void CreateDictionary(void);
    virtual void LoadThesaurus(void);
    virtual void LoadFuzzyComparator(void);
    virtual void LoadStopwords(void);

//    virtual void TestDictionaryNeeded( Query_Root *q );
    virtual void ClearQueryProjections(void);
    virtual void ApplyIndexToQueries( bool second_pass=false );

    virtual void DoScanSteps(void);
    virtual void PrepareToScan(void);
    virtual void ScanDomain(void);

    #if defined FAIND_PLUGINS
    virtual void ProcessEngine( const UFString &engine_name );
    void ProcessEngine( Engine_Plugin *engine, const UFString &params );
    #endif


    virtual void SearchViaIndexOnly(void);

    virtual void AfterScan(void);
 
    // Индексирование файла
    virtual bool IndexFile( const File_Location &filename, Base_File_Reader *reader );

    // Безиндексный поиск паттерна в файле
    virtual bool ContentMatches(
                                const File_Location &filename,
                                Base_File_Reader *reader,
                                MCollect<Fix_Context*> &contexts,
                                const Solarix::Search_Engine::Doc_Info *doc_info 
                               );

    virtual void DoesntMatch(
                             const File_Location &filename,
                             const string &file_format 
                            );

    virtual void PrintContext( const Fix_Context *ctx );
    virtual void DoCommands(
                            const Fix_Context *ctx,
                            const File_Location &filename,
                            const string &file_format 
                           );

    #if defined FAIND_PLUGINS
    virtual void StartProcessingEngine( const UFString &engine );
    #endif

    #if defined FAIND_UNPACK
    virtual void StartProcessingArchive( const File_Location& filename );
    #endif

    #if defined FAIND_WEB 
    virtual void StartProcessingUri( const UFString &adr ); 
    #endif

    #if defined FAIND_NETWORKING 
    virtual void StartProcessingPipe( const UFString &pipename );
    virtual void StartProcessingSocket( const UFString &addr );
    #endif

    #if defined FAIND_WEB 
    virtual void UriIsLoaded( const lem::UFString &adr );  
    #endif


    void ExtractMetainfo( const lem::Path &folder, const lem::Path &filename );

    #if defined LEM_WINDOWS
    // Сканирование дерева каталогов для платформы Windows
    void ScanFoldersWin(void);
    void ProcessFolderWin( 
                          const wchar_t *FolderName,
                          int NameLen,
                          Solarix::Search_Engine::File_Location::LocType loc
                         );
    void ProcessFolderWin(
                          const char *FolderName,
                          int NameLen,
                          Solarix::Search_Engine::File_Location::LocType loc
                         );
    #elif defined LEM_UNIX
    // Сканирование дерева каталогов для Posix-совместимых, 
    // прежде всего - клонов Unix.
    void ScanFoldersPosix(void);
    void ScanFolderPosix( const char* folder_name, bool utf8 );
    #else
    // Прочие платформы - используем крос-платформенную библиотеку.
    void ScanFoldersPortable(void);
    #endif

    #if defined FAIND_UNPACK
    void FreeArchiversResources(void);
    #endif

    #if defined FAIND_WEB
    lem::zeroed<HINTERNET> hInternetSession;

    bool CrawlFtp( const lem::Url &uri_str, int cur_traffic );
    bool ScanFtpFolder(
                       const lem::Url &url,
                       HINTERNET hSession,
                       const wchar_t *folder,
                       int cur_traffic,
                       bool has_stream_filter
                      );
    void DownloadFile( HINTERNET hFile, lem::MemStream &buffer );
    bool ProcessFtpFile(
                        HINTERNET hSession,
                        const lem::Url &url,
                        const lem::UFString &filename,
//                        WIN32_FIND_DATAA data,
                        WIN32_FIND_DATAW data,
                        int &cur_traffic,
                        bool has_stream_filter
                       );

    bool CrawlHttp(
                   const lem::Url &uri_str,
                   int cur_depth,
                   int cur_traffic,  
                   const lem::Url &org_domain
                  );
    #endif

    virtual bool ProcessFile(
                             File_Location &filename,
                             lem::Stream &file,
                             Base_File_Reader *reader,
                             const Solarix::Search_Engine::Doc_Info *doc_info
                            );

    void ProcessMatchingDoc(
                            const File_Location &filename,
                            Base_File_Reader *reader,
                            MCollect<Fix_Context*> &contexts
                           );


    virtual void ClearOptions(void);

    virtual void FormatUnknown( File_Location &filename );
  
    bool CheckModif( const File_Location &fl );

    #if defined FAIND_FILEMON
    virtual void StartMonitoringFolders( Change_Event_Func func );
    #endif

    boost::posix_time::ptime start_time; // Начало сканирования
    boost::posix_time::ptime stop_time;  // Окончание сканирования
 
    lem::Ptr<Solarix::Search_Engine::Base_File_Reader> text_stream; // явно указанный поток для обработки (вместо области сканирования)

    virtual int CreateFiletypeDetector( bool ForceReload=false );

    #if defined FAIND_UNPACK   
    virtual void PrepareUnpackers( bool ForceReload=false );
    #endif

    #if defined FAIND_PLUGINS && defined FAIND_UNPACK
    // Загрузим плагины
    virtual int LoadUnpackerPlugins( bool ForceReload=false );
    virtual lem::Path GetUnpackerPluginsFolder(void) const;
    #endif

    #if defined FAIND_WEB
    virtual const UFString GetHttpAgentName(void) const;
    #endif 

    virtual void StartTime(void);
    virtual void StopTime(void);

    #if !defined LEM_WINDOWS && !defined LEM_UNIX
    virtual void ProcessFolder( const boost::filesystem::path &Path );
    #endif

    #if defined FAIND_NETWORKING
    virtual void ProcessPipe( const UFString &pipename );
    virtual void ProcessSocket( const UFString &addr );
    #endif

    virtual void ScanEngines(void);

    #if defined FAIND_UNPACK   
    virtual void ProcessArchive(
                                File_Location& filename,
                                lem::Stream &file,
                                const UFString &ext
                               );

    virtual void ProcessArchivedFile(
                                     File_Location& filename,
                                     std::pair< lem::Ptr<lem::Pack::IUnpackerFactory>, lem::CPtr<Unpacker_Plugin> > handler
                                    );

    bool IsArchive( const UFString &ext ) const;
    #endif

    virtual void ScanFolders(void);
    virtual void ScanFiles(void);

    #if defined FAIND_WEB
    virtual void ScanSites(void);
    #endif

    #if defined FAIND_NETWORKING
    virtual void ScanPipes(void);
    #endif
   
    #if defined FAIND_WEB
    void OpenInternetSession(void);

    virtual bool ProcessURL(
                            const lem::Url &uri,
                            int cur_depth,
                            int cur_traffic,  
                            const lem::Url &org_domain
                           );
    #endif

    #if !defined LEM_WINDOWS && !defined LEM_UNIX
    virtual void StartProcessingFolder( const boost::filesystem::path &Path );
    #endif

    virtual void StartProcessingFolder( const wchar_t *Path );
    virtual void StartProcessingFolder( const char *Path, bool utf8 );

    #if defined FAIND_NETWORKING 
    virtual void StartProcessingPipe( const UFString &pipename );
    virtual void StartProcessingSocket( const UFString &addr );
    #endif

    virtual void UnknownFormat( File_Location &filename );


    virtual bool ProcessFileWithFormat(
                                       File_Location &filename,
                                       lem::Stream &file,
                                       const lem::MIMEType &format,
                                       const Solarix::Search_Engine::Doc_Info *doc_info
                                      );

    // Генерируем имя файла для сохранения содержимого скачанного из
    // интернета документа.
    virtual const lem::Path GenerateDownloadName( const UFString &url );

//    virtual void BeforeScanningFile( const UFString &filename );

   protected:
    #if defined FAIND_INDEXER
    lem::Ptr<Indexer> indexer;
    #endif 

    volatile bool do_scanning; // continue scanning?

    // -----------------------------------------------------
    // Приготовились к поиску по новой зоне - даем
    // возможность установить CD/DVD в привод, в случае
    // невозможности - возвращается 0 и поиск будет отменен.
    //
    // Должна вернуть:
    //
    // 0 - пропустить диск (индекс)
    // 1 - диск установлен и готов к считыванию
    // 2 - прервать весь поиск
    // -----------------------------------------------------
    virtual int NewZoneLoaded(void);

    // Создаем необходимый индексатор
    virtual void CreateIndexer(void);

    virtual void PresetClone( Crawler *ptr );

   public:
    lem::Ptr<Progress_Callback> callback;
    lem::Ptr<Continue_Callback> ask_continue;

//    Hit_Statistics hit_count; // Счетчик попаданий

    // Распарсенная команда
    lem::Ptr<Crawler_Operation> engine_command; 

    lem::Ptr<General_Options> generals;

    // список стоп-слов и других параметров для лексеров
    lem::Ptr<Lexer_Options> lexer_options;

    // указатель на парсер команд, который породил данный объект
    lem::zeroed_ptr<const CommandParser> command_parser; 

    lem::Ptr<ARC_EXT>& GetArcExt(void) { return arc_ext; }

    // Вернет false, если просмотр области поиска надо прекратить
    virtual bool DoContinueScanning(void);

   public:
    Crawler( const CommandParser *parser );

    virtual ~Crawler(void);

    // Создает копию краулера и клонирует указатели на всевозможные
    // общие модули.
    virtual Crawler* New( const CommandParser *parser ) const;
    virtual Crawler* Clone( const CommandParser *parser );

    virtual void PrintResults(void);

    // Возвращает ссылку на ранее загруженную грамматическую машину
    inline Solarix::Dictionary& GetDictionary(void)
    { 
     LEM_CHECKIT_Z( &*dictionary != NULL );
     return *dictionary; 
    }

    inline Solarix::LD_Seeker& GetSeeker(void)
    { 
     LEM_CHECKIT_Z( &*ld_seeker != NULL );
     return *ld_seeker; 
    }

    lem::Ptr<Fuzzy_Comparator>& GetFuzzyComparator(void) { return fuzzy_eq; }

    #if !defined SOL_NO_AA
    //lem::Ptr<Solarix::Text_Processor>& GetSyntaxAnalyzer(void) { return tpu; }
    #endif


    int CreateIndex( const wchar_t *DomainName, bool Dynamic, int Morphology, bool Proximity, bool Statistics );
    int IndexFile( const wchar_t *Filename );
    int IndexText( const wchar_t *Name, const wchar_t *Text, int TextLen );

    #if defined FAIND_DATAMINE
    virtual Topic_Finder& GetTopicFinder(void);
    virtual void TrainAutoclassifierByXML( lem::Stream &xml );
    #endif

    virtual void SetSrcStream( const wchar_t *Text );

    virtual void Scan(void);

    Detected_Format IsFileAccepted( const lem::Path &filename ) const;
    bool IsFileAcceptedByExtension( const UFString &ext ) const;
    bool IsFileAccepted( lem::Stream &file ) const;
    bool IsFileAccepted(
                        lem::Stream::pos64_type Size,
                        const boost::posix_time::ptime &Creat,
                        const boost::posix_time::ptime &Modif
                       ) const;

    // Полная очистка кэша распакованных файлов.
    virtual void PurgeDownloadCache(void);

    virtual const lem::Path Store( File_Location &filename, lem::Stream &file );

    // Возвращаем список расширений архивных файлов, обрабатываемых движком.
    const UFString ListSupportedUnpackers(void) const;
    void ListSupportedUnpackers( lem::Collect< std::pair<UFString,UFString> > &list ) const;

    // Печатаем список поддерживаемых форматов документов
    void ListSupportedReaders( OFormatter &out ) const;

    virtual void StartProcessingFile( const File_Location &filename, bool force=false );

    virtual void Success(
                         int ictx,
                         const Fix_Context *ctx,
                         const File_Location &filename,
                         const string &file_format 
                        );

    virtual bool ProcessFile(
                             File_Location& filename,
                             const Solarix::Search_Engine::Doc_Info *doc_info=NULL
                            );

    virtual bool ProcessFile(
                             File_Location &filename,
                             lem::Stream &file,
                             const Solarix::Search_Engine::Doc_Info *doc_info
                            );


    // Печать состояния кэша распакованных файлов.
    virtual void PrintDownloadCacheInto( OFormatter &out ) const;

    virtual void LoadDictionary( bool verbose );
    
    // Загружен ли словарь?
    bool CheckDictionary(void) const;

    // Заполняет список названий всех загруженных плагинов.
    virtual void ListAllPlugins( Collect< std::pair<lem::UFString,lem::Path> > &list );

    #if defined FAIND_INDEXER
    inline IndexManager& GetIndexManager(void)
    {
     LEM_CHECKIT_Z(idb);
     return *idb;
    }
    #endif

    #if defined FAIND_IENGINES
    lem::Ptr<IGrammarEngine> GetIGrammarEngine(void);
    lem::Ptr<ISearchEngine> GetISearchEngine(void);
    #endif

    inline lem::Ptr<File_Type_Detector> GetFileTypeDetector(void)
    {
     LEM_CHECKIT_Z(file_type_detector);
     return file_type_detector;
    }

    MediaInfoManager& GetMediaInfoManager(void);

    // Прерываем исполнение в треде.
    virtual void AbortScanning( bool terminate_thread );
    inline bool DoScanning(void) const { return do_scanning; }

    // Возвращает ссылку на менеджер локализованных ресурсов
    lem::UI::Resource_List& GetResources(void) const;

    #if defined FAIND_PLUGINS
    bool FindEnginePlugin( const UFString &plugin_name ) const;
    #endif

    static void PauseExecution(void);
    static void ResumeExecution(void);

    DocumentTagsCache& GetDocumentTagsCache(void);

    int LoadPlugins(void);
  };

 } // namespace Search_Engine
 } // namespace Solarix

#endif
