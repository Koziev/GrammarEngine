#include <lem/solarix/LS_ResultSet_MCollectCref.h>

using namespace lem;
using namespace Solarix;

LS_ResultSet_MCollectCref::LS_ResultSet_MCollectCref(const lem::MCollect<int> &_list)
    : LS_ResultSet(nullptr), i(0), int_dataset(_list), n(CastSizeToInt(_list.size()))
{
    return;
}


bool LS_ResultSet_MCollectCref::Fetch()
{
    if (i < n - 1)
    {
        i++;
        return true;
    }
    else
    {
        return false;
    }
}


int LS_ResultSet_MCollectCref::GetInt(int FieldIndex)
{
    LEM_CHECKIT_Z(FieldIndex == 0);
    return int_dataset[i];
}


lem::UCString LS_ResultSet_MCollectCref::GetUCString(int FieldIndex)
{
    LEM_STOPIT;
    return UCString();
}

lem::UFString LS_ResultSet_MCollectCref::GetUFString(int FieldIndex)
{
    LEM_STOPIT;
    return UFString();
}

lem::FString LS_ResultSet_MCollectCref::GetFString(int FieldIndex)
{
    LEM_STOPIT;
    return FString();
}
