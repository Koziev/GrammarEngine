#if !defined SYNTAX__H
 #define SYNTAX__H

 #include <lem/solarix/dictionary.h>
 #include <lem/solarix/trace_log.h>
 #include <lem/solarix/LA_RecognitionTrace.h>
 #include <lem/solarix/LA_PreprocessorTrace.h>
 #include <lem/solarix/BasicLexer.h>
 #include <lem/solarix/SG_TagFilter.h>
 #include <lem/solarix/WrittenTextAnalysisSession.h>

 using namespace lem;
 using namespace Solarix;

 struct TrBreakpoint
 {
  int pass_count; // сколько раз сработала точка

  lem::zbool once;
  lem::zbool step;
  int ifile, iline; // пользовательские точки - останов в указанной строке указанного файла
  int on_call_stack_depth, on_pass_count;
   
  
  TrBreakpoint(void) : pass_count(0), ifile(UNKNOWN), iline(UNKNOWN), on_call_stack_depth(UNKNOWN), on_pass_count(UNKNOWN) {}
 };

 class LA_RecognitionTrace_Console : public LA_RecognitionTrace
 {
  private:
   Solarix::Dictionary *dict;
   lem::zbool trace;

  public:
   LA_RecognitionTrace_Console( Solarix::Dictionary *d );

   void Trace( bool f ) { trace=f; }

   virtual void CropRuleApplied(
                                const lem::UCString &word_before,
                                const lem::UCString &word_after,
                                const LA_CropRule *rule
                               );

   virtual void Matched( const lem::UCString &word, const LA_RecognitionRule *rule );
   virtual void MatchedSyllable( const lem::UCString &word, const lem::UCString &syllable, const LA_RecognitionRule *rule );
   virtual void PhoneticRuleProduction( const lem::UCString &source, const lem::UCString &result, lem::Real1 val, const LA_PhoneticRule *rule );
   virtual void WordSyllabs( const lem::UCString &word, const lem::MCollect<lem::UCString> &slb_list );

   virtual void SyllabicBreakRuleHit(
                                     const SyllabContext & context,
                                     int cursor_pos,
                                     const SyllabRule & rule
                                    ) {}

   virtual void SyllabicBreakRuleApplied(
                                         const SyllabContext & context,
                                         int cursor_pos,
                                         const SyllabRule & rule
                                        ) {}

 };

 class LA_PreprocessorTrace_Console : public LA_PreprocessorTrace
 {
  private:
   Solarix::Dictionary *dict;
   lem::zbool trace;

  public: 
   LA_PreprocessorTrace_Console( Solarix::Dictionary *d );

   void Trace( bool f ) { trace=f; }

   virtual void LanguageGuessed( const lem::UFString &phrase, int LanguageID );
 };


 class TrDebugger : public TrTrace
 {
  private:
   lem::zbool trace;

   struct AppliedCollocFilter : lem::NonCopyable
   {
    lem::UCString filter_name;
    lem::Path src_filename;
    int src_line;
    lem::UFString context;
   };

   lem::PtrCollect<AppliedCollocFilter> applied_colloc_filter;

   Solarix::Dictionary *dict;
   lem::PtrCollect<TrBreakpoint> breakpoints;
   lem::PtrCollect<TrTraceActor> callstack;

   lem::Collect<lem::Path> source_filename;
   lem::PtrCollect<lem::UTextParser> source_parser;

   void ExecuteBreakpoints( TrTraceActor *a );
   void ExecuteBreakpoint( int ipoint, TrTraceActor *a );
   UTextParser& GetSourceText( const lem::Path &filename );

   lem::zbool stop_before_analysis;
   lem::zbool stop_on_right_boundary;
   lem::zbool stop_after_model;

   LA_RecognitionTrace_Console * recognizer_trace;
   LA_PreprocessorTrace_Console * preprocessor_trace;

   virtual void RaisedExceptionLocation( const lem::MCollect<int> &src_locations );
   virtual void RaisedExceptionLocation( int src_locations );

   void ShowSynPatternResults( const lem::MCollect<SynPatternResult*> & results, bool sort_by_scores, int items_to_show );
   void AfterModelApplication( Solarix::BasicLexer & lexer );
   void StackOverflow( int current_depth );


  public:
   TrDebugger( Solarix::Dictionary *d );
   virtual ~TrDebugger(void);

   void Trace( bool f );

   void ManageTriggers(void);

   virtual void CheckStackOverflow( int current_depth );
   virtual void Enter( TrTraceActor *a );
   virtual void Leave( TrTraceActor *a );
   virtual void Print( const UFString &str );

   virtual void ShowLexerPerformance( BasicLexer & lexer );

   virtual void MorphologicalAnalysisStarts( Solarix::BasicLexer & lexer );
   virtual void MorphologicalAnalysisFinishes( const Solarix::Res_Pack & pack );
   virtual void MorphologyAnalysisCompleted( const Solarix::TextAnalysisSession & fblo );

   void BeforePhrase(void);
   void AfterPhrase(void);
   void ManageBreakpoints(void);

   virtual void PrintStack( lem::OFormatter &out );

   virtual LA_RecognitionTrace* RecognizerTrace(void);
   virtual LA_PreprocessorTrace* PreprocessorTrace(void);

   virtual void BreakOnRightBoundary( const lem::MCollect<SynPatternResult*> & results );

   virtual void DebugTrace( const lem::UCString &marker, const TrValue &arg );

   void PrintTokenizationGraph( BasicLexer & lexer, bool detailed );

   virtual void BeforeSynPatternTreeProve(
                                          const SynPatternPoint &point,
                                          const lem::MCollect<int> &id_src,
                                          const BasicLexer & lexer,
                                          const LexerTextPos * current_token,
                                          const BackTrace * parent_trace
                                         );

   virtual void SynPatternTreeProved(
                                     const SynPatternPoint &point,
                                     const lem::MCollect<int> &id_src,
                                     const BasicLexer & lexer,
                                     const LexerTextPos *current_token, 
                                     const lem::PtrCollect<SynPatternResult> & subresults
                                    );

   virtual void BeforeMatchingTheWord(
                                      const SynPatternPoint &point,
                                      const lem::MCollect<int> &id_src,
                                      const BasicLexer & lexer,
                                      const LexerTextPos *current_token
                                     );


   virtual void LanguageGuessed( const lem::UFString & str, int id_language );
   virtual void ClassifierModelApplied( const Word_Form * focus, const Word_Form * new_token_wordform );
 };


 class SyntaxShell
 {
  public:
   typedef enum { MorphologyMode, SyntaxMode, TokenizerMode, SegmenterMode, LemmatizerMode, SpeakerMode } RunMode;

   void SetMode( RunMode new_mode );

  private:
   RunMode run_mode; // текущий режим функционирования - какой блок анализа работает.

   bool lazy_lexicon;
   lem::Ptr<Dictionary> sol_id;
   lem::Ptr<TrDebugger> debugger;

   OFormatter nul_tty;

   lem::UFString pre_entered_phrase;

   lem::Ptr<WrittenTextAnalysisSession> current_analysis;

   lem::zbool allow_fuzzy;
   lem::zbool CompleteAnalysisOnly;
   lem::zbool UseReconstructor;
   lem::zbool traceon;
   lem::UCString scenario; // сценарий трансформации (перевод и пр.)
   lem::zbool ApplyModel; // использовать языковую статистическую модель для снятия неоднозначности
   int MaxSkipToken;

   lem::zbool UseTopDownThenSparse; // работа по схеме: сначала попробовать полный нисходящий анализ, если неудача и осталось время - то примерный нисходящий.
   lem::zbool EnableFilters;

   int MaxTimeout; // можно интерактивно задать лимит времени на анализ предложения.
   int MaxAlt;
   bool FindFacts;

   lem::ElapsedTime elapsed;

   lem::Collect< std::pair<UCString /*tag*/, UCString /*value*/> > tags; // тэги для фильтрации переводов
   lem::Ptr<Solarix::SG_TagFilter> tags_ptr; // скомпилированные тэги

   lem::Ptr<Solarix::SG_TagFilter> transl0_tag; // специальный фильтр для отбора только переводов с transl_order=0
   lem::Ptr<Solarix::SG_TagFilter> transl1_tag; // специальный фильтр для отбора только основных переводов

   lem::Collect< std::pair<UCString /*param*/, UCString /*value*/> > params; // глобальные параметры для управления алгоритмом перевода

   lem::zbool guess_language; // язык нужно подбирать для каждой вводимой фразы
   int default_language; // язык синтаксического анализа (для многоязычных словарей)
   lem::zbool needs_shortest_var; // печатать на консоли только самые короткие варианты разбора

   lem::zbool debug;

   const lem::UFString enter_cmd( const char *Prompt ) const;
   bool TryCommand( const lem::UFString &str );
   void ShowHelp(void) const;
   void Exiting(void);
   void Tokenize( const UFString & s );
   void Lemmatize( const UFString & str );
   void Speak( const UFString & str );
   void Segmentize( const UFString & s );


   void ShowDictionaryInfo(void);

   bool PerformSyntacticAnalysis( const UFString &sent );
   UFString VarToStr( const Solarix::Variator &var ) const;

   void PrintLexerPerformance( Solarix::BasicLexer & lexer, const lem::MCollect<const LexerTextPos*> & tokens );
   void PrintLexerPerformance( Solarix::BasicLexer & lexer, const LexerTextPos * token );

  public:
   lem::Path dict_dir;

  public:
   SyntaxShell(void);
   ~SyntaxShell(void);

   void SetDebug( bool f );
   void SetPhrase( const lem::UFString &x );

   void LazyLexicon( bool _lazy_lexicon );
   void LoadDictionary();

   void main_loop(void);
   void SetLanguage( const UCString &lang_name );
   void SetThesaurusTags( const lem::Collect< std::pair<UCString /*tag*/, UCString /*value*/> > & Tags );
   void SetEnvParams( const lem::Collect< std::pair<UCString /*param*/, UCString /*value*/> > & Params );

   void AllowIncomplete( bool f ) { CompleteAnalysisOnly=!f; }
   void AllowFuzzy( bool f ) { allow_fuzzy=f; }
   void AllowReconstructor( bool f ) { UseReconstructor=f; }
   void AllowModel(  bool f ) { ApplyModel=f; }
   void RunSemantics() { FindFacts=true; }
   void SetMaxAlt( int _max_alt ) { MaxAlt=_max_alt; }
   void SetMaxSkipToken( int _n ) { MaxSkipToken=_n; }
 };

#endif
