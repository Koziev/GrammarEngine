#if !defined PM_PROCEDURE_LOADER__H
 #define PM_PROCEDURE_LOADER__H

 #include <lem/noncopyable.h>
 #include <lem/containers.h>
 #include <lem/process.h>
 #include <lem/RWULock.h>

 namespace Solarix
 {
  class Dictionary;
  class TrProcedure;
  class TrPatternMatcher;
  class PM_FunctionLoader;
  class PM_Automat;
  class ProcedureEnumerator;
  class PatternMatcherEnumerator;
  class LexiconStorage;

  class PM_ProcedureLoader : lem::NonCopyable
  {
   private:
    Solarix::Dictionary *dict;
    Solarix::PM_Automat *pm;
    Solarix::PM_FunctionLoader *functions;
    Solarix::LexiconStorage *storage;
    const wchar_t *marker;

    lem::MCollect<TrProcedure*> procedures;
    std::map< lem::UCString, int /*id*/ > name2proc;
    std::map< int /*id_proc*/, const TrProcedure* > id2proc;

    lem::MCollect<TrPatternMatcher*> matchers;
    lem::MCollect<lem::UCString> scenario;
    std::map< lem::UCString, int /*id*/ > name2matcher;
    std::map< int /*id*/, const TrPatternMatcher* > id2matcher;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_init;
    lem::Process::RWU_Lock cs_proc, cs_matcher;
    #endif

    void Delete(void);

   public:
    PM_ProcedureLoader( Solarix::Dictionary *Dict, PM_Automat *PM, PM_FunctionLoader *Functions );
    ~PM_ProcedureLoader(void);

    void Connect( LexiconStorage *Storage, const wchar_t *Marker );

    int FindProcedure( const lem::UCString & name, bool throw_exception );
    const TrProcedure* GetProcedure( int id );
    const TrProcedure* GetProcedure( const lem::UCString &name );
    void StoreProcedure( TrProcedure *p );
    ProcedureEnumerator* ListProcedures(void);

    int FindMatcher( const lem::UCString &name );
    const TrPatternMatcher* GetMatcher( int id );
    const TrPatternMatcher* GetMatcher( const lem::UCString &name );
    void StorePatternMatcher( int type, const lem::UCString &name, TrPatternMatcher *m );
    PatternMatcherEnumerator* ListMatchers(void);

    void CompilationFinished(void);
  };
 }

#endif
