// -----------------------------------------------------------------------------
// File SE_QUERY.H
//
// (c) Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// SEARCH ENGINE Core
//
// Объявления классов для запросов (паттерны) в поисковике.
//
// 11.11.2006 - рефакторинг имен методов, убраны '_'
//
// 10.12.2007 - большое обновление кода в связи с реализацией поддержки
//              сложных синонимов (многословных статей в тезаурусе).
// 01.08.2008 - изменение реализации класса Word - хранение списка имен базовых
//              форм для оптимизации поиска по индексу CLucene и MySql.
//
// 11.09.2008 - изменения в реализации нечеткого поиска по AND-словам
// -----------------------------------------------------------------------------
//
// CD->31.10.2004
// LC->11.11.2009
// --------------

#ifndef SEARCHER_QUERY__H
#define SEARCHER_QUERY__H
#pragma once

 #include <lem/set.h>
 #include <lem/string_parser.h>

 //#include <lem/solarix/solarix.h>
 #include <lem/solarix/form_table.h>
 #include <lem/solarix/variator.h>
 //#include <lem/solarix/text_processor.h>
 #include <lem/solarix/phrasema.h>
 #include <lem/solarix/sg_autom.h>
// #include <lem/solarix/pm_condictors.h>
 #include <lem/solarix/word_form.h>
 #include <lem/solarix/se_morphology.h>
 #include <lem/solarix/se_fuzzy_comparator.h>
 #include <lem/solarix/se_index_options.h>
 #include <lem/solarix/se_doc_topic.h>
 #include <lem/solarix/se_fix_context.h>
 #include <lem/solarix/se_context_options.h>
 #include <lem/solarix/se_lexer_options.h>
 #include <lem/solarix/se_search_options.h>

 #if !defined FAIND_NO_BOOST_REGEX
 #include <boost/regex.hpp>
 #endif

 namespace Solarix
 {
  namespace Search_Engine
  {
   struct Search_Options;  
   struct Context_Options;
   struct Action_Options;
   #if defined FAIND_INDEXER
   class Assoc_Files;
   class Indexer;
   class Document_Index;
   struct File_Entry;
   #endif

   class Topic_Finder;

  using lem::Real1;
  using lem::MCollect;
  using lem::PtrCollect;
  using std::wstring;
  using lem::UFString;
  using lem::UCString;
  using lem::Stream;
  using lem::StrParser;
  using lem::UToken;
  using Solarix::Search_Engine::Base_File_Reader;
  using Solarix::Word_Coord;
  using Solarix::RC_Lexem;
  using Solarix::Dictionary;
  using Solarix::LD_Seeker;
  #if !defined SOL_NO_AA
  using Solarix::Variator;
//  using Solarix::Text_Processor;
  #endif 

  #if defined FAIND_INDEXER
  using Solarix::Search_Engine::Indexer;
  using Solarix::Search_Engine::Assoc_Files; 
  using Solarix::Search_Engine::File_Entry;
  #endif 

  class Fix_Context;
  class Fix_States;

  // ***********************************************************
  // Класс представляет интерфейс для получения уникальных id.
  // ***********************************************************
  class Sequence
  {  
   public:
    Sequence(void) {}

    virtual int operator()(void)=0;
  };



  struct Pattern;
  // ******************************************
  // Базовый класс для описания дерева запроса
  // ******************************************
  class Base_Node : public MCollect<Base_Node*>
  {
   private:
    Base_Node( const Base_Node& );
    void operator=( const Base_Node& );

   public:
    typedef enum { UNKNOWN_NODE, QUERY_ROOT, REGEX_PATTERN, LOGIC_PATTERN,
                   WORDS_AND, SINGLE_WORD, WORD,
		           WORD_ALT, WORD_GR, WORD_ANY, 
                   WORD_REGEX, WORD_DIRECT, WORD_CASE_SENSITIVE,
                   WORD_WORDFORMS, WORD_WORDFORMS_SOUNDEX, LOGIC_OR, LOGIC_AND,
				   LOGIC_NOT, ANY_TEXT } NodeType;

   protected:
    NodeType type; // поле типа - нужно для работы с потоками (сохранение запроса)

    void OptimizeChildren(void);
    void Clear(void);

   public:
    Base_Node(void);

    lem::zeroed<bool> negative;        // флаг логического отрицания для узла

    inline NodeType GetType(void) const { return type; }

    virtual ~Base_Node(void);

    // Возвращается краткое условное имя узла
    virtual const wstring GetName(void) const=0;

    // Возвращается подробное описание узла (без имени)
    virtual const wstring GetAttrs(void) const=0;

    // Вызывается перед началом новой попытки фиксации образца на тексте.
    virtual void PrepareToMatch(void);

    #if defined FAIND_INDEXER
    virtual void PrefetchKeywords( Solarix::Search_Engine::Indexer &idb );
    #endif

    inline void Negate(void) { negative = !negative; }

    // Поиск соответствия узлу в загруженном тексте - основная функция
    // для реализации прямого поиска паттернов в текстах.
    virtual bool Fix(
                     Text &text,
                     Dictionary *dict,
                     const LD_Seeker *seeker,
                     #if !defined SOL_NO_AA
//                     Solarix::Text_Processor *tpu, 
                     #endif 
                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                     Fix_Context& context,
                     Fix_States& fx_states
                    );

    virtual bool ContainedInString( const UFString &str ) const;

    #if defined FAIND_INDEXER
    // Подготовка паттерна к быстрому сопоставлению с проиндексированными
    // документами.
    virtual void PrepareToIndexedFix(
                                     const Lexer_Options &lexer_options,
                                     Search_Engine::Indexer *indexer,
                                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                     bool second_pass
                                    );
    #endif

    virtual bool DoesNeedIndexRedo(void) const;

    virtual void RefreshAfterOptimization(void);

    #if defined FAIND_INDEXER
    // Поиск соответствия узлу (обычно - одно слово) в индексе документа.
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif


    #if defined FAIND_INDEXER
    // Еще одна функция для организации поиска паттернов: возвращается
    // список ассоциированных файлов, соответствующих запросу.
    // Возвращенный NULL подразумевает, что данный метод поиска неприменим.
    virtual Assoc_Files* GetAssocFiles( Indexer &indexer, const Pattern &pattern ) const;
    #endif

    // Этот метод вызывается для поиска по накопленным во время
    // сканирования домена данным (к примеру - при извлечении знаний).
    virtual bool AfterDomainScanned(
                                    Dictionary *dict,
                                    #if !defined SOL_NO_AA
//                                    Solarix::Text_Processor *tpu,
                                    #endif
                                    MCollect<Fix_Context*> &fx_ctx
                                   );


    virtual void ApplyDictionary(
                                 Dictionary *dict,
                                 Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                 const Lexer_Options &lo
                                 #if !defined SOL_NO_AA
                                 //, Solarix::Text_Processor *tpu
                                 #endif
                                );

    virtual Base_Node* Optimize(void);
    virtual void Apply( const Search_Options &flags );

    void WriteType( lem::Stream &bin ) const;
    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );

    static Base_Node* load( lem::Stream &bin );
    void save( lem::Stream &bin ) const;
    static Base_Node* optimize( Base_Node *query );

    virtual void Print( OFormatter &stream, int offset, Dictionary *dict ) const;

    virtual bool IsWord(void) const { return false; }

    inline bool IsNegative(void) const { return negative; }
    inline void SetNegative( bool f ) { negative=f; }

    // Нужно для узла (или его веток) загружать Словарь?
    virtual bool NeedsDictionary(void) const;

    // Данный метод вызывается для быстрой проверки паттерна по индексу
    // документа - для AND-фраз. Если данный способ проверки не подходит,
    // например из-за наличия логики OR в паттерне, то возвращается true -
    // то есть документ будет детально проверяться.
    #if defined FAIND_INDEXER
    virtual bool TestAndPhrase( Indexer &idb, const File_Entry &file_entry ) const;
    #endif

    #if defined FAIND_INDEXER
    virtual Fix_Rank CalcDocRank( const File_Entry &file_entry ) const;
    #endif

    virtual void SetCaseSensitive(void);
    virtual void SetWildcards(void);
    virtual void SetRegex(void);
    virtual void SetMorphology( Morphology m );
    virtual void SetSyntax( Syntax x );
    virtual void SetSoundex(void);
    virtual void SetRxSuffix(void);
    virtual void SetSameSentence(void);
    virtual void SetSameLine(void);
    virtual void SetMaxNetDistance( int d );
    virtual void SetOrdered(void);
    virtual void SetDistance( int Dist );
  };


  // *********************************************************************
  // Корневой узел для образца запроса: бывает двух видов, представленных
  // классами-наследниками.
  // *********************************************************************
  class Query_Root : public Base_Node
  {
   public:
    float minbound;  // мин достоверность фиксируемого контекста
    float skip_word; // граница для отбрасывания слов (отбрасываются все
                     // с весом ниже указанного)

   protected:
    UFString pattern; // исходное представление паттерна
    UFString qname;   // имя паттерна

   public:
    Query_Root(void);
    Query_Root( const UFString &Name, const UFString &Pattern );

    virtual void Parse( const UFString &txt, const Search_Options &flags );

    // Если запрос для фиксации требует представления текста в виде одной строки
    virtual bool NeedsSerializedText(void) const;

    // Нужна ли разбивка на слова
    virtual bool NeedsWordedText(void) const;

    inline void SetMinBound( float f ) { minbound=f; }
    inline float GetMinBound(void) const { return minbound; }

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );

    inline const UFString& GetQueryName(void) const { return qname; }
    inline const UFString& GetPattern(void) const { return pattern; }

    virtual UFString GetPatternText(void) const;

    #if defined FAIND_INDEXER
    virtual bool TestAndPhrase( Indexer &idb, const File_Entry &file_entry ) const;
    #endif
  };


  // *******************************************************
  // Корневой узел для образца запроса ПО ОТДЕЛЬНЫМ СЛОВАМ
  // *******************************************************
  class Query_Words : public Query_Root
  {
   public:
    Query_Words( const UFString &Name, const UFString &Pattern );

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;

    virtual bool NeedsSerializedText(void) const { return false; }
    virtual bool NeedsWordedText(void) const { return true; }

    #if defined FAIND_INDEXER
    virtual Assoc_Files* GetAssocFiles( Indexer &indexer, const Pattern &pattern ) const;
    #endif

    virtual bool ContainedInString( const UFString &str ) const;
  };



  // *******************************************
  // Корневой узел для образца запроса ПО ФРАЗЕ
  // *******************************************
  class Query_Phrase : public Query_Root
  {
   public:
    Query_Phrase(void);

    virtual const wstring GetName(void) const;
  };



  class Single_Word : public Query_Root
  {
   public:
    Single_Word(void);
    Single_Word( Base_Node *x );

    void push_back( Base_Node *x );

    virtual bool Fix(
                     Text &text,
                     Dictionary *dict,
                     const LD_Seeker *seeker,
                     #if !defined SOL_NO_AA
//                     Text_Processor *tpu,
                     #endif
                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                     Fix_Context& context,
                     Fix_States& fx_states 
                    );

    virtual bool ContainedInString( const UFString &str ) const;

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;

    #if defined FAIND_INDEXER
    virtual Assoc_Files* GetAssocFiles( Indexer &indexer, const Pattern &pattern ) const;
    #endif
  };


  // ***********************************************************************
  // Формальное требование, удовлетворяемое ЛЮБЫМ документом - используется
  // для отключения поиска файлов по содержимому и обработке их другими
  // алгоритмами
  // ***********************************************************************
  class Any_Text : public Query_Root
  {
   public:
    Any_Text(void);
    Any_Text( Base_Node *x );

    virtual bool Fix(
                     Text &text,
                     Dictionary *dict,
                     const LD_Seeker *seeker,
                     #if !defined SOL_NO_AA
//                     Text_Processor *tpu,
                     #endif
                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                     Fix_Context& context,
                     Fix_States& fx_states 
                    );

    virtual bool ContainedInString( const UFString &str ) const;

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;

    #if defined FAIND_INDEXER
    virtual Assoc_Files* GetAssocFiles( Indexer &indexer, const Pattern &pattern ) const;
    #endif
  };


  class Word;

  class Words_Group : public Query_Root
  {
   protected:
    bool ordered;       // Строго следовать порядку слов в паттерне
    int distance;       // расстояние между словами не должно быть более этого
    bool same_sentence; // слова должны быть в пределах одного предложения
    bool same_line;     // слова должны быть в пределах одной строки 
    Syntax syntax;      // Выполнять грамматический анализ фразы
    bool soundex;       // нечеткий анализ
    lem::zbool allow_partial; // допускается фиксация не всех слов запроса

    void ParseUntilToken(
                         StrParser<UFString> &src,
                         MCollect<Base_Node*> &list1,
                         const UFString &end_token
                        );

   public:
    Words_Group(void);

    virtual void Parse( const UFString &txt, const Search_Options &flags );
    virtual Base_Node* Optimize(void);
    virtual void Apply( const Search_Options &flags );

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;

    virtual void SetSameSentence(void);
    virtual void SetSameLine(void);
    virtual void SetSyntax( Syntax x );
    virtual void SetSoundex(void);
    virtual void SetOrdered(void);
    virtual void SetDistance( int Dist );

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );
  };


  // ********************************************************
  // Для поиска отдельных слов, сгруппированных логическим И
  // ********************************************************
  class Words_And : public Words_Group
  {
   private:
    MCollect<int> i_fixed;

    #if defined SOLARIX_PRO
    lem::PtrCollect<Words_And> alter_ands;
    void GenerateAlterAnds(
                           Solarix::Dictionary *dict,
                           Solarix::Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           const Lexer_Options &lo
                          );
    #endif 

    bool allow_simple_correlate;

    #if !defined SOL_NO_AA
    // Слова группы в виде одного предложения.
    Solarix::Sentence words;
    #endif

    bool DoesMatch(
                   const Word_Form &node,
                   const Word &word,
                   Dictionary &dict
                  ) const;

    #if !defined SOL_NO_AA
    // Карта соответствия вариатора и паттерна.
    struct Corr_Map : lem::NonCopyable
    {  
     const Variator *var; // для какого вариатора

     // соответствия для корней вариатора
     PtrCollect< MCollect< std::pair< int /*iword*/, const Word* > > > root;

     bool good; // заполнена ли карта

     Corr_Map(void) { var=NULL; good=false; }
    };

    PtrCollect<Corr_Map> corrs;

    PtrCollect<Variator> variators;
    #endif

    bool FixSent(
                 Text &text,
                 Dictionary *dict,
                 const LD_Seeker *seeker,
                 #if !defined SOL_NO_AA
//                 Text_Processor *tpu, 
                 #endif 
                 Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                 Fix_Context& context,
                 Fix_States& fx_states
                );

    bool FixSimple(
                   Text &text,
                   Dictionary *dict,
                   const LD_Seeker *seeker,
                   Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                   Fix_Context& context,
                   Fix_States& fx_states
                  );

    bool FixSimpleProx(
                       Text &text,
                       Dictionary *dict,
                       const LD_Seeker *seeker,
                       Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                       Fix_Context& context,
                       Fix_States& fx_states
                      );

    bool FixOrdered(
                    Text &text,
                    Dictionary *dict,
                    const LD_Seeker *seeker,
                    Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                    Fix_Context& context,
                    Fix_States& fx_states
                   );

    bool FixFuzzy(
                  Text &text,
                  Dictionary *dict,
                  const LD_Seeker *seeker,
                  #if !defined SOL_NO_AA
//                  Text_Processor *tpu, 
                  #endif 
                  Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                  Fix_Context& context,
                  Fix_States& fx_states
                 );

    #if !defined SOL_NO_AA
    // Информация о соответствии опорной точки (слова) и узла синтаксического дерева
    // в вариаторе.
    struct Point_Position
    {
     int i_root; // порядковый номер корня в вариаторе
     const Tree_Node *parent; // родительский узел (может быть NULL)
     const Tree_Node *node; // совпавший с опорной точкой узел
     int i_child; // индекс ветки узла в списке веток родителя
    };
    #endif

    #if !defined SOL_NO_AA
    void FindInVar(
                   const Variator &var,
                   const Word &word,
                   MCollect< Point_Position > &res,
                   Dictionary &dict
                  ) const;

    void FindInVar(
                   int i_root,
                   int i_child,
                   const Tree_Node *parent,
                   const Tree_Node *node,
                   const Word &word,
                   MCollect< Point_Position > &res,
                   Dictionary &dict
                  ) const;
    #endif

   public:
    Words_And(void);

    virtual const wstring GetName(void) const;

    virtual bool Fix(
                     Text &text,
                     Dictionary *dict,
                     const LD_Seeker *seeker,
                     #if !defined SOL_NO_AA
//                     Text_Processor *tpu,
                     #endif 
                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                     Fix_Context& context,
                     Fix_States& fx_states 
                    );

    virtual bool ContainedInString( const UFString &str ) const;

    virtual void ApplyDictionary(
                                 Dictionary *dict,
                                 Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                 const Lexer_Options &lo
                                 #if !defined SOL_NO_AA
////                                 , Solarix::Text_Processor *tpu
                                 #endif
                                );

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );

    #if defined FAIND_INDEXER
    virtual Assoc_Files* GetAssocFiles( Indexer &indexer, const Pattern &pattern ) const;
    virtual bool TestAndPhrase(
                               Indexer &indexer,
                               const File_Entry &file_entry
                              ) const;
    #endif
  };

 

  // ******************************************
  // Элемент запроса: требование на одно слово
  // ******************************************
  class Word : public Base_Node
  {
   public:
    UCString word; // исходное слово

    const Search_Options *org_flags;

    lem::zbool case_sensitive;  // учитывать регистр букв
    lem::zbool regex;           // считать регулярным выражением
    lem::zbool wildcards;       // модификатор - подвид регулярного выражения
    lem::zbool rx_suffix;       // модификатор для -rx добавляет к терму в конце .+ для откбрасывания суффикса при поиске
    Morphology morphology;      // режим морфологии - приводить к базовой словоформе или учитывать динамические словоформы
    lem::zbool soundex;         // нечеткий поиск
    int max_net_distance;       // макс. сетевое расстояние при сравнении статей
    lem::zbool obligatory;      // Слово обязательно должно присутствовать в контексте
    float minbound;             // мин достоверность фиксации
    lem::zbool strip_accents;   // нормализовать слово перед сравнениями (лигатуры, акценты)
    lem::zbool rooting;         // для нечеткого сравнения разрешено приведение к корням
    lem::zbool try_translit;    // пробовать транслитерированную форму

    int freq; // частота слова
    float w;  // вес слова, или его ценность - для стоп-слов (союзов и т.д.)
              // это будет почти 0.

    UCString normalized_word; // приведенное к нижнему регистру, убраны диактрики и т.д.
    UCString normalized_word_diactrics; // приведенное к нижнему регистру, но диактрики оставлены

    RC_Lexem rc_ml; // Слово представлено в виде мультилексемы
    MCollect<Word_Coord> found_list;
    MCollect<Real1> val_list;

    MCollect<UCString> str_list; // найденные словоформы и другие формы
    MCollect<float> str_val; // достоверность найденных форм
    std::set<int> ind_list; // супериндексы ключевых слов для форм
    lem::zbool compare_roots; // для ускорения - сравнивать сначала корень
    lem::zbool stopword; // слово относится к категории стоп-слов

    // Базовые формы и их достоверность (для поиска по индексам типа CLucene, в которых
    // лексемы хранятся в нормализованном виде).
    std::map<lem::UCString,float> base_forms;

    MCollect<int> ientry_net; // связанные по тезаурусу статьи

    MCollect<UCString> fuzzy_roots; // найденные корни для нечеткого сравнения
    MCollect<float> fuzzy_roots_vals; // достоверность найденных корней

    lem::zbool accel_ok;  // можно использовать акселератор для сревнения со списком str_list
    UCString accel; // найденный инвариант в списке str_list
    void BuildAccel(void);

    UCString stem; // выделенный псевдокорень для случаев, когда выполняется
                   // поиск не по словарной морфологии.

    int min_len, max_len; // диапазон длин словоформ

    MCollect< std::pair< int /*ientry*/, Real1 /*proj_val*/ > > ientry;

    UFString fix_name; // Именованная точка фиксации

    int catalog_index; // Супериндекс (уникальный ключ) слова в общем списке 
                       // ключевых слов в индексаторе.

    lem::Collect<lem::UFString> complex_links; // сложные (многословные) синонимы
   
    lem::PtrCollect< lem::PtrCollect<Word> > complex_links2; // разбитые на лексемы сложные синонимы

    lem::SoundexPattern soundex_pattern; // для ускорения поиска в именах файлов

    int CalcDistance( Dictionary *dict, int ientry1, int ientry2 ) const;

    void Clear(void);
    void LoadFixName( StrParser<UFString> &txt );
    void SetContent( const UCString &Word );

    #if defined FAIND_INDEXER
    void FindWithoutAffixes(
                            Search_Engine::Indexer *indexer,
                            Search_Engine::Fuzzy_Comparator *fuzzy_eq
                           );

    virtual void PrefetchKeywords( Solarix::Search_Engine::Indexer &idb );
    virtual bool DoesNeedIndexRedo(void) const;
    #endif

    virtual void FindComplexLinks(
                                  Dictionary *dict,
                                  Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                  const Lexer_Options &lo
                                  #if !defined SOL_NO_AA
//                                  , Text_Processor *tpu
                                  #endif
                                 ); 
    
   public:
    Word(void);
    Word( const UCString &Word );

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;

    inline const UCString& GetWord(void) const { return word; }

    inline const UFString& GetFixName(void) const { return fix_name; }

    virtual void SetCaseSensitive(void);
    virtual void SetRegex(void);
    virtual void SetWildcards(void);
    virtual void SetMorphology( Morphology x );
    virtual void SetSoundex(void);
    virtual void SetRxSuffix(void);
    virtual void SetObligatory( bool f );
    virtual void SetMaxNetDistance( int d );

    inline bool GetObligatory(void) const { return obligatory; }

    inline void SetFreq( int n ) { freq=n; }
    inline int GetFreq(void) const { return freq; }

    inline void SetWeight( float f ) { w=f; }
    inline float GetWeight(void) const { return w; }

    virtual void Project( Dictionary *dict );

    virtual bool DoesMatch(
                           File_Lexem &word,
                           Text &text,
                           Dictionary *dict,
                           const LD_Seeker *seeker,
                           Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           Fix_Rel &rel
                          ) const;

    #if defined SOLARIX_PRO
    virtual bool DoesMatchComplexLinks(
                                       Text &text,
                                       int ifrom, int iupto, int &ihit,
                                       Dictionary *dict,
                                       const LD_Seeker *seeker,
                                       Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                       Fix_Context& context,
                                       Fix_Rel &rel
                                      ) const;
    #endif

    virtual bool ContainedInString( const UFString &str ) const;

    virtual bool DoesMatch( const Solarix::Word_Form &wf, Dictionary &dict ) const;

    virtual Base_Node* Optimize(void);

    virtual void Apply( const Search_Options &flags );

    virtual void ApplyDictionary(
                                 Dictionary *dict,
                                 Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                 const Lexer_Options &lo
                                 #if !defined SOL_NO_AA
////                                 , Solarix::Text_Processor *tpu
                                 #endif
                                );

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );

    static Word* load_txt( StrParser<UFString> &txt );
    virtual void LoadTxt( StrParser<UFString> &txt );

    virtual bool IsWord(void) const { return true; }

    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *catalog,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif

    #if defined FAIND_INDEXER
    virtual Assoc_Files* GetAssocFiles( Indexer &indexer, const Pattern &pattern ) const;
    #endif

    #if defined FAIND_INDEXER
    virtual void PrepareToIndexedFix(
                                     const Lexer_Options &lexer_options,
                                     Search_Engine::Indexer *indexer,
                                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                     bool second_pass  
                                    );
    #endif 

    inline bool IsStopword(void) const { return stopword; }

    inline int CountCatalogIndexes(void) const { return ind_list.empty() ? (catalog_index==UNKNOWN ? 0 : 1) : CastSizeToInt(ind_list.size()); }
    inline int GetCatalogIndex(void) const { return catalog_index; }
    void GetCatalogIndexes( lem::MCollect<int> &i ) const;

    #if defined FAIND_INDEXER
    virtual Fix_Rank CalcDocRank( const File_Entry &file_entry ) const;
    #endif
  };


 
  // ****************************************************
  // Логическое слово - группа альтернативных слов (ИЛИ).  
  // ****************************************************
  class Word_Alt : public Word
  {
   private:
    void Clear(void);

    #if defined FAIND_INDEXER
    Assoc_Files* GetAssocFiles( Indexer &indexer, const Pattern &pattern ) const;
    #endif

   public:
    Word_Alt(void);

    virtual bool DoesMatch(
                           File_Lexem &word,
                           Text &text,
                           Dictionary *dict,
                           const LD_Seeker *seeker,
                           Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           Fix_Rel &rel
                          ) const;

    virtual bool ContainedInString( const UFString &str ) const;

    virtual bool DoesMatch(
                           const Solarix::Word_Form &wf,
                           Dictionary &dict
                          ) const;

    virtual Base_Node* Optimize(void);

    virtual void ApplyDictionary(
                                 Dictionary *dict,
                                 Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                 const Lexer_Options &lo
                                 #if !defined SOL_NO_AA
//                                 , Solarix::Text_Processor *tpu
                                 #endif
                                );

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;

    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif
  };



  // *****************************
  // Квантор - любое слово.
  // *****************************
  class Word_Any : public Word
  {
   private:
    void Clear(void);

   public:
    Word_Any(void);

    virtual bool DoesMatch(
                           File_Lexem &word,
                           Text &text,
                           Dictionary *dict,
                           const LD_Seeker *seeker,
                           Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           Fix_Rel &rel
                          ) const;

    virtual bool DoesMatch( const Solarix::Word_Form &wf, Dictionary &dict ) const;

    virtual bool ContainedInString( const UFString &str ) const;

    virtual Base_Node* Optimize(void);
    virtual void ApplyDictionary(
                                 Dictionary *dict,
                                 Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                 const Lexer_Options &lo
                                 #if !defined SOL_NO_AA
//                                 , Solarix::Text_Processor *tpu
                                 #endif
                                );
    virtual void Project( Dictionary *dict ) {}

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;
    virtual void LoadTxt( StrParser<UFString> &src );
    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif
  };



  #if defined FAIND_QUANTORS
  // ******************************************************
  // Опорная точка с детализацией грамматических категорий.
  // ******************************************************
  class Word_Gr : public Word
  {
   private:
    lem::MCollect<UToken> tokens;
    Solarix::PM_RuleElement *point; 
    
    void Clear(void);

    virtual void ApplyDictionary(
                                 Dictionary *dict,
                                 Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                 const Lexer_Options &lo
                                 #if !defined SOL_NO_AA
                                 //, Solarix::Text_Processor *tpu
                                 #endif
                                );

   public:
    Word_Gr(void);

    virtual bool DoesMatch(
                           File_Lexem &word,
                           Text &text,
                           Dictionary *dict,
                           const LD_Seeker *seeker,
                           Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           Fix_Rel &rel
                          ) const;

    virtual bool DoesMatch( const Solarix::Word_Form &wf, Dictionary &dict ) const;
    virtual Base_Node* Optimize(void);

    virtual void Print( OFormatter &stream, int offset, Dictionary *dict ) const;

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;
    virtual void LoadTxt( StrParser<UFString> &txt );
    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );

    virtual bool NeedsDictionary(void) const;
    void TransformToAA( Dictionary *dict, MCollect<UCString> &s );
    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif
  };
  #endif

  #if !defined FAIND_NO_BOOST_REGEX
  class Word_Regex : public Word
  {
   private:
    boost::wregex rx;
    lem::MCollect<int> ientry_regex_matched;


    #if defined FAIND_INDEXER
    virtual void PrepareToIndexedFix(
                                     const Lexer_Options &lexer_options,
                                     Search_Engine::Indexer *indexer,
                                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                     bool second_pass
                                    );
    #endif


    virtual void ApplyDictionary(
                                 Dictionary *dict,
                                 Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                 const Lexer_Options &lo
                                 #if !defined SOL_NO_AA
//                                 , Solarix::Text_Processor *tpu
                                 #endif
                                );


   public:
    Word_Regex(void);
    Word_Regex( const UCString &x );

    virtual void RefreshAfterOptimization(void);

    virtual bool DoesMatch(
                           File_Lexem &word,
                           Text &text,
                           Dictionary *dict,
                           const LD_Seeker *seeker,
                           Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           Fix_Rel &rel
                          ) const;

    virtual bool DoesMatch( const Solarix::Word_Form &wf, Dictionary &dict ) const;

    virtual void LoadBin( lem::Stream &bin );
    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;

    virtual void PrefetchKeywords( Solarix::Search_Engine::Indexer &indexer );
    #endif

    virtual bool ContainedInString( const UFString &str ) const;
  };
  #endif

  class Word_Direct : public Word
  {
   public:
    Word_Direct(void);

    virtual bool DoesMatch(
                           File_Lexem &word,
                           Text &text,
                           Dictionary *dict,
                           const LD_Seeker *seeker,
                           Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           Fix_Rel &rel
                          ) const;

    virtual bool DoesMatch( const Solarix::Word_Form &wf, Dictionary &dict ) const;
  };


  class Word_Case_Sensitive : public Word
  {
   public:
    Word_Case_Sensitive(void);

    virtual bool DoesMatch(
                           File_Lexem &word,
                           Text &text,
                           Dictionary *dict,
                           const LD_Seeker *seeker,
                           Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           Fix_Rel &rel
                          ) const;

    virtual bool DoesMatch( const Solarix::Word_Form &wf, Dictionary &dict ) const;
  };



  class Word_Wordforms : public Word
  {
   public:
    Word_Wordforms(void);

    virtual bool DoesMatch(
                           File_Lexem &word,
                           Text &text,
                           Dictionary *dict,
                           const LD_Seeker *seeker,
                           Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           Fix_Rel &rel
                          ) const;
    virtual bool DoesMatch( const Solarix::Word_Form &wf, Dictionary &dict ) const;

    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif
  };



  class Word_Wordforms_Soundex : public Word_Wordforms
  {
   public:
    Word_Wordforms_Soundex(void);

    virtual void ApplyDictionary(
                                 Dictionary *dict,
                                 Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                 const Lexer_Options &lo
                                 #if !defined SOL_NO_AA
//                                 , Solarix::Text_Processor *tpu
                                 #endif
                                );

    virtual bool DoesMatch(
                           File_Lexem &word,
                           Text &text,
                           Dictionary *dict,
                           const LD_Seeker *seeker,
                           Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                           Fix_Rel &rel
                          ) const;

    virtual bool DoesMatch( const Solarix::Word_Form &wf, Dictionary &dict ) const;

    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif
  };


  #if !defined FAIND_NO_BOOST_REGEX
  // ****************************************************************************
  // Корневой узел для образца запроса в виде одной строки-регулярного выражения
  // ****************************************************************************
  class Query_Regex : public Query_Root
  {
   private:
    lem::UFString str;
    boost::wregex regex;
    lem::zbool case_sensitive;

   public:
    Query_Regex( const UFString &Name, const UFString &Pattern );

    virtual void Parse( const UFString &txt, const Search_Options &flags );

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;

    // Нам нужен текст в виде одной строки
    virtual bool NeedsSerializedText(void) const;

    // А разбивка на слова не требуется
    virtual bool NeedsWordedText(void) const;

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );

    virtual void PrepareToMatch(void);

    virtual bool Fix(
                     Text &text,
                     Dictionary *dict,
                     const LD_Seeker *seeker, 
                     #if !defined SOL_NO_AA
//                     Solarix::Text_Processor *tpu,
                     #endif 
                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                     Fix_Context& context,
                     Fix_States& fx_states 
                    );

    virtual bool ContainedInString( const UFString &str ) const;


    virtual Base_Node* Optimize(void);
  };
  #endif



  class Logic_Or : public Base_Node
  {
   private:
    void Clear(void);

    #if defined FAIND_INDEXER
    Assoc_Files* GetAssocFiles( Indexer &indexer, const Pattern &pattern ) const;
    #endif

   public:
    Logic_Or(void);

    virtual bool Fix(
                     Text &text,
                     Dictionary *dict,
                     const LD_Seeker *seeker, 
                     #if !defined SOL_NO_AA
//                     Solarix::Text_Processor *tpu,
                     #endif
                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                     Fix_Context& context,
                     Fix_States& fx_states 
                    );

    virtual bool ContainedInString( const UFString &str ) const;

    virtual Base_Node* Optimize(void);

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;
    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif
  };


  class Logic_And : public Base_Node
  {
   private:
    void Clear(void);

    #if defined FAIND_INDEXER
    Assoc_Files* GetAssocFiles( Indexer &indexer, const Pattern &pattern ) const;
    #endif

   public:
    Logic_And(void);

    virtual bool Fix(
                     Text &text,
                     Dictionary *dict,
                     const LD_Seeker *seeker, 
                     #if !defined SOL_NO_AA
//                     Solarix::Text_Processor *tpu,
                     #endif
                     Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                     Fix_Context& context,
                     Fix_States& fx_states 
                    );

    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif

    virtual bool ContainedInString( const UFString &str ) const;

    virtual Base_Node* Optimize(void);

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;
  };



  class Logic_Not : public Base_Node
  {
   private:
    void Clear(void);

   public:
    Logic_Not(void);

    virtual Base_Node* Optimize(void);

    virtual const wstring GetName(void) const;
    virtual const wstring GetAttrs(void) const;
    #if defined FAIND_INDEXER
    virtual bool Fix(
                     Search_Engine::Indexer *indexer,
                     Search_Engine::Document_Index *index
                    ) const;
    #endif

    virtual bool ContainedInString( const UFString &str ) const;
  };



  // Описание запроса
  struct Query
  {
   lem::Collect<lem::UFString> text; // первоначальный текст запроса (токены)
   int id;        // уникальный ключ запроса
   boost::posix_time::ptime q_date;  // когда создан запрос

   Query( const lem::Collect<lem::UFString> &Text, int Id );
   Query( const Query &Q );
   void operator=( const Query &Q );
   const lem::UFString GetText(void) const;
  };


  // ***********************************************
  // Pattern - that is sample of text to be found.
  // ***********************************************
  struct Pattern
  {
   Query_Root *q; // результат грамматического разбора паттерна
   int id;        // уникальный ключ запроса
   int id_query;  // к какому запросу относится
   lem::Collect<lem::UFString> file_masks; // для индексного поиска - дополнительные требования на имена файлов

   bool needs_index_application;
   bool needs_dict_application;

   Pattern( const Pattern &x );
   Pattern( Query_Root *Q );
   ~Pattern(void);

   void operator=( const Pattern &x );

   void ApplyDictionary(
                        Dictionary *dict,
                        Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                        const Lexer_Options &lo
                        #if !defined SOL_NO_AA
//                        , Solarix::Text_Processor *tpu
                        #endif
                       );

   #if defined FAIND_INDEXER
   void PrepareToIndexedFix(
                            const Lexer_Options &lexer_options,
                            Search_Engine::Indexer *indexer,
                            Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                            bool second_pass
                           );
   #endif


   void NewZoneLoaded(void) { needs_index_application=true; }

   // Вернет true, если заданы дополнительные требования на найденные файлы
   bool HasMasks(void) const { return !file_masks.empty(); }

   // Проверяем, что имя найденного в индексе документа подходит под список заданных масок
   bool MatchFilename( const wchar_t *filename ) const;
  };


  // *************************************
  // Состояние поиска для точки фиксации.
  // *************************************
  struct Fix_State
  {
   int i_word; // индекс слова, на котором остановился поиск.
   int i_sent; // индекс предложения, на котором остановился поиск
   int i_line; // индекс строки, на которой остановился поиск 
   UFString::const_iterator rx_begin; // с какого места надо искать регэксп

   Fix_State(void) { i_sent=i_line=i_word=UNKNOWN; rx_begin=NULL; }
  };


  // Контейнер для состояний фиксации. Хранит пары значений,
  // первый элемент пары - указатель на точку фиксации, второй - 
  // с какого места надо выполнять поиск для этой точки.
  class Fix_States : public std::map<const Base_Node*,Fix_State>
  {
   public:
    Fix_States(void) {}

    bool HasState( const Base_Node* qnode ) const { return find(qnode)!=end(); }
    void StoreState( const Base_Node* qnode, const Fix_State &state )
    {
     std::map<const Base_Node*,Fix_State>::iterator it = find(qnode);
     if( it==end() )
      insert( std::make_pair(qnode,state) );
     else
      it->second = state;
    }

    void RemoveState( const Base_Node* qnode )
    {
     this->erase(qnode);
    }
  };

  // **************************************************************
  // Базовый класс - занимается соотнесением контента и запросов. 
  // Результатом его работы является множество контекстов фиксации,
  // которые детально описывают место, где паттерн запроса подошел
  // к контексту.
  // **************************************************************
  class Query_Matcher : lem::NonCopyable
  {
   protected:
    bool success; // Флаг успешности проверки (если хоть одна фиксация
                  // удалась).

    Base_File_Reader *reader; // Source of text data
    Text text;           // Загруженные данные

    Query_Root *query;   // Запрос

    Search_Engine::Fuzzy_Comparator *fuzzy_eq;

    MCollect<Fix_Context*> fix_contexts; // Описатели места, где
                                         // паттерн подошел

    boost::shared_ptr<Sequence> seq;
    
    virtual void LoadText( const Search_Options &searching );
    void LoadString(void);
    void LoadLexems( const Search_Options &searching );

    inline bool IsDelim( const UCString &word ) const
    {
     return word.length()==1 &&
            (word.front()==L'.' || word.front()==L'?' || word.front()==L'!');
    }

   public:
    Query_Matcher(
                  Base_File_Reader *Reader,
                  Search_Engine::Fuzzy_Comparator *Fuzzy_eq,
                  boost::shared_ptr<Sequence> Seq=boost::shared_ptr<Sequence>()
                 );

    virtual ~Query_Matcher(void) {}

    virtual void Match(
                       Pattern *Query,
                       Dictionary *dict,
                       const LD_Seeker *seeker, 
                       #if !defined SOL_NO_AA
//                       Text_Processor *tpu,
                       #endif  
                       const Search_Options &searching,
                       const Context_Options &ctx_options,
                       const Indexer_Operation &idx_operation,
                       Action_Options &actions
                      );

    inline bool GetSuccess(void) const { return success; }

    inline const MCollect<Fix_Context*>& GetFixContexts(void) const
    { return fix_contexts; }
  };



   class SE_Sequence : public Sequence
   {  
    public:
     SE_Sequence() {}

     virtual int operator()(void);
   };

  // **************************************************************
  // Базовый класс - занимается соотнесением контента, подаваемого
  // полексемно, и образцов запросов. Результатом его работы
  // является множество контекстов фиксации, которые детально
  // описывают место, где паттерн запроса подошел к контексту.
  // **************************************************************
  class Query_Queue : public Query_Matcher
  {
   public:
    Query_Queue( 
                Base_File_Reader *Reader,
                Search_Engine::Fuzzy_Comparator *Fuzzy_eq,
                boost::shared_ptr<Sequence> Seq
               );

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
  };



   class String_Query_Matcher : public Solarix::Search_Engine::Query_Matcher
   {
    private:
     const wchar_t *beg, *end;

    public:
     String_Query_Matcher(
                          const wchar_t *Beg,
                          const wchar_t *End,
                          Solarix::Search_Engine::Fuzzy_Comparator *fuzzy
                         );

     virtual ~String_Query_Matcher(void);
   };

   struct Action_Options;
   class Fix_Context;

   // Basic class representing a pattern - sample of text to match.
   class RegexEx : lem::NonCopyable
   {
    public:
     Search_Options options; // match options    
     Context_Options ctx_flags; // context building options
     Lexer_Options lexer_options;
     MCollect<Fix_Context*> contexts; // results of previous match
     OFormatter *echo; // lem::Stream for printing debug messages

    private:
     UFString org_pattern;   // original pattern string
     std::auto_ptr<Pattern> pattern;       // compiled pattern
     Solarix::Dictionary *dict;
     const Solarix::LD_Seeker *seeker;
     Solarix::Search_Engine::Fuzzy_Comparator *fuzzy;

     std::auto_ptr<Solarix::Search_Engine::Indexer_Operation> idx_operation;
     std::auto_ptr<Solarix::Search_Engine::Action_Options> actions;

     virtual void Build_Query(void);

    public:
     RegexEx(
             const wchar_t *Pattern,
             Solarix::Dictionary *Dict,
             const Solarix::LD_Seeker *Seeker,
             Solarix::Search_Engine::Fuzzy_Comparator *Fuzzy
            );

     virtual ~RegexEx(void);

     virtual bool Search(
                         const wchar_t *Beg,
                         const wchar_t *End
                        );
   };


 } // namespace Search_Engine
 } // namespace Solarix

#endif
