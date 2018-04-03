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
        MySQLCnx * CreateCnx();

    public:
        StorageConnection_MySQL(
            const lem::FString &_login,
            const lem::FString &_psw,
            const lem::FString &_db,
            const lem::FString &_host,
            int _port,
            int pool_size
        );

        virtual ~StorageConnection_MySQL();

        virtual bool IsConnected() const override;

        virtual void Escape(lem::UFString &str) override;

        virtual TransactionGuard* GetTx() override;
        virtual TransactionGuard* GetReadTx() override;

        virtual void BeginTx() override;
        virtual void CommitTx() override;
        virtual void RollbackTx() override;

        virtual void BeginReadTx() override;
        virtual void EndReadTx() override;

        virtual void Error(const lem::FString &sql);
        virtual void Error() override;
        virtual void Execute(const lem::FString &sql);
        virtual int GetLastId() override;

        virtual LS_ResultSet* Select(const lem::FString &sql) override;
        virtual int SelectInt(const lem::FString &sql, int default_value) override;

        virtual bool DoesIndexExist(const lem::FString &index_name, const lem::FString &table_name) override;
        virtual bool DoesTableExist(const lem::FString &table_name) override;

        virtual void Ping() override;

        // Выделение коннекта из доступных в пуле
        MySQLCnx * GetDb();
    };
}

#endif
