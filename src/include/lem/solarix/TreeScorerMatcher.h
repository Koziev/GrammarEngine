#if !defined TreeScorerMatcher__H
#define TreeScorerMatcher__H

namespace Solarix
{
 class TreeScorerApplicationContext;
 class KnowledgeBase;
 class TreeMatchingExperience;
 struct TreeScorerGroupParams;

 struct TreeScorerMatcher_Result
 {
  bool matched;
  int rule_count;
  int score;

  TreeScorerMatcher_Result() : matched(false), rule_count(0), score(0) {}
 };

 class TreeScorerBoundVariables;
 class TreeScorerMatcher
 {
  private:
   TreeScorerMatcher() {}

  public:
   static bool MatchTreeScorer(
                               SynGram &sg,
                               WordEntrySet &wordentry_sets,
                               int id_point,
                               const Solarix::Word_Form &node,
                               const LinkEdgeContainer & edges,
                               const TreeScorerApplicationContext & parent_context,
                               const TreeScorerGroupParams & params,
                               TreeScorerBoundVariables & bound_variables
                              );

   static bool MatchTreeScorer(
                               SynGram &sg,
                               WordEntrySet &wordentry_sets,
                               const TreeScorerPoint * scorer_leaf,
                               const Solarix::Word_Form &node,
                               const LinkEdgeContainer & edges,
                               const TreeScorerApplicationContext & parent_context,
                               const TreeScorerGroupParams & params,
                               TreeScorerBoundVariables & bound_variables
                              );

   static void MatchRootByGroup(
                                const Solarix::Word_Form * root_wf,
                                int id_group,
                                Dictionary & dict,
                                const lem::MCollect<int> & PatternSequenceNumber,
                                const SynPatternResultBackTrace * x_result,
                                SynPatternResult * cur_result,
                                KnowledgeBase & kbase,
                                TreeMatchingExperience &experience,
                                TreeScorerMatcher_Result & result,
                                TrTrace *trace_log
                               );
 };
}

#endif
