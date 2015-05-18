/*
**  IXE C++ Library
**  ixe/Common/util.cpp
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

// Settings
#include "Common/util.h"

// standard
#ifdef _WIN32
# include <WinSock2.h>		// For GlobalMemoryStatus, timeval
#endif
#include <assert.h>
#include <ctime>
#include <iomanip>		// setw
#ifdef __linux__
# include <sys/sysinfo.h>	// sysinfo
#endif

// local
#include "conf/conf_int.h"
#include "conf/conf_bool.h"

using namespace std;

namespace IXE {

struct stat stat_buf;		// someplace to do a stat(2) in

bool	is_indexable_file(char const* path) {
# ifdef _WIN32
  DWORD dwAttrs = GetFileAttributes(path); 
  return !(dwAttrs & (FILE_ATTRIBUTE_SYSTEM |
		      FILE_ATTRIBUTE_HIDDEN |
		      FILE_ATTRIBUTE_NOT_CONTENT_INDEXED));
# else
  return is_plain_file(path);
# endif
}

//=============================================================================
/**
 *	Perform action on each file in directory tree
 */
//=============================================================================

void
mapDir(char const* pathname, FileAction& action,
       bool recurse_subdirectories, bool follow_symbolic_links,
       int verbosity)
{
# ifndef IXE_NO_SYMBOLIC_LINKS
  if (is_symbolic_link(pathname) && !follow_symbolic_links) {
    if (verbosity > 3)
      std::cout << "  " << pathname << " (skipped: symbolic link)" << std::endl;
    return;
  }
# endif
	
# ifdef __unix__
  if (is_directory(pathname)) {
    if (recurse_subdirectories) {
      DIR *dirp = ::opendir(pathname);
      if (dirp == NULL) {
	if (verbosity > 3)
	  std::cerr << "  " << pathname << " (skipped: can not open)" << std::endl;
	return;
      }
      std::string const dir_string(pathname);
      struct dirent const* dir_ent;
      while ((dir_ent = readdir(dirp)) != NULL)	{
	if (dir_ent->d_name[0] == '.')	// skip dot files
	  continue;
	std::string const path(dir_string + PATH_SEPARATOR + dir_ent->d_name);
	mapDir(path.c_str(), action,
	       recurse_subdirectories, follow_symbolic_links, verbosity);
      }
      ::closedir(dirp);
    }
  }
# elif defined(_WIN32)
  if (is_directory(pathname)) {
      if (recurse_subdirectories) {
	WIN32_FIND_DATA find;
	HANDLE directory;
	
	std::string const dir_string(pathname + std::string("\\*"));

	directory = FindFirstFile(dir_string.c_str(), &find); /* eat .  */
	if (directory == INVALID_HANDLE_VALUE) {
	  if (verbosity > 3)
	    std::cerr << "  " << pathname << " (skipped: can not open)" << std::endl;
	  return;
	}
	if (verbosity > 1)
	  std::cerr << pathname << std::endl;

	FindNextFile(directory, &find);           /* eat .. */

	while (FindNextFile(directory, &find)) {
	  string const path(string(pathname) + PATH_SEPARATOR + 
			    find.cFileName);
	  mapDir(path.c_str(), action,
		 recurse_subdirectories, follow_symbolic_links, verbosity);
	}
      }
    }
# endif // _WIN32
  else
    action(pathname);
}

//=============================================================================
/**
 *      Display the duration of an interval in sec, microseconds
 *
 *      @param msg	Comment message
 *	@param l0	interval start
 *	@param l1	interval end
 */
//=============================================================================
void
showTime(char const* msg, struct ::timeval& l0, struct ::timeval& l1, ostream& out)
{
  long sec = l1.tv_sec - l0.tv_sec;
  long usec = l1.tv_usec - l0.tv_usec;
  if (usec < 0) {
    sec--;
    usec += 1000000;
  }
  out << msg << setw(3) << sec << "\"" << setw(4) << usec / 1000 << " ms";
}

static int htoi(char const* s)
{
  int value;
  int c = s[0];
  if (isupper(c))
    c = tolower(c);
  value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;
  c = s[1];
  if (isupper(c))
    c = tolower(c);
  value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
  return (value);
}

//=============================================================================
/**
 *
 *	Decodes any %## encoding in the given string.
 *
 *	@return	the difference in size between src and dest.
 *
 */
//=============================================================================

int url_decode(char* dest, char const* src, int len)
{
  char* cur = dest;
  if (!len)
    len = ::strlen(src) ;

  while (len--) {
    if (*src == '+')
      *cur = ' ';
    else if (*src == '%' && len >= 2 && isxdigit((int)(src[1]))
	     && isxdigit((int)(src[2]))) {
#     ifdef CHARSET_EBCDIC
      *cur = os_toebcdic[(char)htoi(src + 1)];
#     else
      *cur = (char)htoi(src + 1);
#     endif
      src += 2;
      len -= 2;
    } else
      *cur = *src;
    src++;
    cur++;
  }
  *cur = '\0';
  return cur - dest;
}

static unsigned char hexchars[] = "0123456789abcdef";

//=============================================================================
/**
 * Returns a string in which all non-alphanumeric characters except
 * "-_.!~*'()," have been replaced with a percent (%) sign followed by
 * two hex digits.
 * This is the encoding described in RFC 2396 for protecting literal characters
 * from being interpreted as special URL delimiters, and for protecting URL's
 * from being mangled by transmission media with character conversions (like
 * some email systems).
 *
 * According to RFC 2396, only alphanumerics, the unreserved characters
 * "-_.!~*'()", and reserved characters ";/?:@&=+$,", used for their reserved
 * purposes may be used unencoded within a URL.
 * (@see http://www.faqs.org/rfcs/rfc2396.html)
 */
//=============================================================================
char *
url_encode(char const* s)
{
  register int x, y;
  unsigned char* str;
  int len = ::strlen(s);

  str = (unsigned char *)malloc(3 * len + 1);
  for (x = 0, y = 0; len--; x++, y++) {
    unsigned char c = str[y] = (unsigned char)s[x];
    // cant use isalnum(c) since it depends on locale
    if (!(c >= 'a' && c <= 'z') &&
	!(c >= 'A' && c <= 'Z') &&
	!(c >= '0' && c <= '9') &&
	::strchr("-_.!~*'()", c) == NULL) {
      str[y++] = '%';
      str[y++] = hexchars[(unsigned char)s[x] >> 4];
      str[y] = hexchars[(unsigned char)s[x] & 15];
    }
  }
  str[y] = '\0';
  return (char *)str;
}

/**
 *	@return the length of the encoded string
 */
int
url_encode(char* dst, char const* s)
{
  unsigned char* str = (unsigned char*)dst;
  unsigned char c;

  for (; (c = *s); s++) {
    // cant use isalnum(c) since it depends on locale
    if (!(c >= 'a' && c <= 'z') &&
	!(c >= 'A' && c <= 'Z') &&
	!(c >= '0' && c <= '9') &&
	::strchr("-_.!~*'()", c) == NULL) {
      *str++ = '%';
      *str++ = hexchars[c >> 4];
      *str++ = hexchars[c & 15];
    } else
      *str++ = c;
  }
  *str = '\0';
  return (str - (unsigned char*)dst);
}

/**
 *	Return the URL's site in reverse
 *
 *	@param	url is the URL
 */
void
reverseURLdomain(char* revDomain, char const* url, Size len)
{
  // Can't use "http://", since "//" is comment
  static char const URL[] = "http:/" "/";
  if (::strncasecmp(URL, url, 7)) {
    revDomain[0] = '\0';
    return;
  }
  char const* start = url + 7;
  char const* end = ::strchr(start, '/');
  if (!end)
    end = start + ::strlen(start);
  // strip optional port number (:8080)
  char const* port = ::strchr(start, ':');
  if (port && port < end)
    end = port;
  if ((Size)(end - start) > len)
    start = end - len;
  while (start < end) {
    char const* domain = end;
    while (start < domain && *--domain != '.') ;
    if (start <= domain) {
      if (start == domain &&
	  *domain != '.') // not malformed URL
	domain--;
      int len = end - (domain + 1);
      ::strncpy(revDomain, domain + 1, len);
      revDomain += len;
      *revDomain++ = '.';
      end = domain;
    }
    else
      break;
  }
  // Replace last '.'
  revDomain[-1] = '\0';
}

void
unreverseURLdomain(char* domain, char const* revDomain)
{
  char const* start = revDomain;
  char const* end = revDomain + ::strlen(revDomain);
  if (start == end) {
    domain[0] = '\0';
	return;
  }
  while (start < end) {
    char const* RevDomain = end;
    while (start < RevDomain && *--RevDomain != '.') ;
    if (start <= RevDomain) {
      if (start == RevDomain &&
	  *RevDomain != '.') // not malformed URL
	RevDomain--;
      int len = end - (RevDomain + 1);
      ::strncpy(domain, RevDomain + 1, len);
      domain += len;
      *domain++ = '.';
      end = RevDomain;
    }
    else
      break;
  }
  // Replace last '.'
  domain[-1] = '\0';
}

/**
 *	Detect the available memory
 */
Size
availableMemory() {
# ifdef __linux__
# include <linux/version.h>
# if LINUX_VERSION_CODE > KERNEL_VERSION(2,3,48)
# define MEM_UNIT(info)	info.mem_unit
# else
# define MEM_UNIT(info)	1
# endif
  struct sysinfo info;
  sysinfo(&info);
  return (info.totalram * MEM_UNIT(info));
# elif defined(_WIN32)
  MEMORYSTATUS ms;
  GlobalMemoryStatus(&ms);
  return ms.dwAvailPhys;
# else
  return 0;
# endif
}

/**
 *	Parse a cgi query into a map of key values.
 */
void
cgi_parse(map<char const*, char const*>& keyMap, char* qstart)
{
  // replace ';' with '&'
  char* qend = qstart;
  for (char c = *qstart; (c = *qend); qend++)
    if (c == ';')
      *qend = '&';

  do {
    char* key = qstart;
    char* valstart = ::strchr(qstart, '=');
    valstart = valstart ? valstart : qend;
    char* valend = ::strchr(valstart, '&');
    valend = valend ? valend : qend;
    if (key < valstart && valstart < valend) {
      *valstart = '\0';
      *valend = '\0';
      url_decode(valstart + 1, valstart + 1);
      keyMap[key] = valstart+1;
    }
    qstart = valend + 1;
  } while (qstart < qend);
}

} // namespace IXE
