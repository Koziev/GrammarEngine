#if !defined SOL_NO_NGRAMS
#include <lem/oformatter.h>
#include <lem/unicode.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>
#include <lem/solarix/NGramsStorage_SQLITE.h>

using namespace std;
using namespace lem;
using namespace Solarix;

#if defined(LEM_MSC) && _MSC_VER>=1300 && defined(LEM_WINDOWS)
 #if LEM_DEBUGGING==1
  # pragma comment ( lib, "sqlited.lib" )
 #else
  # pragma comment ( lib, "sqlite.lib" )
 #endif
#endif


NGramsStorage_SQLITE::NGramsStorage_SQLITE(void)
{
 hdb=NULL;
 open_tx=0;
 return;
}


NGramsStorage_SQLITE::~NGramsStorage_SQLITE(void)
{
 Disconnect();
 return;
}


NGramsDBMS* NGramsStorage_SQLITE::CreateDisconnectedClone() const
{
 return new NGramsStorage_SQLITE();
}



bool NGramsStorage_SQLITE::IsRemote(void) const
{
 return false;
}


bool NGramsStorage_SQLITE::Connected(void) const
{
 return hdb!=NULL;
}


void NGramsStorage_SQLITE::Connect( const lem::Path &connection_string )
{
 hdb = lem::sqlite_open_serialized(connection_string.GetUnicode());

 lem::sqlite_execute( hdb, "PRAGMA temp_store = MEMORY" );
 return;
}


void NGramsStorage_SQLITE::Disconnect(void)
{
 if( hdb!=NULL )
  {
   if( hdb!=NULL )
    {
     sqlite3_close(hdb);
    }

   hdb = NULL;
  }

 return;
}


void NGramsStorage_SQLITE::BeginTx(void)
{
 if( open_tx!=0 )
  throw E_BaseException( L"Can not start recursive transaction" );

 open_tx++;
 lem::sqlite_begin_tx(hdb);
 return;
}


void NGramsStorage_SQLITE::BeginReadTx(void)
{
 return;
}


void NGramsStorage_SQLITE::CommitTx(void)
{
 if( open_tx==0 )
  throw E_BaseException( L"Can not commit transaction - no one is open" );

 open_tx--;

 lem::sqlite_commit_tx(hdb);
 return;
}

void NGramsStorage_SQLITE::CommitReadTx(void)
{
 return;
}

void NGramsStorage_SQLITE::CommitRetaining(void)
{
 return;
}


void NGramsStorage_SQLITE::CommitCreatedIndeces(void)
{
 return;
}




void NGramsStorage_SQLITE::ExecuteSql( const char *sql, bool check )
{
 lem::sqlite_execute( hdb, sql );
 return;
} 



int NGramsStorage_SQLITE::SelectInt( const lem::FString &Select, int def )
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


int NGramsStorage_SQLITE::SelectInt( const char *Select, int def )
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


std::pair<int,int> NGramsStorage_SQLITE::SelectIntPair( const lem::FString & Select )
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





bool NGramsStorage_SQLITE::TableExists( const lem::FString &table )
{
 bool exists=false;

 if( SelectInt(lem::format_str( "select count(*) from sqlite_master where type='table' and lower(name)='%s'", lem::to_lower(table).c_str() ))==1 )
  exists=true;

 return exists;
}


void NGramsStorage_SQLITE::ExecuteSql( const lem::FString &sql, bool check )
{
 LEM_CHECKIT_Z( !sql.empty() );
 ExecuteSql(sql.c_str(),check);
 return;
}


void NGramsStorage_SQLITE::SetDBCache( int cache_size )
{
 LEM_CHECKIT_Z( cache_size>0 );
 LEM_CHECKIT_Z( hdb!=NULL );

 char buf[100];
 sprintf( buf, "PRAGMA cache_size=%d", cache_size/1024 ); // 1Kb per page

 lem::sqlite_execute( hdb, buf );

 return;
}


bool NGramsStorage_SQLITE::IndexExists( const lem::FString &idx, const lem::FString &table_name )
{
 FString sql = format_str( "SELECT count(*) FROM sqlite_master"
                           " WHERE type='index'"
                           " AND lower(name)='%s'", lem::to_lower(idx).c_str() );

 return SelectInt(sql)==1;
}



void NGramsStorage_SQLITE::DropIndex( const lem::FString &idx, const lem::FString &table_name )
{
 if( IndexExists( idx, table_name ) )
  ExecuteSql( FString("DROP INDEX ")+idx, false );

 return;
}



void NGramsStorage_SQLITE::SelectInts( const lem::FString &Select, lem::MCollect<int> &list )
{
 LEM_CHECKIT_Z( !Select.empty() );

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
}


void NGramsStorage_SQLITE::SelectFStrings( const lem::FString &Select, lem::Collect<lem::FString> &list )
{
 LEM_CHECKIT_Z( !Select.empty() );

 sqlite3_stmt *stmt=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), -1, &stmt, NULL );
 if( res==SQLITE_OK )
  {
   while( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     lem::FString s = lem::sqlite_column_fstring( stmt, 0 );
     list.push_back(s);
    } 

   sqlite3_finalize(stmt);
  }

 return;
}



lem::UFString NGramsStorage_SQLITE::SelectStr( const char *Select )
{
 UFString res;

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

 return res;
}


LS_ResultSet* NGramsStorage_SQLITE::Select( const lem::FString &sql )
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
   throw E_BaseException(msg.string());
  }
}


void NGramsStorage_SQLITE::CreateTable_Words( const lem::FString &suffix )
{
 lem::FString sql = format_str( "CREATE TABLE NGRAM_WORDS%s( word varchar(64) PRIMARY KEY, id integer )", suffix.c_str() );
 ExecuteSql(sql);
 return;
}


void NGramsStorage_SQLITE::CreateTable_NGrams1( const lem::FString &suffix )
{
 char asql[1000];

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

 ExecuteSql(asql);

 sprintf( asql, "CREATE TABLE NGRAM_STATS1%s( "
                "max_w1 integer NOT NULL,"
                "count_n1 integer NOT NULL"
                ")", suffix.c_str() );

 ExecuteSql(asql);

 #if LEM_DEBUGGING==1
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ1_%s ON NGRAM1%s( iword1 )", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);

 sprintf( asql, "CREATE UNIQUE INDEX ngrams_idx12%s ON NGRAM1%s(id)", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif


 return;
}



void NGramsStorage_SQLITE::CreateTable_NGrams2( const lem::FString &suffix )
{
 char asql[1000];

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
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ2_%s ON NGRAM2%s( iword1, iword2 )", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);

 sprintf( asql, "CREATE UNIQUE INDEX ngrams_idx21%s ON NGRAM2%s(id)", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif

 return;
}


void NGramsStorage_SQLITE::CreateTable_NGrams3( const lem::FString &suffix )
{
 char asql[1000];

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
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ3_%s ON NGRAM3%s( iword1, iword2, iword3 )", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);

 sprintf( asql, "CREATE UNIQUE INDEX ngrams_idx31%s ON NGRAM3%s(id)", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif

 return;
}


void NGramsStorage_SQLITE::CreateTable_NGrams4( const lem::FString &suffix )
{
 char asql[1000];

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
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ4_%s ON NGRAM4%s( iword1, iword2, iword3, iword4 )", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);

 sprintf( asql, "CREATE UNIQUE INDEX ngrams_idx41%s ON NGRAM4%s(id)", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif

 return;
}


void NGramsStorage_SQLITE::CreateTable_NGrams5( const lem::FString &suffix )
{
 char asql[1000];

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
 sprintf( asql, "CREATE UNIQUE INDEX NGRAM_UNQ5_%s ON NGRAM5%s( iword1, iword2, iword3, iword4, iword5 )", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);

 sprintf( asql, "CREATE UNIQUE INDEX ngrams_idx51%s ON NGRAM5%s(id)", suffix.c_str(), suffix.c_str() );
 ExecuteSql(asql);
 #endif

 return;
}



int NGramsStorage_SQLITE::MaxBulkInsert(void) const
{
 return 200;
}


lem::FString NGramsStorage_SQLITE::AppendBulkInsert(
                                                    const lem::FString &suffix,
                                                    int counter,
                                                    int id,
                                                    int id_word1,
                                                    int w
                                                   )
{
 lem::FString str;

 if( counter>0 )
  str += " UNION ALL ";

 str += lem::format_str(
                       " SELECT %d,%d,%d" ,
                       id, id_word1, w ); 

 return str;
}


lem::FString NGramsStorage_SQLITE::AppendBulkInsert(
                                                    const lem::FString &suffix,
                                                    int counter,
                                                    int id,
                                                    int id_word1,
                                                    int id_word2,
                                                    int w
                                                   )
{
 #if LEM_DEBUGGING==1
// if( id_word1==5 && id_word2==6 )
//  printf( "id=%d w=%d\n", id, w );
 #endif

 lem::FString str;

 if( counter>0 )
  str += " UNION ALL ";

 str += lem::format_str( " SELECT %d,%d,%d,%d", id, id_word1, id_word2, w );

 return str;
}


lem::FString NGramsStorage_SQLITE::AppendBulkInsert(
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
  str += " UNION ALL ";

 str += lem::format_str(
                       " SELECT %d,%d,%d,%d,%d",
                       id, id_word1, id_word2, id_word3, w ); 

 return str;
}


lem::FString NGramsStorage_SQLITE::AppendBulkInsert(
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
  str += " UNION ALL ";

 str += lem::format_str(
                       " SELECT %d,%d,%d,%d,%d,%d",
                       id, id_word1, id_word2, id_word3, id_word4, w ); 

 return str;
}



lem::FString NGramsStorage_SQLITE::AppendBulkInsert(
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
  str += " UNION ALL ";

 str += lem::format_str(
                       " SELECT %d,%d,%d,%d,%d,%d,%d",
                       id, id_word1, id_word2, id_word3, id_word4, id_word5, w ); 

 return str;
}


void NGramsStorage_SQLITE::UpdateNGrams(
                                        const lem::FString &suffix,
                                        int order, 
                                        const lem::MCollect< std::pair<int,int> > & list
                                       )
{
 char asql_buf[1000];

 sprintf( asql_buf, "UPDATE NGRAM%d%s SET w=w+? WHERE id=?", order, suffix.c_str() );

 sqlite3_stmt *stmt2=NULL;
 int res = sqlite3_prepare_v2( hdb, asql_buf, -1, &stmt2, NULL );
 if( res!=SQLITE_OK )
  {
   const char *errmsg = sqlite3_errmsg(hdb);
   throw E_BaseException( lem::format_str( L"SQLite error %S", errmsg ).c_str() );
  }

 for( lem::Container::size_type i=0; i<list.size(); ++i )
  {
   #if LEM_DEBUGGING==1
   int debug_id_ngram = list[i].first;
   int debug_add_w = list[i].second;
   if( debug_id_ngram==5 )
    {
//     printf( "add_w=%d\n", debug_add_w );
    }
   #endif

   res = sqlite3_bind_int( stmt2, 1, list[i].second );
   res = sqlite3_bind_int( stmt2, 2, list[i].first );
   res = sqlite3_step( stmt2 );

   if( res!=SQLITE_DONE )
    {
     const char *errmsg = sqlite3_errmsg(hdb);
     throw E_BaseException( lem::format_str( L"SQLite error %S", errmsg ).c_str() );
    }

   res = sqlite3_reset(stmt2);
  }

 sqlite3_finalize(stmt2);
 return;
}


void NGramsStorage_SQLITE::CreateTable_Segments(void)
{
 ExecuteSql( "CREATE TABLE NGRAM_SEGMENTS( segment_n varchar(10) NOT NULL, suffix varchar(30) )" );

 ExecuteSql("CREATE UNIQUE INDEX NGRAM_SEGMENTS_UNQ1 ON NGRAM_SEGMENTS(segment_n,suffix)");

 return;
}

lem::FString NGramsStorage_SQLITE::StartBulkInsert( const lem::FString &suffix, int order )
{
 switch( order )
 {
  case 1: return lem::format_str( "INSERT INTO NGRAM1%s( id, iword1, w ) ", suffix.c_str() );
  case 2: return lem::format_str( "INSERT INTO NGRAM2%s( id, iword1, iword2, w ) ", suffix.c_str() );
  case 3: return lem::format_str( "INSERT INTO NGRAM3%s( id, iword1, iword2, iword3, w ) ", suffix.c_str() );
  case 4: return lem::format_str( "INSERT INTO NGRAM4%s( id, iword1, iword2, iword3, iword4, w ) ", suffix.c_str() );
  case 5: return lem::format_str( "INSERT INTO NGRAM5%s( id, iword1, iword2, iword3, iword4, iword5, w ) ", suffix.c_str() );
  default: LEM_STOPIT; return lem::FString();
 }
}

#endif
