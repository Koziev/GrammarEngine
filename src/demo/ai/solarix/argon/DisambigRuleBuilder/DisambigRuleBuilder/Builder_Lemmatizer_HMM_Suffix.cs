using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

class Builder_Lemmatizer_HMM_Suffix
{
 private int suffix_seq = 0;
 bool allow_new_suffix = true;

 private Dictionary<string, int> suffices = new Dictionary<string, int>();
 private Dictionary<int, string> id2suffix = new Dictionary<int, string>();
 private Dictionary<int, int> id2index = new Dictionary<int, int>();
 private Dictionary<int, int> index2id = new Dictionary<int, int>();

 bool IsUnknownLexem( string s )
 {
  return s.Equals( "UNKNOWNENTRY", System.StringComparison.InvariantCultureIgnoreCase ) ||
         s == "???" ||
         s.Equals( "number_", System.StringComparison.InvariantCultureIgnoreCase );
 }

 string GetSuffixById( int id )
 {
  return id2suffix[id];
 }

 int MatchSuffix( string suffix )
 {
  int id = -1;

  if( suffices.TryGetValue( suffix, out id ) )
   return id;

  if( !allow_new_suffix )
   throw new ApplicationException();

  id = suffix_seq++;

  int index = suffices.Count;
  id2index.Add( id, index );
  index2id.Add( index, id );

  suffices.Add( suffix, id );
  id2suffix.Add( id, suffix );

  return id;
 }

 private HashSet<string> undividable_words = new HashSet<string>();


 private const int MAX_SUFFIX_LEN = 3;
 private string GetSuffix( string word )
 {
  if( undividable_words.Contains( word ) )
   return word;

  if( word.Length > MAX_SUFFIX_LEN )
   return "~" + word.Substring( word.Length - MAX_SUFFIX_LEN );
  else
   return word;
 }

 private int GetTokenSuffix( int pos, int last_word_index, SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  if( pos == 0 )
  {
   int tt = MatchSuffix( "~~BEGIN~~" );
   return tt;
  }
  else if( pos == last_word_index )
  {
   int tt = MatchSuffix( "~~END~~" );
   return tt;
  }
  else
  {
   string word = token.GetWord().ToLower();
   string suffix = GetSuffix( word );
   int tt = MatchSuffix( suffix );
   return tt;
  }
 }


 private int GetLemmaSuffix( int pos, int last_word_index, SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  if( pos == 0 )
  {
   int tt = MatchSuffix( "~~BEGIN~~" );
   return tt;
  }
  else if( pos == last_word_index )
  {
   int tt = MatchSuffix( "~~END~~" );
   return tt;
  }
  else
  {
   int id_entry = token.GetEntryID();
   string entry_name = gren.GetEntryName( id_entry );
   string suffix = GetSuffix( entry_name );
   int tt = MatchSuffix( suffix );
   return tt;
  }
 }

 private int GetFormSuffix( int pos, int last_word_index, string word )
 {
  if( pos == 0 )
  {
   int tt = MatchSuffix( "~~BEGIN~~" );
   return tt;
  }
  else if( pos == last_word_index )
  {
   int tt = MatchSuffix( "~~END~~" );
   return tt;
  }
  else
  {
   string suffix = GetSuffix( word );
   int tt = MatchSuffix( suffix );
   return tt;
  }
 }

 public Builder_Lemmatizer_HMM_Suffix()
 {
 }


 private SolarixGrammarEngineNET.GrammarEngine2 gren;
 public void LoadDictionary( string filepath )
 {
  gren = new SolarixGrammarEngineNET.GrammarEngine2();
  gren.Load( filepath, false );
  Init();
  return;
 }

 int LanguageID = -1;

 public void SetLanguage( int id ) { LanguageID = id; }

 public void Init()
 {
  foreach( string w in new[] { "надо", "подо", "между", "выше", "ниже" } )
  {
   undividable_words.Add( w );
  }

  return;
 }


 public bool ProcessSample( string line )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   int last_word_index = tokens.Count - 1;
   for( int i = 0; i < tokens.Count; ++i )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
    int suffix_id1 = GetTokenSuffix( i, last_word_index, token );

    int nver = token.VersionCount();
    for( int j = 0; j < nver; ++j )
    {
     int ver_ekey = token.GetVersionEntryID( j );
     string ename = gren.GetEntryName( ver_ekey );
     int suffix_id2 = GetFormSuffix( i, last_word_index, ename );
    }
   }
  }

  using( SolarixGrammarEngineNET.AnalysisResults projs = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY ) )
  {
   int last_word_index = projs.Count - 1;
   for( int i = 0; i < projs.Count; ++i )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode token = projs[i];
    int suffix_id1 = GetTokenSuffix( i, last_word_index, token );

    int nver = token.VersionCount();
    for( int j = 0; j < nver; ++j )
    {
     int ver_ekey = token.GetVersionEntryID( j );
     string ename = gren.GetEntryName( ver_ekey );
     int suffix_id2 = GetFormSuffix( i, last_word_index, ename );
    }
   }

  }


  return true;
 }

 int[,] A_counts;
 int[] T_counts;
 Dictionary<int, Dictionary<int, int>> B_counts;

 private int N_STATE = 0; // TODO

 public void FinishSuffixCollection()
 {
  allow_new_suffix = false;

  N_STATE = suffix_seq + 1;

  A_counts = new int[N_STATE, N_STATE];
  for( int i = 0; i < N_STATE; ++i )
   for( int j = 0; j < N_STATE; ++j )
    A_counts[i, j] = 0;

  T_counts = new int[N_STATE];
  for( int i = 0; i < N_STATE; ++i )
   T_counts[i] = 0;

  B_counts = new Dictionary<int, Dictionary<int, int>>();
  return;
 }


 public bool ProcessSample2( string line )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {

   List<int> token2tags = new List<int>();
   List<int> suffices = new List<int>();

   int last_word_index = tokens.Count - 1;

   bool all_hit = true;
   for( int i = 0; i < tokens.Count; ++i )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
    string word = token.GetWord().ToLower();

    int suffix_id = GetTokenSuffix( i, last_word_index, token );
    suffices.Add( suffix_id );

    int lemma_suffix_id = GetLemmaSuffix( i, last_word_index, token );
    token2tags.Add( lemma_suffix_id );
   }

   if( all_hit )
   {
    for( int i = 0; i < tokens.Count; ++i )
    {
     int tt1 = token2tags[i];
     T_counts[tt1]++;

     //SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
     //string word = token.GetWord().ToLower();

     int suffix_id = suffices[i];

     // обновляем матрицу со счетчиками эмиссии.
     Dictionary<int, int> word_freq;
     if( B_counts.TryGetValue( tt1, out word_freq ) )
     {
      int freq0;
      if( word_freq.TryGetValue( suffix_id, out freq0 ) )
      {
       word_freq[suffix_id] = freq0 + 1;
      }
      else
      {
       word_freq.Add( suffix_id, 1 );
      }
     }
     else
     {
      word_freq = new Dictionary<int, int>();
      word_freq.Add( suffix_id, 1 );
      B_counts.Add( tt1, word_freq );
     }

     if( i > 0 )
     {
      // обновляем счетчики переходов между суффиксами лемм.
      int tt0 = token2tags[i - 1];
      A_counts[tt0, tt1]++;
     }
    }
   }
  }

  return true;
 }


 double[,] PA;
 Dictionary<int, Dictionary<int, double>> PB;
 public void FinishLearning()
 {
  PA = new double[N_STATE, N_STATE];
  for( int i = 0; i < N_STATE; ++i )
   for( int j = 0; j < N_STATE; ++j )
   {
    if( T_counts[i] > 0 )
    {
     double p = (double)A_counts[i, j] / (double)T_counts[i];
     PA[i, j] = p;
    }
    else
    {
     PA[i, j] = 0.0;
    }
   }

  PB = new Dictionary<int, Dictionary<int, double>>();
  foreach( var k1 in B_counts )
  {
   Dictionary<int, double> b = new Dictionary<int, double>();
   foreach( var k2 in k1.Value )
   {
    double pb = (double)k2.Value / (double)T_counts[k1.Key];
    b.Add( k2.Key, pb );
   }

   PB.Add( k1.Key, b );
  }

  return;
 }


 public void Check(
                   string line,
                   ref int total_word_count,
                   ref int error_count_no_filter,
                   ref int error_count_with_model
                  )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   List<List<int>> word2tags = new List<List<int>>();
   List<int> selected_tags = new List<int>();

   // Токенизация без использования синтаксических правил
   using( SolarixGrammarEngineNET.AnalysisResults projs = gren.AnalyzeMorphology( line, LanguageID,
    SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY ) )
   {
    if( tokens.Count != projs.Count )
    {
     return;
    }

    // Преобразуем все проекции каждого слова в варианты распознавания тегов

    List<int> tag_set = new List<int>();

    int start_tag = -1, end_tag = -1;

    //List<string> words = new List<string>();
    bool unmatched_tag = false;

    List<int> suffices = new List<int>();
    int last_word_index = tokens.Count - 1;

    for( int i = 0; i < tokens.Count; ++i )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
     string word = token.GetWord().ToLower();
     //   words.Add(word);

     // наблюдаемый параметр - окончание грамматической формы.
     int suffix_id = GetTokenSuffix( i, last_word_index, token );
     suffices.Add( suffix_id );

     SolarixGrammarEngineNET.SyntaxTreeNode proj = projs[i];
     List<int> wt = new List<int>();

     for( int k = 0; k < proj.VersionCount(); ++k )
     {
      int ever = proj.GetVersionEntryID( k );
      string ver_entry = gren.GetEntryName( ever );

      int id_tag = GetFormSuffix( i, last_word_index, ver_entry );

      if( !wt.Contains( id_tag ) )
       wt.Add( id_tag );

      if( !tag_set.Contains( id_tag ) )
       tag_set.Add( id_tag );

      if( i == 0 )
       start_tag = id_tag;
      else if( i == tokens.Count - 1 )
       end_tag = id_tag;

      if( wt.Count == 0 )
      {
       // ни один тег не подошел, это ошибка кодовой книги.
       unmatched_tag = true;
      }
     }

     word2tags.Add( wt );
     selected_tags.Add( wt[0] );
    }


    if( unmatched_tag )
     return;

    // -----------------------------------------
    // Посчитаем ошибки до применения модели
    // -----------------------------------------
    int n_err = 0;

    for( int iword = 1; iword < tokens.Count - 1; ++iword )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[iword];
     int required_suffix_id = GetLemmaSuffix( iword, last_word_index, token );

     int got_suffix_id = selected_tags[iword];
     if( required_suffix_id != got_suffix_id )
      n_err++;
    }

    error_count_no_filter += n_err;
    total_word_count += ( tokens.Count - 2 );

    int Nword = tokens.Count; // кол-во последовательных шагов - число слов, включая левую и правую границы
    int Nstate = tag_set.Count;

    // Viterbi trellis

    // вероятности для состояний
    double[,] V = new double[Nword, Nstate];
    for( int t = 0; t < Nword; ++t )
     for( int s = 0; s < Nstate; ++s )
      V[t, s] = 0.0;

    // backpointers для отслеживания лучшего пути
    int[,] BACKPOINTER = new int[Nword, Nstate];
    for( int t = 0; t < Nword; ++t )
     for( int s = 0; s < Nstate; ++s )
      BACKPOINTER[t, s] = -1; // возможно, надо как-то инициализировать дефолтный путь на случай, если найти лучший не получится - то есть надо проставить от начального до конечного.

    V[0, tag_set.IndexOf( start_tag )] = 1.0; // начальное состояние - стартуем из этого состояния.

    for( int t = 1; t < Nword; ++t )
    {
     // проставляем вероятность получения состояний на шаге t, исходя из значений на предыдущем шаге.

     for( int s2 = 0; s2 < Nstate; ++s2 ) // состояния на шаге t
     {
      double max_v = 0.0;
      int best_prev_state = 0;

      int id_tag2 = tag_set[s2];

      double b = 0.0;

      Dictionary<int, double> bx;
      if( PB.TryGetValue( id_tag2, out bx ) )
      {
       bx.TryGetValue( suffices[t], out b );
      }

      for( int s1 = 0; s1 < Nstate; ++s1 ) // состояния на шаге t-1
      {
       int id_tag1 = tag_set[s1];

       double vt = V[t - 1, s1] * PA[id_tag1, id_tag2] * b;

       if( vt > max_v )
       {
        max_v = vt;
        best_prev_state = s1;
       }
      }

      V[t, s2] = max_v;
      BACKPOINTER[t, s2] = best_prev_state;
     }
    }

    // обратный ход по состояниям, указанным в BACKPOINTER.

    int best_state = tag_set.IndexOf( end_tag );

    for( int t = Nword - 1; t > 0; --t )
    {
     int best_prev_state = BACKPOINTER[t, best_state];

     int selected_tag = tag_set[best_prev_state];

     // Делаем вариант распознавания, давший этот токен, первым в списке.
     // ATT: грубые ошибки выбора тега не допускаем, то есть разрешаем только те теги, которые были
     // получены при распознавании слова.
     if( word2tags[t - 1].Contains( selected_tag ) )
     {
      selected_tags[t - 1] = selected_tag;
     }
     else
     {
      // ... грубая ошибка выбора тега.
      //    SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[t];
      //    string word = token.GetWord().ToLower();
      //    Console.WriteLine( "Грубая ошибка выбора тега - слово {0}", word );
     }

     best_state = best_prev_state;
    }

    // Теперь проверяем количество ошибок в выборе леммы
    for( int iword = 1; iword < tokens.Count - 1; ++iword )
    {
     // это то, что должно получиться
     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[iword];

     int ekey1 = token.GetEntryID();
     string ename = gren.GetEntryName( ekey1 );
     string lemma_suffix = GetSuffix( ename );

     // а это то, что получилось у модели
     int tag = selected_tags[iword];
     if( tag != -1 )
     {
      string model_suffix = GetSuffixById( tag );
      if( model_suffix != lemma_suffix )
       error_count_with_model++;
     }
    }
   }
  }

  return;
 }
}
