#if !defined RECO2_RPOINTS__H
 #define RECO2_RPOINTS__H

 #include <lem/noncopyable.h>
 #include <lem/process.h>
 #include <lem/containers.h>

 namespace Reco2
 {
  class Reconstructor2;
  class RPointEnumerator;
  class Reconstructor2Storage;
  class RPoint;

  class RPoints : lem::NonCopyable
  {
   private:
    Reconstructor2Storage *db;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif
    lem::MCollect<RPoint*> points;
    std::map<int /*id*/,const RPoint*> id2points; // справочник опорных точек
    std::map<int /*id_word*/, int /*id_point*/ > rpoints_by_headword;

   public:
    RPoints(void);

    void Connect( Reconstructor2Storage *_db );
    int FindByHeadword( int id_word );
    const RPoint& operator[]( int id );
    RPoint * Register( int id_word, int weight );
    RPointEnumerator* Enumerate(void);
    int Count(void);
  };
 }

#endif
