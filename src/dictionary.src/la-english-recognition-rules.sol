// Правила несловарной морфологии для английского парсера
// CD->02.04.2011
// LC->17.01.2016

recognition OrdinalNumbers language=English
{
 if "[[:digit:]]*th" then ENG_NUMERAL:"???" { NUMERAL_FORM:ORDINAL }
} 


// 0.001
recognition RealNumber language=English
{
 if "[[:digit:]]*\\.[[:digit:]]+" then ENG_NUMERAL:"???" { NUMERAL_FORM:CARDINAL }
} 

recognition RealNumber language=English
{
 if "[[:digit:]]+\\.[[:digit:]]*" then ENG_NUMERAL:"???" { NUMERAL_FORM:CARDINAL }
} 

// Around 125,000 civilians were killed.
//        ^^^^^^^
recognition RealNumber language=English
{
 if "[[:digit:]]+ \\, [[:digit:]]+" then ENG_NUMERAL:"???" { NUMERAL_FORM:CARDINAL }
} 



// 10x zoom
recognition FoldAdj1 language=English
{
 if "[[:digit:]]+[×x]" then ENG_ADJECTIVE:"???" {}
} 

// 6,000×
recognition FoldAdj2 language=English
{
 if "[[:digit:]]+ , [[:digit:]]+×" then ENG_ADJECTIVE:"???" {}
}

// The eyepiece of a microscope magnifies 10×
//                                        ^^^
recognition FoldAdv1 language=English
{
 if "[[:digit:]]+[×x]" then ENG_ADVERB:"???" { MODIF_TYPE:VERB }
}


// 180°
recognition Grad1 language=English
{
 if "[[:digit:]]+°" then ENG_NOUN:"???" { NUMBER:PLURAL }
}



// Zhuangzi's philosophy has been described by various sources as anarchist.
// ^^^^^^^^
recognition Zhuangzi language=English
{
 if @"[A-Z][a-z]+" then ENG_NOUN:"???" { NUMBER:SINGLE ENG_PROPER_NOUN CHARCASING:FirstCapitalized HAS_POSSESSIVE_FORM }
}

// The Jangil were soon extinct.
//     ^^^^^^
recognition Zhuangzi language=English
{
 if @"[A-Z][a-z]+" then ENG_NOUN:"???" { NUMBER:PLURAL ENG_PROPER_NOUN CHARCASING:FirstCapitalized HAS_POSSESSIVE_FORM }=-1
}


// Barry Bonds won the award three times.
//       ^^^^^
recognition Bonds language=English forced=true
{
 if @"[A-Z][a-z]+" then ENG_NOUN:"???" { NUMBER:SINGLE ENG_PROPER_NOUN CHARCASING:FirstCapitalized HAS_POSSESSIVE_FORM }=-5
}


// MCs are frequently featured in live performances.
// ^^^
recognition MCs language=English forced=true
{
 if @"[A-Z][A-Za-z]*s"
  then ENG_NOUN:"???" { NUMBER:PLURAL ENG_PROPER_NOUN CHARCASING:Upper HAS_POSSESSIVE_FORM }=-5
}


// GM builds battery packs in southern Michigan.
// ^^
recognition GM language=English forced=true
{
 if @"[A-Z]{2,}" then ENG_NOUN:"???" { NUMBER:SINGLE }
}


// Aglaulus demands money in exchange.
// ^^^^^^^^
recognition Aglaulus language=English
{
 if @"[A-Z][a-z]+us" then ENG_NOUN:"???" { NUMBER:SINGLE ENG_PROPER_NOUN CHARCASING:FirstCapitalized HAS_POSSESSIVE_FORM }
}


// Последовательность символов в верхнем регистре очень часто
// является существительным:
// In chemical terms, RNAP is a nucleotidyl transferase.
//                    ^^^^
recognition RNAP language=English
{
 if @"[A-Z]{2,}" then ENG_NOUN:"???" { NUMBER:SINGLE ENG_PROPER_NOUN CHARCASING:FirstCapitalized HAS_POSSESSIVE_FORM }
}


// Одиночный символ:
// C and D do similarly.
// Let m be the magnification;
// Amphotericin B is another option.
recognition a_char language=English
{
 if "[a-z]" then ENG_NOUN:"???" { NUMBER:SINGLE }
}




// Произвольная цепочка символов в роли существительного:
// at the 3' end of an RNA transcript
// -------^^-------------------------
recognition AnyChain language=English
{
 if @".{2,}" then ENG_NOUN:"???" { NUMBER:SINGLE } = -5
}


// 1500s
recognition 1500s language=English
{
 if @"[[:digit:]]{1,4}s" then ENG_NOUN:"???" { NUMBER:PLURAL }
}

// 180°
recognition grad1 language=English
{
 if @"[[:digit:]]+°" then ENG_NOUN:"???" { NUMBER:SINGLE }
}

// 100°f
recognition grad1 language=English
{
 if @"[[:digit:]]+°(F|C)" then ENG_NOUN:"???" { NUMBER:SINGLE }
}

// The euglenozoa are generally accepted as monophyletic.
//     ^^^^^^^^^^
recognition euglenozoa language=English
{
 if @"[A-Za-z]+oa" then ENG_NOUN:"???" { NUMBER:PLURAL }
}

// Продуктивный суффикс -ist
recognition ist language=English
{
 if @"[A-Za-z]+ist" then ENG_NOUN:"???" { NUMBER:SINGLE }
}

recognition ists language=English
{
 if @"[A-Za-z]+ists" then ENG_NOUN:"???" { NUMBER:PLURAL }
}


// Продуктивный суффикс -er/-or
recognition er language=English
{
 if @"[A-Za-z]+(e|o)r" then ENG_NOUN:"???" { NUMBER:SINGLE }
}

recognition ers language=English
{
 if @"[A-Za-z]+(e|o)rs" then ENG_NOUN:"???" { NUMBER:PLURAL }
}


// Герундий
recognition ing_noun language=English
{
 if @"[A-Za-z]+ing" then ENG_NOUN:"???" { NUMBER:SINGLE }
}

recognition ings language=English
{
 if @"[A-Za-z]+ings" then ENG_NOUN:"???" { NUMBER:PLURAL }
}



// -s как общий признак множественного числа
recognition ings language=English
{
 if @"[A-Za-z]+s" then ENG_NOUN:"???" { NUMBER:PLURAL }=-2
}

// Латинские термины на -a:
// Animalia
recognition ia language=English
{
 if @"[A-Za-z]+a" then ENG_NOUN:"???" { NUMBER:SINGLE }
}


// Продуктивный суффикс -tion
recognition tion language=English
{
 if @"[A-Za-z]+tion" then ENG_NOUN:"???" { NUMBER:SINGLE }
}

recognition tions language=English
{
 if @"[A-Za-z]+tions" then ENG_NOUN:"???" { NUMBER:PLURAL }
}



// Продуктивные окончания глаголов
recognition verb_s language=English
{
 if @"[A-Za-z]+s" then ENG_VERB:"???" { VERB_FORM:S }=-2
}

recognition verb_ed language=English
{
 if @"[A-Za-z]+ed" then ENG_VERB:"???" { VERB_FORM:ED }=-2
}

recognition verb_pp language=English
{
 if @"[A-Za-z]+ed" then ENG_VERB:"???" { VERB_FORM:PP }=-2
}

recognition verb_ing language=English
{
 if @"[A-Za-z]+ed" then ENG_VERB:"???" { VERB_FORM:ING }=-2
}

// Продуктивный суффикс -ly для получения наречий
recognition verb_ing language=English
{
 if @"[A-Za-z]+ly" then ENG_ADVERB:"???" { VERB_FORM:ING }=-1
}

// Окончание -ee для существительных
// Caylee
recognition ee language=English
{
 if @"[A-Za-z]+ee" then ENG_NOUN:"???" { NUMBER:SINGLE }
}

recognition ees language=English
{
 if @"[A-Za-z]+ees" then ENG_NOUN:"???" { NUMBER:PLURAL }
}


// -ies
// multiplicities
recognition ian language=English
{
 if @"[A-Za-z]+ies" then ENG_NOUN:"???" { NUMBER:PLURAL }
}


// caymanian
recognition ian language=English
{
 if @"[A-Za-z]+ian" then ENG_NOUN:"???" { NUMBER:SINGLE }
}

recognition ians language=English
{
 if @"[A-Za-z]+ians" then ENG_NOUN:"???" { NUMBER:PLURAL }
}




// Продуктивное окончание -er для компаратива прилагательных
recognition adj_er language=English
{
 if @"[A-Za-z]+er"
  then ENG_ADJECTIVE:"???" { COMPARABILITY:COMPARABLE COMPARABILITY:ANALYTIC ADJ_FORM:COMPARATIVE }
}


// Продуктивное окончание -est для компаратива прилагательных
recognition adj_est language=English
{
 if @"[A-Za-z]+est"
  then ENG_ADJECTIVE:"???" { COMPARABILITY:COMPARABLE COMPARABILITY:ANALYTIC ADJ_FORM:SUPERLATIVE }
}


// Прилагательные на -cal:
// Many brain abscesses are polymicrobical.
//                          ^^^^^^^^^^^^^^
recognition adj_cal language=English
{
 if @"[A-Za-z]+cal"
  then ENG_ADJECTIVE:"???" {}
}

// Spinoza’s second knowledge involves reasoning plus emotions.
// ^^^^^^^^^
recognition Noun_Possessive1 language=English
{
 if @"’s" then ENG_POSSESSION:"'s" {}
}



recognition Shant language=English
{
 if "shan’t" then ENG_AUXVERB:shall_not{ VERB_FORM:UNDEF }
} 


// Paul doesn’t question it in this epistle.
//      ^^^^^^^
recognition doesnt language=English
{
 if "doesn’t" then ENG_VERB:"don't"{ VERB_FORM:S VERB_SLOTS:ModalDirect }
} 

recognition dont language=English
{
 if "don’t" then ENG_VERB:"don't"{ VERB_FORM:S VERB_SLOTS:ModalDirect }
} 

recognition didnt language=English
{
 if "didn’t" then ENG_VERB:"don't"{ VERB_FORM:ED VERB_SLOTS:ModalDirect }
} 


recognition isnt language=English
{
 if "isn’t" then ENG_BEVERB:be_not{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF VERB_SLOTS:COPULATIVE VERB_SLOTS:PastParticiple }
} 

recognition aint language=English
{
 if "ain’t" then ENG_BEVERB:be_not{ PERSON:1 NUMBER:SINGLE VERB_FORM:UNDEF VERB_SLOTS:COPULATIVE VERB_SLOTS:PastParticiple }
} 

/*
unbreakable language=English { "haven't" }
unbreakable language=English { "haven’t" }
unbreakable language=English { "hasn't" }
unbreakable language=English { "hasn’t" }
unbreakable language=English { "hadn't" }
unbreakable language=English { "hadn’t" }
unbreakable language=English { "won't" }
unbreakable language=English { "won’t" }
unbreakable language=English { "isn't" }
unbreakable language=English { "isn’t" }
unbreakable language=English { "aren't" }
unbreakable language=English { "wasn't" }
unbreakable language=English { "wasn’t" }
unbreakable language=English { "weren't" }
unbreakable language=English { "weren’t" }
unbreakable language=English { "can't" }
unbreakable language=English { "can’t" }
unbreakable language=English { "couldn't" }
unbreakable language=English { "couldn’t" }
unbreakable language=English { "mustn't" }
unbreakable language=English { "mustn’t" }
unbreakable language=English { "shouldn't" }
unbreakable language=English { "shouldn’t" }
unbreakable language=English { "wouldn't" }
unbreakable language=English { "wouldn’t" }
*/
