#if defined SOL_MYSQL_NGRAMS && !defined(SOL_NO_NGRAMS)

#include <lem/console_streams.h>
#include <lem/unicode.h>
#include <lem/smart_pointers.h>

#include <lem/solarix/StorageConnection_MySQL.h>
#include <lem/solarix/MySQLCnx.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/NGramsStorage_MySQL.h>

using namespace std;
using namespace lem;
using namespace Solarix;



NGramsStorage_MySQL::NGramsStorage_MySQL( StorageConnection_MySQL *_cnx )
 : cnx(_cnx), open_tx(0)
{
 return;
}


NGramsStorage_MySQL::~NGramsStorage_MySQL(void)
{
 Disconnect();
 return;
}


NGramsDBMS* NGramsStorage_MySQL::CreateDisconnectedClone() const
{
 return NULL;
}



bool NGramsStorage_MySQL::IsRemote(void) const
{
 return true;
}

void NGramsStorage_MySQL::Connect( const lem::Path &dbfile )
{
 return;
}

bool NGramsStorage_MySQL::Connected(void) const
{
 return cnx->IsConnected();
}



void NGramsStorage_MySQL::Disconnect(void)
{
 cnx->Disconnect();
 return;
}


void NGramsStorage_MySQL::BeginTx(void)
{
 if( open_tx!=0 )
  throw E_BaseException( L"Can not start recursive transaction" );

 open_tx++;
 cnx->BeginTx();
 return;
}


void NGramsStorage_MySQL::BeginReadTx(void)
{
 cnx->BeginReadTx();
 return;
}




void NGramsStorage_MySQL::CommitTx(void)
{
 if( open_tx==0 )
  throw E_BaseException( L"Can not commit transaction - no one is open" );

 open_tx--;
 cnx->CommitTx();
 return;
}

void NGramsStorage_MySQL::CommitReadTx(void)
{
 cnx->EndReadTx();
 return;
}



void NGramsStorage_MySQL::CommitRetaining(void)
{
 return;
}


void NGramsStorage_MySQL::CommitCreatedIndeces(void)
{
 return;
}




void NGramsStorage_MySQL::ExecuteSql( const char *sql, bool check )
{
 cnx->Execute(sql);
 return;
} 



int NGramsStorage_MySQL::SelectInt( const lem::FString &sql, int def )
{
 LEM_CHECKIT_Z( !sql.empty() );

 int retval=def;

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 if( rs->Fetch() )
  {
   retval = rs->GetInt(0);
  }

 return retval;
}


int NGramsStorage_MySQL::SelectInt( const char *sql, int def )
{
 LEM_CHECKIT_Z( sql!=NULL );

 int retval=def;

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 if( rs->Fetch() )
  {
   retval = rs->GetInt(0);
  }

 return retval;
}


std::pair<int,int> NGramsStorage_MySQL::SelectIntPair( const lem::FString & sql )
{
 int retval1=-1;
 int retval2=-1;

 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 if( rs->Fetch() )
  {
   retval1 = rs->GetInt(0);
   retval2 = rs->GetInt(1);
  } 

 return std::make_pair(retval1,retval2);
}





bool NGramsStorage_MySQL::TableExists( const lem::FString &table )
{
 return cnx->DoesTableExist(table);
}


void NGramsStorage_MySQL::ExecuteSql( const lem::FString &sql, bool check )
{
 LEM_CHECKIT_Z( !sql.empty() );
 cnx->Execute(sql.c_str());
 return;
}


void NGramsStorage_MySQL::SetDBCache( int cache_size )
{
 return;
}


bool NGramsStorage_MySQL::IndexExists( const lem::FString &idx, const lem::FString & table )
{
 return cnx->DoesIndexExist(idx,table);
}



void NGramsStorage_MySQL::DropIndex( const lem::FString &idx, const lem::FString & table_name )
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 if( cnx->DoesIndexExist(idx,table_name) )
  ExecuteSql( FString("DROP INDEX ")+idx, false );

 return;
}



void NGramsStorage_MySQL::SelectInts( const lem::FString &sql, lem::MCollect<int> &list )
{
 LEM_CHECKIT_Z( !sql.empty() );
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   list.push_back( rs->GetInt(0) );
  }

 return;
}

void NGramsStorage_MySQL::SelectFStrings( const lem::FString &sql, lem::Collect<lem::FString> &list )
{
 LEM_CHECKIT_Z( !sql.empty() );
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 while( rs->Fetch() )
  {
   list.push_back( lem::to_utf8(rs->GetUFString(0)) );
  }

 return;
}



lem::UFString NGramsStorage_MySQL::SelectStr( const char *sql )
{
 lem::Ptr<LS_ResultSet> rs( Select(sql) );
 if( rs->Fetch() )
  {
   return rs->GetUFString(0);
  }

 return UFString();
}



LS_ResultSet* NGramsStorage_MySQL::Select( const lem::FString &sql )
{
 return cnx->Select(sql);
}



void NGramsStorage_MySQL::CreateTable_Words( const lem::FString &suffix )
{
 lem::FString sql = format_str( "CREATE TABLE NGRAM_WORDS%s( word varchar(64) PRIMARY KEY, id integer )", suffix.c_str() );
 ExecuteSql(sql);
 return;
}


void NGramsStorage_MySQL::CreateTable_NGrams1( const lem::FString &suffix )
{
 char asql[200];

 #if LEM_DEBUGGING==1
 sprintf( asql, "CREATE TABLE NGRAM1%s( "
                "id integer NOT NULL PRIMARY KEY,"
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

 ExecuteSql(asql);

 sprintf( asql, "CREATE TABLE NGRAM_STATS1%s( "
                "max_w1 integer NOT NULL,"
                "count_n1 integer NOT NULL"
                ")", suffix.c_str() );

 ExecuteSql(asql);

 #if LEM_DEBUGGING==1
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ1_%s ON NGRAM1%s( iword1 )"
                , suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif

 return;
}



void NGramsStorage_MySQL::CreateTable_NGrams2( const lem::FString &suffix )
{
 char asql[200];

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

 ExecuteSql(asql);

 sprintf( asql, "CREATE TABLE NGRAM_STATS2%s( "
                "max_w2 integer NOT NULL,"
                "count_n2 integer NOT NULL"
                ")", suffix.c_str() );

 ExecuteSql(asql);

 #if LEM_DEBUGGING==1
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ2_%s ON NGRAM2%s( iword1, iword2 )"
                  , suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif

 return;
}


void NGramsStorage_MySQL::CreateTable_NGrams3( const lem::FString &suffix )
{
 char asql[200];

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
 
 ExecuteSql(asql);

 sprintf( asql, "CREATE TABLE NGRAM_STATS3%s( "
                 "max_w3 integer NOT NULL,"
                 "count_n3 integer NOT NULL"
                 ")", suffix.c_str() );

 ExecuteSql(asql);

 #if LEM_DEBUGGING==1
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ3_%s ON NGRAM3%s( iword1, iword2, iword3 )"
                  , suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif

 return;
}


void NGramsStorage_MySQL::CreateTable_NGrams4( const lem::FString &suffix )
{
 char asql[200];

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
 
 ExecuteSql(asql);

 sprintf( asql, "CREATE TABLE NGRAM_STATS4%s( "
                 "max_w4 integer NOT NULL,"
                 "count_n4 integer NOT NULL"
                 ")", suffix.c_str() );

 ExecuteSql(asql);

 #if LEM_DEBUGGING==1
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ4_%s ON NGRAM4%s( iword1, iword2, iword3, iword4 )"
                  , suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif

 return;
}


void NGramsStorage_MySQL::CreateTable_NGrams5( const lem::FString &suffix )
{
 char asql[200];

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
 
 ExecuteSql(asql);

 sprintf( asql, "CREATE TABLE NGRAM_STATS5%s( "
                 "max_w5 integer NOT NULL,"
                 "count_n5 integer NOT NULL"
                 ")", suffix.c_str() );

 ExecuteSql(asql);

 #if LEM_DEBUGGING==1
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ5_%s ON NGRAM5%s( iword1, iword2, iword3, iword4, iword5 )"
                , suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif

 return;
}


int NGramsStorage_MySQL::MaxBulkInsert(void) const
{
 return 250;
}


lem::FString NGramsStorage_MySQL::StartBulkInsert( const lem::FString &suffix, int order )
{
 switch( order )
 {
  case 1: return lem::format_str( "INSERT INTO NGRAM1%s( id, iword1, w ) VALUES ", suffix.c_str() );
  case 2: return lem::format_str( "INSERT INTO NGRAM2%s( id, iword1, iword2, w ) VALUES ", suffix.c_str() );
  case 3: return lem::format_str( "INSERT INTO NGRAM3%s( id, iword1, iword2, iword3, w ) VALUES ", suffix.c_str() );
  case 4: return lem::format_str( "INSERT INTO NGRAM4%s( id, iword1, iword2, iword3, iword4, w ) VALUES ", suffix.c_str() );
  case 5: return lem::format_str( "INSERT INTO NGRAM5%s( id, iword1, iword2, iword3, iword4, iword5, w ) VALUES ", suffix.c_str() );
  default: LEM_STOPIT; return lem::FString();
 }
}


lem::FString NGramsStorage_MySQL::AppendBulkInsert(
                                                   const lem::FString &suffix,
                                                   int counter,
                                                   int id,
                                                   int id_word1,
                                                   int w
                                                  )
{
 lem::FString str;

 if( counter>0 )
  str.Add_Dirty( ',' );

 str += lem::format_str(
                        "( %d, %d, %d )",
                        id, id_word1, w ); 

 return str;
}


lem::FString NGramsStorage_MySQL::AppendBulkInsert(
                                                   const lem::FString &suffix,
                                                   int counter,
                                                   int id,
                                                   int id_word1,
                                                   int id_word2,
                                                   int w
                                                  )
{
 lem::FString str;

 if( counter>0 )
  str.Add_Dirty( ',' );

 str += lem::format_str(
                       "( %d, %d, %d, %d )",
                       id, id_word1, id_word2, w ); 

 return str;
}


lem::FString NGramsStorage_MySQL::AppendBulkInsert(
                                                   const lem::FString &suffix,
                                                   int counter,
                                                   int id,
                                                   int id_word1,
                                                   int id_word2,
                                                   int id_word3,
                                                   int w
                                                  )
{
 lem::FString str;

 if( counter>0 )
  str.Add_Dirty( ',' );

 str += lem::format_str(
                       "( %d, %d, %d, %d, %d )",
                       id, id_word1, id_word2, id_word3, w ); 

 return str;
}


lem::FString NGramsStorage_MySQL::AppendBulkInsert(
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
 lem::FString str;

 if( counter>0 )
  str.Add_Dirty( ',' );

 str += lem::format_str(
                        "( %d, %d, %d, %d, %d, %d )",
                        id, id_word1, id_word2, id_word3, id_word4, w ); 

 return str;
}



lem::FString NGramsStorage_MySQL::AppendBulkInsert(
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
 lem::FString str;

 if( counter>0 )
  str.Add_Dirty( ',' );

 str += lem::format_str(
                       "( %d, %d, %d, %d, %d, %d, %d )",
                       id, id_word1, id_word2, id_word3, id_word4, id_word5, w ); 

 return str;
}


void NGramsStorage_MySQL::UpdateNGrams(
                                       const lem::FString &suffix,
                                       int order, 
                                       const lem::MCollect< std::pair<int,int> > & list
                                       )
{
 char asql_buf[1000];

 MYSQL_BIND    bind[2];
 int           int_data1, int_data2;

 sprintf( asql_buf, "UPDATE NGRAM%d%s SET w=w+? WHERE id=?", order, suffix.c_str() );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 MYSQL_STMT *stmt = mysql_stmt_init(c->mysql);
 if(!stmt)
  {
   cnx->Error();
  }

 if( mysql_stmt_prepare( stmt, asql_buf, strlen(asql_buf) ) )
  {
   cnx->Error(asql_buf);
  }

 /* Get the parameter count from the statement */
 //param_count= mysql_stmt_param_count(stmt);
 /*
if (param_count != 2)
{
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  exit(0);
}
*/

 memset( bind, 0, sizeof(bind) );

 bind[0].buffer_type = MYSQL_TYPE_LONG;
 bind[0].buffer = (char *)&int_data1;
 bind[0].is_null = 0;
 bind[0].length = 0;

 bind[1].buffer_type = MYSQL_TYPE_LONG;
 bind[1].buffer = (char *)&int_data2;
 bind[1].is_null = 0;
 bind[1].length = 0;

 if( mysql_stmt_bind_param(stmt, bind) )
  {
   cnx->Error(asql_buf);
  }

 for( lem::Container::size_type i=0; i<list.size(); ++i )
  {
   int_data1 = list[i].second;
   int_data2 = list[i].first;

   if( mysql_stmt_execute(stmt) )
    {
     cnx->Error();
    }
  }

 return;
}


void NGramsStorage_MySQL::CreateTable_Segments(void)
{
 ExecuteSql( "CREATE TABLE NGRAM_SEGMENTS( segment_n varchar(20) NOT NULL, suffix varchar(30) )" );
 ExecuteSql("CREATE UNIQUE INDEX NGRAM_SEGMENTS_UNQ1 ON NGRAM_SEGMENTS(segment_n,suffix)");

 return;
}


#endif
