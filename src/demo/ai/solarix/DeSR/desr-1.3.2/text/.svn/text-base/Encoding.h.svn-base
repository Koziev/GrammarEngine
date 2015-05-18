/*
**  Tanl C++ Library
**  ixe/text/Encoding.h
**  ----------------------------------------------------------------------
**  Copyright (c) 2002  Giuseppe Attardi (attardi@di.unipi.it).
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

#ifndef Tanl_text_Encoding_H
#define Tanl_text_Encoding_H

// settingd
#include "platform.h"

// Standard
#include <string>

namespace Tanl {
  namespace Text {

class Encoding
{
public:
  typedef unsigned char	ID;

  Encoding(char const name[],
	   ID id,
	   float averageBytesPerChar = 1.0,
	   float maxBytesPerChar = 1.0) :
    name(name),id(id),
    averageBytesPerChar(averageBytesPerChar),
    maxBytesPerChar(maxBytesPerChar)
  { }

  Encoding(char const* name,
	   float averageBytesPerChar = 1.0,
	   float maxBytesPerChar = 1.0) :
    name(name),
    id(-1),
    averageBytesPerChar(averageBytesPerChar),
    maxBytesPerChar(maxBytesPerChar)
  { }

  char const* name;		///< the official canonical name
  ID	id;			///< the internal id for the encoding
  float averageBytesPerChar;	///< the average bytes used to encode one character
  float	maxBytesPerChar;	///< the maximum count of bytes use to encode one character

  /**
   *    name of this encoding
   */
  char const* Name() { return name; }

  /**
   *	Get the encoding with the given name
   */
   static Encoding const*	get(char const* name);

  /**
   *	Get the encoding with the given id
   */
   static Encoding const*	get(ID id);

  /**
   *	Converts a multibyte sequence starting at @c in, of length @c inlen,
   *	from character encoding @c fromCode to this encoding.
   *	The converted sequence is stored in @c out, for a maximum size of
   *	@c outlen.
   *	If @c outlen is 0, a buffer is allocated with malloc() and returned
   *	in @c out.
   *
   *	@returns the size of the converted sequence, or 0 if conversion failed.
   */
  size_t Encode(Encoding const* fromCode, char const* in, size_t inlen,
		char*& out, size_t outlen = 0) const;

  /**
   *    register known Encodings
   */
  static void		Register(Encoding* encoding);
  static void		Register(char const* alias, char const* canonical);
};

} // Text
} // Tanl

#endif // Tanl_text_Encoding_H
