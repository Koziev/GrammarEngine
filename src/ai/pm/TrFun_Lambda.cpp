#include <lem/solarix/pm_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;

#if defined SOL_LOADTXT && defined SOL_COMPILER
TrFun_Lambda::TrFun_Lambda( const TrFunction *Lambda, const MCollect<UCString> &_locals )
 : TrFunCall(TrFunCall::Lambda), fun(Lambda), body(NULL), locals(_locals)
{
 name = Lambda->GetName();
 return;
}
#endif


TrFun_Lambda::TrFun_Lambda(void)
 : TrFunCall(TrFunCall::Lambda), fun(NULL), body(NULL)
{
}


TrFun_Lambda::TrFun_Lambda( const TrFun_Lambda & x )
 : TrFunCall(x)
{
 ret_type = x.ret_type;
 name = x.name;
 arg_name = x.arg_name;
 body = x.body;
 fun = x.fun;
 locals = x.locals;
 return;
}


void TrFun_Lambda::operator=( const TrFunCall & x )
{
 TrFunCall::operator=(x);
 ret_type = ((const TrFun_Lambda&)x).ret_type;
 name = ((const TrFun_Lambda&)x).name;
 arg_name = ((const TrFun_Lambda&)x).arg_name;
 body = ((const TrFun_Lambda&)x).body;
 fun  = ((const TrFun_Lambda&)x).fun; 
 locals  = ((const TrFun_Lambda&)x).locals; 
 return;
}
   

#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_Lambda::Run(
                                    const ElapsedTimeConstraint & constraints,
                                    PM_Automat &pm,
                                    TrFunContext &ctx,
                                    TrTrace *trace_log
                                   ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 TrClosureVars *cv = new TrClosureVars;

 // Значения используемых локальных переменных известны в данном контексте.
 for( lem::Container::size_type i=0; i<locals.size(); ++i )
  {
   lem::Ptr<TrValue> var = ctx.GetVar(locals[i]);
   cv->AddVar( locals[i], *var );
  }

 // Запомним также имена формальных аргументов вызова функции
 cv->arg_name = arg_name;

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 return lem::Ptr<TrValue>( new TrValue(body,cv) );
}
#endif




#if defined SOL_SAVEBIN
void TrFun_Lambda::SaveBin( lem::Stream& bin ) const
{ 
 TrFunCall::SaveBin(bin);
 ret_type.SaveBin(bin);
 bin.write( &name, sizeof(name) );
 arg_name.SaveBin(bin);
 locals.SaveBin(bin);
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrFun_Lambda::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 ret_type.LoadBin(bin);
 bin.read( &name, sizeof(name) );
 arg_name.LoadBin(bin);
 locals.LoadBin(bin);
 return;
}

void TrFun_Lambda::Link( const TrFunctions &funs )
{
 fun = funs.Find(name);
 body = &*fun->body;
 return; 
}
#endif



#if defined SOL_COMPILER
void TrFun_Lambda::RefreshArgumentNames( const TrFunctions &funs )
{
 return;
}
#endif


TrFunCall* TrFun_Lambda::clone(void) const
{
 return new TrFun_Lambda(*this);
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrFun_Lambda::CompileDeclaration(
                                      PM_Automat &pm,
                                      lem::Iridium::Macro_Parser &txtfile,
                                      TrFunctions &functions,
                                      TrKnownVars &known_vars,
                                      const TrBuiltInFunSignature *signature  
                                     )
{
 src_location = pm.GetDict().GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );
 ret_type = fun->ret_type;
 arg_name = fun->arg_name;
 return;
}
#endif
