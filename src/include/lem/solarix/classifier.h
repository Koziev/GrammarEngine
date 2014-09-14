#if !defined SOL_CLASSIFIER__H
 #define SOL_CLASSIFIER__H

 #include <lem/solarix/dictionary.h>
 #include <lem/string_parser.h>
 #include <lem/solarix/NGramsCollectors.h>

 namespace Solarix
 {
  namespace Classifier
  {
   struct ClassifierTrainOptions
   {
    lem::zbool ngrams1, ngrams2, ngrams3, ngrams4, ngrams5;
    lem::zint language_sx_code;

    double freq_ration_treshold; // величина, должна быть >1, отношение частоты
                                 // N-граммы в топике к частоте её в корпусе для категории,
                                 // при которой N-грамма считается значимым признаком.   

    ClassifierTrainOptions(void);
   };

   class ClassificationDB
   {
    public:
     ClassificationDB(void) {}
     virtual ~ClassificationDB(void) {}

     virtual int StoreCategory( const lem::UFString &cname )=0; 
     virtual int StoreTopic( int id_category, const lem::UFString &tname )=0; 
     virtual void StoreSign( int order, int id_category, int id_topic, int id_ngram, double w )=0;
     virtual void StoreOptions( const ClassifierTrainOptions &opts )=0;

     virtual void Begin(void)=0;
     virtual void Commit(void)=0;
   };


   struct CorpusStat
   {
    std::map< int /*Ngram order*/, lem::int64_t > total_freq;
   };

   struct DirSet : lem::NonCopyable
   {
    lem::PtrCollect<lem::Path> dirs;

    void Load( lem::StrParser<lem::UFString> &src );
   };

   struct Category;

   struct Topic : lem::NonCopyable
   {
    static int iseq;

    lem::UFString category, name;
    DirSet dirs;
    lem::Path ngrams_folder;
    int id;

    lem::Ptr<Solarix::NGramsCollectors> ngrams;
    lem::Ptr<Solarix::Ngrams> ngrams_db;

    CorpusStat corpus_stat;

    Topic( const lem::UFString &cname, const lem::UFString &tname, const lem::Path &outdir );
    void Load( lem::StrParser<lem::UFString> &src );
    void LoadDirs( lem::StrParser<lem::UFString> &src );
    void Run( lem::Ptr<Solarix::Dictionary> &dict, const ClassifierTrainOptions &opt );

    void OpenDatabase(
                      lem::Ptr<Solarix::Dictionary> &dict,
                      const ClassifierTrainOptions &opts
                     );

    void CloseDBs(void);

    void FinalComputations(
                           Topic &corpus,
                           Category &my_cat, 
                           lem::Ptr<Solarix::Dictionary> &dict,
                           const ClassifierTrainOptions &opts,
                           ClassificationDB &out_db
                          );

    void CopyNGRAMS( const lem::Path &outdir );
   }; 


   struct Category : lem::NonCopyable
   {
    lem::UFString name;
    lem::PtrCollect<Topic> topics;
    lem::Ptr<Topic> corpus;
    int id;

    const Topic* FindTopic( const lem::UFString & tname ) const;
          Topic* FindTopic( const lem::UFString & tname );

    void Load( lem::StrParser<lem::UFString> &src );
    void AddTopic( Topic *t );
    void Run( lem::Ptr<Solarix::Dictionary> &dict, const ClassifierTrainOptions &opt );

    Category(void):id(UNKNOWN) {}
    Category( const lem::UFString &s ) : name(s), id(UNKNOWN) {}

    void FinalComputations(
                           lem::Ptr<Solarix::Dictionary> &dict,
                           const ClassifierTrainOptions &opts,
                           ClassificationDB &out_db
                          );

    void CopyNGRAMS( const lem::Path &outdir );
   };


   class ClassifierEngine
   {
    private:
     lem::Ptr<Solarix::Dictionary> dict;
     lem::Path outdir;
     lem::OFormatter nul_tty;

     ClassifierTrainOptions opts;
     lem::PtrCollect<Category> category;

     Category* FindCategory( const lem::UFString & catname );

    public:
     ClassifierEngine(void);
    
     void SetOutDir( const lem::Path &out );
     void LoadDictionary( const lem::Path &xml );
     void LoadJob( const lem::Path &jobfile );
     void Learn( lem::OFormatter &console );
   };

  } // namespace Classifier

 } // namespace Solarix


#endif
