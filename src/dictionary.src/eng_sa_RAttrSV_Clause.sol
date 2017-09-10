
// I liked the song Margaret sang
//                  ^^^^^^^^^^^^^
pattern RAttrSV_Clause
{
 PredicateGroup0{ SUBJ_LINKED:1 OBJ_LINKED:0 TRANSITIVITY:TRANSITIVE WORD_ORDER:S_V ~TENSE:IMPERATIVE } : export{ node:root_node }
}

/*
// You know the girl I spoke to
pattern RAttrSV_Clause
{
 s=Sbj_Singular
 v=V_Past_Singular:export{ node:root_node }
 prep=eng_prep:*{ verb_prep( v.root_node, _ ) }
} : links { v.{
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }

// I know the girl you spoke to
pattern RAttrSV_Clause
{
 s=Sbj_Plural
 v=V_Past_Plural:export{ node:root_node }
 prep=eng_prep:*{ verb_prep( v.root_node, _ ) }
} : links { v.{
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }


// You know the girl I speak to
pattern RAttrSV_Clause
{
 s=Sbj_1st_Singular
 v=V_Present_1st_Singular:export{ node:root_node }
 prep=eng_prep:*{ verb_prep( v.root_node, _ ) }
} : links { v.{
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }

// You know the girl he speaks to
pattern RAttrSV_Clause
{
 s=Sbj_3st_Singular
 v=V_Present_3st_Singular:export{ node:root_node }
 prep=eng_prep:*{ verb_prep( v.root_node, _ ) }
} : links { v.{
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }


// You know the girl we speak to
pattern RAttrSV_Clause
{
 s=Sbj_Plural
 v=V_Present_Plural:export{ node:root_node }
 prep=eng_prep:*{ verb_prep( v.root_node, _ ) }
} : links { v.{
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }

// Here is the man I am helped by
pattern RAttrSV_Clause
{
 s=Sbj_1st_Singular
 aux=eng_verb:be{ verb_form:undef person:1 number:single }
 v=eng_verb:*{ verb_form:pp TRANSITIVITY:TRANSITIVE }:export{ node:root_node }
 prep=eng_prep:by{}
} : links { v.{
               <RIGHT_AUX2INFINITIVE>aux
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }

// Here is the man she is helped by
pattern RAttrSV_Clause
{
 s=Sbj_3st_Singular
 aux=eng_verb:be{ verb_form:undef person:3 number:single }
 v=eng_verb:*{ verb_form:pp TRANSITIVITY:TRANSITIVE }:export{ node:root_node }
 prep=eng_prep:by{}
} : links { v.{
               <RIGHT_AUX2INFINITIVE>aux
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }


// Here is the man we are helped by
pattern RAttrSV_Clause
{
 s=Sbj_Plural
 aux=eng_verb:be{ verb_form:undef number:plural }
 v=eng_verb:*{ verb_form:pp TRANSITIVITY:TRANSITIVE }:export{ node:root_node }
 prep=eng_prep:by{}
} : links { v.{
               <RIGHT_AUX2INFINITIVE>aux
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }


// Here is the man I was helped by
pattern RAttrSV_Clause
{
 s=Sbj_Singular
 aux=eng_verb:be{ verb_form:ed number:single }
 v=eng_verb:*{ verb_form:pp TRANSITIVITY:TRANSITIVE }:export{ node:root_node }
 prep=eng_prep:by{}
} : links { v.{
               <RIGHT_AUX2INFINITIVE>aux
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }


// Here is the man we were helped by
pattern RAttrSV_Clause
{
 s=Sbj_Plural
 aux=eng_verb:be{ verb_form:ed number:plural }
 v=eng_verb:*{ verb_form:pp TRANSITIVITY:TRANSITIVE }:export{ node:root_node }
 prep=eng_prep:by{}
} : links { v.{
               <RIGHT_AUX2INFINITIVE>aux
               <SUBJECT>s
               <RIGHT_PREPOSITION>prep
              } }


// He doesn't read the book I send him
pattern RAttrSV_Clause
{
 s=Sbj_1st_Singular
 v=eng_verb:*{ verb_form:undef person:1 VerbWithDativeObject }:export{ node:root_node }
 t=ActionTarget
} : links { v.{
               <SUBJECT>s
               <OBJECT>t
              } }


// They don't read the book he sends them
pattern RAttrSV_Clause
{
 s=Sbj_3st_Singular
 v=eng_verb:*{ verb_form:undef person:3 VerbWithDativeObject }:export{ node:root_node }
 t=ActionTarget
} : links { v.{
               <SUBJECT>s
               <OBJECT>t
              } }


// We don't read the book they sends me
pattern RAttrSV_Clause
{
 s=Sbj_Plural
 v=eng_verb:*{ verb_form:undef number:plural VerbWithDativeObject }:export{ node:root_node }
 t=ActionTarget
} : links { v.{
               <SUBJECT>s
               <OBJECT>t
              } }



// I didn't read the book he sent me
pattern RAttrSV_Clause
{
 s=Sbj_Singular
 v=eng_verb:*{ verb_form:ed VerbWithDativeObject }:export{ node:root_node }
 t=ActionTarget
} : links { v.{
               <SUBJECT>s
               <OBJECT>t
              } }

// I didn't read the book they sent us
pattern RAttrSV_Clause
{
 s=Sbj_Plural
 v=eng_verb:*{ verb_form:ed VerbWithDativeObject }:export{ node:root_node }
 t=ActionTarget
} : links { v.{
               <SUBJECT>s
               <OBJECT>t
              } }
*/
