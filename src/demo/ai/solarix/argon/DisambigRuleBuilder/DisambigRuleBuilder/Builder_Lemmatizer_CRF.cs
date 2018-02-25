using System.Collections.Generic;


class Builder_LEMM_CRF
{
 // ОСНОВНЫЕ НАСТРОЕЧНЫЕ ПАРАМЕТРЫ МОДЕЛИ
 private const int MAX_SUFFIX_LEN = 4; // длина окончания для форм
 private const int MAX_SUFFIX_LEMMA_LEN = 2; // длина окончания для лемм

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

 string GetLemmaByLabel( string label )
 {
  return id2suffix[int.Parse( label )];
 }


 public Builder_LEMM_CRF()
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


 private string GetSuffix( string word )
 {
  if( undevidable_words.Contains( word ) )
   return word;

  if( word.Length > MAX_SUFFIX_LEN )
   return "~" + word.Substring( word.Length - MAX_SUFFIX_LEN );
  else
   return word;
 }

 private string GetLemmaSuffix( string word )
 {
  if( undevidable_words.Contains( word ) )
   return word;

  if( word.Length > MAX_SUFFIX_LEMMA_LEN )
   return "~" + word.Substring( word.Length - MAX_SUFFIX_LEMMA_LEN );
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



 private string GetTokenLemmaSuffix( int pos, int last_word_index, string word )
 {
  if( pos <= 0 )
  {
   string sfx = GetStartLemmaSuffix();
   return sfx;
  }
  else if( pos >= last_word_index )
  {
   string sfx = GetEndLemmaSuffix(); ;
   return sfx;
  }
  else
  {
   string word2 = word.ToLower();
   string suffix = GetLemmaSuffix( word2 );
   return suffix;
  }
 }

 string GetTokenVersionLemma( int version_index, SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  string lemma = string.Empty;
  int ekey = token.GetVersionEntryID( version_index );
  string ename = gren.GetEntryName( ekey );
  if( IsUnknownLexem( ename ) )
   lemma = token.GetWord().ToLower();
  else
   lemma = ename.ToLower();

  return lemma;
 }

 int n_learn_samples = 0;

 System.IO.StreamWriter train_file;
 string train_file_path = "lemm.crf.txt";
 void OpenTrainFile()
 {
  if( train_file == null )
   train_file = new System.IO.StreamWriter( train_file_path );

  return;
 }

 List<string> test_samples = new List<string>();
 List<int> test_sample_token_counts = new List<int>();

 void WriteEOS()
 {
  OpenTrainFile();
  train_file.WriteLine( "" );
  return;
 }

 void WriteTrain( string tag1, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{1}\t{0}", tag1, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{2}\t{0}\t{1}", tag1, tag2, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{3}\t{0}\t{1}\t{2}", tag1, tag2, tag3, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string tag4, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{4}\t{0}\t{1}\t{2}\t{3}", tag1, tag2, tag3, tag4, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string tag4, string tag5, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{5}\t{0}\t{1}\t{2}\t{3}\t{4}", tag1, tag2, tag3, tag4, tag5, result );
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

 string ResultLabel( int tag_id )
 {
  string s = string.Format( "lemma={0}", tag_id );
  return s;
 }


 public bool ProcessSample( string line )
 {
  n_learn_samples++;

  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   test_samples.Add( line );
   test_sample_token_counts.Add( tokens.Count );

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

    string lemma_suffix = GetLemmaSuffix( lemma );
    sfx_lemma.Add( lemma_suffix );
    sfx_lemma_index.Add( MatchSuffix( lemma_suffix, true ) );
   }

   for( int iword = 1; iword < tokens.Count - 1; ++iword )
   {
    if( iword == 0 || iword == tokens.Count - 1 )
    {
     string tag = TagLabel( 0, sfx_index[iword] );
     string res = ResultLabel( sfx_lemma_index[iword] );
     WriteTrain( tag, res );
    }/*
    else if( iword > 1 && iword < tokens.Count - 2 )
    {
     string tag1 = TagLabel( -2, sfx_index[iword - 2] );
     string tag2 = TagLabel( -1, sfx_index[iword - 1] );
     string tag3 = TagLabel( 0, sfx_index[iword] );
     string tag4 = TagLabel( 1, sfx_index[iword + 1] );
     string tag5 = TagLabel( 2, sfx_index[iword + 2] );
     string res = ResultLabel( sfx_lemma_index[iword] );
     WriteTrain( tag1, tag2, tag3, tag4, tag5, res );
    }*/
    else
    {
     string tag1 = TagLabel( -1, sfx_index[iword - 1] );
     string tag2 = TagLabel( 0, sfx_index[iword] );
     string tag3 = TagLabel( 1, sfx_index[iword + 1] );

     string res = ResultLabel( sfx_lemma_index[iword] );
     WriteTrain( tag1, tag2, tag3, res );
    }
   }

   WriteEOS();
  }

  return true;
 }


 int total_word_count = 0;
 int error_count_no_filter = 0;
 int error_count_with_ngram = 0;

 public void FinishLearning()
 {
  train_file.Close();
  train_file = null;

  // тренируем модель
  string input_file = string.Format( "{0}\\{1}", System.IO.Directory.GetCurrentDirectory(), train_file_path );
  string output_file = string.Format( "{0}\\test_result.txt", System.IO.Directory.GetCurrentDirectory() );
  string cmd = string.Format( "{0}\\crfsuite_lemm_train.cmd", System.IO.Directory.GetCurrentDirectory() );

  System.Diagnostics.Process p = new System.Diagnostics.Process();
  p.StartInfo.Arguments = string.Format( "\"{0}\" \"{1}\"", input_file, output_file );
  p.StartInfo.FileName = cmd;
  bool r = p.Start();
  p.WaitForExit();

  return;
 }




 int raw_model_error_count = 0;
 public void FinishTesting()
 {
  // теперь получем через обученную модель для каждого тестового предложения предсказываемую лемму
  string error_file = string.Format( "{0}\\crf_errors.txt", System.IO.Directory.GetCurrentDirectory() );

  string input_file = string.Format( "{0}\\{1}", System.IO.Directory.GetCurrentDirectory(), train_file_path );
  string test_output_file = string.Format( "{0}\\test_result.txt", System.IO.Directory.GetCurrentDirectory() );
  string cmd = string.Format( "{0}\\crfsuite_lemm_test.cmd", System.IO.Directory.GetCurrentDirectory() );

  System.Diagnostics.Process p = new System.Diagnostics.Process();
  p.StartInfo.Arguments = string.Format( "\"{0}\" \"{1}\"", input_file, test_output_file );
  p.StartInfo.FileName = cmd;
  bool r = p.Start();
  p.WaitForExit();

  using( System.IO.StreamReader rdr = new System.IO.StreamReader( test_output_file ) )
  {
   int sent_count = 0;
   while( !rdr.EndOfStream && sent_count < test_samples.Count )
   {
    int ntoken = test_sample_token_counts[sent_count];

    List<int> model_lemma_ids = new List<int>();

    model_lemma_ids.Add( -100 );
    for( int i = 0; i < ntoken - 2; ++i )
    {
     string line = rdr.ReadLine();
     string[] toks = line.Split( '\t' );
     string required_lemma_id = toks[0].Split( '=' )[1];
     string model_lemma_id = toks[1].Split( '=' )[1];
     model_lemma_ids.Add( int.Parse( model_lemma_id ) );

     if( required_lemma_id != model_lemma_id )
     {
      string model_lemma_suffix = id2suffix[int.Parse( model_lemma_id )];
      string required_lemma_suffix = id2suffix[int.Parse( required_lemma_id )];

      raw_model_error_count++;
     }
    }
    model_lemma_ids.Add( -100 );

    string empty_line = rdr.ReadLine();
    if( empty_line.Length != 0 )
     throw new System.ApplicationException();

    string sent = test_samples[sent_count];
    System.Console.WriteLine( "1.{0} {1}", sent_count, sent );
    Check( sent, model_lemma_ids );

    sent_count++;
   }
  }

  return;
 }


 /*
  public void Check( string line, List<int> model_lemma_ids )
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

     // model_lemma_ids - это те леммы, которые выбраны моделью.
     for( int iword = 1; iword < projs.Count - 1; ++iword )
     {
      // теперь перебираем проекции и смотрим, которая из них имеет в нормальной форме выбранный суффикс.
      for( int iproj = 0; iproj < word2lemmas[iword].Count; ++iproj )
      {
       string ename = word2lemmas[iword][iproj];
       string proj_suffix = GetSuffix( ename.ToLower() );
       int id_suffix = MatchSuffix( proj_suffix, false );
       if( id_suffix == -1 )
        continue;

       if( id_suffix == model_lemma_ids[iword] )
       {
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



 public void Check( string line, List<int> model_lemma_ids )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   total_word_count += tokens.Count - 2;

   System.Text.StringBuilder b = new System.Text.StringBuilder();
   b.Capacity = 100;

   int last_word_index = tokens.Count - 1;

   for( int iword = 1; iword < tokens.Count - 1; ++iword )
   {
    string word = tokens[iword].GetWord();

    bool hit = false;

    System.IntPtr hLemmas = SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_GetLemmasW( lemm_engine, word );
    if( hLemmas == System.IntPtr.Zero )
     throw new System.ApplicationException();

    int nlemma = SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_CountLemmas( hLemmas );
    for( int i = 0; i < nlemma; ++i )
    {
     b.Length = 0;
     SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_GetLemmaStringW( hLemmas, i, b, b.Capacity );

     string lemma = b.ToString().ToLower();

     int id_lemma = MatchSuffix( GetLemmaSuffix( lemma ), false );
     if( id_lemma == -1 )
      continue;

     if( model_lemma_ids[iword] == id_lemma )
     {
      // модель выбрала эту лемму. сравним с вариантами точных лемм.
      bool found_lemma = false;
      for( int j = 0; j < tokens[iword].VersionCount(); ++j )
      {
       string version_lemma = GetTokenVersionLemma( j, tokens[iword] );
       string version_suffix = GetLemmaSuffix( version_lemma );
       int version_id = MatchSuffix( version_suffix, true );
       if( version_id == id_lemma )
       {
        found_lemma = true;
        break;
       }
      }

      hit = found_lemma;
      break;
     }
    }

    if( !hit )
    {
     error_count_with_ngram++;
    }

    SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_DeleteLemmas( hLemmas );
   }
  }

  return;
 }




 public void PrintTestResults()
 {
  System.Console.WriteLine( "total_check_word_count={0}", total_word_count );
  System.Console.WriteLine( "error_count_no_filter={0}, i.e. {1}%", error_count_no_filter, PercentFormatter.Percent( error_count_no_filter, total_word_count ) );
  System.Console.WriteLine( "raw_model_error_count={0}, i.e. {1}%", raw_model_error_count, PercentFormatter.Percent( raw_model_error_count, total_word_count ) );
  System.Console.WriteLine( "error_count_with_ngram={0}, i.e. {1}%", error_count_with_ngram, PercentFormatter.Percent( error_count_with_ngram, total_word_count ) );
  return;
 }
}
