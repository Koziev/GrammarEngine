#include <lem/config.h>

#if defined LEM_WINDOWS
#define _WIN32_WINNT 0x0500 
#include <windows.h>
#endif

#if defined LEM_LINUX
#include <memory.h>
#endif

#include <lem/runtime_checks.h>
#include <lem/solarix/ElapsedTimeConstraint.h>


using namespace Solarix;

#if defined LEM_LINUX
volatile int ElapsedTimeConstraint::time_seq=0;
#endif

ElapsedTimeConstraint::ElapsedTimeConstraint( int _max_elapsed_millisec )
{
 max_elapsed_millisec = _max_elapsed_millisec;
 exceeded=false;

 #if defined LEM_WINDOWS
 hTimerQueue = NULL;
 hTimer = NULL;
 #elif defined LEM_LINUX
 timer_is_armed = false;
 #endif

 if( max_elapsed_millisec>0 && max_elapsed_millisec<10000000 )
  {
   #if defined LEM_WINDOWS
   hTimerQueue = CreateTimerQueue();

   BOOL rc = CreateTimerQueueTimer( 
                                   &hTimer,
                                   hTimerQueue,
                                   (WAITORTIMERCALLBACK)TimerCallback,
                                   (void*)this,
                                   max_elapsed_millisec,
                                   0,
                                   WT_EXECUTEINTIMERTHREAD | WT_EXECUTEONLYONCE
                                  );

   #elif defined LEM_LINUX

//    timer_is_armed=true;

/*
    se.sigev_notify = SIGEV_THREAD;
    se.sigev_signo = 1;
    se.sigev_notify_function = &timer_routine;
    se.sigev_value.sival_ptr = this;
    int rc = timer_create(CLOCK_REALTIME, &se, &tt);
    if( rc!=0 )
     throw lem::E_BaseException( L"Can not create new timer by timer_create" );
     
    tv.it_interval.tv_sec = 0;
    tv.it_interval.tv_nsec = 0;
    tv.it_value.tv_sec = (max_elapsed_millisec/1000) + ( (max_elapsed_millisec%1000)>0 ? 1 : 0 );
    tv.it_value.tv_nsec = 0;
    rc = timer_settime(tt, 0, &tv, NULL);
    if( rc!=0 )
     throw lem::E_BaseException( L"Can not set timer by timer_settime" );
*/

/*
    // Establishing handler for signal SIG
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timer_routine;
    sigemptyset(&sa.sa_mask);
    if (sigaction( SIGRTMIN, &sa, NULL ) == -1)
     throw lem::E_BaseException( L"ElapsedTimeConstraint: error in sigaction" );

    // Create the timer
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = this;
    if( timer_create( CLOCK_REALTIME, &sev, &timerid ) == -1 )
     throw lem::E_BaseException( L"ElapsedTimeConstraint: error in timer_create" );

    // Start the timer
    its.it_value.tv_sec = (max_elapsed_millisec/1000) + ( (max_elapsed_millisec%1000)>0 ? 1 : 0 );
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
*/
   #else

   thread = new lem::Process::Thread( ThreadFunction );
   thread->Start( (void*)this );
   #endif
  }
}


#if defined LEM_WINDOWS
VOID CALLBACK ElapsedTimeConstraint::TimerCallback( PVOID lpParameter, BOOLEAN TimerOrWaitFired )
{
 ElapsedTimeConstraint * self = (ElapsedTimeConstraint*)lpParameter;
 self->exceeded = true;
 return;
}
#elif defined LEM_LINUX
void ElapsedTimeConstraint::timer_routine( int sig, siginfo_t * si, void * uc )
{
 ElapsedTimeConstraint * self = (ElapsedTimeConstraint*)si->si_value.sival_ptr;
 self->exceeded = true;
 signal( sig, SIG_IGN );
 return;
}
#else
void ElapsedTimeConstraint::ThreadFunction( void * data )
{
 ElapsedTimeConstraint * self = (ElapsedTimeConstraint*)data;
 lem::Process::Sleep( self->max_elapsed_millisec );
 self->exceeded = true;
 return;
}
#endif


ElapsedTimeConstraint::~ElapsedTimeConstraint()
{
 #if defined LEM_WINDOWS
 if( hTimer!=NULL )
  {
   DeleteTimerQueueEx( hTimerQueue, NULL );
   hTimerQueue = NULL;
  }
 #elif defined LEM_LINUX
 if( timer_is_armed )
  {
   timer_delete(&timerid);
  }
 #else
 if( thread!=NULL )
  {
   thread->Abort();
   delete thread;
  }
 #endif
 return;
}
