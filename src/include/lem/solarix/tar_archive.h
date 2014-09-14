// ----------------------------------------------------------------------------
// File TAR_ARCHIVE.H
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
// Обертка для методов работы с TAR архивами. Сделано специально для поисковых
// утилит, для распаковки на лету архивов и просмотра файлов в этих архивах.
//
// 14.04.2008 - компилируется только с макросом SOLARIX_PREMIUM или FAIND_TAR
// ----------------------------------------------------------------------------
//
// CD->19.12.2004
// LC->14.04.2008
// --------------

#ifndef LEM_TAR__H
#define LEM_TAR__H
#pragma once

 #if defined SOLARIX_PREMIUM || defined FAIND_TAR

#include <lem/fstring.h>
#include <lem/streams.h>
#include <lem/smart_pointers.h>
#include <lem/solarix/base_archive.h>

namespace lem
{
 namespace Pack
 {
  namespace Tar
  {
   using lem::Pack::Base_Archive;

  const int OUTBUFSIZ   = 2048;
  const int UNC_OUTBUFSIZ = 8192;

  enum { CMD_DONOTHING, CMD_EXTRACT, CMD_EXTRACT_NOPATH, CMD_LIST, CMD_TEST,
          CMD_UNPACK };

  enum { HEADER_GZIP=1, HEADER_PKZIP, HEADER_PKZIP_END };

  struct TARHEADER
  {
    char name[100];
    char operm[8];
    char ouid[8];
    char ogid[8];
    char osize[12];
    char otime[12];
    char ocsum[8];
    char flags;
    char filler[355];
  };

  /* gzip header bit flag definitions */
  const int IS_MULTI = 2;
  const int IS_EXTRA = 4;
  const int IS_FILENAME = 8;
  const int IS_COMMENT = 16;
  const int IS_ENCRYPT = 32;

  /* pkzip header bit flag definitions */
  const int PK_IS_ENCRYPT = 1;
  const int PK_IS_ENDHEADER = 9;
  const int PK_IS_EXTENDED = 8;

  extern lem::uint16_t mask_bits[];

  struct gzip_hdr
  {
   lem::uint16_t magic;
   lem::uint8_t method;
   lem::uint8_t flags;
   lem::uint32_t time;
   lem::uint8_t extra_flags;
   lem::uint8_t os;
  };

  struct pkzip_hdr
  {
   unsigned long magic;
   unsigned char version;
   unsigned char os;
   unsigned int bitflag;
   unsigned int method;
   unsigned int modtime;
   unsigned int moddate;
   unsigned long crc32;
   unsigned long c_size;
   unsigned long u_size;
   unsigned int filename_size;
   unsigned int extra_field_length;
  };


  struct gzip_end
  {
   lem::uint32_t crc32;
   lem::uint32_t size;
  };

  struct pkzip_end
  {
   long magic; /* NO magic number according to APPNOTE.TXT,
                  but to ensure compability with Tar, we add it ... uuuh... */
   unsigned long crc32;
   unsigned long comp_size;
   unsigned long size;
  };



/* Huffman code lookup table entry--this entry is four lem::uint8_ts for machines
   that have 16-bit pointers (e.g. PC's in the small or medium model).
   Valid extra bits are 0..13.  e == 15 is EOB (end of block), e == 16
   means that v is a literal, 16 < e < 32 means that v is a pointer to
   the next table, which codes e - 16 bits, and lastly e == 99 indicates
   an unused code.  If a code with e == 99 is looked up, this implies an
   error in the data. */
  struct huft
  {
   lem::uint8_t e;               /* number of extra bits or operation */
   lem::uint8_t b;               /* number of bits in this code or subcode */
   union {
           lem::uint16_t n;            /* literal, length base, or distance base */
           huft *t;     /* pointer to next level of table */
         } v;
  };


class TAR_Archive : public Base_Archive
{
 private:
  int command; 
  int headertype;

  pkzip_hdr pk_header;
  gzip_hdr gz_header;

  unsigned char slide[0x8000];

  FString unpacked_name;

  int outcnt;
  lem::uint32_t outsiz;
  lem::uint8_t *outptr;
  lem::uint8_t *outbuf;

  unsigned wp;            /* current position in slide */
  lem::uint32_t bb;                       /* bit buffer */
  unsigned bk;                    /* bits in bit buffer */
  lem::uint16_t bytebuf;

  int datapos;
  int position;
  long size;

  int lbits;          /* bits in base literal/length lookup table */
  int dbits;          /* bits in base distance lookup table */

  int error;

  unsigned hufts;    /* track memory usage */

  bool first_ungzipped_block;
  bool extract_gzip;

  int read_tar_header( const lem::uint8_t *bytes, int size );
  int istarheader( unsigned char *hdr, long csum, char askflag );
  int read_tar_header(void);
  int read_gzip_header(void);
  int read_pkzip_header(void);
  unsigned long updcrc( lem::uint8_t *s, unsigned long n );
  int extract_tar(void);
  int untarstream( lem::uint8_t data[], unsigned long datasize );
  int listtarstream( lem::uint8_t data[], unsigned long datasize );
  int FlushOutput(void);
  int ReadByte( lem::uint16_t *x );
  int inflate_entry(void);
  int inflate_block( int *e );
  int inflate_dynamic(void);
  int inflate_fixed(void);
  int inflate_stored(void);
  int inflate_codes( huft *tl, huft *td, int bl, int bd );
  void flush( unsigned w );
  int huft_free( huft *t );

  int huft_build(
                 unsigned *b,
                 unsigned n,
                 unsigned s,
                 lem::uint16_t *d,
                 lem::uint16_t *e,
                 huft **t,
                 int *m );

 public:
  TAR_Archive(void);
  ~TAR_Archive(void);

  bool Open( boost::shared_ptr<Stream> Stream, const Solarix::Search_Engine::PluginOptions *Options );
  void Extract_Files( Base_File_Processor &x );

  virtual const lem::Path Extract_File( const UFString &filename, lem::Pack::Base_File_Processor &x ) { return lem::Path(); }
};

    class ITARUnpacker : public IUnpackerFactory
    {
     public:
      ITARUnpacker(void) {}

      virtual Base_Archive* New(void *ptr=NULL) const { return new TAR_Archive(); }
    };


   } // namespace Tar
  } // namespace Pack
 } // namespace lem


 #endif // #if defined SOLARIX_PREMIUM || defined FAIND_TAR

#endif
