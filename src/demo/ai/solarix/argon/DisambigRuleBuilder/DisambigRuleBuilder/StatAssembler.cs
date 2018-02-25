using System;
using System.Collections.Generic;
using System.Linq;


class WordformKEY
{
 public int id_entry;
 public string wordform;

 public override int GetHashCode()
 {
  return id_entry ^ wordform.GetHashCode();
 }

 public override bool Equals( object obj )
 {
  WordformKEY k = (WordformKEY)obj;
  return id_entry == k.id_entry && wordform == k.wordform;
 }
}


class NodeDistance
{
 public SolarixGrammarEngineNET.SyntaxTreeNode token;
 public int distance;
}

class WordentryDistance
{
 public int id_entry1 = -1, id_entry2 = -1;
 public int sum_distance = 0, sum_distance2 = 0, N;
 public WordentryDistance() { }

 public override int GetHashCode()
 {
  return id_entry1 ^ ( id_entry2 << 8 );
 }

 public override bool Equals( object obj )
 {
  WordentryDistance y = (WordentryDistance)obj;
  return id_entry1 == y.id_entry1 && id_entry2 == y.id_entry2;
 }
}

class StatAssembler
{
 Dictionary<string, int> sample2count;

 Dictionary<WordentryDistance, WordentryDistance> distance_matrix = new Dictionary<WordentryDistance, WordentryDistance>();

 Dictionary<int, int> edge_len2count = new Dictionary<int, int>();

 int word_count = 0;
 Dictionary<WordformKEY, int> wordform_stat;
 Dictionary<int, int> wordentry_stat;
 int max_depth = 0;
 string max_depth_sentence = string.Empty;

 int MIN_SEMATAG_FREQ=1;

 public bool WordEntryOnly = true;

 public StatAssembler()
 {
  wordform_stat = new Dictionary<WordformKEY, int>();
  wordentry_stat = new Dictionary<int, int>();
  sample2count = new Dictionary<string, int>();
 }


 public void ChangeModelParams( List<string> model_params )
 {
  foreach( string p in model_params )
  {
   string[] tx = p.Split( '=' );
   string pname = tx[0].Trim();
   string pval = tx[1].Trim();

   switch( pname.ToUpper() )
   {
    case "MIN_SEMATAG_FREQ": MIN_SEMATAG_FREQ = int.Parse( pval ); break;
    default: throw new ApplicationException( string.Format( "Unknown model param {0}={1}", pname, pval ) );
   }
  }
 }


 public SolarixGrammarEngineNET.GrammarEngine2 gren;
 public void LoadDictionary( string filepath )
 {
  gren = new SolarixGrammarEngineNET.GrammarEngine2();
  gren.Load( filepath, false );
  return;
 }

 int LanguageID = -1;
 public void SetLanguage( int id ) { LanguageID = id; }

 public bool ProcessSample( SampleData line )
 {
  if( WordEntryOnly )
  {
   return ProcessSample_WordEntryOnly( line );
  }
  else
  {
   return ProcessSample_Complete( line );
  }
 }

 public bool ProcessSample_WordEntryOnly( SampleData sample )
 {
  if( sample.morphology == null )
   sample.morphology = gren.AnalyzeMorphology( sample.sample, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY );

  for( int iword = 1; iword < sample.morphology.Count - 1; ++iword )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode token = sample.morphology[iword];
   string word = token.GetWord().ToLower();

   int id_entry = token.GetEntryID();

   int f;
   if( wordentry_stat.TryGetValue( id_entry, out f ) )
    wordentry_stat[id_entry] = f + 1;
   else
    wordentry_stat.Add( id_entry, 1 );
  }

  return true;
 }

 public bool ProcessSample_Complete( SampleData sample )
 {
  int c = 0;
  if( sample2count.TryGetValue( sample.sample, out c ) )
   sample2count[sample.sample] = c + 1;
  else
   sample2count.Add( sample.sample, 1 );

  // Морфологический разбор
  if( sample.morphology == null )
   sample.morphology = gren.AnalyzeMorphology( sample.sample, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY );

  for( int iword = 1; iword < sample.morphology.Count - 1; ++iword )
  {
   word_count++;

   SolarixGrammarEngineNET.SyntaxTreeNode token = sample.morphology[iword];
   string word = token.GetWord().ToLower();

   WordformKEY k = new WordformKEY();
   k.wordform = word;
   k.id_entry = token.GetEntryID();

   int f = 0;
   if( wordform_stat.TryGetValue( k, out f ) )
    wordform_stat[k] = f + 1;
   else
    wordform_stat.Add( k, 1 );

   int id_entry = token.GetEntryID();
   if( wordentry_stat.TryGetValue( id_entry, out f ) )
    wordentry_stat[id_entry] = f + 1;
   else
    wordentry_stat.Add( id_entry, 1 );
  }

  if( sample.syntax_tree == null )
   sample.syntax_tree = gren.AnalyzeSyntax( sample.sample, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY, 0 );

  for( int i = 1; i < sample.syntax_tree.Count - 1; ++i )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode token = sample.syntax_tree[i];
   TraverseEdges( token );
  }

  return true;
 }

 void TraverseEdges( SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  foreach( SolarixGrammarEngineNET.SyntaxTreeNode leaf in token.leafs )
  {
   int distance = System.Math.Abs( leaf.GetWordPosition() - token.GetWordPosition() );
   if( edge_len2count.ContainsKey( distance ) )
    edge_len2count[distance] = edge_len2count[distance] + 1;
   else
    edge_len2count.Add( distance, 1 );

   TraverseEdges( leaf );
  }
 }


 void FillDistanceMatrix( SolarixGrammarEngineNET.SyntaxTreeNode node )
 {
  List<List<NodeDistance>> node_clouds = new List<List<NodeDistance>>();

  foreach( SolarixGrammarEngineNET.SyntaxTreeNode subnode in node.leafs )
  {
   List<NodeDistance> d = new List<NodeDistance>();

   NodeDistance n = new NodeDistance();
   n.token = subnode;
   n.distance = 1;
   d.Add( n );

   AssembleChildren( subnode, d, 2 );
   node_clouds.Add( d );

   foreach( NodeDistance nn in d )
    AddDistance( node, nn.token, nn.distance );
  }

  for( int i = 0; i < node_clouds.Count() - 1; ++i )
   for( int j = i + 1; j < node_clouds.Count(); ++j )
   {
    List<NodeDistance> cloud1 = node_clouds[i];
    List<NodeDistance> cloud2 = node_clouds[j];

    foreach( NodeDistance d1 in cloud1 )
     foreach( NodeDistance d2 in cloud2 )
     {
      AddDistance( d1.token, d2.token, d1.distance + d2.distance );
     }
   }

  foreach( SolarixGrammarEngineNET.SyntaxTreeNode subnode in node.leafs )
  {
   FillDistanceMatrix( subnode );
  }

  return;
 }


 void AssembleChildren( SolarixGrammarEngineNET.SyntaxTreeNode root, List<NodeDistance> children, int distance )
 {
  foreach( SolarixGrammarEngineNET.SyntaxTreeNode subnode in root.leafs )
  {
   NodeDistance n = new NodeDistance();
   n.distance = distance;
   n.token = subnode;
   children.Add( n );
   AssembleChildren( subnode, children, distance + 1 );
  }

  return;
 }


 void AddDistance( SolarixGrammarEngineNET.SyntaxTreeNode root, SolarixGrammarEngineNET.SyntaxTreeNode node, int distance )
 {
  WordentryDistance x = new WordentryDistance();

  x.id_entry1 = root.GetEntryID();
  x.id_entry2 = node.GetEntryID();
  if( x.id_entry1 > x.id_entry2 )
  {
   x.id_entry2 = root.GetEntryID();
   x.id_entry1 = node.GetEntryID();
  }

  WordentryDistance y;
  if( distance_matrix.TryGetValue( x, out y ) )
  {
   y.sum_distance += distance;
   y.sum_distance2 += distance * distance;
   y.N++;
  }
  else
  {
   x.N = 1;
   x.sum_distance += distance;
   x.sum_distance2 += distance * distance;
   distance_matrix.Add( x, x );
  }

  return;
 }


 int FindDepth( SolarixGrammarEngineNET.SyntaxTreeNode node )
 {
  int d = 1;
  int max_child_depth = 0;
  foreach( SolarixGrammarEngineNET.SyntaxTreeNode subnode in node.leafs )
  {
   int dd = FindDepth( subnode );
   max_child_depth = System.Math.Max( max_child_depth, dd );
  }

  return max_child_depth + d;
 }

 public void Print()
 {
  System.Console.WriteLine( "Всего слов={0}", word_count );
  System.Console.WriteLine( "Использовано разных словарных статей={0}", wordentry_stat.Count );
  System.Console.WriteLine( "Макс. глубина графа={0} для предложения:\n{1}", max_depth, max_depth_sentence );
  return;
 }

 private string EscapeSQL( string s )
 {
  return s.Replace( "'", "''" );
 }

 public void Store()
 {
  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "edge_lens.txt" ) )
  {
   foreach( var x in edge_len2count.OrderBy( z => z.Key ) )
   {
    wr.WriteLine( "{0};{1}", x.Key, x.Value );
   }
  }



  int n_assoc2 = 0;

  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "distance2.sql" ) )
  {
   wr.WriteLine( "DELETE FROM assoc2_corpus_stat;" );

   foreach( var w2 in distance_matrix.OrderByDescending( z => z.Value.id_entry1 ).ThenByDescending( z => z.Value.N ) )
   {
    string word1 = gren.GetEntryName( w2.Key.id_entry1 );
    string word2 = gren.GetEntryName( w2.Key.id_entry2 );

    double M = ( (double)w2.Key.sum_distance ) / ( (double)w2.Key.N );
    double D = ( (double)w2.Key.sum_distance2 ) / ( (double)w2.Key.N ) - M * M;

    wr.WriteLine( "INSERT INTO assoc2_corpus_stat( id_entry1, id_entry2, word1, word2, M, D, N ) VALUES ( {5}, {6}, '{0}', '{1}', {2}, {3}, {4} );", EscapeSQL( word1 ), EscapeSQL( word2 ), M.ToString( "0.####" ).Replace( ",", "." ), System.Math.Sqrt( D ).ToString( "0.####" ).Replace( ",", "." ), w2.Key.N, w2.Key.id_entry1, w2.Key.id_entry2 );
    n_assoc2++;

    if( ( n_assoc2 % 100 ) == 0 )
     wr.WriteLine( "GO" );
   }
  }

  System.Console.WriteLine( "Total number of biword associations: {0}", n_assoc2 );

  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "stat.sql" ) )
  {
   wr.WriteLine( "DELETE FROM wordform_corpus_stat;" );
   wr.WriteLine( "DELETE FROM wordentry_corpus_stat;" );

   foreach( var x in wordform_stat )
   {
    wr.WriteLine( "INSERT INTO wordform_corpus_stat( id_entry, word, freq ) VALUES ( {0}, '{1}', {2} );", x.Key.id_entry, x.Key.wordform.Replace( "'", "''" ), x.Value );
   }

   foreach( var x in wordentry_stat )
   {
    wr.WriteLine( "INSERT INTO wordentry_corpus_stat( id_entry, freq ) VALUES ( {0}, {1} );", x.Key, x.Value );
   }
  }


  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "wordentry.stat.txt" ) )
  {
   foreach( var x in wordentry_stat.OrderByDescending( z => z.Value ) )
   {
    wr.WriteLine( "{0};{1};{2}", x.Key, gren.GetEntryName( x.Key ), x.Value );
   }
  }

  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "wordentry.stat2.txt" ) )
  {
   foreach( var x in wordentry_stat.OrderByDescending( z => z.Value ) )
   {
    wr.WriteLine( "[{0}]", gren.GetEntryName( x.Key ) );
   }
  }

  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "lemma_sematags.txt" ) )
  {
   foreach( var x in wordentry_stat.Where( z => z.Value>=MIN_SEMATAG_FREQ ).OrderByDescending( z => z.Value ) )
   {
    string lemma = gren.GetEntryName( x.Key );
    if( !char.IsPunctuation( lemma[0] ) && lemma != "???" && lemma != "unknownentry" && lemma != "number_" )
     wr.WriteLine( "{0}\t{1}", lemma, x.Key );
   }
  }


  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "dublicated_samples.txt" ) )
  {
   foreach( var k in sample2count.Where( z => z.Value > 1 ) )
   {
    wr.WriteLine( "{0}", k.Key );
   }
  }

  return;
 }
}

