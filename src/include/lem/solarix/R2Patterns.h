#if !defined RECO2_RPatterns__H
 #define RECO2_RPatterns__H

 #include <lem/noncopyable.h>
 #include <lem/process.h>
 #include <lem/containers.h>
 #include <lem/solarix/R2Utils.h>

 namespace Reco2
 {
  class RPattern;
  class RPatternEnumerator;
  class Reconstructor2Storage;

  class RPatterns : lem::NonCopyable
  {
   private:
    Reconstructor2Storage *db;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif
    lem::MCollect<RPattern*> patterns;
    std::map< int /*id_pattern*/, const RPattern* > id2pattern;

   public:
    RPatterns(void);
    ~RPatterns(void);

    void Connect( Reconstructor2Storage *_db );

    int Count(void) const;
    
    RPattern * BuildPattern( int _id_ngram, int _freq, const ints & _id_points );
    const RPattern& operator[]( int id );

    RPatternEnumerator* Enumerate(void);
  };
 }
#endif
