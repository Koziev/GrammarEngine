// -----------------------------------------------------------------------------
// File IO_TBS.H
//
// (c) Koziev Elijah
//
// Contens:
// Класс MemLinesStream используется для распечатки содержимого вариаторов и
// опорных контекстов в приятной форме.
// -----------------------------------------------------------------------------
//
// CD->19.12.1998
// LC->03.08.2009
// --------------

#ifndef SOL_TEXT_BSTREAM__H
#define SOL_TEXT_BSTREAM__H
#pragma once

 #include <lem/streams.h>

 namespace lem
 {
  class MemLinesStream : public lem::Stream
  {
   protected:
    std::vector<lem::UFString> line; // Строки хранящейся распечатки.

   public:
    MemLinesStream(void):Stream(false,true) {}

    virtual void put( char ch )
    {
     wput( 0x000000ff & ch );
     return;
    }

    virtual void wput( wchar_t ch )
    {
     if( line.empty() )
      line.push_back( L"" );

     if( ch==L'\n' )
      line.push_back( L"" );
     else if( ch==L'\r' )
      {}
     else
      line.back() += ch;

     return;
    }

    inline int GetnLine(void) const { return CastSizeToInt(line.size()); }
    inline const UFString& GetLine( int i ) const { return line[i]; }

    inline size_t GetLeft( int iline ) const
    {
     const UFString& s = line[iline];
     size_t ipos=0;
     while( s[ipos]==L' ' ) ipos++;
     return ipos;
    }

    inline size_t GetRight( int iline ) const
    { return line[iline].length(); }

    virtual void write( const void *src, pos_type size ) {};
    virtual pos_type read( void *dest, pos_type size ) { return 0; }
    virtual int get(void) { return 0; }

    virtual void flush(void) {};

    virtual bool eof(void) const { return false; }

    virtual lem::Stream::pos_type tellp(void) const { return 0; }

    virtual lem::Stream::pos_type seekp( lem::Stream::off_type pos, int whereto=SEEK_SET )
    { return (size_t)-1; }

    virtual bool move( lem::Stream::off_type offset )
    { return false; }

    virtual lem::Stream::pos_type fsize(void) const { return 0; }
    virtual void Check(void) const {}
    virtual void close(void) {}
  };

 } // namespace 'lem'

#endif
