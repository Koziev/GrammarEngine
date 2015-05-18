/*
**  DeSR
**  src/Attributes.cpp
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

#include "TokenAttributes.h"

// standard
#include <iostream>

// library
#include "Common/util.h"	// FOR_EACH

using namespace std;

namespace Tanl {

AttributeId AttributeIndex::insert(const char* name)
{
  AttributeId id = Text::WordIndex::insert(name);
  if (id >= names.size()) {
    // add new name to names
    names.resize(id + 1);
    names[id] = ::strdup(name);
  }
  return id;
}

AttributeIndex& AttributeIndex::operator =(AttributeIndex const& ai)
{
  Text::WordIndex::operator=(ai);
  for (unsigned i = 0; i < names.size(); i++)
    free((void*)names[i]);
  names.resize(ai.size());
  for (unsigned i = 0; i < ai.names.size(); i++)
    names[i] = strdup(ai.names[i]);
  return *this;
}

AttributeIndex::~AttributeIndex()
{
  for (unsigned i = 0; i < names.size(); i++)
    free((void*)names[i]);
}

ostream& operator <<(ostream& os, AttributeIndex const& ai)
{
  FOR_EACH (Tanl::Text::WordIndex, ai, it)
    os << '<' << it->first << ", " << it->second << "> ";
  return os << endl;
}

// ======================================================================

AttributeIndex* Attributes::emptyAttrIndex = new AttributeIndex();

Attributes::Attributes(AttributeIndex* attributeIndex) :
  attributeIndex(attributeIndex)
{
  if (attributeIndex)
    values.resize(attributeIndex->size());
  else
    this->attributeIndex = emptyAttrIndex;
}

Attributes::Attributes(AttributeIndex* attributeIndex, std::vector<Attribute>& values) :
  attributeIndex(attributeIndex),
  values(values)
{ }

} // namespace Tanl
