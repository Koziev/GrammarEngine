#if !defined LA_TreeScorerCall__H && defined SOL_CAA && defined SOL_DEBUGGING
 #define LA_TreeScorerCall__H

 #include <lem/solarix/translation.h>

 namespace Solarix
 {
  class LinkEdgeContainer;
  class TreeScorerCall : public TrTraceActor
  {
   private:
    const LinkEdgeContainer & edges;

   public:
    TreeScorerCall( int dbg_seq, int id_src, const LinkEdgeContainer & _edges ) : TrTraceActor(dbg_seq,id_src), edges(_edges) {}
    virtual void Print( Dictionary &dict, OFormatter &out, const TrTraceActor *opening=NULL ) {}
    virtual bool IsStatement(void) const { return true; }
    virtual void PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const;
    virtual bool ExecuteBreakpoints() const { return true; }
  };

 }
#endif
