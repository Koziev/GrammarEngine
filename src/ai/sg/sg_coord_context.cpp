// -----------------------------------------------------------------------------
// File SG_COORD_CONTEXT.CPP
//
// (c) Koziev Elijah
//
// Content:
// Класс SG_CoordContext - информация о грамматическом классе и координатах.
// -----------------------------------------------------------------------------
//
// CD->09.08.2003
// LC->09.06.2011
// --------------

#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/Sg_CoordContext.h>

using namespace lem;
using namespace Solarix;

SG_CoordContext::SG_CoordContext(void)
{ iclass=UNKNOWN; }

SG_CoordContext::SG_CoordContext( int iClass, const Solarix::CP_Array &Coords )
{ iclass=iClass; coords=Coords; }

SG_CoordContext::SG_CoordContext( const SG_CoordContext &x )
{ iclass=x.iclass; coords=x.coords; }

void SG_CoordContext::operator=( const SG_CoordContext &x )
{ iclass=x.iclass; coords=x.coords; }

void SG_CoordContext::SaveTxt( OFormatter &txt, SynGram &sg ) const
{
 const UCString &class_name = sg.classes()[iclass].GetName();

 txt.printf(
            " %us:\"???\" { "
            , class_name.c_str()
           );

 for( Container::size_type k=0; k<coords.size(); k++ )
  {
   const int icoord = coords[k].GetCoord().GetIndex();
   const int istate = coords[k].GetState();

   const UCString &coord_name = sg.coords()[ icoord ].GetName().front();

   if( !sg.coords()[icoord].states().size() )
    {
     if( istate!=0 )
      txt.printf( " %us", coord_name.c_str() );
     else
      txt.printf( " ~%us", coord_name.c_str() );
    }
   else
    {
     const UCString &state_name = sg.coords()[ icoord ].GetStateName( istate );
     txt.printf( " %us:%us", coord_name.c_str(), state_name.c_str() );
    }
  }

 txt.printf( " }" );

 return;
}


#if defined SOL_LOADTXT
/*************************************************************************
***************************************************************************/
void SG_CoordContext::LoadTxt( Macro_Parser &txtfile, const SynGram &gram )
{
 return;
}
#endif
