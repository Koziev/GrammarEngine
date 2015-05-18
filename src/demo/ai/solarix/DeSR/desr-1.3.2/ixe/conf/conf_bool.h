/*
**  IXE C++ Library
**  ixe/conf/conf_bool.h
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

#ifndef conf_bool_H
#define conf_bool_H

// Settings
#include "conf/conf.h"

// local

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A conf<bool> is a Var for containing the value of a Boolean
 *	configuration variable.
 *
 */

template <> class conf<bool> : public VarDefault<bool>
{
public:
  conf() {}

  conf(char const* name, bool default_value, Configuration::Params& params = Configuration::variables()) :
    VarDefault<bool>(name, default_value, params)
  { }

  conf<bool>& operator =(bool new_value) {
    value = new_value;
    return *this;
  }

protected:
  virtual void		parseValue(char const*& line);
};

} // namespace IXE

#endif	/* conf_bool_H */
