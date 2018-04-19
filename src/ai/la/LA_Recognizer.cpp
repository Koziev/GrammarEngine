#include <lem/oformatter.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/Languages.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/LA_RecognitionRule.h>
#include <lem/solarix/LA_RecognitionRules.h>
#include <lem/solarix/LA_Recognizer.h>

using namespace Solarix;



LA_Recognizer::LA_Recognizer(Solarix::Dictionary *Dict)
{
    dict = Dict;
    storage = nullptr;
    return;
}


void LA_Recognizer::Connect(LexiconStorage *Storage)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs_init);
#endif

    storage = Storage;
    DeleteRules();
    return;
}


LA_Recognizer::~LA_Recognizer()
{
    DeleteRules();
    return;
}


void LA_Recognizer::DeleteRules()
{
    for (auto rule : rules)
    {
        delete rule;
    }

    rules.clear();
    id_langs.clear();
    all_langs.clear();

    return;
}


void LA_Recognizer::LoadRulesFromStorage(int id_language)
{
    LA_RecognitionRules *lang_rules = new LA_RecognitionRules(id_language, storage);

    std::unique_ptr<LS_ResultSet> rs1(storage->ListRecognitionRules(id_language, false));
    while (rs1->Fetch())
    {
        const int id = rs1->GetInt(0);
        LA_RecognitionRule *rule = storage->GetRecognitionRule(id);
        lang_rules->Add(rule);
    }

    id_langs.push_back(id_language);
    rules.push_back(lang_rules);

    return;
}


void LA_Recognizer::LoadRules(int id_language)
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs);
#endif

    const int idx = id_langs.find(id_language);
    if (idx == UNKNOWN)
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        LoadRulesFromStorage(id_language);

        // ������� ��� ����� � ����� -1 ����������� ������, ������� �������� � �� � ������ ������� ����������
        const int idxu = id_langs.find(UNKNOWN);
        if (idxu == UNKNOWN)
        {
            LoadRulesFromStorage(UNKNOWN);
        }
    }

    return;
}


const LA_RecognitionRules* LA_Recognizer::GetRules(int id_language) const
{
    const int idx = id_langs.find(id_language);
    if (idx == UNKNOWN)
    {
        lem::MemFormatter mem;
        mem.printf("Could not find the recognition rules for id_language=%d", id_language);
        throw lem::E_BaseException(mem.string());
    }

    return rules[idx];
}


// **************************************************************
// �������� ID ���� ������ � ������� ��� ���� ������.
// ��� ���������� � ������, ����� ����������� ��������� ������
// � ��������� ID �����=-1.
// **************************************************************
void LA_Recognizer::LoadAllLangs()
{
#if defined LEM_THREADS
    lem::Process::RWU_ReaderGuard rlock(cs_langs);
#endif
    if (all_langs.empty())
    {
#if defined LEM_THREADS
        lem::Process::RWU_WriterGuard wlock(rlock);
#endif

        Solarix::Languages &langs = dict->GetSynGram().languages();
        std::unique_ptr<Solarix::LanguageEnumerator> e(langs.Enumerate());
        while (e->Fetch())
        {
            all_langs.push_back(e->GetId());
            LoadRules(e->GetId());
        }
    }

    return;
}


bool LA_Recognizer::Apply(
    const lem::UCString & normalized_word,
    const lem::UCString & original_word,
    float word_score,
    float min_bound,
    lem::MCollect<Word_Coord> & found_list,
    lem::MCollect<ProjScore> & val_list,
    lem::PtrCollect<LA_ProjectInfo> & inf_list,
    int id_language,
    bool only_forced,
    LA_RecognitionTrace *trace
)
{
    bool matched = false;

    if (lem::is_quantor(id_language))
    {
        LoadAllLangs();

        // Apply all rules.
        for (lem::Container::size_type j = 0; j < rules.size(); ++j)
        {
            const LA_RecognitionRules *r = rules[j];
            if (r->Apply(normalized_word, original_word, word_score, found_list, val_list, inf_list, only_forced, trace))
                matched = true;
        }
    }
    else
    {
        LoadRules(id_language);

        const LA_RecognitionRules *rules1 = GetRules(id_language);
        if (rules1->Apply(normalized_word, original_word, word_score, found_list, val_list, inf_list, only_forced, trace))
            matched = true;

        const LA_RecognitionRules *rules2 = GetRules(UNKNOWN);
        if (rules2->Apply(normalized_word, original_word, word_score, found_list, val_list, inf_list, only_forced, trace))
            matched = true;
    }

    return matched;
}


bool LA_Recognizer::ApplyForSyllabs(
    const lem::UCString &word,
    float word_score,
    const lem::MCollect<lem::UCString> & syllabs,
    float min_bound,
    lem::MCollect<Solarix::Word_Coord> &found_list,
    lem::MCollect<ProjScore> &val_list,
    lem::PtrCollect<Solarix::LA_ProjectInfo> &inf_list,
    int id_language,
    LA_RecognitionTrace *trace
)
{
    LEM_CHECKIT_Z(!syllabs.empty());

    bool matched = false;

    if (lem::is_quantor(id_language))
    {
        LoadAllLangs();

        // Apply all rules.
        for (lem::Container::size_type j = 0; j < rules.size(); ++j)
        {
            const LA_RecognitionRules *r = rules[j];
            if (r->ApplyForSyllabs(word, word_score, syllabs, found_list, val_list, inf_list, trace))
                matched = true;
        }
    }
    else
    {
        LoadRules(id_language);

        const LA_RecognitionRules *rules1 = GetRules(id_language);
        if (rules1->ApplyForSyllabs(word, word_score, syllabs, found_list, val_list, inf_list, trace))
            matched = true;

        const LA_RecognitionRules *rules2 = GetRules(UNKNOWN);
        if (rules2->ApplyForSyllabs(word, word_score, syllabs, found_list, val_list, inf_list, trace))
            matched = true;
    }

    return matched;
}





#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_Recognizer::LoadTxt_Recognition(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict)
{
    LA_RecognitionRule* r = new LA_RecognitionRule();
    r->LoadTxt(txtfile, dict);
    storage->StoreRecognitionRule(r);
    return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_Recognizer::LoadTxt_Misspelling(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict)
{
    txtfile.read_it(B_LANGUAGE);
    // ������ ���� ������������ �����, � ������ �������� ��������� �������.
    txtfile.read_it(B_EQUAL);
    lem::Iridium::BethToken t1 = txtfile.read();
    int id_language = dict.GetSynGram().Find_Language(t1.string());
    if (id_language == UNKNOWN)
    {
        lem::Iridium::Print_Error(t1, txtfile);
        dict.GetIO().merr().printf("Unknown language name %us\n", t1.c_str());
        throw lem::E_BaseException();
    }

    txtfile.read_it(B_OFIGPAREN);

    txtfile.read_it(B_IF);

    Solarix::Lexem old_word = txtfile.read().string();
    old_word.strip(L'"');
    dict.GetLexAuto().TranslateLexem(old_word, true, id_language);

    txtfile.read_it(B_THEN);

    Solarix::Lexem new_word = txtfile.read().string();
    new_word.strip(L'"');
    dict.GetLexAuto().TranslateLexem(new_word, true, id_language);

    txtfile.read_it(B_CFIGPAREN);

    storage->AddMisspelling(id_language, old_word, new_word);
    return;
}
#endif


bool LA_Recognizer::RewriteMisspeltWord(
    int id_language,
    const lem::UCString &word,
    lem::MCollect<lem::UCString> &new_words
)
{
    return storage->FindMisspelling(id_language, word, new_words);
}
