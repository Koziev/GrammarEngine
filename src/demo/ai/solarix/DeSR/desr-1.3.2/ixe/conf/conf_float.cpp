/*
**  IXE C++ Library
**  ixe/conf_float.cpp
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

// Settings
#include "conf/conf_float.h"

// standard
#include <iostream>
#include <stdlib.h>

// local
#include "text/strings.h"

using namespace std;
using namespace Tanl::Text;

namespace IXE {

//=============================================================================
/**
 *
 *      Construct (initialize) a conf<float>.
 *
 *      @param name    The name of the configuration variable.
 *
 */
//=============================================================================
conf<float>::conf(char const *name, float default_value, Configuration::Params& params)
  : VarDefault<float>(name, default_value, params)
{ }

//=============================================================================
/**
 *      Assign a new value to the configuration variable.
 *
 *      @param new_value       The potential new value.
 */
//=============================================================================
conf<float>&
conf<float>::operator =(float new_value)
{
  value = new_value;
  return *this;
}

//=============================================================================
/**
 *
 *      Parse an float value from a configuration file line.  If successful,
 *      assign the value to ourselves; otherwise complain.
 *
 *      @param line            The line to be parsed.
 *
 */
//=============================================================================
/* virtual */
void conf<float>::parseValue(char const*& lines)
{
  if (!lines || !*lines) {
    LOG(Configuration error) << '"' << name() << "\" has no value" << endl;
    return;
  }

  char const* line = next_token_line(lines, " \t\r");
  float const n = ::atof(line);
  if (n || *line == '0') {
    operator =(n);
  } else
    LOG(Configuration error) << '"' << name() << "\" has a non-numeric value"
			     << endl;
}

} // namespace IXE
