#if !defined SYNTAX__H
#define SYNTAX__H

#include <lem/solarix/dictionary.h>
#include <lem/solarix/trace_log.h>
#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/LA_PreprocessorTrace.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/SG_TagFilter.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>

using namespace lem;
using namespace Solarix;

class LA_RecognitionTrace_Console : public LA_RecognitionTrace
{
private:
    Solarix::Dictionary *dict;
    lem::zbool trace;

public:
    LA_RecognitionTrace_Console(Solarix::Dictionary *d);

    void Trace(bool f) { trace = f; }

    virtual void CropRuleApplied(
        const lem::UCString &word_before,
        const lem::UCString &word_after,
        const LA_CropRule *rule
    );

    virtual void Matched(const lem::UCString &word, const LA_RecognitionRule *rule);
    virtual void MatchedSyllable(const lem::UCString &word, const lem::UCString &syllable, const LA_RecognitionRule *rule);
    virtual void PhoneticRuleProduction(const lem::UCString &source, const lem::UCString &result, lem::Real1 val, const LA_PhoneticRule *rule);
    virtual void WordSyllabs(const lem::UCString &word, const lem::MCollect<lem::UCString> &slb_list);

    virtual void SyllabicBreakRuleHit(
        const SyllabContext & context,
        int cursor_pos,
        const SyllabRule & rule
    ) {}

    virtual void SyllabicBreakRuleApplied(
        const SyllabContext & context,
        int cursor_pos,
        const SyllabRule & rule
    ) {}

};

#endif
