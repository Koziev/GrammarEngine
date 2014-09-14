#if !defined TrTraceSynIteratorPass__H && defined SOL_CAA
#define TrTraceSynIteratorPass__H

#include <lem/solarix/trace_log.h>

namespace lem
{
 class OFormatter;
}

namespace Solarix
{
 class SynIteratorPass;
 class ConnectorApplication;
 class ConnectionState;

 class TrTraceSynIteratorPass : public TrTraceActor
 {
  private:
   const SynIteratorPass * actor;
   const lem::MCollect<ConnectorApplication*> * current_contexts;
   const lem::MCollect<ConnectorApplication*> * new_contexts;
   const ConnectionState * state;

  public:
   TrTraceSynIteratorPass(
                          int mark,
                          int Location, 
                          const SynIteratorPass * _actor,
                          const lem::MCollect<ConnectorApplication*> * _current_contexts,
                          const lem::MCollect<ConnectorApplication*> * _new_contexts,
                          const ConnectionState * _state
                         );

   virtual void Print( Dictionary &dict, lem::OFormatter &out, const TrTraceActor *opening=NULL );
   virtual void PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const;
   virtual bool IsStatement(void) const;
 };
}

#endif
