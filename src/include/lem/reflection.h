#ifndef LEM_REFLECTION__H
#define LEM_REFLECTION__H
#pragma once

 #include <lem/config.h>

 #if defined LEM_MFC
  #include <afxwin.h>
 #endif

 #include <string>
 #include <lem/oformatter.h>

 namespace lem
 { 
  namespace Reflection
  {
   extern void PrintCompilationInfo( lem::OFormatter &txt );

   // Application target OS. It can differ from current host OS.
   extern const std::string TargetOs(void);

   // Information about the compiler
   extern const std::string CompilerInfo(void);

   // Вызывается для запоминания во внутреннем буфере пути к стартовому
   // каталогу модуля (exe или dll). Аргумент - полный путь к модулю (то
   // есть с именем файла).
   extern void SetStartupFilename( const lem::Path &fn );

   extern const lem::Path& GetStartupFolder(void);
   extern const lem::Path& GetStartupFilename(void);
  }
 }

#endif

