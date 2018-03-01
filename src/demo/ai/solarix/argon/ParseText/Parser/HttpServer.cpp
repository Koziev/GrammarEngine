#if defined HTTP_PARSER_SERVICE
#include <lem/logfile.h>
#include <lem/conversions.h>
#include "ParserEngineBase.h"
#include "HttpServer.h"

using namespace lem;

ParserHttpServer::ParserHttpServer( ParserEngineBase *eng )
 : HttpServer()
{
 parser=eng;
}

bool ParserHttpServer::GenerateHtml( const char *url, const char * query, lem::UFString &out, char ** content_type )
{
 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "%W24us Processing URL [%s] in ParserHttpServer::GenerateHtml\n", timestamp().c_str(), url );

 FString Url(url);
 if( !lem::lem_is_empty(query) )
  {
   Url += '?';
   Url += query;
  }

 if( Url.eq_beg( "/query.html" ) || Url==L"/" || Url.eq_beg( "/index.htm" ) )
  {
   // По умолчанию - страница для ввода поискового запроса
   BeginHtml(out);
   ShowQueryPage(Url,out);
   EndHtml(out);
  }
 else if( Url.eq_beg( "/parse.html?" ) )
  {
   ShowResultsPage(Url,out,content_type);
  }
 else if( Url.eq_beg( "/info.html" ) )
  {
   BeginHtml(out);
   ShowInfoPage(Url,out);
   EndHtml(out);
  }

 return true;
}



void ParserHttpServer::ShowQueryPage( const FString &url, lem::UFString &out )
{
 out += L"<form method=\"GET | POST\" action=\"http://";
 out += GetAddress();
 out += L":";
 out += lem::to_ustr(GetPort()).c_str();
 out += L"/parse.html\">"
        L"<p align=center><label for='string'>Sentence:</label>"
        L"<input type='text' name='string' size='100%' id='string'/>&nbsp;&nbsp;"
        L"<input type='submit' value='Parse' name='cb_parse'/></p>";
 out += "</form>";

 return;
}



void ParserHttpServer::ShowResultsPage( const FString &url, lem::UFString &out, char ** content_type )
{
 int iquery = url.search( '?' );

 if( iquery!=UNKNOWN )
  {
   std::list< std::pair<string/*var*/,wstring/*value*/> > list;
   GetParams( url.c_str()+iquery+1, list );

   UFString sentence;
   UFString res_format;

   for( std::list< std::pair<string/*var*/,wstring/*value*/> >::const_iterator i=list.begin();
        i!=list.end();
        i++ )
    { 
     if( i->first == "string" )
      sentence = i->second.c_str();
    }

   if( res_format==L"xml" )
    {
    }
   else
    {
     lem::MemFormatter out_stream;
     out_stream.printf( "<?xml version='1.0' encoding='utf-8' ?>\n<parsing>\n" );
     parser->ParseString( sentence, -1, &out_stream );
     out_stream.printf( "</parsing>" );
     out = out_stream.string();
     *content_type = "text/xml";
    }
  }
 else
  {
   BeginHtml(out);
   ShowQueryPage( url, out );
   EndHtml(out);
  }

 return;
}





void ParserHttpServer::ShowInfoPage( const FString &url, lem::UFString &out )
{
 out += L"<br>\n";

 // ...

 return;
}

#endif // #if defined HTTP_PARSER_SERVICE

