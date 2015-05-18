/*
**  DeSR
**  src/IPipe.h
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

#ifndef Tanl_IPipe_H
#define Tanl_IPipe_H

#include "Enumerator.h"

namespace Tanl {
/**
 *	@ingroup parser
 *
 *	IPipe interface.
 *	Provides way to connect Enumerators in a pipeline.
 */
template <class Tin, class Tout = Tin>
struct IPipe {
  virtual Enumerator<Tout>*	pipe(Enumerator<Tin>&) = 0;
  virtual ~IPipe() { }
};

} // namespace Tanl

#endif // Tanl_IPipe_H
