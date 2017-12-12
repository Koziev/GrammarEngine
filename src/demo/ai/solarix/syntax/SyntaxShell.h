#if !defined SyntaxShell__H
#define SyntaxShell__H

#include <lem/solarix/dictionary.h>
#include <lem/solarix/trace_log.h>
#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/LA_PreprocessorTrace.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/SG_TagFilter.h>
#include <lem/solarix/WrittenTextAnalysisSession.h>
#include "TrDebugger.h"


using namespace lem;
using namespace Solarix;


class SyntaxShell
{
public:
    typedef enum { MorphologyMode, SyntaxMode, TokenizerMode, SegmenterMode, LemmatizerMode, SpeakerMode } RunMode;

    void SetMode(RunMode new_mode);

private:
    RunMode run_mode; // текущий режим функционирования - какой блок анализа работает.

    bool lazy_lexicon;
    lem::Ptr<Dictionary> sol_id;
    lem::Ptr<TrDebugger> debugger;

    OFormatter nul_tty;

    lem::UFString pre_entered_phrase;

    lem::Ptr<WrittenTextAnalysisSession> current_analysis;

    lem::zbool allow_fuzzy;
    lem::zbool CompleteAnalysisOnly;
    lem::zbool UseReconstructor;
    lem::zbool traceon;
    lem::UCString scenario; // сценарий трансформации (перевод и пр.)
    lem::zbool ApplyModel; // использовать языковую статистическую модель для снятия неоднозначности
    int MaxSkipToken;

    lem::zbool UseTopDownThenSparse; // работа по схеме: сначала попробовать полный нисходящий анализ, если неудача и осталось время - то примерный нисходящий.

    int MaxTimeout; // можно интерактивно задать лимит времени на анализ предложения.
    int MaxAlt;
    bool FindFacts;

    lem::ElapsedTime elapsed;

    lem::Collect< std::pair<UCString /*tag*/, UCString /*value*/> > tags; // тэги для фильтрации переводов
    lem::Ptr<Solarix::SG_TagFilter> tags_ptr; // скомпилированные тэги

    lem::Ptr<Solarix::SG_TagFilter> transl0_tag; // специальный фильтр для отбора только переводов с transl_order=0
    lem::Ptr<Solarix::SG_TagFilter> transl1_tag; // специальный фильтр для отбора только основных переводов

    lem::Collect< std::pair<UCString /*param*/, UCString /*value*/> > params; // глобальные параметры для управления алгоритмом перевода

    lem::zbool guess_language; // язык нужно подбирать для каждой вводимой фразы
    int default_language; // язык синтаксического анализа (для многоязычных словарей)
    lem::zbool needs_shortest_var; // печатать на консоли только самые короткие варианты разбора

    lem::zbool debug;

    const lem::UFString enter_cmd(const char *Prompt) const;
    bool TryCommand(const lem::UFString &str);
    void ShowHelp(void) const;
    void Exiting(void);
    void Tokenize(const UFString & s);
    void Lemmatize(const UFString & str);
    void Speak(const UFString & str);
    void Segmentize(const UFString & s);


    void ShowDictionaryInfo(void);

    bool PerformSyntacticAnalysis(const UFString &sent);
    UFString VarToStr(const Solarix::Variator &var) const;

    void PrintLexerPerformance(Solarix::BasicLexer & lexer, const lem::MCollect<const LexerTextPos*> & tokens);
    void PrintLexerPerformance(Solarix::BasicLexer & lexer, const LexerTextPos * token);

public:
    lem::Path dict_dir;

public:
    SyntaxShell(void);
    ~SyntaxShell(void);

    void SetDebug(bool f);
    void SetPhrase(const lem::UFString &x);

    void LazyLexicon(bool _lazy_lexicon);
    void LoadDictionary();

    void main_loop(void);
    void SetLanguage(const UCString &lang_name);
    void SetThesaurusTags(const lem::Collect< std::pair<UCString /*tag*/, UCString /*value*/> > & Tags);
    void SetEnvParams(const lem::Collect< std::pair<UCString /*param*/, UCString /*value*/> > & Params);

    void AllowIncomplete(bool f) { CompleteAnalysisOnly = !f; }
    void AllowFuzzy(bool f) { allow_fuzzy = f; }
    void AllowReconstructor(bool f) { UseReconstructor = f; }
    void AllowModel(bool f) { ApplyModel = f; }
    void RunSemantics() { FindFacts = true; }
    void SetMaxAlt(int _max_alt) { MaxAlt = _max_alt; }
    void SetMaxSkipToken(int _n) { MaxSkipToken = _n; }
};

#endif
