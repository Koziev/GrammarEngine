#ifndef LEM_PROCESS__H
#define LEM_PROCESS__H
#pragma once

 #include <lem/config.h>
 #include <boost/utility.hpp>

 #if defined LEM_QT
  #include <QLibrary>
 #endif

 #if defined LEM_WXWIDGETS
  #include <wx/wx.h>
  #include <wx/dynlib.h>
  #include <wx/thread.h>
  #if !defined CALLBACK
   #define CALLBACK 
  #endif
 #elif defined LEM_WINDOWS

  #if defined LEM_MFC
   #include <afxwin.h>
  #else
   #include <windows.h>
  #endif

  #include <process.h>
 #elif defined LEM_UNIX
  #include <pthread.h>
  #define CALLBACK  
 #else
  #error
  #define CALLBACK 
 #endif

 #if !defined DLL_ENTRY
  #if defined LEM_UNIX
   #define DLL_ENTRY  extern "C" /*__cdecl*/
  #elif defined LEM_WINDOWS
   #if defined DLL_EXPORTS || defined _USRDLL
    #define DLL_ENTRY extern "C" __declspec(dllexport)
   #else
    #define DLL_ENTRY extern "C" __declspec(dllimport)
   #endif
  #else
   #define DLL_ENTRY 
  #endif
 #endif


 #if !defined LEM_EXPORT_FUN
  #if defined LEM_WINDOWS
   #define LEM_EXPORT_FUN(RetType) __declspec(dllexport) RetType
   #define LEM_IMPORT_FUN(RetType) __declspec(dllimport) RetType
  #elif defined LEM_UNIX && defined LEM_GNUC
   #define LEM_EXPORT_FUN(RetType) extern "C" RetType __attribute__((visibility("default")))
   #define LEM_IMPORT_FUN(RetType) extern "C" RetType
  #else
   #error Unknown platform
  #endif
 #endif


 #if defined LEM_LINUX
  #if defined HAVE_ATOMIC_H
   #include <asm/atomic.h>
  #elif defined USE_GLIB
   #include <glib.h>
  #endif
 #elif defined LEM_FREEBSD
  #include <atomic.h> // src/sys/i386/include/atomic.h
 #elif defined LEM_SUNOS
  #include <sys/atomic.h>
 #elif defined LEM_DARWIN
  //#include <sys/atomic.h>
 #endif

 #if defined LEM_UNIX
  #include <pthread.h> 
 #endif

 #include <lem/path.h> 

 namespace lem
 {
  namespace Process
  {
   // ***********************************
   // Динамически загружаемые библиотеки
   // ***********************************
   class Dll : boost::noncopyable
   {
    private:
     lem::UFString error_msg;
    
     #if defined LEM_WXWIDGETS
     wxDynamicLibrary *wxdll;
     #elif defined LEM_QT
     QLibrary *qtdll;
     #elif defined LEM_WINDOWS
     HMODULE hlib;
     #elif defined LEM_UNIX || defined LEM_DARWIN
     void* hlib;
     #endif 

    protected:
     lem::Path filename; // откуда была загружена библиотека

    public:   
     Dll(void);
     virtual ~Dll(void);

     // Стандартное расширение для DLL файлов для текущей платформы
     static const char* StdExtension(void);
     
     const wchar_t* Error(void) const; 

     // Load a shared library from a given path.
     // Загрузка DLL из указанного файла.
     bool Load( const lem::Path& filename, bool add_extension=false );
     bool Load( const char *filename, bool add_extension=false );
     bool Load( const wchar_t *filename, bool add_extension=false );
       
     // Close a shared library
     // Выгружаем DLL
     void Free(void);
 
     // Загружена ли DLL
     bool IsLoaded(void) const;

     // Load a symbol from a shared library
     // Возвращает адрес экспортируемого символа
     const void* Import( const char *name ) const;

     // Есть ли указанный экспортированный символ
     bool HasSymbol( const char *name ) const;

     // Из какого файла была загружена DLL
     const lem::Path& GetFilename(void) const { return filename; }
   };


   #if defined LEM_THREADS

   #if defined LEM_WINDOWS
    #define LEM_THREADADR void __cdecl
   #else
    #define LEM_THREADADR void
   #endif

   #if defined LEM_WINDOWS
   typedef int ThreadID;
   #else
   typedef pthread_t ThreadID;
   #endif

   #if defined LEM_WXWIDGETS
   class Thread : public wxThread
   #else
   class Thread
   #endif
   {
    public:
     static ThreadID GetCurrentID(void);
     static int Id2Int( ThreadID id );

    private:
     #if !defined LEM_WXWIDGETS
      #if defined LEM_WINDOWS
      HANDLE handle;
      #elif defined LEM_UNIX
      pthread_t handle;
      #else
      // ...
      #endif
     #endif

     #if defined LEM_WXWIDGETS
     virtual ExitCode Entry(void);
     #endif

    public:
     #if defined LEM_WINDOWS
     typedef void( __cdecl *start_address )( void * );
     #else
     typedef void(*start_address)( void * );
     #endif

    protected:
     void *context; // входные данные

    public:
     start_address adr; // адрес исполняемой процедуры

     #if defined LEM_MSC && _MSC_VER<1300
     Thread( /*Thread::*/start_address Adr );
     #else
     Thread( Thread::start_address Adr );
     #endif

     ~Thread(void);

     void Start( void *Context=NULL );
     void Abort(void);

     #if !defined LEM_WXWIDGETS
     void Pause(void);
     void Resume(void);
     #endif

     void Fast(void);
     void Normal(void);
     void Slow(void);
   };
  #endif

  #if defined LEM_WXWIDGETS && !defined LEM_WINDOWS && defined LEM_THREADS
  typedef wxCriticalSection CriticalSection;
  #else
  class CriticalSection
  {
   private:
    #if defined LEM_THREADS

    #if defined LEM_WINDOWS
    CRITICAL_SECTION cs;
    #endif

    #if defined LEM_UNIX
    pthread_mutexattr_t attr;
    pthread_mutex_t cs;
    #endif

    #endif

   public:
    CriticalSection(void);
    ~CriticalSection(void);

    void Enter(void);
    void Leave(void);
    bool TryEnter(void);
  };
  #endif


  #if defined LEM_THREADS
  // **********************************************************
  // Для автоматизации разблокирования критической секции при
  // выходе из области видимости в генераторах исключений.
  // **********************************************************
  class CritSecLocker
  {
   private:
    CriticalSection *cs;

   public:
    CritSecLocker( CriticalSection *CS );
    ~CritSecLocker(void);
  };
  #endif


  #if defined LEM_THREADS
  #if defined LEM_WXWIDGETS
  class Mutex : public wxMutex
  #else
  class Mutex
  #endif
  {
   private:
    #if defined LEM_WINDOWS
    HANDLE mtx;
    #endif

   public:
    Mutex(void);
    ~Mutex(void);

    bool Lock(void);
    bool TryLock(void);
    bool Unlock(void);
  };
  #endif

   #if defined LEM_THREADS
   class Event
   {
    private:
     #if defined LEM_WINDOWS
     HANDLE hEvent;
     #endif

    public:
     Event(void);
     ~Event(void);

     bool IsOk(void);
     void Signal(void);
     void Wait(void);
     void Reset(void);
   };
   #endif


   class InterlockedInt
   { 
    private:
     #if defined LEM_WINDOWS
     volatile LONG value;
     #elif defined LEM_LINUX
      #if defined HAVE_ATOMIC_H     
       volatile atomic_t value;
      #elif defined USE_GLIB
       volatile gint value;
      #else
       volatile int value;
      #endif 
     #elif defined LEM_FREEBSD
     volatile int value;
     #elif defined LEM_DARWIN
     volatile int value;
     #else
     volatile int value;
     #endif

    public:
     InterlockedInt(void)
     #if defined LEM_WINDOWS
      : value(0) {}
     #elif defined LEM_LINUX
      {
       #if defined HAVE_ATOMIC_H
        atomic_set(&value,0);
       #elif defined USE_GLIB
        g_atomic_int_set(&value,0);
       #else
        value=0;   
       #endif 
      }
     #elif defined LEM_DARWIN
      {
       value=0;   
      }
     #else
      #error
     #endif

     InterlockedInt( int i )
     #if defined LEM_WINDOWS
      : value(i) {}
     #elif defined LEM_LINUX || defined LEM_UNIX
      {
       #if defined HAVE_ATOMIC_H
        atomic_set(&value,i);
       #elif defined USE_GLIB
        g_atomic_int_set(&value,i);
       #else
        value=i;
       #endif 
      }
     #elif defined LEM_DARWIN
      value=i;
     #else
      #error
     #endif
     

     InterlockedInt( const InterlockedInt &x );

     void operator=( const InterlockedInt &x );
     void operator=( int x );

     int operator++(void);
     int operator--(void);
     int operator++(int);
     int operator--(int);

     int operator+=( int x );

     inline bool operator==( int x ) const
     #if defined LEM_WINDOWS
     { return value==x; }
     #elif defined LEM_LINUX
     { return get()==x; }
     #elif defined LEM_FREEBSD
     { return value==x; }
     #else
     { return value==x; }
     #endif


     inline bool operator!=( int x ) const
     #if defined LEM_WINDOWS
     { return value!=x; }
     #elif defined LEM_LINUX
     { return get()!=x; }
     #elif defined LEM_FREEBSD
     { return value!=x; }
     #else
     { return value!=x; }
     #endif

     inline bool operator>( int x ) const
     #if defined LEM_WINDOWS
     { return value>x; }
     #elif defined LEM_LINUX
     { return get()>x; }
     #elif defined LEM_FREEBSD
     { return value>x; }
     #else
     { return value>x; }
     #endif

     inline bool operator>=( int x ) const
     #if defined LEM_WINDOWS
     { return value>=x; }
     #elif defined LEM_LINUX
     { return get()>=x; }
     #elif defined LEM_FREEBSD
     { return value>=x; }
     #else
     { return value>=x; }
     #endif

     inline bool operator<( int x ) const
     #if defined LEM_WINDOWS
     { return value<x; }
     #elif defined LEM_LINUX
     { return get()<x; }
     #elif defined LEM_FREEBSD
     { return value<x; }
     #else
     { return value<x; }
     #endif

     inline bool operator<=( int x ) const
     #if defined LEM_WINDOWS
     { return value<=x; }
     #elif defined LEM_LINUX
     { return get()<=x; }
     #elif defined LEM_FREEBSD
     { return value<=x; }
     #else
     { return value<=x; }
     #endif

     #if defined LEM_WINDOWS
     inline operator int(void) const { return value; }
     inline int get(void) const { return value; }
     #elif defined LEM_LINUX
       #if defined HAVE_ATOMIC_H
        inline operator int(void) const { return atomic_read(&value); }
        inline int get(void) const { return atomic_read(&value); }
       #elif defined USE_GLIB
        inline operator int(void) const { return g_atomic_int_get(&value); }
        inline int get(void) const { return g_atomic_int_get(&value); }
       #else
        inline operator int(void) const { return value; }
        inline int get(void) const { return value; }
       #endif 
     #elif defined LEM_FREEBSD
     inline operator int(void) const { return value; }
     inline int get(void) const { return value; }
     #else
     inline operator int(void) const { return value; }
     inline int get(void) const { return value; }
     #endif
   };


   // Terminates the program and sets the exit code to RetCode.
   extern void Exit( int RetCode=0 );

   // Freeze the program execution for a given interval
   extern void Sleep( int msec );

   // pid
   extern int GetID(void);
   extern bool DoesExist( int pid );

  } // namespace Process

 } // namespace lem

#endif
