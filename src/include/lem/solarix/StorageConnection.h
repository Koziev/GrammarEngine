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
        StorageConnection() :ref_count(0) {}
        virtual ~StorageConnection() {}

        virtual TransactionGuard* GetTx() = 0;
        virtual TransactionGuard* GetReadTx() = 0;

        void AddRef() { ref_count++; }
        int Release() { return ref_count > 0 ? --ref_count : 0; }

        void Disconnect() { Release(); }

        virtual void Ping() {}

        virtual bool IsConnected() const = 0;

        virtual void Escape(lem::UFString &str) = 0;

        virtual void BeginTx() = 0;
        virtual void CommitTx() = 0;
        virtual void RollbackTx() = 0;

        virtual void BeginReadTx() = 0;
        virtual void EndReadTx() = 0;

        virtual void Error(const lem::FString &sql) = 0;
        virtual void Error() = 0;
        virtual void Execute(const lem::FString &sql) = 0;
        virtual int GetLastId() = 0;

        virtual LS_ResultSet* Select(const lem::FString &sql) = 0;
        virtual int SelectInt(const lem::FString &sql, int default_value) = 0;

        virtual bool DoesIndexExist(const lem::FString &index_name, const lem::FString &table_name) = 0;
        virtual bool DoesTableExist(const lem::FString &table_name) = 0;
    };
}

#endif
