/*
**  DeSR
**  src/Enumerator.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2005  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef Tanl_Enumerator_H
#define Tanl_Enumerator_H

namespace Tanl {

/**
 *	@ingroup parser
 */
struct Disposable {
  /** Used for cleanup, e.g. when embedded in SWIG proxies. */
  virtual void Dispose() {}
};

/**
 *	@ingroup parser
 *
 *	Enumerator interface.
 */
template <class T>
class Enumerator : public Disposable
{
public:
  typedef T		ItemType;

  /** Advances to the next element of the collection.
      @return true if there is another item available. */
  virtual bool		MoveNext() = 0;

  /** @return the current element. */
  virtual ItemType	Current() = 0;

  /**	Optional reset to the beginning of the enumeration. */
  virtual void		Reset() {}

  virtual ~Enumerator() {}
};

} // namespace Tanl

#endif // Tanl_Enumerator_H
