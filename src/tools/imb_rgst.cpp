// -----------------------------------------------------------------------------
// File IMB_RGST.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2003
//     elijah@metacom.ru
//
// Nuclear Power Engineering Institute, Reactor Design Department
// Karpov State Research Center, Physical Chemistry Institute
// Vologda Registration Centre
//
// Content:
// Работа с реестром Windows.
// -----------------------------------------------------------------------------
//
// CD->01.04.02
// LC->18.11.03
// ------------

#include <lem/config.h>

#if defined LEM_WIN32

#include <lem/runtime_checks.h>
#include <imb_rgst.h>

#include <lem/conversions.h>

using namespace lem;

IMB_Registry::IMB_Registry(void)
{
 hRootKey=NULL;
 hCurKey=NULL;
 return;
}

// ****************************************************************
// Перемещаемся на секцию переменных, объединенных указанным через
// имя ключем. При необходимости ключ создается.
// ****************************************************************
bool IMB_Registry::seek_subkey( const char *KeyName )
{
 return RegCreateKey(
                     hCurKey,
                     KeyName,
                     &hCurKey
                    )==ERROR_SUCCESS;
}

// ************************************************************
// Извлекаем значения переменных.
// ************************************************************
const FString IMB_Registry::get_string( const char *ValName )
{
 LEM_CHECKIT( hCurKey!=NULL );

 DWORD type=0;
 DWORD sz=0;

 if( RegQueryValueEx( hCurKey, ValName, 0, &type, NULL, &sz )!=ERROR_SUCCESS )
  // Ошибка поиска значения - возвращаем пустую строку.
  return "";

 unsigned char *buffer = new char[sz+1];
 memset( buffer, 0, sz+1 );

 sz++;
 RegQueryValueEx( hCurKey, ValName, 0, &type, buffer, &sz );
 FString res = (char*)buffer;

 delete[] buffer;
 return res;
}

bool IMB_Registry::get_bool( const char *ValName )
{
 return get_string(ValName)=="true";
}

// **********************************************************************
// Устанавливаем значения переменных. При необходимости переменные
// будут созданы.
// **********************************************************************
void IMB_Registry::set_string( const char *ValName, const char *Content )
{
 LEM_CHECKIT( hCurKey!=NULL );

 const char *c = Content==NULL ? "" : Content;

 RegSetValueEx( hCurKey, ValName, 0, REG_SZ, (UCHAR*)c, strlen(c) );
 return;
}

void IMB_Registry::set_bool( const char *ValName, const bool Content )
{
 LEM_CHECKIT( hCurKey!=NULL );

 const char *c = Content ? "true" : "false";
 RegSetValueEx( hCurKey, ValName, 0, REG_SZ, (UCHAR*)c, strlen(c) );
 return;
}

#endif

// ----------------------- End Of File [IMB_RGST.CPP] --------------------------
