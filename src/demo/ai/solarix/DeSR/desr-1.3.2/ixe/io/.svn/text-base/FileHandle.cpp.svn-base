/*
**  IXE C++ Library
**  ixe/Common/FileHandle.cpp
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
#include "io/FileHandle.h"

// standard
#include <cerrno>
#include <algorithm>
#include <sys/stat.h>		/* for stat(2) */
#include <fcntl.h>		/* for open(2), O_RDONLY, etc */
#include <cstring>		/* for memset */
#ifdef	_WIN32
#define lseek(__fd,__offset,__fromwhere) SetFilePointer(__fd,__offset,NULL,__fromwhere)
#else
# include <unistd.h>		/* for close(2), PAGE_SIZE */
#endif

// local

using namespace std;

namespace IXE {

namespace io {

//=============================================================================

bool FileHandle::open(char const *path, ios::openmode mode) {
# ifdef _WIN32
  if (mode & ios::out)
    fd_ = ::CreateFile(path, GENERIC_WRITE | GENERIC_READ, 0, NULL,
		       OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  else
    fd_ = ::CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL,
		       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (fd_ == INVALID_HANDLE_VALUE) {
    fd_ = 0;
    return false;
  }
  if (mode & ios::trunc && mode & ios::out)
    SetEndOfFile(fd_);
  if (mode & ios::app && mode & ios::out)
    SetFilePointer(fd_, 0, 0, FILE_END);
# else
  int flags = 0;
  int perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
  if (mode & ios::in && mode & ios::out)
    flags = O_RDWR | O_CREAT;
  else if (mode & ios::in)
    flags = O_RDONLY;
  else if (mode & ios::out) {
    flags = O_WRONLY | O_CREAT;
    if (mode & ios::trunc)
      flags |= O_TRUNC;
    if (mode & ios::app)
      flags |= O_APPEND;
  }

  if ((fd_ = ::open(path, flags, perm)) == -1) {
    fd_ = 0;
    return false;
  }
# endif
  return true;
}

void FileHandle::close() {
  if (fd_)
#   ifdef _WIN32
    ::CloseHandle(fd_);
#   else
  ::close(fd_);
#   endif
  fd_ = 0;
}

off64_t FileHandle::size() {
# ifdef _WIN32
  DWORD		sizeHigh;
  DWORD sizeLow = ::GetFileSize(fd_, &sizeHigh);
  return ((off64_t)sizeHigh) << 32 | (off64_t)sizeLow;
# else
  struct stat stat_buf;
  if (::fstat(fd_, &stat_buf) == -1)
    return 0;
  return stat_buf.st_size;
# endif
}

bool FileHandle::truncate(off64_t size)
{
# ifdef _WIN32
  if (!SetFilePointer(fd_, ((DWORD*)&size)[1], (LONG*)&((DWORD*)&size)[0], FILE_BEGIN))
    return false;
  SetEndOfFile(fd_);
  return true;
# else
  return !ftruncate(fd_, size);
# endif
}

//=============================================================================
/**
 *	Write an entry in the file at @param offset.
 *	File is expanded and filled with 0 from end to offset.
 */
//=============================================================================

bool FileHandle::write(off64_t offset, void const* data, Size length)
{
  static int const bufsize = 4096;
  off64_t filesize = size();
  if (offset > filesize) {
    char blank[bufsize];
    lseek(fd_, 0, SEEK_END);
    ::memset(blank, 0, bufsize);
    int rest = offset - filesize;
    do {
      int wsize = MIN(bufsize, rest);
#     ifndef _MSC_VER
      if (::write(fd_, (void*)blank, wsize) > 0)
#     else
      DWORD nBytes;
      WriteFile(fd_, (LPCVOID)blank, wsize, &nBytes, NULL);
      if (nBytes > 0)
#     endif
	rest -= wsize;
      else
	return false;
    } while (rest > 0);
  } else
    lseek(fd_, offset, SEEK_SET);
  return write(data, length);
}

//=============================================================================
/**
 *	Write an entry in the file at current position.
 */
//=============================================================================

bool FileHandle::write(void const* data, Size length)
{
# ifdef _MSC_VER
  DWORD nBytes;
  WriteFile(fd_, (LPCVOID)data, length, &nBytes, NULL);
  return (nBytes >= 0);
# else
  return (::write(fd_, data, length) >= 0);
# endif
}

} // namespace io

} // namespace IXE
