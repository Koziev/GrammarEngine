using System.Collections.Generic;


class Builder_LEMM_MEMM
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

 public Builder_LEMM_MEMM()
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

 private string GetStartLemmaSuffix() { return "~~BEGIN~~"; }
 private string GetEndLemmaSuffix() { return "~~END~~"; }


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

 int n_learn_samples = 0;

 System.IO.StreamWriter train_file;
 string train_file_path = "lemm.maxent.txt";
 void OpenTrainFile()
 {
  if( train_file == null )
   train_file = new System.IO.StreamWriter( train_file_path );

  return;
 }

 void WriteTrain( string tag1, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{0} {1}", tag1, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{0} {1} {2}", tag1, tag2, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{0} {1} {2} {3}", tag1, tag2, tag3, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string tag4, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{0} {1} {2} {3} {4}", tag1, tag2, tag3, tag4, result );
  return;
 }

 void WriteTrain( string tag1, string tag2, string tag3, string tag4, string tag5, string result )
 {
  OpenTrainFile();
  train_file.WriteLine( "{0} {1} {2} {3} {4} {5}", tag1, tag2, tag3, tag4, tag5, result );
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

     string sfx = GetTokenSuffix( iword, last_word_index, lemma );

     int id_lemma = MatchSuffix( sfx, true );
    }
   }
  }


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

    string lemma_suffix = GetTokenSuffix( iword, last_word_index, lemma );
    sfx_lemma.Add( lemma_suffix );
    sfx_lemma_index.Add( MatchSuffix( lemma_suffix, true ) );
   }

   for( int iword = 1; iword < tokens.Count - 1; ++iword )
   {
    string tag1 = LemmaLabel( -1, sfx_lemma_index[iword - 1] ); // для Витерби

    // features как контекст +/-1 слово вокруг текущего
    string tag2 = TagLabel( -1, sfx_index[iword - 1] );
    string tag3 = TagLabel( 0, sfx_index[iword] );
    string tag4 = TagLabel( 1, sfx_index[iword + 1] );

    string res = ResultLabel( sfx_lemma_index[iword] );

    WriteTrain( tag1, tag2, tag3, tag4, res );
   }
  }

  return true;
 }


 int total_word_count = 0;
 int error_count_no_filter = 0;
 int error_count_with_ngram = 0;
 Dictionary<string, int> result_label2id;

 SharpEntropy.GisModel mModel;
 public void FinishLearning()
 {
  train_file.Close();
  train_file = null;

  System.Console.WriteLine( "Training..." );

  System.IO.StreamReader trainingStreamReader = new System.IO.StreamReader( train_file_path );
  SharpEntropy.ITrainingEventReader eventReader = new SharpEntropy.BasicEventReader( new SharpEntropy.PlainTextByLineDataReader( trainingStreamReader ) );
  SharpEntropy.GisTrainer trainer = new SharpEntropy.GisTrainer();
  trainer.TrainModel( eventReader );
  mModel = new SharpEntropy.GisModel( trainer );

  result_label2id = new Dictionary<string, int>();

  foreach( string label in result_labels )
  {
   int id = mModel.GetOutcomeIndex( label );
   result_label2id.Add( label, id );
  }

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
    List<List<int>> word2lemma_id = new List<List<int>>();

    List<string> lemmas = new List<string>();

    int last_word_index = projs.Count - 1;


    List<List<double>> viterbi_P = new List<List<double>>();
    List<List<int>> viterbi_backpointer = new List<List<int>>();

    for( int iword = 0; iword < projs.Count; ++iword )
    {
     if( iword == 0 || iword == last_word_index )
     {
      List<string> w2l = new List<string>();
      w2l.Add( string.Empty );
      word2lemmas.Add( w2l );

      List<int> w2li = new List<int>();
      w2li.Add( MatchSuffix( GetTokenSuffix( 0, last_word_index, projs[iword] ), false ) );
      word2lemma_id.Add( w2li );
     }
     else
     {
      List<string> word_lemmas = new List<string>();
      List<int> word_lemma_ids = new List<int>();
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
        int id_lemma = MatchSuffix( GetSuffix( lemma ), false );
        if( id_lemma == -1 )
         throw new System.ApplicationException();

        word_lemma_ids.Add( id_lemma );
       }
      }

      word2lemmas.Add( word_lemmas );
      word2lemma_id.Add( word_lemma_ids );
     }

     lemmas.Add( word2lemmas[iword][0] );

     List<double> px = new List<double>();
     List<int> bx = new List<int>();
     for( int i = 0; i < word2lemmas[iword].Count; ++i )
     {
      if( iword == 0 )
       px.Add( 1.0 ); // состояние START
      else
       px.Add( 0.0 ); // для остальных столбцов пока не знаем

      bx.Add( -1 );
     }

     viterbi_P.Add( px );
     viterbi_backpointer.Add( bx );
    }

    // Для каждого слова получим id_suffix
    List<int> word_suffices = new List<int>();

    for( int iword = 0; iword < projs.Count; ++iword )
    {
     string word = projs[iword].GetWord().ToLower();
     string suffix = GetTokenSuffix( iword, last_word_index, projs[iword] );
     int id_suffix = MatchSuffix( suffix, false );
     if( id_suffix == -1 )
      continue;

     word_suffices.Add( id_suffix );
    }

    // расчет по решетке
    for( int iword = 1; iword < projs.Count - 1; ++iword )
    {
     // в этом столбце столько разных состояний
     int n_states = word2lemmas[iword].Count;

     // сразу получим теги для контекста
     int id_suffix1 = word_suffices[iword - 1];
     int id_suffix2 = word_suffices[iword];
     int id_suffix3 = word_suffices[iword + 1];

     string label1 = TagLabel( -1, id_suffix1 );
     string label2 = TagLabel( 0, id_suffix2 );
     string label3 = TagLabel( 1, id_suffix3 );

     for( int istate = 0; istate < n_states; ++istate )
     {
      // для состояния istate получим целевую метку для леммы
      int id_result_lemma = word2lemma_id[iword][istate];
      string result_label = ResultLabel( id_result_lemma );

      if( !result_label2id.ContainsKey( result_label ) )
       // переходов в такое состояние не было вообще, будет нулевая верояность
       continue;

      int res_label_index = result_label2id[result_label];

      // просматриваем переходы из состояний предыдущего шага
      int n_prev_states = word2lemmas[iword - 1].Count;

      double best_p = -1.0;
      int best_prev_state_index = -1;

      for( int i_prev_state = 0; i_prev_state < n_prev_states; ++i_prev_state )
      {
       int id_prev_lemma = word2lemma_id[iword - 1][i_prev_state];
       string prev_lemma_label = LemmaLabel( -1, id_prev_lemma );
       double P_prev = viterbi_P[iword - 1][i_prev_state];

       // запускаем модель для получения достоверности нового состояния
       System.Collections.ArrayList context = new System.Collections.ArrayList();
       context.Add( prev_lemma_label );
       context.Add( label1 );
       context.Add( label2 );
       context.Add( label3 );

       try
       {
        double[] probabilities = mModel.Evaluate( (string[])context.ToArray( typeof( string ) ) );

        double p = probabilities[res_label_index];

        double P12 = p * P_prev; // вероятность данного перехода
        if( P12 > best_p )
        {
         best_p = P12;
         best_prev_state_index = i_prev_state;
        }
       }
       catch( System.Exception ex )
       {
        // ... обычно это означает, что встретился ключ, которые не был включен в обучающий набор.
        // будем считать, что у таких переходов нулевая вероятность.s
       }
      }

      if( n_states == 1 )
      {
       // если на данном шаге всего 1 состояние, то можем принудительно присвоить ему накопленную достоверность=1 и таким образом
       // улучшить поведение модели при появлении неизвестных слов, приводящих к обнулению вероятностей.
       viterbi_P[iword][istate] = 1.0;
      }
      else
      {
       viterbi_P[iword][istate] = best_p;
      }

      viterbi_backpointer[iword][istate] = best_prev_state_index;
     }
    }

    // Для последнего состояния END просто найдем самое достоверное на пред. шаге
    double best_P1 = 0;
    int best_state1 = 0;
    for( int i = 0; i < word2lemmas[last_word_index - 1].Count; ++i )
    {
     double p = viterbi_P[last_word_index - 1][i];
     if( p > best_P1 )
     {
      best_P1 = p;
      best_state1 = i;
     }
    }

    viterbi_P[last_word_index][0] = best_P1;
    viterbi_backpointer[last_word_index][0] = best_state1;

    // теперь обратный проход по решетке, через записи в backpointer'ах восстанавливаем самую достоверную цепочку лемм
    // для последнего шага - всего одно состояние END.
    int cur_backpointer = viterbi_backpointer[projs.Count - 1][0];
    int j = projs.Count - 2;

    List<string> best_lemmas = new List<string>();
    for( int k = 0; k < projs.Count; ++k )
     best_lemmas.Add( string.Empty );

    while( j > 0 )
    {
     // для этого шага - такая лучшая лемма
     string best_lemma = word2lemmas[j][cur_backpointer];
     best_lemmas[j] = best_lemma;

     // определяем лучшее состояние для предыдущего шага
     int prev_backpointer = viterbi_backpointer[j][cur_backpointer];
     cur_backpointer = prev_backpointer;

     j--;
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

     if( mustbe != best_lemmas[iword] )
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
