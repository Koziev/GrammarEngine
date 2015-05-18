#define IMPORT(RetType) __declspec(dllexport) RetType __stdcall

IMPORT(void*) DesrInit( int BeamSize, const char *ConfigFile, const char * ModelFile );
IMPORT(char*) DesrTag( void * engine_ptr, const char * src );
IMPORT(int) DesrFreeResult( void * engine_ptr, char * result_str );
IMPORT(int) DesrDeleteEngine( void * engine_ptr );
