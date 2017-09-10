// ГЕРУНДИЙ И ПРЕДЛОЖНЫЙ ОБОРОТ С НИМ.
// This is done by making use of fluorescence.
//                 ^^^^^^^^^^^^^^^^^^^^^^^^^^

patterns GerundVerb export { node:root_node TRANSITIVITY VERB_SLOTS }
pattern GerundVerb
{
 v=VerbWithPostfix{ verb_form:ing } : export { node:root_node TRANSITIVITY VERB_SLOTS }
}

// Отрицательная форма:
pattern GerundVerb
{
 not=eng_particle:not{}
 v=VerbWithPostfix{ verb_form:ing } : export { node:root_node TRANSITIVITY VERB_SLOTS }
}
: links { v.<NEGATION_PARTICLE>not }
: ngrams { 1 }


// The roll was being called.
//              ^^^^^^^^^^^^
pattern GerundVerb
{
 v=eng_beverb{ verb_form:ing } : export { node:root_node TRANSITIVITY VERB_SLOTS }
}


// ------------------------------------------------------


// Восходящая сборка герундиального оборота
patterns Gerund0_up { language=English bottomup }
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

pattern Gerund0_up
{
 v=GerundVerb : export { node:root_node TRANSITIVITY VERB_SLOTS OBLIG_TRANSITIVITY OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }
}


// Прикрепляем наречную группу справа:
// There is a procedure for getting it back.
//                                     ^^^^
// Its reasons for doing so were not disclosed;
//                       ^^
pattern Gerund0_up
{
 v=Gerund0_up:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }
 adv=AdvRightModifier4Verb
}
: links { v.<ATTRIBUTE>adv }
: ngrams { eng_verb_adv_score(v,adv) }



// Предложно-герундиальный паттерн справа:
pattern Gerund0_up
{
 v=Gerund0_up:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 adv=GerundAdvPhrase
}
: links { v.<ATTRIBUTE>adv }


// Прикрепляем предложную группу справа:
// Diamonds can be collected by moving into them.
//                                     ^^^^^^^^^
// Cabbage was created by selecting for short petioles.
//                        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern Gerund0_up
{
 v=Gerund0_up:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 p=PreposPhrase
}
: links { v.<PREPOS_ADJUNCT>p }
: ngrams
{
 eng_v_prep_n_score( v, p, p.n2 )
 eng_v_prep_score( v, p )
}


// Прямое дополнение справа:
// Beds usually built by moving seats and tables.
//                              ^^^^^^^^^^^^^^^^
pattern Gerund0_up
{
 v=Gerund0_up{ [-5]TRANSITIVITY:TRANSITIVE [-5]OBJ_LINKED:0 GERUND_LINKED:0 }:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED }
 obj=DirectObj
}
: links { v.<OBJECT>obj }
: ngrams { eng_v_obj_score( v, obj ) }



// Прикрепляем дательный объект для дитранзитивных глаголов:
// He shows his love by giving her freedom.
//                             ^^^
// Maguire dealt with this by giving the creatures names.
//                                   ^^^^^^^^^^^^^
// The coroner began by giving him some advice.
//                             ^^^
pattern Gerund0_up
{
 v=Gerund0_up{ VERB_SLOTS:DITRANSITIVE OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 }:export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED:0 OBJ2_LINKED:1 GERUND_LINKED }
 obj=ActionTarget
}
: links { v.<OBJECT>obj }
: ngrams { eng_v_obj_score( v, obj ) }


// Прикрепляем герундиальную группу для глаголов с валентностью GERUND_OBJ
pattern Gerund0_up
{
 v=Gerund0_up{ VERB_SLOTS:GERUND GERUND_LINKED:0 } : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED:1 }
 gerund=Gerund
} : links { v.<GERUND>gerund }
  : ngrams { 1 }


// Связочные глаголы присоединяют страдательное причастие или прилагательное справа:  
// This is the forum for getting them deleted.
//                                    ^^^^^^^
pattern Gerund0_up
{
 v=Gerund0_up{ GERUND_LINKED:0 } : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED:1 }
 pp=AdjRhema
} : links { v.<ADJ_PARTICIPLE>pp }
  : ngrams { 1 }




  

// Присоединяем второй герундий через союз:  
pattern Gerund0_up
{
 v=Gerund0_up : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 conj=Or_And
 v2=Gerund
} : links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// Разрешим прикреплять цепочку герундиальных паттернов через запятую со штрафом.
pattern Gerund0_up
{
 v=Gerund0_up : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 comma=','
 v2=Gerund
} : links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }



// Разрешим прикрепить любое слово или группу слов справа к инфинитиву с большим штрафом.
pattern Gerund0_up
{
 v=Gerund0_up : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS OBJ_LINKED OBJ2_LINKED GERUND_LINKED }
 unk=UnknownRightGroup
}
: links { v.<UNKNOWN_SLOT>unk }


// Losing genetic diversity by classifying traits as diseases.
//                                                ^^^^^^^^^^^
// TODO

// ---------------------------------------------------------------------

patterns Gerund0
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

pattern Gerund0
{
 v1=Gerund0_up : export { node:root_node TRANSITIVITY VERB_SLOTS OBLIG_TRANSITIVITY OBJ_LINKED  OBJ2_LINKED GERUND_LINKED }
}
: ngrams { VerbValency(v1) }


// Модальный глагол в герундии может присоединять другой инфинитив справа
pattern Gerund0
{
 v1=Gerund0_up{ [-10]VERB_SLOTS:ModalTo } : export { node:root_node TRANSITIVITY VERB_SLOTS OBLIG_TRANSITIVITY OBJ_LINKED  OBJ2_LINKED GERUND_LINKED }
 v2=InfinitiveGroup
}
: links { v1.<INFINITIVE>v2 }


// Cities responded by making modifications to prevent it.
//                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// TODO              


// ------------------------------------------------------------------

// Глагол с обязательной переходностью без прямого дополнения - штрафуем.
pattern Gerund
{
 v1=Gerund0{ OBLIG_TRANSITIVITY:1 [-2]OBJ_LINKED:0 } : export { node:root_node }
}
: ngrams { VerbValency(v1) }

// Прочие глаголы без обязательного прямого дополнения
pattern Gerund
{
 v1=Gerund0{ ~OBLIG_TRANSITIVITY:1 } : export { node:root_node }
}
: ngrams { VerbValency(v1) }





// ------------------------------


wordentry_set GerundPrepos0=
{
 eng_prep:by{},
 eng_prep:from{},
 eng_prep:before{}, 
 eng_prep:instead of{},
 eng_prep:against{}, // Proof the materials against shrinking in the dryer.
 eng_prep:without{},  // Don't sign a contract without reading the fine print.
 eng_prep:after{},
 eng_prep:in{} // They were busily engaged in buying souvenirs.
}


patterns GerundPrepos export { node:root_node }

pattern GerundPrepos
{
 eng_prep:*{ [-2]GerundPrepos0 } : export { node:root_node }
}


// He paused worriedly before calling the bank. 
//                     ^^^^^^^^^^^^^^^^^^^^^^^
pattern GerundAdvPhrase
{
 prep=GerundPrepos : export { node:root_node }
 g=Gerund
} : links { prep.<OBJECT>g }

// ----------------------------

// Наречный оборот WHILE + gerund:
// The lovers held hands while walking.
//                       ^^^^^^^^^^^^^
pattern GerundAdvPhrase
{
 while=eng_conj:while{} : export { node:root_node }
 g=Gerund
} : links { while.<GERUND>g }

