#include <lem/config_microsoft.h>

#undef LEM_COMPILER_NAME
#undef LEM_COMPILER_VERSION

#define LEM_COMPILER_NAME "Intel Compiler"

#if __INTEL_COMPILER==900
 #define LEM_COMPILER_VERSION "9.0"
#else
 #define LEM_COMPILER_VERSION ""
#endif 
