#ifndef SE_CRAWLER_OPERATION__H
#define SE_CRAWLER_OPERATION__H
#pragma once

 #include <lem/config.h>

 #if !defined LEM_WINDOWS && !defined LEM_UNIX
  #include <boost/filesystem/path.hpp>
 #endif

 #include <boost/utility.hpp>
 #include <boost/logic/tribool.hpp>

 #include <lem/tuple.h>
 #include <lem/nullable.h>
 #include <lem/process.h>
 #include <lem/ptr_container.h>
 #include <lem/smart_pointers.h>
 #include <lem/math/random.h>


 #if defined FAIND_SQL
 #include <lem/db.h>
 #include <lem/io_db_stream.h>
 #endif 
 
 #include <lem/ufstring.h>
 #include <lem/zeroed.h>
 #include <lem/cfg_parser.h>
 #include <lem/path.h>
 #include <lem/ptr_container.h>
 #include <lem/streams.h>
 #include <lem/smart_pointers.h>
 #include <lem/date_time.h>

 #if defined SOLARIX_PRO
  #include <lem/solarix/se_httpd.h>
 #endif

 #include <lem/solarix/se_query.h>
 #include <lem/solarix/se_action_options.h>
 #include <lem/solarix/se_echo_options.h>
 #include <lem/solarix/se_scan_options.h>


 namespace Solarix
 {
  namespace Search_Engine
  { 


  struct DownloadCache_Operation : lem::NonCopyable
  {
   UFString command;

   inline bool Empty(void) const { return command.empty(); }
  };

  #if defined FAIND_DATAMINE
  struct TopicDB_Operation : lem::NonCopyable
  {
   lem::UFString command;
   lem::UFString arg;
 
   bool Empty(void) const { return command.empty(); }
  };
  #endif

  #if defined SOLARIX_PRO
  struct TagsDB_Operation : lem::NonCopyable
  {
   lem::UFString command;
   lem::UFString docs;
   lem::UFString tags;
   lem::UFString value;

   bool Empty(void) const { return command.empty(); }
  };
  #endif

  #if defined FAIND_PROBE_FEATURE
  struct Probe_Operation : lem::NonCopyable
  {
   lem::UFString feature;
   bool Empty(void) const { return feature.empty(); }
  };
  #endif 

  #if defined SOLARIX_PRO
  struct HttpdOperation : lem::NonCopyable
  {
   typedef enum { None, Start, Pause, Stop } CommandType;

   CommandType command;
   lem::FString ip;
   int port;
 
   HttpdOperation(void) { command=None; port=-1; }
   bool Empty(void) const { return command==None; }
  };
  #endif

  // *****************************************************
  // Для создания внешнего исполнителя команд -help=NN
  // *****************************************************
  struct Help_Operation : lem::NonCopyable
  {
   lem::Nullable<int> division;

   inline bool Empty(void) { return division.IsNull(); }
  };


  // *******************************************************
  // Результат парсинга команды - все параметры управления
  // работой краулера и других модулей.
  // *******************************************************
  class Crawler_Operation
  {
   public:
    Help_Operation help_operation;
    DownloadCache_Operation dcache_operation;
    Indexer_Operation idb_operation;
    #if defined FAIND_DATAMINE
    TopicDB_Operation topicdb_operation;
    #endif
    #if defined SOLARIX_PRO
    HttpdOperation httpd_operation;
    #endif

    #if defined SOLARIX_PRO
    TagsDB_Operation tagsdb_operation;
    #endif

    #if defined FAIND_PROBE_FEATURE
    Probe_Operation probe_operation;
    #endif

    lem::Ptr<Query> query_info; // Запрос
    Ptr_NC_Collect<Pattern> queries; // Паттерны запроса

    Scan_Options scanning; // флаги сканирования (область поиска)
    Search_Options flags;     
    Echo_Options echo;
    #if defined FAIND_INDEXER
    Indexer_Options idb_options; 
    #endif  
    Context_Options ctx_options;   // Fix context decoration options
    Action_Options action;         // Для обработки результатов поиска (запись в поток и т.д.)
    lem::Collect<FString> tunes;   // Miscelaneous tuning options

    Crawler_Operation(void) {}
    Crawler_Operation( const Crawler_Operation &ini );

    const Crawler_Operation& operator=( const Crawler_Operation &ini );

    void Clear(void);

    // Выполняется поиск
    bool IsSearching(void) const;
  };
 }
}

#endif
