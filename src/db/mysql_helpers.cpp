#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/mysql_helpers.h>
#include <lem/oformatter.h>
#include <lem/conversions.h>

using namespace lem;

int lem::mysql_select_int( MYSQL* db, const char *Select )
{
 int retval=-1;

 int ok = mysql_query( db, Select );
 if( ok==0 )
  {
   MYSQL_RES *res = mysql_store_result(db);
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
   mem.printf( "Error in MySQL, sql=%s, error=%us", Select, mysql_errmsg(db).c_str() );
   throw lem::E_BaseException(mem.string());
  }

 return retval;
}


int lem::mysql_column_int( MYSQL_ROW row, int icol )
{
 const char *str = row[icol];
 return lem::to_int(str);
}


lem::UFString lem::mysql_column_ufstring( MYSQL_ROW row, int icol )
{
 const char *str = row[icol];
 UFString res( lem::from_utf8(str) );
 return res;
}

lem::FString lem::mysql_column_fstring( MYSQL_ROW row, int icol )
{
 const char *str = row[icol];
 return FString(str);
}

lem::UCString lem::mysql_column_ucstring( MYSQL_ROW row, int icol )
{
 const char *str = row[icol];
 UCString res( lem::from_utf8(str).c_str() );
 return res;
}


lem::UFString lem::mysql_errmsg( MYSQL* mysql )
{
 return lem::to_unicode( mysql_error(mysql) );
}


void lem::mysql_begin_tx( MYSQL* mysql )
{
 LEM_CHECKIT_Z(mysql!=NULL);

 int res = mysql_query(mysql,"BEGIN");
 if( res!=0 )
  throw E_BaseException( lem::format_str( L"MySQL error: can not begin transaction, message=%s", to_unicode(mysql_error(mysql)).c_str() ).c_str() );

 return;
}


void lem::mysql_commit_tx( MYSQL* mysql )
{
 LEM_CHECKIT_Z(mysql!=NULL);
 int res = mysql_query(mysql,"COMMIT");
 if( res!=0 )
  throw E_BaseException( lem::format_str( L"MySQL error: can not commit transaction, message=%s", to_unicode(mysql_error(mysql)).c_str() ).c_str() );

 return;
}


void lem::mysql_rollback_tx( MYSQL* mysql )
{
 LEM_CHECKIT_Z(mysql!=NULL);
 int res = mysql_query(mysql,"ROLLBACK");
 if( res!=0 )
  throw E_BaseException( lem::format_str( L"MySQL error: can not rollback transaction, message=%s", to_unicode(mysql_error(mysql)).c_str() ).c_str() );
}


void lem::mysql_escape( lem::UFString &str )
{
 str.subst_all( L"\\", L"\\\\" );
 str.subst_all( L"'", L"\\'" );
 return;
}


void lem::mysql_escape( lem::FString &str )
{
 str.subst_all( "\\", "\\\\" );
 str.subst_all( "'", "\\'" );
 return;
}

#endif
