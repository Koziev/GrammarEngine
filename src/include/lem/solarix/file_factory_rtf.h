// -----------------------------------------------------------------------------
// File FILE_FACTORY_RTF.H
//
// (c) Koziev Elijah
//     Solarix Intellectronix project - http://www.solarix.ru
//
// Content:
// LEM C++ library
//
// -----------------------------------------------------------------------------
//
// CD->04.11.2004
// LC->20.07.2008
// --------------

#if !defined FILE_FACTORY_RTF__H && defined FAIND_RTF_READER
 #define FILE_FACTORY_RTF__H
#pragma once

 #include <lem/config.h>
 #include <lem/streams.h>
 #include <lem/ustreams.h>
 #include <lem/solarix/file_factory_imp.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
/*
   struct Scan_Options; 

   using lem::MCollect;
   using lem::UCString;
   using lem::UFString;
   using lem::Stream;
   using lem::SourceState;
   
*/

   class Txt_Rtf_Reader : public Text_File_Reader
   {
    private:
     lem::Char_Stream::RTF_Decoder *file;

    public:
     Txt_Rtf_Reader(
                    const lem::UFString &filename,
                    lem::StreamPtr File,
                    const Scan_Options &Scanning
                   );

     virtual void Set_Options( const Scan_Options& flags );
     virtual Stream::pos_type fsize(void) { return file->fsize(); }
   };


   class Rtf_Detector : public File_Detector
   {
    public:
     Rtf_Detector(void);

     virtual Base_File_Reader* Test(
                                    const Scan_Options &scanning,
                                    const UFString &filename,
                                    const UFString &ext,
                                    lem::StreamPtr &file
                                   );

     virtual Base_File_Reader* Test(
                                    const Scan_Options &scanning,
                                    const UFString &filename,
                                    const lem::MIMEType &mime,
                                    lem::StreamPtr &file
                                   );
   };

  } // namespace Search_Engine
 } // namespace Solarix

#endif
