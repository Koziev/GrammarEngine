#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;

TrFun_Constant::TrFun_Constant(void)
: TrFunCall( TrFunCall::Constant )
{
}
 
TrFun_Constant::TrFun_Constant( const TrValue &v )
: TrFunCall( TrFunCall::Constant ), value(v)
{
}
   
TrFun_Constant::TrFun_Constant( const TrFun_Constant & x )
 : TrFunCall(x), value(x.value)
{
}

void TrFun_Constant::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 value = ((const TrFun_Constant&)x).value;
 return;
}

#if defined SOL_COMPILER
void TrFun_Constant::RefreshArgumentNames( const TrFunctions &declarations )
{
 value.RefreshArgumentNames(declarations);
 return;
}
#endif


#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_Constant::Run(
                                      const ElapsedTimeConstraint & constraints,
                                      PM_Automat &pm,
                                      TrFunContext &ctx,
                                      TrTrace *trace_log
                                     ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 lem::Ptr<TrValue> ret( new TrValue(value) );

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 return ret;
}
#endif


#if defined SOL_SAVEBIN
void TrFun_Constant::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);
 value.SaveBin(bin);
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrFun_Constant::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 value.LoadBin(bin);
 return;
}

void TrFun_Constant::Link( const TrFunctions &funs )
{
 value.Link(funs);
 return;
}
#endif


TrFunCall* TrFun_Constant::clone(void) const
{
 return new TrFun_Constant(*this);
}
