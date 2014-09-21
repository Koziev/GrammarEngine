// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MAXENTTAGGERLIB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MAXENTTAGGERLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MAXENTTAGGERLIB_EXPORTS
#define MAXENTTAGGERLIB_API __declspec(dllexport)
#else
#define MAXENTTAGGERLIB_API __declspec(dllimport)
#endif


MAXENTTAGGERLIB_API void* MaxEntLibCreate(void);
MAXENTTAGGERLIB_API int MaxEntLibFree( void * ptr );
MAXENTTAGGERLIB_API int MaxEntLibLoad( void * model_ptr, const char * filepath );
MAXENTTAGGERLIB_API double MaxEntLibEval( void * model_ptr, const char ** features, int features_count, const char * label );
