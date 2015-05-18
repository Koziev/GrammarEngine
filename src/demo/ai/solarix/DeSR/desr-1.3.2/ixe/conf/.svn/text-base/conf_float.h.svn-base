/*
**  IXE C++ Library
**  ixe/conf/conf_float.h
** ----------------------------------------------------------------------
**  Copyright (c) 2007  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef IXE_conf_float_H
#define IXE_conf_float_H

// Settings
#include "platform.h"

// system
#include <string>

// local
#include "conf/conf.h"

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A conf<float> is a Var for containing the value of a float
 *	configuration variable.
 *
 */

template <> class conf<float> : public VarDefault<float>
{
public:
	conf(char const *name,
	     float default_value = 0.0, Configuration::Params& params = Configuration::variables());

	conf<float>&	operator =(float new_value);

	conf<float>&	operator =(char const* s) {
	  parseValue(s);
	  return *this;
	}

protected:
	virtual void	parseValue(char const*& line);
};

} // namespace IXE

#endif	/* IXE_conf_float_H */
