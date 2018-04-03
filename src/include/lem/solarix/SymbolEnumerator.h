#if !defined SYMBOL_ENUMERATOR__H
#define SYMBOL_ENUMERATOR__H

#include <lem/noncopyable.h>

namespace Solarix
{
    class GG_Entry;
    class Symbols;
    class LS_ResultSet;

    class SymbolEnumerator : lem::NonCopyable
    {
    private:
        LS_ResultSet *rs;
        Symbols *symbols;

    public:
        SymbolEnumerator(Symbols *_symbols, LS_ResultSet *_ts);
        virtual ~SymbolEnumerator();

        virtual bool Fetch();
        virtual int GetId();
        virtual const GG_Entry& GetItem();
    };
}
#endif
