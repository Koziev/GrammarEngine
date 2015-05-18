/*
**  Tanl C++ Library
**  ixe/text/less.h
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

#ifndef	Tanl_Text_less_H
#define	Tanl_Text_less_H

// Settings
#include "platform.h"

// standard
#include <cstring>
#include <functional>

namespace std
{
/**
 *	Specialize the binary_function "less" so that C-style strings (char
 *	const*) will work properly with STL containers.
 *
 *	@see std::binary_function, std::less, strcmp(3)
 *
 *	Bjarne Stroustrup.  "The C++ Programming Language, 3rd ed."
 *	Addison-Wesley, Reading, MA, 1997.  p. 468.
 *
 */
  template <> struct less<char const*> :
  std::binary_function<char const*, char const*, bool>
  {
    result_type
    operator ()(first_argument_type a, second_argument_type b) const {
      return ::strcmp(a, b) < 0;
    }
  };
}

#endif	/* Tanl_Text_less_H */
