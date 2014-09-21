#define compiler_declared

#define LEM_WATCOM        // Компилятор WATCOM C++, 32х разрядный.

#define LEM_COMPILER_NAME "Watcom Compiler"


  #if __WATCOMC__==1000
   #define LEM_WATCOM_10
   #define LEM_COMPILER_VERSION 10
  #elif __WATCOMC__==1100
   #define LEM_WATCOM_11
   #define LEM_COMPILER_VERSION 11
  #elif __WATCOMC__>=1220
   #define LEM_WATCOM_11
   #define LEM_COMPILER_VERSION 11
  #else
   #error Unknown version of WATCOM C++ Compiler
  #endif

  #if defined(__DOS__) || defined(MSDOS)

   #define LEM_DOS          // Будем работать под управлением MS DOS

   #define LEM_32            // 32-разрядное приложение.
   #define LEM_DOS32
   #define LEM_DOS_EXTENDER // В среде DOS Extender'a

  #elif defined __WIN95__

   #define LEM_WINDOWS
   #define LEM_32           // 32-разрядное приложение.
   #define LEM_WIN32
   #define LEM_WIN95        // Windows 95
   #define LEM_WIN32API

   #if !defined LEM_GUI && !defined LEM_CONSOLE
    #define LEM_GUI
   #endif

  #elif defined(_WINNT_) || defined (__NT__)

   #define LEM_WINDOWS
   #define LEM_WINNT        // Windows NT
   #define LEM_32           // 32-разрядное приложение.
   #define LEM_WIN32
   #define LEM_WIN32API

   #if !defined LEM_GUI && !defined LEM_CONSOLE
    #define LEM_GUI
   #endif

  #elif defined(__WINDOWS__) || defined(__WINDOWS_386__) || defined (__CHEAP_WINDOWS__)

   #define LEM_WINDOWS      // MS Windows XXX

   #if defined(__WIN32__) || defined (__WINDOWS__386__)
    #define LEM_32            // 32-разрядное приложение.
    #define LEM_WIN32
   #else
    #define LEM_16            // 16-разрядное приложение.
    #define LEM_WIN16
   #endif

   #if !defined LEM_GUI && !defined LEM_CONSOLE
    #define LEM_GUI
   #endif

  #elif defined(__OS2__)

   #define LEM_OS2          // OS/2.

  #elif defined(__QNX__)

   #define LEM_QNX          // QNX.

  #elif defined(__NETWARE_386__)

   #define LEM_NETWARE_386  // QNX.

  #else

   #error Unknown OS or CPU !

  #endif

  #define LEM_STANDARD_CPP  // Только ANSI-стандартные функции.

  #if __WATCOMC__==1100
   // Версия 11 уже имеет встроенный тип bool (версия 10 не имеет).
   #define LEM_USE_BOOL
  #endif

// #define LEM_NOCACHE // Кэш будет работать! Смотри также комментарии ниже...
// define LEM_LOG_ASSIGNMENT

  // WATCOM does not understand expressions: template<> class A<true> {...};
  #define LEM_NO_EMPTY_TMPL

  #define LEM_NOREAL10

  #define LEM_NO_PARTIAL_TPL
