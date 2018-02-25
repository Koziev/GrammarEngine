using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

#region Морфологическая_Модель
class BayesStat_Morph
{
 private SolarixGrammarEngineNET.GrammarEngine2 gren;

 public TagBook tags, selectors;

 public Dictionary<NGram2, int> ngrams2;
 public Dictionary<int, List<NGram2>> tag0_2_ngram2;

 public Dictionary<NGram2, int> ngrams2_1;
 public Dictionary<int, List<NGram2>> tag1_2_ngram2;

 // ---------

 public Dictionary<NGram3, int> ngrams3; // 0,1 --> 2
 public Dictionary<Int2, List<NGram3>> tag0_2_ngram3;

 public Dictionary<NGram3, int> ngrams3_1; // 0 --> 1 <-- 2
 public Dictionary<Int2, List<NGram3>> tag1_2_ngram3;

 // --------

 public Dictionary<NGram4, int> ngrams4; // 0,1,2 --> 3
 public Dictionary<Int3, List<NGram4>> tag0_2_ngram4;

 public Dictionary<NGram4, int> ngrams4_1; // 0,1 --> 2 <-- 3
 public Dictionary<Int3, List<NGram4>> tag1_2_ngram4;

 public BayesStat_Morph()
 {
  ngrams2 = new Dictionary<NGram2, int>();
  tag0_2_ngram2 = new Dictionary<int, List<NGram2>>();

  ngrams2_1 = new Dictionary<NGram2, int>();
  tag1_2_ngram2 = new Dictionary<int, List<NGram2>>();

  // --------

  ngrams3 = new Dictionary<NGram3, int>();
  tag0_2_ngram3 = new Dictionary<Int2, List<NGram3>>();

  ngrams3_1 = new Dictionary<NGram3, int>();
  tag1_2_ngram3 = new Dictionary<Int2, List<NGram3>>();

  ngrams4 = new Dictionary<NGram4, int>();
  tag0_2_ngram4 = new Dictionary<Int3, List<NGram4>>();

  ngrams4_1 = new Dictionary<NGram4, int>();
  tag1_2_ngram4 = new Dictionary<Int3, List<NGram4>>();
 }


 public void Init( SolarixGrammarEngineNET.GrammarEngine2 _gren )
 {
  gren = _gren;
  tags = new TagBook( "case_prediction" );

  string str_tags =
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
ИНФИНИТИВ МОДАЛЬНЫЙ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
ИНФИНИТИВ
ДЕЕПРИЧАСТИЕ МОДАЛЬНЫЙ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
ДЕЕПРИЧАСТИЕ
ПРЕДЛОГ
СОЮЗ
ЧАСТИЦА
ПУНКТУАТОР
НАРЕЧИЕ
BETH:BEGIN{}
BETH:END{}
";


  tags.Load( str_tags, gren );

  selectors = new TagBook( "pos_prediction" );

  string str_selectors =
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
";

  selectors.Load( str_selectors, gren );
 }


 public void AddNGram( int tags0, int tags1 )
 {
  NGram2 n2;
  n2.tags0 = tags0;
  n2.tags1 = tags1;

  int freq = 0;
  if( ngrams2.TryGetValue( n2, out freq ) )
  {
   ngrams2[n2] = freq + 1;
  }
  else
  {
   ngrams2.Add( n2, 1 );
  }

  return;
 }


 public void AddNGram_1( int tags0, int tags1 )
 {
  NGram2 n2;
  n2.tags0 = tags0;
  n2.tags1 = tags1;

  int freq = 0;
  if( ngrams2_1.TryGetValue( n2, out freq ) )
  {
   ngrams2_1[n2] = freq + 1;
  }
  else
  {
   ngrams2_1.Add( n2, 1 );
  }

  return;
 }



 public void AddNGram( int tags0, int tags1, int tags2 )
 {
  NGram3 n3;
  n3.tags0 = tags0;
  n3.tags1 = tags1;
  n3.tags2 = tags2;

  int freq = 0;
  if( ngrams3.TryGetValue( n3, out freq ) )
  {
   ngrams3[n3] = freq + 1;
  }
  else
  {
   ngrams3.Add( n3, 1 );
  }

  return;
 }


 public void AddNGram_1( int tags0, int tags1, int tags2 )
 {
  NGram3 n3;
  n3.tags0 = tags0;
  n3.tags1 = tags1;
  n3.tags2 = tags2;

  int freq = 0;
  if( ngrams3_1.TryGetValue( n3, out freq ) )
  {
   ngrams3_1[n3] = freq + 1;
  }
  else
  {
   ngrams3_1.Add( n3, 1 );
  }

  return;
 }


 public void AddNGram( int tags0, int tags1, int tags2, int tags3 )
 {
  NGram4 n4;
  n4.tags0 = tags0;
  n4.tags1 = tags1;
  n4.tags2 = tags2;
  n4.tags3 = tags3;

  int freq = 0;
  if( ngrams4.TryGetValue( n4, out freq ) )
  {
   ngrams4[n4] = freq + 1;
  }
  else
  {
   ngrams4.Add( n4, 1 );
  }

  return;
 }

 public void AddNGram_1( int tags0, int tags1, int tags2, int tags3 )
 {
  NGram4 n4;
  n4.tags0 = tags0;
  n4.tags1 = tags1;
  n4.tags2 = tags2;
  n4.tags3 = tags3;

  int freq = 0;
  if( ngrams4_1.TryGetValue( n4, out freq ) )
  {
   ngrams4_1[n4] = freq + 1;
  }
  else
  {
   ngrams4_1.Add( n4, 1 );
  }

  return;
 }



 public bool ProcessSample( string line, SolarixGrammarEngineNET.AnalysisResults tokens )
 {
  List<int> token2tags = new List<int>();
  List<int> token2selectors = new List<int>();

  for( int i = 0; i < tokens.Count; ++i )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
   string word = token.GetWord().ToLower();

   int tt = tags.MatchTags( token, gren );
   token2tags.Add( tt );

   int st = selectors.MatchTags( token, gren );
   token2selectors.Add( st );
  }


  // --------------------
  // ДИГРАММЫ
  // --------------------

  // 1 --> 2
  for( int iword = 1; iword < tokens.Count; ++iword )
  {
   // ДИГРАММЫ
   int tags1 = token2tags[iword - 1];
   if( tags1 != -1 )
   {
    int tags2 = token2selectors[iword];
    if( tags2 != -1 )
     AddNGram( tags1, tags2 );
   }
  }

  // 1 <-- 2
  for( int iword = 1; iword < tokens.Count; ++iword )
  {
   int tags2 = token2tags[iword];
   if( tags2 != -1 )
   {
    int tags1 = token2selectors[iword - 1];

    if( tags1 != -1 )
     AddNGram_1( tags1, tags2 );
   }
  }


  // ---------------------------------------------
  // ТРИГРАММЫ
  // ---------------------------------------------

  // 1,2 --> 3
  for( int iword = 2; iword < tokens.Count; ++iword )
  {
   int tags0 = token2tags[iword - 2];
   if( tags0 != -1 )
   {
    int tags1 = token2tags[iword - 1];
    if( tags1 != -1 )
    {
     int tags2 = token2selectors[iword];
     if( tags2 != -1 )
      AddNGram( tags0, tags1, tags2 );
    }
   }
  }

  // 1 --> 2 <-- 3
  for( int iword = 2; iword < tokens.Count; ++iword )
  {
   int tags0 = token2tags[iword - 2];
   if( tags0 != -1 )
   {
    int tags1 = token2selectors[iword - 1];
    if( tags1 != -1 )
    {
     int tags2 = token2tags[iword];
     if( tags2 != -1 )
      AddNGram_1( tags0, tags1, tags2 );
    }
   }
  }

  // ---------------------------------------------
  // ТЕТРАГРАММЫ
  // ---------------------------------------------

  // 1,2,3 --> 4
  for( int iword = 3; iword < tokens.Count; ++iword )
  {
   int tags0 = token2tags[iword - 3];
   if( tags0 != -1 )
   {
    int tags1 = token2tags[iword - 2];
    if( tags1 != -1 )
    {
     int tags2 = token2tags[iword - 1];
     if( tags2 != -1 )
     {
      int tags3 = token2selectors[iword];
      if( tags3 != -1 )
      {
       AddNGram( tags0, tags1, tags2, tags3 );
      }
     }
    }
   }
  }


  // 1,2 --> 3 <-- 4

  for( int iword = 3; iword < tokens.Count; ++iword )
  {
   int tags0 = token2tags[iword - 3];
   if( tags0 != -1 )
   {
    int tags1 = token2tags[iword - 2];
    if( tags1 != -1 )
    {
     int tags2 = token2selectors[iword - 1];
     if( tags2 != -1 )
     {
      int tags3 = token2tags[iword];
      if( tags3 != -1 )
      {
       AddNGram_1( tags0, tags1, tags2, tags3 );
      }
     }
    }
   }
  }

  return true;
 }



 public void FinishLearning()
 {
  // -----------------
  // ДИГРАММЫ
  // -----------------

  foreach( KeyValuePair<NGram2, int> x in ngrams2 )
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


  foreach( KeyValuePair<NGram2, int> x in ngrams2_1 )
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

  // -------------
  // ТРИГРАММЫ
  // -------------

  foreach( KeyValuePair<NGram3, int> x in ngrams3 )
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


  foreach( KeyValuePair<NGram3, int> x in ngrams3_1 )
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



  // ------------------
  // ТЕТРАГРАММЫ
  // ------------------

  foreach( KeyValuePair<NGram4, int> x in ngrams4 )
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

  foreach( KeyValuePair<NGram4, int> x in ngrams4_1 )
  {
   int tags0 = x.Key.tags0;
   int tags1 = x.Key.tags1;
   int tags3 = x.Key.tags3;
   Int3 k = new Int3( tags0, tags1, tags3 );

   List<NGram4> n;
   if( tag1_2_ngram4.TryGetValue( k, out n ) )
   {
    n.Add( x.Key );
   }
   else
   {
    n = new List<NGram4>();
    n.Add( x.Key );
    tag1_2_ngram4.Add( k, n );
   }
  }

  return;
 }



 public void DumpRules( System.IO.StreamWriter dest )
 {
  // --------------
  // 2-ГРАММЫ
  // --------------

  dest.WriteLine( "// {0} 2-grams:", ngrams2.Count );

  List<KeyValuePair<NGram2, int>> n2f = new List<KeyValuePair<NGram2, int>>( ngrams2.Select( z => z ) );
  n2f.Sort( new NGram2Freq() );

  Dictionary<int, int> n2_tag0_sum = new Dictionary<int, int>();
  foreach( var x in n2f )
  {
   int freq;
   if( n2_tag0_sum.TryGetValue( x.Key.tags0, out freq ) )
   {
    n2_tag0_sum[x.Key.tags0] = freq + x.Value;
   }
   else
   {
    n2_tag0_sum.Add( x.Key.tags0, x.Value );
   }
  }


  int tag0_cur = -1;
  foreach( var x in n2f )
  {
   if( tag0_cur != x.Key.tags0 )
   {
    tag0_cur = x.Key.tags0;
    dest.WriteLine( "{0}", new string( '-', 40 ) );
   }

   int freq_sum = n2_tag0_sum[tag0_cur];
   dest.WriteLine( "digram {0} -> {1} : {2} // {3} | {4} -> {5}%", x.Key.tags0, x.Key.tags1, x.Value, tags[x.Key.tags0].ToString(), selectors[x.Key.tags1].ToString(), PercentFormatter.Percent( x.Value, freq_sum ) );
  }

  // --------------
  // 3-ГРАММЫ
  // --------------

  dest.WriteLine( "\n\n// {0} 3-grams:", ngrams3.Count );

  List<KeyValuePair<NGram3, int>> n3f = new List<KeyValuePair<NGram3, int>>( ngrams3.Select( z => z ) );
  n3f.Sort( new NGram3Freq() );

  Dictionary<NGram2, int> n3_tag_sum = new Dictionary<NGram2, int>();
  foreach( var x in n3f )
  {
   NGram2 key;
   key.tags0 = x.Key.tags0;
   key.tags1 = x.Key.tags1;
   int freq;
   if( n3_tag_sum.TryGetValue( key, out freq ) )
    n3_tag_sum[key] = freq + x.Value;
   else
    n3_tag_sum.Add( key, x.Value );
  }

  tag0_cur = -1;
  int tag1_cur = -1;
  foreach( var x in n3f )
  {
   if( tag0_cur != x.Key.tags0 || tag1_cur != x.Key.tags1 )
   {
    tag0_cur = x.Key.tags0;
    tag1_cur = x.Key.tags1;

    dest.WriteLine( "{0}", new string( '-', 40 ) );
   }

   NGram2 key;
   key.tags0 = x.Key.tags0;
   key.tags1 = x.Key.tags1;
   int freq_sum = n3_tag_sum[key];

   dest.WriteLine( "trigram {0} {1} -> {2} : {3} // {4} | {5} | {6} -> {7}", x.Key.tags0, x.Key.tags1, x.Key.tags2, x.Value, tags[x.Key.tags0].ToString(), tags[x.Key.tags1].ToString(), selectors[x.Key.tags2].ToString(), PercentFormatter.Percent( x.Value, freq_sum ) );
  }

  // --------------
  // 4-ГРАММЫ
  // --------------

  dest.WriteLine( "\n\n// {0} 4-grams:", ngrams4.Count );

  List<KeyValuePair<NGram4, int>> n4f = new List<KeyValuePair<NGram4, int>>( ngrams4.Select( z => z ) );
  n4f.Sort( new NGram4Freq() );

  Dictionary<NGram3, int> n4_tag_sum = new Dictionary<NGram3, int>();
  foreach( var x in n4f )
  {
   NGram3 key;
   key.tags0 = x.Key.tags0;
   key.tags1 = x.Key.tags1;
   key.tags2 = x.Key.tags2;
   int freq;
   if( n4_tag_sum.TryGetValue( key, out freq ) )
    n4_tag_sum[key] = freq + x.Value;
   else
    n4_tag_sum.Add( key, x.Value );
  }

  tag0_cur = -1;
  tag1_cur = -1;
  int tag2_cur = -1;
  foreach( var x in n4f )
  {
   if( tag0_cur != x.Key.tags0 || tag1_cur != x.Key.tags1 || tag2_cur != x.Key.tags2 )
   {
    tag0_cur = x.Key.tags0;
    tag1_cur = x.Key.tags1;
    tag2_cur = x.Key.tags2;

    dest.WriteLine( "{0}", new string( '-', 40 ) );
   }

   NGram3 key;
   key.tags0 = x.Key.tags0;
   key.tags1 = x.Key.tags1;
   key.tags2 = x.Key.tags2;
   int freq_sum = n4_tag_sum[key];

   dest.WriteLine( "tetragram {0} {1} {2} -> {3} : {4} // {5} | {6} | {7} | {8} -> {9}",
    x.Key.tags0, x.Key.tags1, x.Key.tags2, x.Key.tags3, x.Value,
    tags[x.Key.tags0].ToString(), tags[x.Key.tags1].ToString(), tags[x.Key.tags2].ToString(),
    selectors[x.Key.tags3].ToString(), PercentFormatter.Percent( x.Value, freq_sum ) );
  }

  return;
 }




 public void SelectPOS( SolarixGrammarEngineNET.AnalysisResults projs, List<Dictionary<int, int>> pos_score )
 {
  List<List<int>> word2tags = new List<List<int>>();

  // Преобразуем все проекции каждого слова в варианты распознавания тегов
  for( int i = 0; i < projs.Count; ++i )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode proj = projs[i];
   string word = proj.GetWord().ToLower();

   List<int> wt = new List<int>();
   for( int j = 0; j < proj.VersionCount(); ++j )
   {
    int id_tag = tags.MatchTags( proj, j, gren );
    if( !wt.Contains( id_tag ) )
     wt.Add( id_tag );
   }

   word2tags.Add( wt );
  }



  List<int> pos_score_order = new List<int>();

  // Инициализируем вектор частей речи значениями, которые соответствуют
  // чамым частотным словоформам.
  for( int iword = 0; iword < projs.Count - 1; ++iword )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode proj = projs[iword];

   Dictionary<int, int> p = new Dictionary<int, int>();

   for( int iproj = 0; iproj < proj.VersionCount(); ++iproj )
   {
    int ekey = proj.GetVersionEntryID( iproj );
    int id_class = gren.GetEntryClass( ekey );

    if( !p.ContainsKey( id_class ) )
    {
     // Первый по порядку вариант повысим в шансах быть избранным, так как он уже выбран на основе частоты монограмм.
     if( iproj == 0 )
      p.Add( id_class, 1 );
     else
      p.Add( id_class, 0 );
    }
   }

   pos_score.Add( p );
   pos_score_order.Add( 1 );
  }


  bool use_2grams = true;
  bool use_3grams = true;
  bool use_4grams = true;

  int LAST_WORD_INDEX = projs.Count - 1;

  // ---------------------------------
  // теперь применим модель
  // ---------------------------------

  for( int iword = 0; iword < projs.Count; ++iword )
  {
   string word = projs[iword].GetWord();

   bool applied = false;

   // ==============
   // ТЕТРАГРАММЫ
   // ==============
   if( use_4grams )
   {
    if( !applied )
    {
     if( word2tags[iword].Count > 1 )
     {
      if( iword > 2 )
      {
       // Выбираем POS для iword на основе iword-3,iword-2,iword-1
       List<int> tags0 = word2tags[iword - 3];
       List<int> tags1 = word2tags[iword - 2];
       List<int> tags2 = word2tags[iword - 1];

       foreach( int tag0 in tags0 )
        foreach( int tag1 in tags1 )
         foreach( int tag2 in tags2 )
         {
          List<NGram4> n4_list;
          Int3 k = new Int3( tag0, tag1, tag2 );

          if( tag0_2_ngram4.TryGetValue( k, out n4_list ) )
          {
           // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1,tag2 и прибавляем очки соответствующим частям речи.
           foreach( NGram4 n4_probe in n4_list )
           {
            int tag3 = n4_probe.tags3;
            TagMatcher m = selectors[tag3];

            List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

            Dictionary<int, int> pos2score = pos_score[iword];

            foreach( KeyValuePair<int, int> p in pos2score )
            {
             if( m.MatchPartOfSpeech( p.Key ) )
             {
              int m_freq = ngrams4[n4_probe];
              changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
              applied = true;
             }
            }

            foreach( var kv in changes )
             pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

            pos_score_order[iword] = 4;
           }
          }
         }
      }

      if( iword > 1 && iword < LAST_WORD_INDEX )
      {
       // Выбираем POS для iword на основе iword-2,iword-1,iword+1
       List<int> tags0 = word2tags[iword - 2];
       List<int> tags1 = word2tags[iword - 1];
       List<int> tags3 = word2tags[iword + 1];

       foreach( int tag0 in tags0 )
        foreach( int tag1 in tags1 )
         foreach( int tag3 in tags3 )
         {
          List<NGram4> n4_list;
          Int3 k = new Int3( tag0, tag1, tag3 );

          if( tag1_2_ngram4.TryGetValue( k, out n4_list ) )
          {
           // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1,tag3 и прибавляем очки соответствующим частям речи.
           foreach( NGram4 n4_probe in n4_list )
           {
            int tag2 = n4_probe.tags2;
            TagMatcher m = selectors[tag2];

            List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

            Dictionary<int, int> pos2score = pos_score[iword];

            foreach( KeyValuePair<int, int> p in pos2score )
            {
             if( m.MatchPartOfSpeech( p.Key ) )
             {
              int m_freq = ngrams4_1[n4_probe];
              changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
              applied = true;
             }
            }

            foreach( var kv in changes )
             pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

            pos_score_order[iword] = 4;
           }
          }
         }
      }
     }
     else if( iword > 2 && word2tags[iword - 1].Count > 1 && pos_score_order[iword - 1] < 4 ) // Выбираем POS для iword-1 на основе iword-3,iword-2,iword
     {
      List<int> tags0 = word2tags[iword - 3];
      List<int> tags1 = word2tags[iword - 2];
      List<int> tags3 = word2tags[iword];

      foreach( int tag0 in tags0 )
       foreach( int tag1 in tags1 )
        foreach( int tag3 in tags3 )
        {
         List<NGram4> n4_list;
         Int3 k = new Int3( tag0, tag1, tag3 );

         if( tag1_2_ngram4.TryGetValue( k, out n4_list ) )
         {
          // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1,tag2 и прибавляем очки соответствующим частям речи.
          foreach( NGram4 n4_probe in n4_list )
          {
           int tag2 = n4_probe.tags2;
           TagMatcher m = selectors[tag2];

           List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

           Dictionary<int, int> pos2score = pos_score[iword];

           foreach( KeyValuePair<int, int> p in pos2score )
           {
            if( m.MatchPartOfSpeech( p.Key ) )
            {
             int m_freq = ngrams4_1[n4_probe];
             changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
             applied = true;
            }
           }

           foreach( var kv in changes )
            pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

           pos_score_order[iword - 1] = 4;
          }
         }
        }
     }
    }
   }


   // ==============
   // ТРИГРАММЫ
   // ==============
   if( use_3grams )
   {
    if( !applied )
    {
     if( word2tags[iword].Count > 1 && pos_score_order[iword] < 3 )
     {
      if( iword > 1 )
      {
       // Выбираем POS для iword на основе iword-2,iword-1
       List<int> tags0 = word2tags[iword - 2];
       List<int> tags1 = word2tags[iword - 1];

       foreach( int tag0 in tags0 )
        foreach( int tag1 in tags1 )
        {
         List<NGram3> n3_list;
         Int2 k = new Int2( tag0, tag1 );

         if( tag0_2_ngram3.TryGetValue( k, out n3_list ) )
         {
          // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1, и прибавляем очки соответствующим частям речи.
          foreach( NGram3 n3_probe in n3_list )
          {
           int tag2 = n3_probe.tags2;
           TagMatcher m = selectors[tag2];

           List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

           Dictionary<int, int> pos2score = pos_score[iword];

           foreach( KeyValuePair<int, int> p in pos2score )
           {
            if( m.MatchPartOfSpeech( p.Key ) )
            {
             int m_freq = ngrams3[n3_probe];
             changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
             applied = true;
            }
           }

           foreach( var kv in changes )
            pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

           pos_score_order[iword] = 3;
          }
         }
        }
      }

      if( iword > 1 && iword < LAST_WORD_INDEX )
      {
       // добавим выбор POS в iword на основе iword-1,iword+1
       // сосед_слева  СЛОВО  сосед_справа
       //    tag0       tag1      tag2

       List<int> tags0 = word2tags[iword - 1];
       List<int> tags2 = word2tags[iword + 1];

       foreach( int tag0 in tags0 )
        foreach( int tag2 in tags2 )
        {
         List<NGram3> n3_list;
         Int2 k = new Int2( tag0, tag2 );

         if( tag1_2_ngram3.TryGetValue( k, out n3_list ) )
         {
          // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1, и прибавляем очки соответствующим частям речи.
          foreach( NGram3 n3_probe in n3_list )
          {
           int tag1 = n3_probe.tags1;
           TagMatcher m = selectors[tag1];

           List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

           Dictionary<int, int> pos2score = pos_score[iword];

           foreach( KeyValuePair<int, int> p in pos2score )
           {
            if( m.MatchPartOfSpeech( p.Key ) )
            {
             int m_freq = ngrams3_1[n3_probe];
             changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
             applied = true;
            }
           }

           foreach( var kv in changes )
            pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

           pos_score_order[iword] = 3;
          }
         }
        }
      }
     }
     else if( iword > 1 && word2tags[iword - 1].Count > 1 && pos_score_order[iword - 1] < 3 ) // Выбираем POS для iword-1 на основе iword-2,iword
     {
      List<int> tags0 = word2tags[iword - 2];
      List<int> tags2 = word2tags[iword];

      foreach( int tag0 in tags0 )
       foreach( int tag2 in tags2 )
       {
        List<NGram3> n3_list;
        Int2 k = new Int2( tag0, tag2 );

        if( tag1_2_ngram3.TryGetValue( k, out n3_list ) )
        {
         // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1, и прибавляем очки соответствующим частям речи.
         foreach( NGram3 n3_probe in n3_list )
         {
          int tag1 = n3_probe.tags1;
          TagMatcher m = selectors[tag1];

          List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

          Dictionary<int, int> pos2score = pos_score[iword];

          foreach( KeyValuePair<int, int> p in pos2score )
          {
           if( m.MatchPartOfSpeech( p.Key ) )
           {
            int m_freq = ngrams3_1[n3_probe];
            changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
            applied = true;
           }
          }

          foreach( var kv in changes )
           pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

          pos_score_order[iword] = 3;
         }
        }
       }
     }
    }
   }


   // ==============
   // ДИГРАММЫ
   // ==============
   if( use_2grams )
   {
    if( !applied )
    {
     if( word2tags[iword].Count > 1 && pos_score_order[iword] < 2 ) // Выбираем POS для iword на основе iword-1
     {
      if( iword > 1 )
      {
       List<int> tags0 = word2tags[iword - 1];

       foreach( int tag0 in tags0 )
       {
        List<NGram2> n2_list;
        if( tag0_2_ngram2.TryGetValue( tag0, out n2_list ) )
        {
         // Перебираем варианты, которые вытекают из наличия тега tag0, и прибавляем очки соответствующим частям речи.
         foreach( NGram2 n2_probe in n2_list )
         {
          int tag1 = n2_probe.tags1;
          TagMatcher m = selectors[tag1];

          List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

          Dictionary<int, int> pos2score = pos_score[iword];

          foreach( KeyValuePair<int, int> p in pos2score )
          {
           if( m.MatchPartOfSpeech( p.Key ) )
           {
            int m_freq = ngrams2[n2_probe];
            changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
            applied = true;
           }
          }

          foreach( var kv in changes )
           pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

          pos_score_order[iword] = 2;
         }
        }

       }
      }

      if( iword < LAST_WORD_INDEX )
      {
       List<int> tags1 = word2tags[iword + 1];

       foreach( int tag1 in tags1 )
       {
        List<NGram2> n2_list;
        if( tag1_2_ngram2.TryGetValue( tag1, out n2_list ) )
        {
         // Перебираем варианты, которые вытекают из наличия тега tag1, и прибавляем очки соответствующим частям речи.
         foreach( NGram2 n2_probe in n2_list )
         {
          int tag0 = n2_probe.tags0;
          TagMatcher m = selectors[tag0];

          List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

          Dictionary<int, int> pos2score = pos_score[iword];

          foreach( KeyValuePair<int, int> p in pos2score )
          {
           if( m.MatchPartOfSpeech( p.Key ) )
           {
            int m_freq = ngrams2_1[n2_probe];
            changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
            applied = true;
           }
          }

          foreach( var kv in changes )
           pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

          pos_score_order[iword] = 2;
         }
        }

       }
      }

     }
     else if( iword > 1 && word2tags[iword - 1].Count > 1 && pos_score_order[iword - 1] == 1 ) // Выбираем POS для iword-1 на основе iword
     {
      List<int> tags1 = word2tags[iword];

      foreach( int tag1 in tags1 )
      {
       List<NGram2> n2_list;
       if( tag1_2_ngram2.TryGetValue( tag1, out n2_list ) )
       {
        // Перебираем варианты, которые вытекают из наличия тега tag1, и прибавляем очки соответствующим частям речи.
        foreach( NGram2 n2_probe in n2_list )
        {
         int tag0 = n2_probe.tags0;
         TagMatcher m = selectors[tag0];

         List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

         Dictionary<int, int> pos2score = pos_score[iword - 1];

         foreach( KeyValuePair<int, int> p in pos2score )
         {
          if( m.MatchPartOfSpeech( p.Key ) )
          {
           int m_freq = ngrams2_1[n2_probe];
           changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
           applied = true;
          }
         }

         foreach( var kv in changes )
          pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

         pos_score_order[iword - 1] = 2;
        }
       }
      }
     }
    }
   }
  }

  return;
 }

}
#endregion Морфологическая_Модель




#region Суффиксальная_Модель
class BayesStat_Suffix
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


 private TagBook selectors;

 private Dictionary<NGram2, int> ngrams2;
 private Dictionary<int, List<NGram2>> tag0_2_ngram2;

 private Dictionary<NGram2, int> ngrams2_1;
 private Dictionary<int, List<NGram2>> tag1_2_ngram2;

 private Dictionary<NGram3, int> ngrams3;
 private Dictionary<Int2, List<NGram3>> tag0_2_ngram3;

 private Dictionary<NGram3, int> ngrams3_1;
 private Dictionary<Int2, List<NGram3>> tag1_2_ngram3;

 private Dictionary<NGram4, int> ngrams4;
 private Dictionary<Int3, List<NGram4>> tag0_2_ngram4;

 private Dictionary<NGram4, int> ngrams4_1;
 private Dictionary<Int3, List<NGram4>> tag1_2_ngram4;

 public BayesStat_Suffix()
 {
  ngrams2 = new Dictionary<NGram2, int>();
  tag0_2_ngram2 = new Dictionary<int, List<NGram2>>();

  ngrams2_1 = new Dictionary<NGram2, int>();
  tag1_2_ngram2 = new Dictionary<int, List<NGram2>>();

  ngrams3 = new Dictionary<NGram3, int>();
  tag0_2_ngram3 = new Dictionary<Int2, List<NGram3>>();

  ngrams3_1 = new Dictionary<NGram3, int>();
  tag1_2_ngram3 = new Dictionary<Int2, List<NGram3>>();

  ngrams4 = new Dictionary<NGram4, int>();
  tag0_2_ngram4 = new Dictionary<Int3, List<NGram4>>();

  ngrams4_1 = new Dictionary<NGram4, int>();
  tag1_2_ngram4 = new Dictionary<Int3, List<NGram4>>();
 }


 private SolarixGrammarEngineNET.GrammarEngine2 gren;

 public void Init( SolarixGrammarEngineNET.GrammarEngine2 _gren )
 {
  gren = _gren;

  foreach( string w in new[] { "надо", "подо", "между", "выше", "ниже" } )
  {
   undividable_words.Add( w );
  }

  selectors = new TagBook( "pos_prediction" );

  string str_selectors =
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
";

  selectors.Load( str_selectors, gren );
 }


 private void AddNGram( int tags0, int tags1 )
 {
  NGram2 n2;
  n2.tags0 = tags0;
  n2.tags1 = tags1;

  int freq = 0;
  if( ngrams2.TryGetValue( n2, out freq ) )
  {
   ngrams2[n2] = freq + 1;
  }
  else
  {
   ngrams2.Add( n2, 1 );
  }

  return;
 }


 private void AddNGram_1( int tags0, int tags1 )
 {
  NGram2 n2;
  n2.tags0 = tags0;
  n2.tags1 = tags1;

  int freq = 0;
  if( ngrams2_1.TryGetValue( n2, out freq ) )
  {
   ngrams2_1[n2] = freq + 1;
  }
  else
  {
   ngrams2_1.Add( n2, 1 );
  }

  return;
 }





 private void AddNGram( int tags0, int tags1, int tags2 )
 {
  NGram3 n3;
  n3.tags0 = tags0;
  n3.tags1 = tags1;
  n3.tags2 = tags2;

  int freq = 0;
  if( ngrams3.TryGetValue( n3, out freq ) )
  {
   ngrams3[n3] = freq + 1;
  }
  else
  {
   ngrams3.Add( n3, 1 );
  }

  return;
 }


 private void AddNGram_1( int tags0, int tags1, int tags2 )
 {
  NGram3 n3;
  n3.tags0 = tags0;
  n3.tags1 = tags1;
  n3.tags2 = tags2;

  int freq = 0;
  if( ngrams3_1.TryGetValue( n3, out freq ) )
  {
   ngrams3_1[n3] = freq + 1;
  }
  else
  {
   ngrams3_1.Add( n3, 1 );
  }

  return;
 }


 private void AddNGram( int tags0, int tags1, int tags2, int tags3 )
 {
  NGram4 n4;
  n4.tags0 = tags0;
  n4.tags1 = tags1;
  n4.tags2 = tags2;
  n4.tags3 = tags3;

  int freq = 0;
  if( ngrams4.TryGetValue( n4, out freq ) )
  {
   ngrams4[n4] = freq + 1;
  }
  else
  {
   ngrams4.Add( n4, 1 );
  }

  return;
 }

 private void AddNGram_1( int tags0, int tags1, int tags2, int tags3 )
 {
  NGram4 n4;
  n4.tags0 = tags0;
  n4.tags1 = tags1;
  n4.tags2 = tags2;
  n4.tags3 = tags3;

  int freq = 0;
  if( ngrams4_1.TryGetValue( n4, out freq ) )
  {
   ngrams4_1[n4] = freq + 1;
  }
  else
  {
   ngrams4_1.Add( n4, 1 );
  }

  return;
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


 public bool ProcessSample( string line, SolarixGrammarEngineNET.AnalysisResults tokens )
 {
  List<int> token2tags = new List<int>();
  List<int> token2selectors = new List<int>();

  int last_word_index = tokens.Count - 1;

  for( int i = 0; i < tokens.Count; ++i )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];

   int tt = GetTokenSuffix( i, last_word_index, token );
   token2tags.Add( tt );

   int st = selectors.MatchTags( token, gren );
   token2selectors.Add( st );
  }


  // --------------------
  // ДИГРАММЫ
  // --------------------

  // 1 --> 2
  for( int iword = 1; iword < tokens.Count; ++iword )
  {
   // ДИГРАММЫ
   int tags1 = token2tags[iword - 1];
   if( tags1 != -1 )
   {
    int tags2 = token2selectors[iword];
    if( tags2 != -1 )
     AddNGram( tags1, tags2 );
   }
  }

  // 2 --> 1
  for( int iword = 1; iword < tokens.Count; ++iword )
  {
   int tags2 = token2tags[iword];
   if( tags2 != -1 )
   {
    int tags1 = token2selectors[iword - 1];

    if( tags1 != -1 )
     AddNGram_1( tags1, tags2 );
   }
  }


  // ---------------------------------------------
  // ТРИГРАММЫ
  // ---------------------------------------------

  // 1,2 --> 3
  for( int iword = 2; iword < tokens.Count; ++iword )
  {
   int tags0 = token2tags[iword - 2];
   if( tags0 != -1 )
   {
    int tags1 = token2tags[iword - 1];
    if( tags1 != -1 )
    {
     int tags2 = token2selectors[iword];
     if( tags2 != -1 )
      AddNGram( tags0, tags1, tags2 );
    }
   }
  }

  // 1 --> 2 <-- 3
  for( int iword = 2; iword < tokens.Count; ++iword )
  {
   int tags0 = token2tags[iword - 2];
   if( tags0 != -1 )
   {
    int tags1 = token2selectors[iword - 1];
    if( tags1 != -1 )
    {
     int tags2 = token2tags[iword];
     if( tags2 != -1 )
      AddNGram_1( tags0, tags1, tags2 );
    }
   }
  }

  // ---------------------------------------------
  // ТЕТРАГРАММЫ
  // ---------------------------------------------

  // 1,2,3 --> 4
  for( int iword = 3; iword < tokens.Count; ++iword )
  {
   int tags0 = token2tags[iword - 3];
   if( tags0 != -1 )
   {
    int tags1 = token2tags[iword - 2];
    if( tags1 != -1 )
    {
     int tags2 = token2tags[iword - 1];
     if( tags2 != -1 )
     {
      int tags3 = token2selectors[iword];
      if( tags3 != -1 )
      {
       AddNGram( tags0, tags1, tags2, tags3 );
      }
     }
    }
   }
  }


  // 1,2 --> 3 <-- 4

  for( int iword = 3; iword < tokens.Count; ++iword )
  {
   int tags0 = token2tags[iword - 3];
   if( tags0 != -1 )
   {
    int tags1 = token2tags[iword - 2];
    if( tags1 != -1 )
    {
     int tags2 = token2selectors[iword - 1];
     if( tags2 != -1 )
     {
      int tags3 = token2tags[iword];
      if( tags3 != -1 )
      {
       AddNGram_1( tags0, tags1, tags2, tags3 );
      }
     }
    }
   }
  }

  return true;
 }

 public void FinishLearning()
 {
  // -----------------
  // ДИГРАММЫ
  // -----------------

  foreach( KeyValuePair<NGram2, int> x in ngrams2 )
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


  foreach( KeyValuePair<NGram2, int> x in ngrams2_1 )
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


  // -------------
  // ТРИГРАММЫ
  // -------------

  foreach( KeyValuePair<NGram3, int> x in ngrams3 )
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


  foreach( KeyValuePair<NGram3, int> x in ngrams3_1 )
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



  // ------------------
  // ТЕТРАГРАММЫ
  // ------------------

  foreach( KeyValuePair<NGram4, int> x in ngrams4 )
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

  foreach( KeyValuePair<NGram4, int> x in ngrams4_1 )
  {
   int tags0 = x.Key.tags0;
   int tags1 = x.Key.tags1;
   int tags3 = x.Key.tags3;
   Int3 k = new Int3( tags0, tags1, tags3 );

   List<NGram4> n;
   if( tag1_2_ngram4.TryGetValue( k, out n ) )
   {
    n.Add( x.Key );
   }
   else
   {
    n = new List<NGram4>();
    n.Add( x.Key );
    tag1_2_ngram4.Add( k, n );
   }
  }



  return;
 }



 public void SelectPOS( SolarixGrammarEngineNET.AnalysisResults projs, List<Dictionary<int, int>> pos_score )
 {
  int last_word_index = projs.Count - 1;


  List<int> n_pos = new List<int>(); // кол-во разных частей речи для каждого токена
  List<int> word2tags = new List<int>();

  // Преобразуем все проекции каждого слова в варианты распознавания тегов
  for( int i = 0; i < projs.Count; ++i )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode token = projs[i];
   int index = GetTokenSuffix( i, last_word_index, token );

   word2tags.Add( index );

   // На сколько разных частей речи проецируется данное слово
   List<int> pos_list = new List<int>();
   for( int k = 0; k < projs[i].VersionCount(); ++k )
   {
    int ekey0 = projs[i].GetVersionEntryID( k );
    int id_class0 = gren.GetEntryClass( ekey0 );
    if( !pos_list.Contains( id_class0 ) )
     pos_list.Add( id_class0 );
   }

   n_pos.Add( pos_list.Count );
  }

  List<int> pos_score_order = new List<int>();

  // Инициализируем вектор частей речи значениями, которые соответствуют
  // чамым частотным словоформам.
  for( int iword = 0; iword < projs.Count - 1; ++iword )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode proj = projs[iword];

   Dictionary<int, int> p = new Dictionary<int, int>();

   for( int iproj = 0; iproj < proj.VersionCount(); ++iproj )
   {
    int ekey = proj.GetVersionEntryID( iproj );
    int id_class = gren.GetEntryClass( ekey );

    if( !p.ContainsKey( id_class ) )
    {
     if( iproj == 0 )
      p.Add( id_class, 1 );
     else
      p.Add( id_class, 0 );
    }
   }

   pos_score.Add( p );
   pos_score_order.Add( 1 );
  }


  // ---------------------------------
  // теперь применим модель
  // ---------------------------------
  bool use_4grams = true;
  bool use_3grams = true;
  bool use_2grams = true;

  for( int iword = 1; iword < projs.Count - 1; ++iword )
  {
   string word = projs[iword].GetWord();

   bool applied = false;

   // ==============
   // ТЕТРАГРАММЫ
   // ==============

   if( use_4grams && !applied && iword > 2 )
   {
    if( n_pos[iword] > 1 ) // Выбираем POS для iword на основе iword-3,iword-2,iword-1
    {
     int tag0 = word2tags[iword - 3];
     int tag1 = word2tags[iword - 2];
     int tag2 = word2tags[iword - 1];

     List<NGram4> n4_list;
     Int3 k = new Int3( tag0, tag1, tag2 );

     if( tag0_2_ngram4.TryGetValue( k, out n4_list ) )
     {
      // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1,tag2 и прибавляем очки соответствующим частям речи.
      foreach( NGram4 n4_probe in n4_list )
      {
       int tag3 = n4_probe.tags3;
       TagMatcher m = selectors[tag3];

       List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

       Dictionary<int, int> pos2score = pos_score[iword];

       foreach( KeyValuePair<int, int> p in pos2score )
       {
        if( m.MatchPartOfSpeech( p.Key ) )
        {
         int m_freq = ngrams4[n4_probe];
         changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
         applied = true;
        }
       }

       foreach( var kv in changes )
        pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

       pos_score_order[iword] = 4;
      }
     }
    }
    else if( n_pos[iword - 1] > 1 && pos_score_order[iword - 1] < 4 ) // Выбираем POS для iword-1 на основе iword-3,iword-2,iword
    {
     int tag0 = word2tags[iword - 3];
     int tag1 = word2tags[iword - 2];
     int tag3 = word2tags[iword];

     List<NGram4> n4_list;
     Int3 k = new Int3( tag0, tag1, tag3 );

     if( tag1_2_ngram4.TryGetValue( k, out n4_list ) )
     {
      // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1,tag2 и прибавляем очки соответствующим частям речи.
      foreach( NGram4 n4_probe in n4_list )
      {
       int tag2 = n4_probe.tags2;
       TagMatcher m = selectors[tag2];

       List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

       Dictionary<int, int> pos2score = pos_score[iword];

       foreach( KeyValuePair<int, int> p in pos2score )
       {
        if( m.MatchPartOfSpeech( p.Key ) )
        {
         int m_freq = ngrams4_1[n4_probe];
         changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
         applied = true;
        }
       }

       foreach( var kv in changes )
        pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

       pos_score_order[iword - 1] = 4;
      }
     }
    }
   }



   // ==============
   // ТРИГРАММЫ
   // ==============

   if( use_3grams && !applied && iword > 1 )
   {
    if( n_pos[iword] > 1 ) // Выбираем POS для iword на основе iword-2,iword-1
    {
     {
      int tag0 = word2tags[iword - 2];
      int tag1 = word2tags[iword - 1];

      List<NGram3> n3_list;
      Int2 k = new Int2( tag0, tag1 );

      if( tag0_2_ngram3.TryGetValue( k, out n3_list ) )
      {
       // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1, и прибавляем очки соответствующим частям речи.
       foreach( NGram3 n3_probe in n3_list )
       {
        int tag2 = n3_probe.tags2;
        TagMatcher m = selectors[tag2];

        List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

        Dictionary<int, int> pos2score = pos_score[iword];

        foreach( KeyValuePair<int, int> p in pos2score )
        {
         if( m.MatchPartOfSpeech( p.Key ) )
         {
          int m_freq = ngrams3[n3_probe];
          changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
          applied = true;
         }
        }

        foreach( var kv in changes )
         pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;
       }
      }
     }


     if( iword < last_word_index )
     {
      // iword-1 --> iword <-- iword+1

      int tag0 = word2tags[iword - 1];
      int tag2 = word2tags[iword + 1];

      List<NGram3> n3_list;
      Int2 k = new Int2( tag0, tag2 );

      if( tag1_2_ngram3.TryGetValue( k, out n3_list ) )
      {
       // Перебираем варианты, которые вытекают из наличия тегов tag0,tag2, и прибавляем очки соответствующим частям речи.
       foreach( NGram3 n3_probe in n3_list )
       {
        int tag1 = n3_probe.tags1;
        TagMatcher m = selectors[tag1];

        List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

        Dictionary<int, int> pos2score = pos_score[iword];

        foreach( KeyValuePair<int, int> p in pos2score )
        {
         if( m.MatchPartOfSpeech( p.Key ) )
         {
          int m_freq = ngrams3_1[n3_probe];
          changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
          applied = true;
         }
        }

        foreach( var kv in changes )
         pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

        pos_score_order[iword] = 3;
       }
      }
     }
    }
    else if( n_pos[iword - 1] > 1 && pos_score_order[iword - 1] < 3 ) // Выбираем POS для iword-1 на основе iword-2,iword
    {
     int tag0 = word2tags[iword - 2];
     int tag2 = word2tags[iword];

     List<NGram3> n3_list;
     Int2 k = new Int2( tag0, tag2 );

     if( tag1_2_ngram3.TryGetValue( k, out n3_list ) )
     {
      // Перебираем варианты, которые вытекают из наличия тегов tag0,tag2, и прибавляем очки соответствующим частям речи.
      foreach( NGram3 n3_probe in n3_list )
      {
       int tag1 = n3_probe.tags1;
       TagMatcher m = selectors[tag1];

       List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

       Dictionary<int, int> pos2score = pos_score[iword];

       foreach( KeyValuePair<int, int> p in pos2score )
       {
        if( m.MatchPartOfSpeech( p.Key ) )
        {
         int m_freq = ngrams3_1[n3_probe];
         changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
         applied = true;
        }
       }

       foreach( var kv in changes )
        pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

       pos_score_order[iword] = 3;
      }
     }
    }
   }


   // ==============
   // ДИГРАММЫ
   // ==============

   if( use_2grams && !applied && iword > 1 )
   {
    if( n_pos[iword] > 1 ) // Выбираем POS для iword на основе iword-1
    {
     {
      int tag0 = word2tags[iword - 1];

      List<NGram2> n2_list;
      if( tag0_2_ngram2.TryGetValue( tag0, out n2_list ) )
      {
       // Перебираем варианты, которые вытекают из наличия тега tag0, и прибавляем очки соответствующим частям речи.
       foreach( NGram2 n2_probe in n2_list )
       {
        int tag1 = n2_probe.tags1;
        TagMatcher m = selectors[tag1];

        List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

        Dictionary<int, int> pos2score = pos_score[iword];

        foreach( KeyValuePair<int, int> p in pos2score )
        {
         if( m.MatchPartOfSpeech( p.Key ) )
         {
          int m_freq = ngrams2[n2_probe];
          changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
          applied = true;
         }
        }

        foreach( var kv in changes )
         pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

        pos_score_order[iword] = 2;
       }
      }
     }

     if( iword < last_word_index )
     {
      // iword <-- iword+1
      int tag1 = word2tags[iword + 1];

      List<NGram2> n2_list;
      if( tag1_2_ngram2.TryGetValue( tag1, out n2_list ) )
      {
       // Перебираем варианты, которые вытекают из наличия тега tag1, и прибавляем очки соответствующим частям речи.
       foreach( NGram2 n2_probe in n2_list )
       {
        int tag0 = n2_probe.tags0;
        TagMatcher m = selectors[tag0];

        List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

        Dictionary<int, int> pos2score = pos_score[iword];

        foreach( KeyValuePair<int, int> p in pos2score )
        {
         if( m.MatchPartOfSpeech( p.Key ) )
         {
          int m_freq = ngrams2_1[n2_probe];
          changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
          applied = true;
         }
        }

        foreach( var kv in changes )
         pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

        pos_score_order[iword] = 2;
       }
      }
     }
    }
    else if( n_pos[iword - 1] > 1 && pos_score_order[iword - 1] == 1 ) // Выбираем POS для iword-1 на основе iword
    {
     int tag1 = word2tags[iword];

     List<NGram2> n2_list;
     if( tag1_2_ngram2.TryGetValue( tag1, out n2_list ) )
     {
      // Перебираем варианты, которые вытекают из наличия тега tag1, и прибавляем очки соответствующим частям речи.
      foreach( NGram2 n2_probe in n2_list )
      {
       int tag0 = n2_probe.tags0;
       TagMatcher m = selectors[tag0];

       List<KeyValuePair<int, int>> changes = new List<KeyValuePair<int, int>>();

       Dictionary<int, int> pos2score = pos_score[iword - 1];

       foreach( KeyValuePair<int, int> p in pos2score )
       {
        if( m.MatchPartOfSpeech( p.Key ) )
        {
         int m_freq = ngrams2_1[n2_probe];
         changes.Add( new KeyValuePair<int, int>( p.Key, m_freq ) );
         applied = true;
        }
       }

       foreach( var kv in changes )
        pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

       pos_score_order[iword - 1] = 2;
      }
     }
    }
   }
  }

  return;
 }
}
#endregion Суффиксальная_Модель



class Builder_Bayes_2Factor
{
 BayesStat_Morph MORPH;
 BayesStat_Suffix SUFFIX;

 public Builder_Bayes_2Factor()
 {
  MORPH = new BayesStat_Morph();
  SUFFIX = new BayesStat_Suffix();
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
  MORPH.Init( gren );
  SUFFIX.Init( gren );
 }




 public bool ProcessSample( string line )
 {
  // Морфологический разбор
  SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY );

  MORPH.ProcessSample( line, tokens );
  SUFFIX.ProcessSample( line, tokens );

  return true;
 }



 public void FinishLearning()
 {
  MORPH.FinishLearning();
  SUFFIX.FinishLearning();

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
   // Токенизация без использования синтаксических правил
   using( SolarixGrammarEngineNET.AnalysisResults projs = gren.AnalyzeMorphology( line, LanguageID,
    SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY /*| SolarixGrammarEngineNET.GrammarEngine.SOL_GREN_DISABLE_FILTERS*/ ) )
   {

    if( tokens.Count != projs.Count )
    {
     return;
    }


    // -----------------------------------------
    // Посчитаем ошибки до применения модели
    // -----------------------------------------
    int n_err = 0;
    for( int iword = 1; iword < tokens.Count - 1; ++iword )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode proj = projs[iword];
     int ekey0 = proj.GetEntryID();
     int id_class0 = gren.GetEntryClass( ekey0 );

     // Совпадает с точным значением?
     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[iword];
     int ekey1 = token.GetEntryID();
     int id_class1 = gren.GetEntryClass( ekey1 );

     if( id_class0 != id_class1 )
      n_err++;
    }

    error_count_no_filter += n_err;
    total_word_count += ( tokens.Count - 2 );

    List<Dictionary<int, int>> pos_score_1 = new List<Dictionary<int, int>>();
    MORPH.SelectPOS( projs, pos_score_1 );

    List<Dictionary<int, int>> pos_score_2 = new List<Dictionary<int, int>>();
    SUFFIX.SelectPOS( projs, pos_score_2 );

    List<Dictionary<int, double>> pos_score = new List<Dictionary<int, double>>();
    for( int i = 0; i < pos_score_1.Count; ++i )
    {
     Dictionary<int, double> scores = new Dictionary<int, double>();

     double sum_1 = 0.0;
     foreach( KeyValuePair<int, int> k in pos_score_1[i] )
      sum_1 += k.Value;

     double sum_2 = 0.0;
     foreach( KeyValuePair<int, int> k in pos_score_2[i] )
      sum_2 += k.Value;

     foreach( KeyValuePair<int, int> k in pos_score_1[i] )
     {
      double s1 = ( (double)k.Value ) / sum_1;

      int f2;
      if( !pos_score_2[i].TryGetValue( k.Key, out f2 ) )
       f2 = 0;

      double s2 = ( (double)f2 ) / sum_2;

      double ss = s1 * s2;

      scores.Add( k.Key, ss );
     }

     foreach( KeyValuePair<int, int> k in pos_score_2[i] )
     {
      if( !scores.ContainsKey( k.Key ) )
      {
       double s2 = ( (double)k.Value ) / sum_2;
       scores.Add( k.Key, s2 );
      }
     }

     pos_score.Add( scores );
    }


    // -----------------------------------------------------------
    // Совпадает ли выбранные id_class с требуемыми значениями?
    // -----------------------------------------------------------

    for( int iword = 1; iword < projs.Count - 1; ++iword )
    {
     Dictionary<int, double> word_pos_scores = pos_score[iword];
     double best_score = 0;
     int best_pos = -1;
     foreach( KeyValuePair<int, double> k in word_pos_scores )
     {
      if( k.Value > best_score )
      {
       best_score = k.Value;
       best_pos = k.Key;
      }
     }

     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[iword];
     int ekey1 = token.GetEntryID();
     int id_class1 = gren.GetEntryClass( ekey1 );

     if( best_pos != id_class1 )
      error_count_with_model++;
    }

   }
  }

  return;
 }




 public void DumpRules( string filepath )
 {
  using( System.IO.StreamWriter dest = new System.IO.StreamWriter( filepath, false, new UTF8Encoding( true ) ) )
  {
   MORPH.DumpRules( dest );
  }

  return;
 }
}
