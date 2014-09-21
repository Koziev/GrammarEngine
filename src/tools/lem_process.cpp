// ---------------------------------------------------------
// CD->21.04.2007
// LC->11.03.2010
// --------------

#include <lem/config.h>

#if defined LEM_MFC
 #include <afx.h>
#endif

#if defined LEM_QT
 #include <QThread>
 #include <QCoreApplication>
#endif

#include <stdlib.h>
#include <lem/process.h>

using namespace lem;

void lem::Process::Exit( int RetCode )
{
 #if LEM_DEBUGGING
  LEM_TRAP;
 #endif
 
 #if defined LEM_QT
  QCoreApplication::instance()->exit(RetCode();
 #elif defined LEM_DOTNET
 System::Application::Exit(RetCode);  
 #else
 exit(RetCode);
 #endif
}

void lem::Process::Sleep( int msec )
{
 if( msec==0 )
  return;

 #if defined LEM_WINDOWS
  ::Sleep(msec);
 #elif defined LEM_UNIX
  usleep(msec*1000);
 #elif defined LEM_QT

  QThread::currentThread()->msleep(msec);
 #else
  
 #endif
}


// ********************************
// pid текущего процесса
// ********************************
int lem::Process::GetID(void)
{
 #if defined LEM_UNIX
  return (int)getpid(); 
 #elif defined LEM_WINDOWS
  return (int)GetCurrentProcessId();
 #elif defined LEM_QT
  return QCoreApplication::instance()->applicationPid();
 #else
  #error
 #endif
}


// **************************************
// Жив ли еще процесс с указанным pid
// **************************************
bool lem::Process::DoesExist( int pid )
{
 #if defined LEM_WINDOWS
 HANDLE h = OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, pid );
 if( h!=NULL )
  CloseHandle(h);

 return h!=NULL;
 #elif defined LEM_UNIX

 char fname[64];
 sprintf( fname, "/proc/%d/cmdline", pid );
 return lem::Path::DoesExist(fname);

 //pid_t f = getpgid(pid);
 //return f!=(pid_t)-1;

 #else
 #error;
 #endif
}
