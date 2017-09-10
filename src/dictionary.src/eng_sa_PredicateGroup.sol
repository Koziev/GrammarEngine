#region Samples
/*

Сборка предиката с глаголом в форме 1го лица единственного числа настоящего времени:

 I do agree!
 I know the trick;
 I had two concerns
 I don't get it.
 I forget every worry.
 I feel your pain.
 I don't see that;
 I don't see any.
 I strongly oppose merger.
 I don't use names.
 
 
Сборка предиката с глаголом в форме 3го лица единственного числа настоящего времени.

He thinks of other gods.
He lives in a body.


Сборка предиката с глаголом в форме единственного числа прошедшего времени.

активный залог
--------------

He died in 1935.
The aircraft landed safely.
I wrote these rituals.
I had an inspiration.
He married an Armenian woman.
Their son married an Armenian.
His prediction proved quite accurate.
She died on February 1.
She died on February 1.
He advocated navigational improvements on the Sangamon River.
He partnered with Stephen T. Logan from 1841 until 1844.
Based on this evidence, Armstrong was acquitted.

пассивный залог
---------------

It was, however, never written.



Сборка предиката с глаголом в форме множественного числа прошедшего времени.

активный залог
--------------

We practised discrimination and exclusion.
We rooted for the underdog.
We hired a prairie wagon.
Later we consolidated the lists.
We deleted this last year;
We jumped at the chance.
Women depended on men economically.
Few men volunteered to serve;
Sutawijaya and his men survived.
The two men became friends.

пассивный залог
---------------

Twenty-two Thakur men were killed.
All three men were cleared;
The men were never recaptured.



 -- ...

 
*/
#endregion Samples


// ===============================================================================
// восходящая сборка
// ===============================================================================
patterns Predicate_up { bottomup language=English }
export
{
 node:root_node
 TENSE
 PERSON
 NUMBER
 TRANSITIVITY
 VOICE
 OBLIG_TRANSITIVITY
 VERB_SLOTS
 SUBJ_LINKED OBJ_LINKED RHEMA_LINKED OBJ2_LINKED SECONDVERB_LINKED GERUND_LINKED
 SUBJ_LOC OBJ_LOC RHEMA_LOC 
 WORD_ORDER
}


// ----------------------------------------------------------------------------


// Затравочное правило.
#region seed_up

patterns PredicateUpHead { language=English }
export
{
 node:root_node
 TENSE
 PERSON
 NUMBER
 TRANSITIVITY
 VOICE
 OBLIG_TRANSITIVITY
 VERB_SLOTS
 SUBJ_LINKED
 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED
 SUBJ_LOC OBJ_LOC RHEMA_LOC 
 WORD_ORDER
}


pattern PredicateUpHead
{
 V_Present_1st_Singular
  : export {
            TENSE:PRESENT
            PERSON:1
            NUMBER:SINGLE
            TRANSITIVITY
            VOICE
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:0 OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 RHEMA_LINKED:0
            SUBJ_LOC:None OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:UNKNOWN
            node:root_node
           }
}

pattern PredicateUpHead
{
 V_Present_3st_Singular
  : export {
            TENSE:PRESENT
            PERSON:3
            NUMBER:SINGLE
            TRANSITIVITY
            VOICE
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:0 OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 RHEMA_LINKED:0
            SUBJ_LOC:None OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:UNKNOWN
            node:root_node
           }
}

pattern PredicateUpHead export { node:root_node TENSE (PERSON) NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
{
 V_Present_Plural
  : export {
            TENSE:PRESENT
            NUMBER:PLURAL
            TRANSITIVITY
            VOICE
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:0
            OBJ_LINKED:0
            OBJ2_LINKED:0
            GERUND_LINKED:0
            SECONDVERB_LINKED:0
            RHEMA_LINKED:0
            SUBJ_LOC:None OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:UNKNOWN
            node:root_node
           }
}


pattern PredicateUpHead export { node:root_node TENSE (PERSON) NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
{
 V_Past_Singular
  : export {
            TENSE:PAST
            NUMBER:SINGLE
            TRANSITIVITY
            VOICE
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:0
            OBJ_LINKED:0
            OBJ2_LINKED:0
            GERUND_LINKED:0
            SECONDVERB_LINKED:0
            RHEMA_LINKED:0
            SUBJ_LOC:None OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:UNKNOWN
            node:root_node
           }
}


pattern PredicateUpHead export { node:root_node TENSE (PERSON) NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
{
 V_Past_Plural
  : export {
            TENSE:PAST
            NUMBER:PLURAL
            TRANSITIVITY
            VOICE
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:0
            OBJ_LINKED:0
            OBJ2_LINKED:0
            GERUND_LINKED:0
            SECONDVERB_LINKED:0
            RHEMA_LINKED:0
            SUBJ_LOC:None OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:UNKNOWN
            node:root_node
           }
}


pattern PredicateUpHead export { node:root_node TENSE (PERSON) (NUMBER) TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
{
 V_Future
  : export {
            TENSE:FUTURE
            TRANSITIVITY
            VOICE
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:0
            OBJ_LINKED:0
            OBJ2_LINKED:0
            GERUND_LINKED:0
            SECONDVERB_LINKED:0
            RHEMA_LINKED:0
            SUBJ_LOC:None OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:UNKNOWN
            node:root_node
           }
} 

pattern PredicateUpHead export { node:root_node TENSE (PERSON) (NUMBER) TRANSITIVITY (VOICE) OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
{
 V_Modal
  : export {
            TENSE
            TRANSITIVITY
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:0
            OBJ_LINKED:0
            OBJ2_LINKED:0
            GERUND_LINKED:0
            SECONDVERB_LINKED:0
            RHEMA_LINKED:0
            SUBJ_LOC:None OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:UNKNOWN
            node:root_node
           }
}


pattern PredicateUpHead export { node:root_node TENSE (PERSON) (NUMBER) TRANSITIVITY (VOICE) OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
{
 V_Imperative
  : export {
            TENSE:IMPERATIVE
            TRANSITIVITY
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:1
            OBJ_LINKED:0
            OBJ2_LINKED:0
            GERUND_LINKED:0
            SECONDVERB_LINKED:0
            RHEMA_LINKED:0
            SUBJ_LOC:None OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:UNKNOWN
            node:root_node
           }
}


// --- для вопросительных конструкций ---

patterns SecondQuestVerb export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }

pattern SecondQuestVerb
{
 eng_verb:*{ VERB_FORM:INF } : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
} 

pattern SecondQuestVerb
{
 eng_beverb:*{ VERB_FORM:INF } : export { node:root_node TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}

patterns AuxDoVerb export { node:root_node VERB_FORM }

pattern AuxDoVerb
{
 v=eng_verb:do{} : export { node:root_node VERB_FORM }
} 

pattern AuxDoVerb
{
 v=eng_verb:do{} : export { node:root_node VERB_FORM }
 n=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>n }

pattern AuxDoVerb
{
 eng_verb:"don't"{} : export { node:root_node VERB_FORM }
} 





// Для вопросительных конструкций с обратным порядком слов
// Does This Bus Stop At 82nd Street?
// ^^^^^^^^^^^^^^^^^^
pattern PredicateUpHead
{
 aux=AuxDoVerb{ VERB_FORM:S }
 s=Sbj_3st_Singular
 v=SecondQuestVerb
  : export {
            TENSE:PRESENT
            PERSON:3
            NUMBER:SINGLE
            TRANSITIVITY
            VOICE
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:1 OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 RHEMA_LINKED:0
            SUBJ_LOC:Right OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:V_S
            node:root_node
           }
}
: links { v.{ <SUBJECT>s <LEFT_AUX_VERB>aux } }
: ngrams { eng_sbj_verb_score( s, v ) }

// How do you figure?
pattern PredicateUpHead export { node:root_node TENSE (PERSON) NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
{
 aux=AuxDoVerb{ VERB_FORM:INF }
 s=Sbj_Plural
 v=SecondQuestVerb
  : export {
            TENSE:PRESENT
            NUMBER:PLURAL
            TRANSITIVITY
            VOICE
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:1
            OBJ_LINKED:0
            OBJ2_LINKED:0
            GERUND_LINKED:0
            SECONDVERB_LINKED:0
            RHEMA_LINKED:0
            SUBJ_LOC:Right OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:V_S
            node:root_node
           }
}
: links { v.{ <SUBJECT>s <LEFT_AUX_VERB>aux } }
: ngrams { eng_sbj_verb_score( s, v ) }


// Did you put it in a bottle?
pattern PredicateUpHead export { node:root_node TENSE (PERSON) (NUMBER) TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
{
 aux=AuxDoVerb{ VERB_FORM:ED }
 s=Sbj
 v=SecondQuestVerb
  : export {
            TENSE:PAST
            TRANSITIVITY
            VOICE
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:1
            OBJ_LINKED:0
            OBJ2_LINKED:0
            GERUND_LINKED:0
            SECONDVERB_LINKED:0
            RHEMA_LINKED:0
            SUBJ_LOC:Right OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:V_S
            node:root_node
           }
}
: links { v.{ <SUBJECT>s <LEFT_AUX_VERB>aux } }
: ngrams { eng_sbj_verb_score( s, v ) }


// Will you have saved enough at retirement?
// What can we hear?
pattern PredicateUpHead export { node:root_node TENSE (PERSON) (NUMBER) TRANSITIVITY (VOICE) OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
{
 aux=V_Modal
 s=Sbj
 v=SecondQuestVerb
  : export {
            TENSE
            TRANSITIVITY
            OBLIG_TRANSITIVITY
            VERB_SLOTS
            SUBJ_LINKED:1
            OBJ_LINKED:0
            OBJ2_LINKED:0
            GERUND_LINKED:0
            SECONDVERB_LINKED:0
            RHEMA_LINKED:0
            SUBJ_LOC:Right OBJ_LOC:None RHEMA_LOC:None 
            WORD_ORDER:V_S
            node:root_node
           }
}
: links { v.{ <SUBJECT>s <LEFT_AUX_VERB>aux } }
: ngrams
{
 1
 eng_sbj_verb_score( s, v )
}



pattern Predicate_up
{
 v=PredicateUpHead : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC WORD_ORDER }
}

#endregion seed_up




// Подлежащее справа для обратного порядка слов или для
// некоторых стилистических оттенков:
#region VerbSubject

// How do I make links?
pattern Predicate_up
{
 v=Predicate_up{ TENSE:PRESENT PERSON:1 NUMBER:SINGLE SUBJ_LINKED:0 SECONDVERB_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC:Right OBJ_LOC RHEMA_LOC WORD_ORDER:V_S }
 s=Sbj_1st_Singular
}
: links { v.<SUBJECT>s }
: ngrams { eng_sbj_verb_score( s, v ) }


// So says too Leonard Peikoff.
// Does she have Indian blood?
pattern Predicate_up
{
 v=Predicate_up{ TENSE:PRESENT PERSON:3 NUMBER:SINGLE SUBJ_LINKED:0 SECONDVERB_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC:Right OBJ_LOC RHEMA_LOC WORD_ORDER:V_S }
 s=Sbj_3st_Singular
}
: links { v.<SUBJECT>s }
: ngrams { eng_sbj_verb_score( s, v ) }

// Do you believe in God?
//    ^^^
// Do they share environmental causes?
//    ^^^^
// In the room were three men.
//                  ^^^^^^^^^
// Are there lurking variables?
//           ^^^^^^^^^^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ TENSE:PRESENT NUMBER:PLURAL SUBJ_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 ~RHEMA_LOC:Right }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC:Right OBJ_LOC RHEMA_LOC WORD_ORDER:V_S }
 s=Sbj_Plural
}
: links { v.<SUBJECT>s }
: ngrams
{
 -1
 eng_sbj_verb_score( s, v )
}


// What did he do yesterday?
// Which groups did he name?
pattern Predicate_up
{
 v=Predicate_up{ TENSE:PAST NUMBER:SINGLE SUBJ_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC:Right OBJ_LOC RHEMA_LOC WORD_ORDER:V_S }
 s=Sbj_Singular
}
: links { v.<SUBJECT>s }
: ngrams
{
 -1
 eng_sbj_verb_score( s, v )
}

// Did they tell us that?
pattern Predicate_up
{
 v=Predicate_up{ TENSE:PAST NUMBER:PLURAL SUBJ_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC:Right OBJ_LOC RHEMA_LOC WORD_ORDER:V_S }
 s=Sbj_Plural
}
: links { v.<SUBJECT>s }
: ngrams
{
 -1
 eng_sbj_verb_score( s, v )
}


// Who will she choose in the end?
pattern Predicate_up
{
 v=Predicate_up{ TENSE:FUTURE SUBJ_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC:Right OBJ_LOC RHEMA_LOC WORD_ORDER:V_S }
 s=Sbj
}
: links { v.<SUBJECT>s }
: ngrams
{
 -1
 eng_sbj_verb_score( s, v )
}

// May I have your name?
// ^^^^^
pattern Predicate_up
{
 v=Predicate_up{ EngModalVerb0 SUBJ_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC:Right OBJ_LOC RHEMA_LOC  WORD_ORDER:V_S }
 s=Sbj
}
: links { v.<SUBJECT>s }
: ngrams
{
 -1
 eng_sbj_verb_score( s, v )
}


#endregion VerbSubject


#region RightAppeal
patterns Appeal export { node:root_node }

pattern Appeal
{
 NounGrpWithoutArticle : export { node:root_node }
}

pattern Appeal
{
 Sbj : export { node:root_node }
} : ngrams { -1 }

// Do you remember me, Jasmine Bligh?
//                   ^^^^^^^^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ SUBJ_LINKED:1 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC WORD_ORDER }
 comma=','
 a=Appeal
}
: links { v.<APPEAL>a.<PUNCTUATION>comma }
: ngrams { -1 }

#endregion RightAppeal



#region RightAdv

// Прикрепляем наречную группу справа
//
// From that hour they never parted more.
//                                  ^^^^
pattern Predicate_up
{
 v=Predicate_up{ SECONDVERB_LINKED:0 [-1]GERUND_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 adv=AdvRightModifier4Verb
}
: links { v.<ATTRIBUTE>adv }
: ngrams { eng_verb_adv_score(v,adv) }


// It lays here, on the table
//         ^^^^^^^^^^^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ SECONDVERB_LINKED:0 GERUND_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 adv=AdvRightModifier4Verb
 comma=','
 adv2=PreposPhrase{ verb_prep(v,_) }
}
: links { v.{ <ATTRIBUTE>adv <ATTRIBUTE>adv2.<PUNCTUATION>comma } }
: ngrams
{
 eng_verb_adv_score(v,adv)
 eng_v_prep_score(v,adv2)
 eng_v_prep_n_score(v,adv2,adv2.n2)
}


// The child was standing in the middle of the crossfire, defenselessly.
//                                                      ^^^^^^^^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ SECONDVERB_LINKED:0 GERUND_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 comma=','
 adv=AdvGroup
 @noshift(RightClauseBoundary)
}
: links { v.{ <ATTRIBUTE>adv <PUNCTUATION>comma } }
: ngrams
{
 -1
 eng_verb_adv_score(v,adv)
}




pattern Predicate_up
{
 v=Predicate_up{ SECONDVERB_LINKED:0 [-1]GERUND_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 adv=RightAdvPhrase
}
: links { v.<ATTRIBUTE>adv }


// Рефлексивное местоимение в роли обстоятельства для глагола:
// The compiler is itself written in TypeScript.
//                 ^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ SECONDVERB_LINKED:0 [-1]GERUND_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 adv=ENG_PRONOUN:*{ PRONOUN_FORM:REFLEXIVE }
}
: links { v.<ATTRIBUTE>adv }

#endregion RightAdv




#region DirectObj

// Прикрепляем прямое дополнение, если глагол переходный и слот дополнения свободен.
//
// I meet their wives.
//        ^^^^^^^^^^^
//
// I play a lot of open strings.
//        ^^^^^^^^^^^^^^^^^^^^^
//
// She has three doctorate degrees.
//         ^^^^^^^^^^^^^^^^^^^^^^^
//
// The men reconsidered their plan.
//                      ^^^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ TRANSITIVITY:TRANSITIVE OBJ_LINKED:0 SECONDVERB_LINKED:0 RHEMA_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 obj=RightDirectObj
}
: links { v.<OBJECT>obj }
: ngrams { eng_v_obj_score( v, obj ) }



// Полный предикат в роли правого прямого дополнения:
// The table shows which orderings are admitted.
//                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern RightDirectObj
{
 a=eng_adjective:which{}
 sbj=NounGroup
 p=PredicateConjTail{ SUBJ_LINKED:0 =sbj:NUMBER } : export { node:root_node }
} : links { p.<SUBJECT>sbj.<ATTRIBUTE>a }


#endregion DirectObj




// Обособленный атрибут прямого дополнения:
// Read found him unconscious the next morning.
//                ^^^^^^^^^^^
// Philosophers call such propositions "analytic."
//              ^^^^                    ^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ TRANSITIVITY:TRANSITIVE VERB_SLOTS:SeparateAttr OBJ_LINKED:1 SECONDVERB_LINKED:0 RHEMA_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED:1 SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 attr=AdjRhema1
}
: links { v.<SEPARATE_ATTR>attr }




// Предложно-герундиальный паттерн справа:
// I write a chapter every night before falling asleep.
//                               ^^^^^^^^^^^^^^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ SECONDVERB_LINKED:0 GERUND_LINKED:0 } :export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 adv=GerundAdvPhrase
}
: links { v.<ATTRIBUTE>adv }
// : eng_v_prep_n_score( v, p, p.n2 )


// you’ll see how to use WCF to build distributed applications.
//            ^^^^^^^^^^^...
// TODO ...



// This statement causes Dann to become quite upset.
//                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// TODO ...


// Прикрепляем предложную группу справа:
//
// I talk to them.
//        ^^^^^^^
// I disagree on the meaning of the word.
//            ^^^^^^^^^^^^^^^^^^^^^^^^^^
// All his men were on foot.
//                  ^^^^^^^
pattern Predicate_up
{
 v=Predicate_up { SECONDVERB_LINKED:0 [-1]GERUND_LINKED:0 [-2]RHEMA_LINKED:0 } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 p=PreposPhrase{ verb_prep(v,_) }
}
: links { v.<PREPOS_ADJUNCT>p }
: ngrams
{
 eng_v_prep_n_score( v, p, p.n2 )
 eng_v_prep_score( v, p )
}




// Прикрепляем дательный объект для дитранзитивных глаголов:
// I give you the woman's words;
//        ^^^
// I give them all my contacts
//        ^^^^
// I give you a few more examples.
//        ^^^
// To summarize, I give you pakaran:
//                      ^^^

pattern Predicate_up
{
 v=Predicate_up{ VERB_SLOTS:DITRANSITIVE OBJ_LINKED:0 OBJ2_LINKED:0 [-1]GERUND_LINKED:0 SECONDVERB_LINKED:0 }:export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED:0 OBJ2_LINKED:1 GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC WORD_ORDER }
 obj=DirectObj
}
: links { v.<OBJECT>obj }
: ngrams { eng_v_obj_score( v, obj ) }


// Прикрепляем герундиальную группу для глаголов типа to keep
// I keep stalling the car.
pattern Predicate_up
{
 v=Predicate_up{ VERB_SLOTS:GERUND RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 } :export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED:1 SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 gerund=Gerund
} : links { v.<GERUND>gerund }
  : ngrams { 1 }


  
  
  
// Прямое дополнение для страдательного залога глагола TO CALL:  
#region PassiveVerbWithDirectObj
wordentry_set PassiveVerbWithDirectObj={ eng_verb:call{}, eng_verb:consider{}, eng_verb:declare{}, eng_verb:name{}, eng_verb:rename{} }
// The islands were renamed Bioko and Annobon.
// Apollo was declared the winner because of this.
// Such compounds are called cycloalkanes.
// This is considered the first synthetic pigment.
// This is called generation loss.
// These are called dihedral angles.
pattern Predicate_up
{
 v=Predicate_up{ OBJ_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 VERB_SLOTS:COPULATIVE } :export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE:PASSIVE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED:1 SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 r=PastParticipleGroup{ PassiveVerbWithDirectObj }
 obj=RightDirectObj
}
: links { v.<RHEMA>r.<OBJECT>obj }
: ngrams { 2 }
#endregion PassiveVerbWithDirectObj

 
  

// Прикрепляем справа второй смысловой глагол в предложениях с обратным порядком слов:
// What then did you go to see?
//                   ^^
pattern Predicate_up
{
 v=Predicate_up{ VERB_SLOTS:ModalTo GERUND_LINKED:0 SECONDVERB_LINKED:0 }  :export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED:1 RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 v2=InfinitiveGroup
} : links { v.<SECOND_VERB>v2 }


// He asked me to come to his house
pattern Predicate_up
{
 v=Predicate_up{ VERB_SLOTS:AskedAction OBJ_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 }  :export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED:1 RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 obj=RightDirectObj
 v2=InfinitiveGroup
} : links { v.{ <OBJECT>obj <SECOND_VERB>v2 } }




// I could not do that
//   ^^^^^^^^^^^^^...
pattern Predicate_up
{
 v=Predicate_up{ VERB_SLOTS:ModalDirect GERUND_LINKED:0 SECONDVERB_LINKED:0 }  :export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED:1 RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 v2=BareInfinitive2
} : links { v.<SECOND_VERB>v2 }

// В некоторых конструкциях свободная переходность присоединенного инфинитива
// переходит к предикату и может быть заполнена непроективной связью:
// what we would meet.
pattern Predicate_up
{
 v=Predicate_up{ VERB_SLOTS:ModalDirect GERUND_LINKED:0 SECONDVERB_LINKED:0 }  :export { node:root_node TENSE PERSON NUMBER VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED:1 RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC WORD_ORDER }
 v2=BareInfinitive2{ TRANSITIVITY:TRANSITIVE OBJ_LINKED:0 } : export { TRANSITIVITY }
} : links { v.<SECOND_VERB>v2 }



// Если глагол имеет незанятый слот для страдательного причастия...
#region RightPP

// Had I packed my toothbrush?
// ^^^   ^^^^^^^^^^^^^^^^^^^^
wordentry_set HaveAuxVerb={ eng_verb:have{} }
pattern Predicate_up
{
 v=Predicate_up{ HaveAuxVerb RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 OBJ_LINKED:0 VERB_SLOTS:PastParticiple } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC:Right WORD_ORDER }
 r=PastParticipleGroup
} : links { v.<RHEMA>r }


pattern Predicate_up
{
 v=Predicate_up{ RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 OBJ_LINKED:0 VERB_SLOTS:PastParticiple } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC:Right WORD_ORDER }
 r=PastParticipleGroup{ OBJ_LINKED:0 }
} : links { v.<RHEMA>r }

#endregion RightPP


// Для связочных глаголов прикрепляем справа рему и взводим флаг присоединения объекта.
#region RightRhema
// Edmund finds out and feels betrayed by them both.
//                      ^^^^^^^^^^^^^^...

// I am a student. I am happy.
pattern Predicate_up
{
 v=Predicate_up{ NUMBER:SINGLE RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 VERB_SLOTS:COPULATIVE } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC:Right WORD_ORDER }
 r=SingularRhema
} : links { v.<RHEMA>r }

// it is difficult to apply evenly.
pattern Predicate_up
{
 v=Predicate_up{ NUMBER:SINGLE RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 VERB_SLOTS:COPULATIVE } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED:1 SUBJ_LOC OBJ_LOC RHEMA_LOC:Right WORD_ORDER }
 r=AdjRhema1
 inf=InfinitiveGroup
} : links { v.{ <RHEMA>r <INFINITIVE>inf } }

// It was a relief to see her.
pattern Predicate_up
{
 v=Predicate_up{ NUMBER:SINGLE RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 VERB_SLOTS:COPULATIVE } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED:1 SUBJ_LOC OBJ_LOC RHEMA_LOC:Right WORD_ORDER }
 r=NounRhema{ NUMBER:SINGLE }
 inf=InfinitiveGroup
} : links { v.{ <RHEMA>r <INFINITIVE>inf } }


// They are recognizably slimmer now.
pattern Predicate_up
{
 v=Predicate_up{ NUMBER:PLURAL RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 VERB_SLOTS:COPULATIVE } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC:Right WORD_ORDER }
 r=PluralRhema
} : links { v.<RHEMA>r }


// Problems of this type are very difficult to solve.
pattern Predicate_up
{
 v=Predicate_up{ NUMBER:PLURAL RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 VERB_SLOTS:COPULATIVE } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED:1 SUBJ_LOC OBJ_LOC RHEMA_LOC:Right WORD_ORDER }
 r=AdjRhema1
 inf=InfinitiveGroup
} : links { v.{ <RHEMA>r <INFINITIVE>inf } }




// Рема для будущего времени
// I will be ready
pattern Predicate_up
{
 v=Predicate_up{ TENSE:FUTURE RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 VERB_SLOTS:COPULATIVE } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC:Right WORD_ORDER }
 r=RhemaGroup
} : links { v.<RHEMA>r }



// Рема для императива:
// Be brave!
pattern Predicate_up
{
 v=Predicate_up{ TENSE:IMPERATIVE RHEMA_LINKED:0 GERUND_LINKED:0 SECONDVERB_LINKED:0 VERB_SLOTS:COPULATIVE } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC:Right  WORD_ORDER }
 r=RhemaGroup
} : links { v.<RHEMA>r }
#endregion RightRhema


// Правая инфинитивная группа для модальных глаголов:
//
// I want to stay longer.
//        ^^^^^^^^^^^^^^
//
// Then he starts to worry.
//                ^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ VERB_SLOTS:ModalTo OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 RHEMA_LINKED:0 SECONDVERB_LINKED:0 } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED RHEMA_LINKED SECONDVERB_LINKED:1 SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 inf=InfinitiveGroup
}
: links { v.<INFINITIVE>inf }
: ngrams { 2 VerbValency(v) }


// Инфинитивная группа для немодальных глаголов:
// I shudder to confess them.
//           ^^^^^^^^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up{ ~VERB_SLOTS:ModalTo ~VERB_SLOTS:ModalDirect OBJ_LINKED:0 OBJ2_LINKED:0 GERUND_LINKED:0 RHEMA_LINKED:0 SECONDVERB_LINKED:0 } : export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED:1 OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED:1 RHEMA_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 inf=InfinitiveGroup
}
: links { v.<INFINITIVE>inf }
: ngrams { -2 }


#region RightGerundPhrase
// Деепричастный (герундиальный) оборот справа:
// The heart muscle contracts faster, increasing blood flow through blood vessels.
//                                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern Predicate_up
{
 v=Predicate_up :export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 comma=','
 gerund=Gerund
 @noshift( RightClauseBoundary )
} : links { v.{ <ATTRIBUTE>gerund.<PUNCTUATION>comma } }
  : ngrams { -1 }

// Which is not accurate concerning the model?
//                       ^^^^^^^^^^^^^^^^^^^^  
pattern Predicate_up
{
 v=Predicate_up :export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED RHEMA_LINKED  SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER }
 gerund=Gerund
 @noshift( RightClauseBoundary )
} : links { v.<ATTRIBUTE>gerund }
  : ngrams { -4 }
  
#endregion RightGerundPhrase

  
/*
// Разрешим прикрепить любое слово или цепочку слов справа к глаголу с большим штрафом.
pattern Predicate_up
{
 v=Predicate_up :export { node:root_node TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY DITRANSITIVE SUBJ_LINKED GERUND_OBJ ENG_MODALITY OBJ_LINKED OBJ2_LINKED GERUND_LINKED SECONDVERB_LINKED WORD_ORDER }
 any=UnknownRightGroup
} : links { v.<UNKNOWN_SLOT>any }
*/



// ====================================================================
// нисходящая сборка для присоединения левых актантов и сирконстантов
// ====================================================================
patterns Predicate_down { language=English }
export
{
 node:root_node
 TENSE
 PERSON
 NUMBER
 TRANSITIVITY
 VOICE
 OBLIG_TRANSITIVITY
 VERB_SLOTS
 GERUND_LINKED SUBJ_LINKED OBJ_LINKED RHEMA_LINKED
 SUBJ_LOC OBJ_LOC RHEMA_LOC 
 WORD_ORDER
}


#region Seed

pattern Predicate_down
{
 Predicate_up : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED SUBJ_LOC OBJ_LOC RHEMA_LOC  WORD_ORDER node:root_node }
}

#endregion Seed

// ---------------------------------------------------------

// Подцепляем подлежащее слева
#region LeftSubject

// I firmly believe this;
// ^
pattern Predicate_down
{
 sbj=Sbj_1st_Singular
 v=Predicate_down{ TENSE:PRESENT PERSON:1 NUMBER:SINGLE SUBJ_LINKED:0 } : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER:S_V SUBJ_LOC:Left OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<SUBJECT>sbj }
: ngrams { eng_sbj_verb_score( sbj, v ) }


// She lives in Los Angeles.
// ^^^
pattern Predicate_down
{
 sbj=Sbj_3st_Singular
 v=Predicate_down{ TENSE:PRESENT PERSON:3 NUMBER:SINGLE SUBJ_LINKED:0 } : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER:S_V SUBJ_LOC:Left OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<SUBJECT>sbj }
: ngrams { eng_sbj_verb_score( sbj, v ) }


// They work out their issues;
// ^^^^
pattern Predicate_down
{
 sbj=Sbj_Plural
 v=Predicate_down{ TENSE:PRESENT NUMBER:PLURAL SUBJ_LINKED:0 } : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER:S_V SUBJ_LOC:Left OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<SUBJECT>sbj }
: ngrams { eng_sbj_verb_score( sbj, v ) }



// It galvanized such hostility.
// ^^
pattern Predicate_down
{
 sbj=Sbj_Singular
 v=Predicate_down{ TENSE:PAST NUMBER:SINGLE SUBJ_LINKED:0 } : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER:S_V SUBJ_LOC:Left OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<SUBJECT>sbj }
: ngrams { eng_sbj_verb_score( sbj, v ) }


// In fact they never shut up about it.
//         ^^^^
pattern Predicate_down
{
 sbj=Sbj_Plural
 v=Predicate_down{ TENSE:PAST NUMBER:PLURAL SUBJ_LINKED:0 } : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER:S_V SUBJ_LOC:Left OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<SUBJECT>sbj }
: ngrams { eng_sbj_verb_score( sbj, v ) }


pattern Predicate_down
{
 s=Sbj
 v=Predicate_down{ TENSE:FUTURE SUBJ_LINKED:0 } : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER:S_V SUBJ_LOC:Left OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<SUBJECT>s }
: ngrams { eng_sbj_verb_score( s, v ) }

// Chemotherapy may be used simultaneously.
// ^^^^^^^^^^^^ ^^^
pattern Predicate_down
{
 s=Sbj
 v=Predicate_down{ EngModalVerb0 SUBJ_LINKED:0 } : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED:1 OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER:S_V SUBJ_LOC:Left OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<SUBJECT>s }
: ngrams { eng_sbj_verb_score( s, v ) }

#endregion LeftSubject


#region LeftAppeal
// Обращение слева
// World, do you know your creator?
// ^^^^^^
pattern Predicate_down
{
 a=Appeal
 comma=','
 v=Predicate_down{ SUBJ_LINKED:1 } : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<APPEAL>a.<PUNCTUATION>comma }
: ngrams { -1 }
#endregion LeftAppeal


// -------------------------------------------------------------------

// Рема слева от глагола для вопросительных предложений:
#region LeftRhema
// Who am I?
pattern Predicate_down
{
 r=SingularRhema
 v=Predicate_down{ NUMBER:SINGLE RHEMA_LINKED:0 GERUND_LINKED:0 ~SUBJ_LOC:Left VERB_SLOTS:COPULATIVE } : export { TENSE NUMBER PERSON TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 GERUND_LINKED OBJ_LINKED WORD_ORDER:V_S SUBJ_LOC OBJ_LOC RHEMA_LOC:Left node:root_node }
}
: links { v.<RHEMA>r }
: ngrams { -1 }


// Who are you?
pattern Predicate_down
{
 r=PluralRhema
 v=Predicate_down{ NUMBER:PLURAL RHEMA_LINKED:0 GERUND_LINKED:0 ~SUBJ_LOC:Left VERB_SLOTS:COPULATIVE } : export { TENSE NUMBER PERSON TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED RHEMA_LINKED:1 OBJ_LINKED GERUND_LINKED WORD_ORDER:V_S SUBJ_LOC OBJ_LOC RHEMA_LOC:Left node:root_node }
}
: links { v.<RHEMA>r }
: ngrams { -1 }
#endregion LeftRhema



// Подцепляем предложную группу слева:
#region LeftPrepos

// To the tenth section I make no objection.
// ^^^^^^^^^^^^^^^^^^^^
// Without ceasing I make a commemoration of you.
// ^^^^^^^^^^^^^^^
// At some point he recovers.
// ^^^^^^^^^^^^^
// From her I never experienced the slightest hindrance.
// ^^^^^^^^
// However, in the end they never left Glenbogle.
//          ^^^^^^^^^^
pattern Predicate_down
{
 p=PreposPhrase
 v=Predicate_down{ verb_prep(_,p) } : export { TENSE NUMBER PERSON TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<PREPOS_ADJUNCT>p }
: ngrams
{
 eng_v_prep_n_score( v, p, p.n2 )
 eng_v_prep_score( v, p )
}

#endregion LeftPrepos



// Вводная группа слева:
#region LeftIntro
// At this point, I have a cold.
// ^^^^^^^^^^^^^^
// On the merits, I make no recommendation.
// ^^^^^^^^^^^^^^
// However, she prefers melons.
// ^^^^^^^^
// After that, I went straight for Zeppelin.
// ^^^^^^^^^^^
// As for that comment, I misrepresented myself;
// ^^^^^^^^^^^^^^^^^^^^
// Climbing out of the cellar, I stood dumbfounded.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Still, they never declined an invitation.
// ^^^^^^
pattern Predicate_down
{
 o=ClauseOpener
 v=Predicate_down : export { TENSE NUMBER PERSON TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<ATTRIBUTE>o }

#endregion LeftIntro




// Прямое дополнение слева, со штрафом:
// But this remark I make only in passing.
//     ^^^^^^^^^^^
pattern Predicate_down
{
 obj=DirectObj
 v=Predicate_down{ TRANSITIVITY:TRANSITIVE OBJ_LINKED:0 } : export { TENSE NUMBER PERSON TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED:1 RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -8
 eng_v_obj_score( v, obj )
}


wordform_set QuestWhDirectObj = 
{
 'what'{ class:eng_noun },
 'whom'{ class:eng_pronoun NOUN_FORM:BASIC CASE:PREPOSITIVE } // whom
}

// Особо обработаем случай, когда слева добавляется прямое дополнение WHAT:
// what we would meet.
// ^^^^
pattern Predicate_down
{
 obj=QuestWhDirectObj
 v=Predicate_down{ TRANSITIVITY:TRANSITIVE OBJ_LINKED:0 } : export { TENSE NUMBER PERSON TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED:1 RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<OBJECT>obj }
: ngrams
{
 eng_v_obj_score( v, obj )
}



// Подцепляем наречную группу слева:
//
// I publicly accused Arkan.
//   ^^^^^^^^
//
// Therefore I make no more use of her.
// ^^^^^^^^^
//
// Eventually she marries Reverend Naysmith.
// ^^^^^^^^^^
//
// Two months later she dies.
// ^^^^^^^^^^^^^^^^
//
// But surely I placed some confidence in you.
//     ^^^^^^
//
// Fortunately we never had to find out.
// ^^^^^^^^^^^
pattern Predicate_down
{
 a=AdvLeftModifier4Verb
 v=Predicate_down : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<ATTRIBUTE>a }
: ngrams { eng_adv_v_score( a, v ) }


// Civil rights, however, were deemphasized.
//             ^^^^^^^^^^
pattern Predicate_down
{
 comma1=','
 a=AdvLeftModifier4Verb
 comma2=','
 v=Predicate_down : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<ATTRIBUTE>a.{ <PUNCTUATION>comma1 <PUNCTUATION>comma2 } }
: ngrams { -2 }



// On 8 December Gibson did not fly.
// ^^^^^^^^^^^^^        ^^^^^^^^^^^
pattern Predicate_down
{
 a=AdverbialPhrase
 v=Predicate_down : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<ATTRIBUTE>a }



#region ClauseOpener

patterns PredicateOpener export { node:root_node }

// Twenty years ago, George was inclined to be fat
pattern PredicateOpener
{
 AdverbialPhrase:export { node:root_node }
}


// At nine o'clock, we all assembled in the hall
// At school, George was inclined to be fat
// In the year 2072, the program was brought on line
pattern PredicateOpener
{
 PreposPhrase:export { node:root_node }
}

// These problems apart, the country is doing well.
// ^^^^^^^^^^^^^^^^^^^^
pattern PredicateOpener
{
 obj=PreposObject
 p=eng_postpos:*{}:export { node:root_node }
} : links { p.<OBJECT>obj }


// When he saw his axe, he smiled happily
// ^^^^^^^^^^^^^^^^^^^^
// When athletes begin to exercise, their heart rates increase.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern PredicateOpener
{
 WHEN_AdvPhrase : export { node:root_node }
}



pattern Predicate_down
{
 @probe_left(LeftClauseBoundary)
 a=PredicateOpener
 comma=','
 v=Predicate_down : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<ATTRIBUTE>a.<PUNCTUATION>comma }


#endregion ClauseOpener



// Парные союзы обрабатываем по упрощенной схеме, в которой первый союз проглатывается
// первым сказуемым.
wordentry_set PairConj1 = { eng_conj:neither{}, eng_conj:either{} }
// I neither enjoy nor like the attention.
//   ^^^^^^^ 
pattern Predicate_down
{
 a=PairConj1
 v=Predicate_down : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<PREFIX_CONJUNCTION>a }

// ----------------------------------------------------------

/*
// разрешаем присоединять любую группу слов слева с большим штрафом
pattern Predicate_down
{
 a=UnknownLeftGroup
 v=Predicate_down : export { TENSE PERSON NUMBER TRANSITIVITY VOICE OBLIG_TRANSITIVITY VERB_SLOTS SUBJ_LINKED OBJ_LINKED RHEMA_LINKED GERUND_LINKED WORD_ORDER SUBJ_LOC OBJ_LOC RHEMA_LOC  node:root_node }
}
: links { v.<UNKNOWN_SLOT>a }
: ngrams { -10 }
*/

 
 
// ---------------------------------------------------------------------



pattern PredicateConjTail
{
 v=Predicate_down{ OBLIG_TRANSITIVITY:1 [-5]OBJ_LINKED:1 } : export { node:root_node SUBJ_LINKED TENSE VOICE PERSON NUMBER TRANSITIVITY OBJ_LINKED WORD_ORDER }
}
: ngrams
{
 VerbValency(v)
}

pattern PredicateConjTail
{
 v=Predicate_down{ ~OBLIG_TRANSITIVITY:1 } : export { node:root_node SUBJ_LINKED TENSE VOICE PERSON NUMBER TRANSITIVITY OBJ_LINKED WORD_ORDER }
}
: ngrams { VerbValency(v) }


pattern PredicateConjTail
{
 v=Predicate_down{ TENSE:IMPERATIVE } : export { node:root_node SUBJ_LINKED TENSE VOICE PERSON NUMBER TRANSITIVITY OBJ_LINKED WORD_ORDER }
}
: ngrams { VerbValency(v) }

// -----------------------------------------------------------------------------------------

function int verb_val( tree root )
{
 // Оштрафуем конфигурацию дерева, когда у корневого глагола Be 
 // есть подлежащее, но нет ремы или обстоятельства
 if( eq( wordform_class(root), ENG_BEVERB ) )
  then
  {
	  int n_sbj=0;
	  int n_rhema=0;
	  int n_adv=0;
	  int n_prep=0;
	  
   	  int nchild = link_count( root, "" );
	  int i;
	  for i=0 to arith_minus( nchild, 1 )
	  {
		  tree child = link_getref( root, "", i );
		  int lt = link_get_type2( root, "", i );
		  if( eq( lt, <SUBJECT> ) )
			  then n_sbj = arith_plus( n_sbj, 1 );
		  else if( eq( lt, <RHEMA> ) )
			  then n_rhema = arith_plus( n_rhema, 1 );
		  else if( eq( lt, <ATTRIBUTE> ) )
			  then n_adv = arith_plus( n_adv, 1 );
		  else if( eq( lt, <PREPOS_ADJUNCT> ) )
			  then n_prep = arith_plus( n_prep, 1 );
	  }
	  
	  if( log_and( gt( n_sbj, 0 ), eq( n_rhema, 0 ), eq( n_adv, 0 ), eq( n_prep, 0 ) ) )
	   then
	   {
        return -5;	  
	   }	
  }
	
 return 0;
}

pattern PredicateGroup0
{
 v=PredicateConjTail{ [-5]SUBJ_LINKED:1 } : export { node:root_node SUBJ_LINKED TENSE VOICE PERSON NUMBER TRANSITIVITY OBJ_LINKED WORD_ORDER }
}
: ngrams
{
 VerbValency(v)
 verb_val(v)
}

// ---------------------------------------------------------------------

pattern PredicateGroup
{
 PredicateGroup0 : export { node:root_node PERSON NUMBER VOICE SUBJ_LINKED }
} 


// ---------------------------------------------------------------
// Группа сказуемых. Могут соединяться сказуемые в разном глагольном времени.
// Также соединяем предикаты со своими подлежащими.
 
// Прикрепляем второе однородное сказуемое через союз
//
// I think and dream of my son;  
//   ^^^^^^^^^^^^^^^^^^^^^^^^^
// Gian Lorenzo Bernini restored and refinished the statue.
//                               ^^^^^^^^^^^^^^^^^^^^^^^^^
// Saeed Nafisi analyzed and edited several critical works.
//                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern PredicateGroup
{
 v=PredicateGroup0 : export { node:root_node PERSON NUMBER VOICE SUBJ_LINKED }
 conj=Or_And 
 v2=PredicateConjTail{ SUBJ_LINKED:0 [-9]=v:PERSON [-9]=v:NUMBER } // прикрепляем однородное сказуемое
}
: links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


pattern PredicateGroup
{
 v=PredicateGroup0 : export { node:root_node PERSON NUMBER VOICE SUBJ_LINKED }
 conj=Or_And 
 v2=PredicateConjTail{ SUBJ_LINKED:1 ~TENSE:IMPERATIVE [-1]=v:TENSE } // прикрепляем полный предикат
} : links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// В цепочке сказуемых может быть больше двух элементов, и одно из сказуемых прикрепляется
// не через союз, а через запятую:
//           
pattern PredicateGroup
{
 v=PredicateGroup0 :export { node:root_node VOICE SUBJ_LINKED PERSON NUMBER }
 comma=','
 v2=PredicateGroup{ SUBJ_LINKED:0 [-9]=v:PERSON [-9]=v:NUMBER } // прикрепляем однородное сказуемое
}
: links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }
: ngrams { -1 }


pattern PredicateGroup
{
 v=PredicateGroup0 :export { node:root_node VOICE SUBJ_LINKED PERSON NUMBER }
 comma=','
 v2=PredicateGroup{ SUBJ_LINKED:1 } // прикрепляем полный предикат
}
: links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }
: ngrams { -1 }

 

// Парные союзы обрабатываем по упрощенной схеме, в которой первый союз проглатывается
// первым сказуемым.
// I neither enjoy nor like the attention.
//   ^^^^^^^       ^^^
pattern PredicateGroup
{
 v=PredicateGroup0 : export { node:root_node VOICE SUBJ_LINKED PERSON NUMBER }
 conj=eng_conj:nor{}
 v2=PredicateGroup{ SUBJ_LINKED:0 [-9]=v:PERSON [-9]=v:NUMBER } // прикрепляем однородное сказуемое
} : links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }



// На всякий случай правило с любыми союзами.
pattern PredicateGroup
{
 v=PredicateGroup0 : export { node:root_node VOICE SUBJ_LINKED PERSON NUMBER }
 conj=eng_conj:*{}
 v2=PredicateGroup{ SUBJ_LINKED:0 [-9]=v:PERSON [-9]=v:NUMBER } // прикрепляем однородное сказуемое
}
: links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }
: ngrams { -2 }


pattern PredicateGroup
{
 v=PredicateGroup0 : export { node:root_node VOICE SUBJ_LINKED PERSON NUMBER }
 comma=','
 conj=eng_conj:*{}
 v2=PredicateGroup{ SUBJ_LINKED:0 [-9]=v:PERSON [-9]=v:NUMBER } // прикрепляем однородное сказуемое
}
: links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }
: ngrams { -2 }


pattern PredicateGroup
{
 v=PredicateGroup0 : export { node:root_node VOICE SUBJ_LINKED PERSON NUMBER }
 comma=','
 conj=eng_conj:*{}
 v2=PredicateGroup{ SUBJ_LINKED:1 } // прикрепляем полный предикат
}
: links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }
: ngrams { -2 }
  

// --------------------------------------------------------------------
