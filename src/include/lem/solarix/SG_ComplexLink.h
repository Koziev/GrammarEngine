#if !defined SG_ComplexLink__H
#define SG_ComplexLink__H

#include <lem/ufstring.h>
#include <lem/solarix/tree_link.h>
#include <lem/solarix/SG_TagsList.h>

namespace lem
{
    namespace Iridium
    {
        class Macro_Parser;
    }
}

namespace Solarix
{
    class SynGram;

    class SG_ComplexLink
    {
    public:
        int tl_id; // PK в таблице sg_tlink
        Tree_Link link; // тип связи
        lem::UFString entry1; // какая статья 
        lem::UFString entry2; // с какой составной статьей связана
        SG_TagsList tags;

    private:
#if defined SOL_LOADTXT && defined SOL_COMPILER
        static void LoadPoint(lem::Iridium::Macro_Parser &txtfile, SynGram &gram, lem::UFString &entry);
#endif

    public:
        SG_ComplexLink();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, SynGram &gram);
#endif

        // Оператор сравнения применяется для сортировки списка связок
        bool operator<(const SG_ComplexLink &x) const;

        inline bool operator==(const SG_ComplexLink &x) const
        {
            return entry1 == x.entry1 &&
                link == x.link &&
                entry2 == x.entry2 &&
                tags == x.tags;
        }

        inline Tree_Link GetLink() const { return link; }
        inline const lem::UFString& GetEntry1() const { return entry1; }
        inline const lem::UFString& GetEntry2() const { return entry2; }
        inline SG_TagsList GetTags() const { return tags; }
    };


}
#endif
