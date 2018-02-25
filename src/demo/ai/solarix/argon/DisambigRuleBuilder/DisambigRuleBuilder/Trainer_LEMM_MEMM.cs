using System.Collections.Generic;


class Trainer_LEMM_MEMM
{
 // ОСНОВНЫЕ НАСТРОЕЧНЫЕ ПАРАМЕТРЫ МОДЕЛИ
 private const int MAX_SUFFIX_LEN = 4; // длина окончания для форм
 private const int MAX_SUFFIX_LEMMA_LEN = 4; // длина окончания для лемм



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

 public Trainer_LEMM_MEMM()
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

 string GetSuffixById( int id ) { return id2suffix[id]; }

 private string GetTokenSuffix( int pos, int last_word_index, SolarixGrammarEngineNET.SyntaxTreeNode token )
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
   string word = token.GetWord().ToLower();
   string suffix = GetSuffix( word );
   return suffix;
  }
 }


 private string GetTokenSuffix( int pos, int last_word_index, string word )
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
   string suffix = GetSuffix( word2 );
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

 int n_learn_samples = 0;

 System.IO.StreamWriter train_file, test_file, tokens_file;
 string train_file_path = "lemm.maxent.txt";
 string test_file_path = "lemm.maxent.test.txt";
 string tokens_file_path = "tokens.txt";

 void OpenTrainFile()
 {
  if( train_file == null )
  {
   train_file = new System.IO.StreamWriter( train_file_path );
   test_file = new System.IO.StreamWriter( test_file_path );
  }

  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string tag4, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{4} {0} {1} {2} {3}", tag1, tag2, tag3, tag4, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{3} {0} {1} {2}", tag1, tag2, tag3, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string tag4, string tag5, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{5} {0} {1} {2} {3} {4}", tag1, tag2, tag3, tag4, tag5, result );
  return;
 }

 void WriteTest( string tag1, string tag2, string tag3, string tag4, string result )
 {
  OpenTrainFile();
  test_file.WriteLine( "{4} {0} {1} {2} {3}", tag1, tag2, tag3, tag4, result );
  return;
 }

 void WriteTest( string tag1, string tag2, string tag3, string tag4, string tag5, string result )
 {
  OpenTrainFile();
  test_file.WriteLine( "{5} {0} {1} {2} {3} {4}", tag1, tag2, tag3, tag4, tag5, result );
  return;
 }

 void WriteTest( string tag1, string tag2, string tag3, string result )
 {
  OpenTrainFile();
  test_file.WriteLine( "{3} {0} {1} {2}", tag1, tag2, tag3, result );
  return;
 }

 void WriteTestEOS()
 {
  OpenTrainFile();
  //test_file.WriteLine( "" );
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

 string LemmaLabel( int offset, int tag_id )
 {
  if( offset < 0 )
   return string.Format( "prevlemm_{0}_{1}", -offset, tag_id );
  else if( offset == 0 )
   return string.Format( "thislemm_{0}", tag_id );
  else
   return string.Format( "nextlemm_{0}_{1}", offset, tag_id );
 }

 string ResultLabel( int tag_id )
 {
  string s = string.Format( "{0}", tag_id );
  return s;
 }

 List<string> test_samples = new List<string>();
 List<int> test_sample_token_counts = new List<int>();

 public bool ProcessSample( string line )
 {
  n_learn_samples++;

  if( tokens_file == null )
   tokens_file = new System.IO.StreamWriter( tokens_file_path );

  // чтобы получить все возможные теги, надо для каждого слова получить все возможные распознавания.
  using( SolarixGrammarEngineNET.AnalysisResults projs = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY ) )
  {
   int last_word_index = projs.Count - 1;

   for( int iword = 0; iword < projs.Count; ++iword )
   {
    for( int iproj = 0; iproj < projs[iword].VersionCount(); ++iproj )
    {
     string lemma = string.Empty;
     int ekey = projs[iword].GetVersionEntryID( iproj );
     string ename = gren.GetEntryName( ekey );
     if( IsUnknownLexem( ename ) )
      lemma = projs[iword].GetWord().ToLower();
     else
      lemma = ename.ToLower();

     string sfx1 = GetTokenSuffix( iword, last_word_index, lemma );
     int id1 = MatchSuffix( sfx1, true );

     string sfx2 = GetTokenLemmaSuffix( iword, last_word_index, lemma );
     int id2 = MatchSuffix( sfx2, true );
    }
   }
  }


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

    if( iword > 0 && iword < tokens.Count - 1 )
    {
     tokens_file.Write( "{0}", word );

     // все допустимые варианты лемматизации
     int nlemma = 0;
     for( int j = 0; j < tokens[iword].VersionCount(); ++j )
     {
      int id_entry = tokens[iword].GetVersionEntryID( j );
      string ename2 = gren.GetEntryName( id_entry );

      if( IsUnknownLexem( ename2 ) ) // не будем учитывать ошибки лемматизации для не-словарных лексем.
       continue;

      tokens_file.Write( "\t{0}", ename2 );

      nlemma++;
     }

     if( nlemma == 0 )
      tokens_file.Write( "\t{0}", word );

     tokens_file.WriteLine( "" );
    }

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

    string lemma_suffix = GetTokenLemmaSuffix( iword, last_word_index, lemma );
    sfx_lemma.Add( lemma_suffix );
    sfx_lemma_index.Add( MatchSuffix( lemma_suffix, true ) );
   }
   tokens_file.WriteLine( "" );

   for( int iword = 1; iword < tokens.Count - 1; ++iword )
   {
    string res = ResultLabel( sfx_lemma_index[iword] );

    //string tag0 = LemmaLabel( -1, sfx_lemma_index[iword - 1] ); // для Витерби в MEMM

    if( iword > 1 && iword < tokens.Count - 2 )
    {
     string tag1 = TagLabel( -2, sfx_index[iword - 2] );
     string tag2 = TagLabel( -1, sfx_index[iword - 1] );
     string tag3 = TagLabel( 0, sfx_index[iword] );
     string tag4 = TagLabel( 1, sfx_index[iword + 1] );
     string tag5 = TagLabel( 2, sfx_index[iword + 2] );

     WriteTrain( tag1, tag2, tag3, tag4, tag5, res );
     WriteTest( tag1, tag2, tag3, tag4, tag5, res );
    }
    else
    {
     string tag2 = TagLabel( -1, sfx_index[iword - 1] );
     string tag3 = TagLabel( 0, sfx_index[iword] );
     string tag4 = TagLabel( 1, sfx_index[iword + 1] );

     WriteTrain( tag2, tag3, tag4, res );
     WriteTest( tag2, tag3, tag4, res );
    }
   }

   WriteTestEOS();
  }

  return true;
 }


 public void FinishLearning()
 {
  train_file.Close();
  train_file = null;

  test_file.Close();
  test_file = null;

  tokens_file.Close();
  tokens_file = null;

  string input_file = string.Format( "{0}\\{1}", System.IO.Directory.GetCurrentDirectory(), train_file_path );
  string cmd = string.Format( "{0}\\maxent_train.cmd", System.IO.Directory.GetCurrentDirectory() );

  System.Diagnostics.Process p = new System.Diagnostics.Process();
  p.StartInfo.Arguments = string.Format( "\"{0}\" \"{1}\"", input_file, "lemm.model" );
  p.StartInfo.FileName = cmd;
  bool r = p.Start();
  p.WaitForExit();

  return;
 }




 int raw_model_error_count = 0;
 public void FinishTesting()
 {
  // теперь получем через обученную модель для каждого тестового предложения предсказываемую лемму
  string input_file = string.Format( "{0}\\{1}", System.IO.Directory.GetCurrentDirectory(), test_file_path );
  string test_output_file = string.Format( "{0}\\test_result.txt", System.IO.Directory.GetCurrentDirectory() );
  string cmd = string.Format( "{0}\\maxent_test.cmd", System.IO.Directory.GetCurrentDirectory() );

  System.Diagnostics.Process p = new System.Diagnostics.Process();
  p.StartInfo.Arguments = string.Format( "\"{0}\" \"{1}\" lemm.model", input_file, test_output_file );
  p.StartInfo.FileName = cmd;
  bool r = p.Start();
  p.WaitForExit();

  using( System.IO.StreamReader rdr = new System.IO.StreamReader( test_output_file ) )
  {
   using( System.IO.StreamReader rdr_tokens = new System.IO.StreamReader( tokens_file_path ) )
   {
    int sent_count = 0;
    while( !rdr.EndOfStream && sent_count < test_samples.Count )
    {
     int ntoken = test_sample_token_counts[sent_count];

     List<int> model_lemma_ids = new List<int>();
     List<string> tokens = new List<string>();
     List<List<string>> token_lemmas = new List<List<string>>();

     // нам нужен начальный токен
     tokens.Add( "$BEGIN" );
     token_lemmas.Add( new List<string>() );
     model_lemma_ids.Add( MatchSuffix( GetStartLemmaSuffix(), false ) );

     for( int i = 0; i < ntoken - 2; ++i )
     {
      string line = rdr.ReadLine();
      string[] toks = line.Split( ' ' );
      string required_lemma_id = toks[0];
      string model_lemma_id = toks[1];
      model_lemma_ids.Add( int.Parse( model_lemma_id ) );

      if( required_lemma_id != model_lemma_id )
       raw_model_error_count++;

      line = rdr_tokens.ReadLine();
      string[] ltoks = line.Split( '\t' );
      tokens.Add( ltoks[0] );

      List<string> lx = new List<string>();
      for( int j = 1; j < ltoks.Length; ++j )
       lx.Add( ltoks[j] );

      token_lemmas.Add( lx );
     }

     tokens.Add( "$END" );
     token_lemmas.Add( new List<string>() );
     model_lemma_ids.Add( MatchSuffix( GetEndLemmaSuffix(), false ) );

     //     string empty_line = rdr.ReadLine();
     //     if( empty_line.Length != 0 )
     //      throw new System.ApplicationException();

     string empty_line = rdr_tokens.ReadLine();
     if( empty_line.Length != 0 )
      throw new System.ApplicationException();

     string sent = test_samples[sent_count];
     System.Console.WriteLine( "1.{0} {1}", sent_count, sent );
     Check( tokens, token_lemmas, model_lemma_ids );

     sent_count++;
    }
   }
  }

  return;
 }


 int total_word_count = 0;
 int error_count_with_ngram = 0;

 public void Check(
                   List<string> words, // исходные слова
                   List<List<string>> word_lemmas, // точные леммы для слов (может быть несколько вариантов на 1 слово)
                   List<int> model_lemma_ids // id суффиксов лемм, которые предсказала модель
                  )
 {
  System.Text.StringBuilder b = new System.Text.StringBuilder();
  b.Capacity = 100;

  for( int iword = 0; iword < words.Count; ++iword )
  {
   string word = words[iword];
   bool hit = false;

   // для данного слова получаем варианты лемматизации (wx) и id суффиксов для этих вариантов (ids)

   if( iword > 0 && iword < words.Count - 1 )
   {
    total_word_count++;

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
      hit = true;
      break;
     }
    }

    if( !hit )
    {
     System.Text.StringBuilder txt = new System.Text.StringBuilder();
     txt.Append( "Полученные леммы для слова:" );
     for( int i = 0; i < nlemma; ++i )
     {
      b.Length = 0;
      SolarixLemmatizatorEngineNET.LemmatizatorEngine.sol_GetLemmaStringW( hLemmas, i, b, b.Capacity );
      string lemma = b.ToString().ToLower();
      txt.AppendFormat( " {0}", lemma );
     }

     txt.Append( "\n Ожидаемые варианты лемм:" );
     for( int j = 0; j < word_lemmas[iword].Count; ++j )
     {
      txt.AppendFormat( " {0}", word_lemmas[iword][j] );
     }

     txt.Append( "\n" );

     string model_suffix = GetSuffixById( model_lemma_ids[iword] );
     txt.AppendFormat( " Model suffix: {0}", model_suffix );

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
  System.Console.WriteLine( "raw_model_error_count={0}, i.e. {1}%", raw_model_error_count, PercentFormatter.Percent( raw_model_error_count, total_word_count ) );
  System.Console.WriteLine( "error_count_with_ngram={0}, i.e. {1}%", error_count_with_ngram, PercentFormatter.Percent( error_count_with_ngram, total_word_count ) );
  return;
 }

}
