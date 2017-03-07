#if !defined LA_SynPatternPointCall__H
 #define LA_SynPatternPointCall__H

 #include <lem/solarix/translation.h>

 namespace Solarix
 {
  class SynPatternPoint;
  class Variator;
  class BackTrace;

  #if defined SOL_CAA && !defined SOL_NO_AA
  class SynPatternPointCall : public TrTraceActor
  {
   private:
    const SynPatternPoint * point;
    const BackTrace * markers;
    const LexerTextPos * token;

   public:
    SynPatternPointCall( int mark, const lem::MCollect<int> &Location, const SynPatternPoint *p, const LexerTextPos * _token, const BackTrace *_markers );
    virtual void Print( Dictionary &dict, OFormatter &out, const TrTraceActor *opening=NULL );
    virtual bool IsStatement(void) const { return true; }
    virtual void PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const;
    virtual void PrintCurrentToken( Solarix::Dictionary &dict, lem::OFormatter &out ) const;

    virtual bool ExecuteBreakpoints() const { return false; }
  };
  #endif

 }
#endif
