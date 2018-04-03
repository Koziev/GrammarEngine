#if !defined SOL_ALPHABET__H
#define SOL_ALPHABET__H

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
    class Dictionary;

    class Alphabet
    {
    private:
        int id;        // Unique alphabet id
        lem::UCString name; // alphabet name (Russian, Latin, etc)

    public:
        Alphabet();
        Alphabet(int Id, const lem::UCString &Name);

        inline const lem::UCString& get_Name(void) const { return name; }
        inline int get_Id() const { return id; }

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict);
#endif
    };

}

#endif
