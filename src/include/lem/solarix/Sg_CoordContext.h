#if !defined SG_CoordContext__H
#define SG_CoordContext__H

#include <lem/solarix/coord_pair.h>

namespace lem
{
    class OFormatter;

    namespace Iridium
    {
        class Macro_Parser;
    }
}

namespace Solarix
{
    class SynGram;

    struct SG_CoordContext
    {
        int iclass;
        Solarix::CP_Array coords;

        SG_CoordContext();
        SG_CoordContext(int iClass, const Solarix::CP_Array & Coords);
        SG_CoordContext(const SG_CoordContext &x);

        void operator=(const SG_CoordContext &x);

        inline int size() const { return CastSizeToInt(coords.size()); }

        void SaveTxt(lem::OFormatter &txt, Solarix::SynGram &sg) const;

#if defined SOL_LOADTXT
        void LoadTxt(lem::Iridium::Macro_Parser &txtfile, const Solarix::SynGram &sg);
#endif
    };
}
#endif
