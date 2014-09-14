// -----------------------------------------------------------------------------
// File SE_CATALOGUER_FILEDB.H
//
// (c) 2008 by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// 06.10.2008 - объявление класса Idb_List_File вынесено из se_indexer.h в
//              данный файл в ходе рефакторинга проекта. 
// -----------------------------------------------------------------------------
//
// CD->06.10.2008
// LC->13.11.2008
// --------------

#if !defined SE_CATALOGUER_FILEDB__H && defined FAIND_IDBLIST_FILEDB
 #define SE_CATALOGUER_FILEDB__H
#pragma once

 #include <lem/solarix/se_indexer.h>
 
 namespace Solarix
 {
  namespace Search_Engine
  { 

   // ***************************************************************
   // Специализация каталогизатора для хранения в дисковом файле.
   // ***************************************************************
   class Idb_List_File : public Idb_List
   {  
    private:
     boost::posix_time::ptime list_timestamp; // отметка времени загруженного списка,
                                              // используется для синхранизации зеркала
                                              // в оперативке и образа на диске. 

     lem::Path list_filename; // "idb_filename" имя файла со списком описателей индексов
     lem::Path todel_filename; // имя файла со списком путей для удаления

     // полный путь к корневому файлу со списком индексов
     const lem::Path GetListFileName(void) const;

     // полный путь к списку файлов/папок для удаления
     const lem::Path GetToDelFileName(void) const;

     virtual void SaveScheduledFiles(void);

    public:
     Idb_List_File( const Indexer_Options *Flags );
     virtual ~Idb_List_File(void);

     // Печать сведений о реализации хранилища.
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
                              Domain_Info::EngineType engine_type=Domain_Info::FaindEngine,
                              bool shared=false,
                              bool allows_word_wheeled_search=false
                             );

     virtual void StoreDomainCommands( int id_zone, const UFString &Cmd );

     // Запоминаем, что при индексации зоны использован словарь. Изменения
     // запоминаются в хранилище.
     virtual void SetNeedsDictionary( const UFString &Domain_Name, bool Flag );

     // Загрузка списка зон из файла (или БД) в оперативную память
     virtual void Load(void);

     // Запись измененного списка областей в дисковый файл, атомарная
     // операция (либо целиком успешна, либо в хранилище останется старый
     // список).
     virtual void Save(void);

     // Удаление описания зоны и сохранение изменения в хранилище.
     virtual void DeleteDomain( int id_zone );

     virtual void ReloadDomain( int id_zone );

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


  } // namespace Search_Engine
 } // namespace Solarix

#endif
