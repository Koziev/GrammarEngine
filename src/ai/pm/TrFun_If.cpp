#include <lem/solarix/pm_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;


TrFun_If::TrFun_If(void)
 : TrFunCall( TrFunCall::If )
{
}


TrFun_If::TrFun_If( const TrFun_If & x )
 : TrFunCall(x), cond(x.cond->clone()), f_then(x.f_then->clone())
{
 if( x.f_else.NotNull() )
  f_else = x.f_else->clone();

 return;
}




void TrFun_If::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 cond = ((const TrFun_If&)x).cond->clone();
 f_then = ((const TrFun_If&)x).f_then->clone();

 if( ((const TrFun_If&)x).f_else.NotNull() )
  f_else = ((const TrFun_If&)x).f_else->clone();
 else
  f_else.reset();

 return;
}
   

#if defined SOL_CAA
// Функция if возвращает в качестве результата значение, которое вернут then- или else-ветка,
// либо void.
lem::Ptr<TrValue> TrFun_If::Run(
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

 lem::Ptr<TrValue> ret;

 lem::Ptr<TrValue> v = cond->Run(constraints,pm,ctx,trace_log);
 if( v->GetBool() )
  {
   ret = f_then->Run(constraints,pm,ctx2,trace_log);
  }
 else if( f_else.NotNull() )
  {
   ret = f_else->Run(constraints,pm,ctx2,trace_log);
  }
 else
  {
   ret = new TrValue;
  }

 if( ctx2.e_break )
  {
   ctx.e_break = ctx2.e_break;
   ctx.e_return = ctx2.e_return;
  }

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,true) );

 return ret;
}
#endif


#if defined SOL_SAVEBIN
void TrFun_If::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);
 cond->SaveBin(bin);
 f_then->SaveBin(bin);
 bin.write_bool( f_else.NotNull() );
 if( f_else.NotNull() )
  f_else->SaveBin(bin);
  
 return;
}
#endif


#if defined SOL_LOADBIN 
void TrFun_If::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 cond = TrFunCall::load_bin(bin);
 f_then = TrFunCall::load_bin(bin);
 if( bin.read_bool() )
  f_else = TrFunCall::load_bin(bin);
 return;
}

void TrFun_If::Link( const TrFunctions &funs )
{
 cond->Link(funs);
 f_then->Link(funs);
 if( f_else.NotNull() )
  f_else->Link(funs);
 return;
}
#endif


#if defined SOL_COMPILER
void TrFun_If::RefreshArgumentNames( const TrFunctions &funs )
{
 cond->RefreshArgumentNames(funs);
 f_then->RefreshArgumentNames(funs);
 if( f_else.NotNull() )
  f_else->RefreshArgumentNames(funs);

 return;
}
#endif


TrFunCall* TrFun_If::clone(void) const
{
 return new TrFun_If(*this);
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
// if(x) then ... else ...
void TrFun_If::CompileDeclaration(
                                   PM_Automat &pm,
                                   lem::Iridium::Macro_Parser &txtfile,
                                   TrFunctions &functions,
                                   TrKnownVars &known_vars,
                                   const TrBuiltInFunSignature *signature  
                                  )
{
 src_location = pm.GetDict().GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );

 // Условие опционально может быть заключено в круглые скобочки.
 const bool req_paren = txtfile.probe( B_OROUNDPAREN );
 cond = functions.CompileCall( pm, txtfile, known_vars );
 if( req_paren )
  txtfile.read_it( B_CROUNDPAREN );

 txtfile.read_it( B_THEN );
 f_then = functions.CompileCall( pm, txtfile, known_vars );
 txtfile.probe( B_SEMICOLON );

 if( txtfile.pick().GetToken()==B_ELSE )
  {
   txtfile.read_it(B_ELSE);
   f_else = functions.CompileCall( pm, txtfile, known_vars );
   txtfile.probe( B_SEMICOLON );
  }

 return;
}
#endif

