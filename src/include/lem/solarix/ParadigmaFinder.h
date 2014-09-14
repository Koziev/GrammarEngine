#if !defined ParadigmaFinder__H
 #define ParadigmaFinder__H

 #include <lem/RWULock.h>

 namespace Solarix
 {
  class LexiconStorage;
  class ParadigmaMatcher;

  class ParadigmaFinder
  {
   private:
    LexiconStorage *storage;

    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs;
    #endif

    volatile bool loaded;
    lem::MCollect<int> id_class;
    lem::MCollect< ParadigmaMatcher* > matchers;
    lem::MCollect<int> ids;

    typedef std::map< int /*id_class*/, lem::MCollect< std::pair<int,const ParadigmaMatcher*> >* > CLASS2DECL;
    CLASS2DECL class2decl;

    void LoadFromDB(void);

   public:
    ParadigmaFinder( LexiconStorage *_storage );
    ~ParadigmaFinder(void);

    void Find( int PartOfSpeech, const lem::UCString &entry_name, lem::MCollect<int> &ids );
    void Add( const ParadigmaMatcher &matcher, int PartOfSpeech, int id );
  };
 }
#endif
