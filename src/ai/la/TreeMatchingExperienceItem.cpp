#include <lem/solarix/TreeMatchingExperience.h>

using namespace Solarix;

TreeMatchingExperienceItem::TreeMatchingExperienceItem(bool src_success, const lem::PtrCollect<SynPatternResult> &src)
{
    success = src_success;
    for (auto x : src)
    {
        results.push_back(x->Copy1(nullptr));
    }
}

void TreeMatchingExperienceItem::Add(const SynPatternResult & src)
{
    results.push_back(src.Copy1(nullptr));
    return;
}



void TreeMatchingExperienceItem::Copy(const BackTrace *parent_trace, lem::PtrCollect<SynPatternResult> &ext) const
{
    for (auto result : results)
    {
        ext.push_back(result->Copy1(parent_trace));
    }

    return;
}
