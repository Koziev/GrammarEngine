using System.Collections.Generic;
using System.Linq;

class WordTags
{
 public int common;
 public int modality;
 public int valency;

 public WordTags() { common=-1; modality=-1; valency=-1; }
}


class TreeLookup
{
 public bool ok = false;

 private List<List<string>> labels;

 public TreeLookup() { }


 private void CollectSubtreeNodeIndeces( SolarixGrammarEngineNET.SyntaxTreeNode node, List<int> word_index )
 {
  if( node.GetWord() == "." )
   return;

  word_index.Add( node.GetWordPosition() );

  for( int ileaf = 0; ileaf < node.leafs.Count; ++ileaf )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode leaf = node.leafs[ileaf];
   CollectSubtreeNodeIndeces( leaf, word_index );
  }

  return;
 }


 private void SetLabel( SolarixGrammarEngineNET.SyntaxTreeNode node, string label, bool recursive )
 {
  if( recursive )
  {
   List<int> indeces = new List<int>();
   CollectSubtreeNodeIndeces( node, indeces );

   int k = 0;
   foreach( int index in indeces.OrderBy( z => z ) )
   {
    if( k == 0 )
    {
     labels[index + 1].Insert( 0, label );
    }
    else
     labels[index + 1].Insert( 0, label );

    k++;
   }
  }
  else
  {
   int index = node.GetWordPosition();
   labels[index + 1].Insert( 0, label );
  }

  return;
 }

 int chunk_num = 0;

 private void ProcessTree( SolarixGrammarEngineNET.SyntaxTreeNode node, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  int p_ekey = node.GetEntryID();
  int id_class = gren.GetEntryClass( p_ekey );

  if(
     id_class == SolarixGrammarEngineNET.GrammarEngineAPI.NOUN_ru ||
     id_class == SolarixGrammarEngineNET.GrammarEngineAPI.PRONOUN2_ru ||
     id_class == SolarixGrammarEngineNET.GrammarEngineAPI.PRONOUN_ru
    )
  {
   SetLabel( node, string.Format( "NP:{0}", chunk_num++ ), true );

   for( int ileaf = 0; ileaf < node.leafs.Count; ++ileaf )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode leaf = node.leafs[ileaf];

    if(
       node.GetLinkType( ileaf ) == SolarixGrammarEngineNET.GrammarEngineAPI.RIGHT_GENITIVE_OBJECT_link ||
       node.GetLinkType( ileaf ) == SolarixGrammarEngineNET.GrammarEngineAPI.OBJECT_link
      )
    {
     SetLabel( leaf, string.Format( "NP:{0}", chunk_num++ ), true );
    }
   }
  }
  else if( id_class == SolarixGrammarEngineNET.GrammarEngineAPI.PREPOS_ru )
  {
   SetLabel( node, string.Format( "PN:{0}", chunk_num++ ), true );

   for( int ileaf = 0; ileaf < node.leafs.Count; ++ileaf )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode leaf = node.leafs[ileaf];

    int p_ekey2 = leaf.GetEntryID();
    int id_class2 = gren.GetEntryClass( p_ekey2 );
    if(
       id_class2 == SolarixGrammarEngineNET.GrammarEngineAPI.NOUN_ru ||
       id_class2 == SolarixGrammarEngineNET.GrammarEngineAPI.ADJ_ru ||
       id_class2 == SolarixGrammarEngineNET.GrammarEngineAPI.PRONOUN_ru ||
       id_class2 == SolarixGrammarEngineNET.GrammarEngineAPI.PRONOUN2_ru ||
       id_class2 == SolarixGrammarEngineNET.GrammarEngineAPI.NUMBER_ru
      )
    {
     SetLabel( leaf, string.Format( "NP:{0}", chunk_num++ ), true );
    }
   }
  }
  else if(
          id_class == SolarixGrammarEngineNET.GrammarEngineAPI.IMPERSONAL_VERB_ru ||
          id_class == SolarixGrammarEngineNET.GrammarEngineAPI.VERB_ru ||
          id_class == SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru
         )
  {
   SetLabel( node, string.Format( "VP:{0}", chunk_num++ ), true );
   SetLabel( node, string.Format( "VX:{0}", chunk_num++ ), false ); // корневой глагол отмечаем как VX

   for( int ileaf = 0; ileaf < node.leafs.Count; ++ileaf )
   {
    SolarixGrammarEngineNET.SyntaxTreeNode leaf = node.leafs[ileaf];

    if( node.GetLinkType( ileaf ) == SolarixGrammarEngineNET.GrammarEngineAPI.SUBJECT_link )
    {
     SetLabel( leaf, string.Format( "NP:{0}", chunk_num++ ), true );
    }
    else if( node.GetLinkType( ileaf ) == SolarixGrammarEngineNET.GrammarEngineAPI.OBJECT_link )
    {
     SetLabel( leaf, string.Format( "NP:{0}", chunk_num++ ), true );
    }
   }
  }

  for( int ileaf = 0; ileaf < node.leafs.Count; ++ileaf )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode leaf = node.leafs[ileaf];
   ProcessTree( leaf, gren );
  }

  return;
 }


 bool Find( string label, List<string> labels )
 {
  foreach( string l in labels )
   if( l.StartsWith( label ) )
    return true;

  return false;
 }

 bool FindExact( string label, List<string> labels )
 {
  foreach( string l in labels )
   if( l == label )
    return true;

  return false;
 }

 void RemoveLabel( string label, List<string> labels )
 {
  for( int i = 0; i < labels.Count; ++i )
   if( labels[i].StartsWith( label ) )
   {
    labels.RemoveAt( i );
    break;
   }

  return;
 }

 public void Collect( SolarixGrammarEngineNET.AnalysisResults tokens, SolarixGrammarEngineNET.AnalysisResults trees, SolarixGrammarEngineNET.GrammarEngine2 gren )
 {
  if( trees.Count == 3 )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode root = trees[1];
   int p_ekey = root.GetEntryID();
   int id_class = gren.GetEntryClass( p_ekey );

   if(
      id_class == SolarixGrammarEngineNET.GrammarEngineAPI.IMPERSONAL_VERB_ru ||
      id_class == SolarixGrammarEngineNET.GrammarEngineAPI.VERB_ru ||
      id_class == SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru
     )
    ok = true;
  }

  if( ok )
  {
   int N = tokens.Count;

   labels = new List<List<string>>();
   for( int iroot = 0; iroot < N; ++iroot )
   {
    List<string> x = new List<string>();
    x.Add( "O" );
    labels.Add( x );
   }

   for( int iroot = 1; iroot < trees.Count - 1; ++iroot )
    ProcessTree( trees[iroot], gren );

   // -----------------------------------------------
   // Уточняем разметку для групп существительных
   // -----------------------------------------------
   for( int i = 1; i < N - 1; ++i )
   {
    List<string> l = labels[i];

    if( l[0].StartsWith( "NP" ) )
    {
     string NP = l[0];

     // меняем метку у первого токена на B-NP
     l.RemoveAt( 0 );
     l.Insert( 0, "B-NP" );

     // идем вправо до появления другой NP-метки.
     for( int k = i + 1; k < N; ++k )
     {
      if( labels[k][0] == NP )
      {
       labels[k].RemoveAt( 0 );
       labels[k].Insert( 0, "I-NP" );
      }
      else
      {
       // Удалим все появления NP-метки далее вправо.
       for( int q = k; q < N; ++q )
        labels[q].Remove( NP );

       break;
      }
     }
    }
   }


   // Уточняем разметку для глагольных групп.
   for( int i = 1; i < N - 1; ++i )
   {
    List<string> l = labels[i];

    if( l[0].StartsWith( "VX" ) )
    {
     // Корневой глагол в сказуемом.
     // Цепочка токенов в группе может быть разорвана из-за того, что наречный оборот, привязанный к сказуемому,
     // стоит справа от глагольного дополнения. Поэтому проверим наличие таких разрывов.
     l.RemoveAt( 0 ); // под VX лежит VP, который мы сейчас поднимем
     string VP = l[0];

     int vp_begin = i;
     // ищем разрыв слева
     for( int k = i - 1; k >= 0; --k )
     {
      if( labels[k][0] != VP )
      {
       // слева - конец цепочки токенов для этого сказуемого. Удалим все более левые упоминания этого VP.
       for( ; k >= 0; --k )
       {
        labels[k].Remove( VP );
       }

       break;
      }
      else
       vp_begin = k;
     }

     int vp_end = i;
     // ищем разрыв справа
     for( int k = i + 1; k < N; ++k )
     {
      if( labels[k][0] != VP )
      {
       // справа - конец цепочки токенов для этого сказуемого. Удалим все более правые упоминания этого VP.
       for( ; k < N; ++k )
       {
        labels[k].Remove( VP );
       }
       break;
      }
      else
       vp_end = k;
     }

     // поставим отметку на первый VP-токен
     labels[vp_begin].RemoveAt( 0 );
     labels[vp_begin].Insert( 0, "B-VP" );

     // а остальные пометим как I-VP
     for( int j = vp_begin + 1; j <= vp_end; ++j )
     {
      labels[j].Remove( VP );
      labels[j].Insert( 0, "I-VP" );
     }
    }
   }


   for( int i = 0; i < labels.Count; ++i )
   {
    string l = labels[i][0];
    string[] t = l.Split( ':' );
    labels[i].Clear();
    labels[i].Add( t[0] );
   }
  }

  return;
 }

 public string GetTokenLabel( int iword )
 {
  return labels[iword][0];
 }
}

class Builder_Syntax_CRF
{
 System.IO.StreamWriter crf_file, visual_file;

 private TagBook tags, tags_modality, tags_valency;
 int START_id, END_id; // id тегов для границ

 bool IsUnknownLexem( string s )
 {
  return s.Equals( "UNKNOWNENTRY", System.StringComparison.InvariantCultureIgnoreCase ) ||
         s == "???" ||
         s.Equals( "number_", System.StringComparison.InvariantCultureIgnoreCase );
 }

 public Builder_Syntax_CRF()
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

 private HashSet<string> undividable_words = new HashSet<string>();

 public void Init()
 {
  tags_modality = new TagBook("modality");
  tags_modality.Load( "МОДАЛЬНЫЙ", gren );

  tags_valency = new TagBook("valency");
  tags_valency.Load(
@"
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ВИН
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ТВОР
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ВИН
ПРЕДЛОГ ПАДЕЖ:РОД ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ПРЕДЛОГ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ПРЕДЛОГ ПАДЕЖ:РОД
ПРЕДЛОГ ПАДЕЖ:ТВОР
ПРЕДЛОГ ПАДЕЖ:ВИН
ПРЕДЛОГ ПАДЕЖ:ДАТ

ПОСЛЕЛОГ ПАДЕЖ:ВИН
ПОСЛЕЛОГ ПАДЕЖ:ДАТ
ПОСЛЕЛОГ ПАДЕЖ:РОД
ПОСЛЕЛОГ ПАДЕЖ:ТВОР

ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ВИН
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ВИН
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН
ГЛАГОЛ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ДАТ
ГЛАГОЛ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ

ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ВИН
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ВИН
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ДАТ
ИНФИНИТИВ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ

ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ТВОР
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ВИН
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ПАРТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ТВОР
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ВИН
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ДАТ
ДЕЕПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ

ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ПАРТ ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ВИН ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ПАРТ ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ВИН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ПАРТ ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ПАРТ ПАДЕЖВАЛ:ВИН ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ВИН ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ВИН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ВИН ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ПАРТ ПАДЕЖВАЛ:ТВОР
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ПАРТ ПАДЕЖВАЛ:ВИН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ПАРТ ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ВИН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ВИН ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ПАРТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ТВОР
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ВИН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ВИН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ТВОР ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:РОД
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ТВОР
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ДАТ
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ
", gren );

  tags = new TagBook( "featureset" );

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
'ДОЛЖНЫ'
'НЕ'
'ДАВАЙ'
'ДАВАЙТЕ'
'ДАЙ'
'-'
','
'.'

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


ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:МУЖ 
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:ЖЕН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ИМ ЧИСЛО:ЕД РОД:СР
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ИМ ЧИСЛО:МН

ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:МУЖ 
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:ЖЕН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:СР
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:РОД ЧИСЛО:МН

ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:МУЖ 
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:ЖЕН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ТВОР ЧИСЛО:ЕД РОД:СР
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ТВОР ЧИСЛО:МН

ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:МУЖ 
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:ЖЕН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ВИН ЧИСЛО:ЕД РОД:СР
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ВИН ЧИСЛО:МН

ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:МУЖ 
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:ЖЕН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ДАТ ЧИСЛО:ЕД РОД:СР
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ДАТ ЧИСЛО:МН

ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:МУЖ 
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:ЖЕН
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ПРЕДЛ ЧИСЛО:ЕД РОД:СР
ПРИЛАГАТЕЛЬНОЕ ПРИЧАСТИЕ СТРАД ~КРАТКИЙ ПАДЕЖ:ПРЕДЛ ЧИСЛО:МН

ГЛАГОЛ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:МУЖ
ГЛАГОЛ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:ЖЕН
ГЛАГОЛ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР
ГЛАГОЛ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН

ГЛАГОЛ ВРЕМЯ:НАСТОЯЩЕЕ ЧИСЛО:ЕД ЛИЦО:1
ГЛАГОЛ ВРЕМЯ:НАСТОЯЩЕЕ ЧИСЛО:ЕД ЛИЦО:2
ГЛАГОЛ ВРЕМЯ:НАСТОЯЩЕЕ ЧИСЛО:ЕД ЛИЦО:3
ГЛАГОЛ ВРЕМЯ:НАСТОЯЩЕЕ ЧИСЛО:МН ЛИЦО:1
ГЛАГОЛ ВРЕМЯ:НАСТОЯЩЕЕ ЧИСЛО:МН ЛИЦО:2
ГЛАГОЛ ВРЕМЯ:НАСТОЯЩЕЕ ЧИСЛО:МН ЛИЦО:3

ГЛАГОЛ ВРЕМЯ:БУДУЩЕЕ ЧИСЛО:ЕД ЛИЦО:1
ГЛАГОЛ ВРЕМЯ:БУДУЩЕЕ ЧИСЛО:ЕД ЛИЦО:2
ГЛАГОЛ ВРЕМЯ:БУДУЩЕЕ ЧИСЛО:ЕД ЛИЦО:3
ГЛАГОЛ ВРЕМЯ:БУДУЩЕЕ ЧИСЛО:МН ЛИЦО:1
ГЛАГОЛ ВРЕМЯ:БУДУЩЕЕ ЧИСЛО:МН ЛИЦО:2
ГЛАГОЛ ВРЕМЯ:БУДУЩЕЕ ЧИСЛО:МН ЛИЦО:3

ГЛАГОЛ НАКЛОНЕНИЕ:ПОБУД ЛИЦО:1 ЧИСЛО:МН
ГЛАГОЛ НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:ЕД
ГЛАГОЛ НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:МН

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

ИНФИНИТИВ
ДЕЕПРИЧАСТИЕ

БЕЗЛИЧ_ГЛАГОЛ

NUM_WORD

UNKNOWNENTRIES
ВВОДНОЕ
ПРЕДЛОГ
СОЮЗ
ЧАСТИЦА
ПУНКТУАТОР
НАРЕЧИЕ
BETH:BEGIN{}
BETH:END{}
";

  tags.Load( str_tags, gren );

  START_id = tags.FindBySrc( "BETH:BEGIN{}" );
  END_id = tags.FindBySrc( "BETH:END{}" );

  return;
 }

 int n_learn_samples = 0;



 public bool ProcessSample( string line )
 {
  if( crf_file == null )
  {
   crf_file = new System.IO.StreamWriter( "crf_train.txt" );
   visual_file = new System.IO.StreamWriter( "crf_visual.txt" );
  }

  bool r = Sentence2Features( line );
  if( r )
   n_learn_samples++;

  return true;
 }




 void PullFeatures1( System.Text.StringBuilder b, List<WordTags> token_features, int ifocus, int offset )
 {
  int iword = ifocus + offset;

  if( iword >= 0 && iword < token_features.Count )
  {
   WordTags f = token_features[iword];
   b.AppendFormat( "\tF[{0}]={1}", offset, f.common );

   if( f.modality!=-1 )
    b.AppendFormat( "\tM[{0}]={1}", offset, f.common );

   if( f.valency!=-1 )
    b.AppendFormat( "\tV[{0}]={1}", offset, f.common );
  }

  return;
 }


 void PullFeatures2( System.Text.StringBuilder b, List<WordTags> token_features, int ifocus, int offset1, int offset2 )
 {
  int iword1 = ifocus + offset1;
  int iword2 = ifocus + offset2;

  if( iword1 >= 0 && iword1 < token_features.Count && iword2 >= 0 && iword2 < token_features.Count )
  {
   WordTags f1 = token_features[iword1];
   WordTags f2 = token_features[iword2];

   b.AppendFormat( "\tF[{0},{1}]={2},{3}", offset1, offset2, f1.common, f2.common );
  }

  return;
 }



 void PullFeatures3( System.Text.StringBuilder b, List<WordTags> token_features, int ifocus, int offset1, int offset2, int offset3 )
 {
  int iword1 = ifocus + offset1;
  int iword2 = ifocus + offset2;
  int iword3 = ifocus + offset3;

  if( iword1 >= 0 && iword1 < token_features.Count && iword2 >= 0 && iword2 < token_features.Count && iword3 >= 0 && iword3 < token_features.Count )
  {
   WordTags f1 = token_features[iword1];
   WordTags f2 = token_features[iword2];
   WordTags f3 = token_features[iword3];

   b.AppendFormat( "\ttag[{0},{1},{2}]={3},{4},{5}", offset1, offset2, offset3, f1.common, f2.common, f3.common );
  }

  return;
 }


 

 public bool Sentence2Features( string line )
 {
  // синтаксический разбор в дерево
  using( SolarixGrammarEngineNET.AnalysisResults trees = gren.AnalyzeSyntax( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY, 0 ) )
  {
   // Морфологический разбор
   using( SolarixGrammarEngineNET.AnalysisResults tokens = gren.AnalyzeMorphology( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY ) )
   {
    TreeLookup syntax = new TreeLookup();
    syntax.Collect( tokens, trees, gren );

    if( !syntax.ok )
     return false;

    int N = tokens.Count;

    List<WordTags> tag_index = new List<WordTags>();
    List<string> words = new List<string>();
    List<string> labels = new List<string>();

    WordTags start_t = new WordTags();
    start_t.common = START_id;
    tag_index.Add( start_t );
    words.Add( "<START>" );
    labels.Add( "O" );

    for( int iword = 1; iword < tokens.Count - 1; ++iword )
    {
     SolarixGrammarEngineNET.SyntaxTreeNode token = tokens[iword];
     string word = token.GetWord().ToLower();

     SolarixGrammarEngineNET.SyntaxTreeNode token_prev = tokens[iword - 1];

     WordTags t = new WordTags();

     t.common = tags.MatchTags( tokens[iword], gren );
     t.modality = tags_modality.MatchTags( tokens[iword], gren );
     t.valency = tags_valency.MatchTags( tokens[iword], gren );

     tag_index.Add(t);

     string crf_word = word.Replace( " ", "_" );
     words.Add( crf_word );

     labels.Add( syntax.GetTokenLabel( iword ) );
    }

    WordTags end_t = new WordTags();
    end_t.common = END_id;
    tag_index.Add( end_t );
    words.Add( "<END>" );
    labels.Add( "O" );

    System.Text.StringBuilder b = new System.Text.StringBuilder();

    int last_word_index = tokens.Count - 1;
    for( int iword = 0; iword < tokens.Count; ++iword )
    {
     b.Length = 0;

     string output_label = labels[iword];
     string word = words[iword];

//     PullFeatures1( b, tag_index, iword, -3 );
     PullFeatures1( b, tag_index, iword, -2 );
     PullFeatures1( b, tag_index, iword, -1 );
     PullFeatures1( b, tag_index, iword, 0 );
     PullFeatures1( b, tag_index, iword, 1 );
     PullFeatures1( b, tag_index, iword, 2 );
//     PullFeatures1( b, tag_index, iword, 3 );

//     PullFeatures2( b, tag_index, iword, -3, -2 );
     PullFeatures2( b, tag_index, iword, -2, -1 );
     PullFeatures2( b, tag_index, iword, -1, 0 );
     PullFeatures2( b, tag_index, iword, 0, 1 );
     PullFeatures2( b, tag_index, iword, 1, 2 );
//     PullFeatures2( b, tag_index, iword, 3, 4 );

//     PullFeatures3( b, tag_index, iword, -3, -2, -1 );
     PullFeatures3( b, tag_index, iword, -2, -1, 0 );
     PullFeatures3( b, tag_index, iword, -1, 0, 1 );
     PullFeatures3( b, tag_index, iword, 0, 1, 2 );
//     PullFeatures3( b, tag_index, iword, 1, 2, 3 );

     crf_file.WriteLine( "{0}{1}", output_label, b.ToString() );

     visual_file.WriteLine( "{0}\t{1}\t{2}", word, output_label, tag_index[iword] );
    }

    crf_file.WriteLine( "" );
    visual_file.WriteLine( "" );
   }
  }

  return true;
 }

 public void FinishLearning()
 {
  crf_file.Close();
  crf_file = null;

  visual_file.Close();
  visual_file = null;

  string input_file = null;
  string cmd = null;

  input_file = string.Format( "{0}\\crf_train.txt", System.IO.Directory.GetCurrentDirectory() );
  cmd = string.Format( "{0}\\crfsuite_train.cmd", System.IO.Directory.GetCurrentDirectory() );

  System.Diagnostics.Process p = new System.Diagnostics.Process();
  p.StartInfo.Arguments = input_file;
  p.StartInfo.FileName = cmd;
  bool r = p.Start();
  p.WaitForExit();

  return;
 }

 List<string> test_samples = new List<string>();

 public void Check( string line )
 {
  if( crf_file == null )
  {
   crf_file = new System.IO.StreamWriter( "crf_test.txt" );
   visual_file = new System.IO.StreamWriter( "crf_visual.txt" );
  }

  if( Sentence2Features( line ) )
   test_samples.Add( line );

  return;
 }


 public void FinishTesting( out int total_word_count, out int error_count_with_model )
 {
  total_word_count = 0;
  error_count_with_model = 0;

  crf_file.Close();
  crf_file = null;

  visual_file.Close();
  visual_file = null;

  string input_file = null;
  string output_file = null;
  string cmd = null;

  input_file = string.Format( "{0}\\crf_test.txt", System.IO.Directory.GetCurrentDirectory() );
  output_file = string.Format( "{0}\\test_result.txt", System.IO.Directory.GetCurrentDirectory() );
  cmd = string.Format( "{0}\\crfsuite_test.cmd", System.IO.Directory.GetCurrentDirectory() );

  System.Diagnostics.Process p = new System.Diagnostics.Process();
  p.StartInfo.Arguments = string.Format( "\"{0}\" \"{1}\"", input_file, output_file );
  p.StartInfo.FileName = cmd;
  bool r = p.Start();
  p.WaitForExit();

  System.IO.StreamReader rdr = new System.IO.StreamReader( output_file );

  int n_line = 0;

  while( !rdr.EndOfStream )
  {
   string line = rdr.ReadLine();
   if( line == null )
    break;

   if( line.Length == 0 )
   {
    n_line++;
    continue;
   }

   total_word_count++;

   string[] toks = line.Split( '\t' );
   string required_class = toks[0];
   string model_class = toks[1];

   if( required_class != model_class )
   {
    string sample = test_samples[n_line];
    error_count_with_model++;
   }
  }

  return;
 }

}

