using System.Collections.Generic;
using System;
using System.Linq;

class Edge4Stat
{
 public SolarixGrammarEngineNET.SyntaxTreeNode from, to;
}

class NodeLeafCount
{
 public int total_count; // сколько всего раз встретилось в текстах
 public int leaf_count; // сколько раз встретилось как лист
}


class Rule3Gram
{
 public SolarixGrammarEngineNET.SyntaxTreeNode root, node, subnode;
}


class ParsingToken
{
 int position;
 string original_word; // нормализованное слово
 string token;
 string tag;

 public ParsingToken( int _position, string _token, string _tag, string _original_word )
 {
  position = _position;
  token = _token; tag = _tag; original_word = _original_word;
 }

 public int GetPosition() { return position; }
 public string GetToken() { return token; }
 public string GetTag() { return tag; }
 public string GetOriginalWord() { return original_word; }

 public override int GetHashCode()
 {
  return ( position << 20 ) ^ token.GetHashCode();
 }

 public override bool Equals( object obj )
 {
  ParsingToken x = (ParsingToken)obj;
  return position == x.position && token == x.token && original_word == x.original_word;
 }
}

class ParsingContext
{
 int hash = 0;
 public void CalcHash()
 {
  hash = 0;

  for( int i = 0; i < tokens.Count; ++i )
   hash = hash ^ tokens[i].GetHashCode();

  for( int j = 0; j < edges.Count; ++j )
  {
   hash = hash ^ edges[j].GetHashCode();
  }

  return;
 }

 public List<ParsingToken> tokens = new List<ParsingToken>();
 public List<Edge4Stat_Words> edges = new List<Edge4Stat_Words>();
 int total_score = 0;

 public ParsingContext( List<ParsingToken> _tokens )
 {
  tokens = _tokens;
  total_score = 0;
  CalcHash();
 }

 public ParsingContext( List<ParsingToken> _tokens, int score, List<Edge4Stat_Words> _edges )
 {
  tokens = _tokens;
  total_score = score;
  edges = _edges;
  CalcHash();
 }

 public int GetScore() { return total_score; }

 public bool HasChildren( int token_position )
 {
  foreach( var e in edges )
   if( e.root_index == 0 )
   {
    if( e.l_token.GetPosition() == token_position )
     return true;
   }
   else //if( e.root_index==1 )
   {
    if( e.r_token.GetPosition() == token_position )
     return true;
   }

  return false;
 }

 public bool ContainsEdgeAndWords( string l_word, string r_word, int root_index )
 {
  foreach( var e in edges )
   if( e.l_token.GetOriginalWord() == l_word && e.r_token.GetOriginalWord() == r_word && e.root_index == root_index )
    return true;

  return false;
 }

 public override int GetHashCode()
 {
  return hash;
 }

 public override bool Equals( object obj )
 {
  ParsingContext x = (ParsingContext)obj;
  if( x.hash != hash || tokens.Count != x.tokens.Count )
   return false;

  for( int i = 0; i < tokens.Count; ++i )
  {
   if( !tokens[i].Equals( x.tokens[i] ) )
    return false;
  }

  return true;
 }

 public string PrintStructure()
 {
  System.Text.StringBuilder b = new System.Text.StringBuilder();

  foreach( var e in edges )
  {
   if( e.root_index == 1 )
    b.AppendFormat( "{0} --> {1}\n", e.l_token.GetOriginalWord(), e.r_token.GetOriginalWord() );
   else
    b.AppendFormat( "{0} <-- {1}\n", e.l_token.GetOriginalWord(), e.r_token.GetOriginalWord() );
  }

  return b.ToString();
 }
}

class ParsingContexts
{
 int max_context_count = 100;
 public List<ParsingContext> contexts = new List<ParsingContext>();
 int min_score = 0;

 public ParsingContexts( ParsingContext org_context ) { contexts.Add( org_context ); min_score = org_context.GetScore(); }

 public int Count() { return contexts.Count; }
 public ParsingContext this[int index]
 {
  get { return contexts[index]; }
  set { contexts[index] = value; }
 }

 public List<ParsingContext> new_contexts = new List<ParsingContext>();
 public void Add( ParsingContext c )
 {
  new_contexts.Add( c );
  return;
 }

 public int Commit()
 {
  int n_added = 0;
  foreach( ParsingContext c in new_contexts )
  {
   if( contexts.Contains( c ) )
    continue;

   if( contexts.Count < max_context_count )
   {
    contexts.Add( c );
    min_score = Math.Min( min_score, c.GetScore() );
    n_added++;
   }
   else if( c.GetScore() > min_score )
   {
    min_score = c.GetScore();

    for( int i = contexts.Count - 1; i >= 0; --i )
    {
     if( contexts[i].GetScore() < c.GetScore() )
      contexts.RemoveAt( i );
     else
      min_score = Math.Min( min_score, contexts[i].GetScore() );
    }

    contexts.Add( c );
    n_added++;
   }
  }

  new_contexts.Clear();

  return n_added;
 }

 public ParsingContext GetBest()
 {
  int best_score = contexts[0].GetScore();
  ParsingContext best = contexts[0];

  for( int i = 1; i < contexts.Count; ++i )
  {
   ParsingContext c = contexts[i];

   if( c.GetScore() > best_score )
   {
    best_score = c.GetScore();
    best = c;
   }
  }

  return best;
 }
}


class SuffixBook
{
 int suffix_len;
 HashSet<string> unbreakable_words;

 public SuffixBook( int _suffix_len, string _unbreakable_words )
 {
  suffix_len = _suffix_len;
  unbreakable_words = new HashSet<string>();
  foreach( string w in _unbreakable_words.Split( '|' ) )
  {
   unbreakable_words.Add( w.ToUpper() );
  }
 }

 public string GetCode( string word )
 {
  return ReduceToSuffix( word.ToUpper() );
 }

 string ReduceToSuffix( string word )
 {
  if( unbreakable_words.Contains( word ) )
   return word;

  if( word.Length <= suffix_len )
   return word;

  return "~" + word.Substring( word.Length - suffix_len );
 }
}




class Rule4Headword
{
 public string child_word;
 public int child_position; // -1/+1
 public int score;

 public int GetScore() { return score; }
 public void AddScoreOffset( int add ) { score += add; }
}

class Rules4Headword
{
 string headword;
 List<Rule4Headword> rules;
 Dictionary<string, Rule4Headword> left_child2rule, right_child2rule;

 public Rules4Headword( string _headword )
 {
  headword = _headword;
  rules = new List<Rule4Headword>();
  left_child2rule = new Dictionary<string, Rule4Headword>();
  right_child2rule = new Dictionary<string, Rule4Headword>();
 }

 public void AddScoreOffset( int add )
 {
  foreach( var r in left_child2rule )
   r.Value.AddScoreOffset( add );

  foreach( var r in right_child2rule )
   r.Value.AddScoreOffset( add );

  return;
 }

 public int GetMaxScore()
 {
  int s = 0;
  foreach( var r in left_child2rule )
   s = Math.Max( s, r.Value.GetScore() );

  foreach( var r in right_child2rule )
   s = Math.Max( s, r.Value.GetScore() );

  return s;
 }

 public void AddRule( string child_word, int child_position, int score )
 {
  Dictionary<string, Rule4Headword> position_rules;

  if( child_position == -1 )
   position_rules = left_child2rule;
  else if( child_position == 1 )
   position_rules = right_child2rule;
  else throw new ApplicationException();

  Rule4Headword r;
  if( position_rules.TryGetValue( child_word, out r ) )
  {
   position_rules[child_word].score += score;
  }
  else
  {
   r = new Rule4Headword();
   r.child_position = child_position;
   r.child_word = child_word;
   r.score = score;
   rules.Add( r );
   position_rules.Add( child_word, r );
  }
 }

 public int FindRule( string child_word, int child_position )
 {
  Dictionary<string, Rule4Headword> position_rules;

  if( child_position == -1 )
   position_rules = left_child2rule;
  else if( child_position == 1 )
   position_rules = right_child2rule;
  else throw new ApplicationException();

  Rule4Headword r;
  if( position_rules.TryGetValue( child_word, out r ) )
  {
   return r.score;
  }

  // TODO: нечеткий поиск примерных совпадений
  // .......

  return 0;
 }
}


class NGrams4Headword
{
 Dictionary<string, int> root_node_subnode = new Dictionary<string, int>();

 public void Add_Root_Node_Subnode( string node, string subnode )
 {
  string key = string.Format( "{0}|{1}", node, subnode );
  int score;
  if( root_node_subnode.TryGetValue( key, out score ) )
   root_node_subnode[key] = score + 1;
  else
   root_node_subnode.Add( key, 1 );

  return;
 }

 public int FindRule_Root_Node_Subnode( string node, string subnode )
 {
  string key = string.Format( "{0}|{1}", node, subnode );
  int res;
  if( root_node_subnode.TryGetValue( key, out res ) )
   return res;
  else
   return 0;
 }

 public void AddScoreOffset( int add )
 {
  Dictionary<string, int> root_node_subnode2 = new Dictionary<string, int>();
  foreach( var x in root_node_subnode )
   root_node_subnode2.Add( x.Key, x.Value + add );

  root_node_subnode = root_node_subnode2;

  return;
 }

}




class Edge4Stat_Words
{
 public ParsingToken l_token, r_token;
 public int root_index = -1;

 public override int GetHashCode()
 {
  return l_token.GetHashCode() ^ ( r_token.GetHashCode() << 8 ) ^ ( root_index << 20 );
 }

 public override bool Equals( object obj )
 {
  Edge4Stat_Words x = (Edge4Stat_Words)obj;
  return x.l_token == l_token && x.r_token == r_token && root_index == x.root_index;
 }
}




class EdgeStat
{
 SuffixBook suffices;

 public EdgeStat()
 {
  suffices = new SuffixBook( 3, "были|была|был|было|буду|будем|будешь|будете" );
 }

 string NormalizeToken( string word )
 {
  return word.ToUpper();
 }

 string NormalizeTokenSx( string word )
 {
  return suffices.GetCode( word );
 }

 private SolarixGrammarEngineNET.GrammarEngine2 gren;
 public void LoadDictionary( string filepath )
 {
  gren = new SolarixGrammarEngineNET.GrammarEngine2();
  gren.Load( filepath, false );
  return;
 }

 public SolarixGrammarEngineNET.GrammarEngine2 GetGrammarEngine() { return gren; }

 int LanguageID = -1;
 public void SetLanguage( int id ) { LanguageID = id; }



 private void AssembleEdges( SolarixGrammarEngineNET.SyntaxTreeNode node, List<Edge4Stat> edges, Dictionary<string, NodeLeafCount> leaves )
 {
  string uword = node.GetWord().ToUpper();
  NodeLeafCount word_info;
  if( !leaves.TryGetValue( uword, out word_info ) )
  {
   word_info = new NodeLeafCount();
   leaves.Add( uword, word_info );
  }

  word_info.total_count++;
  if( node.leafs.Count == 0 )
   word_info.leaf_count++;

  foreach( SolarixGrammarEngineNET.SyntaxTreeNode leaf in node.leafs )
  {
   Edge4Stat edge = new Edge4Stat();
   edge.from = node;
   edge.to = leaf;

   edges.Add( edge );

   AssembleEdges( leaf, edges, leaves );
  }

  return;
 }

 private void AssembleEdges( SolarixGrammarEngineNET.AnalysisResults syntax_tree, List<Edge4Stat> edges, Dictionary<string, NodeLeafCount> leaves )
 {
  for( int iroot = 1; iroot < syntax_tree.Count - 1; ++iroot )
   AssembleEdges( syntax_tree[iroot], edges, leaves );

  return;
 }


 private void Assemble3Grams( SolarixGrammarEngineNET.AnalysisResults syntax_tree, List<Rule3Gram> ngrams )
 {
  for( int iroot = 1; iroot < syntax_tree.Count - 1; ++iroot )
   Assemble3Grams( syntax_tree[iroot], ngrams );

  return;
 }


 private void Assemble3Grams( SolarixGrammarEngineNET.SyntaxTreeNode node, List<Rule3Gram> ngrams )
 {
  foreach( SolarixGrammarEngineNET.SyntaxTreeNode leaf in node.leafs )
  {
   if( leaf.leafs.Count > 0 )
   {
    foreach( SolarixGrammarEngineNET.SyntaxTreeNode leaf2 in leaf.leafs )
    {
     Rule3Gram ngram = new Rule3Gram();
     ngram.root = node;
     ngram.node = leaf;
     ngram.subnode = leaf2;
     ngrams.Add( ngram );
    }
   }

   Assemble3Grams( leaf, ngrams );
  }

  return;
 }



 //Dictionary<string, NGrams4Headword> headword_ngrams = new Dictionary<string, NGrams4Headword>();

 Dictionary<string, Rules4Headword> headword_rules = new Dictionary<string, Rules4Headword>();
 Dictionary<string, Rules4Headword> headword_sx_rules = new Dictionary<string, Rules4Headword>();


 Dictionary<string, int> leaf_score = new Dictionary<string, int>(); // штрафы за то, что слово остается листом (обычно это для предлогов)
 Dictionary<string, NodeLeafCount> leaves_count = new Dictionary<string, NodeLeafCount>();

 public bool ProcessSample( SampleData sample )
 {
  /*
    List<Rule3Gram> ngrams = new List<Rule3Gram>();
    Assemble3Grams( sample.syntax_tree, ngrams );

    foreach( Rule3Gram ngram in ngrams )
    {
     if( ngram.root.GetWordPosition() < ngram.node.GetWordPosition() &&
         ngram.node.GetWordPosition() < ngram.subnode.GetWordPosition() )
     {
      NGrams4Headword nx;
      if( !headword_ngrams.TryGetValue( ngram.root.GetWord().ToUpper(), out nx ) )
      {
       nx = new NGrams4Headword();
       headword_ngrams.Add( ngram.root.GetWord().ToUpper(), nx );
      }

      nx.Add_Root_Node_Subnode( ngram.node.GetWord().ToUpper(), ngram.subnode.GetWord().ToUpper() );
     }
     // TODO ELSE остальные топологии
    }
  */


  List<Edge4Stat> edges = new List<Edge4Stat>();
  AssembleEdges( sample.syntax_tree, edges, leaves_count );

  foreach( Edge4Stat e in edges )
  {
   int child_position = e.from.GetWordPosition() > e.to.GetWordPosition() ? -1 : 1;

   // --- ПРАВИЛО ДЛЯ ТОЧНЫХ СЛОВ ---
   string headword = NormalizeToken( e.from.GetWord() );
   string child_word = NormalizeToken( e.to.GetWord() );

   Rules4Headword rx;
   if( !headword_rules.TryGetValue( headword, out rx ) )
   {
    rx = new Rules4Headword( headword );
    headword_rules.Add( headword, rx );
   }

   rx.AddRule( child_word, child_position, 1 );


   // --- ПРАВИЛО ДЛЯ СУФФИКСОВ СЛОВ ---
   string headword_sx = NormalizeTokenSx( e.from.GetWord() );
   string child_word_sx = NormalizeTokenSx( e.to.GetWord() );

   Rules4Headword rx_sx;
   if( !headword_sx_rules.TryGetValue( headword_sx, out rx_sx ) )
   {
    rx_sx = new Rules4Headword( headword_sx );
    headword_sx_rules.Add( headword_sx, rx_sx );
   }

   rx_sx.AddRule( child_word_sx, child_position, 1 );

  }

  return true;
 }


 public void ListStat( string filename )
 {
  using( System.IO.StreamWriter wrt = new System.IO.StreamWriter( filename ) )
  {
   // ...
  }

  return;
 }

 public void AfterLearning()
 {
  foreach( var x in leaves_count )
  {
   if( x.Value.leaf_count < x.Value.total_count / 2 )
   {
    int leaf_fine = ( x.Value.total_count - x.Value.leaf_count ) / 3 + 1; // ??? регулировка экспериментом
    leaf_score.Add( x.Key, leaf_fine );
   }
  }

  // -------------------------

  int max_sx_score = 0;
  foreach( var g in headword_sx_rules )
  {
   max_sx_score = Math.Max( max_sx_score, g.Value.GetMaxScore() );
  }

  int max_rule2_score = 0;
  foreach( var g in headword_rules )
  {
   g.Value.AddScoreOffset( max_sx_score + 1 );
   max_rule2_score = Math.Max( max_rule2_score, g.Value.GetMaxScore() );
  }

  /*
    max_rule2_score *= 2; // так как мы присоединяем 2 узла в триграммах, то нам надо пересилить скоринг двух отдельных биграм.
    foreach( var g in headword_ngrams )
    {
     g.Value.AddScoreOffset( max_rule2_score );
    }
  */

  return;
 }


 int n_matched_edge = 0;
 int n_total_edge = 0;


 public ParsingContext ParseAndReturnBest( string text )
 {
  List<ParsingToken> tokens = new List<ParsingToken>();

  string[] toks = text.Split( " ,.!-:;?()\r\n".ToCharArray(), StringSplitOptions.RemoveEmptyEntries );
  for( int i = 0; i < toks.Length; ++i )
  {
   string word = toks[i];
   tokens.Add( new ParsingToken( i, NormalizeToken( word ), NormalizeTokenSx( word ), word ) );
  }

  ParsingContext org_context = new ParsingContext( tokens );
  return ParseAndReturnBest( org_context );
 }


 ParsingContext ParseAndReturnBest( ParsingContext org_context )
 {
  ParsingContexts contexts = new ParsingContexts( org_context );

  int n_pass = 0;
  while( true )
  {
   n_pass++;
   for( int ictx = 0; ictx < contexts.Count(); ++ictx )
   {
    ParsingContext cur_context = contexts[ictx];
    int ntoken = cur_context.tokens.Count;

    for( int iword = 0; iword < cur_context.tokens.Count; ++iword )
    {
     // ищем правила, применимые для сборки контекста вокруг слова в iword.
     ParsingToken headword = cur_context.tokens[iword];

     for( int rule_layer = 0; rule_layer < 2; ++rule_layer )
     {
      ParsingContext new_ctx = null;

      /*
            if( rule_layer == 0 )
            {
             if( cur_context.tokens.Count > 2 )
             {
              // проверяем 3-граммы
              NGrams4Headword ngrams = null;
              if( headword_ngrams.TryGetValue( headword.GetToken(), out ngrams ) )
              {
               if( iword + 2 <= cur_context.tokens.Count - 1 )
               {
                // ROOT + NODE + SUBNODE
                ParsingToken node_token = cur_context.tokens[iword + 1];
                ParsingToken subnode_token = cur_context.tokens[iword + 2];

                int score = ngrams.FindRule_Root_Node_Subnode( node_token.GetToken(), subnode_token.GetToken() );
                if( score > 0 )
                {
                 // создаем новый контекст

                 List<ParsingToken> new_tokens = new List<ParsingToken>();
                 for( int j = 0; j < cur_context.tokens.Count; ++j )
                  if( j != iword + 1 && j != iword + 2 )
                   new_tokens.Add( cur_context.tokens[j] );

                 Edge4Stat_Words e1 = new Edge4Stat_Words();
                 e1.l_token = headword;
                 e1.r_token = node_token;
                 e1.root_index = 0;

                 Edge4Stat_Words e2 = new Edge4Stat_Words();
                 e2.l_token = node_token;
                 e2.r_token = subnode_token;
                 e2.root_index = 0;

                 List<Edge4Stat_Words> new_edges = new List<Edge4Stat_Words>();
                 new_edges.AddRange( cur_context.edges );
                 new_edges.Add( e1 );
                 new_edges.Add( e2 );

                 new_ctx = new ParsingContext( new_tokens, cur_context.GetScore() + score, new_edges );


                }
               }
              }
             }
            }
            else
            {
      */

      Rules4Headword rules = null;

      bool head_found;

      if( rule_layer == 0 )
       head_found = headword_rules.TryGetValue( headword.GetToken(), out rules );
      else
       head_found = headword_sx_rules.TryGetValue( headword.GetTag(), out rules );

      if( head_found )
      {
       for( int offset = -2; offset <= 2; ++offset )
       {
        if( offset == 0 )
         continue;

        int remove_index = iword + offset;

        if( remove_index < 0 || remove_index >= ntoken )
         continue; // слово за пределами цепочки

        ParsingToken child_word = cur_context.tokens[remove_index];
        int child_position = offset < 0 ? -1 : 1;

        int score = rules.FindRule( rule_layer == 0 ? child_word.GetToken() : child_word.GetTag(), child_position );

        if( score > 0 )
        {
         // для непроективных дальных ребер штрафуем через уменьшение частотности
         int freq = score / Math.Abs( offset );

         // также штраф за лист, если зависимый токен не имеет веток
         int leaf_fine=0;
         if( !cur_context.HasChildren( cur_context.tokens[remove_index].GetPosition() ) )
          {
           leaf_score.TryGetValue( cur_context.tokens[remove_index].GetToken(), out leaf_fine );
          }
         

         // зависимое слово убираем из контекста
         List<ParsingToken> new_tokens = new List<ParsingToken>();
         for( int j = 0; j < cur_context.tokens.Count; ++j )
          if( j != remove_index )
           new_tokens.Add( cur_context.tokens[j] );

         Edge4Stat_Words e = new Edge4Stat_Words();
         if( child_position == -1 )
         {
          e.l_token = child_word;
          e.r_token = headword;
          e.root_index = 1;
         }
         else
         {
          e.r_token = child_word;
          e.l_token = headword;
          e.root_index = 0;
         }

         List<Edge4Stat_Words> new_edges = new List<Edge4Stat_Words>();
         new_edges.AddRange( cur_context.edges );
         new_edges.Add( e );

         new_ctx = new ParsingContext( new_tokens, cur_context.GetScore() + freq - leaf_fine, new_edges );
        }
       }
      }



      if( new_ctx != null )
      {
       // проверим уникальность
       bool do_add = true;
       for( int i = 0; i < contexts.Count(); ++i )
        if( contexts[i].GetHashCode() == new_ctx.GetHashCode() )
         if( contexts[i].Equals( new_ctx ) )
         {
          if( contexts[i].GetScore() < new_ctx.GetScore() )
          {
           contexts[i] = new_ctx;
          }

          do_add = false;
          break;
         }

       if( do_add )
       {
        for( int i = 0; i < contexts.new_contexts.Count(); ++i )
         if( contexts.new_contexts[i].GetHashCode() == new_ctx.GetHashCode() )
          if( contexts.new_contexts[i].Equals( new_ctx ) )
          {
           if( contexts.new_contexts[i].GetScore() < new_ctx.GetScore() )
           {
            contexts.new_contexts[i] = new_ctx;
           }

           do_add = false;
           break;
          }

        if( do_add )
        {
         contexts.Add( new_ctx );
        }
       }
      }
     }
    }
   }

   if( contexts.Commit() == 0 )
    break;
  }

  // теперь берем самый лучший результат
  ParsingContext best = contexts.GetBest();

  return best;
 }

 public void Check( SampleData sample )
 {
  // такие ребра должны быть
  List<Edge4Stat> edges = new List<Edge4Stat>();
  Dictionary<string, NodeLeafCount> node_leaves = new Dictionary<string, NodeLeafCount>();

  AssembleEdges( sample.syntax_tree, edges, node_leaves );

  List<ParsingToken> tokens = new List<ParsingToken>();
  for( int i = 1; i < sample.morphology.Count - 1; ++i )
  {
   string word = sample.morphology[i].GetWord();
   tokens.Add( new ParsingToken( sample.morphology[i].GetWordPosition(), NormalizeToken( word ), NormalizeTokenSx( word ), word ) );
  }

  ParsingContext org_context = new ParsingContext( tokens );

  ParsingContext best = ParseAndReturnBest( org_context );

  // и сравниваем списки ребер.

  n_total_edge += edges.Count;

  foreach( Edge4Stat e in edges )
  {
   string l_word, r_word;
   int root_index;

   if( e.from.GetWordPosition() > e.to.GetWordPosition() )
   {
    // 0 <-- 1
    l_word = e.to.GetWord();
    r_word = e.from.GetWord();
    root_index = 1;
   }
   else
   {
    // 0 --> 1
    r_word = e.to.GetWord();
    l_word = e.from.GetWord();
    root_index = 0;
   }

   if( best.ContainsEdgeAndWords( l_word, r_word, root_index ) )
    n_matched_edge++;
   else
   {
    Console.WriteLine( "MISSING EDGE {0}--{1} in {2}", l_word, r_word, sample.sample );
   }
  }

  // ...

  return;
 }

 public void PrintStat()
 {
  Console.WriteLine( "edge accuracy={0:F4}%", ( n_matched_edge * 100.0 ) / n_total_edge );
  return;
 }

}

