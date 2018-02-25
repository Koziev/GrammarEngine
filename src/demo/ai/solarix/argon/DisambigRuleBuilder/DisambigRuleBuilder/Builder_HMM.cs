using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

class Builder_HMM
{
 private TagBook tags;


 public Builder_HMM()
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

 int[,] A_counts;
 int[] T_counts;

 Dictionary<int, Dictionary<string, int>> B_counts;

 public void SetLanguage( int id ) { LanguageID = id; }

 public void Init()
 {
  tags = new TagBook( "POS_prediction" );

  string str_tags =

/*
@"
ГЛАГОЛ
ИНФИНИТИВ
ПРИЛАГАТЕЛЬНОЕ
ДЕЕПРИЧАСТИЕ
ПРЕДЛОГ
СУЩЕСТВИТЕЛЬНОЕ
МЕСТОИМЕНИЕ
ЧИСЛИТЕЛЬНОЕ
МЕСТОИМ_СУЩ
СОЮЗ
ЧАСТИЦА
НАРЕЧИЕ
ПОСЛЕЛОГ
БЕЗЛИЧ_ГЛАГОЛ
ПУНКТУАТОР
UNKNOWNENTRIES
ВВОДНОЕ
NUM_WORD
BETH
";*/

@"
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ

СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ЗВАТ
СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ
СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:РОД
СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПАРТ
СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ТВОР
СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН
СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ДАТ
СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ
СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:МЕСТ

ПРИЛАГАТЕЛЬНОЕ КРАТКИЙ
ПРИЛАГАТЕЛЬНОЕ СТЕПЕНЬ:СРАВН

ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ИМ
ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:РОД
ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ТВОР
ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН
ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ

МЕСТОИМЕНИЕ ПАДЕЖ:ИМ
МЕСТОИМЕНИЕ ПАДЕЖ:РОД
МЕСТОИМЕНИЕ ПАДЕЖ:ТВОР
МЕСТОИМЕНИЕ ПАДЕЖ:ВИН
МЕСТОИМЕНИЕ ПАДЕЖ:ДАТ
МЕСТОИМЕНИЕ ПАДЕЖ:ПРЕДЛ

МЕСТОИМ_СУЩ ПАДЕЖ:ИМ
МЕСТОИМ_СУЩ ПАДЕЖ:РОД
МЕСТОИМ_СУЩ ПАДЕЖ:ТВОР
МЕСТОИМ_СУЩ ПАДЕЖ:ВИН
МЕСТОИМ_СУЩ ПАДЕЖ:ДАТ
МЕСТОИМ_СУЩ ПАДЕЖ:ПРЕДЛ

ГЛАГОЛ
ИНФИНИТИВ
ДЕЕПРИЧАСТИЕ
ПРЕДЛОГ
ЧИСЛИТЕЛЬНОЕ
СОЮЗ
ЧАСТИЦА
НАРЕЧИЕ
ПОСЛЕЛОГ
БЕЗЛИЧ_ГЛАГОЛ
ПУНКТУАТОР
UNKNOWNENTRIES
ВВОДНОЕ
NUM_WORD
BETH
";



  tags.Load( str_tags, gren );

  A_counts = new int[tags.Count(), tags.Count()];
  for( int i = 0; i < tags.Count(); ++i )
   for( int j = 0; j < tags.Count(); ++j )
    A_counts[i, j] = 0;

  T_counts = new int[tags.Count()];
  for( int i = 0; i < tags.Count(); ++i )
   T_counts[i] = 0;

  B_counts = new Dictionary<int, Dictionary<string, int>>();

  return;
 }


 public bool ProcessSample( string line )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   List<int> token2tags = new List<int>();

   bool all_hit = true;
   for( int i = 0; i < tokens.Count; ++i )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
    string word = token.GetWord().ToLower();

    int tt = tags.MatchTags( token, gren );
    if( tt == -1 )
    {
     all_hit = false;
     break;
    }

    token2tags.Add( tags.GetIndexById( tt ) );
   }

   if( all_hit )
   {
    for( int i = 0; i < tokens.Count; ++i )
    {
     int tt1 = token2tags[i];
     T_counts[tt1]++;

     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
     string word = token.GetWord().ToLower();

     Dictionary<string, int> word_freq;
     if( B_counts.TryGetValue( tt1, out word_freq ) )
     {
      int freq0;
      if( word_freq.TryGetValue( word, out freq0 ) )
      {
       word_freq[word] = freq0 + 1;
      }
      else
      {
       word_freq.Add( word, 1 );
      }
     }
     else
     {
      word_freq = new Dictionary<string, int>();
      word_freq.Add( word, 1 );
      B_counts.Add( tt1, word_freq );
     }

     if( i > 0 )
     {
      int tt0 = token2tags[i - 1];
      A_counts[tt0, tt1]++;
     }
    }
   }
  }

  return true;
 }

 double[,] PA;
 Dictionary<int, Dictionary<string, double>> PB;
 public void FinishLearning()
 {
  PA = new double[tags.Count(), tags.Count()];
  for( int i = 0; i < tags.Count(); ++i )
   for( int j = 0; j < tags.Count(); ++j )
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

  PB = new Dictionary<int, Dictionary<string, double>>();
  foreach( var k1 in B_counts )
  {
   Dictionary<string, double> b = new Dictionary<string, double>();
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
                   ref int POS_error_count,
                   ref int FEATURESET_error_count
                  )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   List<List<int>> word2tags = new List<List<int>>();
   List<int> selected_tags = new List<int>();

   // Токенизация без использования синтаксических правил
   using( SolarixGrammarEngineNET.AnalysisResults projs = gren.AnalyzeMorphology( line, LanguageID,
    SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY /*| SolarixGrammarEngineNET.GrammarEngine.SOL_GREN_DISABLE_FILTERS*/ ) )
   {

    if( tokens.Count != projs.Count )
    {
     return;
    }

    // Преобразуем все проекции каждого слова в варианты распознавания тегов

    List<int> tag_set = new List<int>();

    int start_tag = -1, end_tag = -1;

    List<string> words = new List<string>();
    bool unmatched_tag = false;

    for( int i = 0; i < tokens.Count; ++i )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
     string word = token.GetWord().ToLower();
     words.Add( word );

     SolarixGrammarEngineNET.SyntaxTreeNode proj = projs[i];
     List<int> wt = new List<int>();
     for( int j = 0; j < proj.VersionCount(); ++j )
     {
      int id_tag = tags.GetIndexById( tags.MatchTags( proj, j, gren ) );
      if( id_tag != -1 )
      {
       if( !wt.Contains( id_tag ) )
        wt.Add( id_tag );

       if( !tag_set.Contains( id_tag ) )
        tag_set.Add( id_tag );
      }

      if( i == 0 )
       start_tag = id_tag;
      else if( i == tokens.Count - 1 )
       end_tag = id_tag;
     }

     if( wt.Count == 0 )
     {
      // ни один тег не подошел, это ошибка кодовой книги.
      unmatched_tag = true;
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
     int ekey1 = token.GetEntryID();
     int id_class1 = gren.GetEntryClass( ekey1 );

     int tag = selected_tags[iword];
     if( tag != -1 )
     {
      TagMatcher m = tags[tags.GetIdByIndex( tag )];
      if( !m.MatchPartOfSpeech( id_class1 ) )
       n_err++;
     }
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

      Dictionary<string, double> bx;
      if( PB.TryGetValue( id_tag2, out bx ) )
      {
       bx.TryGetValue( words[t], out b );
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
      selected_tags[t - 1] = selected_tag;
     else
     {
      // ... грубая ошибка выбора тега.
     }

     best_state = best_prev_state;
    }


    // Теперь проверяем количество ошибок в выборе частей речи.
    for( int iword = 1; iword < tokens.Count - 1; ++iword )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[iword];
     int ekey1 = token.GetEntryID();
     int id_class1 = gren.GetEntryClass( ekey1 );

     int tag = selected_tags[iword];
     if( tag != -1 )
     {
      TagMatcher m = tags[tags.GetIdByIndex( tag )];

      if( !m.MatchPartOfSpeech( id_class1 ) )
       POS_error_count++;

      if( !m.Match( token, gren ) )
       FEATURESET_error_count++;
     }
    }
   }
  }

  return;
 }
}
