#include <lem/macros.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/GG_Coordinates.h>
#include <lem/solarix/GG_CoordEnumerator.h>

using namespace Solarix;


GG_CoordEnumerator::GG_CoordEnumerator( AlphabetStorage *_db, GG_Coordinates * _p )
 : rs(nullptr), db(_db), p(_p)
{
}

GG_CoordEnumerator::~GG_CoordEnumerator(void)
{
 lem_rub_off(rs);
 return;
}

bool GG_CoordEnumerator::Fetch(void)
{
 if( rs==nullptr )
  {
   rs = db->ListCoords();
  }

 return rs->Fetch();
}

int GG_CoordEnumerator::GetId(void)
{
 return rs->GetInt(0);
}

const GramCoord& GG_CoordEnumerator::GetItem(void)
{
 const int id = rs->GetInt(0);
 return (*p)[id]; 
}

