#if defined SOL_FIREBIRD_NGRAMS && !defined(SOL_NO_NGRAMS)

#include <lem/console_streams.h>
#include <lem/unicode.h>

#if defined SOL_MYSQL_NGRAMS
#include <lem/solarix/StorageConnection_MySQL.h> 
#endif


#include <lem/solarix/ngrams_dbms.h>

using namespace std;
using namespace lem;
using namespace Solarix;

#if defined SOL_FIREBIRD_NGRAMS

 #if defined(LEM_MSC) && _MSC_VER>=1300
  #pragma comment ( lib, "fbclient_ms.lib" )
 #endif

#else

 #if defined(LEM_MSC) && _MSC_VER>=1300 && defined(LEM_WINDOWS)
  #if LEM_DEBUGGING==1
   # pragma comment ( lib, "sqlited.lib" )
  #else
   # pragma comment ( lib, "sqlite.lib" )
  #endif
 #endif

#endif

#if defined SOL_FIREBIRD_NGRAMS
static char isc_tpb[5] = { isc_tpb_version1, isc_tpb_write, isc_tpb_read_committed, isc_tpb_nowait,
                           isc_tpb_rec_version };

static char isc_tpb_rd[5] = { isc_tpb_version1, isc_tpb_read, isc_tpb_read_committed, isc_tpb_nowait,
                           isc_tpb_rec_version };
#endif






NGramsDBMS::NGramsDBMS(void)
{
 hdb=NULL;
 htx=NULL;
 return;
}


NGramsDBMS::~NGramsDBMS(void)
{
 Disconnect();
 return;
}

bool NGramsDBMS::IsRemote(void) const
{
 return true;
}

bool NGramsDBMS::Connected(void) const
{
 return hdb!=NULL;
}


void NGramsDBMS::Connect( const lem::Path &dbfile )
{
 #if defined SOL_FIREBIRD_NGRAMS

  LEM_CHECKIT_Z( hdb==NULL );

  bool created=false;
  if( !dbfile.DoesExist() )
   {
    if( isc_dsql_execute_immediate(status, &hdb, &htx, 0,
     lem::format_str( "CREATE DATABASE '%s' USER 'SYSDBA' PASSWORD 'MASTERKEY' DEFAULT CHARACTER SET UTF8", dbfile.GetAscii().c_str() ).c_str(), 3, 0L
     ) )
    {
     #if LEM_DEBUGGING==1
     isc_print_status(status);
     #endif
     throw E_BaseException( lem::format_str( L"FireBird error: can not create database [%s]", dbfile.GetUnicode().c_str() ).c_str() );
    }

    hdb=NULL;
    htx=NULL;
    created=true;
   }

  int params_cur=0;

  char login[32]="SYSDBA";
  char psw[32]="MASTERKEY";

//  if( !created )
//   *login=*psw=0;

  char login_len = strlen(login);
  char psw_len = strlen(psw);

  char params[128];
  params[params_cur++] = isc_dpb_version1;
  params[params_cur++] = isc_dpb_user_name;
  params[params_cur++] = login_len;
  memcpy( params+params_cur, login, login_len ); params_cur+=login_len;
  params[ params_cur++ ] = isc_dpb_password;
  params[ params_cur++ ] = psw_len;
  memcpy( params+params_cur, psw, psw_len ); params_cur+=psw_len;
  int count=0;

  if( isc_attach_database(status, 0, dbfile.GetAscii().c_str(), &hdb, params_cur, params ) )
   {
    #if LEM_DEBUGGING==1
    isc_print_status(status);
    #endif
    throw E_BaseException( L"FireBird error: can not connect to database" );
   }

 #elif defined SOL_SQLITE_NGRAMS

  #if defined LEM_WINDOWS
  int res = sqlite3_open16( dbfile.GetUnicode().c_str(), &hdb );
  #else
  int res = sqlite3_open( lem::to_utf8(dbfile.GetUnicode()).c_str(), &hdb );
  #endif

  if( res!=SQLITE_OK )
   {
    UFString msg = lem::format_str( L"Can not open SQLite database file '%s', error=%d message=%s", dbfile.GetUnicode().c_str(), res, sqlite3_errmsg16(hdb) );
    throw E_BaseException( msg.c_str() );
   }

  res = sqlite3_exec( hdb, "PRAGMA temp_store = MEMORY", NULL, NULL, NULL );
  if( res!=SQLITE_OK )
   {
    UFString msg = lem::format_str( L"Can not set PRAGMA TEMP_STORE=MEMORY, error=%d message=%s", res, sqlite3_errmsg16(hdb) );
    throw E_BaseException( msg.c_str() );
   }

 #endif

 return;
}


void NGramsDBMS::Disconnect(void)
{
 LEM_CHECKIT_Z( htx==NULL ); // транзакция должна быть завершена
 if( hdb!=NULL )
  {
   #if defined SOL_FIREBIRD_NGRAMS

   if( htx!=NULL )
    {
     lem::mout->printf( "\n%vfCFireBird error%vn: closing connection - last transaction is still active!\n" );
    }

   if( isc_detach_database( status, &hdb) )
    {
     #if LEM_DEBUGGING==1
     isc_print_status(status);
     #endif
     throw E_BaseException( L"FireBird error: can not detach database" );
    }
  
   #else

   if( hdb!=NULL )
    {
     sqlite3_close(hdb);
    }

   #endif

   hdb = NULL;
  }

 return;
}


void NGramsDBMS::BeginTx(void)
{
 // Откроем транзакцию
 #if defined SOL_SQLITE_NGRAMS
 int res = sqlite3_exec( hdb, "BEGIN;", NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  #if defined LEM_WINDOWS
   throw E_BaseException( lem::format_str( L"SQLite error %d: can not begin transaction, message=%ws", res, sqlite3_errmsg16(hdb) ).c_str() );
  #else
   throw E_BaseException( lem::format_str( L"SQLite error %d: can not begin transaction, message=%S", res, sqlite3_errmsg(hdb) ).c_str() );
  #endif 
 #elif defined SOL_FIREBIRD_NGRAMS
 LEM_CHECKIT_Z( htx==NULL );

 if( htx!=NULL )
  throw E_BaseException( L"FireBird error: can not begin >>>recursive<<< transaction" );

 if( isc_start_transaction(status, &htx, 1, &hdb, 5, isc_tpb ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   throw E_BaseException( L"FireBird error: can not start transaction" );
  }
 #endif

 return;
}


void NGramsDBMS::BeginReadTx(void)
{
 #if defined SOL_SQLITE_NGRAMS
 int res = sqlite3_exec( hdb, "BEGIN;", NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  #if defined LEM_WINDOWS
   throw E_BaseException( lem::format_str( L"SQLite error %d: can not begin transaction, message=%ws", res, sqlite3_errmsg16(hdb) ).c_str() );
  #else
   throw E_BaseException( lem::format_str( L"SQLite error %d: can not begin transaction, message=%S", res, sqlite3_errmsg(hdb) ).c_str() );
  #endif 
 #elif defined SOL_FIREBIRD_NGRAMS
 LEM_CHECKIT_Z( htx==NULL );

 if( htx!=NULL )
  {
   lem::mout->printf( "\n%vfCFireBird error%vn: can not begin >>>recursive<<< transaction!\n" );
   return;
  }

 if( isc_start_transaction(status, &htx, 1, &hdb, 5, isc_tpb_rd ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   throw E_BaseException( L"FireBird error: can not start transaction" );
  }
 #endif

 return;
}




void NGramsDBMS::Commit(void)
{
 #if defined SOL_SQLITE_NGRAMS
 int res = sqlite3_exec( hdb, "COMMIT", NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  throw E_BaseException( lem::format_str( "SQLite error %d: can not commit transaction, message=%s", res, sqlite3_errmsg(hdb) ).c_str() );
 #elif defined SOL_FIREBIRD_NGRAMS
 LEM_CHECKIT_Z( htx!=NULL );
 if( htx==NULL )
  {
   lem::mout->printf( "\n%vfCFireBird error%vn: can not commit >>>NULL<<< transaction!\n" );
   return;
  }

 if( isc_commit_transaction( status, &htx ) )
  {
   isc_print_status(status);
   throw E_BaseException( L"FireBird error: can not commit transaction" );
  }

 htx = NULL;
 #endif
 return;
}


void NGramsDBMS::CommitRetaining(void)
{
 #if defined SOL_SQLITE_NGRAMS
 Commit();
 BeginTx();
 #elif defined SOL_FIREBIRD_NGRAMS
 LEM_CHECKIT_Z( htx!=NULL );
 if( htx==NULL )
  {
   lem::mout->printf( "\n%vfCFireBird error%vn: can not commit >>>NULL<<< transaction!\n" );
   return;
  }

 if( isc_commit_retaining(status, &htx) )
  {
   isc_print_status(status);
   throw E_BaseException( L"FireBird error: can not commit transaction" );
  }

 #endif
 return;
}


// SQLite создает индексы сразу же во время CREATE INDEX ...
// FireBird создает их по COMMIT.
void NGramsDBMS::CommitCreatedIndeces(void)
{
 #if defined SOL_FIREBIRD_NGRAMS
 Commit();
 BeginTx();
 #endif

 return;
}




void NGramsDBMS::ExecuteSql( const char *sql, bool check )
{
 #if defined SOL_SQLITE_NGRAMS
 int res = sqlite3_exec( hdb, sql, NULL, NULL, NULL );
 if( check && res!=SQLITE_OK )
  {
   const wchar_t *errmsg = (const wchar_t*)sqlite3_errmsg16(hdb);
   UFString msg = lem::format_str(L"Can not execute SQLite statement, error=%s", errmsg );
   throw E_BaseException( msg.c_str() );
  }
 #elif defined SOL_FIREBIRD_NGRAMS
 LEM_CHECKIT_Z( htx!=NULL );

 if( htx==NULL )
  throw E_BaseException( lem::format_str(L"Can not execute SQL command, because no transaction is open: %S",sql).c_str() );

 if( isc_dsql_execute_immediate( status, &hdb, &htx, 0, sql, 3, 0L ) )
  {
   if( check )
    {
     #if LEM_DEBUGGING==1
     isc_print_status(status);
     #endif
     throw E_BaseException( lem::format_str(L"Can not execute SQL command: %S",sql).c_str() );
    }
  }
 #endif

 return;
} 



#if defined SOL_SQLITE_NGRAMS

int NGramsDBMS::SelectInt( const lem::FString &Select, int def )
{
 LEM_CHECKIT_Z( !Select.empty() );

 int retval=def;

 sqlite3_stmt *stmt=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), -1, &stmt, NULL );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     retval = sqlite3_column_int(stmt,0);
    } 

   sqlite3_finalize(stmt);
  }

 return retval;
}


int NGramsDBMS::SelectInt( const char *Select, int def )
{
 LEM_CHECKIT_Z( Select!=NULL );

 int retval=def;

 sqlite3_stmt *stmt=NULL;
 int res = sqlite3_prepare_v2( hdb, Select, -1, &stmt, NULL );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     retval = sqlite3_column_int(stmt,0);
    } 

   sqlite3_finalize(stmt);
  }

 return retval;
}


std::pair<int,int> NGramsDBMS::SelectIntPair( const lem::FString & Select )
{
 int retval1=-1;
 int retval2=-1;

 sqlite3_stmt *stmt=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), -1, &stmt, NULL );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     retval1 = sqlite3_column_int(stmt,0);
     retval2 = sqlite3_column_int(stmt,1);
    } 

   sqlite3_finalize(stmt);
  }

 return std::make_pair(retval1,retval2);
}
#endif



#if defined SOL_FIREBIRD_NGRAMS
int NGramsDBMS::SelectInt( const char *sql, int def )
{
 return SelectInt(FString(sql),def);
}


int NGramsDBMS::SelectInt( const lem::FString &sql, int def )
{
 LEM_CHECKIT_Z( !sql.empty() );
 LEM_CHECKIT_Z( htx!=NULL );
 LEM_CHECKIT_Z( hdb!=NULL );

 int retval=def;
 isc_stmt_handle stmt = NULL;
 short flag3=0;

 XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(1));
 sqlda->sqln = 1;
 sqlda->version = 1;

 sqlda->sqlvar[0].sqldata = (char *)&retval;
 sqlda->sqlvar[0].sqltype = SQL_LONG+1;
 sqlda->sqlvar[0].sqllen  = sizeof(retval);
 sqlda->sqlvar[0].sqlind  = &flag3;

 if( isc_dsql_allocate_statement( status, &hdb, &stmt ) )
  {
   free(sqlda);
   return retval;
  }

 if( isc_dsql_prepare( status, &htx, &stmt, 0, sql.c_str(), 1, sqlda ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return retval;
  }

 if( isc_dsql_execute(status, &htx, &stmt, 1, NULL) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return retval;
  }

 long fetch_stat = isc_dsql_fetch( status, &stmt, 1, sqlda );

 if( isc_dsql_free_statement(status, &stmt, DSQL_drop) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return retval;
  }

 free(sqlda);

 return retval;
}


std::pair<int,int> NGramsDBMS::SelectIntPair( const lem::FString &sql )
{
 LEM_CHECKIT_Z( !sql.empty() );
 LEM_CHECKIT_Z( htx!=NULL );
 LEM_CHECKIT_Z( hdb!=NULL );

 std::pair<int,int> retval(-1,-1);

 isc_stmt_handle stmt = NULL;
 short flag3=0, flag4=1;

 XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(2));
 sqlda->sqln = 2;
 sqlda->version = 1;

 sqlda->sqlvar[0].sqldata = (char *)&retval.first;
 sqlda->sqlvar[0].sqltype = SQL_LONG+1;
 sqlda->sqlvar[0].sqllen  = sizeof(retval.first);
 sqlda->sqlvar[0].sqlind  = &flag3;

 sqlda->sqlvar[1].sqldata = (char *)&retval.second;
 sqlda->sqlvar[1].sqltype = SQL_LONG+1;
 sqlda->sqlvar[1].sqllen  = sizeof(retval.second);
 sqlda->sqlvar[1].sqlind  = &flag4;

 if( isc_dsql_allocate_statement( status, &hdb, &stmt ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return retval;
  }

 if( isc_dsql_prepare( status, &htx, &stmt, 0, sql.c_str(), 1, sqlda ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return retval;
  }

 if( isc_dsql_execute(status, &htx, &stmt, 1, NULL) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return retval;
  }

 long fetch_stat = isc_dsql_fetch( status, &stmt, 1, sqlda );

 if( isc_dsql_free_statement(status, &stmt, DSQL_drop) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return retval;
  }

 free(sqlda);

 return retval;
}


#endif



bool NGramsDBMS::TableExists( const lem::FString &table )
{
 bool exists=false;

 #if defined SOL_SQLITE_NGRAMS
 if( SelectInt(lem::format_str( "select count(*) from sqlite_master where type='table' and lower(name)='%s'", lem::to_lower(table).c_str() ))==1 )
  exists=true;
 #elif defined SOL_FIREBIRD_NGRAMS
 if( SelectInt(lem::format_str( "select count(*) from RDB$RELATIONS WHERE Lower(RDB$RELATION_NAME)='%s'", to_lower(table).c_str() ))==1 )
  exists=true;
 #endif 


 return exists;
}


void NGramsDBMS::ExecuteSql( const lem::FString &sql, bool check )
{
 LEM_CHECKIT_Z( !sql.empty() );
 ExecuteSql(sql.c_str(),check);
 return;
}


void NGramsDBMS::SetDBCache( int cache_size )
{
 #if defined SOL_SQLITE_NGRAMS

 LEM_CHECKIT_Z( cache_size>0 );
 LEM_CHECKIT_Z( hdb!=NULL );

 char buf[100];
 sprintf( buf, "PRAGMA cache_size=%d", cache_size/1024 ); // 1Kb per page

 int res = sqlite3_exec( hdb, buf, NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   const char *errmsg = sqlite3_errmsg(hdb);
   throw E_BaseException( lem::format_str( L"SQLite error %S", errmsg ).c_str() );
  }

 #endif

 return;
}


bool NGramsDBMS::IndexExists( const lem::FString &idx )
{
 #if defined SOL_SQLITE_NGRAMS
 return false;
 #elif defined SOL_FIREBIRD_NGRAMS
 return SelectInt(lem::format_str( "select count(*) from RDB$INDICES WHERE Lower(RDB$INDEX_NAME)='%s'", to_lower(idx).c_str() ))==1;
 #endif 
}



void NGramsDBMS::DropIndex( const lem::FString &idx )
{
 #if defined SOL_SQLITE_NGRAMS
 ExecuteSql( FString("DROP INDEX ")+idx, false );
 #elif defined SOL_FIREBIRD_NGRAMS
 if( SelectInt(lem::format_str( "select count(*) from RDB$INDICES WHERE Lower(RDB$INDEX_NAME)='%s'", to_lower(idx).c_str() ))==1 )
  ExecuteSql( FString("DROP INDEX ")+idx, false );
 #endif 

 return;
}


#if defined SOL_FIREBIRD_NGRAMS
void Solarix::RTrim( char *word, int len )
{
 int i=len-1;
 while( i>0 && word[i]==' ' )
  i--;

 word[i+1]=0;
 return;
}
#endif


void NGramsDBMS::SelectInts( const lem::FString &Select, lem::MCollect<int> &list )
{
 LEM_CHECKIT_Z( !Select.empty() );

 #if defined SOL_SQLITE_NGRAMS

 sqlite3_stmt *stmt=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), -1, &stmt, NULL );
 if( res==SQLITE_OK )
  {
   while( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     int i = sqlite3_column_int(stmt,0);
     list.push_back(i);
    } 

   sqlite3_finalize(stmt);
  }

 return;

 #elif defined SOL_FIREBIRD_NGRAMS

 LEM_CHECKIT_Z( htx!=NULL );
 LEM_CHECKIT_Z( hdb!=NULL );

 int val=0;
 isc_stmt_handle stmt = NULL;
 short flag3=0;

 XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(1));
 sqlda->sqln = 1;
 sqlda->version = 1;

 sqlda->sqlvar[0].sqldata = (char *)&val;
 sqlda->sqlvar[0].sqltype = SQL_LONG+1;
 sqlda->sqlvar[0].sqllen  = sizeof(val);
 sqlda->sqlvar[0].sqlind  = &flag3;

 if( isc_dsql_allocate_statement( status, &hdb, &stmt ) )
  {
   free(sqlda);
   return;
  }

 if( isc_dsql_prepare( status, &htx, &stmt, 0, Select.c_str(), 1, sqlda ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return;
  }

 if( isc_dsql_execute(status, &htx, &stmt, 1, NULL) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return;
  }

 while(true)
  {
   long fetch_stat = isc_dsql_fetch( status, &stmt, 1, sqlda );

   if( fetch_stat!=0 )
    {
     if( fetch_stat==100 )
      break;  

     #if LEM_DEBUGGING==1
     isc_print_status(status);
     #endif
     break; 
    }

   list.push_back(val);
  }

 if( isc_dsql_free_statement(status, &stmt, DSQL_drop) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
  }

 free(sqlda);

 #endif
}


lem::UFString NGramsDBMS::SelectStr( const char *Select )
{
 UFString res;

 #if defined SOL_SQLITE_NGRAMS

 int retval=0;

 sqlite3_stmt *stmt=NULL;
 int rc = sqlite3_prepare_v2( hdb, Select, -1, &stmt, NULL );
 if( rc==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     const wchar_t *txt = (const wchar_t*)sqlite3_column_text16(stmt,0);
     res = txt;
    } 

   sqlite3_finalize(stmt);
  }

 #elif defined SOL_FIREBIRD_NGRAMS

 LEM_CHECKIT_Z( htx!=NULL );
 LEM_CHECKIT_Z( hdb!=NULL );

 sqlchar word;

 int retval=0;
 isc_stmt_handle stmt = NULL;
 short flag0=0;

 XSQLDA *sqlda = (XSQLDA *)malloc(XSQLDA_LENGTH(1));
 sqlda->sqln = 1;
 sqlda->version = 1;

 sqlda->sqlvar[0].sqldata = (char *)word;
 sqlda->sqlvar[0].sqltype = SQL_TEXT+1;
 sqlda->sqlvar[0].sqlind  = &flag0;

 if( isc_dsql_allocate_statement( status, &hdb, &stmt ) )
  {
   free(sqlda);
   return res;
  }

 if( isc_dsql_prepare( status, &htx, &stmt, 0, Select, 1, sqlda ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return res;
  }

 if( isc_dsql_execute(status, &htx, &stmt, 1, NULL) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return res;
  }

 long fetch_stat = isc_dsql_fetch( status, &stmt, 1, sqlda );

 RTrim( word, sqlda->sqlvar[0].sqllen );
 res = from_utf8(word);

 if( isc_dsql_free_statement(status, &stmt, DSQL_drop) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   free(sqlda);
   return res;
  }

 free(sqlda);

 #endif

 return res;
}

void NGramsStorage_MySQL::CreateTable_Words( const lem::FString &suffix )
{
 const int l=lem::UCString::max_len*6+1; // utf8 encoding
 lem::FString sql = format_str( "CREATE TABLE WORDS%s( word char(%d) PRIMARY KEY, id integer )", suffix.c_str(), l );
 ExecuteSql(asql);
 return;
}

void NGramsStorage_FireBird::CreateTable_NGrams1( const lem::FString &suffix )
{
   #if LEM_DEBUGGING==1
   sprintf( asql, "CREATE TABLE NGRAM1%s( "
                  "id integer NOT NULL,"
                  "iword1 integer NOT NULL,"
                  "w integer NOT NULL"
                  ")", suffix.c_str() );
   #else
   sprintf( asql, "CREATE TABLE NGRAM1%s( "
                  "id integer,"
                  "iword1 integer,"
                  "w integer"
                  ")", suffix.c_str() );
   #endif

   db->ExecuteSql(asql);

   sprintf( asql, "CREATE TABLE STATS1%s( "
                  "max_w1 integer NOT NULL,"
                  "count_n1 integer NOT NULL"
                  ")", suffix.c_str() );

   db->ExecuteSql(asql);
   needs_index_creation1=true;

   #if LEM_DEBUGGING==1
    #if defined SOL_FIREBIRD_NGRAMS
     sprintf( asql, "ALTER TABLE NGRAM1%s "
                    "add constraint UNQ1_%s unique ( iword1 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #elif defined SOL_SQLITE_NGRAMS
     sprintf( asql, "CREATE UNIQUE INDEX UNQ1_%s ON NGRAM1%s( iword1 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #endif
   #endif


 return;
}



void NGramsStorage_FireBird::CreateTable_NGrams2( const lem::FString &suffix )
{
   #if LEM_DEBUGGING==1
   sprintf( asql, "CREATE TABLE NGRAM2%s( "
                  "id integer NOT NULL,"
                  "iword1 integer NOT NULL,"
                  "iword2 integer NOT NULL,"
                  "w integer NOT NULL"
                  ")", suffix.c_str() );
   #else
   sprintf( asql, "CREATE TABLE NGRAM2%s( "
                  "id integer,"
                  "iword1 integer,"
                  "iword2 integer,"
                  "w integer"
                  ")", suffix.c_str() );
   #endif

   db->ExecuteSql(asql);

   sprintf( asql, "CREATE TABLE STATS2%s( "
                  "max_w2 integer NOT NULL,"
                  "count_n2 integer NOT NULL"
                  ")", suffix.c_str() );

   db->ExecuteSql(asql);
   needs_index_creation2=true;

   #if LEM_DEBUGGING==1
    #if defined SOL_FIREBIRD_NGRAMS
     sprintf( asql, "ALTER TABLE NGRAM2%s "
                    "add constraint UNQ2_%s unique ( iword1, iword2 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #elif defined SOL_SQLITE_NGRAMS
     sprintf( asql, "CREATE UNIQUE INDEX UNQ2_%s ON NGRAM2%s( iword1, iword2 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #endif
   #endif


 return;
}


void NGramsStorage_FireBird::CreateTable_NGrams3( const lem::FString &suffix )
{
   #if LEM_DEBUGGING==1
   sprintf( asql, "CREATE TABLE NGRAM3%s( "
                  "id integer NOT NULL," 
                  "iword1 integer NOT NULL,"
                  "iword2 integer NOT NULL,"
                  "iword3 integer NOT NULL,"
                  "w integer NOT NULL"
                  ")", suffix.c_str() );
   #else
   sprintf( asql, "CREATE TABLE NGRAM3%s( "
                  "id integer," 
                  "iword1 integer,"
                  "iword2 integer,"
                  "iword3 integer,"
                  "w integer"
                  ")", suffix.c_str() );
   #endif
 
   db->ExecuteSql(asql);

   sprintf( asql, "CREATE TABLE STATS3%s( "
                   "max_w3 integer NOT NULL,"
                   "count_n3 integer NOT NULL"
                   ")", suffix.c_str() );

   db->ExecuteSql(asql);
   needs_index_creation3=true;

   #if LEM_DEBUGGING==1
    #if defined SOL_FIREBIRD_NGRAMS
     sprintf( asql, "ALTER TABLE NGRAM3%s "
                    "add constraint UNQ3_%s unique ( iword1, iword2, iword3 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #elif defined SOL_SQLITE_NGRAMS
     sprintf( asql, "CREATE UNIQUE INDEX UNQ3_%s ON NGRAM3%s( iword1, iword2, iword3 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #endif
   #endif


 return;
}


void NGramsStorage_FireBird::CreateTable_NGrams4( const lem::FString &suffix )
{
   #if LEM_DEBUGGING==1
   sprintf( asql, "CREATE TABLE NGRAM4%s( "
                  "id integer NOT NULL," 
                  "iword1 integer NOT NULL,"
                  "iword2 integer NOT NULL,"
                  "iword3 integer NOT NULL,"
                  "iword4 integer NOT NULL,"
                  "w integer NOT NULL"
                  ")", suffix.c_str() );
   #else
   sprintf( asql, "CREATE TABLE NGRAM4%s( "
                  "id integer," 
                  "iword1 integer,"
                  "iword2 integer,"
                  "iword3 integer,"
                  "iword4 integer,"
                  "w integer"
                  ")", suffix.c_str() );
   #endif
 
   db->ExecuteSql(asql);

   sprintf( asql, "CREATE TABLE STATS4%s( "
                   "max_w4 integer NOT NULL,"
                   "count_n4 integer NOT NULL"
                   ")", suffix.c_str() );

   db->ExecuteSql(asql);
   needs_index_creation4=true;

   #if LEM_DEBUGGING==1
    #if defined SOL_FIREBIRD_NGRAMS
     sprintf( asql, "ALTER TABLE NGRAM4%s "
                    "add constraint UNQ4_%s unique ( iword1, iword2, iword3, iword4 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #elif defined SOL_SQLITE_NGRAMS
     sprintf( asql, "CREATE UNIQUE INDEX UNQ4_%s ON NGRAM4%s( iword1, iword2, iword3, iword4 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #endif
   #endif


 return;
}


void NGramsStorage_FireBird::CreateTable_NGrams5( const lem::FString &suffix )
{
   #if LEM_DEBUGGING==1
   sprintf( asql, "CREATE TABLE NGRAM5%s( "
                  "id integer NOT NULL," 
                  "iword1 integer NOT NULL,"
                  "iword2 integer NOT NULL,"
                  "iword3 integer NOT NULL,"
                  "iword4 integer NOT NULL,"
                  "iword5 integer NOT NULL,"
                  "w integer NOT NULL"
                  ")", suffix.c_str() );
   #else
   sprintf( asql, "CREATE TABLE NGRAM5%s( "
                  "id integer," 
                  "iword1 integer,"
                  "iword2 integer,"
                  "iword3 integer,"
                  "iword4 integer,"
                  "iword5 integer,"
                  "w integer"
                  ")", suffix.c_str() );
   #endif
 
   db->ExecuteSql(asql);

   sprintf( asql, "CREATE TABLE STATS5%s( "
                   "max_w5 integer NOT NULL,"
                   "count_n5 integer NOT NULL"
                   ")", suffix.c_str() );

   db->ExecuteSql(asql);
   needs_index_creation5=true;

   #if LEM_DEBUGGING==1
    #if defined SOL_FIREBIRD_NGRAMS
     sprintf( asql, "ALTER TABLE NGRAM5%s "
                    "add constraint UNQ5_%s unique ( iword1, iword2, iword3, iword4, iword5 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #elif defined SOL_SQLITE_NGRAMS
     sprintf( asql, "CREATE UNIQUE INDEX UNQ5_%s ON NGRAM5%s( iword1, iword2, iword3, iword4, iword5 )"
                    , suffix.c_str(), suffix.c_str() );
     db->ExecuteSql(asql);
    #endif
   #endif


 return;
}

int NGramsStorage_FireBird::MaxBulkInsert(void) const
{
 return 100;
}


lem::FString NGramsStorage_FireBird::AppendBulkInsert(
                                                    const lem::FString &suffix,
                                                    int counter,
                                                    int id,
                                                    int id_word1,
                                                    int w
                                                   )
{
 if( counter>=1 )
  inserts.Add_Dirty( " UNION ALL " );

 sprintf(
         asql_buf,
         
         #if defined SOL_SQLITE_NGRAMS
         " SELECT %d, %d, %d ",
         #elif defined SOL_FIREBIRD_NGRAMS
         " SELECT %d, %d, %d FROM RDB$DATABASE",
         #endif

         it->second.first, it->first, it->second.second );
}

lem::FString NGramsStorage_FireBird::AppendBulkInsert(
                                                    const lem::FString &suffix,
                                                    int counter,
                                                    int id,
                                                    int id_word1,
                                                    int id_word2,
                                                    int w
                                                   )
{
}

lem::FString NGramsStorage_FireBird::AppendBulkInsert(
                                                    const lem::FString &suffix,
                                                    int counter,
                                                    int id,
                                                    int id_word1,
                                                    int id_word2,
                                                    int id_word3,
                                                    int w
                                                   )
{
}

lem::FString NGramsStorage_FireBird::AppendBulkInsert(
                                                    const lem::FString &suffix,
                                                    int counter,
                                                    int id,
                                                    int id_word1,
                                                    int id_word2,
                                                    int id_word3,
                                                    int id_word4,
                                                    int w
                                                   )
{
}

lem::FString NGramsStorage_FireBird::AppendBulkInsert(
                                                    const lem::FString &suffix,
                                                    int counter,
                                                    int id,
                                                    int id_word1,
                                                    int id_word2,
                                                    int id_word3,
                                                    int id_word4,
                                                    int id_word5,
                                                    int w
                                                   )
{
}


void NGramsStorage_FireBird::UpdateNGrams(
                                        const lem::FString &suffix,
                                        int order, 
                                        const lem::MCollect< std::pair<int,int> > & list
                                       )
{
   lem::Container::size_type nu = list.size();

   if( nu>0 )
    {
     if( order==1 )
      {
       if( !db->IndexExists( lem::format_str( "idx11%s", suffix.c_str() ) ) )
        {
         sprintf( asql_buf, "CREATE UNIQUE INDEX idx11%s ON NGRAM1%s(id)", suffix.c_str(), suffix.c_str() );
         db->ExecuteSql(asql_buf);
         db->CommitCreatedIndeces();
        }
      }
 
     if( order==2 )
      {
       if( !db->IndexExists( lem::format_str( "idx21%s", suffix.c_str() ) ) )
        {
         sprintf( asql_buf, "CREATE UNIQUE INDEX idx21%s ON NGRAM2%s(id)", suffix.c_str(), suffix.c_str() );
         db->ExecuteSql(asql_buf);
         db->CommitCreatedIndeces();
        }
      }

     if( order==3 )
      {
       if( !db->IndexExists( lem::format_str( "idx31%s", suffix.c_str() ) ) )
        {
         sprintf( asql_buf, "CREATE UNIQUE INDEX idx31%s ON NGRAM3%s(id)", suffix.c_str(), suffix.c_str() );
         db->ExecuteSql(asql_buf);
         db->CommitCreatedIndeces();
        }
      }  

     if( order==4 )
      {
       if( !db->IndexExists( lem::format_str( "idx41%s", suffix.c_str() ) ) )
        {
         sprintf( asql_buf, "CREATE UNIQUE INDEX idx41%s ON NGRAM4%s(id)", suffix.c_str(), suffix.c_str() );
         db->ExecuteSql(asql_buf);
         db->CommitCreatedIndeces();
        }
      }

     if( order==5 )
      {
       if( !db->IndexExists( lem::format_str( "idx51%s", suffix.c_str() ) ) )
        {
         sprintf( asql_buf, "CREATE UNIQUE INDEX idx51%s ON NGRAM5%s(id)", suffix.c_str(), suffix.c_str() );
         db->ExecuteSql(asql_buf);
         db->CommitCreatedIndeces();
        }
      }

     int nu10=CastSizeToInt(nu/10);
     int prev_p=0;
     for( lem::Container::size_type i=0; i<nu; ++i )
      {
       sprintf( asql_buf, "UPDATE NGRAM%d%s SET w=w+%d WHERE id=%d", order, suffix.c_str(), list[i].second, list[i].first );
       db->ExecuteSql(asql_buf);

       if( !(i%1024) && nu10>0 )
        {
         int p = i/nu10;
         if( p>p_prev )
          {
           p_prev=p;
           mout->printf( " %d", p );
           mout->flush(); 
          } 
        }  
      }
    }

}

void NGramsStorage_FireBird::CreateTable_Segments(void)
{
   db->ExecuteSql(
   #if defined SOL_FIREBIRD_NGRAMS
   "CREATE TABLE SEGMENTS( segment_n integer, suffix char(30) )"
   #else
   "CREATE TABLE SEGMENTS( segment_n integer, suffix varchar(30) )"
   #endif
   );

 return;
}

#endif
