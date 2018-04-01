// 11.03.2010 - для фреймворка Qt используется QDesktopServices
// 28.03.2018 - рефакторинг кода
//
// LC->28.03.2018
// --------------

#include <lem/config.h>

#if defined LEM_WINDOWS
 #include <windows.h>
#endif

#if defined LEM_WINDOWS
 #include <shlobj.h>
 #include <commdlg.h>
#endif

#if defined LEM_UNIX
 #if defined LEM_LINUX
  #include <ncurses.h>
 #else 
// #include <curses.h>
  #include <ncurses.h>
 #endif
#endif


#include <lem/strings.h>
#include <lem/system_config.h>
#include <lem/conversions.h>
#include <lem/logfile.h>

#if defined LEM_CONSOLE
 #include <lem/keyboard.h>
#endif

#if defined LEM_DOS
 #include <stdlib.h>
#endif

#include <lem/shell.h>

#if defined LEM_WINDOWS 
 #undef MessageBox
#endif


#if defined(LEM_MSC) && defined(LEM_WINDOWS)
#pragma comment ( lib, "shlwapi.lib" )
#pragma comment ( lib, "shell32.lib" )
#pragma comment ( lib, "comdlg32.lib" )
#endif

using namespace lem;
using namespace lem::Shell;



/*************************************************************************
 Запуск командного процессора Операционной Системы на исполнение, аргумент
 cmd задаёт командную строку, которая передатся интерпретатору для
 выполнения. Возвращается *true*, если запуск и исполнение интерпретатора
 успешны, иначе возвращаем *false*.
*************************************************************************/
/*
bool lem::Shell::Execute( const wchar_t *Filename )
{
 LEM_CHECKIT_Z( lem::lem_is_empty(Filename)==false );

 if( lem::lem_is_empty(Filename) )
  return false;

 #if defined LEM_QT

  QString url( QString("file:///"), QString::fromWCharArray(Filename) );
  return QDesktopServices::openUrl( url, QUrl::TolerantMode));

 #elif defined LEM_DOS

  #if defined LEM_USE_WCHAR
   const int res = _wsystem( Filename );
  #else
   char *buf = new char[lem_strlen(cmd)+1];
   lem_unicode_to_ascii( buf, cmd );
   const int res = std::system( buf );
   delete[] buf;
  #endif

 return res==0;

 #elif defined LEM_DOT_NET

  System::Diagnostics::Process *p = new System::Diagnostics::Process;
  bool res = p->Start( new System::String(Filename) );
  return res;

 #elif defined LEM_WINDOWS

 int hErr=0;

 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   wchar_t cwd[ lem::Path::MaxLen+1 ];
   memset( cwd, 0, sizeof(cwd) );
   GetCurrentDirectoryW( lem::Path::MaxLen, cwd );

   hErr = (int)ShellExecuteW( NULL, L"open", Filename, NULL, cwd, SW_SHOW );

   if( hErr==SE_ERR_NOASSOC || hErr==SE_ERR_ASSOCINCOMPLETE )
    {
     lem::UFString f( L"shell32.dll,OpenAs_RunDLL " );
     f += Filename;

     hErr = (int)ShellExecuteW( NULL, L"open", L"Rundll32.exe", f.c_str(), NULL, SW_SHOW );
    }
  }
 else
  {
   lem::UFString u(Filename);
   lem::FString a(lem::to_ascii(u));

   char cwd[ lem::Path::MaxLen+1 ];
   memset( cwd, 0, sizeof(cwd) );
   GetCurrentDirectoryA( lem::Path::MaxLen, cwd );

   hErr = (int)ShellExecuteA( NULL, "open", a.c_str(), NULL, cwd, SW_SHOW );

   if( hErr==SE_ERR_NOASSOC || hErr==SE_ERR_ASSOCINCOMPLETE )
    {
     lem::FString p( "shell32.dll,OpenAs_RunDLL " );
     p += a;

     hErr = (int)ShellExecuteA( NULL, "open", "Rundll32.exe", p.c_str(), NULL, SW_SHOW );
    }
  }

 return int(hErr)>32;

 #elif defined LEM_WXWIDGETS

 return wxShell( wxString(Filename) );

 #elif defined LEM_UNIX

 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   const int res = std::system( to_utf8( UFString(Filename) ).c_str() );
   return res==0;
  }
 else
  {
   const int res = std::system( to_ascii( UFString(Filename) ).c_str() );
   return res==0;
  }

 #else

 int res = _wsystem( Filename );
 return res==0;

 #endif
}


bool lem::Shell::Execute( const UFString& Appname, const UFString &Filename, bool Silent )
{
 LEM_CHECKIT_Z( !Appname.empty() && !Filename.empty() );

 if( Appname.empty() && Filename.empty() )
  return false;

 #if defined LEM_DOS

  UFString cmd( UFString(L"\"")+ Appname + UFString(L"\" \"") + Filename + UFString(L"\"") );
  #if defined LEM_USE_WCHAR
   const int res = _wsystem( cmd.c_str() );
  #else
   char *buf = new char[lem_strlen(cmd)+1];
   lem_unicode_to_ascii( buf, cmd );
   const int res = std::system( buf );
   delete[] buf;
  #endif

 return res==0;

 #elif defined LEM_DOT_NET

  System::Diagnostics::Process *p = new System::Diagnostics::Process;
  bool res = p->Start( new System::String(Appname.c_str()), new System::String(Filename.c_str()) );
  return res;

 #elif defined LEM_WINDOWS

 int hErr=0;

 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   hErr = (int)ShellExecuteW( NULL, L"open", Appname.c_str(), Filename.c_str(), NULL, Silent ? SW_HIDE : SW_SHOW );
  }
 else
  {
   lem::FString a1 = to_ascii(Appname);
   lem::FString a2 = to_ascii(Filename);

   hErr = (int)ShellExecuteA( NULL, "open", a1.c_str(), a2.c_str(), NULL, Silent ? SW_HIDE : SW_SHOW );
  }

 if( hErr<=32 )
  {
   if( lem::LogFile::IsOpen() )
    {
     lem::LogFile::logfile->printf( "ShellExecute Appname=%us Filename=%us error:", Appname.c_str(), Filename.c_str() );

     switch(hErr)
     {
      case ERROR_FILE_NOT_FOUND: lem::LogFile::logfile->printf( "The specified file was not found\n" ); break;
      case ERROR_PATH_NOT_FOUND: lem::LogFile::logfile->printf( "The specified path was not found\n" ); break; 
      case ERROR_BAD_FORMAT: lem::LogFile::logfile->printf( "The .exe file is invalid (non-Microsoft Win32® .exe or error in .exe image)\n" ); break; 
      case SE_ERR_ACCESSDENIED: lem::LogFile::logfile->printf( "The operating system denied access to the specified file\n" ); break; 
      case SE_ERR_ASSOCINCOMPLETE: lem::LogFile::logfile->printf( "The file name association is incomplete or invalid\n" ); break; 
      case SE_ERR_DDEBUSY: lem::LogFile::logfile->printf( "The Dynamic Data Exchange (DDE) transaction could not be completed because other DDE transactions were being processed\n" ); break;
      case SE_ERR_DDEFAIL: lem::LogFile::logfile->printf( "The DDE transaction failed\n" ); break; 
      case SE_ERR_DDETIMEOUT: lem::LogFile::logfile->printf( "The DDE transaction could not be completed because the request timed out\n" ); break; 
      case SE_ERR_DLLNOTFOUND: lem::LogFile::logfile->printf( "The specified dynamic-link library (DLL) was not found\n" ); break; 
//  case SE_ERR_FNF: printf( "The specified file was not found\n" ); break; 
      case SE_ERR_NOASSOC: lem::LogFile::logfile->printf( "There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable\n" ); break; 
      case SE_ERR_OOM: lem::LogFile::logfile->printf( "There was not enough memory to complete the operation\n" ); break; 
//  case SE_ERR_PNF: printf( "The specified path was not found\n" ); break; 
      case SE_ERR_SHARE: lem::LogFile::logfile->printf( "A sharing violation occurred\n" ); break; 
      default: lem::LogFile::logfile->printf( "Unknown error\n" ); break; 
     }
    }
  }

 return int(hErr)>32;

 #elif defined LEM_WXWIDGETS

 if( Appname.empty() )
  {
   bool res = ::wxLaunchDefaultBrowser( wxString(Filename.c_str()) );
   return res;
  }
 else
  {
   UFString cmd( UFString(L"\"")+ Appname + UFString(L"\" \"") + Filename + UFString(L"\"") );
   int res = _wsystem( cmd.c_str() );
   return res==0;
  }

 #elif defined LEM_UNIX

 UFString cmd( UFString(L"\"")+ Appname + UFString(L"\" \"") + Filename + UFString(L"\"") );


 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   const int res = std::system( to_utf8(cmd).c_str() );
   return res==0;
  }
 else
  {
   const int res = std::system( to_ascii(cmd).c_str() );
   return res==0;
  }

 #else

 UFString cmd( UFString(L"\"")+ Appname + UFString(L"\" \"") + Filename + UFString(L"\"") );

 int res = _wsystem( cmd.c_str() );
 return res==0;

 #endif
}


bool lem::Shell::Execute( const lem::Path &Filename )
{
 return Execute( Filename.GetUnicode().c_str() );
}


// Исполнение командной строки, которая может включать любую
// корректную для ОС операцию.
int lem::Shell::CommandLine( const lem::UFString &cmdline )
{
 #if defined LEM_WINDOWS 

 return lem::Shell::Execute( L"cmd", cmdline, false ) ? 0 : 1;

 #else
 if( lem::System_Config::IsFilesystemUtf8() ) 
  {
   return ::system( lem::to_utf8(cmdline).c_str() );
  }
 else
  {
   return ::system( lem::to_ascii(cmdline).c_str() );
  } 
 #endif 
}
*/

void lem::Shell::Error( const lem::UFString& Text )
{
 Error(Text.c_str());
}

void lem::Shell::Error( const lem::FString& Text )
{
 Error(Text.c_str());
}

static const wchar_t ru_error[]=L"\x41E\x448\x438\x431\x43A\x430";

// *************************************************
// Выводим сообщение об ошибке подходящим способом
// *************************************************
void lem::Shell::Error( const wchar_t *Text )
{
 UFString err_msg( lem::UI::get_UI().IsRussian() ? ru_error : L"Error" );

 #if defined LEM_CONSOLE

  #if defined LEM_UNIX
  endwin();
  #endif

 fflush(stdout);

 #if defined LEM_UNIX
 if( lem::System_Config::SupportUnicodeConsole() )
  {
   fprintf(
           stderr,
           "\n%s: %s\n",
           to_utf8(err_msg).c_str(),
           to_utf8(UFString(Text)).c_str()
          );
  }  
 else
 #endif
  {
   fprintf(
           stderr,
           "\n%s: %s\n",
           to_ascii(err_msg, &lem::UI::get_UI().GetTtyCp()).c_str(),
           to_ascii( UFString(Text), &lem::UI::get_UI().GetTtyCp()).c_str()
          );
  }

 #elif defined LEM_DOT_NET

  System::Windows::Forms::MessageBox::Show( Text );

 #elif defined LEM_WXWIDGETS
  wxWindow *wnd = NULL;
  if( lem::WxForms::WinApp::app!=NULL )
   wnd = lem::WxForms::WinApp::app->GetFrontWindow();
  else
   wnd = wxTheApp->GetTopWindow();

  wxMessageDialog dlg( wnd, wxString(Text), err_msg.c_str(), wxOK | wxICON_ERROR );
  dlg.ShowModal();

 #elif defined LEM_QT

  QMessageBox mb;
  mb.setText( QString::fromWCharArray(Text) );
  mb.exec();

 #elif defined LEM_WINDOWS
  #if defined LEM_MFC
  HWND hWnd = AfxGetMainWnd()->m_hWnd;
  #else 
  HWND hWnd = GetForegroundWindow();
  #endif

 if( lem::System_Config::SupportUnicodeGui() )
  MessageBoxW( hWnd, Text, err_msg.c_str(), MB_OK | MB_ICONERROR );
 else 
  MessageBoxA(
              hWnd,
              to_ascii( UFString(Text) ).c_str(),
              to_ascii( err_msg ).c_str(),
              MB_OK | MB_ICONERROR
             );
 #else
  #error ...
 #endif

 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "lem::Shell::Error->%us\n", Text );

 return;
}
 

void lem::Shell::Error( const char *Text )
{
 lem::Shell::Error( to_unicode( FString(Text) ).c_str() );
}


void lem::Shell::Error( const lem::UFString& Text, const lem::UFString& Title )
{ Error( Text.c_str(), Title.c_str() ); }


void lem::Shell::Error( const wchar_t *Text, const wchar_t *Title )
{
 #if defined LEM_CONSOLE

  #if defined LEM_UNIX
  endwin();
  #endif

 fflush(stdout);

 #if defined LEM_UNIX
 if( lem::System_Config::SupportUnicodeConsole() )
  {
   fprintf(
           stderr,
           "\n%s: %s\n",
           to_utf8( UFString(Title) ).c_str(),
           to_utf8( UFString(Text) ).c_str()
          );
  }
 else
 #endif 
  {
   fprintf(
           stderr,
           "\n%s: %s\n",
           to_ascii( UFString(Title), &lem::UI::get_UI().GetTtyCp()).c_str(),
           to_ascii( UFString(Text), &lem::UI::get_UI().GetTtyCp()).c_str()
          );
  }

 #elif defined LEM_DOT_NET
 System::Windows::Forms::MessageBox::Show( Text );
 #elif defined LEM_WXWIDGETS
  wxWindow *wnd = NULL;
  if( lem::WxForms::WinApp::app!=NULL )
   wnd = lem::WxForms::WinApp::app->GetFrontWindow();
  else
   wnd = wxTheApp->GetTopWindow();

  wxMessageDialog dlg( wnd, wxString(Text), wxString(Title), wxOK | wxICON_ERROR );
  dlg.ShowModal();

 #elif defined LEM_QT

  QMessageBox mb;
  mb.setText( QString::fromWCharArray(Title) );
  mb.setInformativeText( QString::fromWCharArray(Text) );
  mb.exec();

 #elif defined LEM_WINDOWS
  #if defined LEM_MFC
  HWND hWnd = AfxGetMainWnd()->m_hWnd;
  #else 
  HWND hWnd = GetForegroundWindow();
  #endif

 if( lem::System_Config::SupportUnicodeGui() )
  MessageBoxW( hWnd, Text, Title, MB_OK | MB_ICONERROR );
 else 
  MessageBoxA(
              hWnd,
              to_ascii( UFString(Text) ).c_str(),
              to_ascii( UFString(Title) ).c_str(),
              MB_OK | MB_ICONERROR
             );
 #else
  #error ...
 #endif

 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "lem::Shell::Error->%ls : %ls: %ls\n", Title, Text );

 return;
}


// ********************************************************************
// Стандартный диалог для выбора каталога.
// Опциональный аргумент start_path - каталог, с которого нужно начать
// просмотр.
// ********************************************************************

#if defined LEM_QT
lem::Path lem::Shell::AskFolder( const wchar_t *message, QWidget* hWnd )
#else
lem::Path lem::Shell::AskFolder( const wchar_t *message, void* hWnd )
#endif
{
 lem::Path empty;
 return AskFolder(message,hWnd,empty);
}

#if defined LEM_QT
lem::Path lem::Shell::AskFolder( const wchar_t *message, QWidget* qWnd, const lem::Path &start_path )
#else
lem::Path lem::Shell::AskFolder( const wchar_t *message, void* hWnd, const lem::Path &start_path )
#endif
{
 #if defined LEM_QT

  QString fileName = QFileDialog::getOpenFileName( qWnd, QString::fromWCharArray(message), QString::fromWCharArray(start_path.GetUnicode().c_str()) );
  lem::UFString us(fileName);
  return lem::Path(us);

 #elif defined LEM_WINDOWS && defined LEM_GUI

 static bool first = true;
 wchar_t Folder[512]=L"";

 if( first )
  {
   first = false;
   CoInitialize(NULL);
  }

 BROWSEINFOW bi;

 if( hWnd!=NULL )
  {
   bi.hwndOwner = (HWND)hWnd;
  }
 else
  {
   #if defined LEM_MFC
   bi.hwndOwner = AfxGetMainWnd()->m_hWnd;
   #else 
   bi.hwndOwner = GetForegroundWindow();
   #endif
  }

 if( lem::lem_is_empty(message) )
  bi.lpszTitle = L"Select destination folder";
 else
  bi.lpszTitle = message;

 bi.pidlRoot = NULL;
 bi.pszDisplayName = Folder;
 bi.ulFlags = BIF_USENEWUI | BIF_RETURNONLYFSDIRS; //0; //BIF_BROWSEFORCOMPUTER;
 //bi.lpfn = NULL;
 bi.lpfn = BrowseCallbackProc;

 UFString str_path( start_path.GetUnicode() );

 if( str_path.empty() )
  bi.lParam = 0;
 else
  bi.lParam = (LPARAM)str_path.c_str();

 bi.iImage=-1;
 LPITEMIDLIST list = SHBrowseForFolderW(&bi);

 LPMALLOC pMalloc = NULL;
 SHGetMalloc( &pMalloc );

 if( list )
  {
   IShellFolder *ppshf=NULL;
   HRESULT hr = SHGetDesktopFolder( &ppshf );

   LPITEMIDLIST pidlMyComputer=NULL, pidlMyDocuments=NULL;

   hr = SHGetSpecialFolderLocation( NULL, CSIDL_PERSONAL, &pidlMyDocuments );
   if( hr==S_OK && pidlMyDocuments!=NULL )
    {
     if( ppshf!=NULL && ppshf->CompareIDs(SHCIDS_CANONICALONLY,pidlMyDocuments,list)==0 )
      {
       ppshf->Release();
       pMalloc->Release();
       return lem::Path::GetMyDocuments();
      } 
    }
    
   hr = SHGetSpecialFolderLocation( (HWND)hWnd, CSIDL_DRIVES, &pidlMyComputer );
   if( hr==S_OK && pidlMyComputer!=NULL )
    {
     if( ppshf!=NULL && ppshf->CompareIDs(SHCIDS_CANONICALONLY,pidlMyComputer,list)==0 )
      {
       ppshf->Release();
       pMalloc->Release();
       return lem::Path(L"\\\\.");
      }
    }

   if( ppshf!=NULL )
    {
     ppshf->Release();
     ppshf=NULL;
    }

   if( SHGetPathFromIDListW( list, Folder ) )
    {
     if( pMalloc!=NULL )
      {
       pMalloc->Free(list);
       pMalloc->Release();
       pMalloc=NULL;
      }

     lem::Path p(Folder);
     return p;
    }
  }


 if( pMalloc!=NULL )
  {
   pMalloc->Free(list);
   pMalloc->Release();
  } 

 lem::Path empty;
 return empty;
 
 #elif defined LEM_WXWIDGETS
 wxString title;

 if( lem::lem_is_empty(message) )
  title = L"Select destination folder";
 else
  title = message;

 wxString dir = wxDirSelector(title);
 lem::Path p(dir.c_str());
 return p;

 #elif defined LEM_CONSOLE

 if( message!=NULL )
  mout->printf( "%us", message );

 while(true)
  { 
   UFString s = mkey->ask_ufstring();

   if( !s.empty() )
    {
     return lem::Path(s);
    }
  }

 #else

 lem::Path empty;
 return empty;

 #endif
}


/*
bool lem::Shell::Execute( const UFString &Filename )
{
 return Execute( Filename.c_str() );
}
*/

void lem::Shell::Message( const char *Text )
{
 lem::Shell::Message( to_unicode( FString(Text) ) );
} 


void lem::Shell::Message( const wchar_t *Text )
{
 #if defined LEM_CONSOLE

  #if defined LEM_UNIX
  endwin();
  #endif

  fflush(stdout);

  if( lem::System_Config::SupportUnicodeConsole() )
   fprintf(stdout, "%s\n", to_utf8(UFString(Text)).c_str() );
  else
   fprintf(stdout, "%s\n", to_ascii( UFString(Text),&lem::UI::get_UI().GetTtyCp()).c_str() );

 #elif defined LEM_DOT_NET

 System::Windows::Forms::MessageBox::Show( Text );

 #elif defined LEM_WINDOWS

  #if defined LEM_MFC
  HWND hWnd = AfxGetMainWnd()->m_hWnd;
  #else 
  HWND hWnd = GetForegroundWindow();
  #endif

 if( lem::System_Config::SupportUnicodeGui() )
  MessageBoxW( hWnd, Text, L"", MB_OK );
 else 
  MessageBoxA( hWnd, to_ascii( UFString(Text) ).c_str(), "", MB_OK );

 #elif defined LEM_WXWIDGETS

  wxWindow *wnd = NULL;
  if( lem::WxForms::WinApp::app!=NULL )
   wnd = lem::WxForms::WinApp::app->GetFrontWindow();
  else
   wnd = wxTheApp->GetTopWindow();

  wxMessageDialog dlg( wnd, wxString(Text), wxTheApp->GetAppName().c_str(), wxOK );
  dlg.ShowModal();

 #elif defined LEM_QT

  QMessageBox mb;
  mb.setText( QString::fromWCharArray(Text) );
  mb.exec();

 #else

  #error ...

 #endif
}

void lem::Shell::Message( const lem::UFString& Text )
{
 lem::Shell::Message(Text.c_str());
}



#if defined LEM_DOT_NET
void lem::Shell::Error( System::String *Text, System::String *Title )
{
 if( Title!=NULL )
  lem::Shell::Error( to_ustr(Text), to_ustr(Title) ); 
 else
  lem::Shell::Error( to_ustr(Text).c_str() ); 
}
#endif


void lem::Shell::Error( const std::wstring &Text )
{ lem::Shell::Error(Text.c_str()); }


void lem::Shell::Error( const std::string &Text )
{ lem::Shell::Error(Text.c_str()); }
