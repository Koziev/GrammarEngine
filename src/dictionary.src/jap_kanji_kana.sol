// CD->29.01.2010
// LC->18.04.2010

#define NounKanjiKana( a, b ) \
 #begin
  link JAP_NOUN:a{} <to_kana> JAP_NOUN:b{}
  link JAP_NOUN:b{} <to_kanji> JAP_NOUN:a{}
 #end 

automat sg
{
 NounKanjiKana( 計算機, コンピューター )

}


