#if !defined LA_PreprocessorTrace_Console__H
#define LA_PreprocessorTrace_Console__H

#include <lem/solarix/dictionary.h>
#include <lem/solarix/trace_log.h>
#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/LA_PreprocessorTrace.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/SG_TagFilter.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>

using namespace lem;
using namespace Solarix;


class LA_PreprocessorTrace_Console : public LA_PreprocessorTrace
{
private:
    Solarix::Dictionary *dict;
    lem::zbool trace;

public:
    LA_PreprocessorTrace_Console(Solarix::Dictionary *d);

    void Trace(bool f) { trace = f; }

    virtual void LanguageGuessed(const lem::UFString &phrase, int LanguageID);
};


#endif

