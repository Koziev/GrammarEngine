#include <lem/macros.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/SG_Coordinates.h>
#include <lem/solarix/SG_CoordEnumerator.h>

using namespace Solarix;


SG_CoordEnumerator::SG_CoordEnumerator( LexiconStorage *_db, SG_Coordinates * _p )
 : rs(NULL), db(_db), p(_p)
{
}

SG_CoordEnumerator::~SG_CoordEnumerator(void)
{
 lem_rub_off(rs);
 return;
}

bool SG_CoordEnumerator::Fetch(void)
{
 if( rs==NULL )
  {
   rs = db->ListCoords();
  }

 return rs->Fetch();
}

int SG_CoordEnumerator::GetId(void)
{
 return rs->GetInt(0);
}

const GramCoord& SG_CoordEnumerator::GetItem(void)
{
 const int id = rs->GetInt(0);
 return (*p)[id]; 
}

