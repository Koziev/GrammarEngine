// -----------------------------------------------------------------------------
// File ZIP_ARCHIVE.H
//
// (c) by Koziev Elijah
//
// Content:
//
// ќбертка дл€ методов работы с RAR архивами. —делано специально дл€ поисковых
// утилит, дл€ распаковки на лету архивов и просмотра файлов в этих архивах.
// -----------------------------------------------------------------------------
//
// CD->04.11.2004
// LC->16.08.2007
// --------------

#ifndef LEM_ZIP__H
#define LEM_ZIP__H
#pragma once

 #include <lem/solarix/base_archive.h>

 namespace lem
 {
  namespace Pack
  {
   namespace Zip
   {
    class Zip_Archive : public Base_Archive
    {
     private:
      boost::shared_ptr<Stream> infile;

     public:
      Zip_Archive(void);

      virtual void Open( boost::shared_ptr<Stream> file );
      virtual void Extract_Files( Base_File_Processor &x );

      virtual void Extract_File( const UFString &filename, lem::Pack::Base_File_Processor &x ) {}

      static void Free_Static_Resources(void);
    };

    class IZIPUnpacker : public IUnpackerFactory
    {
     public:
      IZIPUnpacker(void) {}

      virtual Base_Archive* New(void *ptr=NULL) const { return new Zip_Archive(); }
    };
   } // namespace Zip
  } // namespace Pack
 } // namespace lem

#endif

