/*
**	IXE
**	win32/platform.h
** ----------------------------------------------------------------------
**	Copyright (c) 2000  Ideare SpA. All rights reserved.
** ----------------------------------------------------------------------
*/

#ifndef platform_H
#define platform_H

// reduce unnecessary linking
#define WIN32_LEAN_AND_MEAN

#include <time.h>

#define NAMESPACE_IXE_BEGIN	namespace IXE {
#define NAMESPACE_IXE_END	}

#define PATH_SEPARATOR '\\'

// from limits.h
#define PATH_MAX            1024

// Windows doesn't have any notion of symbolic links.
#define	IXE_NO_SYMBOLIC_LINKS

// Intel is LittleEndian
#undef WORDS_BIGENDIAN

// Search service is provided as a Web Service
#undef SEARCH_DAEMON
#define IXE_SOCKLEN_TYPE int

// Support for paragraph search
#define PARAGRAPH_SEARCH

#define S_ISDIR(X) ((_S_IFDIR & (X)) != 0)
#define S_ISREG(X) ((_S_IFREG & (X)) != 0)

#define HAVE_TR1_UNORDERED_MAP
#define HAVE_TR1_UNORDERED_SET
#define HAVE_TR1_RANDOM

/*
#include <windows.h>

size_t
getAllocationGranularity()
{
 SYSTEM_INFO s;
 GetSystemInfo(&s);
 return s.dwAllocationGranularity;
*/

#define PAGE_SIZE 65536		// getAllocationGranularity()

#ifdef _MSC_VER
// VS 2005
#define localtime_r(t, tm) localtime_s(tm, t)
#define gmtime_r(t, tm) gmtime_s(tm, t)

// Use this to avoid warnings on _vsnprintf()
#define _CRT_SECURE_NO_WARNINGS
#define strncasecmp _strnicmp
#define strnicmp _strnicmp
#define strcasecmp _stricmp
#define snprintf _snprintf
#define strdup _strdup
#if (_MSC_VER < 1500)
#define vsnprintf _vsnprintf
#endif
#define finite _finite

// avoid warnings on truncated typenames
#pragma warning(disable:4786)
#pragma warning(disable:4995)

// avoid warnings on 'this' used in base member initializer
#pragma warning(disable:4355)

// avoid warnings on deprecated hash_set
#pragma warning(disable:4996)

// forcing int to bool
#pragma warning(disable:4800)

// avoid warnings on conversion from size_t to Size
#pragma warning(disable:4267)
// avoid warnings on conversion from __w64 to Size
#pragma warning(disable:4244)
// avoid warnings on pointer truncation from __w64 to Size
#pragma warning(disable:4311)

// avoid warning on nonstandard extension used : zero-sized array
#pragma warning(disable:4200)

#endif // _MSC_VER

#define MIN	(std::min)
#define MAX	(std::max)

#define LINE_MAX 2048

#define off64_t __int64

typedef long off32_t;
typedef int ssize_t;

typedef unsigned short int in_port_t;

#define BYTE_ALIGN

#define _POSIX_ARG_MAX 4096

#define SEARCH_DAEMON
#define MULTI_THREADED

#ifdef _M_IX86
#define __i386__
#endif

#define StringToAnsi(s) \
	(char const*)Marshal::StringToHGlobalAnsi(s).ToPointer()

/*
#ifndef DllExport
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define DllExport
#   else
#     define DllExport __declspec(dllexport)
#   endif
# endif
#endif
*/

#endif	/* platform_H */
