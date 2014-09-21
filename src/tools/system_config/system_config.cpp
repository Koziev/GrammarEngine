// -----------------------------------------------------------------------------
// File SYSTEM_CONFIG.CPP
//
// (c) by Koziev Elijah     all rights reserved 
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
// Доступ к службам системного администрирования.
//
// Взаимодействие с менеджером процессов Операционной Системы.
//
// Процедуры для работы с hardware. Большая зависимость от архитектуры и от
// используемого компилятора C/C++!
//
// 04.02.2007 - введена SupportUnicodeGui
// 07.04.2007 - добавлены IsNetfx10Installed, IsNetfx11Installed, 
//              GetNetfx10SPLevel, GetNetfx11SPLevel.  
// 13.04.2007 - GetHardwareInfo. 
//
// 27.04.2007 - new procedures IsUnix() and IsFreeBSD()
//
// 27.04.2007 - utf-8 console locale detection in SupportUnicodeConsole()
//
// 09.05.2007 - исправлена функция детектирования WinNT 4.0
//
// 28.06.2007 - добавлено обнаружение MS Windows Vista в GetHostOs
// 
// 16.04.2008 - добавлена функция IsOS64()
//
// 22.04.2008 - добавлены функции GetFilesystemCP и IsFilesystemUtf8
// -----------------------------------------------------------------------------
//
// CD->23.10.2000
// LC->29.05.2010
// --------------

#include <lem/conversions.h>
#include <lem/oformatter.h>
#include <lem/registry.h>

#if defined LEM_LINUX
 #include <sys/sysinfo.h>
 #include <sys/utsname.h>
 #include <unistd.h>
#endif

#if defined LEM_DARWIN
 #include <sys/utsname.h>
#endif

#if defined LEM_WXWIDGETS
 #include <wx/utils.h>
#endif

#if defined LEM_WINDOWS || defined LEM_DOS

 #if !defined LEM_MFC
  #include <windows.h>
 #endif

 #include <tchar.h>
 #include <Lmcons.h> // для UNLEN в GetUserName

 #if defined LEM_MSC && _MSC_VER>=1300 && _MSC_VER<1800
  #include <atlstr.h>
  #include <shldisp.h>
 #endif
 
 #include <shlobj.h>

 // In case the machine this is compiled on does not have the most recent platform SDK
 // with these values defined, define them here
 #ifndef SM_TABLETPC
  #define SM_TABLETPC		86
 #endif

 #ifndef SM_MEDIACENTER
  #define SM_MEDIACENTER	87
 #endif
#endif

#if defined LEM_QT
 #include <QDir>
#endif

#include <lem/system_config.h>


using namespace lem;
using namespace std;


/******************************************************************
Function Name:	RegistryGetValue
Description:	Get the value of a reg key
Inputs:			HKEY hk - The hk of the key to retrieve
				TCHAR *pszKey - Name of the key to retrieve
				TCHAR *pszValue - The value that will be retrieved
				DWORD dwType - The type of the value that will be retrieved
				LPBYTE data - A buffer to save the retrieved data
				DWORD dwSize - The size of the data retrieved
Results:		true if successful, false otherwise
******************************************************************/
#if defined LEM_WINDOWS
#if defined LEM_QT
static bool RegistryGetValue(HKEY hk, const wchar_t * pszKey, const wchar_t * pszValue, DWORD dwType, LPBYTE data, DWORD dwSize )
#else
static bool RegistryGetValue(HKEY hk, const TCHAR * pszKey, const TCHAR * pszValue, DWORD dwType, LPBYTE data, DWORD dwSize)
#endif
{
 HKEY hkOpened;

 // Try to open the key
 #if defined LEM_QT
 if( RegOpenKeyExW(hk, pszKey, 0, KEY_READ | KEY_WRITE, &hkOpened) != ERROR_SUCCESS )
 #else
 if( RegOpenKeyEx(hk, pszKey, 0, KEY_READ | KEY_WRITE, &hkOpened) != ERROR_SUCCESS )
 #endif
  {
   return false;
  }

 // If the key was opened, try to retrieve the value
 #if defined LEM_QT
 if( RegQueryValueExW(hkOpened, pszValue, 0, &dwType, (LPBYTE)data, &dwSize) != ERROR_SUCCESS )
 #else
 if( RegQueryValueEx(hkOpened, pszValue, 0, &dwType, (LPBYTE)data, &dwSize) != ERROR_SUCCESS )
 #endif
  {
   RegCloseKey(hkOpened);
   return false;
  }
	
 // Clean up
 RegCloseKey(hkOpened);

 return true;
}
#endif



// *****************************************************************
// Возвращается имя домашнего каталога для юзера в текущей сессии.
// *****************************************************************
const lem::Path lem::System_Config::GetHomeDir(void)
{
 #if defined LEM_QT

  QString h = QDir::toNativeSeparators(QDir::homePath());
  lem::UFString us(h);
  return lem::Path(us);

 #elif defined LEM_WINDOWS || defined LEM_DOS

 wchar_t wpath[ lem::Path::MaxLen+1 ];
 memset( wpath, 0, sizeof(wpath) );
 if( SHGetSpecialFolderPathW(NULL,wpath,0x0005 /*CSIDL_PERSONAL*/,FALSE)==TRUE )
  {
   if( wpath[0]!=0 )
    {
     if( wpath[ wcslen(wpath)-1 ]!=L'\\' )
      wcscat( wpath, L"\\" );

     lem::Path p(wpath);
     return p;
    }
  }

 // Эта переменная окружения существует только для Win NT.
 const char *home = getenv( "USERPROFILE" );

 if( !home )
  {
   home = getenv( "HOMEPATH" );
   if( !home )
    {
     // Для Win9x все гораздо корявее - один каталог на всех...
     home = getenv( "windir" );

     if( !home )
      return lem::Path("c:\\");
    }
  }

 char apath[ lem::Path::MaxLen+1 ];
 strcpy( apath, home );
 OemToCharA( apath, apath );

 std::string p(home);

 if( !p.empty() && p.at( p.length()-1 )!='\\' )
  p += '\\';

 std::wstring u( to_unicode( p ) );
 return lem::Path(u);

 #elif defined LEM_UNIX

 const char *home = getenv( "HOME" );

 if( !home )
  home = getenv("HOMEPATH");

 if( home!=NULL )
  {
   std::string p(home);

   if( !p.empty() && !lem::Path::IsPathDelimiter( p.at( p.length()-1 ) ) )
    p += lem::Path::GetPathDelimiter();

   return lem::Path(p);
  }
  
 return lem::Path( "/home/" );

 #elif defined LEM_WXWIDGETS

  return lem::Path( wxGetUserHome( wxGetUserId() ) );

 #else

  #error You have to implement get_home_dir() for this OS!

 #endif
}

// **********************************************************
// Возвращается путь к каталогу "...\юзер\Application Data\" 
// или его аналогу для текущей платформы, для сохранения
// данных программы.
// **********************************************************
const lem::Path lem::System_Config::GetAppdataDir(void)
{
 #if defined LEM_WINDOWS || defined LEM_DOS

 wchar_t wpath[ lem::Path::MaxLen+1 ];
 memset( wpath, 0, sizeof(wpath) );

 #if defined LEM_QT
 if( SHGetFolderPathW( NULL, 0x001a/*CSIDL_COMMON_APPDATA*/, (HANDLE)-1, 0 /*SHGFP_TYPE_CURRENT*/, wpath )==S_OK )
 #else
 if( SHGetSpecialFolderPathW(NULL,wpath,0x001a/*CSIDL_COMMON_APPDATA*/,FALSE)==TRUE )
 #endif
  {
   if( wpath[0]!=0 )
    {
     if( wpath[ wcslen(wpath)-1 ]!=L'\\' )
      wcscat( wpath, L"\\" );

     lem::Path p(wpath);
     return p;
    }
  }

 // Эта переменная окружения существует только для Win 2000/XP/2003.
 // ATTENTION! Ее нет в WinNT 4.0!
 const char *path = getenv( "APPDATA" );

 if( !path )
  {
   if( IsNT4() )
    {
     lem::Path p( GetHomeDir() );
     p.AppendPathDelimiter(); 
     return p;
    }

   // Для Win98/Me каталог c:\Windows\Application Data

   std::string p;

   const char *root = getenv( "windir" ); // Win 98 / ME
   if( root!=NULL )
    {
     p = root;

     if( !p.empty() && p.at( p.length()-1 )!='\\' )
      p += '\\';

     p += "Application Data\\";
    }

   if( !p.empty() && (GetFileAttributesA( p.c_str() )&FILE_ATTRIBUTE_DIRECTORY)==FILE_ATTRIBUTE_DIRECTORY )
    {
     std::wstring u( to_unicode( p ) );//, &lem::UI::get_UI().GetTtyCp() ) );
     return lem::Path(u);
    }

   // Возвращаем путь к домашнему каталогу
   return GetHomeDir();
  }
 else
  {
   char apath[ lem::Path::MaxLen+1 ];
   strcpy( apath, path );
   OemToCharA( apath, apath );

   std::string p( apath );
   if( !p.empty() && p.at( p.length()-1 )!='\\' )
    p += '\\';
 
   std::wstring u( to_unicode( p ) );
   return lem::Path(u);
  }

 #elif defined LEM_UNIX

 const char *path = getenv( "HOME" );
 return lem::Path(path);

 #else

  #error You have to implement the function for this OS!

 #endif
}


 
bool lem::System_Config::SupportUnicodeGui(void)
{
 #if defined LEM_UNIX
  return false;
 #elif defined LEM_WINDOWS 
  // Для Win9x - есть проблемы.
  if( IsWin9x() )
   return false;

  return true;
 #else
  return false; 
 #endif
}


// **********************************************************
// Returns true, if OS supports unicode in filenames.
// For MS Windows NT, the wide versions of filesystem access
// API calls should be used.
// For Linux, utf-8 is used to encode the filenames.
// **********************************************************
bool lem::System_Config::SupportUnicodeFilenames(void)
{
 #if defined LEM_LINUX || defined LEM_DARWIN

  static bool inited=false; 
  static bool utf8_locale=false;
  if( !inited )
   {
    const char *lang = getenv("LANG");
    if( lang!=NULL && (lem::lem_findi( lang, "UTF-8" )!=UNKNOWN || lem::lem_findi( lang, "UTF8" )!=UNKNOWN) )
     utf8_locale = true;
   
    inited = true;
   }

  return utf8_locale;

 #elif defined LEM_UNIX
  return false;
 #elif defined LEM_WINDOWS
  // Для Win9x - есть проблемы.
  if( IsWin9x() )
   return false;

  return true;
 #else
  return false;  
 #endif
}


bool lem::System_Config::SupportUnicodeConsole(void)
{
 #if defined LEM_UNIX || defined LEM_DARWIN

  // utf-8 консоль под Linux
  const char *lang = getenv("LANG");
  if( lang!=NULL && (lem::lem_findi( lang, "UTF-8" )!=UNKNOWN || lem::lem_findi( lang, "UTF8" )!=UNKNOWN) )
   return true;
   
  return false;
 #elif defined LEM_WINDOWS
  // Для Win9x - есть проблемы.
  if( IsWin9x() )
   return false;

  // Линейка WinNT нормально поддерживает UNICODE
  return true;
 #else
  return false; 
 #endif
}



bool lem::System_Config::IsWin9x(void)
{
 #if defined LEM_WINDOWS

 static bool first=true;
 static bool is_9x=false;

 if( first )
  {
   first = false;
   OSVERSIONINFO info;
   memset( &info, 0, sizeof(info) );
   info.dwOSVersionInfoSize = sizeof(info);
   GetVersionEx( &info );

   if(
      info.dwPlatformId==VER_PLATFORM_WIN32s ||
      info.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS
     )
    {
     is_9x=true;
     return true;
    }

   if(
      info.dwPlatformId!=VER_PLATFORM_WIN32_NT &&
      info.dwMajorVersion==4 &&
      (
       info.dwMinorVersion==0 ||
       info.dwMinorVersion==10 ||
       info.dwMinorVersion==90
      )
     )  
    {
     is_9x=true;
     return true;
    }

   is_9x=false;
  }

 return is_9x; 

 #endif
 
 return false;
}



bool lem::System_Config::IsNT4(void)
{
 #if defined LEM_WINDOWS

 static bool first=true;
 static bool is_nt4=false;

 if( first )
  {
   first = false;
   OSVERSIONINFO info;
   memset( &info, 0, sizeof(info) );
   info.dwOSVersionInfoSize = sizeof(info);
   GetVersionEx( &info );

   if(
      info.dwPlatformId==VER_PLATFORM_WIN32s ||
      info.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS
     )
    {
     is_nt4=false; 
     return false;
    }

   if(
      info.dwPlatformId==VER_PLATFORM_WIN32_NT &&
      info.dwMajorVersion==4 &&
      info.dwMinorVersion==0
     )  
    { 
     const char *appdir = getenv("APPDIR");
     if( appdir==NULL )
      { 
       is_nt4 = true;
       return true;
      }
    } 

   is_nt4 = false;
   return false;
  }

 return is_nt4;

 #else
 return false; 
 #endif
}


bool lem::System_Config::IsWin2k(void)
{
 #if defined LEM_WINDOWS

 static bool first=true;
 static bool is_2k=false;

 if( first )
  {
   first = false;

   OSVERSIONINFO info;
   memset( &info, 0, sizeof(info) );
   info.dwOSVersionInfoSize = sizeof(info);
   GetVersionEx( &info );

   if(
      info.dwPlatformId==VER_PLATFORM_WIN32_NT &&
      info.dwMajorVersion==5 &&
      info.dwMinorVersion==0
     )  
    { 
     is_2k = true;
     return true;
    } 

   is_2k = false;
   return false;
  }

 return is_2k;

 #else
 return false; 
 #endif
}


bool lem::System_Config::IsTabletPC(void)
{
 #if defined LEM_WINDOWS
 return GetSystemMetrics(SM_TABLETPC) != 0;
 #else
 return false;
 #endif
}


bool lem::System_Config::IsMediaCenter(void)
{
 #if defined LEM_WINDOWS
 return GetSystemMetrics(SM_MEDIACENTER) != 0;
 #else
 return false;
 #endif
}


// ********************************************************
// ВОзвращает описание версии установленного .NET Framework
// ********************************************************
const std::string lem::System_Config::GetNetfxInfo(void)
{
 #if defined LEM_WINDOWS
 std::string ret;

 if( IsNetfx11Installed() )
  {
   ret = ".NET v.1.1"; 

   int sp = GetNetfx11SPLevel();
   if( sp!=-1 )
    {
     ret += " SP v.";
     ret += lem::to_str(sp).c_str();
    }
  }
 else if( IsNetfx10Installed() )
  {
   ret = ".NET v.1.0"; 

   int sp = GetNetfx10SPLevel();
   if( sp!=-1 )
    {
     ret += " SP v.";
     ret += to_ascii( UFString(sp) ).c_str();
    }
  }

 return ret;

 #else
  return "";
 #endif
}



// ********************************************************
// На какой платформе исполняется программа
// ********************************************************
const std::string lem::System_Config::GetHostOs( bool detailed )
{
 if( !detailed )
  {
   #if defined LEM_DOT_NET
    return ".NET";
   #elif defined LEM_WINDOWS
    #if defined LEM_64
    return "Win64";
    #else
    return "Win32";    
    #endif
   #elif defined LEM_LINUX

    struct utsname buf;
    memset( &buf, 0, sizeof(buf) );
    int r = uname(&buf);
    if( r==0 )
     {
      std::string s;
      s += buf.sysname;
      s += " ";
      s += buf.release;
      s += " ";
      s += buf.machine;
      return s;
     }
    else
     {
      #if __SIZEOF_POINTER__==8
      return "Linux x86_64";
      #else
      return "Linux";
      #endif
     }

   #elif defined LEM_DARWIN

    struct utsname buf;
    memset( &buf, 0, sizeof(buf) );
    int r = uname(&buf);
    if( r==0 )
     {
      std::string s;
      s += buf.sysname;
      s += " ";
      s += buf.release;
      s += " ";
      s += buf.machine;
      return s;
     }
    else
     {
      #if defined LEM_64
      return "Darwin x86_64";
      #else
      return "Darwin";
      #endif
     }
   #elif defined LEM_BSD
    #if defined __FreeBSD__
     return "FreeBSD";
    #elif defined __OpenBSD__
     return "OpenBSD";
    #else
     return "BSD Unix";
    #endif
   #elif defined LEM_UNIX
    return "Unix";
   #elif defined LEM_DOS
    return "DOS";        
   #endif
  } 

 #if defined LEM_WINDOWS

 std::string ret;

 if( IsTabletPC() )
  {
   ret = "Windows Tablet PC";
   return ret;
  }

 BOOL bOsVersionInfoEx;
 OSVERSIONINFOEXA osvi;

 // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
 // If that fails, try using the OSVERSIONINFO structure.

 ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXA));
 osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);

 if( (bOsVersionInfoEx = GetVersionExA( (OSVERSIONINFOA *) &osvi) )!=0 )
  {
   osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFOA);
   if( GetVersionExA ( (OSVERSIONINFOA *) &osvi) )
    {
     if( osvi.dwMajorVersion>=5 )
      {
       lem::WinRegistry reg;
       reg.HKLM();
       if( reg.seek_subkey( "Software\\Microsoft\\Windows NT\\CurrentVersion" ) )
        {
         lem::FString product = reg.get_string( "ProductName" );
         if( !product.empty() )
          {
           ret = product.c_str();  
 
           // Номер сервис-пака
           lem::FString sp = osvi.szCSDVersion;// reg.get_string( "CSDVersion" );
           if( !sp.empty() )
            { 
             ret += ' ';
             ret += sp.c_str();
            } 
          }
        }  
      }
   
     if( ret.empty() )
      switch (osvi.dwPlatformId)
      {
       // Test for the Windows NT product family.
       case VER_PLATFORM_WIN32_NT:
        // Test for the specific product family.
        if( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1 )
         ret = "MS Windows 7 ";
        else if( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 )
         {
          ret = "MS Windows Vista ";
         }
        else if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
         {
          ret = "MS Windows Server 2003 family, ";
         }
        else if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
         { 
          ret = "MS Windows XP ";
 
          if( IsMediaCenter() )
           ret += "Media Center Edition "; 
         }
        else if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
         ret = "MS Windows 2000 ";
        else if( osvi.dwMajorVersion <= 4 )
         ret = "MS Windows NT ";

        // Test for specific product on Windows NT 4.0 SP6 and later.
        if( bOsVersionInfoEx )
         {
          #if _MSC_VER>=1300
          // Test for the workstation type.
          if( osvi.wProductType == VER_NT_WORKSTATION )
           {
            if( osvi.dwMajorVersion == 4 )
             ret += "Workstation 4.0 ";
            else if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
             ret += "Home Edition ";
            else
             ret += "Professional ";
           }
          // Test for the server type.
          else if( osvi.wProductType == VER_NT_SERVER )
           {
            if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
             {
              if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
               ret += "Datacenter Edition ";
              else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
               ret += "Enterprise Edition ";
              else if ( osvi.wSuiteMask == VER_SUITE_BLADE )
               ret += "Web Edition ";
              else
               ret += "Standard Edition ";
             }
            else if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
             {
              if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
               ret += "Datacenter Server ";
              else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
               ret += "Advanced Server ";
              else
               ret += "Server ";
             }
            else  // Windows NT 4.0 
             {
              if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
               ret += "Server 4.0, Enterprise Edition ";
              else
               ret +="Server 4.0 ";
             }
           }
          #endif
         }
        else  // Test for specific product on Windows NT 4.0 SP5 and earlier
         {
          HKEY hKey;
          const int BUFSIZE=256;
          char szProductType[BUFSIZE];
          DWORD dwBufLen=BUFSIZE;
          LONG lRet;
 
          lRet = RegOpenKeyExA( HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\ProductOptions", 0, KEY_QUERY_VALUE, &hKey );
          if( lRet != ERROR_SUCCESS )
           ret = "MS Windows";
          else
           {
            lRet = RegQueryValueExA( hKey, "ProductType", NULL, NULL, (LPBYTE) szProductType, &dwBufLen);
            if( (lRet != ERROR_SUCCESS) || (dwBufLen > BUFSIZE) )
             ret = "MS Windows";
            else
             {
              RegCloseKey( hKey );
 
              if( strcmpi( "WINNT", szProductType) == 0 )
               ret += "Workstation ";
              else if( strcmpi( "LANMANNT", szProductType) == 0 )
               ret += "Server ";
              else if( strcmpi( "SERVERNT", szProductType) == 0 )
               ret += "Advanced Server ";

              ret += lem::to_str( (int)osvi.dwMajorVersion ).c_str();
              ret += ".";
              ret += lem::to_str( (int)osvi.dwMinorVersion ).c_str();
             }
           }
         }

        // Display service pack (if any) and build number.

        if( osvi.dwMajorVersion == 4 && strcmpi( osvi.szCSDVersion, "Service Pack 6" ) == 0 )
         {
          HKEY hKey;
          LONG lRet;

          // Test for SP6 versus SP6a.
          lRet = RegOpenKeyExA( HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009", 0, KEY_QUERY_VALUE, &hKey );
          if( lRet == ERROR_SUCCESS )
           {
            ret += "Service Pack 6a (Build ";
            ret += lem::to_str( int(osvi.dwBuildNumber & 0xFFFF) ).c_str();
            ret += ")";
           }
          else // Windows NT 4.0 prior to SP6a
           {
            ret += osvi.szCSDVersion;
            ret += " (Build ";
            ret += lem::to_str( int(osvi.dwBuildNumber & 0xFFFF) ).c_str();
            ret += ") ";
           } 

          RegCloseKey( hKey );
         }
        else // Windows NT 3.51 and earlier or Windows 2000 and later
         {
          ret += osvi.szCSDVersion;
          ret += " (Build ";
          ret += lem::to_str( int(osvi.dwBuildNumber & 0xFFFF) ).c_str();
          ret += ") ";
         }

        break;

       // Test for the Windows 95 product family.
       case VER_PLATFORM_WIN32_WINDOWS:

       if( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0 )
        {
         ret += "MS Windows 95 ";
         if( osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B' )
          ret += "OSR2 ";
         } 

       if( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10 )
        {
         ret += "MS Windows 98 ";
         if( osvi.szCSDVersion[1] == 'A' )
          ret += "SE ";
         } 

       if( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90 )
        {
         ret += "MS Windows Millennium Edition";
        } 
       break;

      case VER_PLATFORM_WIN32s:
       ret += "Microsoft Win32s";
       break;
     }
    }

   if( IsOS64() )
    ret += " x64";

  }
 else
  {
   const char *os = getenv( "OS" );

   if( !os )
    {
     #if defined LEM_WXWIDGETS
     ret = to_ascii( std::wstring( wxGetOsDescription() ) );
     #else
     ret = "unknown MS Windows";
     #endif
    }
   else
    ret = std::string(os);
  }

  #if defined LEM_DOT_NET
   std::string fx = GetNetfxInfo();
   if( !fx.empty() )
    {
     ret += " ";
     ret += fx;
    }
  #endif

  return ret;

 #elif defined LEM_LINUX

  struct utsname uninfo;
  if( uname(&uninfo) < 0 )
   {
    return std::string( "cannot get system name" );
   }

  std::string res( uninfo.sysname );
  res += " ";
  res += uninfo.release;
 
  return res;

 #elif defined LEM_WXWIDGETS

  return to_ascii( std::wstring( wxGetOsDescription() ) );

 #elif defined LEM_UNIX

 return string( "unix" );

 #else

  return std::string( "unknown os" );

 #endif
}



const std::string lem::System_Config::GetHostName(void)
{
 #if defined LEM_WXWIDGETS
 
 return to_ascii( std::wstring(wxGetHostName().c_str()) );

 #elif defined LEM_WINDOWS

 char name[MAX_COMPUTERNAME_LENGTH+1]="";
 DWORD Size=MAX_COMPUTERNAME_LENGTH;

 if(!GetComputerNameA( name, &Size ))
  return std::string("unaccessible");

 return std::string(name);
 
 #else

  return std::string("unknown");

 #endif
}


// *************************************************************************
// Проверка простейшей методики определения режима выравнивания полей в
// структурах на границу слов. Проверена для нескольких компиляторов:
//
//  Borland C++ 3.1 (DOS): byte + word alignment
//  Borland C++ 4.5 (Win32 console): byte + word + dword + qword alignment
//  Borland C++ Builder v.5.01: byte+word+dword+qword alignment
//  Watcom C++ v.10,11 (DOS Extender): byte + word + dword + qword alignment
//  GNU C++ (DJGPP) Compiler: dword alignment
//
// Написать код для обнаружения выравнивания на границу параграфа (16 байт)
// для Borland C++ Builder не удалось, так как встроенного типа с размером
// 16 байт нет, а 10-ти байтовый long double для IBM PC не даёт нужного
// эффекта. Для Watcom C++ v.11 определение выравнивания на 16-байтный
// параграф работает нормально.
// *************************************************************************

// 17 -> byte
// 18 -> word
// 20 -> double word
// 24 -> quadruple word
// 32 -> octuple word (16-byte boundary alignment)
namespace lem
{
 struct ss_6 { double a; char b; double c; };
}

int lem::System_Config::GetAlignmentSize(void)
{
 #if defined LEM_BORLAND
 #pragma warn-rch
 #endif

 #if defined LEM_BORLAND
 #pragma warn-ccc
 #endif

 switch( sizeof(ss_6) )
 {
  case 32: return 16;
  case 24: return 8;
  case 20: return 4;
  case 18: return 2;
  case 17: return 1;
  default: LEM_STOPIT; return 32; // More than 16 bytes boundary alignment!
 }

 #if defined LEM_BORLAND
 #pragma warn+ccc
 #endif

 #if defined LEM_BORLAND
 #pragma warn+rch
 #endif
}

// *************************************************************************
// Мы должны определить тип адресной архитектуры, а именно - используется ли
// сегментация, каков размер сегмента и смещения. Возвращается символическая
// константа либо UNKNOWN.
// *************************************************************************
lem::System_Config::AddressingType lem::System_Config::GetAddressingType(void)
{
 #if defined LEM_WXWIDGETS
 if( wxIsPlatform64Bit() )
  return ADDRESSING_64;
 #endif

 char* a = NULL;

 if( sizeof(a)==8 )
  return ADDRESSING_64;

 a += 65535;
 a++;

 // Если теперь значение a снова равно NULL, то имеем дело с архитектурой
 // 16+16, то есть значение сегмента (16 бит) и значение смещения (16 бит).
 if( !a )
  return ADDRESSING_16_16;

 if( sizeof(a)==4 )
  return ADDRESSING_32;

 return ADDRESSING_UNKNOWN;
}



bool lem::System_Config::IsLinux(void)
{
 static bool flag=false;
 static bool init=false;

 if( !init )
  {
   if(
      (getenv("PATH")!=NULL && *getenv("PATH")=='/') ||
      (getenv("TMP")!=NULL && *getenv("TMP")=='/') ||
      (getenv("TMPDIR")!=NULL && *getenv("TMPDIR")=='/') ||
      (getenv("TERM")!=NULL && strcmp(getenv("TERM"),"linux")==0 )
     )
    flag = true;

   init=true;
  }
 
 return flag;
}


bool lem::System_Config::IsUnix(void)
{
 #if defined LEM_UNIX
 return true;
 #else
 return false;
 #endif
}


bool lem::System_Config::IsFreeBSD(void)
{
 #if defined LEM_BSD
 return true;
 #else
 return false;
 #endif
}



#if defined LEM_WINDOWS

 #if defined LEM_QT

 static const wchar_t g_szNetfx10RegKeyName[] = L"Software\\Microsoft\\.NETFramework\\Policy\\v1.0";
 static const wchar_t g_szNetfx10RegKeyValue[] = L"3705";
 static const wchar_t g_szNetfx10SPxMSIRegKeyName[] = L"Software\\Microsoft\\Active Setup\\Installed Components\\{78705f0d-e8db-4b2d-8193-982bdda15ecd}";
 static const wchar_t g_szNetfx10SPxOCMRegKeyName[] = L"Software\\Microsoft\\Active Setup\\Installed Components\\{FDC11A6F-17D1-48f9-9EA3-9051954BAA24}";
 static const wchar_t g_szNetfx10SPxRegValueName[] = L"Version";
 static const wchar_t g_szNetfx11RegKeyName[] = L"Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322";
 static const wchar_t g_szNetfx11SPxRegKeyName[] = L"Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322";
 static const wchar_t g_szNetfx11RegValueName[] = L"Install";
 static const wchar_t g_szNetfx11SPxRegValueName[] = L"SP";

 #elif defined _UNICODE && defined _MSC_VER && _MSC_VER<1300

 // Constants that represent registry key names and value names to use for detection

 static const TCHAR g_szNetfx10RegKeyName[] = _T("Software\\Microsoft\\.NETFramework\\Policy\\v1.0");
 static const TCHAR g_szNetfx10RegKeyValue[] = _T("3705");
 static const TCHAR g_szNetfx10SPxMSIRegKeyName[] = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{78705f0d-e8db-4b2d-8193-982bdda15ecd}");
 static const TCHAR g_szNetfx10SPxOCMRegKeyName[] = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{FDC11A6F-17D1-48f9-9EA3-9051954BAA24}");
 static const TCHAR g_szNetfx10SPxRegValueName[] = _T("Version");
 static const TCHAR g_szNetfx11RegKeyName[] = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322");
 static const TCHAR g_szNetfx11SPxRegKeyName[] = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322");
 static const TCHAR g_szNetfx11RegValueName[] = _T("Install");
 static const TCHAR g_szNetfx11SPxRegValueName[] = _T("SP");

 #else

 static const TCHAR g_szNetfx10RegKeyName[] = _T("Software\\Microsoft\\.NETFramework\\Policy\\v1.0");
 static const TCHAR g_szNetfx10RegKeyValue[] = _T("3705");
 static const TCHAR g_szNetfx10SPxMSIRegKeyName[] = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{78705f0d-e8db-4b2d-8193-982bdda15ecd}");
 static const TCHAR g_szNetfx10SPxOCMRegKeyName[] = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{FDC11A6F-17D1-48f9-9EA3-9051954BAA24}");
 static const TCHAR g_szNetfx10SPxRegValueName[] = _T("Version");
 static const TCHAR g_szNetfx11RegKeyName[] = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322");
 static const TCHAR g_szNetfx11SPxRegKeyName[] = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322");
 static const TCHAR g_szNetfx11RegValueName[] = _T("Install");
 static const TCHAR g_szNetfx11SPxRegValueName[] = _T("SP");

 #endif 

#endif

/******************************************************************
Function Name:	IsNetfx10Installed
Description:	Uses the detection method recommended at
				http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnnetdep/html/dotnetfxref.asp
				to determine whether the .NET Framework 1.0 is
				installed on the machine
Inputs:			NONE
Results:		true if the .NET Framework 1.0 is installed
				false otherwise
******************************************************************/
bool lem::System_Config::IsNetfx10Installed(void)
{
 #if defined LEM_WINDOWS

  #if defined LEM_QT
   char szRegValue[MAX_PATH];
   return RegistryGetValue( HKEY_LOCAL_MACHINE, g_szNetfx10RegKeyName, g_szNetfx10RegKeyValue, NULL, (LPBYTE)szRegValue, MAX_PATH );
  #else
   TCHAR szRegValue[MAX_PATH];
   return RegistryGetValue( HKEY_LOCAL_MACHINE, g_szNetfx10RegKeyName, g_szNetfx10RegKeyValue, NULL, (LPBYTE)szRegValue, MAX_PATH );
  #endif

 #else
 return false; 
 #endif
}


/******************************************************************
Function Name:	IsNetfx11Installed
Description:	Uses the detection method recommended at
				http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnnetdep/html/redistdeploy1_1.asp
				to determine whether the .NET Framework 1.1 is
				installed on the machine
Inputs:			NONE
Results:		true if the .NET Framework 1.1 is installed
				false otherwise
******************************************************************/
bool lem::System_Config::IsNetfx11Installed(void)
{
 #if defined LEM_WINDOWS
 bool bRetValue = false;
 DWORD dwRegValue=0;

 if( RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx11RegKeyName, g_szNetfx11RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)) )
  {
   if( 1 == dwRegValue )
    bRetValue = true;
  }

 return bRetValue;
 #else
 return false;
 #endif
}


/******************************************************************
Function Name:	GetNetfx10SPLevel
Description:	Uses the detection method recommended at
				http://blogs.msdn.com/astebner/archive/2004/09/14/229802.aspx
				to determine what service pack for the 
				.NET Framework 1.0 is installed on the machine
Inputs:			NONE
Results:		integer representing SP level for .NET Framework 1.0
******************************************************************/
int lem::System_Config::GetNetfx10SPLevel(void)
{
 #if defined LEM_WINDOWS
 TCHAR szRegValue[MAX_PATH];
 TCHAR *pszSPLevel = NULL;
 int iRetValue = -1;
 bool bRegistryRetVal = false;

 // TODO - Need to detect what OS we are running on so we know what
 // registry key to use to look up the SP level
 if( IsTabletPC() || IsMediaCenter() )
  bRegistryRetVal = RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx10SPxOCMRegKeyName, g_szNetfx10SPxRegValueName, NULL, (LPBYTE)szRegValue, MAX_PATH);
 else
  bRegistryRetVal = RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx10SPxMSIRegKeyName, g_szNetfx10SPxRegValueName, NULL, (LPBYTE)szRegValue, MAX_PATH);

 if( bRegistryRetVal )
  {
   // This registry value should be of the format
   // #,#,#####,# where the last # is the SP level
   // Try to parse off the last # here


   #if defined _UNICODE && defined _MSC_VER && _MSC_VER<1300
    pszSPLevel = _tcsrchr( szRegValue, L',' );
   #else
    pszSPLevel = _tcsrchr( szRegValue, L',' );
   #endif

   if( NULL != pszSPLevel )
    {
     // Increment the pointer to skip the comma
     pszSPLevel++;

     // Convert the remaining value to an integer
     #if defined _UNICODE && defined _MSC_VER && _MSC_VER<1300
      iRetValue = _ttoi(pszSPLevel);
     #else
      iRetValue = _ttoi(pszSPLevel);
     #endif
    }
  }

 return iRetValue;
 #else
 return -1;
 #endif
}


/******************************************************************
Function Name:	GetNetfx11SPLevel
Description:	Uses the detection method recommended at
				http://blogs.msdn.com/astebner/archive/2004/09/14/229574.aspx
				to determine what service pack for the 
				.NET Framework 1.1 is installed on the machine
Inputs:			NONE
Results:		integer representing SP level for .NET Framework 1.1
******************************************************************/
int lem::System_Config::GetNetfx11SPLevel(void)
{
 #if defined LEM_WINDOWS
 DWORD dwRegValue=0;

 if( RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx11SPxRegKeyName, g_szNetfx11SPxRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)) )
  {
   return (int)dwRegValue;
  }

 // We can only get here if the .NET Framework 1.1 is not
 // installed or there was some kind of error retrieving
 // the data from the registry
 return -1;
 #else
 return -1;
 #endif
}


// *******************************************************
// Возвращает имя пользователя (логин) для текущей сессии
// *******************************************************
const std::string lem::System_Config::GetUserLogin(void)
{
 #if defined LEM_UNIX
  const char *s = getlogin();
  if( s==NULL )
   {
    s = getenv("LOGNAME");
    if( s!=NULL ) 
     return std::string(s);
     
    s = getenv("USER");
    if( s!=NULL ) 
     return std::string(s);

    return std::string("");          
   }     
  else    
   return std::string( s );
 #elif defined LEM_WINDOWS
  char uname[ UNLEN+1 ];
  memset( uname, 0, sizeof(uname) );
  DWORD l=UNLEN;
  GetUserNameA( uname, &l );
  return std::string(uname);
 #else
  return std::string("");
 #endif
}




// ************************************************************
// Show some brief info about current session.
// ************************************************************
void lem::System_Config::PrintInfo( lem::OFormatter &dst )
{
 dst.printf(
            "Session info:\n user=%s\n app_dir=%us\n home_dir=%us\n tmp_dir=%us\n"
            " unicode console=%b\n"
            " unicode filenames=%b\n"
            " unicode GUI=%b\n"
            , GetUserLogin().c_str()
            , lem::System_Config::GetAppdataDir().GetUnicode().c_str()
            , lem::System_Config::GetHomeDir().GetUnicode().c_str()
            , lem::Path::GetTmpFolder().GetUnicode().c_str()
            , lem::System_Config::SupportUnicodeConsole()
            , lem::System_Config::SupportUnicodeFilenames()
            , lem::System_Config::SupportUnicodeGui()
           );

 return;  
}


// *********************************************************
// Filename are case sensitive (false for Windows,
// true for Unix by default).
// *********************************************************
bool lem::System_Config::FilenamesCaseSensitive(void)
{
 #if defined LEM_WINDOWS || defined LEM_DOS
 return false;
 #elif defined LEM_UNIX
 return true;
 #else
  #error
 #endif
}


// **************************************************************
// Returns true for L'-' on Unix/Windows and L'/' on Windows/Dos
// **************************************************************
bool lem::System_Config::IsCmdLineOption( wchar_t ch )
{
 #if defined LEM_UNIX

 return ch==L'-';

 #elif defined LEM_WINDOWS

 return ch==L'-' || ch==L'\\';
 
 #elif defined LEM_DOS

 return ch==L'\\';

 #else

 #error

 #endif
}


bool lem::System_Config::IsCmdLineOption( char ch )
{
 return lem::System_Config::IsCmdLineOption( (wchar_t)ch );
}



// *********************************************************
// Поддерживает ли платформа Unicode строки в вызовах API
// *********************************************************
bool lem::System_Config::SupportUnicodeAPI(void)
{
 #if defined LEM_WINDOWS
 return !IsWin9x();
 #else
 return false;
 #endif
}


bool lem::System_Config::IsVista(void)
{
 #if defined LEM_WINDOWS

 BOOL bOsVersionInfoEx;
 OSVERSIONINFOEXA osvi;

 // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
 // If that fails, try using the OSVERSIONINFO structure.

 ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXA));
 osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);

 if( (bOsVersionInfoEx = GetVersionExA( (OSVERSIONINFOA *) &osvi) )!=0 )
  {
   osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFOA);
   if( GetVersionExA ( (OSVERSIONINFOA *) &osvi) )
    {
     if( osvi.dwPlatformId==VER_PLATFORM_WIN32_NT && osvi.dwMajorVersion==6 && osvi.dwMinorVersion==0 )
      return true;  
    }
  }

  return false;

 #else
  return false;
 #endif
}


bool lem::System_Config::IsVistaOrNewer(void)
{
 #if defined LEM_WINDOWS

 BOOL bOsVersionInfoEx;
 OSVERSIONINFOEXA osvi;

 // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
 // If that fails, try using the OSVERSIONINFO structure.

 ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXA));
 osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);

 if( (bOsVersionInfoEx = GetVersionExA( (OSVERSIONINFOA *) &osvi) )!=0 )
  {
   osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFOA);
   if( GetVersionExA ( (OSVERSIONINFOA *) &osvi) )
    {
     if( osvi.dwPlatformId==VER_PLATFORM_WIN32_NT && osvi.dwMajorVersion>=6 )
      return true;  
    }
  }

  return false;

 #else
  return false;
 #endif
}



bool lem::System_Config::IsOS64(void)
{
 #if defined LEM_WXWIDGETS

 return wxIsPlatform64Bit();

 #elif defined LEM_WINDOWS
 
 return getenv("ProgramFiles(x86)")!=NULL;
 
 #elif defined LEM_LINUX && defined LEM_64
 
 return true; 

 #else

 return false;

 #endif
}


bool lem::System_Config::IsFilesystemUtf8( const lem::Path *path )
{
 #if defined LEM_WINDOWS
  return false;
 #else
  return SupportUnicodeFilenames();
 #endif
}


// *********************************************************************************
// Возвращает кодировку имен файлов, опционально может быть указан также некий путь
// к файлу или папке, если файловая система допускает монтирование множества
// устройств с разными настройками кодировок.
// *********************************************************************************
const lem::CodeConverter* lem::System_Config::GetFilesystemCP( const lem::Path *path )
{
 #if defined LEM_WINDOWS
  int cpi=0;

  BOOL f = AreFileApisANSI();
  if( f!=0 )
   {
    cpi = GetACP();
   }
  else
   {
    cpi = GetOEMCP();
   }
  
 const lem::CodeConverter *cp = lem::CodeConverter::getConverter(cpi);
 LEM_CHECKIT_Z(cp!=NULL);
 return cp;

 #else
  return NULL;
 #endif
}

// ********************************************************************
// Символы окончания строки
// \r\n для Windows
// \n для Linux
//
// Если escaped=true, то возвращаемая строка будет иметь символы слеш
// ********************************************************************
const std::string lem::System_Config::GetLineTerminator( bool escaped )
{
 #if defined LEM_WINDOWS
  if( escaped )
   return std::string("\\r\\n");
  else
   return std::string("\r\n");  
 #else
  if( escaped )
   return std::string("\\n");
  else
   return std::string("\n");  
 #endif 
}


