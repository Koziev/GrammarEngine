using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

class Builder_HMM_Suffix
{
 private TagBook tags;

 private int suffix_seq = 0;

 private Dictionary<string, int> suffices = new Dictionary<string, int>();
 private Dictionary<int, string> id2suffix = new Dictionary<int, string>();

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

 private HashSet<string> undividable_words = new HashSet<string>();


 private const int MAX_SUFFIX_LEN = 4;
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

 public Builder_HMM_Suffix()
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

 Dictionary<int, Dictionary<int, int>> B_counts;

 public void SetLanguage( int id ) { LanguageID = id; }

 public void Init()
 {
  foreach( string w in new[] { "надо", "подо", "между", "выше", "ниже" } )
  {
   undividable_words.Add( w );
  }

  tags = new TagBook( "POS_prediction" );

  string str_tags =
   /*
   @"
   ЧАСТИЦА:БЫ{},
   ЧАСТИЦА:ЛИ{},
   ЧАСТИЦА:КА{},

   ГЛАГОЛ:БЫТЬ{},
   ИНФИНИТИВ:БЫТЬ{},
   ГЛАГОЛ:ХОТЕТЬ{},
   ИНФИНИТИВ:ХОТЕТЬ{},
   ГЛАГОЛ:МОЧЬ{},
   ИНФИНИТИВ:МОЧЬ{},
   'ДОЛЖЕН'
   'ДОЛЖНА'
   'НЕ'
   'ДАВАЙ'
   'ДАВАЙТЕ'
   'ДАЙ'

   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:МУЖ
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:СР
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:МН

   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:ЖЕН
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:МУЖ
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:СР
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:МН

   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПАРТ ЧИСЛО:ЕД РОД:ЖЕН
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПАРТ ЧИСЛО:ЕД РОД:МУЖ
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПАРТ ЧИСЛО:ЕД РОД:СР

   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:МУЖ
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:СР
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:МН

   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:ЖЕН
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:СР
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:МН

   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:ЖЕН
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:МУЖ
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:СР
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:МН

   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:ЖЕН
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:МУЖ
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:СР
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН

   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:МЕСТ ЧИСЛО:ЕД РОД:ЖЕН
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:МЕСТ ЧИСЛО:ЕД РОД:МУЖ
   СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:МЕСТ ЧИСЛО:ЕД РОД:СР

   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:МУЖ
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:СР
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ИМ ЧИСЛО:МН

   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:ЖЕН
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:МУЖ
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:СР
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:РОД ЧИСЛО:МН

   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:МУЖ
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:СР
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ТВОР ЧИСЛО:МН

   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:ЖЕН
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:СР
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ВИН ЧИСЛО:МН

   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:ЖЕН
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:МУЖ
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:СР
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ДАТ ЧИСЛО:МН

   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:ЖЕН
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:МУЖ
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:СР
   ПРИЛАГАТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН

   ПРИЛАГАТЕЛЬНОЕ КРАТКИЙ РОД:ЖЕН ЧИСЛО:ЕД
   ПРИЛАГАТЕЛЬНОЕ КРАТКИЙ РОД:МУЖ ЧИСЛО:ЕД
   ПРИЛАГАТЕЛЬНОЕ КРАТКИЙ РОД:СР ЧИСЛО:ЕД
   ПРИЛАГАТЕЛЬНОЕ КРАТКИЙ ЧИСЛО:МН

   ПРИЛАГАТЕЛЬНОЕ СТЕПЕНЬ:СРАВН

   МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:1
   МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:МН ЛИЦО:1

   МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:2
   МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:МН ЛИЦО:2

   МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:3 РОД:МУЖ
   МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:3 РОД:ЖЕН
   МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:ЕД ЛИЦО:3 РОД:СР
   МЕСТОИМЕНИЕ ПАДЕЖ:ИМ ЧИСЛО:МН ЛИЦО:3

   МЕСТОИМЕНИЕ ПАДЕЖ:РОД ЧИСЛО:ЕД
   МЕСТОИМЕНИЕ ПАДЕЖ:РОД ЧИСЛО:МН

   МЕСТОИМЕНИЕ ПАДЕЖ:ТВОР ЧИСЛО:ЕД
   МЕСТОИМЕНИЕ ПАДЕЖ:ТВОР ЧИСЛО:МН

   МЕСТОИМЕНИЕ ПАДЕЖ:ВИН ЧИСЛО:ЕД
   МЕСТОИМЕНИЕ ПАДЕЖ:ВИН ЧИСЛО:МН

   МЕСТОИМЕНИЕ ПАДЕЖ:ДАТ ЧИСЛО:ЕД
   МЕСТОИМЕНИЕ ПАДЕЖ:ДАТ ЧИСЛО:МН

   МЕСТОИМЕНИЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД
   МЕСТОИМЕНИЕ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН

   МЕСТОИМ_СУЩ ПАДЕЖ:ИМ
   МЕСТОИМ_СУЩ ПАДЕЖ:РОД
   МЕСТОИМ_СУЩ ПАДЕЖ:ТВОР
   МЕСТОИМ_СУЩ ПАДЕЖ:ВИН
   МЕСТОИМ_СУЩ ПАДЕЖ:ДАТ
   МЕСТОИМ_СУЩ ПАДЕЖ:ПРЕДЛ

   ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ИМ
   ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:РОД
   ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ТВОР
   ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ВИН
   ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ДАТ
   ЧИСЛИТЕЛЬНОЕ ПАДЕЖ:ПРЕДЛ

   ГЛАГОЛ МОДАЛЬНЫЙ
   ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
   ГЛАГОЛ
   БЕЗЛИЧ_ГЛАГОЛ
   ИНФИНИТИВ МОДАЛЬНЫЙ
   ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
   ИНФИНИТИВ
   ДЕЕПРИЧАСТИЕ МОДАЛЬНЫЙ
   ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
   ДЕЕПРИЧАСТИЕ
   ПРЕДЛОГ
   ПОСЛЕЛОГ
   СОЮЗ
   ЧАСТИЦА
   ПУНКТУАТОР
   НАРЕЧИЕ
   ВВОДНОЕ
   NUM_WORD
   UNKNOWNENTRIES
   BETH:BEGIN{}
   BETH:END{}
   ";
   */
@"ГЛАГОЛ
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
BETH";

  tags.Load( str_tags, gren );

  A_counts = new int[tags.Count(), tags.Count()];
  for( int i = 0; i < tags.Count(); ++i )
   for( int j = 0; j < tags.Count(); ++j )
    A_counts[i, j] = 0;

  T_counts = new int[tags.Count()];
  for( int i = 0; i < tags.Count(); ++i )
   T_counts[i] = 0;

  B_counts = new Dictionary<int, Dictionary<int, int>>();

  return;
 }


 public bool ProcessSample( string line )
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

     //SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
     //string word = token.GetWord().ToLower();

     int suffix_id = suffices[i];

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
    SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY /*| SolarixGrammarEngineNET.GrammarEngine.SOL_GREN_DISABLE_FILTERS*/ ) )
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

     int suffix_id = GetTokenSuffix( i, last_word_index, token );
     suffices.Add( suffix_id );


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
       error_count_with_model++;
     }
    }
   }
  }

  return;
 }
}
