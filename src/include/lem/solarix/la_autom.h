// -----------------------------------------------------------------------------
// File LA_AUTOM.H
//
// (c) Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// Лексический Автомат и поддерживающие классы.
//
// 02.10.2005 - проектор теперь работает с мультилексемами типа Lexem
//              (а не Multylexem) в соответствии с общей стратегией хранения
//              мультилексем словаря как объектов класса Lexem.
//
// 16.05.2006 - изменено внутреннее представление правил для продукции
//              динамических форм (префиксы, аффиксы)
//
// 20.09.2006 - добавлен метод Translate_To_Infinitive - приведение произвольной
//              словарной статьи к форме инфинитива 
//
// 09.06.2008 - добавлен метод для определения языка предложения
// 04.09.2008 - добавлен второй метод для определения языка предложения после
//              выполненных проекций
// 05.01.2009 - добавлена работа (загрузка и использование) фильтров вариаторов
// -----------------------------------------------------------------------------
//
// CD->15.03.1996
// LC->05.09.2014
// --------------

#ifndef SOL_LEXAUTO__H
#define SOL_LEXAUTO__H
#pragma once

 #include <lem/config.h>

 #include <map>

 #include <lem/cyclyc_stack.h>
 #include <lem/queue.h>
 #include <lem/ptr_container.h>
 #include <lem/solarix/automaton.h>
 #include <lem/solarix/ml_projections.h>
 #include <lem/solarix/tree_link.h>
 #include <lem/solarix/SynPattern.h>
 #include <lem/solarix/LA_ProjectInfo.h>
 #include <lem/solarix/pm_autom.h>
 #include <lem/solarix/phrasema.h>
 #include <lem/solarix/EndingStat.h>

 namespace lem
 {
  class UFString;
 }

 namespace Solarix
 {

 /***********************************************************************
  Класс для хранения информации об успешном проецировании мультилексемы
  на Лексикон. Является элементом кэша для Лексического Автомата.
 ***********************************************************************/
 class LexicalAutomat;
 class SynGram;
 class Sentence;
 class LA_RecognitionTrace;
 class CasingCoder;
 class LA_WordProjectionBuffer;
 class Dictionary;
 class LD_Seeker;
 class SG_TagFilter; 
 class WordEntrySet;
 class Phrasema;
 class LA_Recognizer;
 class LA_Preprocessor;
 class LA_PreprocessorTrace;
 class LA_PhoneticMatcher;
 class LA_Pack;
 class MLProjList;
 class LA_SynPatternTrees;
 class LexiconStorage;
 class LA_RecognitionTrace;
 class LA_WordProjBuffer;
 class KnowledgeBase;
 struct WordSplitResults;
 struct TextRecognitionParameters;
 class TreeScorers;
 class MorphologyModels;

 class LexicalAutomat : public PM_Automat
 {
  private:
   GraphGram *GG;
   SynGram  *SG;
   LexiconStorage *storage;
   bool do_delete_storage;

   MorphologyModels * models;

   lem::zbool lazy_load;

   lem::UCString ROOT_NODE_NAME;

   #if defined SOL_COMPILER
   lem::zint compilation_error_count; // счетчик ошибок компиляции - для отложенного прерывания
                                      // компиляции словаря не сразу при возникновении первой же
                                      // ошибки, а по завершении трансляции.
   #endif

   #if defined SOL_COMPILER
   lem::MCollect<int> morph_filter_lang;
   lem::PtrCollect< lem::MCollect<int> > morph_filter_compilation;
   #endif


   inline GraphGram& GetGraphGram(void) const { return *GG; }
   inline SynGram&   GetSynGram(void) const   { return *SG; }

   // Список (кэш) осуществленных проекций мультилексем.
   LA_WordProjBuffer *word_proj;

   // Вносить ли изменения в содержимое кэша? Если нет, то кэш будет работать,
   // но новые словоформы не будут в него заноситься.
   bool do_update_cache;

   // На сколько букв могут отличаться две мультилексемы для того, чтобы
   // алгоритм нечеткого сравнения признал их близкими. Это поле сначала
   // инициализируется как -1, и будет переустановлено как целое положительное
   // число на основе ПАРАМЕТРА из списка нашего Автомата. Второй раз поиск в
   // списке параметров Автомата можно будет не проводить.
   int NMISSMAX;

   // Крейсерская вместимость кэша осуществленных лексем.
   int NWORDPROJMAX;

   // Какова минимальная допустимая достоверность проекций. Инициализируется на
   // основе ПАРАМЕТРА Автомата.
   float MIN_PROJ_SCORE;

   #if defined LEM_THREADS
   lem::Process::RWU_Lock cs_word_assoc;
   #endif
   std::set<int> unassociated_words;


   #if defined SOL_CAA
    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_casing_coder;
    #endif
    CasingCoder* casing_coder;
   #endif


   #if defined LEM_THREADS
   lem::Process::RWU_Lock cs_lang_optional_diacritics;
   #endif
   std::map<int/*id_langyage*/,int/*0-no optional diakritics, 1 - optional diakritics*/> id_language_with_optional_diacritics;
   std::map<int/*id_language*/,lem::UFString/*characters with diacritics*/> optional_diacritics_for_languages;
   std::map<int/*id_language*/,int/*aux_form_type*/> optional_diacritics_aux_type;
   bool IsLanguageWithOptionalDiaktiriks( int id_language );

   KnowledgeBase * knowledges;
   TreeScorers * tree_scorers;

   #if defined LEM_THREADS
   lem::Process::RWU_Lock cs_unknown_entry_key;
   #endif
   volatile int unknown_entry_key;

   #if defined LEM_THREADS
   lem::Process::RWU_Lock cs_wordform_frequency;
   #endif
   typedef std::map< std::pair<int/*id_entry*/,int/*iform*/>, int/*frequency*/ > WORDFORM_FREQUENCY;
   WORDFORM_FREQUENCY wordform_frequency;

   #if defined SOL_CAA
    struct EndingKey
    {
     lem::UCString ending;
     int id_language;
     EndingKey() : id_language(UNKNOWN) {}
     EndingKey( const lem::UCString _ending, int _id_language ) : ending(_ending), id_language(_id_language) {}

     inline bool operator==( const EndingKey &x ) const { return ending==x.ending && id_language==x.id_language; }

     inline bool operator>( const EndingKey &x ) const
     {
      if( ending>x.ending ) return true;
      if( ending<x.ending ) return false;
      return id_language>x.id_language; 
     }

     inline bool operator<( const EndingKey &x ) const
     {
      if( ending<x.ending ) return true;
      if( ending>x.ending ) return false;
      return id_language<x.id_language;
     }
    };

    struct EndingInfo
    {
     bool found;
     int nform, sumfreq;
     EndingInfo() : found(false), nform(0), sumfreq(0) {}
    };

    #if defined LEM_THREADS
    lem::Process::RWU_Lock cs_endings;
    #endif
    lem::MCollect<int> ending_stat_lang; // id_language
    lem::MCollect<EndingStat> ending_stat_data;
    std::map< EndingKey, EndingInfo > ending_info;
   #endif


   #if defined LEM_THREADS
   lem::Process::CriticalSection cs_default_alphabets;
   #endif
   lem::MCollect<int> DefaultAlphabets;
   lem::zbool DefaultAlphabetsOk;
   const lem::MCollect<int> GetDefaultAlphabets(void);

   #if defined SOL_CAA
   void Project(
                MLProjList &proj,
                int method,
                bool use_original,
                int id_lang,
                LA_RecognitionTrace *trace
               );

   void FindParameters(void);
   #endif


   #if defined LEM_THREADS
   lem::Process::CriticalSection cs;
   #endif

   #if defined LEM_THREADS
   lem::Process::RWU_Lock cs_minrel;
   #endif

   volatile bool minrel_loaded;

   float GetMinProjectionScore(void);

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   lem::PtrCollect<SynPattern> patterns; // паттерны (грамматика НС) для фильтрации

   //lem::PtrCollect<SynPattern> sparse_patterns /*, sparse_patterns_with_keys*/; // паттерны для неполного анализа
   lem::PtrCollect<SynPattern> incomplete_patterns;

   lem::PtrCollect<SynPattern> named_patterns_list;
   SynPatterns pattern_declarations; // объявления параметров для групп именованных фильтров
   #endif

   WordEntrySet *wordentry_set; // именованные списки словарных статей
   LA_Preprocessor *preprocessor; // правила препроцессинга и постпроцессинга
   LA_Recognizer *recognizer; // правила распознавания грамматических атрибутов по префиксам и аффиксам
   LA_PhoneticMatcher *phonetic_matcher; // Правила фонетического сравнения
   LA_SynPatternTrees *pattern_trees;

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void Compile_Finder( const lem::Path &outdir );
   #endif


   bool Project_1(
                  const RC_Lexem &A,
                  const lem::UCString &original_word,
                  float scoreA,
                  MCollect<Word_Coord> &found_list,
                  MCollect<ProjScore> &val_list,
                  lem::PtrCollect<LA_ProjectInfo> &inf_list,
                  bool refresh_cache,
                  bool allow_fuzzy,
                  bool use_recognition_rules,
                  int id_lang,
                  LA_RecognitionTrace *trace
                 );

   #if defined SOL_CAA
   void Project_2(
                  const RC_Lexem &A,
                  int nmissmax,
                  MCollect<Word_Coord> &found_list,
                  MCollect<ProjScore> &val_list,
                  lem::PtrCollect<LA_ProjectInfo> &inf_list,
                  int id_lang,
                  LA_RecognitionTrace *trace
                 );

   bool Project_3(
                  const RC_Lexem &A,
                  const lem::UCString & original_word,
                  float scoreA,
                  MCollect<Word_Coord> &found_list,
                  MCollect<ProjScore> &val_list,
                  lem::PtrCollect<LA_ProjectInfo> &inf_list,
                  int id_lang,
                  LA_RecognitionTrace *trace
                 );
   const EndingStat & GetEndingStat( int id_lang );
   bool GetEnding( int id_lang, const lem::UCString &ending, int &nform, int &sumfreq );

   #endif

   #if defined SOL_CAA
   // Для внутреннего использования в SeekThesaurus
   int SeekThesaurus0(
                      int ientry_key,
                      bool Synonyms,
                      bool Grammar_Links,
                      bool Translations,
                      bool Semantics,  
                      int nJumps,
                      lem::MCollect<int> &result_keys,
                      const SG_TagFilter *tags=NULL
                     );
   #endif

   #if defined SOL_CAA
   bool Translate_To_X( int link, int needed_class, int ientry_key, MCollect<int> &ie_linked, int depth ) const;
   #endif


   std::map<int,int> unknown_entries;

   #if defined SOL_CAA
   lem::MCollect< Tree_Link > allowed_links_synonyms;
   lem::MCollect< Tree_Link > allowed_links_grammar;
   lem::MCollect< Tree_Link > allowed_links_translations;
   lem::MCollect< Tree_Link > allowed_links_semantics;
   void InitLinks(void); 
   #endif

   #if defined SOL_CAA
   int CompareThem(
                   const Lexem &A,
                   const Lexem &B,
                   int id_language,
                   int NMISSMAX,
                   Real1 *Equality
                  ) const;
   #endif

   #if defined SOL_CAA
   void ProducePhonInv( MLProjList &proj, int id_language, LA_RecognitionTrace *trace );
   LA_Pack* AlephAuto( int id_language, const Lexem &lex, int n_max_tran, LA_RecognitionTrace *trace );
   void ProducePhonInv(
                       const lem::UCString &word,
                       int id_language,
                       lem::MCollect<lem::UCString> &res,
                       lem::MCollect<lem::Real1> &rels,
                       LA_RecognitionTrace *trace
                      );
   #endif

   #if defined SOL_CAA
   bool AddResults(
                   MLProjList &proj,
                   const MCollect<Word_Coord> &coords,
                   const MCollect<ProjScore> &vals,
                   const lem::PtrCollect<LA_ProjectInfo> &inf_list
                  );
   #endif

   void ToLexemX( const wchar_t *word, bool substitute_entries, Lexem &res, int LanguageID=UNKNOWN );

  protected:
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual bool ProcessLexem(
                             const BethToken &t,
                             Macro_Parser &txtfile,
                             const Binarization_Options &options
                            );

   virtual bool ProcessLexem2(
                              const BethToken &t,
                              Macro_Parser &txtfile,
                              const Binarization_Options &options
                             );
   #endif

  public:

   // Способ генерации динамических форм
   enum DynformsMode { Wordforms=0, // запрет динамических форм
                       Dynforms_Last_Chance, // динамические формы генерируются, если не найдена прямая проекция
                       Dynforms_Always // динамические формы генерируются до проекции 
                     };

  public:
   LexicalAutomat(void);
   virtual ~LexicalAutomat(void);

   virtual void SetDictPtr( Dictionary *d );
   void SetStorage( LexiconStorage *stg, bool _do_delete );
   LexiconStorage& GetStorage(void) { return *storage; }

   bool IsCorrectWord( const UCString& word ) const;

   void TranslateLexem(
                       Lexem &mlex,
                       bool substitute_entries=true,
                       int LanguageID=UNKNOWN
                      );

   void TranslateLexem(
                       lem::UFString &str,
                       bool substitute_entries,
                       int LanguageID=UNKNOWN
                      );

   bool ProjectJob( MLProjList &proj, int id_lang, bool allow_unknown_entries, LA_RecognitionTrace *trace );

   #if defined SOL_CAA
   inline void DoUpdateCache( bool fUpdate ) { do_update_cache=fUpdate; }
   #endif

   #if defined SOL_REPORT
   virtual void Report( OFormatter &dst_stream );
   #endif

   bool Produce_Dynforms(
                         const UCString &lex, // оригинальное слово
                         lem::MCollect<UCString> &list,
                         lem::MCollect<lem::Real1> &dynform_rels,
                         int id_language,
                         LA_RecognitionTrace *trace
                        );

   bool Generate_Forms_From_Normal(
                                   const UCString &word,
                                   lem::MCollect<UCString> &list
                                  );


   void ProjectWord(
                    const UCString &A,
                    MCollect<Word_Coord> &found_list,
                    MCollect<ProjScore> &val_list,
                    lem::PtrCollect<LA_ProjectInfo> &prj_extra_inf,
                    DynformsMode allow_dynforms,  
                    int nmissmax,
                    int id_lang,
                    LA_RecognitionTrace *trace
                   );

   void ProjectWord(
                    const RC_Lexem &A,
                    MCollect<Word_Coord> &found_list,
                    MCollect<ProjScore> &val_list,
                    lem::PtrCollect<LA_ProjectInfo> &prj_extra_inf,
                    DynformsMode allow_dynforms,
                    int nmissmax,
                    int id_lang,
                    LA_RecognitionTrace *trace
                   );

   void ProjectWord(
                    const lem::UCString &word,
                    MCollect<Word_Coord> &found_list,
                    int id_lang
                   );

   #if defined SOL_CAA
   Solarix::Word_Form* ProjectWord(
                                   const lem::UCString &word,
                                   int WordIndex,
                                   int WordParts,
                                   const TokenizationTags * tags,
                                   const TextRecognitionParameters & params,
                                   LA_RecognitionTrace *trace
                                  );
   #endif


   #if defined SOL_CAA
   int Project_Dynforms(
                        const UCString &lex,
                        int id_language,
                        const LD_Seeker &seeker
                       ) const;

   #endif


   #if defined SOL_CAA
   bool FindMisspeltWord(
                         const lem::UCString &word,
                         MCollect<lem::UCString> &corrected_word,
                         int id_lang
                        );
   #endif


   #if defined SOL_CAA
   void ProjectUnknown(
                       const RC_Lexem &A,
                       const lem::UCString & original_word,
                       MCollect<Word_Coord> &found_list,
                       MCollect<ProjScore> &val_list,
                       PtrCollect<LA_ProjectInfo> &inf_list,
                       int id_language,
                       bool refresh_cache
                      );
   #endif

   virtual const UCString GetName(void) const;

   #if defined SOL_REPORT
   virtual void PrintMap( OFormatter &dst_stream );
   #endif

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual void Prepare( const lem::Path &outdir, const Binarization_Options &opts );
   virtual void Optimize(void);
   #endif

   #if defined SOL_CAA
   bool Translate_To_Nouns( int ientry_key, MCollect<int> &keys_linked, int depth=1 ) const;
   bool Translate_To_Infinitives( int ientry_key, MCollect<int> &keys_linked, int depth=1 ) const;
   bool Translate_To_Verbs( int ientry_key, MCollect<int> &keys_linked, int depth=1 ) const;
   bool Translate_To_Gerund( int ientry_key, MCollect<int> &keys_linked, int depth=1 ) const;
   bool Translate_To_Gerund2( int ientry_key, MCollect<int> &keys_linked, int depth=1 ) const;

   void SeekThesaurus( int ientry_key, bool Synonyms, bool Grammar_Links,
                       bool Translations, bool Semantics, int nJumps,
                       lem::MCollect<int> &result_entry_keys, const SG_TagFilter *tags=NULL );

   void Synonymize( int iEntryKey, lem::MCollect<int> &result_entry_keys, const SG_TagFilter *tags=NULL );
   void Translate( int iEntryKey, lem::MCollect<int> &result_entry_keys, const SG_TagFilter *tags=NULL );
   #endif

   #if defined SOL_CAA
   void GetBaseForm( lem::UCString &word, bool allow_dynforms ) const;

   /// Определение языка для фразы по алфавиту и лексикону
   int GuessLanguage( const lem::UFString &str ) const;
   int GuessLanguage( const Sentence & phrase );
   int GuessLanguage( const Variator &phrase ) const;
   void GetAllProjections(
                          const lem::UCString &word,
                          bool allow_dynforms,
                          lem::MCollect<int> &ies
                         );

   int Find_Quantor_Entry( int iclass );
   #endif

   #if defined SOL_CAA
   Solarix::Word_Form* ProjectWord2Wordform( const lem::UCString &word, int LanguageID );
   #endif

   #if defined SOL_CAA
   CasingCoder& GetCasingCoder(void);
   #endif

   LA_SynPatternTrees& GetSynPatternTrees(void) { return *pattern_trees; }
   WordEntrySet & GetWordEntrySet(void) { return *wordentry_set; }
   LA_PhoneticMatcher & GetPhoneticMatcher(void) { return *phonetic_matcher; }
   KnowledgeBase & GetKnowledgeBase() { return * knowledges; }

   virtual void BeforeSyntaxRecompilation(void);

   #if defined SOL_EXPORT_SQL
   virtual void SaveRules_SQL( OFormatter &out, OFormatter &alters, const SQL_Production &sql_version ); 
   #endif

   void SetLazyLoad(void);

   int GetUnknownEntryKey(void);
   int GetWordformFrequency( int id_entry, int iform );

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   const SynPatterns& GetPatternDeclarations(void) const { return pattern_declarations; }
   #endif

   const lem::UCString* GetRootNodeName() const;

   #if defined SOL_CAA
   void ListAssociationsForEntry( int id_entry, lem::MCollect<int> & ids );
   #endif

   MorphologyModels& GetModel() const { return *models; }

   TreeScorers& GetTreeScorers() { return *tree_scorers; }
 };

 } // namespace 'Solarix'

#endif
