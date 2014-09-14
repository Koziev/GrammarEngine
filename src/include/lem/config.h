#ifndef LEM_CONFIG__H
#define LEM_CONFIG__H
#pragma once

// -----------------------------------------------------------------------------
// File CONFIG.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia
//
// Content:
// Определение контекста компиляции - набора макросов, которые полностью
// характеризуют среду, в которой будет выполняться скомпилированная программа.
// Некоторые макросы могут (или должны) выставляться вручную, но большинство
// определяется автоматически - в зависимости от компилятора.
//
// 29.04.2007 - target platform detection hints have been partially copied from
//              BOOST select_platform_config.hpp
//
// 02.10.2007 - LEM_THEADS is defined when _MT is defined (MSVC specific)
//
// 22.05.2008 - if LEM_WIN98 defined then _WIN32_WINDOWS is defined as 0x0410
// -----------------------------------------------------------------------------
//
// CD->20.06.1998
// LC->13.11.2010
// --------------

#if !defined LEM_INCLUDE_DUPEL
 #define LEM_NODUP
#endif

#if !defined LEM_DEBUGGING
 #if defined NDEBUG
  // Runtime checks are disabled
  #define LEM_DEBUGGING 0
 #elif defined(_DEBUG) || defined(DEBUG)
  // Runtime checks are enabled
  #define LEM_DEBUGGING 1
 #else
  // Debugging is OFF by default
  #define LEM_DEBUGGING 0
 #endif
#endif 


 /**********************************************************************

   LEM_COMPILER_NAME - полное имя используемого компилятора в двойных
                       апострофах.

   LEM_COMPILER_VERSION - обозначение версии компилятора (31 для '3.1', 45 дл
                          '4.5' и так далее).

   Target platform UI:
                   LEM_CONSOLE - console application.
                   LEM_GUI     - GUI application

   Target platform OS:
                   LEM_DOS
                   LEM_WINDOWS
                   LEM_LINUX
                   LEM_MACOS 
                   LEM_BEOS
                   LEM_BSD
                   LEM_UNIX

   Target platform details:
    LEM_32  - 32bit application (i386 or higher is required).
    LEM_16  - 16bit application

 ***********************************************************************/

 #include <boost/config.hpp>

 #if defined __INTEL_COMPILER || defined BOOST_INTEL
  #include <lem/config_intel.h>
 #elif defined __WATCOMC__
  #include <lem/config_watcom.h>
 #elif defined(__BORLANDC__)
  #include <lem/config_borland.h>
 #elif defined(__DJGPP__)
  #include <lem/config_djgpp.h>
 #elif defined __GNUC__
  #include <lem/config_gnu.h>
 #elif defined _MSC_VER || defined BOOST_MSVC
  #include <lem/config_microsoft.h>
 #endif

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__LINUX__)
 #if !defined LEM_LINUX
  #define LEM_LINUX
  #define LEM_UNIX
 #endif
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
 #if !defined LEM_BSD
  #define LEM_BSD
  #define LEM_UNIX
 #endif
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
 #if !defined LEM_WINDOWS
  #define LEM_WINDOWS 
 #endif
#elif defined(__BEOS__)
 #if !defined LEM_BEOS
  #define LEM_BEOS
 #endif
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
 #if !defined LEM_MACOS
  #define LEM_MACOS
 #endif
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
 #if !defined LEM_UNIX
  #define LEM_UNIX
 #endif
#endif

#if defined LEM_UNIX && !defined LEM_USES_NCURSES
 #define LEM_USES_NCURSES 1
#endif  

#if defined BOOST_COMPILER && !defined compiler_declared
 #define compiler_declared
#endif

#if !defined compiler_declared
 #error Compiler must be declared!
#else
 #undef compiler_declared
#endif

#if !defined LEM_WCHAR_T
 #if defined LEM_WINDOWS
  #undef LEM_WCHAR_T
  #define LEM_WCHAR_T 2
 #elif defined LEM_UNIX
  #undef LEM_WCHAR_T
  #define LEM_WCHAR_T 4
 #endif
#endif


#if defined LEM_WINDOWS && !defined STRICT
 #define STRICT
#endif

 #if defined(UNICODE) || defined(_UNICODE)
  #if !defined LEM_UNICODE
   #define LEM_UNICODE
  #endif
 #endif
 
 #if defined LEM_WXFORMS && !defined LEM_WXWIDGETS
  #define LEM_WXWIDGETS
  #define LEM_GUI
 #endif 

 #if defined LEM_WXWIDGETS && defined LEM_GUI && !defined LEM_WXFORMS
  #define LEM_WXFORMS
 #endif

 #if defined __MT__ || defined _MT
  #if !defined LEM_THREADS && !defined LEM_NO_THREADS
   #define LEM_THREADS
  #endif
 #endif 

 #if defined LEM_WINDOWS && defined LEM_WIN98
  #undef _WIN32_WINDOWS
  #undef WINVER
  #define _WIN32_WINDOWS 0x0410
  #define WINVER 0x0410
 #endif

#endif
