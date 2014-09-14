#if !defined GrafBuilder__H
#define GrafBuilder__H

#include <map>
#include <lem/containers.h>
#include <lem/solarix/PatternSynLinkedGroup.h>
#include <lem/solarix/PatternLinkEdge.h>

namespace Solarix {

class Word_Form;
class Tree_Node;

class GrafBuilder
{
 private:
  struct PatternSynLinkedGroup2
  {
   int index_begin, index_end;
   int root_node_index;

   PatternSynLinkedGroup2(void) : index_begin(UNKNOWN), index_end(UNKNOWN), root_node_index(UNKNOWN) {}
   PatternSynLinkedGroup2( int i0, int i1, int inode ) : index_begin(i0), index_end(i1), root_node_index(inode) {}
  };  

  struct PatternLinkEdge2
  {
   int index_from, index_to;
   int link_type;

   PatternLinkEdge2(void) : index_from(UNKNOWN), index_to(UNKNOWN), link_type(UNKNOWN) {}
   PatternLinkEdge2( int f, int l, int t ) : index_from(f), index_to(t), link_type(l) {}
  };

  lem::MCollect<PatternSynLinkedGroup2> linkage_groups;
  lem::MCollect<PatternLinkEdge2> linkage_edges;
  int i_end;

  typedef std::multimap< const Word_Form*, const PatternLinkEdge2* > FROM2EDGE;
  FROM2EDGE from2edge;

  typedef std::map< const Word_Form*, const PatternSynLinkedGroup2* > ROOT2GROUP;
  ROOT2GROUP root2group;

  lem::MCollect<PatternLinkEdge> prelinked_edges_1;
  lem::MCollect<PatternLinkEdge> prelinked_edges_2;

  std::map<const Word_Form*,const Word_Form*> new_wordform_2_old_wordform;


  void StoreLinkage(
                    const LINKAGE_GROUPS & groups,
                    const LINKAGE_EDGES & edges,
                    const std::map<const LexerTextPos*,int> & token2index,
                    const std::map< const Word_Form *, int > & version2index,
                    bool there_are_prelinked_nodes,
                    const lem::MCollect<Tree_Node*> & roots
                   );

  void BuildGraf( lem::MCollect<Tree_Node*> & roots, bool there_are_prelinked_nodes, bool reorder_tree );
  void BuildGrafForNode1( lem::MCollect<Tree_Node*> & roots, Tree_Node * root );
  void BuildGrafForNode2( lem::MCollect<Tree_Node*> & roots, Tree_Node * root );
  void BuildGrafForNode3( Tree_Node * node );
  void BuildGrafForNode4( Tree_Node * node, const Word_Form * old_child_wordform );


  void SortChildren( Tree_Node * root ) const;

  bool ignore_begin_end_tokens; // обычно true - и в граф не включаютс€ первый и последний токены, которые обычно €вл€ютс€ BEGIN и END.

 public:
  GrafBuilder(void);

  void BuildGraf(
                 const LINKAGE_GROUPS & groups,
                 const LINKAGE_EDGES & edges,
                 const std::map<const LexerTextPos*,int> & token2index,
                 const std::map< const Word_Form *, int > & version2index,
                 lem::MCollect<Tree_Node*> & roots,
                 bool there_are_prelinked_nodes,
                 bool reorder_tree
                );

  void IgnoreBeginEndTokens( bool f ) { ignore_begin_end_tokens=f; }
};


}
#endif
