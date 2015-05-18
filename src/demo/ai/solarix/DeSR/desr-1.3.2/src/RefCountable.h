/*
**  DeSR
**  src/RefCountable.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef Tanl_RefCountable_H
#define Tanl_RefCountable_H

namespace Tanl {

/**
 *	@ingroup parser
 */
struct RefCountable {
  RefCountable()  :
    refCount(0)
  { }

  unsigned	refCount;
  unsigned	incRef() { return ++refCount; }
  unsigned	decRef() {
    if (--refCount == 0) { delete this; return 0; }
    else return refCount;
  }
};

} // namespace Tanl

#endif // Tanl_RefCountable_H
