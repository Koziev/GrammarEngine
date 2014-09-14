#include <lem/macro_parser.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/TreeScorers.h>
#include <lem/solarix/WordEntrySetItem.h>
#include <lem/solarix/WordSetItem.h>
#include <lem/solarix/TreeScorer.h>

using namespace Solarix;

TreeScorer::TreeScorer() : id_language(UNKNOWN), id_group(UNKNOWN), generic(false)
{
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void TreeScorer::LoadTxt( Dictionary & dict, lem::Iridium::Macro_Parser & txtfile, WordEntrySet & sets, TreeScorers & scorers )
{
 // ќпционально может быть им€ - если это не scorer верхнего уровн€, а вызываемый по имени член группы.
 if( !txtfile.probe( B_LANGUAGE ) )
  {
   lem::Iridium::BethToken t_group = txtfile.read();
   id_group = scorers.FindGroup( t_group.string(), false );
   if( id_group==UNKNOWN )
    {
     lem::Iridium::Print_Error(t_group,txtfile);
     dict.GetIO().merr().printf( "Unknown group name %us\n", t_group.string().c_str() );
     throw lem::E_BaseException();
    }

   txtfile.read_it( B_LANGUAGE );
   txtfile.read_it( B_EQUAL );
  }
 else
  {
   txtfile.read_it( B_EQUAL );
  }

 // ƒл€ каждого правила нужно задать целевой €зык, чтобы правильно
 // распознать словарные статьи в опорных точках.
 lem::Iridium::BethToken lang = txtfile.read();
 id_language = dict.GetSynGram().Find_Language(lang.string());
 if( id_language==UNKNOWN )
  {
   lem::Iridium::Print_Error(lang,txtfile);
   dict.GetIO().merr().printf( "Unknown language name %us\n", lang.c_str() );
   throw lem::E_BaseException();
  }

 // в особых случа€х полезно использовать не прив€занные к конкретному селектору правила, в этом
 // случае надо €вно указать ключевое слово "generic".
 generic = txtfile.probe(L"generic");

 txtfile.read_it( B_OFIGPAREN );

 txtfile.read_it( B_IF );

 lem::Iridium::BSourceState root_pos = txtfile.tellp();

 // ѕолноценное дерево с произвольной иерархией узлов
 TreeScorerMarkers markers;
 txtfile.read_it( B_CONTEXT );
 txtfile.read_it( B_OFIGPAREN );
 root.LoadTxt_Tree( dict, txtfile, *this, sets, scorers, markers );
 txtfile.read_it( B_CFIGPAREN );
 

 // хот€ бы один узел в дереве должен быть задан однозначно, а не квантором, иначе
 // перебор деревьев станет очень т€желым.
 if( !generic && (id_group==UNKNOWN && root.FindNonQuantorNode()==NULL) )
  {
   lem::Iridium::Print_Error(root_pos,txtfile);
   dict.GetIO().merr().printf( "At least one node in tree scorer must be either an explicit word or word entry\n" );
   throw lem::E_BaseException();
  }

 // теперь читаем вес этого правила.
 txtfile.read_it( B_THEN );

 score.LoadTxt( dict, txtfile, markers );

 txtfile.read_it( B_CFIGPAREN );

 return;
}
#endif




void TreeScorer::Save( LexiconStorage & storage )
{
 const int id_root = root.Store(storage,UNKNOWN);

 if( IsNamedGroup() )
  {
   // запомним, что в данную группу id_group входит поддерево с корнем id_root
   storage.StoreTreeScoreGroupMember( id_group, id_root );
  }

 if( !generic )
  {
   if( root.IsWord() )
    storage.RegisterTreeScorer_Word( root.GetWord(), id_root, score.SerializeExpression(), score.GetExpressionType(), true, id_group );
   else if( root.IsEntry() && root.GetEntryKey()!=ANY_STATE )
    storage.RegisterTreeScorer_Wordentry( root.GetEntryKey(), id_root, score.SerializeExpression(), score.GetExpressionType(), true, id_group );
   else if( root.IsMetaEntry() )
    {
     // получим список статей, которые вход€т в метастатью.
     lem::MCollect<int> entries;
     storage.GetMetaEntryItems( root.GetMetaEntryKey(), entries );
     for( lem::Container::size_type i=0; i<entries.size(); ++i )
      storage.RegisterTreeScorer_Wordentry( entries[i], id_root, score.SerializeExpression(), score.GetExpressionType(), true, id_group );
    }
   else if( root.IsWordentrySet() )
    {
     lem::Ptr<WordEntrySetItem> s( storage.GetWordEntrySet( storage.FindWordEntrySet(root.GetSetName()) ) );

     const std::set<int> & ids = s->GetIDs();
     for( std::set<int>::const_iterator it=ids.begin(); it!=ids.end(); ++it )
      storage.RegisterTreeScorer_Wordentry( *it, id_root, score.SerializeExpression(), score.GetExpressionType(), true, id_group );
    }
   else if( root.IsWordSet() )
    {
     lem::Ptr<WordSetItem> s( storage.GetWordSet( storage.FindWordSet(root.GetSetName()) ) );

     const std::set<lem::UCString> & words = s->GetWords();

     for( std::set<lem::UCString>::const_iterator it=words.begin(); it!=words.end(); ++it )
      storage.RegisterTreeScorer_Word( *it, id_root, score.SerializeExpression(), score.GetExpressionType(), true, id_group );
    }
   else
    {
     const TreeScorerPoint * anchor_node = root.FindNonQuantorNode();

     if( anchor_node!=NULL )
      {
       if( anchor_node->IsWord() )
        storage.RegisterTreeScorer_Word( anchor_node->GetWord(), id_root, score.SerializeExpression(), score.GetExpressionType(), false, id_group );
       else if( anchor_node->IsEntry() && anchor_node->GetEntryKey()!=ANY_STATE )
        storage.RegisterTreeScorer_Wordentry( anchor_node->GetEntryKey(), id_root, score.SerializeExpression(), score.GetExpressionType(), false, id_group );
       else if( anchor_node->IsMetaEntry() )
        {
         // получим список статей, которые вход€т в метастатью.
         lem::MCollect<int> entries;
         storage.GetMetaEntryItems( anchor_node->GetMetaEntryKey(), entries );
         for( lem::Container::size_type i=0; i<entries.size(); ++i )
          storage.RegisterTreeScorer_Wordentry( entries[i], id_root, score.SerializeExpression(), score.GetExpressionType(), false, id_group );
        }
       else
        LEM_STOPIT;
      }
    }
  }
 else
  {
   storage.RegisterTreeScorer_Generic( id_root, score.SerializeExpression(), score.GetExpressionType(), id_group );
  }

 return;
}
