#if !defined PatternMatcherEnumerator__H
 #define PatternMatcherEnumerator__H

 #include <lem/noncopyable.h>

 namespace Solarix
 {
  class PM_ProcedureLoader;
  class LS_ResultSet;
  class PatternMatcherEnumerator : lem::NonCopyable
  {
   private:
    PM_ProcedureLoader *procs;
    LS_ResultSet *rs;

   public:
    PatternMatcherEnumerator( LS_ResultSet *RS, PM_ProcedureLoader *Procs );
    ~PatternMatcherEnumerator(void);

    bool Fetch(void);
    int GetId(void);
    const TrPatternMatcher& GetMatcher(void);
  };
 }

#endif
