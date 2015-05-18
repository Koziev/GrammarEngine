/*
**	DeSR
**	conf_Replacements.h
** ----------------------------------------------------------------------
**	Copyright (c) 2010  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef Parser_conf_Replacements_H
#define Parser_conf_Replacements_H

// standard
#include <vector>

// library
#include "conf/conf.h"
#include "text/RegExp.h"

using namespace Tanl::Text;

namespace IXE {

/**
 *	Extension of RegExp::Pattern that stores original pattern for serialization.
 */
class Pattern2 : public RegExp::Pattern
{
public:
  Pattern2() { }
  Pattern2(std::string& pattern, int cflags = 0) :
    RegExp::Pattern(pattern, cflags),
    pattern(pattern)
  { }

  /**
   *	Assignement.
   */
  Pattern2& operator =(Pattern2 const& other) {
    if (this != &other) {
      this->Pattern::operator=(other);
      pattern = other.pattern;
    }
    return *this;
  }

  std::string pattern;
};

/**
 *	@ingroup configuration
 *
 *	A conf_Replacements contains pairs of (RegExp::Pattern, replacement).
 *	The replacement string may contain backslash references (\0 ... \9)
 *	to refer to portions matched by Pattern.
 *
 */

typedef std::vector<std::pair<Pattern2, std::string> > Replacements;

// Required dummy specialization.
template<>
inline void Var<Replacements>::serialize(std::ostream& os) { }

template<>
class conf<Replacements> : public Var<Replacements>
{
public:

  conf<Replacements>(char const* name, Configuration::Params& params = Configuration::variables()) : Var<value_type>(name, params) { }

protected:
  /**
   *      Parse the line of text by splitting it into words that are separated
   *      by whitespace.
   *
   *      @param line            The line of text to be parsed.
   */
  virtual void		parseValue(char const*& line) {
    char const* tok = next_token_line(line, " \r\t");
    std::string pattern(tok, line - tok);
    while ((tok = next_token_line(line, " \r\t")))
      value.push_back(std::make_pair(Pattern2(pattern, RegExp::Anchored), std::string(tok, line - tok)));
  }
  virtual void		reset() { }

  void serialize(std::ostream& os)
  {
    FOR_EACH (Replacements, value, fit)
      os << name() << "\t\"" << fit->first.pattern << "\" " << fit->second << std::endl;
  }

};

} // namespace IXE

#endif	/* Parser_conf_Replacements_H */
