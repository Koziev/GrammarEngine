#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;

TrFun_Var::TrFun_Var(void)
: TrFunCall( TrFunCall::Var )
{
}

TrFun_Var::TrFun_Var( const UCString &VarName )
: TrFunCall( TrFunCall::Var ), var_name(VarName)
{
}
   
TrFun_Var::TrFun_Var( const TrFun_Var & x )
: TrFunCall(x), var_name(x.var_name)
{
}

void TrFun_Var::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 var_name = ((const TrFun_Var&)x).var_name;
 return;
}


#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_Var::Run(
                                 const ElapsedTimeConstraint & constraints,
                                 PM_Automat &pm,
                                 TrFunContext &ctx,
                                 TrTrace *trace_log
                                ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 lem::Ptr<TrValue> ret = ctx.GetVar(var_name);

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 return ret;
}
#endif


#if defined SOL_SAVEBIN
void TrFun_Var::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);
 bin.write( &var_name, sizeof(var_name) );
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrFun_Var::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 bin.read( &var_name, sizeof(var_name) );
 return;
}

void TrFun_Var::Link( const TrFunctions &funs )
{
 return;
}
#endif


#if defined SOL_COMPILER
void TrFun_Var::RefreshArgumentNames( const TrFunctions &funs )
{
 return;
}
#endif

TrFunCall* TrFun_Var::clone(void) const
{
 return new TrFun_Var(*this);
}
