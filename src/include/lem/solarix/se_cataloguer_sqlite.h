#if !defined IDX_CATALOGUER_SQLITE__H
 #define IDX_CATALOGUER_SQLITE__H
#pragma once

 #if defined FAIND_IDBLIST_SQLITE

 #include <lem/sqlite/sqlite3.h> 
 #include <lem/solarix/se_indexer.h>

 namespace Solarix
 {

  namespace Search_Engine
  { 

   // ***************************************************************
   // Специализация каталогизатора для хранения в реляционной СУБД.
   // ***************************************************************
   class Idb_List_SQLite : public Idb_List
   {  
    private:
     boost::posix_time::ptime list_timestamp; // отметка времени загруженного списка,
                                              // используется для синхранизации зеркала
                                              // в оперативке и образа в БД. 

     lem::Path list_filename; // "idb_filename" имя файла БД (только для SQLite)

     struct sqlite3* hdb; // дескриптор БД

     // полный путь к корневому файлу со списком индексов
     const lem::Path GetListFileName(void) const;

     // В таблицу CHANGELOG записывается текущее время как время
     // последнего сохранения записей в IDB_LIST
     void UpdateChangelog(void);

     // Создаем необходимые таблицы в пустой БД.
     void CreateScheme(void);
     void CreateAdditionalTables(void);

     void BeginTransaction(void);
     void CommitTransaction(void);
     void RollbackTransaction(void);
     int SelectInt( const char *Select );
     void UpdateSQL( const Domain_Info &domain, FString &update ) const;
     void UpdateSQL_NeedsRefresh( const Domain_Info &domain, FString &update ) const;
     void InsertSQL( const Domain_Info &domain, FString &update ) const;
     void InsertSQL_Remoting( const Domain_Info &domain, FString &update ) const;
     void DeleteSQL_Remoting( const Domain_Info &domain, FString &sql ) const;

     void SaveChangedFiles( const Domain_Info &domain ) const;

     virtual void SaveScheduledFiles(void);

     const Domain_Info& ImportDomain( const Domain_Info &d, const Remote_Zone& r );

     void OpenDatabase(void);
     void CloseDatabase(void);

    public:
     Idb_List_SQLite( const Indexer_Options *Flags );
     virtual ~Idb_List_SQLite(void);

     // Печать сведений о реализации хранилища.
     // Для StorageInfo=true также печатается информация о состоянии 
     // хранилища данных.
     virtual void PrintVersion(
                               OFormatter &out,
                               const lem::UI::Resource_List &resx,
                               bool StorageInfo=false
                              ) const;

     virtual int CreateDomain(
                              const UFString &Domain_Name,
                              const lem::Path &index_db_folder,
                              Domain_Info::ContentMode Mode,
                              bool ReadOnly,
                              const UFString &Cmd,
                              Domain_Info::ChangesMonitorType Refresh=Domain_Info/*::Changes_Monitor*/::Manual,
                              Domain_Info::EngineType engine_type=Domain_Info::FaindEngine ,
                              bool shared=false,
                              bool allows_word_wheeled_search=false
                             );

     virtual void StoreDomainCommands( int id_zone, const UFString &Cmd );

     // Запоминаем, что при индексации зоны использован словарь. Изменения
     // запоминаются в хранилище.
     virtual void SetNeedsDictionary( const UFString &Domain_Name, bool Flag );

     // Загрузка списка зон из файла (или БД) в оперативную память
     virtual void Load(void);

     // Перезагрузка описания одного индекса
     virtual void ReloadDomain( int id );


     // Запись измененного списка областей в дисковый файл, атомарная
     // операция (либо целиком успешна, либо в хранилище останется старый
     // список).
     virtual void Save(void);

     // Удаление описания зоны и сохранение изменения в хранилище.
     virtual void DeleteDomain( int id_zone );

     // Очистка зоны - само описание остается.
     virtual void PurgeDomain( int id_zone );

     // Переименование зоны и сохранение изменений в хранилище
     virtual void Rename( int iZone, const UFString &new_name );

     // Изменение описания индекса и сохранение изменений в хранилище
     virtual void SetComment( int iZone, const UFString &Comment );

     virtual void Share( int id_zone, bool shared );

     // Для указанного индекса сохраняется только флаг
     // "нуждается в переиндексировании".
     virtual void SaveNeedsRefreshFlag( int id_zone );

     virtual void DeleteAllIndexes(void);

     // В зоне еще не производилось индексирование?
     virtual bool IsEmptyDomain( int id_zone );

     // Сохранение корневой таблицы в указанном каталоге.
     virtual void BackupDomainsList( const lem::Path &dest_folder );

     // Восстановление корневой таблицы из резервной копии в указанном каталоге.
     virtual void RestoreDomainsList( const lem::Path &dest_folder );

     // Сохранение индекса в указанном каталоге.
     virtual void BackupDomain( const UFString &domain_name, const lem::Path &dest_folder );

     // Восстановление индекса из резервной копии в указанном каталоге.
     virtual void RestoreDomain( const UFString &domain_name, const lem::Path &dest_folder );

     // Пытаемся заблокировать указанный индекс, возвращаем true в случае успеха.
     virtual bool LockByReader( int id_index );
     virtual bool LockByWriter( int id_index );

     // Проверяем наличие блокировки. Это не всегда срабатывает ожидаемым
     // образом, так как после успешной проверки блокировка может измениться.
     virtual bool IsLockedByReader( int id_index );
     virtual bool IsLockedByWriter( int id_index );

     // Пытаемся заблокировать указанный индекс, возвращаем true в случае успеха.
     virtual void UnlockByReader( int id_index );
     virtual void UnlockByWriter( int id_index );

     // Принудительное снятие всех блокировок.
     virtual void UnlockAll(void);
   };

  }
  
}

#endif
 
#endif
