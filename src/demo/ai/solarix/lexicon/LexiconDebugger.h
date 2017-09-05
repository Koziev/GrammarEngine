#if !defined LexiconDebugger__H
#define LexiconDebugger__H

#include <lem/solarix/dictionary.h>
#include <lem/solarix/LA_ProjectInfo.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/SG_TagFilter.h>
#include <lem/solarix/ProjScore.h>
#include <lem/solarix/LA_RecognitionTrace.h>

class LexiconDebugger : public Solarix::LA_RecognitionTrace
{
private:
    Solarix::Dictionary *dict;
    lem::zbool trace;

public:
    LexiconDebugger(Solarix::Dictionary *Dict);

    void Trace(bool f) { trace = f; }

    virtual ~LexiconDebugger(void) {}

    virtual void CropRuleApplied(
        const lem::UCString &word_before,
        const lem::UCString &word_after,
        const Solarix::LA_CropRule *rule
    );

    virtual void Matched(const lem::UCString &word, const Solarix::LA_RecognitionRule *rule);
    virtual void MatchedSyllable(const lem::UCString &word, const lem::UCString &syllable, const Solarix::LA_RecognitionRule *rule);
    virtual void PhoneticRuleProduction(const lem::UCString &source, const lem::UCString &result, lem::Real1 val, const Solarix::LA_PhoneticRule *rule);
    virtual void WordSyllabs(const lem::UCString &word, const lem::MCollect<lem::UCString> &slb_list);

    virtual void SyllabicBreakRuleHit(
        const Solarix::SyllabContext & context,
        int cursor_pos,
        const Solarix::SyllabRule & rule
    );

    virtual void SyllabicBreakRuleApplied(
        const Solarix::SyllabContext & context,
        int cursor_pos,
        const Solarix::SyllabRule & rule
    );
};


#endif
