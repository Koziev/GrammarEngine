#if !defined WordEntries_File__H
#define WordEntries_File__H

#include <lem/solarix/WordEntries.h>
#include <lem/solarix/SG_EntryGroup.h>
#include <lem/solarix/LexemDictionary.h>
#include <lem/solarix/BaseRef.h>
#include <lem/solarix/coord_pair.h>
#include <lem/bit_array32.h>
#include <lem/process.h>


namespace Solarix
{
    class SynGram;
    class LexicalAutomat;
    class LD_Seeker;
    class SG_BogusEntry;
    struct Dictionary_Config;

    struct WordEntries_LookUpItem
    {
        lem::int32_t start_index;
        lem::int16_t len;
    };

    class WordEntries_LookUp : lem::NonCopyable
    {
    public:
        lem::MCollect<lem::int32_t> sorted_lexem_index;
        lem::MCollect<WordEntries_LookUpItem> lexem_slot;
        lem::MCollect<int> entry_index;

        void InitLexems(const LexemDictionary & lexems);
        int Findlexem(const LexemDictionary & lexems, const lem::UCString & lexem) const;
        void Clear();
        void SaveBin(lem::Stream & bin) const;
        void LoadBin(lem::Stream & bin);
    };

    class WordEntries_File : public WordEntries
    {
    private:
        SynGram *sg;

        LexemDictionary ml_ref;
        BaseRef<CP_Array> coord_ref;

        // Информация для алгоритма быстрого поиска.
        WordEntries_LookUp lookup_table;

        void ClearGroups();

        lem::PtrCollect<SG_Entry> entry;   // Список словарных статей.
        lem::IntCollect           ientry;
        lem::IntCollect           u_entry; // Список статей '?'

        int max_ml_len;                    // Max. number of lexem in a wordform.

        std::map< int/*entry_key*/, int/*entry_index*/ > key_to_index;

        // Хранит ключи статей с многолексемными формами.
        lem::IntCollect ML_entry_key_list;

        // Перечислены (по одному разу) все лексемы. которые участвуют в
        // формировании имён многолексемных словоформ.
        lem::MCollect<Lexem> ML_entry_lex_list;
        lem::MCollect<lem::BitArray32> ML_entry_pre_list; // В паре с предыдущим.
        std::set<Lexem> ML_fronts; // для быстрого определения, что лексема может быть началом мультилексемы
        std::set<Lexem> ML_ML; // список всех мультилексем

#if defined SOL_LOADTXT && defined SOL_COMPILER
        std::multimap< std::pair<lem::UCString/*entry name*/, int/*class*/>, int > entry_class_lookup;
#endif

        SG_BogusEntry *bogus_entry;

        int predefined_entry[SOL_SG_NPREDEF_ENTRIES]; // Вектор ключей для предопределённых статей.

        // Для ленивой загрузки
#if defined LEM_THREADS
        lem::Process::CriticalSection cs;
#endif
        bool lazy_load;
        lem::MCollect<lem::Stream::pos_type> entry_pos;
        lem::Path entries_path;
        lem::Ptr<lem::BinaryReader> entries_bin;
        void LoadEntry(int index);

        friend class WordEntryEnumerator_File;
        friend class WordEntryEnumerator_File_ByGroup;
        friend class WordFormEnumerator_File1;
        friend class WordFormEnumerator_File2;
        friend class WordFormEnumerator_File3;
        friend class LexemeEnumerator_File;
        friend class WordFormEnumeratorFuzzy_File;
        friend class WordFormEnumeratorGlobbing_File;


        int size() const;
        SG_Entry& GetWordEntry(int index);
        void AddAutoCreated(SG_Entry *e);
        const SG_Entry& GetEntryByKey(int key);
        int FindEntryIndexByKey(int key) const;
        void Delete_Entries();


#if defined SOL_COMPILER
        void BuildLookUpTable();
        void SortUp();
        void ProcessSynEntries();
#endif

    public:
        WordEntries_File(SynGram * _sg, const Dictionary_Config &cfg);
        virtual ~WordEntries_File();

        virtual void CreateDefaultEntries() override;

        virtual bool PreferPrefixSearch() override;

        virtual int CountEntries(int id_class, int id_language) override;
        virtual int CountForms(int id_language) override;

        virtual bool IsMultilexemHead(const lem::UCString &word, MultiLexemInfo &info) override;
        virtual int GetMaxMultilexemLen() override;
        virtual bool IsMultilexemForm(const Solarix::Lexem &lex) override;
        virtual bool IsWordForm(const Solarix::Lexem &lex) override;


        virtual int FindEntry(const lem::UCString &word_name, int id_class) override;
        virtual int FindEntryOmonym(const Lexem& lname, int iclass, const Solarix::GramCoordPair &p) override;
        virtual int FindEntryOmonym(const Lexem& lname, int iclass, const lem::MCollect<Solarix::GramCoordPair> &p) override;
        virtual int FindEntryOmonym(const Lexem& lname, int iclass, const ExactWordEntryLocator &locator) override;

        virtual WordEntryEnumerator* ListEntries(const lem::UCString &name, int id_class) override;
        virtual WordEntryEnumerator* ListEntries() override;

        virtual Word_Coord FindWordForm(const UCString& name) override;
        virtual WordFormEnumerator* ListWordForms(const lem::UCString &form, bool allow_nonterminals) override;
        virtual WordFormEnumerator* ListWordForms(const lem::MCollect<lem::UCString> &forms) override;
        virtual WordFormEnumerator* ListWordForms_Fuzzy(const lem::UCString &word, float min_val) override;
        virtual WordFormEnumerator* ListWordForms_Globbing(const lem::UFString &mask) override;

        virtual int CountLexemes() override;
        virtual LexemeEnumerator* ListLexemes() override;

        virtual const SG_Entry& GetEntry(int ekey) override;
        virtual SG_Entry& GetEntryForChange(int ekey) override;

        virtual int GetPredefinedEntryKey(int index) override;
        virtual int FindQuantorEntry(int id_class) override;

#if defined SOL_LOADTXT
        virtual int LoadEntry(lem::StrParser<lem::UFString> &txt) override;
#endif

        virtual int CreateEntry(const lem::UCString &ename, int id_class) override;
        virtual int AddEntry(SG_Entry *new_entry) override;
        virtual const Lexem* AddLexeme(const Solarix::Lexem &lex) override;
        virtual const CP_Array* AddCoordPairs(const CP_Array &x) override;
        virtual const Lexem* ReattachLexeme(const Lexem *ptr) override;
        virtual const CP_Array* ReattachCoordPairs(const CP_Array *ptr) override;


        virtual void PrepareForMerging() override;
        virtual void CommitCompilation(lem::OFormatter &err) override;

        virtual CharNode* GetPrefixTreeForAllLanguages() override;
        virtual CharNode* GetPrefixTree(const std::set<int>& allowed_langs) override;

        virtual void ReplaceEntry(int ekey, SG_Entry *dummy) override;
        virtual void PostRead(Macro_Parser &txtfile, const Binarization_Options &options) override;

        virtual void LoadBin(lem::Stream &bin) override;
        virtual void SaveBin(lem::Stream &bin) const override;

        virtual void DetailedReport(OFormatter &txtfile) override;

        virtual LD_Seeker* Get_Seeker() override;

#if defined SOL_LOADBIN
        virtual LD_Seeker* Load_Seeker(lem::Stream &bin) override;
#endif

        virtual const lem::IntCollect& GetUEntries() override;

        void SetLazyLoad(const lem::Path & morphology_path);

        virtual int GetUnknownEntryKey() override;
    };
}

#endif
