/*
**  DeSR
**  src/Tokenizer.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef DeSR_Tokenizer_H
#define DeSR_Tokenizer_H

// settings

// standard
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <fstream>

// local
#include "Enumerator.h"
#include "Serializable.h"

namespace Parser {

/**
 *	@ingroup parser
 */
class Scanner : public ptbFlexLexer
{

 public:

  /** Token types.  */
  enum TokenType {
    Eof  =  0,
    Word = 200,
    Abbrev,
    Date,
    Number,
    Phone,
    Tag,
    Url,
    Punct
  };

  static char const* TypeName[];

  /**
   * Represents a token recognized by the scanner.
   */
  // can't inherit from Serializable, because SWIG can't handle it
  // nested class with virtual methods.
  struct Token { // : public Serializable {
    Token(char const* text = 0, TokenType type = (TokenType)0) :
      text(text), type(type) { }
    
    char const* text;		///< the text of the token
    TokenType type;		///< the type of the token

    Token const& operator =(Token const& o) {
      if (this != &o) {
	delete text;
	text = strdup(o.text);
	type = o.type;
      }
      return *this;
    }

   ~Token() { free((void*)text); }

    void	serialize(std::ostream& stream);

  };

  /**
   *	We define our own method scan() instead of yylex(), since we return
   *	a Token instead of int.
   */
  Token scan();			// i.e. YY_DECL
};

#undef YY_DECL
#define YY_DECL Parser::Scanner::Token Parser::Scanner::scan()
#define yylval token.text

/**
 *	@ingroup parser
 *
 *	Read a plain text file, split into tokens.
 *	Provides an Enumerator interface, since it needs to look at next token
 *	to determine if there are more.
 *	An Iterator interface would be more cumbersome to implement.
 */
class Tokenizer : public Tanl::Enumerator<Scanner::Token const*>
{
 public:

  /** 
   *	Creates a new @c Tokenizer. 
   *	@param is	the stream containing the sentence to read.
   */
  Tokenizer(std::istream* is, char const* lang = 0);

  /** Returns the current token */
  Scanner::Token const*	Current();

  /** Advance to the next token and return true if there is one available */
  bool		MoveNext();

  /**	Restart */
  void		Reset();

 private:
  Scanner	scanner;
  Scanner::Token token;		///< the current token
  std::istream&	stream;
};

} // namespace Parser

#endif // DeSR_Tokenizer_H
