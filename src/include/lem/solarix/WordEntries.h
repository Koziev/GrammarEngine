#if !defined WordEntries__H
#define WordEntries__H

#include <set>
#include <lem/containers.h>
#include <lem/tuple.h>
#include <lem/string_parser.h>
#include <lem/solarix/WordCoord.h>
#include <lem/solarix/coord_pair.h>

namespace lem
{
    class UCString;
    class OFormatter;

    namespace Iridium
    {
        class Macro_Parser;
    }
}

namespace Solarix
{
    struct MultiLexemInfo
    {
        int maxlen;

        MultiLexemInfo(void) : maxlen(UNKNOWN) {}
    };

    class LexicalAutomat;
    class SynGram;
    class WordEntryEnumerator;
    class WordFormEnumerator;
    class SG_Entry;
    struct CharNode;
    struct Binarization_Options;
    class Lexem;
    class CP_Array;
    class LD_Seeker;
    class LexemeEnumerator;
    struct ExactWordEntryLocator;

    class WordEntries
    {
    public:
        WordEntries(void) {}
        virtual ~WordEntries(void) {}

        virtual void CreateDefaultEntries(void) = 0;

        virtual int CountEntries(int id_class, int id_language) = 0;
        virtual int CountForms(int id_language) = 0;

        virtual bool PreferPrefixSearch(void) = 0;

        virtual int GetMaxMultilexemLen(void) = 0;
        virtual bool IsMultilexemHead(const lem::UCString &word, MultiLexemInfo &info) = 0;
        virtual bool IsMultilexemForm(const Solarix::Lexem &lex) = 0;
        virtual bool IsWordForm(const Solarix::Lexem &lex) = 0;

        virtual int FindEntry(const lem::UCString &word_name, int id_class) = 0;
        virtual int FindEntryOmonym(const Lexem& lname, int iclass, const Solarix::GramCoordPair &p) = 0;
        virtual int FindEntryOmonym(const Lexem& lname, int iclass, const lem::MCollect<Solarix::GramCoordPair> &p) = 0;
        virtual int FindEntryOmonym(const Lexem& lname, int iclass, const ExactWordEntryLocator &locator) = 0;

        //virtual WordEntryEnumerator* ListEntries( const lem::triple<wchar_t,wchar_t,wchar_t> & prefix3 )=0;
        virtual WordEntryEnumerator* ListEntries(const lem::UCString &name, int id_class) = 0;
        virtual WordEntryEnumerator* ListEntries(void) = 0;

        virtual Word_Coord FindWordForm(const lem::UCString& name) = 0;
        virtual WordFormEnumerator* ListWordForms(const lem::UCString &form, bool allow_nonterminals) = 0;
        virtual WordFormEnumerator* ListWordForms(const lem::MCollect<lem::UCString> &forms) = 0;
        virtual WordFormEnumerator* ListWordForms_Fuzzy(const lem::UCString &word, float min_val) = 0;
        virtual WordFormEnumerator* ListWordForms_Globbing(const lem::UFString &mask) = 0;

        virtual int CountLexemes(void) = 0;
        virtual LexemeEnumerator* ListLexemes(void) = 0;

        virtual const SG_Entry& GetEntry(int ekey) = 0;
        virtual SG_Entry& GetEntryForChange(int ekey) = 0;

#if defined SOL_LOADTXT
        virtual int LoadEntry(lem::StrParser<lem::UFString> &txt) = 0;
#endif
        virtual int CreateEntry(const lem::UCString &ename, int id_class) = 0;
        virtual int GetPredefinedEntryKey(int index) = 0;
        virtual int FindQuantorEntry(int id_class) = 0;

        virtual int AddEntry(SG_Entry *new_entry) = 0;
        virtual const Lexem* AddLexeme(const Solarix::Lexem &lex) = 0;
        virtual const CP_Array* AddCoordPairs(const CP_Array &x) = 0;
        virtual const Lexem* ReattachLexeme(const Lexem *ptr) = 0;
        virtual const CP_Array* ReattachCoordPairs(const CP_Array *ptr) = 0;

        virtual void PrepareForMerging(void) = 0;
        virtual void CommitCompilation(lem::OFormatter &err) = 0;

        virtual CharNode* GetPrefixTreeForAllLanguages(void) = 0;
        virtual CharNode* GetPrefixTree(const std::set<int>& allowed_langs) = 0;

        virtual void ReplaceEntry(int ekey, SG_Entry *dummy) = 0;
        virtual void PostRead(lem::Iridium::Macro_Parser &txtfile, const Binarization_Options &options) = 0;

        virtual void LoadBin(lem::Stream &bin) = 0;
        virtual void SaveBin(lem::Stream &bin) const = 0;

        virtual void DetailedReport(lem::OFormatter &txtfile) = 0;

        virtual LD_Seeker* Get_Seeker(void) = 0;

#if defined SOL_LOADBIN
        virtual LD_Seeker* Load_Seeker(lem::Stream &bin) = 0;
#endif

        virtual const lem::IntCollect& GetUEntries(void) = 0;

        virtual int GetUnknownEntryKey(void) = 0;
    };

}

#endif
