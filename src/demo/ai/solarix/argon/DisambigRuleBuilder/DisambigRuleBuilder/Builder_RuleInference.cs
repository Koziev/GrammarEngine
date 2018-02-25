using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class TokenRecognizer
{
 int generality;
 string lexem;
 int id_class, id_entry;
 List<SolarixGrammarEngineNET.CoordPair> pairs;
 List<TokenRecognizer> more_abstract;

 public TokenRecognizer( string _lexem )
 {
  lexem = _lexem;
  id_class = -1;
  id_entry = -1;
  generality = 1000000;
  pairs = new List<SolarixGrammarEngineNET.CoordPair>();
 }

 public TokenRecognizer( int _id_class, int _id_entry )
 {
  generality = 0;

  id_class = _id_class;
  if( id_class != -1 )
   generality += 1;

  id_entry = _id_entry;
  if( id_entry != -1 )
   generality += 1000;

  pairs = new List<SolarixGrammarEngineNET.CoordPair>();

  return;
 }

 public TokenRecognizer( int _id_class, int _id_entry, List<SolarixGrammarEngineNET.CoordPair> _pairs )
 {
  generality = 0;

  id_class = _id_class;
  if( id_class != -1 )
   generality += 1;

  id_entry = _id_entry;
  if( id_entry != -1 )
   generality += 1000;

  pairs = _pairs;
  generality += pairs.Count;

  return;
 }

 public void SetMoreAbstract( List<TokenRecognizer> _more_abstract )
 {
  more_abstract = _more_abstract;
 }


 public bool SameChecker( TokenRecognizer t )
 {
  if( lexem != t.lexem )
   return false;

  if( id_class != t.id_class )
   return false;

  if( id_entry != t.id_entry )
   return false;

  if( pairs.Count != t.pairs.Count )
   return false;

  for( int i = 0; i < pairs.Count; ++i )
   if( !pairs[i].Equals( t.pairs[i] ) )
    return false;

  return true;
 }

 public int Generality() { return generality; }

 public bool Match( SolarixGrammarEngineNET.SyntaxTreeNode token, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  if( !string.IsNullOrEmpty( lexem ) )
  {
   return lexem.Equals( token.GetWord(), StringComparison.CurrentCultureIgnoreCase );
  }

  // Признаём сопоставимость с любой версией токена.
  int nver = token.VersionCount();
  for( int iver = 0; iver < nver; ++iver )
  {
   int version_ekey = token.GetVersionEntryID( iver );

   if( id_entry != -1 && version_ekey == id_entry )
    return true;

   if( id_class != -1 && gren.GetEntryClass( version_ekey ) == id_class )
    return true;

   bool pairs_matched = true;
   foreach( SolarixGrammarEngineNET.CoordPair p in pairs )
   {
    if( !token.VersionContains( iver, p ) )
    {
     pairs_matched = false;
     break;
    }
   }

   if( pairs_matched )
    return true;
  }

  return true;
 }

 public string GetContextPoint( SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  System.Text.StringBuilder b = new StringBuilder();

  if( !string.IsNullOrEmpty( lexem ) )
   b.AppendFormat( "\"{0}\"", lexem );
  else
  {
   if( id_class != -1 )
   {
    b.AppendFormat( "{0}:*", gren.GetClassName( id_class ) );
   }
   else
   {
    int pos = gren.GetEntryClass( id_entry );
    b.AppendFormat( "{0}:{1}", gren.GetClassName( pos ), gren.GetEntryName( id_entry ) );
   }

   b.Append( "{" );

   // выводим список координатных пар
   foreach( SolarixGrammarEngineNET.CoordPair p in pairs )
   {
    string CoordName = gren.GetCoordName( p.CoordID );
    if( gren.CountCoordStates( p.CoordID ) == 0 )
    {
     if( p.StateID == 1 )
      b.AppendFormat( " {0}", CoordName );
     else
      b.AppendFormat( " ~{0}", CoordName );
    }
    else
    {
     string StateName = gren.GetCoordStateName( p.CoordID, p.StateID );
     b.AppendFormat( " {0}:{1}", CoordName, StateName );
    }
   }

   b.Append( " }" );
  }

  return b.ToString();
 }

 private bool ContainsInMoreAbstract( TokenRecognizer probe )
 {
  if( more_abstract != null )
  {
   if( more_abstract.Contains( probe ) )
    return true;

   foreach( TokenRecognizer z in more_abstract )
    if( z.ContainsInMoreAbstract( probe ) )
     return true;
  }

  return false;
 }

 private bool A_in_B( List<SolarixGrammarEngineNET.CoordPair> A, List<SolarixGrammarEngineNET.CoordPair> B )
 {
  foreach( SolarixGrammarEngineNET.CoordPair p in A )
   if( !B.Contains( p ) )
    return false;

  return true;
 }

 // Вернет true, если данный объект более общий, чем y, и включает его.
 public bool DoesIncludeArgument( TokenRecognizer y )
 {
  if( y.ContainsInMoreAbstract( this ) )
   return true;

  if( ContainsInMoreAbstract( y ) )
   return false;

  if( id_class == y.id_class && id_class != -1 )
  {
   return pairs.Count <= y.pairs.Count && A_in_B( pairs, y.pairs );
  }

  if( id_entry == y.id_entry && id_entry != -1 )
  {
   return pairs.Count <= y.pairs.Count && A_in_B( pairs, y.pairs );
  }

  if( !string.IsNullOrEmpty( lexem ) && !string.IsNullOrEmpty( y.lexem ) && lexem == y.lexem )
   return true;

  return false;
 }

}



class TokenTagsEnumerator
{
 SolarixGrammarEngineNET.SyntaxTreeNode token;
 List<TokenRecognizer> list;

 public TokenTagsEnumerator( bool IsBoundaryToken, SolarixGrammarEngineNET.SyntaxTreeNode _token, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  token = _token;
  list = new List<TokenRecognizer>();


  int id_entry = token.GetEntryID();
  int id_class = gren.GetEntryClass( id_entry );

  // Подготовим список измерений и атрибутов.
  List<SolarixGrammarEngineNET.CoordPair> dims = new List<SolarixGrammarEngineNET.CoordPair>();
  List<SolarixGrammarEngineNET.CoordPair> attrs = new List<SolarixGrammarEngineNET.CoordPair>();
  List<SolarixGrammarEngineNET.CoordPair> pairs = token.GetPairs();
  foreach( SolarixGrammarEngineNET.CoordPair p in pairs )
  {
   int t = gren.GetCoordType( id_class, p.CoordID );
   if( t == 0 || t == 2 )
    attrs.Add( p );
   else if( t == 1 )
    dims.Add( p );
  }

  // ------------------------------------------------------
  // Часть речи - самый общий случай
  // ------------------------------------------------------

  TokenRecognizer tr4 = new TokenRecognizer( id_class, -1 );
  list.Add( tr4 );

  List<TokenRecognizer> more_abstract = new List<TokenRecognizer>();
  more_abstract.Add( tr4 );

  // ------------------------------------------------------
  // Часть речи и комбинации атрибутов
  // ------------------------------------------------------

  if( attrs.Count > 0 )
  {
   List<TokenRecognizer> created_recognizers = new List<TokenRecognizer>();

   bool[] dim_bit = new bool[attrs.Count];
   for( int i = 0; i < attrs.Count; ++i )
    dim_bit[i] = false;

   while( true )
   {
    List<SolarixGrammarEngineNET.CoordPair> selected_pairs = new List<SolarixGrammarEngineNET.CoordPair>();
    for( int i = 0; i < attrs.Count; ++i )
     if( dim_bit[i] )
      selected_pairs.Add( attrs[i] );

    if( selected_pairs.Count > 0 )
    {
     TokenRecognizer tr3 = new TokenRecognizer( id_class, -1, selected_pairs );
     tr3.SetMoreAbstract( more_abstract );
     list.Add( tr3 );
     created_recognizers.Add( tr3 );
    }

    // Следующая комбинация
    int carry = 1;
    for( int ibit = dim_bit.Length - 1; ibit >= 0; --ibit )
    {
     if( dim_bit[ibit] == false )
     {
      dim_bit[ibit] = true;
      carry = 0;
      break;
     }
     else
     {
      dim_bit[ibit] = false;
     }
    }

    if( carry == 1 )
     break;
   }

   more_abstract = created_recognizers;
  }


  // Лемма - только id словарной статьи. Это боее частный случай, чем указание части речи.
  TokenRecognizer tr2 = new TokenRecognizer( -1, id_entry );
  tr2.SetMoreAbstract( more_abstract );
  list.Add( tr2 );
  more_abstract = new List<TokenRecognizer>();
  more_abstract.Add( tr2 );


  if( dims.Count > 0 )
  {
   List<TokenRecognizer> created_recognizers = new List<TokenRecognizer>();

   // -----------------------------------------------------------------------
   // Лемма (то есть id словарной статьи) и различные комбинации измерений.
   // -----------------------------------------------------------------------
   bool[] dim_bit = new bool[dims.Count];
   for( int i = 0; i < dims.Count; ++i )
    dim_bit[i] = false;

   while( true )
   {
    List<SolarixGrammarEngineNET.CoordPair> selected_pairs = new List<SolarixGrammarEngineNET.CoordPair>();
    for( int i = 0; i < dims.Count; ++i )
     if( dim_bit[i] )
      selected_pairs.Add( dims[i] );

    if( selected_pairs.Count > 0 )
    {
     TokenRecognizer tr5 = new TokenRecognizer( -1, id_entry, selected_pairs );
     tr5.SetMoreAbstract( more_abstract );
     created_recognizers.Add( tr5 );
     list.Add( tr5 );
    }

    // Следующая комбинация
    int carry = 1;
    for( int ibit = dim_bit.Length - 1; ibit >= 0; --ibit )
    {
     if( dim_bit[ibit] == false )
     {
      dim_bit[ibit] = true;
      carry = 0;
      break;
     }
     else
     {
      dim_bit[ibit] = false;
     }
    }

    if( carry == 1 )
     break;
   }

   more_abstract = created_recognizers;
  }


  // ----------------------------------
  // Лексема - самый частный случай.
  // ----------------------------------
  /*
    if( !IsBoundaryToken )
    {
     TokenRecognizer tr0 = new TokenRecognizer( token.GetWord() );
     tr0.SetMoreAbstract( more_abstract );
     list.Add( tr0 );
    }
  */

  return;
 }

 public int Count { get { return list.Count; } }
 public TokenRecognizer this[int index] { get { return list[index]; } }
}


class OmonymTokenRecognizer
{
 private int position;
 private int id_entry;
 private string word;

 public OmonymTokenRecognizer( int _position, SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  position = _position;
  id_entry = token.GetEntryID();
  word = token.GetWord();
 }

 public int GetPosition() { return position; }

 public bool Match( SolarixGrammarEngineNET.SyntaxTreeNode token )
 {
  return token.GetEntryID() == id_entry;
 }

 public string GetContextPoint( SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  return string.Format( "[\"{0}\"{{class:{1}}}]", word, gren.GetClassName( gren.GetEntryClass( id_entry ) ) );
 }
}


class MatchedContextInfo
{
 private string sample, context;

 public MatchedContextInfo( string _sample, SolarixGrammarEngineNET.AnalysisResults tokens, int left_i, int len )
 {
  sample = _sample;

  System.Text.StringBuilder b = new StringBuilder();
  for( int i = 0; i < len; ++i )
  {
   string word = tokens[left_i + i].GetWord();
   if( i == 0 )
    b.AppendFormat( "{0}", word );
   else
    b.AppendFormat( " {0}", word );
  }

  context = b.ToString();
  return;
 }

 public string GetSample() { return sample; }

 public override string ToString()
 {
  return string.Format( "{0} / {1}", sample, context );
 }

 public override bool Equals( object obj )
 {
  MatchedContextInfo x = (MatchedContextInfo)obj;
  return x.sample == sample && x.context == context;
 }

 public override int GetHashCode()
 {
  return sample.GetHashCode() ^ context.GetHashCode();
 }
}


class ContextRecognizer
{
 private static int seq_counter = 0;

 private int id;
 private int success_count, fail_count;

 private HashSet<MatchedContextInfo> success_samples, fail_samples;
 private List<TokenRecognizer> points;
 private OmonymTokenRecognizer omonym_point;
 private string rule_context_str;

 public ContextRecognizer( List<TokenRecognizer> _points, OmonymTokenRecognizer _omonym_point, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  id = seq_counter++;
  omonym_point = _omonym_point;
  points = _points;
  success_count = 0;
  fail_count = 0;
  success_samples = new HashSet<MatchedContextInfo>();
  fail_samples = new HashSet<MatchedContextInfo>();
  rule_context_str = PrintContext( gren );
 }

 public void Success( MatchedContextInfo info ) { success_count++; success_samples.Add( info ); }
 public void Fail( MatchedContextInfo info ) { fail_count++; fail_samples.Add( info ); }

 public bool EqualTokens( ContextRecognizer y )
 {
  for( int i = 0; i < points.Count; ++i )
   if( points[i] != null && !points[i].SameChecker( y.points[i] ) )
    return false;

  return true;
 }

 public int Match( SolarixGrammarEngineNET.AnalysisResults tokens, int left_i, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  // Проверяем, что не-омонимичные термы сопоставляются.
  bool m = true;
  for( int iterm = 0; iterm < points.Count; ++iterm )
   if( points[iterm] != null )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[left_i + iterm];
    if( !points[iterm].Match( token, gren ) )
    {
     m = false;
     break;
    }
   }

  if( m )
  {
   // Осталось проверить, правильно ли снята омонимия.
   SolarixGrammarEngineNET.SyntaxTreeNode omonym_token = tokens[left_i + omonym_point.GetPosition()];
   return omonym_point.Match( omonym_token ) ? 1 : 0;
  }

  return -1;
 }

 // Вернет true, если данное правило более общее, чем y.
 public bool IncludesY( ContextRecognizer y )
 {
  for( int i = 0; i < points.Count; ++i )
   if( points[i] != null )
    if( !points[i].DoesIncludeArgument( y.points[i] ) )
     return false;

  return true;
 }


 public bool HasEverFailed() { return fail_count > 0; }


 public int DumpRule( System.IO.TextWriter dest, int LanguageID, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  dest.WriteLine( "\n\n#region\n// This rules has {0} successful checks:", success_count );

  // Выведем список эталонов, которые подтверждают правило:
  foreach( MatchedContextInfo sample in success_samples )
  {
   dest.WriteLine( "// {0}", sample.ToString() );
  }

  dest.WriteLine( "#endregion" );

  // теперь само правило
  string lang = string.Empty; ;
  switch( LanguageID )
  {
   case SolarixGrammarEngineNET.GrammarEngineAPI.RUSSIAN_LANGUAGE: lang = "Russian"; break;
   case SolarixGrammarEngineNET.GrammarEngineAPI.ENGLISH_LANGUAGE: lang = "English"; break;
  }

  dest.WriteLine( "colloc_filter auto_rule_{1} language={0}", lang, id );
  dest.WriteLine( "{" );
  dest.WriteLine( " if context {{{0} }} then accept", rule_context_str );
  dest.WriteLine( "}\n" );

  return 1;
 }

 private string PrintContext( SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  System.Text.StringBuilder ctx_str = new StringBuilder();
  foreach( var point in points )
  {
   if( point == null )
    ctx_str.AppendFormat( " {0}", omonym_point.GetContextPoint( gren ) );
   else
    ctx_str.AppendFormat( " {0}", point.GetContextPoint( gren ) );
  }

  return ctx_str.ToString();
 }

 public void GetSamples( HashSet<string> samples )
 {
  foreach( var x in success_samples )
   samples.Add( x.GetSample() );

  return;
 }

 public override string ToString()
 {
  return rule_context_str;
 }

}


class OmonymContextEnumerator
{
 SolarixGrammarEngineNET.GrammarEngine2 gren;

 int left_i;
 int len;
 int omonym_position;

 List<ContextRecognizer> recognizers;

 private bool IsBoundaryToken( SolarixGrammarEngineNET.AnalysisResults tokens, int index )
 {
  return index == 0 || index == tokens.Count - 1;
 }

 public OmonymContextEnumerator( SolarixGrammarEngineNET.AnalysisResults tokens, int _omonym_position, int _left_i, int _len, SolarixGrammarEngineNET.GrammarEngine2 _gren )
 {
  gren = _gren;
  left_i = _left_i;
  len = _len;
  omonym_position = _omonym_position;

  recognizers = new List<ContextRecognizer>();

  // Для каждого токена, кроме омонимичной формы, генерируем список вариантов.

  // ... пока только код для контекстов длины=2
  if( len == 2 )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode omonym_token = tokens[left_i + omonym_position];

   OmonymTokenRecognizer omonym_point = new OmonymTokenRecognizer( omonym_position, omonym_token );

   if( omonym_position == 0 )
   {
    TokenTagsEnumerator tte = new TokenTagsEnumerator( IsBoundaryToken( tokens, left_i + 1 ), tokens[left_i + 1], gren );

    int n = tte.Count;
    for( int i = 0; i < n; ++i )
    {
     List<TokenRecognizer> points = new List<TokenRecognizer>();
     points.Add( null ); // это омонимичная форма
     points.Add( tte[i] );
     ContextRecognizer ctx_recognizer = new ContextRecognizer( points, omonym_point, gren );
     recognizers.Add( ctx_recognizer );
    }
   }
   else
   {
    TokenTagsEnumerator tte = new TokenTagsEnumerator( IsBoundaryToken( tokens, left_i ), tokens[left_i], gren );

    int n = tte.Count;
    for( int i = 0; i < n; ++i )
    {
     List<TokenRecognizer> points = new List<TokenRecognizer>();
     points.Add( tte[i] );
     points.Add( null ); // это омонимичная форма
     ContextRecognizer ctx_recognizer = new ContextRecognizer( points, omonym_point, gren );
     recognizers.Add( ctx_recognizer );
    }
   }
  }
 }

 public int Count { get { return recognizers.Count; } }
 public ContextRecognizer this[int index] { get { return recognizers[index]; } }
}


struct OmonymContext
{
 public int len;
 public int position;
}


class OmonymRule
{
 OmonymContext ctx;

 List<ContextRecognizer> recognizers;

 public OmonymRule( OmonymContext _ctx )
 {
  ctx = _ctx;
  recognizers = new List<ContextRecognizer>();
 }



 public void ProcessSample( string line, SolarixGrammarEngineNET.AnalysisResults tokens, int left_i, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  // В контекст входят слова от left_i по left_i+ctx.len.
  /*
    // ---- DEBUG
    System.Text.StringBuilder b = new StringBuilder();
    for( int i=0; i<ctx.len; ++i )
     if( i>0 )
      b.AppendFormat( " {0}", tokens[left_i+i].GetWord() );
     else
      b.AppendFormat( "{0}", tokens[left_i+i].GetWord() );
  
    string context_str = b.ToString();
    // --- END DEBUG
  */

  // ... todo проверяем, не сопоставляются ли слова с уже имеющимися контекстами.
  for( int i = 0; i < recognizers.Count; ++i )
  {
   ContextRecognizer recognizer = recognizers[i];
   int match = recognizer.Match( tokens, left_i, gren );
   if( match == 1 )
   {
    // правило правильно распознало контекст и сняло омонимию.
    recognizer.Success( new MatchedContextInfo( line, tokens, left_i, ctx.len ) );
   }
   else if( match == 0 )
   {
    // правило распознало контекст, но неправильно сняло омонимию.
    recognizer.Fail( new MatchedContextInfo( line, tokens, left_i, ctx.len ) );
   }
  }

  // Используем сэмпл для генерации правил только в том случае, если омонимичный токен дал 1 вариант словарной статьи.
  bool generate_rule = true;
  int omonym_ekey = -1;
  SolarixGrammarEngineNET.SyntaxTreeNode omonym_token = tokens[left_i + ctx.position];
  int omonym_versions = omonym_token.VersionCount();
  for( int iver = 0; iver < omonym_versions; ++iver )
  {
   int ekey = omonym_token.GetVersionEntryID( iver );
   if( omonym_ekey == -1 )
    omonym_ekey = ekey;
   else if( omonym_ekey != ekey )
   {
    // омонимичный токен распознан как несколько разных лемм, поэтому не будет генерировать для него правила.
    generate_rule = false;
    break;
   }
  }

  if( generate_rule )
  {
   // Генерируем варианты распознавания контекста, начиная от самого конкретного - через лексемы не-мононимичных слов, для самых
   // общих - частей речи для них же.
   OmonymContextEnumerator ctx_generator = new OmonymContextEnumerator( tokens, ctx.position, left_i, ctx.len, gren );

   for( int i = 0; i < ctx_generator.Count; ++i )
   {
    ContextRecognizer recognizer = ctx_generator[i];

    // проверим, что такого распознавателя еще нет.
    bool is_unique = true;
    foreach( ContextRecognizer r in recognizers )
    {
     if( r.EqualTokens( recognizer ) )
     {
      is_unique = false;
      break;
     }
    }

    if( is_unique )
    {
     recognizer.Success( new MatchedContextInfo( line, tokens, left_i, ctx.len ) );
     recognizers.Add( recognizer );
    }
   }
  }

  return;
 }

 public int DumpRules( System.IO.TextWriter dest, int LanguageID, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  int counter = 0;

  // Выводим все правила (todo - надо только самые общие из возможных), которые ни разу не ошиблись.
  List<ContextRecognizer> good = new List<ContextRecognizer>();

  foreach( ContextRecognizer r in recognizers )
   if( !r.HasEverFailed() )
    good.Add( r );

  // теперь оставим в этом списке только ортогональные правила.
  List<ContextRecognizer> orthogonal = new List<ContextRecognizer>();
  for( int i = 0; i < good.Count; ++i )
  {
   ContextRecognizer x = good[i];

   bool is_orthogonal = true;

   for( int j = 0; j < good.Count; ++j )
    if( i != j && good[j].IncludesY( x ) )
    {
     is_orthogonal = false;
     break;
    }

   if( is_orthogonal )
    orthogonal.Add( x );
  }

  foreach( ContextRecognizer r in orthogonal )
  {
   counter += r.DumpRule( dest, LanguageID, gren );
  }

  return counter;
 }

 public void GetSamples( HashSet<string> samples )
 {
  foreach( var x in recognizers )
   x.GetSamples( samples );

  return;
 }

}



// Генератор правил для одной омонимичной формы
class OmonymProcessor
{
 private string word, normalized;
 Dictionary<OmonymContext, OmonymRule> rules;

 public OmonymProcessor( string _word )
 {
  word = _word;
  normalized = word.ToLower();
  rules = new Dictionary<OmonymContext, OmonymRule>();
 }

 public void ProcessSample( string line, SolarixGrammarEngineNET.AnalysisResults tokens, int LanguageID, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  int sample_len = tokens.Count;
  for( int i = 0; i < sample_len; ++i )
  {
   if( tokens[i].GetWord().Equals( word, StringComparison.CurrentCultureIgnoreCase ) )
   {
    int position = i;

    // Омоним распознан однозначно?
    SolarixGrammarEngineNET.SyntaxTreeNode omonym_token = tokens[position];

    // Создаем все возможные контексты с омонимом - разной длины, с разным местоположением.
    int MIN_CONTEXT_LEN = 2, MAX_CONTEXT_LEN = 2;
    for( int left_i = position - MAX_CONTEXT_LEN + 1; left_i <= position; ++left_i )
     if( left_i >= 0 )
     {
      int min_len = Math.Max( position - left_i + 1, MIN_CONTEXT_LEN );
      for( int ctx_len = min_len; ctx_len <= MAX_CONTEXT_LEN; ++ctx_len )
      {
       OmonymContext ctx;
       ctx.len = ctx_len;
       ctx.position = position - left_i;

       if( rules.ContainsKey( ctx ) )
       {
        rules[ctx].ProcessSample( line, tokens, left_i, gren );
       }
       else
       {
        OmonymRule rule = new OmonymRule( ctx );
        rules.Add( ctx, rule );
        rule.ProcessSample( line, tokens, left_i, gren );
       }
      }
     }
   }
  }

  return;
 }

 public int DumpRules( System.IO.TextWriter dest, int LanguageID, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  int counter = 0;

  foreach( var r in rules )
  {
   counter += r.Value.DumpRules( dest, LanguageID, gren );
  }

  return counter;
 }

 public int CountSamples()
 {
  HashSet<string> samples = new HashSet<string>();

  foreach( var r in rules )
  {
   r.Value.GetSamples( samples );
  }

  return samples.Count;
 }
}


class Builder_RuleInference
{
 // если внешние омонимы надо самостоятельно искать в обрабатываемых образцах
 public bool retrieve_omonyms_from_samples = false;

 public int MaxOmonymPerSession = 10; // макс. число омонимов, для которых будет строится группа фильтров в рамках одной сессии.

 // Список омонимичных форм, для которых будут генерироваться правила.
 private HashSet<string> omonyms;
 private Dictionary<string, OmonymProcessor> omonym_processors;

 private HashSet<string> not_omonyms;

 private HashSet<string> ignore_omonyms; // обработанные в предыдущих итерациях омонимы, которые теперь надо игнорировать.

 private void InitOmonyms()
 {
  omonyms = new HashSet<string>();
  omonym_processors = new Dictionary<string, OmonymProcessor>();
  not_omonyms = new HashSet<string>();
  ignore_omonyms = new HashSet<string>();

  if( !retrieve_omonyms_from_samples )
  {
   foreach( string word in new string[] { "мой" } ) //, "мою", "мыл", "мыла", "мыло", "дома", "домой", "села" } )
   {
    string lword = word.ToLower();
    omonyms.Add( lword );
    OmonymProcessor processor = new OmonymProcessor( word );
    omonym_processors.Add( word, processor );
   }
  }

  return;
 }


 public bool IsThereOmonymsToProcess()
 {
  foreach( string o in omonyms )
   if( !ignore_omonyms.Contains( o ) )
    return true;

  return false;
 }


 public void NewPortion()
 {
  foreach( string w in omonyms )
   ignore_omonyms.Add( w );

  omonyms.Clear();
  omonym_processors.Clear();
  return;
 }

 public Builder_RuleInference()
 {
  InitOmonyms();
 }


 private SolarixGrammarEngineNET.GrammarEngine2 gren;
 public void LoadDictionary( string filepath )
 {
  gren = new SolarixGrammarEngineNET.GrammarEngine2();
  gren.Load( filepath, false ); // для скорости парсинга загружаем лексикон в память
  return;
 }


 int LanguageID = -1;
 public void SetLanguage( int id ) { LanguageID = id; }



 public bool ProcessSample( string line )
 {
  int occurence_count = 0;

  // Морфологический разбор
  using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
  {

   for( int i = 1; i < tokens.Count - 1; ++i )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[i];
    string word = token.GetWord().ToLower();

    if( retrieve_omonyms_from_samples )
    {
     if( omonyms.Contains( word ) )
     {
      occurence_count++;
      omonym_processors[word].ProcessSample( line, tokens, LanguageID, gren );
     }
     else if( !not_omonyms.Contains( word ) && omonyms.Count < MaxOmonymPerSession )
     {
      bool is_omonym = false;

      if( !ignore_omonyms.Contains( word ) )
      {
       // сделаем проекцию слова
       int id_class0 = -1;
       using( SolarixGrammarEngineNET.WordProjections projs = gren.FindWordForm( word ) )
       {
        for( int j = 0; j < projs.Count; ++j )
        {
         int id_entry = projs.GetEntryKey( j );
         int id_class = gren.GetEntryClass( id_entry );
         if( id_class0 == -1 )
          id_class0 = id_class;
         else if( id_class0 != id_class )
         {
          is_omonym = true;
          break;
         }
        }
       }

       if( is_omonym )
       {
        omonyms.Add( word );
        OmonymProcessor processor = new OmonymProcessor( word );
        omonym_processors.Add( word, processor );

        occurence_count++;
        omonym_processors[word].ProcessSample( line, tokens, LanguageID, gren );
       }
       else
        not_omonyms.Add( word );
      }
     }
    }
    else if( omonyms.Contains( word ) )
    {
     occurence_count++;
     omonym_processors[word].ProcessSample( line, tokens, LanguageID, gren );
    }
   }
  }

  return occurence_count > 0;
 }


 public void DumpRules( string filepath )
 {
  using( System.IO.StreamWriter dest = new System.IO.StreamWriter( filepath, false, new UTF8Encoding( true ) ) )
  {
   int rule_count = 0;

   dest.WriteLine( "/*" );

   foreach( var processor in omonym_processors )
   {
    int n = processor.Value.CountSamples();
    dest.WriteLine( "{0} --> {1} sample(s)", processor.Key, n );
   }

   dest.Write( "{0} omonyms are to be resolved:", omonyms.Count );
   foreach( string w in omonyms )
    dest.Write( " [{0}]", w );
   dest.WriteLine( "" );

   dest.WriteLine( "*/" );

   foreach( var processor in omonym_processors )
    rule_count += processor.Value.DumpRules( dest, LanguageID, gren );

   dest.WriteLine( "// There are {0} rules in this file.", rule_count );
  }

  return;
 }
}

