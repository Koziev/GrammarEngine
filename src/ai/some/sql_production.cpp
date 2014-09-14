#include <lem/containers.h>
#include <lem/conversions.h>
#include <lem/solarix/sql_production.h>

using namespace lem;
using namespace Solarix;

SQL_Production::SQL_Production( const FString &Version )
 : version(Version)
{
 utf8=true; bom=false;
 ascii=false;
 demo=false;
 norules=false;
 top_freq=UNKNOWN;

 version.to_lower();
 version.strip_apostrophes();
 version.trim();

 bulk_inserts=1;
 comment = "//";

 begin_tx = "";
 commit_tx = "COMMIT;";

 internal_commit_tx.re_clear();

 lem::MCollect<lem::CString> tokens;

 internal_commit_period = lem::int_max;

 lem::parse( version, tokens, false );

 for( lem::Container::size_type i=0; i<tokens.size(); ++i )
  {
   const lem::CString &token = tokens[i];

   if( token=="oracle" )
    {
     type = Oracle;
     comment = "--";
     bulk_inserts=128;
     internal_commit_tx="COMMIT;";
     internal_commit_period=100;
    }
   else if( token=="mysql" )
    {
     type = MySql;
     comment = "#";
     bulk_inserts=128;
     internal_commit_tx="COMMIT;";
     //internal_commit_period=100;
    }
   else if( token=="postgres" )
    {
     type = Postgres;
     comment = "--";
     bulk_inserts=128;
     begin_tx = "BEGIN;";
     internal_commit_tx="\nCOMMIT;\nBEGIN;\n";
     //internal_commit_period=100;
    }
   else if( token=="firebird" )
    {
     type = FireBird;
     begin_tx = "";
     comment = "--";
     bulk_inserts=50;
     internal_commit_period=100;
     begin_tx = "SET TRANSACTION;";
     internal_commit_tx="\nCOMMIT;\nSET TRANSACTION;\n";
    }
   else if( token=="sqlite" )
    {
     type = SQLite;
     comment = "--";
     bulk_inserts=50;
     begin_tx = "BEGIN;";
    }
   else if( token=="mssql" )
    {
     type = MsSql;
     comment = "--";
     bulk_inserts=lem::int_max;
     begin_tx = "BEGIN TRANSACTION";
     commit_tx = "COMMIT\r\nGO";
     internal_commit_tx="COMMIT\r\nGO\r\nBEGIN TRANSACTION";
     internal_commit_period=100;
    }
   else if( token == "utf8" )
    {
     utf8=true;
     ascii=false;
    }
   else if( token == "bom" )
    {
     bom=true;
    }
   else if( token == "mssql_bulk_insert" )
    {
     mssql_bulk_insert=true;
    }
   else if( token == "loader" )
    {
     loader=true;
    }
   else if( token == "demo" )
    {
     demo=true;

     // Далее идет несколько числовых значений в формате 0xnnnn
     // Это UNICODE-коды первых символов имен статей, которые
     // будут выгружаться
     i++;
     while( i<tokens.size() )
      {
       if( tokens[i].eq_beg( L"0x" ) )
        {
         int u=0;
         lem::to_int( tokens[i].c_str()+2, &u, 16 );
         demo_ename_front.push_back( (wchar_t)u );
         i++;
        }
       else if( lem::is_int(tokens[i].c_str()) )
        {
         demo_ename_front.push_back( (wchar_t)lem::to_int(tokens[i]) );
         i++;
        }
       else
        {
         i--;
         break;
        }
      }
    }
   else if( token == "ascii" )
    {
     utf8=false;
     ascii=true;
    }
   else if( token == "noschema" )
    {
     noschema=true;
    }
   else if( token == "lemmatizator" )
    {
     lemmatizator=true;
    }
   else if( token == "noformcoords" )
    {
     noformcoords=true;
    }
   else if( token == "norules" )
    {
     norules=true;
    }
   else if( token == "top_freq" )
    {
     i+=1;
     const lem::CString & freq = tokens[i];
     top_freq = lem::to_int(freq.c_str());
    }
   else
    {
     lem::UFString msg = format_str( L"Invalid option %s in SQL_Production ctor", to_unicode(token).c_str() );
     throw lem::E_BaseException(msg);
    }
  }
 
 return;
}


lem::UFString SQL_Production::SqlStr( const UCString &s ) const
{
 UFString res(s.c_str());

 if( type==FireBird || type==MsSql || type==SQLite || type==Oracle )
  {
   res.subst_all( L"\\", L"\\\\" );
   res.subst_all( L"'", L"''" );
   res.subst_all( L"\r", L"\\r" );
   res.subst_all( L"\n", L"\\n" );
   res.subst_all( L"\t", L"\\t" );

   if( type==FireBird )
    {
     // суррогатные пары надо убивать, FB на них ругается malformed string...
     for( int i=0; i<res.length(); ++i )
      if( (res[i] & 0xF800)==0xD800 )
       {
        res.set(i,L'?');
        if( i<res.length()-1 )
         res.set(i+1,L'?');
       }
    }
  }
 else if( type==Postgres )
  {
   res.subst_all( L"'", L"''" );
  }
 else if( type == MySql )
  {
   res.subst_all( L"\\", L"\\\\" );
   res.subst_all( L"'", L"\\'" );
   res.subst_all( L"\r", L"\\r" );
   res.subst_all( L"\n", L"\\n" );
   res.subst_all( L"\t", L"\\t" );
  }

 res.re_clear();

 return res;
}


lem::UFString SQL_Production::SqlStr( const UFString &s ) const
{
 UFString res(s);

 if( type==FireBird || type==MsSql || type==SQLite || type==Oracle )
  {
   res.subst_all( L"'", L"''" );
   res.subst_all( L"\r", L"\\r" );
   res.subst_all( L"\n", L"\\n" );
   res.subst_all( L"\t", L"\\t" );

   if( type==FireBird )
    {
     // суррогатные пары надо убивать, FB на них ругается malformed string...
     for( int i=0; i<res.length(); ++i )
      if( (res[i] & 0xF800)==0xD800 )
       {
        res.set(i,L'?');
        if( i<res.length()-1 )
         res.set(i+1,L'?');
       }
    }
  }
 else if( type==Postgres )
  {
   res.subst_all( L"'", L"''" );
  }
 else if( type == MySql )
  {
   res.subst_all( L"\\", L"\\\\" );
   res.subst_all( L"'", L"\\'" );
   res.subst_all( L"\r", L"\\r" );
   res.subst_all( L"\n", L"\\n" );
   res.subst_all( L"\t", L"\\t" );
  }

 return res;
}



// Для демо-режима выгрузки - проверяет, что первый символ имени
// статьи соответствует ранее определенным фильтрам.
bool SQL_Production::MatchEntryName( const lem::UCString &ename ) const
{
 return !demo || demo_ename_front.empty() || demo_ename_front.find(ename.front())!=UNKNOWN;
}



// Возвращает префикс для строковых литералов, например для поля типа nvarchar2 для Oracle и MS SQL
// возвращает N, для других СУБД может вернуть пустую строку (не NULL).
const wchar_t * SQL_Production::GetNPrefix(void) const
{
 if( type==MsSql || type==Oracle )
  {
   if( utf8 )
    return L"N";
  }

 return L"";
}

const wchar_t * SQL_Production::GetLoadInfileText(void) const
{
 if( type==MySql )
  {
   return L"LOAD DATA LOCAL INFILE";
  }
 else if( type==Postgres )
  {
   return L"\\COPY";
  }

 LEM_STOPIT;
 return L"";
}



static wchar_t c2h( lem::uint16_t c )
{
 wchar_t r=0;

 switch(c)
 {
  case 0: r=L'0'; break;
  case 1: r=L'1'; break;
  case 2: r=L'2'; break;
  case 3: r=L'3'; break;
  case 4: r=L'4'; break;
  case 5: r=L'5'; break;
  case 6: r=L'6'; break;
  case 7: r=L'7'; break;
  case 8: r=L'8'; break;
  case 9: r=L'9'; break;
  case 10: r=L'A'; break;
  case 11: r=L'B'; break;
  case 12: r=L'C'; break;
  case 13: r=L'D'; break;
  case 14: r=L'E'; break;
  case 15: r=L'F'; break;
 }

 return r;
}

static lem::UFString uchar2hex( lem::uint16_t c )
{
 lem::UFString res;
 res = c2h( (c & 0xf000)>>12 );
 res += c2h( (c & 0x0f00)>>8 );
 res += c2h( (c & 0x00f0)>>4 );
 res += c2h( (c & 0x000f) );
 return res;
}

lem::UFString SQL_Production::Oracle_UNISTR( const lem::UFString & str )
{
 UFString s2=L"UNISTR('";
 for( int i=0; i<str.length(); ++i )
  s2 += lem::format_str( L"\\%s", uchar2hex(str[i]).c_str() );

 s2+= L"')";

 return s2;
}


lem::UFString SQL_Production::ClearInvalidChars( const lem::UFString & str ) const
{
 lem::UFString res;

 if( IsAscii() )
  {
   for( int k=0; k<str.length(); ++k )
    {
     char ac = ((SBCodeConverter&)lem::UI::get_UI().GetSessionCp()).to_ascii( str[k] );
     if( ac!=0 )
      res.Add_Dirty( str[k] );
    }

   res.calc_hash();
  }
 else
  res = str;

 return res;
}
