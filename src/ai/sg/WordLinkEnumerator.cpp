#include <lem/solarix/sg_autom.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/WordLinkEnumerator.h>

using namespace Solarix;

WordLinkEnumerator::WordLinkEnumerator(SG_Net *th)
    : ekey1(UNKNOWN), thesaurus(th), link_type(UNKNOWN)
{
    rs = NULL;
    ekey1_field = ekey2_field = link_type_field = tags_field = UNKNOWN;
    return;
}


WordLinkEnumerator::WordLinkEnumerator(SG_Net *th, int _ekey1)
    : ekey1(_ekey1), thesaurus(th), link_type(UNKNOWN)
{
    rs = NULL;
    ekey1_field = ekey2_field = link_type_field = tags_field = UNKNOWN;
    return;
}

WordLinkEnumerator::WordLinkEnumerator(SG_Net *th, int _ekey1, int _link_type)
    : ekey1(_ekey1), thesaurus(th), link_type(_link_type)
{
    rs = NULL;
    ekey1_field = ekey2_field = link_type_field = tags_field = UNKNOWN;
    return;
}

WordLinkEnumerator::~WordLinkEnumerator()
{
    lem_rub_off(rs);
    return;
}


bool WordLinkEnumerator::Fetch()
{
    if (rs == nullptr)
    {
        if (ekey1 == UNKNOWN)
        {
            rs = thesaurus->GetStorage().ListWordLinks();
            ekey1_field = 1;
            ekey2_field = 2;
            link_type_field = 4;
            tags_field = 5;
        }
        else if (link_type == UNKNOWN)
        {
            rs = thesaurus->GetStorage().ListWordLinks(ekey1);
            ekey2_field = 1;
            link_type_field = 3;
            tags_field = 4;
        }
        else
        {
            rs = thesaurus->GetStorage().ListWordLinks(ekey1, link_type);
            ekey2_field = 1;
            tags_field = 2;
        }
    }

    return rs->Fetch();
}


int WordLinkEnumerator::GetLinkId()
{
    return rs->GetInt(0);
}

int WordLinkEnumerator::GetEntryKey1()
{
    if (ekey1 == UNKNOWN)
        return rs->GetInt(ekey1_field);
    else
        return ekey1;
}


int WordLinkEnumerator::GetEntryKey2()
{
    return rs->GetInt(ekey2_field);
}


int WordLinkEnumerator::GetLinkType()
{
    if (link_type == UNKNOWN)
        return rs->GetInt(link_type_field);
    else
        return link_type;
}

int WordLinkEnumerator::GetTagsId()
{
    const int id_tags = rs->GetInt(tags_field);
    return id_tags;
}


SG_TagsList WordLinkEnumerator::GetTags()
{
    const int id_tags = rs->GetInt(tags_field);
    return thesaurus->GetWordLinkTags(id_tags, GetLinkId());
}
