#if !defined SyllabRule__H
#define SyllabRule__H

#include <lem/noncopyable.h>
#include <lem/ptr_container.h>
#include <lem/RWULock.h>
#include <lem/solarix/coord_pair.h>

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
    class AlphabetStorage;


    class SyllabContextPoint
    {
    private:
        void operator = (const SyllabContextPoint &x);

    protected:
        bool is_syllab, is_left_boundary, is_right_boundary;
        lem::UCString syllab, normalized_syllab;
        lem::uint32_t char_ucs4, normalized_char_ucs4;
        int id_entry, id_class;
        lem::MCollect<Solarix::GramCoordPair> coords;

    protected:
        SyllabContextPoint();

    public:
        SyllabContextPoint(const SyllabContextPoint &x);

        bool IsSyllab() const { return is_syllab; }
        bool IsLeftBoundary() const { return is_left_boundary; }
        bool IsRightBoundary() const { return is_right_boundary; }

        lem::UCString BuildSyllab(bool Normalized) const;

        lem::uint32_t GetChar() const { return char_ucs4; }
        lem::uint32_t GetNormalizedChar() const { return normalized_char_ucs4; }

        int GetEntryID() const { return id_entry; }
        int GetClassID() const { return id_class; }
        const lem::MCollect<GramCoordPair>& GetCoords(void) const { return coords; }
        bool FindPair(int id_coord, int id_state) const;

        void Print(lem::OFormatter &to) const;
    };

    class SyllabContextLeftBoundary : public SyllabContextPoint
    {
    public:
        SyllabContextLeftBoundary() { is_left_boundary = true; }
    };

    class SyllabContextRightBoundary : public SyllabContextPoint
    {
    public:
        SyllabContextRightBoundary() { is_right_boundary = true; }
    };


    class SyllabContext;
    class SyllabContextGroup : public SyllabContextPoint
    {
    public:
        SyllabContextGroup(const SyllabContext &points, int merge_index0, int merge_count);
    };


    class SyllabContextSymbol : public SyllabContextPoint
    {
    public:
        SyllabContextSymbol(lem::uint32_t ucs32, lem::uint32_t normalized_ucs32, int _id_entry, int _id_class, const lem::MCollect<GramCoordPair> &_coords);
    };


    class SyllabContextUnknownSymbol : public SyllabContextPoint
    {
    public:
        SyllabContextUnknownSymbol(lem::uint32_t ucs32);
    };


    class SyllabRulesForLanguage;
    class GraphGram;
    class LA_RecognitionTrace;

    class SyllabContext : lem::NonCopyable
    {
    private:
        lem::Ptr_NC_Collect<SyllabContextPoint> points;

        void Replace(int start_index, int count, lem::MCollect<SyllabContextPoint*> & new_points);

    public:
        SyllabContext(GraphGram &alphabet, const lem::UCString &word, int id_language);

        int Count(void) const { return CastSizeToInt(points.size()); }
        const SyllabContextPoint& GetPoint(int index) const { return *points[index]; }
        SyllabContextPoint* ExtractPoint(int index);

        void Print(lem::OFormatter &to) const;

        void GetResultSyllabs(lem::MCollect<lem::UCString> &result_syllabs, bool Normalized) const;
        void Apply(const SyllabRulesForLanguage & rules, LA_RecognitionTrace *trace);
    };


    class SyllabConditionPoint : lem::NonCopyable
    {
    private:
        lem::MCollect<lem::uint32_t> codes;
        int id_class;
        int id_entry;
        int id_coord0, id_state0;
        bool is_left_boundary, is_right_boundary;
        bool is_positive;

        bool Positive(bool r) const;

    public:
        SyllabConditionPoint();
        SyllabConditionPoint(
            const lem::MCollect<lem::uint32_t> &ucs4,
            int _id_class,
            int _id_entry,
            int _id_coord0,
            int _id_state0,
            bool _is_left_boundary,
            bool _is_right_boundary,
            bool _is_positive
        );

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict);
#endif

        void Store(AlphabetStorage * storage, int id_rule, int point_index) const;

        bool Check(const SyllabContext &ctx, int cursor_pos) const;
    };


    class SyllabCondition : lem::NonCopyable
    {
    private:
        lem::Ptr_NC_Collect<SyllabConditionPoint> points;

    public:
        SyllabCondition();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict);
#endif

        void Store(AlphabetStorage * storage, int id_rule) const;
        void Load(AlphabetStorage * storage, int id_rule);

        int Count(void) const { return CastSizeToInt(points.size()); }
        const SyllabConditionPoint& GetPoint(int index) const { return *points[index]; }

        bool Check(const SyllabContext &ctx, int cursor_pos) const;
    };



    class SyllabResultPoint : lem::NonCopyable
    {
    private:
        int copy_index;
        int merge_index0, merge_count;

    public:
        SyllabResultPoint();
        SyllabResultPoint(int _copy_index, int _merge_index0, int _merge_count);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict, const SyllabCondition &condition);
#endif

        void Store(AlphabetStorage * storage, int id_rule, int point_index) const;

        SyllabContextPoint* Produce(SyllabContext & ctx, int cursor_pos) const;
    };

    class SyllabResult : lem::NonCopyable
    {
    private:
        lem::Ptr_NC_Collect<SyllabResultPoint> points;
        int cursor_shift;

    public:
        SyllabResult();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict, const SyllabCondition &condition);
#endif

        void Load(AlphabetStorage * storage, int id_rule, int _cursor_shift);

        int Count(void) const { return CastSizeToInt(points.size()); }
        const SyllabResultPoint& GetPoint(int index) const { return *points[index]; }

        int GetShift(void) const { return cursor_shift; }

        void Store(AlphabetStorage * storage, int id_rule) const;

        void Produce(SyllabContext & ctx, int cursor_pos, lem::MCollect<SyllabContextPoint*> &new_points) const;
    };


    class SyllabRule : lem::NonCopyable
    {
    private:
        int id_src, id_language;
        lem::UCString name;
        SyllabCondition condition;
        SyllabResult result;

    public:
        SyllabRule();
        SyllabRule(const lem::UCString &_name, int _id_src, int _id_language);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict);
#endif

        void Store(AlphabetStorage * storage) const;

        int GetLanguage() const { return id_language; }
        int GetSource() const { return id_src; }
        const lem::UCString& GetName() const { return name; }
        const SyllabCondition& GetCondition() const { return condition; }
        SyllabCondition& GetCondition() { return condition; }
        const SyllabResult& GetResult() const { return result; }
        SyllabResult& GetResult() { return result; }
    };


    class SyllabRulesForLanguage : lem::NonCopyable
    {
    public:
        typedef std::multimap<int, const SyllabRule*> LEN2RULES;
        typedef LEN2RULES::const_iterator LEN2RULES_IT;

    private:
        int id_language;
        lem::Ptr_NC_Collect<SyllabRule> rules;
        LEN2RULES len2rules;
        int min_len, max_len;

    public:
        SyllabRulesForLanguage(int id_language);
        void Load(AlphabetStorage *storage);

        int GetMinLen() const { return min_len; }
        int GetMaxLen() const { return max_len; }

        std::pair<SyllabRulesForLanguage::LEN2RULES_IT, SyllabRulesForLanguage::LEN2RULES_IT> GetRulesForContextLen(int len) const { return len2rules.equal_range(len); }
    };


    class SyllabRules : lem::NonCopyable
    {
    private:
        AlphabetStorage *storage;

#if defined LEM_THREADS
        lem::Process::RWU_Lock cs;
#endif

        lem::Ptr_NC_Collect<SyllabRulesForLanguage> rules;
        std::map< int, const SyllabRulesForLanguage *> lang2rules;

    public:
        SyllabRules();
        void Connect(AlphabetStorage * _storage);

        const SyllabRulesForLanguage & GetRules(int id_language);
    };

}

#endif
