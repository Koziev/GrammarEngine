// -----------------------------------------------------------------------------
// File WIN32_Registry.CPP
//
// (c) Koziev Elijah
//
// Content:
// Работа с реестром Windows.
//
// 19.09.2007 - добавлены методы CopyKey и RenameSubKey
// 23.09.2009 - добавлен метод remove
// -----------------------------------------------------------------------------
//
// CD->01.04.2002
// LC->23.09.2009
// --------------

#include <lem/config.h>

#if defined LEM_WINDOWS

#include <lem/runtime_checks.h>
#include <lem/conversions.h>
#include <lem/char_buffer.h>
#include <lem/system_config.h>
#include <lem/Registry.h>

using namespace lem;

WinRegistry::WinRegistry(void)
{
 hRootKey=NULL;
 hCurKey=NULL;
 return;
}

// ****************************************************************
// Перемещаемся на секцию переменных, объединенных указанным через
// имя ключем.
// ****************************************************************
bool WinRegistry::seek_subkey( const char *KeyName )
{
 LEM_CHECKIT_Z(KeyName);
 LEM_CHECKIT_Z(hCurKey);

 if( KeyName==NULL || hCurKey==NULL )
  return false;

 LONG res=RegOpenKeyA(hCurKey,KeyName,&hCurKey);

 return res==ERROR_SUCCESS && hCurKey!=NULL;
}

// ************************************************************
// Извлекаем значения переменных.
// ************************************************************
const FString WinRegistry::get_string( const char *ValName )
{
 LEM_CHECKIT_Z( hCurKey!=NULL );
 LEM_CHECKIT_Z(ValName!=NULL);

 DWORD type=0;
 DWORD sz=0;

 if( RegQueryValueExA( hCurKey, ValName, 0, &type, NULL, &sz )!=ERROR_SUCCESS )
  // Ошибка поиска значения - возвращаем пустую строку.
  return "";

 if( type==REG_DWORD )
  {
   DWORD d=0;
   if( RegQueryValueExA( hCurKey, ValName, 0, &type, (LPBYTE)&d, &sz )==ERROR_SUCCESS )
    {
     return FString( to_str( (int)d ).c_str());
    }
  }
 else if( type==REG_SZ )
  {
   lem::CharBuffer buffer(sz+1);
//   memset( buffer, 0, sz+1 );

   sz++;
   if( RegQueryValueExA( hCurKey, ValName, 0, &type, (LPBYTE)(char*)buffer, &sz )==ERROR_SUCCESS )
    {
     return FString( (char*)buffer );
    }
  }

 return FString();
}

bool WinRegistry::get_bool( const char *ValName )
{
 LEM_CHECKIT_Z(ValName!=NULL);
 FString s(get_string(ValName));
 return s.eqi("true") || s=="1";
}

bool WinRegistry::remove( const char *ValName )
{
 LEM_CHECKIT_Z(ValName!=NULL);
 bool rc = RegDeleteValueA( hCurKey, ValName )==ERROR_SUCCESS;
 LEM_CHECKIT_Z(rc);
 return rc;
}


// **********************************************************************
// Устанавливаем значения переменных. При необходимости переменные
// будут созданы.
// **********************************************************************
void WinRegistry::set_string( const char *ValName, const char *Content )
{
 LEM_CHECKIT_Z( ValName!=NULL );
 LEM_CHECKIT_Z( hCurKey!=NULL );
 LEM_CHECKIT_Z( Content!=NULL );

 const char *c = Content==NULL ? "" : Content;

 RegSetValueExA( hCurKey, ValName, 0, REG_SZ, (UCHAR*)c, strlen(c) );
 return;
}

void WinRegistry::set_bool( const char *ValName, const bool Content )
{
 LEM_CHECKIT_Z( hCurKey!=NULL );

 const char *c = Content ? "true" : "false";
 RegSetValueExA( hCurKey, ValName, 0, REG_SZ, (UCHAR*)c, strlen(c) );
 return;
}


// ****************************************************
// (c) locate file search engine project (BSD license)
// ****************************************************
LONG WinRegistry::CopyKey( HKEY hSource, HKEY hDestination )
{
 LEM_CHECKIT_Z( hSource!=NULL );
 LEM_CHECKIT_Z( hDestination!=NULL );

 LONG lRet=ERROR_SUCCESS;

 // First copy subkeys
 #if defined LEM_QT
 wchar_t szName[1000];
 wchar_t szClass[1000];
 #else
 TCHAR szName[1000];
 TCHAR szClass[1000];
 #endif

 DWORD cb,i;
 for(i=0;;i++)
  {
   DWORD cb2=1000;
   cb=1000;

   if(RegEnumKeyEx(hSource,i,szName,&cb,NULL,szClass,&cb2,NULL)!=ERROR_SUCCESS)
    break;

   HKEY hSubSource,hSubDestination;

   LONG lErr=RegOpenKeyEx(hSource,szName,0,KEY_READ,&hSubSource);
   if(lErr!=ERROR_SUCCESS)
    {
     lRet=lErr;
     continue;
    }

   lErr=RegCreateKeyEx(hDestination,szName,0,szClass,0,KEY_ALL_ACCESS,NULL,&hSubDestination,NULL);
   if(lErr!=ERROR_SUCCESS)
    {
     RegCloseKey(hSubSource);
     lRet=lErr;
     continue;
    }

   if(CopyKey(hSubSource,hSubDestination)<=0)
    lRet=lErr;
			

   RegCloseKey(hSubSource);
   RegCloseKey(hSubDestination);
  }

 // Now copying values
 for( i=0;;i++ )
  {
   cb=1000;
   DWORD dwType,dwDataSize;
   if( RegEnumValue(hSource,i,szName,&cb,NULL,&dwType,NULL,&dwDataSize)!=ERROR_SUCCESS )
    break;

   BYTE* pData=new BYTE[dwDataSize+1];

   LONG lErr;
   if( (lErr=RegQueryValueEx(hSource,szName,NULL,NULL,pData,&dwDataSize))!=ERROR_SUCCESS )
    lRet=lErr;
   else if ((lErr=RegSetValueEx(hDestination,szName,NULL,dwType,pData,dwDataSize))!=ERROR_SUCCESS)
    lRet=lErr;

   delete[] pData;
  }

 return lRet;   
}


// ****************************************************
// (c) locate file search engine project (BSD license)
// ****************************************************
LONG WinRegistry::RenameSubKey( HKEY hKey, const char* szOldName, const char* szNewName )
{
 LEM_CHECKIT_Z( hKey!=NULL );
 LEM_CHECKIT_Z( lem::lem_is_empty(szOldName)==false );
 LEM_CHECKIT_Z( lem::lem_is_empty(szNewName)==false );

 HKEY hSource,hDestination;
	
 LONG lErr=RegOpenKeyExA(hKey,szOldName,0,KEY_READ,&hSource);
 if(lErr!=ERROR_SUCCESS)
  return lErr;
	
 lErr=RegCreateKeyExA(hKey,szNewName,0,NULL,0,KEY_ALL_ACCESS,NULL,&hDestination,NULL);
 if(lErr!=ERROR_SUCCESS)
  {
   RegCloseKey(hSource);
   return lErr;
  }

 LONG lRet=CopyKey(hSource,hDestination);
 RegCloseKey(hSource);
 RegCloseKey(hDestination);

 if( lRet==ERROR_SUCCESS )
  {
   RegDeleteKeyA(hKey,szOldName);
   return ERROR_SUCCESS;
  }

 return lRet;
}


LONG WinRegistry::RenameSubKey( HKEY hKey, const wchar_t* szOldName, const wchar_t* szNewName )
{
 LEM_CHECKIT_Z( hKey!=NULL );
 LEM_CHECKIT_Z( lem::lem_is_empty(szOldName)==false );
 LEM_CHECKIT_Z( lem::lem_is_empty(szNewName)==false );

 if( !lem::System_Config::SupportUnicodeAPI() )
  return RenameSubKey(hKey, to_ascii(szOldName).c_str(), to_ascii(szNewName).c_str() );

 HKEY hSource,hDestination;
	
 LONG lErr=RegOpenKeyExW(hKey,szOldName,0,KEY_READ,&hSource);
 if(lErr!=ERROR_SUCCESS)
  return lErr;

 lErr=RegCreateKeyExW(hKey,szNewName,0,NULL,0,KEY_ALL_ACCESS,NULL,&hDestination,NULL);
 if(lErr!=ERROR_SUCCESS)
  {
   RegCloseKey(hSource);
   return lErr;
  }

 LONG lRet=CopyKey(hSource,hDestination);
 RegCloseKey(hSource);
 RegCloseKey(hDestination);

 if(lRet==ERROR_SUCCESS)
  {
   RegDeleteKeyW(hKey,szOldName);
   return ERROR_SUCCESS;
  }

 return lRet;
}

#endif
