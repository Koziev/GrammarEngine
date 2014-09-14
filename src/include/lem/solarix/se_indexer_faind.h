#ifndef IDX_INDEXER_FAIND__H
#define IDX_INDEXER_FAIND__H
#pragma once

 #if defined FAIND_INDEXER_FILEDB

 #include <lem/solarix/se_indexer.h>


 namespace Solarix
 {

  namespace Search_Engine
  {
   typedef Indexer IndexerFaind;


   class DocumentIteratorFaind : public DocumentIterator
   {
    private:
     int count;

    public:
     DocumentIteratorFaind( int n ) : count(n) {}  

     virtual int Size(void) const;
     virtual int GetDocId( int i ) const;
   };


   class IndexWriterFaind : public IndexerFaind
   {
    private:
     DocumentsList documents; // Список проиндексированных документов
     Storage storage;                // все файлы хранилища

     lem::Ptr<lem::BinaryFile> doc_writer;    // поток для записи описателей документов при индексировании
     lem::Ptr<lem::BinaryFile> docpos_writer; // поток для записи позиций описателей документов при индексировании
     int document_counter; // счетчик проиндексированных документов.

     lem::Ptr<File_Entry> writer_file_entry;

    private:
     Assoc_Hash_Array assoc_hashes; // Связь ключевых слов и документов
     Zone_Proximity zone_prox; // Матрица близости слов

     // В этом векторе в ходе индексирования статической зоны накапливаются
     // позиции блоков подокументных данных во временном файле
     std::vector<Stream::pos64_type> tmp_doc_pos;

     // индекс имени текущего файла БД в списке stor_files
     lem::zeroed<int> i_indeces_stream; 

     // Файл для сохранения индексов
     boost::shared_ptr<lem::BinaryFile> indeces_stream; 

     // временный файл для сохранения данных по ходу индексирования
     // он будет удален сразу после завершения индексирования.
     boost::shared_ptr<lem::BinaryFile> tmp_stream;

     // Вектор используется в ходе индексирования статической зоны для сохранения
     // позиций во временном потоке для подокументных индексов
     lem::MCollect< std::pair< DocIndex /* indexed_file[] */, Stream::pos64_type > > doc_keywords_tmp;

     // рабочая матрица для индексации - используется для построения списков
     // ассоциированных с ключевыми словами файлов (последний этап построения индекса)
     typedef std::map< Index_Entry, lem::MCollect<DocIndex>* > ASSOC_WORK;
     typedef ASSOC_WORK::iterator AW_ITER; 

     void DeleteTmpStream(void);

     BinaryFile* GetCurrentStream(void);
     inline int GetCurrentStreamIndex(void) const { return i_indeces_stream; }

     BinaryFile* GetCurrentTmpStream(void);
     void ReadingTmpStream(void);

     Assoc_Files* CreateAssocFiles( int super_index );
     Assoc_Files* CreateAssocFilesHandles( int super_index );

     void CreateStaticAssoc(void);
     //void CreateDynamicAssoc(void) ;
     void FinishCreateAssoc( ASSOC_WORK &assoc_work );
     void BuildAssocForDocument( const File_Entry *entry );
     void BuildZoneProx(void);
     Document_Index* CreateDocIndex(void) const;

     void Load( File_Entry* pfile );

     virtual void SaveZoneStatus(void);

    public:
     IndexWriterFaind(
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

     virtual ~IndexWriterFaind(void);

     virtual bool DoesSupportMorphology(void) const;
     virtual void AddDocument( const File_Location &filename, Base_File_Reader *reader );
   };



   class IndexReaderFaind : public IndexerFaind
   {
    private:
     lem::MCollect<lem::Stream::pos64_type> docspos;
     lem::PtrCollect<File_Entry> docs_cache; // подгружаемый с диска кэш описателей документов
     lem::Ptr<lem::BinaryFile> docs_file; // открытый поток для подгрузки описателей документов
     
     DocumentsList documents; // Список проиндексированных документов
     Storage storage;         // все файлы хранилища

     void DeleteTmpStream(void);

     void LoadStorage(void);
     bool LoadStatus( bool do_throw=false );
     void LoadProxMatrix( lem::Stream& bin );
     void LoadKeywords(void);
     bool LoadAssocHashes(void);
     void LoadProxMatrix(void);
     void LoadDocuments(void);

     // Все списки для загруженного в память индекса очищаются.
     virtual void ClearLists(void);

     Assoc_Hash_Array assoc_hashes; // Связь ключевых слов и документов
     Zone_Proximity zone_prox; // Матрица близости слов
                                  
     // поток чтения из матрицы зоны
     boost::shared_ptr<lem::BinaryFile> zone_mtx; 

     // поток для подгрузки подгрупп ключевых слов
     boost::shared_ptr<Stream> prefetch_stream; 

     void Load(void);

     virtual bool FindIndex(
                            const File_Location &loc,
                            File_Entry **entry,
                            bool &broken,
                            bool do_load=true
                           );

     virtual bool LoadDocumentIndex( File_Entry *x );


    public:
     IndexReaderFaind(
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

     virtual ~IndexReaderFaind(void);

     virtual bool DoesSupportMorphology(void) const;

     virtual FString GetEngineName(void) const;

     virtual int CountDocuments(void);
     virtual int CountKeywords(void);
     virtual void DumpHTML( const lem::Path &filename );
     virtual void DumpCSV( const lem::Path &filename );
     virtual void DumpTXT( const lem::Path &filename );

     virtual void FinishPrefetchingKeywords(void);
     virtual Assoc_Files* GetAllFiles(void);
     virtual Assoc_Files* GetAssocFiles( int super_index1, int super_index2, const Pattern &pattern );
     virtual Assoc_Files* GetAssocFiles( int super_index, const Pattern &pattern );
     virtual boost::shared_ptr<File_Entry> GetDocumentById( int id_doc );
     virtual boost::shared_ptr<File_Entry> GetDocumentByIndex( int idoc );
     virtual int GetDocumentId( int idoc );
     virtual Zone_Statistics GetZoneStat(void);

     #if defined FAIND_DATAMINE
     virtual boost::shared_ptr<Doc_Topic> LoadDocumentTopic( int i_file );
     #endif

     virtual void PrefetchKeyword( const UCString &Word );
     virtual void PreparePrefetchingKeywords(void);
     virtual void PrintInfo( OFormatter &out, bool detailed );
     virtual ProximityMatrixProber* GetProximityMatrixProber( const File_Entry *file_entry );
   };


   class IndexReaderNoIndex : public IndexerFaind
   {
    private:
     virtual void ClearLists(void);
     virtual bool FindIndex(
                            const File_Location &loc,
                            File_Entry **entry,
                            bool &broken,
                            bool do_load=true
                           );

     virtual bool LoadDocumentIndex( File_Entry *x );


    public:
     IndexReaderNoIndex(
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

     virtual ~IndexReaderNoIndex(void);

     virtual bool DoesSupportMorphology(void) const;

     virtual FString GetEngineName(void) const;

     virtual int CountDocuments(void);
     virtual int CountKeywords(void);
     virtual void DumpHTML( const lem::Path &filename );
     virtual void DumpCSV( const lem::Path &filename );
     virtual void DumpTXT( const lem::Path &filename );

     virtual void FinishPrefetchingKeywords(void);
     virtual Assoc_Files* GetAllFiles(void);
     virtual Assoc_Files* GetAssocFiles( int super_index1, int super_index2, const Pattern &pattern );
     virtual Assoc_Files* GetAssocFiles( int super_index, const Pattern &pattern );
     virtual boost::shared_ptr<File_Entry> GetDocumentById( int id_doc );
     virtual boost::shared_ptr<File_Entry> GetDocumentByIndex( int idoc );
     virtual int GetDocumentId( int idoc );
     virtual Zone_Statistics GetZoneStat(void);

     #if defined FAIND_DATAMINE
     virtual boost::shared_ptr<Doc_Topic> LoadDocumentTopic( int i_file );
     #endif

     virtual void PrefetchKeyword( const UCString &Word );
     virtual void PreparePrefetchingKeywords(void);
     virtual void PrintInfo( OFormatter &out, bool detailed );
     virtual ProximityMatrixProber* GetProximityMatrixProber( const File_Entry *file_entry );
   };

  }

 }

#endif

#endif
