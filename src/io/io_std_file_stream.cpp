// -----------------------------------------------------------------------------
// File IO_STD_FILE_STREAM.CPP
//
// (c) Koziev Elijah
//
// Content:
// Бинарные потоки ввода-вывода: класс StdFileStream - обертка для std'шного
// потока fstream.
// -----------------------------------------------------------------------------
//
// CD->02.03.1996
// LC->19.07.2008
// --------------

#include <lem/streams.h>

using namespace std;
using namespace lem;



StdFileStream::StdFileStream(
                             const lem::Path& filename,
                             bool for_read,
                             bool for_write,
                             bool for_append
                            )
 : Stream(for_read,for_write,filename)
{
/*
 // This code is non-portable, or extremely difficult to make portable.
 // One of the reasons - the type of ios::in, out, app VARIES among
 // C++ compilers. Even MinGW differs from GCC in mandrake 10.0 !!!

 #if defined LEM_BORLAND
 unsigned mode = ios::out;
 #elif defined LEM_MSC
 unsigned mode = ios::out;
 #elif defined LEM_GNUC
// unsigned mode = ios::out;
 std::_Ios_Openmode mode = ios::out;
 #else
 std::_Ios_Openmode mode = ios::out;
 #endif

 if( for_read )   mode = ios::in;
 if( for_write )  mode = ios::out;
 if( for_append ) mode = ios::app;

 stream = new fstream( filename, mode );
*/

 stream = NULL;

 if( for_read )
  {
   if( for_write )
    stream = new fstream( filename.GetAscii().c_str(), ios::in | ios::out );
   else
    stream = new fstream( filename.GetAscii().c_str(), ios::in );
  }
 else if( for_write )
  stream = new fstream( filename.GetAscii().c_str(), ios::in | ios::out );
 else if( for_append )
  stream = new fstream( filename.GetAscii().c_str(), ios::in | ios::app );

 do_del = true;

 return;
}


StdFileStream::StdFileStream(void)
{ stream=NULL; do_del=false; }

StdFileStream::StdFileStream( fstream *Stream )
{ stream=Stream; do_del=false; }



StdFileStream::~StdFileStream(void)
{
 if(do_del)
  delete stream;

 stream=NULL;
}


void StdFileStream::Check(void) const
{
}


void StdFileStream::write( const void *src, pos_type size )
{ stream->write( (const char*)src, (std::streamsize)size ); }

void StdFileStream::put( char Ch )
{ stream->put(Ch); }

lem::Stream::pos_type StdFileStream::read( void *dest, lem::Stream::pos_type size )
{
 stream->read( (char*)dest, (std::streamsize)size );
 return 0;
}

int StdFileStream::get(void)
{ return stream->get(); }

void StdFileStream::flush(void)
{ stream->flush(); }

void StdFileStream::close(void)
{ stream->close(); }

bool StdFileStream::eof(void) const
{ return stream->eof(); }

lem::Stream::pos_type StdFileStream::tellp(void) const
{ return stream->tellp(); }

lem::Stream::pos_type StdFileStream::seekp( lem::Stream::off_type /*to*/, int /*whereto*/ )
{ return (size_t)-1; }

bool StdFileStream::move( lem::Stream::off_type offset )
{
 stream->seekp(offset);
 return true;
}

lem::Stream::pos_type StdFileStream::fsize(void) const
{ return 0; }
