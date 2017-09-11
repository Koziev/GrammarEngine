// CD->07.03.2009
// LC->10.06.2009


#define JapPronoun(x) entry x : JAP_PRONOUN { JAP_PRONOUN_TYPE:POINTING }

automat sg
{
 JapPronoun( これ ) // это
 JapPronoun( それ ) // это, то
 JapPronoun( あれ ) // вон то
 JapPronoun( どれ ) // что? Какой? который?
 JapPronoun( 何 ) // что?
 JapPronoun( なに ) // что?
 JapPronoun( なん ) // что?
 JapPronoun( どなた ) // Кто? (более вежливо)
 JapPronoun( どんな ) // Какой?
 JapPronoun( どこ ) // Где? Какое место?
 JapPronoun( どちら ) // Где? В каком месте? В каком направлении?
 JapPronoun( どの ) // Какой? Который?


 // ****************************
 // ЛИЧНЫЕ МЕСТОИМЕНИЯ
 // ****************************
 entry 私 : JAP_PRONOUN
 {
  JAP_PRONOUN_TYPE:PERSONAL

  JAP_PERSON:1 JAP_NUMBER:SINGULAR { 私 }   // ваташи - я Formal
  JAP_PERSON:1 JAP_NUMBER:SINGULAR { わたし } // я
  JAP_PERSON:1 JAP_NUMBER:SINGULAR { わたくし } // я
  JAP_PERSON:1 JAP_NUMBER:SINGULAR { マンゴ } // я

  JAP_PERSON:1 JAP_NUMBER:SINGULAR JAP_GENDER:MASCULINE { 僕 }   // я 'boku'   Informal / Masculine
  JAP_PERSON:1 JAP_NUMBER:SINGULAR JAP_GENDER:FEMININE { あたし } // я 'atashi' Informal / Feminine
  JAP_PERSON:1 JAP_NUMBER:SINGULAR JAP_GENDER:MASCULINE { 俺 } // я 'ore' Rude - Masculine

  JAP_PERSON:1 JAP_NUMBER:PLURAL { 私達 } // мы 'watakushitachi' Formal 
  JAP_PERSON:1 JAP_NUMBER:PLURAL { 私達 } // мы 'watashitachi' Polite
  JAP_PERSON:1 JAP_NUMBER:PLURAL { 私たち } // ???

  JAP_PERSON:1 JAP_NUMBER:PLURAL JAP_GENDER:MASCULINE { 僕達 }  // мы 'bokutachi' Informal - Masculine
  JAP_PERSON:1 JAP_NUMBER:PLURAL JAP_GENDER:FEMININE { あたし達 } // мы 'atashitachi' Informal - Feminine
  JAP_PERSON:1 JAP_NUMBER:PLURAL JAP_GENDER:MASCULINE { 俺等 }  // мы 'orera' Rude - Masculine

  JAP_PERSON:2 JAP_NUMBER:SINGULAR { あなた } // ты 'anata' Polite
  JAP_PERSON:2 JAP_NUMBER:SINGULAR { 君 } // ты 'kimi' Informal
  JAP_PERSON:2 JAP_NUMBER:SINGULAR JAP_GENDER:MASCULINE { お前 } // ты 'o-mae' Rude - Masculine

  JAP_PERSON:2 JAP_NUMBER:PLURAL { あなた方 } // вы 'anatagata'
  JAP_PERSON:2 JAP_NUMBER:PLURAL { あなた達 } // вы 'anatatachi' Polite
  JAP_PERSON:2 JAP_NUMBER:PLURAL { 君達 } // вы 'kimitachi' Informal
  JAP_PERSON:2 JAP_NUMBER:PLURAL { お前等 } // вы 'o-maera' Rude - Masculine

  JAP_PERSON:3 JAP_NUMBER:SINGULAR JAP_GENDER:MASCULINE { 彼 } // он, его 'kare'
  JAP_PERSON:3 JAP_NUMBER:SINGULAR JAP_GENDER:FEMININE { 彼女 } // 	она, её 'kanojo'
  JAP_PERSON:3 JAP_NUMBER:SINGULAR { あの方 } // он, она, его, ее 'ano kata' Formal
  JAP_PERSON:3 JAP_NUMBER:SINGULAR { あの人 } // он, она, его, ее 'ano hito'
  JAP_PERSON:3 JAP_NUMBER:SINGULAR { あのかた } // он


  JAP_PERSON:3 JAP_NUMBER:PLURAL { あの方々 } // они 'ano katagata' Formal
  JAP_PERSON:3 JAP_NUMBER:PLURAL { あの方達 } // они 'ano katatachi' Formal
  JAP_PERSON:3 JAP_NUMBER:PLURAL { あの人達 } // они 'ano hitotachi'
  JAP_PERSON:3 JAP_NUMBER:PLURAL { 彼等 }   // они 'karera'
  JAP_PERSON:3 JAP_NUMBER:PLURAL JAP_GENDER:FEMININE { 彼女達 }  // они 'kanojotachi' All women
 }


 // *****************************
 // Притяжательные местоимения
 // *****************************
 entry 私の : JAP_PRONOUN
 {
  JAP_PRONOUN_TYPE:POSSESSIVE

  JAP_PERSON:1 JAP_NUMBER:SINGULAR { 私の } // мой 'watakushi no'   my, mine
  JAP_PERSON:1 JAP_NUMBER:SINGULAR { 僕の } // мой 'boku no'        my, mine
  JAP_PERSON:1 JAP_NUMBER:SINGULAR { あたしの } // мой 'atashi no'    my, mine
  JAP_PERSON:1 JAP_NUMBER:SINGULAR { 俺の } // мой 'ore no'         my, mine


  JAP_PERSON:1 JAP_NUMBER:PLURAL { 私達の } // наш  	'watakushitachi no'  	our, ours
  JAP_PERSON:1 JAP_NUMBER:PLURAL { 僕達の } // наш  	'bokutachi no'  	our, ours
  JAP_PERSON:1 JAP_NUMBER:PLURAL { あたし達の } // наш  	'atashitachi no'  	our, ours
  JAP_PERSON:1 JAP_NUMBER:PLURAL { 俺等の } // наш  	'orera no'  		our, ours
  JAP_PERSON:1 JAP_NUMBER:PLURAL { 私たちの }

  JAP_PERSON:2 JAP_NUMBER:SINGULAR { あなたの } // твой 'anata no'  	your, yours
  JAP_PERSON:2 JAP_NUMBER:SINGULAR { 君の } // твой 'kimi no'  	your, yours
  JAP_PERSON:2 JAP_NUMBER:SINGULAR { お前の } // твой 'o-mae no'  	your, yours

  JAP_PERSON:2 JAP_NUMBER:PLURAL { あなた方の } // ваш 	'anatagata no'  	your, yours
  JAP_PERSON:2 JAP_NUMBER:PLURAL { あなた達の } // ваш	'anatatachi no'  	your, yours
  JAP_PERSON:2 JAP_NUMBER:PLURAL { 君達の } // ваш 	'kimitachi no'  	your, yours
  JAP_PERSON:2 JAP_NUMBER:PLURAL { お前等の } // ваш	'o-maera no'  	your, yours
  JAP_PERSON:2 JAP_NUMBER:PLURAL { あなたがたの }

  JAP_PERSON:3 JAP_NUMBER:SINGULAR { あの方の } // его/ее 'ano kata no' his/her, hers
  JAP_PERSON:3 JAP_NUMBER:SINGULAR { あの人の } // его/ее  'ano hito no' his/her, hers
  JAP_PERSON:3 JAP_NUMBER:SINGULAR { 彼の }   // его 'kare no' his
  JAP_PERSON:3 JAP_NUMBER:SINGULAR { 彼女の }  // его/ее  'kanojo no' her, hers

  JAP_PERSON:3 JAP_NUMBER:PLURAL { あの方々の } //  	их 'ano katagata no'  	their, theirs
  JAP_PERSON:3 JAP_NUMBER:PLURAL { あの方達の } //  	их 'ano katatachi no'  	their, theirs
  JAP_PERSON:3 JAP_NUMBER:PLURAL { あの人達の } //  	их 'ano hitotachi no'  	their, theirs
  JAP_PERSON:3 JAP_NUMBER:PLURAL { 彼等の } //  	их 'karera no'  	their, theirs
  JAP_PERSON:3 JAP_NUMBER:PLURAL { 彼女達の } //  	их 'kanojotachi no'  	their, theirs
  JAP_PERSON:3 JAP_NUMBER:PLURAL { あの人たちの }
  JAP_PERSON:3 JAP_NUMBER:PLURAL { あの方がたの }
 }

}
