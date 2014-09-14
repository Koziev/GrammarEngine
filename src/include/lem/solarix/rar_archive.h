// -----------------------------------------------------------------------------
// File RAR_ARCHIVE.H
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


#if !defined LEM_RAR__H
 #define LEM_RAR__H
#pragma once

 #include <rar.hpp>

 #include <lem/containers.h>
 #include <lem/solarix/base_archive.h>

 namespace lem
 {
  namespace Pack
  {
   class Rar_Archive : public Base_Archive
   {
    private:
     static bool first;

     lem::FString ArcName;
     lem::UFString ArcNameW;

     RAR::CommandData *Cmd;
     boost::shared_ptr<Stream> infile;

    public:
     Rar_Archive(void);
     ~Rar_Archive(void);

     virtual void Open( boost::shared_ptr<Stream> file );
     void List( lem::Collect<lem::UFString> &files );

     virtual void Extract_Files( Base_File_Processor &x );

     virtual void Extract_File( const UFString &filename, lem::Pack::Base_File_Processor &x );

     virtual void Extract_Commentary( UFString &buffer );
   };

    class IRARUnpacker : public IUnpackerFactory
    {
     public:
      IRARUnpacker(void) {}

      virtual Base_Archive* New(void *ptr=NULL) const { return new Rar_Archive(); }

      virtual bool CanExtractSingleFile(void) const { return true; }
    };

  } // namespace Pack

 } // namespace lem

#endif

