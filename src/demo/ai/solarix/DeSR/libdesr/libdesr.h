#if defined LIBDESR_EXPORT
 #if defined _WIN32
  #define IMPORT(RetType) __declspec(dllexport) RetType __stdcall
 #else
  #define IMPORT(RetType) RetType
 #endif
#else
 #if defined _WIN32
  #define IMPORT(RetType) RetType __stdcall
 #else
  //#define IMPORT(RetType) extern "C" RetType
  #define IMPORT(RetType) RetType
 #endif
#endif


IMPORT(void*) DesrInit( int BeamSize, const char *ConfigFile, const char * ModelFile );
IMPORT(char*) DesrTag( void * engine_ptr, const char * src );
IMPORT(int) DesrFreeResult( void * engine_ptr, char * result_str );
IMPORT(int) DesrDeleteEngine( void * engine_ptr );
