#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;


TrFun_Return::TrFun_Return(void)
 : TrFunCall( TrFunCall::Return )
{
}


TrFun_Return::TrFun_Return( TrFunCall *Expr )
 : TrFunCall( TrFunCall::Return ), expr(Expr)
{
}


TrFun_Return::TrFun_Return( const TrFun_Return & x )
 : TrFunCall(x), expr(x.expr->clone())
{
}



void TrFun_Return::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 expr = ((const TrFun_Return&)x).expr->clone();
 return;
}
   

#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_Return::Run(
                                   const ElapsedTimeConstraint & constraints,
                                   PM_Automat &pm,
                                   TrFunContext &ctx,
                                   TrTrace *trace_log
                                  ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 lem::Ptr<TrValue> v = expr->Run(constraints,pm,ctx,trace_log);

 ctx.GetVar( L"((return))" )->Assign( *v );

 ctx.e_break = true;
 ctx.e_return = true;

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 return v; 
}
#endif


#if defined SOL_SAVEBIN
void TrFun_Return::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);
 expr->SaveBin(bin);
 return;
}
#endif


#if defined SOL_LOADBIN 
void TrFun_Return::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 expr = TrFunCall::load_bin(bin);
 return;
}

void TrFun_Return::Link( const TrFunctions &funs )
{
 expr->Link(funs);
 return;
}

#endif

#if defined SOL_COMPILER
void TrFun_Return::RefreshArgumentNames( const TrFunctions &funs )
{
 expr->RefreshArgumentNames(funs);
 return;
}
#endif


TrFunCall* TrFun_Return::clone(void) const
{
 return new TrFun_Return(*this);
}
