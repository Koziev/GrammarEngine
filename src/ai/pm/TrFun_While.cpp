#include <lem/solarix/pm_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;


TrFun_While::TrFun_While(void)
 : TrFunCall( TrFunCall::While )
{
}


TrFun_While::TrFun_While( const TrFun_While & x )
 : TrFunCall(x), cond(x.cond->clone()), body(x.body->clone())
{
 return;
}




void TrFun_While::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 cond = ((const TrFun_While&)x).cond->clone();
 body = ((const TrFun_While&)x).body->clone();
 return;
}
   

#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_While::Run(
                                   const ElapsedTimeConstraint & constraints,
                                   PM_Automat &pm,
                                   TrFunContext &ctx,
                                   TrTrace *trace_log
                                  ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,true) );

 TrFunContext ctx2(&ctx);

 while( ctx2.e_break==false )
  {
   TrFunContext ctx3(&ctx);
   lem::Ptr<TrValue> v = cond->Run(constraints,pm,ctx3,trace_log);
   if( v->GetBool()==false )
    break;

   body->Run(constraints,pm,ctx2,trace_log);
  }

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,true) );

 return lem::Ptr<TrValue>( new TrValue ); 
}
#endif


#if defined SOL_SAVEBIN
void TrFun_While::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);
 cond->SaveBin(bin);
 body->SaveBin(bin);
  
 return;
}
#endif


#if defined SOL_LOADBIN 
void TrFun_While::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 cond = TrFunCall::load_bin(bin);
 body = TrFunCall::load_bin(bin);
 return;
}

void TrFun_While::Link( const TrFunctions &funs )
{
 cond->Link(funs);
 body->Link(funs);
 return;
}
#endif

#if defined SOL_COMPILER
void TrFun_While::RefreshArgumentNames( const TrFunctions &funs )
{
 cond->RefreshArgumentNames(funs);
 body->RefreshArgumentNames(funs);
 return;
}
#endif


TrFunCall* TrFun_While::clone(void) const
{
 return new TrFun_While(*this);
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
// while(x) ...
void TrFun_While::CompileDeclaration(
                                     PM_Automat &pm,
                                     lem::Iridium::Macro_Parser &txtfile,
                                     TrFunctions &functions,
                                     const TrProcedureDeclaration &procs,
                                     TrKnownVars &known_vars,
                                     const TrBuiltInFunSignature *signature  
                                    )
{
 src_location = pm.GetDict().GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );
 txtfile.read_it( B_OROUNDPAREN );
 cond = functions.CompileCall( pm, txtfile, procs, known_vars );
 txtfile.read_it( B_CROUNDPAREN );
 body = functions.CompileCall( pm, txtfile, procs, known_vars );
 return;
}
#endif

