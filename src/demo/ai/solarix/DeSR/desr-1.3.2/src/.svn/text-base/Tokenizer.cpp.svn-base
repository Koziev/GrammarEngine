/*
**  DeSR
**  src/Tokenizer.cpp
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

#undef yyFlexLexer
#define yyFlexLexer ptbFlexLexer
#include "FlexLexer.h"

#include "Tokenizer.h"

// define required default virtual method
int ptbFlexLexer::yylex() { return 0; }

namespace Parser {

  char const* Scanner::TypeName[] = { "Eof",
    "Word",
    "Abbrev",
    "Date",
    "Number",
    "Phone",
    "Tag",
    "Url",
    "Punct"
};

void Scanner::Token::serialize(std::ostream& stream)
{
  stream << "<token type='" <<
    TypeName[((int)this->type)%9] <<
    "' text='" << this->text << "' />";
}

Tokenizer::Tokenizer(std::istream* is, char const* lang) :
  stream(*is)
{
  scanner.switch_streams(&stream, 0);
}

Scanner::Token const* Tokenizer::Current()
{
  return &token;
}

bool Tokenizer::MoveNext()
{
  token = scanner.scan();
  return token.type != Scanner::Eof;
}

void Tokenizer::Reset() {
  stream.seekg(0);
  scanner.switch_streams(&stream, 0);
}

} // namespace Parser
