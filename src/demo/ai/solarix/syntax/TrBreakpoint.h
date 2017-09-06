#if !defined TrBreakpoint_H
#define TrBreakpoint_H

#include <lem/solarix/dictionary.h>
#include <lem/solarix/trace_log.h>
#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/LA_PreprocessorTrace.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/SG_TagFilter.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>

using namespace lem;
using namespace Solarix;

struct TrBreakpoint
{
    int pass_count; // сколько раз сработала точка

    lem::zbool once;
    lem::zbool step;
    int ifile, iline; // пользовательские точки - останов в указанной строке указанного файла
    int on_call_stack_depth, on_pass_count;


    TrBreakpoint(void) : pass_count(0), ifile(UNKNOWN), iline(UNKNOWN), on_call_stack_depth(UNKNOWN), on_pass_count(UNKNOWN) {}
};

#endif

