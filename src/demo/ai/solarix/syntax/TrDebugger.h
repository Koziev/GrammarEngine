#if !defined TrDebugger_H
#define TrDebugger_H

#include <lem/solarix/dictionary.h>
#include <lem/solarix/trace_log.h>
#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/LA_PreprocessorTrace.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/SG_TagFilter.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include "TrBreakpoint.h"
#include "LA_RecognitionTrace_Console.h"
#include "LA_PreprocessorTrace_Console.h"


using namespace lem;
using namespace Solarix;


class TrDebugger : public TrTrace
{
private:
    lem::zbool trace;

    struct AppliedCollocFilter : lem::NonCopyable
    {
        lem::UCString filter_name;
        lem::Path src_filename;
        int src_line;
        lem::UFString context;
    };

    lem::PtrCollect<AppliedCollocFilter> applied_colloc_filter;

    Solarix::Dictionary *dict;
    lem::PtrCollect<TrBreakpoint> breakpoints;
    lem::PtrCollect<TrTraceActor> callstack;

    lem::Collect<lem::Path> source_filename;
    lem::PtrCollect<lem::UTextParser> source_parser;

    void ExecuteBreakpoints(TrTraceActor *a);
    void ExecuteBreakpoint(int ipoint, TrTraceActor *a);
    UTextParser& GetSourceText(const lem::Path &filename);

    lem::zbool stop_before_analysis;
    lem::zbool stop_on_right_boundary;
    lem::zbool stop_after_model;

    LA_RecognitionTrace_Console * recognizer_trace;
    LA_PreprocessorTrace_Console * preprocessor_trace;

    virtual void RaisedExceptionLocation(const lem::MCollect<int> &src_locations);
    virtual void RaisedExceptionLocation(int src_locations);

    void ShowSynPatternResults(const lem::MCollect<SynPatternResult*> & results, bool sort_by_scores, int items_to_show);
    void AfterModelApplication(Solarix::BasicLexer & lexer);
    void StackOverflow(int current_depth);


public:
    TrDebugger(Solarix::Dictionary *d);
    virtual ~TrDebugger(void);

    void Trace(bool f);

    void ManageTriggers(void);

    virtual void CheckStackOverflow(int current_depth);
    virtual void Enter(TrTraceActor *a);
    virtual void Leave(TrTraceActor *a);
    virtual void Print(const UFString &str);

    virtual void ShowLexerPerformance(BasicLexer & lexer);

    virtual void MorphologicalAnalysisStarts(Solarix::BasicLexer & lexer);
    virtual void MorphologicalAnalysisFinishes(const Solarix::Res_Pack & pack);
    virtual void MorphologyAnalysisCompleted(const Solarix::TextAnalysisSession & fblo);

    void BeforePhrase(void);
    void AfterPhrase(void);
    void ManageBreakpoints(void);

    virtual void PrintStack(lem::OFormatter &out);

    virtual LA_RecognitionTrace* RecognizerTrace(void);
    virtual LA_PreprocessorTrace* PreprocessorTrace(void);

    virtual void BreakOnRightBoundary(const lem::MCollect<SynPatternResult*> & results);

    virtual void DebugTrace(const lem::UCString &marker, const TrValue &arg);

    void PrintTokenizationGraph(BasicLexer & lexer, bool detailed);

    virtual void BeforeSynPatternTreeProve(
        const SynPatternPoint &point,
        const lem::MCollect<int> &id_src,
        const BasicLexer & lexer,
        const LexerTextPos * current_token,
        const BackTrace * parent_trace
    );

    virtual void SynPatternTreeProved(
        const SynPatternPoint &point,
        const lem::MCollect<int> &id_src,
        const BasicLexer & lexer,
        const LexerTextPos *current_token,
        const lem::PtrCollect<SynPatternResult> & subresults
    );

    virtual void BeforeMatchingTheWord(
        const SynPatternPoint &point,
        const lem::MCollect<int> &id_src,
        const BasicLexer & lexer,
        const LexerTextPos *current_token
    );


    virtual void LanguageGuessed(const lem::UFString & str, int id_language);
    virtual void ClassifierModelApplied(const Word_Form * focus, const Word_Form * new_token_wordform);
};

#endif

