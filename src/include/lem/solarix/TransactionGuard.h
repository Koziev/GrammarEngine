#if !defined TransactionGuard__H
 #define TransactionGuard__H

 namespace Solarix
 {
  class TransactionGuard
  {
   public:
    TransactionGuard(void) {}
    virtual ~TransactionGuard(void) {}
    virtual void Begin(void)=0;
    virtual void Commit(void)=0;
  };
 }

#endif
