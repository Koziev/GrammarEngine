/*
**  IXE C++ Library
**  ixe/io/mappedFile.h
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

#ifndef IXE_mappedFile_H
#define IXE_mappedFile_H

// Settings
#include "platform.h"

// standard
#include <iterator>
#include <sys/types.h>			/* for off_t */
#include <cerrno>			/* for errno */

// local
#include "include/error.h"
#include "io/FileHandle.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace IXE {

namespace io {

//=============================================================================
/**
 *	A mappedFile is an object that maps a file into memory (via the Unix
 *	system call mmap(2)) allowing it to be accessed via iterators.
 *	Processing a file, especially files accessed randomly, is MUCH faster
 *	than standard I/O.
 *
 *	@see mmap(2)
 *
 *	W. Richard Stevens.  "Advanced Programming in the Unix Environment,"
 *	Addison-Wesley, Reading, MA, 1993.  pp. 407-413
 *
 */
//=============================================================================

class MappedFileView
{
 public:
  ////////// typedefs ///////////////////////////////////////////////////

# ifdef _WIN32
  typedef DWORD			size_type;
# else
  typedef off64_t		size_type;
# endif
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef char			value_type;
  typedef ptrdiff_t		difference_type;
  typedef value_type*		pointer;
  typedef value_type&		reference;
  typedef value_type const&	const_reference;

  ////////// constructors & destructor //////////////////////////////////

  MappedFileView() : size_(0), addr_(0), ptr_(0)
#   ifdef _WIN32
    , map_(0)
#   endif
 { }

  MappedFileView(FileHandle* fh, off64_t offset, size_type size,
		 std::ios::openmode mode = std::ios::in) {
    open(fh, offset, size, mode);
  }

  MappedFileView(FileHandle* fh) { open(fh, 0, (size_type)fh->size()); }

  ~MappedFileView() { close(); }

  ////////// iterators //////////////////////////////////////////////////

  typedef value_type* iterator;
  typedef value_type const* const_iterator;

# ifdef _MSC_VER
  typedef std::reverse_bidirectional_iterator<iterator, char*> reverse_iterator;
  typedef std::reverse_bidirectional_iterator<const_iterator, char*, char const&> const_reverse_iterator;
# else
  typedef std::reverse_iterator<char*> reverse_iterator;
  typedef const std::reverse_iterator<char const*> const_reverse_iterator;
# endif

  iterator		begin()		{ return (iterator)ptr_; }
  const_iterator	begin() const	{ return (const_iterator)ptr_; }
  iterator		end()		{ return begin() + size_; }
  const_iterator	end() const	{ return begin() + size_; }

  reverse_iterator 	rbegin()	{ return reverse_iterator(end()); }
  reverse_iterator 	rend()		{ return reverse_iterator(begin()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  const_reverse_iterator rend() const	{ return const_reverse_iterator(begin()); }

  ////////// member functions ///////////////////////////////////////////

  bool			open(FileHandle* fh, off64_t offset, size_type size,
			     std::ios::openmode mode = std::ios::in);
  void			close();

  reference		back()			{ return *(end() - 1); }
  const_reference	back() const		{ return *(end() - 1); }
  reference		front()			{ return *begin(); }
  const_reference	front() const		{ return *begin(); }
  bool			empty() const		{ return !size_; }
  size_type		max_size() const	{ return size_; }
  size_type		size() const		{ return size_; }

  reference		operator [](size_type i) { return *(begin() + i); }

  const_reference	operator [](size_type i) const {
    return *(begin() + i);
  }

protected:
# ifdef _WIN32
  HANDLE		map_;
# endif
  size_type		size_;
  void*			addr_;
  void*			ptr_;	// actual location (considering page alignment)
};

/**
 *	Map a whole file
 */
class mappedFile : public MappedFileView
{
 public:
  ////////// constructors & destructor //////////////////////////////////

  mappedFile()		{ init(); }
  mappedFile(char const* path, std::ios::openmode mode = std::ios::in) {
    init();
    int r = open(path, mode);
    if (!r)
      throw MmapError(std::string("Cannot mmap file ") += path);
  }
  ~mappedFile()		{ close(); }

  ////////// member functions ///////////////////////////////////////////

  bool			open(char const *path,
			     std::ios::openmode = std::ios::in);
  void			close();
  operator		bool() const		{ return !errno_; }
  int			error() const		{ return errno_; }
  bool			write(off64_t offset, void const* data, Size length);
  bool			remap(Size size, std::ios::openmode = std::ios::in);
  FileHandle&		handle() { return fh_; }

 private:
  FileHandle		fh_;
  int			errno_;

  void			init();
};

} // namespace io
} // namespace IXE

#endif	/* IXE_mappedFile_H */
