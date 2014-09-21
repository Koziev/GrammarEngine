// LC->06.03.2010

#include <lem/config.h>

#if defined LEM_MFC
 #include <afx.h>
#endif

#if defined LEM_WINDOWS
 #include <windows.h>
 #include <wininet.h>
 #include <tchar.h> 
#endif

#if defined(LEM_MSC) && _MSC_VER>=1300
 #include <strsafe.h>
#endif

#if defined LEM_QT
 #include <QUrl>
#endif

#include <lem/conversions.h>
#include <lem/url.h>

#if defined(LEM_MSC) && defined LEM_WINDOWS
 #pragma comment ( lib, "wininet.lib" )
#endif


using namespace lem;

Url::Url( const UFString &str, bool exception )
 : full_address(str), ok(true)
{
 HttpProtocol();
 Canonize(exception);
 Parse(exception);
}


Url::Url( const Url &base, const UFString &doc, bool exception )
 : ok(true)
{
 #if defined LEM_QT

 full_address = base.full_address;
 full_address += L'/';
 full_address += doc;

 #else

 wchar_t Buffer[MAX_URL_LEN];
 DWORD l = sizeof(Buffer);

 BOOL res = InternetCombineUrlW(
                                base.string().c_str(), 
                                doc.c_str(),  
                                Buffer,
                                &l, 
                                0
                               ); 

 if( !res )
  {
   ok = false;

   if( exception )
    throw E_BaseException(
                          wstring(L"Can not combine URLs: ")+
                          wstring(base.string().c_str())+
                          wstring( L" and " )+
                          doc.c_str()
                         );
  } 

 full_address = Buffer;

 #endif

 HttpProtocol();
 Canonize(exception);
 Parse(exception);

 return;
}


// *******************************************************************
// Если протокол не указан, то вставит http:// в начале строки адреса
// *******************************************************************
void Url::HttpProtocol(void)
{
 if( full_address.empty() )
  return;

 if(
    lem_eq_begin( full_address.c_str(), L"http://" ) ||
    lem_eq_begin( full_address.c_str(), L"file:///" ) ||
    lem_eq_begin( full_address.c_str(), L"ftp://" )  ||
    lem_eq_begin( full_address.c_str(), L"https://" )
   )
  return;

 full_address = UFString(L"http://")+full_address;
 return;
}



void Url::Canonize( bool exception )
{
 #if defined LEM_QT
  // ...
  LEM_STOPIT;
 #else
 wchar_t Buffer[MAX_URL_LEN];
 DWORD res_len=MAX_URL_LEN;

 BOOL res = InternetCanonicalizeUrlW( 
                                     full_address.c_str(),
                                     Buffer,         
                                     &res_len,
                                     0//URL_ESCAPE_UNSAFE
                                    );

 if( res!=TRUE )
  {
   ok = false;

   if( exception )
    throw E_BaseException( wstring(L"Could not canonize URL=")+full_address.c_str() );  
  }

 full_address = Buffer;
 #endif

 return;
}


void Url::Parse( bool exception )
{
 #if defined LEM_QT
  // ...
  LEM_STOPIT;
 #else

 URL_COMPONENTSW parts;
 parts.dwStructSize = sizeof(parts);

 parts.dwSchemeLength = 16;
 parts.lpszScheme = new wchar_t[ parts.dwSchemeLength ];
 *parts.lpszScheme = 0;

 parts.dwHostNameLength = MAX_URL_LEN;
 parts.lpszHostName = new wchar_t[ parts.dwHostNameLength ];
 *parts.lpszHostName = 0;

 parts.dwUserNameLength = MAX_URL_LEN;
 parts.lpszUserName = new wchar_t[ parts.dwUserNameLength ];
 *parts.lpszUserName = 0;

 parts.dwPasswordLength = MAX_URL_LEN;
 parts.lpszPassword = new wchar_t[ parts.dwPasswordLength ];
 *parts.lpszPassword = 0;

 parts.dwUrlPathLength = MAX_URL_LEN;
 parts.lpszUrlPath = new wchar_t[ parts.dwUrlPathLength ];
 *parts.lpszUrlPath = 0;

 parts.lpszExtraInfo = NULL;
 parts.dwExtraInfoLength = 0;

 if( !InternetCrackUrlW( 
                        full_address.c_str(),
                        0,
                        0,
                        &parts
                       ) )
  {
   ok = false;
   if( exception )
    throw E_BaseException( wstring(L"Can not parse URL ")+full_address.c_str() );
  } 
 

 protocol = parts.lpszScheme;
 port     = parts.nPort;

 login    = parts.lpszUserName;
 password = parts.lpszPassword;
 path     = parts.lpszUrlPath;
 adr      = parts.lpszHostName;
 
 delete[] parts.lpszScheme;
 delete[] parts.lpszHostName;
 delete[] parts.lpszUserName;
 delete[] parts.lpszPassword;
 delete[] parts.lpszUrlPath;
 #endif

 return;
}

void Url::SaveBin( lem::Stream &bin ) const
{
}

void Url::LoadBin( lem::Stream &bin )
{
}


const UFString Url::GetDomainString(void) const
{
/*
 if( length()<4 )
  return string();

 // Смотрим суффикс
 const wchar_t c = back();
 if( c==L'\\' || c==L'/' )
  return string();

 UFString s3 = lem::right( string(), 4 ).to_lower();

 int dot_pos=UNKNOWN;
 for( int i=length()-1; i>=0; i-- ) 
  if( full_address[i] == L'.' )
   {
    dot_pos = i;
    break;
   }
  else if( full_address
*/

 UFString ret( protocol.c_str() );
 if( !ret.empty() )
  ret.Add_Dirty( L"://" );

 ret.Add_Dirty( adr );

 if( port>0 )
  {
   // Добавляем порт  http://127.0.0.1:21
   //                                 ^^^ 
   ret.Add_Dirty( L':' );
   ret.Add_Dirty( to_ustr(port).c_str() );    
  }

 ret.calc_hash();
 
 return ret;  
}


const UFString Url::GetDocumentString(void) const
{
 if( !path.empty() )
  return path;

 return full_address;
}


static char* UrlDecode( const char *source, char *dest )
{
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


static void HtmlDecode( const char* abuf, wchar_t *wbuf )
{
 int idest=0;
 *wbuf=0;

 char num[10];

 int isrc=0;
 while( abuf[isrc] )
  { 
   if( abuf[isrc] == '&' ) 
    {
     isrc++;
     if( abuf[isrc]=='#' )
      {
       // Код символа в виде &#nnnn;
       //                      ^^^^
       isrc++; 
       int j=0;
       while( abuf[isrc] )
        if( abuf[isrc] == ';' )
         { isrc++; break;}
        else
         {
          if( j<CastSizeToInt(sizeof(num)) )
           num[j++] = abuf[isrc];
          isrc++;
         }

       num[j]=0;
       wbuf[idest++] = atoi(num);
      }
    }
   else
    wbuf[idest++] = abuf[isrc++]; 
  }

 wbuf[idest] = 0;
 return;
}


void lem::GetUrlParams(
                       const char *urlstr,
                       std::list< std::pair<string/*var*/,wstring/*value*/> > &list
                      )
{
 const char *quest = strchr( urlstr, '?' );

 if( quest==NULL )
  return;

 quest++;
 int i=0;
 const int l=strlen(quest);

 char var_name[64]="";
 char value[512]="";
 char abuf[512]="";
 wchar_t wbuf[512]=L"";

 while( quest[i] && i<l )
  {
   // имя переменной - до символа '='
   //int i0=i;
   int j=0;
   *var_name = 0; 
   while( quest[i] && i<l ) 
    if( quest[i] == '=' )
     { i++; break; }
    else
     {
      if( j<CastSizeToInt(sizeof(var_name)) )
       var_name[j++] = quest[i];
      var_name[j]=0;
      i++;
     }  
          
   if( !*var_name )
    break;

   if( !quest[i]  || i>=l )
    break;


   // Извлекаем значение переменной
   j=0;
   *value = 0;
   while( quest[i] && i<l )
    {
     if( quest[i]=='&' )
      {
       i++; break;
      }

     if( j<CastSizeToInt(sizeof(value)) )
      {
       value[j++]=quest[i++];
       value[j]=0;
      }  
    }

   UrlDecode( value, abuf );
   HtmlDecode( abuf, wbuf );

   // Добавляем переменную и значение в массив
   if( *wbuf )
    list.push_back( make_pair(string(var_name),wstring(wbuf)) );
  }

 return;
}

bool lem::Url::IsUrl( const wchar_t *str )
{
 if(
    lem::lem_eq_begin( L"http://", str ) ||
    lem::lem_eq_begin( L"ftp://", str )  ||
    lem::lem_eq_begin( L"https://", str ) ||
    lem::lem_eq_begin( L"ftps://", str ) 
   )
  return true;

 return false;
}
