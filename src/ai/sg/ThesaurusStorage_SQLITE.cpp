#include <lem/oformatter.h>
#include <lem/unicode.h>
#include <lem/smart_pointers.h>
#include <lem/conversions.h>
#include <lem/sqlite_helpers.h>
#include <lem/solarix/PhraseLink.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>
#include <lem/solarix/LexiconStorage_SQLITE.h>
#include <lem/solarix/TransactionGuard_SQLITE.h>
#include <lem/solarix/ThesaurusStorage_SQLITE.h>

using namespace lem;
using namespace Solarix;

#if defined(LEM_MSC) && _MSC_VER>=1300 && defined(LEM_WINDOWS)
#if LEM_DEBUGGING==1
 # pragma comment ( lib, "sqlited.lib" )
#else
 # pragma comment ( lib, "sqlite.lib" )
#endif
#endif

#if defined LEM_BORLAND
 #pragma comment(lib,"sqlite_bcb6.lib")
#endif


ThesaurusStorage_SQLITE::ThesaurusStorage_SQLITE()
{}


ThesaurusStorage_SQLITE::ThesaurusStorage_SQLITE( const lem::UFString &connection_string )
:sqlite_connection_string(connection_string)
{
 Connect();
 return;
}


ThesaurusStorage_SQLITE::~ThesaurusStorage_SQLITE(void)
{
 Disconnect();
 return; 
}


void ThesaurusStorage_SQLITE::Connect(void)
{
 hdb = lem::sqlite_open_serialized(sqlite_connection_string);
 return;
}


void ThesaurusStorage_SQLITE::Disconnect(void)
{
 if( hdb!=NULL )
  {
   sqlite3_close(hdb);
   hdb=NULL;
  }

 return; 
}


void ThesaurusStorage_SQLITE::BeginTx(void)
{
 sqlite_begin_tx(hdb);
 return;
}

void ThesaurusStorage_SQLITE::CommitTx(void)
{
 sqlite_commit_tx(hdb);
 return;
}

void ThesaurusStorage_SQLITE::RollBackTx(void)
{
 sqlite_rollback_tx(hdb);
 return;
}


TransactionGuard* ThesaurusStorage_SQLITE::GetTxGuard(void)
{
 return new TransactionGuard_SQLITE(hdb);
}



void ThesaurusStorage_SQLITE::CreateSchema(void)
{
 CreateTable_TagSets();
 CreateTable_SG_Tag();
 CreateTable_SG_Tag_Value();
 CreateTables_WordLinks();
 CreateTables_PhraseLinks();

 return;
}


void ThesaurusStorage_SQLITE::CreateTable_TagSets(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"tag_set") )
  { 
   const char create_ddl[] = "CREATE TABLE tag_set( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " tags varchar(256) NOT NULL UNIQUE"
                             ")";

   int res = sqlite3_exec( hdb, create_ddl, NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }

   res = sqlite3_exec( hdb, "INSERT INTO tag_set(id,tags) VALUES (-1,'-')", NULL, NULL, NULL );
   res = sqlite3_exec( hdb, "INSERT INTO tag_set(id,tags) VALUES (0,'')", NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }
   
  }

 return;
}


void ThesaurusStorage_SQLITE::CreateTable_SG_Tag(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"sg_tag") )
  { 
   const char create_ddl[] = "CREATE TABLE sg_tag( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " name varchar(256) NOT NULL UNIQUE"
                             ")";

   int res = sqlite3_exec( hdb, create_ddl, NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }
  }

 return;
}



void ThesaurusStorage_SQLITE::CreateTable_SG_Tag_Value(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"sg_tag_value") )
  { 
   const char create_ddl[] = "CREATE TABLE sg_tag_value( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_tag integer NOT NULL,"
                             " ivalue integer NOT NULL," 
                             " name varchar(256) NOT NULL"
                             ")";

   int res = sqlite3_exec( hdb, create_ddl, NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }

   res = sqlite3_exec( hdb, "CREATE INDEX sg_tag_value_idx1 ON sg_tag_value(id_tag)", NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }
  }

 return;
}


bool ThesaurusStorage_SQLITE::GetTagSet( int id, lem::UFString &tags )
{
 LEM_CHECKIT_Z( id>=0 );
 tags.clear();

 bool ok=false;

 if( id==0 )
  {
   ok=true;
  }
 else
  {
   lem::FString Select( lem::format_str("SELECT tags FROM tag_set WHERE id=%d",id) );
 
   sqlite3_stmt *stmt=NULL;
   const char *dummy=NULL;
   int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
   tags.clear();
   if( res==SQLITE_OK )
    {
     if( sqlite3_step( stmt ) == SQLITE_ROW )
      {
       tags = lem::sqlite_column_ufstring(stmt,0);
       ok=true;
      }
    }
   else
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }

   sqlite3_finalize(stmt);
  }

 return ok;
}


LS_ResultSet* ThesaurusStorage_SQLITE::List_TagSets(void)
{
 lem::FString Select("SELECT id, tags FROM tag_set ORDER BY id");

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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


int ThesaurusStorage_SQLITE::AddTagSet( const lem::UFString &tags )
{
 MemFormatter mem;
 mem.printf("SELECT id FROM tag_set WHERE tags='%us'",tags.c_str());
 lem::FString Select( lem::to_utf8(mem.string()) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   int id=UNKNOWN;

   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     id = sqlite3_column_int(stmt,0);
    }

   sqlite3_finalize(stmt);
   if( id==UNKNOWN )
    {
     lem::MemFormatter ms;
     ms.printf( "INSERT INTO tag_set( tags ) VALUES ( '%us' )", tags.c_str() );

     lem::FString s(lem::to_utf8(ms.string()));
     int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
     if( res!=SQLITE_OK )
      {
       lem::MemFormatter msg;
       msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
       throw E_BaseException(msg.string());
      }
     
     id = (int)sqlite3_last_insert_rowid(hdb);
    }

   return id;
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }
}


void ThesaurusStorage_SQLITE::CopyDatabase( const lem::Path & thesaurus_db_path )
{
 lem::sqlite_vacuum(hdb);

 Disconnect();

 lem::Path sqlite_file = lem::sqlite_get_absolute_filepath(sqlite_connection_string);
 if( sqlite_file.DoesExist() )
  {
   lem::Path::CopyFile( sqlite_file, thesaurus_db_path );
  }

 return;
}


LS_ResultSet* ThesaurusStorage_SQLITE::ListTagDefs(void)
{
 lem::FString Select("SELECT id, name FROM sg_tag ORDER BY id");

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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



void ThesaurusStorage_SQLITE::GetTagName( int id_tag, lem::UCString &name )
{
 LEM_CHECKIT_Z( id_tag>=0 );

 name.clear();

 lem::FString Select( lem::format_str( "SELECT name FROM sg_tag WHERE id=%d", id_tag ) );
 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   int id=UNKNOWN;

   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     name = sqlite_column_ucstring( stmt, 0 );
    }

   sqlite3_finalize(stmt);

   if( name.empty() )
    {
     lem::MemFormatter msg;
     msg.printf( "Cannot find tag with id=%d", id_tag );
     throw E_BaseException( msg.string() );
    }

   return;
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }
}


int ThesaurusStorage_SQLITE::GetTagId( const lem::UCString &tag_name )
{
 lem::MemFormatter s;
 s.printf( "SELECT id FROM sg_tag WHERE name='%us'", lem::to_upper(tag_name).c_str() );
 lem::FString Select( lem::to_utf8(s.string()) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   int id=UNKNOWN;

   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     id = sqlite3_column_int(stmt,0);
    }

   sqlite3_finalize(stmt);

   return id;
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }
}


LS_ResultSet* ThesaurusStorage_SQLITE::List_TagValues( int id_tag )
{
 LEM_CHECKIT_Z( id_tag!=UNKNOWN );

 lem::FString Select( lem::format_str( "SELECT ivalue, name FROM sg_tag_value WHERE id_tag=%d ORDER BY ivalue", id_tag ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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

int ThesaurusStorage_SQLITE::AddTag( const lem::UCString & tag_name )
{
 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_tag( name ) VALUES ( '%us' )", lem::to_upper(tag_name).c_str() );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }
     
 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


int ThesaurusStorage_SQLITE::AddTagValue( int id_tag, int ivalue, const lem::UCString & value_name )
{
 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_tag_value( id_tag, ivalue, name ) VALUES ( %d, %d, '%us' )", id_tag, ivalue, value_name.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }
     
 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


void ThesaurusStorage_SQLITE::CreateTables_WordLinks(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"sg_link") )
  { 
   const char create_ddl1[] = "CREATE TABLE sg_link( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_entry1 integer NOT NULL,"
                             " id_entry2 integer NOT NULL,"
                             " icoord integer," 
                             " istate integer NOT NULL,"
                             " tags integer"
                             ")";

   int res = sqlite3_exec( hdb, create_ddl1, NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }

   res = sqlite3_exec( hdb, "CREATE INDEX sg_link_idx1 ON sg_link(id_entry1)", NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }

   res = sqlite3_exec( hdb, "CREATE INDEX sg_link_idx2 ON sg_link(id_entry2)", NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }
  }

 if( !lem::sqlite_does_table_exist(hdb,"sg_link_tag") )
  { 
   const char create_ddl2[] = "CREATE TABLE sg_link_tag( "
                             " id integer PRIMARY KEY NOT NULL,"
                             " id_link integer NOT NULL,"
                             " id_tag integer NOT NULL,"
                             " ivalue integer NOT NULL" 
                             ")";

   int res = sqlite3_exec( hdb, create_ddl2, NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }

   res = sqlite3_exec( hdb, "CREATE INDEX sg_link_tag_idx1 ON sg_link_tag(id_link)", NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }
  }

 return;
}


void ThesaurusStorage_SQLITE::ReplaceEntryKey( int old_ekey, int new_ekey )
{
 LEM_CHECKIT_Z( old_ekey!=UNKNOWN );
 LEM_CHECKIT_Z( new_ekey!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "UPDATE sg_link SET id_entry1=%d WHERE id_entry1=%d", new_ekey, old_ekey );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 ms.printf( "UPDATE sg_link SET id_entry2=%d WHERE id_entry2=%d", new_ekey, old_ekey );

 s = lem::to_utf8(ms.string());
 res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return;
}

int ThesaurusStorage_SQLITE::CountWordLinks( int optional_link_type )
{
 if( optional_link_type==UNKNOWN || optional_link_type==ANY_STATE )
  {
   lem::FString Select( "SELECT count(*) FROM sg_link" );
   return lem::sqlite_select_int( hdb, Select.c_str() );
  }
 else
  {
   lem::FString Select(lem::format_str( "SELECT count(*) FROM sg_link WHERE istate=%d", optional_link_type ) );
   return lem::sqlite_select_int( hdb, Select.c_str() );
  }
}


LS_ResultSet* ThesaurusStorage_SQLITE::ListWordLinks(void)
{
 lem::FString Select("SELECT id, id_entry1, id_entry2, icoord, istate, tags FROM sg_link");

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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



LS_ResultSet* ThesaurusStorage_SQLITE::ListWordLinks( int ekey1 )
{
 LEM_CHECKIT_Z( ekey1!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, id_entry2, icoord, istate, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry1=%d", ekey1 ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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


LS_ResultSet* ThesaurusStorage_SQLITE::ListWordLinks( int ekey1, int link_type )
{
 LEM_CHECKIT_Z( ekey1!=UNKNOWN );
 LEM_CHECKIT_Z( link_type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, id_entry2, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry1=%d AND istate=%d", ekey1, link_type ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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


LS_ResultSet* ThesaurusStorage_SQLITE::ListWordLinks( int ekey1, const lem::MCollect<int> & link_types )
{
 LEM_CHECKIT_Z( ekey1!=UNKNOWN );

 lem::FString in;

 if( link_types.empty() )
  {
   in.re_clear();
  }
 else if( link_types.size()==1 )
  {
   in = lem::format_str( "AND istate=%d", link_types.front() );
  }
 else
  {
   in="AND istate in (";
   for( lem::Container::size_type i=0; i<link_types.size(); ++i )
    {
     if( i>0 ) in += ",";
     in += lem::to_str( link_types[i] ).c_str();
    }
   in += ")";
  }

 lem::FString Select(lem::format_str( "SELECT id, id_entry2, icoord, istate, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry1=%d %s", ekey1, in.c_str() ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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







LS_ResultSet* ThesaurusStorage_SQLITE::ListWordLinks2( int ekey2 )
{
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, id_entry1, icoord, istate, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry2=%d", ekey2 ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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


LS_ResultSet* ThesaurusStorage_SQLITE::ListWordLinks2( int ekey2, int link_type )
{
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, id_entry1, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry2=%d AND istate=%d", ekey2, link_type ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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


LS_ResultSet* ThesaurusStorage_SQLITE::ListWordLinks2( int ekey2, const lem::MCollect<int> & link_types )
{
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );

 lem::FString in;
 for( lem::Container::size_type i=0; i<link_types.size(); ++i )
  {
   if( !in.empty() ) in += ", ";
   in += lem::to_str( link_types[i] ).c_str();
  }

 lem::FString Select(lem::format_str( "SELECT id, id_entry1, icoord, istate, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry2=%d AND istate in (%s)", ekey2, in.c_str() ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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






int ThesaurusStorage_SQLITE::FindWordLink( int ekey1, int ekey2, int type )
{
 LEM_CHECKIT_Z( ekey1!=UNKNOWN );
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );
 LEM_CHECKIT_Z( type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id FROM sg_link WHERE id_entry1=%d AND id_entry2=%d AND istate=%d",
  ekey1, ekey2, type ) );
 return lem::sqlite_select_int( hdb, Select.c_str() );
}



bool ThesaurusStorage_SQLITE::GetWordLink( int id, WordLink &info )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id_entry1, id_entry2, istate FROM sg_link "
  "WHERE id=%d", id ) );

 bool ok=false;

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     info.id = id;
     info.ekey1 = sqlite3_column_int(stmt,0);
     info.ekey2 = sqlite3_column_int(stmt,1);
     info.link_type = sqlite3_column_int(stmt,2);
     ok = true;
    }
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return ok;
}


int ThesaurusStorage_SQLITE::AddWordLink( int ekey1, int ekey2, int link_type, int id_tag_set )
{
 LEM_CHECKIT_Z( ekey1!=UNKNOWN );
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );
 LEM_CHECKIT_Z( link_type!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_link( id_entry1, id_entry2, icoord, istate, tags )"
  " VALUES ( %d, %d, 0, %d, %d )", ekey1, ekey2, link_type, id_tag_set );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


void ThesaurusStorage_SQLITE::DeleteWordLink( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE sg_link_tag WHERE id_link=%d", id );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 ms.printf( "DELETE sg_link WHERE id=%d", id );

 s = lem::to_utf8(ms.string());
 res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return;
}


int /*id_tag_set*/ ThesaurusStorage_SQLITE::GetWordLinkTags(
                                                            int id_link,
                                                            lem::MCollect< std::pair<int,int> > &atomized_tags
                                                           )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT Coalesce(tags,-1) FROM sg_link WHERE id=%d", id_link ) );

 atomized_tags.clear();

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     int id_tag_set = sqlite3_column_int(stmt,0);

     if( id_tag_set==-1 )
      {
       sqlite3_finalize(stmt);

       lem::FString Select(lem::format_str( "SELECT id_tag, ivalue FROM sg_link_tag "
         "WHERE id_link=%d", id_link ) );

       sqlite3_stmt *stmt=NULL;
       const char *dummy=NULL;
       int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
       if( res==SQLITE_OK )
        {
         lem::Ptr<LS_ResultSet_SQLITE> rs = new LS_ResultSet_SQLITE(stmt);
         while( rs->Fetch() )
          {
           int id_tag = rs->GetInt(0);
           int ivalue = rs->GetInt(1);
           atomized_tags.push_back( std::make_pair(id_tag,ivalue) );
          }    
        }

       return UNKNOWN; 
      }
     else
      {
       sqlite3_finalize(stmt);
       return id_tag_set;
      }      
    }
   else
    {
     sqlite3_finalize(stmt);
     return UNKNOWN;
    }
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }
}


void ThesaurusStorage_SQLITE::SetWordLinkTags( int id_link, int id_tag_set )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE sg_link_tag WHERE id_link=%d", id_link );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 ms.printf( "UPDATE sg_link SET tags=%d WHERE id=%d", id_tag_set, id_link );

 s = lem::to_utf8(ms.string());
 res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return;
}


void ThesaurusStorage_SQLITE::ClearWordLinkTags( int id_link )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE sg_link_tag WHERE id_link=%d", id_link );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 ms.printf( "UPDATE sg_link SET tags=0 WHERE id=%d", id_link );

 s = lem::to_utf8(ms.string());
 res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return;
}


void ThesaurusStorage_SQLITE::CreateTables_PhraseLinks(void)
{
 if( !lem::sqlite_does_table_exist(hdb,"sg_tlink") )
  { 
   // таблица связей между фразами
   const char create_tlinks[] = "CREATE TABLE sg_tlink( "
                                " tl_id integer PRIMARY KEY NOT NULL,"
                                " tl_te_id1 integer NOT NULL,"
                                " tl_te_id2 integer NOT NULL,"
                                " tl_icoord integer NOT NULL,"
                                " tl_istate integer NOT NULL,"
                                " tl_tags integer"
                                ")";

   int res = sqlite3_exec( hdb, create_tlinks, NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }

   // теги
   const char create_tags[]="create table sg_tlink_tag( "
                             "tlt_id integer PRIMARY KEY NOT NULL, "
                             "tlt_tl_id int NOT NULL, "
                             "tlt_id_tag int NOT NULL, "
                             "tlt_ivalue int NOT NULL );";

   res = sqlite3_exec( hdb, create_tags, NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }

   // Дополнительные флаги для связей
   const char create_tlinkflag[] = "CREATE TABLE sg_tlink_flag( "
                                 " tlf_id integer PRIMARY KEY NOT NULL,"
                                 " tlf_tl_id integer NOT NULL,"
                                 " tlf_flag varchar(32) NOT NULL,"
                                 " tlf_value varchar(32) NOT NULL"
                                 ")";

   res = sqlite3_exec( hdb, create_tlinkflag, NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
     throw E_BaseException(msg.string());
    }

   const char* ci[] = {
                       "CREATE UNIQUE INDEX sg_tlink_idx1 ON sg_tlink(tl_id)",
                       "CREATE UNIQUE INDEX sg_tlink_idx2 ON sg_tlink(tl_te_id1,tl_te_id2,tl_istate)",
                       "CREATE INDEX sg_tlink_idx3 ON sg_tlink(tl_te_id1)",
                       "CREATE INDEX sg_tlink_idx4 ON sg_tlink(tl_te_id2)",
                       "CREATE INDEX sg_tlink_flag_idx1 ON sg_tlink_flag(tlf_tl_id)",
                       NULL
                      };

   int i=0;
   while( ci[i]!=NULL )
    {
     res = sqlite3_exec( hdb, ci[i], NULL, NULL, NULL );
     if( res!=SQLITE_OK )
      {
       lem::MemFormatter msg;
       msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
       throw E_BaseException(msg.string());
      }

     i++;
    }
  }

 return;
}



int ThesaurusStorage_SQLITE::CountPhraseLinks( int optional_link_type )
{
 if( optional_link_type==UNKNOWN || optional_link_type==ANY_STATE )
  {
   lem::FString Select( "SELECT count(*) FROM sg_tlink" );
   return lem::sqlite_select_int( hdb, Select.c_str() );
  }
 else
  {
   lem::FString Select(lem::format_str( "SELECT count(*) FROM sg_tlink WHERE tl_istate=%d", optional_link_type ) );
   return lem::sqlite_select_int( hdb, Select.c_str() );
  }
}


LS_ResultSet* ThesaurusStorage_SQLITE::ListPhraseLinks(void)
{
 lem::FString Select( "SELECT tl_id, tl_te_id1, tl_te_id2, tl_icoord, tl_istate, Coalesce(tl_tags,-1) FROM sg_tlink " );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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


LS_ResultSet* ThesaurusStorage_SQLITE::ListPhraseLinks( int id_phrase1 )
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT tl_id, tl_te_id2, tl_icoord, tl_istate, Coalesce(tl_tags,-1) FROM sg_tlink "
  "WHERE tl_te_id1=%d", id_phrase1 ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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



LS_ResultSet* ThesaurusStorage_SQLITE::ListPhraseLinks( int id_phrase1, int link_type )
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT tl_id, tl_te_id2, Coalesce(tl_tags,-1) FROM sg_tlink "
  "WHERE tl_te_id1=%d AND tl_istate=%d", id_phrase1, link_type ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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



LS_ResultSet* ThesaurusStorage_SQLITE::ListPhraseLinks( int id_phrase1, const lem::MCollect<int> & link_types )
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );

 lem::FString in;

 if( link_types.empty() )
  {
   in.re_clear();
  }
 else if( link_types.size()==1 )
  {
   in = lem::format_str( "AND tl_istate=%d", link_types.front() );
  }
 else
  {
   in="AND tl_istate in (";
   for( lem::Container::size_type i=0; i<link_types.size(); ++i )
    {
     if( i>0 ) in += ",";
     in += lem::to_str( link_types[i] ).c_str();
    }
   in += ")";
  }

 lem::FString Select(lem::format_str( "SELECT tl_id, tl_te_id2, tl_icoord, tl_istate, Coalesce(tl_tags,-1) FROM sg_tlink "
  "WHERE tl_te_id1=%d %s", id_phrase1, in.c_str() ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
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






int ThesaurusStorage_SQLITE::FindPhraseLink( int id_phrase1, int id_phrase2, int link_type )
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );
 LEM_CHECKIT_Z( id_phrase2!=UNKNOWN );
 LEM_CHECKIT_Z( link_type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT tl_id FROM sg_tlink WHERE tl_te_id1=%d AND tl_te_id2=%d AND tl_istate=%d",
  id_phrase1, id_phrase2, link_type ) );
 return lem::sqlite_select_int( hdb, Select.c_str() );
}



bool ThesaurusStorage_SQLITE::GetPhraseLink( int id, PhraseLink &info )
{
 lem::FString Select(lem::format_str( "SELECT tl_te_id1, tl_te_id2, tl_istate, Coalesce(tl_tags,-1) FROM sg_tlink "
  "WHERE tl_id=%d", id ) );

 bool ok=false;

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     info.id = id;
     info.id_entry1 = sqlite3_column_int(stmt,0);
     info.id_entry2 = sqlite3_column_int(stmt,1);
     info.link_type = sqlite3_column_int(stmt,2);
     info.id_tags   = sqlite3_column_int(stmt,3);
     ok = true;
    }
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return ok;
}


int ThesaurusStorage_SQLITE::AddPhraseLink( int id_phrase1, int id_phrase2, int link_type, int id_tag_set )
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );
 LEM_CHECKIT_Z( id_phrase2!=UNKNOWN );
 LEM_CHECKIT_Z( link_type!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_tlink( tl_te_id1, tl_te_id2, tl_icoord, tl_istate, tl_tags )"
  " VALUES ( %d, %d, 0, %d, %d )", id_phrase1, id_phrase2, link_type, id_tag_set );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 int id = (int)sqlite3_last_insert_rowid(hdb);
 return id;
}


void ThesaurusStorage_SQLITE::DeletePhraseLink( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE sg_tlink_tag WHERE tlt_tl_id=%d", id );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 ms.printf( "DELETE sg_tlink_flag WHERE tlf_tl_id=%d", id );

 s = lem::to_utf8(ms.string());
 res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 ms.printf( "DELETE sg_tlink WHERE tl_id=%d", id );

 s = lem::to_utf8(ms.string());
 res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return;
}


int /*id_tag_set*/ ThesaurusStorage_SQLITE::GetPhraseLinkTags(
                                                              int id_link,
                                                              lem::MCollect< std::pair<int,int> > &atomized_tags
                                                             )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT Coalesce(tl_tags,-1) FROM sg_tlink WHERE tl_id=%d", id_link ) );

 atomized_tags.clear();

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   if( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     int id_tag_set = sqlite3_column_int(stmt,0);

     if( id_tag_set==-1 )
      {
       sqlite3_finalize(stmt);

       lem::FString Select(lem::format_str( "SELECT tlt_id_tag, tlt_ivalue FROM sg_tlink_tag "
         "WHERE tlt_tl_id=%d", id_link ) );

       sqlite3_stmt *stmt=NULL;
       const char *dummy=NULL;
       int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
       if( res==SQLITE_OK )
        {
         lem::Ptr<LS_ResultSet_SQLITE> rs = new LS_ResultSet_SQLITE(stmt);
         while( rs->Fetch() )
          {
           int id_tag = rs->GetInt(0);
           int ivalue = rs->GetInt(1);
           atomized_tags.push_back( std::make_pair(id_tag,ivalue) );
          }    
        }

       return UNKNOWN; 
      }
     else
      {
       sqlite3_finalize(stmt);
       return id_tag_set;
      }      
    }
   else
    {
     sqlite3_finalize(stmt);
     return UNKNOWN;
    }
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }
}


void ThesaurusStorage_SQLITE::SetPhraseLinkTags( int id_link, int id_tag_set )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );
 LEM_CHECKIT_Z( id_tag_set==UNKNOWN || id_tag_set>=0 );

 lem::MemFormatter ms;

 ms.printf( "DELETE sg_tlink_tag WHERE tlt_tl_id=%d", id_link );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 ms.printf( "UPDATE sg_tlink SET tl_tags=%d WHERE tl_id=%d", id_tag_set, id_link );

 s = lem::to_utf8(ms.string());
 res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return;
}


void ThesaurusStorage_SQLITE::ClearPhraseLinkTags( int id_link )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE sg_tlink_tag WHERE tlt_tl_id=%d", id_link );

 lem::FString s(lem::to_utf8(ms.string()));
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 ms.printf( "UPDATE sg_tlink SET tl_tags=0 WHERE tl_id=%d", id_link );

 s = lem::to_utf8(ms.string());
 res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return;
}






void ThesaurusStorage_SQLITE::GetPhraseFlags( int id_phrase, lem::PtrCollect<SG_LinkFlag> &flags )
{
 LEM_CHECKIT_Z( id_phrase!=UNKNOWN );

 FString Select( lem::format_str(
    "SELECT tlf_id, tlf_flag, tlf_value"
    " FROM sg_tlink_flag"
    " WHERE tlf_tl_id=%d", id_phrase ) );

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   while( sqlite3_step( stmt ) == SQLITE_ROW )
    {
     const int tlf_id = sqlite3_column_int(stmt,0);
     UFString tl_flag( lem::sqlite_column_ufstring(stmt,1) );
     UFString tl_value( lem::sqlite_column_ufstring(stmt,2) );

     SG_LinkFlag *x = new SG_LinkFlag(tlf_id,tl_flag,tl_value);
     flags.push_back(x);
    }

   sqlite3_finalize(stmt);
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return;
}


void ThesaurusStorage_SQLITE::ClearPhraseLinkFlags( int id_link )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 FString s( lem::format_str( "DELETE FROM sg_tlink_flag WHERE tlf_tl_id=%d", id_link ) );

 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 return;
}


int ThesaurusStorage_SQLITE::AddPhraseLinkFlag( int id_link, const lem::UCString &flag, const lem::UCString &value )
{
 FString a(lem::to_utf8(flag.c_str()));
 sqlite_escape(a);

 FString b(lem::to_utf8(value.c_str()));
 sqlite_escape(b);

 lem::FString s( lem::format_str( "INSERT INTO sg_tlink_flag( tlf_tl_id, tlf_flag, tlf_value )"
      " VALUES ( %d, '%s', '%s' )", id_link, a.c_str(), b.c_str() ) );
 int res = sqlite3_exec( hdb, s.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw E_BaseException(msg.string());
  }

 int tlf_id = (int)sqlite3_last_insert_rowid(hdb);
 return tlf_id;
}
