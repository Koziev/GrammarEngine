#if defined SOL_DEBUGGING

// CD->28.07.2009
// LC->06.09.2017

#include <lem/keyboard.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/TrMorphologyTracer.h>
#include <lem/solarix/LA_CropRule.h>
#include <lem/solarix/LA_RecognitionRule.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_PreprocessorTokRule.h>
#include <lem/solarix/SourceFilenameEnumerator.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/LexerTextPos.h>

#include "LA_RecognitionTrace_Console.h"

using namespace lem;
using namespace Solarix;

LA_RecognitionTrace_Console::LA_RecognitionTrace_Console(Solarix::Dictionary *d)
{
    dict = d;
}

void LA_RecognitionTrace_Console::CropRuleApplied(
    const lem::UCString &word_before,
    const lem::UCString &word_after,
    const LA_CropRule *rule
)
{
    if (trace)
        mout->printf("Crop rule %vfA%us%vn has been applied: %vfE%us%vn -> %vfE%us%vn\n", rule->GetName().c_str(), word_before.c_str(), word_after.c_str());

    return;
}

void LA_RecognitionTrace_Console::Matched(const lem::UCString &word, const LA_RecognitionRule *rule)
{
    if (trace)
    {
        mout->printf("Recognition rule %vfA%us%vn has been applied for %vfE%us%vn score=%vf9%4.2rf%vn", rule->GetName().c_str(), word.c_str(), rule->GetScore());

        const Solarix::SG_Entry &e = dict->GetSynGram().GetEntry(rule->GetEntryKey());
        const int id_class = e.GetClass();
        mout->printf(" %us:%us ", dict->GetSynGram().GetClass(id_class).GetName().c_str(), e.GetName().c_str());
        rule->GetCoords().SaveTxt(*mout, dict->GetSynGram());
        mout->printf("\n");
    }

    return;
}

void LA_RecognitionTrace_Console::MatchedSyllable(const lem::UCString &word, const lem::UCString &syllable, const LA_RecognitionRule *rule)
{
    if (trace)
    {
        mout->printf("Recognition rule %vfA%us%vn has been applied for syllable %vfE%us%vn in word %vfE%us%vn score=%vf9%4.2rf%vn"
            , rule->GetName().c_str(), syllable.c_str(), word.c_str(), rule->GetScore());

        const Solarix::SG_Entry &e = dict->GetSynGram().GetEntry(rule->GetEntryKey());
        const int id_class = e.GetClass();
        mout->printf(" %us:%us ", dict->GetSynGram().GetClass(id_class).GetName().c_str(), e.GetName().c_str());
        rule->GetCoords().SaveTxt(*mout, dict->GetSynGram());
        mout->printf("\n");
    }

    return;
}

void LA_RecognitionTrace_Console::PhoneticRuleProduction(const lem::UCString &source, const lem::UCString &result, lem::Real1 val, const LA_PhoneticRule *rule)
{
    if (trace)
    {
        mout->printf("Phonetic rule %vfA%us%vn has been applied: %vfE%us%vn -> %vfE%us%vn  rel=%vf9%4.2rf%vn\n",
            rule->GetName().c_str(), source.c_str(), result.c_str(), val.GetFloat());
    }

    return;
}


void LA_RecognitionTrace_Console::WordSyllabs(const lem::UCString &word, const lem::MCollect<lem::UCString> &slb_list)
{
    if (trace)
    {
        mout->printf("Word %vfE%us%vn has been split to syllables:", word.c_str());

        for (lem::Container::size_type i = 0; i<slb_list.size(); i++)
            lem::mout->printf(" %us", slb_list[i].c_str());

        mout->eol();
    }

    return;
}

#endif
