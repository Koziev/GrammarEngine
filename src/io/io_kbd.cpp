// -----------------------------------------------------------------------------
// File IO_KBD.CPP
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
// ������ � �������: ������������ ����.
// ����� ��� ������ � ������������ ����������� ��� ����������� ������.
//
// 01.09.2007 - ���������� ������ ���������������� � mout: ����� ����� ������
//              � �������� Enter'� �������� OFormatter::npos ����������
//              ������������, ��� ��������� � ��������� �������������� �
//              ��������� �������.
// 26.05.2008 - ������ ��� ������������� � MFC
// 28.02.2009 - ���������� ask_ufstring ��� Windows - ������ UNICODE-������
//              ����� ������ ������� WinAPI, � �� �������� ����� ascii.
// -----------------------------------------------------------------------------
//
// CD->08.02.1996
// LC->10.12.2010
// --------------

#include <lem/config.h>

#if defined LEM_MFC
 #include <afxwin.h>
#endif

#if defined LEM_WINDOWS && defined LEM_GUI
 #if defined LEM_MFC
  #include <afxwin.h>
 #else 
  #include <windows.h>
 #endif
#elif defined LEM_WINDOWS && defined LEM_CONSOLE
 #include <conio.h>
#endif

#include <lem/keyboard.h>

#if defined LEM_UNIX
 #include <curses.h>
#endif

#if defined LEM_CONSOLE && defined LEM_WIN32
  #if defined LEM_MFC
   #include <afxwin.h>
  #else 
   #include <windows.h>
  #endif
#endif

#if defined LEM_CONSOLE
 #include <iostream>

 #if defined LEM_UNIX
  #include <termios.h>
 #endif

#endif

#include <lem/io_ekeys.h>
#include <lem/streams.h>
#include <lem/user_interface.h>
#include <lem/oformatter.h>
#include <lem/conversions.h>
#include <lem/system_config.h>

using namespace std;
using namespace lem;

static int lem_getch(void);

#if defined LEM_CONSOLE && defined LEM_WIN32
  // see 'lem_coap.cpp'
//  extern HANDLE lem_hConsoleOutput;
//  extern HANDLE lem_hConsoleInput;
#endif



/*****************************************************************************

  1. This code plays a role of keyboard driver. Its principal function is to
     interact with computer hardware by use of system low-level calls and
     to hide all architecture dependent aspects. The Solaris System Kernel
     works with virtual stream which supplies the codes of pressed keys as
     these codes were retrieved from a sequentially-accessed disk file.
     Actual source of these codes depends on the operating system being used.
     Under MSDOS we use a simple console-based mechanism, and under MSWindows
     we take some advantages of GUI.

  2. Keyboard inlet stream may be redirected in order to satisfy any specific
     requirement of an operating system.

  3. It is worth mentioning that this streaming class is the one and only
     legal way for Solaris Verbal Conveyer to get data from keyboard-like
     peripheral device. Once you adjust this code there is no more need to
     look through the whole source code of Solaris.

  4. There is one more thing you are supposed to take into account when
     creating your own keyboard driver. Sometimes the Kernel creates more than
     one keyboard stream simultaneously. Sure only one of these streams
     considered as active at a moment. But you must be prepared to create
     separate window for each stream under Windows (as I do).

  5. Only two procedures are used to retrieve keyboard data: ::isready() and
     ::read_fstring(). The method ::get() can be used but is not recommended,
     as it's incompatible with MSWindows keyboard streaming approach.

  6. Under MSDOS two special keys F3 and F10 are used. F3 is used to force
     recording sound data from microphone. F10 shuts down the program.
     The way these key are processed may look intricate: ::read_fstring()
     returns the strings 'stop' and ' record!' when one of the keys is struck.
     This is the duty of Verbal Conveyer to recognize those strings and take
     appropriate measures. Note, that lexical content of the predefined
     command strings is stored in [sol_ssss.cpp] file.
*******************************************************************************/

#if defined LEM_CONSOLE || defined LEM_EASYWIN

IKbdFormatter::IKbdFormatter(void)
{ dev_cp=local_cp=866; }

IKbdFormatter::IKbdFormatter( lem::Ptr<KbdStream> s )
{
 stream=s;
 dev_cp=local_cp=866;
}

void IKbdFormatter::SetCP( int Device, int Local )
{ dev_cp=Device; local_cp=Local; }


#undef getch
int IKbdFormatter::getch(void)
{
 return stream->get();
}

/**************************************************************
 ����������� ����� ����� ��� ���������� ������ � ����������,
 �������� name - �������� ��� ������ (������� ���� �� ������).
***************************************************************/
KbdStream::KbdStream(void)
:Stream()
{
 SetMode( true, false, false );
 return;
}

KbdStream::~KbdStream(void)
{
 return;
}


void KbdStream::write( const void * /*src*/, size_t /*size*/ ) {}

lem::Stream::pos_type KbdStream::read( void * /*dest*/, size_t /*size*/ ) { return 0; }
void KbdStream::put( char /*ch*/ ) {}
bool KbdStream::eof(void) const { return false; }
lem::Stream::pos_type KbdStream::tellp(void) const { return 0; }
lem::Stream::pos_type KbdStream::seekp( lem::Stream::off_type /*pos*/, int /*whereto*/ ) { return (size_t)-1; }
bool KbdStream::move( lem::Stream::off_type /*offset*/ ) { return false; }
void KbdStream::close(void) {}
lem::Stream::pos_type KbdStream::fsize(void) const { return 0; }
void KbdStream::flush(void) {}


/********************************************************************
 ���������� ������ ������� � ����������. ���� ����� ���������� ����,
 �� ����� ����� �����.

 ������ �������� ������� �� ��, ��� ����� ����� ���������� ��������
 ����� ����� 255 - ��� �������������� ������ � ���������. ��� ��������
 ��� �������, ��� ��� ������� ����� get ���������� �������� ����������
 �����. ���������� ������������� ��������� ��� ����������� �����
 ����� ���������� � ����� [io_ekeys.h].
*********************************************************************/
int KbdStream::get(void)
{
 return lem_getch();
}

/*************************************************************************
 ���������� true, ���� � ������ ���� ������, �� ���� ���� ������
 �������.

 �������� ��� Win32 �������� ����������, � ��� ��� � ����: � ��������
 ��� �� � ������ �������. ������������� PeekConsoleInput ��� ������
 ����� ������ � ����������� �������� ������ �� ����. ������ ���:
 ������� ��� ���������� ������ ���������� (��� ����� ���� � ������
 ������ - ������� �� ���� � ������). ���� � ��� ��������� ���
 ������ � ������� ������� � �� ���������� �������, �� ������ ����
 ����. � �� ��������, ����� ���������� � ����������� ���� � �� �� �������,
 ��� ��� ��� �������� � ���.
**************************************************************************/
bool KbdStream::isready(void) const
{
/*
 #if defined LEM_WIN32 && defined LEM_CONSOLE
 DWORD counter=0;

 DWORD ie;
 GetNumberOfConsoleInputEvents(lem_hConsoleInput,&ie);

 if( ie<2 )
  return false;

 INPUT_RECORD *ir = new INPUT_RECORD[ie];
 memset( ir, 0, sizeof(INPUT_RECORD)*ie );

 if( !PeekConsoleInput( lem_hConsoleInput, ir, ie, &counter ) )
  {
   delete[] ir;
   return false;
  }

 if( ie!=counter )
  {
   delete[] ir;
   return false;
  }

 bool down, up;

 for( int i=0; i<int(ie); i++ )
  {
   const char ch = ir[i].Event.KeyEvent.uChar.AsciiChar;

   if(
      ir[i].EventType==KEY_EVENT &&
      !ir[i].Event.KeyEvent.bKeyDown &&
      isprint(ch)
     )
   {
    down = true;
    continue;
   }

   if(
      ir[i].EventType==KEY_EVENT &&
      ir[i].Event.KeyEvent.bKeyDown &&
      isprint(ch)
     )
    {
     up = true;
     continue;
    }
  }

 delete[] ir;
 return down && up;

 #else

 return kbhit();

 #endif
*/

 return false;
}

/***************************************************************************
 ���� ������ � ��������� - ����������� ��������� ��������� ��������, �
 ������� �������� ������ ������� ������ � ������������� ��.

 � ������������ MSDOS ��� WIN/EASYWIN ��� ������ �� �������� ������������
 ����� mout, ��� ��� ���������� ���������� ������ ������������
 ������� ������������� ����.
****************************************************************************/
const FString KbdStream::read_fstring(void)
{
 FString buffer;

/*
 #if 0 //defined LEM_WIN32 && defined LEM_CONSOLE

 SetConsoleMode(
                lem_hConsoleInput,
                ENABLE_LINE_INPUT |
                ENABLE_ECHO_INPUT |
                ENABLE_PROCESSED_INPUT
               );

 const char s[]="?";
 DWORD d;
 WriteConsole( lem_hConsoleOutput, s, strlen(s), &d, NULL );

 // �������� ����� ��� �������� � ���������� ��������.
 SOLACHAR *b = new SOLACHAR[256];
 b[0]=0;

 DWORD counter=0;
 while( !counter )
  ReadConsole( lem_hConsoleInput, b, 255, &counter, NULL );

 if( b[ counter-2 ] == '\r' || b[ counter-2 ] == '\n' )
  b[counter-2] = 0;
 else
  // ������� ���������, �������� ���������� C-������.
  b[counter]=0;

 buffer=b;
 delete[] b; b=NULL;

 // ���������� ������� � ���������� �����.
 SetConsoleMode( lem_hConsoleInput, ENABLE_PROCESSED_INPUT );

 #else*/

 #if defined LEM_WINDOWS && defined LEM_UNICODE_CONSOLE
 if( lem::System_Config::SupportUnicodeConsole() )
  {
   lem::UFString buffer;

   HANDLE hKbd = GetStdHandle(STD_INPUT_HANDLE);

   DWORD OldMode=0;
   GetConsoleMode( hKbd, &OldMode );
   SetConsoleMode( hKbd, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT );

   int ibuf=0;
   while(true)
    {
     BOOL rc;
     DWORD n=0;
     wchar_t c=0;
     rc = ReadConsoleW( hKbd, &c, 1, &n, NULL );
     if( c=='\r' )
      {
       rc = ReadConsoleW( hKbd, &c, 1, &n, NULL ); // \n
       LEM_CHECKIT_Z(c=='\n');
       break;
      }

     if( rc==0 || n!=1 || c=='\r' )
      break;

     buffer += c;
    }

   SetConsoleMode( hKbd, OldMode );

   return lem::to_ascii( buffer, &lem::UI::get_UI().GetTtyCp() );
  }
 #endif



 // �� ������ ������ ������� ���������� � ������.
 mout->flush();

/*
 char b[250];
 b[0] = 0;
 gets(b);

 buffer = b;
*/
 

 bool cont=true;
// bool insert=true;

 int pos=0;
 while(cont)
  {
   lem::uint16_t ch=lem_getch();

   if( ch==LEM_EKEY_ESC )
    {
     // ����� �� �����.
     mout->eol();
     mout->flush();
     return FString();
    }

   switch(ch)
    {
     case LEM_EKEY_ENTER:
      #if defined LEM_WINDOWS
      mout->printf( '\x0a' );
      #endif
      cont=false;
      break;

     case LEM_EKEY_CR:
      // ������ ������� ������.
      cont=false;
      break;

     case LEM_EKEY_ESC:
      {
       // ������ 'ESC' - ������� ����� � ������ ������ ������.
       buffer="";
       mout->eol();
       mout->flush();
       cont=false;
       break;
      }

     case LEM_EKEY_BKSP:
      {
       // '<-'. ������� ������ ����� �������� � ���������� ������ �����.

       if( pos>0 )
        {
         pos--;
         buffer.remove(pos);
         mout->cr();
         (*mout)<<buffer.c_str();
         mout->printf(' ');
         mout->cr();
         (*mout)<<buffer.c_str();
         mout->flush();
        }

       break;
      }

     default:
      buffer.insert_char(pos,(char)ch);
      mout->flush();
      pos++;
      break;
    }
  }

 mout->ResetPos(0);

 return buffer;
}

#endif // defined LEM_CONSOLE


#if defined(LEM_WINDOWS) && defined(LEM_GUI)

//#include <imb_tty.h>

/*
KbdStream::KbdStream(void)
:Stream(true,false,"")
{
 wnd = NULL;
 return;
}

KbdStream::~KbdStream(void)
{
 lem_rub_off(wnd);
 return;
}

void KbdStream::CreateWnd(void)
{
 // ������� ���� �������� ���������.

 LEM_STOPIT; // ...

 return;
}


int KbdStream::get(void)
{
 if( !(wnd) )
  CreateWnd();

 return wnd->getch();
}

bool KbdStream::isready(void) const
{
// if( IS_NIL(wnd) )
//  CreateWnd();

 return !(wnd) ? false : wnd->is_ready();
}

const FString KbdStream::read_fstring(void)
{
 if( !wnd )
  CreateWnd();

 return wnd->gets();
}
*/
#endif // defined LEM_WINDOWS && defined LEM_GUI


static const char mes0[]=
                          "Incorrect input [%s]\n"
                          "Please repeat\n";


bool IKbdFormatter::isready(void) const
{ return !stream ? false : stream->isready(); }



const FString IKbdFormatter::ask_fstring(
                                         const char* question,
                                         OFormatter &s,
                                         bool psw
                                        )
{
 FString buffer;
 bool first=true;

 while(true)
  {
   if(!first)
    s.printf( mes0, buffer.c_str() );

   s.printf( "%us", lem::to_unicode(question).c_str() );

   buffer=edline("",psw).c_str();
   if( buffer.length()>0 )
    break;

   first=false;
  }

 recode_string( buffer, dev_cp, local_cp );

 return buffer;
}


const UFString IKbdFormatter::ask_ufstring(
                                           const char* question,
                                           OFormatter &s,
                                           bool psw
                                          )
{
 #if defined LEM_WINDOWS && defined LEM_UNICODE_CONSOLE
 if( lem::System_Config::SupportUnicodeConsole() )
  {
   if( question!=NULL )
    s.printf( "%s", question );

   lem::UFString buffer;

   HANDLE hKbd = GetStdHandle(STD_INPUT_HANDLE);

   DWORD OldMode=0;
   GetConsoleMode( hKbd, &OldMode );
   SetConsoleMode( hKbd, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT );

   int ibuf=0;
   while(true)
    {
     BOOL rc;
     DWORD n=0;
     wchar_t c=0;
     rc = ReadConsoleW( hKbd, &c, 1, &n, NULL );
     if( c=='\r' )
      {
       rc = ReadConsoleW( hKbd, &c, 1, &n, NULL ); // \n
       LEM_CHECKIT_Z(c=='\n');
       break;
      }

     if( rc==0 || n!=1 || c=='\r' )
      break;

     buffer += c;
    }

   SetConsoleMode( hKbd, OldMode );

   return buffer;
  }
 #endif

 #if defined LEM_LINUX
 if( lem::System_Config::SupportUnicodeConsole() )
  {
   if( question!=NULL )
    s.printf( "%s", question );

   char buf[1000]="";
   fgets( buf, sizeof(buf)-1, stdin );
   int l = strlen(buf);
   if( l>0 && (buf[l-1]=='\n' || buf[l-1]=='\r') ) buf[l-1]=0;
   if( l>1 && (buf[l-2]=='\n' || buf[l-2]=='\r') ) buf[l-2]=0;
   return lem::from_utf8(buf);
  } 
 #endif

 return to_unicode( ask_fstring(question,s,psw), &lem::UI::get_UI().GetTtyCp() );
}


const lem::CString IKbdFormatter::ask_string(
                                             const char* question,
                                             OFormatter &s,
                                             bool psw
                                            )
{
 lem::FString buffer;

 bool first=true;

 while(true)
  {
   if(!first)
    s.printf( mes0, buffer.c_str() );

   s.printf( "%us", lem::to_unicode(question).c_str() );

   buffer=edline("",psw);
   if( buffer.length()>0 )
    break;

   first=false;
  }

 recode_string( buffer, dev_cp, local_cp );

 return buffer.c_str();
}


bool IKbdFormatter::ask_bool( const char *question, OFormatter &s )
{
 CString buffer;
 bool res=false, first=true;

 while(true)
  {
   if(!first)
    s.printf( mes0, buffer.c_str() );

   s.printf( "%us", lem::to_unicode(question).c_str() );

   if(!first)
    {
     #if defined LEM_RUSSIAN
      s.printf(
               " �������� ������: [ y,yes,on,��,���,1 / n,not,no,off,���,����,0 ] "
              );
     #else
      s.printf(
               " Acceptable answers: [ y,yes,on,1 / n,not,no,off,0 ] "
              );
     #endif
    }

   buffer=edline("").c_str();
   if( to_bool( buffer.c_str(), &res ) )
    break;

   first=false;
  }

 return res;
}

#if !defined LEM_NOREAL
// ******************************************
// *                                        *
// *   ���� ����� � ��������� ������ REAL   *
// *                                        *
// ******************************************
double IKbdFormatter::ask_real( const char *question, OFormatter &s )
{
 CString buffer;

 bool first=true;
 double res;

 while(true)
  {
   if(!first)
    s.printf( mes0, buffer.c_str() );

   s.printf( "%us", lem::to_unicode(question).c_str() );

   buffer = edline("").c_str();
   if( to_real( buffer.c_str(), &res ) )
    break;

   first=false;
  }

 return res;
}
#endif

// ******************************************
// *                                        *
// *   ���� ������ ����� �������� ���� int  *
// *                                        *
// ******************************************
int IKbdFormatter::ask_int( const char *question, OFormatter &s )
{
 FString buffer;
 bool first=true;
 int res;

 while(true)
  {
   if(!first)
    s.printf( mes0, buffer.c_str() );

   s.printf( "%us", lem::to_unicode(question).c_str() );

   buffer=edline("");
   if( to_int( buffer.c_str(), &res ) )
    break;

   first=false;
  }

 return res;
}


// *************************************************************************
// ����������� ��������� �������� �������� - ������������ ��� �����������
// ����� ����������� ����� ������ � ���������, ������ ����������� ���������
// ���������.
//
// ���� psw=true, �� �������� ������� ���������� �� ������ �������� '*'.
// ��� ������ ������������ ��� ����� �������.
// *************************************************************************
const FString IKbdFormatter::edline(
                                    const char *question,
                                    bool psw,
                                    OFormatter &s
                                   )
{
 LEM_CHECKIT_Z( stream );

/*
 int pos=0;
 s.printf( "%s", question );

 FString buffer;

 #if defined LEM_WATCOM

 bool cont=true;

 while(cont)
  {
   char ch=stream->get();

   switch(ch)
    {
     case '\r':
      // ������ ������� ������.
      cont=false;
      break;

     #if !defined LEM_BORLAND_3_1
     case 3: // Ctrl-C
       raise(SIGBREAK);
       buffer="";
       cont=false;
       break;
     #endif

     case 27:
      {
       // ������ 'ESC' - ������� ����� � ������ ������ ������.
       buffer="";
       cont=false;
       break;
      }

     case '\b':
      {
       // '<-'
       if( buffer.len() )
        {
         pos--;
         buffer.remove(pos);

         s.printf( "'\b'" );
        }

       break;
      }

     case 0:
       stream->get();
       break;

     default:
       {
        if( pos<buffer.length() )
         buffer.set(pos,ch);
        else
         buffer += ch;

        pos++;

        if( psw )
         s.printf( "*" );
        else
         s.printf( "%c", ch );

        break;
       }
    }
  }

 #elif defined LEM_SYMANTEC || defined LEM_DJGPP

  // ���� ������� �� ����������.
  LEM_CHECKIT( psw=false );

  char *b = new char[128];
  gets( b );
  buffer=b;
  delete b;

 #else

 bool cont=true;
 bool insert=true;

 int x0=wherex(), y0=wherey();

 while(cont)
  {
   int x=wherex(), y=wherey();

   char ch=stream->get();

   switch(ch)
    {
     case '\r':
      // ������ ������� ������.
      cont=false;
      s.eol();
      break;

     #if !defined LEM_BORLAND_3_1
     case 3: // Ctrl-C
       raise(SIGBREAK);
       buffer="";
       cont=false;
       break;
     #endif

     case 27:
      {
       // ������ 'ESC' - ������� ����� � ������ ������ ������.
       buffer="";
       cont=false;
       s.eol();
       break;
      }

     case '\b':
      {
       // '<-'

       if( pos>0 )
        {
         pos--;
         buffer.remove(pos);
         gotoxy(x0,y0);

         if( !psw )
          s.printf( "%s ", buffer.string() );
         else
          s.printf( "%H* ", buffer.len() );

         gotoxy(x-1,y);
        }

       break;
      }

     case 0:
      {
       ch=stream->get();

       switch(ch)
        {
         case 'K':
          if(pos>0)
           {
            pos--;
            gotoxy(x-1,y);
           }
          break;

         case 'M':
          if(pos<buffer.len())
           {
            pos++;
            gotoxy(x+1,y);
           }
          break;

         case 'R':
          #if !defined LEM_WINDOWS
          if( (insert=!insert) )
           _setcursortype(_NORMALCURSOR);
          else
           _setcursortype(_SOLIDCURSOR);
          break;
          #endif

         case 'S':
          buffer.remove(pos);
          gotoxy(x0,y0);

          if( !psw )
           s.printf( "%s ", buffer.string() );
          else
           s.printf( "%H* ", buffer.len() );

          gotoxy(x,y);
          break;
        }

       break;
      }

     default:
      if( insert )
       {
        // ����� ������� ��������
        if( pos<buffer.len() )
         buffer.set(pos,ch);
        else
         buffer += ch;

        gotoxy(x0,y0);

         if( !psw )
          s.printf( "%s ", buffer.string() );
         else
          s.printf( "%H* ", buffer.len() );

        gotoxy(x+1,y);
        pos++;
       }
      else
       {
        // ����� 'overwrite'
        if( pos<buffer.len() )
         buffer.set(pos,ch);
        else
         buffer += ch;

        gotoxy(x0,y0);

         if( !psw )
          s.printf( "%s ", buffer.string() );
         else
          s.printf( "%H* ", buffer.len() );

        gotoxy(x,y);
       }
    }
  }
 #endif

 return buffer;
*/

 return stream->read_fstring();
}


void IKbdFormatter::wait(void)
{
 stream->wait_ready();
 return;
}



#if defined LEM_CONSOLE && defined LEM_UNIX
static struct termios stored_settings;
     
static void set_keypress(void)
{
 struct termios new_settings;
     
 tcgetattr(0,&stored_settings);
     
 new_settings = stored_settings;
     
 /* Disable canonical mode, and set buffer size to 1 byte */
 new_settings.c_lflag &= (~ICANON);
 new_settings.c_cc[VTIME] = 0;
 new_settings.c_cc[VMIN] = 1;
     
 tcsetattr(0,TCSANOW,&new_settings);
 return;
}
     
static void reset_keypress(void)
{
 tcsetattr(0,TCSANOW,&stored_settings);
 return;
}
#endif


 // ************************************************************************
 // ��������� ���������� ���������� � ���� ���� ������ ����������� �������,
 // �� ��� ��������� �� ������ ������� ��� ������� � ���������� ������
 // 16-������ ���.
 //
 // ���� ������ ������� ������� (������� ��������� ����������� ���� ENTER),
 // �� ������������ �������� ����� ������ � ��������� 0x0000-0x00ff. ���
 // ����������� ��������� � �������������� ������ ������������ �������� ��
 // ��������� 0x0100...0xff00. ������ ��������� � ����� [io_ekeys.h] - ����
 // ����������� ���������.
 // *************************************************************************
 static int lem_getch(void)
 {
  #if defined LEM_WINDOWS && defined LEM_GUI

   MSG msg;
   HWND hwnd=GetFocus();

   // ���������� ������� ���� �� ��������� ��������� � �������.
    do
     {
      GetMessage( &msg, hwnd, 0, 0x7FFF );
     }
    while (msg.message != WM_KEYDOWN);

   return msg.wParam;

/*
  #elif defined LEM_WIN32 && defined LEM_CONSOLE

   char b[1]={ '\0' };
   DWORD counter=0;

   // ����, ���� �� ����� ������ �������.
   while(!counter)
    ReadConsole( lem_hConsoleInput, b, 1, &counter, NULL );

   return b[0];
*/
  #elif defined LEM_UNIX && defined LEM_CONSOLE

   set_keypress();

   if( lem::System_Config::SupportUnicodeConsole() )
    {
     const unsigned int ch0 = getchar();
  
     unsigned int ch1 = 0;
     if( ch0==0 )
      ch1 = (getchar()<<8);

     const char res_ch = ch1 | ch0;
   
     if( res_ch=='\n' )
      printf( "\r\n" ); 
  
      reset_keypress();
     return res_ch;
    }
   else
    {
    set_keypress();

     const unsigned int ch0 = getch();
  
     unsigned int ch1 = 0;
     if( ch0==0 )
      ch1 = (getch()<<8);
     else
      {
       mout->printf(ch0);
      }           

     const char res_ch = ch1 | ch0;
   
     if( res_ch=='\n' )
      printf( "\r\n" ); 

     reset_keypress();
     return res_ch;
    }          
  
  #elif defined LEM_WINDOWS && defined LEM_CONSOLE

   #if defined LEM_BORLAND
   const unsigned int ch0 = getche();
   unsigned int ch1 = 0;
   if( ch0==0 )
    ch1 = (getche()<<8);
   #else
   const unsigned int ch0 = _getche();
   unsigned int ch1 = 0;
   if( ch0==0 )
    ch1 = (_getche()<<8);
   #endif

   return ch1 | ch0;

  #elif /*defined LEM_WINDOWS &&*/ defined LEM_CONSOLE

   const unsigned int ch0 = cin.get();
   unsigned int ch1 = 0;
   if( ch0==0 )
    ch1 = (cin.get()<<8);

   return ch1 | ch0;

  #elif defined LEM_GNUC && defined LEM_DOS

   const unsigned int ch0 = getch();
   unsigned int ch1 = 0;
   if( ch0==0 )
    ch1 = (getch()<<8);

   return ch1 | ch0;

  #else

   const unsigned int ch0 = getch();
   unsigned int ch1 = 0;
   if( ch0==0 )
    ch1 = (getch()<<8);

   return ch1 | ch0;

  #endif
 }
