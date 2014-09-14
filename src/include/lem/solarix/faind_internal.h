// -----------------------------------------------------------------------------
// File FAIND_INTERNAL.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar Faind_Engine and Search Faind_Engine API functions (Win32 DLL)
// API для доступа к грамматическому движку и поисковику в виде обычной Win32 DLL.
//
// Коды грамматических категорий (индексы классов, координат, состояний и т.д.)
// объявлены в виде символических констант в файле _sg_api.h, который
// генерируется компилятором YGRES.
//
// 09.10.2006 - рефакторинг, в именах процедур API убраны подчеркивания кроме
//              префикса "sol_"
//
// 09.10.2006 - начало интеграции расширенных регулярных выражений (RegexEx)
//
// 12.10.2006 - введена процедура sol_TranslateToBase - слово преобразует к
//              базовой форме. 
//
// 15.10.2006 - компоненты грамматического и поискового движка объединены.
//
// 21.11.2006 - в процедуру sol_TranslateToBase добавлен вызов стеммера.
//
// 30.09.2007 - в API добавляются процедуры для параметризации запросов
// -----------------------------------------------------------------------------
//
// CD->20.06.2005
// LC->28.02.2013
// --------------

#ifndef FAIND_INTERNAL__H
#define FAIND_INTERNAL__H
#pragma once

 #include <lem/oformatter.h>

 #if defined SOLARIX_SEARCH_ENGINE
 #include <lem/solarix/search_engine_query_params.h>
 #include <lem/solarix/search_engine_callbacks.h>
 #include <lem/solarix/se_scan_options.h>
 #include <lem/solarix/file_factory.h>
 #endif

 #if defined SOLARIX_SYNONYMIZER_ENGINE
 #include <lem/solarix/file_factory.h>
 #include <lem/solarix/se_scan_options.h>
 #endif

 #if defined SOLARIX_PRO && defined GM_PHRASE_GENERATOR
 #include <lem/solarix/phrase_generator.h>
 #endif

 #if defined DLL_EXPORTS || defined FAIND_IENGINES
  #define GREN_EXPORTS
 #else
  #define GREN_IMPORTS
 #endif

 #if !defined SOL_NO_AA
  //#include <lem/solarix/text_processor.h>
 #endif

 #if defined SOLARIX_PRO
  #include <lem/solarix/se_fuzzy_comparator.h>
 #endif

 #include <lem/solarix/form_table.h>

 #include <lem/solarix/_sg_api.h>

 namespace Solarix
 {
  class Tree_Node;
  class SentenceBroker;
  class PhrasoBlock;
 }

 #define SOL_CREATE_GREN_DONT_INIT_SQLITE 0x00010000
 #define SOL_CREATE_GREN_LAZY_LEXICON 0x00000001


 #if defined SOLARIX_SEARCH_ENGINE
  #if defined LEM_WINDOWS 
   typedef VOID (CALLBACK *Faind_EngineCallbackProc_StartFile)( const wchar_t *Filename );
   typedef VOID (CALLBACK *Faind_EngineCallbackProc_StartFolder)( const wchar_t *Folder );
   typedef VOID (CALLBACK *Faind_EngineCallbackProc_Success)(
                                                            const wchar_t *filename,
                                                            const wchar_t *location,
                                                            const wchar_t *tmp
                                                           );
   typedef const wchar_t* (CALLBACK *sol_DocumentProvider)( const wchar_t *Docname );
  #else
   typedef void (*Faind_EngineCallbackProc_StartFile)( const wchar_t *Filename );
   typedef void (*Faind_EngineCallbackProc_StartFolder)( const wchar_t *Folder );
   typedef void (*Faind_EngineCallbackProc_Success)(
                                                    const wchar_t *filename,
                                                    const wchar_t *location,
                                                    const wchar_t *tmp
                                                   );
   typedef const wchar_t* (*sol_DocumentProvider)( const wchar_t *Docname );
  #endif 
 #endif


namespace Solarix
{
 #if defined SOLARIX_SEARCH_ENGINE
 namespace Search_Engine
 {
  class CommandParser;
  class CmdExecutor;
  class RegexEx;
 }
 #endif

 class Dictionary;
 class LD_Seeker;
 class SentenceBroker;

 class XmlText
 {
  private:
   lem::MemStream content;

  public:
   lem::OUFormatter *out;

  public:
   XmlText(void);
   ~XmlText(void);

   const char* GetChars(void) const { return content.get_Block(); }
   int GetChars( char *Buffer, int BufferSize );
   lem::Stream::pos_type GetLen(void) const { return content.fsize(); }
 };

  typedef enum { No_Dataset, Xml_Dataset, Html_Dataset } Type_Dataset;

  #if defined SOLARIX_SEARCH_ENGINE
  struct Start_File_Processing_Handler;
  #endif

  class SynGram;

  // This class is highest-level wrapper for text search engine.
  class Faind_Engine
  {
   public:
    #if defined LEM_THREADS
    lem::Process::CriticalSection cs;
    #endif
    lem::Ptr<Solarix::Dictionary> dict; // указатель на загруженный словарь
    lem::Ptr<Solarix::LD_Seeker> seeker; // быстрый поиск слов

    #if defined SOLARIX_PRO
    lem::Ptr<Solarix::Search_Engine::Fuzzy_Comparator> fuzzy; // для нечеткого поиска
    #endif

    Solarix::SynGram *sg; // для ускорения доступа к лексикону
  
    int n_lexicon_reserve;

    int DefaultLanguage; // Default language index

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_error;
    #endif
    lem::UFString error; // Error message if was any (non thread-safe!!!)
    void SetError( const lem::UFString & error_text );

    #if defined SOLARIX_SEARCH_ENGINE
    lem::Ptr<Solarix::Search_Engine::CommandParser> parser;
    Start_File_Processing_Handler *callback;
    lem::Ptr<Solarix::Search_Engine::Crawler> crawler;
    lem::Ptr<Solarix::Search_Engine::File_Type_Detector> detector;
    Solarix::Search_Engine::Scan_Options scanning;

    // Which format of result dataset to use.
    Type_Dataset dataset_flag;
    lem::zbool html_header_footer;

    lem::zbool ini_loaded;
    lem::zbool ram_cataloguer;
    #elif defined SOLARIX_SYNONYMIZER_ENGINE
    Solarix::Search_Engine::Scan_Options scanning;
    lem::Ptr<Solarix::Search_Engine::File_Type_Detector> detector;
    #endif

    lem::OFormatter *nul_tty;
    lem::zbool ok;

   public:
    #if defined SOLARIX_SEARCH_ENGINE
    Faind_Engine( Solarix::Search_Engine::CommandParser *Parser=NULL );
    #else
    Faind_Engine(void);
    #endif

    virtual ~Faind_Engine(void);

    void PostINI(void);

    #if defined SOLARIX_SEARCH_ENGINE
    bool Set_Callback_StartFile( Faind_EngineCallbackProc_StartFile ptr );
    bool Set_Callback_StartFolder( Faind_EngineCallbackProc_StartFolder ptr );
    bool Set_Callback_Success( Faind_EngineCallbackProc_Success ptr );
    #endif

    #if defined SOLARIX_SEARCH_ENGINE
    // Do not generate implicit result dataset: command line
    // must contain explicit options to build result file.
    void Dont_Generate_Results(void) { dataset_flag = No_Dataset; }

    // Generate HTML result implicitely.
    void Generate_Html(void) { dataset_flag = Html_Dataset; }

    // Generate XML result implicitely.
    void Generate_Xml(void) { dataset_flag = Xml_Dataset; }

    void Strip_Html(void) { html_header_footer=false; }
    #endif

    bool Load( const wchar_t *DictionaryXml, bool LazyLexicon );
   };


 struct GREN_Strings
 {
  lem::MCollect<lem::UCString> list;
 };

 struct GREN_WordCoords
 {
  lem::MCollect<Solarix::Word_Coord> list;
 };

  #if defined SOLARIX_SEARCH_ENGINE
  struct Faind_Executor
  {
   lem::MemStream dump;
   Solarix::Search_Engine::CmdExecutor* cmd;
   lem::UFString *result; // search results (XML or HTML text)

   Faind_Executor(void);
   ~Faind_Executor(void);

    int GetResultLen(void) const
    { return result ? result->length() : 0; }
  
    void GetResult( char *buffer );
    void GetResult( wchar_t *buffer );
  };
  #endif

 


 #if defined SOLARIX_SEARCH_ENGINE
 // Callback-драйвер - для поддержания обратной связи с клиентским кодом во время
 // длительного поиска.
 struct Start_File_Processing_Handler : public Solarix::Search_Engine::Progress_Callback
 {
  Faind_EngineCallbackProc_StartFile cbStartFile;
  Faind_EngineCallbackProc_StartFolder cbStartFolder;
  Faind_EngineCallbackProc_Success cbSuccess;

  Faind_Engine* engine;

  Start_File_Processing_Handler( Faind_Engine* E );

  // Метод вызывается при начале обработки очередного файла 
  virtual void Start_File( const wchar_t *filename );

  // Метод вызывается при начале обработки очередного каталога
  virtual void Start_Folder( const wchar_t *filename ); 

  // Есть успех поиска паттерна в указанном файле
  virtual void Success( const wchar_t *filename, const wchar_t *location, const wchar_t *tmp );
 };
 #endif
}

#if !defined DLL_EXPORTS
 #define FAIND_INTERNAL_TYPES
#endif

#if defined FAIND_INTERNAL_TYPES
typedef Solarix::Faind_Engine* HFAIND;
typedef Solarix::XmlText* HFAINDXML;
#endif


#if defined SOLARIX_GRAMMAR_ENGINE || !defined FAIND_INTERNAL_TYPES
typedef void* HFAINDCMD;
typedef void* HREGEXEX;
typedef void* HFAINDPARAMS;
#else
typedef Solarix::Faind_Executor* HFAINDCMD;
typedef Solarix::Search_Engine::RegexEx* HREGEXEX;
typedef Solarix::Search_Engine::QueryParams* HFAINDPARAMS;
#endif

#if defined SOLARIX_PRO && defined GM_PHRASE_GENERATOR && defined FAIND_INTERNAL_TYPES
typedef PhraseGenerator* HGREN_PHRASOMAT;
typedef Solarix::SentenceBroker* HGREN_SBROKER;
#else
typedef void* HGREN_PHRASOMAT; 
typedef void* HGREN_SBROKER;
#endif

#if defined FAIND_INTERNAL_TYPES 
typedef Solarix::GREN_Strings* HGREN_STR;
typedef lem::MCollect<int> *HGREN_INTARRAY;
typedef Solarix::GREN_WordCoords* HGREN_WCOORD;
typedef lem::UFString * HGREN_LONGSTRING;
#endif

#if !defined SOL_NO_AA && defined FAIND_INTERNAL_TYPES
typedef Solarix::Res_Pack* HGREN_RESPACK;
typedef const Solarix::Tree_Node* HGREN_TREENODE;
#else
typedef void* HGREN_RESPACK;
typedef const void* HGREN_TREENODE;
#endif

#include <lem/solarix/faind.h>

inline Solarix::Faind_Engine* HandleEngine( HFAIND hFaind )
{
 return (Solarix::Faind_Engine*)hFaind;
}


inline Solarix::GREN_Strings* HandleStrList( HGREN_STR hStr )
{
 return (Solarix::GREN_Strings*)hStr;
}

inline Solarix::PhrasoBlock* HandlePack( HGREN_RESPACK hPack )
{ return (Solarix::PhrasoBlock*)hPack; }

inline const Solarix::Tree_Node* HandleNode( HGREN_TREENODE hNode )
{
 return (const Solarix::Tree_Node*)hNode;
}

inline Solarix::SentenceBroker* HandleBroker( HGREN_SBROKER hBroker )
{
 return (Solarix::SentenceBroker*)hBroker;
} 

#endif
