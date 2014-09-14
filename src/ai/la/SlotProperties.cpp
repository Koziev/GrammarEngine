#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/SlotProperties.h>

using namespace Solarix;


SlotProperties::SlotProperties() : left(false), right(false), key(false), obligatory(true), multiple(false)
{
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void SlotProperties::LoadTxt( Dictionary &dict, lem::Iridium::Macro_Parser & txtfile )
{
 if( txtfile.probe( B_OSPAREN ) )
  {
   obligatory=true;
   multiple=false;

   while( !txtfile.eof() )
   {
    lem::Iridium::BethToken t = txtfile.read();
    if( t.GetToken()==B_CSPAREN )
     break;

    if( t.GetToken()==B_COMMA )
     continue;

    if( t.string().eqi(L"optional") )
     obligatory=false;
    else if( t.string().eqi(L"multiple") )
     multiple=true;
    else
     {
      lem::Iridium::Print_Error(t,txtfile);
      dict.GetIO().merr().printf( "Unknown property [%vfE%us%vn]\n", t.string().c_str() );
      throw E_ParserError();
     }
   }
  }

 return;
}
#endif
