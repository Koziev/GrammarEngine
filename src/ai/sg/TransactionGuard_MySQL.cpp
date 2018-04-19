#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/solarix/StorageConnection_MySQL.h> 
#include <lem/solarix/MySQLCnx.h>
#include <lem/solarix/TransactionGuard_MySQL.h>

using namespace Solarix;

TransactionGuard_MySQL::TransactionGuard_MySQL(StorageConnection_MySQL *_cnx)
    : cnx(_cnx), committed(false), started(false)
{
}

TransactionGuard_MySQL::~TransactionGuard_MySQL()
{
    if (!committed && started)
    {
        cnx->RollbackTx();
        started = false;
    }
}

void TransactionGuard_MySQL::Begin()
{
    if (!started)
    {
        committed = false;
        cnx->BeginTx();
        started = true;
    }
}


void TransactionGuard_MySQL::Commit()
{
    if (started)
    {
        cnx->CommitTx();
        committed = true;
        started = false;
    }

    return;
}



ReadTransactionGuard_MySQL::ReadTransactionGuard_MySQL(StorageConnection_MySQL *_cnx)
    : cnx(_cnx), committed(false)
{
    MySQLCnx *c = _cnx->GetDb();

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    if (c->InTransaction())
        committed = true;
    else
        cnx->BeginReadTx();

    return;
}

ReadTransactionGuard_MySQL::~ReadTransactionGuard_MySQL()
{
    if (!committed)
    {
        cnx->EndReadTx();
        committed = true;
    }
}

void ReadTransactionGuard_MySQL::Begin()
{
}


void ReadTransactionGuard_MySQL::Commit()
{
    if (!committed)
    {
        cnx->EndReadTx();
        committed = true;
    }

    return;
}


#endif
