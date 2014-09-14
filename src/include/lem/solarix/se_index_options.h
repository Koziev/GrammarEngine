#ifndef SE_INDEX_OPTIONS__H
#define SE_INDEX_OPTIONS__H
#pragma once

 // Структура Indexer_Options - общие параметры индексатора, 
 // одщие для всех создаваемых индексаторов в рамках текущей
 // сессии.
 
 #include <boost/utility.hpp>
 #include <lem/zeroed.h>
 #include <boost/logic/tribool.hpp>
 #include <lem/fstring.h>
 #include <lem/noncopyable.h>
 #include <lem/ufstring.h>
 #include <lem/solarix/se_morphology.h>
 #include <lem/solarix/se_domain_info.h>

 #if defined FAIND_IDBLIST_MYSQL || defined FAIND_INDEXER_MYSQL
  #define FAIND_MYSQL
 #endif

 #if defined FAIND_MYSQL
  #include <lem/mysql/mysql.h>
 #endif

 namespace Solarix
 {
  namespace Search_Engine
  { 
   using boost::logic::tribool;

   // **************************************************
   // Структура с параметрами подключения к SQL backend
   // **************************************************
   struct SQLConnection : boost::noncopyable
   {
    lem::FString login;
    lem::FString psw;
    lem::FString db;   // имя базы для MySQL, алиас для Oracle, или DSN для ODBC
    lem::FString host; // адрес хоста (опционально, если SQL драйвер требует).

    #if defined FAIND_MYSQL
    MYSQL* mysql;
    #endif
   
    SQLConnection(void);
    ~SQLConnection(void);

    // Подключаемся к СУБД
    void Connect(void);

    void Disconnect(void);

    // Начинаем транзакцию
    void Begin(void);

    // Фиксируем транзакцию
    void Commit(void);

    // Откатываем транзакцию
    void Rollback(void);

    #if defined FAIND_MYSQL
    inline MYSQL* GetHandle(void) { return mysql; }
    #endif

    bool Connected(void) const;
   };


   #if defined FAIND_INDEXER
   // *****************************************
   // Опции для управления работой индексаторов
   // *****************************************
   struct Indexer_Options
   {
    bool use; // Использовать ли индексатор при поиске
    lem::Path storage; // Каталог с файлами индексатора (если файловое хранилище)
    SQLConnection *connection; // Параметры подключения к БД

    lem::zbool allow_clucene_wr; // разрешать одновременную работу одного писателя
                                 // и множества читателей для индексатора CLucene

    lem::zbool allow_mysql_wr; // разрешать одновременную работу одного писателя
                               // и множества читателей для индексатора MySQL
 
    lem::zbool ram_cataloguer; // объект базы каталогизатора типа Idb_List_File_Ram для поиска с CD
    lem::Path preload_index_db; // путь (абсолютный, с раскрытыми макросами) для каталога с базой индекса для загрузки
    lem::UFString preload_index_name; // имя этого индекса
    lem::zbool subst_cddrive; // автоматически заменять имя диска на CDROM для путей к найденным файлам

    Indexer_Options(void);

    Indexer_Options( const Indexer_Options &x );

    void operator=( const Indexer_Options &x );

    inline void Disable(void) 
    { use = false; }

    bool CheckSQLConnection(void) const;
   };
   #endif
 
   #if defined FAIND_INDEXER
   struct Create_Command : lem::NonCopyable
   {
    lem::UFString Name;
    lem::Path LocationFolder;
    lem::zbool ReadOnly;
    lem::zbool shared;
    lem::zbool word_wheeled_search;
    Solarix::Search_Engine::Domain_Info::ContentMode Mode;
    Solarix::Search_Engine::Domain_Info::ChangesMonitorType Refresh;
    Solarix::Search_Engine::Domain_Info::EngineType engine_type;

    Create_Command(void)
    {
     Mode = Solarix::Search_Engine::Domain_Info::/*ContentMode::*/Static;
     Refresh = Solarix::Search_Engine::Domain_Info::/*ChangesMonitorType::*/Manual;
     engine_type = Solarix::Search_Engine::Domain_Info::/*EngineType::*/FaindEngine;
    }
   };
   #endif



   // **************************************************
   // Параметры создаваемого или используемого индекса,
   // команды DDL для индекса или всех индексов.
   // **************************************************
   struct Indexer_Operation
   {
    #if defined FAIND_INDEXER
    static lem::UFString ALL_ZONES_NAME; // внутреннее имя для обозначения 'все зоны' для поиска
    static lem::UFString ALL_SHARED_ZONES_NAME; // аналогично для расшаренных индексов

    lem::zbool use; // использовать индексатор
    lem::UFString domain_name; // Имя области поиска
    int id_domain; // если индекс загружен, то - его id.

    lem::Collect<lem::UFString> domains; // Список имен зон - если поиск по нескольким зонам 

    lem::UFString command; // текстовое представление команды
    lem::UFString arg, arg2; // дополнительные аргументы команды
    lem::zbool ddl; // для команд типа -index purge
    Create_Command create; // дополнительные аргументы для команды -index create_domain ...

    lem::zbool searching;     // выставляется программой: поиск по зоне
    lem::zbool indexing;      // выставляется программой: индексирование зоны
    lem::zbool updating;      // выставляется программой: обновление индекса
    lem::zbool optimize;      // оптимизировать и чистить базу при commit'е (если индексатор поддерживает)
    lem::zbool add_files;     // в индекс добавляются папки
    
    lem::zbool touch_files;   // при поиске только по индексу - искать контексты в файлах
    lem::zbool touch_servers; // проверять доступность FTP серверов
    lem::zbool show_metainfo; // показывать метаинформацию о найденном документе (теги)   

    Solarix::Search_Engine::Morphology morphology; // использовать приведение к базовым формам при заполнении
                           // справочника или учитывать динамические словоформы 

    tribool allow_reindex; // разрешено ли в ходе поиска переиндексировать измененные
                           // документы.

    lem::zbool recreate_whole_assoc; // полное пересоздание прямых списков по документным индексам
    lem::zbool store_docindex; // сохранять подокументный индекс
    lem::zbool store_docmatrix; // для документов сохранять доп. информацию

    lem::zbool store_doc_prox; // сохранять подокументную матрицу близости
    lem::zbool store_zone_prox; // строить и схоранять общезоновую матрицу связанности
   
    // Для зоны построена матрица связности и ее можно использовать для поиска
    lem::zbool can_read_zone_prox;

    lem::zbool create_proximity; // для документов сохранять матрицу близости слов
    lem::zbool create_frequency; // для документов накапливать статистику частот слов
    lem::zbool knowledge_mine;   // извлекать данные и сохранять результаты в индексе

    lem::zbool create_topic; // находить и сохранять темы документов и другие метапризнаки
    lem::zbool store_tags; // запоминать в подокументном индексе тэги документов (например,
                     // содержимое <title> в HTML или тэги для MP3)
    lem::zbool store_contents; // содержимое документов сохранять в базы для offline поиска на сменных носителях

    enum Ranking { No_Rank, Freq_Rank, Rel_Freq_Rank };
    Ranking ranking; // при поиске вычислять вес документа (один из алгоритмов)

    lem::zbool load_all_keywords;

    lem::zbool control_modif; // контролировать соответствие записей о файлах в базе и
                        // реальных файлов
 
    lem::zbool force_reindex; // Необходимо выполнять сканирование зоны для переиндексирования 

    lem::zbool allow_rooting;   // пытаться ли приводить к корню автоматически при поиске

    void Init( const Indexer_Operation &x );

    Indexer_Operation(void); 
    Indexer_Operation( const Indexer_Operation &x );

    void operator=( const Indexer_Operation &x );

    inline void Disable(void) 
    {
     load_all_keywords=false;
    }

    inline bool AllDomains(void) const { return domain_name==ALL_ZONES_NAME; }
    inline bool AllSharedDomains(void) const { return domain_name==ALL_SHARED_ZONES_NAME; }
    #endif
   };

  }
 } 
 
#endif
