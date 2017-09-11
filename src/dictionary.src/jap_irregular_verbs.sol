// Неправильные японские глаголы
//
// CD->08.03.2009
// LC->08.05.2011
// --------------

automat sg
{

 entry する : JAP_VERB // делать
 {
  JAP_FORM:KANA
  JAP_VERB_BASE:I          { し   }
  JAP_VERB_BASE:II         { し   }
  JAP_VERB_BASE:III        { する  }
  JAP_VERB_BASE:IV         { すれ  }
  JAP_VERB_BASE:V          { しよう }
  JAP_VERB_BASE:PAST       { した  }
  JAP_VERB_BASE:PARTICIPLE { して  }
  JAP_VERB_BASE:POTENTIAL  { できる }
  JAP_VERB_BASE:CONDITIONAL  { すれば }
 }


 entry 来る : JAP_VERB // приходить
 {
  JAP_FORM:KANJI
  JAP_VERB_BASE:I          { 来   }
  JAP_VERB_BASE:II         { 来   }
  JAP_VERB_BASE:III        { 来る  }
  JAP_VERB_BASE:IV         { 来れ  }
  JAP_VERB_BASE:V          { 来よう }
  JAP_VERB_BASE:PAST       { 来た  }
  JAP_VERB_BASE:PARTICIPLE { 来て  }
  JAP_VERB_BASE:POTENTIAL  { 来られる }
  JAP_VERB_BASE:CONDITIONAL  { 来れば }
 }

 entry くる : JAP_VERB // приходить
 {
  JAP_FORM:KANA
  JAP_VERB_BASE:III        { くる  }
  JAP_VERB_BASE:IV         { くれ  }
  JAP_VERB_BASE:V          { こよう }
  JAP_VERB_BASE:PAST       { きた  }
  JAP_VERB_BASE:PARTICIPLE { きて  }
 }

 entry 行く : JAP_VERB // идти
 {
  JAP_FORM:KANJI
  JAP_VERB_BASE:I          { 行か }
  JAP_VERB_BASE:II         { 行き  }
  JAP_VERB_BASE:III        { 行く  }
  JAP_VERB_BASE:IV         { 行け  }
  JAP_VERB_BASE:V          { 行こう }
  JAP_VERB_BASE:PAST       { 行った }
  JAP_VERB_BASE:PARTICIPLE { 行って }
  JAP_VERB_BASE:POTENTIAL  { 行ける }
  JAP_VERB_BASE:CONDITIONAL  { 行けば }
 }


 // ********************************
 // СВЯЗКА 'ЕСТЬ' - разные формы
 // ********************************
 entry です : JAP_VERB
 {
  JAP_FORM:KANJI

  JAP_VERB_BASE:III { です } // стандартная форма
  JAP_VERB_BASE:III { だ  } // грубая форма

  JAP_VERB_BASE:PAST { でした } // вежливая форма
  JAP_VERB_BASE:PAST { だった } // грубая форма
 }


 // ********************************
 // НЕ СУЩЕСТВУЕТ - разные формы
 // ********************************
 entry じゃない : JAP_VERB
 {
  JAP_FORM:KANJI

  JAP_VERB_BASE:III { ではありません }
  JAP_VERB_BASE:III { じゃありません }
  
  JAP_VERB_BASE:III { ありません }
  JAP_VERB_BASE:III { ないです }

  JAP_VERB_BASE:III { ない   } // грубая форма
  JAP_VERB_BASE:III { ではない } // грубая форма
  JAP_VERB_BASE:III { じゃない } // грубая форма

  
  JAP_VERB_BASE:PAST { ありませんでした }
//  JAP_VERB_BASE:PAST { なかったです   }
//  JAP_VERB_BASE:PAST { ではなかった   }
//  JAP_VERB_BASE:PAST { じゃなかった   }
//  JAP_VERB_BASE:PAST { ではありませんでした }
//  JAP_VERB_BASE:PAST { じゃありませんでした }
  
 }


/*
 // ИМЕЕТСЯ - формы для одушевленных и неодушевленных предметов
 entry あります : JAP_VERB
 {
  JAP_FORM:KANJI

  JAP_VERB_BASE:III { あります }
  JAP_VERB_BASE:III { います }
 }
*/

/*
 entry j_BECOME : JAP_VERB { JAP_FORM:ROMAJI } // для конструкции 'становиться' +に+なる
 entry j_LOVE : JAP_VERB { JAP_FORM:ROMAJI } // для конструкции любить делать что-л.
 entry j_DONTLOVE : JAP_VERB { JAP_FORM:ROMAJI } // для конструкции не любить делать что-л.
 entry j_ABLE : JAP_VERB { JAP_FORM:ROMAJI } // для конструкции 'уметь что-л.'
 entry j_NOTABLE : JAP_VERB { JAP_FORM:ROMAJI } // для конструкции 'не уметь что-л.'
*/ 


 // это регулярный глагол на самом деле
 entry いろ : JAP_VERB
 {
  JAP_FORM:KANA
  JAP_VERB_BASE:I            { "い"    }
  JAP_VERB_BASE:II           { "い"    }
  JAP_VERB_BASE:III          { "いろ"   }
  JAP_VERB_BASE:IV           { "いれ"   }
  JAP_VERB_BASE:V            { "いよう"  }
  JAP_VERB_BASE:PAST         { "いた"   }
  JAP_VERB_BASE:PARTICIPLE   { "いて"   }
  JAP_VERB_BASE:POTENTIAL    { "いられる" }
  JAP_VERB_BASE:CONDITIONAL  { "いれば"  }
 }
}

