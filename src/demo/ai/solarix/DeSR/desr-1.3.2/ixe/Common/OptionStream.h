/*
**  IXE C++ Library
**  ixe/OptionStream.h
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

#ifndef	IXE_OptionStream_H
#define	IXE_OptionStream_H

// Settings
#include "platform.h"

// standard
#include <iostream>

namespace IXE {

using namespace std;

/**
 *	Options describes a set of command-line options.
 */

struct Options
{
  enum {
    no_arg	= 0,
    req_arg	= 1,
    opt_arg	= 2
  };

  struct spec {
    //
    // A spec gives a specification for an option: its long name,
    // its argument type, and it's short option equivalent.  A
    // null-terminated array of specs is given to the OptionStream
    // constructor.
    //
    // The arg_type takes on one of the above enum values, but is
    // not declared as an enum to allow the integer values to be
    // used as a shorthand.
    //
    // Regardless of whether the user enters a long or a short
    // option, it is the short option character that is returned to
    // the caller in order to be able to use a simple switch
    // statement to do different things depending on the option.
    //
    // If, for a given long option there is to be no short option
    // equivalent, then the caller has to make up bogus ones that
    // the user will never type.  Either the ASCII control or high
    // characters can be user for this.  The null character may not
    // be used.
    //

    char const*		long_name;
    short		arg_type;
    unsigned char	c;
    char const*		use_msg;
  };

  static ostream&	usage(spec const options[], ostream& err);
};

/**
 *	Given the traditional argc and argv for command-line arguments, extract
 *	options from them following the stream model.
 *
 * RATIONALE
 *
 *	Why not use the standard getopt() or GNU's getopt_long()?  Because
 *	neither are thread-safe and I needed a thread-safe version.
*/

class OptionStream
{
public:
	OptionStream(int argc, char* argv[], Options::spec const[], 
		     std::ostream& = std::cerr);

	int	shift() const		{ return index; }
	operator bool() const 		{ return !end; }

	class Option {
		//
		// An option is what is extracted from an OptionStream.  Its
		// operator char() gives which option it is and arg() gives its
		// argument, if any.  For options that do not have an argument,
		// arg() returns the null pointer.
		//
		// An option may be copied in which case it has a private copy
		// of its argument.
		//
	public:
		Option(char c = '\0', char* a = 0) :
			c(c), _arg(a), am_copy(false) { }
		Option(Option const& o) {
			if (&o != this) copy(o);
		}
		~Option() {
			if (am_copy) delete[] _arg;
		}
		Option& operator =(Option const &o) {
			if (&o != this) {
				if (am_copy) delete[] _arg;
				copy(o);
			}
			return *this;
		}

		char* arg() const	{ return _arg; }
		operator char() const	{ return c; }

		friend OptionStream& operator >>(OptionStream&, Option&);
	private:
		char	c;
		char* _arg;
		bool	am_copy;
		void	copy(Option const&);
	};

	friend OptionStream& operator >>(OptionStream&, Option&);
private:
	int		argc;
	char**		argv;
	Options::spec const*	specs;
	std::ostream&	err;
	int		index;
	char*		next_c;
	bool		end;
};

} // namespace IXE

#endif	/* IXE_OptionStream_H */
