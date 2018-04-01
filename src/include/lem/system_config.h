#ifndef LEM_SYSTEM_CONFIG__H
#define LEM_SYSTEM_CONFIG__H
#pragma once

 // 07-04-2007 Добавлена функция GetHostOs()
 // 21.04.2007 - PrintInfo() added.
 // 27.04.2007 - возвращаемые процедурами GetHomeDir() и GetAppdataDir() пути имеют тип lem::Path
 // 22.04.2008 - добавлены IsFilesystemUtf8() и GetFilesystemCP()
 // 23.05.2008 - добавлена IsWin2k()
 // 30.09.2009 - добавлена IsVistaOrNewer() для работы с Server 2008 и WIndows 7

 #include <lem/config.h>
 #include <lem/path.h>
 #include <string>

 namespace lem
 {
  class OFormatter;
  class CodeConverter;

  namespace System_Config
  {
   // Возвращает имя домашнего каталога для текущего юзера.
   //extern const lem::Path GetHomeDir(void);

   //extern const lem::Path GetAppdataDir(void);

     // На какой платформе исполняется программа
   extern const std::string GetHostOs( bool detailed=true );

   // 64-битная ОС (программа может быть 32-битной).
   extern bool IsOS64(void);

   // Поддерживает ли платформа Unicode строки в вызовах API
   extern bool SupportUnicodeAPI(void);

   // Поддерживает ли текущая платформа нормальную работу _wfopen и
   // других функций для UNICODE-имен файлов
   extern bool SupportUnicodeFilenames(void);

   // Можно ли в текстовой консоли использовать нормальный вывод 
   // UNICODE текста
   extern bool SupportUnicodeConsole(void);

   // Поддерживает ли текущая платформа UNICODE для GUI
   extern bool SupportUnicodeGui(void);

   // Filename are case sensitive (false for Windows, true for Unix by default).
   extern bool FilenamesCaseSensitive(void);

   // Имя рабочей станции (хост в локальной сети)
   extern const std::string GetHostName(void);

   // Символы окончания строки
   // \r\n для Windows
   // \n для Linux
   //
   // Если escaped=true, то возвращаемая строка будет иметь символы слеш
   extern const std::string GetLineTerminator( bool escaped );

   // Возвращает размер выравнивания для скомпилированной программы
   // (в байтах).
   extern int GetAlignmentSize(void);

   // Возвращает имя пользователя (логин) для текущей сессии
   extern const std::string GetUserLogin(void);

   //extern bool IsWin9x(void);
   //extern bool IsNT4(void);
   extern bool IsWin2k(void);
   extern bool IsUnix(void);
   extern bool IsLinux(void);
   extern bool IsFreeBSD(void);
   //extern bool IsTabletPC(void);
   //extern bool IsMediaCenter(void);
   extern bool IsVista(void);
   extern bool IsVistaOrNewer(void);

/*
   extern bool IsNetfx10Installed(void);
   extern bool IsNetfx11Installed(void);
   extern int GetNetfx10SPLevel(void);
   extern int GetNetfx11SPLevel(void);

   // Возвращает строковое описание установленной версии .NETа
   extern const std::string GetNetfxInfo(void);
*/

   // ******************************
   // Возвращает тип адресации
   // ******************************
   typedef enum {
                 ADDRESSING_UNKNOWN=-1,
                 ADDRESSING_16_16,     // Старая large memory model СЕГМЕНТ:СМЕЩЕНИЕ
                 ADDRESSING_32,        // 32 бит
                 ADDRESSING_64         // 64 бит
                } AddressingType;


   extern AddressingType GetAddressingType(void);

   // Show some brief info about current session.
   extern void PrintInfo( lem::OFormatter &dst );

   // Returns true for L'-' on Unix/Windows and L'/' on Windows/Dos
   extern bool IsCmdLineOption( wchar_t ch );
   extern bool IsCmdLineOption( char ch );


   //extern bool IsServiceRunning( const char *DaemonName );
   //extern void ShowIndexingServiceControlDialog(void);
   //extern bool IsIndexingServiceRunning(void);

   extern bool IsFilesystemUtf8( const lem::Path *path=NULL );
   extern const lem::CodeConverter* GetFilesystemCP( const lem::Path *path=NULL );

  } // namespace System_Config
 } // namespace lem

#endif
 
