// -----------------------------------------------------------------------------
// File FILE_FACTORY_NULL.H
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

#if !defined FILE_FACTORY_NULL__H
 #define FILE_FACTORY_NULL__H
#pragma once

 #include <lem/solarix/file_factory.h>

 namespace Solarix
 {
  namespace Search_Engine
  {

 class Null_Detector : public File_Detector
 {
  public:
   Null_Detector(void);

   virtual Base_File_Reader* Test(
                                  const Scan_Options &scanning,
                                  const UFString &filename,
                                  const UFString &ext,
                                  lem::StreamPtr &file
                                 );


   Base_File_Reader* Test(
                          const Scan_Options &scanning,
                          const UFString &filename,
                          const lem::MIMEType &mime,
                          lem::StreamPtr &file
                         );

   virtual bool NeedsContents(void) const { return false; }
 };

 class Null_Reader : public Base_File_Reader
 {
  protected:
   lem::StreamPtr stream;

  public:
   Null_Reader( 
               const UFString &filename,
               lem::StreamPtr file,
               const Scan_Options &Scanning
              );

   virtual void read( Base_File_Lexem &l );
   virtual bool eof(void) const;
   virtual void read_whole_text( UFString &text );
   virtual void read_line( UFString &text );
   virtual void rewind(void);
   virtual Stream::pos_type fsize(void);
 };

 } // namespace Search_Engine
 } // namespace Solarix

#endif
