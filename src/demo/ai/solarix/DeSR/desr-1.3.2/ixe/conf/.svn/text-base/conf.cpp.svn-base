/*
**  IXE C++ Library
**  ixe/conf/conf.cpp
**  ----------------------------------------------------------------------
**  Copyright (c) 2000  Ideare SpA.
**  Copyright (c) 2000  Giuseppe Attardi (attardi@di.unipi.it).
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

// Settings
#include "conf/conf.h"

// standard
#include <cctype>
#include <cstring>
#include <iostream>

// local
#include "include/config.h"	// ConfigFileDefault
#include "io/mappedFile.h"
#include "Common/util.h"
#include "conf/conf_bool.h"	// so we can declare verbosity

using namespace std;
using namespace IXE::io;

namespace IXE {

/** Whether to report errors in config. file. */
conf<bool>	VerboseConfig("VerboseConfig", false);

//=============================================================================
/**
 *      Define and initialize (exactly once) a static data member for Conf
 *      and return a reference to it.  The reason for this function is to
 *      guarantee that the map is initialized before its first use across all
 *      translation units, something that would not guaranteed if it were a
 *      static data member initialized at file scope.
 *
 *      @return		a reference to a static instance of an initialized Params.
 *
 * @see
 *      Margaret A. Ellis and Bjarne Stroustrup.  "The Annotated C++
 *      Reference Manual."  Addison-Wesley, Reading, MA, 1990.  p. 19.
 */
//=============================================================================

Configuration::Params& Configuration::variables()
{
  static Params    m;
  return m;
}

Configuration::Configuration(Params& params) :
  params(params)
{ }

void Configuration::insert(Item* var)
{
  variables()[var->name()] = var;
}

//=============================================================================

void Configuration::load(char const* file_name)
{
  try {
    mappedFile conf_file(file_name);

    register int line_no = 0;
    register mappedFile::const_iterator c = conf_file.begin(), nl = c;

    while (c != conf_file.end() && nl != conf_file.end()) {
      if (!(nl = ::strchr(c, '\n')))
        //
        // We can't find a "line," i.e., a sequence of
        // characters terminated by a newline, so stop.
        //
        break;
      ++line_no;
      //
      // See if the line is entirely whitespace optionally followed
      // by a comment starting with '#': if so, skip it.  If we don't
      // end up skipping it, leading whitespace will have been skipped.
      //
      while (c != nl && isspace((unsigned char)*c))
        ++c;
      if (c == nl || *c == '#')
        c = nl + 1;
      else if (c != nl) {
        //
        // The line has something on it worth parsing further
	string line(c, nl-c-1);	// except last
	// combine continuation lines
	while (nl[-1] == '\\') {
	  line += ' ';
	  c = nl+1;
	  nl = ::strchr(c, '\n');
	  if (nl) {
	    ++line_no;
	    line.append(c, nl-c);
	  } else
	    break;
	}
	line += nl[-1];
        parseLine(line.c_str(), line_no);
	c = nl+1;
      }
    }
  } catch (MmapError&) {
    if (!::strcmp(file_name, ConfigFileDefault))
      //
      // The configuration file couldn't be opened; however,
      // the file name is the default, so assume that none is
      // being used and simply return.
      //
      LOG(error) << "could not read configuration from \""
		 << file_name << '"' << endl;
  }
}

void Configuration::load(istream& is, char const* close)
{
  int line_no = 0;
  string line;
  while (getline(is, line)) {
    if (line_no == 0) {
      // read version number
      size_t valStart = line.find("version='");
      if (valStart != string::npos) {
	valStart += strlen("version='");
	size_t valEnd = line.find("'", valStart);
	if (valEnd != string::npos) {
	  string versionNumber = line.substr(valStart, valEnd - valStart);
	  Params::const_iterator const v = params.find("Version");
	  if (v != params.end()) {
	    char const* value = versionNumber.c_str();
	    v->second->parseValue(value);
	  }
	}
      }
    }
    ++line_no;
    if (line.size() == 0)
      continue;
    if (line == close)		// stop at close tag
      return;
    // combine multiple lines
    while (line.size() && line[line.size() - 1] == '\\') {
      line[line.size() - 1] = ' ';
      ++line_no;
      string cont;
      if (getline(is, cont))
	line += cont;
    }
    char const* c = line.c_str();
    char const* end = c + line.size();
    // skip leading whitespace
    while (c != end && isspace((unsigned char)*c))
      ++c;
    // skip comments
    if (*c != '#' && *c != '\0') {
      // The line has something on it worth parsing further
      parseLine(c, line_no, params);
    }
  }
}

static inline void SKIP_EOL(char const*& x)
{
  if (x[0] == '\r') {
    ++x;
    if (x[0] == '\n') ++x;
  } else if (x[0] == '\n') {
    ++x;
    if (x[0] == '\r') ++x;
  }
}

// FIXME: include Mac \n\r sequence.
// (x)[1] always exists, because x is null terminated string.
#define EOL(x)	((x)[0] == '\n' || (x)[0] == '\r' && (x)[1] == '\n')
#define SKIP_EOL(x) { if ((x)[0] == '\r') ++(x); ++(x); }

char  const* next_token_line(char const*& ptr, const char* sep, char esc)
{
  // skip all letters that are included in the separator string
  // as well as newline preceded by esc character
  while (*ptr) {
    if (*ptr == esc && EOL(ptr+1)) {
	SKIP_EOL(++ptr);
    } else if (EOL(ptr))
      return 0;
    else if (strchr(sep, *ptr))
      ++ptr;
    else
      break;
  }

  if (*ptr) {
    // so this is where the next piece of string starts
    char const* start = ptr++;

    // scan through the string to find where it ends, it ends on a
    // null byte or a character that exists in the separator string
    while (*ptr && !EOL(ptr)) {
      if (*ptr == esc) {
	++ptr;
	if (*ptr)
	  ++ptr;
      } else if (strchr(sep, *ptr))
	break;
      else
	++ptr;
    }
    if (ptr == start)		// no tokens on this line
      return 0;
    return start;		// return the position where the string starts
  }

  // we ended up on a null byte, there are no more strings to find!
  return 0;
}


//=============================================================================
/**
 *      Parse a non-comment or non-blank line from a the configuration file,
 *      the first word of which is the variable name.
 *	Look up the variable in our map and delegate the parsing of the
 *	rest of the line to an instance of a derived class that
 *	knows how to parse its own line format.
 *
 *      @param line            A line from a configuration file to be parsed.
 *      @param line_no         The line number of the line.
 */
//=============================================================================

void Configuration::parseLine(char const* line, int line_no, Params& params)
{
  char const* varstart = next_token_line(line, " \r\t"); // just the variable name
  char var[256];
  int len = line - varstart;
  ::strncpy(var, varstart, len);
  var[len] = '\0';
  char const* start = line;
  Params::const_iterator const v = params.find(var);
  if (v == params.end()) {
    if (VerboseConfig)
      LOG(warning) << '"' << line << "\" at " << line_no << " in config. file unrecognized; ignored\n";
  } else {
    //
    // Remove leading whitespace from value and then parse each line
    // in a series, where \ is a continuation mark
    //
    while (*line && line[0] != '\n' && isspace((unsigned char)*line))
      ++line;
    if (line[0] != '\n')
      v->second->parseValue(line);
  }
  // skip to next line
  char const* endline = ::strpbrk(line, "\n\r");
  if (endline) {
    line = endline;
    SKIP_EOL(line);
  }
}

//=============================================================================

void Configuration::serialize(ostream& os)
{
  FOR_EACH (Params, params, vit)
    vit->second->serialize(os);
}

//=============================================================================

void Configuration::reset()
{
  TO_EACH (Params, variables(), v)
    v->second->reset();
}

} // namespace IXE
