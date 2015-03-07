#include <lem/solarix/sg_autom.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/BackRefCorrel.h>

using namespace Solarix;

void BackRefCorrel::SaveTxt( lem::OFormatter &txt, SynGram &sg ) const
{
 if( !affirmative )
  txt.printf( "!=" );
 else
  txt.printf( "=" );

 if( id_coord0==id_coord1 )
  {
   txt.printf( "%us:", name.c_str() );
  }
 else
  {
   txt.printf( "%us->%us:", sg.coords()[id_coord1].GetName().string().c_str(), name.c_str() );
  }

 if( for_group )
  {
   txt.printf( "[%us]", sg.coords()[id_coord0].GetName().string().c_str() );
  }
 else
  {
   txt.printf( "%us", sg.coords()[id_coord0].GetName().string().c_str() );
  } 

 return;
}
