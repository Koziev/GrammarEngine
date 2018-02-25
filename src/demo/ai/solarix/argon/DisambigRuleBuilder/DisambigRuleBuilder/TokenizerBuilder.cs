using System;
using System.Collections.Generic;
using System.Linq;


class TokenizerTokenFeatures
{
 public string org_word; // в оригинальном виде
 public string word; // в нижнем регистре
 public string crf_word; // с заменой пробелов на _
 public List<string> tags = new List<string>();
 public string output_tag; // такой тэг должен выбрать обученная модель

 public bool IsBegin, IsEnd; // флажки для граничных токенов

 public override string ToString()
 {
  return string.Format( "{0} => {1}", org_word, output_tag );
 }
}


class TokenizerBuilder
{
 private int CONTEXT_SPAN = -1; // +/- столько слов слева и справа
 private int SUFFIX_LEN = -1;

 System.IO.StreamWriter crf_file_train, crf_file_test;
 System.IO.StreamWriter test_samples_file;

 int n_learn_samples = 0;
 int n_train_patterns = 0; // чисто тренировочных паттернов - в одном исходном предложении будет много паттернов, обычно столько, сколько слов.

 bool IsUnknownLexem( string s )
 {
  return s.Equals( "UNKNOWNENTRY", System.StringComparison.InvariantCultureIgnoreCase ) ||
         s == "???" ||
         s.Equals( "number_", System.StringComparison.InvariantCultureIgnoreCase );
 }

 public TokenizerBuilder()
 {
 }


 public void ChangeModelParams( List<string> model_params )
 {
  foreach( string p in model_params.Where( z => !string.IsNullOrEmpty( z ) ) )
  {
   string[] tx = p.Split( '=' );
   string pname = tx[0].Trim();
   string pval = tx[1].Trim();

   switch( pname.ToUpper() )
   {
    default: throw new ApplicationException( string.Format( "Unknown model param {0}={1}", pname, pval ) );
   }
  }
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

 HashSet<string> wordforms = new HashSet<string>();
 HashSet<string> SWU = new HashSet<string>(); // слова, содержащие ровно 1 токен
 Dictionary<int, HashSet<string>> BEGIN_MWU = new Dictionary<int, HashSet<string>>();
 Dictionary<int, HashSet<string>> INNER_MWU = new Dictionary<int, HashSet<string>>();
 Dictionary<int, HashSet<string>> END_MWU = new Dictionary<int, HashSet<string>>();
 HashSet<string> MWU_PART = new HashSet<string>(); // итоговый список токенов, которые входят в MWU

 private void RegisterWordform( string word )
 {
  if( !wordforms.Contains( word ) )
  {
   wordforms.Add( word );

   if( word.Length > 1 && word.IndexOfAny( " -,.".ToCharArray() ) != -1 )
   {
    string[] tokens = word.Replace( "-", " - " ).Replace( ",", " , " ).Replace( ".", " . " ).Split( " ".ToCharArray(), StringSplitOptions.RemoveEmptyEntries );

    for( int i = 0; i < tokens.Length; ++i )
    {
     Dictionary<int, HashSet<string>> lx;
     if( i == 0 )
      lx = BEGIN_MWU;
     else if( i == tokens.Length - 1 )
      // последний токен
      lx = END_MWU;
     else
      // внутренние токены
      lx = INNER_MWU;

     HashSet<string> wx;
     if( !lx.TryGetValue( tokens.Length, out wx ) )
     {
      wx = new HashSet<string>();
      lx.Add( tokens.Length, wx );
     }

     wx.Add( tokens[i] );

     MWU_PART.Add( tokens[i].ToUpper() );
    }
   }
  }

  return;
 }

 public void Init()
 {
  CONTEXT_SPAN = Math.Max( 2, Program.CONTEXT_SPAN );
  SUFFIX_LEN = Math.Max( 2, Program.SUFFIX_LEN );

  // Подготовим признаки токенов.

  IntPtr hEntries = SolarixGrammarEngineNET.GrammarEngine.sol_ListEntries( gren.GetEngineHandle(), 0, 0, "", SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE, -1 );
  int nEntry = SolarixGrammarEngineNET.GrammarEngine.sol_CountInts( hEntries );

  for( int i = 0; i < nEntry; ++i )
  {
   int id_entry = SolarixGrammarEngineNET.GrammarEngine.sol_GetInt( hEntries, i );

//   if( id_entry == 1073742245 )
//    Console.WriteLine( "i={0}", i );

   IntPtr hForms = SolarixGrammarEngineNET.GrammarEngine.sol_ListEntryForms( gren.GetEngineHandle(), id_entry );
   int nForm = SolarixGrammarEngineNET.GrammarEngine.sol_CountStrings( hForms );
   for( int j = 0; j < nForm; ++j )
   {
    string form = SolarixGrammarEngineNET.GrammarEngine.sol_GetStringFX( hForms, j );
    RegisterWordform( form.ToUpper() );
   }

   SolarixGrammarEngineNET.GrammarEngine.sol_DeleteStrings( hForms );
  }


  SolarixGrammarEngineNET.GrammarEngine.sol_DeleteInts( hEntries );

  return;
 }


 public bool ProcessSample( SampleData sample )
 {
  n_learn_samples++;

  if( crf_file_train == null )
  {
   crf_file_train = new System.IO.StreamWriter( "crf_train.txt" );
  }

  Sentence2Features( crf_file_train, sample );

  return true;
 }

 int Constraints = 60000 | ( 50 << 22 ); // 1 минута и 50 альтернатив

 private bool Sentence2Features( System.IO.StreamWriter crf_file, SampleData sample )
 {
  // Морфологический разбор

  if( sample.morphology.IsNull() )
   sample.morphology = gren.AnalyzeMorphology( sample.sample, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY, Constraints );

  if( sample.tokenization.IsNull() )
   sample.tokenization = gren.AnalyzeMorphology( sample.sample, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_TOKENIZE_ONLY, 0 );

  //  if( sample.syntax_tree.IsNull() )
  //   sample.syntax_tree = gren.AnalyzeSyntax( sample.sample, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY, 0, Constraints );

  if( sample.morphology.Count != sample.tokenization.Count )
  {
   return false;
  }

  // ----------------------------------------------
  // Готовим наборы признаков для каждого токена
  // ----------------------------------------------

  List<TokenizerTokenFeatures> token_features = new List<TokenizerTokenFeatures>();

  token_features.AddRange( GetFeatures( 0, sample.morphology.Count, sample.morphology[0], sample.tokenization[0] ) );

  for( int iword = 1; iword < sample.morphology.Count - 1; ++iword )
  {
   List<TokenizerTokenFeatures> f = GetFeatures( iword, sample.morphology.Count, sample.morphology[iword], sample.tokenization[iword] );
   token_features.AddRange( f );
  }

  token_features.AddRange( GetFeatures( sample.morphology.Count - 1, sample.morphology.Count, sample.morphology[sample.morphology.Count - 1], sample.tokenization[sample.morphology.Count - 1] ) );

  System.Text.StringBuilder b = new System.Text.StringBuilder();

  for( int iword = 0; iword < token_features.Count; ++iword )
  {
   b.Length = 0;

   TokenizerTokenFeatures f_this = token_features[iword];

   PullFeatures1( b, token_features, iword, 0 );

   // и соседние слова
   if( CONTEXT_SPAN > 4 )
    PullFeatures1( b, token_features, iword, -5 );

   if( CONTEXT_SPAN > 3 )
    PullFeatures1( b, token_features, iword, -4 );

   if( CONTEXT_SPAN > 2 )
    PullFeatures1( b, token_features, iword, -3 );

   if( CONTEXT_SPAN > 1 )
    PullFeatures1( b, token_features, iword, -2 );

   PullFeatures1( b, token_features, iword, -1 );
   PullFeatures1( b, token_features, iword, 1 );

   if( CONTEXT_SPAN > 1 )
    PullFeatures1( b, token_features, iword, 2 );

   if( CONTEXT_SPAN > 2 )
    PullFeatures1( b, token_features, iword, 3 );

   if( CONTEXT_SPAN > 3 )
    PullFeatures1( b, token_features, iword, 4 );

   if( CONTEXT_SPAN > 4 )
    PullFeatures1( b, token_features, iword, 5 );

   crf_file.Write( "{0}", f_this.output_tag );

   crf_file.WriteLine( "{0}", b.ToString() );
   n_train_patterns++;
  }


  crf_file.WriteLine( "" ); // пустые строки отделяют предложения
  crf_file.Flush();

  return true;
 }



 string GetSuffix( string uppercase_word )
 {
  if( uppercase_word.Length < SUFFIX_LEN )
   return uppercase_word;
  else if( MWU_PART.Contains( uppercase_word ) )
   return uppercase_word;
  else
   return "~" + uppercase_word.Substring( uppercase_word.Length - SUFFIX_LEN, SUFFIX_LEN );
 }


 List<TokenizerTokenFeatures> GetFeatures(
                                          int token_index,
                                          int token_count,
                                          SolarixGrammarEngineNET.SyntaxTreeNode token,
                                          SolarixGrammarEngineNET.SyntaxTreeNode all_projs
                                         )
 {
  List<TokenizerTokenFeatures> fx = new List<TokenizerTokenFeatures>();

  if( token_index == 0 )
  {
   TokenizerTokenFeatures f = new TokenizerTokenFeatures();
   f.IsBegin = true;
   f.tags.Add( "<START>" );
   f.crf_word = f.org_word = f.word = "<START>";
   f.output_tag = "B";
   fx.Add( f );
  }
  else if( token_index == token_count - 1 )
  {
   TokenizerTokenFeatures f = new TokenizerTokenFeatures();
   f.IsEnd = true;
   f.tags.Add( "<END>" );
   f.crf_word = f.org_word = f.word = "<END>";
   f.output_tag = "B";
   fx.Add( f );
  }
  else
  {
   string original_word = token.GetWord().ToUpper();

   int lexem_counter = 0;

   string[] tx = original_word.Replace( "-", " - " ).Replace( ",", " , " ).Replace( ".", " . " )
                               .Split( " ".ToCharArray(), StringSplitOptions.RemoveEmptyEntries );


   foreach( string t in tx )
   {
    string t2 = t.Trim();
    if( t2.Length != 0 )
    {
     TokenizerTokenFeatures f = new TokenizerTokenFeatures();
     f.org_word = t2;
     f.word = t2.ToUpper();

     f.tags.Add( string.Format( "suffix={0}", GetSuffix( f.word ) ) );

     foreach( var p in BEGIN_MWU )
     {
      if( p.Value.Contains( t ) )
      {
       f.tags.Add( string.Format( "begin_mwu_{0}", p.Key ) );
      }
     }

     foreach( var p in INNER_MWU )
     {
      if( p.Value.Contains( t ) )
      {
       f.tags.Add( string.Format( "inner_mwu_{0}", p.Key ) );
      }
     }

     foreach( var p in END_MWU )
     {
      if( p.Value.Contains( t ) )
      {
       f.tags.Add( string.Format( "end_mwu_{0}", p.Key ) );
      }
     }

     f.crf_word = f.word.Replace( " ", "_" );

     if( lexem_counter == 0 )
      f.output_tag = "B";
     else
      f.output_tag = "C";

     fx.Add( f );
     lexem_counter++;
    }
   }
  }

  return fx;
 }

 string FieldDelimiter() { return "\t"; }



 void PullFeatures1( System.Text.StringBuilder b, List<TokenizerTokenFeatures> token_features, int ifocus, int offset )
 {
  int iword = ifocus + offset;

  if( iword >= 0 && iword < token_features.Count )
  {
   TokenizerTokenFeatures f = token_features[iword];

   foreach( string tag in f.tags )
    b.AppendFormat( "{0}[{1}]{2}", FieldDelimiter(), offset, tag );
  }

  return;
 }



 public void FinishLearning()
 {
  StoreCodeBook();

  Console.WriteLine( "CONTEXT_SPAN=+/-{0}", CONTEXT_SPAN );
  Console.WriteLine( "Number of training patterns={0}", n_train_patterns );

  if( test_samples_file != null )
  {
   test_samples_file.Close();
   test_samples_file = null;
  }


  if( crf_file_train != null )
  {
   crf_file_train.Close();
   crf_file_train = null;
  }

  string input_file = null;
  string cmd = null;

  Console.WriteLine( "Start training CRFSuite..." );
  input_file = string.Format( "{0}\\crf_train.txt", System.IO.Directory.GetCurrentDirectory() );
  cmd = string.Format( "{0}\\crfsuite_tokenizer_train.cmd", System.IO.Directory.GetCurrentDirectory() );

  System.Diagnostics.Process p = new System.Diagnostics.Process();
  p.StartInfo.Arguments = input_file;
  p.StartInfo.FileName = cmd;

  Console.WriteLine( "Executing {0} {1}", p.StartInfo.FileName, p.StartInfo.Arguments );

  bool r = p.Start();
  p.WaitForExit();

  return;
 }


 bool IsAa( string s )
 {
  if( s.Length < 2 )
   return false;

  if( !char.IsUpper( s[0] ) )
   return false;

  for( int i = 1; i < s.Length; ++i )
   if( char.IsUpper( s[i] ) )
    return false;

  return true;
 }


 List<string> test_samples = new List<string>();

 public void Check( SampleData sample )
 {
  if( test_samples_file == null )
  {
   test_samples_file = new System.IO.StreamWriter( "test_samples.txt" );
  }

  test_samples_file.WriteLine( "{0}", sample.sample );


  if( crf_file_test == null )
  {
   crf_file_test = new System.IO.StreamWriter( "crf_test.txt" );
  }

  bool b = Sentence2Features( crf_file_test, sample );

  if( b )
   test_samples.Add( sample.sample );

  return;
 }


 private void FinishTesting(
                            out int total_word_count,
                            out int total_etalon_C,
                            out int error_count,
                            out int B_instead_of_C_count,
                            out int C_instead_of_B_count
                           )
 {
  total_word_count = 0;
  error_count = 0;
  total_etalon_C = 0;
  B_instead_of_C_count = 0;
  C_instead_of_B_count = 0;

  if( crf_file_test != null )
   crf_file_test.Close();
  crf_file_test = null;

  string input_file = null;
  string output_file = null;
  string cmd = null;

  string error_file = string.Format( "{0}\\crf_errors.txt", System.IO.Directory.GetCurrentDirectory() );

  Console.WriteLine( "Start testing CRFSuite" );

  input_file = string.Format( "{0}\\crf_test.txt", System.IO.Directory.GetCurrentDirectory() );
  output_file = string.Format( "{0}\\test_result.txt", System.IO.Directory.GetCurrentDirectory() );
  cmd = string.Format( "{0}\\crfsuite_tokenizer_test.cmd", System.IO.Directory.GetCurrentDirectory() );

  System.Diagnostics.Process p = new System.Diagnostics.Process();
  p.StartInfo.Arguments = string.Format( "\"{0}\" \"{1}\"", input_file, output_file );
  p.StartInfo.FileName = cmd;

  Console.WriteLine( "Executing {0} {1}", p.StartInfo.FileName, p.StartInfo.Arguments );

  bool r = p.Start();
  p.WaitForExit();

  using( System.IO.StreamWriter w_err = new System.IO.StreamWriter( error_file ) )
  {
   System.IO.StreamReader rdr = new System.IO.StreamReader( output_file );

   int sent_count = 0;
   int token_count = 0;

   string sample = string.Empty;
   List<int> coord_diff_list = new List<int>();

   int line_count = 1;

   while( !rdr.EndOfStream && sent_count < test_samples.Count )
   {
    if( token_count == 0 )
    {
     sample = test_samples[sent_count];
     System.Console.WriteLine( "2.{0} {1}", sent_count, sample );
    }

    string line = rdr.ReadLine();
    line_count++;

    if( line == null )
     break;

    if( line.Length == 0 )
    {
     sent_count++;
     token_count = 0;
     continue;
    }

    token_count++;
    total_word_count++;

    string[] toks = line.Split( '\t' );
    string required_tag = toks[0];
    string model_tag = toks[1];

    if( required_tag == "C" )
     total_etalon_C++;

    if( required_tag != model_tag )
    {
     if( required_tag == "C" && model_tag == "B" )
      B_instead_of_C_count++;
     else if( required_tag == "B" && model_tag == "C" )
      C_instead_of_B_count++;

     if( required_tag == "-1" || model_tag == "-1" || required_tag == "(null)" || model_tag == "(null)" )
     {
      // error_count_with_model_full_featureset++; TODO: вынести в отдельный счетчик

      w_err.WriteLine( "\nSample: {0}", sample );
      w_err.WriteLine( "Expected tag id: {0}", required_tag );
      w_err.WriteLine( "Yield token: {0}", model_tag );
     }
     else
     {
      error_count++;
     }
    }
   }
  }

  return;
 }

 private static void WriteStr( string str, System.IO.BinaryWriter wrt )
 {
  byte[] w8 = System.Text.Encoding.UTF8.GetBytes( str );
  wrt.Write( w8.Length );
  wrt.Write( w8 );
  return;
 }

 public void StoreModel() { }

 private void StoreCodeBook()
 {
  string path = "tokenizer.codebook";

  Console.WriteLine( "Storing the codebook to [{0}]...", path );

  if( System.IO.File.Exists( path ) )
   System.IO.File.Delete( path );

  using( System.IO.BinaryWriter wr = new System.IO.BinaryWriter( System.IO.File.OpenWrite( path ) ) )
  {
   wr.Write( 0 );
   wr.Write( CONTEXT_SPAN );

   /*
      // добавим справочник прочих параметров модели
      List<KeyValuePair<string, string>> model_params = new List<KeyValuePair<string, string>>();
      model_params.Add( new KeyValuePair<string, string>( "RICH_INPUT_TAGSET", RICH_INPUT_TAGSET.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_POS_TAGS", EMIT_POS_TAGS.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_MORPH_TAGS", EMIT_MORPH_TAGS.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_FORM_TAGS", EMIT_FORM_TAGS.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_NORMAL_FORMS", EMIT_NORMAL_FORMS.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_SEMANTIC_TAGS", EMIT_SEMANTIC_TAGS.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_POS_FOR_CONTEXT", EMIT_POS_FOR_CONTEXT.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_MORPH_FOR_CONTEXT", EMIT_MORPH_FOR_CONTEXT.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_FORMTAGS_FOR_CONTEXT", EMIT_FORMTAGS_FOR_CONTEXT.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_AA_FEATURE", EMIT_AA_FEATURE.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_AA_FOR_CONTEXT", EMIT_AA_FOR_CONTEXT.ToString() ) );
      model_params.Add( new KeyValuePair<string, string>( "EMIT_PAIRWISE_FEATURE", EMIT_PAIRWISE_FEATURE.ToString() ) );


      wr.Write( model_params.Count );
      foreach( KeyValuePair<string, string> k in model_params )
      {
       WriteStr( k.Key, wr );
       WriteStr( k.Value, wr );
      }
   */

   wr.Close();
  }

  Console.WriteLine( "Codebook stored" );

  return;
 }


 public void FinishTesting()
 {
  int total_word_count = 0; // всего обработано слов
  int total_C_count = 0;
  int error_count = 0;
  int B_instead_of_C_count = 0;
  int C_instead_of_B_count = 0;

  FinishTesting( out total_word_count, out total_C_count, out error_count, out B_instead_of_C_count, out C_instead_of_B_count );


  Console.WriteLine( "CONTEXT_SPAN={0}", CONTEXT_SPAN );
  Console.WriteLine( "SUFFIX_LEN={0}", SUFFIX_LEN );
  Console.WriteLine( "total_word_count={0}", total_word_count );
  Console.WriteLine( "Segmentation error count={0}, i.e. {1}%", error_count, PercentFormatter.Percent( error_count, total_word_count ) );
  Console.WriteLine( "B_instead_of_C_errors={0}%", PercentFormatter.Percent( B_instead_of_C_count, total_C_count ) );

  using( System.IO.StreamWriter wrt = new System.IO.StreamWriter( "model-training.txt", true ) )
  {
   wrt.WriteLine( "{0} TOKENIZER n_learn_samples={1} n_train_patterns={2} total_recognition_error={3} B_instead_of_C_errors={4}",
    DateTime.Now.ToString( "dd.MM.yyyy" ), n_learn_samples, n_train_patterns, PercentFormatter.Percent( error_count, total_word_count ),
    PercentFormatter.Percent( B_instead_of_C_count, total_C_count )
    );
  }

  return;
 }


}
