#if !defined TrTraceSynIterator__H && defined SOL_CAA
#define TrTraceSynIterator__H

#include <lem/solarix/trace_log.h>

namespace lem
{
 class OFormatter;
}

namespace Solarix
{
 class SynIterator;
 class ConnectorApplication;
 class ConnectionState;

 class TrTraceSynIterator : public TrTraceActor
 {
  private:
   const SynIterator * iterator;
   const lem::MCollect<ConnectorApplication*> * current_contexts;
   const lem::MCollect<ConnectorApplication*> * new_contexts;
   const ConnectionState * state;

  public:
   TrTraceSynIterator(
                      int mark,
                      int Location, 
                      const SynIterator * _iterator,
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
