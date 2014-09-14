// -----------------------------------------------------------------------------
// File IO_BASE_STREAM.CPP
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ supplementary library
// Ѕинарные потоки ввода-вывода, обслуживаютс€ как дисковые файлы (BinaryFile),
// так и отображенные в оперативную пам€ть (MemoryFile). ѕредназначены в
// основном дл€ использовани€ в классах более высокого уровн€ (BaseSource и
// OFormatter) - парсерах ввода и форматтерах вывода.
// -----------------------------------------------------------------------------
//
// CD->02.03.1996
// LC->28.02.2009
// --------------

#include <lem/path.h>
#include <lem/system_config.h>
#include <lem/streams.h>

using namespace std;
using namespace lem;


Stream::Stream( bool Readable, bool Writable )
{ binary=true; readable=Readable; writable=Writable; closable=false; }



Stream::Stream( bool Readable, bool Writable, const lem::Path &Name )
 :name(Name)
{ binary=true; readable=Readable; writable=Writable; closable=false; }

Stream::~Stream(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
}


bool Stream::isready(void) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
 return true;
}


void Stream::wr( const FString* s )
{
 size_t l=s->length();
 write( &l, sizeof(l) );
 if( l )
  write( s->c_str(), l+1 );
 return;
}

void Stream::wr( const UFString* s )
{
 size_t l=s->length();
 write( &l, sizeof(l) );
 if( l )
  write( s->c_str(), sizeof(UFString::value_type)*(l+1) );

 return;
}

void Stream::puts( const char *s )
{
 write( s, strlen(s) );
 return;
}

void Stream::write_int( int d )
{ write( &d, sizeof(d) ); }

void Stream::write_bool( bool d )
{ write( &d, sizeof(d) ); }

void Stream::write_uint8( lem::uint8_t d )
{ write( &d, sizeof(d) ); }


lem::uint8_t Stream::read_uint8(void)
{
 lem::uint8_t d=0;
 read( &d, sizeof(d) );
 return d;
}


void Stream::wr( const lem::CString* s )
{ write(s,sizeof(*s)); }

void Stream::wr( const UCString* s )
{ write(s,sizeof(*s)); }

void Stream::wr( const int* i )
{ write(i,sizeof(*i)); }

void Stream::wr( const bool* i )
{ write(i,sizeof(*i)); }


#if !defined LEM_NOREAL
void Stream::wr( const float* i )
{ write(i,sizeof(float)); }

void Stream::wr( const double* i )
{ write(i,sizeof(double)); }

void Stream::wr( const long double* i )
{ write(i,sizeof(long double)); }
#endif



void Stream::rd( int* i )
{ read(i,sizeof(*i)); }

void Stream::rd( bool* i )
{
 read(i,sizeof(bool));
 #if LEM_DEBUGGING==1
 LEM_CHECKIT_Z( *i==0 || *i==1 );
 #endif
}

#if !defined LEM_NOREAL
void Stream::rd( float* i )
{ read(i,sizeof(float)); }

void Stream::rd( double* i )
{ read(i,sizeof(double)); }

void Stream::rd( long double* i )
{ read(i,sizeof(long double)); }

void Stream::rd( UCString *x )
{ read(x,sizeof(*x)); }

void Stream::rd( UFString *x )
{ *x = read_ufstring(); }

void Stream::rd( FString *x )
{ *x = read_fstring(); }


#endif



int Stream::read_int(void)
{
 int res=0;
 rd( &res );
 return res;
}

bool Stream::read_bool(void)
{
 bool res=0;
 rd( &res );
 return res;
}

const lem::CString Stream::read_string(void)
{
 lem::CString buffer;
 read( &buffer, sizeof(buffer) );
 return buffer;
}

const lem::FString Stream::read_fstring(void)
{
 lem::FString buffer;

 size_t l;
 read(&l,sizeof(l));

 if( l )
  {
   char *dummy = new char[ int(l+size_t(1)) ];
   read( dummy, l+size_t(1) );
   buffer=dummy;
   delete[] dummy;
  }

 return buffer;
}

const lem::UFString Stream::read_ufstring(void)
{
 lem::UFString buffer;

 size_t l;
 read(&l,sizeof(l));

 if( l )
  {
   wchar_t *dummy = new wchar_t[ int(l+size_t(1)) ];
   read( dummy, sizeof(UFString::value_type) * ( l+size_t(1) ) );
   buffer=dummy;
   delete[] dummy;
  }

 return buffer;
}


// «амена fscanf( ... "%s" ... );
// 18.07.2006 - добавлен параметр nmax дл€ защиты от overrun'а
void Stream::scan_str( char* str, int nmax )
{
 int i=0;
 *str=0;
 while( !eof() )
  {
   int c = get();
   if( c == EOF )
    break;

   if( c=='\r' || c=='\n' || !c )
    {
     unget(c);
     break;
    }

   if( i<nmax-1 )
    // —имволы за пределы буфера не вписываем, но продолжаем
    // считывание.
    str[i++] = c;
  }

 str[i] = 0;
 return;
}


void Stream::wait_ready(void) const
{
 while(!isready());
 return;
}

// *******************************************************************
// «агружаем целиком содержимое указанного потока в текстовую строку.
// ‘айл должен быть текстовым, иначе первый же встретившийс€ нулевой
// символ приведет к завершению строки и часть данных будет потер€на.
// *******************************************************************
FString* lem::load_whole_file( const lem::Path& filename )
{
 BinaryFile bin( filename, true, false );
 return load_whole_file(bin);
}

FString* lem::load_whole_file( BinaryFile &bin )
{
 BinaryFile::pos_type fs = bin.fsize();

 char *text = (char*)malloc( fs+1 );
 bin.read( text, fs );
 text[fs]=0;

 return new FString( text, true );
}


bool Stream::GetTimes(
                          boost::posix_time::ptime &creat,
                          boost::posix_time::ptime &modif
                         )
{
 return false;
}


void Stream::rewind(void)
{
 seekp(0);
 return;
}

void Stream::to_end(void)
{
 seekp(0,SEEK_END);
 return;
}


wchar_t Stream::wget(void)
{
 LEM_STOPIT;
 #if !defined LEM_BORLAND
 return 0;
 #endif
}

void Stream::wput( wchar_t )
{ LEM_STOPIT; }

void Stream::wputs( const wchar_t *str )
{ LEM_STOPIT; }

void Stream::unget( char c )
{ LEM_STOPIT; }

Stream::pos64_type Stream::tellp64(void) const
{
 LEM_STOPIT;
 #if !defined LEM_BORLAND
 return 0;
 #endif
}

Stream::pos64_type Stream::seekp64( off64_type pos, int whereto )
{
 LEM_STOPIT;
 #if !defined LEM_BORLAND
 return 0;
 #endif
}


const lem::Path& Stream::GetName(void) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
 return name;
}


void Stream::Check(void) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
}


lem::uint64_t Stream::fsize64(void) const
{ return fsize(); }


void Stream::SetForeGroundColor( int /*iColor*/ ) {}
void Stream::SetBackGroundColor( int /*iColor*/ ) {}
void Stream::SetBlinkMode( bool /*blinks*/ ) {}
void Stream::SetHighLightMode(void) {}
void Stream::SetLowLightMode(void) {}
void Stream::SetNormalMode(void) {}

bool Stream::is_failed(void) const { return false; }

bool Stream::IsDiskFile(void) const { return false; }

void Stream::NoBuffer(void) {}

int Stream::Bits_Per_Char(void) const
{ 
 // ѕо умолчанию потоки однобайтовые.
 return 8;
}
