using System.Linq;
using System.Collections.Generic;



class AdjacentMatrix
{
 private TagBook tags;

 bool IsUnknownLexem( string s )
 {
  return s.Equals( "UNKNOWNENTRY", System.StringComparison.InvariantCultureIgnoreCase ) ||
         s == "???" ||
         s.Equals( "number_", System.StringComparison.InvariantCultureIgnoreCase );
 }

 public AdjacentMatrix()
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
СОЮЗ
ЧАСТИЦА
ПУНКТУАТОР
НАРЕЧИЕ
BETH:BEGIN{}
BETH:END{}
";

  tags.Load( str_tags, gren );

  return;
 }

 int n_learn_samples = 0;

 public bool ProcessSample( string line )
 {
  // синтаксический разбор в дерево
  SolarixGrammarEngineNET.AnalysisResults trees = gren.AnalyzeSyntax( line, LanguageID, SolarixGrammarEngineNET.GrammarEngine.MorphologyFlags.SOL_GREN_COMPLETE_ONLY, SolarixGrammarEngineNET.GrammarEngine.SyntaxFlags.SOL_GREN_REORDER_TREE );

  Collect( trees );

  return true;
 }

 string GetNodeNonterminal( SolarixGrammarEngineNET.SyntaxTreeNode node )
 {
  string res=string.Empty;

  int e1 = node.GetEntryID();
  int c1 = gren.GetEntryClass( e1 );

  if( c1==SolarixGrammarEngineNET.GrammarEngineAPI.NOUN_ru || c1==SolarixGrammarEngineNET.GrammarEngineAPI.PRONOUN_ru || c1==SolarixGrammarEngineNET.GrammarEngineAPI.PRONOUN2_ru )  
   {
    int id_case = node.GetCoordState( SolarixGrammarEngineNET.GrammarEngineAPI.CASE_ru );
    string case_str=string.Empty;
    switch(id_case)
    {
     case SolarixGrammarEngineNET.GrammarEngineAPI.NOMINATIVE_CASE_ru: case_str="им"; break;
     case SolarixGrammarEngineNET.GrammarEngineAPI.INSTRUMENTAL_CASE_ru: case_str="твор"; break;
     case SolarixGrammarEngineNET.GrammarEngineAPI.GENITIVE_CASE_ru: case_str="род"; break;
     case SolarixGrammarEngineNET.GrammarEngineAPI.ACCUSATIVE_CASE_ru: case_str="вин"; break;
     case SolarixGrammarEngineNET.GrammarEngineAPI.DATIVE_CASE_ru: case_str="дат"; break;
    }

    res = string.Format( "Сущ_{0}", case_str );
   }
  else if( c1==SolarixGrammarEngineNET.GrammarEngineAPI.ADJ_ru )
   {
    int id_case = node.GetCoordState( SolarixGrammarEngineNET.GrammarEngineAPI.CASE_ru );
    string case_str=string.Empty;
    switch(id_case)
    {
     case SolarixGrammarEngineNET.GrammarEngineAPI.NOMINATIVE_CASE_ru: case_str="им"; break;
     case SolarixGrammarEngineNET.GrammarEngineAPI.INSTRUMENTAL_CASE_ru: case_str="твор"; break;
     case SolarixGrammarEngineNET.GrammarEngineAPI.GENITIVE_CASE_ru: case_str="род"; break;
     case SolarixGrammarEngineNET.GrammarEngineAPI.ACCUSATIVE_CASE_ru: case_str="вин"; break;
     case SolarixGrammarEngineNET.GrammarEngineAPI.DATIVE_CASE_ru: case_str="дат"; break;
    }

    res = string.Format( "Прил_{0}", case_str );
   }
  else if( c1==SolarixGrammarEngineNET.GrammarEngineAPI.ADVERB_ru )
   {
    res = string.Format( "Наречие_{0}", node.GetWord() );
   }
  else if( c1==SolarixGrammarEngineNET.GrammarEngineAPI.PREPOS_ru )
   {
    res = string.Format( "Предлог_{0}", node.GetWord() );
   }
  else if( c1==SolarixGrammarEngineNET.GrammarEngineAPI.PARTICLE_ru )
   {
    res = string.Format( "Частица_{0}", node.GetWord() );
   }
  else if( c1==SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru )
   {
    res = string.Format( "Инф_{0}", node.GetWord() );
   }
  else if( c1==SolarixGrammarEngineNET.GrammarEngineAPI.PUNCTUATION_class )
   {
    res = string.Empty;
   }
  else if( c1==SolarixGrammarEngineNET.GrammarEngineAPI.CONJ_ru )
   {
    res = string.Empty;
   }
  else
   {
    res = string.Empty;
   }

  return res;
 }


 Dictionary<string, int> biword = new Dictionary<string, int>();

 Dictionary<string, int> verb_pattern = new Dictionary<string,int>();

 private void ProcessTree( SolarixGrammarEngineNET.SyntaxTreeNode node )
 {
  string word1 = node.GetWord().ToUpper();

  int e1 = node.GetEntryID();
  int c1 = gren.GetEntryClass( e1 );
  if(
     c1 == SolarixGrammarEngineNET.GrammarEngineAPI.VERB_ru ||
     c1 == SolarixGrammarEngineNET.GrammarEngineAPI.INFINITIVE_ru ||
     c1 == SolarixGrammarEngineNET.GrammarEngineAPI.IMPERSONAL_VERB_ru
    )
  {
   string ename1 = gren.GetEntryName(e1);
   
   System.Text.StringBuilder b = new System.Text.StringBuilder();
   b.AppendFormat( "{0}", ename1 );

   if( node.leafs.Count>0 )
    {
     b.Append( "(" );

     for( int ileaf = 0; ileaf < node.leafs.Count; ++ileaf )
      {
       SolarixGrammarEngineNET.SyntaxTreeNode leaf = node.leafs[ileaf];
       string s = GetNodeNonterminal( leaf );

       if( !string.IsNullOrEmpty(s) )
        b.AppendFormat( " {0}", s );
      }

     b.Append( " )" );
    }

   string str = b.ToString();

   int f = 0;
   if( verb_pattern.TryGetValue( str, out f ) )
    verb_pattern[str] = f+1;
   else
    verb_pattern.Add( str, 1 );
  }

  for( int ileaf = 0; ileaf < node.leafs.Count; ++ileaf )
  {
   SolarixGrammarEngineNET.SyntaxTreeNode leaf = node.leafs[ileaf];

   int e2 = leaf.GetEntryID();
   int c2 = gren.GetEntryClass( e2 );
   if( c2 != SolarixGrammarEngineNET.GrammarEngineAPI.PUNCTUATION_class )
   {
    string word2 = leaf.GetWord().ToUpper();

    string w2 = string.Format( "{0}+{1}", word1, word2 );
    int f = 0;
    if( biword.TryGetValue( w2, out f ) )
     biword[w2] = f + 1;
    else
     biword.Add( w2, 1 );
   }

   ProcessTree( leaf );
  }

  return;
 }

 public void Collect( SolarixGrammarEngineNET.AnalysisResults trees )
 {
  for( int iroot = 1; iroot < trees.Count - 1; ++iroot )
   ProcessTree( trees[iroot] );

  return;
 }

 public void FinishLearning()
 {
  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "biwords.txt" ) )
  {
   foreach( KeyValuePair<string, int> x in biword.ToArray().OrderByDescending( z => z.Value ) )
   {
    wr.WriteLine( "{0} = {1}", x.Key, x.Value );
   }

   wr.Close();
  }


  using( System.IO.StreamWriter wr = new System.IO.StreamWriter( "verb_patterns.txt" ) )
  {
   foreach( KeyValuePair<string, int> x in verb_pattern.ToArray().OrderByDescending( z => z.Value ) )
   {
    wr.WriteLine( "{0} = {1}", x.Key, x.Value );
   }

   wr.Close();
  }


  return;
 }


 public void Check( string line )
 {

  return;
 }

}

