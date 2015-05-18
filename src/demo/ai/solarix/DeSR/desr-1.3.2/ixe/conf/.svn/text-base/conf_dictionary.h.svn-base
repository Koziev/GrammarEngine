/*
**  IXE C++ Library
**  ixe/conf/conf_dictionary.h
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

#ifndef IXE_conf_dictionary_H
#define IXE_conf_dictionary_H

// standard
#include <map>

// local
#include "conf/conf.h"
#include "text/strings.h"

using namespace IXE::Text;

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A conf_dictionary contains a dictionary
 *
 */

typedef std::map<char const*, char const*> Dictionary;

template <>
class conf<Dictionary> : public Var<Dictionary>
{
public:

  conf(char const* name,
       Configuration::Params& params = Configuration::variables()) :
    Var<value_type>(name, params) { }

  char const* operator [](value_type::key_type key) const {
    value_type::const_iterator const kit = value.find(key);
    return kit != value.end() ? kit->second : key;
  }
protected:
  /**
   *      Parse the line of text by splitting it into words that are separated
   *      by whitespace.
   *
   *      @param line            The line of text to be parsed.
   */
  virtual void		parseValue(char const*& line) {
    register char const *s;
    char const* key = next_token_line(line, " \r\t");
    key = strndup(key, line - key);
    while (s = next_token_line(line, " \r\t"))
      if (noOverride)
	free((void*)key);
      else
	value[key] = strndup(s, line - s);
  }
  virtual void		reset() { }
};

} // namespace IXE

#endif	/* IXE_conf_dictionary_H */
