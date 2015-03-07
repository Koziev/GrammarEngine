#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/pm_functionloader.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/LA_WordEntrySet.h>
#include <lem/solarix/TreeScorerApplicationContext.h>
#include <lem/solarix/TreeScorer.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/TreeScorers.h>
#include <lem/solarix/TreeScorerGroupParams.h>
#include <lem/solarix/TreeScorerCall.h>
#include <lem/solarix/TreeScorerMatcher.h>

using namespace Solarix;

class LinkEdgeContainer_AllTrace : public LinkEdgeContainer
{
 private:
   lem::MCollect<PatternLinkEdge> edges;

 public:
  LinkEdgeContainer_AllTrace( 
                             const SynPatternResultBackTrace * x_result,
                             const SynPatternResult * cur_result
                            )
  {
   edges = cur_result->linkage_edges;

   const SynPatternResultBackTrace * p = x_result;
   while( p!=NULL )
   {
    if( p->result!=NULL )
     {
      for( lem::Container::size_type i=0; i<p->result->linkage_edges.size(); ++i )
       {
        if( edges.find( p->result->linkage_edges[i] )==UNKNOWN )
         edges.push_back( p->result->linkage_edges[i] );
       }
     }

    p = p->parent;
   }

   return;
  }

  virtual ~LinkEdgeContainer_AllTrace() {}
  virtual int size() const { return CastSizeToInt(edges.size()); }
  virtual const PatternLinkEdge& operator[]( int index ) const { return edges[index]; }
};



void TreeScorerMatcher::MatchRootByGroup(
                                         const Solarix::Word_Form * root_wf,
                                         int id_group,
                                         Dictionary & dict,
                                         const lem::MCollect<int> & PatternSequenceNumber,
                                         const SynPatternResultBackTrace * x_result,
                                         SynPatternResult * cur_result,
                                         KnowledgeBase & kbase,
                                         TreeMatchingExperience &experience,
                                         TreeScorerMatcher_Result & matching_result,
                                         const ElapsedTimeConstraint & constraints,
                                         TrTrace *trace_log
                                        )
{
 SynGram & sg = dict.GetSynGram();
 WordEntrySet & sets = dict.GetLexAuto().GetWordEntrySet();

 const TreeScorerGroupParams & params = dict.GetLexAuto().GetTreeScorers().GetGroupParams( id_group );

 lem::MCollect<int> headpoint_ids, is_root;
 lem::PtrCollect<TreeScorerResult> scores;
 sg.GetStorage().ListTreeScorers( id_group, *root_wf, headpoint_ids, scores, is_root );

 LEM_CHECKIT_Z( headpoint_ids.size() == scores.size() );
 LEM_CHECKIT_Z( headpoint_ids.size() == is_root.size() );

 // могут быть правила, не привязанные к содержимому корня, их загружаем отдельным вызовом.
 lem::MCollect<int> generic_headpoint_ids;
 lem::PtrCollect<TreeScorerResult> generic_scores;
 sg.GetStorage().ListGenericTreeScorers( id_group, generic_headpoint_ids, generic_scores );
 if( !generic_headpoint_ids.empty() )
  {
   for( lem::Container::size_type i=0; i<generic_headpoint_ids.size(); ++i )
    {
     headpoint_ids.push_back( generic_headpoint_ids[i] );
     scores.push_back( generic_scores[i] );
     generic_scores[i] = NULL;
     is_root.push_back(1);
    }
  }


 matching_result.rule_count=CastSizeToInt( headpoint_ids.size() );

/*
 #if LEM_DEBUGGING==1
 lem::mout->printf( "\nLINKS:\n" );
 cur_result->PrintLinks( *lem::mout, sg );
 lem::mout->eol();
 #endif
*/

 if( headpoint_ids.empty() )
  return;
 
 LinkEdgeContainer_AllTrace edges( x_result, cur_result );

 // Теперь каждое правило пытаемся сопоставить.
 for( lem::Container::size_type j=0; j<headpoint_ids.size(); ++j )
  {
   const int id_headpoint = headpoint_ids[j];
 
   if( is_root[j]  )
    {
     TreeScorerApplicationContext context(NULL);
     TreeScorerBoundVariables bound_variables;

     #if defined SOL_DEBUGGING
     const int id_src = dict.GetSynGram().GetStorage().GetTreeScorerHeadpointSrc(id_headpoint);
     
     const int dbg_mark = TrTraceActor::seq++;
     if( trace_log!=NULL )
      {
       trace_log->Enter( new TreeScorerCall( dbg_mark, id_src, edges ) );
      }

     #endif

     if( TreeScorerMatcher::MatchTreeScorer( sg, sets, id_headpoint, *root_wf, edges, context, params, bound_variables, constraints, trace_log ) )
      {
       scores[j]->Link( dict.GetLexAuto().GetFunctions().Get() );
       const int dscore = scores[j]->Calculate( dict, bound_variables, constraints, trace_log );
       matching_result.score += dscore;
       matching_result.matched = true;

       #if defined SOL_DEBUGGING
       SynPatternDebugTrace dbg;
       dbg.id_src_tree_scorer = id_src;
       dbg.ngram_freq = NGramScore(dscore);
       cur_result->debug_trace.push_back(dbg);
       #endif
      }

     #if defined SOL_DEBUGGING
     if( trace_log!=NULL )
      {
       trace_log->Leave( new TreeScorerCall( dbg_mark, id_src, edges ) );
      }
     #endif
    }
  }

 return;
}


bool TreeScorerMatcher::MatchTreeScorer(
                                        SynGram &sg,
                                        WordEntrySet &wordentry_sets,
                                        int id_point,
                                        const Solarix::Word_Form &node,
                                        const LinkEdgeContainer & edges,
                                        const TreeScorerApplicationContext & parent_context,
                                        const TreeScorerGroupParams & params,
                                        TreeScorerBoundVariables & bound_variables,
                                        const ElapsedTimeConstraint & constraints,
                                        TrTrace *trace_log
                                       )
{
 // Делаем полную тщательную проверку для текущего корня.
 lem::Ptr<TreeScorerPoint> p( sg.GetStorage().LoadTreeScorerPoint( id_point ) );

 return MatchTreeScorer( sg, wordentry_sets, p.get(), node, edges, parent_context, params, bound_variables, constraints, trace_log );
}



bool TreeScorerMatcher::MatchTreeScorer(
                                        SynGram &sg,
                                        WordEntrySet &wordentry_sets,
                                        const TreeScorerPoint * scorer_leaf,
                                        const Solarix::Word_Form &node,
                                        const LinkEdgeContainer & edges,
                                        const TreeScorerApplicationContext & parent_context,
                                        const TreeScorerGroupParams & params,
                                        TreeScorerBoundVariables & bound_variables,
                                        const ElapsedTimeConstraint & constraints,
                                        TrTrace *trace_log
                                       )
{
 if( !scorer_leaf->DoesMatch( sg, node, edges, parent_context, bound_variables ) )
  return false;

 if( scorer_leaf->IsNamedSubtree() )
  {
   const int id_group = scorer_leaf->GetNamedSubtreeGroupId();

   // id всех корней для входящих в эту группу
   lem::MCollect<int> group_roots;
   sg.GetStorage().ListTreeScoreGroupMembers( id_group, group_roots );

   // последовательно перебираем деревья до первого успеха.
   TreeScorerBoundVariables dummy_variables;
   bool matched=false;
   for( lem::Container::size_type i=0; i<group_roots.size(); ++i )
    {
     const int id_root = group_roots[i];

     lem::Ptr<TreeScorerPoint> sub_tree( sg.GetStorage().LoadTreeScorerPoint( id_root ) );

     bool m = MatchTreeScorer( sg, wordentry_sets, sub_tree.get(), node, edges, parent_context, params, dummy_variables, constraints, trace_log );
     if( m )
      {
       matched=true;
       break;
      }
    }

   if( !matched )
    return false;
  }

 if( !scorer_leaf->marker.empty() )
  bound_variables.AddVariable( scorer_leaf->marker, &node );

 if( scorer_leaf->HasLeaves() )
  {
/*
#if LEM_DEBUGGING==1
static int pass_count=0;
lem::mout->printf( "pass_count=%d\n", pass_count++ );
lem::mout->eol();
for( int i=0; i<edges.size(); ++i )
 {
  const Solarix::Word_Form &  wf_from = * edges[i].from;
  const Solarix::Word_Form & wf_to = * edges[i].to;
  lem::mout->printf( "%us <---> %us\n", wf_from.GetName()->c_str(), wf_to.GetName()->c_str() );
 }
#endif
*/

   TreeScorerApplicationContext new_context( &parent_context );
   if( scorer_leaf->relative_position!=UNKNOWN )
    new_context.StoreMatchedPosition( node, scorer_leaf->relative_position );

   // Порядок веток не фиксирован, поэтому придется делать подбор сочетания.
   lem::MCollect<const Solarix::Word_Form*> leafs;
   lem::MCollect<int> link_types;

   for( int i=0; i<edges.size(); ++i )
    {
     if( edges[i].from == & node )
      {
       #if LEM_DEBUGGING==1
       const Solarix::Word_Form & wf_to = * edges[i].to;
       #endif
       leafs.push_back( edges[i].to );
       link_types.push_back( edges[i].link_type );
      }
    }

   bool leaf_count_check=false;
   const int N = CastSizeToInt(leafs.size());
   if( params.allow_unmatched_children )
    {
     leaf_count_check = N >= scorer_leaf->children_quantification.GetMinCount();
    }
   else
    {
     leaf_count_check = N >= scorer_leaf->children_quantification.GetMinCount() &&
                        N <= scorer_leaf->children_quantification.GetMaxCount();
    }

   // Если нам нужно сопоставить больше веток, чем есть в наличии - сразу провал.
   if( !leaf_count_check )
    return false;

   lem::MCollect<TreeScorerPoint*> scorer_leafs;
   sg.GetStorage().LoadTreeScorerChildNodes( scorer_leaf->GetId(), scorer_leafs );

   lem::MCollect<int> scorer_leaf_remaining_count;
   for( lem::Container::size_type k=0; k<scorer_leafs.size(); ++k )
    {
     if( scorer_leafs[k]->quantification.IsNot() )
      scorer_leaf_remaining_count.push_back( -1 );
     else
      scorer_leaf_remaining_count.push_back( scorer_leafs[k]->quantification.GetMaxCount() );
    }

   bool all_matched=true;

   // особым образом проверяем "предикат существования" любой ветки
   if( scorer_leafs.size()==1 && scorer_leafs.front()->quantification.IsNot() )
    {
     if( scorer_leafs.front()->IsAny() && !scorer_leafs.front()->HasConstraints() && !scorer_leafs.front()->HasLeaves() )
      {
       // не должно быть вообще ни одной ветки

       if( !leafs.empty() )
        {
         if( scorer_leafs.front()->relative_position!=UNKNOWN )
          {
           for( lem::Container::size_type j=0; j<leafs.size(); ++j )
            {
             const Word_Form * leaf_token = leafs[j];
             // проверим, что позиция словоформы version не вступает в противоречие с позициями ранее отмеченных токенов.
             if( !parent_context.CheckPosition( *leaf_token, scorer_leafs.front()->relative_position ) )
              {
               all_matched=false;
               break;
              }
            }
          }
         else
          {
           all_matched=false;
          }
        }
      }
     else
      {
       // не должно быть ни одной ветки, подходящей под условия
       TreeScorerBoundVariables dummy_variables;

       for( lem::Container::size_type j=0; j<leafs.size(); ++j )
        if( scorer_leafs.front()->link_type==UNKNOWN || link_types[j]==scorer_leafs.front()->link_type )
         {
          const bool matched = MatchTreeScorer( sg, wordentry_sets, scorer_leafs.front(), *leafs[j], edges, new_context, params, dummy_variables, constraints, trace_log );
          if( matched )
           {
            all_matched=false;
            break;
           }
         }
      }
    }
   else
    {
     for( lem::Container::size_type k=0; k<scorer_leafs.size(); ++k )
      {
       const TreeScorerPoint * scorer_leaf = scorer_leafs[k];
  
       bool leaf_matched=scorer_leaf->quantification.GetMinCount()==0;
      
       for( lem::Container::size_type j=0; j<leafs.size(); ++j )
        if( leafs[j]!=NULL )
         {
          if( scorer_leaf->link_type==UNKNOWN || link_types[j]==scorer_leaf->link_type )
           {
            const bool matched = MatchTreeScorer( sg, wordentry_sets, scorer_leaf, *leafs[j], edges, new_context, params, bound_variables, constraints, trace_log );
            if( scorer_leaf->quantification.IsNot() )
             {
              if( matched )
               {
                leaf_matched=false;
                break;
               }
             }
            else if( matched )
             {
              if( scorer_leaf->relative_position!=UNKNOWN )
               {
                new_context.StoreMatchedPosition( *leafs[j], scorer_leaf->relative_position );
               }

              leafs[j]=NULL; // больше эта ветка не будет сопоставляться
              leaf_matched=true;
      
              scorer_leaf_remaining_count[k]--; // гасим валентность.
      
              // ветка полностью исчерпана?
              if( scorer_leaf_remaining_count[k]==0 )
               break;
             }
           }
         }
      
       if( !leaf_matched )
        {
         all_matched=false;
         break;
        }
      }
    }

   // если нужно, то проверим, что все ветки сопоставлены
   if( all_matched && !params.allow_unmatched_children )
    for( lem::Container::size_type j=0; j<leafs.size(); ++j )
     if( leafs[j]!=NULL )
      {
       all_matched=false;
       break;
      }

   if( all_matched )
    {
     all_matched = new_context.CheckRelativePositions();
    }

   for( lem::Container::size_type j=0; j<scorer_leafs.size(); ++j )
    delete scorer_leafs[j];

   if( !all_matched )
    return false;
  }

 return true;
}
