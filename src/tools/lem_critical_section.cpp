// LC->08.05.2012

#include <lem/config.h>

#if defined LEM_WINDOWS
 #undef _WIN32_WINNT
 #define _WIN32_WINNT 0x0400

 #if defined LEM_MFC
  #include <afxwin.h>
 #else 
  #include <windows.h>
 #endif
#endif

#if defined LEM_UNIX && defined LEM_THREADS
 #include <pthread.h>
 #define USE_PTHREAD
#endif


#include <lem/process.h>

using namespace lem::Process;



#if !defined LEM_WXWIDGETS || defined LEM_WINDOWS

CriticalSection::CriticalSection(void)
{
 #if defined LEM_THREADS

  #if defined LEM_WINDOWS
  InitializeCriticalSection(&cs);
  #endif

  #if defined USE_PTHREAD

  #if LEM_DEBUGGING==1
  int rc = pthread_mutexattr_init( &attr );
  LEM_CHECKIT_Z(rc==0);
  
  rc = pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );
  LEM_CHECKIT_Z(rc==0);
 
  rc = pthread_mutex_init(&cs,&attr);
  LEM_CHECKIT_Z(rc==0);
  #else
  pthread_mutexattr_init( &attr );
  pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );
  pthread_mutex_init(&cs,&attr);
  #endif
  #endif

 #endif

 return;
}

CriticalSection::~CriticalSection(void)
{
 #if defined LEM_THREADS && defined LEM_WINDOWS
 DeleteCriticalSection(&cs);
 #endif

 #if defined USE_PTHRAD
  #if LEM_DEBUGGING==1
   int rc = pthread_mutex_destroy(&cs);
   LEM_CHECKIT_Z( rc==0 );

   rc = pthread_mutexattr_destroy(&attr);
   LEM_CHECKIT_Z( rc==0 );
  #else
   pthread_mutex_destroy(&cs);
   pthread_mutexattr_destroy(&attr);
  #endif
 #endif
 
 return;
}

void CriticalSection::Enter(void)
{
 #if defined LEM_THREADS

  #if defined LEM_WINDOWS
  EnterCriticalSection(&cs);
  #if LEM_DEBUGGING==1
  int lock_count = cs.LockCount;
  #endif
  #endif
 
  #if defined LEM_UNIX
  pthread_mutex_lock( &cs );
  #endif

 #endif

 return;
}


bool CriticalSection::TryEnter(void)
{
 #if defined LEM_THREADS
  #if defined LEM_WINDOWS
  return TryEnterCriticalSection(&cs)!=0;
  #endif
  #if defined LEM_UNIX
  return pthread_mutex_trylock(&cs);
  #endif
 #else
  return false;
 #endif
}


void CriticalSection::Leave(void)
{
 #if defined LEM_THREADS

 #if defined LEM_WINDOWS
  #if LEM_DEBUGGING==1
  int lock_count = cs.LockCount;
  #if defined LEM_32
  LEM_CHECKIT_Z( lock_count>=0 );
  #endif
  #endif
  LeaveCriticalSection(&cs);
 #endif

 #if defined LEM_UNIX
 pthread_mutex_unlock( &cs );
 #endif

 #endif
}

#endif


#if defined LEM_THREADS
CritSecLocker::CritSecLocker( CriticalSection *CS ) : cs(CS)
{
 LEM_CHECKIT_Z(CS!=NULL);
 cs->Enter();
 return;
}

CritSecLocker::~CritSecLocker(void)
{
 cs->Leave();
}
#endif
