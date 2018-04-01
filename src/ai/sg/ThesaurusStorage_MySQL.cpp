#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/oformatter.h>
#include <lem/unicode.h>
#include <lem/smart_pointers.h>
#include <lem/conversions.h>
#include <lem/mysql_helpers.h>
#include <lem/solarix/PhraseLink.h>
#include <lem/solarix/PhraseEntries.h>
#include <lem/solarix/StorageConnection_MySQL.h>
#include <lem/solarix/LexiconStorage_MySQL.h>
#include <lem/solarix/TransactionGuard_MySQL.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/MySQLCnx.h>
#include <lem/solarix/ThesaurusStorage_MySQL.h>

using namespace lem;
using namespace Solarix;


#define NEVER_RETURNS(x) return x;


ThesaurusStorage_MySQL::ThesaurusStorage_MySQL()
{}


ThesaurusStorage_MySQL::ThesaurusStorage_MySQL( StorageConnection_MySQL *_cnx )
:cnx(_cnx)
{
 Connect();
 return;
}


ThesaurusStorage_MySQL::~ThesaurusStorage_MySQL(void)
{
 Disconnect();
 return; 
}


void ThesaurusStorage_MySQL::Connect(void)
{
 return;
}


void ThesaurusStorage_MySQL::Disconnect(void)
{
 cnx->Release();
 return; 
}


void ThesaurusStorage_MySQL::BeginTx(void)
{
 cnx->BeginTx();
 return;
}

void ThesaurusStorage_MySQL::CommitTx(void)
{
 cnx->CommitTx();
 return;
}

void ThesaurusStorage_MySQL::RollBackTx(void)
{
 cnx->RollbackTx();
 return;
}


TransactionGuard* ThesaurusStorage_MySQL::GetTxGuard(void)
{
 return new TransactionGuard_MySQL(cnx);
}



bool ThesaurusStorage_MySQL::GetTagSet( int id, lem::UFString &tags )
{
 LEM_CHECKIT_Z( id>=0 );
 tags.clear();

 lem::FString Select( lem::format_str("SELECT tags FROM tag_set WHERE id=%d",id) );

 bool ok=false;
 
 tags.clear();

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( c->mysql, Select.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       tags = lem::mysql_column_ufstring(row,0);
       ok=true;
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return ok;
}


LS_ResultSet* ThesaurusStorage_MySQL::List_TagSets(void)
{
 lem::FString Select("SELECT id, tags FROM tag_set ORDER BY id");

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}


int ThesaurusStorage_MySQL::AddTagSet( const lem::UFString &tags )
{
 MemFormatter mem;
 mem.printf("SELECT id FROM tag_set WHERE tags='%us'",tags.c_str());
 lem::FString Select( lem::to_utf8(mem.string()) );

 int id=UNKNOWN;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       id = lem::mysql_column_int(row,0);
      }

     mysql_free_result(res);
    }

   if( id==UNKNOWN )
    {
     lem::MemFormatter ms;
     ms.printf( "INSERT INTO tag_set( tags ) VALUES ( '%us' )", tags.c_str() );

     lem::FString s(lem::to_utf8(ms.string()));
     cnx->Execute(s);
     id = cnx->GetLastId();
    }

   return id;
  }
 else
  {
   cnx->Error(Select);
   NEVER_RETURNS(-1);
  }
}


void ThesaurusStorage_MySQL::CopyDatabase( const lem::Path & thesaurus_db_path )
{
 LEM_STOPIT;
 return;
}


LS_ResultSet* ThesaurusStorage_MySQL::ListTagDefs(void)
{
 lem::FString Select("SELECT id, name FROM sg_tag ORDER BY id");

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}



void ThesaurusStorage_MySQL::GetTagName( int id_tag, lem::UCString &name )
{
 LEM_CHECKIT_Z( id_tag>=0 );

 name.clear();
 lem::FString Select( lem::format_str( "SELECT name FROM sg_tag WHERE id=%d", id_tag ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       name = lem::mysql_column_ucstring( row, 0 );
      }

     mysql_free_result(res);
    }

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
   cnx->Error(Select);
  }
}


int ThesaurusStorage_MySQL::GetTagId( const lem::UCString &tag_name )
{
 lem::MemFormatter s;
 s.printf( "SELECT id FROM sg_tag WHERE name='%us'", lem::to_upper(tag_name).c_str() );
 lem::FString Select( lem::to_utf8(s.string()) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int id = lem::mysql_select_int(c->mysql,Select.c_str());
 return id;
}


LS_ResultSet* ThesaurusStorage_MySQL::List_TagValues( int id_tag )
{
 LEM_CHECKIT_Z( id_tag!=UNKNOWN );

 lem::FString Select( lem::format_str( "SELECT ivalue, name FROM sg_tag_value WHERE id_tag=%d ORDER BY ivalue", id_tag ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }  

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}


int ThesaurusStorage_MySQL::AddTag( const lem::UCString & tag_name )
{
 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_tag( name ) VALUES ( '%us' )", lem::to_upper(tag_name).c_str() );

 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);     
 int id = cnx->GetLastId();
 return id;
}


int ThesaurusStorage_MySQL::AddTagValue( int id_tag, int ivalue, const lem::UCString & value_name )
{
 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_tag_value( id_tag, ivalue, name ) VALUES ( %d, %d, '%us' )", id_tag, ivalue, value_name.c_str() );

 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);
 int id = cnx->GetLastId();
 return id;
}




void ThesaurusStorage_MySQL::ReplaceEntryKey( int old_ekey, int new_ekey )
{
 LEM_CHECKIT_Z( old_ekey!=UNKNOWN );
 LEM_CHECKIT_Z( new_ekey!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "UPDATE sg_link SET id_entry1=%d WHERE id_entry1=%d", new_ekey, old_ekey );

 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 ms.printf( "UPDATE sg_link SET id_entry2=%d WHERE id_entry2=%d", new_ekey, old_ekey );
 s = lem::to_utf8(ms.string());
 cnx->Execute(s);
 return;
}


int ThesaurusStorage_MySQL::CountWordLinks( int optional_link_type )
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 if( optional_link_type==UNKNOWN || optional_link_type==ANY_STATE )
  {
   return lem::mysql_select_int( c->mysql, "SELECT count(*) FROM sg_link" );
  }
 else
  {
   lem::FString Select(lem::format_str( "SELECT count(*) FROM sg_link WHERE istate=%d", optional_link_type ) );
   return lem::mysql_select_int( c->mysql, Select.c_str() );
  }
}


LS_ResultSet* ThesaurusStorage_MySQL::ListWordLinks(void)
{
 lem::FString Select("SELECT id, id_entry1, id_entry2, icoord, istate, tags FROM sg_link");

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}



LS_ResultSet* ThesaurusStorage_MySQL::ListWordLinks( int ekey1 )
{
 LEM_CHECKIT_Z( ekey1!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, id_entry2, icoord, istate, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry1=%d", ekey1 ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());
 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }
 
 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}


LS_ResultSet* ThesaurusStorage_MySQL::ListWordLinks( int ekey1, int link_type )
{
 LEM_CHECKIT_Z( ekey1!=UNKNOWN );
 LEM_CHECKIT_Z( link_type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, id_entry2, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry1=%d AND istate=%d", ekey1, link_type ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());
 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}


LS_ResultSet* ThesaurusStorage_MySQL::ListWordLinks( int ekey1, const lem::MCollect<int> & link_types )
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

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}





LS_ResultSet* ThesaurusStorage_MySQL::ListWordLinks2( int ekey2 )
{
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, id_entry1, icoord, istate, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry2=%d", ekey2 ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}


LS_ResultSet* ThesaurusStorage_MySQL::ListWordLinks2( int ekey2, int link_type )
{
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id, id_entry1, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry2=%d AND istate=%d", ekey2, link_type ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}


LS_ResultSet* ThesaurusStorage_MySQL::ListWordLinks2( int ekey2, const lem::MCollect<int> & link_types )
{
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );

 if( link_types.empty() )
  return ListWordLinks2(ekey2);
 else if( link_types.size()==1 )
  return ListWordLinks2(ekey2,link_types.front());

 lem::FString in;
 for( lem::Container::size_type i=0; i<link_types.size(); ++i )
  {
   if( !in.empty() ) in += ", ";
   in += lem::to_str( link_types[i] ).c_str();
  }

 lem::FString Select(lem::format_str( "SELECT id, id_entry1, icoord, istate, Coalesce(tags,-1) FROM sg_link "
  "WHERE id_entry2=%d AND istate in (%s)", ekey2, in.c_str() ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}






int ThesaurusStorage_MySQL::FindWordLink( int ekey1, int ekey2, int type )
{
 LEM_CHECKIT_Z( ekey1!=UNKNOWN );
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );
 LEM_CHECKIT_Z( type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id FROM sg_link WHERE id_entry1=%d AND id_entry2=%d AND istate=%d",
  ekey1, ekey2, type ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 return lem::mysql_select_int( c->mysql, Select.c_str() );
}



bool ThesaurusStorage_MySQL::GetWordLink( int id, WordLink &info )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT id_entry1, id_entry2, istate FROM sg_link "
  "WHERE id=%d", id ) );

 bool ok=false;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( c->mysql, Select.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       info.id = id;
       info.ekey1 = lem::mysql_column_int(row,0);
       info.ekey2 = mysql_column_int(row,1);
       info.link_type = mysql_column_int(row,2);
       ok = true;
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return ok;
}


int ThesaurusStorage_MySQL::AddWordLink( int ekey1, int ekey2, int link_type, int id_tag_set )
{
 LEM_CHECKIT_Z( ekey1!=UNKNOWN );
 LEM_CHECKIT_Z( ekey2!=UNKNOWN );
 LEM_CHECKIT_Z( link_type!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_link( id_entry1, id_entry2, icoord, istate, tags )"
  " VALUES ( %d, %d, 0, %d, %d )", ekey1, ekey2, link_type, id_tag_set );

 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);
 int id = cnx->GetLastId();
 return id;
}


void ThesaurusStorage_MySQL::DeleteWordLink( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE FROM sg_link_tag WHERE id_link=%d", id );

 lem::FString s(lem::to_utf8(ms.string()));
 cnx->Execute(s);

 ms.printf( "DELETE FROM sg_link WHERE id=%d", id );
 s = lem::to_utf8(ms.string());

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 return;
}


int /*id_tag_set*/ ThesaurusStorage_MySQL::GetWordLinkTags(
                                                           int id_link,
                                                           lem::MCollect< std::pair<int,int> > &atomized_tags
                                                          )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT Coalesce(tags,-1) FROM sg_link WHERE id=%d", id_link ) );

 atomized_tags.clear();

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( c->mysql, Select.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     int id_tag_set=UNKNOWN;

     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       id_tag_set = lem::mysql_column_int(row,0);
      }

     if( id_tag_set==-1 )
      {
       mysql_free_result(res);

       lem::FString Select(lem::format_str( "SELECT id_tag, ivalue FROM sg_link_tag "
         "WHERE id_link=%d", id_link ) );

       int rc = mysql_query( c->mysql, Select.c_str() );
       if( rc==0 )
        {
         MYSQL_RES *res = mysql_store_result(c->mysql);
         if( res!=NULL )
          {
           #if defined LEM_THREADS
           c->cs.Enter();
           #endif
 
           lem::Ptr<LS_ResultSet_MySQL> rs = new LS_ResultSet_MySQL(c,res,NULL);
           while( rs->Fetch() )
            {
             int id_tag = rs->GetInt(0);
             int ivalue = rs->GetInt(1);
             atomized_tags.push_back( std::make_pair(id_tag,ivalue) );
            }
          }
        }

       return UNKNOWN; 
      }
     else
      {
       mysql_free_result(res);
       return id_tag_set;
      }      
    }
   else
    {
     mysql_free_result(res);
     return UNKNOWN;
    }
  }
 else
  {
   cnx->Error(Select);
   NEVER_RETURNS(NULL);
  }
}


void ThesaurusStorage_MySQL::SetWordLinkTags( int id_link, int id_tag_set )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE FROM sg_link_tag WHERE id_link=%d", id_link );
 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 ms.printf( "UPDATE sg_link SET tags=%d WHERE id=%d", id_tag_set, id_link );
 s = lem::to_utf8(ms.string());
 cnx->Execute(s);

 return;
}


void ThesaurusStorage_MySQL::ClearWordLinkTags( int id_link )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE FROM sg_link_tag WHERE id_link=%d", id_link );

 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 ms.printf( "UPDATE sg_link SET tags=0 WHERE id=%d", id_link );
 s = lem::to_utf8(ms.string());
 cnx->Execute(s);
 
 return;
}



int ThesaurusStorage_MySQL::CountPhraseLinks( int optional_link_type )
{
 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 if( optional_link_type==UNKNOWN || optional_link_type==ANY_STATE )
  {
   return lem::mysql_select_int( c->mysql, "SELECT count(*) FROM sg_tlink" );
  }
 else
  {
   lem::FString Select(lem::format_str( "SELECT count(*) FROM sg_tlink WHERE tl_istate=%d", optional_link_type ) );
   return lem::mysql_select_int( c->mysql, Select.c_str() );
  }
}


LS_ResultSet* ThesaurusStorage_MySQL::ListPhraseLinks(void)
{
 lem::FString Select( "SELECT tl_id, tl_te_id1, tl_te_id2, tl_icoord, tl_istate, Coalesce(tl_tags,-1) FROM sg_tlink " );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());
 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}


LS_ResultSet* ThesaurusStorage_MySQL::ListPhraseLinks( int id_phrase1 )
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT tl_id, tl_te_id2, tl_icoord, tl_istate, Coalesce(tl_tags,-1) FROM sg_tlink "
  "WHERE tl_te_id1=%d", id_phrase1 ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());
 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}



LS_ResultSet* ThesaurusStorage_MySQL::ListPhraseLinks( int id_phrase1, int link_type )
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT tl_id, tl_te_id2, Coalesce(tl_tags,-1) FROM sg_tlink "
  "WHERE tl_te_id1=%d AND tl_istate=%d", id_phrase1, link_type ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());
 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }    
  }
 
 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}



LS_ResultSet* ThesaurusStorage_MySQL::ListPhraseLinks( int id_phrase1, const lem::MCollect<int> & link_types )
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

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());
 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     return new LS_ResultSet_MySQL(c,res,read_tx.release());
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 NEVER_RETURNS(NULL);
}






int ThesaurusStorage_MySQL::FindPhraseLink( int id_phrase1, int id_phrase2, int link_type )
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );
 LEM_CHECKIT_Z( id_phrase2!=UNKNOWN );
 LEM_CHECKIT_Z( link_type!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT tl_id FROM sg_tlink WHERE tl_te_id1=%d AND tl_te_id2=%d AND tl_istate=%d",
  id_phrase1, id_phrase2, link_type ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 return lem::mysql_select_int( c->mysql, Select.c_str() );
}



bool ThesaurusStorage_MySQL::GetPhraseLink( int id, PhraseLink &info )
{
 lem::FString Select(lem::format_str( "SELECT tl_te_id1, tl_te_id2, tl_istate, Coalesce(tl_tags,-1) FROM sg_tlink "
  "WHERE tl_id=%d", id ) );

 bool ok=false;

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( c->mysql, Select.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       info.id = id;
       info.id_entry1 = lem::mysql_column_int(row,0);
       info.id_entry2 = lem::mysql_column_int(row,1);
       info.link_type = lem::mysql_column_int(row,2);
       info.id_tags   = lem::mysql_column_int(row,3);
       ok = true;
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return ok;
}


int ThesaurusStorage_MySQL::AddPhraseLink( int id_phrase1, int id_phrase2, int link_type, int id_tag_set )
{
 LEM_CHECKIT_Z( id_phrase1!=UNKNOWN );
 LEM_CHECKIT_Z( id_phrase2!=UNKNOWN );
 LEM_CHECKIT_Z( link_type!=UNKNOWN );

 lem::MemFormatter ms;
 ms.printf( "INSERT INTO sg_tlink( tl_te_id1, tl_te_id2, tl_icoord, tl_istate, tl_tags )"
  " VALUES ( %d, %d, 0, %d, %d )", id_phrase1, id_phrase2, link_type, id_tag_set );

 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);
 int id = cnx->GetLastId();
 return id;
}


void ThesaurusStorage_MySQL::DeletePhraseLink( int id )
{
 LEM_CHECKIT_Z( id!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE FROM sg_tlink_tag WHERE tlt_tl_id=%d", id );
 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 ms.printf( "DELETE FROM sg_tlink_flag WHERE tlf_tl_id=%d", id );
 s = lem::to_utf8(ms.string());
 cnx->Execute(s);
 
 ms.printf( "DELETE FROM sg_tlink WHERE tl_id=%d", id );
 s = lem::to_utf8(ms.string());
 cnx->Execute(s);

 return;
}


int /*id_tag_set*/ ThesaurusStorage_MySQL::GetPhraseLinkTags(
                                                             int id_link,
                                                             lem::MCollect< std::pair<int,int> > &atomized_tags
                                                            )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::FString Select(lem::format_str( "SELECT Coalesce(tl_tags,-1) FROM sg_tlink WHERE tl_id=%d", id_link ) );

 atomized_tags.clear();

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( c->mysql, Select.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       int id_tag_set = lem::mysql_column_int(row,0);

       if( id_tag_set==-1 )
        {
         mysql_free_result(res);

         lem::FString Select(lem::format_str( "SELECT tlt_id_tag, tlt_ivalue FROM sg_tlink_tag "
           "WHERE tlt_tl_id=%d", id_link ) );

         rc = mysql_query( c->mysql, Select.c_str() );
         if( rc==0 )
          {
           MYSQL_RES *res = mysql_store_result( c->mysql );
           if( res!=NULL )
            {
             #if defined LEM_THREADS
             c->cs.Enter();
             #endif
             lem::Ptr<LS_ResultSet_MySQL> rs = new LS_ResultSet_MySQL(c,res,NULL);
             while( rs->Fetch() )
              {
               int id_tag = rs->GetInt(0);
               int ivalue = rs->GetInt(1);
               atomized_tags.push_back( std::make_pair(id_tag,ivalue) );
              }
            }
          }
         else
          {
           cnx->Error(Select);
          }
     
         return UNKNOWN; 
        }
       else
        {
         mysql_free_result(res);
         return id_tag_set;
        }
      }
     else
      {
       mysql_free_result(res);
       return UNKNOWN;
      }
    }
   else
    {
     return UNKNOWN;
    } 
  }
 else
  {
   cnx->Error(Select);
   NEVER_RETURNS(-1);
  }
}


void ThesaurusStorage_MySQL::SetPhraseLinkTags( int id_link, int id_tag_set )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );
 LEM_CHECKIT_Z( id_tag_set==UNKNOWN || id_tag_set>=0 );

 lem::MemFormatter ms;

 ms.printf( "DELETE FROM sg_tlink_tag WHERE tlt_tl_id=%d", id_link );
 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 ms.printf( "UPDATE sg_tlink SET tl_tags=%d WHERE tl_id=%d", id_tag_set, id_link );
 s = lem::to_utf8(ms.string());
 cnx->Execute(s);

 return;
}


void ThesaurusStorage_MySQL::ClearPhraseLinkTags( int id_link )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 lem::MemFormatter ms;

 ms.printf( "DELETE FROM sg_tlink_tag WHERE tlt_tl_id=%d", id_link );
 lem::FString s(lem::to_utf8(ms.string()));

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 ms.printf( "UPDATE sg_tlink SET tl_tags=0 WHERE tl_id=%d", id_link );
 s = lem::to_utf8(ms.string());
 cnx->Execute(s);

 return;
}






void ThesaurusStorage_MySQL::GetPhraseFlags( int id_phrase, lem::PtrCollect<SG_LinkFlag> &flags )
{
 LEM_CHECKIT_Z( id_phrase!=UNKNOWN );

 FString Select( lem::format_str(
    "SELECT tlf_id, tlf_flag, tlf_value"
    " FROM sg_tlink_flag"
    " WHERE tlf_tl_id=%d", id_phrase ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( c->mysql, Select.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result( c->mysql );
   if( res!=NULL )
    {
     MYSQL_ROW row;
     while( (row = mysql_fetch_row(res))!=NULL )
      {
       const int tlf_id = lem::mysql_column_int(row,0);
       UFString tl_flag( lem::mysql_column_ufstring(row,1) );
       UFString tl_value( lem::mysql_column_ufstring(row,2) );

       SG_LinkFlag *x = new SG_LinkFlag(tlf_id,tl_flag,tl_value);
       flags.push_back(x);
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(Select);
  }

 return;
}


void ThesaurusStorage_MySQL::ClearPhraseLinkFlags( int id_link )
{
 LEM_CHECKIT_Z( id_link!=UNKNOWN );

 FString s( lem::format_str( "DELETE FROM sg_tlink_flag WHERE tlf_tl_id=%d", id_link ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);

 return;
}


int ThesaurusStorage_MySQL::AddPhraseLinkFlag( int id_link, const lem::UCString &flag, const lem::UCString &value )
{
 FString a(lem::to_utf8(flag.c_str()));
 lem::mysql_escape(a);

 FString b(lem::to_utf8(value.c_str()));
 lem::mysql_escape(b);

 lem::FString s( lem::format_str( "INSERT INTO sg_tlink_flag( tlf_tl_id, tlf_flag, tlf_value )"
      " VALUES ( %d, '%s', '%s' )", id_link, a.c_str(), b.c_str() ) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&c->cs);
 #endif

 cnx->Execute(s);
 int tlf_id = cnx->GetLastId();
 return tlf_id;
}

void ThesaurusStorage_MySQL::CreateSchema(void)
{
}

#endif
