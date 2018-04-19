#if !defined LA_CROP_RULE__H
#define LA_CROP_RULE__H

#include <lem/noncopyable.h>
#include <boost/regex.hpp>
#include <lem/ucstring.h>
#include <lem/zeroed.h>
#include <lem/ufstring.h>
#include <lem/math/fp1.h>

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

    class LA_CropRule : lem::NonCopyable
    {
    public:
        typedef wchar_t HashType;

    private:
        int id;
        int src_location;
        lem::UCString name;
        int id_language;
        lem::zbool is_prefix, is_affix, is_regex, case_sensitive;
        lem::UFString condition;
        lem::UCString result;
        lem::UFString rx_result;
        boost::wregex rx_condition;
        lem::Real1 rel;

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void CompileCondition(const lem::UFString &s);
#endif

    public:
        LA_CropRule();
        LA_CropRule(int Id, const lem::UCString &Name, int Id_Lang, bool IsPrefix, bool IsAffix,
            bool IsCaseSensitive, bool IsRegex, const lem::UFString &Condition, const lem::UFString &Result, int SourceID, lem::Real1 Rel);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict);
#endif

        const lem::UCString& GetName() const { return name; }
        int GetLanguage() const { return id_language; }
        int GetId() const { return id; }
        bool IsPrefix() const { return is_prefix; }
        bool IsAffix() const { return is_affix; }
        bool IsCaseSensitive() const { return case_sensitive; }
        bool IsRegex() const { return is_regex; }
        lem::Real1 GetRel() const { return rel; }

        int GetSourceLocation() const { return src_location; }

        LA_CropRule::HashType GetHash();
        const lem::UFString & GetCondition() const { return condition; }
        const lem::UFString & GetResult() const { return rx_result; }

        static LA_CropRule::HashType CalcHash(const wchar_t * str, bool IsPrefix, bool IsAffix);

        void SetId(int Id) { id = Id; }
        bool Apply(const lem::UCString &text, lem::UCString &result) const;
    };
}

#endif
