/*
**  Tanl C++ Library
**  text/XmlReader.cpp
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

#include "XmlReader.h"

// Standard
#include <string.h>
#include <stdlib.h>

// define required default virtual method
int yyFlexLexer::yylex() { return 0; }

using namespace std;

namespace Tanl {
namespace XML {

XmlReader::XmlReader(istream& stream) :
  NodeType(None),
  state(Initial),
  depth(0),
  isEmptyElement(false),
  scanner(&stream),
  encoding(Text::Encoding::get("UTF-8"))
{
}

static inline string decode(char const* start, size_t len, Text::Encoding const* from)
{
  static Text::Encoding const* utf8Encoding = Text::Encoding::get("UTF-8");

  if (from == utf8Encoding)
    return string(start, len);
  else {
    char* conv;
    size_t l = utf8Encoding->Encode(from, start, len, conv);
    string out = string(conv, l);
    free(conv);
    return out;
  }
}

bool XmlReader::readAttributes()
{
  attrIndex = -1;
  while (true) {
    int tokType = scanner.scan();
    switch (tokType) {
    case ID: {
      string name = scanner.YYText();
      switch (scanner.scan()) {
      case EQ:
	switch (scanner.scan()) {
	case VAL: {
	  string value = scanner.YYText();
	  attrs.push_back(NodeAttr(name, value));
	  continue;
	}
	case EOF:
	  state = Error;
	  throw XmlException("Premature EOF");
	}
	break;
      case EOF:
	state = Error;
	throw XmlException("Premature EOF");
      default:
	state = Error;
	throw XmlException("Syntax error: no equal sign");
      }
    }
    case TAG_EMPTY:
      isEmptyElement = true;
      tagName.clear();
      // no break
    case TAG_END:
      return true;
    }
  }
  return false;
}

bool XmlReader::Read() throw(XmlException)
{
  if (Eof())
    return false;
  state = Interactive;
  while (true) {
    Name.clear();
    Value.clear();
    int tokType = scanner.scan();
    switch (tokType) {
    case XML_DECL:
      NodeType = XmlDeclaration;
      Name = "xml";
      return readAttributes();
    case PROC_INST:
      NodeType = ProcessingInstruction;
      // FIXME: should split into Name and Value
      Value = decode(scanner.YYText()+2, scanner.YYLeng()-4, encoding);
      return true;
    case DOCTYPE:
      NodeType = DocumentType;
      // FIXME: should split into Name and Value
      Value = decode(scanner.YYText()+10, scanner.YYLeng()-11, encoding);
      return true;
    case COMMENT:
      NodeType = Comment;
      Value = decode(scanner.YYText()+4, scanner.YYLeng()-7, encoding);
      return true;
    case TAG_OPEN: {
      attrs.clear();
      attrIndex = 0;
      tokType = scanner.scan();
      if (tokType == ID) {
	NodeType = Element;
	Name = tagName = scanner.YYText();
      } else if (tokType == EndOfFile) {
	state = Error;
	throw XmlException("Premature EOF");
      } else {
	state = Error;
	throw XmlException("Syntax error: no element name");
      }
      if (readAttributes()) {
	++depth;
	return true;
      }
      return false;
    }
    case TAG_CLOSE:
      tagName.clear();
      if (depth) {
	NodeType = EndElement;
	char const* text = scanner.YYText()+2;
	// trim whitespace
	char const* end = strpbrk(text, " \n\r\t>");
	Name = string(text, end - text);
	--depth;
	return true;
      } else {
	state = Error;
	throw XmlException("Syntax error: extra close tag");
      }
    case CHARACTERS:
      NodeType = Text;
      Value = decode(scanner.YYText(), scanner.YYLeng(), encoding);
      return true;
    case RAW_CHARS:
      NodeType = CDATA;
      Value = decode(scanner.YYText(), scanner.YYLeng(), encoding);
      return true;
    case WHITESPACE:
      NodeType = Whitespace;
      Value = scanner.YYText();
      return true;
    case EoF:
      state = EndOfFile;
      return false;
    default:
      state = Error;
      throw XmlException("Syntax error: ");
    }
  }
}

bool XmlReader::MoveToFirstAttribute()
{
  if (!attrs.size())
    return false;
  attrIndex = 0;
  NodeType = Attribute;
  Name = attrs[attrIndex].name;
  Value = attrs[attrIndex].value;
  return true;
}

bool XmlReader::MoveToNextAttribute()
{
  if (++attrIndex < attrs.size()) {
    NodeType = Attribute;
    Name = attrs[attrIndex].name;
    Value = attrs[attrIndex].value;
    return true;
  } else
    return false;
}

} // namespace XML
} // namespace Tanl
