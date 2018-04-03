#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/CriteriaInStorage.h>
#include <lem/solarix/CriterionEnumerator_SQL.h>

using namespace Solarix;

CriterionEnumerator_SQL::CriterionEnumerator_SQL(LS_ResultSet *_rs, CriteriaInStorage *_db)
    : rs(_rs), db(_db)
{
}

CriterionEnumerator_SQL::~CriterionEnumerator_SQL()
{
    delete rs;
}

bool CriterionEnumerator_SQL::Fetch()
{
    return rs->Fetch();
}

int CriterionEnumerator_SQL::GetId()
{
    return rs->GetInt(0);
}

const Criterion& CriterionEnumerator_SQL::GetItem()
{
    return (*db)[GetId()];
}
