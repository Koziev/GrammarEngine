#ifndef LEM_BSTREAM__H
#define LEM_BSTREAM__H
#pragma once

// File STREAMS.H
//
// (c) by Elijah Koziev    all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ supplementary library
//
// This header contains declarations of the stream classes which provide
// flexible input/output abstractions for byte character streams as well as
// concrete classes for reading and writing disk files, console and keyboard,
// and memory mapped files.
//
// �������� ������ �����-������, � ��� ����� - �������� �����. ������ �������
// ������� ������ ����������� �� ������������ ������ ���������� iostreams C++,
// �� �� �������� � �� �������� �� - ������� ������������ �� �����������.
// ������� ��������, ��� ������������ ����� ����������� �������, �������������
// � �������-��������.
//
// 07.01.2006 - ��� ������� ����������� ����� Guardian (��. runtime_checks.h).
//
// 05.04.2006 - � ������� ����� Stream ��������� ��������� eof_pos - ��������
//              ������������� ������� ������� ������ ��� �����.
//
// 30.05.2006 - � ������� ����� Stream �������� ����������� �����
//              IsDiskFile, ������� ��������� ��������, �������� �� �����
//              �������� �������� ������.
//
// 06.11.2006 - ������� ��������� �������� � ������� > 2Gb
//
// 05.01.2007 - ������� ������ rewind(), to_end()
//
// 14.04.2007 - ��� ������������� � gcc ������� ����������� ��������� fpos64_t(0)
//
// 24.05.2007 - ����� move ���������� bool ������� ���������� �����������, �
//              �� ����� ������� � �����, ��� ��� fseek ���������� ������ ����
//              �������. 
//
// 20.06.2007 - ������ ����� UrlFile ��� ������ � ���-��������.
//
// 04.08.2007 - �����������: �������������� BaseStream � Stream
// 20.06.2008 - ��������� ������ BinaryReader � BinaryWriter
// 19.07.2008 - refactoring: ����� ���������� ������� ���������� � *.cpp ������
//              ��� ��������� ������.
// 08.10.2009 - �������� ����� BinaryUpdater
// -----------------------------------------------------------------------------
//
// CD->02.03.1996
// LC->21.10.2014
// --------------

 #include <lem/config.h>

 #if defined LEM_MFC
  #include <afxwin.h>
 #endif

 #if defined LEM_WINDOWS
 #include <io.h>
 #endif

 #include <string>
 #include <iostream>
 #include <fstream>

 #include <boost/noncopyable.hpp>

 #include <stdio.h>
 #include <lem/cstring.h>
 #include <lem/path.h>
 #include <lem/runtime_checks.h>
 #include <lem/date_time.h>

 #if !defined LEM_SMART_REF__H
//  #include <lem/smart_pointers.h>
 #endif
 
 #if defined LEM_WINDOWS
  #include <wininet.h>
//  #include <mmsystem.h>
 #endif

 #if defined move
  #undef move
 #endif

 #if !defined LEM_WATCOM
  using std::string;
  using std::wstring;
  using std::ostream;
  using std::fstream;
 #endif

 namespace lem
 {
  // ********************************************************************
  // ������� ����� ��� ������ (������� �����-������) ��������� �����.
  // ����������� ����� - �������� ����� ������ ����������� �������. � ��
  // ���� ������ ��� ��������� �����������, ��� ��� ������������ ������
  // ������ �������������� ������� � ������ ��������������� ����������
  // �� �����.
  // ********************************************************************
  class Stream : boost::noncopyable
  {
   protected:
    #if LEM_DEBUGGING==1
    Guardian guard1;
    #endif

   private:
    lem::zbool readable, writable; // ����� �� ������ � �������: ������ � ������
                                   // Stream access flags

   protected:
    lem::zbool closable; // ������ �� ���������� ��������� ��������� handles ������
    lem::zbool binary;   // � �������� ������
    lem::zbool seekable; // ����� �� �������� ���������� ��������� ������-������
                         // does the stream allow random access

    lem::Path name; // ��� ������, ������ - ��� �����
                    // Disk file full path


   protected:
    #if LEM_DEBUGGING==1
    Guardian guard2;
    #endif

    // �������� ����� ������� � ������� - ����� �� ��� �������� � �������.
    inline void CheckWritable() const { LEM_CHECKIT_Z(!!writable); }
    inline void CheckReadable() const { LEM_CHECKIT_Z(!!readable); }

    inline void SetMode( bool Readable, bool Writable, bool Seekable=true )
    { readable=Readable; writable=Writable; seekable=Seekable; }

    inline void SetName( const lem::Path &FileName ) { name=FileName; }

    #if LEM_DEBUGGING==1
    inline void Assert() const
    {
     guard1.Assert();
     guard2.Assert();
    }
    #endif

    public:
     typedef size_t pos_type; // ��������� ������� ������/������
                              // (������ ��� �������� ������).
 
     typedef int off_type; // �������� ������� (����� �������� ���).

     enum { eof_pos=0xffffffffUL }; // ������� "��� �����"

     #if defined LEM_FILE64
     // ��������� �������� � ������� > 2Gb
     typedef fpos_t pos64_type;
     typedef fpos_t off64_type;
     #else
     typedef size_t pos64_type;
     typedef size_t off64_type;
     #endif

   public:
    Stream( bool Readable=true, bool Writable=true );
    Stream( bool Readable, bool Writable, const lem::Path &Name );

    virtual ~Stream();

    // ������ ����� ����������, �� ������� ��������� src, �������� size, �
    // ����� � ������� �������.
    virtual void write( const void *src, pos_type size )=0;

    // ������ ����� ���������� � ������� ������, �� ������� ��������� dest,
    // �������� size, � ������� �������.
    // ������������ ������� ����������� ����� ������. 
    virtual pos_type read( void *dest, pos_type size )=0;

    // ������ �� ������ ��� ���������� ��� ����� �� ����� ��������� ������?
    // ����� ����� ��� �������, ������� �������� � ������������ ����
    // ���������� ��� �����.
    virtual bool isready() const;

    // ���� ���������� ������ ������.
    virtual void wait_ready() const;

    // ������ ���������� �������. ����� ���������� EOF (-1) ��� ����������
    // ����� �����. ������������� ������� ������ � ����� �����.
    virtual int get()=0;

    inline int operator()() { return get(); }

    // ��������� ������ � ������� ������� � �����.
    virtual void put( char )=0;

    virtual void puts( const char *s );

    virtual void unget( char c );
    
    // ������ �� ������ UNICODE-�������.
    virtual wchar_t wget();

    // ������ � ����� UNICODE-�������
    virtual void wput( wchar_t );

    // ������ � ����� UNICODE-������
    virtual void wputs( const wchar_t *str );

    // ������ int � bool ��������
    void write_int(  int d );
    void write_bool( bool d );
    void write_uint8( lem::uint8_t d );

    void wr( const CString* s );
    void wr( const FString* s );
    void wr( const UCString* s );
    void wr( const UFString* s );
    void wr( const string* s );
    void wr( const wstring* s );
    void wr( const int* i );
    void wr( const bool* i );
    void wr( const char* str );

    void wr( const float* i );
    void wr( const double* i );
    void wr( const long double* i );

    void rd( CString* s );
    void rd( FString* s );
    void rd( UCString* s );
    void rd( UFString* s );
    void rd( std::string* s );
    void rd( wstring* s );
    void rd( int* i );
    void rd( bool* i );
    void rd( char* str );

    void scan_str( char* str, int nmax );

    void rd( float* i );
    void rd( double* i );
    void rd( long double* i );

    int read_int();
    bool read_bool();
    lem::uint8_t read_uint8();

    const CString read_string();
    const FString read_fstring();
    const UCString read_ustring();
    const UFString read_ufstring();

    virtual const lem::Path& GetName() const;

    // �������� �������� ��������� ������ - �� ���� �� ������ � ����������
    // ���������. ���� ����, �� ������ �������� ��������� �� ����� ���
    // ������������ ����������.
    virtual void Check() const;

    // ������������� ������� ����� � ������.
    virtual void flush()=0;

    // ������ true, ���� ��� ������ ��������� ����� �����.
    virtual bool eof() const=0;

    // ���������� ������� ������� ������� � ������.
    virtual pos_type tellp() const=0;

    virtual pos64_type tellp64() const;

    // ���������� ������ �� �������� �������: ����������� ������� �� ������
    // �����, ������� ������� ��� ����� �����, �������� ��������� where_to.
    // ��� ������� - ��. �������� ����������� ������� fseek(...).
    virtual pos_type seekp( off_type pos, int whereto=SEEK_SET )=0;

    // ��������� ������ (��������� �������) � ������.
    virtual void rewind(); 

    // ��������� ������ � �����.
    virtual void to_end(); 

    virtual pos64_type seekp64( off64_type pos, int whereto=SEEK_SET );

    // ����������� ������� ������������ ������� �������, � ������ ��� � �����
    // ����� �������� ����� �������� offset.
    virtual bool move( off_type offset )=0;

    // ���������� ������ ������ � ��������� �����.
    virtual void close()=0;

    // ���������� ������� ������ ������.
    virtual pos_type fsize() const=0;

    virtual pos64_type fsize64() const;

    // ���������� ��������� ���������� ��� ������ �� ���������...
    // ��� ����������� ������� ��� ������ �����, ������ ��� ������������
    // ������� ��� ���������� ��� ������� ����������� ��������� (���� ncurses)
    virtual void SetForeGroundColor( int /*iColor*/ );
    virtual void SetBackGroundColor( int /*iColor*/ );
    virtual void SetBlinkMode( bool /*blinks*/ );
    virtual void SetHighLightMode();
    virtual void SetLowLightMode();
    virtual void SetNormalMode();

    // ������ true, ���� ��� �������� ������ ��� ������ � ��� �������� ������ �
    // �� ���� ������������� ����������
    virtual bool is_failed() const;

    // ���������� ������� ���������� ������.
    inline bool IsBinary() const
    {
     #if LEM_DEBUGGING==1
     Assert();
     #endif
     return binary;
    }

    // ������������� ���������� ���� ����������� �������� ������ ���
    // ������������ ����������� ������.
    inline void SetClosable( bool f )  { closable=f; }

    inline bool CanWrite() const { return writable; }
    inline bool CanRead()  const { return readable; }
    inline bool CanSeek()  const { return seekable; }


    // ������ TRUE ���� ����� �������� � �������� �������� ������
    virtual bool IsDiskFile() const;

    // ���������� ����� �������� � ��������� ����������� �����
    virtual bool GetTimes(
                          boost::posix_time::ptime &creat,
                          boost::posix_time::ptime &modif
                         );

   // ��������� ����������� �����-������ (���� ����� �� ����������).
   virtual void NoBuffer();

   // ���� ����� ������������ ����� ������� �������� ����� wput � wputs, �� ������ >8,
   // ����� 8 - ������������ �����. 
   virtual int Bits_Per_Char() const;
  };


 //typedef lem::Ptr<Stream> StreamPtr;


 // ********************************************
 // ������� �������� ���� (����� FILE-������� C).
 // ********************************************
 class BinaryFile : public Stream
 {
  protected:
   FILE *file;

   #if LEM_DEBUGGING==1
   Guardian guard3; 
   #endif

   static int n_opened; // ��� ���������� ����� - ������� �������� ������.

   #if LEM_DEBUGGING==1
   inline void Assert() const
   {
    #if defined LEM_MSC && _MSC_VER<1300
    // ...
    #else
    lem::Stream::Assert();
    #endif
     
    guard3.Assert();
   }
   #endif

   void OpenDiskFile( const char *amode, const wchar_t *umode, bool do_throw );

  public:
   BinaryFile();
   BinaryFile( const lem::Path &filename );
   BinaryFile( FILE *f );
   BinaryFile( FILE *f, const lem::Path &filename );

   BinaryFile(
              const lem::Path &filename,
              bool for_read,
              bool for_write,
              bool for_append=false,
              bool text_mode=false,
              bool do_throw=true
             );

   BinaryFile(
              FILE *File,
              bool for_read,
              bool for_write,
              bool for_append=false,
              bool text_mode=false
             );

   // ���������� ����������� ������� �����, ���� �� ������� ������.
   ~BinaryFile();


   virtual void reopen( 
                       bool for_read,
                       bool for_write,
                       bool for_append=false,
                       bool text_mode=false,
                       bool do_throw=true      // �� ��������� ������������ ����������, ���� ���� �� �����������
                      );

   virtual bool is_failed() const;

   virtual void write( const void *src, pos_type size );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get();
   virtual void put( char ch );

   virtual void unget( char c );
   inline FILE* GetStream() { return file; }

   virtual void Check() const;
   virtual void flush();
   virtual bool eof() const;
   virtual pos_type tellp() const;
   virtual pos_type seekp( off_type to, int whereto=SEEK_SET );
   virtual bool move( off_type offset );
   virtual pos64_type tellp64() const;
   virtual pos64_type seekp64( off64_type to, int whereto=SEEK_SET );

   virtual void close();

   virtual pos_type fsize() const;
   virtual pos64_type fsize64() const;

   virtual bool GetTimes(
                         boost::posix_time::ptime &creat,
                         boost::posix_time::ptime &modif
                        );

   virtual bool IsDiskFile() const;

   // ������ ����������� (setvbuf).
   virtual void NoBuffer();
 };


 class BinaryReader : public BinaryFile
 {
  public:
   BinaryReader( const Path& filename );
 };

 class BinaryWriter : public BinaryFile
 {
  public:
   BinaryWriter( const Path& filename );
 };

 class BinaryUpdater : public BinaryFile
 {
  public:
   BinaryUpdater( const Path& filename );
 };


 // *******************************************
 // �������� ���� � ��������� �������.
 // *******************************************
 class TextFile : public BinaryFile
 {
  public:
   TextFile();
   TextFile(
            const Path& filename,
            bool for_read,
            bool for_write,
            bool for_append=false
           );


   // Read characters till EOL ('\n') reached, return collected
   // string.
   const FString read_till_eol();
 };


 class TextReader : public TextFile
 {
  public:
   TextReader();
   TextReader( const Path& filename );
 };

 class TextWriter : public TextFile
 {
  public:
   TextWriter();
   TextWriter( const Path& filename );
 };


 class StdTtyStream : public Stream
 {
  protected:
   ostream *stream;

  public:
   StdTtyStream();
   StdTtyStream( std::ostream *s );

   virtual void write( const void *src, pos_type size );
   virtual void put( char Ch );
   virtual pos_type read( void * /*dest*/, pos_type /*size*/ );
   virtual int get();

   inline operator ostream*() { return stream; }
   inline ostream* GetStream() { return stream; }

   virtual void Check() const;
   virtual void flush();
   virtual void close();
   virtual bool eof() const;
   virtual pos_type tellp() const;
   virtual pos_type seekp( off_type /*to*/, int /*whereto*/=SEEK_SET );
   virtual bool move( off_type /*offset*/ );
   virtual pos_type fsize() const;
 };

 // ******************************************************************
 // �������� �����, ���������� �� ����������� ��������� ������ fstream
 // ******************************************************************
 class StdFileStream : public Stream
 {
  protected:
   fstream *stream;
   bool do_del;          // ����� �� � ����������� ������� ������ stream.

  public:
   StdFileStream();
   StdFileStream( fstream *Stream );
   StdFileStream(
                 const Path& filename,
                 bool for_read,
                 bool for_write,
                 bool for_append=false
                );

   virtual ~StdFileStream();
   virtual void write( const void *src, pos_type size );
   virtual void put( char Ch );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get();
   virtual void Check() const;
   virtual void flush();
   virtual void close();
   virtual bool eof() const;
   virtual pos_type tellp() const;
   virtual pos_type seekp( off_type /*to*/, int /*whereto*/=SEEK_SET );
   virtual bool move( off_type offset );
   virtual pos_type fsize() const;
 };

 // *********************************************************************
 // ����� � ��������� ������� ������. ��� �� ����������� �� Stream
 // �����, ������� ��� ��������� ����������� � Stream. ������� -
 // ������������� ��������������� ���������� ������.
 //
 // � �������� ������ ��� ������ ��� ����� ������ ������������ ������
 // ������ Stream.
 // *********************************************************************
 class BitStream
 {
  protected:
   unsigned char mask;
   unsigned char rack;

   Stream *stream;
   bool del; // ������� �� stream � ����������� ������.

  public:
   BitStream();
   BitStream( Stream *Stream, bool Delete_Stream );

   ~BitStream();

   void OutputBit( int bit );
   void OutputBits( unsigned int bits, int bit_count );
   void put( char c ) { OutputBits( (unsigned char)(c), 8 ); }

   int InputBit();
   unsigned int InputBits( int bit_count );
   int get() { return int(0x000000ffUL&InputBits(8)); }

   // ���� ����� �� �������� � ����� ������, ��� ��� ���� �������� ����������
   // ���, �� ����������� �� ������� �����, �� ������ ������� ������ ��������
   // ���������� � ��������� ������� ����� � �����.
   void flush()
   {
    if( mask!=0x80 )
     {
      put(rack);
      mask=0x80;
     }
   }

   inline bool eof() { return stream->eof(); }

   inline Stream* GetStream() { return stream; }
 };



 /**************************************************************************
                         ������� ������.

  ��������� ����� ���� ������-���������� ��� ��������. ���� ��������
  ��������� ���� � ���������� ������� ������ �� �������, �� ��� �������
  ������������� �� �������� ����. ��������������� �� ������������ ����������
  ������ ����� �� ������������.
 ***************************************************************************/

 class MemStream : public lem::Stream
 {
  protected:
   // ��������� �� ��������� ���� ������ c �����������.
   // ��������: ��� �� null-terminated string!!!
   char **block;

   #if LEM_DEBUGGING==1
   Guardian guard4;
   #endif

   char *w_block;   // ��������������� ���� - ��� ������

   #if LEM_DEBUGGING==1
   Guardian guard5;
   #endif

   size_t cursor;    // ��������� �� ����. ����
   size_t step;      // ��� ���������� ����� ������.
   size_t size;      // ������ ������ �����
   size_t occupied;  // ������� ������ ������ � ����� �������� �����������
   lem::zbool allocatable; // ����� �� �������� ������� �����

   void reallocate( size_t new_size );
   void reallocate(); // ���������� ����� ������.

   #if LEM_DEBUGGING==1
   inline void Assert() const
   {
    #if !defined LEM_MSC || _MSC_VER>=1300
    lem::Stream::Assert();
    #endif
     
    guard4.Assert();
    guard5.Assert();
   }
   #endif

  public:
   MemStream();

   MemStream(
             char **Block,
             bool for_read,
             bool for_write,
             size_t Size=0,
             size_t Step=65536
            );

   MemStream( bool for_write );

   ~MemStream();

   void SetReadable();

   virtual void write( const void *src, pos_type size );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get();
   virtual void put( char ch );
   virtual void unget( char c );

   virtual void Check() const;

   virtual void flush();

   void clear();

   char* PickBlock();

   const FString string() const;

   virtual const char* get_Block() const;

   lem::FString Hex() const;

   virtual bool eof() const;

   virtual pos_type tellp() const;

   virtual pos_type seekp( lem::Stream::off_type to, int whereto=SEEK_SET );

   virtual bool move( lem::Stream::off_type offset );

   virtual void close();
   virtual pos_type fsize() const;
 };


 // *******************************************************************
 // ����������� ����� ��� ����������� ���������� ������ �� ��������
 // ������� ������. ��� ������ ���������� ��� �������� ��������� ������,
 // ��������� � ������� � ���������.
 // *******************************************************************
 class MemReadStream : public MemStream
 {
  private:
   const char *rblock; // ��������� �� ���� ������ c �����������

  public:
   MemReadStream( const char *rBlock );
   MemReadStream( const void *rBlock, size_t Size );

   virtual pos_type read( void *dest, pos_type size );
   virtual int get();
   virtual void unget( char c );

   virtual bool eof() const { return cursor>=size; }

   virtual pos_type tellp() const { return (long)cursor; }

   virtual void close() {}
   virtual pos_type fsize() const { return size; }
   virtual void Check() const { LEM_CHECKIT_Z(rblock!=NULL); }
   virtual const char* get_Block() const { return (const char*)rblock; }
   virtual pos_type seekp( lem::Stream::off_type to, int whereto=SEEK_SET );
 };


 class MemReadHexStream : public lem::Stream
 {
  private:
   int size;
   lem::uint8_t *block;
   int cursor;
     
  public:
   MemReadHexStream( const char *HexData );
   MemReadHexStream( const wchar_t *HexData );
   virtual ~MemReadHexStream();

   virtual pos_type read( void *dest, pos_type size );
   virtual int get();
   virtual void unget( char c );

   virtual bool eof() const;

   virtual pos_type tellp() const { return cursor; }
   virtual pos_type seekp( lem::Stream::off_type to, int whereto=SEEK_SET );
   virtual bool move( lem::Stream::off_type offset );

   virtual void close() {}
   virtual pos_type fsize() const { return size; }
   virtual void Check() const;

   virtual void write( const void *src, pos_type size ) { LEM_STOPIT; }
   virtual void put( char ch ) { LEM_STOPIT; }
   virtual void flush() {}
 };


 /*****************************************************************
  ����������� ����� ��� ������� TTY (������ �� ���������-��������
  ��������� ��� ��� ��������). ���������� ���������� ��������� ����
  �� ����� - �� ���������� ����������� ������������ ���������
  �������, ������� ������ �������������� �����������.

  ����� �������� ������ �������� � ���������� - ��� ������ ������
  � ���������� ���� ������������ std::stdin ��� lem::KbdStream.
 ******************************************************************/
 class TtyStream : public Stream
 {
  protected:
   #if defined LEM_WINDOWS && !defined LEM_DOT_NET
   int fg, bg; // Foreground and background current colors 
   #endif

   TtyStream( const TtyStream &x );
   void operator =( const TtyStream &x );

  public:
   TtyStream();

   virtual ~TtyStream();

   virtual void write( const void *src, size_t size );
   virtual pos_type read( void * /*dest*/, size_t /*size*/ );
   virtual int get();

   virtual void put( char Ch );
   virtual void puts( const char *s );

   void write_string( const CString& s );
   void write_fstring( const FString& s );

   virtual void flush();
   virtual bool eof() const;
   virtual lem::Stream::pos_type tellp() const;
   virtual lem::Stream::pos_type seekp( off_type /*pos*/, int /*whereto*/=SEEK_SET );
   virtual bool move( off_type /*offset*/ );
   virtual void close();
   virtual pos_type fsize() const;

   // ���������� ��������� ���������� ��� ������ �� ���������...
   virtual void SetForeGroundColor( int iColor );
   virtual void SetBackGroundColor( int iColor );
   virtual void SetBlinkMode( bool blinks );
   virtual void SetHighLightMode();
   virtual void SetLowLightMode();
   virtual void SetNormalMode();
 };


 
 // **********************************************************
 // Basic tty implementation: no colors and other attributes
 // **********************************************************
 class TtyStreamStd : public Stream
 {
  protected:
   TtyStreamStd( const TtyStreamStd &x );
   void operator =( const TtyStreamStd &x );

  public:
   TtyStreamStd();

   virtual ~TtyStreamStd();

   virtual void write( const void *src, size_t size );
   virtual pos_type read( void * /*dest*/, size_t /*size*/ );

   virtual int get();

   virtual void put( char Ch );
   virtual void puts( const char *s );

//   void write_string( const CString& s );
//   void write_fstring( const FString& s );

   virtual void flush();
   virtual bool eof() const;
   virtual pos_type tellp() const;

   virtual pos_type seekp( off_type /*pos*/, int /*whereto*/=SEEK_SET );

   virtual bool move( off_type /*offset*/ );

   virtual void close();

   virtual pos_type fsize() const;

   virtual void SetForeGroundColor( int iColor );
   virtual void SetBackGroundColor( int iColor );
   virtual void SetBlinkMode( bool blinks );
   virtual void SetHighLightMode();
   virtual void SetLowLightMode();
   virtual void SetNormalMode();
 };

 // ******************************************************
 // ******************************************************
 #if defined LEM_UNICODE_CONSOLE

 #if defined LEM_WINDOWS
 // UNICODE-������ ������� - ��� MS Windows ������� � W2k
 class TtyUcs2Stream : public TtyStream
 {
  public:
   TtyUcs2Stream();

   virtual void wput( wchar_t );
   virtual int Bits_Per_Char() const;
 };
 #endif

 // ��� ������ �� UTF8 ������� ��� Linux
 #if defined LEM_LINUX || defined LEM_DARWIN
 class TtyUtf8Stream : public TtyStreamStd
 {
  public:
   TtyUtf8Stream();

   virtual void put( char Ch );
   virtual void wput( wchar_t );
 };
 #endif

 #endif


 // ****************************************************************
 // ����� ��� ����� � ��������� (��� �� ���� �������� ���������).
 // ****************************************************************
 class KbdStream : public Stream
 {
  public:
   KbdStream();
   ~KbdStream();

   virtual bool isready() const;
   virtual const FString read_fstring();

   virtual void write( const void * /*src*/, size_t /*size*/ );
   virtual pos_type read( void * /*dest*/, size_t /*size*/ );
   virtual void put( char /*ch*/ );
   virtual int get();
   virtual bool eof() const;
   virtual pos_type tellp() const;
   virtual pos_type seekp( off_type /*pos*/, int /*whereto*/=SEEK_SET );
   virtual bool move( off_type /*offset*/ );
   virtual void close();
   virtual pos_type fsize() const;
   virtual void flush();
 };


 // ********************************************************************
 // ����������� ����� ������ ��������� �� �������. ����� ��������
 // ��������� �� ��������, � ���������� ���� � ��� ����� - ��� �������
 // � ���������� ��.
 // ********************************************************************
 class ErrStream : public MemStream
 {
  public:
   ErrStream():MemStream(true) {}

   virtual void flush();
 };

  // ********************************************************************** 
  // ���������� ������ ������ ������� ���������� � ������ ����� (��� �����,
  // ���� ������� �������� size).
  // ********************************************************************** 
  extern void copy_file( lem::Stream &dst, lem::Stream &src, size_t size=0 );

  //extern FString* load_whole_file( const lem::Path& filename );
  //extern FString* load_whole_file( lem::BinaryFile &bin );

  // ��� ��� ���������� ��� Linux �� ��������� ���������������
  // ���������� fpos_t � 0, �� ����� ������������ ������ 
  // �������.
  inline bool fpos64_not_zero( const lem::Stream::pos64_type &p )
  { 
   #if defined LEM_WINDOWS
   return p!=0;
   #else
   const char* pp = (const char*)&p;
   for( size_t i=0; i<sizeof(p); i++ )
    if( pp[i]!=0 )
     return true;

   return false;   
   #endif
  }

  inline void fpos64_clear( lem::Stream::pos64_type &p )
  { 
   #if defined LEM_WINDOWS
   p=0;
   #else
   memset( &p, 0, sizeof(p) );
   #endif
  }

  
  inline bool fpos64_neq( const lem::Stream::pos64_type &a, const lem::Stream::pos64_type &b )
  { 
   #if defined LEM_WINDOWS
   return a!=b;
   #else
   return !!memcmp( &a, &b, sizeof(a) );
   #endif
  }



 struct ProxyConfig
 {
  typedef enum { NoProxy, AutoProxy, Forced } ProxyType;
  ProxyType type;

  lem::FString ip_port, locals;

  ProxyConfig();
  ProxyConfig( const lem::FString &address );
  ProxyConfig( const ProxyConfig &x );
  void operator=( const ProxyConfig &x );

  inline bool IsAuto() const { return type==AutoProxy; }
  inline bool IsForced() const { return type==Forced; }
  inline bool IsDisabled() const { return type==NoProxy; }

  inline void Disable() { type = NoProxy; }
 };

 extern ProxyConfig AutoProxy;
 extern ProxyConfig NoProxy;


 // ********************************************
 // ����� ��� ������ ���������� � ���-��������
 // ********************************************
 #if defined LEM_CURL
 struct fcurl_data;
 class UrlFile : public Stream
 {
  protected:
   fcurl_data *file;

  public:
   UrlFile( const lem::Path &url, ProxyType proxy=AutoProxy );
   //UrlFile( const lem::Url &url, ProxyType proxy=AutoProxy );

   // ���������� ����������� ������� �����, ���� �� ������� ������.
   ~UrlFile();

   virtual bool is_failed() const;

   virtual void write( const void *src, pos_type size );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get();
   virtual void put( char ch );

   virtual void unget( char c );

   virtual void Check() const;

   virtual void flush();

   virtual bool eof() const;

   virtual pos_type tellp() const;

   virtual pos_type seekp( off_type to, int whereto=SEEK_SET );

   virtual bool move( off_type offset );

   virtual pos64_type tellp64() const;
   virtual pos64_type seekp64( off64_type to, int whereto=SEEK_SET );
   virtual lem::uint64_t fsize64() const;

   virtual void close();

   virtual pos_type fsize() const;

   virtual bool GetTimes(
                         boost::posix_time::ptime &creat,
                         boost::posix_time::ptime &modif
                        );

   virtual bool IsDiskFile() const { return false; }
 };

 #elif defined LEM_WINDOWS

 class Url;

 class UrlFile : public MemStream
 {
  public:
 
  protected:
   HINTERNET hInternetSession;
   bool InitSession( const ProxyConfig& proxy );
   void CloseSession();

   lem::uint8_t *MemoryBlock;

   void Download( const lem::FString &url );

  public:
   UrlFile( const lem::Path &url, const ProxyConfig& proxy=lem::AutoProxy );
   UrlFile( const lem::Url &url, const ProxyConfig& proxy=lem::AutoProxy );
   ~UrlFile();
 };

 #endif


 #if defined LEM_WINDOWS
 // ********************************************
 // ������� ������ ������ ��� ������ ������ ��
 // �������� ������ - ����� Memory Mapped File.
 // ********************************************
 class FastFileReader : public Stream
 {
  protected:
   HANDLE hFile;
   HANDLE hFileMap;
   lem::uint8_t *OrgAdr; // ��������� ����� �������������� �����
   lem::uint8_t *EndAdr; // ��-��������� ������
   lem::uint8_t *CurAdr; // ������� ������� ������� ��� ������
   LARGE_INTEGER filesize; // ������ �����
   
  public:
   FastFileReader( const lem::Path &filename );

   ~FastFileReader();

   virtual bool is_failed() const;

   virtual void write( const void *src, pos_type size );
   virtual pos_type read( void *dest, pos_type size );
   virtual int get();
   virtual void put( char ch );

   virtual void unget( char c );

   virtual void Check() const;
   virtual void flush();

   virtual bool eof() const;

   virtual pos_type tellp() const;
   virtual pos_type seekp( off_type to, int whereto=SEEK_SET );

   virtual bool move( off_type offset );
   virtual pos64_type tellp64() const;
   virtual pos64_type seekp64( off64_type to, int whereto=SEEK_SET );
   virtual pos64_type fsize64() const;
   virtual void close();

   virtual pos_type fsize() const;
   virtual bool IsDiskFile() const;

   #if defined LEM_WINDOWS
   const lem::uint8_t* CurPtr() const { return CurAdr; }
   #endif
 };
 #endif


 } // end of namespace 'lem'

#endif
