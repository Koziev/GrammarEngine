#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPattern.h>

using namespace lem;
using namespace Solarix;


#if defined SOL_COMPILER && defined SOL_LOADTXT
ExportCoordFunction* ExportCoordFunction::load_txt(
                                                   Dictionary &dict,
                                                   lem::Iridium::Macro_Parser & txtfile,
                                                   const SynPatterns & pattern_declarations,
                                                   SynPatternCompilation & compilation_context,
                                                   const SynPatternPoint & point
                                                  )
{
 ExportCoordFunction * res = NULL;

 lem::Iridium::BethToken function_name = txtfile.read();
 if( function_name.string().eqi( L"except" ) )
  res = new ExportCoordFunction_Except();
 else if( function_name.string().eqi( L"if_contains" ) )
  res = new ExportCoordFunction_IfContains();
 else if( function_name.string().eqi( L"if_exported" ) )
  res = new ExportCoordFunction_IfExported();
 else if( function_name.string().eqi( L"add" ) )
  res = new ExportCoordFunction_Add();
 else if( function_name.string().eqi( L"remove" ) )
  res = new ExportCoordFunction_Remove();
 else
  {
   dict.GetIO().merr().printf( "Unknown function '%us' in export section\n", function_name.string().c_str() );
   lem::Iridium::Print_Error(function_name,txtfile);
   throw lem::E_BaseException();
  }

 res->LoadTxt( dict, txtfile, pattern_declarations, compilation_context, point );
 return res;
}
#endif



ExportCoordFunction* ExportCoordFunction::load_bin( lem::Stream & bin )
{
 ExportCoordFunction * res=NULL;

 const int t = bin.read_int();
 switch(t)
 {
  case ExportCoordFunction::ECF_Except:     res = new ExportCoordFunction_Except(); break;
  case ExportCoordFunction::ECF_IfContains: res = new ExportCoordFunction_IfContains(); break;
  case ExportCoordFunction::ECF_IfExported: res = new ExportCoordFunction_IfExported(); break;
  case ExportCoordFunction::ECF_Add:        res = new ExportCoordFunction_Add(); break;
  case ExportCoordFunction::ECF_Remove:     res = new ExportCoordFunction_Remove(); break;
  default:LEM_STOPIT;
 }

 LEM_CHECKIT_Z(res!=NULL);

 res->LoadBin(bin);

 return res;
}

void ExportCoordFunction::SaveBin( lem::Stream & bin ) const
{
 bin.write_int(type);
}


bool ExportCoordFunction::Equals( const ExportCoordFunction & y ) const
{
 return type==y.type;
}

