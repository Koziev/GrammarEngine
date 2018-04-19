#include <lem/sqlite_helpers.h>
#include <lem/solarix/TransactionGuard_SQLITE.h>

using namespace Solarix;

TransactionGuard_SQLITE::TransactionGuard_SQLITE(struct sqlite3* _hdb)
    : hdb(_hdb), committed(false), started(false)
{
}

TransactionGuard_SQLITE::~TransactionGuard_SQLITE()
{
    if (!committed && started)
    {
        lem::sqlite_rollback_tx(hdb);
        started = false;
    }
}

void TransactionGuard_SQLITE::Begin()
{
    if (!started)
    {
        committed = false;
        lem::sqlite_begin_tx(hdb);
        started = true;
    }
}


void TransactionGuard_SQLITE::Commit()
{
    if (started)
    {
        lem::sqlite_commit_tx(hdb);
        committed = true;
        started = false;
    }

    return;
}


ReadTransactionGuard_SQLITE::ReadTransactionGuard_SQLITE(struct sqlite3* _hdb)
    : hdb(_hdb), committed(false)
{
    lem::sqlite_begin_tx(hdb);
    return;
}

ReadTransactionGuard_SQLITE::~ReadTransactionGuard_SQLITE()
{
    if (!committed)
    {
        lem::sqlite_commit_tx(hdb);
        committed = true;
    }
}


void ReadTransactionGuard_SQLITE::Begin()
{
}


void ReadTransactionGuard_SQLITE::Commit()
{
    if (!committed)
    {
        lem::sqlite_commit_tx(hdb);
        committed = true;
    }

    return;
}
