// -----------------------------------------------------------------------------
// File FILE_FACTORY_MSWORD.H
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

#if !defined FILE_FACTORY_MSWORD__H && defined FAIND_DOC_READER
 #define FILE_FACTORY_MSWORD__H
#pragma once

 #include <lem/config.h>

 #if defined LEM_WINDOWS
  #if defined LEM_MFC
   #include <afxwin.h>
  #else 
   #include <windows.h>
  #endif
  #include <ole2.h>
 #endif 

 #include <lem/solarix/file_factory_imp.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
//   struct Scan_Options; 
//   struct PluginOptions;

//   using lem::MCollect;
//   using lem::UCString;
//   using lem::UFString;
//   using lem::Stream;
//   using lem::SourceState;

 class Doc_Detector : public File_Detector
 {
  private:
   Base_File_Reader* Return_Reader(
                                   const Scan_Options &scanning,
                                   const UFString &filename,
                                   lem::StreamPtr &file
                                  );

  public:
   Doc_Detector(void);

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


 const unsigned short fDot = 0x0001;
 const unsigned short fGlsy = 0x0002;
 const unsigned short fComplex = 0x0004;
 const unsigned short fPictures = 0x0008;
 const unsigned short fEncrypted = 0x100;
 const unsigned short fReadOnly = 0x400;
 const unsigned short fReserved = 0x800;
 const unsigned short fExtChar = 0x1000;

 // Поток (Stream) с именем WordDocument начинается с этого заголовка
 struct WordDocHeader
 {
  unsigned short signature;   // 0,1
  unsigned short version;     // 2,3

/*
  unsigned char dum1[6];      // 4,5,6,7,8,9
  unsigned short flags;       // 10,11
  unsigned short unknown1;     // 12,13
  unsigned long encript_key;  // 14,15,16,17
  unsigned char fMacintosh;   // 18
  unsigned char unknown2;     // 19
  unsigned short charset;     // 20,21

  unsigned short unknown3;    // 22,23
  unsigned long text_begin;   // 24,25,26,27     
  unsigned long text_len;     // 28,29,30,31  
*/

  unsigned char dum1[20];

  unsigned text_begin;
  unsigned text_end;

  unsigned char dum2[20];

  unsigned text_len;          // MS Word 6.0
  unsigned char dum3[20];
  unsigned text_len2;         // MS Word 7.0 


  WordDocHeader(void);
 };


 // *********************************************************
 // Для чтения символов из ASCII потоков документов MS Word
 // *********************************************************
 class DOC_Real_Decoder : public lem::Char_Stream::WideStream
 {
  protected:
   bool eof_reached;
   LPSTREAM pIStream;
   WordDocHeader hdr;
   int text_len;
   int chars_left;

   // Для чтения содержимого OLE-потока посимвольно применяем самую
   // эффективную IMHO методику: читаем крупными блоками (по несколько Кб)
   // в буфер-кэш, и уже оттуда отдаем по одному символу.
   enum { max_cache_size=8192 }; // константа для размера кэша
   wchar_t cache[max_cache_size+1]; // один символ - страховочный терминатор
   int cache_size; // реальное число символов в кэше (может быть меньше max_cache_size).
   int icur; // положение курсора чтения в кэше
   Stream::pos_type cache_pos; // файловая позиция первого символа кэша.

   void Invalidate_Cache(void);

   virtual void Load_Cache(void)=0;

   virtual wchar_t Read_Char(void);

  public:
   DOC_Real_Decoder( LPSTREAM pIStream, const WordDocHeader &Hdr );

   virtual bool eof(void) const { return eof_reached; }

   virtual void Write_Beginning(void) {}
   virtual bool Read_Beginning( bool excp=true ) { return true; }

   virtual int Bits_Per_Char(void) { return 16; }
   virtual const char* GetFormat(void) const { return "msword"; }

   virtual void wput( wchar_t ) { LEM_STOPIT; }

   virtual pos_type fsize(void) const { return 0; }
   virtual pos_type tellp(void) const;

   virtual pos_type seekp( off_type to, int whereto=SEEK_SET );
   virtual bool move( off_type offset );

   virtual void Read_Whole_Text( UFString &str )=0;
   void Rewind(void);
   void unget( wchar_t ch );
 };


 class DOC_Unicode_Decoder : public DOC_Real_Decoder
 {
  private:
   virtual void Load_Cache(void);

  public:
   DOC_Unicode_Decoder( LPSTREAM pIStream, const WordDocHeader &Hdr );

   virtual void Read_Whole_Text( UFString &str );
 };

 class DOC_Ascii_Decoder : public DOC_Real_Decoder
 {
  private:
   lem::uint8_t acache[ DOC_Real_Decoder::max_cache_size+1 ];

   virtual void Load_Cache(void);

  public:
   DOC_Ascii_Decoder( LPSTREAM pIStream, const WordDocHeader &Hdr );

   virtual void Read_Whole_Text( UFString &str );
 };

 class Doc_Real_File_Reader : public Text_File_Reader
 {
  protected:
   LPSTORAGE pIStorage;
   LPSTREAM  pIStream;

   bool unicode;

   DOC_Real_Decoder *file;

   lem::Path source_file;
   bool remove_source_file;
 
   // Положение начала и конфа текста в потоке
   WordDocHeader hdr;
   void Open_Stream( const UFString &filename );

  public:
   Doc_Real_File_Reader( const UFString &filename, const Scan_Options &Scanning );

   virtual ~Doc_Real_File_Reader(void);

   void Remove_Source_File(void) { remove_source_file=true; }

   virtual void read_whole_text( UFString &text );
   virtual void rewind(void);

   virtual Stream::pos_type fsize(void);

   virtual bool eof(void) const;
 };

 } // namespace Search_Engine
 } // namespace Solarix

#endif
