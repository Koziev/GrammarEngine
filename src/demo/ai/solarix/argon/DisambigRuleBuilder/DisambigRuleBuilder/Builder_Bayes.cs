using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;


class Builder_Bayes
{
 private TagBook tags, selectors;

 private double A2 = 1.0, A3 = 10.0, A4 = 100.0;
 private bool smooth = true;

 private bool use_2 = false;
 private Dictionary<NGram2, int> ngrams2_0;
 private Dictionary<int, List<NGram2>> tag0_ngram2;

 private Dictionary<NGram2, int> ngrams2_1;
 private Dictionary<int, List<NGram2>> tag1_ngram2;

 // ---------

 private bool use_3 = true;
 private Dictionary<NGram3, int> ngrams3_0; // 0,1 --> 2
 private Dictionary<Int2, List<NGram3>> tag0_ngram3;

 private Dictionary<NGram3, int> ngrams3_1; // 0 --> 1 <-- 2
 private Dictionary<Int2, List<NGram3>> tag1_ngram3;

 private Dictionary<NGram3, int> ngrams3_2; // 0 <-- 1,2
 private Dictionary<Int2, List<NGram3>> tag2_ngram3;

 // --------

 private bool use_4 = false;
 private Dictionary<NGram4, int> ngrams4_0; // 0,1,2 --> 3
 private Dictionary<Int3, List<NGram4>> tag0_ngram4;

 private Dictionary<NGram4, int> ngrams4_1; // 0,1 --> 2 <-- 3
 private Dictionary<Int3, List<NGram4>> tag1_ngram4;

 private Dictionary<NGram4, int> ngrams4_2; // 0 --> 1 <-- 2,3
 private Dictionary<Int3, List<NGram4>> tag2_ngram4;

 private Dictionary<NGram4, int> ngrams4_3; // 0 <-- 1,2,3
 private Dictionary<Int3, List<NGram4>> tag3_ngram4;

 public Builder_Bayes()
 {
  ngrams2_0 = new Dictionary<NGram2, int>();
  tag0_ngram2 = new Dictionary<int, List<NGram2>>();

  ngrams2_1 = new Dictionary<NGram2, int>();
  tag1_ngram2 = new Dictionary<int, List<NGram2>>();

  // --------

  ngrams3_0 = new Dictionary<NGram3, int>();
  tag0_ngram3 = new Dictionary<Int2, List<NGram3>>();

  ngrams3_1 = new Dictionary<NGram3, int>();
  tag1_ngram3 = new Dictionary<Int2, List<NGram3>>();

  ngrams3_2 = new Dictionary<NGram3, int>();
  tag2_ngram3 = new Dictionary<Int2, List<NGram3>>();

  // --------

  ngrams4_0 = new Dictionary<NGram4, int>();
  tag0_ngram4 = new Dictionary<Int3, List<NGram4>>();

  ngrams4_1 = new Dictionary<NGram4, int>();
  tag1_ngram4 = new Dictionary<Int3, List<NGram4>>();

  ngrams4_2 = new Dictionary<NGram4, int>();
  tag2_ngram4 = new Dictionary<Int3, List<NGram4>>();

  ngrams4_3 = new Dictionary<NGram4, int>();
  tag3_ngram4 = new Dictionary<Int3, List<NGram4>>();
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
  tags = new TagBook( "опорный" );

  string str_tags =
@"
BETH:BEGIN{}
BETH:END{}

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
'-'
','
'.'

СУЩЕСТВИТЕЛЬНОЕ ПАДЕЖ:ЗВАТ

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

ВВОДНОЕ

БЕЗЛИЧ_ГЛАГОЛ

NUM_WORD

UNKNOWNENTRIES

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
";

  tags.Load( str_tags, gren );

  selectors = new TagBook( "pos_prediction" );
  string str_selectors =
@"
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

ГЛАГОЛ
ИНФИНИТИВ
ДЕЕПРИЧАСТИЕ
ПРЕДЛОГ
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
";

  selectors.Load( str_selectors, gren );
 }


 private void AddNGram_0( int tags0, int tags1 )
 {
  NGram2 n2;
  n2.tags0 = tags0;
  n2.tags1 = tags1;

  int freq = 0;
  if( ngrams2_0.TryGetValue( n2, out freq ) )
  {
   ngrams2_0[n2] = freq + 1;
  }
  else
  {
   ngrams2_0.Add( n2, 1 );
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



 // 0,1 --> 2
 private void AddNGram_0( int tags0, int tags1, int tags2 )
 {
  NGram3 n3;
  n3.tags0 = tags0;
  n3.tags1 = tags1;
  n3.tags2 = tags2;

  int freq = 0;
  if( ngrams3_0.TryGetValue( n3, out freq ) )
  {
   ngrams3_0[n3] = freq + 1;
  }
  else
  {
   ngrams3_0.Add( n3, 1 );
  }

  return;
 }


 // 0 --> 1 <-- 2
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

 // 0 <-- 1,2
 private void AddNGram_2( int tags0, int tags1, int tags2 )
 {
  NGram3 n3;
  n3.tags0 = tags0;
  n3.tags1 = tags1;
  n3.tags2 = tags2;

  int freq = 0;
  if( ngrams3_2.TryGetValue( n3, out freq ) )
  {
   ngrams3_2[n3] = freq + 1;
  }
  else
  {
   ngrams3_2.Add( n3, 1 );
  }

  return;
 }



 private void AddNGram_X( Dictionary<NGram4, int> ngrams3_x, int tag0, int tag1, int tag2, int tag3 )
 {
  NGram4 n4;
  n4.tags0 = tag0;
  n4.tags1 = tag1;
  n4.tags2 = tag2;
  n4.tags3 = tag3;

  int freq = 0;
  if( ngrams3_x.TryGetValue( n4, out freq ) )
  {
   ngrams3_x[n4] = freq + 1;
  }
  else
  {
   ngrams3_x.Add( n4, 1 );
  }

  return;
 }

 private void AddNGram_0( int tag0, int tag1, int tag2, int tag3 ) { AddNGram_X( ngrams4_0, tag0, tag1, tag2, tag3 ); }
 private void AddNGram_1( int tag0, int tag1, int tag2, int tag3 ) { AddNGram_X( ngrams4_1, tag0, tag1, tag2, tag3 ); }
 private void AddNGram_2( int tag0, int tag1, int tag2, int tag3 ) { AddNGram_X( ngrams4_2, tag0, tag1, tag2, tag3 ); }
 private void AddNGram_3( int tag0, int tag1, int tag2, int tag3 ) { AddNGram_X( ngrams4_3, tag0, tag1, tag2, tag3 ); }



 public bool ProcessSample( string line )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
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

   if( use_2 )
   {
    // 1 --> 2
    for( int iword = 0; iword < tokens.Count - 1; ++iword )
    {
     int tags1 = token2tags[iword];
     if( tags1 != -1 )
     {
      int tags2 = token2selectors[iword + 1];
      if( tags2 != -1 )
       AddNGram_0( tags1, tags2 );
     }
    }

    // 1 <-- 2
    for( int iword = 0; iword < tokens.Count - 1; ++iword )
    {
     int tags1 = token2selectors[iword];
     if( tags1 != -1 )
     {
      int tags2 = token2tags[iword + 1];
      if( tags2 != -1 )
       AddNGram_1( tags1, tags2 );
     }
    }
   }


   if( use_3 )
   {
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
        AddNGram_0( tags0, tags1, tags2 );
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


    // 1 <-- 2,3
    for( int iword = 2; iword < tokens.Count; ++iword )
    {
     int tags0 = token2selectors[iword - 2];
     if( tags0 != -1 )
     {
      int tags1 = token2tags[iword - 1];
      if( tags1 != -1 )
      {
       int tags2 = token2tags[iword];
       if( tags2 != -1 )
        AddNGram_2( tags0, tags1, tags2 );
      }
     }
    }

   }

   // ---------------------------------------------
   // ТЕТРАГРАММЫ
   // ---------------------------------------------
   if( use_4 )
   {
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
         AddNGram_0( tags0, tags1, tags2, tags3 );
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

    // 1 --> 2 <-- 3,4
    for( int iword = 3; iword < tokens.Count; ++iword )
    {
     int tags0 = token2tags[iword - 3];
     if( tags0 != -1 )
     {
      int tags1 = token2selectors[iword - 2];
      if( tags1 != -1 )
      {
       int tags2 = token2tags[iword - 1];
       if( tags2 != -1 )
       {
        int tags3 = token2tags[iword];
        if( tags3 != -1 )
        {
         AddNGram_2( tags0, tags1, tags2, tags3 );
        }
       }
      }
     }
    }

    // 1 <-- 2,3,4
    for( int iword = 3; iword < tokens.Count; ++iword )
    {
     int tags0 = token2selectors[iword - 3];
     if( tags0 != -1 )
     {
      int tags1 = token2tags[iword - 2];
      if( tags1 != -1 )
      {
       int tags2 = token2tags[iword - 1];
       if( tags2 != -1 )
       {
        int tags3 = token2tags[iword];
        if( tags3 != -1 )
        {
         AddNGram_3( tags0, tags1, tags2, tags3 );
        }
       }
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
  if( use_2 )
  {
   foreach( KeyValuePair<NGram2, int> x in ngrams2_0 )
   {
    int tags0 = x.Key.tags0;
    List<NGram2> n;
    if( tag0_ngram2.TryGetValue( tags0, out n ) )
    {
     n.Add( x.Key );
    }
    else
    {
     n = new List<NGram2>();
     n.Add( x.Key );
     tag0_ngram2.Add( tags0, n );
    }
   }


   foreach( KeyValuePair<NGram2, int> x in ngrams2_1 )
   {
    int tags1 = x.Key.tags1;
    List<NGram2> n;
    if( tag1_ngram2.TryGetValue( tags1, out n ) )
    {
     n.Add( x.Key );
    }
    else
    {
     n = new List<NGram2>();
     n.Add( x.Key );
     tag1_ngram2.Add( tags1, n );
    }
   }
  }


  // -------------
  // ТРИГРАММЫ
  // -------------
  if( use_3 )
  {
   foreach( KeyValuePair<NGram3, int> x in ngrams3_0 )
   {
    int tags0 = x.Key.tags0;
    int tags1 = x.Key.tags1;
    Int2 k = new Int2( tags0, tags1 );

    List<NGram3> n;
    if( tag0_ngram3.TryGetValue( k, out n ) )
    {
     n.Add( x.Key );
    }
    else
    {
     n = new List<NGram3>();
     n.Add( x.Key );
     tag0_ngram3.Add( k, n );
    }
   }


   foreach( KeyValuePair<NGram3, int> x in ngrams3_1 )
   {
    int tags0 = x.Key.tags0;
    int tags2 = x.Key.tags2;
    Int2 k = new Int2( tags0, tags2 );

    List<NGram3> n;
    if( tag1_ngram3.TryGetValue( k, out n ) )
    {
     n.Add( x.Key );
    }
    else
    {
     n = new List<NGram3>();
     n.Add( x.Key );
     tag1_ngram3.Add( k, n );
    }
   }


   foreach( KeyValuePair<NGram3, int> x in ngrams3_2 )
   {
    int tags1 = x.Key.tags0;
    int tags2 = x.Key.tags2;
    Int2 k = new Int2( tags1, tags2 );

    List<NGram3> n;
    if( tag2_ngram3.TryGetValue( k, out n ) )
    {
     n.Add( x.Key );
    }
    else
    {
     n = new List<NGram3>();
     n.Add( x.Key );
     tag2_ngram3.Add( k, n );
    }
   }
  }


  // ------------------
  // ТЕТРАГРАММЫ
  // ------------------
  if( use_4 )
  {
   foreach( KeyValuePair<NGram4, int> x in ngrams4_0 )
   {
    int tags0 = x.Key.tags0;
    int tags1 = x.Key.tags1;
    int tags2 = x.Key.tags2;
    Int3 k = new Int3( tags0, tags1, tags2 );

    List<NGram4> n;
    if( tag0_ngram4.TryGetValue( k, out n ) )
    {
     n.Add( x.Key );
    }
    else
    {
     n = new List<NGram4>();
     n.Add( x.Key );
     tag0_ngram4.Add( k, n );
    }
   }

   foreach( KeyValuePair<NGram4, int> x in ngrams4_1 )
   {
    int tags0 = x.Key.tags0;
    int tags1 = x.Key.tags1;
    int tags3 = x.Key.tags3;
    Int3 k = new Int3( tags0, tags1, tags3 );

    List<NGram4> n;
    if( tag1_ngram4.TryGetValue( k, out n ) )
    {
     n.Add( x.Key );
    }
    else
    {
     n = new List<NGram4>();
     n.Add( x.Key );
     tag1_ngram4.Add( k, n );
    }
   }


   foreach( KeyValuePair<NGram4, int> x in ngrams4_2 )
   {
    int tags0 = x.Key.tags0;
    int tags2 = x.Key.tags2;
    int tags3 = x.Key.tags3;
    Int3 k = new Int3( tags0, tags2, tags3 );

    List<NGram4> n;
    if( tag2_ngram4.TryGetValue( k, out n ) )
    {
     n.Add( x.Key );
    }
    else
    {
     n = new List<NGram4>();
     n.Add( x.Key );
     tag2_ngram4.Add( k, n );
    }
   }

   foreach( KeyValuePair<NGram4, int> x in ngrams4_3 )
   {
    int tags1 = x.Key.tags1;
    int tags2 = x.Key.tags2;
    int tags3 = x.Key.tags3;
    Int3 k = new Int3( tags1, tags2, tags3 );

    List<NGram4> n;
    if( tag3_ngram4.TryGetValue( k, out n ) )
    {
     n.Add( x.Key );
    }
    else
    {
     n = new List<NGram4>();
     n.Add( x.Key );
     tag3_ngram4.Add( k, n );
    }
   }
  }

  return;
 }




 public void Check(
                   string line,
                   ref int total_word_count,
                   ref int error_count_no_filter,
                   ref int POS_error_count,
                   ref int FEATURESET_error_count,
                   ref int VERB_error_count
                  )
 {
  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {
   List<List<int>> word2tags = new List<List<int>>();
   List<TagMatcher> word2selector = new List<TagMatcher>();

   // Токенизация без использования синтаксических правил
   using( SolarixGrammarEngineNET.AnalysisResults projs = gren.AnalyzeMorphology( line, LanguageID,
    SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY /*| SolarixGrammarEngineNET.GrammarEngine.SOL_GREN_DISABLE_FILTERS*/ ) )
   {

    if( tokens.Count != projs.Count )
    {
     return;
    }

    // Преобразуем все проекции каждого слова в варианты распознавания тегов
    for( int i = 0; i < tokens.Count; ++i )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
     string word = token.GetWord().ToLower();

     SolarixGrammarEngineNET.SyntaxTreeNode proj = projs[i];
     List<int> wt = new List<int>();
     for( int j = 0; j < proj.VersionCount(); ++j )
     {
      int id_tag = tags.MatchTags( proj, j, gren );
      if( !wt.Contains( id_tag ) )
       wt.Add( id_tag );
     }

     word2tags.Add( wt );
     word2selector.Add( null );
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

    List<Dictionary<int, double>> pos_score = new List<Dictionary<int, double>>();
    List<int> pos_score_order = new List<int>();

    // Инициализируем вектор частей речи значениями, которые соответствуют
    // чамым частотным словоформам.
    for( int iword = 0; iword < tokens.Count; ++iword )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode proj = projs[iword];

     Dictionary<int, double> p = new Dictionary<int, double>();

     for( int iproj = 0; iproj < proj.VersionCount(); ++iproj )
     {
      int ekey = proj.GetVersionEntryID( iproj );
      int id_class = gren.GetEntryClass( ekey );

      if( !p.ContainsKey( id_class ) )
      {
       // Первый по порядку вариант повысим в шансах быть избранным, так как он уже выбран на основе частоты монограмм.
       if( iproj == 0 )
        p.Add( id_class, 1.0 );
       else
        p.Add( id_class, 0.0 );
      }
     }

     pos_score.Add( p );
     pos_score_order.Add( 1 );
    }

    bool use_2grams = use_2;
    bool use_3grams = use_3;
    bool use_4grams = use_4;

    int LAST_WORD_INDEX = tokens.Count - 1;

    // ---------------------------------
    // теперь применим модель
    // ---------------------------------

    for( int iword = 1; iword < tokens.Count - 1; ++iword )
    {
     Dictionary<TagMatcher, double> selector2score = new Dictionary<TagMatcher, double>();

     SolarixGrammarEngineNET.SyntaxTreeNode proj = projs[iword];
     string word = tokens[iword].GetWord();

     Dictionary<int, double> pos2score = pos_score[iword];
     List<KeyValuePair<int, double>> changes = new List<KeyValuePair<int, double>>();

     // ==============
     // ТЕТРАГРАММЫ
     // ==============
     if( use_4grams )
     {
      if( word2tags[iword].Count > 1 )
      {
       if( iword >= 3 )
       {
        // 0,1,2 --> 3
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

           if( tag0_ngram4.TryGetValue( k, out n4_list ) )
           {
            // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1,tag2 и прибавляем очки соответствующим частям речи.
            foreach( NGram4 n4_probe in n4_list )
            {
             int tag3 = n4_probe.tags3;
             TagMatcher m = selectors[tag3];
             if( m.Match( proj, gren ) )
             {

              double m_freq = A4 * ngrams4_0[n4_probe];

              double score0;
              if( selector2score.TryGetValue( m, out score0 ) )
               selector2score[m] = score0 + m_freq;
              else
               selector2score.Add( m, m_freq );

              foreach( KeyValuePair<int, double> p in pos2score )
              {
               if( m.MatchPartOfSpeech( p.Key ) )
               {
                changes.Add( new KeyValuePair<int, double>( p.Key, m_freq ) );
               }
              }

              pos_score_order[iword] = 4;
             }
            }
           }
          }
       }

       if( iword >= 2 && iword < LAST_WORD_INDEX )
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

           if( tag1_ngram4.TryGetValue( k, out n4_list ) )
           {
            // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1,tag3 и прибавляем очки соответствующим частям речи.
            foreach( NGram4 n4_probe in n4_list )
            {
             int tag2 = n4_probe.tags2;
             TagMatcher m = selectors[tag2];
             if( m.Match( proj, gren ) )
             {
              double m_freq = A4 * ngrams4_1[n4_probe];

              double score0;
              if( selector2score.TryGetValue( m, out score0 ) )
               selector2score[m] = score0 + m_freq;
              else
               selector2score.Add( m, m_freq );

              foreach( KeyValuePair<int, double> p in pos2score )
              {
               if( m.MatchPartOfSpeech( p.Key ) )
               {
                changes.Add( new KeyValuePair<int, double>( p.Key, m_freq ) );
               }
              }

              if( !smooth )
               pos_score_order[iword] = 4;
             }
            }
           }
          }
       }



       if( iword >= 1 && iword < LAST_WORD_INDEX - 1 )
       {
        // Выбираем POS для iword на основе iword-1,iword+1,iword+2
        List<int> tags0 = word2tags[iword - 1];
        List<int> tags2 = word2tags[iword + 1];
        List<int> tags3 = word2tags[iword + 2];

        foreach( int tag0 in tags0 )
         foreach( int tag2 in tags2 )
          foreach( int tag3 in tags3 )
          {
           List<NGram4> n4_list;
           Int3 k = new Int3( tag0, tag2, tag3 );

           if( tag2_ngram4.TryGetValue( k, out n4_list ) )
           {
            // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1,tag3 и прибавляем очки соответствующим частям речи.
            foreach( NGram4 n4_probe in n4_list )
            {
             int tag1 = n4_probe.tags1;
             TagMatcher m = selectors[tag1];
             if( m.Match( proj, gren ) )
             {

              double m_freq = A4 * ngrams4_2[n4_probe];

              double score0;
              if( selector2score.TryGetValue( m, out score0 ) )
               selector2score[m] = score0 + m_freq;
              else
               selector2score.Add( m, m_freq );

              foreach( KeyValuePair<int, double> p in pos2score )
              {
               if( m.MatchPartOfSpeech( p.Key ) )
               {
                changes.Add( new KeyValuePair<int, double>( p.Key, m_freq ) );
               }
              }

              if( !smooth )
               pos_score_order[iword] = 4;
             }
            }
           }
          }
       }





       if( iword < LAST_WORD_INDEX - 2 )
       {
        // Выбираем POS для iword на основе iword+1,iword+2,iword+3
        List<int> tags1 = word2tags[iword + 1];
        List<int> tags2 = word2tags[iword + 2];
        List<int> tags3 = word2tags[iword + 3];

        foreach( int tag1 in tags1 )
         foreach( int tag2 in tags2 )
          foreach( int tag3 in tags3 )
          {
           List<NGram4> n4_list;
           Int3 k = new Int3( tag1, tag2, tag3 );

           if( tag3_ngram4.TryGetValue( k, out n4_list ) )
           {
            foreach( NGram4 n4_probe in n4_list )
            {
             int tag0 = n4_probe.tags0;
             TagMatcher m = selectors[tag0];
             if( m.Match( proj, gren ) )
             {

              double m_freq = A4 * ngrams4_3[n4_probe];

              double score0;
              if( selector2score.TryGetValue( m, out score0 ) )
               selector2score[m] = score0 + m_freq;
              else
               selector2score.Add( m, m_freq );

              foreach( KeyValuePair<int, double> p in pos2score )
              {
               if( m.MatchPartOfSpeech( p.Key ) )
               {
                changes.Add( new KeyValuePair<int, double>( p.Key, m_freq ) );
               }
              }

              if( !smooth )
               pos_score_order[iword] = 4;
             }
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
      // Выбираем варианты для слова в позиции iword
      if( word2tags[iword].Count > 1 && pos_score_order[iword] < 3 )
      {
       if( iword > 1 )
       {
        // 0,1 --> 2
        List<int> tags0 = word2tags[iword - 2];
        List<int> tags1 = word2tags[iword - 1];

        foreach( int tag0 in tags0 )
         foreach( int tag1 in tags1 )
         {
          List<NGram3> n3_list;
          Int2 k = new Int2( tag0, tag1 );

          if( tag0_ngram3.TryGetValue( k, out n3_list ) )
          {
           // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1, и прибавляем очки соответствующим частям речи.
           foreach( NGram3 n3_probe in n3_list )
           {
            int tag2 = n3_probe.tags2;
            TagMatcher m = selectors[tag2];
            if( m.Match( proj, gren ) )
            {

             double m_freq = A3 * ngrams3_0[n3_probe];

             double score0;
             if( selector2score.TryGetValue( m, out score0 ) )
              selector2score[m] = score0 + m_freq;
             else
              selector2score.Add( m, m_freq );

             foreach( KeyValuePair<int, double> p in pos2score )
             {
              if( m.MatchPartOfSpeech( p.Key ) )
              {
               changes.Add( new KeyValuePair<int, double>( p.Key, m_freq ) );
              }
             }

             if( !smooth )
              pos_score_order[iword] = 3;
            }
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

          if( tag1_ngram3.TryGetValue( k, out n3_list ) )
          {
           // Перебираем варианты, которые вытекают из наличия тегов tag0,tag1, и прибавляем очки соответствующим частям речи.
           foreach( NGram3 n3_probe in n3_list )
           {
            int tag1 = n3_probe.tags1;
            TagMatcher m = selectors[tag1];
            if( m.Match( proj, gren ) )
            {

             double m_freq = A3 * ngrams3_1[n3_probe];

             double score0;
             if( selector2score.TryGetValue( m, out score0 ) )
              selector2score[m] = score0 + m_freq;
             else
              selector2score.Add( m, m_freq );

             foreach( KeyValuePair<int, double> p in pos2score )
             {
              if( m.MatchPartOfSpeech( p.Key ) )
              {
               changes.Add( new KeyValuePair<int, double>( p.Key, m_freq ) );
              }
             }

             if( !smooth )
              pos_score_order[iword] = 3;
            }
           }
          }
         }
       }


       if( iword < LAST_WORD_INDEX - 1 )
       {
        // 0 <-- 1,2

        List<int> tags1 = word2tags[iword + 1];
        List<int> tags2 = word2tags[iword + 2];

        foreach( int tag1 in tags1 )
         foreach( int tag2 in tags2 )
         {
          List<NGram3> n3_list;
          Int2 k = new Int2( tag1, tag2 );

          if( tag2_ngram3.TryGetValue( k, out n3_list ) )
          {
           // Перебираем варианты, которые вытекают из наличия тегов tag1,tag2, и прибавляем очки соответствующим частям речи.
           foreach( NGram3 n3_probe in n3_list )
           {
            int tag0 = n3_probe.tags0;
            TagMatcher m = selectors[tag0];
            if( m.Match( proj, gren ) )
            {

             double m_freq = A3 * ngrams3_2[n3_probe];

             double score0;
             if( selector2score.TryGetValue( m, out score0 ) )
              selector2score[m] = score0 + m_freq;
             else
              selector2score.Add( m, m_freq );

             foreach( KeyValuePair<int, double> p in pos2score )
             {
              if( m.MatchPartOfSpeech( p.Key ) )
              {
               changes.Add( new KeyValuePair<int, double>( p.Key, m_freq ) );
              }
             }

             if( !smooth )
              pos_score_order[iword] = 3;
            }
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
      if( word2tags[iword].Count > 1 && pos_score_order[iword] < 2 ) // Выбираем POS для iword
      {
       if( iword >= 1 )
       {
        // 0 --> 1
        List<int> tags0 = word2tags[iword - 1];

        foreach( int tag0 in tags0 )
        {
         List<NGram2> n2_list;
         if( tag0_ngram2.TryGetValue( tag0, out n2_list ) )
         {
          // Перебираем варианты, которые вытекают из наличия тега tag0, и прибавляем очки соответствующим частям речи.
          foreach( NGram2 n2_probe in n2_list )
          {
           int tag1 = n2_probe.tags1;
           TagMatcher m = selectors[tag1];

           // Такой вариант распознавания вообще возможен для слова?
           if( m.Match( proj, gren ) )
           {
            double m_freq = A2 * ngrams2_0[n2_probe];

            double score0;
            if( selector2score.TryGetValue( m, out score0 ) )
             selector2score[m] = score0 + m_freq;
            else
             selector2score.Add( m, m_freq );

            foreach( KeyValuePair<int, double> p in pos2score )
            {
             if( m.MatchPartOfSpeech( p.Key ) )
             {
              changes.Add( new KeyValuePair<int, double>( p.Key, m_freq ) );
             }
            }

            if( !smooth )
             pos_score_order[iword] = 2;
           }
          }
         }
        }
       }

       if( iword < LAST_WORD_INDEX )
       {
        // 0 <-- 1
        List<int> tags1 = word2tags[iword + 1];

        foreach( int tag1 in tags1 )
        {
         List<NGram2> n2_list;
         if( tag1_ngram2.TryGetValue( tag1, out n2_list ) )
         {
          // Перебираем варианты, которые вытекают из наличия тега tag1, и прибавляем очки соответствующим частям речи.
          foreach( NGram2 n2_probe in n2_list )
          {
           int tag0 = n2_probe.tags0;
           TagMatcher m = selectors[tag0];

           // Такой вариант распознавания вообще возможен для слова?
           if( m.Match( proj, gren ) )
           {
            double m_freq = A2 * ngrams2_1[n2_probe];

            double score0;
            if( selector2score.TryGetValue( m, out score0 ) )
             selector2score[m] = score0 + m_freq;
            else
             selector2score.Add( m, m_freq );

            foreach( KeyValuePair<int, double> p in pos2score )
            {
             if( m.MatchPartOfSpeech( p.Key ) )
             {
              changes.Add( new KeyValuePair<int, double>( p.Key, m_freq ) );
             }
            }

            if( !smooth )
             pos_score_order[iword] = 2;
           }
          }
         }
        }
       }
      }
     }

     foreach( var kv in changes )
      pos2score[kv.Key] = pos2score[kv.Key] + kv.Value;

     TagMatcher best_selector = null;
     double best_selector_score = 0;
     foreach( var x in selector2score )
      if( x.Value > best_selector_score )
      {
       best_selector_score = x.Value;
       best_selector = x.Key;
      }

     // word2selector
     word2selector[iword] = best_selector;
    }

    // Все вероятности перехода для каждого слова учтены.

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

     // Для слова iword выбрана часть речи best_pos. Это согласуется с эталоном?

     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[iword];

     bool can_be_verb = false;
     bool pos_matched = false;
     for( int k = 0; k < token.VersionCount(); ++k )
     {
      int ekey1 = token.GetVersionEntryID( k );
      int id_class1 = gren.GetEntryClass( ekey1 );
      if( best_pos == id_class1 )
      {
       pos_matched = true;
      }

      can_be_verb = can_be_verb || VerbPOS.IsVerb( id_class1 );
     }

     if( !pos_matched )
      POS_error_count++;

     if(
        ( VerbPOS.IsVerb( best_pos ) && !can_be_verb ) ||
        ( !VerbPOS.IsVerb( best_pos ) && can_be_verb )
       )
      VERB_error_count++;

     // Проверим рспознавание целого набора признаков
     TagMatcher selector = word2selector[iword];

     if( selector != null )
     {
      bool selector_matches = false;

      selector_matches = selector.Match( token, gren );

      if( !selector_matches )
       FEATURESET_error_count++;
     }
    }
   }
  }

  return;
 }





 public void DumpRules( string filepath )
 {
  using( System.IO.StreamWriter dest = new System.IO.StreamWriter( filepath, false, new UTF8Encoding( true ) ) )
  {
   // --------------
   // 2-ГРАММЫ
   // --------------

   dest.WriteLine( "// {0} 2-grams:", ngrams2_0.Count );

   List<KeyValuePair<NGram2, int>> n2f = new List<KeyValuePair<NGram2, int>>( ngrams2_0.Select( z => z ) );
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

   dest.WriteLine( "\n\n// {0} 3-grams:", ngrams3_0.Count );

   List<KeyValuePair<NGram3, int>> n3f = new List<KeyValuePair<NGram3, int>>( ngrams3_0.Select( z => z ) );
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

   dest.WriteLine( "\n\n// {0} 4-grams:", ngrams4_0.Count );

   List<KeyValuePair<NGram4, int>> n4f = new List<KeyValuePair<NGram4, int>>( ngrams4_0.Select( z => z ) );
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
  }

  return;
 }
}
