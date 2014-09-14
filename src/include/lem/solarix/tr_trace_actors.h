#ifndef TR_TRACE_ACTORS__H
#define TR_TRACE_ACTORS__H
#pragma once

 #include <lem/solarix/translation.h>

 namespace Solarix
 {
  #if defined SOL_CAA && !defined SOL_NO_AA
  class TrTraceFunCall : public TrTraceActor
  {
   private:
    const TrFunCall *fun;
    const TrFunContext *ctx;
    bool is_statement;

   public:
    TrTraceFunCall( int mark, int Location, const TrFunCall *f, const TrFunContext *c, bool _statement );
    virtual void Print( Dictionary &dict, OFormatter &out, const TrTraceActor *opening=NULL );
    virtual bool IsStatement(void) const { return is_statement; }
    virtual void PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const;
  };
  #endif

  #if defined SOL_CAA && !defined SOL_NO_AA
  class TrTraceFunGroupStep : public TrTraceActor
  {
   private:
    const TrFunCall *group, *item;
    const TrFunContext *ctx;

   public:
    TrTraceFunGroupStep( int mark, int Location, const TrFunCall *g, const TrFunCall *i, const TrFunContext *c );
    virtual void Print( Dictionary &dict, OFormatter &out, const TrTraceActor *opening=NULL );
    virtual bool IsStatement(void) const { return true; }
    virtual void PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const;
  };
  #endif


 }

#endif
