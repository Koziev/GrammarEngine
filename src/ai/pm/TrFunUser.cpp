#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;


TrFun_User::TrFun_User(void)
 : TrFunCall(TrFunCall::User), fun(NULL), body(NULL)
{
}


TrFun_User::TrFun_User( const TrFun_User & x )
 : TrFunCall(x)
{
 ret_type = x.ret_type;
 name = x.name;
 arg_name = x.arg_name;
 arg_expr = x.arg_expr;
 body = x.body;
 fun = x.fun;
 return;
}


void TrFun_User::operator=( const TrFunCall & x )
{
 TrFunCall::operator=(x);
 ret_type = ((const TrFun_User&)x).ret_type;
 name = ((const TrFun_User&)x).name;
 arg_name = ((const TrFun_User&)x).arg_name;
 arg_expr = ((const TrFun_User&)x).arg_expr;
 body = ((const TrFun_User&)x).body;
 fun  = ((const TrFun_User&)x).fun; 
 return;
}


#if defined SOL_COMPILER
void TrFun_User::RefreshArgumentNames( const TrFunctions &declarations )
{
 // Ищем в окончательных объявлениях свою сигнатуру и проставляем имена переменных вызова.
 // Это необходимо, так как первоначальная версия вызова может быть скомпилирована с
 // использованием предварительного объявления функции, в котором указаны другием имена формальных
 // аргументов.

 const TrFunction *f = declarations.Find(name);
 if( f==NULL )
  LEM_STOPIT;

 if( f->arg_name.size()!=arg_name.size() )
  LEM_STOPIT;

 arg_name = f->arg_name;

 for( lem::Container::size_type i=0; i<arg_expr.size(); ++i )
  arg_expr[i]->RefreshArgumentNames(declarations);
 
 return;
}
#endif


#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_User::Run(
                                  const ElapsedTimeConstraint & constraints,
                                  PM_Automat &pm,
                                  TrFunContext &ctx,
                                  TrTrace *trace_log
                                 ) const
{
 LEM_CHECKIT_Z( fun!=NULL );
 LEM_CHECKIT_Z( body!=NULL );

 #if defined SOL_DEBUGGING
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );
 #endif

 TrContextInvokation ctx2( &ctx );

 for( lem::Container::size_type i=0; i<arg_name.size(); ++i )
  {
   ctx2.arg_name.push_back( arg_name[i] );
   ctx2.arg_value.push_back( new TrValue( arg_expr[i]->Run(constraints,pm,ctx,trace_log) ) );
  }

 // Добавляем особую скрытую переменную для передачи возвращаемого значения.
 ctx2.arg_name.push_back( L"((return))" );
 ctx2.arg_value.push_back( new TrTypeValue( ret_type ) );
 body->Run( constraints, pm, ctx2, trace_log );

 // Проверим, что для не-void функций сработал оператор return.
 if( !ret_type.IsVoid() && !ctx2.e_return )
  {
   throw E_BaseException( format_str(L"Missing 'return xxx' statement in function [%s]", name.c_str() ) );
  }

 #if defined SOL_DEBUGGING
 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );
 #endif

 return lem::Ptr<TrValue>( new TrValue(ctx2.GetVar(L"((return))") ) );
}
#endif



#if defined SOL_SAVEBIN
void TrFun_User::SaveBin( lem::Stream& bin ) const
{ 
 TrFunCall::SaveBin(bin);
 ret_type.SaveBin(bin);
 bin.write( &name, sizeof(name) );
 arg_name.SaveBin(bin);
 arg_expr.SaveBin(bin);
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrFun_User::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 ret_type.LoadBin(bin);
 bin.read( &name, sizeof(name) );
 arg_name.LoadBin(bin);
 arg_expr.LoadBin(bin);
 return;
}

void TrFun_User::Link( const TrFunctions &funs )
{
 fun = funs.Find(name);
 body = &*fun->body;

 for( lem::Container::size_type i=0; i<arg_expr.size(); ++i )
  arg_expr[i]->Link(funs);

 return; 
}
#endif



TrFunCall* TrFun_User::clone(void) const
{
 return new TrFun_User(*this);
}

