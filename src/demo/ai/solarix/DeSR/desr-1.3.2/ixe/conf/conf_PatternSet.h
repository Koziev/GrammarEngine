/*
**  IXE C++ Library
**  ixe/conf/conf_PatternSet.h
** ----------------------------------------------------------------------
**  Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
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

#ifndef IXE_conf_PatternSet_H
#define IXE_conf_PatternSet_H

// local
#include "conf/conf.h"
#include "conf/PatternSet.h"

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A conf_PatternSet contains a list of shell wildcard patterns.
 */

template <>
class conf<PatternSet> : public Var<PatternSet>
{
public:
  conf(char const* name,
       Configuration::Params& params = Configuration::variables()) :
    Var<PatternSet>(name, params) { }

  typedef PatternSet::iterator iterator;
  typedef PatternSet::const_iterator const_iterator;

protected:
  virtual void		parseValue(char const*& line) {
    register char const* s;
    while (s = next_token_line(line, " \r\t"))
      value.insert(s, line -s);	// PatternSet does strdup()
  }
  virtual void		reset() { value.clear(); }
};

} // namespace IXE

#endif	/* IXE_conf_PatternSet_H */
