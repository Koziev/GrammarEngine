// -----------------------------------------------------------------------------
// File UNICODE_ENCODINGS_CONVERSION.CPP
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
//
// ѕреобразование UNICODE строки в формат URL (дл€ справки
// см. RFC 2718 http://www.ietf.org/rfc/rfc2718.txt).
// -----------------------------------------------------------------------------
//
// CD->16.05.2006
// LC->16.05.2006
// --------------

#include <lem/unicode.h>

using namespace lem;

// Copyright (C) 2003, Markus Schutz
// Project URL: http://lyric.sourceforge.net 


/*===========================================================================*/
/* Casts an UCS-4 symbol (ISO-10646) to an UTF-8 byte array.
 * RFC 2279 was used as reference for the conversion algorithm, and can be
 * found at http://www.ietf.org/rfc/rfc2279.txt, or any other RFC database.
 * The first item in the byte array (utf8[0]) stores the length of the UTF-8
 * byte stream.
 */
int lem::UCS4_to_UTF8( lem::uint32_t ucs4, uint8_t utf8[8] )
{
 lem::uint8_t p, max;
 lem::int8_t head;          // Must be signed so the >> adds leading 1s.

 if( ucs4 > int32_max )
  {
   ucs4 = L' ';
  }

 if( ucs4 < 0x80 )
  {
   utf8[0] = 1;
   utf8[1] = ucs4;
  }
 else
  {
   p = 7;
   head = (lem::int8_t)0x80;
   max = 0x3f;

   while (ucs4 > max)
    {
	 utf8[p] = 0x80 | (ucs4 & 0x3f);
	 ucs4 >>= 6;
	 head >>= 1;
	 max >>= 1;
	 p--;
	}
   
   utf8[p] = head | ucs4;
   utf8[0] = 8-p;
   if (utf8[0] < 7)
	memmove(&utf8[1], &utf8[p], utf8[0]);
  }

 return utf8[0];
} 

