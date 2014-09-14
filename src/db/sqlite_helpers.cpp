#include <lem/unicode.h>
#include <lem/oformatter.h>
#include <lem/conversions.h>
#include <lem/sqlite_helpers.h>

using namespace lem;

SqliteTxGuard::SqliteTxGuard(struct sqlite3* _hdb )
: hdb(_hdb), committed(false)
{
}

SqliteTxGuard::~SqliteTxGuard(void)
{
 if( !committed )
  sqlite_rollback_tx(hdb);
}

void SqliteTxGuard::Commit(void)
{
 sqlite_commit_tx(hdb);
 committed=true;
 return;
}


lem::Path lem::sqlite_get_absolute_filepath( const lem::UFString & connection_string )
{
 lem::Path sqlite_file;

 if( connection_string.eq_begi(L"path=") || connection_string.eq_begi(L"file=") )
  {
   lem::UFString db_path, db_file, basedir;

   lem::Collect<UFString> params;
   lem::parse( connection_string, params, L";" );
   for( lem::Container::size_type i=0; i<params.size(); ++i )
    {
     const lem::UFString & param = params[i];
     if( param.eq_begi(L"path=") )
      db_path = param.c_str()+5;
     else if( param.eq_begi(L"file=") )
      db_file = param.c_str()+5;
    }

   if( !db_path.empty() )
    sqlite_file = lem::Path(db_path);
   else
    {
     sqlite_file = lem::Path(basedir);
     sqlite_file.ConcateLeaf(db_file);
    }
  }
 else
  {
   sqlite_file = lem::Path(connection_string);
  }

 return sqlite_file;
}


struct sqlite3* lem::sqlite_open_serialized( const lem::UFString & connection_string )
{
 struct sqlite3 *hdb=NULL;

 bool read_only=false;
 lem::Path sqlite_file;

 if( connection_string.eq_begi(L"path=") || connection_string.eq_begi(L"file=") )
  {
   lem::UFString db_path, db_file, basedir;

   lem::Collect<UFString> params;
   lem::parse( connection_string, params, L";" );
   for( lem::Container::size_type i=0; i<params.size(); ++i )
    {
     const lem::UFString & param = params[i];
     if( param.eq_begi(L"path=") )
      db_path = param.c_str()+5;
     else if( param.eq_begi(L"file=") )
      db_file = param.c_str()+5;
     else if( param.eq_begi(L"basedir=") )
      basedir = param.c_str()+8;
     else if( param.eqi(L"mode=readonly") )
      {
       read_only=true;
      }
     else
      {
       lem::MemFormatter mem;
       mem.printf( "Unknown parameter %us in connection string %us", param.c_str(), connection_string.c_str() );
       throw lem::E_BaseException(mem.string());
      }
    }

   if( !db_path.empty() )
    sqlite_file = lem::Path(db_path);
   else
    {
     sqlite_file = lem::Path(basedir);
     sqlite_file.ConcateLeaf(db_file);
    }
  }
 else
  {
   // Connection string is a DB file name.
   sqlite_file = lem::Path(connection_string);
  }


 #if SQLITE_VERSION_NUMBER<3006018
  #if defined LEM_WINDOWS
  int res = sqlite3_open16( sqlite_file.GetUnicode().c_str(), &hdb );
  #else
  int res = sqlite3_open( to_utf8(sqlite_file.GetUnicode()).c_str(), &hdb );
  #endif
 #else
  int flags = SQLITE_OPEN_FULLMUTEX;
  if( read_only )
   {
    flags = flags | SQLITE_OPEN_READONLY;
   }
  else
   {
    flags = flags | SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
   }

  int res = sqlite3_open_v2( to_utf8(sqlite_file.GetUnicode()).c_str(), &hdb, flags, NULL );
 #endif

 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "Can not open SQLite database file '%us', error=%d message=%us"
               , sqlite_file.GetUnicode().c_str(), res, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException( msg.string() );
  }

 return hdb;
}




void lem::sqlite_begin_tx( struct sqlite3* hdb )
{
 int res = sqlite3_exec( hdb, "BEGIN", NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error %d: can not begin transaction, message=%us", res, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException( msg.string() );
  }

 return;
}

void lem::sqlite_commit_tx( struct sqlite3* hdb )
{
 int res = sqlite3_exec( hdb, "COMMIT", NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error %d: can not commit transaction, message=%us", res, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException( msg.string() );
  }

 return;
}

void lem::sqlite_rollback_tx( struct sqlite3* hdb )
{
 int res = sqlite3_exec( hdb, "ROLLBACK", NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error %d: can not rollback transaction, message=%us", res, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException( msg.string() );
  }

 return;
}

lem::UFString lem::sqlite_column_ufstring( sqlite3_stmt *stmt, int icol )
{
 #if LEM_WCHAR_T==2
 const wchar_t *s = (const wchar_t*)sqlite3_column_text16(stmt,icol);
 return lem::UFString(s);
 #elif LEM_WCHAR_T==4
 const char *s = (const char*)sqlite3_column_text(stmt,icol);
 return lem::from_utf8(s);
 #else
  #error Unsupported wchar_t size!
 #endif
}


lem::FString lem::sqlite_column_fstring( sqlite3_stmt *stmt, int icol )
{
 const char *s = (const char*)sqlite3_column_text(stmt,icol);
 return lem::FString(s);
}


lem::UCString lem::sqlite_column_ucstring( sqlite3_stmt *stmt, int icol )
{
 #if LEM_WCHAR_T==2
 const wchar_t *s = (const wchar_t*)sqlite3_column_text16(stmt,icol);
 return lem::UCString(s);
 #elif LEM_WCHAR_T==4
 const char *s = (const char*)sqlite3_column_text(stmt,icol);
 return UCString(lem::from_utf8(s).c_str());
 #else
  #error Unsupported wchar_t size!
 #endif
}


lem::UFString lem::sqlite_errmsg( struct sqlite3* hdb )
{
 #if LEM_WCHAR_T==2
 const wchar_t *s = (const wchar_t*)sqlite3_errmsg16(hdb);
 return lem::UFString(s);
 #elif LEM_WCHAR_T==4
 const char *s = (const char*)sqlite3_errmsg(hdb);
 return lem::from_utf8(s);
 #else
  #error Unsupported wchar_t size!
 #endif
}
  
int lem::sqlite_select_int( struct sqlite3* hdb, const char *Select )
{
 return sqlite_select_int(hdb,lem::FString(Select));
}



int lem::sqlite_select_int( struct sqlite3* hdb, const lem::FString & Select )
{
 LEM_CHECKIT_Z( hdb!=NULL );
 LEM_CHECKIT_Z( !Select.empty() );

 int retval=-1;

 sqlite3_stmt *stmt=NULL;
 const char *dummy;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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
   msg.printf( "SQLite error: can not execute query %s, message=%us", Select.c_str(), lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException( msg.string() );
  }

 return retval;
}

bool lem::sqlite_does_table_exist( struct sqlite3* hdb, const char *TableName )
{ 
 lem::FString exists( lem::format_str( "SELECT * FROM sqlite_master WHERE type='table' AND name='%s'", TableName ) );

 bool existable=false;

 sqlite3_stmt *stmt=NULL;
 const char *dummy;
 int res = sqlite3_prepare_v2( hdb, exists.c_str(), exists.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   res = sqlite3_step( stmt );
   if( res == SQLITE_ROW )
    {
     existable=true;
    }

   sqlite3_finalize(stmt);
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error: can not execute query %s, message=%us", exists.c_str(), lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException( msg.string() );
  }

 return existable;
}



bool lem::sqlite_does_index_exist( struct sqlite3* hdb, const char *IndexName )
{ 
 lem::FString exists( lem::format_str( "SELECT * FROM sqlite_master WHERE type='index' AND name='%s'", IndexName ) );

 bool existable=false;

 sqlite3_stmt *stmt=NULL;
 const char *dummy;
 int res = sqlite3_prepare_v2( hdb, exists.c_str(), exists.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   res = sqlite3_step( stmt );
   if( res == SQLITE_ROW )
    {
     existable=true;
    }

   sqlite3_finalize(stmt);
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error: can not execute query %s, message=%us", exists.c_str(), lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException( msg.string() );
  }

 return existable;
}


void lem::sqlite_escape( lem::UFString &str )
{ 
 str.subst_all( L"'", L"''" );
 return;
}

void lem::sqlite_escape( lem::FString &str )
{ 
 str.subst_all( "'", "''" );
 return;
}

void lem::sqlite_vacuum( struct sqlite3* hdb )
{
 int res = sqlite3_exec( hdb, "VACUUM", NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error %d: can not execute VACUUM, message=%us", res, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException( msg.string() );
  }

 return;
}


void lem::sqlite_execute( struct sqlite3* hdb, const char *sql )
{
 int res = sqlite3_exec( hdb, sql, NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error=%us", lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }
}


bool lem::sqlite_init_serialized_mode()
{
/*
// #if defined LEM_WINDOWS
 int rc1 = sqlite3_config(SQLITE_CONFIG_SERIALIZED);
 if( rc1!=SQLITE_OK )
  return false;

 int rc2 = sqlite3_initialize();
 if( rc2!=SQLITE_OK )
  return false;
// #endif */

 return true;
}

