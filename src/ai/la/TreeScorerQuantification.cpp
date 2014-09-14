#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/TreeScorer.h>

using namespace Solarix;


#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorerQuantification::LoadTxt( lem::Iridium::Macro_Parser & txtfile )
{
 if( txtfile.probe( B_OSPAREN ) )
  {
   lem::Iridium::BethToken t1 = txtfile.read();

   int n1=0;
   int n2=MAX_COUNT;

   if( t1.GetToken()==B_NOT )
    {
     // Ветка [not] представляет собой требования отсутствия и хранится через
     // пару -1,-1
     min_count=max_count=-1;
    }
   else
    {
     if( lem::is_int(t1.string()) )
      {
       n1 = lem::to_int(t1.string());
      }
     else
      {
       txtfile.seekp(t1); // [,1] эквивалентно [0,1]
      }
  
     if( txtfile.probe( B_COMMA ) )
      {
       lem::Iridium::BethToken t2 = txtfile.read();
       if( lem::is_int(t2.string()) )
        n2 = lem::to_int(t2.string());
       else
        txtfile.seekp(t2);
      }
     else
      {
       n2 = n1; // [1] эквивалентно [1,1]
      }
  
     min_count = n1;
     max_count = n2;
    }

   txtfile.read_it( B_CSPAREN );
  }

 return;
}
#endif
