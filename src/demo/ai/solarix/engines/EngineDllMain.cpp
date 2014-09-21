#include <lem/config.h>

#if defined LEM_WINDOWS

#include <windows.h>

BOOL APIENTRY DllMain(
                      HANDLE /*hModule*/, 
                      DWORD  /*ul_reason_for_call*/, 
                      LPVOID /*lpReserved*/
					 )
{
 // Library DLL is loaded. 
 return TRUE;
}

#endif
