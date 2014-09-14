#define compiler_declared

#define LEM_GNUC

#if defined(__LINUX__) || defined(__linux__)
 #undef LEM_LINUX
 #undef LEM_UNIS
 #define LEM_LINUX
 #define LEM_UNIX
#elif defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
 #undef LEM_BSD
 #undef LEM_UNIX
 #define LEM_BSD
 #define LEM_UNIX 
#elif defined __APPLE__ || defined __APPLE_CC__ || defined __DARWIN__
 #undef LEM_BSD
 #undef LEM_UNIX
 #undef LEM_DARWIN
 #define LEM_BSD
 #define LEM_UNIX 
 #define LEM_DARWIN
#elif !defined LEM_WINDOWS
 #define LEM_WINDOWS
#endif

#if __WORDSIZE==64 || __SIZEOF_POINTER__==8 || __amd64__==1
 #define LEM_64
#else
 #define LEM_32
#endif

#define LEM_UI64
#define LEM_I64

#define LEM_STANDARD_CPP

#define LEM_COMPILER_NAME "GNU C++ Compiler"
#define LEM_COMPILER_VERSION __VERSION__
