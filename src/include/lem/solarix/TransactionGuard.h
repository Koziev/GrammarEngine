#if !defined TransactionGuard__H
#define TransactionGuard__H

namespace Solarix
{
    class TransactionGuard
    {
    public:
        TransactionGuard() {}
        virtual ~TransactionGuard() {}
        virtual void Begin() = 0;
        virtual void Commit() = 0;
    };
}

#endif
