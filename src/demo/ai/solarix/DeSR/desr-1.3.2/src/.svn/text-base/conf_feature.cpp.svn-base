/*
**  DeSR
**  src/conf_feature.cpp
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

// local
#include "conf_feature.h"

// standard

//library
#include "Common/util.h"	// FOR_EACH

using namespace std;
using namespace IXE;
using namespace Tanl::Text;

namespace Parser {

FeatureSpec* FeatureSpec::parse(char const*& line)
{
  char const* st = next_token_line(line, " \t(");
  char const* attribute = strndup(st, line - st);
  // skip blanks
  line = next_token_line(line, " \t");
  if (!line || line[0] != '(') {
    cerr << "Missing '(' after attribute name in feature: " << attribute << line << endl;
    return 0;
  }
  TokenPath* path = TokenPath::parse(line);
  if (!path) {
    cerr << "Bad path for feature: " << attribute << line << endl;
    return 0;
  }
  if (!line || line[0] != ')') {
    cerr << "Missing ')' after feature: " << attribute << line << endl;
    return 0;
  }
  line++;
  FeatureSpec* fs = new FeatureSpec(attribute, path);
  // skip blanks
  st = next_token_line(line, " \t");
  if (st) {
    fs->next = FeatureSpec::parse(st);
  }
  return fs;
}

void FeatureSpec::serialize(std::ostream& os) const
{
  os << attribute << '(' << *path << ')';
  for (FeatureSpec* fs = next; fs; fs = fs->next)
    os << *fs;
}

////////////////////////////////////////////////////////////////////////////////
// conf_features

conf_features::FeatureIndex	conf_features::featureIndex;

void conf_features::add(FeatureSpecs* value, FeatureSpec* fs)
{
  // insert ordered (just for back compatibility, otherwise use push_back()).
  FeatureSpecs::iterator it = value->begin();
  while (it != value->end() && strcmp(fs->attribute, (*it)->attribute) >= 0)
    it++;
  value->insert(it, fs);
  if (!fs->next &&		// single feature
      featureIndex.find(fs->attribute) == featureIndex.end()) {
    featureIndex[fs->attribute] = 0;
    // renumber
    int i = 0;
    TO_EACH (FeatureIndex, featureIndex, fit)
      fit->second = i++;
  }
}

void conf_features::parseValue(char const*& line)
{
  FeatureSpec* fs = FeatureSpec::parse(line);
  if (fs)
    conf_features::add(&value, fs);
}

void conf_features::serialize(std::ostream& os)
{
  FOR_EACH (FeatureSpecs, value, fit)
    os << name() << '\t' << **fit << endl;
}

////////////////////////////////////////////////////////////////////////////////
// conf_single_features

void conf_single_features::parseValue(char const*& line)
{
  char const* st = next_token_line(line, " \r\t");
  char const* feature = strndup(st, line - st);
  TokenPath* tp;
  while ((tp = TokenPath::parse(line)))
    conf_features::add(value, new FeatureSpec(feature, tp));
}

} // namespace Parser
