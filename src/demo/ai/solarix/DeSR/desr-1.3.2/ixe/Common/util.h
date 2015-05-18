/*
**  IXE C++ Library
**  ixe/Common/util.h
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

#ifndef	IXE_util_H
#define	IXE_util_H

// Settings
#include "include/ixe.h"

// local
#include "text/less.h"

// standard
#include <cctype>
#include <cerrno>
#include <climits>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#ifndef	_WIN32
# include <ctime>		// needed by sys/resource.h
# include <dirent.h>		// for DIR, opendir(), readdir()
# include <sys/resource.h>	// for RLIMIT_*
#endif
#include <sys/stat.h>

// to avoid including WinSock2.h here, we introduce Timeval,
// or else timeval will become ambiguous (in IXE and global namespaces)
typedef struct timeval Timeval;

// From RFC 2616:
// http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.2
//
// The HTTP protocol does not place any a priori limit on the length of a URI.
// Servers MUST be able to handle the URI of any resource they serve, and
// SHOULD be able to handle URIs of unbounded length if they provide GET-based
// forms that could generate such URIs. A server SHOULD return 414 (Request-URI
// Too Long) status if a URI is longer than the server can handle (see section
// 10.4.15). 

// However, from
// http://support.microsoft.com/default.aspx?scid=http://support.microsoft.com:80/support/kb/articles/Q208/4/27.ASP&NoWebContent=1
//
// Internet Explorer has a maximum uniform resource locator (URL) length of
// 2,083 characters, with a maximum path length of 2,048 characters.
// This limit applies to both POST and GET request URLs.

// Max length for a URL
#define URL_MAX 2*2048

namespace IXE {

/**
 *
 *	Set the limit for the given resource to its maximum value.
 *
 *	@param resource	The ID for the resource as given in sys/resources.h.
 *
 * NOTE
 *
 *	This can't be an ordinary function since the type "resource" isn't int
 *	on some systems.
 *
 * SEE ALSO
 *
 *	W. Richard Stevens.  "Advanced Programming in the Unix Environment,"
 *	Addison-Wesley, Reading, MA, 1993. pp. 180-184.
 *
 */

#ifdef	_SYS_RESOURCE_H
template <class T>
rlim_t max_out_limit(T resource)
{
  struct rlimit r;
  ::getrlimit(resource, &r);
  r.rlim_cur = r.rlim_max;
  ::setrlimit(resource, &r);
  return r.rlim_max;
}
#endif

//=============================================================================
/**
 *	File test functions.
 */
//=============================================================================

inline bool	file_empty(char const* path) {
  struct stat	stat_buf;
  ::stat(path, &stat_buf);
  return stat_buf.st_size == 0;
}

inline off_t	file_size(char const* path) {
  struct stat	stat_buf;
  ::stat(path, &stat_buf);
  return stat_buf.st_size;
}

inline bool	file_exists(char const* path) {
  struct stat	stat_buf;
  return ::stat(path, &stat_buf) != -1;
}
inline bool	file_exists(std::string const &path) {
  return file_exists(path.c_str());
}

inline bool	is_directory(char const* path) {
  struct stat	stat_buf;
  return ::stat(path, &stat_buf) != -1 && S_ISDIR(stat_buf.st_mode);
}

inline bool	is_directory(std::string const& path) {
			return is_directory(path.c_str());
}

inline bool	is_plain_file(char const* path) {
  struct stat	stat_buf;
  return ::stat(path, &stat_buf) != -1 && S_ISREG(stat_buf.st_mode);
}
inline bool	is_plain_file(std::string const& path) {
  return is_plain_file(path.c_str());
}

bool		is_indexable_file(char const* path);

#ifndef	IXE_NO_SYMBOLIC_LINKS
inline bool	is_symbolic_link(char const* path) {
			struct stat lstat_buf;
			return ::lstat(path, &lstat_buf) != -1
			       && S_ISLNK(lstat_buf.st_mode & S_IFLNK);
}
inline bool	is_symbolic_link(std::string const& path) {
			return is_symbolic_link(path.c_str());
}
#endif	/* IXE_NO_SYMBOLIC_LINKS */

//=============================================================================
/**
 *	Perform action on each file in directory tree
 */
//=============================================================================

struct FileAction {
  virtual void operator() (char const* pathname) = 0;
};

void
mapDir(char const* pathname, FileAction& action,
       bool recurse_subdirectories = true, bool follow_symbolic_links = true,
       int verbosity = 0);

//=============================================================================
/**
 *
 *	Miscelleneous.
 *
 */
//=============================================================================

#define	FOR_EACH(T, C, I) \
	for (T::const_iterator I = (C).begin(); I != (C).end(); ++I)

#define	TO_EACH(T, C, I) \
	for (T::iterator I = (C).begin(); I != (C).end(); ++I)

#define	TRANSFORM_EACH(T, C, I) \
	for (T::iterator I = (C).begin(); I != (C).end(); ++I)

void	showTime(char const* msg, Timeval& l0, Timeval& l1,
		 std::ostream& out = std::cerr);

int	url_decode(char* dest, char const* src, int len = 0);
char*	url_encode(char const* s);
int	url_encode(char* dst, char const* s);
void	reverseURLdomain(char* revDomain, char const* url, Size len);
void	unreverseURLdomain(char* domain, char const* revDomain);
Size	availableMemory();
void	cgi_parse(std::map<char const*, char const*>& keyMap, char* qstart);


// pad file to align
#ifdef BYTE_ALIGN
#define PAD_FILE(o, size)
#else
#define PAD_FILE(o, size) \
	{ int pad = (size - (o.tellp() % size)) % size; \
	  if (pad) { const long z = 0; \
 		   o.write(reinterpret_cast<const char*>(&z), pad); } }
#endif

} // namespace IXE

#endif	/* IXE_util_H */
