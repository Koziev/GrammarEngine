#if defined SOL_CAA

// CD->21.07.2009
// LC->29.07.2009

#include <lem/solarix/res_pack.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;

TrTraceFunCall::TrTraceFunCall( int mark, int Location, const TrFunCall *f, const TrFunContext *c, bool _statement )
 : TrTraceActor(mark,Location)
{
 fun = f;
 ctx = c;
 is_statement = _statement;
 return;
}

void TrTraceFunCall::Print( Dictionary &dict, OFormatter &out, const TrTraceActor *opening )
{
 PrintContext(dict,out);
 return;
}

void TrTraceFunCall::PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const
{
 if( ctx!=NULL )
  {
   out.printf( "Variable in the scope:\n" );
   ctx->PrintVars( dict, out );
  }

 return;
}


#endif
