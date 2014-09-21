#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/mysql_helpers.h>
#include <lem/conversions.h>
#include <lem/oformatter.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/StorageConnection_MySQL.h>
#include <lem/solarix/Charpos2EntryEnumerator_SQL.h>
#include <lem/solarix/MySQLCnx.h>
#include <lem/solarix/Charpos2EntryStorage_MySQL.h>
 
using namespace Solarix;

Charpos2EntryStorage_MySQL::Charpos2EntryStorage_MySQL( StorageConnection_MySQL *_cnx )
: cnx(_cnx)
{
 return;
}


Charpos2EntryStorage_MySQL::~Charpos2EntryStorage_MySQL(void)
{
 cnx->Release();
 return;
}

void Charpos2EntryStorage_MySQL::ClearCharpos( lem::uint32_t c, int pos )
{
 const lem::uint32_t charpos = c | (pos<<24);

 lem::FString sql( lem::format_str( "DELETE FROM charpos2entry WHERE charpos=%u", charpos ) );

 cnx->Execute(sql);

 return;
}

void Charpos2EntryStorage_MySQL::Store( lem::uint32_t c, int pos, const std::set<int> &ies )
{
 const lem::uint32_t charpos = c | (pos<<24);

 lem::FString str_ies;
 str_ies.reserve(1000000);

 lem::MemFormatter mem;

 int key0=-1;
 for( std::set<int>::const_iterator k=ies.begin(); k!=ies.end(); ++k )
  {
   const int keyi = *k;
   if( key0==-1 )
    {
     str_ies.Add_Dirty( lem::to_str(keyi).c_str() );
    }
   else
    {
     str_ies.Add_Dirty( ' ' );
     str_ies.Add_Dirty( lem::to_str(keyi-key0).c_str() );
    }

   key0 = keyi;
  }

 mem.printf( "INSERT INTO charpos2entry(charpos,ies) VALUES (%ud,'%s')", charpos, str_ies.c_str() );
 cnx->Execute( lem::to_utf8(mem.string()) );

 return;
}

static int Digit2Int( char c )
{ return c-'0'; }


void Charpos2EntryStorage_MySQL::Get( lem::uint32_t c, int pos, std::set<int> &ies )
{
 ies.clear();

 const lem::uint32_t charpos = c | (pos<<24);

 lem::FString sql( lem::format_str( "SELECT ies FROM charpos2entry WHERE charpos=%u", charpos ).c_str() );

 MySQLCnx *cx = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cx->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( cx->mysql, sql.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result(cx->mysql);
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       const char *str = row[0];

       int key0=-1;
    
       int icur=0, itok=0;
       char tok[32];
    
       while( str[icur]!=0 )
        {
         if( str[icur]==' ' )
          icur++;
    
         if( str[icur]==0 )
          break;
    
         // собираем символы до пробела или конца строки
         itok=0;
         while( str[icur]!=' ' && str[icur]!=0 )
          {
           tok[itok++] = str[icur++];
          }
 
         if( itok==0 )
          break;
       
         tok[itok]=0;
    
         int keyi;
    
         const int x = itok==1 ? Digit2Int(*tok) : lem::to_int(tok);
         if( key0==-1 )
          {
           keyi=x;
          }
         else
          {
           keyi = key0+x;
          }
    
         key0 = keyi;
    
         ies.insert(keyi);
        }
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(sql);
  }


 return;
}

void Charpos2EntryStorage_MySQL::GetIntersected(
                                                 lem::uint32_t c,
                                                 int pos,
                                                 const std::set<int> &ies0,
                                                 std::set<int> &ies
                                                )
{
 const lem::uint32_t charpos = c | (pos<<24);

 lem::FString sql( lem::format_str( "SELECT ies FROM charpos2entry WHERE charpos=%u", charpos ).c_str() );

 MySQLCnx *cx = cnx->GetDb();
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cx->cs);
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( cx->mysql, sql.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result(cx->mysql);
   if( res!=NULL )
    {
     MYSQL_ROW row = mysql_fetch_row(res);
     if( row )
      {
       const char *str = row[0];

       int key0=-1;
    
       int icur=0, itok=0;
       char tok[32];
    
       while( str[icur]!=0 )
        {
         if( str[icur]==' ' )
          icur++;
    
         if( str[icur]==0 )
          break;
    
         // собираем символы до пробела или конца строки
         itok=0;
         while( str[icur]!=' ' && str[icur]!=0 )
          {
           tok[itok++] = str[icur++];
          }

         if( itok==0 )
          break;
        
         tok[itok]=0;
    
         int keyi;
    
         const int x = itok==1 ? Digit2Int(*tok) : lem::to_int(tok);
         if( key0==-1 )
          {
           keyi=x;
          }
         else
          {
           keyi = key0+x;
          }
    
         key0 = keyi;
    
         if( ies0.find(keyi)!=ies0.end() )
          ies.insert(keyi);
        }
      }

     mysql_free_result(res);
    }
  }
 else
  {
   cnx->Error(sql);
  }

 return;
}


Charpos2EntryEnumerator* Charpos2EntryStorage_MySQL::Enumerate(void)
{
 lem::FString Select("SELECT charpos FROM charpos2entry");

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::auto_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int ok = mysql_query( c->mysql, Select.c_str() );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=NULL )
    {
     return new Charpos2EntryEnumerator_SQL( new LS_ResultSet_MySQL(c,res,read_tx.release()) );
    }
  }

 #if defined LEM_THREADS
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 return NULL;
}


void Charpos2EntryStorage_MySQL::BeginTx(void)
{
 cnx->BeginTx();
 return;
}

void Charpos2EntryStorage_MySQL::CommitTx(void)
{
 cnx->CommitTx();
 return;
}

#endif
