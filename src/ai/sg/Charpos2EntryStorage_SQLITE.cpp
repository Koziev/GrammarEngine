#include <lem/sqlite_helpers.h>
#include <lem/oformatter.h>
#include <lem/conversions.h>
#include <lem/solarix/LS_ResultSet_SQLITE.h>
#include <lem/solarix/Charpos2EntryEnumerator_SQL.h>
#include <lem/solarix/Charpos2EntryStorage_SQLITE.h>
 
using namespace Solarix;

Charpos2EntryStorage_SQLITE::Charpos2EntryStorage_SQLITE( const lem::UFString &connection_string )
: sqlite_connection_string(connection_string)
{
 hdb = lem::sqlite_open_serialized(connection_string);

 if( !lem::sqlite_does_table_exist(hdb,"charpos2entry") )
  { 
   const char create_t1[] = "CREATE TABLE charpos2entry( charpos unsigned int PRIMARY KEY NOT NULL, ies varchar(1000000) NOT NULL)";
   int res = sqlite3_exec( hdb, create_t1, NULL, NULL, NULL );
   if( res!=SQLITE_OK )
    {
     lem::MemFormatter msg;
     msg.printf( "Can not create SQLite table charpos2entry, error=%d message=%us"
                 , res, lem::sqlite_errmsg(hdb).c_str() );
     throw lem::E_BaseException( msg.string() );
    }
  }

  /*
// --- debug
printf( "DEBUG 1\n" );
lem::sqlite_begin_tx(hdb);
printf( "DEBUG 2\n" );
sqlite3_exec( hdb, "INSERT INTO charpos2entry( charpos, ies ) VALUES ( 33, '12345677888 2 3 4 '5 )", NULL, NULL, NULL );
lem::sqlite_commit_tx(hdb);
printf( "DEBUG 3\n" );  
// ----- end
*/

 return;
}


Charpos2EntryStorage_SQLITE::~Charpos2EntryStorage_SQLITE(void)
{
 if( hdb!=NULL )
  {
   sqlite3_close(hdb);
   hdb=NULL;
  }

 return;
}

void Charpos2EntryStorage_SQLITE::ClearCharpos( lem::uint32_t c, int pos )
{
 const lem::uint32_t charpos = c | (pos<<24);

 lem::FString sql( lem::format_str( "DELETE FROM charpos2entry WHERE charpos=%u", charpos ) );

 int res = sqlite3_exec( hdb, sql.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "Can not execute SQLite statement %s, message=%us", sql.c_str(), lem::sqlite_errmsg(hdb).c_str() );
   throw lem::E_BaseException( msg.string() );
  }

 return;
}

void Charpos2EntryStorage_SQLITE::Store( lem::uint32_t c, int pos, const std::set<int> &ies )
{
 const lem::uint32_t charpos = c | (pos<<24);

 lem::FString str_ies;
 str_ies.reserve(100000);


 int key0=-1;
 for( std::set<int>::const_iterator k=ies.begin(); k!=ies.end(); ++k )
  {
   const int keyi = *k;
   if( key0==-1 )
    {
     str_ies += lem::to_str(keyi).c_str();
    }
   else
    {
     str_ies += ' ';
     str_ies += lem::to_str(keyi-key0).c_str();
    }

   key0 = keyi;
  }


/*
 // --------------------------------------------------------------------
 int key0=-1;
 int n1=0;
 for( std::set<int>::const_iterator k=ies.begin(); k!=ies.end(); ++k )
  {
   const int keyi = *k;
   if( key0==-1 )
    {
     str_ies.Add_Dirty( lem::to_str(keyi).c_str() );
    }
   else
    {
     if( (keyi-key0)==1 )
      {
       n1++;
      }
     else
      {
       if( n1>0 )
        {
         str_ies.Add_Dirty( lem::format_str( " *%d", n1 ).c_str() );
         n1=0;
        }

       str_ies.Add_Dirty( ' ' );
       str_ies.Add_Dirty( lem::to_str(keyi-key0).c_str() );
      }
    }

   key0 = keyi;
  }

 if( n1>0 )
  {
   str_ies.Add_Dirty( lem::format_str( " *%d", n1 ).c_str() );
   n1=0;
  }
 // --------------------------------------------------------------------
*/



 lem::MemFormatter mem;
 mem.printf( "INSERT INTO charpos2entry(charpos,ies) VALUES (%ud,'%s')", charpos, str_ies.c_str() );

 lem::FString ins0( lem::to_utf8(mem.string()) );
 int res = sqlite3_exec( hdb, ins0.c_str(), NULL, NULL, NULL );
 if( res!=SQLITE_OK )
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, sql=%us, char=%d, pos=%d, message=%us",
     __FILE__, __LINE__, lem::from_utf8(ins0).c_str(), c, pos, lem::sqlite_errmsg(hdb).c_str() );
   throw lem::E_BaseException(msg.string());
  }


 return;
}

static int Digit2Int( char c )
{ return c-'0'; }

void Charpos2EntryStorage_SQLITE::Get( lem::uint32_t c, int pos, std::set<int> &ies )
{
 ies.clear();

 const lem::uint32_t charpos = c | (pos<<24);

 lem::FString sql( lem::format_str( "SELECT ies FROM charpos2entry WHERE charpos=%u", charpos ).c_str() );

 int retval=-1;
 sqlite3_stmt *stmt=NULL;
 const char *dummy;
 int res = sqlite3_prepare( hdb, sql.c_str(), sql.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   res = sqlite3_step( stmt );
   if( res == SQLITE_ROW )
    {
     const char* str = (const char*)sqlite3_column_text(stmt,0);

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
      
       tok[itok]=0;

       if( itok==0 )
        break;

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

   sqlite3_finalize(stmt);
  }

 return;
}

void Charpos2EntryStorage_SQLITE::GetIntersected(
                                                 lem::uint32_t c,
                                                 int pos,
                                                 const std::set<int> &ies0,
                                                 std::set<int> &ies
                                                )
{
 const lem::uint32_t charpos = c | (pos<<24);

 lem::FString sql( lem::format_str( "SELECT ies FROM charpos2entry WHERE charpos=%u", charpos ).c_str() );

 //int retval=-1;
 sqlite3_stmt *stmt=NULL;
 const char *dummy;
 int res = sqlite3_prepare( hdb, sql.c_str(), sql.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   res = sqlite3_step( stmt );
   if( res == SQLITE_ROW )
    {
     const char* str = (const char*)sqlite3_column_text(stmt,0);

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

   sqlite3_finalize(stmt);
  }

 return;
}


Charpos2EntryEnumerator* Charpos2EntryStorage_SQLITE::Enumerate(void)
{
 lem::FString Select("SELECT charpos FROM charpos2entry");

 sqlite3_stmt *stmt=NULL;
 const char *dummy=NULL;
 int res = sqlite3_prepare_v2( hdb, Select.c_str(), Select.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   return new Charpos2EntryEnumerator_SQL( new LS_ResultSet_SQLITE(stmt) );
  }
 else
  {
   lem::MemFormatter msg;
   msg.printf( "SQLite error in file %s:%d, message=%us", __FILE__, __LINE__, lem::sqlite_errmsg(hdb).c_str() );
   throw lem::E_BaseException(msg.string());
  }
}


void Charpos2EntryStorage_SQLITE::BeginTx(void)
{
 lem::sqlite_begin_tx(hdb);
 return;
}

void Charpos2EntryStorage_SQLITE::CommitTx(void)
{
 lem::sqlite_commit_tx(hdb);
 return;
}

