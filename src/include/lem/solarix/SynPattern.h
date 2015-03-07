#if !defined LA_SYNPATTERN__H
#define LA_SYNPATTERN__H
#pragma once

 #include <lem/noncopyable.h>
 #include <lem/ptr_container.h>
 #include <boost/regex.hpp>
 #include <lem/macro_parser.h>
 #include <lem/solarix/translation.h>
 #include <lem/solarix/coord_pair.h>
 #include <lem/solarix/BackRefCorrel.h>
 #include <lem/solarix/ExportNodes.h>
 #include <lem/solarix/KB_CheckingResult.h>
 #include <lem/solarix/WordSetChecker.h>
 #include <lem/solarix/NGramScore.h>
 #include <lem/solarix/ViolationHandler.h>

 namespace Solarix
 {
  class Dictionary;
  class SynGram;
  class Word_Form;
  class Variator;
  class WordEntrySet;
  class LA_SynPatternTrees;
  class SynPatternCompilation;
  class SynPatternTreeNode;
  class LexicalAutomat;
  class SynPatterns;


  struct SynPatternResult;
  struct SynPatternResultBackTrace
  {
   const SynPatternResultBackTrace * parent;
   const SynPatternResult * result;

   SynPatternResultBackTrace() : parent(NULL), result(NULL) {}
   SynPatternResultBackTrace( const SynPatternResultBackTrace * _parent, const SynPatternResult * _result ) : parent(_parent), result(_result) {}
  };


  struct PatternLinkEdge;
  class LinkEdgeContainer : lem::NonCopyable
  {
   protected:
    LinkEdgeContainer() {}
    
   public:
    virtual ~LinkEdgeContainer() {}
    virtual int size() const=0;
    virtual const PatternLinkEdge& operator[]( int index ) const=0;
  };

  // **********************************************************************************
  // маркировка входных слов для последующей ссылки на них при проверках согласования
  // **********************************************************************************
  struct PatternMarkName
  {
   int pattern_seq; // привязка к паттерну, в рамках которого действует
   lem::UCString mark_name; // имя переменной
   bool syntactical; // маркировка нужна ТОЛЬКО для синтаксического анализа, поэтому при морфоанализе ее можно игнорировать

   PatternMarkName(void) : pattern_seq(UNKNOWN), syntactical(false) {}

   const lem::UCString& GetName(void) const { return mark_name; }
   bool empty(void) const { return mark_name.empty(); }
   void clear(void) { mark_name.clear(); pattern_seq=UNKNOWN; }
   void SyntacticalMarker(void) { syntactical=true; }
   bool IsSyntacticalMarker(void) const { return syntactical; }
  };


  
  class KnowledgeBase;
  class TreeMatchingExperience;
  class BackTrace;
  struct SynPatternResult;

  struct KB_CheckerReturn
  {
   bool success;
   int false_score; // если были условно-успешные проверки со штрафом

   KB_CheckerReturn() : success(false), false_score(0) {}
  };


  class KB_Checker
  {
   private:
    int id_facts;
    lem::MCollect<lem::UCString> backref_name;
    lem::MCollect<lem::UCString> node_name;

   public:
    KB_Checker(void) : id_facts(UNKNOWN) {}

    KB_Checker( const KB_Checker & x );
    void operator=( const KB_Checker & x );

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt( 
                 Dictionary &dict,
                 lem::Iridium::Macro_Parser & txtfile,
                 SynPatternCompilation & compilation_context
                );
    #endif

    bool operator==( const KB_Checker & x ) const;
    bool operator!=( const KB_Checker & x ) const;

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    void LoadBin( lem::Stream& binfile );
    #endif

    #if defined SOL_CAA
    KB_CheckerReturn Check(
                           const lem::MCollect<int> & PatternSequenceNumber,
                           const BackTrace * parent_trace,
                           const SynPatternResult * cur_result,
                           const Solarix::Word_Form * this_wordform,
                           KnowledgeBase & kbase,
                           TreeMatchingExperience &experience
                          ) const;
    #endif
  };

  class SynPatternPoint;

  class PatternExportFuncContext
  {
   public:
    PatternExportFuncContext() {}

    virtual bool ContainsCoordPair( const Solarix::GramCoordPair & pair ) const=0;

    virtual void GetCoordStates( int coord_id, lem::MCollect<int> & state_ids ) const=0;
    virtual void GetCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const=0;

    virtual void SubtractMarkedNodeCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const=0;
  };

  class PatternExportFuncContext_Wordform : public PatternExportFuncContext
  {
   private:
    const Word_Form * wf;

   public:
    PatternExportFuncContext_Wordform( const Word_Form * _wf ) : wf(_wf) {}
    virtual bool ContainsCoordPair( const Solarix::GramCoordPair & pair ) const;
    virtual void GetCoordStates( int coord_id, lem::MCollect<int> & state_ids ) const {}
    virtual void GetCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const {}
    virtual void SubtractMarkedNodeCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const {}
  };

  class PatternExportFuncContext_Null : public PatternExportFuncContext
  {
   public:
    PatternExportFuncContext_Null() {}
    virtual bool ContainsCoordPair( const Solarix::GramCoordPair & pair ) const { return false; }
    virtual void GetCoordStates( int coord_id, lem::MCollect<int> & state_ids ) const {}
    virtual void GetCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const {}
    virtual void SubtractMarkedNodeCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const {}
  };

  class PatternExportFuncContext_Tree : public PatternExportFuncContext
  {
   private:
    const lem::MCollect< std::pair<int,int> > & pairs;
    const Solarix::BackTrace * parent_trace;
    const lem::MCollect<int> & PatternSequenceNumber;

   public:
    PatternExportFuncContext_Tree( const lem::MCollect< std::pair<int,int> > & _pairs, const Solarix::BackTrace * _parent_trace, const lem::MCollect<int> & _PatternSequenceNumber ) : pairs(_pairs), parent_trace(_parent_trace), PatternSequenceNumber(_PatternSequenceNumber) {}
    virtual bool ContainsCoordPair( const Solarix::GramCoordPair & pair ) const;
    virtual void GetCoordStates( int coord_id, lem::MCollect<int> & state_ids ) const;
    virtual void GetCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const;
    virtual void SubtractMarkedNodeCoordStates( const lem::UCString & mark_name, int coord_id, lem::MCollect<int> & state_ids ) const;
  };

  // абстрактная функция экспорта координат
  class ExportCoordFunction
  {
   protected:
    typedef enum { ECF_Unknown=-1, ECF_Except, ECF_IfContains, ECF_IfExported, ECF_Add, ECF_Remove } ExportCoordFunctionType; 
    ExportCoordFunctionType type;

    #if defined SOL_COMPILER && defined SOL_LOADTXT
    virtual void LoadTxt(
                         Dictionary &dict,
                         lem::Iridium::Macro_Parser & txtfile,
                         const SynPatterns & pattern_declarations,
                         SynPatternCompilation & compilation_context,
                         const SynPatternPoint & point
                        )=0;
    #endif

    virtual void LoadBin( lem::Stream & bin )=0;

   public:
    ExportCoordFunction( ExportCoordFunction::ExportCoordFunctionType _type ) : type(_type) {}
    virtual ~ExportCoordFunction() {}

    virtual ExportCoordFunction* Clone()=0;

    #if defined SOL_COMPILER && defined SOL_LOADTXT
    static ExportCoordFunction* load_txt(
                                         Dictionary &dict,
                                         lem::Iridium::Macro_Parser & txtfile,
                                         const SynPatterns & pattern_declarations,
                                         SynPatternCompilation & compilation_context,
                                         const SynPatternPoint & point
                                        );
    #endif

    static ExportCoordFunction* load_bin( lem::Stream & bin );

    virtual void SaveBin( lem::Stream & bin ) const;
    virtual bool Equals( const ExportCoordFunction & y ) const;

    #if defined SOL_CAA
    virtual void Run( SynPatternResult & dest, const PatternExportFuncContext & context ) const=0;
    #endif

    virtual int GetExportCoord() const=0;
    virtual bool IsAdder() const { return false; }
  };


  // добавляем в экспорт заданную координатную пару, если такой пары еще нет.
  class ExportCoordFunction_Add : public ExportCoordFunction
  {
   private:
    Solarix::GramCoordPair pair;

   protected:
    #if defined SOL_COMPILER && defined SOL_LOADTXT
    virtual void LoadTxt(
                         Dictionary &dict,
                         lem::Iridium::Macro_Parser & txtfile,
                         const SynPatterns & pattern_declarations,
                         SynPatternCompilation & compilation_context,
                         const SynPatternPoint & point
                        );
    #endif

   public:
    ExportCoordFunction_Add();

    virtual ExportCoordFunction* Clone();

    virtual bool Equals( const ExportCoordFunction & y ) const;
    virtual void SaveBin( lem::Stream & bin ) const;
    virtual void LoadBin( lem::Stream & bin );

    #if defined SOL_CAA
    virtual void Run( SynPatternResult & dest, const PatternExportFuncContext & context ) const;
    #endif

    virtual int GetExportCoord() const { return pair.GetCoord().GetIndex(); }
    virtual bool IsAdder() const { return true; }
  };


  // Удаляем из списка экспорта указанную координатную пару, если она там есть
  class ExportCoordFunction_Remove : public ExportCoordFunction
  {
   private:
    Solarix::GramCoordPair pair;

   protected:
    #if defined SOL_COMPILER && defined SOL_LOADTXT
    virtual void LoadTxt(
                         Dictionary &dict,
                         lem::Iridium::Macro_Parser & txtfile,
                         const SynPatterns & pattern_declarations,
                         SynPatternCompilation & compilation_context,
                         const SynPatternPoint & point
                        );
    #endif

   public:
    ExportCoordFunction_Remove();

    virtual ExportCoordFunction* Clone();

    virtual bool Equals( const ExportCoordFunction & y ) const;
    virtual void SaveBin( lem::Stream & bin ) const;
    virtual void LoadBin( lem::Stream & bin );

    #if defined SOL_CAA
    virtual void Run( SynPatternResult & dest, const PatternExportFuncContext & context ) const;
    #endif

    virtual int GetExportCoord() const { return pair.GetCoord().GetIndex(); }
    virtual bool IsAdder() const { return true; }
  };


  // экспортирует заданную координатную пару, если она есть в словоформе
  class ExportCoordFunction_IfContains : public ExportCoordFunction
  {
   private:
    Solarix::GramCoordPair pair;

   protected:
    #if defined SOL_COMPILER && defined SOL_LOADTXT
    virtual void LoadTxt(
                         Dictionary &dict,
                         lem::Iridium::Macro_Parser & txtfile,
                         const SynPatterns & pattern_declarations,
                         SynPatternCompilation & compilation_context,
                         const SynPatternPoint & point
                        );
    #endif

   public:
    ExportCoordFunction_IfContains();

    virtual ExportCoordFunction* Clone();

    virtual bool Equals( const ExportCoordFunction & y ) const;
    virtual void SaveBin( lem::Stream & bin ) const;
    virtual void LoadBin( lem::Stream & bin );

    #if defined SOL_CAA
    virtual void Run( SynPatternResult & dest, const PatternExportFuncContext & context ) const;
    #endif

    virtual int GetExportCoord() const { return pair.GetCoord().GetIndex(); }
  };

  // добавляет в экспорт заданную пару, если в экспорте есть состояние заданной координаты.
  // пример использования: экспортировать признак переходности, если после экспорта с фильтрацией валентностей
  // в экспорт попала хоть одна валентность.
  class ExportCoordFunction_IfExported : public ExportCoordFunction
  {
   private:
    Solarix::GramCoordPair export_pair; // экспортируем эту пару
    int trigger_coord; // если есть состояние этой координаты

   protected:
    #if defined SOL_COMPILER && defined SOL_LOADTXT
    virtual void LoadTxt(
                         Dictionary &dict,
                         lem::Iridium::Macro_Parser & txtfile,
                         const SynPatterns & pattern_declarations,
                         SynPatternCompilation & compilation_context,
                         const SynPatternPoint & point
                        );
    #endif

   public:
    ExportCoordFunction_IfExported();

    virtual ExportCoordFunction* Clone();

    virtual bool Equals( const ExportCoordFunction & y ) const;
    virtual void SaveBin( lem::Stream & bin ) const;
    virtual void LoadBin( lem::Stream & bin );

    #if defined SOL_CAA
    virtual void Run( SynPatternResult & dest, const PatternExportFuncContext & context ) const;
    #endif

    virtual int GetExportCoord() const { return export_pair.GetCoord().GetIndex(); }
  };

  // экспортирует все состояния заданной координаты из словоформы, кроме тех, которые
  // имеются у указанных маркировок. Это используется для вычитания использованной валентности, например
  // для глаголов.
  class ExportCoordFunction_Except : public ExportCoordFunction
  {
   private:
    lem::UCString export_source;
    int export_coord_id;
    lem::MCollect<lem::UCString> marker_name;
    lem::MCollect<int> subtract_coord_id;
   
   protected:
    #if defined SOL_COMPILER && defined SOL_LOADTXT
    virtual void LoadTxt(
                         Dictionary &dict,
                         lem::Iridium::Macro_Parser & txtfile,
                         const SynPatterns & pattern_declarations,
                         SynPatternCompilation & compilation_context,
                         const SynPatternPoint & point
                        );
    #endif

   public:
    ExportCoordFunction_Except();

    virtual ExportCoordFunction* Clone();

    virtual bool Equals( const ExportCoordFunction & y ) const;
    virtual void SaveBin( lem::Stream & bin ) const;
    virtual void LoadBin( lem::Stream & bin );

    #if defined SOL_CAA
    virtual void Run( SynPatternResult & dest, const PatternExportFuncContext & context ) const;
    #endif

    virtual int GetExportCoord() const { return export_coord_id; }
  };



  class PatternExportSection
  {
   private:
    friend class SynPatternPoint;
    lem::MCollect<int> export_coords; // экспортируемые опорной точкой координаты
    CP_Array export_pairs; // если нужно экспортировать точно заданную кординатную пару
    lem::MCollect< ExportNode > export_nodes; // для экспорта узлов
    lem::MCollect<ExportCoordFunction*> export_functions; // более сложные функции экспорта координат

   private:
    void operator=( const PatternExportSection & );

   public:
    PatternExportSection();
    PatternExportSection( const PatternExportSection & src );

    ~PatternExportSection();

    void SaveBin( lem::Stream & bin ) const;
    void LoadBin( lem::Stream & bin );

    bool operator==( const PatternExportSection & y ) const;
    bool operator!=( const PatternExportSection & y ) const;

    // вернет true, есть есть экспорт узла под именем ROOT_NODE
    bool HasRootNode() const;

    void ExportPairs_Unconditional( SynPatternResult & dest ) const;
    void ExportCoords_Unconditional( SynPatternResult & dest, const Word_Form * wf ) const;
    void ExportNodes( SynPatternResult & dest, const Word_Form * wf ) const;

    bool ContainsFunctions() const { return !export_functions.empty(); }
    void ExportByFunctions( SynPatternResult & dest, const PatternExportFuncContext & context ) const;

    #if defined SOL_COMPILER && defined SOL_LOADTXT
    void LoadTxt(
                 Dictionary &dict,
                 lem::Iridium::Macro_Parser & txtfile,
                 const SynPatterns & pattern_declarations,
                 SynPatternCompilation & compilation_context,
                 TrFunctions & functions,
                 const SynPatternPoint & point
                );
    #endif
  };


  class PatternLinks;
  class PatternNGrams;
  class PredicateTemplates;
  class TrMorphologyTracerTx;
  class ElapsedTimeConstraint;
  class PatternOptionalPoints;
  class PatternConstraints;


  struct CoordPairChecker
  {
   GramCoordEx pair;
   ViolationHandler violation_handler;

   const GramCoordEx & GetPair() const { return pair;}
   const ViolationHandler & GetViolationHandler() const { return violation_handler; }

   inline bool operator==( const CoordPairChecker & x ) const { return pair==x.pair && violation_handler==x.violation_handler; }
   inline bool operator!=( const CoordPairChecker & x ) const { return pair!=x.pair || violation_handler!=x.violation_handler; }
  };

  class TrTrace;

  class SynPatternPoint
  {
   private:
    lem::MCollect<int> PatternSequenceNumber;
    PatternMarkName mark_name; // успешное сопоставление должно генерировать переменную для
                               // последующих проверок согласования.

    int id_tree; // если тут надо вызвать другое именованное дерево-фильтр
    bool greedy; // Если вызываемое именованное дерево должно выполнить жадное сопоставление

    lem::UCString lexeme; // если задано текстовое содержимое
    int iclass, ekey;

    lem::MCollect<CoordPairChecker> coords; // уточняющие координаты
    lem::MCollect<BackRefCorrel> back_correls; // согласования с левыми точками
    lem::PtrCollect<KB_Checker> kb_checkers;

    lem::MCollect<WordSetChecker> set_checkers; // проверки на вхождение в заданные именованные множества

    lem::Ptr<TrFunCall> check_fun; // лямбда-функция для проверки узла
    lem::Ptr<TrFunCall> correl_fun; // лямбда-функция дополнительных согласований

    int ThesaurusCheck_Link, ThesaurusCheck_Entry; // для проверки, что опорная точка связана с заданной статьей указанным типом связи

    lem::zbool not_tokenizer_flags; // true, если нужно, чтобы у словофорсы не было заданного флага токенизатора
    lem::UFString tokenizer_flags; // проверка у словоформы доп. результатов токенизатора

    lem::UCString function_name; // если это функциональная точка
    lem::MCollect<SynPatternPoint*> args; // аргументы функции
    lem::UCString str_arg;

    lem::zbool terminator; // конечная точка в паттерне

    lem::MCollect<int> id_src; // информация о происхождении опорной точки в исходниках

    lem::UFString rx_string; // длинная строка для построения регекспа
    boost::wregex rx; // для функции @regex

    PatternExportSection * export_section; // экспортируемые наружу признаки
    PatternLinks * links; // построение синтаксического графа
    PatternNGrams * ngrams; // директивы расчета статистики
    PredicateTemplates * predicates; // создание предикатов
    PatternConstraints * pattern_constraints; // дополнительные условия для любых пар термов
    PatternOptionalPoints * optional_points;

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    lem::zbool error;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void RegisterRootNodeExport( SynPatternCompilation & compilation_context ) const;

    void LoadPreciser(
                      LexicalAutomat &la,
                      SynGram &sg,
                      lem::Iridium::Macro_Parser & txtfile,
                      SynPatternCompilation & compilation_context,
                      TrFunctions &functions,
                      int &iclass,
                      lem::MCollect<CoordPairChecker> & coords2,
                      lem::MCollect<BackRefCorrel> & correls,
                      lem::MCollect<WordSetChecker> & setcheckers
                     );

    void LoadExportTxt(
                       Dictionary &dict,
                       lem::Iridium::Macro_Parser & txtfile,
                       const SynPatterns & pattern_declarations,
                       SynPatternCompilation & compilation_context,
                       TrFunctions & functions
                      );
    #endif

    NGramScore CalculateNGramFreq(
                                  Dictionary &dict,
                                  const SynPatternResultBackTrace * x_result,
                                  SynPatternResult * cur_result,
                                  TreeMatchingExperience &experience,
                                  const ElapsedTimeConstraint & constraints,
                                  TrTrace *trace_log
                                 ) const;

    void GenerateLinks( const Solarix::LexicalAutomat & la, SynPatternResult * cur_result ) const;

    bool CheckConstraints(
                          const Solarix::LexicalAutomat & la,
                          const BackTrace * parent_trace,
                          SynPatternResult * cur_result
                         ) const;

    #if defined SOL_CAA
    bool Match_Untill(
                      int banned_id_tree,
                      PM_Automat & pm,
                      SynGram & sg,
                      TreeMatchingExperience & experience,
                      const ElapsedTimeConstraint & constraints,
                      const LexerTextPos * current_token,
                      BasicLexer & lexer,
                      const BackTrace * parent_trace,
                      const SynPatternResultBackTrace * x_result,
                      LA_SynPatternTrees &named_filters,
                      WordEntrySet &wordentry_sets,
                      lem::PtrCollect<SynPatternResult> & results,
                      TrTrace * trace_log
                     ) const;

    bool Match_Wordform(
                        PM_Automat & pm,
                        SynGram & sg,
                        TreeMatchingExperience & experience,
                        const LexerTextPos * current_token,
                        BasicLexer & lexer,
                        const BackTrace * parent_trace,
                        const SynPatternResultBackTrace * x_result,
                        WordEntrySet &wordentry_sets,
                        lem::PtrCollect<SynPatternResult> & results,
                        const ElapsedTimeConstraint & constraints,
                        TrTrace * trace_log
                       ) const;

    bool Match_WordformStrict(
                              PM_Automat & pm,
                              SynGram & sg,
                              TreeMatchingExperience & experience,
                              const LexerTextPos * current_token,
                              BasicLexer & lexer,
                              const BackTrace * parent_trace,
                              const SynPatternResultBackTrace * x_result,
                              WordEntrySet &wordentry_sets,
                              lem::PtrCollect<SynPatternResult> & results,
                              const ElapsedTimeConstraint & constraints,
                              TrTrace * trace_log
                             ) const;


    bool Match_WordformSet(
                           PM_Automat & pm,
                           SynGram & sg,
                           TreeMatchingExperience & experience,
                           const LexerTextPos * current_token,
                           BasicLexer & lexer,
                           const BackTrace * parent_trace,
                           const SynPatternResultBackTrace * x_result,
                           WordEntrySet &wordentry_sets,
                           lem::PtrCollect<SynPatternResult> & results,
                           const ElapsedTimeConstraint & constraints,
                           TrTrace * trace_log
                          ) const;

    bool Match_WordformSet_Strict(
                                  PM_Automat & pm,
                                  SynGram & sg,
                                  TreeMatchingExperience & experience,
                                  const LexerTextPos * current_token,
                                  BasicLexer & lexer,
                                  const BackTrace * parent_trace,
                                  const SynPatternResultBackTrace * x_result,
                                  WordEntrySet &wordentry_sets,
                                  lem::PtrCollect<SynPatternResult> & results,
                                  const ElapsedTimeConstraint & constraints,
                                  TrTrace * trace_log
                                 ) const;


    bool Match_WordentrySet(
                            PM_Automat & pm,
                            SynGram & sg,
                            TreeMatchingExperience & experience,
                            const LexerTextPos * current_token,
                            BasicLexer & lexer,
                            const BackTrace * parent_trace,
                            const SynPatternResultBackTrace * x_result,
                            WordEntrySet &wordentry_sets,
                            lem::PtrCollect<SynPatternResult> & results,
                            const ElapsedTimeConstraint & constraints,
                            TrTrace * trace_log
                           ) const;

    bool Match_WordentrySet_Strict(
                                   PM_Automat & pm,
                                   SynGram & sg,
                                   TreeMatchingExperience & experience,
                                   const LexerTextPos * current_token,
                                   BasicLexer & lexer,
                                   const BackTrace * parent_trace,
                                   const SynPatternResultBackTrace * x_result,
                                   WordEntrySet &wordentry_sets,
                                   lem::PtrCollect<SynPatternResult> & results,
                                   const ElapsedTimeConstraint & constraints,
                                   TrTrace * trace_log
                                  ) const;


    bool Match_WordSet_Strict(
                              PM_Automat & pm,
                              SynGram & sg,
                              TreeMatchingExperience & experience,
                              const LexerTextPos * current_token,
                              BasicLexer & lexer,
                              const BackTrace * parent_trace,
                              const SynPatternResultBackTrace * x_result,
                              WordEntrySet &wordentry_sets,
                              lem::PtrCollect<SynPatternResult> & results,
                              const ElapsedTimeConstraint & constraints,
                              TrTrace * trace_log
                             ) const;

    bool Match_WordSet(
                       PM_Automat & pm,
                       SynGram & sg,
                       TreeMatchingExperience & experience,
                       const LexerTextPos * current_token,
                       BasicLexer & lexer,
                       const BackTrace * parent_trace,
                       const SynPatternResultBackTrace * x_result,
                       WordEntrySet &wordentry_sets,
                       lem::PtrCollect<SynPatternResult> & results,
                       const ElapsedTimeConstraint & constraints,
                       TrTrace * trace_log
                      ) const;

    bool Match_NamedPatterns(
                             int banned_id_tree,
                             PM_Automat &pm,
                             SynGram &sg,
                             TreeMatchingExperience &experience,
                             const ElapsedTimeConstraint & constraints,
                             const LexerTextPos * current_token,
                             BasicLexer & lexer,
                             const BackTrace *parent_trace,
                             const SynPatternResultBackTrace * x_result,
                             LA_SynPatternTrees &named_filters,
                             WordEntrySet &wordentry_sets,
                             bool force_greedy,
                             bool force_export,
                             bool can_skip_outer_tokens,
                             lem::PtrCollect<SynPatternResult> & results,
                             TrTrace *trace_log,
                             int dbg_mark,
                             TrMorphologyTracerTx &log_tx
                            ) const;

    bool Match_NamedPatterns_Strict(
                                    int banned_id_tree,
                                    PM_Automat &pm,
                                    SynGram &sg,
                                    TreeMatchingExperience &experience,
                                    const ElapsedTimeConstraint & constraints,
                                    const LexerTextPos * current_token0,
                                    BasicLexer & lexer,
                                    const BackTrace *parent_trace,
                                    const SynPatternResultBackTrace * x_result,
                                    LA_SynPatternTrees &named_filters,
                                    WordEntrySet &wordentry_sets,
                                    bool force_greedy,
                                    bool force_export,
                                    lem::PtrCollect<SynPatternResult> & results,
                                    TrTrace *trace_log,
                                    int dbg_mark,
                                    TrMorphologyTracerTx & log_tx
                                   ) const;


    bool Execute_Mark(
                      int banned_it_tree,
                      PM_Automat &pm,
                      SynGram &sg,
                      TreeMatchingExperience &experience,
                      const ElapsedTimeConstraint & constraints,
                      const LexerTextPos * current_token,
                      BasicLexer & lexer,
                      const BackTrace *parent_trace,
                      const SynPatternResultBackTrace * x_result,
                      LA_SynPatternTrees &named_filters,
                      WordEntrySet &wordentry_sets,
                      bool force_greedy,
                      bool force_export,
                      bool can_skip_outer_tokens,
                      lem::PtrCollect<SynPatternResult> & results,
                      TrTrace *trace_log
                     ) const;


    bool Equal_ThrowingExceptions(
                                  int banned_it_tree,
                                  PM_Automat &pm,
                                  SynGram &sg,
                                  TreeMatchingExperience &experience,
                                  const ElapsedTimeConstraint & constraints,
                                  const LexerTextPos * current_token,
                                  BasicLexer & lexer,
                                  const BackTrace * parent_trace,
                                  const SynPatternResultBackTrace * x_result,
                                  LA_SynPatternTrees &named_filters,
                                  WordEntrySet &wordentry_sets,
                                  bool force_greedy,
                                  bool force_export,
                                  bool can_skip_outer_tokens,
                                  lem::PtrCollect<SynPatternResult> & results,
                                  TrTrace *trace_log
                                 ) const;
    #endif

   public:
    SynPatternPoint(void);
    SynPatternPoint( const SynPatternPoint &x );

    ~SynPatternPoint(void);

    void operator=( const SynPatternPoint &x );

    bool IsNamedTreeCall() const { return id_tree!=UNKNOWN; }
    void AddRootNodeExport( Dictionary & dict );

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    bool operator<( const SynPatternPoint &x ) const;
    #endif

    bool Equal( const SynPatternPoint &x ) const;
    bool EqualHead( const SynPatternPoint &x ) const;
    void Merge( const SynPatternPoint &src );

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void LoadTxt(
                 Dictionary &dict,
                 lem::Iridium::Macro_Parser & txtfile,
                 const SynPatterns &patterns,
                 SynPatternCompilation & compilation_context,
                 TrFunctions &functions,
                 bool ParseExportSection=true
                );

    bool Error(void) const { return error; }
    void Terminator(void) { terminator=true; }

    const lem::UCString& GetMarkerName(void) const { return mark_name.GetName(); }
    void OptimizeAfterCompilation( const SynPatternCompilation & compilation_context );
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream& bin ) const;
    #endif

    bool IsTerminator(void) const { return terminator; }

    #if defined SOL_LOADBIN 
    void LoadBin( lem::Stream& binfile );
    void Link( const TrFunctions &funs );
    #endif

    void SetLinks( PatternLinks *links_to_store );
    void SetNGrams( PatternNGrams *ngrams_to_store );
    void SetPredicates( PredicateTemplates * predicates_to_store );
    void SetConstraints( PatternConstraints *constraints_to_store );
    void SetOptionalPoints( PatternOptionalPoints *optional_points_to_store );


    #if defined SOL_CAA && !defined SOL_NO_AA
    bool Equal(
               int banned_it_tree,
               PM_Automat &pm,
               SynGram &sg,
               TreeMatchingExperience &experience,
               const ElapsedTimeConstraint & constraints,
               const LexerTextPos * current_token,
               BasicLexer & lexer,
               const BackTrace * parent_trace,
               const SynPatternResultBackTrace * x_result,
               LA_SynPatternTrees &named_filters,
               WordEntrySet &wordentry_sets,
               bool greedy,
               bool force_export,
               bool can_skip_outer_tokens,
               lem::PtrCollect<SynPatternResult> &results,
               TrTrace *trace_log
              ) const;
    #endif

    #if defined SOL_DEBUGGING
    void Print( lem::OFormatter &to, SynGram &sg ) const;
    #endif

    const lem::MCollect<int> & GetSources() const { return id_src; }

    const lem::MCollect<int>& GetPatternSequenceNumber() const { return PatternSequenceNumber; }

    int GetScores(void) const;
  };



  #if defined SOL_LOADTXT && defined SOL_COMPILER
  class SynPatternExport
  {
   public:
    lem::MCollect<int> export_coords; // эскпортируемые координаты
    lem::MCollect<int> null_export_coords; // 1 для экспортируемых координат, которые не обязательно экспортируются

    lem::Collect<lem::UCString> export_nodes; // экспортируемые именованные словоформы
    lem::MCollect<int> null_export_nodes;

   public:
    SynPatternExport(void);
    SynPatternExport( const SynPatternExport &x );
    void operator=( const SynPatternExport &x );

    bool Empty(void) const;

    void LoadTxt(
                 Dictionary &dict,
                 lem::Iridium::Macro_Parser & txtfile
                );

    void RegisterExport( SynPatternCompilation &compilation_context );

    bool ContainsCoord( int CoordID ) const;

    void ExportPairs_Unconditional( SynPatternResult & dest ) const;
  };
  #endif


  #if defined SOL_LOADTXT && defined SOL_COMPILER
  class SynPatternOptions : lem::NonCopyable
  {
   private:
    lem::UCString name;
    bool greedy;
    bool bottomup;
    int id_language;
    SynPatternExport export_info;

   public:
    SynPatternOptions();

    const lem::UCString& GetName(void) const { return name; }
    bool IsGreedy() const { return greedy; }
    bool IsBottomUp() const { return bottomup; }
    bool IsTopDown() const { return !bottomup; }

    int GetLanguageId() const { return id_language; }
    const SynPatternExport& GetExport() const { return export_info; }
    void LoadTxt( Dictionary &dict, lem::Iridium::Macro_Parser & txtfile );
  };
  #endif



  #if defined SOL_LOADTXT && defined SOL_COMPILER
  class SynPatterns : lem::NonCopyable
  {
   private:
    int id_tree_seq;
    lem::PtrCollect<SynPatternOptions> options;
    std::map< lem::UCString, SynPatternOptions* > patterns;
    std::map< lem::UCString, int > name2id;
    std::map< int, int > id2count; // для контроля реализации предварительно объявленных групп

   public:
    SynPatterns(void);

    void LoadTxt( Dictionary &dict, lem::Iridium::Macro_Parser & txtfile );

    bool HasNamedPatterns(void) const { return !options.empty(); }
    bool IsPatternName( const lem::UCString &name ) const;
    const SynPatternOptions& GetOptions( const lem::UCString &name ) const;
    int GetPatternID( const lem::UCString &name ) const;
    int GetNextTreeID();

    void NamedPatternLoaded( const lem::UCString &name );
    void GetUnresolvedForwardDeclarations( lem::MCollect<lem::UCString> & unresolved_names ) const;
  };
  #endif

  class PatternConstraints;

  #if defined SOL_LOADTXT && defined SOL_COMPILER
  class SynPattern : lem::NonCopyable
  {
   private:
    int id_src;
    lem::UCString name; // пользовательское наименование, безымянные
                        // формируют фильтрующее дерево, именованные
                        // используются как вызываемые в узлах основного
                        // фильтра.

    int id_language; // для какого языка действует это правило
    bool incomplete;

    lem::Ptr<SynPatternCompilation> compilation_context; // объявления переменных, для последующего
                                                         // сравнения у всех одноименных контекстов

    PatternConstraints * constraints;

    void LoadLinks( 
                   Dictionary &dict,
                   lem::Iridium::Macro_Parser & txtfile,
                   SynPatternCompilation & compilation_context
                  );

    void LoadNGrams(
                    Dictionary &dict,
                    lem::Iridium::Macro_Parser & txtfile,
                    SynPatternCompilation & compilation_context
                   );

    void LoadPredicates( 
                        Dictionary &dict,
                        lem::Iridium::Macro_Parser & txtfile,
                        SynPatternCompilation & compilation_context
                       );

    void LoadConstraints(
                         Dictionary &dict,
                         lem::Iridium::Macro_Parser & txtfile,
                         SynPatternCompilation & compilation_context
                        );

    lem::PtrCollect<SynPatternPoint> points;

   public:
    lem::MCollect<SlotProperties> slots;
    SynPatternExport export_info; // экспортируемые координаты и именованные словоформы

   public:
    SynPattern();
    ~SynPattern();

    const lem::UCString& GetName() const { return name; }
    int GetLanguageId() const { return id_language; }
    bool IsIncomplete() const { return incomplete; }

    int GetSourceLocation() const { return id_src; }

    void LoadTxt(
                 Dictionary & dict,
                 lem::Iridium::Macro_Parser & txtfile,
                 const SynPatterns & patterns,
                 WordEntrySet & wordentry_set,
                 TrFunctions & functions
                );

    const lem::PtrCollect<SynPatternPoint>& GetPointChain() const;

    bool Error(void) const;

    void Print( lem::OFormatter &to, SynGram &sg ) const;
    void CheckBeforeMerge( const SynPattern &x, SynGram &sg ) const;
  };
  #endif

  class TreeScorerPoint;
  class SynPatternTreeNodeMatchingResults;

  class SynPatternTreeNode : lem::NonCopyable
  {
   private:
    bool bottomup;
    lem::PtrCollect<SynPatternPoint> point;
    lem::PtrCollect<SynPatternTreeNode> leaf;

    #if defined SOL_CAA && !defined SOL_NO_AA
    void Limit(
               BasicLexer & lexer,
               lem::PtrCollect<SynPatternResult> & results,
               SynGram & sg
              ) const;
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    void TryMatchIncomplete(
                            PM_Automat &pm,
                            SynGram &sg,
                            TreeMatchingExperience &experience,
                            const ElapsedTimeConstraint & constraints,
                            LA_SynPatternTrees &named_filters,
                            WordEntrySet &wordentry_sets,
                            BasicLexer & lexer,
                            const LexerTextPos * current_token,
                            const SynPatternResult * current_result,
                            int fragment_no,
                            const BackTrace * parent_trace,
                            lem::PtrCollect<SynPatternResult> &final_results,
                            lem::MCollect<int> & final_result_fragments,
                            TrTrace *trace_log
                           ) const;
    #endif


    #if defined SOL_CAA && !defined SOL_NO_AA
    bool Match(
               int banned_id_tree,
               PM_Automat &pm,
               SynGram &sg,
               TreeMatchingExperience &experience,
               const ElapsedTimeConstraint & constraints,
               LA_SynPatternTrees &named_filters,
               WordEntrySet &wordentry_sets,
               BasicLexer &lexer,
               const LexerTextPos * current_token,
               const BackTrace *parent_trace,
               const SynPatternResultBackTrace * x_result,
               bool greedy,
               bool can_skip_outer_tokens,
               lem::PtrCollect<SynPatternResult> &results,
               TrTrace *trace_log
              ) const;
    #endif


    #if defined SOL_LOADTXT && defined SOL_COMPILER
    SynPatternTreeNode( const SynPattern & pattern, int ipoint=0 );
    SynPatternTreeNode( const lem::MCollect<SynPatternPoint*> & points, int ipoint );
    #endif

   public:
    SynPatternTreeNode(void);

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    SynPatternTreeNode( const lem::MCollect<SynPattern*> & patterns );
    SynPatternTreeNode( const lem::MCollect<SynPatternPoint*> & points );
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void Merge( const SynPattern &pattern, int ipoint );
    void SetBottomUp() { bottomup=true; }
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream& bin ) const;
    #endif

    #if defined SOL_LOADBIN 
    void LoadBin( lem::Stream& binfile );
    void Link( const TrFunctions &funs );
    #endif

    #if defined SOL_CAA && !defined SOL_NO_AA
    bool MatchTree(
                   int id_tree,
                   PM_Automat &pm,
                   SynGram &sg,
                   TreeMatchingExperience &experience,
                   const ElapsedTimeConstraint & constraints,
                   LA_SynPatternTrees &named_filters,
                   WordEntrySet & wordentry_sets,
                   BasicLexer & lexer,
                   const LexerTextPos * current_token,
                   const BackTrace * parent_trace,
                   const SynPatternResultBackTrace * x_result,
                   bool greedy,
                   bool can_skip_outer_tokens,
                   lem::PtrCollect<SynPatternResult> &results,
                   TrTrace *trace_log
                  ) const;
    #endif


    #if defined SOL_CAA && !defined SOL_NO_AA
    SynPatternTreeNodeMatchingResults* CompleteAnalysis(
                                                        PM_Automat &pm,
                                                        SynGram &sg,
                                                        LA_SynPatternTrees &named_filters,
                                                        WordEntrySet &wordentry_sets,
                                                        BasicLexer &lexer,
                                                        int id_language,
                                                        TreeMatchingExperience & experience,
                                                        const ElapsedTimeConstraint & constraints,
                                                        TrTrace *trace_log
                                                       ) const;


    SynPatternTreeNodeMatchingResults* IncompleteAnalysis(
                                                          PM_Automat &pm,
                                                          SynGram &sg,
                                                          LA_SynPatternTrees &named_filters,
                                                          WordEntrySet &wordentry_sets,
                                                          BasicLexer &lexer,
                                                          int id_language,
                                                          TreeMatchingExperience & experience,
                                                          const ElapsedTimeConstraint & constraints,
                                                          TrTrace *trace_log
                                                         ) const;


    bool Empty(void) const;
    #endif
  };
 }

#endif
