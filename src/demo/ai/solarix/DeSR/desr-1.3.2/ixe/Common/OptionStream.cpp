/*
**  IXE C++ Library
**  ixe/OptionStream.cpp
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
#include "Common/OptionStream.h"

// standard
#include <algorithm>		/* for copy() */
#include <cstring>
#include <iterator>

// local

#define	ERROR	os.err << os.argv[0] << ": error: option "

namespace IXE {
using namespace std;

/**
 *	Print usage message on @param err.
 */
ostream&
Options::usage(Options::spec const options[], ostream& err)
{
  err << "options: (unambiguous abbreviations accepted)\n"
    "========\n";
  for (Options::spec const* opt = options; *(int*)opt; opt++)
    err << opt->use_msg << endl;
 return err;			// just to make the compiler happy
}

//=============================================================================
/**
 *
 *      Copy an OptionStream to ourselves.  This is a utility function for the
 *      copy constructor and assignment operator.
 *
 *      @param o       The OptionStream to copy from.
 */
//=============================================================================

void
OptionStream::Option::copy(Option const &o)
{
  c = o.c;
  _arg = ::strdup(o._arg);
  am_copy = true;
}

//=============================================================================
/**
 *
 *      Construct (initialize) an OptionStream.
 *
 *      @param argc    The number of arguments.
 *      @param argv    A vector of the arguments; argv[argc] is null.
 *      @param specs   A vector of option specifications, i.e., the options that are
 *              allowed and their argument parameters.
 *      @param err     The ostream to emit error messages to.
 */
//=============================================================================

OptionStream::OptionStream(int argc, char* argv[],
			   Options::spec const specs[], ostream& err)
  : argc(argc), argv(argv), specs(specs), err(err),
    index(0), next_c(0), end(false)
{ }

//=============================================================================
/**
 *
 *      Parse and extract an option from an option stream (argv values).
 *      Options begin with either a '-' for short options or a "--" for long
 *      options.  Either a '-' or "--" by itself explicitly ends the options;
 *      however, the difference is that '-' is returned as the first non-option
 *      whereas "--" is skipped entirely.
 *
 *      When there are no more options, the OptionStream converts to bool as
 *      false.  The OptionStream's shift() member is the number of options
 *      parsed which the caller can use to adjust argc and argv.
 *
 *      Short options can take an argument either as the remaining characters
 *      of the same argv or in the next argv unless the next argv looks like an
 *      option by beginning with a '-').
 *
 *      Long option names can be abbreviated so long as the abbreviation is
 *      unambiguous.  Long options can take an argument either directly after a
 *      '=' in the same argv or in the next argv (but without an '=') unless
 *      the next argv looks like an option by beginning with a '-').
 *
 *      @param os      The OptionStream to extract options from
 *      @param o       The option to deposit into.
 *      @return	       The passed-in OptionStream.
 *
 */
//=============================================================================

OptionStream&
operator >>(OptionStream& os, OptionStream::Option& o)
{
  char* arg;
  register Options::spec const* s, *found = 0;

  o.c = '\0';

  if (os.next_c && *os.next_c) {
    //
    // We left off within a grouped set of short options taking no
    // arguments, i.e., instead of -a -b -c, the user did -abc and
    // next_c points to a character past 'a'.
    //
    arg = os.next_c;
    goto short_option;
  }

  if (++os.index >= os.argc)	// no more arguments
    goto the_end;
  arg = os.argv[os.index];
  if (!arg || *arg != '-' || !*++arg)	// no more options
    goto the_end;

  if (*arg == '-') {
    if (!*++arg) {			// "--": end of options
      ++os.index;
      goto the_end;
    }

    //
    // Got the start of a long option: find the last character of
    // its name.
    //
    char* end;
    for (end = arg; *end && *end != '='; ++end);

    //
    // Now look through the options table for a match.
    //
    for (s = os.specs; s->long_name; ++s) {
      int const len = end - arg;
      if (::strncmp(arg, s->long_name, len))
	continue;
      if (::strlen(s->long_name) == len)
	{
	  found = s;	// exact match
	  break;
	}
      if (!found)
	{
	  found = s;	// partial match
	  continue;
	}
      ERROR << '"';
      std::copy(arg, end, std::ostream_iterator<char>(os.err, ""));
      os.err << "\" is ambiguous\n";
      return os;
    }
    if (!found) {
      ERROR << '"';
      std::copy(arg, end, std::ostream_iterator<char>(os.err, ""));
      os.err << "\" unrecognized\n";
      return os;
    }

    //
    // Got a long option: now see about its argument.
    //
    arg = 0;
    switch (found->arg_type) {

    case Options::no_arg:
      if (*end == '=') {
	  ERROR << '"' << found->long_name << "\" takes no argument\n";
	  goto set_arg;
	}
      break;

    case Options::req_arg:
    case Options::opt_arg:
      if (*end == '=') {
	arg = ++end;
	break;
      }
      if (++os.index >= os.argc)
	break;
      arg = os.argv[os.index];
      if (*arg == '-') {
	//
	// The next argv looks like an option
	// so assume it is one and that there
	// is no argument for this option.
	//
	arg = 0;
      }
      break;

    default:
      goto bad_spec;
    }

    if (!arg && found->arg_type == Options::req_arg)
      ERROR << '"' << found->long_name << "\" requires an argument\n";
    else
      o.c = found->c;

    goto set_arg;
  }

short_option:
  //
  // Got a single '-' for a short option: look for it in the specs.
  //
  for (s = os.specs; s->c; ++s)
    if (*arg == s->c) {
      found = s;
      break;
    }
  if (!found) {
    ERROR << '"' << *arg << "\" unrecognized\n";
    return os;
  }

  //
  // Found the short option: now see about its argument.
  //
  switch (found->arg_type) {

  case Options::no_arg:
    //
    // Set next_c in case the user gave a grouped set of
    // short options (see the comment near the beginning)
    // so we can pick up where we left off on the next
    // call.
    //
    os.next_c = arg + 1;
    arg = 0;
    break;

  case Options::req_arg:
  case Options::opt_arg:
    //
    // Reset next_c since an option with either a required
    // or optional argument terminates a grouped set of
    // options.
    //
    os.next_c = 0;

    if (!*++arg) {
	//
	// The argument, if any, is given in the next
	// argv.
	//
	if (++os.index >= os.argc)
	  break;
	arg = os.argv[os.index];
	if (*arg == '-') {
	  //
	  // The next argv looks like an option
	  // so assume it is one and that there
	  // is no argument for this option.
	  //
	  arg = 0;
	}
      }
    break;

  default:
    goto bad_spec;
  }

  if (!arg && found->arg_type == Options::req_arg)
    ERROR << '"' << found->c << "\" requires an argument\n";
  else
    o.c = found->c;

set_arg:
  o._arg = arg;
  return os;
the_end:
  os.end = true;
  return os;
bad_spec:
  ERROR << "invalid option argument spec: " << found->arg_type << '\n';
  ::abort();
  return os;			// make compiler happy
}

} // namespace IXE

//=============================================================================
//**

#ifdef TEST_OPTIONSTREAM

using namespace IXE;

int
main(int argc, char *argv[])
{
  static Options::spec const spec[] = {
    "no-arg", 0, 'n',
    "req-arg", 1, 'r',
    "opt-arg", 2, 'o',
    0,
  };
  OptionStream opt_in(argc, argv, spec);
  OptionStream::Option opt;
  while (opt_in >> opt) {
    switch (opt) {
    case 'n':
      cout << "got --no-arg\n";
      break;
    case 'r':
      cout << "got --req-arg=" << opt.arg() << '\n';
      break;
    case 'o':
      cout << "got --opt-arg=";
      cout << (opt.arg()? opt.arg() : "(null)") << endl;
      break;
    default:
      cout << "got weird=" << (int)(char) opt << '\n';
    }
  }
  cout << "shift=" << opt_in.shift() << '\n';

  argc -= opt_in.shift();
  argv += opt_in.shift();

  cout << "argc=" << argc << endl;
  cout << "first non-option=" << (argv[0] ? argv[0] : "(null)") << endl;
}

#endif /* TEST_OPTIONSTREAM */
