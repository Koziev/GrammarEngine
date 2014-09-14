// LC->16.06.2011

#include <lem/solarix/pm_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;

TrFun_Group::TrFun_Group(void)
: TrFunCall( TrFunCall::Group )
{
}

   
TrFun_Group::TrFun_Group( const TrFun_Group & x )
: TrFunCall(x), items(x.items)
{
}

void TrFun_Group::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 items = ((const TrFun_Group&)x).items;
 return;
}


#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_Group::Run(
                                   const ElapsedTimeConstraint & constraints,
                                   PM_Automat &pm,
                                   TrFunContext &ctx,
                                   TrTrace *trace_log
                                  ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 TrContextInvokation ctx2( &ctx ); // чтобы ограничить область жизни переменных в блоке
 
 for( lem::Container::size_type i=0; i<items.size(); i++ )
  {
   const int mark2 = TrTraceActor::seq++;
   if( trace_log!=NULL )
    trace_log->Enter( new TrTraceFunGroupStep(mark2,items[i]->src_location,this,items[i],&ctx2) );

   items[i]->Run(constraints,pm,ctx2,trace_log);

   if( trace_log!=NULL )
    trace_log->Leave( new TrTraceFunGroupStep(mark2,items[i]->src_location,this,items[i],&ctx2) );

   if( ctx2.e_break )
    {
     // ѕрерывание распростран€етс€ по охватывающим блокам до тех пор,
     // пока его €вно не перехватит блок цикла или тела функции.
     ctx.e_break = ctx2.e_break;
     ctx.e_return = ctx2.e_return;
     break;
    }
  }
 
 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 lem::Ptr<TrValue> v( new TrValue );
 return v;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrFun_Group::CompileDeclaration(
                                     PM_Automat &pm,
                                     lem::Iridium::Macro_Parser &txtfile,
                                     TrFunctions &functions,
                                     const TrProcedureDeclaration &procs,
                                     TrKnownVars &known_vars,
                                     const TrBuiltInFunSignature *signature  
                                    )
{
 src_location = pm.GetDict().GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );
 txtfile.read_it( B_OFIGPAREN );

 TrKnownVars block_scope(&known_vars);
 
 while( !txtfile.eof() )
  {
   if( txtfile.pick().GetToken()==B_CFIGPAREN )
    break;

   if( txtfile.pick().GetToken()==B_SEMICOLON )
    {
     // —имволы ; игнорируем, они нужны в исключительных случа€х в тогда
     // считываютс€ €вным образом.
     txtfile.read();
     continue;
    }

   items.push_back( functions.CompileCall(pm,txtfile,procs,block_scope) );
  }

 txtfile.read_it( B_CFIGPAREN );
 return;
}
#endif

#if defined SOL_SAVEBIN
void TrFun_Group::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);
 items.SaveBin(bin);
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrFun_Group::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 items.LoadBin(bin);
 return;
}

void TrFun_Group::Link( const TrFunctions &functions )
{
 for( lem::Container::size_type i=0; i<items.size(); i++ )
  {
   items[i]->Link(functions);
  }

 return;
}

#endif


#if defined SOL_COMPILER
void TrFun_Group::RefreshArgumentNames( const TrFunctions &funs )
{
 for( lem::Container::size_type i=0; i<items.size(); i++ )
  {
   items[i]->RefreshArgumentNames(funs);
  }

 return;
}
#endif


TrFunCall* TrFun_Group::clone(void) const
{
 return new TrFun_Group(*this);
}

