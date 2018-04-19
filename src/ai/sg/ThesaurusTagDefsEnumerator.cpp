#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/ThesaurusTagDefs.h>

using namespace Solarix;

ThesaurusTagDefsEnumerator::ThesaurusTagDefsEnumerator(ThesaurusTagDefs *x) : defs(x), rs(nullptr)
{
}


ThesaurusTagDefsEnumerator::~ThesaurusTagDefsEnumerator()
{
    lem_rub_off(rs);
    return;
}


bool ThesaurusTagDefsEnumerator::Fetch()
{
    if (rs == nullptr)
    {
        rs = defs->db->ListTagDefs();
    }

    return rs->Fetch();
}


int ThesaurusTagDefsEnumerator::GetId() const
{
    return rs->GetInt(0);
}

lem::UCString ThesaurusTagDefsEnumerator::GetName() const
{
    return rs->GetUCString(1);
}

