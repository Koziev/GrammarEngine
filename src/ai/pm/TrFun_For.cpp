#include <lem/solarix/pm_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/tr_funs.h>
#include <lem/solarix/tr_trace_actors.h>

using namespace lem;
using namespace Solarix;


TrFun_For::TrFun_For(void)
 : TrFunCall( TrFunCall::For )
{
}


TrFun_For::TrFun_For( const TrFun_For & x )
 : TrFunCall(x), varname(x.varname), i0(x.i0->clone()), i1(x.i1->clone()),
   step(x.step->clone()), body(x.body->clone())
{
 return;
}




void TrFun_For::operator=( const TrFunCall & x )
{
 TrFunCall::operator =(x);
 varname = ((const TrFun_For&)x).varname;
 i0 = ((const TrFun_For&)x).i0->clone();
 i1 = ((const TrFun_For&)x).i1->clone();
 step = ((const TrFun_For&)x).step->clone();
 body = ((const TrFun_For&)x).body->clone();
 return;
}
   

#if defined SOL_CAA
lem::Ptr<TrValue> TrFun_For::Run(
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

 lem::Ptr<TrValue> i = ctx.GetVar(varname);
 lem::Ptr<TrValue> from = i0->Run(constraints,pm,ctx2,trace_log);
 lem::Ptr<TrValue> to = i1->Run(constraints,pm,ctx2,trace_log);
 lem::Ptr<TrValue> di = step->Run(constraints,pm,ctx2,trace_log);

 int ii0 = from->GetInt();
 int ii1 = to->GetInt();
 int dii = di->GetInt();

 if( dii>0 )
  {
   for( int k=ii0; k<=ii1; k+=dii )
    {
     if( ctx2.e_break==true )
      break;

     TrIntValue a(k);
     i->Assign(a);

     body->Run( constraints, pm, ctx2, trace_log );
    }
  }
 else
  {
   for( int k=ii0; k>=ii1; k+=dii )
    {
     if( ctx2.e_break==true )
      break;

     TrIntValue a(k);
     i->Assign(a);

     body->Run( constraints, pm, ctx2, trace_log );
    }
  }


 // Оператор break мы поглощаем, а return пропускаем во внешний блок.
 if( ctx2.e_return )
  {
   ctx.e_break = ctx2.e_break;
   ctx.e_return = ctx2.e_return;
  }

 if( trace_log!=NULL )
  trace_log->Leave( new TrTraceFunCall(mark,src_location,this,&ctx,true) );

 return lem::Ptr<TrValue>( new TrValue ); 
}
#endif


#if defined SOL_SAVEBIN
void TrFun_For::SaveBin( lem::Stream& bin ) const
{
 TrFunCall::SaveBin(bin);

 bin.write( &varname, sizeof(varname) );
 i0->SaveBin(bin);
 i1->SaveBin(bin);
 step->SaveBin(bin);
 body->SaveBin(bin);
  
 return;
}
#endif


#if defined SOL_LOADBIN 
void TrFun_For::LoadBin( lem::Stream& bin )
{
 TrFunCall::LoadBin(bin);
 bin.read( &varname, sizeof(varname) );
 i0 = TrFunCall::load_bin(bin);
 i1 = TrFunCall::load_bin(bin);
 step = TrFunCall::load_bin(bin);
 body = TrFunCall::load_bin(bin);
 return;
}

void TrFun_For::Link( const TrFunctions &funs )
{
 i0->Link(funs);
 i1->Link(funs);
 step->Link(funs);
 body->Link(funs);

 return;
}
#endif

#if defined SOL_COMPILER
void TrFun_For::RefreshArgumentNames( const TrFunctions &funs )
{
 i0->RefreshArgumentNames(funs);
 i1->RefreshArgumentNames(funs);
 step->RefreshArgumentNames(funs);
 body->RefreshArgumentNames(funs);

 return;
}
#endif


TrFunCall* TrFun_For::clone(void) const
{
 return new TrFun_For(*this);
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
// for i=i0 to i1 step di
void TrFun_For::CompileDeclaration(
                                   PM_Automat &pm,
                                   lem::Iridium::Macro_Parser &txtfile,
                                   TrFunctions &functions,
                                   const TrProcedureDeclaration &procs,
                                   TrKnownVars &known_vars,
                                   const TrBuiltInFunSignature *signature  
                                  )
{
 src_location = pm.GetDict().GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );
 const lem::Iridium::BethToken &vn = txtfile.read();
 if( !known_vars.IsVariable(vn) )
  {
   lem::Iridium::Print_Error( vn, txtfile );
   pm.GetIO().merr().printf( "Unknown variable [%us]\n", vn.c_str() );
   throw E_ParserError();
  }

 varname = vn;
  
 txtfile.read_it( B_EQUAL );

 i0 = functions.CompileCall( pm, txtfile, procs, known_vars );
 txtfile.read_it( L"to" );
 i1 = functions.CompileCall( pm, txtfile, procs, known_vars );

 if( txtfile.pick().eqi(L"step") )
  {
   txtfile.read();
   step = functions.CompileCall( pm, txtfile, procs, known_vars );
  }
 else
  {
   TrIntValue v1(1);
   TrFun_Constant *s = new TrFun_Constant( v1 );
   step = s;
  } 

 body = functions.CompileCall( pm, txtfile, procs, known_vars );

 return;
}
#endif

