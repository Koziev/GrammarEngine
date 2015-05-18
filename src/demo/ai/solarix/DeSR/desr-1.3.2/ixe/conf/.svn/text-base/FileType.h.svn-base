/*
**  IXE C++ Library
**  ixe/conf/FileType.h
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

#ifndef IXE_FILETYPE_H
#define IXE_FILETYPE_H

// Settings
#include "platform.h"

// standard
#include <map>

// local
#include "conf/conf.h"
#include "PatternMap.h"

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A FileType maps a filename pattern to a file type.
 */

class FileType : public Var<PatternMap<char const*> >
{
public:
  FileType(char const* name,
       Configuration::Params& params = Configuration::variables()) :
    Var<value_type>(name, params) { }

  char const* operator [](value_type::key_type key) const {
    value_type::const_iterator const kit = value.find(key);
    return kit != value.end() ? kit->second : "";
  }
protected:

  virtual void	parseValue(char const*& line);
  virtual void	reset() { value.clear(); }
};

extern FileType	fileTypes;		// type associated to file

/**
 *	@ingroup configuration
 *
 *	A MimeType maps a mime type to a document reader type.
 */

typedef FileType MimeType;

extern MimeType	mimeTypes;		// reader type associated to mime

} // namespace IXE

#endif	/* IXE_FILETYPE_H */
