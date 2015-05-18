/*
**  Tanl C++ Library
**  ixe/text/charmap.h
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

#ifndef	Tanl_Text_charmap_H
#define	Tanl_Text_charmap_H

// Settings
#include "platform.h"

// standard
#include <cctype>

namespace Tanl {
namespace Text {

extern char const iso8859_map[256];

/**
 *
 *	Convert an 8-bit ISO 8859-1 (Latin 1) character to its closest 7-bit
 *	ASCII equivalent.  (This mostly means that accents are stripped.)
 *
 *	This function exists to ensure that the value of the character used
 *	to index the iso8859_map[] vector declared above is unsigned.
 *
 *	@param c	The character to be converted.
 *	@return		The said character.
 *
 * SEE ALSO
 *
 *	International Standards Organization.  "ISO 8859-1: Information
 *	Processing -- 8-bit single-byte coded graphic character sets -- Part 1:
 *	Latin alphabet No. 1," 1987.
 *
 */

inline char iso8859_to_ascii(char c)
{
  return iso8859_map[static_cast<unsigned char>(c)];
}

} // namespace Text
} // namespace Tanl

#endif	/* Tanl_Text_charmap_H */
