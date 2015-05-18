/*
**  IXE C++ Library
**  ixe/io/mappedFile.cpp
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
#include "io/mappedFile.h"

// standard
#include <cerrno>
#include <algorithm>
#ifdef __sun__
// avoid #define open open64 in fcntl.h
# define  __PRAGMA_REDEFINE_EXTNAME
#endif
#include <fcntl.h>		/* for open(2), O_RDONLY, etc */
#ifndef	_WIN32
# include <ctime>		/* needed by sys/resource.h */
# include <sys/mman.h>		/* for mmap(2) */
# include <sys/resource.h>	/* for get/setrlimit(2) */
# include <unistd.h>		/* for close(2), PAGE_SIZE */
#endif
#include <sys/stat.h>		/* for stat(2) */
#if defined(MULTI_THREADED) && defined(RLIMIT_VMEM)
# include <pthread.h>
#endif


// local

using namespace std;

namespace IXE {

namespace io {

//=============================================================================

bool
MappedFileView::open(FileHandle* fh, off64_t offset,
		     size_type size, ios::openmode mode)
{
  size_ = size;
  if (!size)
    return true;

# ifdef _WIN32
  map_ = ::CreateFileMapping(fh->fd_, NULL,
			     mode & ios::out ? PAGE_READWRITE : PAGE_READONLY,
			     0, 0, NULL);
  if (!map_)
    return false;

  off64_t aligned = offset & ~(PAGE_SIZE-1);
  off64_t delta = offset - aligned;

  addr_ = ::MapViewOfFile(map_,
			  mode & ios::out ? FILE_MAP_WRITE : FILE_MAP_READ,
			  ((DWORD*)&aligned)[1], ((DWORD*)&aligned)[0],
			  (SIZE_T)(size + ((SIZE_T*)&delta)[0]));
  if (!addr_)
    return false;
# else
  int prot = PROT_NONE;
  if (mode & ios::in)
    prot |= PROT_READ;
  if (mode & ios::out)
    prot |= PROT_WRITE;

  // offset must be aligned to PAGE_SIZE
  off64_t aligned = offset & ~(PAGE_SIZE-1);
  off64_t delta = offset - aligned;
  addr_ = ::mmap(0, size_ + delta, prot, MAP_SHARED, fh->fd_, aligned);
  if (addr_ == MAP_FAILED) {
    addr_ = 0;
    return false;
  }
# endif // _WIN32
  ptr_ = (char*)addr_ + delta;
  return  true;
}

void
MappedFileView::close()
{
# ifdef _WIN32
  if (addr_)
    ::UnmapViewOfFile(addr_);
  if (map_)
    ::CloseHandle(map_);
  map_ = 0;
# else
  if (addr_)
    ::munmap(static_cast<char *>(addr_), size_ + (char*)ptr_ - (char*)addr_);
  addr_ = 0;
# endif
}

//=============================================================================
/**
 *
 *      Max-out our memory-mapped address space since we can potentially
 *      mmap(2) very large files.
 *
 * NOTE
 *
 *      This function is declared extern "C" since it is called via the C
 *      library function pthread_once() (if MULTI_THREADED is defined) and,
 *      because it's a C function, it expects C linkage.
 *
 */
//=============================================================================

#ifdef RLIMIT_VMEM		/* SVR4 */
extern "C" void
max_out_limits()
{
  struct rlimit r;
  ::getrlimit(RLIMIT_VMEM, &r);
  r.rlim_cur = r.rlim_max;
  ::setrlimit(RLIMIT_VMEM, &r);
}
#endif /* RLIMIT_VMEM */

//=============================================================================
/**
 *
 *      Initialize an instance of mappedFile.
 *
 */
//=============================================================================

void
mappedFile::init()
{
#ifdef RLIMIT_VMEM		/* SVR4 */
  //
  // This OS defines a separate resource limit for memory-mapped address
  // space as opposed to data, stack, or heap space.  Anyway, we want to
  // max it out so we can mmap(2) very large files.
  //
# ifdef MULTI_THREADED
  static pthread_once_t max_out = PTHREAD_ONCE_INIT;
  ::pthread_once(&max_out, max_out_limits);
# else
  static bool maxed_out;
  if (!maxed_out)
    {
      max_out_limits();
      maxed_out = true;
    }
# endif /* MULTI_THREADED */
#endif /* RLIMIT_VMEM */

  errno_ = 0;
}

//=============================================================================
/**
 *      Open and mmap a file.
 *
 *      @return		true only if the file was mmapped successfully.
 *
 *	@see mmap(2), open(2), stat(2)
 *
 */
//=============================================================================

bool
mappedFile::open(char const *path, ios::openmode mode)
{
  if (!fh_.open(path, mode))
    return false;
  off64_t size = size_ ? size_ : fh_.size();
  if (size == 0 && !(mode & ios::out))
    // allow mapping so that we can open files used for reference fields
    // (created empty) as mapped also during indexing.
    return false;

  return ((MappedFileView*)this)->open(&fh_, 0, size, mode);
}

//=============================================================================
/**
 *	Change size of map, possibly extending file.
 *	Warning: @param mode must be compatible with the one used in opening
 *	the file.
 */
//=============================================================================
bool
mappedFile::remap(Size new_size, ios::openmode mode)
{
  if (new_size > size_)
    if (!fh_.truncate(new_size))
      return false;
  if (size_) {
# ifdef _GNU_SOURCE
    addr_ = (char*)::mremap(ptr_, size_, new_size, MREMAP_MAYMOVE);
    if (addr_ == MAP_FAILED)
      return false;
# else
    ((MappedFileView*)this)->close();
    if (!((MappedFileView*)this)->open(&fh_, 0, new_size, mode))
      return false;
# endif
  } else {
    if (!((MappedFileView*)this)->open(&fh_, 0, new_size, mode))
      return false;
  }
  size_ = new_size;
  ptr_ = addr_;
  return true;
}

//=============================================================================
/**
 *	Write an entry in the file at @param offset.
 *	File is expanded and filled with 0 from end to offset.
 */
//=============================================================================
bool
mappedFile::write(off64_t offset, void const* data, Size length)
{
  return !fh_.write(offset, data, length);
}

//=============================================================================
/**
 *
 *      Munmaps and closes a file previously opened and mmapped by
 *      mappedFile::open().
 *
 *	@see close(2), mappedFile::open(3), munmap(2)
 *
 */
//=============================================================================

void
mappedFile::close()
{
  ((MappedFileView*)this)->close();
  fh_.close();
}

} // namespace io

} // namespace IXE
