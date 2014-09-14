// -----------------------------------------------------------------------------
// File BZ2_ARCHIVE.H
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
// Обертка для методов работы с BZ2 архивами. Сделано специально для поисковых
// утилит, для распаковки на лету архивов и просмотра файлов в этих архивах.
//
// 14.04.2008 - компилируется только с макросом SOLARIX_PREMIUM или FAIND_BZ2
// -----------------------------------------------------------------------------
//
// CD->23.12.2004
// LC->28.04.2008
// --------------

#pragma once

 #if defined SOLARIX_PREMIUM || defined FAIND_BZ2

#if !defined LEM_BZ2_ARCHIVE__H
 #define LEM_BZ2_ARCHIVE__H

 #include <lem/streams.h>
 #include <lem/solarix/base_archive.h>

 namespace lem
 {
  namespace Pack
  {
   namespace Bz2
   {
    using lem::Stream;
    using lem::Pack::Base_Archive;

    class BZ2_Archive : public Base_Archive
    {
     private:

     public:
      BZ2_Archive(void);

      void Extract_Files( Base_File_Processor &x );

      virtual const lem::Path Extract_File( const UFString &filename, lem::Pack::Base_File_Processor &x ) { return lem::Path(); }
    };

    class IBZ2Unpacker : public IUnpackerFactory
    {
     public:
      IBZ2Unpacker(void) {}

      virtual Base_Archive* New(void *ptr=NULL) const { return new BZ2_Archive(); }
    };

   } // namespace Bz2
  } // namespace Pack
 } // namespace lem

 #endif //  #if defined SOLARIX_PREMIUM || defined FAIND_BZ2

#endif
// --------------------- End Of File [BZ2_ARCHIVE.H] --------------------------
