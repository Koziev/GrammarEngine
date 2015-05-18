/*
**	Tanl
**	text/RegExp.h:  regular expression matcher
** ----------------------------------------------------------------------
**	Copyright (c) 2003  Giuseppe Attardi (attardi@di.unipi.it).
** ----------------------------------------------------------------------
**
**  This file is part of Tanl.
**
**  Tanl is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  Tanl is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

#ifndef Tanl_Text_RegExp_h
#define Tanl_Text_RegExp_h

// Local
#include "text/text.h"
#include "text/pcre/pcre.h"

// Standard
#include <string>
#include <vector>
#include <stdexcept>

namespace Tanl {
namespace Text {
  /**
   *	Regular Expression matching.
   */
namespace RegExp {

class RegExpException : public std::runtime_error {
    public:
    RegExpException(std::string const& msg) : std::runtime_error(msg) {}
};

enum CompileFlags
{
  IgnoreCase    = PCRE_CASELESS,
  NoNewLine     = PCRE_MULTILINE,
  DotAll        = PCRE_DOTALL,
  Extended      = PCRE_EXTENDED,
  Anchored      = PCRE_ANCHORED,
  DollarEndOnly = PCRE_DOLLAR_ENDONLY,
  Extra         = PCRE_EXTRA,
  UnGreedy      = PCRE_UNGREEDY,
  Utf8          = PCRE_UTF8
};

enum EvaluateFlags {
  NotBol        = PCRE_NOTBOL,
  NotEmpty      = PCRE_NOTEMPTY,
  NotEol        = PCRE_NOTEOL
  //  Anchored      = PCRE_ANCHORED // also an EvaluateFlag
};

/** 
 *	Holds the offsets of matching regular expressions
 */
class MatchGroups : std::vector<int>
{
public:
  MatchGroups(int size) :
    std::vector<int>(3 * size, -1)
  { }

  /**
   *	@return the number of matches found.
   */
  size_t size() { return std::vector<int>::size() / 3; }

  /**
   *	Resize the group.
   */
  void	resize(size_type s) { std::vector<int>::resize(s * 3, -1); }

  /**
   *	Access indidual matches, consisting of a pair of integer positions
   *	<start, end>.
   */
  std::pair<int, int>& operator [](int i) {
    return *(std::pair<int, int>*)&std::vector<int>::operator[](2 * i); }
};

/** 
 *  Regular Expression matching.
 *
 *  A pattern is compiled from a regular expression and used in matching.
 *  Regular expressions are written using the Perl 5 syntax.
 *
 *  A simple use for testing whether a string matches a pattern is:
 *
 *  <pre>
 *      Pattern p("a*b");
 *      bool b = p.test("aaab");
 *  </pre>
 *  In order to extract the portions of the string that match,
 *  @c MatchGroups can be used:
 *  <pre>
 *      Pattern p("(a*)b");
 *      MatchGroups m(2);
 *      string s("daaab");
 *      int n = p.matches(s, m);
 *  </pre>
 *  @c n is the number of groups matched: group 0 represents the substring
 *  captured by the whole pattern.
 */
class Pattern
{
private:
  int		_errorCode; 	///< stores the POSIX-error Code
  pcre*		_pcre; 
  pcre_extra*	_pcre_extra;

  /**
   *	Number of capturing subexpressions
   */
  int		subpatterns;

public:

  Pattern() { }

  /** 
   *	@param expression the regular expression
   *	@param cflags a combination of CompileFlags
   *
   *	NOTE. The ISO Latin-15 locale is used by default: ensure that the
   *	locale files for LC_CTYPE=en_US.iso885915 are installed in the OS.
   *	This can be changed using SetLocale().
   */
  Pattern(std::string const& expression, int cflags = 0);

  /** 
   *	@param expression the regular expression
   *	@param cflags a combination of CompileFlags
   *
   *	NOTE. The ISO Latin-15 locale is used by default: ensure that the
   *	locale files for LC_CTYPE=en_US.iso885915 are installed in the OS.
   *	This can be changed using SetLocale().
   */
  Pattern(char const* expression, int cflags = 0);

  /**
   *	Copy constructor. Use pcre_refcount() to avoid freeing twice _pcre.
   */
  Pattern(Pattern const& other) {
    _errorCode = other._errorCode;
    _pcre = other._pcre;
    if (_pcre)
      pcre_refcount(_pcre, 1);
    _pcre_extra = other._pcre_extra;
    subpatterns = other.subpatterns;
  }

  ~Pattern();

  /**
   *	Assignement. Use pcre_refcount() to avoid freeing twice _pcre.
   */
  Pattern& operator =(Pattern const& other) {
    if (this != &other) {
      _errorCode = other._errorCode;
      _pcre = other._pcre;
      if (_pcre)
	pcre_refcount(_pcre, 1);
      _pcre_extra = other._pcre_extra;
      subpatterns = other.subpatterns;
    }
    return *this;
  }

  /**
   *	Tests if the pattern matches at given string @a str.
   *	@param str the string to match.
   *	@param eflags any combinations of EvaluateFlags
   *	@return true if matches
  */
  bool		test(std::string const& str, int eflags = 0) const;

  /**
   *	Tests if the pattern matches at given string @a str, within
   *	the given length @a len.
   *	@param str the string to match.
   *	@param len the length of the string to match.
   *	@param eflags any combinations of EvaluateFlags
   *	@return true if matches
  */
  bool		test(char const* str, size_t len = 0, int eflags = 0);

  /**
   *    compute the size of the match.
   *	@param text the text to match.
   *	@param eflags any combinations of EvaluateFlags.
   *    @return 0 if not matching, otherwise the size of the match
   */
  int		matchSize(std::string const& text, int eflags = 0);
  /**
   *	Matches the text between @a start and @a end and
   *    returns the matching positions in @a pos, expressed as
   *	byte-offset from @a start.
   *	@param start start of the text to match.
   *	@param end end of the text to match.
   *	@param pos the identified matching positions.
   *	@param eflags any combinations of EvaluateFlags
   *    @return 0 if not matching, otherwise the count of matched expressions.
   */
  int		match(const char* start, const char* end,
		      MatchGroups& pos, int eflags = 0);
  /**
   *	Matches the text in @a text and
   *    returns the matching positions in @a pos, expressed as
   *	adjusted character offset (not byte-offset of the UTF8-Stream).
   *	@param text the string to match.
   *	@param pos the identified matching positions.
   *	@param eflags any combinations of EvaluateFlags
   *    @return 0 if not matching, otherwise the count of matched expressions.
   */
  int		match(std::string const& text, MatchGroups& pos, int eflags = 0);
  /**
   *
   *	@param str the text to match.
   *	@param eflags any combinations of EvaluateFlags
   *	@return an vector<string>: [0] substring matched
   *				    [1 - n] sub expression with '()'
   */
  std::vector<std::string> match(std::string const& str, int eflags = 0);

  /**
   *	Replaces the first substring matching the expression within
   *	@a text with the string @a rewrite.
   *	If @a replaceAll is true, all occurrences are replaced.
   *	Within @a rewrite, backslash-escaped digits (\1 to \9)
   *	can be used to insert text matching corresponding parenthesized
   *	group from the pattern.  \0 in "rewrite" refers to the entire
   *	matching text.  E.g.,
   *
   *	<pre>
   *	string s = "yabba dabba doo";
   *	RegExp::Pattern("b+").replace(s, "d");
   *	</pre>
   *
   *	returns "yada dabba doo".  The result is undefined if @a rewrite
   *	contains wrong pattern references.
   */
  std::string	replace(std::string const& text, std::string const& rewrite, bool replaceAll = false);

  /**
   *	Same as @see replace, except that modifies the string @c text.
   *	@returns whether the string was changed.
   */
  bool		modify(std::string& text, std::string const& replwith, bool replaceAll = false);

  /**
   *	Escapes all meta characters
   */
  static std::string	escape(std::string& str);

  /**
   *	Set the locale for use during matching.
   *	Use "en_US.iso885915" or similar for recognizing ISO Latin-15 letters.
   */
  static const unsigned char*	setLocale(char const* locale);

  /**	The current chartable to use for matching */
  static const unsigned char* CharTables;
};

} // namespace RegExp
} // namespace Text
} // namespace Tanl

#endif // Tanl_Text_RegExp_h
