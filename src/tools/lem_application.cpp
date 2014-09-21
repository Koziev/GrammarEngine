#include <lem/config.h>


#if defined LEM_WINDOWS
 #if defined LEM_MFC
  #include <crtdbg.h> 
  #include <afxwin.h>
  #else
  #include <windows.h>
 #endif
#endif

#if defined LEM_UNIX
 #include <sched.h>
#endif

#if defined LEM_FORMS && defined LEM_GUI
 #include <lem/forms/forms.h>
#endif

#if defined LEM_WXWIDGETS && defined LEM_GUI
 #include <lem/forms/wxforms.h>
#endif

#if defined LEM_BORLAND && defined LEM_GUI
#include <vcl.h>
#endif

#if defined LEM_QT
 #include <QCoreApplication>
#endif

#include <lem/application.h>



#if defined LEM_MSC && defined LEM_WINDOWS && defined LEM_MFC

#ifndef _AFXDLL
    #ifndef _UNICODE
        #ifdef _DEBUG
            #pragma comment(lib, "nafxcwd.lib")
        #else
            #pragma comment(lib, "nafxcw.lib")
        #endif
    #else
        #ifdef _DEBUG
            #pragma comment(lib, "uafxcwd.lib")
        #else
            #pragma comment(lib, "uafxcw.lib")
        #endif
    #endif
#else
    #ifndef _UNICODE
        #ifdef _DEBUG
            #pragma comment(lib, "mfc71d.lib")
            #pragma comment(lib, "mfcs71d.lib")
        #else
            #pragma comment(lib, "mfc71.lib")
            #pragma comment(lib, "mfcs71.lib")
        #endif
    #else
        #ifdef _DEBUG
            #pragma comment(lib, "mfc71ud.lib")
            #pragma comment(lib, "mfcs71ud.lib")
        #else
            #pragma comment(lib, "mfc71u.lib")
            #pragma comment(lib, "mfcs71u.lib")
        #endif
    #endif
#endif

#ifdef _DLL
    #if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
        #pragma comment(lib, "msvcrtd.lib")
    #else
        #pragma comment(lib, "msvcrt.lib")
    #endif
#else
#ifdef _MT
    #if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
        #pragma comment(lib, "libcmtd.lib")
    #else
        #pragma comment(lib, "libcmt.lib")
    #endif
#else
    #if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
        #pragma comment(lib, "libcd.lib")
    #else
        #pragma comment(lib, "libc.lib")
    #endif
#endif
#endif

// force inclusion of NOLIB.OBJ for /disallowlib directives
#pragma comment(linker, "/include:__afxForceEXCLUDE")

// force inclusion of DLLMODUL.OBJ for _USRDLL
#ifdef _USRDLL
#pragma comment(linker, "/include:__afxForceUSRDLL")
#endif

// force inclusion of STDAFX.OBJ for precompiled types
#ifdef _AFXDLL
#pragma comment(linker, "/include:__afxForceSTDAFX")
#endif

#endif


using namespace lem;

// ***********************************************
// Process all GUI events in the app main queue
// ***********************************************
void lem::Application::DoEvents(void)
{
 #if defined LEM_QT

 QCoreApplication()::instance()->processEvents();

 #elif defined LEM_CONSOLE

  #if defined LEM_WINDOWS
   Sleep(0);
  #elif defined LEM_UNIX
   sched_yield();
  #endif

  return;

 #elif defined LEM_FORMS && defined LEM_GUI

  lem::Forms::WinApp::app->DoEvents();

 #elif defined LEM_WXWIDGETS && defined LEM_GUI

  lem::WxForms::DoEvents();

 #elif defined LEM_DOT_NET && defined LEM_GUI

  System::Windows::Forms::Application::DoEvents();

 #elif defined LEM_BORLAND && defined LEM_GUI

  Forms::Application->ProcessMessages();

 #elif defined LEM_MFC

  bool process=true;
  while( process )
   {
    MSG msg;
    // Are there any message available?
    while( ::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
     {
      // Yes - retrieve it.
      if( !AfxGetThread()->PumpMessage() )
       {
        ::PostQuitMessage(0);
       }
      else
       {
        long lIdle=0;
//        while( AfxGetApp()->OnIdle(lIdle++) );
       }

      process = false;
      break;
     }
   }

  return;

 #else

  return;

 #endif
}

// ******************************************
// Return the application handle if possible
// ******************************************
void* lem::Application::GetHandle(void)
{
 #if defined LEM_WXWIDGETS && defined LEM_GUI
 HINSTANCE hApp = lem::WxForms::WinApp::GetHandle();
 return hApp;
 #elif defined LEM_FORMS && defined LEM_GUI
 HINSTANCE hApp = lem::Forms::WinApp::GetHandle();
 return hApp;
 #elif defined LEM_MFC
 return AfxGetInstanceHandle();
 #elif defined LEM_WINDOWS
 return GetModuleHandle(NULL);  
 #else
 return NULL;
 #endif
}
