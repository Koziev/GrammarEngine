#if !defined SE_DOMAIN_INFO__H && defined FAIND_INDEXER
#define SE_DOMAIN_INFO__H
#pragma once

 #include <boost/utility.hpp> 
 #include <lem/streams.h>
 #include <lem/process.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
   // ****************************************************************
   // Базовая информация об индексе в таблице описания зон.
   // Хранит спецификацию - тип индекса, его физическое размещение,
   // другие параметры.
   // ****************************************************************
  
   // в этой структуре хранится информация для алиасов индексов - которые
   // на самом деле находятся на удаленном сервере.
   struct Remote_Zone
   {
    lem::zbool ok; // поля проинициализированы
    int id_remote;
    typedef enum { UnknownServer, SQLite, MySQL } ServerType;
    ServerType server_type;
    lem::UFString server_host;
    lem::UFString server_db;
    lem::UFString server_login;
    lem::UFString server_password;
    lem::Path db_folder; // на будущее - для доступа к файловому хранилищу
   
    Remote_Zone(void);
  
    Remote_Zone( const Remote_Zone& x );

    void operator=( const Remote_Zone& x );

    bool EqServer( const Remote_Zone& x ) const;
   };


   class Domain_Info : public boost::noncopyable
   {
    public:
     enum ContentMode { Dynamic=0, Static=1, NoIndex=2 };
     enum ActivationType { NoActivation, CdromActivation };
     enum ChangesMonitorType {
                              Manual,   // ручное переиндексирование
                              WinNT,    // используются средства WinAPI для отслеживания изменений в каталогах
                              Scheduled // регулярное переиндексирование по расписанию
                             }; 
     enum EngineType { FaindEngine, CLuceneEngine, MySqlEngine, LocateEngine,
                       WDSEngine, FTPCrawler }; // тип индексатора

     enum IconType { CD_Icon, WWW_Icon, LAN_Icon, MyComp_Icon, MyDocs_Icon, MyPics_Icon, MySql_Icon, HDD_Icon, Other_Icon };

    private:
     friend class Idb_List;

     #if defined LEM_THREADS
     lem::Process::CriticalSection cs; // для синхронизации изменений
     #endif

     int Id;             // PK записи
     bool Dirty;         // запись нужно сохранять
     bool Actual;
     bool Lock;          // запись залочена - идет ее изменение. 

     lem::UFString Name;      // external_name
     lem::UFString Comment;   // дополнительная произвольная инфа (примечания)
     lem::Path Folder;        // database files folder

     ContentMode Mode;   // domain content is not changable
     bool     ReadOnly;  // can modify database files
     lem::UFString Cmd;       // команды формирования области
     bool     Wordforms; // проиндексирована с -index wordforms

     // **********************************************************
     // Перед началом использования документов в зоне
     // может потребоваться выполнить некие действия - установить
     // диск в привод, подключить сетевой ресурс и т.д.
     ActivationType Activation;

     lem::uint32_t SerialNumber; // серийный номер диска
     lem::FString Cdrom; // имя системного диска CD/DVD привода
     lem::UFString Login, Psw; // для подключения к сетевому ресурсу
     // **********************************************************

     // Сведения о версии словаря
     int DictCode;
     bool NeedsRefresh; // нуждается в переиндексировании

     std::auto_ptr< lem::PtrCollect<lem::Path> > changed_files; // список файлов, которые изменились и нуждаются в переиндексировании
     std::set< lem::Path > changed_files_set; // для контроля за неповторяемостью

     lem::Stream::pos_type FilePos; // позиция сохранения описания в файле

     // Способ контроля изменений в динамическом индексе
     ChangesMonitorType Monitor;

     boost::posix_time::ptime Modif; // дата последнего обновления

     EngineType engine_type; // тип используемого движка

     lem::zbool shared; // признак общего сетевого доступа
     lem::zbool allows_word_wheeled_search; // индекс допускает поиск-по-мере-ввода

     Remote_Zone remoting; // для ссылки на другую зону, возможно удаленную

     void Init( const Domain_Info &x );

    public:
     #if defined FAIND_IDBLIST_RAM
     lem::zbool do_rebase_path;
     lem::UFString old_prefix_path; // начальный участок файлового пути, который надо менять
     lem::UFString new_prefix_path; // на этот участок меняем
     #endif

     static lem::Path domain_info_filename; // "domain_info.bin"

    public:
     Domain_Info( int id=UNKNOWN );
     Domain_Info(
                 int id,
                 const lem::UFString &domain_name,
                 const lem::Path &folder,
                 ContentMode mode,
                 bool readonly,
                 const lem::UFString &cmd,
                 bool wordforms,
                 ChangesMonitorType refresh,
                 EngineType engine,
                 bool is_shared,
                 bool f_allows_word_wheeled_search  
                ); 

     Domain_Info( const Domain_Info &x );
     void operator=( const Domain_Info &x );

     virtual ~Domain_Info(void) {}

     // Отмечаем зону как "удаленная"
     virtual void Deleted(void);

     void LoadBin( lem::Stream &bin );
     void SaveBin( lem::Stream &bin );

     virtual void SaveNeedsRefreshFlag( lem::Stream &bin ) const;

     inline int GetId(void) const { return Id; }
     inline const lem::UFString& GetName(void) const { return Name; }
     inline const lem::UFString& GetComment(void) const { return Comment; }
     inline const lem::UFString& GetCommand(void) const { return Cmd; }
     inline const lem::Path& GetFolder(void) const { return Folder; }
     inline const boost::posix_time::ptime GetModif(void) const { return Modif; }
     inline const lem::FString& GetCdrom(void) const { return Cdrom; }
     inline int GetSerialNumber(void) const { return SerialNumber; }
     inline const lem::UFString& GetLogin(void) const { return Login; }
     inline const lem::UFString& GetPsw(void) const { return Psw; }

     inline ChangesMonitorType GetChangesMonitor(void) const { return Monitor; }
     inline bool DoesNeedIdleRefresh(void) { return Monitor==/*ChangesMonitorType::*/Scheduled; } 
     inline bool IsMonitored(void) const { return Monitor==/*Changes_Monitor::*/WinNT; }

     inline ContentMode GetMode(void) const { return Mode; }

     // вернет false для удаленной зоны 
     inline bool IsActual(void) const { return Actual; }

     inline bool IsReadOnly(void) const { return ReadOnly; }

     inline bool IsStatic(void)  const { return Mode==Static;  }
     inline bool IsDynamic(void) const { return Mode==Dynamic; }
     inline bool IsNoIndex(void) const { return Mode==NoIndex; }

     inline bool GetWordforms(void) const { return Wordforms; }


     inline bool IsShared(void) const { return shared; }
     void Share(void);
     void Unshare(void);
     inline void SetShared( bool f ) { shared=f; }

     inline bool AllowsWordWheeledSearch(void)  { return allows_word_wheeled_search; }
     void SetAllowsWordWheeledSearch( bool f );

     inline ActivationType GetActivation(void) const { return Activation; }

     inline Domain_Info::EngineType GetEngineType(void) const { return engine_type; }

     inline void SetNeedsRefresh( bool f=true ) { NeedsRefresh=f; Dirty=true; }
     inline bool DoesNeedRefresh(void) const { return NeedsRefresh; }
     virtual void Refreshed(void);

     inline void SetCmd( const lem::UFString &cmd ) { Cmd=cmd; Dirty=true; }

     inline void SetWordforms( bool flag ) { Wordforms=flag; Dirty=true; }
     inline void SetDictCode( int code ) { DictCode=code; Dirty=true; }
     inline void SetActivation( ActivationType a ) { Activation=a; Dirty=true; }
     inline void SetCdrom( const lem::FString &cdrom ) { Cdrom=cdrom; Dirty=true; }
     inline void SetSerialNumber( lem::uint32_t serial ) { SerialNumber=serial; Dirty=true; }  
     inline void SetName( const lem::UFString &name ) { Name=name; Dirty=true; }
     inline void SetComment( const lem::UFString &rem ) { Comment=rem; Dirty=true; }
     inline void SetActual( bool f ) { Actual=f; }
     inline void SetFolder( const lem::UFString &str ) { Folder=lem::Path(str); Dirty=true; }
     inline void SetLogin( const lem::UFString &str ) { Login=str; Dirty=true; }
     inline void SetPsw( const lem::UFString &str ) { Psw=str; Dirty=true; }
     inline void SetModif( boost::posix_time::ptime t ) { Modif=t; Dirty=true; }
     inline void SetMonitor( ChangesMonitorType t ) { Monitor=t; Dirty=true; }
     inline void SetMode( ContentMode t ) { Mode=t; Dirty=true; }
     inline void SetReadOnly( bool f ) { ReadOnly=f; Dirty=true; }
     inline void SetEngineType( EngineType type ) { engine_type=type; }

     void GetFolders( lem::Collect<lem::UFString> &list ) const;
     void GetExtFilters( std::set<lem::UFString> &ext_filter ) const;

     inline bool IsDirty(void) const { return Dirty; }
     inline void SetDirty( bool flag ) { Dirty=flag; }

     // Возвращает тип иконки для отрисовки
     Domain_Info::IconType GetIconType(void) const;

     // Вернет true для индекса "My computer"
     bool IsMyComputer(void) const;

     // Возвращает список папок (серверов) с проиндексированными документами,
     // используется только для отображения свойств индекса пользователю.
     lem::UFString GetDocSources( const wchar_t delimiter=L';' ) const;
     
     void AddChangedFiles( lem::Collect< lem::Path* > &changed_files );
     void RefreshWholeZone(void); 
     
     lem::PtrCollect<lem::Path>* GetChangedFiles(void);
     const lem::PtrCollect<lem::Path>& GetChangedFiles2(void) const;
     const bool IsThereChangedFiles(void) const;

     // Если запись является отсылкой на другой индекс (обычно на сервере).
     inline bool IsRemote(void) const { return remoting.ok; }
     inline const Remote_Zone& GetRemoting(void) const { return remoting; }
     void Import( const Domain_Info &remote_domain, const Remote_Zone &remoting );
     void SetRemoting( const Remote_Zone &z ) { remoting=z; }

     int GetModeAndShare(void) const;
   }; 

  }
 }

#endif
