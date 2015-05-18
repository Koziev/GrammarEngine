/*
**  IXE C++ Library
**  ixe/conf/conf_string.h
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

#ifndef conf_string_H
#define conf_string_H

// Settings

// standard
#include <string>

// local
#include "conf/conf.h"

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A conf<string> is a configuration variable containing a
 *	string value.
 *
 */

template <> class conf<std::string> : public VarDefault<std::string>
{
public:
  conf(char const* name, char const* default_value = "",
       Configuration::Params& params = Configuration::variables()) :
    VarDefault<std::string>(name, default_value, params) { }

  operator		char const*() const { return value.c_str(); }

  operator		char*() const { return (char*)value.c_str(); }

  conf<std::string>&	operator =(char const* s) {
    parseValue(s);
    return *this;
  }

  std::string		operator +(char const* s) { return value + s; }
  conf<std::string>&	operator +=(std::string const& s) {
    value += s;
    return *this;
  }
  conf<std::string>&	operator +=(char const* s) {
    value += s;
    return *this;
  }

  void serialize(std::ostream& os) {
    char const* esc = strpbrk(value.c_str(), " \t") ? "\"" : "";
    os << name() << '\t' << esc << value << esc << std::endl;
  }

protected:
  virtual void	parseValue(char const*& line);
};

} // namespace IXE

#endif	/* conf_string_H */
