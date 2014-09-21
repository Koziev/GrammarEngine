// -----------------------------------------------------------------------------
// File PDF_USTREAM.H
//
// (c) by Koziev Elijah
//     Solarix Intellectronix project - http://www.solarix.ru
//
// Content:
// PDF_DEcoder - парсер PDF файлов
// -----------------------------------------------------------------------------
//
// CD->18.11.2004
// LC->15.09.2009
// --------------

#ifndef LEM_PDF_USTREAM__H
#define LEM_PDF_USTREAM__H
#pragma once

 #include <lem/config.h>

 #include <lem/unicode.h>
 #include <lem/streams.h>
 #include <lem/containers.h>
 #include <lem/zeroed.h>
 #include <lem/smart_pointers.h>

 #undef assert

 namespace PDF
 {
  class PDFDoc;
  class TextOutputDev;
  class UnicodeMap;
  class Object;
 };


 namespace lem
 {
  class CodeConverter;
  class OUFormatter;

  typedef lem::Ptr<lem::Stream> StreamPtr;

  namespace Char_Stream
  {
   class PDF_Decoder : public WideStream
   {
    private:
     lem::UFString buffer; // накопитель для извлекаемых символов.
     int icur; // курсор чтения из буфера.
     bool full_read; // содержимое документа полностью загружено для посимвольного чтения

     PDF::UnicodeMap *uMap;
     PDF::Object *obj;
     PDF::PDFDoc *doc;
     PDF::TextOutputDev *textOut;
     FILE *pdf_f;

     static void OutputFunc( void *stream, const unsigned *text, int len );

     int npages; // кол-во страниц в документе
     char *block; // если бинарный образ загружен в память

     virtual wchar_t Read_Char(void);

     bool eof_reached;

    public:
     PDF_Decoder( StreamPtr File );
     virtual ~PDF_Decoder(void);

     virtual bool eof(void) const { return eof_reached; }

     virtual void Write_Beginning(void) {}
     virtual bool Read_Beginning( bool excp=false ) { return true; }

     virtual int Bits_Per_Char(void) const { return 16; }
     virtual const char* GetFormat(void) const { return "pdf"; }

     virtual void wput( wchar_t ) { LEM_STOPIT; }

     virtual pos_type fsize(void) const { return buffer.length(); }
     virtual pos_type tellp(void) const { return icur; }

     virtual pos_type seekp( off_type to, int whereto=SEEK_SET )
     { 
      if( whereto==SEEK_SET && to<buffer.length() )
       {
        icur = to; 
        return 0;
       } 

      return static_cast<pos_type>(-1);
     }

     virtual bool move( off_type offset )
     {
      if( icur+offset < buffer.length() )
       return true;  

      return false; 
     };

     inline const UFString& GetChars(void) const { return buffer; }

     int GetPageCount(void) const { return npages; }
     void ExtractPage( int ipage );
   };

  } // namespace Char_Reader

 } // namespace lem

#endif
