using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace ParserTreeViewer
{

 class SToken
 {
  public int index;
  public string word;
  public string lemma;
  public string part_of_speech;
  public List<string> tags;

  public SToken( int _index, XmlNode n_token )
  {
   index = _index;
   word = n_token.SelectSingleNode( "word" ).InnerText;
   lemma = n_token.SelectSingleNode( "lemma" ).InnerText;

   if( n_token.SelectSingleNode( "part_of_speech" ) != null )
    part_of_speech = n_token.SelectSingleNode( "part_of_speech" ).InnerText;

   tags = new List<string>();
   if( n_token.SelectSingleNode( "tags" ) != null )
   {
    tags.AddRange( n_token.SelectSingleNode( "tags" ).InnerText.Split( '|' ) );
   }
  }

  public override string ToString()
  {
   return word;
  }
 }

 class SNode
 {
  public int index;
  public SToken word;
  public SNode parent;
  public List<string> edge_types = new List<string>();
  public List<SNode> children = new List<SNode>();

  public bool children_vector_ready = false;
  public bool parent_vector_ready = false;

  public override string ToString()
  {
   return word.ToString();
  }


  public void WriteCorpus( System.IO.StreamWriter wrt, string edge_type )
  {
   wrt.WriteLine( "<node>" );

   wrt.WriteLine( "<word>{0}</word>", word.word );

   if( !string.IsNullOrEmpty( edge_type ) )
   {
    wrt.WriteLine( "<link>{0}</link>", edge_type );
   }

   wrt.WriteLine( "<tag_sets>" );
   wrt.WriteLine( "<tag_set>" );
   wrt.WriteLine( "<part_of_speech>{0}</part_of_speech>", word.part_of_speech );

   foreach( string t in word.tags )
   {
    string[] t2 = t.Split( ':' );

    if( word.part_of_speech == "ГЛАГОЛ" )
    {
     if( "НАКЛОНЕНИЕ ВРЕМЯ ЛИЦО ЧИСЛО РОД".Contains( t2[0] ) )
      wrt.WriteLine( "<tag>{0}</tag>", t );
    }
    else if( word.part_of_speech == "СУЩЕСТВИТЕЛЬНОЕ" )
    {
     if( "ПАДЕЖ ЧИСЛО РОД".Contains( t2[0] ) )
      wrt.WriteLine( "<tag>{0}</tag>", t );
    }
    else if( word.part_of_speech == "МЕСТОИМЕНИЕ" )
    {
     if( "ПАДЕЖ ЧИСЛО РОД ЛИЦО".Contains( t2[0] ) )
      wrt.WriteLine( "<tag>{0}</tag>", t );
    }
    else if( word.part_of_speech == "ЧИСЛИТЕЛЬНОЕ" )
    {
     if( "ПАДЕЖ РОД".Contains( t2[0] ) )
      wrt.WriteLine( "<tag>{0}</tag>", t );
    }
    else if( word.part_of_speech == "МЕСТОИМ_СУЩ" )
    {
     if( "ПАДЕЖ".Contains( t2[0] ) )
      wrt.WriteLine( "<tag>{0}</tag>", t );
    }
    else if( word.part_of_speech == "ПРИЛАГАТЕЛЬНОЕ" )
    {
     if( "ПАДЕЖ ЧИСЛО РОД ОДУШ ФОРМА СТЕПЕНЬ".Contains( t2[0] ) )
      wrt.WriteLine( "<tag>{0}</tag>", t );
    }
    else if( word.part_of_speech == "НАРЕЧИЕ" )
    {
     if( "СТЕПЕНЬ".Contains( t2[0] ) )
      wrt.WriteLine( "<tag>{0}</tag>", t );
    }
   }

   wrt.WriteLine( "</tag_set>" );
   wrt.WriteLine( "</tag_sets>" );

   if( children != null && children.Count > 0 )
   {
    wrt.WriteLine( "<children>" );

    List<KeyValuePair<int, int>> index = new List<KeyValuePair<int, int>>();
    for( int i = 0; i < children.Count; ++i )
    {
     index.Add( new KeyValuePair<int, int>( i, children[i].word.index ) );
    }

    foreach( var i in index.OrderBy( z => z.Value ) )
    {
     children[i.Key].WriteCorpus( wrt, edge_types[i.Key] );
    }

    wrt.WriteLine( "</children>" );
   }

   wrt.WriteLine( "</node>" );
  }

 }





 class Sentence
 {
  string text;
  List<SToken> tokens;
  public SNode root;
  List<SNode> nodes;

  public Sentence( XmlNode n_sent )
  {
   text = n_sent.SelectSingleNode( "text" ).InnerText;

   // токены
   tokens = new List<SToken>();
   int token_index = 0;
   foreach( XmlNode n_token in n_sent.SelectNodes( "tokens/token" ) )
   {
    SToken t = new SToken( token_index, n_token );
    tokens.Add( t );
    token_index++;
   }

   // дерево зависимостей
   List<int> root_index = new List<int>();
   Dictionary<int, int> child2parent = new Dictionary<int, int>();
   Dictionary<KeyValuePair<int, int>, string> edge_type = new Dictionary<KeyValuePair<int, int>, string>();
   Dictionary<int, List<int>> parent2child = new Dictionary<int, List<int>>();

   foreach( XmlNode n_token in n_sent.SelectNodes( "syntax_tree/node" ) )
   {
    int child_index = int.Parse( n_token["token"].InnerText );

    if( n_token.Attributes["is_root"] != null && n_token.Attributes["is_root"].Value == "true" )
     root_index.Add( child_index );
    else
    {
     int parent_index = int.Parse( n_token["parent"].InnerText );
     child2parent.Add( child_index, parent_index );

     edge_type.Add( new KeyValuePair<int, int>( child_index, parent_index ), n_token["link_type"].InnerText );

     List<int> child_idx;
     if( !parent2child.TryGetValue( parent_index, out child_idx ) )
     {
      child_idx = new List<int>();
      parent2child.Add( parent_index, child_idx );
     }

     child_idx.Add( child_index );
    }
   }

   nodes = new List<SNode>();
   for( int inode = 0; inode < tokens.Count; ++inode )
   {
    SNode n = new SNode();
    n.index = inode;
    n.word = tokens[inode];
    nodes.Add( n );
   }

   // проставим родителей и детей в каждом узле
   for( int inode = 0; inode < nodes.Count; ++inode )
   {
    SNode node = nodes[inode];

    if( !root_index.Contains( node.index ) )
    {
     SNode parent_node = nodes[child2parent[node.index]];
     node.parent = parent_node;

     parent_node.children.Add( node );
     parent_node.edge_types.Add( edge_type[new KeyValuePair<int, int>( node.index, parent_node.index )] );
    }
    else
    {
     root = node;
    }
   }
  }

  public string GetText()
  {
   return text;
  }


  public override string ToString()
  {
   return text;
  }

  public SNode GetNodeByIndex( int index )
  {
   return nodes[index];
  }

 }
}
