#if !defined GG_OPERATION__H
#define GG_OPERATION__H

#include <lem/ucstring.h>
#include <lem/noncopyable.h>
#include <map>
#include <set>

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

    class GG_CharOperation : lem::NonCopyable
    {
    private:
        int id;
        lem::UCString name;

        std::map< lem::uint32_t, lem::uint32_t > items;
        std::set< lem::uint32_t > result_items; // для проверки вхождения символа в результирующий набор символов

    public:
        GG_CharOperation(void);
        GG_CharOperation(int Id, const lem::UCString &Name, const std::map< lem::uint32_t, lem::uint32_t > &Items);

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, Solarix::Dictionary &dict);
#endif

        const lem::UCString& GetName(void) const { return name; }
        int GetId(void) const { return id; }

        lem::uint32_t Apply(lem::uint32_t src) const;

        const std::map< lem::uint32_t, lem::uint32_t >& Items(void) const { return items; }

        bool IsSourceSymbol(lem::uint32_t c) const { return items.find(c) != items.end(); }
        bool IsResultSymbol(lem::uint32_t c) const { return result_items.find(c) != result_items.end(); }
    };
}

#endif
