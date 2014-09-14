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

    virtual ~StorageConnection_SQLITE(void);

    virtual void Escape( lem::UFString &str );

    virtual TransactionGuard* GetTx(void);
    virtual TransactionGuard* GetReadTx(void);

    virtual bool IsConnected(void) const;

    virtual void BeginTx(void);
    virtual void CommitTx(void);
    virtual void RollbackTx(void);

    virtual void BeginReadTx(void);
    virtual void EndReadTx(void);

    virtual void Error( const lem::FString &sql );
    virtual void Error(void);
    virtual void Execute( const lem::FString &sql );
    virtual int GetLastId(void);

    virtual LS_ResultSet* Select( const lem::FString &sql );
    virtual int SelectInt( const lem::FString &sql, int default_value );

    virtual bool DoesIndexExist( const lem::FString &index_name, const lem::FString &table_name );
    virtual bool DoesTableExist( const lem::FString &table_name );
  };
 }

#endif
