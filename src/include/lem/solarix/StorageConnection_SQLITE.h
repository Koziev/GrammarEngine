#if !defined StorageConnection_SQLITE__H
 #define StorageConnection_SQLITE__H

 #include <lem/path.h>
 #include <lem/sqlite.h>
 #include <lem/solarix/StorageConnection.h>

 namespace Solarix
 {
  class LS_ResultSet;
  class StorageConnection_SQLITE : public StorageConnection
  {
   private:
    lem::UFString sqlite_connection_string;
    struct sqlite3* hdb;

   public:
    StorageConnection_SQLITE( const lem::UFString &connection_string );

    virtual ~StorageConnection_SQLITE();

    virtual void Escape( lem::UFString &str ) override;

    virtual TransactionGuard* GetTx() override;
    virtual TransactionGuard* GetReadTx() override;

    virtual bool IsConnected() const override;

    virtual void BeginTx() override;
    virtual void CommitTx() override;
    virtual void RollbackTx() override;

    virtual void BeginReadTx() override;
    virtual void EndReadTx() override;

    virtual void Error( const lem::FString &sql ) override;
    virtual void Error() override;
    virtual void Execute( const lem::FString &sql ) override;
    virtual int GetLastId() override;

    virtual LS_ResultSet* Select( const lem::FString &sql ) override;
    virtual int SelectInt( const lem::FString &sql, int default_value ) override;

    virtual bool DoesIndexExist( const lem::FString &index_name, const lem::FString &table_name ) override;
    virtual bool DoesTableExist( const lem::FString &table_name ) override;
  };
 }

#endif
