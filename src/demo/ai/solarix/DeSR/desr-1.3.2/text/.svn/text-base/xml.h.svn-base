/*
**  Tanl C++ Library
**  text/xml.h
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

#ifndef Tanl_Text_xml_H
#define Tanl_Text_xml_H

namespace Tanl {
namespace XML {

enum XmlTokenType {
  XML_DECL,
  PROC_INST,
  DOCTYPE,
  COMMENT,
  NOTATION,
  TAG_OPEN,
  TAG_CLOSE,
  TAG_EMPTY,
  TAG_END,
  ID,
  EQ,
  VAL,
  CHARACTERS,
  RAW_CHARS,
  WHITESPACE,
  EoF
};

class XmlScanner : public xmlFlexLexer
{
 public:
  XmlScanner(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0) :
    xmlFlexLexer(arg_yyin, arg_yyout)
  { }

  /**
   *	We define our own method scan() instead of yylex().
   */
  int scan();			// i.e. YY_DECL

};

#undef YY_DECL
#define YY_DECL int Tanl::XML::XmlScanner::scan()

} // namespace XML
} // namespace Tanl

#endif // Tanl_Text_xml_H
