// -----------------------------------------------------------------------------
// File FILE_FACTORY_RAW.H
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

#if !defined FILE_FACTORY_RAW__H && defined FAIND_RAW_READER
 #define FILE_FACTORY_RAW__H
#pragma once

 #include <lem/solarix/file_factory_imp.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
 

 class Raw_Reader_Knowledgebase
 {
  public:
   lem::Collect< std::pair<lem::UFString/*ext*/,int /*# of format*/> > experience;

  public:
   Raw_Reader_Knowledgebase(void) {}

   void LoadBin( Stream &bin );
   void SaveBin( Stream &bin ) const;
 };


 // ********************************************************************
 // Реальный класс: чтение контента из файла произвольного неизвестного
 // формата.
 // ********************************************************************
 class Raw_Reader : public Text_File_Reader
 {
  private:
   lem::StreamPtr org_file; // из этого файла пытаемся извлечь текст
   Raw_Reader_Knowledgebase *experience;

   static lem::Char_Stream::Russian_Filter          russian_filter;
   static lem::Char_Stream::Latin_Filter            latin_filter;
   static lem::Char_Stream::Central_European_Filter central_european_filter;

   typedef enum { Ascii, Utf8, Unicode_BE, Unicode_LE, Cp847, Cp866, Cp1251,
                  Unicode_BE_ru, Unicode_LE_ru, Unknown } VariantType;

   MCollect<VariantType> variants;

   bool allow_russian; // Есть смысл пытаться извлечь кириллицу 

   VariantType used_variant; // Какой вариант установлен.
   UFString used_ext; // Для какого расширения файла.
   void Set_Variant(void);

   bool prepare_format;
   Stream::pos_type start_pos; // с какого байта искать текст
   virtual void Guess_Code_Page(void);

   static wchar_t incorrect_char[];

  public:
   Raw_Reader(
              const UFString &filename,
              const UFString &ext,
              lem::StreamPtr file,
              const Scan_Options &scanning,
              Raw_Reader_Knowledgebase *Experience
             );

   virtual Base_File_Reader* Get_Next_Variant(void);

   virtual void Was_Success(void);
   virtual Stream::pos_type fsize(void) { return org_file->fsize(); }
   virtual void Prepare_Format(void);
   virtual void rewind(void);

   virtual void read( Base_File_Lexem &res );
 };


 class Raw_Detector : public File_Detector
 {
  private:
   Raw_Reader_Knowledgebase kb;

  public:
   Raw_Detector(void);

   virtual void ReadConfig( Stream &file );
   virtual void StoreConfig( Stream &file ) const;


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
