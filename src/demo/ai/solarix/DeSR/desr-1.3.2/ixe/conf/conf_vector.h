/*
**  IXE C++ Library
**  ixe/conf/conf_vector.h
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

#ifndef IXE_conf_vector_H
#define IXE_conf_vector_H

// standard
#include <vector>

// local
#include "conf/conf.h"
#include "text/strings.h"

using namespace IXE::Text;

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A conf_vector contains a set of configuration values.
 *
 */

template <>
class conf<std::vector<std::string> > : public Var<std::vector<std::string> >
{
public:

  conf(char const* name,
       Configuration::Params& params = Configuration::variables()) :
    Var<value_type>(name, params) { }

protected:
  /**
   *      Parse the line of text by splitting it into words that are separated
   *      by whitespace.
   *
   *      @param line            The line of text to be parsed.
   */
  virtual void		parseValue(char const*& line) {
    register char const *s;
    while (s = next_token_line(line, " \r\t"))
      value.push_back(strndup(s, line - s));
  }
  virtual void		reset() { value.clear(); }
};

std::ostream& operator <<(std::ostream& os, std::vector<std::string>& x);

} // namespace IXE

#endif	/* IXE_conf_vector_H */
