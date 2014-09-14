#if !defined VA_GG_TO_SG__H
 #define VA_GG_TO_SG__H

 #include <lem/process.h>
 #include <lem/RWULock.h>
 #include <lem/noncopyable.h>
 #include <lem/containers.h>

 namespace Solarix
 {
  class LexiconStorage;
  class Dictionary;

  class VA_GG_to_SG : lem::NonCopyable
  {
   private:
    LexiconStorage *storage;
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_init;
    lem::Process::RWU_Lock cs;
    #endif
    volatile bool loaded;

    lem::IntCollect _gg_to_sg__id_coord0;
    lem::IntCollect _gg_to_sg__coord;
    lem::IntCollect _gg_to_sg__id_class0;
    lem::IntCollect _gg_to_sg__class;

    void Load(void);

   public:
    VA_GG_to_SG(void);

    void Connect( LexiconStorage *Storage );
    void Prepare( Solarix::Dictionary &dict );
    void Store(void);

    const lem::IntCollect& gg_to_sg__id_coord0(void);
    const lem::IntCollect& gg_to_sg__coord(void);
    const lem::IntCollect& gg_to_sg__id_class0(void);
    const lem::IntCollect& gg_to_sg__class(void);

  };
 }

#endif
