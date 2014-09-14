// -----------------------------------------------------------------------------
// File FILE_FACTORY_PDF.H
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

#if !defined FILE_FACTORY_IMP__H && defined FAIND_PDF_READER
#define FILE_FACTORY_IMP__H
#pragma once

 #include <lem/solarix/file_factory.h>

 namespace Solarix
 {
  namespace Search_Engine
  {

   class Pdf_Detector : public File_Detector
   {
    public:
     Pdf_Detector(void);

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

   class Txt_Pdf_Reader : public Text_File_Reader
   {
    private:
     lem::Char_Stream::PDF_Decoder *file;

    public:
     Txt_Pdf_Reader(
                    const UFString &filename,
                    lem::StreamPtr File,
                    const Scan_Options &Scanning
                   );

     virtual void Set_Options( const Scan_Options& flags );
     virtual Stream::pos_type fsize(void) { return file->fsize(); }
   };

  } // namespace Search_Engine
 } // namespace Solarix

#endif
