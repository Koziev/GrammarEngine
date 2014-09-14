#if !defined RECO2_RPoint2Pattern__H
 #define RECO2_RPoint2Pattern__H

 #include <lem/noncopyable.h>
 #include <lem/process.h>
 #include <lem/solarix/R2Utils.h>

 namespace Reco2
 { 
  class Reconstructor2Storage;

  class Point2Pattern : lem::NonCopyable
  {
   private:
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif

    Reconstructor2Storage *db;
    lem::MCollect< ints* > patterns;
    std::map<int, ints* > point2patterns;

   public:
    Point2Pattern(void);
    
    void Connect( Reconstructor2Storage *_db );

    void FindPatterns( int id_point, std::set<int> &id_patterns );
  };
 }

#endif
