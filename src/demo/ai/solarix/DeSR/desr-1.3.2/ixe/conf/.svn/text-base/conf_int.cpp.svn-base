/*
**  IXE C++ Library
**  ixe/conf/conf_int.h
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

// Settings
#include "conf/conf_int.h"

// standard
#include <stdlib.h>
#include <iostream>

// local
#include "text/strings.h"

using namespace std;
using namespace Tanl::Text;

namespace IXE {

//=============================================================================
/**
 *
 *      Construct (initialize) a conf<int>.
 *
 *      @param name    The name of the configuration variable.
 *
 */
//=============================================================================
conf<int>::conf(char const* name, int default_value, int min, int max, Configuration::Params& map)
: VarDefault<int>(name, default_value, map), min_(min), max_(max)
{ }

conf<int>::conf(char const* name, int default_value, int min, Configuration::Params& map)
  : VarDefault<int>(name, default_value, map), min_(min), max_(INT_MAX)
{ }

conf<int>::conf(char const* name, int default_value, Configuration::Params& map)

  : VarDefault<int>(name, default_value, map), min_(0), max_(INT_MAX)
{ }

//=============================================================================
/**
 *      Assign a new value to the configuration variable, but only if its value
 *      is within the legal range; otherwise complain.
 *
 *      @param new_value       The potential new value.
 */
//=============================================================================
conf<int>& conf<int>::operator =(int new_value)
{
  if (new_value >= min_ && new_value <= max_) {
    value = new_value;
    return *this;
  }

  LOG(Configuration error) << '"' << name() << "\" value \""
			   << new_value << "\" not in range [" << min_ << '-';
  if (max_ == INT_MAX)
    clog << "infinity";
  else
    clog << max_ << ']' << endl;
  return *this;			// make DECXX happy
}

//=============================================================================
/**
 *
 *      Parse an integer value from a configuration file line.  If successful,
 *      assign the value to ourselves; otherwise complain.  The string
 *      "infinity" (regardless of case) is accepted as a legal value.
 *
 *      @param line            The line to be parsed.
 *
 */
//=============================================================================
/* virtual */
void conf<int>::parseValue(char const*& lines)
{
  if (!lines || !*lines) {
    LOG(Configuration error) << '"' << name() << "\" has no value" << endl;
    return;
  }

  char const* line = next_token_line(lines, " \t\r");
  if (!strncasecmp(line, "infinity", 8)) {
    operator =(INT_MAX);
    return;
  }
  int const n = ::atoi(line);
  if (n || *line == '0') {
    operator =(n);
    return;
  }
  LOG(Configuration error) << '"' << name() << "\" has a non-numeric value" << endl;
}

} // namespace IXE
