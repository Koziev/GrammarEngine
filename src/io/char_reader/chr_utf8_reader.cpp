// -----------------------------------------------------------------------------
// File CHR_UTF8_READER.CPP
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
// Класс UTF8_Reader - чтение/запись UTF-8 текстовых файлов.
//
// 30.04.2008 - для удобства использования добавлены конструкторы.
// 11.11.2008 - расширен конструктор с параметром 'путь к файлу', теперь он
//              получает дополнительный аргумент - открывать для чтения (default)
//              или для записи. 
//
// 20.09.2009 - для улучшения производительности при записи больших блоков под
//              MS Win реализация wputs конвертирует и записывает в выходной
//              поток куски по несколько Кб.
// 29.01.2011 - wget() returns space when encounters an invalid utf8 sequence
// -----------------------------------------------------------------------------
//
// CD->20.12.2004
// LC->29.01.2011
// --------------

#include <lem/streams.h>
#include <lem/unicode.h>
#include <lem/conversions.h>
#include <lem/ustreams.h>

using namespace lem;
using namespace lem::Char_Stream;


/*
 	bytes | bits | representation
 	    1 |    7 | 0xxxxxxx
 	    2 |   11 | 110xxxxx 10xxxxxx
 	    3 |   16 | 1110xxxx 10xxxxxx 10xxxxxx
 	    4 |   21 | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/


// В начале текстового файла UTF-8 идут байты EF BB BF


UTF8_Reader::UTF8_Reader( lem::Ptr<lem::Stream> Bin )
:WideStream(SET_UTF8,Bin)
{
 if( Bin.NotNull() )
  Bin->rewind();

 cp = &lem::UI::get_UI().GetSessionCp();
 return;
}


UTF8_Reader::UTF8_Reader( lem::Stream& Bin )
 :WideStream(SET_UTF8, lem::Ptr<Stream>( &Bin, null_deleter() ) )
{
 Bin.rewind();
 cp = &lem::UI::get_UI().GetSessionCp();
 return;
}


UTF8_Reader::UTF8_Reader( const lem::Path &filename, bool for_writing )
 :WideStream( SET_UTF8, lem::Ptr<Stream>( new BinaryFile(filename,!for_writing,for_writing) ) )
{
 cp = (SBCodeConverter*)&lem::UI::get_UI().GetSessionCp();
 return;
}




// ***********************************************************
// Вписываем заголовок для TXT файлов - чтобы распознать
// особый формат UTF-8.
// ***********************************************************
void UTF8_Reader::Write_Beginning(void)
{
 bin->put( (char)0xef );
 bin->put( (char)0xbb );
 bin->put( (char)0xbf );
 return;
}


// ******************************************************************
// Читаем заголовок (BOM) UTF-8 файла. Если excp==true, то
// неправильный заголовок вызовет исключение, если excp=false,
// то вернет false.
// Если заголовок корректный, то вернет true.
// ******************************************************************
bool UTF8_Reader::Read_Beginning( bool excp )
{
 lem::uint8_t b1 = bin->get();
 lem::uint8_t b2 = bin->get();
 lem::uint8_t b3 = bin->get();

 if( (b1!=0xef) || (b2!=0xbb) || (b3!=0xbf) )
  {
   if( excp )
    {
     throw E_BaseException( L"Incorrect UTF-8 file BOM" );
    }
   else
    {
     rewind();
     return false;
    }
  }

 return true; 
}



/*
   ------ UCS-4 ------   ------------------- UTF-8 ---------------------------  
   0000 0000-0000 007F   0xxxxxxx
   0000 0080-0000 07FF   110xxxxx 10xxxxxx
   0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-001F FFFF   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
   0020 0000-03FF FFFF   111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
   0400 0000-7FFF FFFF   1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

/* Based on RFC2279 */

inline bool BYTE6( unsigned char code ) { return (code & 0xfe) == 0xfc; }
inline bool BYTE5( unsigned char code ) { return (code & 0xfc) == 0xf8; }
inline bool BYTE4( unsigned char code ) { return (code & 0xf8) == 0xf0; }
inline bool BYTE3( unsigned char code ) { return (code & 0xf0) == 0xe0; }
inline bool BYTE2( unsigned char code ) { return (code & 0xe0) == 0xc0; }
inline bool BYTE1( unsigned char code ) { return code <= 0x7f; }

#define CLEAR_MSB(code)	 (code & (~0x80))

#define CHECK8(c) { if( (0xc0 & c)!=0x80 ) return ERROR_CHAR; }


wchar_t UTF8_Reader::Read_Char(void)
{
 last_char_pos = bin->tellp();

 int c32 = bin->get();
 
 if( c32==EOF )
  return WEOF;

 lem::uint8_t head = (lem::uint8_t)c32;

 lem::uint32_t uni = 0;
 
 const wchar_t ERROR_CHAR=L' ';
 

 if( BYTE6(head) )
  {
   lem::uint32_t u5 = (lem::uint8_t)bin->get(); CHECK8(u5);
   lem::uint32_t u4 = (lem::uint8_t)bin->get(); CHECK8(u4);
   lem::uint32_t u3 = (lem::uint8_t)bin->get(); CHECK8(u3);
   lem::uint32_t u2 = (lem::uint8_t)bin->get(); CHECK8(u2);
   lem::uint32_t u1 = (lem::uint8_t)bin->get(); CHECK8(u1);

   uni = ((head&0x01)<<30) |
         ((u5&0x3f)<24) |
         ((u4&0x3f)<18) |
         ((u3&0x3f)<12) |
         ((u2&0x3f)<6)  |
         (u1&0x3f); 
  }
 else if( BYTE5(head) )
  {
   lem::uint32_t u4 = (lem::uint8_t)bin->get(); CHECK8(u4);
   lem::uint32_t u3 = (lem::uint8_t)bin->get(); CHECK8(u3);
   lem::uint32_t u2 = (lem::uint8_t)bin->get(); CHECK8(u2);
   lem::uint32_t u1 = (lem::uint8_t)bin->get(); CHECK8(u1);

   uni = ((head&0x03)<<24) |
         ((u4&0x3f)<18) |
         ((u3&0x3f)<12) |
         ((u2&0x3f)<6)  |
         (u1&0x3f); 
  }
 else if( BYTE4(head) )
  {
   lem::uint8_t u4 = head;
   lem::uint8_t u3 = bin->get(); CHECK8(u3);
   lem::uint8_t u2 = bin->get(); CHECK8(u2);
   lem::uint8_t u1 = bin->get(); CHECK8(u1);

   uni = ((u4 & 0x7) << 2) | ((u3 >> 4) & 0x3);
   uni = (uni << 8) | ((u3 & 0xf) << 4 | ((u2 >> 2) & 0xf));
   uni = (uni << 8) | ((u2 & 0x3) << 6 | (u1 & 0x3f));
  }
 else if (BYTE3(head) )
  {
   lem::uint8_t u3 = head;
   lem::uint8_t u2 = bin->get(); CHECK8(u2);
   lem::uint8_t u1 = bin->get(); CHECK8(u1);

   uni = (u3 & 0xf);
   uni = (uni << 4) | ((u2 >> 2) & 0xf);
   uni = (uni << 8) | ((u2 & 0x3) << 6 | (u1 & 0x3f));
  }
 else if (BYTE2(head) )
  {
   /* Ok, First six bit of the 1st byte goes to the first six bits in the
    * first byte. Then bits # 0, 1 in the 2nd byte goes to bits # 6, 7 in
    * the first byte. So we're done with the first byte.
    * Then bits # 2-4 from the 2nd byte goes to the bits # 0-2 in the 2nd
    * byte. So we're done!
    */
   lem::uint8_t u2 = head;
   lem::uint8_t u1 = bin->get(); CHECK8(u1);

   uni = (u2 >> 2) & 0x7;
   uni = (uni << 8) | ((u2 & 0x3) << 6 | (u1 & 0x3f));
  }
 else if (BYTE1(head) )
  {
   uni = head;
  }

 if( sizeof(wchar_t)==2 && uni>0x0000ffff )
  {
   // работаем с utf-16, нам придется разделить 32-битный символ на суррогатную пару.

   lem::uint32_t x = uni-0x00010000;
   lem::uint16_t high_surrogate = 0xD800 + lem::uint16_t( (x>>10) & 0x3FF );
   lem::uint16_t low_surrogate = 0xDC00 + lem::uint16_t(x&0x3FF);

   back_ch = low_surrogate;
   back_pos = last_char_pos;

   return high_surrogate;
  }

 return uni;
}



#if defined LEM_WINDOWS
void UTF8_Reader::wputs( const wchar_t *str )
{
 if( str!=NULL )
  {
   const int l = wcslen(str);
   if( l>64 )
    {
     // Будем конвертировать строку блоками по 8Kb
     const int bsize=8192;
     const int b8size=8192*6;
     
     char *block = new char[b8size];

     int i=0;
     while( i<l )
      { 
       int chunk_size = l-i;
       if( chunk_size>bsize )
        chunk_size = bsize;
  
       int b8 = WideCharToMultiByte( CP_UTF8, 0, str, chunk_size, block, b8size, NULL, NULL );
       LEM_CHECKIT_Z( b8>0 );
       LEM_CHECKIT_Z( b8<=b8size );

       bin->write( block, b8 );

       i += chunk_size;
       str += chunk_size;
      }

     delete[] block;
    }
   else
    {
     while( *str )
      wput( *(str++) );
    }
  }

 return;
}
#endif


void UTF8_Reader::wput( wchar_t uc )
{
 unsigned char u1, u2, u3, u4;

 if( uc < 0x80 )
  bin->put( static_cast<char>(uc) );
 else if (uc < 0x800)
  {
   u2 = 0xC0 | (uc>>6);
   u1 = 0x80 | (uc & 0x3F);
   bin->put(u2);
   bin->put(u1);
  }
 else if (uc < 0x10000)
  {
   u3 = 0xE0 | (uc>>12);
   u2 = 0x80 | ((uc>>6) & 0x3F);
   u1 = 0x80 | (uc & 0x3F);

   bin->put(u3);
   bin->put(u2);
   bin->put(u1);
  }
 else if (uc < 0x200000)
  {
   u4 = 0xF0 | (uc>>18);
   u3 = 0x80 | ((uc>>12) & 0x3F);
   u2 = 0x80 | ((uc>>6) & 0x3F);
   u1 = 0x80 | (uc & 0x3F);

   bin->put(u4);
   bin->put(u3);
   bin->put(u2);
   bin->put(u1);
  }

 return;
}


int UTF8_Reader::get(void)
{
 return wget();
}


void UTF8_Reader::put( char c )
{
 if( cp )
  {
   if( cp->IsMultiByte() )
    {
     wput( c & 0x000000ff );
    }
   else 
    {
     SBCodeConverter *sb = (SBCodeConverter*)cp;
     wput( sb->to_unicode(c) );
    }
  }
 else
  wput(c);

 return;
}



wchar_t UTF8_Reader_Lang::Read_Char(void)
{ return (*filter)( UTF8_Reader::Read_Char() ); }


UTF8_MemReader::UTF8_MemReader( const lem::FString &str )
 : UTF8_Reader( lem::StreamPtr() ), utf8_str(str)
{
 bin = new MemReadStream( utf8_str.c_str() ); 
 return;
}

UTF8_MemReader::UTF8_MemReader( const char *str )
 : UTF8_Reader( lem::StreamPtr() ), utf8_str(str)
{
 bin = new MemReadStream( utf8_str.c_str() ); 
 return;
}
