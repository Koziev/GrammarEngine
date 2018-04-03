#if !defined CharOperationEnumerator__H
#define CharOperationEnumerator__H

#include <lem/noncopyable.h>

namespace Solarix
{
    class LS_ResultSet;
    class GG_CharOperations;
    class GG_CharOperation;

    class CharOperationEnumerator : lem::NonCopyable
    {
    private:
        LS_ResultSet *rs;
        GG_CharOperations *operations;

    public:
        CharOperationEnumerator(LS_ResultSet *RS, GG_CharOperations *OPERS);
        ~CharOperationEnumerator();

        bool Fetch(void);
        const GG_CharOperation & GetOperation();
    };
}

#endif
