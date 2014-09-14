#if !defined PM_FUNCTION_LOADER__H
 #define PM_FUNCTION_LOADER__H

 #include <lem/process.h>
 #include <lem/RWULock.h>

 namespace Solarix
 {
  class TrFunctions;
  class LexiconStorage;
  class Dictionary;

  class PM_FunctionLoader
  {
   private:
    Solarix::Dictionary *dict;
    LexiconStorage *storage;
    const wchar_t *marker;

    TrFunctions *functions;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_init;
    lem::Process::RWU_Lock cs;
    #endif

    volatile bool loaded;
    void Delete(void);
    void Load(void);

   public:
    PM_FunctionLoader( Solarix::Dictionary *Dict );
    ~PM_FunctionLoader(void);

    void Connect( LexiconStorage *Storage, const wchar_t *Marker );

    void CompilationFinished(void);

    TrFunctions& Get(void);
    void Store(void);
  };
 }

#endif
