using System;
using System.Collections.Generic;
using SVM;


class SVM_X_Picker
{
 private TagMatcher tag;
 private int x_index;

 public SVM_X_Picker( string line, SolarixGrammarEngineNET.GrammarEngine2 gren, int _x_index )
 {
  x_index = _x_index;
  tag = new TagMatcher( line, gren );
  return;
 }

 public int GetIndex() { return x_index; }

 public bool Match( SolarixGrammarEngineNET.SyntaxTreeNode token, SolarixGrammarEngineNET.GrammarEngine2 gren )
 { return tag.Match( token, gren ); }
}


// Группа паттернов для одного Y-ка по принципу - дает или не дает Y данный набор X'ов
class SVM_ResultPatterns
{
 public List<SVM.Node[]> _X;
 public List<double> _Y; // 1 или 0

 public SVM_ResultPatterns()
 {
  _X = new List<Node[]>();
  _Y = new List<double>();
 }

 public void Add( SVM.Node[] x, double y )
 {
  _X.Add( x );
  _Y.Add( y );
 }

 public void Write( System.IO.StreamWriter wrt )
 {
  for( int i = 0; i < _X.Count; ++i )
  {
   if( _Y[i] == 1 )
    wrt.Write( "+1" );
   else
    wrt.Write( "-1" );

   for( int j = 0; j < _X[i].Length; ++j )
    wrt.Write( " {0}:{1}", _X[i][j].Index, _X[i][j].Value.ToString( new System.Globalization.CultureInfo( "en-US" ) ) );

   wrt.WriteLine( "" );
  }

  wrt.Flush();
  return;
 }


 public void Clear()
 {
  _X.Clear();
  _Y.Clear();
 }
}





class Builder_SVM
{
 int context_span;
 int x_len; // полная длина вектора признаков


 // --------------------------
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

 private HashSet<string> undevidable_words = new HashSet<string>();
 // --------------------------

 int suffix_len;

 List<SVM_X_Picker> y_picker;
 List<SVM_ResultPatterns> y_patterns;


 public Builder_SVM() { }

 String2Vector suffix2vector;

 public void Init()
 {
  // -------------------------------------------

  suffix2vector = new String2Vector( System.IO.Path.Combine( Program.WORD_FEATURES, "suffices.txt" ) );

  context_span = Program.CONTEXT_SPAN; // число токенов, которые используются для генерации вектора X
  x_len = ( context_span * 2 + 1 ) * suffix2vector.GetVectorLength(); // размерность пространства признаков


  // -------------------------------------------

  suffix_len = Program.SUFFIX_LEN;

  // Распознаваемые признаки

  string y_str =
  @"
СУЩЕСТВИТЕЛЬНОЕ
ПРИЛАГАТЕЛЬНОЕ
МЕСТОИМЕНИЕ
МЕСТОИМ_СУЩ
ЧИСЛИТЕЛЬНОЕ
ГЛАГОЛ
ВВОДНОЕ
БЕЗЛИЧ_ГЛАГОЛ
NUM_WORD
ИНФИНИТИВ
ДЕЕПРИЧАСТИЕ
ПРЕДЛОГ
ПОСЛЕЛОГ
СОЮЗ
ЧАСТИЦА
ПУНКТУАТОР
НАРЕЧИЕ
UNKNOWNENTRIES
ПРИТЯЖ_ЧАСТИЦА
";

  y_picker = new List<SVM_X_Picker>();
  y_patterns = new List<SVM_ResultPatterns>();

  int y_index = 0;
  foreach( string line in y_str.Split( '\n' ) )
  {
   string l = line.Trim();
   if( !string.IsNullOrEmpty( l ) )
   {
    SVM_X_Picker m = new SVM_X_Picker( line, gren, y_index++ );
    y_picker.Add( m );

    SVM_ResultPatterns p = new SVM_ResultPatterns();
    y_patterns.Add( p );
   }
  }

  return;
 }




 private SolarixGrammarEngineNET.GrammarEngine2 gren;
 public void LoadDictionary( string filepath )
 {
  gren = new SolarixGrammarEngineNET.GrammarEngine2();
  gren.Load( filepath, false );
  Init();
  return;
 }

 public SolarixGrammarEngineNET.GrammarEngine2 GetGrammarEngine() { return gren; }

 int LanguageID = -1;
 public void SetLanguage( int id ) { LanguageID = id; }

 private bool ConvertToken2X( SolarixGrammarEngineNET.SyntaxTreeNode token, int token_index, SVM.Node[] X )
 {
  int start = token_index * suffix2vector.GetVectorLength();

  /*
    string lemma = gren.GetEntryName( token.GetEntryID() );
    if( lemma == "???" || lemma == "UNKNOWNENTRY" || lemma == "NUMBER_" )
     lemma = token.GetWord();

    double[] v = lemma2vector.GetVector( lemma.ToLower() );
  */

  if( token == null )
  {
   for( int i = 0; i < suffix2vector.GetVectorLength(); ++i )
    X[start + i] = new SVM.Node( start + i + 1, 0.0 );
  }
  else
  {
   string word = token.GetWord();
   string suffix = word;

   int res;
   if( !int.TryParse( word, out res ) && word.Length > suffix_len + 1 )
   {
    suffix = "~" + word.Substring( word.Length - suffix_len );
   }

   double[] v = suffix2vector.GetVector( suffix.ToLower() );

   for( int i = 0; i < v.Length; ++i )
    X[start + i] = new SVM.Node( start + i + 1, v[i] );
  }

  return true;
 }


 List<System.IO.StreamWriter> wrt_train;
 List<string> train_filename;

 public bool ProcessSample( SampleData sample )
 {
  Sample2Patterns( sample, y_patterns );

  if( wrt_train == null )
  {
   wrt_train = new List<System.IO.StreamWriter>();
   train_filename = new List<string>();

   /* 
      // для SVM
      for( int i = 0; i < y_picker.Count; ++i )
      {
       string train_path = string.Format( "svm_train_{0}.txt", i );
       train_filename.Add( train_path );
       wrt_train.Add( new System.IO.StreamWriter( train_path ) );
      }*/

   string train_path = "maxent_train.txt";
   train_filename.Add( train_path );
   wrt_train.Add( new System.IO.StreamWriter( train_path ) );
  }

  /*
    for( int i = 0; i < y_picker.Count; ++i )
    {
     y_patterns[i].Write( wrt_train[i] );
     y_patterns[i].Clear();
    }
   */

  for( int y = 0; y < y_picker.Count; ++y )
  {
   SVM_ResultPatterns patterns = y_patterns[y];

   for( int i = 0; i < patterns._X.Count; ++i )
   {
    if( patterns._Y[i] == 1.0 )
    {
     wrt_train[0].Write( "{0} ", y );

     for( int j = 0; j < patterns._X[i].Length; ++j )
      wrt_train[0].Write( " {0}:{1}", patterns._X[i][j].Index, (2.0+patterns._X[i][j].Value).ToString( new System.Globalization.CultureInfo( "en-US" ) ) );

     wrt_train[0].WriteLine( "" );
    }
   }

   wrt_train[0].Flush();

   patterns.Clear();
  }

  return true;
 }


 public bool Sample2Patterns( SampleData sample, List<SVM_ResultPatterns> patterns )
 {
  // Морфологический разбор
  // Для каждого слова, кроме первого и последнего токенов...

  for( int word_index = 1; word_index < sample.morphology.Count - 1; ++word_index )
  {
   // Собираем контекст для слова
   SVM.Node[] Xi = new SVM.Node[x_len];
   for( int k = 0; k < x_len; ++k )
    Xi[k] = new SVM.Node( k + 1, 0.0 );

   int idx = 0;
   for( int ctx_index = word_index - context_span; ctx_index <= word_index + context_span; ++ctx_index, ++idx )
   {
    if( ctx_index >= 1 && ctx_index < sample.morphology.Count - 1 )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode token = sample.morphology[ctx_index];
     ConvertToken2X( token, idx, Xi );
    }
    else
    {
     ConvertToken2X( null, idx, Xi );
    }
   }

   SolarixGrammarEngineNET.SyntaxTreeNode token0 = sample.morphology[word_index];
   string word = token0.GetWord().ToLower();

   // Решение
   foreach( SVM_X_Picker y in y_picker )
    if( y.Match( token0, gren ) )
    {
     int y_index = y.GetIndex();

     patterns[y_index].Add( Xi, 1.0 );

     // для остальных Y'ов добавим этот же паттерн как "не-Yi"
     for( int j = 0; j < y_picker.Count; ++j )
      if( j != y_index )
       patterns[j].Add( Xi, 0.0 );

     break;
    }
  }

  return true;
 }



 List<Problem> problems;
 List<RangeTransform> ranges;
 List<Parameter> paramx;
 List<Model> models;

 public void FinishLearning()
 {
  /*
    problems = new List<Problem>();
    ranges = new List<RangeTransform>();
    paramx = new List<Parameter>();
    models = new List<Model>();

    for( int i = 0; i < y_patterns.Count; ++i )
    {
     Console.WriteLine( "Training machine #{0}...", i );
     Problem problem = new Problem( y_patterns[i]._X.Count, y_patterns[i]._Y.ToArray(), y_patterns[i]._X.ToArray(), x_len );
     RangeTransform range = RangeTransform.Compute( problem );
     problem = range.Scale( problem );

     Parameter param = new Parameter();
     param.C = 2;
     param.Gamma = .5;

     Model model = Training.Train( problem, param );

     //problems.Add( problem );
     ranges.Add( range );
     //paramx.Add( param );
     models.Add( model );
    }
  */


  for( int i = 0; i < wrt_train.Count; ++i )
  {
   wrt_train[i].Close();
  }


  /*
    for( int i = 0; i < wrt_train.Count; ++i )
    {
     Console.WriteLine( "Start training SVM light ..." );
     string input_file = string.Format( "\"{0}\\{1}\"", System.IO.Directory.GetCurrentDirectory(), train_filename[i] );
     string model_file = string.Format( "\"{0}\\machine_{1}.dat\"", System.IO.Directory.GetCurrentDirectory(), i );
     string cmd = string.Format( "{0}\\svm_learn.exe", System.IO.Directory.GetCurrentDirectory() );

     System.Diagnostics.Process p = new System.Diagnostics.Process();
     p.StartInfo.Arguments = string.Format( "{0} {1}", input_file, model_file );
     p.StartInfo.FileName = cmd;

     Console.WriteLine( "Training machine #{0}", i );

     bool r = p.Start();
     p.WaitForExit();
    }
  */


  Console.WriteLine( "Start training MaxEnt ..." );
  string input_file = string.Format( "\"{0}\\{1}\"", System.IO.Directory.GetCurrentDirectory(), train_filename[0] );
  string model_file = string.Format( "\"{0}\\maxent.dat\"", System.IO.Directory.GetCurrentDirectory() );
  string cmd = string.Format( "{0}\\maxent_train.cmd", System.IO.Directory.GetCurrentDirectory() );

  System.Diagnostics.Process p = new System.Diagnostics.Process();
  p.StartInfo.Arguments = string.Format( "{0} {1}", input_file, model_file );
  p.StartInfo.FileName = cmd;

  bool r = p.Start();
  p.WaitForExit();

  Console.WriteLine( "Training complete." );

  return;
 }

 List<SVM_ResultPatterns> test_patterns;

 public void Check( SampleData sample )
 {
  if( test_patterns == null )
  {
   test_patterns = new List<SVM_ResultPatterns>();
   for( int i = 0; i < y_picker.Count; ++i )
    test_patterns.Add( new SVM_ResultPatterns() );
  }

  Sample2Patterns( sample, test_patterns );

  return;
 }




 public void FinishTesting()
 {
  /*
    int n_prediction = test_patterns[0]._X.Count;
    int n_word = n_prediction;

    int n_err = 0;

    Console.WriteLine( "Testing..." );

    for( int i = 0; i < n_prediction; ++i )
    {
     int has_err = 0;

     for( int j = 0; j < test_patterns.Count; ++j )
     {
      SVM_ResultPatterns y_pattern = test_patterns[j];

      // Получаем предсказание по обученной модели SVM

      SVM.Node[] Xi = ranges[j].Transform( y_pattern._X[i] );
      double Y_predict = Prediction.Predict( models[j], Xi );

      // Сравниваем с правильным ответом
      if( Math.Abs( Y_predict - y_pattern._Y[i] ) > 0.5 )
       has_err++;
     }

     if( has_err > 0 )
      n_err++;

     if( ( i % 100 ) == 0 )
      Console.WriteLine( "{0} of {1} tested", i, n_prediction );
    }

    Console.WriteLine( "FEATURE_SET recognition error count={0}, i.e. {1}%", n_err, PercentFormatter.Percent( n_err, n_word ) );
  */

  return;
 }

}


