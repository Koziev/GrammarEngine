/*
**  IXE C++ Library
**  ixe/conf/conf.h
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

#ifndef IXE_conf_H
#define IXE_conf_H

// Settings
#include "platform.h"

// standard
#include <iostream>
#include <map>
#include <string>

// local
#include "text/less.h"

namespace IXE {

#define LOG(severity) std::clog << #severity << ": "

/**
 * 	@defgroup configuration Configuration
 *
 *	Classes that provide reading configuration settings
 *	from configuration files.
 */

/**
 *	@ingroup configuration
 *
 *	A Configuration object that holds all the configuration parameters.
 */

class Configuration
{

public:

  // Note that the declaration of std::map has a default "Compare"
  // template parameter of "less<key_type>" and, since we've included
  // less.h above that defines "less<char const*>", C-style string
  // comparisons work properly.
  //
  class Item;
  typedef std::map<char const*, Item*> Params;

  Configuration(Params& params = Configuration::variables());

  /**	Load configuration from file.
   *	Parse the lines in a configuration file setting parameters accordingly.
   *
   *	@param file_name       The name of the configuration file to parse.
   */
  static void		load(char const* file_name);

  /**	Load configuration from stream @param is.
   *	Reading stops at first line equal to closing tag @param close.
   *	Read only parameters listed in @c params.
   */
  void			load(std::istream& is,
			     char const* close = "</desr>");

  /**
   *	Dump configuration parameters to stream @param os, so that they can be
   *	loaded back.
   */
  virtual void		serialize(std::ostream& os);

  static Params&	variables();

  /**
   *      Reset all configuration parameters to their default values.
   */
  static void		reset();

  /** Map collecting all configuration parameters. */
  Params&		params;

private:
  static int		current_config_file_line_no;

  /**
   *	Add a parameter to a configuration object.
   */
  static void		insert(Item* var);

  /**
   *	Parse a non-comment or non-blank line from a the configuration file,
   *	the first word of which is the parameter name.
   *	Look up the parameter in our map and delegate the parsing of the
   *	rest of the line to an instance of a derived class that
   *	knows how to parse its own line format.
   *
   *	@param line            A line from a configuration file to be parsed.
   *	@param line_no         The line number of the line.
   */
  static void		parseLine(char const* line, int line_no,
				  Params& vars = variables());
public:

  /**
   *
   *	An Item is the abstract base class for all configuration parameters.
   *	It parses a given line and, based on the parameter name,
   *	which is the first word on the line, dispatches to an appropriate
   *	instance of a derived class to parse the rest of the line.
   *
   *	The parameter is added to a given Configuration Params or else to a
   *	global one.
   *
   */

  friend class Item;
  class Item
  {
  public:
    char const*	name() const { return name_; }

    virtual void serialize(std::ostream& os) {}

  protected:
    Item(char const* name, Params& params = variables()) : name_(name) {
      if (name)
	params[name] = this;
    }

    virtual		~Item() { };

    /**		Derived classes must define this to parse a line and
     *		set their value.
     */
    virtual void	parseValue(char const*& line) = 0;

    /**		Reset value to default.  Derived classes must define
     *		this.
     */
    virtual void	reset() = 0;

    // so that Configuration::parseLine() can call parseValue()
    friend class Configuration;

  private:

    char const* const	name_;
  };
};

/**
 *	@ingroup configuration
 *
 *	Configuration parameter
 */
template <class T>
class Var : public Configuration::Item
{
public:
  typedef T	value_type;

  Var(char const* name = 0, Configuration::Params& params = Configuration::variables()) :
    Item(name, params)
  { }
					     
  inline operator	T() const { return this->value; }
  inline operator	T*() const { return &this->value; }

  T& operator *() { return this->value; }
  T* operator ->() { return &this->value; }
  /*
    Var<T>&	operator =(std::string const& s) {
    parseValue(s.c_str());
    return *this;
    }

    Var<T>&	operator =(char const* s) {
    parseValue(s);
    return *this;
    }

    Var<T>& operator =(T new_value) {
    this->value = new_value;
    return *this;
    }
  */

  /**
   *	Serialize parameter so that it can be read back.
   */
  virtual void serialize(std::ostream& os) {
    os << name() << '\t' << value << std::endl;
  }

  T		value;		///<		the configured value.

protected:
  Var(char const* name, T value,
      Configuration::Params& params = Configuration::variables()) :
    Item(name, params), value(value) { }

};

/**
 *	@ingroup configuration
 *
 *	Configuration parameter with default value.
 */
template <class T> class VarDefault : public Var<T>
{
public:

  VarDefault() 
  { }

  T		Default() { return default_value; }

protected:
  VarDefault(char const *name, T default_value,
	     Configuration::Params& params = Configuration::variables()) :
    Var<T>(name, default_value, params), default_value(default_value)
 { }

  virtual void	reset() {
    Var<T>::value = default_value;
  }

private:
  T		default_value;
};

// So that we can specialize it later
template <class T> class conf : public Configuration::Item { };

/**
 *	simple string tokenizer, which returns next token within line.
 *	A token is a sequence of characters delimited
 *	by characters in @param sep except if preceded by @param esc.
 *	@param sep	sequence of delimiting characters
 *	@return		the first token from @param ptr.
 *	Advances ptr to the end of the token.
 *	@param esc	is an escape character for line continuation
 */
char const*		next_token_line(char const*& start, const char* sep,
					char esc = '\\');
} // namespace IXE

#endif	/* IXE_conf_H */
