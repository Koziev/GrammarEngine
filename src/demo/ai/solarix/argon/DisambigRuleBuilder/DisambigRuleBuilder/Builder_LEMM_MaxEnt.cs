using System.Collections.Generic;


class Builder_LEMM_MaxEnt
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

 public Builder_LEMM_MaxEnt()
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

 System.IntPtr lemm_engine;
 public void LoadLemmatizer( string filepath )
 {
  lemm_engine = SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_LoadLemmatizatorW( filepath, SolarixLemmatizatorEngineNET.LemmatizatorEngine.LEME_FASTEST );
  if( lemm_engine == System.IntPtr.Zero )
   throw new System.ApplicationException( string.Format( "Can not load lemmatizer from {0}", filepath ) );

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


 private const int MAX_SUFFIX_LEN = 2;
 private string GetSuffix( string word )
 {
  if( undevidable_words.Contains( word ) )
   return word;

  if( word.Length > MAX_SUFFIX_LEN )
   return "~" + word.Substring( word.Length - MAX_SUFFIX_LEN );
  else
   return word;
 }


 private string GetStartLemmaSuffix() { return "~~BEGIN~~"; }
 private string GetEndLemmaSuffix() { return "~~END~~"; }


 private string GetTokenSuffix( int pos, int last_word_index, SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  if( pos == 0 )
  {
   string sfx = GetStartLemmaSuffix();
   return sfx;
  }
  else if( pos == last_word_index )
  {
   string sfx = GetEndLemmaSuffix();
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

 System.IO.StreamWriter train_file;
 string train_file_path = "lemm.maxent.txt";

 System.IO.StreamWriter train_file2;
 string train_file_path2 = "lemm.maxent.2.txt";

 void OpenTrainFile()
 {
  if( train_file == null )
  {
   train_file = new System.IO.StreamWriter( train_file_path );
   train_file2 = new System.IO.StreamWriter( train_file_path2 );
  }

  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{0} {1} {2} {3}", tag1, tag2, tag3, result );
  train_file2.WriteLine( "{3} {0} {1} {2}", tag1, tag2, tag3, result );
  return;
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

 HashSet<string> result_labels = new HashSet<string>();

 string ResultLabel( int tag_id )
 {
  string s = string.Format( "lemma_{0}", tag_id );
  result_labels.Add( s );
  return s;
 }


 public bool ProcessSample( string line )
 {
  n_learn_samples++;

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

   for( int iword = 1; iword < tokens.Count - 1; ++iword )
   {
    string tag1 = TagLabel( -1, sfx_index[iword - 1] );
    string tag2 = TagLabel( 0, sfx_index[iword] );
    string tag3 = TagLabel( 1, sfx_index[iword + 1] );

    string res = ResultLabel( sfx_lemma_index[iword] );
    WriteTrain( tag1, tag2, tag3, res );
   }
  }

  return true;
 }


 int total_word_count = 0;
 int raw_model_error_count=0;
 int error_count_no_filter = 0;
 int error_count_with_ngram = 0;
 Dictionary<string, int> result_label2id;

 SharpEntropy.GisModel mModel;
 public void FinishLearning()
 {
  train_file.Close();
  train_file = null;

  train_file2.Close();
  train_file2 = null;

  System.IO.StreamReader trainingStreamReader = new System.IO.StreamReader( train_file_path );
  SharpEntropy.ITrainingEventReader eventReader = new SharpEntropy.BasicEventReader( new SharpEntropy.PlainTextByLineDataReader( trainingStreamReader ) );
  SharpEntropy.GisTrainer trainer = new SharpEntropy.GisTrainer();
  System.Console.WriteLine( "Training MaxEnt..." );

  trainer.TrainModel( eventReader );
  mModel = new SharpEntropy.GisModel( trainer );

  string modelDataFile = @"maxent_model.txt";
  //SharpEntropy.IO.BinaryGisModelWriter writer = new SharpEntropy.IO.BinaryGisModelWriter();
  SharpEntropy.IO.PlainTextGisModelWriter writer = new SharpEntropy.IO.PlainTextGisModelWriter();
  writer.Persist( mModel, modelDataFile );

  result_label2id = new Dictionary<string, int>();

  foreach( string label in result_labels )
  {
   int id = mModel.GetOutcomeIndex( label );
   result_label2id.Add( label, id );
  }

  return;
 }



 /*
  public void Check( string line )
  {
   // Морфологический разбор
   using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.SOL_GREN_COMPLETE_ONLY ) )
   {
    // Токенизация без использования синтаксических правил
    using( SolarixGrammarEngineNET.AnalysisResults projs = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.SOL_GREN_TOKENIZE_ONLY ) )
    {
     List<List<int>> word2tags = new List<List<int>>();

     if( projs.Count != tokens.Count )
      return;

     total_word_count += projs.Count - 2;

     // Для каждого слова получим списки альтернативных лемматизаций.
     List<List<string>> word2lemmas = new List<List<string>>();

     List<string> lemmas = new List<string>();

     int last_word_index = projs.Count - 1;

     for( int iword = 0; iword < projs.Count; ++iword )
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
         word_lemmas.Add( lemma );
       }

       word2lemmas.Add( word_lemmas );
      }

      lemmas.Add( word2lemmas[iword][0] );
     }


     for( int iword = 1; iword < projs.Count - 1; ++iword )
     {
      string suffix1 = GetTokenSuffix( iword - 1, last_word_index, projs[iword - 1] );
      int id_suffix1 = MatchSuffix( suffix1, false );
      if( id_suffix1 == -1 )
       continue;

      string suffix2 = GetTokenSuffix( iword, last_word_index, projs[iword] );
      int id_suffix2 = MatchSuffix( suffix2, false );
      if( id_suffix2 == -1 )
       continue;

      string suffix3 = GetTokenSuffix( iword + 1, last_word_index, projs[iword + 1] );
      int id_suffix3 = MatchSuffix( suffix3, false );
      if( id_suffix3 == -1 )
       continue;

      string label1 = TagLabel( -1, id_suffix1 );
      string label2 = TagLabel( 0, id_suffix2 );
      string label3 = TagLabel( 1, id_suffix3 );


      System.Collections.ArrayList context = new System.Collections.ArrayList();
      context.Add( label1 );
      context.Add( label2 );
      context.Add( label3 );

      double[] probabilities = mModel.Evaluate( (string[])context.ToArray( typeof( string ) ) );

      // теперь надо выбрать самый достоверный вариант.
      double best_score = 0;

      // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
      for( int iproj = 0; iproj < word2lemmas[iword].Count; ++iproj )
      {
       string ename = word2lemmas[iword][iproj];
       string proj_suffix = GetSuffix( ename.ToLower() );
       int id_suffix = MatchSuffix( proj_suffix, false );
       if( id_suffix == -1 )
        continue;

       string res_label = ResultLabel( id_suffix );

       if( !result_label2id.ContainsKey( res_label ) )
        continue;

       int res_label_index = result_label2id[res_label];

       double p = probabilities[res_label_index];

       if( p > best_score )
       {
        best_score = p;
        lemmas[iword] = ename.ToLower();
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
 */

 public void Check( string line )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   total_word_count += tokens.Count - 2;

   System.Text.StringBuilder b = new System.Text.StringBuilder();
   b.Capacity = 100;

   // Для каждого слова получим списки альтернативных лемматизаций.
   List<List<string>> word2lemmas = new List<List<string>>();

   List<string> lemmas = new List<string>();
   List<int> model_lemma_id = new List<int>();

   int last_word_index = tokens.Count - 1;

   for( int iword = 0; iword < tokens.Count; ++iword )
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

     string word = tokens[iword].GetWord();
     System.IntPtr hLemmas = SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_GetLemmasW( lemm_engine, word );
     if( hLemmas == System.IntPtr.Zero )
      throw new System.ApplicationException();

     int nlemma = SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_CountLemmas( hLemmas );
     for( int i = 0; i < nlemma; ++i )
     {
      b.Length = 0;
      SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_GetLemmaStringW( hLemmas, i, b, b.Capacity );

      string lemma = b.ToString().ToLower();

      if( !word_lemmas.Contains( lemma ) )
       word_lemmas.Add( lemma );
     }
     SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_DeleteLemmas( hLemmas );

     word2lemmas.Add( word_lemmas );
    }

    lemmas.Add( word2lemmas[iword][0] );
    model_lemma_id.Add(0);
   }

   for( int iword = 1; iword < tokens.Count - 1; ++iword )
   {
    string suffix1 = GetTokenSuffix( iword - 1, last_word_index, tokens[iword - 1] );
    int id_suffix1 = MatchSuffix( suffix1, false );
    if( id_suffix1 == -1 )
     continue;

    string suffix2 = GetTokenSuffix( iword, last_word_index, tokens[iword] );
    int id_suffix2 = MatchSuffix( suffix2, false );
    if( id_suffix2 == -1 )
     continue;

    string suffix3 = GetTokenSuffix( iword + 1, last_word_index, tokens[iword + 1] );
    int id_suffix3 = MatchSuffix( suffix3, false );
    if( id_suffix3 == -1 )
     continue;

    string label1 = TagLabel( -1, id_suffix1 );
    string label2 = TagLabel( 0, id_suffix2 );
    string label3 = TagLabel( 1, id_suffix3 );


    System.Collections.ArrayList context = new System.Collections.ArrayList();
    context.Add( label1 );
    context.Add( label2 );
    context.Add( label3 );

    double[] probabilities = mModel.Evaluate( (string[])context.ToArray( typeof( string ) ) );

    // теперь надо выбрать самый достоверный вариант.
    double best_score = 0;

    // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
    for( int iproj = 0; iproj < word2lemmas[iword].Count; ++iproj )
    {
     string ename = word2lemmas[iword][iproj];
     string proj_suffix = GetSuffix( ename.ToLower() );
     int id_suffix = MatchSuffix( proj_suffix, false );
     if( id_suffix == -1 )
      continue;

     string res_label = ResultLabel( id_suffix );

     if( !result_label2id.ContainsKey( res_label ) )
      continue;

     int res_label_index = result_label2id[res_label];

     double p = probabilities[res_label_index];

     if( p > best_score )
     {
      best_score = p;
      model_lemma_id[iword] = id_suffix;
      lemmas[iword] = ename.ToLower();
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

    // отдельно считаем все ошибки модели, так как часть из них могут быть
    // скрыты при выборе леммы в случаях, когда есть только один правильный вариант леммы, и он не совпадает с выбором модели.
    string mustbe_suffix = GetSuffix( mustbe );
    int mustbe_id_suffix = MatchSuffix( mustbe_suffix, false );
    if( mustbe_id_suffix!=model_lemma_id[iword] )
     raw_model_error_count++;

    if( mustbe != lemmas[iword] )
     error_count_with_ngram++;

    string lemma0 = word2lemmas[iword][0].ToLower();

    if( mustbe != lemma0 )
     error_count_no_filter++;
   }
  }

  return;
 }


 public void PrintTestResults()
 {
  System.Console.WriteLine( "total_check_word_count={0}", total_word_count );
  System.Console.WriteLine( "raw_model_error_count={0}, i.e. {1}%", raw_model_error_count, PercentFormatter.Percent( raw_model_error_count, total_word_count ) );
  System.Console.WriteLine( "error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent( error_count_no_filter, total_word_count ) );
  System.Console.WriteLine( "error_count_with_ngram={0}, i.e. {1}%", error_count_with_ngram, PercentFormatter.Percent( error_count_with_ngram, total_word_count ) );

  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "report.txt" ) )
  {
   wr.WriteLine( "total_check_word_count={0}", total_word_count );
   wr.WriteLine( "raw_model_error_count={0}, i.e. {1}%", raw_model_error_count, PercentFormatter.Percent( raw_model_error_count, total_word_count ) );
   wr.WriteLine( "error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent( error_count_no_filter, total_word_count ) );
   wr.WriteLine( "error_count_with_ngram={0}, i.e. {1}%", error_count_with_ngram, PercentFormatter.Percent( error_count_with_ngram, total_word_count ) );
  }

  return;
 }

 public void StoreModel()
 {
  // ...
  return;
 }


}
