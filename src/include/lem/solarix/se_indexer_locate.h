// CD->05.10.2007
// LC->08.10.2008

#ifndef IDX_INDEXER_LOCATE__H
#define IDX_INDEXER_LOCATE__H
#pragma once

 #if defined FAIND_INDEXER_LOCATE

 #include <lem/solarix/se_indexer.h>


 namespace Solarix
 {

  namespace Search_Engine
  {
   class DocumentIteratorLocate : public DocumentIterator
   {
    private:
     int count;

    public:
     DocumentIteratorLocate( int n ) : count(n) {}

     virtual int Size(void) const;
     virtual int GetDocId( int i ) const;
   };

   struct IndexerLocate
   {
    enum { MaxPathLen=lem::Path::MaxLen+4096 };
    enum { MaxSegments=1023 };
   };

   
   struct LocateSegment
   {
    lem::uint32_t flags;
    lem::int32_t id;

    LocateSegment(void):flags(0), id(0) {}
   };

   struct LocateSection
   {
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif

    lem::uint32_t id_seq;
    boost::posix_time::ptime created;
    lem::MCollect<LocateSegment> segments;

    LocateSection(void);
    
    LocateSegment& AddSegment(void);
    void SaveBin( lem::Stream &to ) const;
    void LoadBin( lem::Stream &to );
   };




   // Вспомогательный класс для Writer'а и Updater'а
   class IndexerLocateHelper
   {
    public:
     Storage storage; // все файлы хранилища
     lem::int32_t trans_id;

    private:
     bool mt; // многопоточный режим
     lem::Collect< lem::Path > folders; // какие папки надо индексировать (рекурсивно или нет)
     lem::MCollect<bool> recursive;

    public:
     IndexerLocateHelper(void);

     void SingleThreaded(void);

     void SetTransactionId( lem::int32_t id );

     void PrepareScanDomain(
                            const Indexer_Operation &Operation,
                            const Crawler_Operation &engine_command
                           );

     void Run( Hit_Statistics &stat );
   };



   class IndexWriterLocate : public Indexer
   {
    private:
     lem::int32_t trans_id;
     IndexerLocateHelper helper;
     lem::PtrCollect<lem::Path> to_del;


     void SaveZoneStatus(void);

    public:
     IndexWriterLocate(
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

     virtual ~IndexWriterLocate(void);

     virtual bool DoesSupportMorphology(void) const;
     virtual void AddDocument( const File_Location &filename, Base_File_Reader *reader );

     virtual bool IsActiveWriter(void) const;
     virtual void Run( Solarix::Search_Engine::Hit_Statistics &stat );
   };


   #if defined LEM_WINDOWS
    #define LOCATE_USE_HASH_FILELIST
   #endif

   #if defined LOCATE_USE_HASH_FILELIST

   enum { LOCATE_HASH_NSECTION=8192 };


   typedef lem::uint16_t LocateHash; // тип для хранения хэша файлового пути

   struct QueueItem
   {
    wchar_t p[ lem::Path::MaxLen+1 ];
    int ifile; // индекс описателя файла в основном списке сегмента

    QueueItem(void);
    QueueItem( const wchar_t *s, int file_index );
    QueueItem( const QueueItem &x );
    void operator=( const QueueItem &x );
   };

   struct SegmentSearcher
   {
    UFString prefix;
    int prefix_len;

    int icur;
    int count;
    lem::BinaryReader *rdr;
    wchar_t filename[ lem::Path::MaxLen+1 ];

    SegmentSearcher( const UFString &prf );
    
    std::pair<int,const wchar_t*> Next(void);    
    
   };

   extern LocateHash CalcPathHash( const wchar_t *p );



   #endif


   struct LocateSegmentHandler
   {
    lem::Path db_folder;

    int isegment, trans_id;
    int ibeg, iend; // индексы документов в данном сегменте
    int count; // общее кол-во записей о файлах в базе сегмента
    lem::Ptr<lem::FastFileReader> db;
    lem::Stream::pos_type db_start; // позиция в db для фактического начала записей о файлах (пропуск служебного заголовка и резерва)
    lem::MCollect<lem::Stream::pos_type> record_poses; // загруженные позиции описателей файлов

    lem::zbool prefix_search_prepared;
    lem::Stream::pos64_type section_pos[LOCATE_HASH_NSECTION];
    int section_count[LOCATE_HASH_NSECTION];
    lem::Ptr<lem::BinaryReader> section_stream;
 
    LocateSegmentHandler( lem::Path &folder );

    inline bool MatchDocumentIndex( int idoc ) const { return idoc>=ibeg && idoc<iend; }
    inline int Global2LocalIndex( int idoc ) const
    {
     LEM_CHECKIT_Z( MatchDocumentIndex(idoc) );
     return idoc-ibeg;
    }

    void InitPrefixSearch(void);

    SegmentSearcher* SearchByPrefix( const wchar_t *filename );
   };


   class IndexReaderLocate : public Indexer
   {
    private:
     lem::int32_t trans_id;
     Storage storage; // все файлы хранилища

     lem::PtrCollect<LocateSegmentHandler> hsegments; 
     int total_count;

     int maxhitcount;

     Assoc_Files* GetAssocFiles(
                                LocateSegmentHandler &segment,
                                const UFString &pattern,
                                const Pattern *query_pattern,
                                lem::Process::InterlockedInt *hitcount
                               );

     #if defined LEM_THREADS
     static LEM_THREADADR LocateThread( void *_params );
     #endif  

    public:
     IndexReaderLocate(
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

     virtual ~IndexReaderLocate(void);

     virtual bool DoesSupportMorphology(void) const;

     virtual FString GetEngineName(void) const;

     virtual int CountDocuments(void);
     virtual int CountKeywords(void);

     virtual void FinishPrefetchingKeywords(void);
     virtual Assoc_Files* GetAllFiles(void);
     virtual Assoc_Files* GetAssocFiles( int super_index );

     virtual Assoc_Files* GetAssocFiles( const Pattern &pattern );

     virtual boost::shared_ptr<File_Entry> GetDocumentById( int id_doc );
     virtual boost::shared_ptr<File_Entry> GetDocumentByIndex( int idoc );
     virtual int GetDocumentId( int idoc );
     virtual Zone_Statistics GetZoneStat(void);

     virtual void PrefetchKeyword( const UCString &Word );
     virtual void PreparePrefetchingKeywords(void);
     virtual void PrintInfo( OFormatter &out, bool detailed );

     virtual bool IsActiveSearcher( const Pattern &pattern ) const;
     virtual bool SupportFulltextSearch(void) const;
     virtual bool SupportSolarixKeywordsDictionary(void) const;
     virtual bool NeedsExternalFilesearch(void) const;
   };

  }

 }

#endif

#endif
