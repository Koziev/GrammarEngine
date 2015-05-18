/*
**  IXE C++ Library
**  ixe/conf/ExcludeFile.h
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

#ifndef IXE_ExcludeFile_H
#define IXE_ExcludeFile_H

// local
#include "conf/PatternMap.h"
#include "text/strings.h"

using namespace IXE::Text;

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	An ExcludeFile contains the set of filename patterns
 *	to exclude during either indexing or extraction.
 *
 *	This is the same as index's -E command-line option.
 *
 * NOTE
 *
 *	The bool template parameter is not used here.  It's simpler to reuse
 *	the code for PatternMap as-is.
*/

class ExcludeFile : public Var<PatternMap<bool> >
{
public:
  ExcludeFile(char const* name,
	      Configuration::Params& params = Configuration::variables()) :
    Var<value_type>(name, params) { }

protected:
  virtual void	parseValue(char const*& line) {
    register char const *s;
    while (s = next_token_line(line, " \r\t"))
      value.insert(strndup(s, line -s), false);
  }
  virtual void		reset() { value.clear(); }
};

} // namespace IXE

#endif	/* IXE_ExcludeFile_H */
