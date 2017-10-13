/* ixe/platform.h.  Generated from platform.h.in by configure.  */
/*
**  DeSR
**  ixe/platform.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef IXE_platform_H
#define IXE_platform_H

#define PATH_SEPARATOR '/'

#define MIN	(std::min)
#define MAX	(std::max)

// byte order
/* #undef WORDS_BIGENDIAN */

// alloca()
#define HAVE_ALLOCA 1

// Unicode
/* #undef LEXLEN */

// assert()
#define NDEBUG 1

// Define if your compiler has std::unordered_map  
/* #undef HAVE_STD_UNORDERED_MAP */
  
// Define if your compiler has std::unordered_set  
/* #undef HAVE_STD_UNORDERED_SET */
  
// Define if your compiler has std::tr1::unordered_map  
#define HAVE_TR1_UNORDERED_MAP /**/
  
// Define if your compiler has std::tr1::unordered_set  
#define HAVE_TR1_UNORDERED_SET /**/

// Define if you have hash_map and hash_set includes in ext/ directory.
/* #undef HAVE_EXT_HASH_MAP_SET */

/*
 * Large-file configuration.
 * Disable with configure --disable-largefile
 * (produces index with 32-bit offsets for postings)
 */
/* #undef _FILE_OFFSET_BITS */
/* #undef _LARGE_FILES */

#ifdef __sun
# define __PRAGMA_REDEFINE_EXTNAME
#endif

/*
 * Provide proper definitions for off64_t
*/
/* #undef off64_t */
typedef int off32_t;

/* Determine if processor requires byte alignment */
#define BYTE_ALIGN 1

/*
 * Compute value of getpagesize()
 */
#define PAGE_SIZE 4096

/* Enable GNU extensions.  */
#define _GNU_SOURCE 1

/* Use thread-safe versions of libc functions.  */
#define _REENTRANT 1

#ifdef __DECCXX
#define __USE_STD_IOSTREAM
#endif

#define GMTIME(time, tm)	{ time_t __gmtime_tmp = *time; gmtime_r(&__gmtime_tmp, &tm); }
#define time_now(time)		gettimeofday(time, 0);

#endif	/* IXE_platform_H */
