#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/TokenSplitterRx.h>
#include <lem/solarix/LA_CropRule.h>
#include <lem/solarix/LA_PreprocessorTrace.h>
#include <lem/solarix/LA_Preprocessor.h>

using namespace Solarix;

LA_PreprocessorRules::~LA_PreprocessorRules()
{
    for (auto rule : crop_rules)
    {
        delete rule;
    }

    return;
}


bool LA_PreprocessorRules::Crop(
    const lem::UCString &word,
    lem::MCollect<lem::UCString> &results,
    lem::MCollect<lem::Real1> &rels,
    LA_RecognitionTrace *trace
) const
{
    bool applied = false;

    if (!crop_rules.empty())
    {
        // сначала применяем префиксные правила
        typedef CROP_RULES::const_iterator IT;

        LA_CropRule::HashType prefix_hash = LA_CropRule::CalcHash(word.c_str(), true, false);
        std::pair<IT, IT> pp = prefix_crop_rules.equal_range(prefix_hash);

        lem::UCString result;

        for (auto it = pp.first; it != pp.second; ++it)
        {
            const LA_CropRule *r = it->second;
            if (r->Apply(word, result))
            {
                applied = true;
                results.push_back(result);
                rels.push_back(r->GetRel());
                if (trace != nullptr)
                {
                    trace->CropRuleApplied(word, result, r);
                }
            }
        }

        // теперь отсекаем аффикс

        LA_CropRule::HashType affix_hash = LA_CropRule::CalcHash(word.c_str(), false, true);
        pp = affix_crop_rules.equal_range(affix_hash);

        for (auto it = pp.first; it != pp.second; ++it)
        {
            const LA_CropRule *r = it->second;
            if (r->Apply(word, result))
            {
                applied = true;
                results.push_back(result);
                rels.push_back(r->GetRel());
                if (trace != nullptr)
                {
                    trace->CropRuleApplied(word, result, r);
                }
            }
        }
    }

    return applied;
}
