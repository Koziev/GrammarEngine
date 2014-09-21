// -----------------------------------------------------------------------------
// File LEM_CHEC.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// LEM C++ library  http://www.solarix.ru
// Проверки указателей и т.д. Все эти проверки отключаются препроцессорно, так
// что релиз-версия программы будет свободна от накладных расходов по проверке.
//
// 08.02.2007 - добавлено форматирование текста системных сообщений об ошибках,
//              введены макросы LEM_WCHECKIT и LEM_WCHECKIT_Z
// -----------------------------------------------------------------------------
//
// CD->06.01.1996
// LC->09.10.2010
// --------------

#include <lem/config.h>
#include <lem/path.h>
#include <lem/fstring.h>
#include <lem/shell.h>

#if defined LEM_WINDOWS && defined LEM_GUI && !defined LEM_DOT_NET && !defined LEM_MFC
 #include <windows.h>
#endif

#if defined LEM_BORLAND && defined LEM_DOS
 #include <conio.h>
#endif

#if defined LEM_WATCOM && defined LEM_DOS
 #include <conio.h>
#endif

#if defined LEM_UNIX
// #include <curses.h>
 #include <ncurses.h>
#endif

#if defined LEM_DOT_NET
 #using <system.dll>
 #using <System.Windows.Forms.DLL>
#endif

#if defined LEM_WINDOWS
#include <process.h>
#endif

#include <string>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include <lem/conversions.h>
#include <lem/unicode.h>

#if defined LEM_GUI

#include <lem/fstring.h>
#include <lem/system_config.h>
#include <lem/runtime_checks.h>


#if defined LEM_DOT_NET
 #undef MessageBox
#endif

#endif

using namespace std;
using namespace lem;

// *****************************************************************
// Спрашиваем пользователя, надо ли прерывать исполнение программы.
// *****************************************************************
void lem_ask_abort(void)
{
 #if defined LEM_RUSSIAN
  const char m[]="Продолжить исполнение программы?";
  const char t[]="Программная ошибка";
 #else
  const char m[]="Continue program execution?";
  const char t[]="Software failure";
 #endif

 #if defined LEM_GUI
  if( !lem::Shell::YesNo( m, t ) )
   exit(1);
 #else

  #if defined LEM_UNIX
  endwin();
  #endif

  printf( "%s: %s", t, m );

  #if defined LEM_DOS

  char s[10];
  fgets( s, 8, stdin );
  if( !strcmpi( s, "y" ) )
   exit(1);
  #endif

 #endif
}

char LEM_ASSERT_MSG1[]="\nLEM: Assertion failed\nCondition: %s\nfile %s, line %d\n";

char LEM_ASSERT_MSG2[]="\nLEM: Unconditional program termination\n%s\n"
                                       "file %s, line %d\n";

char LEM_ASSERT_MSG3[]="\nLEM: Unconditional program termination\n%s\n"
                                       "file %s, line %d\n";

char LEM_ASSERT_MSG4[]="\nLEM: Unconditional program termination\n%s\n%s\n"
                                       "file %s, line %d\n";

char LEM_ASSERT_MSG5[]="\nLEM: Assertion failed\n%s\nCondition: %s\nfile %s, line %d\n";
char LEM_ASSERT_MSG6[]="\nLEM: Assertion failed\n%s\n%s\nCondition: %s\nfile %s, line %d\n";

char LEM_ASSERT_MSG8[]="\nLEM: Check point %s\nfile %s, line %d\n";
char LEM_ASSERT_MSG9[]="\nLEM: Check point\n%s\nfile %s, line %d\n";
char LEM_ASSERT_MSG10[]="\nLEM: Check point\n%s\n%s\nfile %s, line %d\n";


char LEM_ASSERT_MSG7[]="";


std::string lem::GetErrorString(void)
{
 #if defined LEM_WINDOWS
 DWORD dw = GetLastError(); 
 if( ERROR_SUCCESS==dw )
  return std::string();

 LPVOID lpMsgBuf=NULL;
 std::string res;
 if(
    !FormatMessageA(
                   FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                   FORMAT_MESSAGE_FROM_SYSTEM,
                   NULL,
                   dw,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   (LPSTR) &lpMsgBuf,
                   0,
                   NULL
                  )
   )
  {
   LocalFree(lpMsgBuf);
   lpMsgBuf=NULL;

   char buf[60];
   *buf=0;

   sprintf( buf, "error code=0x%x", int(dw) );
   return std::string(buf);
  }

 if( lpMsgBuf!=NULL )
  {
   res = (const char*)lpMsgBuf;
   LocalFree(lpMsgBuf);
  }

 return res;

 #elif defined LEM_WXWIDGETS

  wchar_t buf[512];
  *buf=0;

  const unsigned long errcode = wxSysErrorCode();
  sprintf( buf, DIM_A(buf), L"%ls\n", wxSysErrorMsg(errcode) );
  return std::string(buf);
 
 #elif defined LEM_DARWIN

  int e = errno;
  char buf[64];
  sprintf( buf, "error 0x%x\n", errno );
  return std::string(buf);

 #else

  std::string res;

  int e = errno;

  if( e!=0 )
   res = _sys_errlist[e];

  return res;

 #endif
}




void lem::check_failed(
                       const char *mes,
                       const char *cond,
                       const char *filename,
                       int line
                      )
{
 #if defined LEM_WINDOWS
 DWORD dw = GetLastError(); 

 LPVOID lpMsgBuf=NULL;
 if(
    !FormatMessageW(
                   FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                   FORMAT_MESSAGE_FROM_SYSTEM,
                   NULL,
                   dw,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   (LPWSTR) &lpMsgBuf,
                   0,
                   NULL
                  )
   )
  {
   LocalFree(lpMsgBuf);
   lpMsgBuf=NULL;
  }


 lem::UFString buf = lem::UFString(L"LEM: Assertion failed. Condition: ")+
                     lem::UFString(cond) +
                     lem::UFString(L"file: ")+
                     lem::to_unicode(filename)+
                     lem::UFString(L" line: ")+
                     lem::UFString(lem::to_ustr(line).c_str())+
                     lem::UFString(L"\nErrcode=")+
                     lem::UFString(lem::to_ustr((int)dw).c_str())+
                     lem::UFString(L" text=")+
                     lem::UFString((const wchar_t*)lpMsgBuf);
                     
 LocalFree(lpMsgBuf);

 lem::Shell::Error( buf );
 throw lem::E_BaseException(buf);

 #elif defined LEM_WXWIDGETS

  wchar_t buf[512];
  *buf=0;

  const unsigned long errcode = wxSysErrorCode();
  swprintf(
           buf, DIM_A(buf),
           L"LEM: Assertion failed. Condition: %s file: %s line: %d\n"
           L"Errcode=%X text=%ls\n",
           cond, filename, line, errcode, wxSysErrorMsg(errcode) );

  lem::Shell::Error( buf );
  throw lem::ECheckFault( buf );

 #else

 char buf[256];
 sprintf( buf, mes, cond, filename, line );
 lem::Shell::Error( buf );
 throw lem::ECheckFault( to_wstr(buf) );
 #endif
}



void lem::check_failed_a(
                         const char *mes,
                         const char *mes1,
                         const char *cond,
                         const char *filename,
                         int line
                        )
{
 char buf[256];
 sprintf( buf, mes, mes1, cond, filename, line );
 lem::Shell::Error( buf );
 throw lem::ECheckFault( to_wstr(buf) );
}

void lem::check_failed_a2(
                          const char *mes,
                          const char *mes1,
                          const char *mes2,
                          const char *cond,
                          const char *filename,
                          const int line
                         )
{
 char buf[256];
 sprintf( buf, mes, mes1, mes2, cond, filename, line );
 lem::Shell::Error( buf );
 throw lem::ECheckFault( to_wstr(buf) );
}

/*************************************************************************
 После операции выделения динамической памяти имеет смысл проверять
 указатель. Данная процедура вызывается, если указатель, поданный в
 качестве аргумента макроса check_ptr, равен NULL, то есть выделение
 памяти не прошло, программу следует прерывать с выдачей диагностики.
 Мы ограничиваемся генерацией исключения, которое должен перехватить
 внешний модуль.
**************************************************************************/
void lem::mem_failed(void)
{
 lem::Shell::Error( L"LEM: Not enough memory" );

 // Memory allocation fault
 throw lem::EMemFault(L"Memory error");
}

/****************************************************************************
  Проверяем корректность файловых операций.

  Во-первых, проверяем успешность открытия файла. Если file==NULL,
  то операция открытия не прошла, и следует выдать диагностику.

  Во-вторых, при возникновении проблем с прочими файловыми операциями
  проверяем состояние флага ошибок.

  Так как проверки каждой файловой операции обходятся достаточно
  дорого, имеет смысл выключать вызов процедурки макропроцессором
  по тексту программы в зависимости от макроса LEM_DEBUGGING.
*****************************************************************************/
void lem::check_file( const FILE *file, const char *filename )
{
 // Файл открыт успешно ?
 if( file==NULL )
  {
   char buf[256];
   sprintf(
           buf,
           "LEM: there has been a problem opening a file [%s]\n",
           filename==NULL ? "(null)" : filename
          );

   #if defined LEM_GUI
//    show_alert( buf, cp866 );
   #else
    #if defined LEM_UNIX
     endwin();
    #endif

//    fprintf( stderr, "\n" );
//    fprintf( stderr, buf );
   #endif

   throw lem::EFileOpenFault( to_wstr(buf) );
  }

 // Файловая операция прошла успешно ?
 #if defined LEM_DEBUGON
  if( file && ferror((FILE*)file) )
   {
    const char *buffer = "";//strerror(errno);

    char buf[256];
    sprintf(
            buf,
            "LEM: File I/O error: %s for [%s]\n",
            buffer,
            filename==NULL ? "?" : filename
           );

//    lem::show_alert( buf, cp866 );

    throw lem::EFileOpenFault( to_wstr(buf) );
   }
 #endif

 return;
}


void lem::check_file( const FILE *file, const wchar_t *filename )
{
 char *a_filename = lem_unicode_to_ascii(filename);
 check_file(file,a_filename);
 delete a_filename;
 return;
}


void lem::check_file( const FILE *file, const lem::Path& filename )
{
 check_file( file, filename.GetAscii().c_str() );
}




E_BaseException::E_BaseException(void)
{
 text=new wchar_t[1];
 *text=0;
 return;
}

E_BaseException::E_BaseException( const wchar_t *t )
{
 LEM_CHECKIT_Z( t!=NULL );
 text = new wchar_t[ wcslen(t)+1 ];
 wcscpy( text, t );
 return;
}

E_BaseException::E_BaseException( const char *t )
{
 LEM_CHECKIT_Z( t!=NULL );
 const int l = strlen(t);
 text = new wchar_t[ l+1 ];

 for( int i=0; i<l; ++i )
  text[i] = t[i];
 
 return;
}

E_BaseException::E_BaseException( const lem::FString & t )
{
 const int l = t.length();
 text = new wchar_t[ l+1 ];

 for( int i=0; i<l; ++i )
  text[i] = t[i];
 
 return;
}



E_BaseException::E_BaseException( const E_BaseException& x )
{
 text = new wchar_t[ wcslen(x.text)+1 ];
 wcscpy( text, x.text );
 return;
}

E_BaseException::E_BaseException( const std::wstring &Message )
{
 text = new wchar_t[ Message.length()+1 ];
 wcscpy( text, Message.c_str() );
 return;
}

E_BaseException::E_BaseException( const lem::UFString &Message )
{
 text = new wchar_t[ Message.length()+1 ];
 wcscpy( text, Message.c_str() );
 return;
}

E_BaseException::~E_BaseException(void)
{ delete[] text; text=NULL; }


void E_BaseException::operator=( const E_BaseException& x )
{
 if( &x == this )
  return;

 delete[] text; 
 text = new wchar_t[ wcslen(x.text)+1 ];
 wcscpy( text, x.text );
 return;
}
