/*
**  Tanl C++ Library
**  ixe/text/text.h: basic types for Text
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

#ifndef Tanl_Text_text_H
#define Tanl_Text_text_H

namespace Tanl {

/**
 *	Text handling and internationalization support.
 *	@see <a href="http://oss.software.ibm.com/icu">ICU</a>
 */

namespace Text {

/**
 *	UCS2 holds a single UTF-16 code unit
 */
typedef unsigned short	UCS2;
/**
 *	UCS4 represents a Unicode code point.
 */
typedef int		UCS4;

} // Text
} // Tanl

#endif // Tanl_Text_text_H
