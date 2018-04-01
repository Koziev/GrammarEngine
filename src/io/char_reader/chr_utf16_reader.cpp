// -----------------------------------------------------------------------------
// File CHR_UTF16_READER.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ supplementary library
// Класс UTF16_Reader - чтение UTF16 текстовых файлов.
//       UTF16_MemWriter - запись потока в оперативную память
//       UTF16_MemReader - чтение потока из оперативной памяти
//
// 03.11.2008 - исправлена ошибка в UTF16_MemReader::unget, сделана
//              оптимизированная реализация UTF16_MemReader::wpeek.
// -----------------------------------------------------------------------------
//
// CD->20.11.2004
// LC->01.09.2010
// --------------

#include <lem/streams.h>
#include <lem/conversions.h>
#include <lem/ustreams.h>

using namespace boost;
using namespace lem;
using namespace lem::Char_Stream;

UTF16_Reader::UTF16_Reader( WideStreamType t, lem::StreamPtr Bin )
:WideStream(t,Bin)
{
 type=t;
 return;
}

wchar_t UTF16_Reader::Read_Char(void)
{
 lem::uint8_t c1, c2;

 last_char_pos = bin->tellp();

 if( type==SET_UTF16BE )
  {
   // сначала идет младший байт, затем - старший
   c1 = bin->get();
   c2 = bin->get();
  }
 else
  {
   // сначала идет старший байт, затем - младший
   c2 = bin->get();
   c1 = bin->get();
  }

 // Из двух байтов конструируем UNICODE.
 lem::uint16_t u =  ( ((lem::uint16_t)c1) << 8 ) & 0xff00u;
               u |= ( ((lem::uint16_t)c2)      ) & 0x00ffu;

 return static_cast<wchar_t>(u);
}


void UTF16_Reader::wput( wchar_t u )
{
 char c1, c2;

 c1 = static_cast<char>(u >> 8);
 c2 = static_cast<char>(u);

 if( type==SET_UTF16 )
  {
   // сначала идет младший байт, затем - старший
   bin->put(c2);
   bin->put(c1);
  }
 else
  {
   // сначала идет старший байт, затем - млаший
   bin->put(c1);
   bin->put(c2);
  }

 return;
}


const char* UTF16_Reader::GetFormat(void) const
{
 return GetType() == SET_UTF16BE ? "utf16be" : "utf16le";
}


bool UTF16_Reader::Read_Beginning( bool excp )
{
 // Тип - определяем по первой паре байтов файла
 lem::uint8_t b1 = bin->get();
 lem::uint8_t b2 = bin->get();

 if( b1==lem::uint8_t(0xff) && b2==lem::uint8_t(0xfe) )
  type = SET_UTF16;
 else if( b1==lem::uint8_t(0xfe) && b2==lem::uint8_t(0xff) )
  type = SET_UTF16BE;
 else
  {
   if( excp )
    throw E_BaseException( L"Incorrect UTF16 file BOM" );
   else
    return false;
  }

 return true;
}


void UTF16_Reader::Write_Beginning(void)
{
 switch(type)
 {
  case SET_UTF16:
   bin->put( 0xffu );
   bin->put( 0xfeu );
   break;

  case SET_UTF16BE:
   bin->put( 0xfeu );
   bin->put( 0xffu );
   break;

  default: LEM_STOPIT;
 }

 return;
}


UTF16_MemWriter::UTF16_MemWriter()
: UTF16_Reader( Char_Stream::SET_UTF16, lem::StreamPtr() )
{
 SetMode( false, true ); 
 res = new UFString;
 res->reserve(16384);
 return;
}

UTF16_MemWriter::~UTF16_MemWriter(void)
{
 lem_rub_off(res);
}


bool UTF16_MemWriter::Read_Beginning( bool /*excp*/ )
{
 LEM_STOPIT;
 return false;
}


void UTF16_MemWriter::wput( wchar_t u )
{
 // Добавляем по-быстрому, без пересчета хэш-кода.
 res->operator+=(u);
}


UFString* UTF16_MemWriter::Pick_String(void)
{
 UFString *ret = res;
 res = new UFString;
 res->reserve(16384);

 return ret;
}

void UTF16_MemWriter::clear(void)
{
 res->clear();
 return;
}


const UFString& UTF16_MemWriter::string(void) const
{
 return *res;
}


UTF16_MemReader::UTF16_MemReader( const UFString &Src )
: UTF16_Reader( Char_Stream::SET_UTF16, lem::StreamPtr() )
{
 SetMode( true, false );
 res = lem::Ptr<UFString>( (UFString*)&Src, null_deleter() );
 eof_reached = false;
 icur=0;
 return;
}

UTF16_MemReader::UTF16_MemReader( const wchar_t * Src )
: UTF16_Reader( Char_Stream::SET_UTF16, lem::StreamPtr() )
{
 SetMode( true, false );
 res = new UFString(Src);
 eof_reached = false;
 icur=0;
 return;
}

UTF16_MemReader::UTF16_MemReader( lem::Ptr<UFString> Src )
: UTF16_Reader( Char_Stream::SET_UTF16, lem::StreamPtr() ), res(Src)
{
 LEM_CHECKIT_Z( Src.NotNull() );
 SetMode( true, false ); 
 eof_reached = false;
 icur=0;
 return;
}




// ********************************************************************
// pos - это байтовая позиция, хотя мы работаем с широкими символами,
// поэтому надо проверять, что перемещение выполняется на границу
// широкого символа
// ********************************************************************
Stream::pos_type UTF16_MemReader::seekp( off_type pos, int whereto )
{
 LEM_CHECKIT_Z( whereto==0 );
 LEM_CHECKIT_Z( (pos%sizeof(wchar_t))==0 );
 icur = pos/sizeof(wchar_t);
 eof_reached=false;

 if( icur>=res->length() )
  {
   eof_reached=true;
   icur = res->length()*sizeof(wchar_t);
   return (Stream::pos_type)-1;
  }

 return pos;
}


void UTF16_MemReader::Write_Beginning(void)
{ LEM_STOPIT; }

bool UTF16_MemReader::Read_Beginning( bool /*excp*/ )
{ return true; }

void UTF16_MemReader::wput( wchar_t /*u*/ )
{ LEM_STOPIT; }

bool UTF16_MemReader::eof(void) const
{ return eof_reached; }


Stream::pos_type UTF16_MemReader::fsize(void) const
{
 LEM_CHECKIT_Z(res!=NULL);
 return res->length()*sizeof(wchar_t);
}

Stream::pos_type UTF16_MemReader::tellp(void) const
{
 LEM_CHECKIT_Z(res!=NULL);
 return back_ch ? back_pos : sizeof(wchar_t)*icur;
}

void UTF16_MemReader::unget( wchar_t ch )
{
 LEM_CHECKIT_Z( icur>0 );
 back_ch=ch;
 back_pos=sizeof(wchar_t)*(icur-1);
 return;
}

wchar_t UTF16_MemReader::wpeek(void)
{
 LEM_CHECKIT_Z(res!=NULL);

 if( icur >= res->length() )
  return WEOF; 

 return (*res)[icur];
}


wchar_t UTF16_MemReader::Read_Char(void)
{
 LEM_CHECKIT_Z(res!=NULL);

 if( icur >= res->length() )
  {
   eof_reached = true;
   return WEOF; 
  }

 last_char_pos = icur;

 return (*res)[icur++];
}


wchar_t UTF16_Reader_Lang::Read_Char(void)
{
 LEM_CHECKIT_Z( filter!=NULL );
 return (*filter)( UTF16_Reader::Read_Char() );
}



UTF16_MemReader_Lang::UTF16_MemReader_Lang( const UFString &Src, const Lang_Filter *Filter )
 : UTF16_MemReader(Src), filter(Filter)
{
}


wchar_t UTF16_MemReader_Lang::Read_Char(void)
{
 LEM_CHECKIT_Z( filter!=NULL );
 return (*filter)( UTF16_MemReader::Read_Char() );
}
