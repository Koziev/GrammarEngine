#if !defined StorageConnection__H
 #define StorageConnection__H

 #include <lem/process.h>

 namespace Solarix
 {
  class TransactionGuard;
  class LS_ResultSet;
  class StorageConnection
  {
   private:
    lem::Process::InterlockedInt ref_count;

   public:
    StorageConnection(void):ref_count(0) {}
    virtual ~StorageConnection(void) {}

    virtual TransactionGuard* GetTx(void)=0;
    virtual TransactionGuard* GetReadTx(void)=0;

    void AddRef(void) { ref_count++; }
    int Release(void) { return ref_count>0 ? --ref_count : 0; }

    void Disconnect(void) { Release(); }

    virtual void Ping(void) {}

    virtual bool IsConnected(void) const=0;

    virtual void Escape( lem::UFString &str )=0;

    virtual void BeginTx(void)=0;
    virtual void CommitTx(void)=0;
    virtual void RollbackTx(void)=0;

    virtual void BeginReadTx(void)=0;
    virtual void EndReadTx(void)=0;

    virtual void Error( const lem::FString &sql )=0;
    virtual void Error(void)=0;
    virtual void Execute( const lem::FString &sql )=0;
    virtual int GetLastId(void)=0;

    virtual LS_ResultSet* Select( const lem::FString &sql )=0;
    virtual int SelectInt( const lem::FString &sql, int default_value )=0;

    virtual bool DoesIndexExist( const lem::FString &index_name, const lem::FString &table_name )=0;
    virtual bool DoesTableExist( const lem::FString &table_name )=0;
  };
 }

#endif
