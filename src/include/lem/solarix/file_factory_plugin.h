// -----------------------------------------------------------------------------
// File FILE_FACTORY_PLUGIN.H
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
// LC->04.11.2008
// --------------

#if !defined FILE_FACTORY_PLUGIN__H && defined FAIND_PLUGINS
 #define FILE_FACTORY_PLUGIN__H
#pragma once

 #include <lem/ustreams.h>
 #include <lem/solarix/file_factory_imp.h>

 #if defined FAIND_IENGINES
 struct ISearchEngine;
 struct IGrammarEngine;
 typedef ISearchEngine* ISearchEnginePtr;
 typedef IGrammarEngine* IGrammarEnginePtr;
 #else 
 typedef void* ISearchEnginePtr;
 typedef void* IGrammarEnginePtr;
 #endif

 namespace Solarix
 {
  namespace Search_Engine
  {
   struct Scan_Options; 
   struct PluginOptions;
   struct PluginOptions;

  // ************************************************ 
  // Парсер файлов, загружаемый как плагин (из DLL).
  // ************************************************ 
  class Filetype_Plugin : public File_Detector
  {
   protected:
    lem::Path dllpath; // файл загруженной DLL
    lem::Process::Dll hLib;
    void *PluginThis;

    ISearchEnginePtr  _ISearchEnginePtr;
    IGrammarEnginePtr _IGrammarEnginePtr;
   

    friend class Plugin_Reader;
    friend class Plugin_Decoder;

    typedef void*(*constructor_func)(void);
    typedef void(*destructor_func)( void *This );
    typedef const wchar_t*(*get_property_func)( void *ThisPtr, int iProperty, int iSubproperty );
    typedef bool (*set_property_func)( void *ThisPtr, int iProperty, int iSubproperty, const wchar_t *Value );
    typedef void(*get_mime_func)( void *ThisPtr, void *ExtractionContext, const char **Format, const char **Subformat );
    typedef void*(*start_extraction_func)( void *ThisPtr, const wchar_t *Filename, wchar_t **Block, unsigned int *Count, const PluginOptions *Options, IGrammarEnginePtr ge, ISearchEnginePtr se  );
    typedef unsigned(*get_chars_count_func)( void *ThisPtr, void *ExtractionContext );
    typedef bool(*extract_next_chunk_func)( void *ThisPtr, void *ExtractionContext, wchar_t **Block, unsigned int *Count, const PluginOptions *Options, IGrammarEnginePtr ge, ISearchEnginePtr se );
    typedef void(*rewind_func)( void *ThisPtr, void *ExtractionContext );
    typedef void(*extraction_complete_func)( void *ThisPtr, void *ExtractionContext, wchar_t *Block );

    constructor_func constructor_ptr;
    destructor_func destructor_ptr;

    get_property_func get_property_ptr;
    set_property_func set_property_ptr;
    get_mime_func get_mime_ptr;

    // Группа методов для извлечения символьного содержимого файла
    start_extraction_func start_extraction_ptr;
    extract_next_chunk_func extract_next_chunk_ptr;
    rewind_func rewind_ptr;
    extraction_complete_func extraction_complete_ptr;
    get_chars_count_func get_chars_count_ptr;

    void Clear(void);

   public:
    Filetype_Plugin(void);
    ~Filetype_Plugin(void);

    bool Load( 
              const lem::Path &filename
              #if defined FAIND_IENGINES
              , ISearchEnginePtr se
              , IGrammarEnginePtr ge
              #endif
             );

    virtual const wchar_t* GetDescription(void) const { return get_property_ptr(PluginThis,1,0); }
    virtual const lem::Path GetPath(void) const { return dllpath; }

    virtual bool IsPlugin(void) const { return true; }

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


 class Plugin_Decoder : public lem::Char_Stream::WideStream
 {
  public:
   lem::MIMEType mime; // тип открытых данных

  protected:
   bool eof_reached;

   Filetype_Plugin *plugin; // интерфейс к используемому плагину

   ISearchEnginePtr  _ISearchEnginePtr;
   IGrammarEnginePtr _IGrammarEnginePtr;
   const PluginOptions *plugin_options;

   void* hExtraction; // Для сохранения контекста извлечения
   wchar_t *cache; // Указатель на извлеченный блок символов
   unsigned int cache_size;  // Сколько символов в Block

   int icur; // положение курсора чтения в кэше
   Stream::pos_type cache_pos; // позиция курсора чтения в кэше

   void Invalidate_Cache(void);

   virtual void Load_Cache(void);
   virtual wchar_t Read_Char(void);

  public:
   Plugin_Decoder( Filetype_Plugin *Plugin, const wchar_t *Filename, const PluginOptions *Options );
   ~Plugin_Decoder(void);

   virtual bool eof(void) const { return eof_reached; }

   virtual void Write_Beginning(void);
   virtual bool Read_Beginning( bool excp=true );

   virtual int Bits_Per_Char(void) { return 16; }
   virtual const char* GetFormat(void) const;

   virtual void wput( wchar_t ) { LEM_STOPIT; }

   virtual pos_type fsize(void) const { return 0; }
   virtual pos_type tellp(void) const;

   virtual pos_type seekp( off_type to, int whereto=SEEK_SET );
   virtual bool move( off_type offset );

   virtual void Read_Whole_Text( UFString &str );
   void Rewind(void);
   void unget( wchar_t ch );
 };
 

 class Plugin_Reader : public Text_File_Reader
 {
  private:
   lem::Path tmp_src; // временный файл с копией XLS, используется если
                      // обрабатывался не дисковый файл.

   Filetype_Plugin *plugin; // интерфейс к используемому плагину

  public:
   Plugin_Reader(
                 Filetype_Plugin *Plugin,
                 const UFString &filename,
                 lem::StreamPtr File,
                 const Scan_Options &Scanning
                ); 

   virtual ~Plugin_Reader(void);
 };

 } // namespace Search_Engine
 } // namespace Solarix

#endif
