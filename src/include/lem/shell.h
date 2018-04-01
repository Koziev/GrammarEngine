#ifndef LEM_SHELL__H
#define LEM_SHELL__H
#pragma once

// CD->14.12.2006
// LC->28.03.2018
// --------------

 #include <lem/config.h>
 #include <lem/path.h>

 namespace lem
 {
  namespace Shell
  {
      /*
   // Открытие документа в ассоциированной с ним программе, открытие
   // веб-ссылки и т.д.
   extern bool Execute( const wchar_t *Filename );
   extern bool Execute( const UFString &Filename );
   extern bool Execute( const UFString& Appname, const UFString &Filename, bool Silent=false );
   extern bool Execute( const lem::Path &Filename );

   // Исполнение командной строки, которая может включать любую корректную для
   // ОС операцию.
   extern int CommandLine( const lem::UFString &cmdline );
   */

   // Выводим сообщение об ошибке
   extern void Error( const wchar_t *Text ); 
   extern void Error( const char *Text ); 
   extern void Error( const lem::FString &Text ); 
   extern void Error( const wchar_t *Text, const wchar_t *Title ); 
   extern void Error( const lem::UFString& Text, const lem::UFString& Title );
   extern void Error( const lem::UFString& Text );
   extern void Error( const std::wstring &Text ); 
   extern void Error( const std::string &Text ); 

   // Отображение диалога с указанным сообщением (в заголовке - название программы).
   extern void Message( const char *Text ); 
   extern void Message( const wchar_t *Text ); 
   extern void Message( const lem::UFString& Text );

   // Стандартный диалог для выбора каталога
   extern lem::Path AskFolder( const wchar_t *message, void* hWnd, const lem::Path &start_path );
   extern lem::Path AskFolder( const wchar_t *message=NULL, void* hWnd=NULL );

  } // namespace Shell
 } // namespace lem

#endif
