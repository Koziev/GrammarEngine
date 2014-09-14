#include <lem/sqlite_helpers.h>
#include <lem/oformatter.h>
#include <lem/unicode.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>
#include <lem/solarix/TransactionGuard_SQLITE.h>
#include <lem/solarix/StorageConnection_SQLITE.h> 

using namespace Solarix;

StorageConnection_SQLITE::StorageConnection_SQLITE( const lem::UFString &connection_string )
 : sqlite_connection_string(connection_string)
{
 hdb = lem::sqlite_open_serialized(connection_string);
 return;
}


StorageConnection_SQLITE::~StorageConnection_SQLITE(void)
{
 if( hdb!=NULL )
  {
   sqlite3_close(hdb);
   hdb=NULL;
  }

 return;
}


TransactionGuard* StorageConnection_SQLITE::GetTx(void)
{
 return new TransactionGuard_SQLITE(hdb);
}

TransactionGuard* StorageConnection_SQLITE::GetReadTx(void)
{
 return new ReadTransactionGuard_SQLITE(hdb);
}


void StorageConnection_SQLITE::BeginTx(void)
{
 lem::sqlite_begin_tx(hdb);
}


void StorageConnection_SQLITE::CommitTx(void)
{
 lem::sqlite_commit_tx(hdb);
 return;
}


void StorageConnection_SQLITE::RollbackTx(void)
{
 lem::sqlite_rollback_tx(hdb);
 return;
}


void StorageConnection_SQLITE::BeginReadTx(void)
{
 lem::sqlite_begin_tx(hdb);
}


void StorageConnection_SQLITE::EndReadTx(void)
{
 lem::sqlite_commit_tx(hdb);
 return;
}




void StorageConnection_SQLITE::Error( const lem::FString &sql )
{
 lem::MemFormatter mem;
 mem.printf( "Error in SQLite, sql=%s, error=%us", sql.c_str(), lem::sqlite_errmsg(hdb).c_str() );
 throw lem::E_BaseException(mem.string());
}


void StorageConnection_SQLITE::Error(void)
{
 lem::MemFormatter mem;
 mem.printf( "Error in MySQL, message=%us", lem::sqlite_errmsg(hdb).c_str() );
 throw lem::E_BaseException(mem.string());
}


void StorageConnection_SQLITE::Execute( const lem::FString &sql )
{
 int res = sqlite3_exec( hdb, sql.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw lem::E_BaseException(msg.string());
  }

 return;
}


int StorageConnection_SQLITE::GetLastId(void)
{
 return (int)sqlite3_last_insert_rowid(hdb);
}

bool StorageConnection_SQLITE::IsConnected(void) const
{
 return hdb!=NULL;
}


bool StorageConnection_SQLITE::DoesIndexExist( const lem::FString &index_name, const lem::FString &table_name )
{
 return lem::sqlite_does_index_exist( hdb, index_name.c_str() );
}


bool StorageConnection_SQLITE::DoesTableExist( const lem::FString &table_name )
{
 return lem::sqlite_does_table_exist( hdb, table_name.c_str() );
}


LS_ResultSet* StorageConnection_SQLITE::Select( const lem::FString &sql )
{
 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, sql.c_str(), sql.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   return new LS_ResultSet_SQLITE(stmt);
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw lem::E_BaseException(msg.string());
  }
}


int StorageConnection_SQLITE::SelectInt( const lem::FString &sql, int default_value )
{
 int retval=default_value;

 sqlite3_stmt *stmt=NULL;
 const char *dummy;
 int res = sqlite3_prepare_v2( hdb, sql.c_str(), sql.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   res = sqlite3_step( stmt );
   if( res == SQLITE_ROW )
    {
     try
      {
       retval = sqlite3_column_int(stmt,0);
      }
     catch(...)
      {
      }
    }

   sqlite3_finalize(stmt);
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error: can not execute query %s, message=%us", sql.c_str(), lem::sqlite_errmsg(hdb).c_str() );
   throw lem::E_BaseException( msg.string() );
  }

 return retval;
}


void StorageConnection_SQLITE::Escape( lem::UFString &str )
{
 lem::sqlite_escape(str);
 return;
}
