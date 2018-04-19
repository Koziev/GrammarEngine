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

    // ��������� ������������� ����� - �������� ���������� ��������
    struct TreeScorerQuantification
    {
        enum { MAX_COUNT = 1000000 };

        int min_count;
        int max_count;

        TreeScorerQuantification() : min_count(1), max_count(1) {}

        int GetMinCount() const { return min_count == -1 ? 0 : min_count; }
        int GetMaxCount() const { return max_count == -1 ? MAX_COUNT : max_count; }
        bool IsNot() const { return min_count == -1; }

        // ������� ��� ����������� �� ����������� ����� ��������
        void SetNoLimits() { min_count = 0; max_count = MAX_COUNT; }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser & txtfile);
#endif
    };


    // ---------------------------------------------------------------------------------------
    // �������, ����������� ������ ������ ��������� � ������, �������� - ��� � ���� ���� ���
    // �����, ������ � �������� ������ ������, � ���������� ������ ����.
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

        // ��������� ���������� (���� ��������)
        lem::UCString marker;

        // ��������� �������
        int id_group; // ����� ������ �����������
        lem::UCString word;
        int id_entry; // �������� �� �������������� ����� ��������� ������
        int id_metaentry; // ���� ����������� ��������� � ����������
        int id_class;
        lem::UCString wordset_name, wordentryset_name, wordformset_name;
        bool is_positive;
        int link_type; // ��� �����, ��������� � ������ ���� �� ��������, �� ��������� ������������.
        int relative_position; // ��� �������� �������������� ������������ �������������� ������ ����

        CPE_Array coords;
        int ThesaurusCheck_Link, ThesaurusCheck_Entry; // ��� ��������, ��� ������� ����� ������� � �������� ������� ��������� ����� �����
        lem::MCollect<CollocFilterSetChecker> set_checkers; // ��� �������������� �������� ��������� � ����������� ���������

#if defined SOL_LOADTXT && defined SOL_COMPILER
        ExactWordEntryLocator omonym_resolver;
#endif

        lem::MCollect<BackRefCorrel> back_correls; // ������������ � �������������� ������

        TreeScorerQuantification quantification; // ��������� ������ �����
        TreeScorerQuantification children_quantification; // ����� �� ���� �������� ������, ���������� ��� ����������� �������������
        lem::MCollect<TreeScorerPoint*> leafs;

        // �������������� ������� ��� �����
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
        int type; // 0 - ���� �������� �������� ������, 1 - �������� �� ����� ngram
        int score;

        int id_fact; // id ���������� ngram
        lem::MCollect<lem::UCString> args; // ��� ���������� ��� �������� � ���������� �������

        lem::Ptr<TrFunCall> score_fun; // ������� ��� ������� ��������

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
