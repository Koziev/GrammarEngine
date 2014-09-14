#ifndef SCAN_OPTIONS__H
#define SCAN_OPTIONS__H
#pragma once

 #include <lem/zeroed.h>
 #include <lem/streams.h>
 #include <lem/url.h>
 #include <lem/unicode.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/smart_pointers.h>
 #include <lem/solarix/se_plugin_options.h>
 #include <lem/solarix/se_doc_preprocessor.h>
 #include <lem/solarix/se_file_filter.h>
  
 namespace Solarix
 {
  namespace Search_Engine
  { 


  #if defined FAIND_OCR
  struct OCRParams
  {
   lem::zbool use;
   lem::UFString params;

   OCRParams(void);
   OCRParams( const OCRParams &x ); 
   void operator=( const OCRParams &x ); 
 
   void clear(void);

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
  };
  #endif

  // *************************************************
  // Параметры управления экстрактором метаинформации
  // *************************************************
  struct MetaInfoParams
  {
   lem::zbool enabled; // задействован механизм извлечения описания файлов из спецфайлов в папках
   lem::UFString u_metafilename; // имя метафайла
   lem::FString a_metafilename;
   typedef enum { UnknownFormat, XmlFormat, CsvFormat } FormatType;
   FormatType format; // формат

   typedef enum { StoreInCache, StoreInServer } StorageType;
   StorageType storage;

   static wchar_t *Tagname;

   MetaInfoParams(void);
   MetaInfoParams( const MetaInfoParams &x );
   void operator =( const MetaInfoParams &x );

   void clear(void);

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );

   bool IsMetafile( const wchar_t *filename ) const;
   bool IsMetafile( const char *filename ) const;
  };


  // *****************************
  // Files filtering options.
  // Опции по фильтрации файлов.
  // *****************************
  struct Scan_Options
  {
   private:
    #if LEM_DEBUGGING==1
    lem::Guardian guard;
    #endif

    lem::MCollect<int /*bool*/> del_file_filter;

    void Init( const Scan_Options &x );

   public:
    lem::Collect<lem::UFString> cmd_args; // токены командной строки, из которых заполнена структура
   
    bool recurse;             // сканировать подкаталоги
    bool follow_href;         // следовать по гиперссылкам
    int href_depth;           // макс. число прыжков по гиперссылке   
    int limit_traffic;        // ограничение на скачанный траффик по сайтам  
    bool unpack;              // распаковывать и обрабатывать архивы
    lem::zbool skipfiles; // полностью пропускать обработку файлов

    bool allow_raw;           // можно ли работать с файлами неизвестных форматов
    lem::Collect<lem::UFString> raw_ext; // расширения, которые обрабатываются raw редером

    bool allow_gfx;           // можно обрабатывать графические файлы
    bool allow_video;         // можно ли обрабатывать видеофайлы   
    bool allow_audio;         // можно ли обрабатывать аудиофайлы   
    bool allow_exec;          // можно ли обрабатывать исполнимые файлы (exe, dll)
    bool store_all_files;     // в индексной базы сохранять сведения о всех файлах (даже не обработанных ридерами)
    bool fn_cased;            // строго учитывать регистр букв в именах файлов
    bool org_domain;          // по ссылкам не выходить за исходный домен
    bool strip_decoration;    // Удалять теги XML/HTML, RTF и так далее 
    bool process_contents;    // индексировать ли содержимое документов, или ограничиться только именами файлов
 
    lem::Collect<lem::UFString> folder; // каталоги для просмотра
    lem::Collect<lem::UFString> file;   // файлы для просмотра
    lem::Collect<lem::UFString> engine; // внешние поисковики (плагины) и параметры запросов
    bool manual_sources; // при добавлении документов в индекс по одному из прикладного
                         // кода у нас не определены списка имен файлов или каталогов для
                         // обработки, но область поиска не пуста.
    lem::zbool locate_mode; // метапоиск "locate"

    lem::Collect<lem::UFString> file_regex_mask;        // маски для обрабатываемых файлов - регекспы
    lem::Collect<lem::UFString> file_wildcards_notmask; // маски отвергания для обрабатываемых файлов - обычные маски файлов
    lem::Collect<lem::UFString> file_regex_notmask;     // маски отвергания для обрабатываемых файлов - регекспы
    lem::Collect<lem::UFString> file_wildcards_mask;    // маски для обрабатываемых файлов - обычные маски файлов

    #if defined FAIND_WEB
    lem::Collect<lem::Url> uri;       // адреса документов в интернете
    lem::Collect<lem::UFString> uri_mask, uri_notmask;  // маски для URI
    #endif

    #if defined FAIND_NETWORKING 
    lem::Collect<lem::UFString> pipe;      // имена каналов
    lem::Collect<lem::UFString> socket;    // адреса сокетов
    #endif

    lem::MCollect<Base_File_Filter*> file_filter; // Добавленные пользовательским кодом
                                             // обобщенные фильтры для файлов

    lem::MCollect<Base_File_Filter*> file_notfilter; // Добавленные пользовательским кодом
                                                // обобщенные фильтры отвергания для файлов

    lem::MCollect<Base_File_Filter*> all_file_filters; // Все фильтры для файлов,
                              // включая сгенерированные самим кодом и добавленные
                              // пользовательским кодом.

    #if defined FAIND_WEB
    lem::MCollect<Base_File_Filter*> all_uri_filters; // Все фильтры для URI
    lem::UFString proxy_server; // если для выхода в Интернет используется проксик - его адрес
    lem::UFString proxy_bypass; // хосты, доступ к которым идет не через проксик
    bool passive_ftp; // PASSIVE FTP mode
    #endif

    lem::zbool store_download;   // Сохранять загруженные из Интернета документы в
    lem::UFString download_dir;  // этом каталоге.

    lem::CString forced_cp_name; // принудительно заданная кодовая страница для документов 
    const lem::CodeConverter *forced_cp;
    lem::Ptr<lem::Transliterator> translit; // если нужно использовать транслитерацию читаемых текстов
    
    lem::Collect<lem::UFString> prefer_cp_names; // рекомендованные для проверки в CodeGuesser'е кодовые страницы
    lem::MCollect<const lem::CodeConverter*> prefer_cp_list; // указатели на объекты кодовых страниц


    lem::PtrCollect<Doc_Preprocessor> preprocessor; // Модули внутренней обработки документов перед их отдачей в поиск/индексатор

    lem::zbool force_txt; // обрабатывать все файлы как обычные plain text
    lem::zbool force_binhex; // преобразовывать файлы для бинарного поиска байтов

    PluginOptions plugin_options; // группа параметров для передачи в плагины

    #if defined FAIND_OCR
    OCRParams ocr; // параметры управления OCR движком
    #endif

    MetaInfoParams metainfo;

    Scan_Options(void);
    Scan_Options( const Scan_Options &x );

    ~Scan_Options();

    void operator=( const Scan_Options &x );

    // Завершаем подготовку структуры после парсинга командной строки
    void Prepare(void);

    // Очищаем все поля
    void Clear(void);

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    // Is search domain empty?  
    bool IsEmptyDomain(void) const;

    // Is there any filters defined?
    inline bool Filters(void) const
    {
     return !all_file_filters.empty()
            #if defined FAIND_WEB
            || !all_uri_filters.empty()
            #endif
            ; 
    }

    // Вернет true и серийный номер, если в описании зоны поиска
    // фигурирует CD/DVD привод
    bool Refers_Cdrom( lem::uint32_t &SerialNumber, lem::FString &drive ) const;
    bool Refers_Cdrom( const lem::UFString &path, lem::uint32_t &SerialNumber, lem::FString &drive ) const;
  };

 }
}
#endif
