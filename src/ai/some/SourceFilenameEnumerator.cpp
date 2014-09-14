#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/SourceFilenameEnumerator.h>

using namespace Solarix;


SourceFilenameEnumerator::SourceFilenameEnumerator( LS_ResultSet * _rs )
 : rs(_rs)
{
}


SourceFilenameEnumerator::~SourceFilenameEnumerator(void)
{
 lem_rub_off(rs);
}


bool SourceFilenameEnumerator::Fetch(void)
{
 return rs->Fetch();
}


int SourceFilenameEnumerator::GetId(void)
{
 return rs->GetInt(0);
}


lem::Path SourceFilenameEnumerator::GetFilename(void)
{
 return lem::Path(rs->GetUFString(1));
}
