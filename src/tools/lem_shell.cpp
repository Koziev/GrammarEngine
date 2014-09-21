// File LEM_SHELL.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
//
// Namespace lem::Shell - собрание всевозможных процедур для вывода 
// уведомлений, сообщений об ошибках, звуковых сигналов, диалоговых
// окон для выбора файлов и каталогов, запуск приложений и прочее.
//
// 11.03.2010 - для фреймворка Qt используется QDesktopServices
//
// LC->11.03.2010
// --------------

#include <lem/config.h>

#if defined LEM_WINDOWS && !defined LEM_MFC && !defined LEM_VCL
 #include <windows.h>
#endif

#if defined LEM_MFC
 #include <afxwin.h>
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

#if defined LEM_DOT_NET
 #using <mscorlib.dll>
 #using <system.dll>
 #using <System.Windows.Forms.DLL>
#endif

#if defined LEM_WXWIDGETS
 #include <wx/clipbrd.h>
 #include <wx/utils.h>
 #include <wx/dirdlg.h>
 #include <wx/app.h>
 #include <wx/msgdlg.h>
 #include <lem/forms/wxforms.h>
#endif

#if defined LEM_QT
 #undef scroll
 #include <QMessageBox>
 #include <QDesktopServices>
#endif

#include <lem/strings.h>
#include <lem/system_config.h>
#include <lem/conversions.h>
#include <lem/logfile.h>

#if defined LEM_CONSOLE
 #include <lem/keyboard.h>
#endif

#if defined LEM_GUI && defined LEM_FORMS
 #include <lem/forms/forms.h>
#endif

#if defined LEM_DOS
 #include <stdlib.h>
#endif

#if defined LEM_QT
 #undef scroll
 #include <QFileDialog>
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



bool lem::Shell::PathToClipboard( void* hWnd, const wchar_t *path )
{
 if( !path || !*path )
  return false;

 #if defined LEM_WINDOWS

 if( !OpenClipboard((HWND)hWnd) ) 
  return false;

 EmptyClipboard(); 

 const int plen = CastSizeToInt(wcslen(path));

 HGLOBAL hglbCopy = GlobalAlloc( GMEM_MOVEABLE, (plen+1)*sizeof(wchar_t) ); 
 if( hglbCopy == NULL )   
  {
   CloseClipboard();
   return false;
  }
 
 // Lock the handle and copy the text to the buffer. 
 wchar_t *dest = (wchar_t*)GlobalLock(hglbCopy); 
 wcscpy( dest, path );
 GlobalUnlock(hglbCopy); 
 SetClipboardData(CF_UNICODETEXT, hglbCopy); 

 // Теперь скопируем в буфер имя файла в формате, который понимает Explorer
 // В конце ставится 2 символа \0
 DWORD szBuf = (plen+2)*sizeof(wchar_t) + sizeof(DROPFILES);
 hglbCopy = GlobalAlloc( GMEM_MOVEABLE, szBuf ); 
 if( hglbCopy == NULL )   
  {
   CloseClipboard();
   return false;
  }
 
 // Lock the handle and copy the text to the buffer. 
 DROPFILES *ptr = (DROPFILES*)GlobalLock(hglbCopy); 
 memset( ptr, 0, sizeof(DROPFILES) );
 ptr->fWide=TRUE;
 ptr->pFiles=sizeof(DROPFILES); 
 wchar_t *ptrFile = (wchar_t*)(((char*)ptr) + sizeof(DROPFILES));
 wcscpy( ptrFile, path );
 ptrFile[ plen+1 ] = L'\0';

 GlobalUnlock(hglbCopy); 
 SetClipboardData(CF_HDROP, hglbCopy); 

 return CloseClipboard()==TRUE;

 #elif defined LEM_WXWIDGETS

 if( !wxOpenClipboard() ) 
  return false;

 wxEmptyClipboard(); 
 SetClipboardData(CF_HDROP, hglbCopy); 
 wxSetClipboardData( wxCF_TEXT, new wxString(path), -1, -1 )
 return wxCloseClipboard();

 #else

 return true;
 #endif
}


bool lem::Shell::PathsToClipboard( void* hWnd, const lem::Collect<UFString> &list )
{
 if( list.empty() )
  return false;

 #if defined LEM_WINDOWS

 if( !OpenClipboard((HWND)hWnd) ) 
  return false;

 EmptyClipboard();

 UFString strlist;
 strlist.reserve(32768);
 
 for( lem::Container::size_type i=0; i<list.size(); i++ )
  {  
   strlist += list[i];
   strlist += L"\r\n";
  }

 HGLOBAL hglbCopy = GlobalAlloc( GMEM_MOVEABLE, (strlist.length()+1)*sizeof(wchar_t) ); 
 if( hglbCopy == NULL )   
  {
   CloseClipboard();
   return false;
  } 
 
 // Lock the handle and copy the text to the buffer. 
 wchar_t *dest = (wchar_t*)GlobalLock(hglbCopy); 
 wcscpy( dest, strlist.c_str() );
 GlobalUnlock(hglbCopy); 
 
 SetClipboardData(CF_UNICODETEXT, hglbCopy); 

 // Теперь скопируем в буфер имена файлов в формате, который понимает Explorer
 // В конце ставится 2 символа \0
 const int slen = CastSizeToInt(strlist.length() - list.size()); 
 const DWORD szBuf = ( slen + 1 )*sizeof(wchar_t) + sizeof(DROPFILES);
 hglbCopy = GlobalAlloc( GMEM_MOVEABLE, szBuf ); 
 if( hglbCopy == NULL )   
  {
   CloseClipboard();
   return false;
  }
 
 // Lock the handle and copy the text to the buffer. 
 DROPFILES *ptr = (DROPFILES*)GlobalLock(hglbCopy); 
 memset( ptr, 0, sizeof(DROPFILES) );
 ptr->fWide=TRUE;
 ptr->pFiles=sizeof(DROPFILES); 
 wchar_t *ptrFile = (wchar_t*)(((char*)ptr) + sizeof(DROPFILES));

 for( lem::Container::size_type i2=0; i2<list.size(); i2++ )
  {
   wcscpy( ptrFile, list[i2].c_str() );
   ptrFile += list[i2].length()+1;
  }   

 ptrFile[0] = L'\0';

 GlobalUnlock(hglbCopy); 
 SetClipboardData(CF_HDROP, hglbCopy); 

 return CloseClipboard()!=0;

 #elif defined LEM_WXWIDGETS

 if( !wxOpenClipboard() ) 
  return false;

 UFString strlist;
 strlist.reserve(32768);
 
 for( lem::Container::size_type i=0; i<list.size(); i++ )
  {  
   strlist += list[i];
   strlist += L"\r\n";
  }

 wxEmptyClipboard(); 
 SetClipboardData(CF_HDROP, hglbCopy); 
 wxSetClipboardData( wxCF_TEXT, new wxString(strlist.c_str()), -1, -1 )
 return wxCloseClipboard();

 #else

 return true;

 #endif
}

// Звук ошибки
void lem::Shell::ErrorBeep(void)
{
 #if defined LEM_WXWIDGETS
 wxBell();
 #elif defined LEM_WINDOWS
 MessageBeep(-1);
 #elif defined LEM_UNIX
 printf( "\b" );
 #elif defined LEM_DOS
 printf( "\b" );
 #endif

 return;
}


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



// ******************************************************************
// Вывод вопроса с вариантами ответа ДА-НЕТ. Возвращается true, если
// нажата кнопка ДА.
// ******************************************************************
bool lem::Shell::YesNo( const char *Text, const char *Title )
{
 // Перекодируем в стандартную для Win кодировку кириллицы.
 UFString uText  = to_unicode( FString(Text) );
 UFString uTitle = to_unicode( FString(Title) );
 return lem::Shell::YesNo( uText.c_str(), uTitle.c_str() );
}


bool lem::Shell::YesNo( const lem::UFString& Text, const lem::UFString& Title )
{
 return YesNo( Text.c_str(), Title.c_str() );
}


bool lem::Shell::YesNo(
                       const wchar_t *Text,
                       const wchar_t *Title
                      )
{
 #if defined LEM_CONSOLE
 if( Title!=NULL )
  mout->printf( "%us: %us (y/n)?", Title, Text );
 else
  mout->printf( "%us (y/n)?", Text );

 return mkey->ask_bool();
 #elif defined LEM_DOT_NET
  return System::Windows::Forms::MessageBox::Show(
                                                  NULL,
                                                  Text,
                                                  Title,
                                                  System::Windows::Forms::MessageBoxButtons::YesNo
                                                 ) ==
   System::Windows::Forms::DialogResult::Yes;
 #elif defined LEM_WXWIDGETS
  wxWindow *wnd = NULL;
  if( lem::WxForms::WinApp::app!=NULL )
   wnd = lem::WxForms::WinApp::app->GetFrontWindow();
  else
   wnd = wxTheApp->GetTopWindow();
   
  wxMessageDialog dlg( wnd, wxString(Text), wxString(Title), wxYES_NO | wxICON_QUESTION );
  return dlg.ShowModal()==wxID_YES;

 #elif defined LEM_QT

  QMessageBox mb;
  mb.setText( QString::fromWCharArray(Title) );
  mb.setInformativeText( QString::fromWCharArray(Text) );
  mb.setStandardButtons( QMessageBox::Yes | QMessageBox::No );
  mb.exec();


 #elif defined LEM_WINDOWS
  #if defined LEM_MFC
  HWND hWnd = AfxGetMainWnd()->m_hWnd;
  #else 
  HWND hWnd = GetForegroundWindow();
  #endif

  if( lem::System_Config::SupportUnicodeGui() )
   return MessageBoxW(
                      hWnd,
                      Text,
                      Title,
                      MB_YESNO
                     )==IDYES;
  else
   return MessageBoxA(
                      hWnd,
                      to_ascii( UFString(Text) ).c_str(),
                      to_ascii( UFString(Title ) ).c_str(),
                      MB_YESNO
                      )==IDYES;

 #else
  #error
 #endif
}


bool lem::Shell::OkCancel( const lem::UFString &Text,  const lem::UFString &Title )
{
 return OkCancel( Text.c_str(), Title.c_str() );
}


bool lem::Shell::OkCancel( const wchar_t *Text, const wchar_t *Title )
{
 #if defined LEM_CONSOLE
 if( Title!=NULL )
  mout->printf( "%us: %us?", Title, Text );
 else
  mout->printf( "%us?", Text );
 return mkey->ask_bool();
 #elif defined LEM_DOT_NET
  return System::Windows::Forms::MessageBox::Show(
                                                  NULL,
                                                  new System::String(Text),
                                                  new System::String(Title),
                                                  System::Windows::Forms::MessageBoxButtons::OKCancel
                                                 ) ==
   System::Windows::Forms::DialogResult::OK;
 #elif defined LEM_WINDOWS
  #if defined LEM_MFC
  HWND hWnd = AfxGetMainWnd()->m_hWnd;
  #else 
  HWND hWnd = GetForegroundWindow();
  #endif

  if( lem::System_Config::SupportUnicodeGui() )
   return MessageBoxW(
                      hWnd,
                      Text,
                      Title,
                      MB_OKCANCEL
                     )==IDYES;
  else
   return MessageBoxA(
                      hWnd,
                      to_ascii( UFString(Text) ).c_str(),
                      to_ascii( UFString(Title ) ).c_str(),
                      MB_OKCANCEL
                      )==IDYES;

 #elif defined LEM_WXWIDGETS
  wxWindow *wnd = NULL;
  if( lem::WxForms::WinApp::app!=NULL )
   wnd = lem::WxForms::WinApp::app->GetFrontWindow();
  else
   wnd = wxTheApp->GetTopWindow();

  wxMessageDialog dlg( wnd, wxString(Text), wxString(Title), wxCANCEL | wxOK | wxICON_QUESTION )==wxOK;
  return dlg.ShowModal()==wxID_OK;
 #endif
}

// ****************************************************************************
// Посылаем e-mail по указанному адресу, опционально можно задать тему письма
// и его тело.
// ****************************************************************************
bool lem::Shell::SendMail( const wchar_t *adr, const wchar_t *subject, const wchar_t *body )
{
 if( adr==NULL || !*adr )
  return false;

 #if defined LEM_WINDOWS
 int res=-1;
 FString asubject( lem::encode_to_url(subject) );
 FString abody( lem::encode_to_url(body) );

 asubject.re_clear();
 abody.re_clear();

 UFString str = lem::format_str( L"mailto:%us?subject=%s&body=%s", adr, asubject.c_str(), abody.c_str() );

 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   res = (int)ShellExecuteW(NULL,NULL,str.c_str(),NULL,L"",SW_SHOW);
  }
 else
  {
   res = (int)ShellExecuteA(NULL,NULL,to_ascii(str).c_str(),NULL,"",SW_SHOW);
  }
 return res>32;
 #else

 return false;

 #endif 
}


// *********************************************************
// Вызов диалога для настройки параметров интернета (в IE).
// *********************************************************
bool lem::Shell::ConfigureInternet(void)
{
 #if defined LEM_WINDOWS
 return (int)ShellExecuteA( 0, "open", "control.exe", "inetcpl.cpl", ".", SW_SHOW)>32;
 #else
 return false;
 #endif
}


#if defined LEM_WINDOWS
static int CALLBACK BrowseCallbackProc( HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData )
{
 #if defined LEM_MSC && _MSC_VER<1300
 
   // not available for VS 6.0

 #else	 

 if( uMsg == BFFM_INITIALIZED && lpData!=LPARAM(0) )
  {
   SendMessage( hWnd, BFFM_SETSELECTION, TRUE, lpData );
   SendMessage( hWnd, BFFM_SETEXPANDED, TRUE, lpData );
  }
 #endif 

 return 0;
}
#endif


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



void lem::Shell::ShowContextMenu( const lem::UFString& pszPath, int mx, int my )
{
 ShowContextMenu(pszPath.c_str(),mx,my);
}

void lem::Shell::ShowContextMenu( const wchar_t* pszPath, int mx, int my )
{
 void* hWnd = NULL;

 #if defined LEM_WXWIDGETS
 hWnd = GetForegroundWindow();
 #endif

 ShowContextMenu( hWnd, pszPath, mx, my );
 return;  
}


void lem::Shell::ShowContextMenu( const lem::FString& pszPath, int mx, int my )
{
 ShowContextMenu(pszPath.c_str(),mx,my);
}

void lem::Shell::ShowContextMenu( const char* pszPath, int mx, int my )
{
 void* hWnd = NULL;

 #if defined LEM_WXWIDGETS
 hWnd = GetForegroundWindow();
 #endif

 ShowContextMenu( hWnd, to_unicode(pszPath).c_str(), mx, my );
 return;  
}


#if defined LEM_WXWIDGETS
void lem::Shell::ShowContextMenu( const wxString& pszPath, int mx, int my )
{
 ShowContextMenu(pszPath.c_str(),mx,my);
}
#endif


#if defined LEM_WINDOWS
static HRESULT GetSHContextMenu(
                                LPSHELLFOLDER psfFolder,
                                LPCITEMIDLIST localPidl,
                                void** ppCM,
                                int* pcmType
                               )
{
 *ppCM = NULL;
 LPCONTEXTMENU pICv1 = NULL; // plain version

 // try to obtain the lowest possible IContextMenu
 HRESULT hr = psfFolder->GetUIObjectOf( NULL, 1, &localPidl, IID_IContextMenu, NULL, (void**)&pICv1 );
 if(pICv1)
  {
   // try to obtain a higher level pointer, first 3 then 2
   hr = pICv1->QueryInterface(IID_IContextMenu3, ppCM);
   if(NOERROR == hr)
    *pcmType = 3;
   else
    {
     hr = pICv1->QueryInterface(IID_IContextMenu2, ppCM);
     if(NOERROR == hr) *pcmType = 2;
    }

   if(*ppCM)
    pICv1->Release(); // free initial "v1.0" interface
   else
    {
     // no higher version supported
     *pcmType = 1;
     *ppCM = pICv1;
     hr = NOERROR; // never mind the query failures, this'll do
    }
  }

 return hr;
}

#endif


void lem::Shell::ShowContextMenu( void* hWnd, const wchar_t* pszPath, int mx, int my )
{
 LEM_CHECKIT_Z(hWnd!=NULL);
 LEM_CHECKIT_Z(pszPath!=NULL);

 #if defined LEM_WINDOWS && defined LEM_GUI

 int x;
 int y;

 if( mx==-1 && my==-1 )
  {
   POINT pt;
   ::GetCursorPos(&pt);
   x = pt.x;
   y = pt.y;
  }
 else
  {
   x = mx;
   y = my;
  }

// USES_CONVERSION;

 HRESULT hres;

 // Строим полное имя файла/каталога
 wchar_t tchFullPath[MAX_PATH];
 GetFullPathNameW(pszPath, sizeof(tchFullPath)/sizeof(wchar_t), tchFullPath, NULL);

 // Получаем интерфейс IShellFolder рабочего стола
 IShellFolder *pDesktopFolder;
 hres = SHGetDesktopFolder(&pDesktopFolder);

 if( hres!=S_OK || pDesktopFolder==NULL )
  return;

 // Получаем интерфейс IMalloc
 IMalloc *pMalloc;
 hres = SHGetMalloc(&pMalloc);

 if( hres!=S_OK || pMalloc==NULL )
  return;

 if( hWnd==NULL )
  {
   #if defined LEM_MFC
   hWnd = AfxGetMainWnd()->m_hWnd;
   #else 
   hWnd = GetForegroundWindow();
   #endif
  }

 // Преобразуем заданный путь в LPITEMIDLIST
 LPITEMIDLIST pidl;
 hres = pDesktopFolder->ParseDisplayName( (HWND)hWnd, NULL, tchFullPath, NULL, &pidl, NULL );
// HRESULT hres = pDesktopFolder->ParseDisplayName(hWnd, NULL, T2OLE( (LPCSTR)tchFullPath ), NULL, &pidl, NULL );

 if( hres==E_FAIL )
  return;

 if( pidl==NULL )
  return;

 // Ищем последний идентификатор в полученном списке pidl
 LPITEMIDLIST pLastId = pidl;
 USHORT temp;
 while(1)
  {
   int offset = pLastId->mkid.cb;
   temp = *(USHORT*)((BYTE*)pLastId + offset);

   if(temp == 0)
    break;

   pLastId = (LPITEMIDLIST)((BYTE*)pLastId + offset);
  }

  
 // Получаем интерфейс IShellFolder родительского объекта для заданного файла/каталога
 // Примечание: родительский каталог идентифицируется списком pidl за вычетом последнего
 //             элемента, поэтому мы временно зануляем pLastId->mkid.cb, отрезая его от списка
 temp = pLastId->mkid.cb;
 pLastId->mkid.cb = 0;
 IShellFolder *pFolder;
 hres = pDesktopFolder->BindToObject(pidl, NULL, IID_IShellFolder, (void**)&pFolder);

 if( hres!=S_OK || pFolder==NULL )
  {
   pMalloc->Free(pidl);
   return;
  }


 // Получаем интерфейс IContextMenu для заданного файла/каталога
 // Примечание: относительно родительского объекта заданный файл/каталог идентифицируется
 //             единственным элементом pLastId
 pLastId->mkid.cb = temp;
 IContextMenu *pContextMenu;

/*
 hres = pFolder->GetUIObjectOf(
                               (HWND)hWnd,
                               1,
                               (LPCITEMIDLIST *)&pLastId,
                               IID_IContextMenu,
                               NULL,
                               (void**)&pContextMenu
                              );
*/

// -------------------------
 #define MIN_SHELL_ID 1
 #define MAX_SHELL_ID 32767
 int cmType; // we don't need this here
 // assume that psfFolder and pidl are valid
 hres = GetSHContextMenu( pFolder, pLastId, (void**)&pContextMenu, &cmType );
// -------------------------

 if( hres!=S_OK || pContextMenu==NULL )
  return;

 // Создаём меню
 HMENU hPopupMenu = CreatePopupMenu();

// --------------------------------------------
 // fill the menu with the standard shell items
 hres = pContextMenu->QueryContextMenu( hPopupMenu, 0, MIN_SHELL_ID, MAX_SHELL_ID, 0 ); //CMF_EXPLORE );
// --------------------------------------------

 // Заполняем меню
// hres = pContextMenu->QueryContextMenu(hPopupMenu, 0, 1, 0x7FFF, 0);

 if( hres!=S_OK )
  return;

 // Отображаем меню
 UINT nCmd = TrackPopupMenu( hPopupMenu,
      TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_RETURNCMD, x, y, 0, (HWND)hWnd, 0);

 // Выполняем команду (если она была выбрана)
 if(nCmd)
  {
   CMINVOKECOMMANDINFO ici;
   ZeroMemory(&ici, sizeof(CMINVOKECOMMANDINFO));
   ici.cbSize = sizeof(CMINVOKECOMMANDINFO);

   ici.hwnd = (HWND)hWnd;
   ici.lpVerb = MAKEINTRESOURCEA(nCmd-1);
   ici.nShow = SW_SHOWNORMAL;

   pContextMenu->InvokeCommand(&ici);
  }


 // Освобождаем память, выделенную для pidl
 pMalloc->Free(pidl);

 // Освобождаем все полученные интерфейсы
 pDesktopFolder->Release();
 pFolder->Release();
 pContextMenu->Release();
 pMalloc->Release();
 #endif

 return;
}




bool lem::Shell::Execute( const UFString &Filename )
{
 return Execute( Filename.c_str() );
}


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


// *******************************************************
// Ask the user to select the filename to open or to save
// *******************************************************
lem::Path lem::Shell::AskFilename(
                                  bool for_open,
                                  const wchar_t *message,
                                  const lem::Path &folder,
                                  const wchar_t *mask
                                 )
{
 #if defined LEM_CONSOLE
 
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

  /*
 #elif defined LEM_VCL

 if( for_open )
  {
   TOpenDialog *dlg = new TOpenDialog( NULL );
   dlg->Execute();
   lem::Path res( dlg->FileName.c_str() );
   delete dlg;
   return res;
  }
 else
  {
   TSaveDialog *dlg = new TOpenDialog( NULL );
   dlg->Execute();
   lem::Path res( dlg->FileName.c_str() );
   delete dlg;
   return res;
  }
*/

 #elif defined LEM_QT

  QString fileName = QFileDialog::getSaveFileName( NULL, QString::fromWCharArray(message), QString::fromWCharArray(folder.GetUnicode().c_str()), QString::fromWCharArray(mask) );
  lem::UFString us(fileName);
  return lem::Path(us);

 #elif defined LEM_WXWIDGETS && defined LEM_GUI

  wxFileDialog *dlg = new wxFileDialog( wxTheApp->GetTopWindow(), message, L"", L"", lem_is_empty(mask) ? L"*.*" : mask, wxFD_OPEN | wxFD_FILE_MUST_EXIST );

  UFString filename;
  if( dlg->ShowModal()==wxID_OK )
   filename = dlg->GetPath().c_str();
    
  delete dlg;

  return lem::Path(filename); 

 #elif defined LEM_DOT_NET && defined LEM_GUI

 lem::Path ret;

 if( for_open )
  {
   System::Windows::Forms::OpenFileDialog *dlg_file = new System::Windows::Forms::OpenFileDialog();

   if( dlg_file->ShowDialog() == System::Windows::Forms::DialogResult::OK )
    {
     System::String *s = dlg_file->get_FileName();
     ret = lem::Path( s );
    }
  }
 else
  {
   System::Windows::Forms::SaveFileDialog *dlg_file = new System::Windows::Forms::SaveFileDialog();

   if( dlg_file->ShowDialog() == System::Windows::Forms::DialogResult::OK )
    {
     System::String *s = dlg_file->get_FileName();
     ret = lem::Path( s );
    }
  } 

 return ret;

 #elif defined LEM_WINDOWS && defined LEM_GUI

  OPENFILENAMEW filename;

  filename.lpstrFilter = mask;
  filename.Flags = 0;
  wchar_t szName[MAX_PATH];
  memset( szName, 0, sizeof(szName) );

  filename.lStructSize = sizeof( OPENFILENAMEW );

   #if defined LEM_MFC
   filename.hwndOwner = AfxGetMainWnd()->m_hWnd;
   filename.hInstance = AfxGetApp()->m_hInstance;
   #elif defined LEM_FORMS
   filename.hwndOwner = lem::Forms::WinApp::app->Get_Main_Window()->GetHandle();
   filename.hInstance = lem::Forms::WinApp::app->GetInstance()->GetHandle();
   #else 
   filename.hwndOwner = GetForegroundWindow();
//  filename.hwndOwner = NULL;      // An invalid hWnd causes non-modality
   filename.hInstance = NULL;
   #endif


  filename.lpstrCustomFilter = NULL;//custom_filter;
  filename.nMaxCustFilter = 0;//sizeof(custom_filter);
  filename.nFilterIndex = 0;
  filename.lpstrFile = szName;    // Stores the result in this variable
  filename.nMaxFile = sizeof( szName );
  filename.lpstrFileTitle = NULL;
  filename.nMaxFileTitle = 0;

  UFString initial_dir( folder.GetUnicode() );
  filename.lpstrInitialDir = initial_dir.c_str();
  filename.lpstrTitle = message;       // Title for dialog
  filename.nFileOffset = 0;
  filename.nFileExtension = 0;
  filename.lpstrDefExt = L"";
  filename.lCustData = NULL;
  filename.lpfnHook = NULL;
  filename.lpTemplateName = NULL;

  if( !for_open )
   {
    if( GetSaveFileNameW( &filename ) != TRUE )
     return lem::Path();
   }
  else
   {
    if( GetOpenFileNameW( &filename ) != TRUE )
     return lem::Path();
   }

  return lem::Path(szName);

 #else

  #error 

 #endif
}



lem::Path lem::Shell::AskFilename(
                                  bool for_open,
                                  const lem::UFString &message,
                                  const lem::Path &folder,
                                  const wchar_t *mask
                                 )
{
 return AskFilename(for_open,message.c_str(),folder,mask);
}


#if defined LEM_DOT_NET
void lem::Shell::OleDbError( System::Data::OleDb::OleDbException *exception, System::String *text )
{
 System::String *msg = S"Database operation error\n"; 
 if( text!=NULL )
  msg = System::String::Concat( msg, text, S"\n" );

 for( int i=0; i<exception->Errors->Count; i++)
  {
   msg = System::String::Concat( System::String::Concat( msg, S"Cообщение: " ), exception->Errors->get_Item(i)->Message, S"\n" );
   msg = System::String::Concat( System::String::Concat( msg, S"Источник: " ), exception->Errors->get_Item(i)->Source, S"\n" );
   msg = System::String::Concat( System::String::Concat( msg, S"SQL: " ), exception->Errors->get_Item(i)->SQLState, S"\n" );
  }

 lem::Shell::Error( to_ustr(msg) );
 return;
}
#endif



#if defined LEM_DOT_NET
void lem::Shell::Error( System::String *Text, System::String *Title )
{
 if( Title!=NULL )
  lem::Shell::Error( to_ustr(Text), to_ustr(Title) ); 
 else
  lem::Shell::Error( to_ustr(Text).c_str() ); 
}
#endif

#if defined LEM_WINDOWS
// Вызывает форму настройки параметров Проводника
void lem::Shell::ConfigMSIE(void)
{
 ShellExecuteA( 0, "open", "control.exe", "inetcpl.cpl", ".", SW_SHOW );
}
#endif


// *******************************************************************************
// Если путь указывает на файл, то открывает Проводник для папки и выделяет в ней
// этот файл, иначе - просто открывает путь в Проводнике
// *******************************************************************************
void lem::Shell::ExplorePath( const lem::Path &path )
{
 if( path.DoesExist() )
  {
   if( path.IsFolder() )
    {
     lem::Shell::Execute( path.GetUnicode() );
    }
   else
    {
     #if defined LEM_WINDOWS
     if( lem::System_Config::SupportUnicodeFilenames() )
      ShellExecuteW( NULL, NULL, L"explorer.exe", (UFString(L"/select, ") + path.GetUnicode()).c_str(),NULL,SW_SHOWNORMAL );
     else
      ShellExecuteA( NULL, NULL, "explorer.exe", (FString("/select, ") + path.GetAscii()).c_str(),NULL,SW_SHOWNORMAL );
     #else 
     lem::Path folder(path);
     folder.RemoveLastLeaf();
     lem::Shell::Execute( folder.GetUnicode() );
     #endif
    }
  }
}

void lem::Shell::Error( const std::wstring &Text )
{ lem::Shell::Error(Text.c_str()); }


void lem::Shell::Error( const std::string &Text )
{ lem::Shell::Error(Text.c_str()); }
