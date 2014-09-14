// -----------------------------------------------------------------------------
// File SE_CATALOGUER_RAM.H
//
// (c) 2008 by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// 06.10.2008 - объ€вление класса Idb_List_Ram вынесено из se_indexer.h в
//              данный файл в ходе рефакторинга проекта. 
// -----------------------------------------------------------------------------
//
// CD->06.10.2008
// LC->26.09.2009
// --------------

#if !defined SE_CATALOGUER_RAM__H && defined FAIND_IDBLIST_RAM
 #define SE_CATALOGUER_RAM__H
#pragma once

 #include <lem/solarix/se_indexer.h>
 
 namespace Solarix
 {
  namespace Search_Engine
  { 
   // *****************************************************************
   // —пециализаци€ каталогизатора дл€ хранени€ в только в оперативке,
   // дл€ использовани€ в поисковой системе с CD.
   // *****************************************************************
   class Idb_List_Ram : public Idb_List
   {  
    public:
     Idb_List_Ram( const Indexer_Options *Flags );
     virtual ~Idb_List_Ram(void);

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
     virtual void SetNeedsDictionary( const UFString &Domain_Name, bool Flag );
     virtual void Load(void);
     virtual void Save(void);
     virtual void DeleteDomain( int id_zone );
     virtual void PurgeDomain( int id_zone );
     virtual void Rename( int iZone, const UFString &new_name );
     virtual void SetComment( int iZone, const UFString &Comment );
     virtual void Share( int id_zone, bool shared );
     virtual void SaveNeedsRefreshFlag( int id_zone );
     virtual void DeleteAllIndexes(void);
     virtual bool IsEmptyDomain( int id_zone );
     virtual void BackupDomainsList( const lem::Path &dest_folder );
     virtual void RestoreDomainsList( const lem::Path &dest_folder );
     virtual void BackupDomain( const UFString &domain_name, const lem::Path &dest_folder );
     virtual void RestoreDomain( const UFString &domain_name, const lem::Path &dest_folder );
     virtual bool LockByReader( int id_index );
     virtual bool LockByWriter( int id_index );
     virtual bool IsLockedByReader( int id_index );
     virtual bool IsLockedByWriter( int id_index );
     virtual void UnlockByReader( int id_index );
     virtual void UnlockByWriter( int id_index );
     virtual void UnlockAll(void);
     virtual void ReloadDomain( int id );
   };

  } // namespace Search_Engine
 } // namespace Solarix

#endif
