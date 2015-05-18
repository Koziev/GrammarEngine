/*
**  IXE C++ Library
**  ixe/io/File.cpp
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

// local
#include "io/File.h"

// standard
#include <stdio.h>		// rename
#include <errno.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <limits.h>		// PATH_MAX in Mac OS

#ifdef _WIN32
#  include <direct.h>
#  include <io.h>
#  include <winsock2.h>
#  include "win32/timecnv.h"

// FIXME: from sys/unistd.h
#  define F_OK            0       /* does file exist */
#  define X_OK            1       /* is it executable by caller */
#  define W_OK            2       /* is it writable by caller */
#  define R_OK            4       /* is it readable by caller */

#define mkdir(path, mode) _mkdir(path)

#else
#  include <dirent.h>
#  include "io/pstream.h"
#endif

namespace IXE {
namespace io {

bool File::exists()
{
  struct stat	stat_buf;
  return ::stat(pathname, &stat_buf) != -1;
}

bool File::canRead()
{
  return ::access(pathname, R_OK) == 0;
}

bool File::canWrite()
{
  return ::access(pathname, W_OK) == 0;
}

bool File::isDirectory()
{
  struct stat	stat_buf;
  return ::stat(pathname, &stat_buf) != -1 && S_ISDIR(stat_buf.st_mode);
}

bool File::isEmpty()
{
  return length() == 0;
}

bool File::isFile()
{
  struct stat	stat_buf;
  return ::stat(pathname, &stat_buf) != -1 && S_ISREG(stat_buf.st_mode);
}

bool File::isIndexable()
{
# ifdef _WIN32
  DWORD dwAttrs = GetFileAttributes(pathname); 
  return !(dwAttrs & (FILE_ATTRIBUTE_SYSTEM |
		      FILE_ATTRIBUTE_HIDDEN |
		      FILE_ATTRIBUTE_NOT_CONTENT_INDEXED));
# else
  return isFile();
# endif
}

bool File::isLink()
{
# ifdef _WIN32
  return false;
# else
  struct stat lstat_buf;
  return ::lstat(pathname, &lstat_buf) != -1
    && S_ISLNK(lstat_buf.st_mode & S_IFLNK);
# endif
}

bool File::isHidden()
{
  return false;
}

off64_t File::length()
{
  struct stat sbuf;
  if (::stat(pathname, &sbuf) != 0)
    return 0;
  return sbuf.st_size;
}
  
bool File::create()
{
  if (exists())
    return false;
  int fd = ::open(pathname, O_CREAT | O_EXCL, S_IREAD | S_IWRITE);
  if (fd == -1)
    return false;
  ::close(fd);
  return true;
}

bool File::remove()
{
  if (!exists())
    return false;
  if (isDirectory())
    return ::rmdir(pathname) == 0; 
  return ::unlink(pathname) == 0;
}

time_t File::lastAccessed()
{
# ifdef  _WIN32
  FILETIME creationTime;
  FILETIME lastAccessTime;
  FILETIME lastWriteTime;
  
  HANDLE hf = CreateFile(pathname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
  if (hf == INVALID_HANDLE_VALUE)
    return 0;
  GetFileTime(hf, &creationTime, &lastAccessTime, &lastWriteTime);
  CloseHandle(hf);
  return ::FileTimeToNetworkTime(lastWriteTime);
#else
  struct stat sbuf;
  if (::stat(pathname, &sbuf) != 0)
    return 0;
  return time_t(sbuf.st_atime);
#endif
}

bool File::lastAccessed(time_t accesstime)
{
# ifdef _WIN32
  HANDLE hf = CreateFile(pathname, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
  if (hf == INVALID_HANDLE_VALUE)
    return false;
  FILETIME cft = ::NetworkTimeToFileTime(accesstime);
  BOOL bret = SetFileTime(hf, NULL, &cft, NULL);
  CloseHandle(hf);
  return bret == TRUE;    
# else
  utimbuf buf;
  buf.actime = (long)(accesstime / 1000);
  buf.modtime = (long)lastModified() / 1000;
  return ::utime(pathname, &buf) == 0;
# endif
}

time_t File::lastModified()
{
# ifdef _WIN32
  FILETIME creationTime;
  FILETIME lastAccessTime;
  FILETIME lastWriteTime;
  
  HANDLE hf = CreateFile(pathname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
  if (hf == INVALID_HANDLE_VALUE)
    return 0;
  GetFileTime(hf, &creationTime, &lastAccessTime, &lastWriteTime);
  CloseHandle(hf);
  return ::FileTimeToNetworkTime(lastWriteTime);
# else 
  struct stat sbuf;
  if (::stat(pathname, &sbuf) != 0)
    return 0;
  return time_t(sbuf.st_atime);
# endif
}

bool File::lastModified(time_t modtime)
{
# ifdef _WIN32
  HANDLE hf = CreateFile(pathname, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
  if (hf == INVALID_HANDLE_VALUE)
    return false;
  FILETIME cft = ::NetworkTimeToFileTime(modtime);
  BOOL bret = SetFileTime(hf, NULL, NULL, &cft);
  CloseHandle(hf);
  return bret == TRUE;    
# else
  utimbuf buf;
  buf.actime = (long)(lastAccessed() / 1000);
  buf.modtime = (long)(modtime / 1000);
  return ::utime(pathname, &buf) == 0;
# endif
}

time_t File::fileCreated()
{
# ifdef _WIN32
  FILETIME creationTime;
  FILETIME lastAccessTime;
  FILETIME lastWriteTime;
  HANDLE hf = CreateFile(pathname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
  if (hf == INVALID_HANDLE_VALUE)
    return 0;
  GetFileTime(hf, &creationTime, &lastAccessTime, &lastWriteTime);
  CloseHandle(hf);
  return ::FileTimeToNetworkTime(creationTime);
#else 
  struct stat sbuf;
  if (::stat(pathname, &sbuf) != 0)
    return 0;
  return time_t(sbuf.st_ctime);
#endif
}

bool File::makedir(int mode/* = 0777*/) 
{
  if (exists())
    return false;
  return ::mkdir(pathname, mode) == 0;
}

bool File::makedirs(int mode)
{
  char dir[PATH_MAX];
  char const* fn = pathname;
  while (fn && fn[0]) {
    char const* slash = ::strchr(fn, '/');
    if (!slash && !(slash = ::strchr(fn, PATH_SEPARATOR)))
      break;
    int dirlen = slash - pathname;
    ::strncpy(dir, pathname, dirlen);
    dir[dirlen] = '\0';
    fn = slash + 1;
    if (File(dir).isDirectory())
      continue;
    if (::mkdir(dir, mode))
      return false;
  }
  return true;
}

bool File::rename(char const* dest)
{
  if (!exists())
    return false;
  if (File(dest).exists())
    return false;
  return ::rename(pathname, dest) == 0;
}

std::string File::mimeType()
{
# ifndef _WIN32
  char checkMime[PATH_MAX + 20] = "file -i ";
  ::strcat(checkMime, pathname);
  ipstream output(checkMime);
  std::string line;
  std::getline(output, line);
  // format is:
  // filename: text/plain[, language][; charset=encoding]
  int ms = line.find(' ') + 1;		// skip file name:
  return std::string(line, ms);
# else
  return std::string("text/html");
# endif
}

} // io
} // IXE
