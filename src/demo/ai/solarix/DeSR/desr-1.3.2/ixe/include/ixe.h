/*
**  IXE C++ Library
**  ixe/include/ixe.h: basic types for IXE
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

#ifndef IXE_IXE_H
#define IXE_IXE_H

#include "platform.h"

/**
 *  @namespace IXE
 *  @brief  All the IXE classes are declared in namespace IXE.
 *
 *  The IXE Toolkit is a set of modular C++ classes and utilities for
 *  indexing and querying documents.
 */

namespace IXE {

/**
 * DocID is a numeric ID for documents in IXE collections.
 * DocID start at 1, 0 is reserved for no ID.
 */
typedef unsigned	DocID;
DocID const		noDocID = 0;

/**
 * Word position in document.
 * Positions start at 1, 0 is reserved for no position.
 */
typedef unsigned short	HitPosition;
HitPosition const	noPosition = 0;
HitPosition const	maxPosition = (HitPosition)-1;

/**
 * Number of occurrences of a word in a document.
 */
typedef unsigned short	Occurrences;
Occurrences const	maxOccurrences = (Occurrences)-1;

/**
 * TermColor is a numeric ID of a 'color' attribute for the word.
 * The color may represent a META NAME, or some HTML TAG.
 */
typedef short		TermColor;
TermColor const		noColor = -1;
TermColor const		color_Not_Found = -2;

typedef unsigned	TermID;
typedef unsigned	Count;
typedef unsigned	Size;

int const		num_bigrams = 256*256 + 1;

typedef unsigned char	byte;

// Align value 'x' to boundary 'b' which should be power of 2
#define ALIGN(x, b)   (((x) + (b) - 1) & ~((b) - 1))

} // namespace IXE

#endif /* IXE_IXE_H */
