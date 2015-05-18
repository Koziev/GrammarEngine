/*
**  IXE C++ Library
**  ixe/include/char.h: char type
**  ----------------------------------------------------------------------
**  Copyright (c) 2000  Ideare SpA.
**  Copyright (c) 2000  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of DeSR.
**
**  DeSR is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  DeSR is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#ifndef IXE_include_char_H
#define IXE_include_char_H

namespace IXE {

// ----------------------------------------------------------------------
// Character type

#ifdef _WIN32
// FIXME: UNICODE is defined, but it stil premature for IXE to use it
typedef char char_t;
#else
#ifdef UNICODE
#include <wchar.h>
#include <wctype.h>
typedef wchar_t char_t;
#define STRLEN(x)     wcslen(x)
#define STRCMP(x, y)  wcscmp(x, y)
#define STRCPY(x, y)  wcscpy(x, y)
#define STRNCPY(x,y,z) wcsncpy(x, y, z)
#define STRCOLL(x, y) wcscoll(x, y)
#define STRNCMP(x,y,z) wcsncmp(x, y, z)
#define STRLITERAL(x) (wchar_t*)L##x
#define PRINTF        wprintf
#define FPRINTF       fwprintf
#define SPRINTF       swprintf
#define VFPRINTF      vfwprintf
#define FSCANF        fwscanf
#define SSCANF        swscanf
#define GETC(x)       getwc(x)
#define UNGETC(x, y)  ungetwc(x, y)
#define TOLOWER(x)    towlower((x) & 0xFFFF)
#define TOUPPER(x)    towlower((x) & 0xFFFF)
#define ISALNUM(x)    iswalnum((x) & 0xFFFF)
#define STRSTR(x, y)  wcsstr(x, y)
#define STRXFRM(x,y,z) wcsxfrm(x, y, z)
#define STRFTIME(a,b,c,d) wcsftime(a,b,c,d)
#define T_EOF         WEOF
# ifndef _T
# define _T(x) L##x
# endif
#else  // ! UNICODE
typedef char char_t;
#define STRLEN(x)     strlen(x)
#define STRCMP(x, y)  strcmp(x, y)
#define STRCPY(x, y)  strcpy(x, y)
#define STRNCPY(x,y,z) strncpy(x, y, z)
#define STRCOLL(x, y) strcoll(x, y)
#define STRNCMP(x,y,z) strncmp(x, y, z)
#define STRLITERAL(x) (char*)x
#define PRINTF        printf
#define FPRINTF       fprintf
#define SPRINTF       sprintf
#define VFPRINTF      vfprintf
#define FSCANF        fscanf
#define SSCANF        sscanf
#define GETC(x)       getc(x)
#define UNGETC(x, y)  ungetc(x, y)
#define TOLOWER(x)    tolower((x) & 0xFF)
#define TOUPPER(x)    toupper((x) & 0xFF)
#define ISALNUM(x)    isalnum((x) & 0xFF)
#define STRSTR(x, y)  strstr(x, y)
#define STRXFRM(x,y,z) strxfrm(x, y, z)
#define STRFTIME(a,b,c,d) strftime(a,b,c,d)
#define T_EOF         EOF
# ifndef _T
# define _T(x) x
# endif
#endif // UNICODE
#endif // _WIN32

} // IXE

#endif // IXE_include_char_H
