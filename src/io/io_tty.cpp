// -----------------------------------------------------------------------------
// File IO_TTY.CPP
//
// (c) by Elijah Koziev     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                https://github.com/Koziev/GrammarEngine
//
// Content:
// Реализация TtyStream - потока для вывода символов на терминал (или в окно
// эмуляции терминала для графических сред).
//
// 27.04.2007 - TtyUcs4Stream and TtyUtf8Stream are implemented for Windows and
//              Linux UNICODE console.
//
// 25.05.2007 - Utf8 tty stream bug fixed under linux UTF-8 console
// -----------------------------------------------------------------------------
//
// CD->20.06.1998
// LC->01.04.2018
// --------------

#include <lem/config.h>

#include <stdio.h>

#if defined LEM_DOS
#include <conio.h>
#elif defined LEM_UNIX
#if LEM_USES_NCURSES==1
#include <curses.h>
#endif
#endif

#include <lem/unicode.h>
#include <lem/console_application.h>
#include <lem/streams.h>

#if defined LEM_WINDOWS
#define WIN_CUI
#include <windows.h>
static HANDLE hOut = 0;
#endif


using namespace lem;


#if defined LEM_UNIX
// Make NCURSES initialization once.
static volatile int inited_ncurses = 0;
#endif

TtyStreamStd::TtyStreamStd(void)
    :Stream(false, true)
{
    SetMode(false, true, false);

    binary = false;

    return;
}

TtyStreamStd::~TtyStreamStd(void)
{}

void TtyStreamStd::close(void)
{
    return;
}

void TtyStreamStd::write(const void *src, pos_type size)
{
    for (pos_type i = 0; i < size; i++)
        put(((const char*)src)[i]);

    return;
}

void TtyStreamStd::put(char ch)
{
    putchar(0x00ff & ch);
    return;
}

void TtyStreamStd::puts(const char *s)
{
    ::puts(s);
    return;
}

int TtyStreamStd::get(void)
{
    return 0;
}

bool TtyStreamStd::eof(void) const
{
    return false;
}


lem::Stream::pos_type TtyStreamStd::seekp(off_type /*pos*/, int /*whereto*/)
{
    return 0;
}

lem::Stream::pos_type TtyStreamStd::tellp(void) const
{
    LEM_STOPIT;
#if !defined LEM_BORLAND
    return pos_type();
#endif
}


bool TtyStreamStd::move(lem::Stream::off_type /*offset*/)
{
    return false;
}

lem::Stream::pos_type TtyStreamStd::fsize(void) const
{
    return 0;
}


void TtyStreamStd::flush(void)
{
    fflush(stdout);
    return;
}

void TtyStreamStd::SetForeGroundColor(int iColor)
{}

void TtyStreamStd::SetBackGroundColor(int iColor)
{}


void TtyStreamStd::SetBlinkMode(bool blinks)
{}

void TtyStreamStd::SetHighLightMode(void)
{}

void TtyStreamStd::SetLowLightMode(void)
{}

void TtyStreamStd::SetNormalMode(void)
{}

lem::Stream::pos_type TtyStreamStd::read(void * /*dest*/, size_t /*size*/)
{
    LEM_STOPIT;
#if !defined LEM_BORLAND
    return pos_type();
#endif
}

// ##############################################################


/***************************************************************************
 Работа с терминалом стандартными UNIX-подобными средствами не составляет
 труда и интереса. Обращаю внимание лишь на способ, которым мы манипулируем
 цветовыми характеристиками выводимых символов (с помощью стандартной
 библиотеки NCURSES). Для управления цветом консоли Windows используются
 также стандартные функции WinAPI).
****************************************************************************/

TtyStream::TtyStream(void)
    :Stream(false, true)
{
    SetMode(false, true, false);

    binary = false;

#if defined LEM_UNIX && LEM_USES_NCURSES==1
    // ************************************************
    // Инициализация библиотеки NCURSES для LINUX
    // ************************************************
    if (!inited_ncurses)
    {
        initscr();
        start_color();
        cbreak();
        //   nonl();
        //   intrflush(stdscr,FALSE);

        noecho();
        scrollok(stdscr, TRUE);

        init_pair(1, COLOR_BLACK, COLOR_WHITE);
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        init_pair(5, COLOR_RED, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_YELLOW, COLOR_BLACK);
        init_pair(8, COLOR_WHITE, COLOR_BLACK);

        refresh();
    }

    inited_ncurses++;
#endif

#if defined WIN_CUI
    if (!hOut)
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    fg = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    bg = 0;

#endif

    return;
}



int TtyStream::get(void)
{
    return 0;
}

bool TtyStream::eof(void) const
{
    return false;
}

Stream::pos_type TtyStream::tellp(void) const
{
    LEM_STOPIT;
#if !defined LEM_BORLAND
    return pos_type();
#endif
}

Stream::pos_type TtyStream::seekp(lem::Stream::off_type /*pos*/, int /*whereto*/)
{
    return 0;
}

bool TtyStream::move(Stream::off_type /*offset*/)
{
    return false;
}

Stream::pos_type TtyStream::fsize(void) const
{
    return 0;
}



Stream::pos_type TtyStream::read(void * /*dest*/, size_t /*size*/)
{
    LEM_STOPIT;
#if !defined LEM_BORLAND
    return pos_type();
#endif
}




TtyStream::~TtyStream(void)
{
#if defined LEM_UNIX && LEM_USES_NCURSES==1
    if (!--inited_ncurses)
    {
        // NCURSES should be closed
        endwin();
    }
#endif

    /* ... nothing to do ... */
    return;
}

void TtyStream::close(void)
{
    return;
}



void TtyStream::write(const void *src, pos_type size)
{
    for (pos_type i = 0; i < size; i++)
        put(((const char*)src)[i]);

    return;
}

void TtyStream::put(char ch)
{
#if defined WIN_CUI

    char buf[1] = { ch };
    DWORD dummy;

    SetConsoleTextAttribute(hOut, fg | bg);   // set the current colors
    WriteConsoleA(hOut, buf, 1, &dummy, NULL); // put the char

#elif defined LEM_WIN32 && defined LEM_CONSOLE

    printf("%c", ch);

#elif defined LEM_UNIX && LEM_USES_NCURSES==1

    // UNIX (including LINUX) does not require 0x0d character in eol's.
 //   putchar(ch);

    addch(0x00ffU & lem::uint16_t(ch));

    if (ch == '\n')
    {
        refresh();
    }

#else

    printf("%c", ch);
    if (ch == '\n')
        printf("\r");

#endif

    return;
}

void TtyStream::puts(const char *s)
{
#if defined WIN_CUI

    DWORD dummy;
    SetConsoleTextAttribute(hOut, fg | bg);
    WriteConsoleA(hOut, s, lem_strlen(s), &dummy, NULL);

#elif defined LEM_WIN32 && defined LEM_CONSOLE

    int i = 0;
    while (s[i])
        put(s[i++]);

#else

    int i = 0;
    while (s[i])
        put(s[i++]);

#endif

    return;
}








// *********************************************************
// Все символы, застрявшие в буфере вывода, принудительно
// отрисовываются на экране.
// *********************************************************
void TtyStream::flush(void)
{
#if defined WIN_CUI
    // nothing to do
#elif defined LEM_WIN32 && defined LEM_CONSOLE
    // nothing to do
#elif defined LEM_UNIX && defined LEM_CONSOLE && LEM_USES_NCURSES==1
    refresh();
#else
    fflush(stdout);
#endif

    return;
}


/********************************************************
 Индексом задается цвет символов для последующего вывода.
*********************************************************/
void TtyStream::SetForeGroundColor(int iColor)
{
#if defined WIN_CUI

    switch (iColor)
    {
    case 0: fg = 0;                                   break;
    case 1: fg = FOREGROUND_BLUE;                     break;
    case 2: fg = FOREGROUND_GREEN;                    break;
    case 3: fg = FOREGROUND_BLUE | FOREGROUND_GREEN; break;   // CYAN
    case 4: fg = FOREGROUND_RED;                      break;
    case 5: fg = FOREGROUND_RED | FOREGROUND_BLUE;  break;   // MAGENTA
    case 6: fg = FOREGROUND_RED | FOREGROUND_GREEN; break;   // BROWN

    case 7:
        fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
            FOREGROUND_INTENSITY; // LIGHTGRAY
        break;

    case 8:
        fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // DARKWHITE
        break;

    case 9:
        fg = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;

    case 10:
        fg = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;

    case 11:
        fg = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;

    case 12:
        fg = FOREGROUND_RED | FOREGROUND_INTENSITY;
        break;

    case 13:
        fg = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;

    case 14:
        fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;

    case 15:
        fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
            FOREGROUND_INTENSITY; // WHITE
        break;
    }

#elif defined(LEM_BORLAND_3_1) && defined(LEM_DOS)

    textcolor(iColor);

#elif defined LEM_UNIX && LEM_USES_NCURSES==1

    switch (iColor)
    {
    case 0:  attrset(COLOR_PAIR(1)); break;
    case 1:  attrset(COLOR_PAIR(2)); break;
    case 2:  attrset(COLOR_PAIR(3)); break;
    case 3:  attrset(COLOR_PAIR(4)); break;
    case 4:  attrset(COLOR_PAIR(5)); break;
    case 5:  attrset(COLOR_PAIR(6)); break;
    case 6:  attrset(COLOR_PAIR(7)); break;
    case 7:  attrset(COLOR_PAIR(8)); break;
    case 8:  attrset(0); break;
    case 9:  attrset(COLOR_PAIR(2) | A_BOLD); break;
    case 10: attrset(COLOR_PAIR(3) | A_BOLD); break;
    case 11: attrset(COLOR_PAIR(4) | A_BOLD); break;
    case 12: attrset(COLOR_PAIR(5) | A_BOLD); break;
    case 13: attrset(COLOR_PAIR(6) | A_BOLD); break;
    case 14: attrset(COLOR_PAIR(7) | A_BOLD); break;
    case 15: attrset(COLOR_PAIR(8) | A_BOLD); break;
    }

#endif
    return;
}

/****************************************************************
 При выводе на терминал - установка текущего цвета фона символов.
 Цвет задается индексом.
*****************************************************************/
void TtyStream::SetBackGroundColor(int iColor)
{
#if defined(LEM_BORLAND_3_1) && defined(LEM_DOS)
    textbackground(iColor);
#endif
    return;
}


// ***********************************************************************
// Режим мерцания символов - был доступен для MSDOS. Особой пользы от него
// нет, но оставил метод для поддержки совместимости старых программ.
// ***********************************************************************
void TtyStream::SetBlinkMode(bool blinks)
{
#if defined(LEM_BORLAND_3_1) && defined(LEM_DOS)
    text_info ti;
    gettextinfo(&ti);
    int atr = ti.attribute;
    atr ^= BLINK;
    textattr(atr);
#endif

    return;
}

// ***********************************************************************
// Установка режима вывода символов с повышенной яркостью (белые).
// ***********************************************************************
void TtyStream::SetHighLightMode(void)
{
#if defined WIN_CUI
    fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    bg = 0;
#elif defined(LEM_BORLAND_3_1) && defined(LEM_DOS)
    highvideo();
#endif
    return;
}


// ***********************************************************************
// Установка режима вывода символов с пониженной яркостью (темно-серые).
// ***********************************************************************
void TtyStream::SetLowLightMode(void)
{
#if defined WIN_CUI
    fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    bg = 0;
#elif defined(LEM_BORLAND_3_1) && defined(LEM_DOS)
    lowvideo();
#endif

    return;
}


// *********************************************************************
// Установка режима вывода символов обычного цвета (серебристо-серые).
// *********************************************************************
void TtyStream::SetNormalMode(void)
{
#if defined WIN_CUI
    fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    bg = 0;
    // –ўҐв  д®­  Ё бЁ¬ў®«®ў Ї® г¬®«з ­Ёо.
#elif defined(LEM_BORLAND_3_1) && defined(LEM_DOS)
    // normvideo();
    lowvideo();

#elif defined LEM_UNIX && LEM_USES_NCURSES==1

    attrset(0);

#endif
    return;
}







#if defined LEM_UNICODE_CONSOLE

#if defined LEM_WINDOWS 
TtyUcs2Stream::TtyUcs2Stream(void) : TtyStream()
{}


int TtyUcs2Stream::Bits_Per_Char(void) const
{
    return 16;
}


void TtyUcs2Stream::wput(wchar_t ch)
{
#if defined WIN_CUI

    wchar_t buf[1] = { ch };
    DWORD dummy;

    BOOL res = SetConsoleTextAttribute(hOut, fg | bg);   // set the current colors
    LEM_CHECKIT_Z(res != 0);
    res = WriteConsoleW(hOut, buf, 1, &dummy, NULL); // put the char
    LEM_CHECKIT_Z(res != 0);

#else
    LEM_STOPIT;
#endif
}
#endif

#if defined LEM_LINUX || defined LEM_DARWIN

TtyUtf8Stream::TtyUtf8Stream(void) : TtyStreamStd()
{}


void TtyUtf8Stream::put(char ch)
{
    putchar(ch);

    if (ch == '\n')
    {
        putchar('\r');
    }

    return;
}


void TtyUtf8Stream::wput(wchar_t ch)
{
    if (!(0xffffff00 & ch))
        putchar(ch);
    else
    {
        uint8_t utf8[8];
        const int n8 = lem::UCS4_to_UTF8(ch, utf8);
        for (int i = 0; i < n8; i++)
            putchar(utf8[i + 1]);
    }

    if (ch == L'\n')
    {
        putchar('\r');
        //   refresh();
    }
}
#endif

#endif



StdTtyStream::StdTtyStream(void)
{
    stream = NULL;
}

StdTtyStream::StdTtyStream(ostream *s)
    :Stream(false, true)
{
    stream = s;
}

void StdTtyStream::write(const void *src, pos_type size)
{
    stream->write((const char*)src, size);
}

void StdTtyStream::put(char Ch)
{
    stream->put(Ch);
#if LEM_DEBUGGING==1
    Assert();
#endif
}

lem::Stream::pos_type StdTtyStream::read(void * /*dest*/, pos_type /*size*/)
{
    return 0;
}

int StdTtyStream::get(void)
{
    return -1;
}

void StdTtyStream::Check(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif
}

void StdTtyStream::flush(void)
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    stream->flush();
}

void StdTtyStream::close(void)
{
#if LEM_DEBUGGING==1
    Assert();
#endif
}

bool StdTtyStream::eof(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    return false;
}

lem::Stream::pos_type StdTtyStream::tellp(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    return 0;
}

StdTtyStream::pos_type StdTtyStream::seekp(lem::Stream::off_type /*to*/, int /*whereto*/)
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    return (size_t)-1;
}

bool StdTtyStream::move(off_type /*offset*/)
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    return false;
}

lem::Stream::pos_type StdTtyStream::fsize(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    return 0;
}
