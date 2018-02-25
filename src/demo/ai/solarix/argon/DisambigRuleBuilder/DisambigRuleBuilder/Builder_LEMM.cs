using System.Collections.Generic;


class Builder_LEMM
{
 System.IO.StreamWriter diff_file;

 private int suffix_seq = 0;

 private Dictionary<string, int> suffices = new Dictionary<string, int>();
 private Dictionary<int, string> id2suffix = new Dictionary<int, string>();

 // таблицы для диграмм
 private Dictionary<NGram2, int> ngram2 = new Dictionary<NGram2, int>(); // 1 -> 2
 private Dictionary<int, List<NGram2>> tag0_2_ngram2;

 private Dictionary<NGram2, int> ngram2_1 = new Dictionary<NGram2, int>(); // 1 <- 2
 private Dictionary<int, List<NGram2>> tag1_2_ngram2;

 // таблицы для триграмм
 private Dictionary<NGram3, int> ngram3 = new Dictionary<NGram3, int>(); // 1,2->3
 private Dictionary<Int2, List<NGram3>> tag0_2_ngram3;

 private Dictionary<NGram3, int> ngram3_1 = new Dictionary<NGram3, int>(); // 1 -> 2 <- 3
 private Dictionary<Int2, List<NGram3>> tag1_2_ngram3;

 private Dictionary<NGram3, int> ngram3_2 = new Dictionary<NGram3, int>(); // 1 <- 2,3
 private Dictionary<Int2, List<NGram3>> tag2_2_ngram3;

 // таблицы для тетраграмм
 private Dictionary<NGram4, int> ngram4 = new Dictionary<NGram4, int>();
 private Dictionary<Int3, List<NGram4>> tag0_2_ngram4;

 bool IsUnknownLexem( string s )
 {
  return s.Equals( "UNKNOWNENTRY", System.StringComparison.InvariantCultureIgnoreCase ) ||
         s == "???" ||
         s.Equals( "number_", System.StringComparison.InvariantCultureIgnoreCase );
 }

 int MatchSuffix( string suffix )
 {
  int id = -1;

  if( suffices.TryGetValue( suffix, out id ) )
   return id;

  id = suffix_seq++;
  suffices.Add( suffix, id );
  id2suffix.Add( id, suffix );

  return id;
 }

 public Builder_LEMM()
 {
 }

 public SolarixGrammarEngineNET.GrammarEngine2 gren;

 public SolarixGrammarEngineNET.GrammarEngine2 GetGrammarEngine() { return gren; }
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


 private const int MAX_SUFFIX_LEN = 4;
 private string GetSuffix( string word )
 {
  if( undevidable_words.Contains( word ) )
   return word;

  if( word.Length > MAX_SUFFIX_LEN )
   return "~" + word.Substring( word.Length - MAX_SUFFIX_LEN );
  else
   return word;
 }

 private void AddNGram( int s1, int s2 )
 {
  if( s1 == -1 || s2 == -1 )
   throw new System.ApplicationException();

  NGram2 k = new NGram2( s1, s2 );
  int freq;
  if( ngram2.TryGetValue( k, out freq ) )
  {
   ngram2[k] = freq + 1;
  }
  else
   ngram2.Add( k, 1 );

  return;
 }

 private void AddNGram_back( int s1, int s2 )
 {
  if( s1 == -1 || s2 == -1 )
   throw new System.ApplicationException();

  NGram2 k = new NGram2( s1, s2 );
  int freq;
  if( ngram2_1.TryGetValue( k, out freq ) )
  {
   ngram2_1[k] = freq + 1;
  }
  else
   ngram2_1.Add( k, 1 );

  return;
 }





 private void AddNGram( int s1, int s2, int s3 )
 {
  if( s1 == -1 || s2 == -1 || s3 == -1 )
   throw new System.ApplicationException();

  NGram3 k = new NGram3( s1, s2, s3 );
  int freq;
  if( ngram3.TryGetValue( k, out freq ) )
  {
   ngram3[k] = freq + 1;
  }
  else
   ngram3.Add( k, 1 );

  return;
 }


 private void AddNGram_1_0_1( int s1, int s2, int s3 )
 {
  if( s1 == -1 || s2 == -1 || s3 == -1 )
   throw new System.ApplicationException();

  NGram3 k = new NGram3( s1, s2, s3 );
  int freq;
  if( ngram3_1.TryGetValue( k, out freq ) )
  {
   ngram3_1[k] = freq + 1;
  }
  else
   ngram3_1.Add( k, 1 );

  return;
 }

 private void AddNGram_0_1_1( int s1, int s2, int s3 )
 {
  if( s1 == -1 || s2 == -1 || s3 == -1 )
   throw new System.ApplicationException();

  NGram3 k = new NGram3( s1, s2, s3 );
  int freq;
  if( ngram3_2.TryGetValue( k, out freq ) )
  {
   ngram3_2[k] = freq + 1;
  }
  else
   ngram3_2.Add( k, 1 );

  return;
 }




 private void AddNGram( int s1, int s2, int s3, int s4 )
 {
  if( s1 == -1 || s2 == -1 || s3 == -1 || s4 == -1 )
   throw new System.ApplicationException();

  NGram4 k = new NGram4( s1, s2, s3, s4 );
  int freq;
  if( ngram4.TryGetValue( k, out freq ) )
  {
   ngram4[k] = freq + 1;
  }
  else
   ngram4.Add( k, 1 );

  return;
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


 int n_learn_samples = 0;

 public bool ProcessSample( SampleData sample )
 {
  n_learn_samples++;

  // Морфологический разбор
  if( sample.morphology == null )
   sample.morphology = gren.AnalyzeMorphology( sample.sample, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY );

  List<string> sfx = new List<string>();
  List<int> sfx_index = new List<int>();

  List<string> sfx_lemma = new List<string>();
  List<int> sfx_lemma_index = new List<int>();

  int last_word_index = sample.morphology.Count - 1;

  for( int iword = 0; iword < sample.morphology.Count; ++iword )
  {
   string word = sample.morphology[iword].GetWord().ToLower();

   string suffix = GetTokenSuffix( iword, last_word_index, sample.morphology[iword] );
   sfx.Add( suffix );

   int index = MatchSuffix( suffix );
   sfx_index.Add( index );

   int ekey = sample.morphology[iword].GetEntryID();
   string ename = gren.GetEntryName( ekey );
   string lemma;
   if( IsUnknownLexem( ename ) )
    lemma = word;
   else
    lemma = ename.ToLower();

   sfx_lemma.Add( GetSuffix( lemma ) );
   sfx_lemma_index.Add( MatchSuffix( GetSuffix( lemma ) ) );
  }


  // ДИГРАММЫ
  for( int iword = 1; iword < sample.morphology.Count; ++iword )
  {
   int s1 = sfx_index[iword - 1];
   int s2 = sfx_lemma_index[iword];
   AddNGram( s1, s2 );
  }

  for( int iword = 1; iword < sample.morphology.Count; ++iword )
  {
   int s1 = sfx_lemma_index[iword - 1];
   int s2 = sfx_index[iword];
   AddNGram_back( s1, s2 );
  }



  // ТРИГРАММЫ
  for( int iword = 2; iword < sample.morphology.Count; ++iword )
  {
   int s1 = sfx_index[iword - 2];
   int s2 = sfx_index[iword - 1];
   int s3 = sfx_lemma_index[iword];
   AddNGram( s1, s2, s3 );
  }

  for( int iword = 2; iword < sample.morphology.Count; ++iword )
  {
   int s1 = sfx_index[iword - 2];
   int s2 = sfx_lemma_index[iword - 1];
   int s3 = sfx_index[iword];
   AddNGram_1_0_1( s1, s2, s3 );
  }

  for( int iword = 2; iword < sample.morphology.Count; ++iword )
  {
   int s1 = sfx_lemma_index[iword - 2];
   int s2 = sfx_index[iword - 1];
   int s3 = sfx_index[iword];
   AddNGram_0_1_1( s1, s2, s3 );
  }

  // ТЕТРАГРАММЫ
  for( int iword = 3; iword < sample.morphology.Count; ++iword )
  {
   int s1 = sfx_index[iword - 3];
   int s2 = sfx_index[iword - 2];
   int s3 = sfx_index[iword - 1];
   int s4 = sfx_lemma_index[iword];
   AddNGram( s1, s2, s3, s4 );
  }

  return true;
 }


 public void FinishLearning()
 {
  // индекс для поиска диграмм по первому тегу
  tag0_2_ngram2 = new Dictionary<int, List<NGram2>>();
  foreach( KeyValuePair<NGram2, int> x in ngram2 )
  {
   int tags0 = x.Key.tags0;
   List<NGram2> n;
   if( tag0_2_ngram2.TryGetValue( tags0, out n ) )
   {
    n.Add( x.Key );
   }
   else
   {
    n = new List<NGram2>();
    n.Add( x.Key );
    tag0_2_ngram2.Add( tags0, n );
   }
  }

  // индекс для поиска диграмм по второму тегу
  tag1_2_ngram2 = new Dictionary<int, List<NGram2>>();
  foreach( KeyValuePair<NGram2, int> x in ngram2_1 )
  {
   int tags1 = x.Key.tags1;
   List<NGram2> n;
   if( tag1_2_ngram2.TryGetValue( tags1, out n ) )
   {
    n.Add( x.Key );
   }
   else
   {
    n = new List<NGram2>();
    n.Add( x.Key );
    tag1_2_ngram2.Add( tags1, n );
   }
  }


  // ТРИГРАММЫ - индекс для поиска 1,2->3
  tag0_2_ngram3 = new Dictionary<Int2, List<NGram3>>();
  foreach( KeyValuePair<NGram3, int> x in ngram3 )
  {
   int tags0 = x.Key.tags0;
   int tags1 = x.Key.tags1;
   Int2 k = new Int2( tags0, tags1 );

   List<NGram3> n;
   if( tag0_2_ngram3.TryGetValue( k, out n ) )
   {
    n.Add( x.Key );
   }
   else
   {
    n = new List<NGram3>();
    n.Add( x.Key );
    tag0_2_ngram3.Add( k, n );
   }
  }

  // индекс для поиска 0 -> 1 <- 2
  tag1_2_ngram3 = new Dictionary<Int2, List<NGram3>>();
  foreach( KeyValuePair<NGram3, int> x in ngram3_1 )
  {
   int tags0 = x.Key.tags0;
   int tags2 = x.Key.tags2;
   Int2 k = new Int2( tags0, tags2 );

   List<NGram3> n;
   if( tag1_2_ngram3.TryGetValue( k, out n ) )
   {
    n.Add( x.Key );
   }
   else
   {
    n = new List<NGram3>();
    n.Add( x.Key );
    tag1_2_ngram3.Add( k, n );
   }
  }



  // индекс для поиска триграмм 0 <- 1,2
  tag2_2_ngram3 = new Dictionary<Int2, List<NGram3>>();
  foreach( KeyValuePair<NGram3, int> x in ngram3_2 )
  {
   int tags1 = x.Key.tags1;
   int tags2 = x.Key.tags2;
   Int2 k = new Int2( tags1, tags2 );

   List<NGram3> n;
   if( tag2_2_ngram3.TryGetValue( k, out n ) )
   {
    n.Add( x.Key );
   }
   else
   {
    n = new List<NGram3>();
    n.Add( x.Key );
    tag2_2_ngram3.Add( k, n );
   }
  }



  // индекс для поиска тетраграмм 0,1,2->3

  tag0_2_ngram4 = new Dictionary<Int3, List<NGram4>>();
  foreach( KeyValuePair<NGram4, int> x in ngram4 )
  {
   int tags0 = x.Key.tags0;
   int tags1 = x.Key.tags1;
   int tags2 = x.Key.tags2;
   Int3 k = new Int3( tags0, tags1, tags2 );

   List<NGram4> n;
   if( tag0_2_ngram4.TryGetValue( k, out n ) )
   {
    n.Add( x.Key );
   }
   else
   {
    n = new List<NGram4>();
    n.Add( x.Key );
    tag0_2_ngram4.Add( k, n );
   }
  }

  return;
 }


 int n_test_samples = 0;
 int total_word_count = 0;
 int error_count_no_filter = 0;
 int error_count_with_ngram = 0;

 public void StartTesting()
 {
  n_test_samples = 0;
  total_word_count = 0;
  error_count_no_filter = 0;
  error_count_with_ngram = 0;
 }


 public void Check( SampleData sample )
 {
  n_test_samples++;
  List<string> lemmas = null;
  Check( sample, lemmas, ref total_word_count, ref error_count_no_filter, ref error_count_with_ngram );
  return;
 }


 public void ExternalCheck( string sample, List<string> lemmas )
 {
  //  n_test_samples++;
  //  Check( sample, lemmas, ref total_word_count, ref error_count_no_filter, ref error_count_with_ngram );
  return;
 }



 private void Check(
                    SampleData line,
                    List<string> external_lemmas,
                    ref int total_word_count,
                    ref int error_count_no_filter,
                    ref int error_count_with_ngram
                   )
 {
  // Морфологический разбор
  if( line.morphology == null )
   line.morphology = gren.AnalyzeMorphology( line.sample, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY );

  // Токенизация без использования синтаксических правил
  if( line.tokenization == null )
   line.tokenization = gren.AnalyzeMorphology( line.sample, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY );


  List<List<int>> word2tags = new List<List<int>>();

  if( line.morphology.Count != line.tokenization.Count )
   return;

  if( external_lemmas != null && external_lemmas.Count != line.tokenization.Count - 2 )
   return;

  total_word_count += line.tokenization.Count - 2;

  // Для каждого слова получим списки альтернативных лемматизаций.
  List<List<string>> word2lemmas = new List<List<string>>();

  List<string> lemmas = new List<string>();
  List<int> lemma_scores = new List<int>();
  List<int> lemma_order = new List<int>();

  int last_word_index = line.tokenization.Count - 1;
  bool use_4grams = true;
  bool use_3grams = true;
  bool use_2grams = true;


  for( int iword = 0; iword < line.tokenization.Count; ++iword )
  {
   if( iword == 0 || iword == last_word_index )
   {
    List<string> w2l = new List<string>();
    w2l.Add( string.Empty );
    word2lemmas.Add( w2l );
   }
   else
   {
    List<string> word_lemmas = new List<string>();

    // Соберем варианты лемм для токена.
    for( int iproj = 0; iproj < line.tokenization[iword].VersionCount(); ++iproj )
    {
     string lemma = string.Empty;
     int ekey = line.tokenization[iword].GetVersionEntryID(iproj);
     string ename = gren.GetEntryName( ekey );
     if( IsUnknownLexem( ename ) )
      lemma = line.tokenization[iword].GetWord().ToLower(); // для несловарных токенов в качестве леммы берем саму форму
     else
      lemma = ename.ToLower();

     if( !word_lemmas.Contains( lemma ) )
      word_lemmas.Add( lemma );
    }

    word2lemmas.Add( word_lemmas );
   }

   lemmas.Add( word2lemmas[iword][0] );
   lemma_scores.Add( 0 );
   lemma_order.Add( 1 );
  }


  for( int iword = 1; iword < line.tokenization.Count; ++iword )
  {
   bool lemma_created = false;


   if( use_4grams )
   {
    // ИСПОЛЬЗУЕМ ТЕТРАГРАММЫ

    if( !lemma_created && iword > 2 )
    {

     string word1 = line.tokenization[iword - 3].GetWord().ToLower();
     string suffix1 = GetSuffix( word1 );
     int id_suffix1 = MatchSuffix( suffix1 );

     string word2 = line.tokenization[iword - 2].GetWord().ToLower();
     string suffix2 = GetSuffix( word2 );
     int id_suffix2 = MatchSuffix( suffix2 );

     string word3 = line.tokenization[iword - 1].GetWord().ToLower();
     string suffix3 = GetSuffix( word3 );
     int id_suffix3 = MatchSuffix( suffix3 );

     List<NGram4> n4_list;
     Int3 k4 = new Int3( id_suffix1, id_suffix2, id_suffix3 );

     if( tag0_2_ngram4.TryGetValue( k4, out n4_list ) )
     {
      Dictionary<string, int> sfx2score = new Dictionary<string, int>();

      int proj_count = line.tokenization[iword].VersionCount();
      for( int iproj = 0; iproj < proj_count; ++iproj )
      {
       int ekey_i = line.tokenization[iword].GetVersionEntryID( iproj );
       string entry_name = gren.GetEntryName( ekey_i ).ToLower();
       string i_sfx = GetSuffix( entry_name );
       if( !sfx2score.ContainsKey( i_sfx ) )
        sfx2score.Add( i_sfx, 0 );
      }

      foreach( NGram4 n4_probe in n4_list )
      {
       int id_suffix4 = n4_probe.tags3;
       string suffix4 = id2suffix[id_suffix4];

       List<KeyValuePair<string, int>> changes = new List<KeyValuePair<string, int>>();
       foreach( KeyValuePair<string, int> p in sfx2score )
       {
        if( suffix4 == p.Key )
        {
         int sfx_freq = ngram4[n4_probe];
         changes.Add( new KeyValuePair<string, int>( p.Key, sfx_freq ) );
        }
       }

       foreach( var kv in changes )
        sfx2score[kv.Key] = sfx2score[kv.Key] + kv.Value;
      }

      // теперь надо выбрать самый достоверный вариант.
      int best_score = 0;

      // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
      for( int iproj = 0; iproj < line.tokenization[iword].VersionCount(); ++iproj )
      {
       int ekey = line.tokenization[iword].GetVersionEntryID( iproj );

       string ename = gren.GetEntryName( ekey );
       if( !IsUnknownLexem( ename ) )
       {
        string proj_suffix = GetSuffix( ename.ToLower() );
        if( sfx2score.ContainsKey( proj_suffix ) )
        {
         int new_score = sfx2score[proj_suffix];
         if( new_score > best_score )
         {
          best_score = new_score;
          lemmas[iword] = ename.ToLower();
          lemma_scores[iword] = best_score;
          lemma_order[iword] = 4;
          lemma_created = true;
         }
        }
       }
      }
     }
    }
   }


   if( use_3grams )
   {
    // ИСПОЛЬЗУЕМ ТРИГРАММЫ

    if( !lemma_created && iword > 1 )
    {
     // Если текущее слово имеет 1 вариант лемматизации, то можно использовать его для перепроверки предыдущего слова.

     if( iword > 2 && word2lemmas[iword].Count == 1 && word2lemmas[iword - 1].Count == 1 && word2lemmas[iword - 2].Count > 1 && lemma_order[iword - 2] < 3 )
     {
      // переоцениваем слово в iword-2
      // iword-2 <-- iword-1,iword

      string word2 = line.tokenization[iword].GetWord().ToLower();
      string suffix2 = GetSuffix( word2 );
      int id_suffix2 = MatchSuffix( suffix2 );

      string word1 = line.tokenization[iword - 1].GetWord().ToLower();
      string suffix1 = GetSuffix( word1 );
      int id_suffix1 = MatchSuffix( suffix1 );

      List<NGram3> n3_list;
      Int2 k2 = new Int2( id_suffix1, id_suffix2 );
      if( tag2_2_ngram3.TryGetValue( k2, out n3_list ) )
      {
       Dictionary<string, int> sfx2score = new Dictionary<string, int>();

       int proj_count = word2lemmas[iword - 2].Count;
       for( int iproj = 0; iproj < proj_count; ++iproj )
       {
        string entry_name = word2lemmas[iword - 2][iproj];
        string i_sfx = GetSuffix( entry_name );
        if( !sfx2score.ContainsKey( i_sfx ) )
         sfx2score.Add( i_sfx, 0 );
       }

       foreach( NGram3 n3_probe in n3_list )
       {
        int id_suffix0 = n3_probe.tags0;
        string suffix0 = id2suffix[id_suffix0];

        List<KeyValuePair<string, int>> changes = new List<KeyValuePair<string, int>>();
        foreach( KeyValuePair<string, int> p in sfx2score )
        {
         if( suffix0 == p.Key )
         {
          int sfx_freq = ngram3_2[n3_probe];
          changes.Add( new KeyValuePair<string, int>( p.Key, sfx_freq ) );
         }
        }

        foreach( var kv in changes )
         sfx2score[kv.Key] = sfx2score[kv.Key] + kv.Value;
       }

       // теперь надо выбрать самый достоверный вариант.
       int best_score = 0;

       string prev_lemma = string.Empty;
       int prev_score = 0;

       // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
       for( int iproj = 0; iproj < word2lemmas[iword - 2].Count; ++iproj )
       {
        string ename = word2lemmas[iword - 2][iproj];
        string proj_suffix = GetSuffix( ename.ToLower() );
        if( sfx2score.ContainsKey( proj_suffix ) )
        {
         int new_score = sfx2score[proj_suffix];
         if( new_score > best_score )
         {
          prev_score = new_score;
          prev_lemma = ename.ToLower();
         }
        }
       }

       // Если предыдущее слово лемматизировано с меньшей достоверностью, то меняем его.
       if( lemma_scores[iword - 2] < prev_score )
       {
        lemma_scores[iword - 2] = prev_score;
        lemmas[iword - 2] = prev_lemma;
        lemma_order[iword - 2] = 3;
       }
      }
     }
     else if( iword > 1 && word2lemmas[iword].Count == 1 && word2lemmas[iword - 1].Count > 1 && lemma_order[iword - 1] < 3 )
     {
      // переоцениваем слово в iword-1
      // iword-2 --> iword-1 <-- iword

      string word2 = line.tokenization[iword].GetWord().ToLower();
      string suffix2 = GetSuffix( word2 );
      int id_suffix2 = MatchSuffix( suffix2 );

      string word0 = line.tokenization[iword - 2].GetWord().ToLower();
      string suffix0 = GetSuffix( word0 );
      int id_suffix0 = MatchSuffix( suffix0 );

      List<NGram3> n3_list;
      Int2 k2 = new Int2( id_suffix0, id_suffix2 );
      if( tag1_2_ngram3.TryGetValue( k2, out n3_list ) )
      {
       Dictionary<string, int> sfx2score = new Dictionary<string, int>();

       int proj_count = word2lemmas[iword - 1].Count;
       for( int iproj = 0; iproj < proj_count; ++iproj )
       {
        string entry_name = word2lemmas[iword - 1][iproj];
        string i_sfx = GetSuffix( entry_name );
        if( !sfx2score.ContainsKey( i_sfx ) )
         sfx2score.Add( i_sfx, 0 );
       }

       foreach( NGram3 n3_probe in n3_list )
       {
        int id_suffix1 = n3_probe.tags1;
        string suffix1 = id2suffix[id_suffix1];

        List<KeyValuePair<string, int>> changes = new List<KeyValuePair<string, int>>();
        foreach( KeyValuePair<string, int> p in sfx2score )
        {
         if( suffix1 == p.Key )
         {
          int sfx_freq = ngram3_1[n3_probe];
          changes.Add( new KeyValuePair<string, int>( p.Key, sfx_freq ) );
         }
        }

        foreach( var kv in changes )
         sfx2score[kv.Key] = sfx2score[kv.Key] + kv.Value;
       }

       // теперь надо выбрать самый достоверный вариант.
       int best_score = 0;

       string prev_lemma = string.Empty;
       int prev_score = 0;

       // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
       for( int iproj = 0; iproj < word2lemmas[iword - 1].Count; ++iproj )
       {
        string ename = word2lemmas[iword - 1][iproj];
        string proj_suffix = GetSuffix( ename.ToLower() );
        if( sfx2score.ContainsKey( proj_suffix ) )
        {
         int new_score = sfx2score[proj_suffix];
         if( new_score > best_score )
         {
          prev_score = new_score;
          prev_lemma = ename.ToLower();
         }
        }
       }

       // Если предыдущее слово лемматизировано с меньшей достоверностью, то меняем его.
       if( lemma_scores[iword - 1] < prev_score )
       {
        lemma_scores[iword - 1] = prev_score;
        lemmas[iword - 1] = prev_lemma;
        lemma_order[iword - 1] = 3;
       }
      }
     }
     else if( word2lemmas[iword].Count > 1 )
     {
      Dictionary<string, int> sfx2score = new Dictionary<string, int>();

      if( iword > 1 )
      {
       // iword-2,iword-1 --> iword

       string word1 = line.tokenization[iword - 2].GetWord().ToLower();
       string suffix1 = GetSuffix( word1 );
       int id_suffix1 = MatchSuffix( suffix1 );

       string word2 = line.tokenization[iword - 1].GetWord().ToLower();
       string suffix2 = GetSuffix( word2 );
       int id_suffix2 = MatchSuffix( suffix2 );

       List<NGram3> n3_list;
       Int2 k2 = new Int2( id_suffix1, id_suffix2 );

       if( tag0_2_ngram3.TryGetValue( k2, out n3_list ) )
       {
        int proj_count = word2lemmas[iword].Count;
        for( int iproj = 0; iproj < proj_count; ++iproj )
        {
         string entry_name = word2lemmas[iword][iproj];
         string i_sfx = GetSuffix( entry_name );
         if( !sfx2score.ContainsKey( i_sfx ) )
          sfx2score.Add( i_sfx, 0 );
        }

        foreach( NGram3 n3_probe in n3_list )
        {
         int id_suffix3 = n3_probe.tags2;
         string suffix3 = id2suffix[id_suffix3];

         List<KeyValuePair<string, int>> changes = new List<KeyValuePair<string, int>>();
         foreach( KeyValuePair<string, int> p in sfx2score )
         {
          if( suffix3 == p.Key )
          {
           int sfx_freq = ngram3[n3_probe];
           changes.Add( new KeyValuePair<string, int>( p.Key, sfx_freq ) );
          }
         }

         foreach( var kv in changes )
          sfx2score[kv.Key] = sfx2score[kv.Key] + kv.Value;
        }
       }
      }

      if( iword > 0 && iword < last_word_index )
      {
       // iword-1 --> iword <-- iword+1

       string word0 = line.tokenization[iword - 1].GetWord().ToLower();
       string suffix0 = GetSuffix( word0 );
       int id_suffix0 = MatchSuffix( suffix0 );

       string word2 = line.tokenization[iword + 1].GetWord().ToLower();
       string suffix2 = GetSuffix( word2 );
       int id_suffix2 = MatchSuffix( suffix2 );

       List<NGram3> n3_list;
       Int2 k2 = new Int2( id_suffix0, id_suffix2 );

       if( tag1_2_ngram3.TryGetValue( k2, out n3_list ) )
       {
        int proj_count = word2lemmas[iword].Count;
        for( int iproj = 0; iproj < proj_count; ++iproj )
        {
         string entry_name = word2lemmas[iword][iproj];
         string i_sfx = GetSuffix( entry_name );
         if( !sfx2score.ContainsKey( i_sfx ) )
          sfx2score.Add( i_sfx, 0 );
        }

        foreach( NGram3 n3_probe in n3_list )
        {
         int id_suffix1 = n3_probe.tags1;
         string suffix1 = id2suffix[id_suffix1];

         List<KeyValuePair<string, int>> changes = new List<KeyValuePair<string, int>>();
         foreach( KeyValuePair<string, int> p in sfx2score )
         {
          if( suffix1 == p.Key )
          {
           int sfx_freq = ngram3_1[n3_probe];
           changes.Add( new KeyValuePair<string, int>( p.Key, sfx_freq ) );
          }
         }

         foreach( var kv in changes )
          sfx2score[kv.Key] = sfx2score[kv.Key] + kv.Value;
        }
       }
      }



      if( iword > 0 && iword < last_word_index - 1 )
      {
       // iword <-- iword+1,iword+2

       string word1 = line.tokenization[iword + 1].GetWord().ToLower();
       string suffix1 = GetSuffix( word1 );
       int id_suffix1 = MatchSuffix( suffix1 );

       string word2 = line.tokenization[iword + 2].GetWord().ToLower();
       string suffix2 = GetSuffix( word2 );
       int id_suffix2 = MatchSuffix( suffix2 );

       List<NGram3> n3_list;
       Int2 k2 = new Int2( id_suffix1, id_suffix2 );

       if( tag2_2_ngram3.TryGetValue( k2, out n3_list ) )
       {
        int proj_count = word2lemmas[iword].Count;
        for( int iproj = 0; iproj < proj_count; ++iproj )
        {
         string entry_name = word2lemmas[iword][iproj];
         string i_sfx = GetSuffix( entry_name );
         if( !sfx2score.ContainsKey( i_sfx ) )
          sfx2score.Add( i_sfx, 0 );
        }

        foreach( NGram3 n3_probe in n3_list )
        {
         int id_suffix0 = n3_probe.tags0;
         string suffix0 = id2suffix[id_suffix0];

         List<KeyValuePair<string, int>> changes = new List<KeyValuePair<string, int>>();
         foreach( KeyValuePair<string, int> p in sfx2score )
         {
          if( suffix1 == p.Key )
          {
           int sfx_freq = ngram3_2[n3_probe];
           changes.Add( new KeyValuePair<string, int>( p.Key, sfx_freq ) );
          }
         }

         foreach( var kv in changes )
          sfx2score[kv.Key] = sfx2score[kv.Key] + kv.Value;
        }
       }
      }


      // теперь надо выбрать самый достоверный вариант.
      int best_score = 0;

      // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
      for( int iproj = 0; iproj < word2lemmas[iword].Count; ++iproj )
      {
       string ename = word2lemmas[iword][iproj];
       string proj_suffix = GetSuffix( ename.ToLower() );
       if( sfx2score.ContainsKey( proj_suffix ) )
       {
        int new_score = sfx2score[proj_suffix];
        if( new_score > best_score )
        {
         best_score = new_score;
         lemmas[iword] = ename.ToLower();
         lemma_scores[iword] = best_score;
         lemma_order[iword] = 3;
         lemma_created = true;
        }
       }
      }
     }
    }
   }


   if( use_2grams )
   {
    if( !lemma_created )
    {
     // =======================
     // ИСПОЛЬЗУЕМ ДИГРАММЫ
     // =======================

     Dictionary<string, int> sfx2score = new Dictionary<string, int>();

     // Если текущее слово имеет 1 вариант лемматизации, то можно использовать его для перепроверки предыдущего слова.
     if( word2lemmas[iword].Count == 1 && word2lemmas[iword - 1].Count > 1 && lemma_order[iword - 1] < 2 )
     {
      string word2 = line.tokenization[iword].GetWord().ToLower();
      string suffix2 = GetSuffix( word2 );
      int id_suffix2 = MatchSuffix( suffix2 );

      List<NGram2> n2_list;
      if( tag1_2_ngram2.TryGetValue( id_suffix2, out n2_list ) )
      {
       int proj_count = word2lemmas[iword - 1].Count;
       for( int iproj = 0; iproj < proj_count; ++iproj )
       {
        string entry_name = word2lemmas[iword - 1][iproj];
        string i_sfx = GetSuffix( entry_name );
        if( !sfx2score.ContainsKey( i_sfx ) )
         sfx2score.Add( i_sfx, 0 );
       }

       foreach( NGram2 n2_probe in n2_list )
       {
        int id_suffix1 = n2_probe.tags0;
        string suffix1 = id2suffix[id_suffix1];

        List<KeyValuePair<string, int>> changes = new List<KeyValuePair<string, int>>();
        foreach( KeyValuePair<string, int> p in sfx2score )
        {
         if( suffix1 == p.Key )
         {
          int sfx_freq = ngram2_1[n2_probe];
          changes.Add( new KeyValuePair<string, int>( p.Key, sfx_freq ) );
         }
        }

        foreach( var kv in changes )
         sfx2score[kv.Key] = sfx2score[kv.Key] + kv.Value;
       }

       // теперь надо выбрать самый достоверный вариант.
       int best_score = 0;

       string prev_lemma = string.Empty;
       int prev_score = 0;

       // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
       for( int iproj = 0; iproj < word2lemmas[iword - 1].Count; ++iproj )
       {
        string ename = word2lemmas[iword - 1][iproj];
        string proj_suffix = GetSuffix( ename.ToLower() );
        if( sfx2score.ContainsKey( proj_suffix ) )
        {
         int new_score = sfx2score[proj_suffix];
         if( new_score > best_score )
         {
          prev_score = new_score;
          prev_lemma = ename.ToLower();
         }
        }
       }

       // Если предыдущее слово лемматизировано с меньшей достоверностью, то меняем его.
       if( lemma_scores[iword - 1] < prev_score )
       {
        lemma_scores[iword - 1] = prev_score;
        lemmas[iword - 1] = prev_lemma;
        lemma_order[iword - 1] = 2;
       }
      }
     }
     else if( word2lemmas[iword].Count > 1 )
     {
      // iword-1 --> iword
      {
       string word1 = line.tokenization[iword - 1].GetWord().ToLower();
       string suffix1 = GetSuffix( word1 );
       int id_suffix1 = MatchSuffix( suffix1 );

       List<NGram2> n2_list;
       if( tag0_2_ngram2.TryGetValue( id_suffix1, out n2_list ) )
       {
        int proj_count = word2lemmas[iword].Count;
        for( int iproj = 0; iproj < proj_count; ++iproj )
        {
         string entry_name = word2lemmas[iword][iproj];
         string i_sfx = GetSuffix( entry_name );
         if( !sfx2score.ContainsKey( i_sfx ) )
          sfx2score.Add( i_sfx, 0 );
        }

        foreach( NGram2 n2_probe in n2_list )
        {
         int id_suffix2 = n2_probe.tags1;
         string suffix2 = id2suffix[id_suffix2];

         List<KeyValuePair<string, int>> changes = new List<KeyValuePair<string, int>>();
         foreach( KeyValuePair<string, int> p in sfx2score )
         {
          if( suffix2 == p.Key )
          {
           int sfx_freq = ngram2[n2_probe];
           changes.Add( new KeyValuePair<string, int>( p.Key, sfx_freq ) );
          }
         }

         foreach( var kv in changes )
          sfx2score[kv.Key] = sfx2score[kv.Key] + kv.Value;
        }
       }
      }


      if( iword < last_word_index )
      {
       // iword <-- iword+1

       string word2 = line.tokenization[iword + 1].GetWord().ToLower();
       string suffix2 = GetSuffix( word2 );
       int id_suffix2 = MatchSuffix( suffix2 );

       List<NGram2> n2_list;
       if( tag1_2_ngram2.TryGetValue( id_suffix2, out n2_list ) )
       {
        int proj_count = word2lemmas[iword].Count;
        for( int iproj = 0; iproj < proj_count; ++iproj )
        {
         string entry_name = word2lemmas[iword][iproj];
         string i_sfx = GetSuffix( entry_name );
         if( !sfx2score.ContainsKey( i_sfx ) )
          sfx2score.Add( i_sfx, 0 );
        }

        foreach( NGram2 n2_probe in n2_list )
        {
         int id_suffix0 = n2_probe.tags0;
         string suffix0 = id2suffix[id_suffix0];

         List<KeyValuePair<string, int>> changes = new List<KeyValuePair<string, int>>();
         foreach( KeyValuePair<string, int> p in sfx2score )
         {
          if( suffix2 == p.Key )
          {
           int sfx_freq = ngram2_1[n2_probe];
           changes.Add( new KeyValuePair<string, int>( p.Key, sfx_freq ) );
          }
         }

         foreach( var kv in changes )
          sfx2score[kv.Key] = sfx2score[kv.Key] + kv.Value;
        }
       }
      }


      // теперь надо выбрать самый достоверный вариант.
      int best_score = 0;

      // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
      for( int iproj = 0; iproj < word2lemmas[iword].Count; ++iproj )
      {
       string ename = word2lemmas[iword][iproj];
       string proj_suffix = GetSuffix( ename.ToLower() );
       if( sfx2score.ContainsKey( proj_suffix ) )
       {
        int new_score = sfx2score[proj_suffix];
        if( new_score > best_score )
        {
         best_score = new_score;
         lemmas[iword] = ename.ToLower();
         lemma_scores[iword] = best_score;
         lemma_created = true;
        }
       }
      }

     }
    }
   }
  }


  if( external_lemmas != null )
  {
   for( int iword = 1; iword < line.tokenization.Count - 1; ++iword )
   {
    int ekey = line.morphology[iword].GetEntryID();
    string ename = gren.GetEntryName( ekey );

    if( IsUnknownLexem( ename ) ) // не будем учитывать ошибки лемматизации для не-словарных лексем.
     continue;

    string mustbe = external_lemmas[iword - 1].ToLower();

    if( mustbe == "<?-todo-?>" )
     continue;

    if( mustbe != lemmas[iword] )
    {
     if( diff_file == null )
      diff_file = new System.IO.StreamWriter( "diff_file.txt" );

     diff_file.WriteLine( "{0} /// {1}", mustbe, lemmas[iword] );
     diff_file.Flush();

     error_count_with_ngram++;
    }

    string lemma0 = string.Empty;
    int ekey0 = line.tokenization[iword].GetEntryID();
    string ename0 = gren.GetEntryName( ekey0 );
    if( IsUnknownLexem( ename0 ) )
     continue;

    lemma0 = ename0.ToLower();

    if( mustbe != lemma0 )
     error_count_no_filter++;
   }
  }
  else
  {
   // Теперь сравниваем леммы c правильными значениями.
   for( int iword = 1; iword < line.tokenization.Count - 1; ++iword )
   {
    string mustbe = string.Empty;

    int ekey = line.morphology[iword].GetEntryID();
    string ename = gren.GetEntryName( ekey );

    if( IsUnknownLexem( ename ) ) // не будем учитывать ошибки лемматизации для не-словарных лексем.
     continue;

    mustbe = ename.ToLower();

    if( mustbe != lemmas[iword] )
     error_count_with_ngram++;

    int ekey0 = line.morphology[iword].GetEntryID();
    string ename0 = gren.GetEntryName( ekey0 );
    if( IsUnknownLexem( ename0 ) )
     continue;

    string lemma0 = word2lemmas[iword][0];

    if( mustbe != lemma0 )
     error_count_no_filter++;
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


 private int segment;
 System.IO.StreamWriter model_file;
 System.IO.StreamWriter list_file;

 private void OpenModelFiles()
 {
  model_file = new System.IO.StreamWriter( "lemm_model.sol", false, new System.Text.UTF8Encoding( true ) );
  list_file = new System.IO.StreamWriter( "lemm_model.files", false, new System.Text.UTF8Encoding( true ) );
  list_file.WriteLine( "lemm_model.sol" );
 }

 private void CloseModelFiles()
 {
  model_file.Close();
  list_file.Close();
 }

 private void ReopenCurrentModelFile()
 {
  if( model_file.BaseStream.Position > 4000000 )
  {
   model_file.WriteLine( "\n}" );
   model_file.Close();

   segment++;
   string fname = string.Format( "lemm_model_{0}.sol", segment );
   model_file = new System.IO.StreamWriter( fname, false, new System.Text.UTF8Encoding( true ) );
   list_file.WriteLine( "{0}", fname );
   model_file.WriteLine( "automat lemmatizer\n{\n" );
  }
 }

 public void StoreModel()
 {
  OpenModelFiles();

  try
  {
   model_file.WriteLine( "// date: {0}", System.DateTime.Now );
   model_file.WriteLine( "// n_learn_samples={0}", n_learn_samples );
   model_file.WriteLine( "// n_test_samples={0}", n_test_samples );
   model_file.WriteLine( "// total_check_word_count={0}", total_word_count );
   model_file.WriteLine( "// error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent( error_count_no_filter, total_word_count ) );
   model_file.WriteLine( "// error_count_with_ngram={0}, i.e. {1}%", error_count_with_ngram, PercentFormatter.Percent( error_count_with_ngram, total_word_count ) );

   model_file.WriteLine( "automat lemmatizer\n{\n" );
   model_file.WriteLine( "suffix_len {0}", MAX_SUFFIX_LEN );

   foreach( KeyValuePair<string, int> p in suffices )
   {
    ReopenCurrentModelFile();

    if( p.Key[0] == '~' )
     model_file.WriteLine( " suffix {0} \"{1}\"", p.Value, p.Key.Substring( 1 ) );
    else if( p.Key == "\"" )
     model_file.WriteLine( " word {0} \"\\\"\"", p.Value );
    else
     model_file.WriteLine( " word {0} \"{1}\"", p.Value, p.Key );
   }

   model_file.WriteLine( "\n\n" );

   // ------------------- 2-граммы

   model_file.WriteLine( "// {0} 2grams", ngram2.Count );
   foreach( KeyValuePair<NGram2, int> n2 in ngram2 )
   {
    ReopenCurrentModelFile();
    model_file.WriteLine( " ngram2 {0} {1} {2}", n2.Key.tags0, n2.Key.tags1, n2.Value );
   }

   model_file.WriteLine( "// {0} 2grams_1", ngram2_1.Count );
   foreach( KeyValuePair<NGram2, int> n2 in ngram2_1 )
   {
    ReopenCurrentModelFile();
    model_file.WriteLine( " ngram2_1 {0} {1} {2}", n2.Key.tags0, n2.Key.tags1, n2.Value );
   }

   // ------------------- 3-граммы

   model_file.WriteLine( "// {0} 3grams", ngram3.Count );
   foreach( KeyValuePair<NGram3, int> n3 in ngram3 )
   {
    ReopenCurrentModelFile();
    model_file.WriteLine( " ngram3 {0} {1} {2} {3}", n3.Key.tags0, n3.Key.tags1, n3.Key.tags2, n3.Value );
   }

   model_file.WriteLine( "// {0} 3grams_1", ngram3_1.Count );
   foreach( KeyValuePair<NGram3, int> n3 in ngram3_1 )
   {
    ReopenCurrentModelFile();
    model_file.WriteLine( " ngram3_1 {0} {1} {2} {3}", n3.Key.tags0, n3.Key.tags1, n3.Key.tags2, n3.Value );
   }

   model_file.WriteLine( "// {0} 3grams_2", ngram3_2.Count );
   foreach( KeyValuePair<NGram3, int> n3 in ngram3_2 )
   {
    ReopenCurrentModelFile();
    model_file.WriteLine( " ngram3_2 {0} {1} {2} {3}", n3.Key.tags0, n3.Key.tags1, n3.Key.tags2, n3.Value );
   }

   // ------------------- 4-граммы

   model_file.WriteLine( "// {0} 4grams", ngram4.Count );
   foreach( KeyValuePair<NGram4, int> n4 in ngram4 )
   {
    ReopenCurrentModelFile();
    model_file.WriteLine( " ngram4 {0} {1} {2} {3} {4}", n4.Key.tags0, n4.Key.tags1, n4.Key.tags2, n4.Key.tags3, n4.Value );
   }

   model_file.WriteLine( "\n\n" );

   model_file.WriteLine( "}" );
  }
  finally
  {
   CloseModelFiles();
  }

  return;
 }



 public void StoreModel_SQL( System.IO.StreamWriter model_file )
 {
  foreach( KeyValuePair<string, int> p in suffices )
  {
   if( p.Key[0] == '-' )
    model_file.WriteLine( "insert into lemm_suffix(suffix,id) values ('{1}',{0});", p.Value, p.Key.Substring( 1 ) );
   else
    model_file.WriteLine( "insert into lemm_word(word,id) values ('{1}',{0});", p.Value, p.Key );
  }

  model_file.WriteLine( "\n\n" );

  foreach( KeyValuePair<NGram2, int> n2 in ngram2 )
  {
   model_file.WriteLine( "insert into lemm_ngram2(i1,i2,score) values ({0},{1},{2})", n2.Key.tags0, n2.Key.tags1, n2.Value );
  }


  foreach( KeyValuePair<NGram3, int> n3 in ngram3 )
  {
   model_file.WriteLine( "insert into lemm_ngram3(i1,i2,i3,score) values ({0},{1},{2},{3})", n3.Key.tags0, n3.Key.tags1, n3.Key.tags2, n3.Value );
  }

  model_file.WriteLine( "// {0} 4grams", ngram4.Count );
  foreach( KeyValuePair<NGram4, int> n4 in ngram4 )
  {
   model_file.WriteLine( "insert into lemm_ngram3(i1,i2,i3,i4,score) values ({0},{1},{2},{3},{4})", n4.Key.tags0, n4.Key.tags1, n4.Key.tags2, n4.Key.tags3, n4.Value );
  }

  model_file.WriteLine( "\n\n" );

  return;
 }

}

