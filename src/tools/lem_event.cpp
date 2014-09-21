#include <lem/process.h>

#if defined LEM_THREADS

using namespace lem::Process;

Event::Event(void)
{
 #if defined LEM_WINDOWS
 hEvent = CreateEventW( NULL, true, false, NULL );
 LEM_CHECKIT_Z(hEvent!=NULL);
 #endif

 return;
}

Event::~Event(void)
{
}

bool Event::IsOk(void)
{
 #if defined LEM_WINDOWS
 return hEvent!=NULL;
 #else
 return false;
 #endif
}


void Event::Signal(void)
{
 LEM_CHECKIT_Z( IsOk() );

 #if defined LEM_WINDOWS
 SetEvent(hEvent);
 #endif

 return;
}

void Event::Wait(void)
{
 LEM_CHECKIT_Z( IsOk() );

 #if defined LEM_WINDOWS
 DWORD res = WaitForSingleObject( hEvent, INFINITE );
 LEM_CHECKIT_Z( res!=WAIT_FAILED );
 #endif
 return;
}

void Event::Reset(void)
{
 LEM_CHECKIT_Z( IsOk() );

 #if defined LEM_WINDOWS
 BOOL res = ResetEvent( hEvent );
 LEM_CHECKIT_Z( res!=0 );
 #endif
 return;
}

#endif
