#ifndef SOL_NGRAMS__H
#define SOL_NGRAMS__H
#pragma once

 #if !defined SOL_NO_NGRAMS

 #include <lem/smart_pointers.h>
 #include <lem/config.h>
 #include <lem/tuple.h>
 #include <lem/process.h>
 #include <map>
 #include <lem/path.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/solarix/ngrams_dbms.h>

 namespace Solarix
 {
  class Dictionary;
  class NGramHandler;

  // ***************************************************
  // статистический справочник корреляций слов (N-грамм)
  // ***************************************************
  class Ngrams
  {
   private:
    typedef std::map< int /*ientry*/, lem::MCollect<std::pair<int/*ientry*/,float> >* > digram_type;

    digram_type a_n;   // прилагательное+существительное
    digram_type n_a;   // существительные для прилагательного (обратная к a_n)   

    digram_type n_v;   // существительное+глагол
    digram_type v_n;   // глагол+существительное

    digram_type n_n;   // существительное+существительное

    digram_type adv_a; // наречие+прилагательное
    digram_type a_adv; // прилагательное+наречие

    digram_type adv_v; // наречие+глагол
    digram_type v_adv; // глагол+наречие

    digram_type n_p; // обращенная таблица предлог+существительное
    digram_type p_n;

    digram_type v_obj; // глагол+управляемый_объект
    digram_type obj_v;

    void Delete( Ngrams::digram_type &table ) const;

    #if defined SOL_CAA
    void GenerateReverse( const Ngrams::digram_type &src, Ngrams::digram_type &dst );
    void Add( Ngrams::digram_type &table, int ie1, int ie2, float v );
    void Normalize( lem::UCString &word ) const;
    #endif

   private:
    Solarix::Dictionary *dict;
    lem::Ptr<NGramsDBMS> db;

    #if defined LEM_MSC
     __declspec(align(4))
    #endif
    struct Cached2Gram
    {
     std::pair<int,int> ngram;
     lem::int32_t id;
     lem::int32_t w;

     Cached2Gram(void) : ngram(-1,-1), id(UNKNOWN), w(0) {}

     inline bool operator==( const Cached2Gram &q ) const
     { return ngram==q.ngram; }
    };

    #if defined LEM_MSC
     __declspec(align(4))
    #endif
    struct Cached3Gram
    {
     lem::triple<int,int,int> ngram;
     lem::int32_t id;
     lem::int32_t w;

     Cached3Gram(void) : ngram(-1,-1,-1), id(UNKNOWN), w(0) {}

//     inline bool operator<( const Cached3Gram &g ) const
//     { return ngram<g.ngram; }

     inline bool operator==( const Cached3Gram &g ) const
     { return ngram==g.ngram; }
    };


    #if defined LEM_MSC
     __declspec(align(4))
    #endif
    struct Cached4Gram
    {
     lem::foursome<int,int,int,int> ngram;
     lem::int32_t id;
     lem::int32_t w;

     Cached4Gram(void) : ngram(-1,-1,-1,-1), id(UNKNOWN), w(0) {}

     inline bool operator==( const Cached4Gram &g ) const
     { return ngram==g.ngram; }
    };


    #if defined LEM_MSC
     __declspec(align(4))
    #endif
    struct Cached5Gram
    {
     lem::tuple5<int,int,int,int,int> ngram;
     lem::int32_t id;
     lem::int32_t w;

     Cached5Gram(void) : ngram(-1,-1,-1,-1,-1), id(UNKNOWN), w(0) {}

     inline bool operator==( const Cached5Gram &g ) const
     { return ngram==g.ngram; }
    };


    struct raw;


    struct Cache2
    {
     lem::int64_t n;
     lem::int32_t max_freq;
     lem::Ptr<lem::BinaryReader> bin;
     lem::uint64_t *marks_filepos;
     lem::uint32_t *marks_n;
     int n_marks;
     Cached2Gram *search_buffer;

     Cache2(void):n(0),max_freq(0),marks_filepos(NULL),marks_n(NULL),n_marks(0),search_buffer(NULL) {}
     ~Cache2(void);

     std::pair<int,int> find( int x, int y ) const;
     lem::int64_t size(void) const { return n; }
     bool empty(void) const { return n==0; }

     lem::int64_t LoadBin( const lem::Path &p );

     void ForEach( Ngrams *n, const lem::FString &db_suffix, const lem::FString &segment_name, Ngrams::raw *r, NGramHandler *handler );
    };


    struct Cache3
    {
     lem::int64_t n;
     lem::int32_t max_freq;
     lem::Ptr<lem::BinaryReader> bin;
     lem::uint64_t *marks_filepos;
     lem::uint32_t *marks_n;
     int n_marks;
     Cached3Gram *search_buffer;

     Cache3(void):n(0),max_freq(0),marks_filepos(NULL),marks_n(NULL),n_marks(0),search_buffer(NULL) {}
     ~Cache3(void);

     std::pair<int,int> find( int x, int y, int z ) const;
     lem::int64_t size(void) const { return n; }
     bool empty(void) const { return n==0; }

     lem::int64_t LoadBin( const lem::Path &p );
     void ForEach( Ngrams *n, const lem::FString &db_suffix, const lem::FString &segment_name, Ngrams::raw *r, NGramHandler *handler );
    };



    struct Cache4
    {
     lem::int64_t n;
     lem::int32_t max_freq;
     lem::Ptr<lem::BinaryReader> bin;
     lem::uint64_t *marks_filepos;
     lem::uint32_t *marks_n;
     int n_marks;
     Cached4Gram *search_buffer;

     Cache4(void):n(0),max_freq(0),marks_filepos(NULL),marks_n(NULL),n_marks(0),search_buffer(NULL) {}
     ~Cache4(void);

     std::pair<int,int> find( int x, int y, int z, int w ) const;
     lem::int64_t size(void) const { return n; }
     bool empty(void) const { return n==0; }

     lem::int64_t LoadBin( const lem::Path &p );
     void ForEach( Ngrams *n, const lem::FString &db_suffix, const lem::FString &segment_name, Ngrams::raw *r, NGramHandler *handler );
    };



    struct Cache5
    {
     lem::int64_t n;
     lem::int32_t max_freq;
     lem::Ptr<lem::BinaryReader> bin;
     lem::uint64_t *marks_filepos;
     lem::uint32_t *marks_n;
     int n_marks;
     Cached5Gram *search_buffer;

     Cache5(void):n(0),max_freq(0),marks_filepos(NULL),marks_n(NULL),n_marks(0),search_buffer(NULL) {}
     ~Cache5(void);

     std::pair<int,int> find( int x, int y, int z, int w, int v ) const;
     lem::int64_t size(void) const { return n; }
     bool empty(void) const { return n==0; }

     lem::int64_t LoadBin( const lem::Path &p );
     void ForEach( Ngrams *n, const lem::FString &db_suffix, const lem::FString &segment_name, Ngrams::raw *r, NGramHandler *handler );
    };


    // согласованные (ковалентные) N-граммы
    struct cov
    {
     #if defined LEM_THREADS
     lem::Process::CriticalSection cs;
     #endif

     float min_w, max_w;
     lem::int64_t n;
     lem::FString suffix;
     lem::zbool has;
     lem::Collect<lem::FString> segments;
     lem::PtrCollect<Cache2> cache2; // кэш 2-грамм

     cov( const char *sfx ): min_w(0), max_w(0), n(0), suffix(sfx) {}
     lem::int64_t PreloadCachesFromFiles( const lem::Path &folder );
    };

    struct raw
    {
     #if defined LEM_THREADS
     lem::Process::CriticalSection cs;
     #endif

     lem::zbool lemmatize;
     lem::FString suffix;
     float max_w1, max_w2, max_w3, max_w4, max_w5;
     lem::int64_t nraw1, nraw2, nraw3, nraw4, nraw5;
     lem::zbool has1, has2, has3, has4, has5;
     lem::Collect<lem::FString> segments;
     lem::PtrCollect<Cache2> cache2;
     lem::PtrCollect<Cache3> cache3;
     lem::PtrCollect<Cache4> cache4;
     lem::PtrCollect<Cache5> cache5;

     raw( const char *sfx );

     void clear(void);
     lem::int64_t PreloadCachesFromFiles( const lem::Path &folder );
    };

    raw db_raw, db_literal;
    cov db_n_2_n, db_a_2_n, db_n_2_v, db_adv_2_v, db_adv_2_a, db_p_2_n, db_obj_2_v;

    #if defined SOL_LOADBIN
    void LoadCovalent(void);
    void LoadCovalent( Ngrams::cov & pdb );
    #endif

    void DumpRaw3( Ngrams::raw & pdb, lem::OFormatter &to );
    void DumpRaw2( Ngrams::raw & pdb, lem::OFormatter &to );

    void PreloadRaw2Cache( Ngrams::raw &pdb );
    void PreloadRaw3Cache( Ngrams::raw &pdb );

    void ForEachRaw1( bool lemmatized, NGramHandler *handler, int sorting );
    void ForEachRaw2( bool lemmatized, NGramHandler *handler, int sorting );
    void ForEachRaw3( bool lemmatized, NGramHandler *handler, int sorting );
    void ForEachRaw4( bool lemmatized, NGramHandler *handler, int sorting );
    void ForEachRaw5( bool lemmatized, NGramHandler *handler, int sorting );

    #if defined SOL_LOADBIN
    void LoadRaw( Ngrams::raw &pdb );
    #endif

    #if defined SOL_CAA
    void FindLeftWords(
                       Ngrams::cov &pdb,
                       int ie_right,
                       lem::MCollect<std::pair<int/*ientry*/,float> > & res,
                       int min_freq=1
                      );
    void FindRightWords(
                        Ngrams::cov &pdb,
                        int ie_left,
                        lem::MCollect<std::pair<int/*ientry*/,float> > & res,
                        int min_freq=1
                       );
    #endif

    void Dump( Ngrams::cov &pdb, lem::OFormatter &to );

    void Delete(void);

    bool FindRawNGrams(
                       Ngrams::raw &pdb,
                       const lem::UCString &left,
                       float &w,
                       int &iw
                      );


    bool FindRawNGrams(
                       Ngrams::raw &pdb,
                       const lem::UCString &left,
                       const lem::UCString &right,
                       float &w,
                       int &iw
                      );

    bool FindRawNGrams(
                       Ngrams::raw &pdb,
                       const lem::UCString &_w1,
                       const lem::UCString &_w2,
                       const lem::UCString &_w3,
                       float &w,
                       int &iw
                      );

    bool FindRawNGrams(
                       Ngrams::raw &pdb,
                       const lem::UCString &_w1,
                       const lem::UCString &_w2,
                       const lem::UCString &_w3,
                       const lem::UCString &_w4,
                       float &w,
                       int &iw
                      );

    bool FindRawNGrams(
                       Ngrams::raw &pdb,
                       const lem::UCString &_w1,
                       const lem::UCString &_w2,
                       const lem::UCString &_w3,
                       const lem::UCString &_w4,
                       const lem::UCString &_w5,
                       float &w,
                       int &iw
                      );


    int FindRawNGramsID(
                        Ngrams::raw &pdb,
                        const lem::UCString &left,
                        float &w,
                        int &iw
                       );


    int FindRawNGramsID(
                        Ngrams::raw &pdb,
                        const lem::UCString &left,
                        const lem::UCString &right,
                        float &w,
                        int &iw
                       );

    int FindRawNGramsID(
                        Ngrams::raw &pdb,
                        const lem::UCString &_w1,
                        const lem::UCString &_w2,
                        const lem::UCString &_w3,
                        float &w,
                        int &iw
                       );

    int FindRawNGramsID(
                        Ngrams::raw &pdb,
                        const lem::UCString &_w1,
                        const lem::UCString &_w2,
                        const lem::UCString &_w3,
                        const lem::UCString &_w4,
                        float &w,
                        int &iw
                       );

    int FindRawNGramsID(
                        Ngrams::raw &pdb,
                        const lem::UCString &_w1,
                        const lem::UCString &_w2,
                        const lem::UCString &_w3,
                        const lem::UCString &_w4,
                        const lem::UCString &_w5,
                        float &w,
                        int &iw
                       );


    void FindRawNGrams( Ngrams::raw &pdb, const lem::UCString &left, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq=1 );
    void FindRawNGrams( Ngrams::raw &pdb, lem::MCollect<lem::UCString> &left, const lem::UCString &right, lem::MCollect<float> &w, int min_freq=1 );

    void FindRawNGrams( Ngrams::raw &pdb, const lem::UCString &left, lem::MCollect<lem::UCString> &right1, lem::MCollect<lem::UCString> &right2, lem::MCollect<float> &w, int min_freq=1 );
    void FindRawNGrams( Ngrams::raw &pdb, lem::MCollect<lem::UCString> &left1, lem::MCollect<lem::UCString> &left2, const lem::UCString &right, lem::MCollect<float> &w, int min_freq=1 );
    void FindRawNGrams( Ngrams::raw &pdb, lem::MCollect<lem::UCString> &left, const lem::UCString &center, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq=1 );

    lem::int64_t PreloadCachesFromFiles(void);

    lem::zbool available;

   public:
    lem::Path folder; // из какого каталога загружена БД

   public:
    Ngrams( Solarix::Dictionary *d );
    ~Ngrams(void);

    void SetStorage( NGramsDBMS *_storage );
    lem::Ptr<NGramsDBMS> GetStorage(void) { return db; }

    #if defined SOL_LOADBIN
    void Load( const lem::Path &folder );
    #endif

    bool IsAvailable(void) const { return available; }

    #if defined SOL_CAA
    // возвращается список коррелированных с заданным существительным пригалательных.
    void FindAdjsForNoun( int ie_noun, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    void FindNounsForAdj( int ie_adj, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    lem::int64_t CountAdjsForNoun(void) const;

    // возвращается список глаголов, коррелированных с заданным существительным.
    void FindVerbsForNoun( int ie_noun, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    void FindNounsForVerb( int ie_verb, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    lem::int64_t CountVerbsForNoun(void) const;

    // возвращается список существительных, коррелированных с заданным существительным.
    void FindNounsForNoun( int ie_noun, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    lem::int64_t CountNounsForNoun(void) const;

    // Возвращает список наречий, сочетающихся с указанным прилагательным или глаголом
    void FindAdvsForAdj( int ie_adj, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    void FindAdjsForAdv( int ie_adv, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    lem::int64_t CountAdvsForAdj(void) const;

    void FindAdvsForVerb( int ie_verb, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    void FindVerbsForAdv( int ie_adv, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    lem::int64_t CountAdvsForVerb(void) const;

    void FindPreposForNoun( int ie_noun, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    void FindNounsForPrepos( int ie_prepos, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    lem::int64_t CountPreposForNoun(void) const;

    void FindObjsForVerb( int ie_verb, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    void FindVerbsForObj( int ie_noun, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );
    lem::int64_t CountObjsForVerb(void) const;

    // Заполняет список всех связанных слов для данного ie (согласованные 2-граммы)
    void FindLinkedWords( int ie, lem::MCollect<std::pair<int/*ientry*/,float> > &res, int min_freq=1 );


    // *** Работа с несогласованными, raw и literal N-граммами ***

    bool FindRawNGrams(
                       const lem::UCString &left,
                       float &w,
                       int &iw
                      );

    bool FindRawNGrams(
                       const lem::UCString &left,
                       const lem::UCString &right,
                       float &w,
                       int &iw
                      );

    bool FindRawNGrams(
                       const lem::UCString &_w1,
                       const lem::UCString &_w2,
                       const lem::UCString &_w3,
                       float &w,
                       int &iw
                      );

    bool FindRawNGrams(
                       const lem::UCString &_w1,
                       const lem::UCString &_w2,
                       const lem::UCString &_w3,
                       const lem::UCString &_w4,
                       float &w,
                       int &iw
                      );

    bool FindRawNGrams(
                       const lem::UCString &_w1,
                       const lem::UCString &_w2,
                       const lem::UCString &_w3,
                       const lem::UCString &_w4,
                       const lem::UCString &_w5,
                       float &w,
                       int &iw
                      );

    int FindRawNGramsID(
                        const lem::UCString &left,
                        float &w,
                        int &iw
                       );

    int FindRawNGramsID(
                        const lem::UCString &left,
                        const lem::UCString &right,
                        float &w,
                        int &iw
                       );

    int FindRawNGramsID(
                        const lem::UCString &_w1,
                        const lem::UCString &_w2,
                        const lem::UCString &_w3,
                        float &w,
                        int &iw
                       );

    int FindRawNGramsID(
                        const lem::UCString &_w1,
                        const lem::UCString &_w2,
                        const lem::UCString &_w3,
                        const lem::UCString &_w4,
                        float &w,
                        int &iw
                       );

    int FindRawNGramsID(
                        const lem::UCString &_w1,
                        const lem::UCString &_w2,
                        const lem::UCString &_w3,
                        const lem::UCString &_w4,
                        const lem::UCString &_w5,
                        float &w,
                        int &iw
                        );

    void FindRawNGrams( const lem::UCString &left, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq=1 );
    void FindRawNGrams( lem::MCollect<lem::UCString> &left, const lem::UCString &right, lem::MCollect<float> &w, int min_freq=1 );

    void FindRawNGrams( const lem::UCString &left, lem::MCollect<lem::UCString> &right1, lem::MCollect<lem::UCString> &right2, lem::MCollect<float> &w, int min_freq=1 );
    void FindRawNGrams( lem::MCollect<lem::UCString> &left1, lem::MCollect<lem::UCString> &left2, const lem::UCString &right, lem::MCollect<float> &w, int min_freq=1 );
    void FindRawNGrams( lem::MCollect<lem::UCString> &left, const lem::UCString &center, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq=1 );

    bool FindLiteralNGrams(
                           const lem::UCString &left,
                           float &w,
                           int &iw
                          );

    bool FindLiteralNGrams(
                           const lem::UCString &left,
                           const lem::UCString &right,
                           float &w,
                           int &iw
                          );

    bool FindLiteralNGrams(
                           const lem::UCString &_w1,
                           const lem::UCString &_w2,
                           const lem::UCString &_w3,
                           float &w,
                           int &iw
                          );

    bool FindLiteralNGrams(
                           const lem::UCString &_w1,
                           const lem::UCString &_w2,
                           const lem::UCString &_w3,
                           const lem::UCString &_w4,
                           float &w,
                           int &iw
                          );

    bool FindLiteralNGrams(
                           const lem::UCString &_w1,
                           const lem::UCString &_w2,
                           const lem::UCString &_w3,
                           const lem::UCString &_w4,
                           const lem::UCString &_w5,
                           float &w,
                           int &iw
                          );

    void FindLiteralNGrams( const lem::UCString &left, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq=1 );
    void FindLiteralNGrams( lem::MCollect<lem::UCString> &left, const lem::UCString &right, lem::MCollect<float> &w, int min_freq=1 );

    void FindLiteralNGrams( const lem::UCString &left, lem::MCollect<lem::UCString> &right1, lem::MCollect<lem::UCString> &right2, lem::MCollect<float> &w, int min_freq=1 );
    void FindLiteralNGrams( lem::MCollect<lem::UCString> &left1, lem::MCollect<lem::UCString> &left2, const lem::UCString &right, lem::MCollect<float> &w, int min_freq=1 );
    void FindLiteralNGrams( lem::MCollect<lem::UCString> &left, const lem::UCString &center, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq=1 );

    bool FindNGrams(
                    bool lemmatize,
                    const lem::UCString &left,
                    float &w,
                    int &iw
                   );

    bool FindNGrams(
                    bool lemmatize,
                    const lem::UCString &left,
                    const lem::UCString &right,
                    float &w,
                    int &iw
                   );

    bool FindNGrams(
                    bool lemmatize,
                    const lem::UCString &_w1,
                    const lem::UCString &_w2,
                    const lem::UCString &_w3,
                    float &w,
                    int &iw
                   );

    bool FindNGrams(
                    bool lemmatize,
                    const lem::UCString &_w1,
                    const lem::UCString &_w2,
                    const lem::UCString &_w3,
                    const lem::UCString &_w4,
                    float &w,
                    int &iw
                   );

    bool FindNGrams(
                    bool lemmatize,
                    const lem::UCString &_w1,
                    const lem::UCString &_w2,
                    const lem::UCString &_w3,
                    const lem::UCString &_w4,
                    const lem::UCString &_w5,
                    float &w,
                    int &iw
                   );



    int Find1Grams( bool lemmatize, lem::MCollect<lem::UCString> &word, lem::MCollect<int> &iw, lem::MCollect<float> &w, int min_freq=1 );

    // Общее кол-во записей в базе, включая коррелированные и некоррелированные.
    lem::int64_t TotalCount(void) const;

    lem::int64_t CountCovalent(void) const;

    lem::int64_t CountRaw(void) const;
    lem::int64_t CountLiteral(void) const;
    lem::int64_t CountRaw1(void) const;
    lem::int64_t CountRaw2(void) const;
    lem::int64_t CountRaw3(void) const;
    lem::int64_t CountRaw4(void) const;
    lem::int64_t CountRaw5(void) const;
    lem::int64_t CountLiteral1(void) const;
    lem::int64_t CountLiteral2(void) const;
    lem::int64_t CountLiteral3(void) const;
    lem::int64_t CountLiteral4(void) const;
    lem::int64_t CountLiteral5(void) const;

    // Получение суммы частот для всех N-грамм заданного типа
    lem::int64_t SumFreq( int order, bool lemmatized );

    // Обход списка Nграмм заданного порядка
    void ForEachRaw( NGramHandler *handler, int order, bool lemmatized, int sorting );

    // возвращает максимальный порядок имеющихся в базе несогласованных N-грамм.
    int GetRawOrder(void) const;
    int GetLiteralOrder(void) const;

    void Add( const Solarix::Dictionary &dict, int ie1, int ie2, float w );
    #endif

    void DumpRaw3( lem::OFormatter &to );
    void DumpRaw2( lem::OFormatter &to );
    void DumpLiteral3( lem::OFormatter &to );
    void DumpLiteral2( lem::OFormatter &to );

    // Поиск id записи для слова в таблицах WORDS и WORDS_LITERAL
    int FindInWordTable( const lem::UCString &_word, bool lemmatized );

    void CreateTable_Words( const lem::FString &suffix );
    void CreateTable_NGrams1( const lem::FString &suffix );
    void CreateTable_NGrams2( const lem::FString &suffix );
    void CreateTable_NGrams3( const lem::FString &suffix );
    void CreateTable_NGrams4( const lem::FString &suffix );
    void CreateTable_NGrams5( const lem::FString &suffix );

    int MaxBulkInsert(void);

    lem::FString StartBulkInsert( const lem::FString &suffix, int order );

    lem::FString AppendBulkInsert(
                                  const lem::FString &suffix,
                                  int counter,
                                  int id,
                                  int id_word1,
                                  int w
                                 );

    lem::FString AppendBulkInsert(
                                  const lem::FString &suffix,
                                  int counter,
                                  int id,
                                  int id_word1,
                                  int id_word2,
                                  int w
                                 );

    lem::FString AppendBulkInsert(
                                  const lem::FString &suffix,
                                  int counter,
                                  int id,
                                  int id_word1,
                                  int id_word2,
                                  int id_word3,
                                  int w
                                 );

    lem::FString AppendBulkInsert(
                                  const lem::FString &suffix,
                                  int counter,
                                  int id,
                                  int id_word1,
                                  int id_word2,
                                  int id_word3,
                                  int id_word4,
                                  int w
                                 );

    lem::FString AppendBulkInsert(
                                  const lem::FString &suffix,
                                  int counter,
                                  int id,
                                  int id_word1,
                                  int id_word2,
                                  int id_word3,
                                  int id_word4,
                                  int id_word5,
                                  int w
                                 );

    void UpdateNGrams(
                      const lem::FString &suffix,
                      int order, 
                      const lem::MCollect< std::pair<int,int> > & list
                     );


    std::pair<int/*id*/,int/*w*/> Find1Gram( const lem::FString &suffix, int id_word );
    std::pair<int/*id*/,int/*w*/> Find2Gram( const lem::FString &suffix, int id_word1, int id_word2 );
    std::pair<int/*id*/,int/*w*/> Find3Gram( const lem::FString &suffix, int id_word1, int id_word2, int id_word3 );
    std::pair<int/*id*/,int/*w*/> Find4Gram( const lem::FString &suffix, int id_word1, int id_word2, int id_word3, int id_word4 );
    std::pair<int/*id*/,int/*w*/> Find5Gram( const lem::FString &suffix, int id_word1, int id_word2, int id_word3, int id_word4, int id_word5 );

    void FinishBulkInsert( const lem::FString &sql );

    void CreateTable_Segments(void);
    void CreateIndeces1( const lem::FString &suffix, int order );
    void CreateIndeces2( const lem::FString &suffix, int order );
    void CreateIndecesWord2( const lem::FString &suffix );
    int FindWord(
                 const lem::FString &suffix,
                 const lem::UCString &word
                );

    lem::UCString GetWord( const lem::FString &suffix, const lem::FString &segment, int id_word );

    void InsertWord(
                    const lem::FString &suffix,
                    int id_word,
                    const lem::UCString &word
                   );

    void UpdateStatistics( const lem::FString &suffix, int order );
    void EraseFreq1( const lem::FString &suffix, int order );

  };

 }

 #endif

#endif
