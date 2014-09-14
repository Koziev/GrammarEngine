#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/tree_node.h>
#include <lem/solarix/GrafBuilder.h>

#if LEM_DEBUGGING==1
#include <lem/oformatter.h>
#include <lem/console_streams.h>
#endif

using namespace Solarix;

GrafBuilder::GrafBuilder(void):ignore_begin_end_tokens(true)
{}


namespace {
static void CollectNodes( const Tree_Node * node, std::set<const Tree_Node*> & nodes )
{
 nodes.insert( node );
 for( lem::Container::size_type i=0; i<node->leafs().size(); ++i )
  CollectNodes( & node->leafs()[i], nodes );

 return;
}
}

void GrafBuilder::BuildGraf(
                            const LINKAGE_GROUPS & groups,
                            const LINKAGE_EDGES & edges,
                            const std::map<const LexerTextPos*,int> & token2index,
                            const std::map< const Word_Form *, int > & version2index,
                            lem::MCollect<Tree_Node*> & roots,
                            bool there_are_prelinked_nodes,
                            bool reorder_tree
                           )
{
 lem::MCollect<Tree_Node*> old_roots( roots );

 i_end = CastSizeToInt(roots.size())-1;
 StoreLinkage( groups, edges, token2index, version2index, there_are_prelinked_nodes, roots );
 BuildGraf(roots,there_are_prelinked_nodes,reorder_tree);

 std::set<const Tree_Node*> linked_nodes;
 for( lem::Container::size_type i=0; i<roots.size(); ++i )
  CollectNodes( roots[i], linked_nodes );

 for( lem::Container::size_type i=0; i<old_roots.size(); ++i )
  {
   if( linked_nodes.find( old_roots[i] )==linked_nodes.end() )
    delete old_roots[i];
  }

 return;
}


void GrafBuilder::StoreLinkage(
                               const LINKAGE_GROUPS & groups,
                               const LINKAGE_EDGES & edges,
                               const std::map<const LexerTextPos*,int> & token2index,
                               const std::map< const Word_Form *, int > & version2index,
                               bool there_are_prelinked_nodes,
                               const lem::MCollect<Tree_Node*> & roots
                              )
{
 if( there_are_prelinked_nodes )
  {
   std::map<int,const Word_Form*> index2new_wordform;
   for( lem::Container::size_type i=1; i<roots.size()-1; ++i )
    {
     const Word_Form * new_wordform = & roots[i]->GetNode();
     index2new_wordform.insert( std::make_pair( CastSizeToInt(i), new_wordform ) );
    }

   // переход от старой словоформы к новой
   for( std::map< const Word_Form *, int >::const_iterator it=version2index.begin(); it!=version2index.end(); ++it )
    {
     const Word_Form * old_wordform = it->first;
     const int index = it->second;
     if( index2new_wordform.find(index) !=  index2new_wordform.end() )
      {
       const Word_Form * new_wordform = index2new_wordform.find(index)->second;
       new_wordform_2_old_wordform.insert( std::make_pair( new_wordform, old_wordform ) );
      }
    }
  }


 linkage_groups.reserve( groups.size() );
 linkage_edges.reserve( edges.size() );

 for( lem::Container::size_type i=0; i<groups.size(); ++i )
  {
   // Группа связывания по умолчанию включает в себя цепочку токенов (путь в графе токенизации)
   // от tok0 до tok1 (включительно).

   const LexerTextPos * tok0 = groups[i].begin;
   const LexerTextPos * tok1 = groups[i].end;
  
   if( token2index.find(tok0)!=token2index.end() && token2index.find(tok1)!=token2index.end() )
    {
     const int i0 = token2index.find(tok0)->second;
     const int i1 = token2index.find(tok1)->second;
 
     // Один из токенов в группе объявлен центральным, он станет локальным корнем.
     LEM_CHECKIT_Z( version2index.find( groups[i].root_node )!=version2index.end() );
     const int inode = version2index.find( groups[i].root_node )->second;
  
     // сразу уберем связки с терминаторами, так как они будут потом, при слиянии вариаторов-фрагментов,
     // искажать результат.
     if( tok0->IsBegin() || tok1->IsBegin() || inode==0 || tok0->IsEnd() || tok1->IsEnd() || inode==i_end )
      continue;
     
     PatternSynLinkedGroup2 g( i0, i1, inode );
     linkage_groups.push_back( g );
    }
  }

 for( lem::Container::size_type i=0; i<edges.size(); ++i )
  {
   typedef std::map< const Word_Form *, int >::const_iterator V2I_IT;

   V2I_IT it0 = version2index.find(edges[i].from);
   V2I_IT it1 = version2index.find(edges[i].to);

   if( it0==version2index.end() || it1==version2index.end() )
    {
     if( there_are_prelinked_nodes )
      {
       if( it0!=version2index.end() )
        {
         // связь от нормального узла к заранее привязанному.
         prelinked_edges_1.push_back( edges[i] );
        }
       else if( it0==version2index.end() && it1==version2index.end() )
        {
         prelinked_edges_2.push_back( edges[i] );
        }
       else
        {
         LEM_STOPIT;
        }
      }
     else
      {
       LEM_STOPIT;
      }
    }
   else
    {
     const int i0 = it0->second;
     const int i1 = it1->second;

     #if LEM_DEBUGGING==1
     //lem::mout->printf( "%us --> %us (%d --> %d)\n", edges[i].from->GetName()->c_str(), edges[i].to->GetName()->c_str(), i0, i1 );
     #endif

     if( ignore_begin_end_tokens && (i0==0 || i1==0 || i0==i_end || i1==i_end) )
      continue;

     PatternLinkEdge2 e( i0, edges[i].link_type, i1 );
     linkage_edges.push_back(e);
    }
  }

 return;
}




void GrafBuilder::BuildGraf( lem::MCollect<Tree_Node*> & roots, bool there_are_prelinked_nodes, bool reorder_trees )
{
 // Сначала построим граф по явно заданным ребрам linkage_edges. 

 const int size = CastSizeToInt(roots.size());

  // Подсчитаем число входящих и исходящих связей для каждого узла.
 lem::MCollect<int> in_links, out_links;
 in_links.resize( size ); in_links.Nullify();
 out_links.resize( size ); out_links.Nullify(); 

 // Заодно сделаем табличку для быстрого поиска ребер
 for( lem::Container::size_type i=0; i<linkage_edges.size(); ++i )
  {
   const int i_from = linkage_edges[i].index_from;
   if( (i_from!=i_end && i_from>0) || !ignore_begin_end_tokens )
    {
     out_links[i_from]++;
     from2edge.insert( std::make_pair( & roots[i_from]->GetNode() , & linkage_edges[i] ) );
    }

   const int i_to = linkage_edges[i].index_to;
   if( (i_to!=i_end && i_to>0) || !ignore_begin_end_tokens )
    in_links[i_to]++;
  }


 // Теперь идем по группам и тоже считаем входящие и выходящие связи, в данном случае - дефолтные.
 for( lem::Container::size_type i=0; i<linkage_groups.size(); ++i )
  {
   const PatternSynLinkedGroup2 & group = linkage_groups[i];

   const int i_from = group.root_node_index;
   if( i_from!=i_end && i_from>0 )
    {
     const Word_Form * root_node = & roots[ group.root_node_index ]->GetNode();
     out_links[i_from]++;
     root2group.insert( std::make_pair( root_node, &group ) );
    }
   
   for( int k=group.index_begin; k<=group.index_end; ++k )
    {
     const Word_Form * node = & roots[k]->GetNode();
     if( k!=i_from && k!=i_end && k>0 )
      in_links[k]++;
    }
  }

 // Теперь берем те токены, у которых вообще нет ни одной входящей связки - это АБСОЛЮТНЫЕ КОРНИ.
 // От них будем строить графы.
 // Первый и последние токены-терминаторы добавим без построения графа

 lem::MCollect<Tree_Node*> new_roots;
 for( int i=0; i<size; ++i )
  {
   Tree_Node *root = roots[i];

   if( ignore_begin_end_tokens && (i==0 || i==i_end) )
    new_roots.push_back( root );
   else if( in_links[i]==0 )
    {
     new_roots.push_back( root );
     roots[i] = NULL;
     BuildGrafForNode1( roots, root );
     BuildGrafForNode2( roots, root );

     if( there_are_prelinked_nodes )
      BuildGrafForNode3( root );

     if( reorder_trees )
      SortChildren( root ); // для стабилизации топологии отсортируем ветки в порядке возрастания индекса слова
    }
  }

 // Теперь перенесем графы в хранилище вариатора
 if( new_roots.empty() )
  {
   // вообще говоря, это неправильная ситуация. Можно либо бросить исключение, либо
   // оставить исходный набор токенов. Я пока решил оставить исходную цепочку токенов.
  }
 else
  roots = new_roots;

 return;
}


void GrafBuilder::SortChildren( Tree_Node * root ) const
{
 root->leafs().SortByWordIndex();
}


void GrafBuilder::BuildGrafForNode1( lem::MCollect<Tree_Node*> & roots, Tree_Node * root )
{
 // Сначала строим граф на явно заданных ребрах.

 typedef FROM2EDGE::const_iterator IT1;
 std::pair<IT1,IT1> pit1 = from2edge.equal_range( & root->GetNode() );
 for( IT1 it=pit1.first; it!=pit1.second; ++it )
  {
   const PatternLinkEdge2 * edge = it->second;
   const int index2 = edge->index_to;
   if( (index2>0 && index2<i_end) || !ignore_begin_end_tokens )
    {
     Tree_Node * child_node = roots[index2];

     LEM_CHECKIT_Z( child_node!=NULL );

     roots[index2] = NULL;

     child_node->SetLink( edge->link_type );
     root->Add( child_node );

     // Продолжаем построение графа вглубь.
     BuildGrafForNode1( roots, child_node );

     BuildGrafForNode3( child_node );
    }
  }

 return;
}

void GrafBuilder::BuildGrafForNode2( lem::MCollect<Tree_Node*> & roots, Tree_Node * root )
{
 // Достраиваем граф из дефолтных групп
 // Сначала идем вглубь
 for( lem::Container::size_type i=0; i<root->leafs().size(); ++i )
  {
   BuildGrafForNode2( roots, & root->leafs()[i] );
   //BuildGrafForNode3( & root->leafs()[i] );
  }

 // Прикрепляем к текущему узлу все, которые еще не прикреплены куда-нибудь и входят в группу связывания для этого узла
 ROOT2GROUP::const_iterator it = root2group.find( & root->GetNode() );
 if( it!=root2group.end() )
  {
   const PatternSynLinkedGroup2 * group = it->second;
   for( int k=group->index_begin; k<=group->index_end; ++k )
    {
     if( (k>0 && k<i_end) || !ignore_begin_end_tokens )
      {
       Tree_Node * child = roots[k];
       if( child!=NULL && child!=root )
        {
         root->Add( child );
         child->SetLink(UNKNOWN);
         roots[k]=NULL;
        }
      }
    }
  }   

 return;
}


void GrafBuilder::BuildGrafForNode3( Tree_Node * node )
{
 if( !prelinked_edges_1.empty() )
  {
   const Word_Form * new_wordform = & node->GetNode();

   std::map<const Word_Form*,const Word_Form*>::const_iterator it = new_wordform_2_old_wordform.find( new_wordform );
   LEM_CHECKIT_Z( it!=new_wordform_2_old_wordform.end() );

   const Word_Form * old_wordform = it->second;

   // Есть ли предварительные связывания для old_wordform?
   for( lem::Container::size_type i=0; i<prelinked_edges_1.size(); ++i )
    if( prelinked_edges_1[i].from == old_wordform )
     {
      const Word_Form * old_child_wordform = prelinked_edges_1[i].to;
      Word_Form * new_child_wf = new Word_Form( *old_child_wordform, true );
      Tree_Node * new_child = new Tree_Node( new_child_wf, true );
      new_child->SetLink( prelinked_edges_1[i].link_type );

      // и цепляем предварительные связывания для привязываемого узла - так как на стадии предварительного
      // связывания вполне могут быть цепочки из 3 токенов.
      BuildGrafForNode4( new_child, old_child_wordform );

      node->Add(new_child);
     }
  }

 return;
}

void GrafBuilder::BuildGrafForNode4( Tree_Node * node, const Word_Form * old_child_wordform )
{
 for( lem::Container::size_type i=0; i<prelinked_edges_2.size(); ++i )
  {
   if( prelinked_edges_2[i].from == old_child_wordform )
    {
     const Word_Form * old_child_wordform2 = prelinked_edges_2[i].to;

     Word_Form * new_child_wf2 = new Word_Form( *old_child_wordform2, true );
     Tree_Node * new_child2 = new Tree_Node( new_child_wf2, true );
     new_child2->SetLink( prelinked_edges_2[i].link_type );

     BuildGrafForNode4( new_child2, old_child_wordform2 );

     node->Add(new_child2);
    }
  }

 return;
}

