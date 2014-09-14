#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;

TrFun_Break::TrFun_Break(void)
 : TrFunCall( TrFunCall::Break )
{
}


TrFun_Break::TrFun_Break( const TrFun_Break & x )
 : TrFunCall(x)
{
}



void TrFun_Break::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 return;
}
   

#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_Break::Run(
                                   const ElapsedTimeConstraint & constraints,
                                   PM_Automat &pm,
                                   TrFunContext &ctx,
                                   TrTrace *trace_log
                                  ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 ctx.e_break = true;
 lem::Ptr<TrValue> ret( new TrValue ); 

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 return ret;
}
#endif


#if defined SOL_SAVEBIN
void TrFun_Break::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);
 return;
}
#endif


#if defined SOL_LOADBIN 
void TrFun_Break::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 return;
}

void TrFun_Break::Link( const TrFunctions &funs )
{
 return;
}
#endif

#if defined SOL_COMPILER
void TrFun_Break::RefreshArgumentNames( const TrFunctions &declarations )
{
 return;
}
#endif

TrFunCall* TrFun_Break::clone(void) const
{
 return new TrFun_Break(*this);
}
