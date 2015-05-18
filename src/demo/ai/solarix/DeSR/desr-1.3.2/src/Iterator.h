/*
**  DeSR
**  src/Iterator.h
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

#ifndef DeSR_Iterator_H
#define DeSR_Iterator_H

namespace Parser {

/**
 *	@ingroup parser
 *
 *	Iterator interface.
 */
template <class T>
class Iterator
{
public:
  typedef T		ItemType;

  /** @return true if there is another item available */
  virtual bool		hasNext() = 0;

  /** @return the next item */
  virtual ItemType	next() = 0;

  /**	Remove the next item */
  virtual void		remove() {}

};

} // namespace Parser

#endif // DeSR_Iterator_H
