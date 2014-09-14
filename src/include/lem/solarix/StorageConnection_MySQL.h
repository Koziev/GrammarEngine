#if !defined StorageConnection_MySQL__H && defined SOL_MYSQL_DICTIONARY_STORAGE
 #define StorageConnection_MySQL__H

 #include <lem/config.h>
 
 #if defined LEM_WINDOWS
  #include <windows.h>
 #endif

 #include <lem/mysql/mysql.h>
 #include <lem/process.h>
 #include <lem/containers.h>
 #include <lem/fstring.h>
 #include <lem/solarix/StorageConnection.h>

 namespace lem
 {
  class FString;
 }

 namespace Solarix
 {
  struct MySQLCnx;
  

  class StorageConnection_MySQL : public StorageConnection
  {
   private:
    lem::FString login;
    lem::FString psw;
    lem::FString schema;
    lem::FString host;
    int port;

    int pool_size;

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_pool;
    #endif
    lem::MCollect<MySQLCnx*> cnx_list;

    // для внутренних целей - создание нового коннекта для сохранения в пуле,
    // без синхронизации на крит. секции.
    MySQLCnx * CreateCnx(void);

   public:
    StorageConnection_MySQL(
                            const lem::FString &_login,
                            const lem::FString &_psw,
                            const lem::FString &_db,
                            const lem::FString &_host,
                            int _port,
                            int pool_size
                           );

    virtual ~StorageConnection_MySQL(void);

    virtual bool IsConnected(void) const;

    virtual void Escape( lem::UFString &str );

    virtual TransactionGuard* GetTx(void);
    virtual TransactionGuard* GetReadTx(void);

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

    virtual void Ping(void);

    // Выделение коннекта из доступных в пуле
    MySQLCnx * GetDb(void);
  };
 }

#endif
