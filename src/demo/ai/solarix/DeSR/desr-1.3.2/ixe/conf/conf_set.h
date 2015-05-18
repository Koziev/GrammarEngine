/*
**  IXE C++ Library
**  ixe/conf/conf_set.h
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

#ifndef IXE_conf_conf_set_H
#define IXE_conf_conf_set_H

// standard
#include <set>

// local
#include "conf/conf.h"
#include "text/strings.h"

using namespace Tanl::Text;

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A conf_set contains a set of configuration values.
 *
 */

template <class T>
class conf_set : public Var<std::set<T> >
{
public:

  conf_set(char const* name,
	   Configuration::Params& params = Configuration::variables()) :
    Var<std::set<T> >(name, params) { }

  conf_set(char const* name, T const& value,
	   Configuration::Params& params = Configuration::variables()) {
    this->insert(value);
  }

  conf_set(char const* name, char const* list,
	   Configuration::Params& params = Configuration::variables()) :
    Var<std::set<T> >(name, params) {
    this->parseValue(list);
  }

  virtual bool		contains(T const& s) const {
    return this->value.find(s) != this->value.end(); }

protected:
  /**
   *      Parse the line of text by splitting it into tokens separated
   *      by whitespace.
   *
   *      @param line            The line of text to be parsed.
   */
  virtual void		parseValue(char const*& line);

  virtual void		reset() { this->value.clear(); }
};

/**
 *	@ingroup configuration
 *
 *	A conf_set contains a set of configuration string values.
 *
 */
typedef conf_set<std::string> conf_stringset;

template <>
conf_set<std::string>::conf_set(char const* name, std::string const& list,
				Configuration::Params& params);
template <>
void conf_set<std::string>::parseValue(char const*& line);

template <>
void conf_set<int>::parseValue(char const*& line);

std::ostream& operator <<(std::ostream& os, std::set<std::string>& x);

} // namespace IXE

#endif	/* IXE_conf_conf_set_H */
