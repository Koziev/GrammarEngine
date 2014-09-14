#if defined SOLARIX_PRO && !defined SOL_NO_AA

#include <lem/solarix/pm_autom.h>
#include <lem/solarix/translation.h>

using namespace lem;
using namespace Solarix;

#if defined SOL_LOADTXT && defined SOL_COMPILER
void TrType::LoadTxt(
                     PM_Automat &pm,
                     lem::Iridium::Macro_Parser &txtfile,
                     const TrFunctions &funs
                    )
{
 is_const = txtfile.probe( L"const" );

 const lem::Iridium::BethToken& t = txtfile.read();

 if( t.string().eqi( L"bool" ) )
  type = Bool;
 else if( t.string().eqi( L"int" ) )
  type = Int;
 else if( t.string().eqi( L"string" ) )
  type = String;
 else if( t.string().eqi( L"tree" ) )
  type = Tree;
 else if( t.string().eqi( L"trees" ) )
  type = Trees;
 else if( t.string().eqi( L"fun" ) )
  type = Fun;
 else if( t.string().eqi( L"void" ) )
  type = Void;
 else if( t.string().eqi( L"variant" ) )
  type = Variant;
 else if( t.string().eqi( L"tuple" ) )
  type = Tuple;
 else
  {
   lem::Iridium::Print_Error( t, txtfile );
   pm.GetIO().merr().printf( "Unknown type [%us]\n", t.string().c_str() );
   throw E_ParserError();
  }

 return; 
}
#endif


#if defined SOL_SAVEBIN
void TrType::SaveBin( lem::Stream& bin ) const
{
 bin.write( &is_const, sizeof(is_const) );
 bin.write( &type, sizeof(type) );
 return;
}
#endif

#if defined SOL_LOADBIN 
void TrType::LoadBin( lem::Stream& bin )
{
 bin.read( &is_const, sizeof(is_const) );
 bin.read( &type, sizeof(type) );
 return;
}
#endif


lem::UFString TrType::GetName(void) const
{
 lem::UFString res;

 if( is_const )
  res += "const ";

 switch(type)
 {
  case Variant: res +=L"variant"; break;
  case Void: res +=L"void"; break;
  case Bool: res +=L"bool"; break;
  case Int: res +=L"int"; break;
  case String: res +=L"string"; break;
  case Tree: res +=L"tree"; break;
  case Trees: res +=L"trees"; break;
  case Fun: res +=L"fun"; break;
  case Tuple: res +=L"tuple"; break;
 }

 return res;
}


#endif
