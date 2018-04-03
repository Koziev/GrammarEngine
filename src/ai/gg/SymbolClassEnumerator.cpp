#include <lem/solarix/gg_autom.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/SymbolClassEnumerator.h>

using namespace Solarix;

SymbolClassEnumerator::SymbolClassEnumerator(AlphabetStorage *_db, GraphGram *_gg)
    : rs(nullptr), db(_db), gg(_gg)
{
}

SymbolClassEnumerator::~SymbolClassEnumerator(void)
{
    lem_rub_off(rs);
    return;
}


bool SymbolClassEnumerator::Fetch(void)
{
    if (rs == nullptr)
    {
        rs = db->ListClasses();
    }

    return rs->Fetch();
}


int SymbolClassEnumerator::GetId(void)
{
    return rs->GetInt(0);
}

const GramClass& SymbolClassEnumerator::GetItem(void)
{
    const int id = rs->GetInt(0);
    return (const GramClass&)gg->classes()[id];
}

