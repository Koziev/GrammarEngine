#include <lem/unicode.h>
#include <lem/conversions.h>
#include <lem/solarix/ThTranslator.h>

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


TranslatorThesaurus::TranslatorThesaurus(void)
{
 hdb = NULL;
 return;
}


TranslatorThesaurus::~TranslatorThesaurus(void)
{
 if( hdb!=NULL )
  {
   sqlite3_close(hdb);
   hdb=NULL;
  }

 return;
}

void TranslatorThesaurus::Open( const lem::Path &sqlite_file )
{
 #if defined LEM_WINDOWS
 int res = sqlite3_open16( sqlite_file.GetUnicode().c_str(), &hdb );
 #else
 int res = sqlite3_open( to_utf8(sqlite_file.GetUnicode()).c_str(), &hdb );
 #endif

 if( res!=SQLITE_OK )
  {
   UFString msg = lem::format_str( L"Can not open SQLite database file '%s', error=%d message=%s", sqlite_file.GetUnicode().c_str(), res, sqlite3_errmsg16(hdb) );
   throw E_BaseException( msg.c_str() );
  }

 return;
}

void TranslatorThesaurus::GetTags( lem::PtrCollect<lem::UFString> &tags )
{
 int retval=-1;

 sqlite3_stmt *stmt=NULL;

 lem::FString sql( "SELECT tg_name FROM TAGS" );

 const char *dummy;
 int res = sqlite3_prepare( hdb, sql.c_str(), sql.length(), &stmt, &dummy );
 if( res==SQLITE_OK )
  {
   while( sqlite3_step( stmt )==SQLITE_ROW )
    {
     try
      {
       #if defined LEM_WINDOWS
       const wchar_t *txt2 = (const wchar_t*)sqlite3_column_text16(stmt,0);
       tags.push_back( new UFString( txt2 ) );
       #elif defined LEM_UNIX
       const char *txt2 = (const char*)sqlite3_column_text(stmt,0);
       tags.push_back( new UFString( lem::from_utf8(txt2) ) );
       #else
        #error
       #endif
      }
     catch(...)
      {
      }
    }

   sqlite3_finalize(stmt);
  }

 return;
}



void TranslatorThesaurus::Translate( const lem::UFString &in, lem::PtrCollect<lem::UFString> &outs )
{
 int retval=-1;

 sqlite3_stmt *stmt=NULL;

 for( int pass=0; pass<2; ++pass )
  {
   UFString e;
   lem::FString field;

   // Сначала пытаемся найти перевод для слова in с точным соответствием регистра
   // словарной статье. Если ничего не получится, приводим к нижнему регистру и
   // повторяем поиск.
   if( pass==0 )
    {
     e = in;
     field = "t_word";
    }
   else
    {
     e = lem::to_lower(in);
     field = "t_lword";
    }

   lem::FString sql( lem::format_str( "SELECT t_out FROM TRANSL WHERE %s='%s' ORDER BY t_order", field.c_str(), lem::to_utf8(e).c_str() ) );

   int nfound=0;
   const char *dummy;
   int res = sqlite3_prepare( hdb, sql.c_str(), sql.length(), &stmt, &dummy );
   if( res==SQLITE_OK )
    {
     while( sqlite3_step( stmt )==SQLITE_ROW )
      {
       try
        {
         #if defined LEM_WINDOWS
         const wchar_t *txt2 = (const wchar_t*)sqlite3_column_text16(stmt,0);
         outs.push_back( new UFString( txt2 ) );
         #elif defined LEM_UNIX
         const char *txt2 = (const char*)sqlite3_column_text(stmt,0);
         outs.push_back( new UFString( lem::from_utf8(txt2) ) );
         #else
          #error
         #endif
         nfound++;
        }
       catch(...)
        {
        }
      }

     sqlite3_finalize(stmt);

     if( nfound>0 )
      break;
    }

  }

 return;
}

bool TranslatorThesaurus::IsLeftHeadword( const lem::UFString &w, int &minlen, int &maxlen )
{
 UFString uw = lem::UFString(L"CPLX_") + lem::to_upper(w);
 lem::PtrCollect<lem::UFString> outs;
 Translate( uw, outs );
 if( outs.empty() )
  return false;

 lem::MCollect<UCString> toks;
 lem::parse( *outs.front(), toks, false );
 if( toks.size()==2 )
  {
   minlen = lem::to_int( toks[0] );
   maxlen = lem::to_int( toks[1] );
   return true;
  }
 else
  {
   return false;
  } 
}
