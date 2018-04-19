#if !defined SOL_KNOWLEDGE_BASE__H
#define SOL_KNOWLEDGE_BASE__H

#include <map>
#include <lem/RWULock.h>
#include <lem/noncopyable.h>
#include <lem/ptr_container.h>
#include <lem/solarix/coord_pair.h>
#include <lem/solarix/KB_CheckingResult.h>
#include <boost/regex.hpp>

namespace Solarix
{
    class Dictionary;
    class LexiconStorage;
    class KB_Fact;
    class PredicateTemplate;

    class KB_Facts : lem::NonCopyable
    {
    public:
        int id;
        lem::UCString name;
        int id_language;
        int n_arg;
        int n_ret;
        int ret_type; // 0 - boolean, 1 - integer
        int query_mode; // 0 - загружать все в память и кэшировать, 1 - все аргументы по word, 2 - все аргументы по id_entry
        bool check_features; // true если даже для query_mode!=0 необходимо после проверки лемм/лексем проверить еще и координатны пары...

        int violation_score; // штраф за нарушение
        PredicateTemplate *violation_handler; // шаблон предиката, который будет создан в случае нарушения данного факта

#if defined SOL_LOADTXT && defined SOL_COMPILER
        bool allow_generic; // если при компиляции не нужно выбрасывать ошибку в случае, если очередной факт имеет не-индексируемый способ доступа
#endif

    public:
        KB_Facts();
        ~KB_Facts();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(Solarix::Dictionary &dict, lem::Iridium::Macro_Parser &txtfile);
        void UpdateQueryMode(const KB_Fact & x);
#endif

        void SetId(int _id) { id = _id; }

        const lem::UCString& GetName() const { return name; }
        int GetId() const { return id; }
        int GetLanguage() const { return id_language; }
        int CountOfArg() const { return n_arg; }
        int CountOfRet() const { return n_ret; }

        int GetReturnType() const { return ret_type; }
        bool DoesReturnBoolean() const { return ret_type == 0; }
        bool DoesReturnInteger() const { return ret_type == 1; }

        int GetQueryMode() const { return query_mode; }
        bool IsQueryableByWords() const { return query_mode == 1; }
        bool IsQueryableByEntries() const { return query_mode == 2; }

        bool NeedsFeaturesCheck() const { return check_features; }
    };

    class Word_Form;
    struct ExactWordEntryLocator;

    class KB_Argument : lem::NonCopyable
    {
    public:
        bool is_positive;
        int id_entry, id_class, id_metaentry;
        lem::UCString word;
        lem::UFString regex_str;
        boost::wregex rx; // для функции @regex/@regex_strict
        bool is_regex, case_sensitive;
        lem::UCString wordentryset_name, wordset_name;
        CPE_Array coords;
        int ThesaurusCheck_Link, ThesaurusCheck_Entry;

    private:
#if defined SOL_CAA
        bool Positive(bool f) const;
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadPreciser(
            Dictionary & dict,
            lem::Iridium::Macro_Parser & txtfile,
            Solarix::ExactWordEntryLocator & locator
        );
#endif

    public:
        KB_Argument();

        void InitRegularExpression();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(const KB_Facts & facts, Solarix::Dictionary &dict, lem::Iridium::Macro_Parser &txtfile);
#endif

#if defined SOL_CAA
        bool Match(Solarix::Dictionary *dict, const Solarix::Word_Form &val) const;
#endif

        bool IsQueryableByEntry() const;
        bool IsQueryableByWord() const;
        bool NeedsFeatureCheck() const;
        bool IsMetaEntry() const;
    };




    class KB_BoolResult : public KB_CheckingResult
    {
    public:
        KB_BoolResult(int bool_val, int false_fine);
    };

    class KB_IntResult : public KB_CheckingResult
    {
    public:
        KB_IntResult(int int_val);
    };


    class KB_NotMatchedResult : public KB_CheckingResult
    {
    public:
        KB_NotMatchedResult();
    };


    class KnowledgeBase;
    class KB_Fact : lem::NonCopyable
    {
    public:
        int id_group;
        lem::MCollect<KB_Argument*> args;
        int bool_return; // возвращаемый результат для булевской проверки
        int false_score; // опционально - если для bool результата (обычно false) возвращается еще штраф. Значение 0 - значит штраф неприменим, и выполняется жесткий отказ.

        int int_return; // возвращаемое целое число (обычно n-граммы)

        enum { MAX_ARG_FOR_QUERY = 5 };

    public:
        KB_Fact();
        ~KB_Fact();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(KnowledgeBase &kb, Solarix::Dictionary &dict, lem::Iridium::Macro_Parser &txtfile);
#endif

        int GetGroupId() const { return id_group; }
        int CountArgs() const { return CastSizeToInt(args.size()); }
        const KB_Argument & GetArg(int index) const { return *args[index]; }

        int GetBooleanReturn() const { return bool_return; }
        int GetFalseScore() const { return false_score; }
        int GetIntegerReturn() const { return int_return; }

        bool IsQueryableByEntries() const;
        bool IsQueryableByWords() const;
        bool IsMultiIndexed() const;
        bool NeedsFeatureCheck() const;

#if defined SOL_CAA
        KB_CheckingResult Match(Solarix::Dictionary *dict, const KB_Facts & facts, const lem::MCollect<const Solarix::Word_Form*> & args) const;
#endif
    };





#if defined SOL_CAA
    class KB_CachedFacts : lem::NonCopyable
    {
    private:
        int id;
        lem::PtrCollect< KB_Fact > facts;

    public:
        KB_CachedFacts(int _id);

        int CountOfFacts() const { return CastSizeToInt(facts.size()); }
        const KB_Fact& GetFactByIndex(int index) const { return *facts[index]; }

        void AddFact(KB_Fact * x);

        KB_CheckingResult Match(Solarix::Dictionary *dict, const KB_Facts &facts, const lem::MCollect<const Solarix::Word_Form*> & args) const;
    };
#endif



    class KnowledgeBase
    {
    private:
        Solarix::Dictionary *dict;
        LexiconStorage *storage;

#if defined LEM_THREADS
        lem::Process::RWU_Lock facts_cs, cached_facts_cs;
#endif   

        lem::PtrCollect<KB_Facts> fact_groups;
        std::map< lem::UCString, int > name2facts;
        std::map< int /*id*/, KB_Facts* > id2facts;

#if defined SOL_CAA
        lem::PtrCollect<KB_CachedFacts> cached_facts;
        std::map< int /*id*/, const KB_CachedFacts* > id2cached_facts;
#endif

#if defined SOL_CAA
        void LoadSingleFact(int id_fact, KB_CachedFacts & cache);
        const KB_Facts& LoadFacts(int id);
        const KB_CachedFacts& LoadAndCacheFacts(int id);
#endif

    public:
        KnowledgeBase(Solarix::Dictionary *Dict);
        ~KnowledgeBase();

        void Connect(LexiconStorage *stg);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadFactsTxt(lem::Iridium::Macro_Parser &txtfile);
        void LoadFactTxt(lem::Iridium::Macro_Parser &txtfile);
        int FindFacts(const lem::UCString & name) const;
        const KB_Facts& GetFacts(int id) const;
        void AllFactsCompiled();
#endif

#if defined SOL_CAA
        KB_CheckingResult Prove(int id_facts, const lem::MCollect< const Solarix::Word_Form * > &args);
#endif
    };

}


#endif
