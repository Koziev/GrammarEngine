#include <lem/solarix/pm_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/translation.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tr_funs.h>

using namespace lem;
using namespace Solarix;


TrFunCall::TrFunCall( int Type ) : type(Type), src_location(UNKNOWN)
{}

TrFunCall::TrFunCall( const TrFunCall& x ) : type( x.type ), src_location(x.src_location)
{}

void TrFunCall::operator=( const TrFunCall &x )
{
 type=x.type;
 src_location=x.src_location;
 return;
}


#if defined SOL_SAVEBIN
void TrFunCall::SaveBin( lem::Stream& bin ) const
{
 bin.write_int(type);
 bin.write_int(src_location);
 return;
}
#endif


#if defined SOL_LOADBIN 
void TrFunCall::LoadBin( lem::Stream& bin )
{
 src_location = bin.read_int();
 return;
}
#endif


#if defined SOL_LOADBIN 
TrFunCall* TrFunCall::load_bin( lem::Stream& bin )
{
 TrFunCall *res = NULL;

 const int type=bin.read_int();
 switch(type)
 {
  case Var: res = new TrFun_Var; break;
  case Constant: res = new TrFun_Constant; break; 
  case Assign: res = new TrFun_Assign; break; 
  case Group: res = new TrFun_Group; break; 
  case User: res = new TrFun_User; break; 
  case Return: res = new TrFun_Return; break; 
  case Declare: res = new TrFun_Declare; break;
  case If: res = new TrFun_If; break; 
  case While: res = new TrFun_While; break; 
  case For: res = new TrFun_For; break; 
  case Break: res = new TrFun_Break; break; 
  case BuiltIn: res = new TrFun_BuiltIn; break; 
  case CreateWordform: res = new TrFun_CreateWordform; break; 
  case Lambda: res = new TrFun_Lambda; break; 

  default: LEM_STOPIT;
 }

 res->LoadBin(bin);
 return res;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrFunCall::CompileDeclaration(
                                   PM_Automat &pm,
                                   lem::Iridium::Macro_Parser &txtfile,
                                   TrFunctions &functions,
                                   TrKnownVars &known_vars,
                                   const TrBuiltInFunSignature *signature  
                                  )
{
 src_location = pm.GetDict().GetDebugSymbols().RegisterLocation( txtfile, txtfile.tellp() );
 return;
}
#endif
