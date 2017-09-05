#if !defined LexiconShell__H
#define LexiconShell__H

#include <lem/solarix/dictionary.h>
#include <lem/solarix/LA_ProjectInfo.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/SG_TagFilter.h>
#include <lem/solarix/ProjScore.h>
#include <lem/solarix/LA_RecognitionTrace.h>

#include "LexiconDebugger.h"

class LexiconShell
{
private:
    lem::Ptr<Solarix::Dictionary> sol_id;
    lem::Ptr<LexiconDebugger> debugger;

    Solarix::SynGram *SG;
    const Solarix::GraphGram *GG;

    lem::OFormatter nul_tty;

    // Text stream to store the unrecognized words.
    lem::OUFormatter unfound_entry;

    lem::zbool fuzzy;
    lem::zbool first_turn;
    lem::zbool batch_mode;

    bool proj_words;
    bool print_proj;
    bool do_print_proj_coords; // Отображать координатные пары при проекции слов

    void LoadDictionary(const lem::Path &dict_path);

    LexiconDebugger* GetDebugger(void);

    int ShowMenu();
    void ExecuteMenu(int choice);
    void EnterMenuLoop();


    const lem::UFString enter_cmd(const char *Prompt) const;
    void ShowHelp(void) const;
    void SetMode(const lem::UFString &str);
    void Exiting(void);
    void TestStemmer(void);
    void TestFlexer(void);
    void ShowParadigma(void);
    void TestThesaurus();
    void TestLexiconLookUp(void);
    void TestNGrams();
    void SearchByIE();
    void FullMorphologyAnalysis(
        const lem::UFString &word,
        bool print_projections,
        bool print_links
    );
    void MorphologyAnalysis(const lem::UFString &word);
    void ThesaurusQuery(const lem::UFString &word, bool synonyms, bool translations, const Solarix::SG_TagFilter* tags);
    void Show_Semnet(const lem::UFString &word, bool synonyms, bool translations, const Solarix::SG_TagFilter* tags);
    void Display_Projects(
        const lem::MCollect<Solarix::Word_Coord> &res,
        const lem::MCollect<Solarix::ProjScore> &val_list,
        const lem::PtrCollect<Solarix::LA_ProjectInfo> &prj_extra_inf,
        bool print_projections,
        bool print_links
    );

    void PrintPhrase(Solarix::SynGram &sg, Solarix::SG_Phrase & frz);
    void SearchByName(void);

    void ShowStatistics(void);
    void ShowThesaurusStatistics(void);
    void ShowLexiconStatistics(void);
    void ShowSyllabicBreaks(void);


public:
    LexiconShell(const lem::Path &dict_path, bool batch = false, bool write_unfound_entries = false);
    ~LexiconShell(void);

    void main_loop(bool show_menu, const lem::MCollect<int>& menu);
    void ProcessFile(const lem::Path &filename);
    void SearchNGrams(const lem::Path &filename);
};

#endif
