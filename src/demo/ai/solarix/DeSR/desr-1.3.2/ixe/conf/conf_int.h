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

#ifndef conf_int_H
#define conf_int_H

// Settings
#include "platform.h"

// system
#include <climits>				/* for INT_MAX */
#include <string>

// local
#include "conf/conf.h"

namespace IXE {

/**
 *	@ingroup configuration
 *
 *	A conf<int> is a Var for containing the value of an integer
 *	configuration variable.
 *
 */

template <> class conf<int> : public VarDefault<int>
{
 public:
  /**
   *	@param name name of the configuration parameter.
   *	@param default_value	default value.
   *	@param min	minimum, value, default = 0.
   *	@param max	maximum valu, default = INT_MAX.
   */
  conf(char const *name, int default_value, int min, int max,
       Configuration::Params& params = Configuration::variables());

  conf(char const *name, int default_value, int min,
       Configuration::Params& params = Configuration::variables());

  conf(char const *name, int default_value,
       Configuration::Params& params = Configuration::variables());

  conf<int>&	operator =(int new_value);

  conf<int>&	operator =(char const* s) {
    parseValue(s);
    return *this;
  }

  conf<int>& operator ++() {
    ++value;
    return *this;
  }
  conf<int> operator ++(int) { // postfix
    conf<int> tmp = *this;
    ++value;
    return tmp;
  }
  conf<int>& operator --() {
    --value;
    return *this;
  }
  conf<int> operator --(int) { // postfix
    conf<int> tmp = *this;
    --value;
    return tmp;
  }

 protected:
  virtual void	parseValue(char const*& line);
 private:
  int const	min_, max_;
};

} // namespace IXE

#endif	/* conf_int_H */
