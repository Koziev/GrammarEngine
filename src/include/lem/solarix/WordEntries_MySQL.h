#if !defined WordEntries_MySQL__H && defined SOL_MYSQL_DICTIONARY_STORAGE
#define WordEntries_MySQL__H

//#include <lem/process.h>
#include <lem/mysql_helpers.h>
#include <lem/solarix/BaseRef.h>
#include <lem/solarix/coord_pair.h>
#include <lem/RWULock.h>

#if defined SOL_LOADTXT
#include <lem/solarix/LexemDictionary.h>
#endif

#include <lem/solarix/WordEntries_SQL.h>

namespace Solarix
{
    class StorageConnection_MySQL;
    class SynGram;
    struct Dictionary_Config;

    class WordEntries_MySQL : public WordEntries_SQL
    {
    private:
        StorageConnection_MySQL *cnx;

        virtual SG_Entry* LoadEntryFromDb_Impl(int ekey);
        virtual int RegisterLexemeInDatabase(const lem::UCString & lex);
        virtual int RegisterCoordPairsInDatabase(const lem::UFString &int_pairs, const lem::UFString &str_pairs);
        virtual int GetMaxMultilexemLen_Impl();
        virtual bool IsMultilexemHead_Impl(const lem::UCString &word, MultiLexemInfo &info);
        virtual bool IsMultilexemForm_Impl(const Solarix::Lexem &lex);
        virtual int FindEntry_Impl(const lem::UCString &word_name, int id_class);
        virtual void GetUEntries_Impl();
        virtual int GetPredefinedEntryKey_Impl(int index);
        virtual int FindQuantorEntry_Impl(int id_class);

    public:
        WordEntries_MySQL(SynGram &_sg, StorageConnection_MySQL *_cnx, const Dictionary_Config &cfg);
        virtual ~WordEntries_MySQL();

        virtual int CountEntries(int id_class, int id_language) override;
        virtual int CountForms(int id_language) override;

        virtual bool IsWordForm(const Solarix::Lexem &lex) override;

        virtual int FindEntryOmonym(const Lexem& lname, int iclass, const Solarix::GramCoordPair &p) override;
        virtual int FindEntryOmonym(const Lexem& lname, int iclass, const lem::MCollect<Solarix::GramCoordPair> &p) override;
        virtual int FindEntryOmonym(const Lexem& lname, int iclass, const ExactWordEntryLocator &locator) override;

        virtual WordEntryEnumerator* ListEntries(const lem::UCString &name, int id_class) override;
        virtual WordEntryEnumerator* ListEntries() override;

        virtual Word_Coord FindWordForm(const lem::UCString& name) override;
        virtual WordFormEnumerator* ListWordForms(const lem::UCString &form, bool allow_nonterminals) override;
        virtual WordFormEnumerator* ListWordForms(const lem::MCollect<lem::UCString> &forms) override;
        virtual WordFormEnumerator* ListWordForms_Fuzzy(const lem::UCString &word, float min_val) override;
        virtual WordFormEnumerator* ListWordForms_Globbing(const lem::UFString &mask) override;

        virtual int CountLexemes() override;
        virtual LexemeEnumerator* ListLexemes() override;

#if defined SOL_LOADTXT
        virtual int LoadEntry(lem::StrParser<lem::UFString> &txt) override;
#endif
    };

}

#endif
