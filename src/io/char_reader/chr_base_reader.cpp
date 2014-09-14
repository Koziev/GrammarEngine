// -----------------------------------------------------------------------------
// File CHR_BASE_READER.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Класс WideStream - потоки для работы с юникодными символами. 
//
// 19.12.2006 - исправлена ошибка с распознаванием формата ucs2, из-за которой
//              ASCII тексты с первой буквой 'я' могли распознаваться
//              некорректно. 
// 21.07.2008 - сделана поддержка многобайтовых кодировок текущей локали в
//              методы WideStream::GetReader, так что в Linux с кодировкой 
//              utf-8 по умолчанию открывается ридер utf-8.
// 02.09.2009 - поправлена ошибка в read_text, последний считываемый символ EOF
//              не добавляется в буфер. 
// 28.10.2009 - добавлен автоопределитель кодировки на основе Mozilla
//              Charset Guesser
// -----------------------------------------------------------------------------
//
// CD->20.11.2004
// LC->20.02.2010
// --------------

#include <lem/unicode.h>
#include <lem/conversions.h>
#include <lem/ustreams.h>

using namespace boost;
using namespace lem;
using namespace lem::Char_Stream;

WideStream::WideStream( WideStreamType t, lem::Ptr<lem::Stream> Bin )
: bin(Bin), type(t), cp(NULL)
{
 back_ch          = 0;
 back_pos         = 0;
 last_char_pos    = 0;

 // по умолчанию тэги пропускаются
 strip_decoration=true;

 if( bin.get()!=NULL )
  SetMode( bin->CanRead(), bin->CanWrite() ); 

 return;
}


WideStream::WideStream( WideStreamType t )
{
 type             = t;
 back_ch          = 0;
 back_pos         = 0;
 last_char_pos    = 0;
 cp               = NULL;

 // по умолчанию тэги пропускаются
 strip_decoration=true;

 SetMode( true, false );

 return;
}


WideStream::~WideStream(void)
{}


void WideStream::SetEncoding( const CodeConverter *Cp )
{
 cp = Cp;
 return;
}

const CodeConverter* WideStream::GetEncoding(void) const
{
 return cp;
}



void WideStream::wputs( const wchar_t *str )
{
 while( *str )
  wput( *(str++) );

 return;
}


void WideStream::write( const void *src, pos_type size )
{
 LEM_STOPIT;
}


Stream::pos_type WideStream::read( void *dest, pos_type size )
{
 LEM_STOPIT;
 return 0;
}


wchar_t WideStream::wget(void)
{
 if( back_ch )
  {
   wchar_t c=back_ch;
   last_char_pos = back_pos;
   back_ch=0;
   return c;
  }

 return Read_Char(); 
}


wchar_t WideStream::wpeek(void)
{
 wchar_t c = wget();
 unget(c);
 return c;
}



bool WideStream::skip_white2(void)
{
 bool eol=false;
 wchar_t c;
 if( back_ch )
  {
   c = back_ch;
   last_char_pos = back_pos;
   back_ch = 0;
  }
 else
  {
   c = Read_Char();
  }

 while( !eof() )
  {
   if( is_uspace(c) )
    {
     eol = c=='\r' || c=='\n';
     c = Read_Char();
     continue;
    }

   back_pos = last_char_pos;
   back_ch = c;
   break;
  }

 return eol;
}


bool WideStream::eof(void) const
{ return bin.IsNull() ? true : bin->eof(); }

void WideStream::flush(void)
{
 if( bin.NotNull() )
  bin->flush();

 return;
} 

int WideStream::get(void)
{
 wchar_t u = wget();

// if( u==L'\r' || u=='\n' )
//  was_eol=true;

 return (cp && cp->IsSingleByte())? ((const SBCodeConverter*)cp)->to_ascii(u) : static_cast<wchar_t>(u);
}

void WideStream::unget( wchar_t ch )
{
 back_ch=ch;
 //back_pos=bin->tellp();
 back_pos = last_char_pos;
 return;
}


void WideStream::put( char c )
{
 wchar_t u = (cp && cp->IsSingleByte()) ? ((const SBCodeConverter*)cp)->to_unicode(c) : static_cast<wchar_t>(c);
 wput(u);
}


Stream::pos_type WideStream::tellp(void) const
{ return back_ch ? back_pos : bin->tellp(); }


Stream::pos_type WideStream::seekp( off_type pos, int whereto )
{
 back_ch = 0;
 return bin->seekp( pos, whereto );
}

bool WideStream::move( off_type offset )
{ return bin->move(offset); }

void WideStream::close(void)
{
 if( bin.NotNull() ) bin->close();
 return;
}

Stream::pos_type WideStream::fsize(void) const
{ return bin->fsize(); }


#if defined LEM_UNICODE_EX && defined LEM_32 && defined LEM_MZ_CHARGUESSER

#include <nscore.h>
#include <nsUniversalDetector.h>

namespace
{

class MzCharsetGuesser : public nsUniversalDetector
{
 protected:
  const char * res;
  virtual void Report(const char* aCharset)
  {
   res = aCharset;
   return;
  }

 public:
  MzCharsetGuesser(void) : nsUniversalDetector( 0xffffffffU ), res(NULL) {}

 public:
  const char* Process( const char *data, int data_len )
  {
   nsresult rc = HandleData( data, data_len );
   DataEnd();
   Reset();
   return res;
  }
};

static MzCharsetGuesser *mz_charguesser = NULL;
static char * mz_buffer = NULL;

}

#endif

// ********************************************************
// Для бинарного потока подбирает лучший текстовый ридер.
// ********************************************************
lem::Ptr<WideStream> WideStream::GetReader( lem::Ptr<Stream> bin, const lem::CodeConverter *cp )
{
 int i1 = bin->get();
 int i2 = bin->get();
 int i3 = bin->get();

 lem::uint8_t c1 = i1;
 lem::uint8_t c2 = i2;
 
 if( i1==EOF )
  {
   // Пустой файл - не будем пропускать.
   bin->seekp(0);
   return lem::Ptr<WideStream>( new Char_Reader(bin) );
  }

 if( (c1==0xff && c2==0xfe) || (c1==0xfe && c2==0xff) )
  {
   bin->seekp(0);
   UTF16_Reader *r = new UTF16_Reader(SET_UNKNOWN,bin); 

   try
    {
     r->Read_Beginning();
    }
   catch(...)
    {
     delete r;
     throw;
    }

   return lem::Ptr<WideStream>(r);
  }

 // EF BB BF
 if( c1==0xef )
  {
   if( i2==EOF || i3==EOF )
    return lem::Ptr<WideStream>(); // NULL

   lem::uint8_t c3 = i3;

   bin->seekp(0);
   
   if( c2 == 0xbb && c3 == 0xbf )
    {
     UTF8_Reader *r = new UTF8_Reader(bin); 

     try
      {
       r->Read_Beginning();
      }
     catch(...)
      {
       delete r;
       throw;
      }

     return lem::Ptr<WideStream>(r);
    }
  }

 // BOM отсутствует.

 bin->seekp(0);

 // Если для сессии установлена кодировка utf-8, то открываем принудительно
 // UTF8-ридер, но без проверки BOM
 if( &lem::UI::get_UI().GetSessionCp() == lem::cp_utf8 )
  {
   UTF8_Reader *r = new UTF8_Reader(bin); 
   return lem::Ptr<WideStream>(r); 
  }

 #if defined LEM_ICU
 // Если для сессии установлена многобайтовая кодировка, то используем специализированный
 // ридер, который может обрабатывать такие тесты.
 if( lem::UI::get_UI().GetSessionCp().IsMultiByte() )
  {
   ICU_Reader *r = new ICU_Reader(&lem::UI::get_UI().GetSessionCp(),bin); 
   return lem::Ptr<WideStream>(r); 
  }
 #endif

 #if defined LEM_UNICODE_EX && defined LEM_32 && defined LEM_MZ_CHARGUESSER
 if( cp==NULL )
  {
   if( mz_charguesser==NULL )
    {
     mz_charguesser = new MzCharsetGuesser;
     mz_buffer = new char[2001];
    }

   memset( mz_buffer, 0, 2001 );
   bin->read( mz_buffer, 2000 );
   bin->rewind();

   const char *charset = mz_charguesser->Process( mz_buffer, 2000 );
   if( charset!=NULL )
    {
     if( strcmp(charset,"65001")==0 ||  strcmp(charset,"UTF-8")==0 )
      {
       UTF8_Reader *r = new UTF8_Reader(bin); 
       return lem::Ptr<WideStream>(r); 
      }

     cp = lem::CodeConverter::getConverter(charset);
    }   
  }
 #endif

 if( cp!=NULL )
  {
   // Используем явно заданную кодировку

   #if defined LEM_ICU
   if( cp->complex() )
    {
     ICU_Reader *r = new ICU_Reader( cp, bin );
     return lem::Ptr<WideStream>(r);
    }
   #endif
   Char_Reader *r = new Char_Reader(bin);
   r->SetEncoding(cp);
   return lem::Ptr<WideStream>(r);
  }

 // ASCII потоки для однобайтовых кодировок.
 Char_Reader *r = new Char_Reader(bin);
 r->SetEncoding( &lem::UI::get_UI().GetSessionCp() );
 return lem::Ptr<WideStream>(r); 
}


lem::Ptr<WideStream> WideStream::GetReader( const lem::Path &p, const lem::CodeConverter *cp )
{
 lem::Ptr<lem::Stream> bin( new BinaryReader(p) );
 return GetReader(bin,cp);
}


bool WideStream::skip_white(void)
{
 bool was_eol=false;

 while( !eof() )
  {
   wchar_t u = wget();
   if( u==WEOF )
    break;

   if( u==L'\r' || u=='\n' )
    was_eol=true;

   if( !lem::is_uspace(u) ) 
    {
     unget(u);
     break; 
    }
  }

 return was_eol;
}


bool WideStream::read_line( UFString &buffer )
{
 buffer.clear();
 while( !eof() )
  {
   const wchar_t c = wget();

//   if( (c==L'\n' || c==L'\r') && buffer.empty() )
//    break;

   if( c=='\r' )
    {
     wchar_t c2 = wget();
     if( c2!='\n' )
      unget(c2);
 
     break;
    }

   if( c==L'\n' || c==L'\r' || c==WEOF )
    break;

   buffer.Add_Dirty(c); 
  }

 buffer.calc_hash();

 return !buffer.empty();
}
 
// ***********************************************
// Текст целиком загружается в буфер
// ***********************************************
void WideStream::read_text( UFString &buffer )
{
 buffer.clear();
 while( !eof() )
  {
   const wchar_t c = wget();
   if( c==WEOF )
    break;
   buffer.Add_Dirty(c); 
  }

 buffer.calc_hash();
 return;
}

const lem::Path& WideStream::GetName(void) const
{
 if( !!bin )
  return bin->GetName();

 static lem::Path emptypath;
 return emptypath;
}

void WideStream::StripDecoration( bool f )
{ strip_decoration=f; }

void WideStream::wputs( const lem::UFString &str )
{
 wputs( str.c_str() );
 return;
}

void WideStream::wputs( const std::wstring &str )
{
 wputs( str.c_str() );
 return;
}
