#if !defined SynPatternResult__H
 #define SynPatternResult__H

 #include <lem/noncopyable.h>
 #include <lem/ucstring.h>
 #include <lem/zeroed.h>
 #include <lem/solarix/ExportNodes.h>
 #include <lem/solarix/BackTrace.h>
 #include <lem/solarix/PatternLinkEdge.h>
 #include <lem/solarix/PatternSynLinkedGroup.h>
 #include <lem/solarix/NGramScore.h>

 namespace Solarix
 {

  // Результаты сопоставления опорной точки с контекстом.
  // Сочетание булевского флага и целочисленной длины сопоставленного
  // контекста позволяет реализовать опорные точки с нулевой длиной
  class SynPatternMatchResult
  {
   private:
    bool matched;
    int len; // количество токенов в сопоставленной цепочке
    const LexerTextPos * start_token;
    const LexerTextPos * final_token; // последний токен из сопоставленных.
    NGramScore ngram_freq; // сумма частот проверенных N-грамм

   public:
    SynPatternMatchResult(void) : matched(false), len(0), start_token(NULL), final_token(NULL), ngram_freq(0) {}

    SynPatternMatchResult( bool _matched, int _len, const LexerTextPos * _start_token, const LexerTextPos * _final_token, const NGramScore & _ngram_freq )
     : matched(_matched), len(_len), start_token(_start_token), final_token(_final_token), ngram_freq(_ngram_freq) {}

    SynPatternMatchResult( const SynPatternMatchResult &x )
     : matched(x.matched), len(x.len), start_token(x.start_token), final_token(x.final_token), ngram_freq(x.ngram_freq)
    {}

    void operator=( const SynPatternMatchResult &x )
    {
     matched=x.matched;
     len=x.len;
     start_token=x.start_token;
     final_token=x.final_token;
     ngram_freq=x.ngram_freq;
    }

    bool Matched(void) const { return matched; }
    int Length(void) const { return len; }

    const LexerTextPos * GetStartToken() const { return start_token; }
    const LexerTextPos * GetFinalToken() const { return final_token; }

    NGramScore GetNGramFreq(void) const { return ngram_freq; }

    void SetNGramFreq( const NGramScore & new_freq ) { ngram_freq=new_freq; }
    void AddNGramFreq( const NGramScore & delta_freq ) { ngram_freq+=delta_freq; }
  };


  typedef std::multimap< const Word_Form*, int /*iversion*/ > MATCHING_ALTS;
  typedef std::multimap< int /*id_coord*/, int /*id_state*/ > EXPORTED_COORDS;
  typedef lem::MCollect< std::pair<const lem::UCString*,const Word_Form*> > EXPORTED_NODES;



  #if defined SOL_DEBUGGING
  class SynPatternPoint;
  class Word_Form;
  struct SynPatternDebugTrace
  {
   const SynPatternPoint * point;
   const Word_Form * wordform;
   const lem::UCString * pattern_name; // имя выполняемого паттерна.
   bool wordform_matching; // если в этой точке проверялась конкретная словоформа.

   int id_src_tree_scorer; // если был использован tree scorer в секции : ngrams{} для расчета веса - то ссылка на объявление примененного правила оценки
   NGramScore ngram_freq; // если в этом точке был выставлен штраф или поощрение.
   const char * scoring_reason; // константная строковая пометка - причина изменения score
   
   SynPatternDebugTrace() : point(NULL), wordform(NULL), pattern_name(NULL), wordform_matching(false), id_src_tree_scorer(UNKNOWN), scoring_reason(NULL) {}

   SynPatternDebugTrace( const SynPatternPoint * _point, const Word_Form * _wordform, const lem::UCString * _pattern_name )
    : point(_point), wordform(_wordform), pattern_name(_pattern_name), wordform_matching(false), id_src_tree_scorer(UNKNOWN), scoring_reason(NULL)
   {}

   SynPatternDebugTrace( const SynPatternPoint * _point, const Word_Form * _wordform )
    : point(_point), wordform(_wordform), pattern_name(NULL), wordform_matching(true), id_src_tree_scorer(UNKNOWN), scoring_reason(NULL)
   {}

   bool SamePoint( const SynPatternDebugTrace & x ) const
   { return point==x.point && wordform==x.wordform; }
  };

  typedef lem::MCollect<SynPatternDebugTrace> SYNPATTERN_DEBUG_TRACE;
  #endif


  // ******************************************************
  // Альтернативный результат сопоставления дерева.
  // ******************************************************
  struct SynPatternResult : lem::NonCopyable
  {
   SynPatternMatchResult res;
   lem::zbool named_tree_invoked;
   BackTrace trace;
   MATCHING_ALTS matched_alts;
   EXPORTED_COORDS exported_coords;
   EXPORTED_NODES exported_nodes;
   LINKAGE_GROUPS linkage_groups;
   LINKAGE_EDGES linkage_edges;
   lem::zbool has_prelinked_nodes;

   #if defined SOL_DEBUGGING
   SYNPATTERN_DEBUG_TRACE debug_trace;

   // Эти поля заполняются на стадии ApplyTreeScorer, поэтому их не надо пробрасывать через стек вызовов.
   lem::MCollect<int> scorer_id_src; // id позиции в исходниках для примененных tree_scorer и assoc_word.
   #endif

   SynPatternResult(void) {}

   SynPatternResult( const BackTrace *parent_trace ) : trace(parent_trace) {}

   SynPatternResult* Copy1( const BackTrace *parent_trace ) const;

   void FilterExportedCoords( const lem::MCollect<int> & must_be_exported );
   void FilterExportedNodes( const lem::MCollect< ExportNode > & must_be_exported );
   
   #if defined SOL_DEBUGGING
   bool FindExportedNode( const lem::UCString & e ) const;
   #endif

   void Print( lem::OFormatter &out, SynGram &sg ) const;
   void PrintExportedNodes( lem::OFormatter &out, SynGram &sg ) const;
   void PrintLinks( lem::OFormatter &out, SynGram &sg ) const;
   void PrintLinkageGroups( lem::OFormatter &out, SynGram &sg ) const;

   void AddExportedNode( const lem::UCString * name, const Word_Form * node );
   const Word_Form* FindExportNode( const lem::UCString & name ) const;

   int FindLinkageGroup( const LexerTextPos * t1, const LexerTextPos * t2 ) const;
   void AddLinkageGroup( const PatternSynLinkedGroup & new_group );
   void AddLinkageEdge( const PatternLinkEdge & new_edge );

   #if defined SOL_DEBUGGING
   void AppendDebugTrace( const lem::MCollect<SynPatternDebugTrace> & debug_trace2 );
   void Append( const SynPatternDebugTrace & dbg );
   #endif

   void Append( const SynPatternResult & src );
   void AppendMatchedAlts( const SynPatternResult & src );
   void AppendLinks( const SynPatternResult & src );

   int CalcHash() const;
   static bool Equals( const SynPatternResult *x, const SynPatternResult *y );
   static void SelectUnique_WithoutRemoval( lem::MCollect<const SynPatternResult*> & results );
   static void SelectUnique_WithRemoval( lem::MCollect<SynPatternResult*> & results );

   void ResetCoordStates( int coord_id, const lem::MCollect<int> & state_ids );
   void GetExportCoordPairs( lem::MCollect< std::pair<int,int> > & pairs ) const;
  };

 }

#endif
