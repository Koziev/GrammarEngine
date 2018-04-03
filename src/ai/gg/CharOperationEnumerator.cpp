#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/GG_CharOperations.h>
#include <lem/solarix/GG_CharOperation.h>
#include <lem/solarix/CharOperationEnumerator.h>

using namespace Solarix;

CharOperationEnumerator::CharOperationEnumerator( LS_ResultSet *RS, GG_CharOperations *OPERS )
 : rs(RS), operations(OPERS)
{
}

CharOperationEnumerator::~CharOperationEnumerator(void)
{
 lem_rub_off(rs);
}

bool CharOperationEnumerator::Fetch(void)
{
 return rs->Fetch();
}

const GG_CharOperation & CharOperationEnumerator::GetOperation(void)
{
 const int id = rs->GetInt(0);
 return *(*operations)[id];
}
 
