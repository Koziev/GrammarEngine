#ifndef TRACE_LOG__H
#define TRACE_LOG__H
#pragma once

 // CD->13.06.2009
 // LC->10.07.2013

 namespace lem
 {
  class UFString;
  class OFormatter;
 }

 namespace Solarix
 {
  class BasicLexer;
  class LexerTextPos;
  class Tree_Node;
  class TrValue;
  class CollocFilterSourceAccessor;
  class Dictionary;
  class CS_Pattern;
  struct CS_LinkedChains;

  #if defined SOL_CAA && !defined SOL_NO_AA
  // Интерфейс для организации трассировки исполнения трансформант.
  class TrTraceActor : lem::NonCopyable
  {
   public:
    static int seq;
    bool entering;

   protected:
    lem::MCollect<int> src_locations;
    int seq_mark;

   public:
    TrTraceActor( int Mark, int Location );
    TrTraceActor( int Mark, const lem::MCollect<int> & Locations );

    bool HasLocation(void) const { return !src_locations.empty() && src_locations.front()!=UNKNOWN; }
    const lem::MCollect<int>& GetLocations(void) const { return src_locations; }
     
    virtual ~TrTraceActor(void) {}
    virtual void Print( Dictionary &dict,lem::OFormatter &out, const TrTraceActor *opening=NULL )=0;
    bool Match( const TrTraceActor * x ) const;

    // Вернет true для шагов в функции {...}, операторов процедуры, входов в правила трансформации
    // и синтаксического анализа и т.д.
    virtual bool IsStatement(void) const { return false; }

    virtual bool ExecuteBreakpoints(void) const { return true; }

    virtual void PrintContext( Solarix::Dictionary &dict, lem::OFormatter &out ) const;
    virtual int CountContextItems(void) const;
    virtual lem::UFString GetContextItemName( int i ) const;
    virtual void PrintContextItem( Solarix::Dictionary &dict, int i, lem::OFormatter &out ) const;
  };
  #endif

  class TrTraceActor;

  #if defined SOL_CAA
  class TrMorphologyTracer;
  class Variator;
  class LA_RecognitionTrace;
  class LA_PreprocessorTrace;
  //class TrWideContext;
  //class TrYield;
  class Res_Pack;
  class Variator;
  class Plain_Text;
  class SyllabContext;
  class SyllabRule;

  struct CollocFilterInfo;
  struct CollocFilterDebugInfo;
  struct CollocFilterMatchingContext;

  struct SynPatternResult;
  class BackTrace;
  class SynPatternPoint;
  class BasicLexer;
  class TextAnalysisSession;
  //class ConnectionState;
  //class ConnectorApplication;

  class TrTrace
  {
   private:
    TrMorphologyTracer *morphology_tracer;

   public:
    TrTrace(void);
    virtual ~TrTrace(void);

    virtual void Enter( TrTraceActor *a );
    virtual void Leave( TrTraceActor *a );
    virtual void Print( const lem::UFString &str )=0;
    virtual void PrintStack( lem::OFormatter &out ) {}
    virtual void StartNewSentence(void);
    virtual void RaisedExceptionLocation( const lem::MCollect<int> &src_locations )=0;
    virtual void RaisedExceptionLocation( int src_locations )=0;
    virtual void MorphologyAnalysisCompleted( const Solarix::TextAnalysisSession & fblo ) {}

    virtual void ShowLexerPerformance( BasicLexer & lexer ) {}

    virtual void MorphologicalAnalysisStarts( Solarix::BasicLexer & lexer ) {}
    virtual void MorphologicalAnalysisFinishes( const Solarix::Res_Pack & pack ) {}
    virtual TrMorphologyTracer& GetMorphologyTracer(void);

    virtual LA_RecognitionTrace* RecognizerTrace(void)=0;
    virtual LA_PreprocessorTrace* PreprocessorTrace(void)=0;

    virtual void BreakOnRightBoundary( const lem::MCollect<SynPatternResult*> & results )=0;

    virtual void BeforeSynPatternTreeProve(
                                           const SynPatternPoint &point,
                                           const lem::MCollect<int> &id_src,
                                           const BasicLexer & lexer,
                                           const LexerTextPos * current_token,
                                           const BackTrace * parent_trace
                                          )=0;

    // В правилах нисходящего парсера доказано именованное дерево в опорной точке.
    virtual void SynPatternTreeProved(
                                      const SynPatternPoint &point,
                                      const lem::MCollect<int> &id_src,
                                      const BasicLexer & lexer,
                                      const LexerTextPos * current_token,
                                      const lem::PtrCollect<SynPatternResult> & subresults
                                     )=0;

   // Перед началом проверки токена на условие опорной точки
   virtual void BeforeMatchingTheWord(
                                      const SynPatternPoint &point,
                                      const lem::MCollect<int> &id_src,
                                      const BasicLexer & lexer,
                                      const LexerTextPos *current_token
                                     )=0;

    virtual void DebugTrace( const lem::UCString &marker, const TrValue &arg )=0;

    virtual void AfterModelApplication( Solarix::BasicLexer & lexer ) {}

    // Так как язык обрабатываемых предложений не зада явно, то движок предпринял попытку
    // определить язык по статистическим критериям.
    virtual void LanguageGuessed( const lem::UFString & str, int id_language ) {}

    virtual void ClassifierModelApplied( const Word_Form * focus, const Word_Form * new_token_wordform )=0;

  };
  #endif
 }

#endif
