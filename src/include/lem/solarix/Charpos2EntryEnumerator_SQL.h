#if !defined Charpos2EntryEnumerator_SQL__H
#define Charpos2EntryEnumerator_SQL__H

#include <lem/solarix/Charpos2EntryEnumerator.h>

namespace Solarix
{
    class Charpos2EntryEnumerator_SQL : public Charpos2EntryEnumerator
    {
    private:
        LS_ResultSet *rs;

    public:
        Charpos2EntryEnumerator_SQL(LS_ResultSet * _rs);

        virtual ~Charpos2EntryEnumerator_SQL();

        virtual bool Fetch();
        virtual lem::uint32_t GetChar();
        virtual int GetPos();
    };
}

#endif
