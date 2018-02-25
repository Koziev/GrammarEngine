using System.Collections.Generic;

class Builder_LEMM_Bayes
{
 private int suffix_seq = 0;

 private Dictionary<string, int> suffices = new Dictionary<string, int>();
 private Dictionary<int, string> id2suffix = new Dictionary<int, string>();

 bool IsUnknownLexem( string s )
 {
  return s.Equals( "UNKNOWNENTRY", System.StringComparison.InvariantCultureIgnoreCase ) ||
         s == "???" ||
         s.Equals( "number_", System.StringComparison.InvariantCultureIgnoreCase );
 }

 int MatchSuffix( string suffix, bool can_add )
 {
  int id = -1;

  if( suffices.TryGetValue( suffix, out id ) )
   return id;

  if( can_add )
  {
   id = suffix_seq++;
   suffices.Add( suffix, id );
   id2suffix.Add( id, suffix );
   return id;
  }
  else
  {
   return -1;
  }
 }

 public Builder_LEMM_Bayes()
 {
 }

 public SolarixGrammarEngineNET.GrammarEngine2 gren;
 public void LoadDictionary( string filepath )
 {
  gren = new SolarixGrammarEngineNET.GrammarEngine2();
  gren.Load( filepath, false );
  Init();
  return;
 }


 int LanguageID = -1;
 public void SetLanguage( int id ) { LanguageID = id; }

 private HashSet<string> undevidable_words = new HashSet<string>();

 public void Init()
 {
  foreach( string w in new[] { "надо", "подо", "между", "выше", "ниже" } )
  {
   undevidable_words.Add( w );
  }

  return;
 }

 private const int MAX_SUFFIX_LEN = 3;
 private string GetSuffix( string word )
 {
  if( undevidable_words.Contains( word ) )
   return word;

  if( word.Length > MAX_SUFFIX_LEN )
   return "~" + word.Substring( word.Length - MAX_SUFFIX_LEN );
  else
   return word;
 }


 private string GetTokenSuffix( int pos, int last_word_index, SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  if( pos == 0 )
  {
   string sfx = "~~BEGIN~~";
   return sfx;
  }
  else if( pos == last_word_index )
  {
   string sfx = "~~END~~";
   return sfx;
  }
  else
  {
   string word = token.GetWord().ToLower();
   string suffix = GetSuffix( word );
   return suffix;
  }
 }


 string TagLabel( int offset, int tag_id )
 {
  if( offset < 0 )
   return string.Format( "prev_{0}_{1}", -offset, tag_id );
  else if( offset == 0 )
   return string.Format( "this_{0}", tag_id );
  else
   return string.Format( "next_{0}_{1}", offset, tag_id );
 }

 Dictionary<string, int> feature_count = new Dictionary<string, int>();
 void CountFeature( string feature_name )
 {
  int n;
  if( feature_count.TryGetValue( feature_name, out n ) )
   feature_count[feature_name] = n + 1;
  else
   feature_count.Add( feature_name, 1 );

  return;
 }

 int GetFeatureCount( string feature_name )
 {
  int n;
  if( feature_count.TryGetValue( feature_name, out n ) )
   return n;
  else
   return 0;
 }

 Dictionary<string, int> P_count = new Dictionary<string, int>();
 void CountFeature2Result( string feature, int result_tag )
 {
  string s = string.Format( "{0}={1}", feature, result_tag );
  int n;
  if( P_count.TryGetValue( s, out n ) )
   P_count[s] = n + 1;
  else
   P_count.Add( s, 1 );

  return;
 }

 int GetFeature2ResultCount( string feature, int result_tag )
 {
  string s = string.Format( "{0}={1}", feature, result_tag );
  int n;
  if( P_count.TryGetValue( s, out n ) )
   return n;
  else
   return 0;
 }

 public bool ProcessSample( string line )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   List<string> sfx = new List<string>();
   List<int> sfx_index = new List<int>();

   List<string> sfx_lemma = new List<string>();
   List<int> sfx_lemma_index = new List<int>();

   int last_word_index = tokens.Count - 1;

   for( int iword = 0; iword < tokens.Count; ++iword )
   {
    string word = tokens[iword].GetWord().ToLower();

    string suffix = GetTokenSuffix( iword, last_word_index, tokens[iword] );
    sfx.Add( suffix );

    int index = MatchSuffix( suffix, true );
    sfx_index.Add( index );

    int ekey = tokens[iword].GetEntryID();
    string ename = gren.GetEntryName( ekey );
    string lemma;
    if( IsUnknownLexem( ename ) )
     lemma = word;
    else
     lemma = ename.ToLower();

    sfx_lemma.Add( GetSuffix( lemma ) );
    sfx_lemma_index.Add( MatchSuffix( GetSuffix( lemma ), true ) );
   }

   for( int iword = 1; iword < tokens.Count; ++iword )
   {
    string tag0 = TagLabel( 0, sfx_index[iword] );
    CountFeature( tag0 );
    CountFeature2Result( tag0, sfx_lemma_index[iword] );

    if( iword > 0 )
    {
     string tag1 = TagLabel( -1, sfx_index[iword - 1] );
     CountFeature( tag1 );
     CountFeature2Result( tag1, sfx_lemma_index[iword] );
    }

    if( iword < tokens.Count - 1 )
    {
     string tag2 = TagLabel( 1, sfx_index[iword + 1] );
     CountFeature( tag2 );
     CountFeature2Result( tag2, sfx_lemma_index[iword] );
    }
   }
  }

  return true;
 }


 int total_word_count = 0;
 int error_count_no_filter = 0;
 int error_count_with_ngram = 0;

 public void FinishLearning()
 {
  return;
 }


 public void Check( string line )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   // Токенизация без использования синтаксических правил
   using( SolarixGrammarEngineNET.AnalysisResults projs = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY ) )
   {
    List<List<int>> word2tags = new List<List<int>>();

    if( projs.Count != tokens.Count )
     return;

    total_word_count += projs.Count - 2;

    // Для каждого слова получим списки альтернативных лемматизаций.
    List<List<string>> word2lemmas = new List<List<string>>();
    List<List<int>> word2lemma_index = new List<List<int>>();

    List<string> lemmas = new List<string>();

    int last_word_index = projs.Count - 1;

    List<string> word_suffix = new List<string>();
    
    for( int iword = 0; iword < projs.Count; ++iword )
    {
     string suffix = GetTokenSuffix( iword, last_word_index, tokens[iword] );
     word_suffix.Add( suffix );
    }


    for( int iword = 0; iword < projs.Count; ++iword )
    {
     if( iword == 0 || iword == last_word_index )
     {
      List<string> w2l = new List<string>();
      w2l.Add( string.Empty );
      word2lemmas.Add( w2l );

      List<int> w2i = new List<int>();
      w2i.Add( -1 );
      word2lemma_index.Add( w2i );
     }
     else
     {
      List<string> word_lemmas = new List<string>();
      List<int> word_results = new List<int>();

      for( int iproj = 0; iproj < projs[iword].VersionCount(); ++iproj )
      {
       string lemma = string.Empty;
       int ekey = projs[iword].GetVersionEntryID( iproj );
       string ename = gren.GetEntryName( ekey );
       if( IsUnknownLexem( ename ) )
        lemma = projs[iword].GetWord().ToLower();
       else
        lemma = ename.ToLower();

       if( !word_lemmas.Contains( lemma ) )
       {
        word_lemmas.Add( lemma );

        int result = MatchSuffix( GetSuffix( lemma ), false );
        word_results.Add( result );
       }
      }

      word2lemmas.Add( word_lemmas );
      word2lemma_index.Add( word_results );
     }

     lemmas.Add( word2lemmas[iword][0] );
    }


    for( int iword = 1; iword < projs.Count - 1; ++iword )
    {
     List<double> P_lemma = new List<double>();
     for( int k = 0; k < word2lemma_index[iword].Count; ++k )
      {
       if( k==0 )
        P_lemma.Add( 1.0 );
       else
        P_lemma.Add( 1.0 );
      }

     // текущее слово
     string word0 = projs[iword].GetWord().ToLower();
     string suffix0 = word_suffix[iword];
     int id_suffix0 = MatchSuffix( suffix0, false );
     if( id_suffix0 == -1 )
      continue;

     string tag0 = TagLabel( 0, id_suffix0 );

     int N_TOTAL0 = GetFeatureCount( tag0 );

     for( int k = 0; k < word2lemma_index[iword].Count; ++k )
     {
      int lemma_index = word2lemma_index[iword][k];
      int N_LEMMA0 = GetFeature2ResultCount( tag0, lemma_index );

      if( N_TOTAL0 > 0 && N_LEMMA0 > 0 )
      {
       double p = ( (double)N_LEMMA0 ) / ( (double)N_TOTAL0 );
       P_lemma[k] *= p;
      }
     }

     // предыдущее слово
     if( iword > 0 )
     {
      string word1 = projs[iword - 1].GetWord().ToLower();
      string suffix1 = word_suffix[iword-1];
      int id_suffix1 = MatchSuffix( suffix1, false );
      if( id_suffix1 == -1 )
       continue;

      string tag1 = TagLabel( -1, id_suffix1 );

      int N_TOTAL1 = GetFeatureCount( tag1 );

      for( int k = 0; k < word2lemma_index[iword].Count; ++k )
      {
       int lemma_index = word2lemma_index[iword][k];
       int N_LEMMA1 = GetFeature2ResultCount( tag1, lemma_index );

       if( N_TOTAL1 > 0 && N_LEMMA1 > 0 )
       {
        double p = ( (double)N_LEMMA1 ) / ( (double)N_TOTAL1 );
        P_lemma[k] *= p;
       }
      }
     }

     // следующее слово
     if( iword < projs.Count - 1 )
     {
      string word2 = projs[iword + 1].GetWord().ToLower();
      string suffix2 = word_suffix[iword+1];
      int id_suffix2 = MatchSuffix( suffix2, false );
      if( id_suffix2 == -1 )
       continue;

      string tag2 = TagLabel( 1, id_suffix2 );

      int N_TOTAL2 = GetFeatureCount( tag2 );

      for( int k = 0; k < word2lemma_index[iword].Count; ++k )
      {
       int lemma_index = word2lemma_index[iword][k];
       int N_LEMMA2 = GetFeature2ResultCount( tag2, lemma_index );

       if( N_TOTAL2 > 0 && N_LEMMA2 > 0 )
       {
        double p = ( (double)N_LEMMA2 ) / ( (double)N_TOTAL2 );
        P_lemma[k] *= p;
       }
      }
     }


     // теперь надо выбрать самый достоверный вариант.
     double best_P = 0;

     for( int iproj = 0; iproj < word2lemmas[iword].Count; ++iproj )
     {
      double p = P_lemma[iproj];

      if( p > best_P )
      {
       best_P = p;
       lemmas[iword] = word2lemmas[iword][iproj];
      }
     }
    }


    // Теперь сравниваем леммы c правильными значениями.
    for( int iword = 1; iword < tokens.Count - 1; ++iword )
    {
     string mustbe = string.Empty;

     int ekey = tokens[iword].GetEntryID();
     string ename = gren.GetEntryName( ekey );

     if( IsUnknownLexem( ename ) ) // не будем учитывать ошибки лемматизации для не-словарных лексем.
      continue;

     mustbe = ename.ToLower();

     if( mustbe != lemmas[iword] )
      error_count_with_ngram++;

     string lemma0 = string.Empty;
     int ekey0 = projs[iword].GetEntryID();
     string ename0 = gren.GetEntryName( ekey0 );
     if( IsUnknownLexem( ename0 ) )
      continue;

     lemma0 = ename0.ToLower();

     if( mustbe != lemma0 )
      error_count_no_filter++;
    }
   }
  }

  return;
 }


 public void PrintTestResults()
 {
  System.Console.WriteLine( "total_check_word_count={0}", total_word_count );
  System.Console.WriteLine( "error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent( error_count_no_filter, total_word_count ) );
  System.Console.WriteLine( "error_count_with_ngram={0}, i.e. {1}%", error_count_with_ngram, PercentFormatter.Percent( error_count_with_ngram, total_word_count ) );
  return;
 }

 public void StoreModel()
 {
  // ...
  return;
 }


}
