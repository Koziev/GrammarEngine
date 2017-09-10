// Страдательное причастие для некоторых конструкций, похожих на пассивный залог.
// They were busily engaged in buying souvenirs.
// The tubes should not be placed widthwise inside the box
// the void return types must be checked

patterns PastParticiple0 export { node:root_node VERB_SLOTS }


// Отрицательная форма:
// Mosaic Patau syndrome is also not inherited.
//                               ^^^^^^^^^^^^^
pattern PastParticiple0
{
 not=eng_particle:not{}
 v=VerbWithPostfix{ VERB_FORM:PP [-5]TRANSITIVITY:TRANSITIVE } : export { node:root_node VERB_SLOTS }
}
: links { v.<NEGATION_PARTICLE>not }
: ngrams { 1 }


pattern PastParticiple0
{
 v=VerbWithPostfix{ VERB_FORM:PP [-5]TRANSITIVITY:TRANSITIVE } : export { node:root_node VERB_SLOTS }
}


// She won't have been asked
//                ^^^^
pattern PastParticiple0
{
 v=eng_beverb:*{ VERB_FORM:PP } : export { node:root_node VERB_SLOTS }
}


pattern PastParticiple0
{
 not=eng_particle:not{}
 v=eng_beverb:*{ VERB_FORM:PP } : export { node:root_node VERB_SLOTS }
}
: links { v.<NEGATION_PARTICLE>not }
: ngrams { 1 }


// ----------------------------------------------------------------------------

// Восходящая сборка для заполнения правых слотов.
patterns PPAsAdjRhema_up { language=English bottomup }
 export { node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }

// the void return types must be checked
//                               ^^^^^^^
pattern PPAsAdjRhema_up
{
 PastParticiple0 : export { node:root_node OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 VERB_SLOTS }
}


// I became more and more haunted by the stupid riddle.
//                                ^^^^^^^^^^^^^^^^^^^^
// This cannot be airily explained to your children.
//                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up : export{ node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }
 p=PreposPhrase{ verb_prep( v, _ ) }
}
: links { v.<PREPOS_ADJUNCT>p }
: ngrams
{
 eng_v_prep_n_score( v, p, p.n2 )
 eng_v_prep_score( v, p )
}




// This is referred to as diode logic.
//         ^^^^^^^^^^^
pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up : export{ node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }
 p=eng_prep:*{ verb_prep( v, _ ) }
}
: links { v.<PREPOS_ADJUNCT>p }
: ngrams
{
 -2
 eng_v_prep_score( v, p )
}




// No one was reported killed.
//            ^^^^^^^^^^^^^^^
pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up{ VERB_SLOTS:COPULATIVE GERUND_LINKED:0 OBJ_LINKED:0 OBJ2_LINKED:0 } : export{ node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED:1 SECONDVERB_LINKED VERB_SLOTS }
 pp=AdjRhema
} : links { v.<ADJ_PARTICIPLE>pp }
  : ngrams { 1 }


// David was permitted to watch the event.
//           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up{ VERB_SLOTS:ModalTo GERUND_LINKED:0 OBJ_LINKED:0 OBJ2_LINKED:0 SECONDVERB_LINKED:0 } : export{ node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED:1 VERB_SLOTS }
 pp=InfinitiveGroup
} : links { v.<SECOND_VERB>pp }



pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up{ GERUND_LINKED:0 OBJ_LINKED:0 OBJ2_LINKED:0 } : export{ node:root_node OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }
 obj=DirectObj
}
: links { v.<OBJECT>obj }
: ngrams
{
 eng_v_obj_score( v, obj )
}

// Второй объект для дитранзитивных глаголов
// Carolla was not given a middle name;
//                       ^^^^^^^^^^^^^
pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up{ OBJ_LINKED:0 OBJ2_LINKED:0 VERB_SLOTS:Ditransitive } : export{ node:root_node OBJ_LINKED OBJ2_LINKED:1 GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }
 obj=DirectObj
}
: links { v.<OBJECT>obj }
: ngrams
{
 eng_v_obj_score( v, obj )
}



// the void return types must be checked carefully
//                                       ^^^^^^^^^
pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up : export{ node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }
 adv=AdvGroup
}
: links { v.<ATTRIBUTE>adv }
: ngrams { eng_verb_adv_score(v,adv) }


// She is described as vivacious and witty.
//                  ^^^^^^^^^^^^^^^^^^^^^^
pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up : export{ node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }
 adv=RightAdvPhrase
}
: links { v.<ATTRIBUTE>adv }
: ngrams { eng_verb_adv_score(v,adv) }


// 141 were caught and executed.
//                 ^^^^^^^^^^^^
pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up : export { node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }
 conj=Or_And
 v2=PPAsAdjRhema
}
: links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up : export { node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }
 comma=','
 v2=PPAsAdjRhema
}
: links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }


pattern PPAsAdjRhema_up
{
 v=PPAsAdjRhema_up : export { node:root_node OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED VERB_SLOTS }
 comma=','
 conj=Or_And
 v2=PPAsAdjRhema
}
: links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// ----------------------------------------------------------------------

patterns PPAsAdjRhema_down export { node:root_node OBJ_LINKED OBJ2_LINKED VERB_SLOTS }


// Her face became distorted.
//                 ^^^^^^^^^
// Has been re-hashed throughout the debate.
//          ^^^^^^^^^
pattern PPAsAdjRhema_down
{
 PPAsAdjRhema_up : export{ node:root_node OBJ_LINKED OBJ2_LINKED VERB_SLOTS }
}

// Her face became fascinatingly distorted.
//                 ^^^^^^^^^^^^^
// the void return types must be carefully checked
//                               ^^^^^^^^^
pattern PPAsAdjRhema_down
{
 a=AdvLeftModifier4Verb
 v=PPAsAdjRhema_down:export{node:root_node OBJ_LINKED OBJ2_LINKED VERB_SLOTS }
}
: links { v.<ATTRIBUTE>a }
: ngrams { eng_adv_v_score(a,v) }

// ---------------------------------------------------------------------------

pattern PPAsAdjRhema
{
 v=PPAsAdjRhema_down{ OBJ_LINKED:0 } : export{ node:root_node }
}
: ngrams { VerbValency(v) }


// The woodwinds seemed "under-rehearsed".
//                      ^^^^^^^^^^^^^^^^^
pattern PPAsAdjRhema
{
 q1=OpeningQuote
 v=PPAsAdjRhema : export{node:root_node}
 q2=ClosingQuote
} : links
{
 v.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}

// -------------------------------------------------


pattern PastParticipleGroup
{
 v = PPAsAdjRhema_down : export{ OBJ_LINKED node:root_node }
}
: ngrams { VerbValency(v) }


pattern PastParticipleGroup
{
 q1=OpeningQuote
 v=PastParticipleGroup : export{ OBJ_LINKED node:root_node }
 q2=ClosingQuote
} : links
{
 v.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}

// ----------------------------------------------------------------

// Страдательное причастие в роли левого причастного оборота:
// When ordered to strip, he hesitated.
// ^^^^^^^^^^^^^^^^^^^^^

pattern PastParticipleLeftGroup
{
 @probe_left(LeftClauseBoundary)
 a=PastParticipleGroup{ OBJ_LINKED:0 } : export { node:root_node }
 @noshift(',')
}

pattern PastParticipleLeftGroup
{
 @probe_left(LeftClauseBoundary)
 adv=eng_adverb:*{}
 a=PastParticipleGroup{ OBJ_LINKED:0 } : export { node:root_node }
 @noshift(',')
} : links { a.<ATTRIBUTE>adv }

