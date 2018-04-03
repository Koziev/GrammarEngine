#include <lem/solarix/LS_ResultSet.h>
#include <lem/solarix/SourceFilenameEnumerator.h>

using namespace Solarix;


SourceFilenameEnumerator::SourceFilenameEnumerator(LS_ResultSet * _rs)
    : rs(_rs)
{
}


SourceFilenameEnumerator::~SourceFilenameEnumerator()
{
    lem_rub_off(rs);
}


bool SourceFilenameEnumerator::Fetch()
{
    return rs->Fetch();
}


int SourceFilenameEnumerator::GetId()
{
    return rs->GetInt(0);
}


lem::Path SourceFilenameEnumerator::GetFilename()
{
    return lem::Path(rs->GetUFString(1));
}
