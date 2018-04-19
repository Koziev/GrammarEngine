#include <lem/solarix/TreeMatchingExperience.h>

using namespace Solarix;

TreeMatchingExperience::~TreeMatchingExperience()
{
    Clear();
    return;
}

void TreeMatchingExperience::ClearPatternMatchings()
{
    for (auto& it : key2item)
    {
        TreeMatchingExperienceItem * ptr = it.second;
        delete ptr;
    }
    key2item.clear();


    for (auto& it : fragment2item)
    {
        delete it.second;
    }
    fragment2item.clear();

    return;
}

void TreeMatchingExperience::Clear()
{
    ClearPatternMatchings();

    for (auto& it : kbid2item)
    {
        delete it.second;
    }
    kbid2item.clear();

    return;
}



bool TreeMatchingExperience::FindKBCheckerMatching(int id_facts, const lem::MCollect< const Solarix::Word_Form * > & arg_values, KB_CheckingResult * res) const
{
    LEM_CHECKIT_Z(id_facts != UNKNOWN);
    LEM_CHECKIT_Z(arg_values.size() > 0);

    typedef KBID2ITEM::const_iterator IT;
    std::pair<IT, IT> pit = kbid2item.equal_range(std::make_pair(id_facts, arg_values.front()));

    for (IT it = pit.first; it != pit.second; ++it)
    {
        if (arg_values == it->second->arg_values)
        {
            *res = it->second->res;
            return true;
        }
    }

    return false;
}


void TreeMatchingExperience::AddKBCheckerMatching(int id_facts, const lem::MCollect< const Solarix::Word_Form * > & arg_values, const KB_CheckingResult & res)
{
    LEM_CHECKIT_Z(id_facts != UNKNOWN);
    LEM_CHECKIT_Z(arg_values.size() > 0);

    TME_KBChecker * y = new TME_KBChecker(arg_values, res);
    kbid2item.insert(std::make_pair(std::make_pair(id_facts, arg_values.front()), y));
    return;
}


void TreeMatchingExperience::Add(int id_tree, const LexerTextPos * token, bool success, const lem::PtrCollect<SynPatternResult> &results)
{
    LEM_CHECKIT_Z(id_tree != UNKNOWN);
    LEM_CHECKIT_Z(token != NULL);

    TreeMatchingExperienceKey key(id_tree, token);
    TreeMatchingExperienceItem *item = new TreeMatchingExperienceItem(success, results);

    auto it = key2item.find(key);
    if (it != key2item.end())
    {
        delete it->second;
        key2item.erase(key);
    }

    key2item.insert(std::make_pair(key, item));
    return;
}


void TreeMatchingExperience::Update(int id_tree, const LexerTextPos * token, bool success, const SynPatternResult & result)
{
    LEM_CHECKIT_Z(id_tree != UNKNOWN);
    LEM_CHECKIT_Z(token != nullptr);

    TreeMatchingExperienceKey key(id_tree, token);
    LEM_CHECKIT_Z(key2item.find(key) != key2item.end());

    TreeMatchingExperienceItem * item = key2item.find(key)->second;
    LEM_CHECKIT_Z(item->success == success);
    item->Add(result);

    return;
}





int TreeMatchingExperience::FindAccelerator(const LexerTextPos * token, int id_accel) const
{
    std::pair<const LexerTextPos*, int> key(token, id_accel);
    if (token_accel_success.find(key) != token_accel_success.end())
        return 1;

    if (token_accel_mismatch.find(key) != token_accel_mismatch.end())
        return 0;

    return -1;
}


void TreeMatchingExperience::StoreAccelerator(const LexerTextPos * token, int id_accel, bool result)
{
    if (result)
        token_accel_success.insert(std::make_pair(token, id_accel));
    else
        token_accel_mismatch.insert(std::make_pair(token, id_accel));

    return;
}



void TreeMatchingExperience::StoreMatchedFragment(const LexerTextPos * token, bool matched, const lem::PtrCollect<SynPatternResult> & results)
{
    LEM_CHECKIT_Z(token != nullptr);
    TreeMatchingExperienceItem *item = new TreeMatchingExperienceItem(matched, results);
    fragment2item.insert(std::make_pair(token, item));
    return;
}



bool TreeMatchingExperience::GetMatchedFragmentAt(const LexerTextPos * token, lem::PtrCollect<SynPatternResult> & results, bool * matched) const
{
    LEM_CHECKIT_Z(token != nullptr);
    FRAGMENT2ITEM::const_iterator it = fragment2item.find(token);
    if (it == fragment2item.end())
        return false;
    else
    {
        for (lem::Container::size_type i = 0; i < it->second->results.size(); ++i)
        {
            results.push_back(it->second->results[i]->Copy1(nullptr));
        }

        *matched = it->second->success;

        return true;
    }
}


