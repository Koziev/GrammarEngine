#include <lem/solarix/LA_PreprocessorTokRule.h>
#include <lem/solarix/TokenSplitterRx.h>

using namespace Solarix;


TokenSplitterRx::TokenSplitterRx(const LA_PreprocessorTokRule * rule)
{
    LEM_CHECKIT_Z(rule->IsRegex());
    LEM_CHECKIT_Z(rule->GetLeft().size() == 1);
    LEM_CHECKIT_Z(rule->GetRight().size() > 0);

    source_rule = rule;
    greedy = rule->IsGreedy();
    rx_condition = &rule->GetLeft().front()->rx_condition;

    return;
}


bool TokenSplitterRx::Apply(const lem::UCString & word, lem::MCollect<lem::UCString> & result) const
{
    boost::wcmatch matches;
    if (boost::regex_match(word.c_str(), matches, *rx_condition))
    {
        result.clear();

        for (lem::Container::size_type i = 0; i < source_rule->GetRight().size(); ++i)
        {
            const lem::UFString & rtok = source_rule->GetRight()[i]->condition;
            if (rtok.front() == L'?')
            {
                const int idx = lem::to_int(rtok.c_str() + 1);
                std::wstring w(matches[idx].first, matches[idx].second);
                result.push_back(lem::UCString(w.c_str()));
            }
            else
            {
                result.push_back(lem::UCString(rtok.c_str()));
            }
        }

        return true;
    }
    else
        return false;
}

