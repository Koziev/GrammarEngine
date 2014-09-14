#include <lem/macros.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/WordEntrySetEnumerator.h>

using namespace Solarix;

WordEntrySetEnumerator::WordEntrySetEnumerator( LS_ResultSet *RS, WordEntrySet *Sets )
 : rs(RS), sets(Sets)
{
}

WordEntrySetEnumerator::~WordEntrySetEnumerator(void)
{
 lem_rub_off(rs);
}


bool WordEntrySetEnumerator::Fetch(void)
{
 return rs->Fetch();
}

int WordEntrySetEnumerator::GetId(void)
{
 return rs->GetInt(0);
}

const WordEntrySetItem& WordEntrySetEnumerator::GetItem(void)
{
 int id = rs->GetInt(0);
 return sets->GetWordEntrySet(id);
}
