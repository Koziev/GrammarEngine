/*
**  Tanl C++ Library
**  text/XmlReader.h
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

#ifndef Tanl_Text_XmlReader_H
#define Tanl_Text_XmlReader_H

#undef yyFlexLexer
#define yyFlexLexer xmlFlexLexer
#include "FlexLexer.h"
#include "xml.h"

#include "Encoding.h"

// standard
#include <fstream>
#include <stdexcept>
#include <vector>

namespace Tanl {
namespace XML {

enum XmlNodeType
{
  None,		         ///< The state the reader is in before Read has been called 
  Attribute,             ///< An attribute defined within an element 
  CDATA,                 ///< Identifies a block of data that will not parsed by the XML reader 
  Comment,		 ///< A comment (<!-- ... -->)
  Document,		 ///< A Document object
  DocumentType,		 ///< Document type declaration (<!DOCTYPE...>)
  Element,		 ///< Represents the beginning of an element 
  EndElement,		 ///< The end element tag.
  Entity,		 ///< An entity declaration (<!ENTITY...>)
  EntityReference,	 ///< An entity reference (&num;)
  Notation,		 ///< A notation in the document type declaration (e.g. <!NOTATION...> )
  ProcessingInstruction, ///< An XML processing instruction (e.g. <?pi test?>)
  Text,			 ///< The text value of an element 
  Whitespace,		 ///< White space between tags 
  XmlDeclaration         ///< The XML declaration (<?xml version='1.0' ?>)
};

struct  XmlException : public std::runtime_error {
  XmlException(char const* msg) : std::runtime_error(msg) {}
};

class XmlReader
{
public:

  XmlReader(std::istream& stream);

  enum State {
    Initial,			// the Read method has not been called.
    Interactive,		// The Read method has been called.
    Error,			// An error occurred thata prevents continuing.
    EndOfFile,			// The end of file has been reached successfully.
    Closed			// The Close() method has been called.
  };

  /**
   *    Reads the next node from the stream.
   *	@return true if successful.
   */
  bool		Read() throw(XmlException);

  int		AttributeCount() { return attrs.size(); }

  bool		MoveToFirstAttribute();

  bool		MoveToNextAttribute();
  /**	Tells whether the reader is positioned at the end of the stream. */
  bool		Eof() { return state == EndOfFile; }
  /***	Gets the depth of the current node in the XML document. */
  int		Depth() { return depth; }

  XmlNodeType	NodeType;
  std::string	Name;
  std::string	Value;
  bool		isEmptyElement;
  Text::Encoding const*	encoding;

  struct NodeAttr {
    NodeAttr(std::string& name, std::string& value) :
      name(name),
      value(value)
    { }
    std::string name;
    std::string value;
  };

private:
  bool		readAttributes();

  XmlScanner	scanner;
  State		state;
  int		depth;
  std::string	tagName;
  std::vector<NodeAttr>	attrs;
  unsigned		attrIndex;
};

} // namespace XML
} // namespace Tanl

#endif // Tanl_Text_XmlReader_H
