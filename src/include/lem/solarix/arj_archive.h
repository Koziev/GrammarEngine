// -----------------------------------------------------------------------------
// File ARJ_ARCHIVE.H
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
// LEM C++ supplementary library
// Обертка для методов работы с ARJ архивами. Сделано специально для поисковых
// утилит, для распаковки на лету архивов и просмотра файлов в этих архивах.
//
// 14.04.2008 - компилируется только с макросом SOLARIX_PREMIUM или FAIND_ARJ
// -----------------------------------------------------------------------------
//
// CD->22.12.2004
// LC->17.05.2008
// --------------

#pragma once

#if defined SOLARIX_PREMIUM || defined FAIND_ARJ

#if !defined ARJ_ARCHIVE__H
 #define ARJ_ARCHIVE__H

 #include <limits.h>
 #include <stdio.h>
 #include <lem/streams.h>
 #include <lem/solarix/base_archive.h>

 namespace lem
 {
  namespace Pack
  {
   namespace Arj
   {
    using lem::Stream;
    
 #define CODE_BIT          16

 /* size of self-extracting prefix */
 #define MAXSFX            500000L
 #define FNAME_MAX         512
 #define FIRST_HDR_SIZE    30
 #define FIRST_HDR_SIZE_V  34
 #define COMMENT_MAX       2048
 #define HEADERSIZE_MAX   (FIRST_HDR_SIZE + 10 + FNAME_MAX + COMMENT_MAX)

#define THRESHOLD    3
#define DDICSIZ      26624
#define MAXDICBIT   16
#define MATCHBIT     8
#define MAXMATCH   256

#undef NC 
#define NC          (UCHAR_MAX + MAXMATCH + 2 - THRESHOLD)

#define NP          (MAXDICBIT + 1)
#define CBIT         9
#define NT          (CODE_BIT + 3)
#define PBIT         5
#define TBIT         5

#if NT > NP
#define NPT NT
#else
#define NPT NP
#endif

#define CTABLESIZE  4096
#define PTABLESIZE   256

extern char M_VERSION [];

extern char M_ARCDATE [];
extern char M_ARCDATEM[];
extern char M_BADCOMND[];
extern char M_BADCOMNT[];
extern char M_BADHEADR[];
extern char M_BADTABLE[];
extern char M_CANTOPEN[];
extern char M_CANTREAD[];
extern char M_CANTWRIT[];
extern char M_CRCERROR[];
extern char M_CRCOK   [];
extern char M_DIFFHOST[];
extern char M_ENCRYPT [];
extern char M_ERRORCNT[];
extern char M_EXTRACT [];
extern char M_FEXISTS [];
extern char M_HEADRCRC[];
extern char M_NBRFILES[];
extern char M_NOMEMORY[];
extern char M_NOTARJ  [];
extern char M_PROCARC [];
extern char M_SKIPPED [];
extern char M_SUFFIX  [];
extern char M_TESTING [];
extern char M_UNKNMETH[];
extern char M_UNKNTYPE[];
extern char M_UNKNVERS[];

  typedef void voidp;
  typedef unsigned char  uchar;   /*  8 bits or more */
  typedef unsigned int   uint;    /* 16 - 32 bits or more */
  typedef unsigned short ushort;  /* 16 bits or more */
  typedef unsigned long  ulong;   /* 32 bits or more */
  typedef ulong UCRC;     /* CRC-32 */

  using lem::Pack::Base_Archive;

 class ARJ_Archive : public Base_Archive
{
 private:
  UCRC crc;
 
  ushort bitbuf;
  long   compsize;
  long   origsize;
  uchar  subbitbuf;
  uchar  header[HEADERSIZE_MAX];
  char   arc_name[FNAME_MAX];
  int    command;
  int    bitcount;
  int    file_type;
  int    no_output;
  int    error_count;


  void strlower(char *str);
  void strupper(char *str);
  voidp *malloc_msg(int size);
  void disp_clock(void);
  void error(char *fmt, char *arg);
  void fillbuf(int n);
  ushort getbits(int n);
  void fwrite_txt_crc(uchar *p, int n);
  void init_getbits(void);

  int    file_exists(char *name);
  void   get_mode_str(char *str, uint fmode);
//  int    set_ftime_mode(char *name, ulong timestamp, uint fmode, uint host);

  void   decode(void);
  void   decode_f(void);

  void  make_crctable(void);
  void  crc_buf(char *str, int len);
  void  strparity(uchar *p);
  int   fget_byte(Stream *f);
  uint  fget_word(Stream *f);
  ulong fget_longword(Stream *f);
  void  fread_crc(uchar *p, int n, Stream *f);
  void  decode_path(char *name);
  void  get_date_str(char *str, ulong tstamp);
  int   parse_path(char *pathname, char *path, char *entry);
  void  strncopy(char *to, char *from, int len);
  uint  get_word(void);
  ulong get_longword(void);
  long  find_header( Stream *fd );
  int   read_header(int first, Stream *fd, char *name);
  void  skip(void);
  void  unstore(void);
  int   check_flags(void);
  int   extract(void);
  int   test(void);
  uint  ratio(long a, long b);
  void  list_start(void);
  void  list_arc(int count);
  void  execute_cmd(void);

  void   make_table(int nchar, uchar *bitlen, int tablebits, ushort *table, int tablesize);
  void   read_pt_len(int nn, int nbit, int i_special);
  void   read_c_len(void);
  ushort decode_c(void);
  ushort decode_p(void);
  void   decode_start(void);
  short  decode_ptr(void);
  short  decode_len(void);

  uchar  *text;

  short  getlen;
  short  getbuf;

  ushort left[2 * NC - 1];
  ushort right[2 * NC - 1];
  uchar  c_len[NC];
  uchar  pt_len[NPT];

  ushort c_table[CTABLESIZE];
  ushort pt_table[PTABLESIZE];
  ushort blocksize;

  char   filename[FNAME_MAX];
  char   comment[COMMENT_MAX];
  char   *hdr_filename;
  char   *hdr_comment;

  ushort headersize;
  uchar  first_hdr_size;
  uchar  arj_nbr;
  uchar  arj_x_nbr;
  uchar  host_os;
  uchar  arj_flags;
  short  method;
  uint   file_mode;
  ulong  time_stamp;
  short  entry_pos;
  ushort host_data;
  uchar  *get_ptr;
  UCRC   file_crc;
  UCRC   header_crc;

  long   first_hdr_pos;
  long   torigsize;
  long   tcompsize;

  int    clock_inx;

//  char   *writemode[2]  = { "wb",  "w" };

  UCRC   crctable[UCHAR_MAX + 1];

 public:
  ARJ_Archive(void);

  virtual void Extract_Files( Base_File_Processor &x );

  virtual const lem::Path Extract_File( const UFString &filename, lem::Pack::Base_File_Processor &x ) { return lem::Path(); }
};

    class IARJUnpacker : public IUnpackerFactory
    {
     public:
      IARJUnpacker(void) {}

      virtual Base_Archive* New(void *ptr=NULL) const { return new ARJ_Archive(); }
    };

 } // namespace Arj
 } // namespace Pack
 } // namespace lem

#endif //  #if defined SOLARIX_PREMIUM || defined FAIND_ARJ

#endif
