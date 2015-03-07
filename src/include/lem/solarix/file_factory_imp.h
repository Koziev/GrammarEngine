// -----------------------------------------------------------------------------
// File FILE_FACTORY_IMP.H
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
// LC->11.10.2014
// --------------

#ifndef FILE_FACTORY_IMP__H
#define FILE_FACTORY_IMP__H
#pragma once

 #include <lem/string_parser.h>
 #include <lem/solarix/file_factory.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
   struct Scan_Options; 

   using lem::MCollect;
   using lem::UCString;
   using lem::UFString;
   using lem::Stream;
   using lem::SourceState;
   
 class String_Reader : public Base_File_Reader
 {
  public:
   const wchar_t *cur;

  protected:
   const wchar_t *beg, *end;  

  public:
   String_Reader( const wchar_t *Beg, const wchar_t *End );

   virtual void read( Base_File_Lexem &l );
   virtual bool eof() const { return cur==end; }
   virtual void read_whole_text( UFString &text );
   virtual void read_line( UFString &text );
   virtual void rewind();

   virtual lem::Stream::pos_type fsize() { return end-beg; }
   virtual lem::Stream::pos64_type fsize64() { return end-beg; }
 };


 class Mem_String_Reader : public String_Reader
 {
  private:
   UFString *buffer;

  public:
   Mem_String_Reader( UFString *Buffer );
   Mem_String_Reader( UFString *Buffer, const wchar_t *Beg, const wchar_t *End );

   virtual ~Mem_String_Reader();
 };


 // **************************************************************
 // В состав этого промежуточного базового класса входит
 // CodeConverter Guesser - алгоритм для определения кодовой страницы
 // **************************************************************
 class Text_File_Reader : public Base_File_Reader
 {
  protected:
   int line; // счетчик строк
   lem::Char_Stream::WideStreamPtr stream;
   lem::zbool eof_reached; // был достигнут конец потока
   const Scan_Options *scanning;

   static MCollect<const lem::CodeConverter*> cplist_intrinsic;

   static void Prepare_Ru_Dict();
   static void Prepare_En_Dict();
   static void Prepare_Fr_Dict();

   static void Prepare_Dict();

   float Project_Words(
                       int n_max_words=64,  // сколько слов проецировать
                       int n_min_cyr=0      // мин число русских слов
                      );
   bool Is_Impossible( const UCString &w ) const;

   lem::zbool enable_guesser; // флаг - разрешать ли подбор кодовых страниц
   virtual void Guess_Code_Page();

  public:
   Text_File_Reader( const Scan_Options &Scanning );

   virtual ~Text_File_Reader();

   virtual void read( Base_File_Lexem &l );
   virtual bool eof() const;
   virtual void read_whole_text( UFString &text );
   virtual void read_line( UFString &text );
   virtual void rewind();

   virtual lem::Stream::pos_type fsize() { return stream->fsize(); }
   virtual lem::Stream::pos64_type fsize64() { return stream->fsize64(); }
 };


 // ********************************************************************
 // Реальный класс: чтение контента из простого текстового ASCII-файла.
 // ********************************************************************
 class Txt_Ascii_Reader : public Text_File_Reader
 {
  private:
   virtual void Prepare_Format();

  public:
   Txt_Ascii_Reader(
                    const UFString &filename,
                    lem::StreamPtr file,
                    const Scan_Options &Scanning
                   );

   Txt_Ascii_Reader(
                    const UFString &filename,
                    lem::StreamPtr File,
                    const Scan_Options &Scanning,
                    const lem::MIMEType &Format
                   );

 };


 class Txt_Translit_Reader : public Text_File_Reader
 {
  public:
   Txt_Translit_Reader(
                       const UFString &filename,
                       lem::StreamPtr file,
                       const Scan_Options &Scanning
                      );
 };


 // ********************************************************************
 // Реальный класс: чтение контента из HTML-файла.
 // ********************************************************************
 class Txt_Html_Reader : public Text_File_Reader
 {
  public:
   Txt_Html_Reader(
                   const lem::UFString &filename,
                   lem::StreamPtr File,
                   const Scan_Options &Scanning
                  );


   Txt_Html_Reader(
                   const UFString &filename,
                   lem::StreamPtr File,
                   const Scan_Options &scanning,
                   const lem::MIMEType &Format
                  );


   Txt_Html_Reader( const Scan_Options &Scanning );

   virtual void Set_Options( const Scan_Options& flags );
 };



 class Txt_Detector : public File_Detector
 {
  public:
   Txt_Detector();

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

 class Html_Detector : public File_Detector
 {
  public:
   Html_Detector();

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

 #if defined FAIND_GFX_READER
 class JPEG_Detector : public File_Detector
 {
  public:
   JPEG_Detector();

   virtual Base_File_Reader* Test(
                                  const Scan_Options &scanning,
                                  const UFString &filename,
                                  const UFString &ext,
                                  lem::StreamPtr &file
                                 );

   virtual Base_File_Reader* Test(
                                  const Scan_Options &scanning,
                                  const UFString &filename,
                                  const lem::MIMEType &Format,
                                  lem::StreamPtr &file
                                 );
 };
 #endif

 #if defined FAIND_EXE_READER
 class EXE_Detector : public File_Detector
 {
  public:
   EXE_Detector();

   virtual Base_File_Reader* Test(
                                  const Scan_Options &scanning,
                                  const UFString &filename,
                                  const UFString &ext,
                                  lem::StreamPtr &file
                                 );

   virtual Base_File_Reader* Test(
                                  const Scan_Options &scanning,
                                  const UFString &filename,
                                  const lem::MIMEType &Format,
                                  lem::StreamPtr &file
                                 );
 };
 #endif

 class Str_File_Reader : public Base_File_Reader
 {
  protected:
   lem::StreamPtr stream;
   UFString text;
   lem::Ptr< lem::StrParser< UFString > > parser;
   int icur; // позиция чтения из icur;

  public:
   Str_File_Reader( 
                   const UFString &filename,
                   lem::StreamPtr file,
                   const Scan_Options &Scanning
                  );

   ~Str_File_Reader();

   virtual void read( Base_File_Lexem &l );
   virtual bool eof() const;
   virtual void read_whole_text( UFString &text );
   virtual void read_line( UFString &text );
   virtual void rewind();
   virtual lem::Stream::pos_type fsize();
   virtual lem::Stream::pos64_type fsize64();
 };

 #if defined FAIND_EXE_READER
 class EXE_File_Reader : public Str_File_Reader
 {
  public:
   EXE_File_Reader( 
                   const UFString &filename,
                   lem::StreamPtr file,
                   const Scan_Options &Scanning
                  );
 };
 #endif

 #if defined FAIND_GFX_READER
 class JPEG_File_Reader : public Str_File_Reader
 {
  public:
   JPEG_File_Reader( 
                    const UFString &filename,
                    lem::StreamPtr file,
                    const Scan_Options &Scanning
                   );
 };
 #endif


 class BinHex_Reader : public Base_File_Reader
 {
  protected:
   lem::StreamPtr stream;

  public:
   BinHex_Reader( 
                 const UFString &filename,
                 lem::StreamPtr file,
                 const Scan_Options &Scanning
                );

   virtual void read( Base_File_Lexem &l );
   virtual bool eof() const;
   virtual void read_whole_text( UFString &text );
   virtual void read_line( UFString &text );
   virtual void rewind();
   virtual lem::Stream::pos_type fsize();
   virtual lem::Stream::pos64_type fsize64();
 };


 } // namespace Search_Engine
 } // namespace Solarix

#endif
