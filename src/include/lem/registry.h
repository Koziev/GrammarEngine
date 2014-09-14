// -----------------------------------------------------------------------------
// File Registry.H
//
// (c) Koziev Elijah
//
// Content:
// Класс-оболочка для доступа к системному реестру.
// -----------------------------------------------------------------------------
//
// CD->31.03.2002
// LC->23.09.2009
// --------------

#ifndef IMB_WinRegistry__H
#define IMB_WinRegistry__H
#pragma once

 #if defined LEM_WINDOWS

 #if defined LEM_MFC
  #include <afxwin.h>
 #else 
  #include <windows.h>
 #endif

 #include <lem/fstring.h>

 namespace lem
 {
  class WinRegistry
  {
   private:
    HKEY hRootKey;
    HKEY hCurKey;

   public:
    WinRegistry(void);

    inline void HKCU(void) { hRootKey=hCurKey=HKEY_CURRENT_USER; }
    inline void HKLM(void) { hRootKey=hCurKey=HKEY_LOCAL_MACHINE; }
    inline void HKCLS(void) { hRootKey=hCurKey=HKEY_CLASSES_ROOT; }

    // Перемещаемся на секцию переменных, объединенных указанным через
    // имя ключем. При необходимости ключ создается.
    bool seek_subkey( const char *KeyName );

    // Извлекаем значения переменных.
    const FString get_string( const char *ValName );
    bool get_bool( const char *ValName );

    // Удаление переменной
    bool remove( const char *ValName );

    // Устанавливаем значения переменных. При необходимости переменные
    // будут созданы.
    void set_string( const char *ValName, const char *Content );
    void set_bool( const char *ValName, bool Content );

    LONG CopyKey( HKEY hSource, HKEY hDestination );
    LONG RenameSubKey( HKEY hKey, const char* szOldName, const char* szNewName );
    LONG RenameSubKey( HKEY hKey, const wchar_t* szOldName, const wchar_t* szNewName );
  };

 } // namespace 'lem'

 #endif

#endif
