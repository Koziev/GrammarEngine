// CD->07.03.2009
// LC->07.03.2009
// --------------

automat sg
{
 #define JapNumber( Kanji, Hiragana ) \
  #begin 
  entry Kanji : JAP_NUMBER
  {
   JAP_FORM:KANJI { Kanji }
   JAP_FORM:KANA  { Hiragana }
  }
  #end

 /*1*/  JapNumber( 一つ, ひとつ )
 /*2*/  JapNumber( 二つ, ふたつ )
 /*3*/  JapNumber( 三つ, みっつ )
 /*4*/  JapNumber( 四つ, よっつ )
 /*5*/  JapNumber( 五つ, いつつ )
 /*6*/  JapNumber( 六つ, むっつ )
 /*7*/  JapNumber( 七つ, ななつ )
 /*8*/  JapNumber( 八つ, やっつ )
 /*9*/  JapNumber( 九つ, ここのつ )
 /*10*/ JapNumber( 十, とお )
 /*20*/ JapNumber( 二十, はたち )

}

