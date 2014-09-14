#if !defined TransactionGuard_SQLITE__H
 #define TransactionGuard_SQLITE__H

 #include <lem/solarix/TransactionGuard.h>

 namespace Solarix
 {
  class TransactionGuard_SQLITE : public TransactionGuard
  {
   private:
    bool started;
    bool committed;
    struct sqlite3* hdb;

   public:
    TransactionGuard_SQLITE( struct sqlite3* _hdb );
    virtual ~TransactionGuard_SQLITE(void);
    virtual void Begin(void);
    virtual void Commit(void);
  };

  class ReadTransactionGuard_SQLITE : public TransactionGuard
  {
   private:
    bool committed;
    struct sqlite3* hdb;

   public:
    ReadTransactionGuard_SQLITE( struct sqlite3* _hdb );
    virtual ~ReadTransactionGuard_SQLITE(void);
    virtual void Begin(void);
    virtual void Commit(void);
  };
 }

#endif
