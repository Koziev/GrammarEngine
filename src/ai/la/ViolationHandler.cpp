#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/ViolationHandler.h>

using namespace Solarix;

#if defined SOL_COMPILER && defined SOL_LOADTXT
void ViolationHandler::LoadTxt( lem::Iridium::Macro_Parser & txtfile )
{
 if( txtfile.probe( B_OSPAREN ) )
  {
   txtfile.read_it( B_SUB );
   violation_score = -txtfile.read_int();
   txtfile.probe( B_CSPAREN );
  }
 else
  {
   violation_score=0;
  }

 return;
}
#endif
