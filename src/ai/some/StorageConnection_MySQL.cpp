#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/runtime_checks.h>
#include <lem/mysql_helpers.h>
#include <lem/conversions.h>
#include <lem/fstring.h>
#include <lem/logfile.h>
#include <lem/oformatter.h>
#include <lem/unicode.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/TransactionGuard_MySQL.h>
#include <lem/solarix/MySQLCnx.h>
#include <lem/solarix/StorageConnection_MySQL.h> 

#if defined(LEM_MSC) && _MSC_VER>=1300 && defined(LEM_WINDOWS)
 #pragma comment ( lib, "libmysql.lib" )
#endif

using namespace Solarix;

StorageConnection_MySQL::StorageConnection_MySQL(
                                                 const lem::FString &_login,
                                                 const lem::FString &_psw,
                                                 const lem::FString &_db,
                                                 const lem::FString &_host,
                                                 int _port,
                                                 int _pool_size
                                                )
 : login(_login), psw(_psw), schema(_db), host(_host), port(_port), pool_size(_pool_size)
{
 LEM_CHECKIT_Z( pool_size>0 );

 cnx_list.resize( pool_size );
 cnx_list.Nullify();

 return;
}


StorageConnection_MySQL::~StorageConnection_MySQL(void)
{
 for( lem::Container::size_type i=0; i<cnx_list.size(); ++i )
  {
   if( cnx_list[i]!=NULL )
    {
     mysql_close( cnx_list[i]->mysql );
     delete cnx_list[i];
    }
  }

 return;
}




TransactionGuard* StorageConnection_MySQL::GetTx(void)
{
 return new TransactionGuard_MySQL(this);
}

TransactionGuard* StorageConnection_MySQL::GetReadTx(void)
{
 return new ReadTransactionGuard_MySQL(this);
}


void StorageConnection_MySQL::BeginTx(void)
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 lem::mysql_begin_tx(cnx->mysql);
 cnx->tx_count++;
 //LEM_CHECKIT_Z( cnx->tx_count==1 );

 return;
}


void StorageConnection_MySQL::CommitTx(void)
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 lem::mysql_commit_tx(cnx->mysql);
 cnx->tx_count--;
// LEM_CHECKIT_Z( cnx->tx_count==0 );

 return;
}


void StorageConnection_MySQL::RollbackTx(void)
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 lem::mysql_rollback_tx(cnx->mysql);
 cnx->tx_count--;
 LEM_CHECKIT_Z( cnx->tx_count==0 );

 return;
}



void StorageConnection_MySQL::BeginReadTx(void)
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 lem::mysql_begin_tx(cnx->mysql);
 cnx->tx_count++;
 LEM_CHECKIT_Z( cnx->tx_count==1 );

 return;
}


void StorageConnection_MySQL::EndReadTx(void)
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 lem::mysql_commit_tx(cnx->mysql);
 cnx->tx_count--;
 LEM_CHECKIT_Z( cnx->tx_count==0 );

 return;
}


void StorageConnection_MySQL::Error( const lem::FString &sql )
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 lem::MemFormatter mem;
 mem.printf( "Error in MySQL, sql=%s, error=%us", sql.c_str(), lem::mysql_errmsg(cnx->mysql).c_str() );
 throw lem::E_BaseException(mem.string());
}


void StorageConnection_MySQL::Error(void)
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 lem::MemFormatter mem;
 mem.printf( "Error in MySQL, message=%us", lem::mysql_errmsg(cnx->mysql).c_str() );
 throw lem::E_BaseException(mem.string());
}


void StorageConnection_MySQL::Execute( const lem::FString &sql )
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 int res = mysql_query(cnx->mysql,sql.c_str());
 if( res!=0 )
  Error(sql);

 return;
}


int StorageConnection_MySQL::GetLastId(void)
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 return (int)mysql_insert_id(cnx->mysql);
}

bool StorageConnection_MySQL::IsConnected(void) const
{
 return true;
}


bool StorageConnection_MySQL::DoesIndexExist( const lem::FString &index_name, const lem::FString &table_name )
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 lem::FString sql( lem::format_str( "SHOW INDEX FROM %s FROM %s WHERE Key_name='%s'"
                                    , table_name.c_str(), schema.c_str(), index_name.c_str() ) );
 
 bool rc=false;

 int ok = mysql_query( cnx->mysql, sql.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(cnx->mysql);
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       rc = true;
      }

     mysql_free_result(res);
    }
  }
 else
  {
   lem::MemFormatter mem;
   mem.printf( "Error in MySQL, sql=%s, error=%us", sql.c_str(), lem::mysql_errmsg(cnx->mysql).c_str() );
   throw lem::E_BaseException(mem.string());
  }

 return rc;
}


bool StorageConnection_MySQL::DoesTableExist( const lem::FString &table_name )
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 lem::FString sql( lem::format_str( "SELECT count(*) FROM INFORMATION_SCHEMA.TABLES"
                                    " WHERE TABLE_SCHEMA='%s' AND"
                                    " TABLE_NAME='%s'", schema.c_str(), table_name.c_str() ) );
 return lem::mysql_select_int( cnx->mysql, sql.c_str() )==1;
}


LS_ResultSet* StorageConnection_MySQL::Select( const lem::FString &sql )
{
 MySQLCnx *cnx = GetDb();

 #if defined LEM_THREADS 
 cnx->cs.Enter();
 #endif

 std::auto_ptr<TransactionGuard> read_tx(GetReadTx());

 int ok = mysql_query( cnx->mysql, sql.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(cnx->mysql);
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(cnx,res,read_tx.release());
    }
   else
    {
     #if defined LEM_THREADS 
     cnx->cs.Leave();
     #endif

     LEM_STOPIT;
    } 
  }
 else
  {
   Error(sql);
  }

 #if defined LEM_THREADS 
 cnx->cs.Leave();
 #endif

 return NULL;
}


void StorageConnection_MySQL::Ping(void)
{
/*
 int rc = mysql_ping(mysql);
 if( rc!=0 )
  {
   lem::MemFormatter mem;
   mem.printf( "Error in MySQL: mysql_ping returned %d, message=%us", rc, lem::mysql_errmsg(mysql).c_str() );
   throw lem::E_BaseException(mem.string());
  }
*/
 #if defined LEM_THREADS
 //lem::Process::CritSecLocker guard(&cs_pool);
 #endif

 for( lem::Container::size_type i=0; i<cnx_list.size(); ++i )
  {
   MySQLCnx *cnx = cnx_list[i];

   if( cnx==NULL )
    continue;

   #if defined LEM_THREADS
   lem::Process::CritSecLocker guard(&cnx->cs);
   #endif

   int ok = mysql_query( cnx->mysql, "select count(*) from information_schema.tables" );
   if( ok!=0 )
    {
     lem::MemFormatter mem;
     mem.printf( "Error in MySQL: file %s line %d message=%us", __FILE__, __LINE__, lem::mysql_errmsg(cnx->mysql).c_str() );
     throw lem::E_BaseException(mem.string());
    }
   else
    {
     MYSQL_RES *res = mysql_store_result(cnx->mysql);
     mysql_free_result(res);
    }
  }

 return;
}



MySQLCnx* StorageConnection_MySQL::CreateCnx(void)
{
 const int thread_safe = mysql_thread_safe();
 if( thread_safe!=1 )
  throw lem::E_BaseException( L"Thread-safe libmysql is required" );

 static char *opt_unix_socket=0;

 MYSQL *mysql=NULL;

 if( !(mysql=mysql_init(NULL)) )
  {
   throw lem::E_BaseException( L"mysql_init failed" );
  }

 if( !(mysql_real_connect( mysql, host.c_str(), login.c_str(),
                          psw.c_str(), "", port,
                          opt_unix_socket, CLIENT_MULTI_STATEMENTS )))
  {
   lem::MemFormatter msg;
   msg.printf( "Can not connect to MySQL database host='%s', login='%s', password='%s', port=%d, error message=%us"
               , host.c_str()
               , login.c_str()
               , psw.c_str()
               , port
               , lem::to_unicode(mysql_error(mysql)).c_str() );


   lem::UFString err(msg.string());
   if( lem::LogFile::IsOpen() )
    lem::LogFile::logfile->printf( "%us\n", err.c_str() );

   throw lem::E_BaseException( err );
  }

 mysql->reconnect = 1;

 if( mysql_select_db( mysql, schema.c_str() )!=0 )
  {
   lem::MemFormatter msg;
   msg.printf( "Can not select database='%s', error message=%us"
               , lem::to_unicode(schema).c_str()
               , lem::to_unicode(mysql_error(mysql)).c_str() );

   lem::UFString err(msg.string());
   if( lem::LogFile::IsOpen() )  
    lem::LogFile::logfile->printf( "%us\n", err.c_str() );

   throw lem::E_BaseException( err );
  }

 mysql_autocommit( mysql, FALSE );

 int rc2 = mysql_set_character_set( mysql, "utf8" );

 MySQLCnx *cnx = new MySQLCnx;
 cnx->mysql = mysql;

 return cnx;
}


MySQLCnx* StorageConnection_MySQL::GetDb(void)
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs_pool);
 #endif

 if( cnx_list.size()==1 )
  {
   if( cnx_list.front()==NULL )
    {
     cnx_list[0] = CreateCnx();
    }

   MySQLCnx *cnx = cnx_list.front();
   return cnx;
  }
 else
  {
   #if defined LEM_THREADS
   lem::Process::ThreadID thread_id = lem::Process::Thread::GetCurrentID();
   const int ithread = lem::Process::Thread::Id2Int(thread_id);
   const int icnx = ithread % CastSizeToInt(cnx_list.size());
   #else
   const int icnx = 0;
   #endif

   MySQLCnx *cnx = cnx_list[icnx];
   
   if( cnx==NULL )
    {
     cnx = CreateCnx();
     cnx_list[icnx] = cnx;
     return cnx;
    }
   else
    {
     return cnx;
    }
  }
}


int StorageConnection_MySQL::SelectInt( const lem::FString &sql, int default_value )
{
 int retval=default_value;

 MySQLCnx *cnx = GetDb();
 
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cnx->cs);
 #endif

 int ok = mysql_query( cnx->mysql, sql.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(cnx->mysql);
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       const char *str = row[0];

       if( !lem::to_int( str, &retval ) )
        retval=-1;
      }

     mysql_free_result(res);
    }
  }
 else
  {
   lem::MemFormatter mem;
   mem.printf( "Error in MySQL, sql=%s, error=%us", sql.c_str(), lem::mysql_errmsg(cnx->mysql).c_str() );
   throw lem::E_BaseException(mem.string());
  }

 return retval;
}

void StorageConnection_MySQL::Escape( lem::UFString &str )
{
 lem::mysql_escape(str);
 return;
}

#endif
