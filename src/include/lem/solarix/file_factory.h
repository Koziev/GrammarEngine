// -----------------------------------------------------------------------------
// File FILE_FACTORY.H
//
// (c) by Koziev Elijah
//     Solarix Intellectronix project - http://www.solarix.ru
//
// Content:
// LEM C++ library
//
// Парсеры текстовых файлов разных форматов - для выделения простого текста.
//
// 28.04.2006 - добавлена работа с аудиофайлами формата Ogg Vorbis
// 30.04.2006 - добавлена работа с файлами формата JPEG (извлечение комментария)
//
// 03.05.2006 - класс MIMEType переименован в MIMETypeType
// 26.05.2006 - добавлен новый модуль для работы с файлами Excel
// 23.09.2006 - введен механизм плагинов для подключения новых парсеров
// 10.12.2006 - введено распознование формата файла по задаваемому MIME
//              документа (к примеру, для интернет-краулера).
// -----------------------------------------------------------------------------
//
// CD->04.11.2004
// LC->06.12.2008
// --------------

#ifndef FILE_FACTORY__H
#define FILE_FACTORY__H
#pragma once

 #include <lem/config.h>

 #include <lem/zeroed.h>
 #include <lem/containers.h>
 #include <lem/cstring.h>
 #include <lem/lexers.h>
 #include <lem/mime.h>
 
 #if defined FAIND_IENGINES
 struct ISearchEngine;
 struct IGrammarEngine;
 #endif

 namespace Solarix
 {
  namespace Search_Engine
  {
   struct Scan_Options; 

   using lem::MCollect;
   using lem::UCString;
   using lem::UFString;
   using lem::Stream;
   
   class Crawler;

   // Дополнительная информация о документе, который должен быть
   // обработан пауком. Это пустой базовый класс.
   struct Doc_Info
   {
   };

   // ***********************************
   // Для каждого слова нужно знать, где
   // в файле оно было расположено.
   // ***********************************
   struct Base_File_Lexem
   {
    lem::UCString original;      // исходное слово - до всех преобразований
    lem::UCString word;          // само слово (нормализованное для упрощения сравнения)
    lem::Stream::pos_type where; // положение начала слова в файле
    int line;                    // номер строки

    Base_File_Lexem(void)
    {
     where = (Stream::pos_type)-1;
     line = 0;
    } 
   };



 class ITagStream;

 // *********************************************************
 // Базовый класс - чтение контента из файла (полексемно или
 // целого текста в виде одной строки).
 // *********************************************************
 class Base_File_Reader
 {
  protected:
   lem::MIMEType format;      // Текстовое описание формата
   lem::zbool strip_accents;   // убирать диактрические значки у букв

   // Извлеченные из файла тэги
   lem::Collect< std::pair<UFString/*param*/,UFString/*value*/> > params;

   void Add_Tag( const UFString &Param, const UFString &Value );

  public:
   Base_File_Reader(void);
   virtual ~Base_File_Reader(void);

   inline void Strip_Accents(void) { strip_accents=true; }

   virtual void read( Base_File_Lexem &l )=0;
   virtual bool eof(void) const=0;
   virtual void read_whole_text( UFString &text )=0;
   virtual void read_line( UFString &text )=0;
   virtual void rewind(void)=0;
   virtual lem::Stream::pos_type fsize(void)=0;
   virtual lem::Stream::pos64_type fsize64(void)=0;

   inline const lem::MIMEType& get_Format(void) const { return format; }

   virtual void Set_Options( const Scan_Options& flags );
   virtual Base_File_Reader* Get_Next_Variant(void);
   virtual void Was_Success(void);

   virtual void Prepare_Format(void);

   virtual void Store_Tags( ITagStream *dst );
 };


 // *****************************************************************
 // Детектор типа файла - по расширению имени и по содержимому
 // опознает формат файла и возвращает текстовую читалку для файла.
 //
 // 10.12.2006 - введено также детектирование по известному MIME типу
 //              документа. 
 //
 // File type detector - it tries to recognize file format.
 // *****************************************************************
 class File_Detector
 {
  protected:
   std::string format;    // Произвольное описание формата, который распознается
                     // детектором.

   std::string subformat; // Дополнительные сведения о формате

   lem::MIMEType mime; // MIME тип, распознаваемый детектором (если применимо)/

   std::map<UFString,int> match_ext; // расширения файлов, которые обрабатывает
                                     // детектор (если распознавание идет по
                                     // расширению).  

   inline bool MatchExt( const UFString &ext ) const
   { return match_ext.find(ext)!=match_ext.end(); }

  public:
   File_Detector(
                 const char *Format,
                 const char *Subformat
                ) : format(Format), subformat(Subformat) {}

   virtual ~File_Detector(void) {}

   // Если для работы соответствующего ридера нужен контент файла, а не только
   // его имя, то нужно возвращать true.
   virtual bool NeedsContent(void) const { return true; }

   virtual bool IsPlugin(void) const { return false; }
   virtual const wchar_t* GetDescription(void) const { return L""; }

   inline const string& GetFormat(void) const { return format; } 
   inline const string& GetSubformat(void) const { return subformat; } 

   virtual const lem::Path GetPath(void) const { return lem::Path(); }

   // ***********************************************
   // Подходит ли обработчик для указанного файла.
   // Если подходит, то возвращается указатель
   // на лексер/парсер файла.
   // ***********************************************
   virtual Base_File_Reader* Test(
                                  const Scan_Options &scanning,
                                  const UFString &filename,
                                  const UFString &ext,
                                  lem::StreamPtr &file
                                 )=0;

   virtual Base_File_Reader* Test(
                                  const Scan_Options &scanning,
                                  const UFString &filename,
                                  const lem::MIMEType &mime,
                                  lem::StreamPtr &file
                                 )=0;

   virtual void ReadConfig( lem::Stream &file ) {}
   virtual void StoreConfig( lem::Stream &file ) const {}

   inline const std::map<UFString,int>& GetMatchExt(void) const { return match_ext; }
 };



 class Detected_Format
 {
  private:
   lem::uint16_t flags;

  public:
   Detected_Format(void) { flags=0; }

   Detected_Format( bool Acceptable, bool Needs_Contents=false ) 
   {
    flags = (Acceptable ? 0x01 : 0x00) | (Needs_Contents ? 0x02 : 0x00);
   }

   inline bool IsAccepted(void) const { return (flags&0x01)==0x01; }
   inline bool NeedsContent(void) const { return (flags&0x02)==0x02; }
 };
 


 class File_Type_Detector
 {
  protected:
   MCollect< File_Detector* > detector; // Список детекторов форматов файлов
   File_Detector *null_detector; // этот детектор - не в общем списке. ОБЯЗАТЕЛЬНО УДАЛЯТЬ!

   // Для ускорения отсева неприемлемых файлов при инициализации списка
   // детекторов также формируется этот список свойств детекторов.
   typedef std::map<UFString /*ext*/, std::pair<int /*detector[]*/, bool /*needs_content*/ > >::const_iterator EXT_IT;
   std::map<UFString /*ext*/, std::pair<int /*detector[]*/, bool /*needs_content*/ > > u_ext;

   // Расширения графических, видеофайлов и т.д.
   std::map<UFString,int> gfx_ext;
   std::map<UFString,int> video_ext;
   std::map<UFString,int> audio_ext;
   std::map<UFString,int> exec_ext;

   void RetrieveExts(void);

   Base_File_Reader* FindReader(
                                const Scan_Options &scanning,
                                const UFString &filename,
                                const UFString *ext,
                                const lem::MIMEType *mime,  
                                lem::StreamPtr file
                               );

  public:
   Solarix::Search_Engine::Crawler* master_crawler; // для доступа к словарю и т.д.   

  public:
   File_Type_Detector(void);

   virtual ~File_Type_Detector(void);

   // Инициализация внутреннего списка обработчиков файлов разных форматов.
   virtual void AttachDetectors(void);

   #if defined FAIND_PLUGINS
   // Ищет и загружает плагины в указанном каталоге.
   virtual int LoadPlugins( 
                           const lem::Path &folder,
                           lem::OFormatter *logfile
                           #if defined FAIND_IENGINES
                           , ISearchEngine* se
                           , IGrammarEngine* ge
                           #endif
                          );

   // Добавляет в список описание загруженных плагинов
   void ListPlugins( lem::Collect< std::pair<UFString,lem::Path> > &list ) const;
   #endif

   // Чтение конфигурационных параметров из бинарного файла конфигурации
   virtual void ReadConfig( lem::Stream &file );
   virtual void StoreConfig( lem::Stream &file ) const;

   // возвращает подтверждение возможности читать файл с указанным именем.
   // В структуре Detected_Format также возвращается доп. информация.
   Detected_Format IsAcceptableFilenameFast(
                                            const Scan_Options &scanning,
                                            const UFString &ext
                                           ) const;

   virtual Base_File_Reader* FindReader(
                                        const Scan_Options &scanning,
                                        const UFString &filename,
                                        const UFString &ext
                                       );

   virtual Base_File_Reader* FindReader(
                                        const Scan_Options &scanning,
                                        const UFString &filename,
                                        const UFString &ext,
                                        lem::StreamPtr file
                                       );

   virtual Base_File_Reader* FindReader(
                                        const Scan_Options &scanning,
                                        const UFString &filename,
                                        const lem::MIMEType &mime,
                                        lem::StreamPtr file
                                       );

   virtual Base_File_Reader* GetTxtReader(
                                          const Scan_Options &scanning,
                                          const UFString &filename,
                                          lem::StreamPtr file
                                         );

   void ListSupportedReaders( lem::OFormatter &out ) const;
   int Count(void) const;
 };

  class DocumentInformer
  {
   private:
    UFString empty;

    std::map< UFString /*ext*/, UFString* /*info*/ > cache;
    typedef std::map< UFString /*ext*/, UFString* /*info*/ >::iterator IM;

   public:
    DocumentInformer(void);
    ~DocumentInformer(void);

    void ClearCache(void); 
    
    const UFString& GetInfo( const UFString &filename );
  };

 } // namespace Search_Engine
 } // namespace Solarix

#endif
