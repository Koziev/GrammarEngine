#pragma once

#define LEM_COMPILER_NAME "Borland C Builder"

 #if __BCPLUSPLUS__==0x310

  #define LEM_COMPILER_VERSION "3.1"

  #define compiler_declared

  #define LEM_BORLAND
  #define LEM_BORLAND_3_1    // Компилятор Borland C++ 3.1
  #define LEM_16             // 16-разрядное приложение.

  #if defined(_Windows)

   #define LEM_WINDOWS
   #define LEM_WIN16
   #if !defined LEM_GUI && !defined LEM_CONSOLE && !defined LEM_EASYWIN
    #define LEM_GUI
   #endif

  #elif defined(__MSDOS__)
   #define LEM_DOS
   #define LEM_DOS16
   #define LEM_CONSOLE
  #else
   #error Unknown OS or CPU
  #endif

  #if defined __STDC__
   #define LEM_STANDARD_CPP
  #endif

// define LEM_LOG_ASSIGNMENT

 #endif // end of Borland C++ 3.1 config

 // ************************************************************************
 // ************************************************************************
 // ************************************************************************
 // ************************************************************************

 #if __VER__==0x400

  #define compiler_declared

  #define LEM_BORLAND
  #define LEM_BORLAND_4_0    // Компилятор Borland C++ 4.0

  #define LEM_COMPILER_VERSION "4.0"

  #if defined __WIN32__

   #define LEM_32             // 32-bit application for MS Win32
   #define LEM_WIN32
   #define LEM_WINDOWS

   #if defined(_WINNT_) || defined (__NT__)
    #define LEM_WINNT        // Windows NT
    #if defined __CONSOLE__ && !defined LEM_CONSOLE
     #error Windows Console not supported
     #define LEM_CONSOLE
    #else
     #if !defined LEM_GUI && !defined LEM_CONSOLE
      #define LEM_GUI
     #endif
    #endif
   #endif

  #else

   #define LEM_16             // 16-разрядное приложение.

   #if defined(_Windows)
    #define LEM_WINDOWS
    #define LEM_WIN16
    #undef LEM_GUI

    #if !defined LEM_GUI && !defined LEM_CONSOLE
     #define LEM_GUI
    #endif

   #elif defined(__MSDOS__)
    #define LEM_DOS
    #define LEM_DOS16
   #else
    #error Unknown OS or CPU
   #endif

  #endif

  #if defined __STDC__
   #define LEM_STANDARD_CPP
  #endif

// define LEM_LOG_ASSIGNMENT

 #endif // end of Borland C++ 4.0 config


 // ************************************************************************
 // ************************************************************************
 // ************************************************************************
 // ************************************************************************

 #if __BCPLUSPLUS__==0x340

  #define compiler_declared

  #define LEM_BORLAND
  #define LEM_BORLAND_4_5    // Компилятор Borland C++ 4.5

  #define LEM_COMPILER_VERSION "4.5"

  #if defined __WIN32__

   #define LEM_32             // 32-bit application for MS Win32
   #define LEM_WIN32
   #define LEM_WINDOWS

   #if defined __CONSOLE__ && !defined LEM_CONSOLE
    #error Windows Console not supported
    #define LEM_CONSOLE
   #else
    #if !defined LEM_GUI && !defined LEM_CONSOLE
     #define LEM_GUI
    #endif
   #endif

   #if defined(_WINNT_) || defined (__NT__)
    #define LEM_WINNT        // Windows NT
   #endif

  #else

   #if defined(_Windows)

    #define LEM_WINDOWS
    #if sizeof(int)==2
     #define LEM_16
     #define LEM_WIN16
    #else
     #define LEM_32
     #define LEM_WIN32
    #endif

    #if !defined LEM_GUI && !defined LEM_CONSOLE
     #define LEM_GUI
    #endif

   #elif defined(__MSDOS__)

    #define LEM_DOS
    #if sizeof(int)==2
     #define LEM_16
     #define LEM_DOS6
    #else
     #define LEM_32
     #define LEM_DOS32
    #endif

   #else
    #error Unknown OS or CPU
   #endif

  #endif

  #if defined __STDC__
   #define LEM_STANDARD_CPP
  #endif

// define LEM_LOG_ASSIGNMENT

 #endif // end of Borland C++ 4.5 config


 // ************************************************************************
 // ************************************************************************
 // ************************************************************************
 // ************************************************************************

 #if __BCPLUSPLUS__>=0x520

  #define compiler_declared

  #define LEM_BORLAND
  #define LEM_BORLAND_5_0    // Компилятор Borland C++ Builder 5.x

  #define LEM_COMPILER_VERSION "5.0"

  #if defined _MAK_TARGET_OS_msdos

   #define LEM_DOS
   #define LEM_32
   #define LEM_DOS32

  #elif defined(_Windows)

   #define LEM_WINDOWS

   #if defined __WIN32__

    #define LEM_32
    #define LEM_WIN32

    #if defined(_WINNT_) || defined (__NT__)
     #define LEM_WINNT        // Windows NT
    #endif

    #if !defined LEM_GUI && !defined LEM_CONSOLE
     #define LEM_GUI
    #endif

   #else

    #define LEM_16
    #define LEM_WIN16

    #if !defined LEM_GUI && !defined LEM_CONSOLE
     #define LEM_GUI
    #endif

   #endif

  #elif defined(__MSDOS__)

   #define LEM_DOS
   #if sizeof(int)==2
    #define LEM_16
    #define LEM_DOS16
   #else
    #define LEM_32
    #define LEM_DOS32
   #endif

  #else
   #error Unknown OS or CPU
  #endif

  #if defined __STDC__
   #define SOL_STANDARD_CPP
  #endif

// define LEM_LOG_ASSIGNMENT

  #define LEM_WIN32API

 #endif // end of Borland C++ Builder v.1.0


 #if __BCPLUSPLUS__>=0x600
  #define LEM_CODEGEAR
 #endif

 #if defined INC_VCL || defined VCL_FULL || defined VCL_H
  #if !defined LEM_VCL
   #define LEM_VCL
  #endif
 #endif

#if defined LEM_32

// CodeGear 2009 does not need this template function
#if !defined LEM_CODEGEAR
namespace std
{
 template <typename T>
 inline void swap( T &a, T &b )
 { T c(a); a=b; b=c; }
}
#endif

#if defined __MT__ && !defined LEM_THREADS
 #define LEM_THREADS
#endif

#endif


