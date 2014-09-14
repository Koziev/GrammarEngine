#include <lem/solarix/CriteriaInFile.h>
#include <lem/solarix/CriterionEnumeratorInFile.h>

using namespace Solarix;

CriterionEnumeratorInFile::CriterionEnumeratorInFile( const CriteriaInFile *_criteria )
 : criteria(_criteria), i(-1)
{
}

bool CriterionEnumeratorInFile::Fetch(void)
{
 i++;
 return i<CastSizeToInt(criteria->list.size());
}

int CriterionEnumeratorInFile::GetId(void)
{
 return i;
}

const Criterion& CriterionEnumeratorInFile::GetItem(void)
{
 return criteria->list[i];
}
