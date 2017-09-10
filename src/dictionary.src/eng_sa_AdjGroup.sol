
// -------------- PRENOMINAL ADJECTIVES -----------------


patterns CompoundAdjective export { node:root_node ADJ_FORM COMPARABILITY ADJ_SLOTS }

pattern CompoundAdjective
{
 eng_adjective:*{} : export { node:root_node ADJ_FORM COMPARABILITY ADJ_SLOTS }
}

// Составные прилагательные:
// Non-overlapping magisteria.
// ^^^^^^^^^^^^^^^
pattern CompoundAdjective
{
 p=eng_compound_preadj:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 a=eng_adjective:*{} : export { node:root_node ADJ_FORM COMPARABILITY ADJ_SLOTS }
} : links { a.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }


// Artistic revolution and cultural/political revolutions.
//                         ^^^^^^^^^^^^^^^^^^
pattern CompoundAdjective
{
 p=eng_adjective:*{}
 t='/'
 a=eng_adjective:*{} : export { node:root_node ADJ_FORM COMPARABILITY ADJ_SLOTS }
} : links { a.<RIGHT_LOGIC_ITEM>t.<NEXT_COLLOCATION_ITEM>p }


// Arubus is a government-owned bus company.
//             ^^^^^^^^^^^^^^^^
// List of spaceflight-related accidents and incidents.
//         ^^^^^^^^^^^^^^^^^^^
pattern CompoundAdjective
{
 p=eng_noun:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 a=eng_adjective:*{} : export { node:root_node ADJ_FORM COMPARABILITY ADJ_SLOTS }
}
: links { a.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }
: ngrams { -1 }


// Highest-grossing Australian films.
// ^^^^^^^^^^^^^^^^
pattern CompoundAdjective
{
 p=eng_adverb:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 a=eng_adjective:*{} : export { node:root_node ADJ_FORM COMPARABILITY ADJ_SLOTS }
} : links { a.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }



// The flight feathers are brownish-black.
//                         ^^^^^^^^^^^^^^
pattern CompoundAdjective
{
 p=eng_adjective:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 a=eng_adjective:*{} : export { node:root_node ADJ_FORM COMPARABILITY ADJ_SLOTS }
} : links { a.<RIGHT_LOGIC_ITEM>t.<NEXT_COLLOCATION_ITEM>p }



pattern CompoundAdjective
{
 q1=OpeningQuote
 n=CompoundAdjective : export { node:root_node ADJ_FORM COMPARABILITY ADJ_SLOTS }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}

// Одиночная открывающая кавычка в случаях, когда вторая кавычка стоит после финальной точки:
// Philosophers call such propositions "analytic."
//                                     ^^^^^^^^^
pattern CompoundAdjective
{
 q1=OpeningQuote
 n=CompoundAdjective : export { node:root_node ADJ_FORM COMPARABILITY ADJ_SLOTS }
}
: links { n.<PREPEND_QUOTE>q1 }
: ngrams { -1 }

  
// Nodtveidt received a 10-year sentence.
//                      ^^^^^^^
pattern CompoundAdjective export { node:root_node ADJ_FORM COMPARABILITY (ADJ_SLOTS) }
{
 q=num_word:*{} : export { node:root_node ADJ_FORM:BASIC COMPARABILITY:NONCOMPARABLE }
 t='-'
 n=TimeWord
} : links { q.<NEXT_COLLOCATION_ITEM>t.<NEXT_COLLOCATION_ITEM>n }


// -------------------------------------------------------------------------




patterns PreposObject export { node:root_node }


wordentry_set AdjAsIdentifier = {
                                 eng_adjective:this{},
                                 eng_adjective:that{},
                                 eng_adjective:these{},
                                 eng_adjective:those{},
                                 eng_adjective:another{},
                                 eng_adjective:many{},
                                 eng_adjective:every{},
                                 eng_adjective:each{},
                                 eng_adjective:some{}
                                }

patterns AttributiveAdj0 { language=English } export { node:root_node }

// Обычные прилагательные в положительной степени обычно могут атрибутировать существительное,
// за исключением небольшого количества особых случаев.
//
// White rabbit lives in the forest.
//       ^^^^^^
pattern AttributiveAdj0
{
 CompoundAdjective{ adj_form:basic /*[-5]~AdjAsIdentifier [-5]~CannotBePrenominalAdj*/ }:export{node:root_node}
}


// наречие в качестве модификатора атрибутивного прилагательного:
//
// He received a somewhat haphazard schooling. 
//               ^^^^^^^^^^^^^^^^^^
pattern AttributiveAdj0
{
 adv=AdvModifier4Adj
 adj=CompoundAdjective{ adj_form:basic [-1]EngAdjByAdv [-5]~AdjAsIdentifier [-5]~CannotBePrenominalAdj }:export{node:root_node}
}
: links { adj.<ATTRIBUTE>adv }
: ngrams { eng_adv_adj_score(adv,adj) }



// Наречие-модификатор enough справа от модифицируемого прилагательного:
// He is a good enough player.	
//         ^^^^^^^^^^^
pattern AttributiveAdj0
{
 a=CompoundAdjective{ adj_form:basic AdjWithEnoughPostfix }:export{node:root_node}
 a2=eng_adverb:enough{}
}
: links { a.<ATTRIBUTE>a2 }
: ngrams { eng_adv_adj_score(a2,a) }



// Некоторые причастия также могут атрибутировать существительное, но из-за ограничений на
// возможность использования запятых в цепочках я выделяю их в отдельную категорию.

patterns ParticipleAsAdj0 { language=English } export { node:root_node }


// причастие прошедшего времени в роли прилагательного
// I found the broken unit
//             ^^^^^^
// Prostheses are technically the complete finished item.
//                                         ^^^^^^^^
pattern ParticipleAsAdj0
{
 CompoundVerb{ VERB_FORM:PP [-1]PPAsAdjModif ~SpecialVerbs [-5]TRANSITIVITY:TRANSITIVE }:export{node:root_node}
}


// Completely broken windows must be repaired
// ^^^^^^^^^^^^^^^^^
// The most densely inhabited area is Flanders.
//     ^^^^^^^^^^^^^^^^^^^^^^
pattern ParticipleAsAdj0
{
 adv=AdvGroup{ [-2]MODIF_TYPE:VERB }
 v=CompoundVerb{ VERB_FORM:PP [-1]PPAsAdjModif ~SpecialVerbs }:export{node:root_node}
}
: links { v.<ATTRIBUTE>adv }
: ngrams { eng_adv_adj_score( adv, v ) }



// Причастия настоящего времени от непереходных глаголов могут выступать в роли прилагательных,
// атрибутирующих существительные.
// I see the sleeping child
pattern ParticipleAsAdj0
{
 CompoundVerb{ VERB_FORM:ING [-5]~TRANSITIVITY:TRANSITIVE ~IngVerbCantBeAdj }:export{node:root_node}
}



// Fastly running cat catches the mice
// ^^^^^^^^^^^^^^
pattern ParticipleAsAdj0
{
 adv=AdvLeftModifier4Verb
 v=eng_verb:*{ VERB_FORM:ING [-5]~TRANSITIVITY:TRANSITIVE ~IngVerbCantBeAdj }:export{node:root_node}
}
: links { v.<ATTRIBUTE>adv }
: ngrams { eng_adv_v_score( adv, v ) }


// ---------------------------------------------------------------

// Компаратив прилагательного
patterns AdjComparative0 { language=English }

// He is smarter
//       ^^^^^^^
pattern AdjComparative0 export { node:root_node }
{ eng_adjective:*{ adj_form:comparative }:export{node:root_node} }

// He is more accurate
//       ^^^^^^^^^^^^^
pattern AdjComparative0 export { node:root_node }
{
 aux=eng_adverb:more{}
 a=eng_adjective:*{ adj_form:basic COMPARABILITY:ANALYTIC }:export{node:root_node}
} : links { a.<ATTRIBUTE>aux }


// It is much bigger
//       ^^^^^^^^^^^
pattern AdjComparative0 export { node:root_node }
{
 adv=eng_adverb:*{ [-5]Adv4CompAdj }
 adj=eng_adjective:*{ adj_form:comparative }:export{node:root_node}
} : links { adj.<ATTRIBUTE>adv }


// -------------------------------------------------

patterns AttrAdj0 { language=English } export { node:root_node }

pattern AttrAdj0
{
 AttributiveAdj0:export{node:root_node}
}

// Компаратив прилагательного в роли левого атрибута существительного:
// Four smaller domes flank the main dome.
//      ^^^^^^^
pattern AttrAdj0
{
 AdjComparative0:export{node:root_node}
}



pattern AttrAdj0
{
 ParticipleAsAdj0:export{node:root_node}
}




// your guess is as good as mine
// ^^^^
pattern AttrAdj0
{
 PronounGroup{ NOUN_FORM:POSSESSIVE PRONOUN_FORM:PRE }:export{node:root_node}
}

// It is an 800 years old temple.
//          ^^^^^^^^^^^^^
// 32-years old Melissa Lawson won.
// ^^^^^^^^^^^^
pattern AttrAdj0
{
 YearsOldAdj : export { node:root_node }
}





// -------------------------------------------------------

// Восходящая сборка атрибутивной группы

patterns PrenominalAdjUp { bottomup language=English }
export
{
 KEYFEATURE_DETECTED // есть союзный паттерн или перечисление через запятую
 KEYFEATURE_REQUIRED // =0 присоединено хотя бы одно прилагательное или причастие
 KEYFEATURE_DESIRABLE // есть союз
 node:root_node
}

// Затравочный элемент
pattern PrenominalAdjUp
{
 AttrAdj0:export{ KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED:1 KEYFEATURE_DESIRABLE:0 node:root_node }
}



// Присоединяем элемент через запятую:
// a red, white and blue flag
pattern PrenominalAdjUp
{
 n1=PrenominalAdjUp:export{ KEYFEATURE_DESIRABLE:0 node:root_node }
 comma=',' : export { KEYFEATURE_DETECTED:1 }
 n2=AttrAdj0:export { KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }


wordentry_set PrenomialAdjConj=
{
 eng_conj:or{}, // A feudal or ritualistic society
 eng_conj:but{}, // A large but wieldy book.
 eng_conj:and{}, // A litigious and acrimonious spirit.
 eng_conj:rather than{}, // Chordal rather than contrapuntal music.
 eng_conj:"vs."{}, // Wet vs. dry systems.
 eng_conj:versus{}, // Linear versus nonlinear control theory.
 eng_conj:vs{}

}

// Присоединяем элемент через союз:
pattern PrenominalAdjUp
{
 n1=PrenominalAdjUp:export { node:root_node }
 conj=PrenomialAdjConj : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=AttrAdj0:export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 1 }


// Yellow indicates acceptable but not ideal cases.
//                  ^^^^^^^^^^^^^^^^^^^^^^^^
pattern PrenominalAdjUp
{
 n1=PrenominalAdjUp:export { node:root_node }
 conj=eng_conj:but{} : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n=eng_particle:not{}
 n2=AttrAdj0:export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2.<NEGATION_PARTICLE>n }
: ngrams { 1 }



// Финальный нетерминал - группа прилагательного в роли левого определения существительного
patterns PrenominalAdjGroup { language=English } export { node:root_node }

// Одиночное прилагательное:
pattern PrenominalAdjGroup
{
 AttrAdj0 : export { node:root_node }
}

// В группу входит минимум одно прилагательное и есть союзы:
pattern PrenominalAdjGroup
{
 n=PrenominalAdjUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:1 }:export{ node:root_node }
}


// Особо рассматриваем группу из нескольких прилагательных, связанных
// без использования союза. Небольшой штраф дает преимущество союзным конструкциям.
// They live in a big, red house
//                ^^^^^^^^
pattern PrenominalAdjGroup
{
 n=PrenominalAdjUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:0 }:export{ node:root_node }
} : ngrams { -1 }


// It experiences both tangential and centripetal acceleration.
//                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern PrenominalAdjGroup
{
 c1=eng_conj:both{}
 n1=PrenominalAdjGroup:export{ node:root_node }
 c2=eng_conj:and{}
 n2=PrenominalAdjGroup
}
: links { n1.{ <PREFIX_CONJUNCTION>c1 <RIGHT_LOGIC_ITEM>c2.<NEXT_COLLOCATION_ITEM>n2 } }
: ngrams { 1 }


// ------------------------------------------------------------------



// ------------------------------------------------------------------

// Группа компаративов может быть нужна для некоторых конструкций типа:

patterns AdjComparative2 export { node:root_node }

pattern AdjComparative2
{
 AdjComparative0 : export { node:root_node }
} 



// ------------------------------------------------------------------

patterns AdjSuperlative0 { language=English }


pattern AdjSuperlative0 export { node:root_node }
{ eng_adjective:*{ adj_form:superlative }:export{node:root_node} }

pattern AdjSuperlative0 export { node:root_node }
{
 aux=eng_adverb:most{}
 a=eng_adjective:*{ adj_form:basic COMPARABILITY:ANALYTIC }:export{node:root_node}
} : links { a.<ATTRIBUTE>aux }


pattern AdjSuperlative0 export { node:root_node }
{
 adv=eng_adverb:*{ [-5]Adv4CompAdj }
 adj=eng_adjective:*{ adj_form:superlative }:export{node:root_node}
} : links { adj.<ATTRIBUTE>adv }

// ---------------------------------------------

patterns AdjSuperlative2 export { node:root_node }

pattern AdjSuperlative2
{
 AdjSuperlative0 : export { node:root_node }
} 

// It became their biggest commercial success thus far.
//                 ^^^^^^^
pattern PrenominalAdjGroup
{
 AdjSuperlative2 : export { node:root_node }
}


// ------------------------------------------------------------------

// Восходящая сборка группы прилагательного


patterns AdjGroupItem { language=English } export { node:root_node }


pattern AdjGroupItem
{
 AttrAdj0 : export { node:root_node }
}

pattern AdjGroupItem
{
 AdjComparative0 : export { node:root_node }
}


pattern AdjGroupItem
{
 AdjSuperlative0 : export { node:root_node }
}


// включая прилагательное с правым предложным дополнением ...
patterns Adj_WithPreposAdjunct { language=English } export { node:root_node }


pattern AdjGroupItem
{
 Adj_WithPreposAdjunct : export { node:root_node }
}


// Nothing interesting has happened since we parted.
// ^^^^^^^^^^^^^^^^^^^
pattern AdjGroupItem
{
 n=eng_noun:nothing{} : export{node:root_node}
 a=eng_adjective:*{}
} : links { n.<ATTRIBUTE>a }


// At first he didn't notice anything strange.
pattern AdjGroupItem
{
 n=eng_noun:anything{}:export{node:root_node}
 a=eng_adjective:*{ adj_form:basic }
} : links { n.<ATTRIBUTE>a } 


// ------------------------------------------------------------------
// Автономная группа прилагательного, обычно в роли объекта для предложного паттерна etc.


patterns AdjGroupUp { bottomup language=English }
export
{
 KEYFEATURE_DETECTED // есть союзный паттерн или перечисление через запятую
 KEYFEATURE_REQUIRED // =0 присоединено хотя бы одно прилагательное или причастие
 KEYFEATURE_DESIRABLE // есть союз
 node:root_node
}

// Затравочный элемент
pattern AdjGroupUp
{
 AdjGroupItem : export { KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED:1 KEYFEATURE_DESIRABLE:0 node:root_node }
}



// Присоединяем элемент через запятую:
// a red, white and blue flag
pattern AdjGroupUp
{
 n1=AdjGroupUp : export{ KEYFEATURE_DESIRABLE:0 node:root_node }
 comma=',' : export { KEYFEATURE_DETECTED:1 }
 n2=AdjGroupItem : export { KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>n2 }


// Присоединяем элемент через союз:
// Portland cement may be grey or white.
//                        ^^^^^^^^^^^^^
pattern AdjGroupUp
{
 n1=AdjGroupUp : export { node:root_node }
 conj=PrenomialAdjConj : export{ KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=AdjGroupItem : export{ KEYFEATURE_REQUIRED:0 }
}
: links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }
: ngrams { 1 }



// Финальный нетерминал - группа прилагательного в роли левого определения существительного
patterns AdjGroup { language=English } export { node:root_node }

// Одиночное прилагательное:
pattern AdjGroup
{
 AdjGroupItem : export { node:root_node }
}

// В группу входит минимум одно прилагательное и есть союзы:
pattern AdjGroup
{
 AdjGroupUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:1 }:export{ node:root_node }
}

// Особо рассматриваем группу из нескольких прилагательных, связанных
// без использования союза. Небольшой штраф дает преимущество союзным конструкциям.
pattern AdjGroup
{
 AdjGroupUp{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:0 }:export{ node:root_node }
} : ngrams { -1 }


// Паттерны с парными союзами:
// Some alleles are neither dominant nor recessive.
//                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern AdjGroup
{
 conj1=eng_conj:neither{}
 a1=AdjGroup : export { node:root_node }
 conj2=eng_conj:nor{}
 a2=AdjGroup
} : links { a1.{ <PREFIX_CONJUNCTION>conj1 <RIGHT_LOGIC_ITEM>conj2.a2 } }


// Embossers can be either one-sided or two-sided.
//                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern AdjGroup
{
 conj1=eng_conj:either{}
 a1=AdjGroup : export { node:root_node }
 conj2=eng_conj:or{}
 a2=AdjGroup
} : links { a1.{ <PREFIX_CONJUNCTION>conj1 <RIGHT_LOGIC_ITEM>conj2.a2 } }


pattern AdjGroup
{
 conj1=eng_conj:both{}
 a1=AdjGroup : export { node:root_node }
 conj2=eng_conj:and{}
 a2=AdjGroup
} : links { a1.{ <PREFIX_CONJUNCTION>conj1 <RIGHT_LOGIC_ITEM>conj2.a2 } }




pattern AdjGroup
{
 q1=OpeningQuote
 n=AdjGroup : export { node:root_node }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}
  



// ----------------------------------------------------------------------------------------------


// *************************************************
// Прилагательное с правым предложным дополнением.
// *************************************************

patterns Adj_WithPreposAdjunct0 export { node:root_node }

// Berkman pleaded not guilty to all charges.
//                 ^^^^^^^^^^...
pattern Adj_WithPreposAdjunct0
{
 n=eng_particle:not{}
 a=CompoundAdjective{ adj_form:basic } : export { node:root_node }
} : links { a.<NEGATION_PARTICLE>n }

pattern Adj_WithPreposAdjunct0
{
 a=CompoundAdjective{ adj_form:basic } : export { node:root_node }
}


patterns PreposItem export { node:root_node }


// My pocket is full of apples
//              ^^^^^^^^^^^^^^
pattern Adj_WithPreposAdjunct
{
 a=Adj_WithPreposAdjunct0 : export { node:root_node }
 p=PreposItem{ adj_prep( a, _ )  }
 n=PreposObject
}
: links { a.<PREPOS_ADJUNCT>p.<OBJECT>n }
: ngrams { eng_adj_prep_score( a, p ) }



// He was blissfully unaware of the danger.
pattern Adj_WithPreposAdjunct
{
 adv=AdvModifier4Adj
 a=Adj_WithPreposAdjunct0 : export { node:root_node }
 p=PreposItem{ adj_prep( a, _ )  }
 n=PreposObject
} : links { a.{
               <ATTRIBUTE>adv
               <PREPOS_ADJUNCT>p.<OBJECT>n
              } }
: ngrams { eng_adj_prep_score( a, p ) }


patterns Gerund { language=English } export { node:root_node }


// I am interested in collecting stamps.
pattern Adj_WithPreposAdjunct
{
 a=Adj_WithPreposAdjunct0 : export { node:root_node }
 p=PreposItem{ adj_prep( a, _ ) }
 g=Gerund
}
: links { a.<PREPOS_ADJUNCT>p.<OBJECT>g }
: ngrams { eng_adj_prep_score( a, p ) }


// I am terribly afraid of offending someone.
pattern Adj_WithPreposAdjunct
{
 adv=AdvModifier4Adj
 a=Adj_WithPreposAdjunct0 : export { node:root_node }
 p=PreposItem{ adj_prep( a, _ ) }
 g=Gerund
} : links { a.{
               <ATTRIBUTE>adv
               <PREPOS_ADJUNCT>p.<OBJECT>g
              } }
: ngrams { eng_adj_prep_score( a, p ) }



// Элективная конструкция:
// He acted with the best of motives.
//                   ^^^^^^^^^^^^^^^
pattern Adj_WithPreposAdjunct
{
 a=CompoundAdjective{ adj_form:superlative } : export { node:root_node }
 p=eng_prep:of{}
 obj=PreposObject
} : links { a.<PREPOS_ADJUNCT>p.<OBJECT>obj }
  : ngrams { 1 }

