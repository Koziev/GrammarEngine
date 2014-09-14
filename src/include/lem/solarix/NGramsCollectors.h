#if !defined(NGRAMS_COLLECTORS__H) && !defined(SOL_NO_NGRAMS)
#define NGRAMS_COLLECTORS__H
#pragma once

 #include <lem/path.h>
 #include <lem/oformatter.h>
 #include <lem/solarix/dictionary.h>
 #include <lem/solarix/sg_autom.h>
 #include <lem/solarix/la_autom.h>
 #include <lem/solarix/LanguagesEnum.h>
 #include <lem/solarix/se_scan_options.h>
 #include <lem/solarix/file_factory.h>
 #include <lem/mallocator.h>
 #include <lem/solarix/LemmatizatorStorage.h>
 #include <lem/solarix/ngrams_dbms.h>
 
 namespace Solarix
 {

  namespace NGramsCollectorFlags
  { 
   typedef int Flags;
 
   const int Words          = 0x00000001;
   const int Raw2Grams      = 0x00000002;
   const int Raw3Grams      = 0x00000004;
   const int Raw4Grams      = 0x00000008;
   const int Raw5Grams      = 0x00000010;
   const int Covalent2Grams = 0x00000020;

    //! константы задания способа проверки согласованности слов в парах - несогласованные
    //  слова не обрабатываются.
   const int Noun_Noun      = 0x00010000;
   const int Adj_Noun       = 0x00020000;
   const int Noun_Verb      = 0x00040000;
   const int Adverb_Verb    = 0x00080000;
   const int Adverb_Adj     = 0x00100000;
   const int Prepos_Noun    = 0x00200000;
   const int Verb_Object    = 0x00400000;
  }


 class NGrams2Cache : lem::NonCopyable
 {
  public:
   bool echo;

  public:
   NGrams2Cache(void) {}
   virtual ~NGrams2Cache(void) {}
   virtual void Open( const lem::Path &folder, const lem::FString &table )=0;
   virtual void InsertOrUpdate( int i1, int i2, int freq )=0;
   virtual std::pair<int,int> Select( int i1, int i2 )=0;
   virtual void Commit(void)=0;
   virtual void Upload( NGramsDBMS &db, const FString &sql )=0;
   virtual void Print( NGramsDBMS &db, const lem::FString &sql, const lem::FString &format, OFormatter &to )=0;
   virtual void SetBufferSize( int n )=0;
 };


 class NGrams3Cache : lem::NonCopyable
 {
  public:
   bool echo;

  public:
   NGrams3Cache(void) {}
   virtual ~NGrams3Cache(void) {}
   virtual void Open( const lem::Path &folder, const lem::FString &table )=0;
   virtual void InsertOrUpdate( int i1, int i2, int i3, int freq )=0;
   virtual std::pair<int,int> Select( int i1, int i2, int i3 )=0;
   virtual void Commit(void)=0;
   virtual void Upload( NGramsDBMS &db, const FString &sql )=0;
   virtual void Print( NGramsDBMS &db, const lem::FString &sql, const lem::FString &format, OFormatter &to )=0;
   virtual void SetBufferSize( int n )=0;
 };


 class NGrams4Cache : lem::NonCopyable
 {
  public:
   bool echo;

  public:
   NGrams4Cache(void) {}
   virtual ~NGrams4Cache(void) {}
   virtual void Open( const lem::Path &folder, const lem::FString &table )=0;
   virtual void InsertOrUpdate( int i1, int i2, int i3, int i4, int freq )=0;
   virtual std::pair<int,int> Select( int i1, int i2, int i3, int i4 )=0;
   virtual void Commit(void)=0;
   virtual void Upload( NGramsDBMS &db, const FString &sql )=0;
   virtual void Print( NGramsDBMS &db, const lem::FString &sql, const lem::FString &format, OFormatter &to )=0;
   virtual void SetBufferSize( int n )=0;
 };

 class NGrams5Cache : lem::NonCopyable
 {
  public:
   bool echo;

  public:
   NGrams5Cache(void) {}
   virtual ~NGrams5Cache(void) {}
   virtual void Open( const lem::Path &folder, const lem::FString &table )=0;
   virtual void InsertOrUpdate( int i1, int i2, int i3, int i4, int i5, int freq )=0;
   virtual std::pair<int,int> Select( int i1, int i2, int i3, int i4, int i5 )=0;
   virtual void Commit(void)=0;
   virtual void Upload( NGramsDBMS &db, const FString &sql )=0;
   virtual void Print( NGramsDBMS &db, const lem::FString &sql, const lem::FString &format, OFormatter &to )=0;
   virtual void SetBufferSize( int n )=0;
 };


 class RawNGramsCollector;
 class NGramFilter : lem::NonCopyable
 {
  protected:
   NGramFilter(void) {}

  public:
   virtual ~NGramFilter(void) {}

   virtual NGramFilter* Clone(void) const=0;
   virtual void AttachCollector( RawNGramsCollector *collector )=0;

   virtual bool Probe( RawNGramsCollector *collector, int ie1 )=0;
   virtual bool Probe( RawNGramsCollector *collector, int ie1, int ie2 )=0;
   virtual bool Probe( RawNGramsCollector *collector, int ie1, int ie2, int ie3 )=0;
   virtual bool Probe( RawNGramsCollector *collector, int ie1, int ie2, int ie3, int ie4 )=0;
   virtual bool Probe( RawNGramsCollector *collector, int ie1, int ie2, int ie3, int ie4, int ie5 )=0;
 };


 // ********************************************** 
 // Класс для накопления несогласованных N-грамм
 // ********************************************** 
 class RawNGramsCollector
 {
  public:
   lem::Path outdir; // в какой каталог записывать временные файлы

   NGramFilter *filter; // для фильтрации сохраняемых N-грамм

   lem::Ptr<NGramsDBMS> db;
   lem::Ptr<NGrams2Cache> disk_cache2;
   lem::Ptr<NGrams3Cache> disk_cache3;
   lem::Ptr<NGrams4Cache> disk_cache4;
   lem::Ptr<NGrams5Cache> disk_cache5;

   bool use_disk_cache, upload_to_db, print_ngrams;
   lem::zbool clean_database;
   lem::FString print_format; // формат печати (csv,xml и т.п.)
   lem::Ptr<OFormatter> print_file; // в этот поток печатать список n-грамм

   lem::Ptr<Solarix::Dictionary> sol_id;
   Solarix::SynGram *sg;
   Solarix::LexicalAutomat *la;
   lem::Ptr<Solarix::LemmatizatorStorage> lemm;
   

   lem::zbool accum_1grams, accum_2grams, accum_3grams, accum_4grams, accum_5grams;
   lem::zbool needs_WORDS, needs_NGRAM1, needs_NGRAM2, needs_NGRAM3, needs_NGRAM4, needs_NGRAM5;
   lem::zbool segmentation, lemmatization;
   lem::FString segment_n;

  protected:
   lem::FString suffix0; // суффикс для имен таблиц и пр., чтобы отличать таблицы
                         // для разных типов N-грамм 

   lem::FString suffix; // суффикс+номер сегмента

   int FindIE( const lem::UCString &word );

   char asql[512];
   wchar_t sql[512]; // буфер для конструирования SQL-операторов сохранения N-грамм

   lem::MCollect<lem::UCString> sentence_word;

   lem::zint id_word, id1, id2, id3, id4, id5;
   int ie21, ie22;
   int ie31, ie32, ie33;
   int ie41, ie42, ie43, ie44;
   int ie51, ie52, ie53, ie54, ie55;

   lem::zint doc_count;

   bool needs_index_creation1, needs_index_creation2, needs_index_creation3,
        needs_index_creation4, needs_index_creation5;

   // --- КЭШ ТАБЛИЦЫ WORDS ---
   int max_words_cache;
   lem::zbool overload_words;
   lem::zint words_cache_size; // быстрая работа map::size() вызывает сомнения
   std::map< lem::UCString, int /*id_word*/ > words_cache;

   // --- КЭШ ТАБЛИЦЫ NGRAM1 ---
   int max_ngram1_cache;
   lem::zint ngram1_cache_size;
   lem::zbool overload1;
   typedef lem::MAllocator< std::pair<int,int> > NGRAM1_CACHE_ALLOCATOR;
   typedef std::map<
                    int /*iword1*/,
                    int /*id*/,
                    std::less< int >,
                    NGRAM1_CACHE_ALLOCATOR
                  > NGRAM1_CACHE;
   lem::Ptr<NGRAM1_CACHE_ALLOCATOR> ngram1_cache_allocator;
   lem::Ptr<NGRAM1_CACHE> ngram1_cache;

   // --- КЭШ ТАБЛИЦЫ NGRAM1 для одного документа ---
   int max_ngram1_doccache;
   typedef lem::MAllocator< std::pair<int,std::pair<int,int> > > NGRAM1_DOCCACHE_ALLOCATOR;
   typedef std::map<
                    int /*iword1*/,
                    std::pair< int /*id*/, int /*freq*/ >,
                    std::less< int >,
                    NGRAM1_DOCCACHE_ALLOCATOR
                   > NGRAM1_DOCCACHE;
   lem::Ptr<NGRAM1_DOCCACHE_ALLOCATOR> ngram1_doccache_allocator;
   lem::Ptr<NGRAM1_DOCCACHE> ngram1_doccache;


   // --- КЭШ ТАБЛИЦЫ NGRAM2 ---
   int max_ngram2_cache;
   lem::zint ngram2_cache_size;
   lem::zbool overload2; // кэш перегружен - нужно проверять записи и на диске

   typedef lem::MAllocator< std::pair<std::pair<int,int>,int> > NGRAM2_CACHE_ALLOCATOR;

   typedef std::map<
                    std::pair<int /*iword1*/, int /*iword2*/ >,
                    int /*id*/,
                    std::less< std::pair<int,int> >,
                    NGRAM2_CACHE_ALLOCATOR
                  > NGRAM2_CACHE;

   lem::Ptr<NGRAM2_CACHE_ALLOCATOR> ngram2_cache_allocator;
   lem::Ptr<NGRAM2_CACHE> ngram2_cache;

   int Find2Gram( int iword1, int iword2 );

   // --- КЭШ ТАБЛИЦЫ NGRAM2 для одного документа ---
   int max_ngram2_doccache;
   typedef lem::MAllocator< std::pair<std::pair<int,int>,std::pair<int,int> > > NGRAM2_DOCCACHE_ALLOCATOR;
   typedef std::map<
                    std::pair<int /*iword1*/, int /*iword2*/ >,
                    std::pair< int /*id*/, int /*freq*/ >,
                    std::less< std::pair<int,int> >,
                    NGRAM2_DOCCACHE_ALLOCATOR
                   > NGRAM2_DOCCACHE;

   lem::Ptr<NGRAM2_DOCCACHE_ALLOCATOR> ngram2_doccache_allocator;
   lem::Ptr<NGRAM2_DOCCACHE> ngram2_doccache;
      

   // --- КЭШ ТАБЛИЦЫ NGRAM3 ---
   int max_ngram3_cache;
   typedef lem::MAllocator< std::pair<lem::triple<int,int,int>,int> > NGRAM3_CACHE_ALLOCATOR;
   lem::zint ngram3_cache_size;
   lem::zbool overload3; // кэш перегружен - нужно проверять записи и на диске
   typedef std::map<
                    lem::triple<int /*iword1*/, int /*iword2*/, int /*iword3*/ >,
                    int /*id*/,
                    std::less< lem::triple<int /*iword1*/, int /*iword2*/, int /*iword3*/ > >,
                    NGRAM3_CACHE_ALLOCATOR
                  > NGRAM3_CACHE;
   lem::Ptr<NGRAM3_CACHE_ALLOCATOR> ngram3_cache_allocator;
   lem::Ptr<NGRAM3_CACHE> ngram3_cache;

   // --- КЭШ ТАБЛИЦЫ NGRAM3 для одного документа ---
   int max_ngram3_doccache;
   typedef lem::MAllocator< std::pair<lem::triple<int,int,int>,std::pair<int,int> > > NGRAM3_DOCCACHE_ALLOCATOR;
   typedef std::map<
                    lem::triple<int /*iword1*/, int /*iword2*/, int /*iword3*/ >,
                    std::pair< int /*id*/, int /*freq*/ >,
                    std::less< lem::triple<int /*iword1*/, int /*iword2*/, int /*iword3*/ > >,
                    NGRAM3_DOCCACHE_ALLOCATOR
                  > NGRAM3_DOCCACHE;
   lem::Ptr<NGRAM3_DOCCACHE_ALLOCATOR> ngram3_doccache_allocator;
   lem::Ptr<NGRAM3_DOCCACHE> ngram3_doccache;


   // --- КЭШ ТАБЛИЦЫ NGRAM4 ---
   int max_ngram4_cache;
   typedef lem::MAllocator< std::pair<lem::foursome<int,int,int,int>,int> > NGRAM4_CACHE_ALLOCATOR;
   lem::zint ngram4_cache_size;
   lem::zbool overload4; // кэш перегружен - нужно проверять записи и на диске
   typedef std::map<
                    lem::foursome<int /*iword1*/, int /*iword2*/, int /*iword3*/, int /*iword4*/ >,
                    int /*id*/,
                    std::less< lem::foursome<int /*iword1*/, int /*iword2*/, int /*iword3*/, int /*iword4*/ > >,
                    NGRAM4_CACHE_ALLOCATOR
                  > NGRAM4_CACHE;
   lem::Ptr<NGRAM4_CACHE_ALLOCATOR> ngram4_cache_allocator;
   lem::Ptr<NGRAM4_CACHE> ngram4_cache;

   // --- КЭШ ТАБЛИЦЫ NGRAM4 для одного документа ---
   int max_ngram4_doccache;
   typedef lem::MAllocator< std::pair<lem::foursome<int,int,int,int>,std::pair<int,int> > > NGRAM4_DOCCACHE_ALLOCATOR;
   typedef std::map<
                    lem::foursome<int /*iword1*/, int /*iword2*/, int /*iword3*/, int /*iword4*/ >,
                    std::pair< int /*id*/, int /*freq*/ >,
                    std::less< lem::foursome<int /*iword1*/, int /*iword2*/, int /*iword3*/, int /*iword4*/ > >,
                    NGRAM4_DOCCACHE_ALLOCATOR
                  > NGRAM4_DOCCACHE;
   lem::Ptr<NGRAM4_DOCCACHE_ALLOCATOR> ngram4_doccache_allocator;
   lem::Ptr<NGRAM4_DOCCACHE> ngram4_doccache;



   // --- КЭШ ТАБЛИЦЫ NGRAM5 ---
   int max_ngram5_cache;
   typedef lem::MAllocator< std::pair<lem::tuple5<int,int,int,int,int>,int> > NGRAM5_CACHE_ALLOCATOR;
   lem::zint ngram5_cache_size;
   lem::zbool overload5; // кэш перегружен - нужно проверять записи и на диске
   typedef std::map<
                    lem::tuple5<int /*iword1*/, int /*iword2*/, int /*iword3*/, int /*iword4*/, int /*iword5*/ >,
                    int /*id*/,
                    std::less< lem::tuple5<int /*iword1*/, int /*iword2*/, int /*iword3*/, int /*iword4*/, int /*iword5*/ > >,
                    NGRAM5_CACHE_ALLOCATOR
                  > NGRAM5_CACHE;
   lem::Ptr<NGRAM5_CACHE_ALLOCATOR> ngram5_cache_allocator;
   lem::Ptr<NGRAM5_CACHE> ngram5_cache;

   // --- КЭШ ТАБЛИЦЫ NGRAM5 для одного документа ---
   int max_ngram5_doccache;
   typedef lem::MAllocator< std::pair<lem::tuple5<int,int,int,int,int>,std::pair<int,int> > > NGRAM5_DOCCACHE_ALLOCATOR;
   typedef std::map<
                    lem::tuple5<int /*iword1*/, int /*iword2*/, int /*iword3*/, int /*iword4*/, int /*iword5*/ >,
                    std::pair< int /*id*/, int /*freq*/ >,
                    std::less< lem::tuple5<int /*iword1*/, int /*iword2*/, int /*iword3*/, int /*iword4*/, int /*iword5*/ > >,
                    NGRAM5_DOCCACHE_ALLOCATOR
                  > NGRAM5_DOCCACHE;
   lem::Ptr<NGRAM5_DOCCACHE_ALLOCATOR> ngram5_doccache_allocator;
   lem::Ptr<NGRAM5_DOCCACHE> ngram5_doccache;





   lem::MCollect< std::pair< int /*NGRAM1.id*/, int /*plus_w*/ > > Update1Gram;
   lem::MCollect< std::pair< int /*NGRAM2.id*/, int /*plus_w*/ > > Update2Gram;
   lem::MCollect< std::pair< int /*NGRAM2.id*/, int /*plus_w*/ > > Update3Gram;
   lem::MCollect< std::pair< int /*NGRAM2.id*/, int /*plus_w*/ > > Update4Gram;
   lem::MCollect< std::pair< int /*NGRAM2.id*/, int /*plus_w*/ > > Update5Gram;


   wchar_t usql_buf[1024];
   char asql_buf[1024];

   virtual void PresetTablesSuffix(void);


   lem::MCollect<lem::UCString> delims;
   void Push( int id_word );
   void PurgeDocCache( bool echo );
   void PurgeDocCache1( bool echo );
   void PurgeDocCache2( bool echo );
   void PurgeDocCache3( bool echo );
   void PurgeDocCache4( bool echo );
   void PurgeDocCache5( bool echo );
   int NormalizeAndRegisterWord( const UCString &l );
   void Store1Gram( int ie11, int freq );
   void Store2Gram( int ie21, int ie22, int freq );
   void Store3Gram( int ie31, int ie32, int ie33, int freq );
   void Store4Gram( int ie41, int ie42, int ie43, int ie44, int freq );
   void Store5Gram( int ie51, int ie52, int ie53, int ie54, int ie55, int freq );
   void CreateIndeces( bool echo );
   void CreateIndeces1( bool echo );
   void CreateIndeces2( bool echo );
   void CreateIndeces3( bool echo );
   void CreateIndeces4( bool echo );
   void CreateIndeces5( bool echo );

   virtual void ProcessSentence( const lem::MCollect<UCString> &sent );
   virtual void ProcessSingleWord( const UCString &l );


  public:
   RawNGramsCollector(void);
   virtual ~RawNGramsCollector(void);

   virtual void Prepare(
                        lem::Ptr<Solarix::Dictionary> dict,
                        const lem::Path &_outdir,
                        Language _language
                       );


   virtual void SetDocCacheCapacity( int n );
   virtual void SetNGramsCacheCapacity( int n );

   virtual void Process( const UCString &l );
   virtual void Report(void);
   virtual void EraseFreq1(void);
   virtual void Merge( const lem::Path &dbfile, bool echo );
   virtual void ProcessFinalStat( bool echo );

   virtual void BeginDocument( bool echo );
   virtual void EndDocument( bool echo );
   virtual void EndAll( bool echo );

   virtual void StoreNGram( const UFString &a, const UFString &b, int freq );
   virtual void StoreNGram( const UFString &a, const UFString &b, const UFString &c, int freq );
   virtual void StoreNGram( const UFString &a, const UFString &b, const UFString &c, const UFString &d, int freq );
   virtual void StoreNGram( const UFString &a, const UFString &b, const UFString &c, const UFString &d, const UFString &e, int freq );
   virtual void InternalFlush( bool echo );

   const UCString& IE_2_Word( int ie ) const;

   int RegisterWord( const lem::UCString &word );
   void SetFilter( NGramFilter *filter );
 };





 class CovalentNGramsCollector : public RawNGramsCollector
 {
  private:
   lem::MCollect<lem::UCString> sentence_word;

   NGramsCollectorFlags::Flags correl;
   Language language;
   lem::zint distance; // на каком макс. расстоянии искать пары
   lem::zbool add_reverse_links; // суммировать обратные связи
   lem::MCollect<int> stopadvs_ru, stopverbs_ru, stopverbs_en, stopadjs_ru, stopadjs_en, stopadvs_en;

   int IE_2_IClass( int ie ) const;

   void Consider2Gram(
                      int ie_prev,
                      int iclass_prev,
                      const UCString &word_prev,
                      int ie,
                      int iclass,
                      const UCString &word
                     );

   void Consider3Gram(
                      int ie_prev,
                      int iclass_prev,
                      const UCString &word_prev,
                      int ie_0,
                      int iclass_0,
                      const UCString &word_0,
                      int ie,
                      int iclass,
                      const UCString &word
                     );

   int ToVerb( int ie_inf );

   virtual void ProcessSentence( const lem::MCollect<UCString> &sent );
   virtual void PresetTablesSuffix(void);

  public:
   CovalentNGramsCollector( NGramsCollectorFlags::Flags _correl );

   virtual void Prepare(
                        lem::Ptr<Solarix::Dictionary> dict,
                        const lem::Path &_outdir,
                        Language _language
                       );

   virtual void EndDocument( bool echo );
   virtual void Merge( const lem::Path &dbfile, bool echo  );
   virtual void EndAll( bool echo );
 };


 

 class NGramsCollectors
 {
  private:
   lem::Ptr<NGramsDBMS> db;
   lem::Ptr<LemmatizatorStorage> lemm;

   wchar_t usql_buf[1024];
   char asql_buf[1024];

   lem::Ptr<Solarix::Dictionary> dict;
   lem::PtrCollect<RawNGramsCollector> ngrams; // Специализированные накопители
   Solarix::NGramsCollectorFlags::Flags flags;
   Language language;
   lem::Path outdir;
   lem::zbool erase_freq1;
   lem::zbool clean_database;

  public:
   NGramsCollectors( lem::Ptr<Solarix::Dictionary> _dict, lem::Ptr<LemmatizatorStorage> _lemm );
   ~NGramsCollectors(void);

   void SetStorage( lem::Ptr<NGramsDBMS> _db );

   void Prepare(
                const lem::Path &_outdir,
                Language _language,
                Solarix::NGramsCollectorFlags::Flags _flags,
                bool do_erase_freq1,
                bool do_segmentation,
                bool do_lemmatization,
                bool use_disk_cache,
                bool upload_to_db,
                const lem::FString &segment_n,
                bool cleanup_database=false
               );

   void SetFilter( NGramFilter *filter );

   virtual void SetDocCacheCapacity( int n );
   virtual void SetNGramsCacheCapacity( int n );
   virtual void SetDBCache( int cache_size );

   void PrintNgrams( const FString &format, lem::Ptr<OFormatter> to );

   void Process( const UCString &l );

   void StoreNGram( const UFString &a, const UFString &b, int freq );
   void StoreNGram( const UFString &a, const UFString &b, const UFString &c, int freq );
   void InternalFlush( bool echo );

   void BeginDocument( bool echo );
   void EndDocument( bool echo );
   void EndAll( bool echo );
   void Report(void);
   void Merge( const lem::Path &folder, bool echo  );

   void BuildKnowledgeBase(
                           Solarix::Search_Engine::File_Type_Detector& detector,
                           const Solarix::Search_Engine::Scan_Options& scanning,
                           const lem::Path &DocumentsFolder,
                           const lem::Path &DestinationFolder,
                           Solarix::Language language,
                           bool echo  
                          );
 };


 } // namespace Solarix


#endif
