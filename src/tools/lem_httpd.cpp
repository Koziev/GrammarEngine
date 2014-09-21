// CD->21.08.2009
// LC->16.01.2011

#include <lem/runtime_checks.h>
#include <lem/unicode.h>
#include <lem/conversions.h>
#include <lem/logfile.h>
#include <lem/httpd.h>

using namespace lem;

#if defined(LEM_MSC) && defined(LEM_WINDOWS)
#pragma comment ( lib, "Ws2_32.lib" )
#endif



HttpServer::HttpServer(void)
{
 ctx = NULL;
 port = UNKNOWN;
 ExitCode=-1;
 return;
}


HttpServer::~HttpServer(void)
{
 ctx = NULL;
 return;
}


void HttpServer::Run( const char *Addr, int Port )
{
 LEM_CHECKIT_Z(Addr!=NULL);
 LEM_CHECKIT_Z(Port>0 && Port<0x0000ffff );

 ExitCode=0;

 ip=Addr;
 port=Port;

 server_url = L"http://";
 server_url += ip.c_str();
 server_url += L":";
 server_url += to_ustr( (int)port ).c_str();

 ctx = mg_start();
 
 FString binding( lem::format_str( "%s:%d", Addr, Port ) );
 mg_set_option(ctx, "ports", binding.c_str() );// lem::to_str(Port).c_str() );

 mg_set_uri_callback( ctx, "/*", &HttpCallback, (void*)this );

 EnterWaitLoop();

 return;
}

int HttpServer::GetExitCode(void)
{
 return ExitCode;
}


void HttpServer::ReleaseResources(void)
{
 mg_stop(ctx);
 return;
}


void HttpServer::EnterWaitLoop(void)
{
 // Реализация по умолчанию предполагает усыпление главного треда навечно,
 // но производные классы могут сделать какую-либо обработку в фоне.
 #if defined LEM_WINDOWS
 Sleep(INFINITE);
 #else
 sleep(-1);
 #endif
 return;
}


void HttpServer::HttpCallback(
                              struct mg_connection *conn,
                              const struct mg_request_info *request_info,
                              void *user_data
                             )
{
 const char * url = request_info->uri;
 const char * query = request_info->query_string;

 HttpServer *This = (HttpServer*)user_data;

 char *outdata=NULL;
 int freer_type=0;

 try
  {
   This->StartProcessingQuery(url);

   char * content_type = "text/html";

   bool page_generated=false;
   if( strcmp(request_info->request_method,"GET")==0 )
    {
     page_generated = This->GenerateHtml( url, query, &outdata, &freer_type, &content_type );
    }
   else if( strcmp(request_info->request_method,"POST")==0 )
    {
     page_generated = This->ProcessPostRequest( url, query, request_info->post_data, request_info->post_data_len, &outdata, &freer_type, &content_type );
    }

   if( page_generated )
    This->WriteHeader( conn, content_type );
   else
    This->PageNotFound( conn );

   if( outdata!=NULL )
    {
     const int l = strlen(outdata);
     if( l<8000 )
      {
       mg_printf( conn, "%s", outdata );
      }
     else
      {
       int tail=l;
       int ipos=0; 

       while( tail>0 )
        {
         int chunk=8000; 
         if( tail<8000 )
          chunk = tail;

         char c = outdata[ipos+chunk];
         outdata[ipos+chunk] = 0; 
         mg_printf( conn, "%s", outdata+ipos );
         outdata[ipos+chunk] = c;
         ipos += chunk;
         tail -= chunk;  
        }
      }
    }
  }
 catch(...)
  {
   if( lem::LogFile::IsOpen() )
    {
     lem::MemFormatter mem;
     mem.printf( "Inhandled exception in file %s line %d", __FILE__, __LINE__ );
     lem::LogFile::Print( mem.string() );
    }
  }

 try
  {
   switch( freer_type )
   {
    case 0: break;
    case 1: delete[] outdata; break;
    case 2: free(outdata); break;
   }
  }
 catch(...)
  {
   if( lem::LogFile::IsOpen() )
    {
     lem::MemFormatter mem;
     mem.printf( "Inhandled exception in file %s line %d", __FILE__, __LINE__ );
     lem::LogFile::Print( mem.string() );
    }
  } 

 try
  {
   This->StartProcessingQuery(url);
  }
 catch(...)
  {
   if( lem::LogFile::IsOpen() )
    {
     lem::MemFormatter mem;
     mem.printf( "Inhandled exception in file %s line %d", __FILE__, __LINE__ );
     lem::LogFile::Print( mem.string() );
    }
  } 

 return;
}






bool HttpServer::GenerateHtml(
                              const char * url,
                              const char * query,
                              char **outdata,
                              int *freer_type,
                              char **content_type
                             )
{
 LEM_CHECKIT_Z(url);

 lem::UFString out;

 if( GenerateHtml(url,query,out,content_type) && !out.empty() )
  {
   lem::FString utf8 = to_utf8( out ); 
   *outdata = new char[ utf8.length()+1 ];
   strcpy( *outdata, utf8.c_str() );
   *freer_type = 1;
   return true;   
  }
 else
  {
   *outdata = "<html><body></body></html>";
   *freer_type = 0;
  }

 return true;
}



bool HttpServer::ProcessPostRequest(
                                    const char *url,
                                    const char * query,
                                    const char * post_data,
                                    int post_data_len,
                                    char **outdata,
                                    int *freer_type,
                                    char **content_type
                                   )
{
 LEM_CHECKIT_Z(url);

 lem::UFString out;

 if( ProcessPostRequest(url,query,post_data,post_data_len,out,content_type) && !out.empty() )
  {
   lem::FString utf8 = to_utf8( out ); 
   *outdata = new char[ utf8.length()+1 ];
   strcpy( *outdata, utf8.c_str() );
   *freer_type = 1;
   return true;   
  }
 else
  {
   *outdata = "<html><body></body></html>";
   *freer_type = 0;
  }

 return true;
}


bool HttpServer::GenerateHtml(
                              const char * url,
                              const char * query,
                              lem::UFString &outdata,
                              char **content_type
                             )
{
 return false;
}


bool HttpServer::ProcessPostRequest(
                                    const char * url,
                                    const char * query,
                                    const char * post_data,
                                    int post_data_len,
                                    lem::UFString &outdata,
                                    char **content_type
                                   )
{
 return false;
}

void HttpServer::WriteHeader( struct mg_connection *conn, const char *content_type )
{
 mg_printf( conn, "HTTP/1.1 200 OK\r\n"
 "Content-Type: %s\r\n"
 "Connection: close\r\n\r\n", content_type );

 return;
}

void HttpServer::PageNotFound( struct mg_connection *conn )
{
 mg_printf( conn, "HTTP/1.1 404 Not Found\r\n" );
 return;
}

void HttpServer::BeginHtml( lem::UFString &out, const wchar_t *PageTitle ) const
{
 BeginHtml( out, PageTitle, NULL );
 return;
}


void HttpServer::BeginHtml( lem::UFString &out, const wchar_t *PageTitle, const wchar_t *HeaderMeta ) const
{
 out = "<html>\n<head>\n"
       "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n";     

 if( !lem::lem_is_empty(HeaderMeta) )
  {
   out += HeaderMeta;
  }

 if( !lem::lem_is_empty(PageTitle) )
  {
   out += "<title>";
   out += lem::encode_chars_to_html(PageTitle).c_str();
   out += "</title>";
  }

 out += "</head><body>\n";

 return;
}


void HttpServer::EndHtml( lem::UFString &out ) const
{
 out += "\n</body>\n</html>\n";
}




char* HttpServer::urlDecode( const char *source, char *dest ) const
{
 LEM_CHECKIT_Z(source);
 LEM_CHECKIT_Z(dest);

 char *ret;
 char hex[3];

 if(!dest)
  dest = NULL;
 else
  *dest = 0;

 ret = dest;

 if(!source)
  return dest;

 while( *source )
  {
   switch(*source)
   {
    case '+':
     *(dest++) = ' ';
     break;
   
    case '%':
     // NOTE: wrong input can finish with "...%" giving
     // buffer overflow, cut string here
     if(source[1])
      {
       hex[0] = source[1];
       ++source;
       if(source[1])
        {
         hex[1] = source[1];
         ++source;
        }
       else
        hex[1] = 0;
      }
     else
      hex[0] = hex[1] = 0;	

     hex[2] = 0;
     *(dest++) = (char)strtol(hex, NULL, 16);
     break;

    default:
     *(dest++) = *source;
   }

   ++source;
  }

 *dest = 0;
 return ret;
}	


void HttpServer::htmlDecode( const char* abuf, wchar_t *wbuf ) const
{
 LEM_CHECKIT_Z(abuf);
 LEM_CHECKIT_Z(wbuf);

 UFString buf2 = lem::from_utf8( FString(abuf) );

 int idest=0;
 *wbuf=0;

 char num[10];

 int isrc=0;
 while( isrc<buf2.length() )
  { 
   if( buf2[isrc] == L'&' ) 
    {
     isrc++;
     if( buf2[isrc]==L'#' )
      {
       // Код символа в виде &#nnnn;
       //                      ^^^^
       isrc++; 
       int j=0;
       while( isrc<buf2.length() )
        if( buf2[isrc] == L';' )
         { isrc++; break;}
        else
         {
          if( j<sizeof(num) )
           num[j++] = buf2[isrc];
          isrc++;
         }

       num[j]=0;
       wbuf[idest++] = atoi(num);
      }
    }
   else
    wbuf[idest++] = buf2[isrc++]; 
  }

 wbuf[idest] = 0;
 return;
}



void HttpServer::GetParams(
                           const char *query,
                           std::list< std::pair<string/*var*/,wstring/*value*/> > &list
                          ) const
{
 if( query==NULL )
  return;

 int i=0;
 const int l=strlen(query);

 std::string var_name;
 std::string value;

 while( query[i] && i<l )
  {
   // имя переменной - до символа '='
   int i0=i;
   var_name.clear(); 
   while( query[i] && i<l ) 
    if( query[i] == '=' )
     { i++; break; }
    else
     {
      var_name += query[i];
      i++;
     }  
          
    if( var_name.empty() )
     break;

    if( !query[i]  || i>=l )
     break;

    // Извлекаем значение переменной
    value.clear();
    while( query[i] && i<l )
     {
      if( query[i]=='&' )
       {
        i++; break;
       }

      value += query[i++];
     }

    char *abuf = new char[ value.length()+1 ];
    wchar_t *wbuf = new wchar_t[ value.length()+1 ];

    urlDecode( value.c_str(), abuf );
    htmlDecode( abuf, wbuf );

    // Добавляем переменную и значение в массив
    if( *wbuf )
     list.push_back( make_pair(string(var_name),wstring(wbuf)) );

    delete[] abuf;
    delete[] wbuf;
   }

 return;
}


void HttpServer::StartProcessingQuery( const char *url_query )
{}


void HttpServer::EndProcessingQuery( const char *url_query )
{}
