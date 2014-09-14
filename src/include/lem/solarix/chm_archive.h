// -----------------------------------------------------------------------------
// File CHM_ARCHIVE.H
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
// Обертка для методов работы с CHM архивами.
// -----------------------------------------------------------------------------
//
// CD->15.03.2005
// LC->28.04.2008
// --------------


/* CHMtools v0.1 */
/* Copyright 2001 Matthew T. Russotto */
/*  
    This file is part of CHMtools

    CHMtools is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    
    CHMtools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    alem::int32_t  with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/



#if !defined CHM_ARCHIVE__H
 #define CHM_ARCHIVE__H

 //#include <stdio.h>
 #include <lem/solarix/base_archive.h>

 namespace lem
 {
  namespace Pack
  {
   namespace Chm
   {
    using lem::Stream;
    using lem::Pack::Base_Archive;

    typedef struct guid_t
    {
     lem::uint32_t guid1;
     lem::uint16_t guid2[2];
     lem::uint8_t guid3[8];
    } guid_t;

    typedef struct chmheader
    {
     char itsf[4];
     lem::uint32_t version; /* CHMTools only deals with version 3 */
     lem::uint32_t tot_hdrlen; /*  0x60 in version 3 */
     lem::uint32_t unk3; /* always 0x01 */
     lem::uint32_t last_modified; /* format unknown */
     lem::uint32_t langid; /* usually 0x0409 (ENGLISH_US); I've seen 0x0407 (GERMAN_GERMAN) */
     guid_t unk_guid1; /* 7C01FD10-7BAA-11D0-9E0C-00A0-C922-E6EC */
     guid_t unk_guid2; /* 7C01FD11-7BAA-11D0-9E0C-00A0-C922-E6EC */
    } chmheader;

    typedef struct hsecentry
    {
     lem::uint32_t offset;
     lem::uint32_t offset_hi; /* note that CHMLib does not support >4GB files */
     lem::uint32_t length;
     lem::uint32_t length_hi; 
    } hsecentry;

    typedef hsecentry hsectable[2];

    typedef struct hsec1_t
    {
     lem::uint32_t unk1; /* 0x1FE */
     lem::uint32_t unk2; /* 0 */
     lem::uint32_t file_length;
     lem::uint32_t file_length_hi;
    } hsec1_t;

    typedef struct dirheader
    {
     char itsp[4];
     lem::uint32_t unk1;        /* 0x01 */
     lem::uint32_t length;      /* 0x54 */
     lem::uint32_t unk3;        /* 0x0a */
     lem::uint32_t chunksize;   /* 0x1000 */
     lem::uint32_t unk5;        /* 0x02 */
     lem::uint32_t tree_depth;        /* 1 if there is no index chunk, 2 if there is one.  CHMTools does not handle higher numbers */
     lem::uint32_t indexchunk;  /* -1 if none, but 0 (probably erroneously) in at least one file */
     lem::uint32_t firstpmglchunk; 
     lem::uint32_t lastpmglchunk;
     lem::uint32_t unk8;        /* 0xFFFFFFFF */
     lem::uint32_t ndirchunks;
     lem::uint32_t langid;        /* 0x0409 (again?) */
     guid_t unk_guid1;   /* 5D02926A-212E-11D0-9DF9-00A0C922E6EC */
     lem::uint32_t unk10;       /* 0x54 */
     lem::uint32_t unk11[3];    /* 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF */
    } dirheader;

    typedef struct pmglchunkheader
    {
     char pmgl[4];
     lem::uint32_t quickreflen; /* length of the quickref area at the end of section */
     lem::uint32_t unk1; /* 0   probably intended to be this_chunk, but not necessary
                        because this_chunk is defined by position */
     lem::uint32_t prev_chunk;
     lem::uint32_t next_chunk;
    } pmglchunkheader;

    typedef struct direntry
    {
     lem::uint32_t section;
     lem::uint32_t offset;
     lem::uint32_t length;
     char name[256];
    } direntry;

    typedef struct chm_dir
    {
     int nentries;
     direntry entry[1];
    } chm_dir;

    typedef struct contsecentry
    {
     char name[256];
     int offset;
     short iscompressed;
     lem::uint8_t  *cache;
     lem::uint32_t cachesize;
    } contsecentry;

    typedef struct contsecs
    {
     int nentries;
     struct contsecentry entry[1];
    } contsecs;

    typedef struct chmfile
    {
     Stream *cf;
     chmheader ch;
     hsectable hs;
     contsecs *cs;
     dirheader dh;
     chm_dir *dir;
     lem::uint32_t file_length;
     lem::uint32_t content_offset;
    } chmfile;
 


/* generic stuff */
//#define CAB(x) (decomp_state.x)
//#define ZIP(x) (decomp_state.methods.zip.x)
//#define QTM(x) (decomp_state.methods.qtm.x)

//#undef lem::uint8_t 
//#undef Ulem::int32_t 
//#undef lem::int32_t 
//#undef lem::uint16_t 

//typedef unsigned char lem::uint8_t ;
//typedef unsigned lem::int32_t  Ulem::int32_t ;
//typedef unsigned short lem::uint16_t ;
//typedef lem::int32_t  lem::int32_t ;


#define LZX(x) (decomp_state.methods.lzx.x)
#define DECR_OK           (0)
#define DECR_DATAFORMAT   (1)
#define DECR_ILLEGALDATA  (2)
#define DECR_NOMEMORY     (3)
#define DECR_CHECKSUM     (4)
#define DECR_INPUT        (5)
#define DECR_OUTPUT       (6)

/* CAB data blocks are <= 32768 bytes in uncompressed form. Uncompressed
 * blocks have zero growth. MSZIP guarantees that it won't grow above
 * uncompressed size by more than 12 bytes. LZX guarantees it won't grow
 * more than 6144 bytes.
 */
#define CAB_BLOCKMAX (32768)
#define CAB_INPUTMAX (CAB_BLOCKMAX+6144)

/* LZX stuff */

/* some constants defined by the LZX specification */
#define LZX_MIN_MATCH                (2)
#define LZX_MAX_MATCH                (257)
#define LZX_NUM_CHARS                (256)
#define LZX_BLOCKTYPE_INVALID        (0)   /* also blocktypes 4-7 invalid */
#define LZX_BLOCKTYPE_VERBATIM       (1)
#define LZX_BLOCKTYPE_ALIGNED        (2)
#define LZX_BLOCKTYPE_UNCOMPRESSED   (3)
#define LZX_PRETREE_NUM_ELEMENTS     (20)
#define LZX_ALIGNED_NUM_ELEMENTS     (8)   /* aligned offset tree #elements */
#define LZX_NUM_PRIMARY_LENGTHS      (7)   /* this one missing from spec! */
#define LZX_NUM_SECONDARY_LENGTHS    (249) /* length tree #elements */

/* LZX huffman defines: tweak tablebits as desired */
#define LZX_PRETREE_MAXSYMBOLS  (LZX_PRETREE_NUM_ELEMENTS)
#define LZX_PRETREE_TABLEBITS   (6)
#define LZX_MAINTREE_MAXSYMBOLS (LZX_NUM_CHARS + 50*8)
#define LZX_MAINTREE_TABLEBITS  (12)
#define LZX_LENGTH_MAXSYMBOLS   (LZX_NUM_SECONDARY_LENGTHS+1)
#define LZX_LENGTH_TABLEBITS    (12)
#define LZX_ALIGNED_MAXSYMBOLS  (LZX_ALIGNED_NUM_ELEMENTS)
#define LZX_ALIGNED_TABLEBITS   (7)

#define LZX_LENTABLE_SAFETY (64) /* we allow length table decoding overruns */

#define LZX_DECLARE_TABLE(tbl) \
  lem::uint16_t  tbl##_table[(1<<LZX_##tbl##_TABLEBITS) + (LZX_##tbl##_MAXSYMBOLS<<1)];\
  lem::uint8_t  tbl##_len  [LZX_##tbl##_MAXSYMBOLS + LZX_LENTABLE_SAFETY]

struct LZXstate {
    lem::uint8_t  *window;         /* the actual decoding window              */
    lem::uint32_t window_size;     /* window size (32Kb through 2Mb)          */
    lem::uint32_t actual_size;     /* window size when it was first allocated */
    lem::uint32_t window_posn;     /* current offset within the window        */
    lem::uint32_t R0, R1, R2;      /* for the LRU offset system               */
    lem::uint16_t  main_elements;   /* number of main tree elements            */
    int   header_read;     /* have we started decoding at all yet?    */
    lem::uint16_t  block_type;      /* type of this block                      */
    lem::uint32_t block_length;    /* uncompressed length of this block       */
    lem::uint32_t block_remaining; /* uncompressed bytes still left to decode */
    lem::uint32_t frames_read;     /* the number of CFDATA blocks processed   */
    lem::int32_t   intel_filesize;  /* magic header value used for transform   */
    lem::int32_t   intel_curpos;    /* current offset in transform space       */
    int   intel_started;   /* have we seen any translatable data yet? */

    LZX_DECLARE_TABLE(PRETREE);
    LZX_DECLARE_TABLE(MAINTREE);
    LZX_DECLARE_TABLE(LENGTH);
    LZX_DECLARE_TABLE(ALIGNED);
};






    class CHM_Archive : public Base_Archive
    {
     private:
      int chm_getfile(chmfile *c, char *name, lem::uint32_t *length, lem::uint8_t  **outbuf);
      chmfile *chm_openfile( Stream *in );
      void chm_close(chmfile *l);
      int LZXinit(int window);
      int LZXdecompress( lem::uint8_t  *inbuf, lem::uint8_t  *outbuf, lem::uint32_t inlen, lem::uint32_t outlen );
      void get_guid( lem::uint8_t  *buf, guid_t *guid );
      void make_guid_string( guid_t *guid, char *s );
      void guid_fix_endian( guid_t *guid ); 
      int readheader( chmfile *c );
      int readhsectable( chmfile *c );
      int readdirheader( chmfile *c );
      lem::uint32_t getencint( lem::uint8_t  **p );
      int read_chm_dir( chmfile *c );
      direntry* getdirentry( char *name, chm_dir *dir );
//      int chm_getfile( chmfile *c, char *name, lem::uint32_t *length, lem::uint8_t  **outbuf );
      int readcontsecs( chmfile *c );

     public:
      CHM_Archive(void);

      virtual void Extract_Files( Base_File_Processor &x );
      virtual const lem::Path Extract_File( const UFString &filename, lem::Pack::Base_File_Processor &x );
    };


    class ICHMUnpacker : public IUnpackerFactory
    {
     public:
      ICHMUnpacker(void) {}

      virtual Base_Archive* New(void *ptr=NULL) const { return new CHM_Archive(); }

      virtual bool CanExtractSingleFile(void) const { return true; }
    };


   } // namespace Chm
  } // namespace Pack
 } // namespace lem

#endif
