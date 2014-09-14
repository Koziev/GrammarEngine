#include <lem/solarix/PatternSynLinkedGroup.h>
#include <lem/solarix/SynPatternResult.h>
#include <lem/solarix/BackTraceItem.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/PatternLinks.h>

using namespace Solarix;


PatternDefaultLinkage::PatternDefaultLinkage(void):optional_node(false)
{}


PatternDefaultLinkage::PatternDefaultLinkage( const lem::UCString &marker, const lem::UCString &node, bool optional )
 : optional_node(optional), marker_name(marker), node_name(node)
{}


void PatternDefaultLinkage::SaveBin( lem::Stream &bin ) const
{
 bin.write_bool(optional_node);
 bin.write( &marker_name, sizeof(marker_name) );
 bin.write( &node_name, sizeof(node_name) );
 return;
}


void PatternDefaultLinkage::LoadBin( lem::Stream &bin )
{
 optional_node = bin.read_bool();
 bin.read( &marker_name, sizeof(marker_name) );
 bin.read( &node_name, sizeof(node_name) );
 return;
}



#if defined SOL_CAA
void PatternDefaultLinkage::Generate( const LexicalAutomat & la, const lem::MCollect<int> & PatternSequenceNumber, SynPatternResult * cur_result ) const
{
 if( optional_node && !cur_result->trace.Contains(PatternSequenceNumber,marker_name) )
  return;

 const BackTraceItem & mark_data = *cur_result->trace.Get(PatternSequenceNumber,marker_name);

 if( mark_data.IsSingleWord() )
  return;

 if( node_name.empty() )
  {
   // сначала пробуем найти токен с пометкой root_node.
   const Word_Form * root_node0 = mark_data.FindNode( *la.GetRootNodeName() );
   if( root_node0!=NULL )
    {
     PatternSynLinkedGroup new_group( mark_data.GetBeginToken(), mark_data.GetEndToken(), root_node0 );

     if( cur_result->FindLinkageGroup(mark_data.GetBeginToken(),mark_data.GetEndToken())==UNKNOWN )
      cur_result->AddLinkageGroup( new_group );
    }
   else
    {
     // В качестве центрального берем первый токен.
     const LexerTextPos * begin_token = mark_data.GetBeginToken();
     const Solarix::Word_Form * root_node = begin_token->GetWordform();
  
     PatternSynLinkedGroup new_group( mark_data.GetBeginToken(), mark_data.GetEndToken(), root_node );

     if( cur_result->FindLinkageGroup(mark_data.GetBeginToken(),mark_data.GetEndToken())==UNKNOWN )
      cur_result->AddLinkageGroup( new_group );
    }
  }
 else
  {
   // Центральный узел указан явно.

   const Word_Form * root_node = mark_data.FindNode(node_name);
   LEM_CHECKIT_Z( root_node!=NULL );
   PatternSynLinkedGroup new_group( mark_data.GetBeginToken(), mark_data.GetEndToken(), root_node );

   if( cur_result->FindLinkageGroup(mark_data.GetBeginToken(),mark_data.GetEndToken())==UNKNOWN )
    cur_result->AddLinkageGroup( new_group );
  }
 

 return;
}
#endif
