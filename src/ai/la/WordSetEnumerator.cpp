#include <lem/macros.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/WordSetEnumerator.h>

using namespace Solarix;

WordSetEnumerator::WordSetEnumerator(LS_ResultSet *RS, WordEntrySet *Sets)
    : rs(RS), sets(Sets)
{
}

WordSetEnumerator::~WordSetEnumerator()
{
    lem_rub_off(rs);
}


bool WordSetEnumerator::Fetch()
{
    return rs->Fetch();
}

int WordSetEnumerator::GetId()
{
    return rs->GetInt(0);
}

const WordSetItem& WordSetEnumerator::GetItem()
{
    int id = rs->GetInt(0);
    return sets->GetWordSet(id);
}
