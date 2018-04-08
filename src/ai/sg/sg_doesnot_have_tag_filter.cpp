#include <lem/solarix/dictionary.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/sg_doesnot_have_tag_tagfilter.h>

using namespace lem;
using namespace Solarix;


TF_DoesNotHaveTag::TF_DoesNotHaveTag(const Dictionary &dict, const UCString & tag_name)
{
    itag = dict.GetSynGram().Get_Net().FindTag(tag_name);
    return;
}

bool TF_DoesNotHaveTag::Match(SG_TagsList x) const
{
    if (x == nullptr)
        return true;

    for (lem::Container::size_type i = 0; i < x->size(); ++i)
    {
        if (x->get(i).first == itag)
        {
            if (x->get(i).second > 1)
                return false;
        }
    }

    return true;
}

bool TF_DoesNotHaveTag::Empty() const
{
    return itag != UNKNOWN;
}
