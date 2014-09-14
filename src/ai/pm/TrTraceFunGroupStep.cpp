#if defined SOL_CAA

// CD->28.07.2009
// LC->29.07.2009

#include <lem/solarix/res_pack.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;

TrTraceFunGroupStep::TrTraceFunGroupStep( int mark, int Location, const TrFunCall *g, const TrFunCall *i, const TrFunContext *c )
 : TrTraceActor(mark,Location)
{
 group = g;
 item = i;
 ctx = c;
 return;
}

void TrTraceFunGroupStep::Print( Dictionary &dict, OFormatter &out, const TrTraceActor *opening )
{
}


void TrTraceFunGroupStep::PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const
{
 if( ctx!=NULL )
  {
   out.printf( "Variable in the scope:\n" );
   ctx->PrintVars( dict, out );
   out.eol();
  }

 return;
}

#endif
