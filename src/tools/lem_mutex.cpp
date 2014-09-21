#include <lem/process.h>

#if defined LEM_THREADS

using namespace lem;
using namespace Process;


Mutex::Mutex(void)
{
 #if defined LEM_WINDOWS && !defined LEM_WXWIDGETS
 mtx = CreateMutex(NULL,0,0);
 LEM_CHECKIT_Z(mtx!=NULL);
 #endif
}

Mutex::~Mutex(void)
{
 #if defined LEM_WINDOWS && !defined LEM_WXWIDGETS
 ReleaseMutex(mtx);
 mtx = NULL;
 #endif
}


bool Mutex::Lock(void)
{
 #if defined LEM_WXWIDGETS
 return wxMutex::Lock()==wxMUTEX_NO_ERROR; 
 #elif defined LEM_WINDOWS
 DWORD res = WaitForSingleObject(mtx,-1L);
 return res == WAIT_OBJECT_0;
 #endif
}

bool Mutex::TryLock(void)
{
 #if defined LEM_WXWIDGETS
 return wxMutex::TryLock()==wxMUTEX_NO_ERROR;
 #elif defined LEM_WINDOWS
 DWORD res = WaitForSingleObject(mtx,-1L);
 return res == WAIT_OBJECT_0;
 #endif
}


bool Mutex::Unlock(void)
{
 #if defined LEM_WXWIDGETS
 return wxMutex::Unlock()==wxMUTEX_NO_ERROR;
 #elif defined LEM_WINDOWS
 LEM_CHECKIT_Z(mtx!=NULL);
 return ReleaseMutex(mtx)!=0;
 #endif
}

#endif
