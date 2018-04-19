#if defined SOL_CAA

#include <lem/solarix/KnowledgeBase.h>

using namespace Solarix;

KB_CachedFacts::KB_CachedFacts(int _id) : id(_id)
{
    LEM_CHECKIT_Z(id != UNKNOWN);
}

KB_CheckingResult KB_CachedFacts::Match(Solarix::Dictionary * dict, const KB_Facts & group, const lem::MCollect<const Solarix::Word_Form*> & args) const
{
    for (lem::Container::size_type i = 0; i < facts.size(); ++i)
    {
        KB_CheckingResult res = facts[i]->Match(dict, group, args);
        if (res.IsMatched())
            return res;
    }

    return KB_NotMatchedResult();
}


void KB_CachedFacts::AddFact(KB_Fact * x)
{
    LEM_CHECKIT_Z(x != nullptr);
    facts.push_back(x);
    return;
}

#endif
