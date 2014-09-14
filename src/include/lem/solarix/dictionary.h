// -----------------------------------------------------------------------------
// File DICTIONARY.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
// Класс Dictionary - хранение информации об объектном языке, фундаментальные
// Автоматы, составляющие Грамматический Конвейер, и так далее. Остов ("frame")
// Системы.
//
// 12.06.2007 - class Dictionary is inherited from boost::noncopyable.
// 22.06.2007 - в словаре хранится указатель на загружаемый стеммер
// 23.07.2007 - Stem выполняет стемминг, если загружен нужный модуль.
// 02.10.2007 - введена синхронизация ctor/dtor в многопоточности
// 30.06.2008 - добавлена базовая поддержка подсистемы OCR
// 24.12.2010 - рефакторинг движка N-грамм, введение Storage Abstraction
// 26.12.2010 - добавлен лемматизатор
// -----------------------------------------------------------------------------
//
// CD->15.03.1996
// LC->22.08.2013
// --------------

#ifndef SOL_DICTIONARY__H
#define SOL_DICTIONARY__H
#pragma once

 #include <lem/zeroed.h>
 #include <lem/containers.h>
 #include <lem/streams.h>
 #include <lem/date_time.h>
 #include <lem/sol_io.h>
 #include <lem/macro_parser.h>

 #include <lem/solarix/solarix_binarization_options.h>
 #include <lem/solarix/dictionary_config_options.h>
 #include <lem/solarix/automata_indeces.h>

 #include <lem/solarix/sql_production.h>
 #include <lem/solarix/load_options.h>
 #include <lem/solarix/sg_autom.h>

 #include <lem/solarix/ngrams.h>
 #include <lem/solarix/sentencebroker.h>
 #include <lem/solarix/debug_symbols.h>
 #include <lem/solarix/trace_log.h>
 #include <lem/solarix/PrefixEntrySearcher.h>
 #include <lem/solarix/SG_Affixtable.h>
 #include <lem/solarix/speaker.h>

 namespace lem
 {
  namespace Xml
  {
   class Parser;
  }
 }

 namespace Reco2
 {
  class Reconstructor2;
 }

 namespace Solarix
 {
  using lem::uint32_t;
  using lem::uint8_t;
  using lem::Sol_IO;
  using lem::Stream;
  using lem::UCString;
  using lem::UFString;
  using lem::CodeConverter;
  using lem::OFormatter;
  using lem::MCollect;
  using lem::Collect;
  using lem::USrcLookUpTable;

  class Automaton;
  class GraphGram;
  class SynGram;
  class LexicalAutomat;
  
  class AlephAutomat;
  class StorageConnections;
  class LemmatizatorStorage;
  class DebugSymbols;
  
  // Для каждого модуля сегментации можно задать индивидуальные папки,
  // где надо искать саму библиотеку, файлы данных.
  struct SegmenterEngineInfo : lem::NonCopyable
  {
   // условное наименование сегментатора, указанное в объявлении языка
   lem::UFString name;

   // полный файловый путь для папки с загружаемой библиотекой
   lem::Path library_path; 

   // если не пусто, то имя файла DLL/SO, иначе будет использовано наименование сегментатора, указанное в объявлении языка
   lem::UFString dll_name;

   // папка с данными, откуда сегментатор будет их брать
   lem::Path data_path;

   // дополнительные параметры инициализации, разбираемые самим сегментатором
   lem::UFString params;

   bool Match( const lem::UFString &segm_name ) const;
   lem::Path GetFullPath( const lem::UFString &segm_name ) const;
  };


  // Информация для подключения к хранилищу реконструктора
  struct Reconstructor2Info : lem::NonCopyable
  {
   lem::UFString provider;
   lem::UFString connection_string;
   bool enabled;
  };


  struct TextTokenizationRules;
  class LEMM_Compiler;

  class Dictionary : lem::NonCopyable
  {
   public:
    static volatile int counter; // number of active instances
    lem::zbool loaded; // Словарь успешно загружен из файла

    #if defined LEM_THREADS
    lem::Process::CriticalSection cs_share, cs_lang, cs_UseTokenizerEngineAsSyntan;
    lem::Process::RWU_Lock cs_tokenizer;
    #endif

    std::map<int,bool> UseTokenizerEngineAsSyntan_List;

    StorageConnections *storage;

    lem::Path dictionary_xml;  
    lem::Path xml_base_path; // папка, из которой загружен XML файл словаря
    lem::Path morphology_path; // путь к diction.bin

    int compilation_tracing; // флаг управления трассировкой компиляции словаря

    struct Version // условный номер версии словаря (для контроля индексных баз)
    {
     lem::int32_t code;

     Version(void) { code=0; }
     Version( const lem::UFString &serialized );

     lem::UFString serialize(void) const;

     lem::CString string(void) const;

     inline bool IsFree(void) const { return code<2; }
     inline bool IsPro(void) const { return code>1; }
     inline bool IsPremium(void) const { return code>1000; }
    };

    Version version;


    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_tokenization_rules;
    #endif
    lem::MCollect<TextTokenizationRules*> tokenization_rules;

    
    lem::Ptr<Solarix::Affix_Table> affix_table;

    lem::Ptr<Solarix::LD_Seeker> seeker;
    #if defined SOL_CAA
    lem::Ptr<Solarix::SG_Stemmer> stemmer;
    #endif

    #if !defined SOL_NO_NGRAMS
    lem::Ptr<Solarix::Ngrams> ngrams; // статистический справочник по N-граммам
    #endif

    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_prefix_entry_searcher;
    #endif
    lem::UFString prefix_entry_searcher_provider;
    lem::UFString prefix_entry_searcher_connection_string;
    lem::Ptr<PrefixEntrySearcher> prefix_entry_searcher;

    #if defined SOL_CAA && !defined SOL_NO_AA
    lem::Ptr<Solarix::TrTrace> trace_log;
    #endif

    inline const Version& GetVersion(void) const { return version; }

   private:
    LemmatizatorStorage * lemmatizer;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    LEMM_Compiler * lemmatizer_compiler;
    #endif

    DebugSymbols * debug_symbols; // информация для отладчика

    Automaton* auto_list[SOL_N_AUTOMATA]; // Список указателей на Автоматы.
    GraphGram *gg;
    SynGram *sg;
    LexicalAutomat *la;

    #if !defined SOL_NO_AA
    AlephAutomat *aa;
    #endif

    #if defined SOL_USE_SPEAKER
    lem::Ptr<Speaker> speaker;
    #endif

    lem::PtrCollect<SegmenterEngineInfo> segmenters_info;
    const SegmenterEngineInfo* FindSegmenterInfo( const lem::UFString &name ) const;

    #if defined SOL_CAA && !defined SOL_NO_AA
    // Для каждого языка может быть создан свой токенизатор.
    lem::PtrCollect<Solarix::SentenceTokenizer> tokenizers_ptr; 
    std::map< int /*язык*/, Solarix::SentenceTokenizer* > sentence_tokenizers;
    #endif

    int key_counter; // Для создания уникальных ключей.

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void Prepare( const lem::Path &outdir, const Binarization_Options &opts );
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    // Условное наименование источника текущих компилируемых данных (статей, связей)
    lem::UCString current_originator; 
    #endif
    
    Dictionary_Config cfg;

    OFormatter *nul_stream; // NUL device lem::Stream
    Sol_IO io_env;

    UCString *token_list;
    wchar_t **complex_token_list;
    static USrcLookUpTable look_up_table;
    int ndelim;

    int DefaultLanguageID;

    void Write_Binary_File_Header( lem::Stream &bin ) const;
    bool Check_Binary_File_Header( lem::Stream &bin, bool do_stop ) const;

    void LoadTokTable(void);
    void AttachAutomata(void);
    void InitA( const Dictionary_Config &cfg );
    void Clear(void);
    void PreparePipes(void);

    #if defined SOL_LOADBIN
    void LoadModules( lem::Xml::Parser &xml, lem::UFString &connection_string );
    #endif

    // Lock access to these
    Dictionary( const Dictionary & );
    void operator=( const Dictionary & );

   public:
    Dictionary(
               OFormatter *Echo_Pipe=NULL,
               OFormatter *Err_Pipe=NULL,
               const Dictionary_Config &_cfg=Dictionary_Config()
              ); 

    virtual ~Dictionary(void);

    inline const Sol_IO& GetIO(void) const { return io_env; }
    inline int GetDebugLevel_ir(void) const { return compilation_tracing; }

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt(
                 lem::Stream &txt,
                 const char *defines,
                 const Binarization_Options &options,
                 const CodeConverter &cp,
                 const UFString& root_dir
                );

    void LoadTxt(
                 lem::Stream &src_stream,
                 const MCollect<UCString> &defines,
                 const Binarization_Options &options,
                 const CodeConverter &in_cp,
                 const UFString& root_dir
                );

    void PrepareAfterTranslation( const lem::Path &outdir, const Binarization_Options &opts );
    #endif
 
    #if defined SOL_LOADBIN && defined SOL_COMPILER
    void PrepareForMerging(void);
    void BeforeSyntaxRecompilation(void);
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void Optimize(void);
    #endif

    #if defined LEM_THREADS
    static lem::Process::CriticalSection cs_init; // для аккуратной инициализации глобальных полей
    #endif 

    #if defined SOL_LOADBIN

    void LoadBin( lem::Stream &src_stream, const Load_Options &opt );
    void LoadMorphology( const lem::Path &morphology_path, const Load_Options &opt );

    void LoadAffixTable( const lem::Path &affix_path );

    void LoadSeeker( const lem::Path &seeker_path );

    void LoadStemmer( const lem::Path &stemmer_path );

    #if !defined SOL_NO_NGRAMS
    void LoadNgrams( const lem::Path &ngrams_path, NGramsDBMS *storage );
    #endif

    bool LoadModules(
                     const lem::Path &dictionary_xml,
                     const Load_Options &opt
                    );
    #endif

    void CreateEmptySeeker(void);

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &dst_stream ) const; 
    #endif

    #if defined SOL_REPORT
    void MapAlphabet( OFormatter &dst_stream );
    void MapLexicon( OFormatter &dst_stream );
    void MapTransformer( OFormatter &dst_stream );
    #endif

    #if defined SOL_EXPORT_SQL
    void Save_SQL( OFormatter &txt, OFormatter &txt2, const SQL_Production &sql_version );
    void SaveRules_SQL( OFormatter &txt, OFormatter &txt2, const SQL_Production &sql_version );
    #endif

    inline Automaton* GetAutomatPtr( int iAuto )
    { return auto_list[iAuto]; }

    inline GraphGram& GetGraphGram(void) const
    {
     LEM_CHECKIT_Z(gg);
     return *gg;
    }

    // Возвращает ссылку на объект "Синтаксическая грамматика",
    // который фактически представляет собой Лексикон - базу
    // словарных статей, словоформ и нескольких алгоритмов простого
    // доступа к ним.
    inline SynGram& GetSynGram(void) const
    {
     LEM_CHECKIT_Z(sg);
     return *sg;
    }

    inline LexicalAutomat& GetLexAuto(void) const
    {
     LEM_CHECKIT_Z(la);
     return *la;
    }

    #if !defined SOL_NO_AA
    inline AlephAutomat& GetAlephAuto(void) const
    {
     LEM_CHECKIT_Z(aa);
     return *aa;
    }
    #endif

    #if defined SOL_REPORT
    void Report( OFormatter &where_to ) const;
    #endif

    void Delete(void);

    #if defined SOL_CAA

    void Initialize(void);

    void LA_Project_Lexem( const wchar_t *Word, int id_language, int &nproj );
   
    #endif

    inline int GetNextKey(void)
    {
     LEM_CHECKIT_Z(key_counter>0);
     return key_counter++;
    }

   void SetTraceLevel( int Level, unsigned int ForWhom );

   #if defined SOL_CAA
   // Если возможно, усекает аргумент до псевдокорня. Возвращает
   // true, если усечение выполнено.
   bool Stem( UCString &word ) const;
   #endif

   #if !defined SOL_NO_NGRAMS
   lem::Ptr<Ngrams> GetNgrams(void) { return ngrams; }
   #endif

   bool IsNgramsAvailable(void) const;

   LemmatizatorStorage& GetLemmatizer(void) { return *lemmatizer; }
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   const LEMM_Compiler * GetLemmatizerCompiler() { return lemmatizer_compiler; }
   #endif

   #if defined SOL_CAA && !defined SOL_NO_AA
   lem::Ptr<SentenceTokenizer> GetSentenceTokenizer( int language );
   bool UseTokenizerEngineAsSyntan( int id_language );
   #endif

   bool IsPrefixEntrySearcherAvailable(void) const;
   lem::Ptr<PrefixEntrySearcher> GetPrefixEntrySearcher( int max_found_entries=20 );

   #if defined SOL_CAA
   // Определяет количество найденных 2- и 3-грамм
   void MatchNGrams( const lem::MCollect<lem::UCString> &words, int * unmatched_2_ngrams, int * n2, int * n3 );
   #endif 

   int GetLanguages( lem::MCollect<int> &langs );
   int GetDefaultLanguage(void);
   void SetDefaultLanguage( int id );

   #if defined SOL_CAA && !defined SOL_NO_AA
   Solarix::TrTrace* GetDebugger(void) { return trace_log.NotNull() ? &*trace_log : (TrTrace*)NULL; }
   #endif

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void SetCurrentOriginator( const lem::UCString &s ) { current_originator=s; }
   const lem::UCString & GetCurrentOriginator(void) const { return current_originator; }
   #endif

   StorageConnections * GetConnections(void) { return storage; }

   lem::UFString SubstituteConnectionString(
                                            lem::Xml::Parser &xml,
                                            const lem::UFString &connection_string
                                           ) const;

   lem::UFString BuildSQLiteConnectionString(
                                             lem::Xml::Parser &parser,
                                             const lem::UFString &raw_string,
                                             const lem::Path &xml_dir
                                            ) const;

   DebugSymbols& GetDebugSymbols(void) { return *debug_symbols; }

   #if defined SOL_CAA
   TextTokenizationRules * GetTokenizationRules( const lem::MCollect<int> & id_language );
   #endif

   #if defined SOL_USE_SPEAKER
   Speaker* GetSpeaker();
   #endif
  };

 } // end of namespace 'Solarix'
 
#endif
