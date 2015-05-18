/*
**  DeSR
**  src/Serializable.h
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

#ifndef DeSR_Serializable_H
#define DeSR_Serializable_H

#include <iostream>

namespace Parser {

/**
 *	@ingroup parser
 *
 *	Serializable interface.
 */
struct Serializable
{
  /** Serializes the object to the stream.
      @return the stream. */
  virtual void serialize(std::ostream& stream) = 0;

};

} // namespace Parser

#endif // DeSR_Serializable_H
