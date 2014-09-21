// -----------------------------------------------------------------------------
// File CAST_TO_URL.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
//
// Преобразование UNICODE строки в формат URL.
// -----------------------------------------------------------------------------
//
// CD->16.05.2006
// LC->15.10.2009
// --------------

#include <lem/fstring.h>
#include <lem/unicode.h>
#include <lem/conversions.h>

using namespace lem;

// Copyright (C) 2003, Markus Schutz
// Project URL: http://lyric.sourceforge.net 

 /* URL strings store non-ASCII and special characters as UTF-8 sequences
 * using a %hh notation, where 'h' is a hexadecimal digit. Spaces ' ' are
 * stored as '+'.
 * RFC 2718 section 2.2.5 was used as reference for the conversion algorithm,
 * and can be found at http://www.ietf.org/rfc/rfc2718.txt, or any other RFC
 * database.
 * RFC 2279 was used as reference for the UCS-4 to UTF-8 conversion algorithm,
 * and can be found at http://www.ietf.org/rfc/rfc2279.txt, or any other RFC
 * database.
 */ 

const FString lem::encode_to_url( const UFString &str )
{
 FString res;
 res.reserve( str.size()*3 ) ;

 lem::uint8_t utf8[8];
 char buf[8];

 for( int i=0; i<str.size(); ++i )
  {
   UFString::value_type symbol = str[i];

   if( symbol < 0x80 )
    {
         if( ((symbol>32) && (symbol <= 35)) ||
             ((symbol >= 37) && (symbol <= 44)) ||
             ((symbol >= 58) && (symbol <= 64)) ||
             ((symbol == 91) || (symbol == 96)) ||
             ((symbol >= 93) && (symbol <= 94)) ||
             ((symbol >=123) && (symbol <=127)) )
	  {
	   res.Add_Dirty('%');
	   sprintf( buf, "%02X", symbol);
	   res.Add_Dirty(buf[0]);
	   res.Add_Dirty(buf[1]);
	  }
     else if (symbol == ' ') 
      res.Add_Dirty('+');
     else
	  res.Add_Dirty( static_cast<char>(symbol) );
    }
   else
    {
	 lem::UCS4_to_UTF8( symbol, utf8 );
     for( int k=0; k<utf8[0]; k++ )
      {
       res.Add_Dirty('%');
       sprintf( buf, "%02X", utf8[k+1] );
       res.Add_Dirty(buf[0]);
       res.Add_Dirty(buf[1]);
      }
    }
  }

 res.calc_hash();
 return res;
}

// **************************************************************************
// Кодирование символов в адресе: не-ASCII символы представляются в виде %HH
// **************************************************************************

const lem::FString lem::encode_to_url( const lem::FString &str )
{
 // кодируем некоторые символы через %-escape
 FString res;
 const int l = str.length();

 if( !l )
  return res;

 res.reserve( l*3 );

 char hex[32];

 for( int i=0; i<l; i++ )
  {
   const char c = str[i];
   if( c==' ' )
    res.Add_Dirty('+');
   else if( lem::is_latin(c) || lem::is_digit(c) )
    res.Add_Dirty(str[i]);
   else
    {
     lem::uint16_t c16 = 0x00ff & c;
     lem::uint16_to_str( c16, hex, 16 );
     res.Add_Dirty( '%' );
     res.Add_Dirty( hex );
    } 
  }

 res.calc_hash();
 return res;
}



/*
FString lem::EncodeUrl( const UFString &str )
{ return EncodeUrl(str.c_str()); }

FString lem::EncodeUrl( const wchar_t *str )
{
 // переводим строку в UTF8
 FString utf8( lem::to_utf8(str) );

 // Теперь кодируем некоторые символы через %-escape
 FString res;
 const int l = utf8.length();

 if( !l )
  return res;

 res.reserve( l*3 );

 char hex[32];

 for( int i=0; i<l; i++ )
  if( lem::is_latin(utf8[i]) || lem::is_digit(utf8[i]) )
   res.Add_Dirty(utf8[i]);
  else
   {
    lem::uint16_t c = 0x00ff & utf8[i];
    lem::uint16_to_str( c, hex, 16 );
    res.Add_Dirty( hex );
   } 

 res.calc_hash();
 return res;
}
*/

