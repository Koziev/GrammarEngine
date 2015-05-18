/*
**  IXE C++ Library
**  ixe/include/Set.h
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

#ifndef IXE_Set_H
#define IXE_Set_H

// Settings
#include "platform.h"

// standard
#include <set>
#include <string>

// local
#include "text/less.h"

namespace IXE {

/**
 *
 *	A Set is a set but with the addition of a contains() member
 *	function, one that returns a simpler bool result indicating whether a
 *	given element is in the set.
 *
 */

template <class T> class Set : public std::set<T>
{
public:
	bool contains(T const &s) const { return this->find(s) != this->end(); }
};

/**
 *
 *	Specialize Set for C-stle strings so as not to have a reference
 *	(implemented as a pointer) to a char const*.
 *
 */

template <> class Set<char const*> : public std::set<char const*>
{
public:
	bool contains(char const *s) const { return find(s) != this->end(); }
};

typedef Set<char const*>	chars_set;

} // namespace IXE

#endif	/* IXE_Set_H */
