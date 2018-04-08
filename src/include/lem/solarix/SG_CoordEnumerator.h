#if !defined SG_CoordEnumerator__H
#define SG_CoordEnumerator__H

#include <lem/solarix/CoordEnumerator.h>

namespace Solarix
{
    class SG_Coordinates;
    class LS_ResultSet;
    class LexiconStorage;

    class SG_CoordEnumerator : public CoordEnumerator
    {
    private:
        LS_ResultSet *rs;
        LexiconStorage *db;
        SG_Coordinates *p;

    public:
        SG_CoordEnumerator(LexiconStorage *_db, SG_Coordinates * _p);
        virtual ~SG_CoordEnumerator();

        virtual bool Fetch() override;
        virtual int GetId() override;
        virtual const GramCoord& GetItem() override;
    };
}

#endif
