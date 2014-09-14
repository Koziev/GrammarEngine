#if defined SOL_FIREBIRD_DICTIONARY_STORAGE

#include <lem/runtime_checks.h>
#include <lem/mysql_helpers.h>
#include <lem/fstring.h>
#include <lem/logfile.h>
#include <lem/oformatter.h>
#include <lem/unicode.h>
#include <lem/solarix/StorageConnection_FireBird.h> 
#include <lem/solarix/TransactionGuard_FireBird.h>

#if defined(LEM_MSC) && _MSC_VER>=1300
 #pragma comment ( lib, "fbclient_ms.lib" )
#endif

using namespace Solarix;

static char isc_tpb[5] = { isc_tpb_version1, isc_tpb_write, isc_tpb_read_committed, isc_tpb_nowait,
                           isc_tpb_rec_version };

static char isc_tpb_rd[5] = { isc_tpb_version1, isc_tpb_read, isc_tpb_read_committed, isc_tpb_nowait,
                           isc_tpb_rec_version };


StorageConnection_FireBird::StorageConnection_FireBird(
                                                       const lem::FString &login,
                                                       const lem::FString &psw,
                                                       const lem::FString &db
                                                      )
{
 int params_cur=0;

 const char login_len = login.length();
 const char psw_len = psw.length();

 char params[128];
 params[params_cur++] = isc_dpb_version1;
 params[params_cur++] = isc_dpb_user_name;
 params[params_cur++] = login_len;
 memcpy( params+params_cur, login, login_len ); params_cur+=login_len;
 params[ params_cur++ ] = isc_dpb_password;
 params[ params_cur++ ] = psw_len;
 memcpy( params+params_cur, psw, psw_len ); params_cur+=psw_len;
 int count=0;

 if( isc_attach_database(status, 0, db.c_str(), &hdb, params_cur, params ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   throw E_BaseException( L"FireBird error: can not connect to database" );
  }

 return;
}


StorageConnection_FireBird::~StorageConnection_FireBird(void)
{
 if( htx!=NULL )
  {
   throw E_BaseException("FireBird error: closing connection - last transaction is still active!");
  }

 if( isc_detach_database( status, &hdb ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   throw E_BaseException( L"FireBird error: can not detach database" );
  }

 hdb=NULL;

 return;
}


TransactionGuard* StorageConnection_FireBird::GetTx(void)
{
 return new TransactionGuard_FireBird(this);
}


void StorageConnection_FireBird::BeginTx(void)
{
 if( htx!=NULL )
  throw E_BaseException( L"FireBird error: can not begin >>>recursive<<< transaction" );

 if( isc_start_transaction(status, &htx, 1, &hdb, 5, isc_tpb ) )
  {
   #if LEM_DEBUGGING==1
   isc_print_status(status);
   #endif
   throw E_BaseException( L"FireBird error: can not start transaction" );
  }

 return;
}


void StorageConnection_FireBird::CommitTx(void)
{
 if( htx==NULL )
  {
   throw E_BaseException( "FireBird error: can not commit >>>NULL<<< transaction!" );
  }

 if( isc_commit_transaction( status, &htx ) )
  {
   isc_print_status(status);
   throw E_BaseException( L"FireBird error: can not commit transaction" );
  }

 htx = NULL;

 return;
}



void StorageConnection_FireBird::CommitRetainingTx(void)
{
 if( htx==NULL )
  {
   throw E_BaseException( "FireBird error: can not commit >>>NULL<<< transaction!" );
  }

 if( isc_commit_retaining( status, &htx ) )
  {
   isc_print_status(status);
   throw E_BaseException( L"FireBird error: can not commit transaction" );
  }

 htx = NULL;

 return;
}


void StorageConnection_FireBird::RollbackTx(void)
{
 if( htx==NULL )
  {
   throw E_BaseException( "FireBird error: can not rollback >>>NULL<<< transaction!" );
  }

 if( isc_rollback_transaction( status, &htx ) )
  {
   isc_print_status(status);
   throw E_BaseException( L"FireBird error: can not rollback transaction" );
  }

 htx = NULL;

 return;
}


void StorageConnection_FireBird::Error( const lem::FString &sql )
{
 #if LEM_DEBUGGING==1
 isc_print_status(status);
 #endif

 SQLCODE=isc_sqlcode(status);

 lem::MemFormatter mem;
 mem.printf( "Error in FireBird, sql=%s SQLCODE=%d", sql.c_str(), SQLCODE );
 throw lem::E_BaseException(mem.string());
}

void StorageConnection_FireBird::Execute( const lem::FString &sql )
{
 if( htx==NULL )
  throw E_BaseException( L"Can not execute SQL command, because no transaction is open" );

 if( isc_dsql_execute_immediate( status, &hdb, &htx, 0, sql, 3, 0L ) )
  {
   Error(sql);
  }

 return;
}





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




bool StorageConnection_FireBird::TableExists( const lem::FString &table )
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





bool StorageConnection_FireBird::IndexExists( const lem::FString &idx )
{
 #if defined SOL_SQLITE_NGRAMS
 return false;
 #elif defined SOL_FIREBIRD_NGRAMS
 return SelectInt(lem::format_str( "select count(*) from RDB$INDICES WHERE Lower(RDB$INDEX_NAME)='%s'", to_lower(idx).c_str() ))==1;
 #endif 
}



void StorageConnection_FireBird::DropIndex( const lem::FString &idx )
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


void StorageConnection_FireBird::SelectInts( const lem::FString &Select, lem::MCollect<int> &list )
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


lem::UFString StorageConnection_FireBird::SelectStr( const char *Select )
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

bool NGramsStorage_FireBird::IsConnected(void) const
{
 return hdb!=NULL;
}


#endif
