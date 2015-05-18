/*
**  DeSR
**  MaxEntropy/model/EventStream.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef ME_EventStream_H
#define ME_EventStream_H

#include <iostream>
#include <string>
#include "maxent.h"

namespace ME {

/**
 *	A stream of training events.
 */
class EventStream
{
public:

  virtual bool		hasNext() = 0;
  virtual Event*	next() = 0;

  /**
   * @return the string representation of event outcomes
   */
  char const**	outcomes() { return outcomeLabels; }

private:
  char const* outcomeLabels[];	// outcomeID -> original string of outcome
};

}
#endif // ME_EventStream_H
