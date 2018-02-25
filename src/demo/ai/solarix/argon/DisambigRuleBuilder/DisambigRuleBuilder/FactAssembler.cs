using System.Collections.Generic;
using System.Linq;
using System;


class FactAssembler
{
 class Word2
 {
  public int id_entry1, id_entry2;

  public override int GetHashCode()
  {
   return id_entry1 ^ ( id_entry2 << 16 );
  }

  public override bool Equals( object obj )
  {
   Word2 y = (Word2)obj;
   return y.id_entry1==id_entry1 && y.id_entry2==id_entry2;
  }
 }

 HashSet<string> samples;

 Dictionary<Word2, int> verb_prepos, prepos_noun, adj_noun;

 public FactAssembler()
 {
  samples = new HashSet<string>();
  verb_prepos = new Dictionary<Word2, int>();
  prepos_noun = new Dictionary<Word2, int>();
  adj_noun = new Dictionary<Word2, int>();
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

 public void ProcessSample( string line )
 {
  if( samples.Contains( line ) )
   return;

  samples.Add( line );

  bool complete = false;
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeSyntax( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY, 0 ) )
  {
   if( tokens.Count == 3 )
   {
    complete = true;
    TraverseNode( tokens[1] );
   }
  }

  if( !complete )
  {
   // Морфологический разбор
   using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
   {
    for( int iword = 1; iword < tokens.Count - 2; ++iword )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[iword];
     SolarixGrammarEngineNET.SyntaxTreeNode token2 = tokens[iword + 1];

     if( IsPreposition( token ) && IsNoun( token2 ) )
      Store_Prepos_Noun( token, token2 );
     else if( IsVerb( token ) && IsPreposition( token2 ) )
      Store_Verb_Prepos( token, token2 );
    }
   }
  }

  return;
 }

 bool IsPreposition( SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  if( token.VersionCount() == 1 )
  {
   int id_entry = token.GetEntryID();
   int pos = gren.GetEntryClass( id_entry );
   if( pos == SolarixGrammarEngineNET.GrammarEngineAPI.PREPOS_ru )
    return true;
  }

  return false;
 }

 bool IsVerb( SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  if( token.VersionCount() == 1 )
  {
   int id_entry = token.GetEntryID();
   int pos = gren.GetEntryClass( id_entry );
   if( pos == SolarixGrammarEngineNET.GrammarEngineAPI.VERB_ru )
    return true;
   else if( pos == SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru )
    return true;
   else if( pos == SolarixGrammarEngineNET.GrammarEngineAPI.GERUND_2_ru )
    return true;
  }

  return false;
 }

 bool IsNoun( SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  if( token.VersionCount() == 1 )
  {
   int id_entry = token.GetEntryID();
   int pos = gren.GetEntryClass( id_entry );
   if( pos == SolarixGrammarEngineNET.GrammarEngineAPI.NOUN_ru )
    return true;
  }

  return false;
 }

 bool IsAdjective( SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  if( token.VersionCount() == 1 )
  {
   int id_entry = token.GetEntryID();
   int pos = gren.GetEntryClass( id_entry );
   if( pos == SolarixGrammarEngineNET.GrammarEngineAPI.ADJ_ru )
    return true;
  }

  return false;
 }

 void Store( Dictionary<Word2, int> dict, SolarixGrammarEngineNET.SyntaxTreeNode t1, SolarixGrammarEngineNET.SyntaxTreeNode t2 )
 {
  Word2 k = new Word2();
  k.id_entry1 = t1.GetEntryID();
  k.id_entry2 = t2.GetEntryID();
  int n;
  if( dict.TryGetValue( k, out n ) )
   dict[k] = n + 1;
  else
   dict.Add( k, 1 );

  return;
 }

 void Store_Prepos_Noun( SolarixGrammarEngineNET.SyntaxTreeNode prepos, SolarixGrammarEngineNET.SyntaxTreeNode noun )
 {
  //Store( prepos_noun, prepos, noun );
  return;
 }

 void Store_Verb_Prepos( SolarixGrammarEngineNET.SyntaxTreeNode verb, SolarixGrammarEngineNET.SyntaxTreeNode prepos )
 {
  Store( verb_prepos, verb, prepos );
  return;
 }

 void Store_Adj_Noun( SolarixGrammarEngineNET.SyntaxTreeNode adj, SolarixGrammarEngineNET.SyntaxTreeNode noun )
 {
  //Store( adj_noun, adj, noun );
  return;
 }

 void TraverseNode( SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  if( IsPreposition( token ) )
  {
   if( token.leafs.Count == 1 )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode object_token = token.leafs[0];
    if( IsNoun( object_token ) )
    {
     Store_Prepos_Noun( token, object_token );
    }
   }
  }
  else if( IsVerb( token ) )
  {
   foreach( SolarixGrammarEngineNET.SyntaxTreeNode subnode in token.leafs )
   {
    if( IsPreposition( subnode ) )
    {
     Store_Verb_Prepos( token, subnode );
    }
   }
  }
  else if( IsNoun( token ) )
  {
   foreach( SolarixGrammarEngineNET.SyntaxTreeNode subnode in token.leafs )
   {
    if( IsAdjective( subnode ) )
    {
     Store_Adj_Noun( subnode, token );
    }
   }
  }

  foreach( SolarixGrammarEngineNET.SyntaxTreeNode subnode in token.leafs )
  {
   TraverseNode( subnode );
  }

  return;
 }


 public void Print()
 {
  Console.WriteLine( "verb+prepos: {0}", verb_prepos.Count );
  Console.WriteLine( "prepos+noun: {0}", prepos_noun.Count );
  Console.WriteLine( "adj+noun: {0}", adj_noun.Count );

  return;
 }

 private string EscapeSQL( string s )
 {
  return s.Replace( "'", "''" );
 }

 public void Store()
 {
  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "kb_verb_prepos.txt" ) )
  {
   string prev_word1 = string.Empty;
   foreach( var x in verb_prepos.OrderByDescending( z => z.Key.id_entry1 ).ThenByDescending( z => z.Value ) )
   {
    string word1 = gren.GetEntryName( x.Key.id_entry1 );
    string word2 = gren.GetEntryName( x.Key.id_entry2 );

    if( word1 != "???" )
    {
     if( prev_word1 != word1 )
      wr.WriteLine( "\n\n" );

     prev_word1 = word1;
     wr.WriteLine( "{0} {1} = {2}", word1, word2, x.Value );
    }
   }
  }

  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "kb_prepos_noun.txt" ) )
  {
   string prev_word1 = string.Empty;
   foreach( var x in prepos_noun.OrderByDescending( z => z.Key.id_entry1 ).ThenByDescending( z => z.Value ) )
   {
    string word1 = gren.GetEntryName( x.Key.id_entry1 );
    string word2 = gren.GetEntryName( x.Key.id_entry2 );

    if( word2 != "???" )
    {
     if( prev_word1 != word1 )
      wr.WriteLine( "\n\n" );

     prev_word1 = word1;
     wr.WriteLine( "{0} {1} = {2}", word1, word2, x.Value );
    }
   }
  }

  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "kb_adj_noun.txt" ) )
  {
   string prev_word1 = string.Empty;
   foreach( var x in adj_noun.OrderByDescending( z => z.Key.id_entry1 ).ThenByDescending( z => z.Value ) )
   {
    string word1 = gren.GetEntryName( x.Key.id_entry1 );
    string word2 = gren.GetEntryName( x.Key.id_entry2 );

    if( word1 != "???" && word2 != "???" )
    {
     if( prev_word1 != word1 )
      wr.WriteLine( "\n\n" );

     prev_word1 = word1;
     wr.WriteLine( "{0} {1} = {2}", word1, word2, x.Value );
    }
   }
  }

  return;
 }
}

