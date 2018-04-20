// CD->08.04.2007
// LC->20.04.2018
// --------------

#include <lem/config.h>

#if defined LEM_THREADS

#if defined LEM_MFC
#include <afx.h>
#endif

#if defined LEM_WINDOWS
#include <process.h>
#endif

#include <lem/process.h>

using namespace lem::Process;


Thread::Thread(start_address Adr)
#if defined LEM_WXWIDGETS
    : wxThread(wxTHREAD_JOINABLE)
#endif
{
    LEM_CHECKIT_Z(Adr != nullptr);

    adr = Adr;
    context = nullptr;

#if defined LEM_WXWIDGETS
    wxThread::Create();
#elif defined LEM_WINDOWS
    handle = nullptr;
#elif defined LEM_UNIX
    handle = nullptr;
#else
#error
#endif
}

Thread::~Thread(void)
{
    adr = nullptr;
    context = nullptr;

#if !defined LEM_WXWIDGETS
#if defined LEM_WINDOWS
    handle = nullptr;
#elif defined LEM_UNIX
    handle = nullptr;
#else
#error
#endif
#endif

    return;
}


void Thread::Start(void *Context)
{
    LEM_CHECKIT_Z(this != nullptr);

    context = Context;

#if defined LEM_WXWIDGETS

    wxThread::Run();

#elif defined LEM_WINDOWS

#if defined LEM_THREADS
#if defined LEM_BORLAND
    handle = (HANDLE)_beginthread((start_address)adr, 0, Context);
#else
    handle = (HANDLE)_beginthread((start_address)adr, 0, Context);
    //  handle = (HANDLE)_beginthread( (void(__cdecl*)(void*))adr, 0, Context );
#endif
#else
    handle = nullptr;
#endif
    // handle = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)adr, Context, 0, NULL );

    LEM_CHECKIT_Z(handle != nullptr);

#elif defined LEM_UNIX

    // int err = pthread_create( &handle, NULL, (start_address*)&adr, Context );
    int err = pthread_create(&handle, nullptr, (void*(*)(void*))&adr, Context);
    LEM_CHECKIT_Z(err == 0);

#else
#error
#endif
}


#if defined LEM_WXWIDGETS
wxThread::ExitCode Thread::Entry(void)
{
    LEM_CHECKIT_Z(this != nullptr);
    adr(context);
    return 0;
}
#endif

void Thread::Abort(void)
{
    LEM_CHECKIT_Z(this != nullptr);

#if defined LEM_WXWIDGETS
    wxThread::Kill();
#elif defined LEM_WINDOWS
    TerminateThread(handle, 0);
#elif defined LEM_UNIX
    pthread_cancel(handle);
#else
#error
#endif
}

#if !defined LEM_WXWIDGETS
void Thread::Pause(void)
{
    LEM_CHECKIT_Z(this != nullptr);

#if defined LEM_WINDOWS
    DWORD err = SuspendThread(handle);
    LEM_CHECKIT_Z(err != (DWORD)-1);
#elif defined LEM_UNIX
    // ???
#else
#error
#endif
}
#endif


#if !defined LEM_WXWIDGETS
void Thread::Resume(void)
{
    LEM_CHECKIT_Z(this != nullptr);

#if defined LEM_WINDOWS
    DWORD err = ResumeThread(handle);
    LEM_CHECKIT_Z(err != (DWORD)-1);
#elif defined LEM_UNIX
    // ??? 
#else
#error
#endif
}
#endif


void Thread::Fast(void)
{
    LEM_CHECKIT_Z(this != nullptr);

#if defined LEM_WXWIDGETS
    wxThread::SetPriority(WXTHREAD_MIN_PRIORITY);
#elif defined LEM_WINDOWS
    DWORD err = SetThreadPriority(handle, THREAD_PRIORITY_HIGHEST);
    LEM_CHECKIT_Z(err != 0);
#endif
}

void Thread::Normal(void)
{
    LEM_CHECKIT_Z(this != nullptr);

#if defined LEM_WXWIDGETS
    wxThread::SetPriority(WXTHREAD_DEFAULT_PRIORITY);
#elif defined LEM_WINDOWS
    // BOOL ok = SetPriorityClass( GetCurrentProcess(), IDLE_PRIORITY_CLASS );
    // LEM_CHECKIT_Z(ok!=0);
    DWORD err = SetThreadPriority(handle, THREAD_PRIORITY_NORMAL);
    LEM_CHECKIT_Z(err != 0);
#endif
}

void Thread::Slow(void)
{
    LEM_CHECKIT_Z(this != nullptr);

#if defined LEM_WXWIDGETS
    wxThread::SetPriority(WXTHREAD_MAX_PRIORITY);
#elif defined LEM_WINDOWS
    DWORD err = SetThreadPriority(handle, THREAD_PRIORITY_LOWEST);
    LEM_CHECKIT_Z(err != 0);
#endif
}


lem::Process::ThreadID Thread::GetCurrentID(void)
{
#if defined LEM_WINDOWS
    return GetCurrentThreadId();
#endif

#if defined LEM_UNIX
    return pthread_self();
#endif
}


int Thread::Id2Int(ThreadID id)
{
    return (int)id;
}

#endif
