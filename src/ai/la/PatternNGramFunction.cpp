#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/KnowledgeBase.h>
#include <lem/solarix/TreeMatchingExperience.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/TreeScorerMatcher.h>
#include <lem/solarix/TreeScorers.h>
#include <lem/solarix/PatternNGrams.h>

using namespace Solarix;


PatternNGramFunction::PatternNGramFunction(void) : missing_score(0), id_group(UNKNOWN)
{
}

PatternNGramFunction::PatternNGramFunction( const PatternNGramFunction & x )
 : root_marker(x.root_marker), group_name(x.group_name), id_group(x.id_group), missing_score(x.missing_score)
{
}

void PatternNGramFunction::operator=( const PatternNGramFunction & x )
{
 root_marker = x.root_marker;
 group_name = x.group_name;
 id_group = x.id_group;
 missing_score = x.missing_score;
}

bool PatternNGramFunction::operator!=( const PatternNGramFunction & x ) const
{
 return root_marker!=x.root_marker || id_group!=x.id_group || missing_score!=x.missing_score;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternNGramFunction::LoadTxt(
                                   int id_group0,
                                   Dictionary &dict,
                                   lem::Iridium::Macro_Parser & txtfile,
                                   VariableChecker & compilation_context
                                  )
{
 lem::Iridium::BSourceState beg = txtfile.tellp();

 if( id_group0==UNKNOWN )
  txtfile.read_it( L"tree_score" );

 txtfile.read_it( B_OROUNDPAREN );

 root_marker = txtfile.read().string();
 root_marker.to_upper();
 if( compilation_context.Find(root_marker)==UNKNOWN )
  {
   dict.GetIO().merr().printf( "Variable [%us] is not declared", root_marker.c_str() );
   lem::Iridium::Print_Error(beg,txtfile);
   throw lem::E_BaseException();
  }

 if( id_group0==UNKNOWN )
  {
   txtfile.read_it( B_COMMA );

   group_name = txtfile.read().string();
   group_name.to_upper();

   id_group = dict.GetLexAuto().GetTreeScorers().FindGroup( group_name, true );
   if( id_group==UNKNOWN )
    {
     dict.GetIO().merr().printf( "Tree scorer group [%us] not found", group_name.c_str() );
     lem::Iridium::Print_Error(beg,txtfile);
     throw lem::E_BaseException();
    }
  }
 else
  {
   id_group=id_group0;
  }

 if( txtfile.probe( B_COMMA ) )
  {
   txtfile.read_it( B_SUB );
   missing_score = -txtfile.read_int();
  }

 txtfile.probe(B_CROUNDPAREN);

 return; 
}
#endif    

void PatternNGramFunction::SaveBin( lem::Stream &bin ) const
{
 bin.write( &root_marker, sizeof(root_marker) );
 bin.write( &group_name, sizeof(group_name) );
 bin.write_int( id_group );
 bin.write_int( missing_score );
 return; 
}

void PatternNGramFunction::LoadBin( lem::Stream &bin )
{
 bin.read( &root_marker, sizeof(root_marker) );
 bin.read( &group_name, sizeof(group_name) );
 id_group = bin.read_int();
 missing_score = bin.read_int();
 return;
}



#if defined SOL_CAA
const Solarix::Word_Form* PatternNGramFunction::GetRootNode(
                                                            Dictionary & dict,
                                                            const lem::MCollect<int> & PatternSequenceNumber,
                                                            const SynPatternResult * cur_result
                                                           ) const
{
 if( !cur_result->trace.Contains(PatternSequenceNumber,root_marker) )
  {
   lem::MemFormatter mem;
   mem.printf( "Can not find root node marker [%us]", root_marker.c_str() );
   throw lem::E_BaseException( mem.string() );
   return 0;
  }

 const BackTraceItem & mark_data = *cur_result->trace.Get(PatternSequenceNumber,root_marker);

 if( mark_data.IsSingleWord() )
  {
   const Word_Form * root_node = mark_data.GetSingleRootNode();
   return root_node;
  }
 else
  {
   // сначала пробуем найти токен с пометкой root_node.
   const Word_Form * root_node0 = mark_data.FindNode( * dict.GetLexAuto().GetRootNodeName() );
   if( root_node0!=NULL )
    {
     return root_node0;
    }
   else
    {
     // В качестве центрального берем первый токен.
     const LexerTextPos * token = mark_data.GetBeginToken();
     const Solarix::Word_Form * root_node = token->GetWordform();
     return root_node;
    }
  }

 LEM_STOPIT;
 return NULL;
}
#endif


#if defined SOL_CAA
int PatternNGramFunction::Match(
                                Dictionary & dict,
                                const lem::MCollect<int> & PatternSequenceNumber,
                                const SynPatternResultBackTrace * x_result,
                                SynPatternResult * cur_result,
                                KnowledgeBase & kbase,
                                TreeMatchingExperience &experience,
                                TrTrace *trace_log
                               ) const
{
/*
 #if LEM_DEBUGGING==1
 lem::mout->eol();
 cur_result->PrintLinks( *lem::mout, dict.GetSynGram() );
 lem::mout->eol();

 const SynPatternResultBackTrace * p = x_result;
 while( p!=NULL )
 {
  if( p->result!=NULL )
   {
    if( !p->result->linkage_edges.empty() )
     {
      lem::mout->eol();
      p->result->PrintLinks( *lem::mout, dict.GetSynGram() );
      lem::mout->eol();
     }
   }

  p = p->parent;
 }
 #endif
*/

 // ищем корень и делаем оценку от него с помощью заданной группы оценщиков.
 const Solarix::Word_Form * root_wf = GetRootNode( dict, PatternSequenceNumber, cur_result );

 TreeScorerMatcher_Result matching_result;
 TreeScorerMatcher::MatchRootByGroup( root_wf, id_group, dict, PatternSequenceNumber, x_result, cur_result, kbase, experience, matching_result, trace_log );
 
 if( matching_result.matched )
  return matching_result.score;
 else
  {
   if( matching_result.rule_count>0 ) // были ли найдены правила, проверяющие данное дерево?
    return missing_score;
   else
    return 0;
  }
}
#endif
