#if !defined SynPatternTreeNodeMatchingResults__H && defined SOL_CAA && !defined SOL_NO_AA
#define SynPatternTreeNodeMatchingResults__H

#include <lem/noncopyable.h>
#include <lem/solarix/BackTrace.h>

namespace Solarix {

struct SynPatternResult;
class Res_Pack;
class BasicLexer;
class LexerTextPos;
class WordEntrySet;
class TreeScorerPoint;
class WordAssociation;
class TreeScorerApplicationContext;

class SynPatternTreeNodeMatchingResults : lem::NonCopyable
{
 public:
  lem::MCollect<SynPatternResult*> results;
  BackTrace null_trace;
  bool merge_results;
  lem::MCollect<LexerTextPos*> tokens_garbage_collector;

 private:
  Res_Pack * GenerateAllPaths( Dictionary & dict, BasicLexer & lexer, TrTrace *trace_log );
  Res_Pack * GenerateFilteredPaths(
                                   Dictionary &dict,
                                   BasicLexer & lexer,
                                   bool DoLinkNodes,
                                   bool CompleteAnalysisOnly,
                                   TrTrace *trace_log
                                  );


  void ApplyWordAssociations( Dictionary & dict );
  float ApplyLinkedAssocs(
                          Dictionary & dict,
                          const Solarix::Word_Form * wf,
                          const lem::MCollect<WordAssociation*> & assocs,
                          const std::multimap<const Solarix::Word_Form *,const Solarix::Word_Form *> & edges_down,
                          const std::multimap<const Solarix::Word_Form *,const Solarix::Word_Form *> & edges_up,
                          std::set< std::pair<const Solarix::Word_Form *,const Solarix::Word_Form *> > & visited_edges,
                          std::set<const Solarix::Word_Form *> & processed_wf
                          #if defined SOL_DEBUGGING
                          , lem::MCollect<int> & scorer_id_src
                          #endif
                         ) const;

  float ApplyLinkedAssocs(
                          Dictionary & dict,
                          const Solarix::Word_Form * wf,
                          const Solarix::Word_Form * current_wf,
                          int current_distance,
                          const lem::MCollect<WordAssociation*> & assocs,
                          const std::multimap<const Solarix::Word_Form *,const Solarix::Word_Form *> & edges_down,
                          const std::multimap<const Solarix::Word_Form *,const Solarix::Word_Form *> & edges_up,
                          std::set< std::pair<const Solarix::Word_Form *,const Solarix::Word_Form *> > & visited_edges,
                          std::set<const Solarix::Word_Form *> & processed_wf
                          #if defined SOL_DEBUGGING
                          , lem::MCollect<int> & scorer_id_src
                          #endif
                         ) const;


  void ApplyTreeScorers(
                        SynGram &sg,
                        WordEntrySet &sets,
                        SynPatternResult & res
                       ) const;

  bool MatchTreeScorer(
                       SynGram &sg,
                       WordEntrySet &wordentry_sets,
                       int id_point,
                       const Solarix::Word_Form &node,
                       const SynPatternResult & res,
                       const TreeScorerApplicationContext & parent_context
                      ) const;

  bool MatchTreeScorer(
                       SynGram &sg,
                       WordEntrySet &wordentry_sets,
                       const TreeScorerPoint * scorer_leaf,
                       const Solarix::Word_Form &node,
                       const SynPatternResult & res,
                       const TreeScorerApplicationContext & parent_context
                      ) const;


 public:
  SynPatternTreeNodeMatchingResults();
  ~SynPatternTreeNodeMatchingResults();

  void ApplyTokenScores();

  void MergeResults( bool f ) { merge_results=f; }

  Res_Pack * BuildGrafs(
                        Dictionary &dict,
                        BasicLexer & lexer,
                        bool DoLinkNodes,
                        bool CompleteAnalysisOnly,
                        TrTrace *trace_log
                       );

  void Print( Dictionary & dict, lem::OFormatter & out ) const;

  void AddResult( SynPatternResult * r );
  void SetResults( const lem::MCollect<SynPatternResult*> & new_results );

  void FilterMaxCoverage();

  void Clear();
  bool empty() const { return results.empty(); }
};

}


#endif
