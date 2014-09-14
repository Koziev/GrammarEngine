#define compiler_declared
#define LEM_MSC

#pragma warning( disable : 4995 )
#pragma warning( disable : 4996 )

#if defined _MANAGED && _MANAGED==1
 #define LEM_DOT_NET
#endif

#if defined WIN32 && !defined LEM_WINDOWS
 #define LEM_WINDOWS 1
#endif

#if defined(_WINDOWS) && !defined(_CONSOLE)
 #undef LEM_GUI
 #define LEM_GUI
#endif

#if defined _CONSOLE
 #undef LEM_CONSOLE
 #define LEM_CONSOLE
#endif

#if !defined LEM_GUI && !defined LEM_CONSOLE
 #undef LEM_CONSOLE
 #define LEM_CONSOLE
#endif

#undef min
#undef max


#if defined LEM_MSC && _MSC_VER<1300
 // MSVC 6.0 
/*
 #pragma warning( disable : 4786 )
 namespace std
 {
  template <class T>
  inline T max( const T &a, const T &b )
  { return a>b ? a : b; }

  template <class T>
  inline T min( const T &a, const T &b )
  { return a<b ? a : b; }
 }
*/
#endif



#if _MSC_VER>=1300 && !defined __INTEL_COMPILER
 // Enable 64-bit file offsets
 #define LEM_FILE64
#endif


#define LEM_COMPILER_NAME "Microsoft VisualStudio"

 
#if _MSC_VER>=1200 && _MSC_VER<1300
 #define LEM_COMPILER_VERSION "6.0"
#elif _MSC_VER>=1300 && _MSC_VER<1400
 #define LEM_COMPILER_VERSION "2003"
 #define LEM_I64
 #define LEM_UI64
#elif _MSC_VER>=1400 && _MSC_VER<1500
 #define LEM_COMPILER_VERSION "2005"
 #define LEM_I64
 #define LEM_UI64
#else _MSC_VER>=1500
 #define LEM_COMPILER_VERSION "2008"
 #define LEM_I64
 #define LEM_UI64
#endif

#if defined _M_IA64 || defined _M_X64 || defined _WIN64
 #define LEM_64
#else
 #define LEM_32
#endif

#if defined __AFX_H__ || defined LEM_MFC

 // Enable cooperation with MFC
 #if !defined LEM_MFC
  #define LEM_MFC
 #endif

 #if LEM_DEBUGGING==0
  #define _AFX_NO_DEBUG_CRT
  //#define _ATL_NO_DEBUG_CRT
 #endif

#endif

#if defined LEM_WINDOWS && !defined WINVER && !defined LEM_98
 // Windows XP and Windows .NET Server
 #define WINVER 0x0501
#endif
