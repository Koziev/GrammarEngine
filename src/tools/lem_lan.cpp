// File LEM_LAN.CPP
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
//
//
// 03.10.2007 - введены GetLocalShares и GetShares.
// 20.10.2007 - введена GetIPs
//
// CD->21.02.2005
// LC->08.04.2010
// --------------

#include <lem/config.h>

#if defined LEM_WINDOWS || defined LEM_DOT_NET
#include <winsock.h>
#include <windows.h>
#include <lm.h>
#endif

#include <lem/fstring.h>
#include <lem/path.h>
#include <lem/conversions.h>
#include <lem/network.h>

using namespace lem;
using namespace lem::Network;

bool lem::Network::LAN::icpm_init=false;
bool lem::Network::LAN::winsock_init=false;
#if defined LEM_WINDOWS || defined LEM_DOT_NET
WSADATA lem::Network::LAN::ws;
#endif

#if defined(LEM_MSC) && defined(LEM_WINDOWS)
# pragma comment ( lib, "wininet.lib" )
# pragma comment ( lib, "WSock32.lib" )
# pragma comment ( lib, "Mpr.lib" )
# pragma comment ( lib, "Netapi32.lib" )
#endif


void LAN::Get_Disks( lem::Collect<lem::Path> &list, LAN::Callback callback, LAN::Progress progress )
{
 #if defined LEM_WINDOWS || defined LEM_DOT_NET
 NETRESOURCE nr;

 nr.dwScope      = RESOURCE_GLOBALNET;
 nr.dwType       = RESOURCETYPE_DISK;  
 nr.dwUsage      = RESOURCEUSAGE_CONTAINER;
 nr.lpLocalName  = TEXT("");
 nr.lpRemoteName = TEXT("");
 nr.lpComment    = TEXT("");
 nr.lpProvider   = TEXT("");

 EnumerateFunc( list, &nr, callback, progress );
 #endif
  
 return;
}


void LAN::Get_Hosts(
                    lem::Collect<lem::Path> &list,
                    LAN::Callback callback,
                    LAN::Progress progress
                   )
{
 #if defined LEM_WINDOWS || defined LEM_DOT_NET
 NETRESOURCE nr;

 nr.dwScope      = RESOURCE_CONTEXT;// RESOURCE_GLOBALNET;
 nr.dwType       = RESOURCETYPE_DISK;  
 nr.dwUsage      = RESOURCEUSAGE_CONTAINER;
 nr.lpLocalName  = TEXT("");
 nr.lpRemoteName = TEXT("");
 nr.lpComment    = TEXT("");
 nr.lpProvider   = TEXT("");

 EnumerateHostsFunc( list, &nr, callback, progress );
 #endif
  
 return;
}





#if defined LEM_WINDOWS || defined LEM_DOT_NET
bool LAN::EnumerateFunc(
                        lem::Collect<lem::Path> &list,
                        void *_Ptr,
                        LAN::Callback callback,
                        LAN::Progress progress  
                       )
{ 
 LPNETRESOURCEA lpnr = (LPNETRESOURCEA)_Ptr;

 DWORD dwResult, dwResultEnum;
 HANDLE hEnum;
 DWORD cbBuffer = 16384;      // 16K is a good size
 DWORD cEntries = -1;         // enumerate all possible entries
 LPNETRESOURCEA lpnrLocal;     // pointer to enumerated structures
 DWORD i;

 //
 // Call the WNetOpenEnum function to begin the enumeration.
 //
 dwResult = WNetOpenEnumA(
                          RESOURCE_GLOBALNET, // all network resources
                          RESOURCETYPE_ANY,   // all resources
                          0,         // enumerate all resources
                          lpnr,      // NULL first time the function is called
                          &hEnum );  // handle to the resource

 if (dwResult != NO_ERROR)
  {  
    //
    // Process errors with an application-defined error handler.
    //
//    NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetOpenEnum");
    return FALSE;
  }

 //
 // Call the GlobalAlloc function to allocate resources.
 //
 lpnrLocal = (LPNETRESOURCEA) GlobalAlloc(GPTR, cbBuffer);
 if( lpnrLocal == NULL ) 
  return FALSE;
  
 do
  {  
    //
    // Initialize the buffer.
    //
    ZeroMemory(lpnrLocal, cbBuffer);
    //
    // Call the WNetEnumResource function to continue
    //  the enumeration.
    //
    dwResultEnum = WNetEnumResourceA(hEnum,      // resource handle
                                    &cEntries,  // defined locally as -1
                                    lpnrLocal,  // LPNETRESOURCE
                                    &cbBuffer); // buffer size
    //
    // If the call succeeds, loop through the structures.
    //
    if (dwResultEnum == NO_ERROR)
    {
      for(i = 0; i < cEntries; i++)
      {
        // Call an application-defined function to
        //  display the contents of the NETRESOURCE structures.
        //
//        DisplayStruct( hdc, &lpnrLocal[i] );

        // If the NETRESOURCE structure represents a container resource, 
        //  call the EnumerateFunc function recursively.

        if( progress )
         progress( lpnrLocal[i].lpRemoteName );

        if(RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage
                                       & RESOURCEUSAGE_CONTAINER))
         {
          if( !EnumerateFunc(list, &lpnrLocal[i], callback, progress ) )
           {
//            TextOut(hdc, 10, 10, "EnumerateFunc returned FALSE.", 29);
           } 

//          printf( "CONTAINER: %s %s\n",  lpnrLocal[i].lpLocalName, lpnrLocal[i].lpRemoteName );
         }
        else
         {
//          printf( "DISK: %s %s\n",  lpnrLocal[i].lpLocalName, lpnrLocal[i].lpRemoteName );
          if(
             lpnrLocal[i].lpRemoteName[0]=='\\' &&
             lpnrLocal[i].lpRemoteName[1]=='\\'
            )
           {
            list.push_back( lem::Path( FString(lpnrLocal[i].lpRemoteName) ) );
 
            if( callback!=NULL )
             callback( list.back() );
           } 
         }
      }
    }
    // Process errors.
    //
    else if (dwResultEnum != ERROR_NO_MORE_ITEMS)
    {
//      NetErrorHandler(hwnd, dwResultEnum, (LPSTR)"WNetEnumResource");
      break;
    }
  }
 //
 // End do.
 //
 while(dwResultEnum != ERROR_NO_MORE_ITEMS);

 //
 // Call the GlobalFree function to free the memory.
 //
 GlobalFree((HGLOBAL)lpnrLocal);

 //
 // Call WNetCloseEnum to end the enumeration.
 //
 dwResult = WNetCloseEnum(hEnum);
  
 if(dwResult != NO_ERROR)
  { 
    //
    // Process errors.
    //
//    NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetCloseEnum");
    return FALSE;
  }

 return TRUE;
}
#endif 





#if defined LEM_WINDOWS || defined LEM_DOT_NET
// ************************************************************
// Функция-делегат для сбора списка хостов в локальной сети
// ************************************************************
bool LAN::EnumerateHostsFunc(
                             lem::Collect<lem::Path> &list,
                             void *_Ptr,
                             LAN::Callback callback,
                             LAN::Progress progress  
                            )
{ 
 LPNETRESOURCEA lpnr = (LPNETRESOURCEA)_Ptr;

 DWORD dwResult, dwResultEnum;
 HANDLE hEnum;
 DWORD cbBuffer = 16384;      // 16K is a good size
 DWORD cEntries = -1;         // enumerate all possible entries
 LPNETRESOURCEA lpnrLocal;     // pointer to enumerated structures
 DWORD i;

 //
 // Call the WNetOpenEnum function to begin the enumeration.
 //
 dwResult = WNetOpenEnumA(
                          RESOURCE_GLOBALNET, // all network resources
                          RESOURCETYPE_ANY,   // all resources
                          0,         // enumerate all resources
                          lpnr,      // NULL first time the function is called
                          &hEnum );  // handle to the resource

 if (dwResult != NO_ERROR)
  {  
    //
    // Process errors with an application-defined error handler.
    //
//    NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetOpenEnum");
    return FALSE;
  }

 //
 // Call the GlobalAlloc function to allocate resources.
 //
 lpnrLocal = (LPNETRESOURCEA) GlobalAlloc(GPTR, cbBuffer);
 if( lpnrLocal == NULL ) 
  return FALSE;
  
 do
  {  
    //
    // Initialize the buffer.
    //
    ZeroMemory(lpnrLocal, cbBuffer);
    //
    // Call the WNetEnumResource function to continue
    //  the enumeration.
    //
    dwResultEnum = WNetEnumResourceA(hEnum,      // resource handle
                                    &cEntries,  // defined locally as -1
                                    lpnrLocal,  // LPNETRESOURCE
                                    &cbBuffer); // buffer size
    //
    // If the call succeeds, loop through the structures.
    //
    if (dwResultEnum == NO_ERROR)
    {
      for(i = 0; i < cEntries; i++)
      {
        // Call an application-defined function to
        //  display the contents of the NETRESOURCE structures.
        //
//        DisplayStruct( hdc, &lpnrLocal[i] );

        // If the NETRESOURCE structure represents a container resource, 
        //  call the EnumerateFunc function recursively.

        if( progress )
         progress( lpnrLocal[i].lpRemoteName );

        if( lpnrLocal[i].dwDisplayType == RESOURCEDISPLAYTYPE_SERVER )
         { 
          if(
             lpnrLocal[i].lpRemoteName[0]=='\\' &&
             lpnrLocal[i].lpRemoteName[1]=='\\'
            )
           {
            int f=false;
            int j=2;
            while( lpnrLocal[i].lpRemoteName[j]!=0 )
             if( lpnrLocal[i].lpRemoteName[j]=='\\' )
              { f=true; break; }
             else
              j++;    

            if( lpnrLocal[i].lpRemoteName[j]=='\\' && lpnrLocal[i].lpRemoteName[j]==0 )
             f = false;

            if( !f )
             list.push_back( lem::Path( FString(lpnrLocal[i].lpRemoteName) ) );
 
            if( callback!=NULL )
             callback( list.back() );
           } 

         }

        if( RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage & RESOURCEUSAGE_CONTAINER) )
         {
          if( !EnumerateHostsFunc(list, &lpnrLocal[i], callback, progress ) )
           {
//            TextOut(hdc, 10, 10, "EnumerateFunc returned FALSE.", 29);
           } 

//          printf( "CONTAINER: %s %s\n",  lpnrLocal[i].lpLocalName, lpnrLocal[i].lpRemoteName );
         }
      }
    }
    // Process errors.
    //
    else if (dwResultEnum != ERROR_NO_MORE_ITEMS)
    {
//      NetErrorHandler(hwnd, dwResultEnum, (LPSTR)"WNetEnumResource");
      break;
    }
  }
 //
 // End do.
 //
 while(dwResultEnum != ERROR_NO_MORE_ITEMS);

 //
 // Call the GlobalFree function to free the memory.
 //
 GlobalFree((HGLOBAL)lpnrLocal);

 //
 // Call WNetCloseEnum to end the enumeration.
 //
 dwResult = WNetCloseEnum(hEnum);
  
 if(dwResult != NO_ERROR)
  { 
    //
    // Process errors.
    //
//    NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetCloseEnum");
    return FALSE;
  }

 return TRUE;
}
#endif 



#if defined LEM_WINDOWS || defined LEM_DOT_NET
HANDLE ping_icmp;
HMODULE ping_lib, hWinsock;

typedef DWORD (WINAPI *__IcmpSendEcho) (HANDLE IcmpHandle, unsigned long DestinationAddress,
							  LPVOID RequestData, WORD RequestSize,
							  void* RequestOptions, LPVOID ReplyBuffer, DWORD ReplySize,
							  DWORD Timeout);
typedef HANDLE (WINAPI *__IcmpCreateFile) ();
typedef BOOL (WINAPI *__IcmpCloseHandle) (HANDLE hIcmp);

typedef int (WINAPI* e_WSAStartup_t) (WORD, LPWSADATA);
typedef int (WINAPI* e_WSACleanup_t) ();
typedef hostent* (WINAPI* e_gethostbyname_t) (const char*);

__IcmpCreateFile IcmpCreateFile;
__IcmpSendEcho IcmpSendEcho;
__IcmpCloseHandle IcmpCloseHandle;

e_WSAStartup_t e_WSAStartup;
e_WSACleanup_t e_WSACleanup;
e_gethostbyname_t e_gethostbyname;
#endif


void lem::Network::Ip_To_A( IP4 ip, char *buf )
{
 in_addr a;
 a.S_un.S_addr = ip;
 strcpy( buf, inet_ntoa(a) );
/*
 sprintf(
         buf,
         "%u.%u.%u.%u",
         (ip&0xff000000U)>>24,
         (ip&0x00ff0000U)>>16,
         (ip&0x0000ff00U)>>8,
         (ip&0x000000ffU)
         );
*/
 return;
}


#if defined LEM_WINDOWS || defined LEM_DOT_NET
void LAN::Load_ICPM(void)
{
 WSADATA wd;

 hWinsock = LoadLibraryA("wsock32.dll");
 e_WSAStartup = (e_WSAStartup_t) GetProcAddress (hWinsock, "WSAStartup");
 e_WSACleanup = (e_WSACleanup_t) GetProcAddress (hWinsock, "WSACleanup");
 e_gethostbyname = (e_gethostbyname_t) GetProcAddress (hWinsock, "gethostbyname");

 e_WSAStartup (MAKEWORD (1, 1), &wd);
 ping_lib = LoadLibraryA("icmp.dll");
 IcmpCreateFile = (__IcmpCreateFile) GetProcAddress (ping_lib, "IcmpCreateFile");
 IcmpSendEcho = (__IcmpSendEcho) GetProcAddress (ping_lib, "IcmpSendEcho");
 IcmpCloseHandle = (__IcmpCloseHandle) GetProcAddress (ping_lib, "IcmpCloseHandle");
 ping_icmp = IcmpCreateFile ();
}
#endif


#if defined LEM_WINDOWS || defined LEM_DOT_NET
void LAN::Unload_ICPM(void)
{
 IcmpCloseHandle(ping_icmp);
 FreeLibrary (ping_lib);
 IcmpCreateFile = NULL;
 IcmpSendEcho = NULL;
 IcmpCloseHandle = NULL;
 e_WSACleanup();
 FreeLibrary(hWinsock);
}
#endif

bool LAN::ping_computer( IP4 ip, unsigned long timeout )
{
 #if defined LEM_WINDOWS || defined LEM_DOT_NET
 char buf [256];
 return (ip == 0) ? false :
		(bool) (IcmpSendEcho(ping_icmp, ip, buf, 8, NULL, buf, 256, timeout)!=0);
 #else
 return false;
 #endif
}


bool LAN::Get_Host_Name( Host &j )
{
 #if defined LEM_WINDOWS || defined LEM_DOT_NET
 if( !*j.hostname )
  {
   char buf[256];
   Ip_To_A( j.ip, buf );

   hostent *h = gethostbyaddr( (const char*)&j.ip, 256, AF_INET );
   if( h )
    {
     strcpy( j.hostname, h->h_name ); 
     return true;
    }
  }
 #endif

 return false;
}



// *****************************
// По имени получаем IP хоста
// *****************************
IP4 LAN::Get_Host_Ip( char *name )
{
 #if defined LEM_WINDOWS || defined LEM_DOT_NET
 hostent *he;

 he = e_gethostbyname (name);
 if( he == NULL )
  return 0;
 else
  return *((unsigned long*) he->h_addr_list [0]);
 #else
  return 0;
 #endif
}



// Пинг для одного заданного IP адресом хоста. Вернет true если хост откликнулся
bool LAN::Ping_Host( IP4 ip, unsigned Timeout )
{ 
 #if defined LEM_WINDOWS || defined LEM_DOT_NET
 if( !icpm_init )
  Load_ICPM();

 return ping_computer(ip,Timeout);
 #else
 return false;
 #endif
}



void LAN::InitWinSocket(void)
{
 #if defined LEM_WINDOWS || defined LEM_DOT_NET
 if( !winsock_init )
  {
   winsock_init=true;

   if( !!WSAStartup(0x0101,&ws) ) // возвращает 0, если ошибок нет.
    {
     // Ошибка запуска библиотеки WinSock!!!
    }
  }
 #endif

 return;
}




bool LAN::scan_computer(
                        IP4 ip,
                        const MCollect<unsigned> &ports,
                        unsigned long timeout,
                        unsigned *found_port
                       )
{
 #if defined LEM_WINDOWS || defined LEM_DOT_NET

 sockaddr_in san;

 SOCKET sckt = socket( AF_INET, SOCK_STREAM, 0 );

 if( sckt==INVALID_SOCKET || !!WSAGetLastError() )
  {
   // Ошибка подключения!
   return false;
  }

 // Заполняем структуру sockaddr - для использования с протоколом TCP/IP.
 san.sin_family = AF_INET;
 san.sin_addr.s_addr = ip;// inet_addr( IP.get_ip().c_str() );
 size_t sanSize = sizeof(san);

 for( Container::size_type i=0; i<ports.size(); i++ )
  { 
   san.sin_port = htons( ports[i] );

   if( connect( sckt, (sockaddr *) &san, sanSize )!=0 )
    {
     // Ошибка связывания
     DWORD err = WSAGetLastError();
    }
   else
    {
     shutdown( sckt, 1 );
     closesocket(sckt);
     sckt = NULL;

     if(found_port!=NULL)
      *found_port = ports[i];

     return true;
    }
  }
 #endif

 return false;
}




// Проверка онлайна для хостов в заданном диапазоне или по списку ip.
// Возвращает список активных хостов в виде "\\10.117.10.1\" или "\\host1\",
// причем по возможности разрешает адреса в нормальные имена
void LAN::Ping_Hosts(
                     IP4 from, IP4 upto,
                     const MCollect<IP4> iplist,
                     const MCollect<unsigned> &ports,
                     unsigned Timeout,
                     lem::Collect<lem::Path> &list,
                     LAN::Callback callback,
                     LAN::Progress progress,
                     const char *www_prefix
                    )
{
 #if defined LEM_WINDOWS || defined LEM_DOT_NET

 if( ports.empty() && !icpm_init )
  Load_ICPM();

 if( !ports.empty() && !winsock_init )
  InitWinSocket();

 in_addr ia0;
 in_addr ia1;

 ia0.S_un.S_addr = from;
 ia1.S_un.S_addr = upto;

 in_addr ia_i;
 ia_i = ia0;

 int ilist=0;
 while(true)
  {
   IP4 ip;

   if( iplist.empty() )
    {
     ip = ia_i.S_un.S_addr;
     if( ip==upto && from!=upto )
      break;
    }
   else
    {
     if( ilist==iplist.size() )
      break;
     ip = iplist[ilist++]; 
    }

   char buf[64];
   Host h;
   h.ip = ip;

   bool online=false;
   unsigned found_port=0;

   if( progress )
    {
     Ip_To_A( ip, buf );
     progress( buf );
    }

   if( ports.empty() )
    online = ping_computer( ip, Timeout );
   else
    online = scan_computer( ip, ports, Timeout, &found_port );

   if( online )
    {
     FString s;

     if( ports.empty() )
      {
       s = "\\\\";
      }
     else if( www_prefix!=NULL )
      {
       s = www_prefix;
      }

     if( Get_Host_Name( h ) )
      {
       s += h.hostname;
      }
     else
      {
       Ip_To_A( ip, buf );
       s += buf;
      }

     if( found_port!=0 )
      {
       s += ":";
       s += to_str( int(found_port) ).c_str();
      }

     if( ports.empty() )
      {
       NETRESOURCEA nr;

       nr.dwScope      = RESOURCE_GLOBALNET;
       nr.dwType       = RESOURCETYPE_DISK;  
       nr.dwUsage      = RESOURCEUSAGE_CONTAINER;
       nr.lpLocalName  = "";
       nr.lpRemoteName = (char*)s.c_str();
       nr.lpComment    = "";
       nr.lpProvider   = NULL;//TEXT("Microsoft Windows Network");

       EnumerateFunc( list, &nr, callback, progress );
      }
     else
      {
       lem::Path resource(s);
       list.push_back( resource );
       if( callback )
        callback( resource );
      } 
    }

   if( from==upto )
    break;

   ia_i.S_un.S_un_b.s_b4++;
   if( ia_i.S_un.S_addr == upto )
    break;
  }
 #endif

 return;
}



void LAN::GetLocalShares(
                         lem::Collect<lem::UFString> &shares, 
                         lem::Collect<lem::Path> &folders
                        )
{
 GetShares(NULL,shares,folders);
 return;
}



void LAN::GetShares(
                    const wchar_t *Host,
                    lem::Collect<lem::UFString> &shares, 
                    lem::Collect<lem::Path> &folders
                   )
{
 #if defined LEM_WINDOWS || defined LEM_DOT_NET

  #if defined LEM_WINDOWS && _MSC_VER<1300

   // ... not supported

  #elif defined LEM_WIN98

   // ... not supported

  #else

   BYTE *info_buffer=NULL;
   DWORD entriesread=0, totalentries=0, resume_handle=0;

   NET_API_STATUS e1 = NetShareEnum(
                                    (LMSTR)Host,
                                    0,
                                    &info_buffer,
                                    MAX_PREFERRED_LENGTH, 
                                    &entriesread,
                                    &totalentries,
                                    NULL
                                   );

   if( e1==NERR_Success )
    {
     shares.reserve(entriesread);
     folders.reserve(entriesread);

     const SHARE_INFO_0 *info = (const SHARE_INFO_0 *)info_buffer;
   
     for( DWORD i=0; i<entriesread; i++ )
      {
       const SHARE_INFO_0 &s = info[i];
     
       const wchar_t *share = (const wchar_t*)s.shi0_netname;
     
//     wprintf( L"share[%d]=%ls\n", i, share );
     
       BYTE *buf2=NULL;
       e1 = NetShareGetInfo( NULL, (LMSTR)share, 2, &buf2 );
     
       if( e1==NERR_Success )
        { 
         const SHARE_INFO_2 &si = *(const SHARE_INFO_2*)buf2;
     
         if( si.shi2_type==STYPE_DISKTREE )
          { 
           const wchar_t *local_path = (const wchar_t*)si.shi2_path;
//         wprintf( L"share[%d]=%ls localpath=%ls\n", i, share, local_path );

           if( !lem::lem_is_empty(share) && !lem::lem_is_empty(local_path) )
            {
             shares.push_back( lem::UFString(share) );
             folders.push_back( lem::Path(local_path) );
            } 
          }
        }
       
       NetApiBufferFree(buf2);
      }  
    }

   NetApiBufferFree(info_buffer);

  #endif

 #endif

 return;
}


// ***********************************************
// Getting the list of host IP's
// Заполняет список значениями IP для хоста
// ***********************************************
void LAN::GetIPs( lem::Collect<lem::FString> &ips )
{
 BOOL bRet = TRUE;
 char name[255];
 int i=0;
 PHOSTENT hostinfo;

 if( gethostname( name, sizeof(name)) == 0 )
  {
   // get the host info
   if((hostinfo = gethostbyname(name)) != NULL)
    {
     while( hostinfo->h_addr_list[i] != NULL )
      {
       char *ip_addr = inet_ntoa (*(struct in_addr *)hostinfo->h_addr_list[i]);
       ips.push_back( FString(ip_addr) );
      }
    }
  }

 return;
}


/*
GetMacAddress
Include nb30.h and link with netapi32.lib. This article is based on Q118623.
Source
Collapse

typedef struct _ASTAT_
{
	ADAPTER_STATUS adapt;
	NAME_BUFFER    NameBuff[30];
} ASTAT, * PASTAT;


CString GetMacAddress(CString sNetBiosName)
{
    ASTAT Adapter;
	
    NCB ncb;
    UCHAR uRetCode;
	
    memset(&ncb, 0, sizeof(ncb));
    ncb.ncb_command = NCBRESET;
    ncb.ncb_lana_num = 0;
	
    uRetCode = Netbios(&ncb);
	
    memset(&ncb, 0, sizeof(ncb));
    ncb.ncb_command = NCBASTAT;
    ncb.ncb_lana_num = 0;
	
    sNetBiosName.MakeUpper();
	
    FillMemory(ncb.ncb_callname, NCBNAMSZ - 1, 0x20);
	
    strcpy((char *)ncb.ncb_callname, (LPCTSTR) sNetBiosName);
	
    ncb.ncb_callname[sNetBiosName.GetLength()] = 0x20;
    ncb.ncb_callname[NCBNAMSZ] = 0x0;
	
    ncb.ncb_buffer = (unsigned char *) &Adapter;
    ncb.ncb_length = sizeof(Adapter);
	
    uRetCode = Netbios(&ncb);
    
    CString sMacAddress;
	
    if (uRetCode == 0)
    {
    	sMacAddress.Format(_T("%02x%02x%02x%02x%02x%02x"),
    	    Adapter.adapt.adapter_address[0],
            Adapter.adapt.adapter_address[1],
            Adapter.adapt.adapter_address[2],
            Adapter.adapt.adapter_address[3],
            Adapter.adapt.adapter_address[4],
            Adapter.adapt.adapter_address[5]);
    }
    return sMacAddress;
}
*/
