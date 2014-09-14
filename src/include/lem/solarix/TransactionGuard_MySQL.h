#if !defined TransactionGuard_MySQL__H
 #define TransactionGuard_MySQL__H

 #include <lem/solarix/TransactionGuard.h>

 namespace Solarix
 {
  class StorageConnection_MySQL;
  class TransactionGuard_MySQL : public TransactionGuard
  {
   private:
    bool started;
    bool committed;
    StorageConnection_MySQL *cnx;

   public:
    TransactionGuard_MySQL( StorageConnection_MySQL *_cnx );
    virtual ~TransactionGuard_MySQL(void);
    virtual void Begin(void);
    virtual void Commit(void);
  };

  class ReadTransactionGuard_MySQL : public TransactionGuard
  {
   private:
    bool committed;
    StorageConnection_MySQL *cnx;

   public:
    ReadTransactionGuard_MySQL( StorageConnection_MySQL *_cnx );
    virtual ~ReadTransactionGuard_MySQL(void);
    virtual void Begin(void);
    virtual void Commit(void);
  };

 }

#endif
