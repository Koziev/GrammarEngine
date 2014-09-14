#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;

TrFun_Assign::TrFun_Assign(void)
: TrFunCall( TrFunCall::Assign )
{
}
   

TrFun_Assign::TrFun_Assign( const UCString &VarName, TrFunCall *Expr )
: TrFunCall( TrFunCall::Assign ), var_name(VarName), expr(Expr)
{
}
   
TrFun_Assign::TrFun_Assign( const TrFun_Assign & x )
: TrFunCall(x), var_name(x.var_name), expr(x.expr)
{
}

void TrFun_Assign::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 var_name = ((const TrFun_Assign&)x).var_name;
 expr = ((const TrFun_Assign&)x).expr;
 return;
}


#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_Assign::Run(
                                    const ElapsedTimeConstraint & constraints,
                                    PM_Automat &pm,
                                    TrFunContext &ctx,
                                    TrTrace *trace_log
                                   ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 lem::Ptr<TrValue> left = ctx.GetVar(var_name);
 const bool const_var = left->GetType().IsConst();
 lem::Ptr<TrValue> right = expr->Run(constraints,pm,ctx,trace_log);
 left->Assign(*right);

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 return left;
}
#endif


#if defined SOL_SAVEBIN
void TrFun_Assign::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);
 bin.write( &var_name, sizeof(var_name) );
 expr.SaveBin(bin);
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrFun_Assign::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 bin.read( &var_name, sizeof(var_name) );
 expr.LoadBin(bin);
 return;
}

void TrFun_Assign::Link( const TrFunctions &funs )
{
 expr->Link(funs);
 return;
}
#endif


#if defined SOL_COMPILER
void TrFun_Assign::RefreshArgumentNames( const TrFunctions &declarations )
{
 expr->RefreshArgumentNames(declarations);
 return;
}
#endif

TrFunCall* TrFun_Assign::clone(void) const
{
 return new TrFun_Assign(*this);
}
