
// Либо одиночный глагол, либо глагол с постфиксом (наречной частицей).
patterns VerbWithPostfix export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }

// ------------------------------------------------------------------


patterns BareInfinitive0_head { language=English }
export
{
 node:root_node
 TRANSITIVITY
 VERB_SLOTS
 OBLIG_TRANSITIVITY
 OBJ_LINKED
 OBJ2_LINKED
 GERUND_LINKED
}

pattern BareInfinitive0_head
{
 v=VerbWithPostfix{ verb_form:inf } : export { node:root_node TRANSITIVITY VERB_SLOTS OBLIG_TRANSITIVITY OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }
}

patterns BeVerb export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS NUMBER PERSON }

// These claims turned out to be false.
//                            ^^
pattern BareInfinitive0_head
{
 v=BeVerb{ verb_form:inf } : export { node:root_node TRANSITIVITY VERB_SLOTS OBLIG_TRANSITIVITY OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }
}



// Let's not discuss it
//       ^^^^^^^^^^^^^^
pattern BareInfinitive0_head
{
 n=eng_particle:not{}
 v=VerbWithPostfix{ verb_form:inf } : export { node:root_node TRANSITIVITY VERB_SLOTS OBLIG_TRANSITIVITY OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }
} : links { v.<NEGATION_PARTICLE>n }


// ------------------------------------------------------------------

// Восходящая сборка инфинитива
patterns BareInfinitive0_up { language=English bottomup }
export
{
 node:root_node
 TRANSITIVITY
 VERB_SLOTS
 OBLIG_TRANSITIVITY
 OBJ_LINKED
 OBJ2_LINKED
 GERUND_LINKED
}

pattern BareInfinitive0_up
{
 v=BareInfinitive0_head : export { node:root_node TRANSITIVITY VERB_SLOTS OBLIG_TRANSITIVITY OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }
}


// Прикрепляем наречную группу справа
// Anyone want to assist here?
//                       ^^^^
// I want to stay longer.
//                ^^^^^^
// I want to work more quickly and reliably.
//                ^^^^^^^^^^^^^^^^^^^^^^^^^
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }
 adv=AdvGroup
}
: links { v.<ATTRIBUTE>adv }
: ngrams { eng_verb_adv_score(v,adv) }


patterns RightAdvPhrase export { node:root_node }

// 
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }
 adv=RightAdvPhrase
}
: links { v.<ATTRIBUTE>adv }




patterns GerundAdvPhrase export { node:root_node }


// Предложно-герундиальный паттерн справа:
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 adv=GerundAdvPhrase
}
: links { v.<ATTRIBUTE>adv }


// Прикрепляем предложную группу справа:
// I don't want to write for the opponents.
//                       ^^^^^^^^^^^^^^^^^
// Others don't want to bother with the paperwork.
//                             ^^^^^^^^^^^^^^^^^^
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 p=PreposPhrase{ verb_prep(v,_) }
}
: links { v.<PREPOS_ADJUNCT>p }
: ngrams
{
 eng_v_prep_n_score( v, p, p.n2 )
 eng_v_prep_score( v, p )
}


// Прямое дополнение справа:
//
// I want to forget Goschen.
//                  ^^^^^^^
// I want to do it.
//              ^^
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up{ [-5]TRANSITIVITY:TRANSITIVE /*[-5]*/OBJ_LINKED:0 }:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED }
 obj=RightDirectObj
}
: links { v.<OBJECT>obj }
: ngrams { eng_v_obj_score( v, obj ) }



// Прикрепляем дательный объект для дитранзитивных глаголов:
// Cairo and Gutman agree to give him Wilmer.
//                                ^^^
// It was developed to give Fairfield a downtown.
//                          ^^^^^^^^^
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up{ VERb_SLOTS:DITRANSITIVE OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED:0 OBJ2_LINKED:1 GERUND_LINKED }
 obj=ActionTarget
}
: links { v.<OBJECT>obj }
: ngrams { eng_v_obj_score( v, obj ) }



// Прикрепляем герундиальную группу для глаголов с валентностью GERUND_OBJ
// This provides power to keep the clock going.
//                                       ^^^^^
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up{ VERB_SLOTS:GERUND GERUND_LINKED:0 } : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED:1 }
 gerund=Gerund
} : links { v.<GERUND>gerund }
  : ngrams { 1 }


// I shouldn't have done it.
//             ^^^^^^^^^^^^  
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up{ GERUND_LINKED:0 /*SECONDVERB_LINKED:0*/ VERB_SLOTS:PastParticiple } : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED:1 }
 r=PastParticipleGroup
} : links { v.<RHEMA>r }
  
  
  

patterns AdjRhema { language=English } export { node:root_node }

// Связочные глаголы присоединяют страдательное причастие или прилагательное справа:  
// The oil may get refined during the process.
//             ^^^^^^^^^^^^...
// You want to be congratulated.
//                ^^^^^^^^^^^^^
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up{ VERB_SLOTS:COPULATIVE GERUND_LINKED:0 } : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED:1 }
 pp=AdjRhema
} : links { v.<ADJ_PARTICIPLE>pp }
  : ngrams { 1 }


patterns AdjRhema1 export { node:root_node }

// She once conspired with Julie to get him expelled.
//                               ^^^^^^^^^^^^^^^^^^^
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up{ OBJ_LINKED:0 GERUND_LINKED:0 VERB_SLOTS:SeparateAttr } : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED:1 }
 obj=DirectObj
 pp=AdjRhema1
} : links { v.{ <OBJECT>obj <SEPARATE_ATTR>pp } }
  : ngrams { 1 }


  

// Присоединяем второй инфинитив через союз:  
// Click to view and read.
//               ^^^^^^^^
// The plastic is allowed to cool and harden.  
//                                ^^^^^^^^^^
// Cholesterol is required to build and maintain membranes;
//                                  ^^^^^^^^^^^^^^^^^^^^^^
// Temperatures continued to increase and began to stabilize.
//                                        ^^^^^^^^^^^^^^^^^^
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 conj=Or_And
 v2=InfinitiveGroup
} : links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// Разрешим прикреплять цепочку инфинтивов через запятую со штрафом.
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 comma=','
 v2=InfinitiveGroup
} : links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }



// Разрешим прикрепить любое слово или группу слов справа к инфинитиву с большим штрафом.
pattern BareInfinitive0_up
{
 v=BareInfinitive0_up : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 unk=UnknownRightGroup
}
: links { v.<UNKNOWN_SLOT>unk }



// ---------------------------------------------------------------------

patterns BareInfinitive0
export
{
 node:root_node
 TRANSITIVITY
 OBLIG_TRANSITIVITY
 VERB_SLOTS
 OBJ_LINKED
 OBJ2_LINKED
 GERUND_LINKED
}

pattern BareInfinitive0
{
 v1=BareInfinitive0_up : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED  OBJ2_LINKED GERUND_LINKED }
}
: ngrams { VerbValency(v1) }


// Модальный инфинитив может присоединять другой инфинитив справа
pattern BareInfinitive0
{
 v1=BareInfinitive0_up{ [-10]VERB_SLOTS:ModalTo } : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED  OBJ2_LINKED GERUND_LINKED }
 v2=InfinitiveGroup
}
: links { v1.<INFINITIVE>v2 }

// ------------------------------------------------------------------

patterns BareInfinitive export { node:root_node TRANSITIVITY OBJ_LINKED }

// Инфинитив с обязательной переходностью без прямого дополнения - штрафуем.
pattern BareInfinitive
{
 v1=BareInfinitive0{ OBLIG_TRANSITIVITY:1 [-2]OBJ_LINKED:0 } : export { node:root_node TRANSITIVITY OBJ_LINKED }
}
: ngrams { VerbValency(v1) }

// Прочие глаголы.
pattern BareInfinitive
{
 v1=BareInfinitive0{ ~OBLIG_TRANSITIVITY:1 } : export { node:root_node TRANSITIVITY OBJ_LINKED }
}
: ngrams { VerbValency(v1) }

// -----------------------------------------------------------

// Группа инфинитивов с союзным паттерном
patterns BareInfinitive2 export { node:root_node TRANSITIVITY OBJ_LINKED }

pattern BareInfinitive2
{
 v1=BareInfinitive : export { node:root_node TRANSITIVITY OBJ_LINKED }
}

pattern BareInfinitive2
{
 v1=BareInfinitive : export { node:root_node TRANSITIVITY OBJ_LINKED }
 conj=Or_And
 v2=BareInfinitive
} : links { v1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// -----------------------------------------------------------------

pattern InfinitiveGroup
{
 p=eng_particle:to{} : export { node:root_node }
 v=BareInfinitive2
} : links { p.<NEXT_COLLOCATION_ITEM>v }


// Отрицательный инфинитив
// It is inconvenient not to have a telephone in the kitchen.
//                    ^^^^^^^^^^^^...
pattern InfinitiveGroup
{
 not=eng_particle:not{}
 p=eng_particle:to{}:export { node:root_node }
 v=BareInfinitive2
} : links { p.{ <NEGATION_PARTICLE>not <NEXT_COLLOCATION_ITEM>v } }

                                      

pattern InfinitiveGroup
{
 q1=OpeningQuote
 n=InfinitiveGroup : export{ node:root_node }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}

