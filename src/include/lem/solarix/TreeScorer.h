#if !defined TreeScorer__H
#define TreeScorer__H

#include <lem/noncopyable.h>
#include <lem/ptr_container.h>
#include <lem/solarix/coord_pair.h>
#include <lem/solarix/CollocFilterSetChecker.h>
#include <lem/solarix/BackRefCorrel.h>
#include <lem/solarix/translation.h>

#if defined SOL_LOADTXT && defined SOL_COMPILER
#include <lem/solarix/ExactWordEntryLocator.h>
#endif


namespace lem
{
    namespace Iridium
    {
        class Macro_Parser;
    }
}

namespace Solarix
{
    class Dictionary;
    class LexiconStorage;
    class WordEntrySet;
    class TreeScorer;
    class SynGram;
    class Word_Form;
    class TreeScorers;
    class TreeScorerApplicationContext;

    // параметры повторяемости ветки - диапазон количества повторов
    struct TreeScorerQuantification
    {
        enum { MAX_COUNT = 1000000 };

        int min_count;
        int max_count;

        TreeScorerQuantification() : min_count(1), max_count(1) {}

        int GetMinCount() const { return min_count == -1 ? 0 : min_count; }
        int GetMaxCount() const { return max_count == -1 ? MAX_COUNT : max_count; }
        bool IsNot() const { return min_count == -1; }

        // снимаем все ограничения на допускаемое число повторов
        void SetNoLimits() { min_count = 0; max_count = MAX_COUNT; }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser & txtfile);
#endif
    };


    // ---------------------------------------------------------------------------------------
    // функции, проверяющие разные особые топологии в дереве, например - что у узла есть два
    // листа, идущие в исходном тексте подряд, с одинаковой частью речи.
    // ---------------------------------------------------------------------------------------

    struct TreeScorerPredicateArg
    {
        int id_class;

        TreeScorerPredicateArg();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile);
#endif
    };

    class LinkEdgeContainer;
    class TreeScorerPredicate : lem::NonCopyable
    {
    private:
        lem::UCString func_name;
        lem::Collect<TreeScorerPredicateArg> args;

    public:
        TreeScorerPredicate() {}
        TreeScorerPredicate(const lem::UCString &_func_name, const lem::Collect<TreeScorerPredicateArg> &_args);
        virtual ~TreeScorerPredicate() {}

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile);
#endif

        void Store(LexiconStorage & storage, int id_host_point);

#if defined SOL_CAA
        bool DoesMatch(
            SynGram &sg,
            const Word_Form & version,
            const LinkEdgeContainer & edges,
            const TreeScorerApplicationContext & context
        ) const;
#endif
    };

    class TreeScorerMarkers : lem::NonCopyable
    {
    private:
        lem::MCollect<lem::UCString> bound_markers;

    public:
        TreeScorerMarkers() {}

        bool IsAlreadyBound(const lem::UCString & uppercased_marker) const
        {
            return bound_markers.find(uppercased_marker) != UNKNOWN;
        }

        void AddBoundMarker(const lem::UCString & uppercased_marker)
        {
            bound_markers.push_back(uppercased_marker);
        }

        int CountMarkers() const { return CastSizeToInt(bound_markers.size()); }
        const lem::UCString& GetMarker(int index) const { return bound_markers[index]; }
    };

    class TreeScorerBoundVariables;

    class TreeScorerPoint : lem::NonCopyable
    {
    public:
        int id;
        int id_src;

        // связанная переменная (если заявлена)
        lem::UCString marker;

        // первичные фильтры
        int id_group; // вызов группы поддеревьев
        lem::UCString word;
        int id_entry; // проверка на грамматическую форму словарной статьи
        int id_metaentry; // если проверяется вхождение в метастатью
        int id_class;
        lem::UCString wordset_name, wordentryset_name, wordformset_name;
        bool is_positive;
        int link_type; // тип ребра, входящего в данный узел из родителя, по умолчанию игнорируется.
        int relative_position; // для проверки относительного расположения сопрставленных графом слов

        CPE_Array coords;
        int ThesaurusCheck_Link, ThesaurusCheck_Entry; // для проверки, что опорная точка связана с заданной статьей указанным типом связи
        lem::MCollect<CollocFilterSetChecker> set_checkers; // для дополнительной проверки вхождения в именованные множества

#if defined SOL_LOADTXT && defined SOL_COMPILER
        ExactWordEntryLocator omonym_resolver;
#endif

        lem::MCollect<BackRefCorrel> back_correls; // согласования с маркированными узлами

        TreeScorerQuantification quantification; // параметры данной ветки
        TreeScorerQuantification children_quantification; // суммы по всем дочерним веткам, необходимо для оптимизации сопоставления
        lem::MCollect<TreeScorerPoint*> leafs;

        // дополнительные условия для узлов
        lem::MCollect<TreeScorerPredicate*> predicates;

    private:
#if defined SOL_LOADTXT && defined SOL_COMPILER

        void LoadTxt_Point(
            Dictionary & dict,
            lem::Iridium::Macro_Parser & txtfile,
            const TreeScorer &body,
            WordEntrySet & sets,
            TreeScorers & scorers,
            TreeScorerMarkers & markers
        );

        void LoadPreciser(
            Dictionary & dict,
            lem::Iridium::Macro_Parser & txtfile,
            WordEntrySet &sets,
            TreeScorerMarkers & markers
        );

        void LoadMarker(
            Dictionary & dict,
            lem::Iridium::Macro_Parser & txtfile,
            TreeScorerMarkers & markers
        );

#endif

        bool Positive(bool f) const;

    public:
        TreeScorerPoint();

        ~TreeScorerPoint();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt_Sequence(
            Dictionary & dict,
            lem::Iridium::Macro_Parser & txtfile,
            const TreeScorer &body,
            WordEntrySet & sets,
            TreeScorers & scorers,
            TreeScorerMarkers & markers
        );

        void LoadTxt_Tree(
            Dictionary & dict,
            lem::Iridium::Macro_Parser & txtfile,
            const TreeScorer &body,
            WordEntrySet & sets,
            TreeScorers & scorers,
            TreeScorerMarkers & markers
        );
#endif

        const lem::UCString & GetWord() const { return word; }
        int GetEntryKey() const { return id_entry; }
        int GetMetaEntryKey() const { return id_metaentry; }
        const lem::UCString& GetSetName() const;

        bool IsNamedSubtree() const { return id_group != UNKNOWN; }
        int GetNamedSubtreeGroupId() const { return id_group; }

        bool IsWord() const { return !word.empty(); }
        bool IsWordentrySet() const { return !wordentryset_name.empty(); }
        bool IsWordSet() const { return !wordset_name.empty(); }
        bool IsWordformSet() const { return !wordformset_name.empty(); }
        bool IsEntry() const { return id_entry != UNKNOWN; }
        bool IsMetaEntry() const { return id_metaentry != UNKNOWN; }
        bool IsClass() const { return id_class != UNKNOWN; }
        bool IsAny() const { return id_entry == ANY_STATE; }

        bool HasConstraints() const;

        const TreeScorerPoint * FindNonQuantorNode() const;

        int GetRelativePosition() const { return relative_position; }

        int HasLeaves() const { return children_quantification.max_count > 0; }
        int GetId() const { return id; }

        int Store(LexiconStorage & storage, int id_parent_point);

#if defined SOL_CAA
        bool DoesMatch(
            SynGram &sg,
            const Word_Form & version,
            const LinkEdgeContainer & edges,
            const TreeScorerApplicationContext & context,
            const TreeScorerBoundVariables & bound_variables
        ) const;
#endif
    };


    class TreeScorerBoundVariables;

    class TreeScorerResult : lem::NonCopyable
    {
    public:
        enum { UnknownScoreType = -1, NumberScoreType = 0, NGramScoreType = 1, FuncScoreType = 2 };

    private:
        int type; // 0 - явно заданная числовая оценка, 1 - указание на вызов ngram
        int score;

        int id_fact; // id вызываемой ngram
        lem::MCollect<lem::UCString> args; // имя аргументов для передачи в вызываемую функцию

        lem::Ptr<TrFunCall> score_fun; // функция для сложной проверки

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadBoundVars(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, const TreeScorerMarkers & markers);
#endif

    public:
        TreeScorerResult();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, const TreeScorerMarkers & markers);
#endif

        int GetExpressionType() const { return type; }
        lem::UFString SerializeExpression() const;
        void DeserializeExpression(int expr_type, const lem::UFString & serialized);
        void Link(const TrFunctions &funs);

#if defined SOL_CAA
        int Calculate(
            Dictionary & dict,
            const TreeScorerBoundVariables & bound_variables,
            const ElapsedTimeConstraint & constraints,
            TrTrace *trace_log
        ) const;
#endif
    };


    class TreeScorer : lem::NonCopyable
    {
    private:
        int id_language;
        TreeScorerPoint root;
        TreeScorerResult score;
        int id_group;
        bool generic;

    public:
        TreeScorer();

        int GetLanguage() const { return id_language; }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, WordEntrySet & sets, TreeScorers & scorers);
#endif

        void Save(LexiconStorage & storage);

        bool IsNamedGroup() const { return id_group != UNKNOWN; }
    };


}
#endif
