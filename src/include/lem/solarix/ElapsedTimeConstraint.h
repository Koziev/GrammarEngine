#if !defined ElapsedTimeConstraint__H
#define ElapsedTimeConstraint__H

#include <lem/noncopyable.h>

#if defined LEM_WINDOWS
#include <windows.h>
#elif defined LEM_LINUX
#include <signal.h>
#include <time.h>
#else
#include <lem/process.h>
#endif

namespace Solarix
{
 class ElapsedTimeConstraint : lem::NonCopyable
 {
  private:
   #if defined LEM_WINDOWS
   HANDLE hTimerQueue, hTimer;
   static VOID CALLBACK TimerCallback( PVOID lpParameter, BOOLEAN TimerOrWaitFired );
   #elif defined LEM_LINUX
   bool timer_is_armed;
   static volatile int time_seq;
   timer_t timerid;
   struct sigevent sev;
   struct itimerspec its;
   struct sigaction sa;
   static void timer_routine( int sig, siginfo_t * si, void * uc );
   #else
   lem::Process::Thread * thread;
   static void ThreadFunction( void * data );
   #endif

   int max_elapsed_millisec;
   volatile bool exceeded;
   
  public:
   ElapsedTimeConstraint( int _max_elapsed_millisec );
   ~ElapsedTimeConstraint();

   int GetTimeout() const { return max_elapsed_millisec; }
   inline bool Exceeded() const { return exceeded; }
 };
}

#endif
