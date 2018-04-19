#if !defined LA_UNBREAKABLE_RULE__H
#define LA_UNBREAKABLE_RULE__H

#include <lem/noncopyable.h>
#include <lem/zeroed.h>
#include <lem/ufstring.h>
#include <lem/ucstring.h>

namespace lem
{
    namespace Iridium
    {
        class Macro_Parser;
    }
}

namespace Solarix
{
    class LA_UnbreakableRule : lem::NonCopyable
    {
    private:
        int id;
        lem::zbool is_regex;
        lem::UFString pattern;
        lem::UCString name;
        int id_language;
        int src_location;

    public:
        LA_UnbreakableRule();
        LA_UnbreakableRule(int Id, const lem::UCString &Name, int Id_Lang, bool IsRegex, const lem::UFString &Pattern, int SourceID);

        int GetSourceLocation() const { return src_location; }

        int GetId() const { return id; }
        void SetId(int _id) { id = _id; }

        bool IsRegex() const { return is_regex; }
        const lem::UCString& GetName() const { return name; }
        const lem::UFString& GetPattern() const { return pattern; }
        int GetLanguage() const { return id_language; }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(Macro_Parser &txtfile, Dictionary &dict);
#endif
    };

}

#endif
