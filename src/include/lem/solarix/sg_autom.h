// -----------------------------------------------------------------------------
// File SG_AUTOM.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// LEM C++ library  http://www.solarix.ru
//
// Классы Синтаксической Грамматики (Лексикона и Грамматической Сети).
//
// 30.09.2005 - изменено внутреннее представление мультилексем. Теперь вместо
//              хранения отдельных частей мультилексемы в виде динамического
//              списка они хранятся как обычная лексема с пробелами.
//
// 01.10.2005 - изменен способ хранения грамматической сети - теперь связки
//              хранятся не в каждой словрной статье, а в общем списке.
//
// 07.10.2005 - введена возможность загрузки статей только для определенного
//              языка и динамической догрузки.
//
// 20.05.2006 - добавлен класс Link_Generator для автоматического создания
//              парных обратных связок в тезаурусе в конце фазы компиляции.
//
// 24.05.2006 - для совместимости со словарями ispell каждая словарная статья 
//              может ссылаться на несколько таблиц формообразования. 
//
// 06.06.2006 - убран виртуальный метод SG_Entry::IsBogus - для экономии памяти,
//              (указатель в таблице виртуальных методов).
//
// 21.11.2006 - рефакторинг имен методов.
// 29.08.2010 - отказ от Lite версий, убираем соответствующие методы и поля
// 18.11.2010 - переработка хранилища словарных статей
// -----------------------------------------------------------------------------
//
// CD->15.03.1996
// LC->17.04.2018
// --------------

#ifndef SOL_SYNGRAM__H
#define SOL_SYNGRAM__H
#pragma once

#include <lem/config.h>

#include <set>

#if defined SOL_LOADTXT
#include <lem/string_parser.h>
#endif

#include <lem/RWULock.h>

#include <lem/tuple.h>
#include <lem/ptr_container.h>
#include <lem/mset.h>
#include <lem/stl.h>
#include <lem/macro_parser.h>

#include <lem/solarix/solarix_binarization_options.h>
#include <lem/solarix/dictionary_config_options.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/lexem.h>
#include <lem/solarix/tree_link.h>
#include <lem/solarix/grammar.h>
#include <lem/solarix/sg_defs.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/form_table.h>
#include <lem/solarix/sql_production.h>
#include <lem/solarix/SG_TagsList.h>
#include <lem/solarix/SG_LinkFlag.h>
#include <lem/solarix/CplxLeft.h>
#include <lem/solarix/Languages.h>

#undef AddForm
#undef GetForm
#undef CountForms
#undef min
#undef max

namespace Solarix
{
    using lem::uint8_t;

    using lem::Ptr_NC_Collect;
    using lem::MCollect;
    using lem::Collect;
    using lem::MSet;
    using lem::UCString;
    using lem::OFormatter;
    using lem::Iridium::BSourceState;
    using lem::IntCollect;

    inline uint8_t get_hash(const Lexem &x) { return x.GetHash(); }

    // ****************************************************
    // Вычисление хэш-кода для вектора координатных пар.
    // ****************************************************
    inline uint8_t get_hash(const CP_Array &a)
    {
        uint8_t res = 0;
        for (auto& x : a)
        {
            res ^= (x.GetCoord().GetIndex() + x.GetState());
        }

        return res;
    }


    inline uint8_t get_hash(const lem::MCollect< std::pair<int, int> > &a)
    {
        uint8_t res = 0;
        for (auto &x : a)
        {
            res ^= (x.first + x.second);
        }

        return res;
    }


    //**************************************************************************
    // Структура описывает соответствие ключа словарной статьи и её индекса.
    // Используется для организации отсортированного по величине ключа списка,
    // благодаря которому поиск статьи с заданным ключём ускоряется.
    //**************************************************************************
    class SG_KeyHandler
    {
    private:
        int key;
        int index;

    public:
        SG_KeyHandler() { key = index = UNKNOWN; }
        SG_KeyHandler(int Key, int Index) { key = Key; index = Index; }

        SG_KeyHandler(lem::Stream &bin);

#if defined SOL_LOADBIN 
        void LoadBin(lem::Stream &bin);
#endif

#if defined SOL_SAVEBIN
        void SaveBin(lem::Stream &bin) const;
#endif

        inline int GetKey() const { return key; }
        inline int GetIndex() const { return index; }
    };




    class LexicalAutomat;


#if defined SOL_LOADTXT && defined SOL_COMPILER
    // ******************************************************************
    // Генератор связей для тезауруса.
    // Позволяет автоматически сгенерировать обратные или дополнительные
    // связи для явно определенных в словаре.
    // ******************************************************************
    class Link_Generator
    {
    private:
        lem::zbool multitier; // многосвязный - в левой части есть 2 условия

        // Описание первого условия
        int iclass0, iclass1;
        Tree_Link direct_link;
        lem::UCString Aname, Bname; // условные имена точек в первом условии

        // Второе условие для многосвязного генератора
        int iclass20, iclass21;
        Tree_Link link2;
        lem::UCString Cname, Dname; // условные имена точек во втором условии

        // Результатная правая часть
        lem::UCString Xname, Yname; // подставляемые в генерируемую связку статьи из условия
        Tree_Link reverse_link;

    public:
        Link_Generator();

        void LoadTxt(
            Macro_Parser &txtfile,
            SynGram &sg,
            const Binarization_Options &options
        );

        bool IsMultitier() const { return multitier; }

        // Для простого генератора с одним условием в левой части - проверяем,
        // что связь подходит под условия
        bool Match(int iClass0, const Tree_Link &l, int iClass1) const;

        // Для многосвязного генератора с 2мя условиями в левой части - проверяем
        // связку и генерируем связки-результаты.
        bool Match2(
            SynGram &sg,
            int ek0,
            const Tree_Link &l,
            int ek1,
            lem::MCollect< lem::foursome<int, int, int, int> > &generated
        ) const;

        inline Tree_Link getReverseLink() const { return reverse_link; }
    };
#endif





    class AuxFormTypes;
    class LexiconStorage;
    class PhraseEnumerator;
    class PhraseNoteEnumerator;
    class SG_Class;
    class WordEntries;
    class SG_Net;
    class SG_EntryForm;
    class LanguageUsage;
    struct CharNode;
    class SG_Entry;
    class SG_DeclensionAutomat;
    struct ExactWordEntryLocator;

    class SynGram : public Grammar
    {
    public:
        enum { SegmentationNote = 0, SyntaxNote = 1, PivotNote = 2 };

    private:
        SG_Net * net; // Грамматическая сеть (тезаурус)
        AuxFormTypes * aux_form_types;
        LexiconStorage * storage;
        bool do_delete_storage;
        WordEntries * word_entries;
        Languages * langs; // List of valid languages specifications
        LanguageUsage * lang_usage; // language usage - default, input, output

        lem::Stream::pos_type entries_beg_pos; // позиция начала списка статей

        lem::zint internal_offset_buffer;

        SG_DeclensionAutomat* DSA;    // СубАвтомат Формообразования

#if defined SOL_LOADTXT && defined SOL_COMPILER
        std::map<UCString, CplxLeft*> cplx_map;
        lem::PtrCollect<CplxLeft> cplx_list;
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
        lem::Ptr< lem::Path > wordfreq_filename; // путь к временному файлу, куда записываются калибраторы с частотами слов
        lem::Ptr< lem::BinaryWriter > wordfreq_file;

        lem::PtrCollect<Link_Generator> link_generators;
        std::set< std::pair<int /*iclass*/, lem::UCString/*ename*/> > omonyms, omonyms_history;
#endif

#if defined SOL_CAA
#if defined LEM_THREADS
        lem::Process::RWU_Lock cs_prefix_tree;
#endif    
        Solarix::CharNode* prefix_tree;
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual bool ProcessLexem(
            const BethToken &t,
            Macro_Parser& txt,
            const Binarization_Options &options
        );

        virtual bool ProcessLexem2(
            const BethToken &t,
            Macro_Parser& txt,
            const Binarization_Options &options
        );

        void LoadEntryGroup(Macro_Parser& txtfile);

        virtual void LoadEntry(
            Macro_Parser& txtfile,
            bool is_extern,
            SG_Entry *dummy,
            const Binarization_Options &options
        );

        void LoadEntry(
            Macro_Parser& txtfile,
            bool is_extern,
            const Binarization_Options &options
        );

        void LoadQuantor(
            Macro_Parser& txtfile,
            bool is_extern,
            const Binarization_Options &options
        );

        void LoadEntryTag(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        );

        void LoadFrequency(Macro_Parser &txtfile, const lem::UCString & keyword);

        void LoadAuxWord(Macro_Parser& txtfile);

        virtual void PostRead(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        );
        //void ProcessSynEntries(void);
        //void BuildLookUpTable(void);
        //void SortUp(void);
        void Generate_Links(const Binarization_Options &opts);

        void LoadPhrase(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        );

        void Load_Link(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        );

        void LoadOmonym(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        );

        void Load_Link_Generator(
            Macro_Parser &txtfile,
            const Binarization_Options &options
        );

        void Add_Entry(SG_Entry *e);
        void Write_Declarations(const lem::Path &outdir);
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual void LoadClass(Macro_Parser& txtfile, bool is_extern);
#endif

        const GraphGram& GetGraphGram() const;

        void PrintMap_2(OFormatter &txtfile, int iclass);

        virtual GramClass* Create_Class() const;

    public:
        SynGram(Dictionary & dict, const Dictionary_Config &cfg);
        virtual ~SynGram();

        // Копирование блокируем.
        SynGram(const SynGram&) = delete;
        void operator=(const SynGram&) = delete;

#if defined SOL_LOADTXT
        int LoadEntry(lem::StrParser<lem::UFString> &txt);
#endif

#if defined SOL_SAVETXT
        void SaveTxt(OFormatter &txt);
#endif

#if defined SOL_SAVEBIN
        virtual void SaveBin(lem::Stream& bin) const;
#endif

        void SaveLexiconDb(const lem::Path &lexicon_db_path);

#if defined SOL_EXPORT_SQL
        virtual void Save_SQL(OFormatter &out, OFormatter &alters, const SQL_Production &sql_version);
        void SaveLemmatizatorSQL(OFormatter &out, OFormatter &alters, const SQL_Production &sql_version) const;
        virtual void SaveRules_SQL(OFormatter &out, OFormatter &alters, const SQL_Production &sql_version);
#endif

#if defined SOL_LOADBIN
        virtual void LoadBin(lem::Stream& bin, const Load_Options &opt);
#endif

#if defined SOL_REPORT
        virtual void Report(OFormatter &where_to);
        virtual void PrintMap(OFormatter &txtfile);
        void DetailedReport(OFormatter &txtfile);
#endif

        int FindEntry(const UCString& name, int iclass, bool do_account_quantors);
        int FindEntry2(const Lexem& name, int iclass);

        // пытаемся найти метастатью, возвращаем ее ID или UNKNOWN при неуспехе.
        int FindMetaEntry(const UCString& name, int id_class);

        bool FindMLEntryForm(const Lexem& ml_name);

        // Ищем все словарные статьи с указанным именем.
        bool FindEntries(const Lexem& name, lem::MCollect<int> &ies) const;

        int FindComplexEntry(const UFString &phrase);

        PhraseEnumerator* GetComplexEntries(bool left = true, bool right = true);
        PhraseNoteEnumerator* EnumeratePhraseNotes(int id_phrase);

        // Возвращается индекс доступа к кванторной статье
        // по заданному грамматическому классу. Если найти
        // кванторную статью не удается, то возвращаем UNKNOWN.
        int Find_Quantor_Entry(int iclass);

        const SG_DeclensionAutomat& Get_DSA(void) const { return *DSA; }
        SG_DeclensionAutomat& Get_DSA(void) { return *DSA; }

#if defined SOL_LOADTXT
        const Word_Coord FindEntryForm(const lem::UCString& name) const;
        void FindEntryForms(const UCString& name, lem::MCollect<Word_Coord> &wc) const;
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
        int FindEntryOmonym(const Lexem& lname, int iclass, const Solarix::GramCoordPair &p) const;
        int FindEntryOmonym(const Lexem& lname, int iclass, const lem::MCollect<Solarix::GramCoordPair> &p);
        int FindEntryOmonym(const Lexem& lname, int iclass, const ExactWordEntryLocator & locator);
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
        //inline int GetnCalibr(void) const { return CastSizeToInt(calibr.size()); }
        //inline const SG_calibrator& GetCalibr( int i ) const { return *calibr[i]; }
#endif

        int GetMaxMLLen() const;

        virtual const lem::UCString GetName() const;

#if defined SOL_LOADTXT && defined SOL_COMPILER
        virtual void Prepare(const lem::Path &outdir, const Binarization_Options &opts);
#endif

#if defined SOL_CAA
        int FindLinkedEntryKey(
            int From_Entry_Key,
            const lem::UCString &link_name
        );
#endif

        int GetPredefinedEntryKey(int index);

#if defined SOL_EXPORT_SQL
        void Dump_XML(OFormatter &xml, lem::OFormatter &xsd, int max_entry_count);
#endif

#if defined SOL_CAA
        int Calc_Distance(int ientry1, int ientry2, int max_dist);
#endif

#if defined SOL_CAA
        int IsMultiLexemBegin(const Lexem &l) const;
        bool IsMultiLexem(const Lexem &l) const;
        bool IsWordForm(const Lexem &l) const;
#endif

        int Find_Language(const UCString &Name);
        inline Languages& languages() const { return *langs; }

        inline const SG_Net& Get_Net() const { return *net; }
        inline       SG_Net& Get_Net() { return *net; }


        // Get the total number of entries (for all languages if Id_Language=UNKNOWN)
        int GetnEntry(int Id_Language = UNKNOWN);

        // Подсчет общего числа словоформ
        int Count_Forms(int Id_Language = UNKNOWN);

        // Кол-во фразовых статей
        int GetnPhrase();

        int Find_Link(const UCString &s) const;
        Tree_Link Find_Tree_Link(const UCString &s) const;

        const SG_Class& GetClass(int id);

#if defined SOL_CAA
        const CharNode& GetPrefixTree(void);
        CharNode* GetPrefixTreeForAllLanguages(void);
        CharNode* GetPrefixTree(const std::set<int>& allowed_langs);
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
        bool IsOmonym(int iclass, const lem::UCString &ename) const;
#endif

#if defined SOL_LOADBIN || defined SOL_COMPILER
        void PrepareForMerging();
#endif

        LexiconStorage& GetStorage() { return *storage; }
        void SetStorage(LexiconStorage *stg, bool _do_delete);

        WordEntries& GetEntries() { return *word_entries; }
        void SetEntries(WordEntries *x);

        AuxFormTypes& GetAuxFormTypes() { return *aux_form_types; }
        bool GetAuxForm(int id_entry, int iform, int aux_type_id, lem::UFString &aux_form);


#if defined SOL_LOADTXT && defined SOL_COMPILER
        void StoreCplxLeft(const lem::UFString &phrase);
#endif

        // Является ли слово началом многословной левой части сложной связки
        bool IsComplexHeadword(const UCString &w, int &minlen, int &maxlen);

        const SG_Entry& GetEntry(int ekey);
        const lem::IntCollect& GetUEntries(void);


        void SerializeCoords(
            const lem::MCollect< Solarix::GramCoordPair > & pairs,
            lem::UFString &str,
            bool as_numbers
        );

        void ComposeEntryAttrs(
            const SG_Entry &e,
            lem::UFString &entry_attrs,
            bool as_numbers
        );

        void ComposeFormDims(
            const SG_Entry &e,
            const SG_EntryForm &form,
            lem::UFString &form_dims,
            bool as_numbers
        );

        LanguageUsage& GetLanguageUsage(void);
    };

#if defined SOL_CAA
    class SG_Stemmer
    {
    private:
        lem::Process::Dll dll;
        void* hStemmer;

        typedef void*(*sol_CreateStemmerForLanguage_fun)(const char *lang2);
        typedef void(*sol_DeleteStemmer_fun)(void* hStemmer);
        typedef int(*sol_Stem_fun)(void* hStemmer, wchar_t *Word);

        sol_CreateStemmerForLanguage_fun sol_CreateStemmerForLanguage;
        sol_DeleteStemmer_fun            sol_DeleteStemmer;
        sol_Stem_fun                     sol_Stem;

    public:
        SG_Stemmer(void);

        void Load(const lem::Path &dllpath);
        bool Stem(const UCString &org, UCString &stem) const;
    };
#endif



#if defined SOL_LOADTXT
    extern int sol_load_class_entry(
        Macro_Parser &txtfile,
        SynGram &gram,
        bool do_search = true,
        bool do_check = true
    );
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
    extern int sol_load_omonym(
        Macro_Parser &txtfile,
        SynGram &gram,
        bool do_check
    );
#endif

    extern void sol_print_class_entry(
        OFormatter &txtfile,
        SynGram &gram,
        const int entry_key
    );

} // namespace 'Solarix'

#endif
