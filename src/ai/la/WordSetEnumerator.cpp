#include <lem/macros.h>
#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/WordSetEnumerator.h>

using namespace Solarix;

WordSetEnumerator::WordSetEnumerator( LS_ResultSet *RS, WordEntrySet *Sets )
 : rs(RS), sets(Sets)
{
}

WordSetEnumerator::~WordSetEnumerator(void)
{
 lem_rub_off(rs);
}


bool WordSetEnumerator::Fetch(void)
{
 return rs->Fetch();
}

int WordSetEnumerator::GetId(void)
{
 return rs->GetInt(0);
}

const WordSetItem& WordSetEnumerator::GetItem(void)
{
 int id = rs->GetInt(0);
 return sets->GetWordSet(id);
}
