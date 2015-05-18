/*
**  DeSR
**  src/PosTaggerStub.cpp
**  ----------------------------------------------------------------------
**  Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
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

#include "PosTagger.h"

namespace Parser {

/**
 * Stub version of PosTagger, to replace the real PosTagger when not needed.
 */

PosTagger::PosTagger(char const* PosParameters)
{
}

bool PosTagger::tag(Tagged& sentence)
{
  return false;
}

PennPosTagger::PosMap		PennPosTagger::posMap;

PennPosTagger::PennPosTagger(const char* PosParameters) :
  PosTagger(PosParameters)
{
}

bool PennPosTagger::tag(Tagged& sentence)
{
  return false;
}

} // namespace TreeTagger

