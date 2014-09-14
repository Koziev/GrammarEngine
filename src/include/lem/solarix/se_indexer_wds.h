#ifndef IDX_INDEXER_WDS__H
#define IDX_INDEXER_WDS__H
#pragma once

 #if defined FAIND_INDEXER_WDS

 #define OLEDBVER 0x250
 #if defined LEM_MFC
  #include <afxwin.h>
 #else 
  #include <windows.h>
 #endif
 #include <ole2.h>
 #include <oledb.h>

 #include <ntquery.h>
 #include <atldbcli.h>

 #include <lem/solarix/se_text.h>
 #include <lem/solarix/se_crawler_operation.h>
 #include <lem/solarix/se_indexer_active_reader.h>

 namespace Solarix
 {

  namespace Search_Engine
  {
  
   class DocumentIteratorWDS : public DocumentIterator
   {
    private:
     std::auto_ptr<Assoc_Files> files;

    public:
     DocumentIteratorWDS( Assoc_Files *_files ) : files(_files) {}
     virtual ~DocumentIteratorWDS(void) {}

     virtual int Size(void) const;
     virtual int GetDocId( int i ) const;
   };
  


   class IndexWriterWDS : public Indexer
   {
    private:

    public:
     IndexWriterWDS(
                    IndexManager *Manager,
                    const Domain_Info &Domain_info,
                    Solarix::Dictionary *ptrDict,
                    const LD_Seeker *seeker,
                    const Echo_Options *Echo,
                    const General_Options *Generals
                   );

     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );

     virtual void Commit(void);

     virtual ~IndexWriterWDS(void);

     virtual void AddDocument( const File_Location &filename, Base_File_Reader *reader );

     virtual bool DoesSupportMorphology(void) const;
     virtual bool IsActiveWriter(void) const;
     virtual void Run( Solarix::Search_Engine::Hit_Statistics &stat );
   };



   class IndexUpdaterWDS : public Indexer
   {
    private:

    public:
     IndexUpdaterWDS(
                     IndexManager *Manager,
                     const Domain_Info &Domain_info,
                     Solarix::Dictionary *ptrDict,
                     const LD_Seeker *seeker,
                     const Echo_Options *Echo,
                     const General_Options *Generals
                    );

     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );

     virtual void Commit(void);

     virtual ~IndexUpdaterWDS(void);

     virtual bool IsFileChanged( const File_Location &filename );
     virtual void AddDocument( const File_Location &filename, Base_File_Reader *reader );
     virtual bool DoesSupportMorphology(void) const;
     virtual bool IsActiveWriter(void) const;
     virtual void Run( Solarix::Search_Engine::Hit_Statistics &stat );
   };

  
   class IndexReaderWDS : public IndexActiveReader
   {
    private:
     lem::zbool connected;
     CDataSource cDataSource;
     CSession cSession;
     enum SyntaxType { VistaSQL, XPSP2SQL };
     SyntaxType sql_syntax;

     virtual Assoc_Files* GetAssocFilesForPhrase( const lem::UFString &phrase, int distance, int maxhitcount, const Pattern &pattern );
     virtual Assoc_Files* GetAssocFiles( const UCString &word, bool Prefix, int maxhitcount, const Pattern &pattern ); // поиск по одному слову
     virtual Assoc_Files* GetAssocFiles( const MCollect<UCString> &words, int maxhitcount, const Pattern &pattern ); // поиск по альтернативным словам (OR)

     Assoc_Files* ExecuteSQL( const lem::UFString& query_sql, int maxhitcount );

     virtual bool CanPerformActiveFilesearch( const Pattern &pattern ) const;
     virtual Assoc_Files* PerformActiveFilesearch( const Pattern &pattern );
     virtual bool NeedsExternalFilesearch(void) const;

    public:
     IndexReaderWDS(
                    IndexManager *Manager,
                    const Domain_Info &Domain_info,
                    Solarix::Dictionary *ptrDict,
                    const LD_Seeker *seeker,
                    const Echo_Options *Echo,
                    const General_Options *Generals
                   );

     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );

     virtual void Commit(void);

     virtual ~IndexReaderWDS(void);

     virtual Zone_Statistics GetZoneStat(void);
  
     virtual int CountDocuments(void);

     virtual void LoadDocuments(void);
     virtual boost::shared_ptr<File_Entry> GetDocumentByIndex( int idoc );
     virtual boost::shared_ptr<File_Entry> GetDocumentById( int id_doc );

     virtual Assoc_Files* GetAllFiles(void);

     virtual FString GetEngineName(void) const;
     
     virtual void PrintInfo( OFormatter &out, bool detailed=false );
     virtual bool DoesSupportMorphology(void) const;
   };

  }
 }


#endif

#endif
