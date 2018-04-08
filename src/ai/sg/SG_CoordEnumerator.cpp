#include <lem/macros.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/SG_Coordinates.h>
#include <lem/solarix/SG_CoordEnumerator.h>

using namespace Solarix;


SG_CoordEnumerator::SG_CoordEnumerator(LexiconStorage *_db, SG_Coordinates * _p)
    : rs(nullptr), db(_db), p(_p)
{
}

SG_CoordEnumerator::~SG_CoordEnumerator()
{
    lem_rub_off(rs);
    return;
}

bool SG_CoordEnumerator::Fetch()
{
    if (rs == nullptr)
    {
        rs = db->ListCoords();
    }

    return rs->Fetch();
}

int SG_CoordEnumerator::GetId()
{
    return rs->GetInt(0);
}

const GramCoord& SG_CoordEnumerator::GetItem()
{
    const int id = rs->GetInt(0);
    return (*p)[id];
}

