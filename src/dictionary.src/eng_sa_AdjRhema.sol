// --------------------------------------------------------------------
// Предикативные прилагательные, соединяющиеся со связочными глаголами
// --------------------------------------------------------------------


// TODO: переделаить на восходящую сборку восходящих конструкций

patterns AdjRhema0 { language=English } export { node:root_node ADJ_SLOTS ADJ_FORM }

// I am happy
//      ^^^^^
// Bismuthides are not even wholly ionic;
//                                 ^^^^^
pattern AdjRhema0
{
 CompoundAdjective{ [-1]EngPredicativeAdjs }:export { node:root_node ADJ_SLOTS ADJ_FORM }
}

// Berkman pleaded not guilty to all charges.
//                 ^^^^^^^^^^
pattern AdjRhema0
{
 n=eng_particle:not{}
 a=CompoundAdjective{ [-1]EngPredicativeAdjs } : export { node:root_node ADJ_SLOTS ADJ_FORM }
}
: links { a.<NEGATION_PARTICLE>n }
: ngrams { -2 }



// Organically certified berries are becoming more widely available.
//                                            ^^^^^^^^^^^
// He is slightly mad
//       ^^^^^^^^
pattern AdjRhema0
{
 adv=AdvModifier4Adj
 adj=CompoundAdjective{ adj_form:basic [-1]EngPredicativeAdjs }:export { node:root_node ADJ_SLOTS ADJ_FORM }
}
: links { adj.<ATTRIBUTE>adv }
: ngrams
{
 1
 eng_adv_adj_score( adv, adj )
}


// She is much faster 
pattern AdjRhema0
{
 adv=eng_adverb:much{}
 adj=CompoundAdjective{ adj_form:comparative [-1]EngPredicativeAdjs }:export { node:root_node ADJ_SLOTS ADJ_FORM }
} : links { adj.<ATTRIBUTE>adv }


// He was recognizably slimmer now.
pattern AdjRhema0
{
 adv=AdvModifier4Adj
 adj=CompoundAdjective{ adj_form:comparative [-1]EngPredicativeAdjs }:export { node:root_node ADJ_SLOTS ADJ_FORM }
} : links { adj.<ATTRIBUTE>adv }



// He is good enough
//       ^^^^^^^^^^^
pattern AdjRhema0
{
 a=CompoundAdjective{ adj_form:basic AdjWithEnoughPostfix [-1]EngPredicativeAdjs }:export { node:root_node ADJ_SLOTS ADJ_FORM }
 a2=eng_adverb:enough{}
} : links { a.<ATTRIBUTE>a2 }


// --------------------------------------------------------------
// аналитическая сравнительная степень прилагательного в реме:
// --------------------------------------------------------------

patterns CompPrefix export { node:root_node }

pattern CompPrefix
{
 eng_adverb:more{} : export { node:root_node }
}


// The orbit of Earth is less circular than the orbit of a comet.
//                       ^^^^
pattern CompPrefix
{
 eng_adverb:little{ ADJ_FORM:COMPARATIVE } : export { node:root_node }
}



// This language is more popular
pattern AdjRhema0
{
 adv=CompPrefix
 adj=CompoundAdjective{ adj_form:basic comparability:analytic [-1]EngPredicativeAdjs }:export { node:root_node ADJ_SLOTS ADJ_FORM:COMPARATIVE }
} : links { adj.<ATTRIBUTE>adv }


// This language is significantly more popular
pattern AdjRhema0
{
 adv0=Adv4CompAdj{adj_form:basic}
 adv=CompPrefix
 adj=CompoundAdjective{ adj_form:basic comparability:analytic [-1]EngPredicativeAdjs }:export { node:root_node ADJ_SLOTS ADJ_FORM:COMPARATIVE }
}
: links { adj.<ATTRIBUTE>adv.<ATTRIBUTE>adv0 }
: ngrams { eng_adv_adv_score(adv0,adv) }



// ---------------------------------------------------------------------

// С присоединенными правыми элементами

pattern AdjRhema1
{
 AdjRhema0 : export { node:root_node }
}

// Farmers were unable to pay their debts.
//              ^^^^^^^^^^^^^^^^^^^^^^^^^
pattern AdjRhema1
{
 a=AdjRhema0{ ADJ_FORM:BASIC ADJ_SLOTS:Modal } : export { node:root_node }
 inf=InfinitiveGroup
} : links { a.<INFINITIVE>inf }


// Tom is taller than Richard
pattern AdjRhema1
{
 a=AdjRhema0{ ADJ_FORM:COMPARATIVE } : export { node:root_node }
 conj=eng_conj:than{}
 obj=ComparativeObj
}
: links { a.<RIGHT_COMPARISON_Y>conj.<OBJECT>obj }
: ngrams { 1 }


// ---------------------------------------------------------------------
// Элективная конструкция
// Brian was the 10th of 11 children.
//               ^^^^^^^^^^^^^^^^^^^
pattern AdjRhema1
{
 d=eng_article:the{}
 n=OrdinalNumber : export { node:root_node }
 p=eng_prep:of{}
 tail=ElectiveTail
}
: links { n.{ <ATTRIBUTE>d <PREPOS_ADJUNCT>p.<OBJECT>tail } }
: ngrams { 1 }


// Its chemistry was different than the bedrocks.
//                   ^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern AdjRhema1
{
 a=AdjRhema0 : export { node:root_node }
 c=eng_conj:than{}
 n=DirectObj
} : links { a.<RIGHT_COMPARISON_Y>c.<NEXT_COLLOCATION_ITEM>n }



// ---------------------------------------------------------------------


pattern AdjRhema1
{
 PPAsAdjRhema : export { node:root_node }
}


// ---------------------------------------------------------------------

pattern AdjRhema
{ AdjRhema1:export { node:root_node } }


// This book is mine
// These books are mine
pattern AdjRhema
{ eng_pronoun:I{ NOUN_FORM:POSSESSIVE PRONOUN_FORM:POST }:export { node:root_node } }


// We are the best, aren't we?
pattern AdjRhema
{
 det=eng_article:the{}
 a=CompoundAdjective{ adj_form:superlative SuperlativePredicativeAdv } : export { node:root_node }
} : links { a.<ATTRIBUTE>det }


wordentry_set AdjConj={
 eng_conj:or{},
 eng_conj:and{},
 eng_conj:plus{},
 eng_conj:but{},
 eng_conj:versus{},
 eng_conj:vs{}
} 


// We are tired and hungry
// The signal was weak or noisy
// It was very stable but extremely expensive.
//        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// The anecdotes are literary, and late;
pattern AdjRhema
{
 a1=AdjRhema0:export { node:root_node }
 comma=@optional(',')
 conj=AdjConj
 a2=AdjRhema0
} : links
{
 a1.<RIGHT_LOGIC_ITEM>conj.{ ~<PUNCTUATION>comma <NEXT_COLLOCATION_ITEM>a2 }
}




pattern AdjRhema
{
 eng_numeral:*{ numeral_form:cardinal }:export { node:root_node }
}


// The roles are but three;
//               ^^^^^^^^^
pattern AdjRhema
{
 mod=eng_adverb:*{ MODIF_TYPE:NUMBER }
 n=eng_numeral:*{ numeral_form:cardinal }:export { node:root_node }
} : links { n.<ATTRIBUTE>mod }



// This device is byte oriented
// This makes sense because many devices are byte oriented
pattern AdjRhema
{
 n=eng_noun:*{ number:single }:export { node:root_node }
 a=eng_verb:*{ verb_form:pp n_pp(n,_) }
} : links { n.<ATTRIBUTE>a }


// This is the best of the three knives
pattern AdjRhema
{
 det=eng_article:the{}
 a=eng_adjective:*{ adj_form:superlative } : export { node:root_node }
 prep=eng_prep:of{}
 n=PreposObject
} : links { a.{
               <ATTRIBUTE>det
               <OBJECT>prep.<NEXT_COLLOCATION_ITEM>n
              } }

/*
// Tom is the oldest of the three
pattern AdjRhema
{
 det=eng_article:the{}
 a=eng_adjective:*{ adj_form:superlative } : export { node:root_node }
 prep=eng_prep:of{}
 det2=eng_article:the{}
 c=eng_numeral:*{ ~OneNumberFilter }
} : links { a.{
               <ATTRIBUTE>det
               <OBJECT>prep.<NEXT_COLLOCATION_ITEM>c.<ATTRIBUTE>det2
              } }
*/

pattern AdjRhema 
{
 Adj_WithPreposAdjunct : export { node:root_node }
}

/*
// The situation is getting more serious.
// It must be getting more serious.
pattern AdjRhema
{
 v="getting"{ class:eng_verb verb_form:ing }:export{node:root_node}
 a=AdjRhema0
} : links { v.<ATTRIBUTE>a }
*/

// -----------------------------------------------------
// Союзные паттерны для предикативных прилагательных.
// -----------------------------------------------------

// His gratitude was simple and touching.
pattern AdjRhema
{
 a1=AdjRhema0:export { node:root_node }
 conj=eng_conj:and{}
 a2=AdjRhema0
} : links { a1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }

// Many routes are unsafe or disrupted.
pattern AdjRhema
{
 a1=AdjRhema0:export { node:root_node }
 conj=eng_conj:or{}
 a2=AdjRhema0
} : links { a1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }

// Acrylic blankets are both warm and washable.
pattern AdjRhema
{
 conj1=eng_conj:both{}
 a1=AdjRhema0:export { node:root_node }
 conj2=eng_conj:and{}
 a2=AdjRhema0
} : links
{
 a1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>conj2.
      <NEXT_COLLOCATION_ITEM>a2
    }
}

// effective, but cancelled
pattern AdjRhema
{
 a1=AdjRhema0:export { node:root_node }
 comma=','
 conj=eng_conj:but{}
 a2=AdjRhema0
} : links { a1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }


pattern AdjRhema
{
 YearsOldAdj : export { node:root_node }
}

