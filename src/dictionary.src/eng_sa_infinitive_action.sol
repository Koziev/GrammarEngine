// LC->31.05.2012


pattern InfinitiveAction
{
 p=eng_particle:to{}:export { node:root_node }
 v=BareInfinitive : export { node:root_node->verb }
} : links { p.<NEXT_COLLOCATION_ITEM>v }


// It is inconvenient not to have a telephone in the kitchen.
pattern InfinitiveAction
{
 not=eng_particle:not{}
 p=eng_particle:to{}:export { node:root_node }
 v=eng_verb:*{ verb_form:inf TRANSITIVITY:TRANSITIVE } : export { node:verb }
 obj=DirectObj
} : links { p.<NEXT_COLLOCATION_ITEM>v.{
                                        <NEGATION_PARTICLE>not
                                        <OBJECT>obj
                                       } }


// Отрицательный инфинитив
// It is inconvenient not to have a telephone in the kitchen.
pattern InfinitiveAction
{
 not=eng_particle:not{}
 p=eng_particle:to{}:export { node:root_node }
 v=eng_verb:*{ verb_form:inf TRANSITIVITY:TRANSITIVE } : export { node:verb }
 obj=DirectObj
 Adv1=PreposPhrase{ verb_prep( v, _.prepos ) }
} : links { p.<NEXT_COLLOCATION_ITEM>v.{
                                        <NEGATION_PARTICLE>not
                                        <OBJECT>obj
                                        <ATTRIBUTE>Adv1
                                       } }


// ---------------------


/*
// It is possible for the computations to produce an invalid result that exceeds the range
//                                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf TRANSITIVITY:TRANSITIVE } : export { node:root_node }
 obj=DirectObj_RAttrSV
} : links { v.<OBJECT>obj }
*/

/*
// I want to know more
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf } : export { node:root_node }
 adv=AdvGroup_SV
} : links { v.<ATTRIBUTE>adv }



// I was afraid to dive from the board into the pool.
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf } : export { node:root_node }
 adv1=PreposPhrase{ verb_prep( v, _.prepos ) }
 adv2=PreposPhrase{ verb_prep( v, _.prepos ) }
} : links { v.{
               <ATTRIBUTE>adv1
               <ATTRIBUTE>adv2
              } } 





// This statement is difficult to refute or accept on the base of current research evidence.
//                                ^^^^^^^^^^^^^^^^
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf } : export { node:root_node }
 conj=eng_conj:or{}
 v2=eng_verb:*{ verb_form:inf }
 adv=AdvGroup_SV
} : links { v.{
               <RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2
               <ATTRIBUTE>adv
              } }





// We began to steer away westerly.
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf } : export { node:root_node }
 adv1=SimplePostfixAdverb4Verb
 adv2=SimplePostfixAdverb4Verb
} : links { v.{
               <ATTRIBUTE>adv1
               <ATTRIBUTE>adv2
              } }




// I am able to speak English fluently.
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf TRANSITIVITY:TRANSITIVE } : export { node:root_node }
 obj=DirectObj
 adv=AdvGroup
} : links { v.{
               <OBJECT>obj
               <ATTRIBUTE>adv
              } }


// He had to consult his associate before continuing.
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf TRANSITIVITY:TRANSITIVE } : export { node:root_node }
 obj=DirectObj
 adv=GerundAdvPhrase
} : links { v.{
               <OBJECT>obj
               <ATTRIBUTE>adv
              } }


// He had to stop before continuing.
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf } : export { node:root_node }
 adv=GerundAdvPhrase
} : links { v.<ATTRIBUTE>adv }



// Father had to learn how to change the baby.
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf } : export { node:root_node }
 how=HOW_AdvPhrase
} : links { v.<ATTRIBUTE>how }


// The U.S. plans to airlift citizens from Japan
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf TRANSITIVITY:TRANSITIVE } : export { node:root_node }
 obj=DirectObj
 Adv1=PreposPhrase{ verb_prep( v, _.prepos ) }
} : links { v.{
               <OBJECT>obj
               <ATTRIBUTE>Adv1
              } }





// The U.S. plans to airlift citizens from Japan by helicopters
pattern BareInfinitive
{
 v=eng_verb:*{ verb_form:inf TRANSITIVITY:TRANSITIVE } : export { node:root_node }
 obj=DirectObj
 Adv1=PreposPhrase{ verb_prep( v, _.prepos ) }
 Adv2=PreposPhrase{ verb_prep( v, _.prepos ) }
} : links { v.{
               <OBJECT>obj
               <ATTRIBUTE>Adv1
               <ATTRIBUTE>Adv2
              } }



// I am happy to be George's friend.
pattern BareInfinitive
{
 v=eng_verb:be{ verb_form:inf } : export { node:root_node }
 obj=SingularNounRhema
} : links { v.<OBJECT>obj }


// I am happy to have been George's friend.
pattern BareInfinitive
{
 aux=eng_verb:have{ verb_form:inf }
 b='been' : export { node:root_node }
 obj=SingularNounRhema
} : links { b.{
               <LEFT_AUX_VERB>aux
               <OBJECT>obj
              } }


 

// It wants to be asked
pattern BareInfinitive
{
 v=eng_verb:be{verb_form:inf} : export { node:root_node }
 pp=eng_verb:*{ verb_form:pp ~SpecialVerbs }
} : links { v.<ATTRIBUTE>pp }



// I ought to be more careful
pattern BareInfinitive
{
 v=eng_verb:be{verb_form:inf} : export { node:root_node }
 adj=AdjRhema
} : links { v.<ATTRIBUTE>adj }


// You ought to be working.
pattern BareInfinitive
{
 v=eng_verb:be{verb_form:inf} : export { node:root_node }
 ing=eng_verb:*{ verb_form:ing }
} : links { v.<ATTRIBUTE>ing }
*/
