// -----------------------------------------------------------------------------
// File CHR_CHAR_READER.CPP
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
// Класс Char_Reader - чтение ASCII-файлов с перекодированием в юникод по
// заданной кодовой странице (обычно для однобайтных кодировок).
// -----------------------------------------------------------------------------
//
// CD->20.11.2004
// LC->03.12.2011
// --------------


#include <lem/unicode.h>
#include <lem/streams.h>
#include <lem/conversions.h>
#include <lem/char_buffer.h>
#include <lem/ustreams.h>


using namespace std;
using namespace lem;
using namespace lem::Char_Stream;


Char_Reader::Char_Reader( lem::Ptr<Stream> Bin )
:WideStream(SET_ASCII,Bin)
{
 *format=0;
 SetEncoding( &lem::UI::get_UI().GetSessionCp() );
 return;
}


Char_Reader::Char_Reader( lem::Ptr<Stream> Bin, const CodeConverter *CP )
:WideStream(SET_ASCII,Bin)
{
 *format=0;
 SetEncoding( CP );
 return;
}



void Char_Reader::SetEncoding( const CodeConverter *CP )
{
 if( !CP->IsSingleByte() )
  throw E_BaseException( L"Char_Reader does not allow multibyte encodings" );

 cp=CP;

 if( cp )
  {
//   strcpy( format, "charset=" );
//   strcat( format, to_str( cp->get_Index() ).c_str() );
   strcpy( format, to_str( cp->get_Index() ).c_str() );
  }

 return;
}


wchar_t Char_Reader::Read_Char(void)
{
 last_char_pos = bin->tellp();
 const int c = bin->get();

 if( c==EOF )
  return WEOF;

 if( cp->IsSingleByte() )
  {
   return ((SBCodeConverter*)cp)->to_unicode( c );
  }
 else
  {
   LEM_STOPIT;
   return WEOF; 
  }
}

void Char_Reader::wput( wchar_t u )
{
 if( cp->IsSingleByte() )
  {
   bin->put( ((SBCodeConverter*)cp)->to_ascii(u) );
  }
 else
  {
   lem::CharBuffer aCh( cp->EstimateAsciiLen(1)+1 );   
   const int n = cp->to_ascii( u, aCh );
   bin->write( (const char*)aCh, n );
  }

 return;
}

int Char_Reader::get(void)
{ return bin->get(); }


void Char_Reader::put( char c )
{ bin->put(c); }


const char* Char_Reader::GetFormat(void) const
{
 return format;
}


wchar_t Char_Reader_Lang::Read_Char(void)
{
 LEM_CHECKIT_Z( filter!=NULL );
 return (*filter)( Char_Reader::Read_Char() );
}
