/*
**  IXE C++ Library
**  ixe/io/FileHandle.h
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

#ifndef IXE_FileHandle_H
#define IXE_FileHandle_H

// Settings
#include "include/ixe.h"

// standard
#include <sys/types.h>			/* for off_t */
#include <fstream>

// local
#include "include/error.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

namespace IXE {

namespace io {

//=============================================================================
/**
 *	FileHandle abstract from OS
 */
//=============================================================================

class FileHandle
{
public:
  FileHandle() : fd_(0) { }

  FileHandle(char const* path, std::ios::openmode mode = std::ios::in) {
    if (!open(path, mode))
      throw FileError(std::string("Cannot open file ") += path);
  }

  ~FileHandle() { close(); }

  bool			open(char const *path,
			     std::ios::openmode mode = std::ios::in);
  void			close();
  off64_t		size();
  bool			truncate(off64_t size);
  bool			write(off64_t offset, void const* data, Size length);
  bool			write(void const* data, Size length);

# ifdef _WIN32
  HANDLE		fd_;
# else
  int			fd_;			// Unix file descriptor
# endif
};

} // namespace io

} // namespace IXE

#endif	/* IXE_FileHandle_H */
