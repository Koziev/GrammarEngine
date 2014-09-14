#include <lem/sqlite_helpers.h>
#include <lem/solarix/TransactionGuard_SQLITE.h>

using namespace Solarix;

TransactionGuard_SQLITE::TransactionGuard_SQLITE( struct sqlite3* _hdb )
: hdb(_hdb), committed(false), started(false)
{
}

TransactionGuard_SQLITE::~TransactionGuard_SQLITE(void)
{
 if( !committed && started )
  {
   lem::sqlite_rollback_tx(hdb);
   started=false;
  }
}

void TransactionGuard_SQLITE::Begin(void)
{
 if( !started )
  {
   committed=false;
   lem::sqlite_begin_tx(hdb);
   started=true;
  }
}


void TransactionGuard_SQLITE::Commit(void)
{
 if( started )
  {
   lem::sqlite_commit_tx(hdb);
   committed=true;
   started=false;
  }

 return;
}


ReadTransactionGuard_SQLITE::ReadTransactionGuard_SQLITE( struct sqlite3* _hdb )
: hdb(_hdb), committed(false)
{
 lem::sqlite_begin_tx(hdb);
 return;
}

ReadTransactionGuard_SQLITE::~ReadTransactionGuard_SQLITE(void)
{
 if( !committed )
  {
   lem::sqlite_commit_tx(hdb);
   committed=true;
  }
}


void ReadTransactionGuard_SQLITE::Begin(void)
{
}


void ReadTransactionGuard_SQLITE::Commit(void)
{
 if( !committed )
  {
   lem::sqlite_commit_tx(hdb);
   committed=true;
  }

 return;
}
