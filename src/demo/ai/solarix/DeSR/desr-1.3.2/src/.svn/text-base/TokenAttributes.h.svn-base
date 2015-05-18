/*
**  DeSR
**  src/TokenAttributes.h
** ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
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

#ifndef DeSR_TokenAttributes_H
#define DeSR_TokenAttributes_H

// local

// library
#include "text/WordIndex.h"
#include "include/error.h"

// standard
#include <vector>
#include <sstream>

namespace Tanl {

typedef unsigned	AttributeId;

/**
 *	@ingroup parser
 *
 *	Associates to an attribute name the index of its value in a attribute vector.
 */
struct AttributeIndex : public Text::WordIndex
{
  std::vector<char const*>	names;

  /**
   *	Inserts a key in the index.
   *	@return the AttributeId for the key.
   */
  AttributeId	insert(const char* name);

  AttributeIndex& operator =(AttributeIndex const& ai);

  ~AttributeIndex();
};

std::ostream& operator <<(std::ostream& os, AttributeIndex const& ai);

/**
 *	@ingroup parser
 *
 *	Represents the attributes of a token.
 *	It behaves similarly to hash_map<char const*, string>, but it uses
 *	an internal map @c attributeIndex to provide access to attributes
 *	by name, which can be shared by tokens from the same corpus.
 */
struct Attributes
{
  typedef std::string		Attribute;

  AttributeIndex*		attributeIndex;
  std::vector<Attribute>	values;

  static AttributeIndex*	emptyAttrIndex;

  Attributes(AttributeIndex* attributeIndex);

  Attributes(AttributeIndex* attributeIndex, std::vector<Attribute>& values);

  Attribute& operator [](int i) { return values[i]; }

  bool operator ==(const Attributes& other) {
    return attributeIndex == other.attributeIndex &&
      values == other.values;
  }

  bool operator !=(const Attributes& other) { return !(*this == other); }

  struct const_iterator {
    const_iterator(Attributes const& attributes, int fit = 0) :
      attributes(attributes),
      fit(fit)
    { }

    bool operator ==(const const_iterator& other) {
      return &attributes == &other.attributes && fit == other.fit;
    }
    bool operator !=(const const_iterator& other) { return !(*this == other); }
    const_iterator& operator ++() { fit++; return *this; }
    const_iterator operator ++(int) { // postincrement
      const_iterator tmp = *this;
      ++*this;
      return tmp;
    }

    // can't use string& since pair<> constructor uses reference parameters.
    std::pair<char const*, std::string const*> operator*() {
      std::string const& val = attributes.values[fit];
      return std::make_pair(attributes.attributeIndex->names[fit], &val);
    }

    Attributes const& attributes;
    int fit;
  };

  const_iterator begin() const { return const_iterator(*this); }
  const_iterator end() const { return const_iterator(*this, values.size()); }

  /**
   *	Get the value of attribute with name @c name.
   */
  std::string const* get(std::string const& name) const {
    AttributeId id = attributeIndex->index(name.c_str());
    return (id == Text::WordIndex::None) ? 0 : &values[id];
  }

  /**
   *	Get the value of attribute with name @c name.
   */
  std::string const* get(char const* name) const {
    AttributeId id = attributeIndex->index(name);
    return (id == Text::WordIndex::None) ? 0 : &values[id];
  }

  /**
   *	Get the AttributeId for key @c key or WordIndex::None if not present.
   */
  AttributeId	index(char const* key) const {
    return attributeIndex->index(key);
  }

  /**
   *	Insert a new attribute with key @c key and value @c value.
   */
  void insert(char const* key, char const* value) {
    AttributeId id = attributeIndex->insert(key); // get an ID for key
    if (id >= values.size())
      values.resize(id + 1);
    values[id] = value;
  }

  /**
   *	Insert a new attribute with key @c key and value @c value.
   */
  void insert(char const* key, std::string const& value) {
    AttributeId id = attributeIndex->insert(key); // get an ID for key
    if (id >= values.size())
      values.resize(id + 1);
    values[id] = value;
  }

  /**
   *	Insert a new attribute with key @c key and value @c value.
   */
  void insert(char const* key, int value) {
    AttributeId id = attributeIndex->insert(key); // get an ID for key
    if (id >= values.size())
      values.resize(id + 1);
    std::ostringstream oss;
    oss << value;
    values[id] = oss.str();
  }
};

} // namespace Tanl

#endif // DeSR_TokenAttributes_H
