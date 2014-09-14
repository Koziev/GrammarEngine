#if !defined RECO2_RWord2Point__H
 #define RECO2_RWord2Point__H

 #include <lem/noncopyable.h>
 #include <lem/process.h>
 #include <lem/solarix/R2Utils.h>

 namespace Reco2
 {
  class Reconstructor2Storage;

  class Word2Point : lem::NonCopyable
  {
   private:
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif

    Reconstructor2Storage *db;
    lem::MCollect< ints* > points;
    std::map< int, ints* > word2points;

   public:
    Word2Point(void);
    
    void Connect( Reconstructor2Storage *_db );

    void Add( int id_word, int id_point );
    void FindPoints( int id_word, std::set<int> &id_points );
  };
 }

#endif
