/*
**  IXE C++ Library
**  ixe/io/File.h
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

#ifndef	IXE_io_File_H
#define	IXE_io_File_H

// Settings
#include "platform.h"

// standard
#ifdef _WIN32
# include <sys/utime.h>
#else
# include <utime.h>
# include <unistd.h>		// off64_t
#endif
#include <string>

namespace IXE {
  /**
   *	Platform independent IO.
   */
namespace io {

class File
{
public:
  File(char const* pathname)
    : pathname(pathname)
  { }

  File(std::string& pathname)
    : pathname(pathname.c_str())
  { }

  bool		create();
  /** @return true if file esists */
  bool		exists();
  /** @return true if read permissions are granted on file */
  bool		canRead();
  /** @return true if write permissions are granted on file */
  bool		canWrite();
  bool		isEmpty();
  /** @return true if file is directory */
  bool		isDirectory();
  /** @return true if file is normal file */
  bool		isFile();
  bool		isHidden();
  bool		isIndexable();
  bool		isLink();
  off64_t	length();
  bool		remove();
  /** @return the associated MIM type */
  std::string	mimeType();
  /**
   * @return seconds since 1970-01-01T00:00:00:000
   */
  time_t	lastAccessed();
  bool		lastAccessed(time_t);
  /**
   * @return seconds since 1970-01-01T00:00:00:000
   */
  time_t	lastModified();
  bool		lastModified(time_t);
  /**
   * @return seconds since 1970-01-01T00:00:00:000
   */
  time_t	fileCreated();
  bool		makedir(int mode = 0755);
  /**
   *	Create directory hierarchy
   */
  bool		makedirs(int mode = 0755);
  bool		rename(char const* dest);
protected:
  char const*	pathname;
};

} // io
} // IXE

#endif // IXE_io_File_H
