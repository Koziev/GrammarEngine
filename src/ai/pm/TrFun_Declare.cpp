#include <lem/solarix/pm_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;


TrFun_Declare::TrFun_Declare(void)
 : TrFunCall(TrFunCall::Declare )
{
}

TrFun_Declare::TrFun_Declare( const TrFun_Declare & x )
 : TrFunCall(x), var_type(x.var_type), var_name(x.var_name), var_value(x.var_value)
{
}

void TrFun_Declare::operator=( const TrFunCall & x )
{
 TrFunCall::operator=(x);
 var_name = ((const TrFun_Declare&)x).var_name;
 var_type = ((const TrFun_Declare&)x).var_type;
 var_value = ((const TrFun_Declare&)x).var_value;
 return;
}
   
#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_Declare::Run(
                                     const ElapsedTimeConstraint & constraints,
                                     PM_Automat &pm,
                                     TrFunContext &ctx,
                                     TrTrace *trace_log
                                    ) const
{
 const int mark = TrTraceActor::seq++;
 if( trace_log!=NULL )
  trace_log->Enter( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 for( lem::Container::size_type i=0; i<var_name.size(); ++i )
  {
   lem::Ptr<TrValue> v = var_value[i]==NULL ? lem::Ptr<TrValue>(new TrTypeValue(var_type)) : var_value[i]->Run(constraints,pm,ctx,trace_log);
   ctx.AddVar( var_name[i], v );
  }

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,false) );

 return lem::Ptr<TrValue>( new TrValue );
}
#endif

#if defined SOL_SAVEBIN
void TrFun_Declare::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);
 var_name.SaveBin(bin);
 var_type.SaveBin(bin);
 var_value.SaveBin(bin);
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrFun_Declare::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 var_name.LoadBin(bin);
 var_type.LoadBin(bin);
 var_value.LoadBin(bin);
 return;
}

void TrFun_Declare::Link( const TrFunctions &funs )
{
 for( lem::Container::size_type i=0; i<var_name.size(); ++i )
  {
   if( var_value[i]!=NULL )
    var_value[i]->Link(funs);
  }

 return;
}

#endif


#if defined SOL_COMPILER
void TrFun_Declare::RefreshArgumentNames( const TrFunctions &funs )
{
 for( lem::Container::size_type i=0; i<var_name.size(); ++i )
  {
   if( var_value[i]!=NULL )
    var_value[i]->RefreshArgumentNames(funs);
  }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrFun_Declare::CompileDeclaration(
                                       PM_Automat &pm,
                                       lem::Iridium::Macro_Parser &txtfile,
                                       TrFunctions &functions,
                                       const TrProcedureDeclaration &procs,
                                       TrKnownVars &known_vars,
                                       const TrBuiltInFunSignature *signature  
                                      )
{
 src_location = pm.GetDict().GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );
 var_type.LoadTxt(pm,txtfile,functions);

 while( !txtfile.eof() )
  {
   TrFunCall *expr = NULL;
   const lem::Iridium::BethToken &vname = txtfile.read();
   if( txtfile.pick().GetToken()==B_EQUAL )
    {
     txtfile.read();
     expr = functions.CompileCall( pm, txtfile, procs, known_vars );
    }

   if( var_name.find(vname.string())!=UNKNOWN )
    {
     lem::Iridium::Print_Error( vname, txtfile );
     pm.GetIO().merr().printf( "Variable [%us] is already declared", vname.c_str() );
     throw E_ParserError();
    }

   var_name.push_back(vname);
   var_value.push_back(expr);

   known_vars.RegisterVar( var_type, vname );

   if( txtfile.pick().GetToken()!=B_COMMA )
    break;  
    
   txtfile.read_it(B_COMMA);
  }

 txtfile.read_it(B_SEMICOLON);

 return;
}
#endif


TrFunCall* TrFun_Declare::clone(void) const
{
 return new TrFun_Declare(*this);
}
