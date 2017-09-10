#include "eng_sa_adv_macros.inc"

//patterns PP_InPassiveTense export { node:root_node }

// ------------------------------------------------------------------------------

#region VerbWithPostfix
// I ask. 
//   ^^^
pattern VerbWithPostfix
{
 v=CompoundVerb : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}

// It is/was here.
//    ^^^^^^
// This just seemed hopeless as it is/was.
//                                 ^^^^^^
// Consensus on the block is/was pretty clear.
//                        ^^^^^^
pattern VerbWithPostfix
{
 v=CompoundVerb : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
 conj='/'
 v2=CompoundVerb{ [-4]=v:NUMBER [-4]=v:PERSON } 
}
: links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }




pattern BeVerb
{
 v=eng_beverb:*{} : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS NUMBER PERSON }
}

pattern BeVerb
{
 v=eng_beverb:*{} : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS NUMBER PERSON }
 conj='/'
 v2=eng_beverb:*{ [-4]=v:NUMBER [-4]=v:PERSON } 
}
: links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }




pattern VerbWithPostfix
{
 q1=OpeningQuote
 n=VerbWithPostfix : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}

#endregion VerbWithPostfix


#region HAVE_Aux

patterns HAVE_Aux { language=English } export { node:root_node VERB_FORM TENSE }
pattern HAVE_Aux
{
 eng_verb:have{} : export { VERB_FORM node:root_node TENSE }
}

pattern HAVE_Aux
{
 eng_verb:"haven't"{} : export { VERB_FORM node:root_node TENSE }
}

pattern HAVE_Aux
{
 v=eng_verb:have{} : export { VERB_FORM node:root_node TENSE }
 n=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>n }

#endregion HAVE_Aux


// ---------------------------------------------------------------------------------

// VERB FORMS

#define VERB_PV( coords ) VerbWithPostfix{ coords }:export { node:root_node OBLIG_TRANSITIVITY VERB_SLOTS TRANSITIVITY:INTRANSITIVE VOICE:PASSIVE }

#define VERB_T_AV( coords ) VerbWithPostfix{ coords }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }

#define VERB_T( coords ) VerbWithPostfix{ coords }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node }


patterns V_Present_1st_Singular export { TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS VOICE node:root_node }
patterns V_Present_3st_Singular export { TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS VOICE node:root_node }
patterns V_Present_Plural export { TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS VOICE node:root_node }
patterns V_Past_Singular export { TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS VOICE node:root_node }
patterns V_Past_Plural export { TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS VOICE node:root_node }
patterns V_Imperative export { TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node }

patterns PPAsAdjRhema export{node:root_node}



#region V_Imperative

// Go!
pattern V_Imperative
{
 VERB_T( VERB_FORM:INF )
}

// Do run!
pattern V_Imperative
{
 aux=eng_verb:do{ VERB_FORM:INF }
 v=VERB_T( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux }
  : ngrams { 1 }

  
pattern V_Imperative
{
 BeVerb{ VERB_FORM:INF } :export { TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node }
}
  

  

// Do not ask!
pattern V_Imperative
{
 aux=eng_verb:do{ VERB_FORM:INF }
 n=eng_particle:not{}
 v=VERB_T( VERB_FORM:INF )
} : links {
           v.{
              <NEGATION_PARTICLE>n
              <LEFT_AUX_VERB>aux
             }
          }
: ngrams { 1 }

pattern V_Imperative
{
 aux=eng_verb:do{ VERB_FORM:INF }
 n=eng_particle:not{}
 adv=V_ADV_BETWEEN
 v=VERB_T( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n
             } 
          }
: ngrams { 1 }

// Don't ask!
pattern V_Imperative
{
 aux=eng_verb:"don't"{ VERB_FORM:INF }
 v=VERB_T( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux }


// Don't ever make my mind up!
// ^^^^^^^^^^^^^^^
pattern V_Imperative
{
 aux=eng_verb:"don't"{ VERB_FORM:INF }
 a=V_ADV_BETWEEN
 v=VERB_T( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>a
              <LEFT_AUX_VERB>aux
             }
          }

#endregion V_Imperative



// ********************************
// PRESENT SIMPLE TENSE
// ********************************

#region V_Present_1st_Singular

#region ActiveVoice
// I ask. I run fast. I hardly know. 
pattern V_Present_1st_Singular
{
 VERB_T_AV( VERB_FORM:INF )
}

// I am ready.
// I am here.
// I am a student.
pattern V_Present_1st_Singular
{
 BeVerb{ VERB_FORM:UNDEF PERSON:1 NUMBER:SINGLE }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
}


// I am not ready.
// I am not a student.
pattern V_Present_1st_Singular
{
 v=BeVerb{ VERB_FORM:UNDEF PERSON:1 NUMBER:SINGLE }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
 n=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>n }


// I have been a student
// I have been a student for 6 years.
// I've been a student for 6 years. 
// I've been a student at my University now for 5 years.
pattern V_Present_1st_Singular
{
 v=HAVE_Aux{ VERB_FORM:INF }:export{ node:root_node VOICE:ACTIVE }
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.<LEFT_AUX_VERB>aux1 }
: ngrams { 1 }


// I have previously been a student.
//   ^^^^^^^^^^^^^^^^^^^^
pattern V_Present_1st_Singular
{
 v=HAVE_Aux{ VERB_FORM:INF }:export{ node:root_node VOICE:ACTIVE }
 a=V_ADV_BETWEEN
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.{ <ATTRIBUTE>a <LEFT_AUX_VERB>aux1 } }
: ngrams { 1 }




// Generated results need not exist as files.
//                   ^^^^^^^^
pattern V_Present_1st_Singular
{
 v=eng_verb:*{ EngVerbNot0 VERB_FORM:INF }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
 n=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>n }


// I do ask. I really do believe. I do run fast.
//   ^^^^^^           ^^^^^^^^^^    ^^^^^^^^^^^
// Because I really do enjoy writing it...
//                  ^^^^^^^^
pattern V_Present_1st_Singular
{
 aux=eng_verb:do{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux }
  : ngrams { 1 }


// I do not ask.
pattern V_Present_1st_Singular
{
 aux=eng_verb:do{ VERB_FORM:INF }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <NEGATION_PARTICLE>n
              <LEFT_AUX_VERB>aux
             }
          }
: ngrams { 1 }

// I do not really understand myself these days.
//   ^^^^^^^^^^^^^^^^^^^^^^^^
pattern V_Present_1st_Singular
{
 aux=eng_verb:do{ VERB_FORM:INF }
 n=eng_particle:not{}
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n
             } 
          }
: ngrams { 1 }

// I don't ask.
pattern V_Present_1st_Singular
{
 aux=eng_verb:"don't"{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux }


// I don't really believe.
pattern V_Present_1st_Singular
{
 aux=eng_verb:"don't"{ VERB_FORM:INF }
 a=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>a
              <LEFT_AUX_VERB>aux
             }
          }


// I am going to win this game           
pattern V_Present_1st_Singular
{
 aux=BeVerb{ VERB_FORM:UNDEF PERSON:1 NUMBER:SINGLE }
 going=ENG_VERB:go { VERB_FORM:ING }
 p=eng_particle:to{}
 inf=VERB_T_AV( VERB_FORM:INF )
} : links { inf.<LEFT_AUX_VERB>aux.<NEXT_COLLOCATION_ITEM>going.<POSTFIX_PARTICLE>p }


wordentry_set AdvForGONNA=
{
 eng_adverb:now{}
}

// ???
// I am going now to feed the ducks and geese
pattern V_Present_1st_Singular
{
 aux=BeVerb{ VERB_FORM:UNDEF PERSON:1 NUMBER:SINGLE }
 going=ENG_VERB:go { VERB_FORM:ING }
 adv=AdvForGONNA
 p=eng_particle:to{}
 inf=VERB_T_AV( VERB_FORM:INF )
} : links {
           inf.<LEFT_AUX_VERB>aux.<NEXT_COLLOCATION_ITEM>going.{
                                                                <POSTFIX_PARTICLE>p
                                                                <ATTRIBUTE>adv
                                                               } }

/*
patterns PP_WithGet export { node:root_node }

// I get annoyed
pattern PP_WithGet
{
 eng_verb:*{ verb_form:pp }:export{ node:root_node }
}

// I get paid retroactively.
pattern PP_WithGet
{
 pp=eng_verb:*{ verb_form:pp }:export{ node:root_node }
 adv=eng_adverb:*{ adj_form:basic }
} : links { pp.<ATTRIBUTE>adv }


// I get annoyed
pattern V_Present_1st_Singular export { (TRANSITIVITY) (ENG_MODALITY) (OBLIG_TRANSITIVITY) (DITRANSITIVE) (COPULATIVE) (GERUND_OBJ) VOICE node:root_node }
{
 v=eng_verb:get{ VERB_FORM:INF }
 pp=PP_WithGet : export { node:root_node VOICE:PASSIVE } 
} : links { pp.<LEFT_AUX_VERB>v }
*/
#endregion ActiveVoice

/*
#region PassiveVoice

// **********************************************************************
// Паттерны для распознавания формы причастия прошедшего времени для
// аналитических конструкций пассивного залога.
// **********************************************************************

//patterns PassiveInnerAdvGrp export { node:root_node }


// The survey was carried out aerially.
//                ^^^^^^^^^^^
// Nobody is legally allowed to stultify
//                   ^^^^^^^^^^^^^^^^^^^
pattern PP_InPassiveTense
{
 PPAsAdjRhema : export { node:root_node }
}

// -----------------------------------------------------------


// I am asked. I'm asked.
pattern V_Present_1st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux=BeVerb{ VERB_FORM:UNDEF PERSON:1 NUMBER:SINGLE } // am, 'm
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.<LEFT_AUX_VERB>aux  }
: ngrams { 1 }


// I am not asked.
pattern V_Present_1st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux='am'{ class:eng_verb }
 n=eng_particle:not{}
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }

#endregion PassiveVoice
*/

#endregion V_Present_1st_Singular


#region V_Present_3st_Singular
// ---------------
// active voice
// ---------------

// He asks
pattern V_Present_3st_Singular
{ VERB_T_AV( VERB_FORM:S ) }

// He is a doctor
pattern V_Present_3st_Singular
{ 
 v=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }:export{ VOICE:ACTIVE TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node }
}


// She has been a student
// She has been a student for 6 years.
pattern V_Present_3st_Singular
{
 v=HAVE_Aux{ VERB_FORM:S }:export{ node:root_node VOICE:ACTIVE }
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.<LEFT_AUX_VERB>aux1 }
: ngrams { 1 }

// She has previously been a student.
pattern V_Present_3st_Singular
{
 v=HAVE_Aux{ VERB_FORM:S }:export{ node:root_node VOICE:ACTIVE }
 a=V_ADV_BETWEEN
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.{ <ATTRIBUTE>a <LEFT_AUX_VERB>aux1 } }
: ngrams { 1 }


// He does ask 
pattern V_Present_3st_Singular
{
 aux=eng_verb:do{ VERB_FORM:S }
 v=VERB_T_AV( VERB_FORM:INF )
}
: links { v.<LEFT_AUX_VERB>aux }
: ngrams { 1 }

// He does not ask 
pattern V_Present_3st_Singular
{ 
 aux=eng_verb:do{ VERB_FORM:S }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }

// He does not really sleep
pattern V_Present_3st_Singular
{
 aux=eng_verb:do{ VERB_FORM:S }
 n=eng_particle:not{}
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n
             }
          }
: ngrams { 1 }

// He doesn't ask 
pattern V_Present_3st_Singular
{
 aux=eng_verb:"don't"{ VERB_FORM:S }
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux }

// He doesn't like fish
pattern V_Present_3st_Singular
{
 aux=eng_verb:"don't"{ VERB_FORM:S }
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.{
               <ATTRIBUTE>adv
               <LEFT_AUX_VERB>aux
              } }

// He is going to win this game 
pattern V_Present_3st_Singular
{
 aux=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 going=ENG_VERB:go { VERB_FORM:ING }
 p=eng_particle:to{}
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux.<NEXT_COLLOCATION_ITEM>going.<NEXT_COLLOCATION_ITEM>p }


// He is not ready
//    ^^^^^^
pattern V_Present_3st_Singular
{
 v=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }:export{ VOICE:ACTIVE TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node }
 n=eng_particle:not{}
}
: links { v.<NEGATION_PARTICLE>n }
: ngrams { 2 }


pattern V_Present_3st_Singular
{
 v=eng_verb:*{ EngVerbNot0 VERB_FORM:S }:export{ VOICE:ACTIVE TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node }
 n=eng_particle:not{}
}
: links { v.<NEGATION_PARTICLE>n }



/*
// He gets annoyed
pattern V_Present_3st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (DITRANSITIVE) ( COPULATIVE) (GERUND_OBJ) VOICE node:root_node }
{
 v=eng_verb:get{ verb_form:undef person:3 number:single }
 pp=PP_WithGet : export { node:root_node VOICE:PASSIVE } 
} : links { pp.<LEFT_AUX_VERB>v }
*/

// -----------------
// passive voice
// -----------------

/*
// He is asked.
pattern V_Present_3st_Singular export { (TRANSITIVITY) (VERB_SLOTS) (OBLIG_TRANSITIVITY) VOICE node:root_node }
{
 aux=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 1 }

// The prepositional phrase here is used adverbially.
pattern V_Present_3st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 adv=PrefixPassiveAdv
 aux=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.{
               <LEFT_AUX_VERB>aux
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }




// He is not asked.
pattern V_Present_3st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 n=eng_particle:not{}
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
}
: links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }
*/

#endregion V_Present_3st_Singular


#region V_Present_Plural


// We ask
pattern V_Present_Plural
{ VERB_T_AV( VERB_FORM:INF ) }


// You do ask
pattern V_Present_Plural
{
 aux=eng_verb:do{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 1 }

// They do not ask 
pattern V_Present_Plural
{
 aux=eng_verb:do{ VERB_FORM:INF }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }

// They do not ever ask
pattern V_Present_Plural
{
 aux=eng_verb:do{ VERB_FORM:INF }
 n=eng_particle:not{}
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n
             }
          }
: ngrams { 1 }

// We don't ask 
pattern V_Present_Plural
{
 aux=eng_verb:"don't"{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.<LEFT_AUX_VERB>aux
          }

// We don't ever ask 
pattern V_Present_Plural
{
 aux=eng_verb:"don't"{ VERB_FORM:INF }
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux
             }
          }

// We are going to win this game
pattern V_Present_Plural
{
 aux=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }
 going=ENG_VERB:go { VERB_FORM:ING }
 p=eng_particle:to{}
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux.<NEXT_COLLOCATION_ITEM>going.<POSTFIX_PARTICLE>p }


pattern V_Present_Plural
{
 v=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
}

// We are not ready
//    ^^^^^^^
pattern V_Present_Plural
{
 v=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
 n=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>n }



// There have been no releases since 2003.
//       ^^^^^^^^^
// You've been a student
// You've been a student at university. 
pattern V_Present_Plural
{
 v=HAVE_Aux{ VERB_FORM:INF }:export{ node:root_node VOICE:ACTIVE }
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.<LEFT_AUX_VERB>aux1 }
: ngrams { 1 }

// You've previously been a student
pattern V_Present_Plural
{
 v=HAVE_Aux{ VERB_FORM:INF }:export{ node:root_node VOICE:ACTIVE }
 a=V_ADV_BETWEEN
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.{ <ATTRIBUTE>a <LEFT_AUX_VERB>aux1 } }
: ngrams { 1 }








// Monads need not be "small";
//        ^^^^^^^^
pattern V_Present_Plural
{
 v=eng_verb:*{ EngVerbNot0 VERB_FORM:INF }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
 n=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>n }


// Images are often not paramount;
//        ^^^^^^^^^^^^^
pattern V_Present_Plural
{
 v=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
 adv=AdvGroup
 n=eng_particle:not{}
} : links { v.{ <ATTRIBUTE>adv <NEGATION_PARTICLE>n } }


/*
// ---------------
// passive voice
// ---------------

// You are asked. We're asked. 
pattern V_Present_Plural export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 1 }


// ??? 
// The prepositional phrases here are used adverbially.
pattern V_Present_Plural export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 adv=PrefixPassiveAdv
 aux=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.{
               <LEFT_AUX_VERB>aux
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }




// We are not asked. 
pattern V_Present_Plural export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }
 n=eng_particle:not{}
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }
*/
 
#endregion V_Present_Plural
 
 
 
// ********************************
// PAST SIMPLE TENSE
// ********************************


#region V_Past_Singular

// I asked 
pattern V_Past_Singular
{
 VerbWithPostfix{ VERB_FORM:ED }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
}

// I was here
pattern V_Past_Singular
{
 BeVerb{ VERB_FORM:ED NUMBER:SINGLE }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
}

pattern V_Past_Singular
{
 v=HAVE_Aux{ VERB_FORM:ED }:export{ node:root_node VOICE:ACTIVE }
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.<LEFT_AUX_VERB>aux1 }
: ngrams { 1 }

// I had never been late for school until yesterday.
pattern V_Past_Singular
{
 v=HAVE_Aux{ VERB_FORM:ED }:export{ node:root_node VOICE:ACTIVE }
 a=V_ADV_BETWEEN
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.{ <ATTRIBUTE>a <LEFT_AUX_VERB>aux1 } }
: ngrams { 1 }




// I was not ready
//   ^^^^^^^
pattern V_Past_Singular
{
 v=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
 n=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>n }


// I did not ask
pattern V_Past_Singular
{
 aux=eng_verb:do{ VERB_FORM:ED }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }

// I did not ever ask 
pattern V_Past_Singular
{
 aux=eng_verb:do{ VERB_FORM:ED }
 n=eng_particle:not{}
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n
             }
          }
: ngrams { 1 }          

// I didn't ask 
pattern V_Past_Singular
{
 aux=eng_verb:"don't"{ VERB_FORM:ED }
 v=VERB_T_AV( VERB_FORM:INF )
}
: links { v.<LEFT_AUX_VERB>aux }
: ngrams { 1 }


// I didn't ever ask 
pattern V_Past_Singular
{
 aux=eng_verb:"don't"{ VERB_FORM:ED }
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux
             }
          }
: ngrams { 1 }
		  
 

/*
// ---------------
// passive voice
// ---------------


// I was asked
pattern V_Past_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 1 }

// The prepositional phrase here was used adverbially.
pattern V_Past_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 adv=PrefixPassiveAdv
 aux=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.{
               <LEFT_AUX_VERB>aux
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }

// I was not asked
pattern V_Past_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }
 n=eng_particle:not{}
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }

*/

#endregion V_Past_Singular


#region V_Past_Plural

// You asked 
pattern V_Past_Plural
{
 VerbWithPostfix{ VERB_FORM:ED }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
}

// We are here
pattern V_Past_Plural
{
 v=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
}

// We were not ready
//    ^^^^^^^^
pattern V_Past_Plural
{
 v=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
 n=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>n }


// I had never been late for school until yesterday.
pattern V_Past_Plural
{
 v=HAVE_Aux{ VERB_FORM:ED }:export{ node:root_node VOICE:ACTIVE }
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.<LEFT_AUX_VERB>aux1 }
: ngrams { 1 }

// We had never been late for school until yesterday.
pattern V_Past_Plural
{
 v=HAVE_Aux{ VERB_FORM:ED }:export{ node:root_node VOICE:ACTIVE }
 a=V_ADV_BETWEEN
 aux1='been' : export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.{ <ATTRIBUTE>a <LEFT_AUX_VERB>aux1 } }
: ngrams { 1 }






pattern V_Past_Plural
{
 v=VerbWithPostfix{ EngVerbNot0 VERB_FORM:ED }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
 n=eng_particle:not{}
} : links { v.<NEGATION_PARTICLE>n }



// We did not ask 
pattern V_Past_Plural
{
 aux=eng_verb:do{ VERB_FORM:ED }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:INF )
}
: links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }

// You did not even talk to me
pattern V_Past_Plural
{
 aux=eng_verb:do{ VERB_FORM:ED }
 n=eng_particle:not{}
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n
             }
          }
: ngrams { 1 }


// They didn't ask 
pattern V_Past_Plural
{
 aux=eng_verb:"don't"{ VERB_FORM:ED }
 v=VERB_T_AV( VERB_FORM:INF )
}
: links { v.<LEFT_AUX_VERB>aux }
: ngrams { 1 }


// They didn't even talk to me
pattern V_Past_Plural
{
 aux=eng_verb:"don't"{ VERB_FORM:ED }
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux
             }
          }
: ngrams { 1 }
		  
/* 
// -----------------
// passive voice
// -----------------

// You were asked
pattern V_Past_Plural export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 1 }


// The prepositional phrases here were used adverbially.
pattern V_Past_Plural export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 adv=PrefixPassiveAdv
 aux=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.{
               <LEFT_AUX_VERB>aux
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }


// We were not asked 
pattern V_Past_Plural export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 n=eng_particle:not{}
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }
*/


#endregion V_Past_Plural




 
// ********************************
// FUTURE SIMPLE TENSE
// ********************************

#region V_Future

patterns V_Future export { TRANSITIVITY (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }

// I will ask 
pattern V_Future
{
 aux=Will_Shall
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 1 }


// I will be ready
//   ^^^^^^^
pattern V_Future
{
 aux=Will_Shall
 v=BeVerb{ VERB_FORM:INF }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
} : links { v.<LEFT_AUX_VERB>aux }


// He will not be ready
pattern V_Future
{
 aux=Will_Shall
 n=eng_particle:not{}
 v=BeVerb{ VERB_FORM:INF }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
} : links { v.{ <LEFT_AUX_VERB>aux <NEGATION_PARTICLE>n } }
: ngrams { 1 }





// I will often ask 
pattern V_Future
{
 aux=Will_Shall
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:INF )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux
             }
          }


// I will not ask 
pattern V_Future
{
 aux=Will_Shall
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }

// I won't ask 
pattern V_Future
{
 aux=Will_Shall_Not
 v=VERB_T_AV( VERB_FORM:INF )
} : links { v.<LEFT_AUX_VERB>aux }


/*
// -----------------
// passive voice
// -----------------

// I will be asked 
pattern V_Future export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux1=Will_Shall
 aux2=BeVerb{ verb_form:inf }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
}
: links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// The prepositional phrase here will be used adverbially.
pattern V_Future export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 adv=PrefixPassiveAdv
 aux1=Will_Shall
 aux2=BeVerb{ verb_form:inf }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
}
: links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }


// I will not be asked 
pattern V_Future export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux1=Will_Shall
 n=eng_particle:not{}
 aux2=BeVerb{ verb_form:inf }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
}
: links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// I won't be asked 
pattern V_Future export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) (VERB_SLOTS) VOICE node:root_node }
{
 aux1=Will_Shall_Not
 aux2=BeVerb{ verb_form:inf }
 v=PP_InPassiveTense:export { node:root_node VOICE:PASSIVE }
}
: links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }
*/

#endregion V_Future


// ********************************
// PRESENT PERFECT TENSE
// ********************************


// наречия, которые могут стоять внутри аналитической конструкции to have + pp:
wordentry_set SingleAdverb1_PT = eng_adverb:{
 clearly, // History has clearly shown the folly of that policy.
 unrecognizably, // He had unrecognizably aged.
 stupidly, // He had stupidly bought a one way ticket.
 previously, // She had previously lived in Chicago.
 just, // He has just arrived.
 vastly, // He had vastly overestimated his resources.
 always,
 never,
 often,
 "never ever", // I have never ever spoken to George's sister.
 hardly, // I have hardly spoken to George's sister.
 scarcely, // I have scarcely spoken to George's sister.
 seldom, // I have seldom spoken to George's sister.
 rarely, // I have rarely spoken to George's sister.
 already,
 since, // Guthrie has since become a registered Republican.
 willfully, // She had willfully deceived me.
 quickly // She had quickly opened the door
}

patterns SingleAdverb_PT { language=English }

pattern SingleAdverb_PT export { node:root_node } { SingleAdverb1_PT{ADJ_FORM:BASIC}:export{node:root_node} }


// I have hardly ever spoken to George's sister.
// I have scarcely ever spoken to George's sister.
// I have never ever spoken to George's sister.
pattern SingleAdverb_PT export { node:root_node }
{
 a1=SingleAdverb1_PT{ADJ_FORM:BASIC}:export{node:root_node}
 a2=eng_adverb:ever{}
} : links { a1.<ATTRIBUTE>a2 }

#region V_Present_1st_Singular

// --------------- 
// active voice
// --------------- 

// I have done it
pattern V_Present_1st_Singular
{
 aux=eng_verb:have{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }
  : ngrams { 1 }


// I have already done it
pattern V_Present_1st_Singular
{
 aux=eng_verb:have{ VERB_FORM:INF }
 adv=SingleAdverb_PT
 v=VERB_T_AV( VERB_FORM:PP )
} : links {
           v.{
               <ATTRIBUTE>adv
               <LEFT_AUX_VERB>aux
             }
          }



// I have not done           
pattern V_Present_1st_Singular
{
 aux=eng_verb:have{ VERB_FORM:INF }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }


// I haven't done
pattern V_Present_1st_Singular
{
 aux=eng_verb:"haven't"{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }

#endregion V_Present_1st_Singular


// -------------------- 3е ЛИЦО ------------------------

#region V_Present_3st_Singular

// She has done
pattern V_Present_3st_Singular
{
 aux=eng_verb:have{ VERB_FORM:S }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }


// She has already done it
pattern V_Present_3st_Singular
{
 aux=eng_verb:have{ VERB_FORM:S }
 adv=SingleAdverb_PT
 v=VERB_T_AV( VERB_FORM:PP )
} : links {
           v.{
               <ATTRIBUTE>adv
               <LEFT_AUX_VERB>aux
             }
          }


// She has not done 
pattern V_Present_3st_Singular
{
 aux=eng_verb:have{ VERB_FORM:S }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }

// She hasn't done 
pattern V_Present_3st_Singular export { TRANSITIVITY (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux=eng_verb:"haven't"{ VERB_FORM:S }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }

#endregion V_Present_3st_Singular


// -------------------- МНОЖЕСТВЕННОЕ ЧИСЛО ------------------------

#region V_Present_Plural
// You have done 
pattern V_Present_Plural
{
 aux=eng_verb:have{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }
  : ngrams { 1 }

// We have already done it
pattern V_Present_Plural
{
 aux=eng_verb:have{ VERB_FORM:INF }
 adv=SingleAdverb_PT
 v=VERB_T_AV( VERB_FORM:PP )
} : links {
           v.{
               <ATTRIBUTE>adv
               <LEFT_AUX_VERB>aux
             }
          }


// We have not done 
pattern V_Present_Plural
{
 aux=eng_verb:have{ VERB_FORM:INF }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }

// They haven't done 
pattern V_Present_Plural
{
 aux=eng_verb:"haven't"{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }

#endregion V_Present_Plural



patterns PassiveInnerAdverb export { node:root_node }
pattern PassiveInnerAdverb
{
 eng_adverb:*{ [-5]PassiveInnerAdverb0 } : export { node:root_node }
}


/*
// ---------------
// passive voice
// ---------------

#region V_Present_1st_Singular
// I have been done
pattern V_Present_1st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
}
: links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// I have not been done 
pattern V_Present_1st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
}
: links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// I haven't been done
pattern V_Present_1st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:"haven't"{ VERB_FORM:INF }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
}
: links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// I have been unpleasantly surprised.
pattern V_Present_1st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 aux2='been'
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
}
: links { v.{
             <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
             <ATTRIBUTE>adv
            } }
: ngrams { 1 }


// Наречия, которые не могут стоять внутри паттерна perfect tense passive voice
// The dust has likely been blown
//              ^^^^^^
wordentry_set CantBePPInnerAdverb=
{
 eng_adverb:so{},
 eng_adverb:that{},
 eng_adverb:very{}
}

pattern V_Present_1st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 adv=eng_adverb:*{ adj_form:basic ~CantBePPInnerAdverb }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }

#endregion V_Present_1st_Singular


#region V_Present_3st_Singular
// She has been done 
pattern V_Present_3st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:S }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// The dust has likely been blown out of the disk by supernova explosions
//          ^^^^^^^^^^^^^^^^^^^^^
pattern V_Present_3st_Singular export { (TRANSITIVITY) (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:S }
 adv=eng_adverb:*{ adj_form:basic ~CantBePPInnerAdverb }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }


// She has not been done 
pattern V_Present_3st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:S }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// She hasn't been done 
pattern V_Present_3st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:"haven't"{ VERB_FORM:S }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// His name has long been forgotten.
pattern V_Present_3st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:S }
 adv=PerfectAuxAdv1
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }


// He has been unpleasantly surprised.
pattern V_Present_3st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:S }
 aux2='been'
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }





// You have been done 
pattern V_Present_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


pattern V_Present_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 adv=eng_adverb:*{ adj_form:basic ~CantBePPInnerAdverb }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }



// We have not been done 
pattern V_Present_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// They haven't been done 
pattern V_Present_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:"haven't"{ VERB_FORM:INF }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }



pattern V_Present_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 adv=PerfectAuxAdv1
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }


// They have been unpleasantly surprised.
pattern V_Present_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 aux2='been'
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }

#endregion V_Present_3st_Singular
*/


// ********************************
// PAST PERFECT TENSE
// ********************************

// --------------
// active voice
// --------------

#region V_Past_Singular
// I had asked 
pattern V_Past_Singular
{
 aux=eng_verb:have{ VERB_FORM:ED }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }


// She had quickly opened the door
pattern V_Past_Singular
{
 aux=eng_verb:have{ VERB_FORM:ED }
 adv=SingleAdverb_PT
 v=VERB_T_AV( VERB_FORM:PP )
} : links {
           v.{
               <ATTRIBUTE>adv
               <LEFT_AUX_VERB>aux
             }
          }



// She had not asked 
pattern V_Past_Singular
{
 aux=eng_verb:have{ VERB_FORM:ED }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }

// He hadn't asked 
pattern V_Past_Singular
{
 aux=eng_verb:"haven't"{ VERB_FORM:ED }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }

#endregion V_Past_Singular

#region V_Past_Plural
// We had asked 
pattern V_Past_Plural
{
 aux=eng_verb:have{ VERB_FORM:ED }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }

// They had never travelled abroad.
pattern V_Past_Plural
{
 aux=eng_verb:have{ VERB_FORM:ED }
 adv=SingleAdverb_PT
 v=VERB_T_AV( VERB_FORM:PP )
} : links {
           v.{
               <ATTRIBUTE>adv
               <LEFT_AUX_VERB>aux
             }
          }





// You had not asked 
pattern V_Past_Plural
{
 aux=eng_verb:have{ VERB_FORM:ED }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
 
// They hadn't asked 
pattern V_Past_Plural
{
 aux=eng_verb:"haven't"{ VERB_FORM:ED }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux }

#endregion V_Past_Plural

/*
// --------------
// passive voice
// --------------

#region V_Past_Singular
// I had been asked 
pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
:ngrams { 1 }


pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 adv=eng_adverb:*{ adj_form:basic ~CantBePPInnerAdverb }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
:ngrams { 1 }



// She had not been asked 
pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
:ngrams { 1 }

// Grachtengordel had not yet been established.
//                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 n=eng_particle:not{}
 adv=PassiveInnerAdverb
 aux2='been'
 v=VERB_PV( VERB_FORM:PP )
}
: links { v.{
             <LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2
             <ATTRIBUTE>adv
           }
        }
:ngrams { 2 }



// He hadn't been asked 
pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:"haven't"{ VERB_FORM:ED }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
:ngrams { 1 }



// His name had long been forgotten.
pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 adv=PerfectAuxAdv1
 aux2='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
:ngrams { 1 }


// He had been unpleasantly surprised.
pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 aux2='been'
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
:ngrams { 1 }
#endregion V_Past_Singular



#region V_Past_Plural
// We had been asked 
pattern V_Past_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


pattern V_Past_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 adv=eng_adverb:*{ adj_form:basic ~CantBePPInnerAdverb }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP TRANSITIVITY:TRANSITIVE )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }



// You had not been asked 
pattern V_Past_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// They hadn't been asked 
pattern V_Past_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:"haven't"{ VERB_FORM:ED }
 aux2='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }



// His names had long been forgotten.
pattern V_Past_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 adv=PerfectAuxAdv1
 aux2='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }


// They had been unpleasantly surprised.
pattern V_Past_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 aux2='been'
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }

#endregion V_Past_Plural
*/


// ********************************
// FUTURE PERFECT TENSE
// ********************************

// --------------------
// active voice
// --------------------

#region V_Future
// I will have asked 
pattern V_Future
{
 aux1=Will_Shall
 aux2=eng_verb:have{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

// You will not have asked 
pattern V_Future
{
 aux1=Will_Shall
 n=eng_particle:not{}
 aux2=eng_verb:have{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }

// She won't have asked 
pattern V_Future
{
 aux1=Will_Shall_Not
 aux2=eng_verb:have{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

#endregion V_Future

/*
// ---------------
// passive voice
// ---------------

#region V_Future
// I will have been asked 
pattern V_Future export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=Will_Shall
 aux2=eng_verb:have{ VERB_FORM:INF }
 aux3='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3 }
: ngrams { 1 }

// You will not have been asked 
pattern V_Future export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=Will_Shall
 n=eng_particle:not{}
 aux2=eng_verb:have{ VERB_FORM:INF }
 aux3='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3 }
: ngrams { 1 }

// She won't have been asked 
pattern V_Future export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=Will_Shall_Not
 aux2=eng_verb:have{ VERB_FORM:INF }
 aux3='been'
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3 }
: ngrams { 1 }

#endregion V_Future
*/

// ********************************
// PRESENT CONTINUOUS TENSE
// ********************************

// --------------- 
// active voice
// --------------- 
#region V_Present_1st_Singular
// I am asking 
pattern V_Present_1st_Singular
{
 aux=BeVerb{ PERSON:1 NUMBER:SINGLE VERB_FORM:UNDEF }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 2 }


// I am apparently working
pattern V_Present_1st_Singular
{
 aux=BeVerb{ PERSON:1 NUMBER:SINGLE VERB_FORM:UNDEF }
 adv=ContinuousInnerAdverb
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.{
               <LEFT_AUX_VERB>aux
               <ATTRIBUTE>adv
              } }
: ngrams { 2 }


// I am not asking 
pattern V_Present_1st_Singular
{
 aux=BeVerb{ PERSON:1 NUMBER:SINGLE VERB_FORM:UNDEF }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 2 }

/*
// I ain't asking 
pattern V_Present_1st_Singular
{
 aux=BeVerb{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 2 }
*/
#endregion V_Present_1st_Singular


#region V_Present_3st_Singular
// She is asking 
pattern V_Present_3st_Singular
{
 aux=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 2 }


// It is being polished
pattern V_Present_3st_Singular
{
 aux=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 v=eng_beverb:*{ VERB_FORM:ING }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
}
: links { v.<LEFT_AUX_VERB>aux }
: ngrams { 3 }



/*
// He apparently is coming
pattern V_Present_3st_Singular
{
 a=CopulaBeAdvModifier
 aux=BeVerb{ VERB_FORM:S }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux.<ATTRIBUTE>a }
*/

// Jane is apparently coming
pattern V_Present_3st_Singular
{
 aux=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 a=ContinuousInnerAdverb
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.{
               <LEFT_AUX_VERB>aux
               <ATTRIBUTE>a
              } }
: ngrams { 2 }





// He is not asking
pattern V_Present_3st_Singular
{
 aux=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 2 }


// It is not being polished
pattern V_Present_3st_Singular
{
 aux=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 n=eng_particle:not{}
 v=eng_beverb:be{ VERB_FORM:ING }:export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
}
: links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 3 }


/*
// He apparently is not coming
pattern V_Present_3st_Singular
{
 a=CopulaBeAdvModifier
 aux=BeVerb{ VERB_FORM:S }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux.{
                                  <NEGATION_PARTICLE>n
                                  <ATTRIBUTE>a
                                 } }
*/

/*
// He isn't asking
pattern V_Present_3st_Singular
{
 aux=BeVerb{ VERB_FORM:S }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 2 }
*/

/*
// He apparently isn't asking
pattern V_Present_3st_Singular
{
 a=CopulaBeAdvModifier
 aux=BeVerb{ VERB_FORM:S }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux.<ATTRIBUTE>a }
: ngrams { 2 }
*/

#endregion V_Present_3st_Singular


#region V_Present_Plural

// We are asking 
pattern V_Present_Plural
{
 aux=BeVerb{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 2 }


// We are currently investigating the cause 
pattern V_Present_Plural
{
 aux=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }
 adv=ContinuousInnerAdverb
 v=VERB_T_AV( VERB_FORM:ING )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux
             }
          }
: ngrams { 2 }

// We are not asking
pattern V_Present_Plural
{
 aux=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 2 }

/*
// We aren't asking 
pattern V_Present_Plural
{
 aux=BeVerb{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 2 }
*/
 
#endregion V_Present_Plural

/*
// ---------------
// passive voice
// ---------------

#region V_Present_1st_Singular
// I am being asked
pattern V_Present_1st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ PERSON:1 NUMBER:SINGLE VERB_FORM:UNDEF }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }


// I am being sharply questioned.
pattern V_Present_1st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ PERSON:1 NUMBER:SINGLE VERB_FORM:UNDEF }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 1 }



// I am not being asked 
pattern V_Present_1st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ PERSON:1 NUMBER:SINGLE VERB_FORM:UNDEF }
 n=eng_particle:not{}
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 1 }

#endregion V_Present_1st_Singular

#region V_Present_3st_Singular
// She is being asked 
pattern V_Present_3st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 3 }


// He is being sharply questioned.
pattern V_Present_3st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 3 }




// He is not being asked 
pattern V_Present_3st_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ PERSON:3 NUMBER:SINGLE VERB_FORM:UNDEF }
 n=eng_particle:not{}
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 3 }

#endregion V_Present_3st_Singular

#region V_Present_Plural
// We are being asked 
pattern V_Present_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 3 }

// We are being sharply questioned.
pattern V_Present_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 3 }




// We are not being asked 
pattern V_Present_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ NUMBER:PLURAL VERB_FORM:UNDEF }
 n=eng_particle:not{}
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 3 }

#endregion V_Present_Plural
*/


// ********************************
// PAST CONTINUOUS TENSE
// ********************************

// ---------------
// active voice 
// ---------------

#region V_Past_Singular
// I was asking 
pattern V_Past_Singular
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 3 }

// He was once living in London 
pattern V_Past_Singular
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:ING )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux
             }
          }
: ngrams { 3 }

// He was not asking           
pattern V_Past_Singular
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 3 }

/*
// It wasn't asking           
pattern V_Past_Singular
{
 aux=ENG_BEVERB:BE_not{ VERB_FORM:ED NUMBER:SINGLE }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 3 }
*/

#endregion V_Past_Singular


#region V_Past_Plural
// We were asking 
pattern V_Past_Plural
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 2 }

// We were once living in London 
pattern V_Past_Plural
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 adv=V_ADV_BETWEEN
 v=VERB_T_AV( VERB_FORM:ING )
} : links {
           v.{
              <ATTRIBUTE>adv
              <LEFT_AUX_VERB>aux
             }
          }
: ngrams { 2 }

// You were not asking           
pattern V_Past_Plural
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 n=eng_particle:not{}
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux.<NEGATION_PARTICLE>n }
: ngrams { 2 }

/*
// They weren't asking 
pattern V_Past_Plural
{
 aux=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux }
: ngrams { 2 }
*/
#endregion V_Past_Plural

/*
// ----------------
// passive voice
// ----------------

#region V_Past_Singular

// I was being asked 
pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 2 }


// She was being sharply questioned.
pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 2 }



// He was not being asked 
pattern V_Past_Singular export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ VERB_FORM:ED NUMBER:SINGLE }
 n=eng_particle:not{}
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 2 }
#endregion V_Past_Singular

#region V_Past_Plural
// We were being asked 
pattern V_Past_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 2 }

// You were not being asked 
pattern V_Past_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 n=eng_particle:not{}
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 2 }

// We were being sharply questioned.
pattern V_Past_Plural export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=BeVerb{ VERB_FORM:ED NUMBER:PLURAL }
 aux2=ENG_BEVERB:BE{ verb_form:ing }
 adv=PassiveInnerAdverb
 v=VERB_PV( VERB_FORM:PP )
} : links { v.{
               <LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2
               <ATTRIBUTE>adv
              } }
: ngrams { 2 }

#endregion V_Past_Plural
*/


// ********************************
// FUTURE CONTINUOUS TENSE
// ********************************

// -------------
// active voice
// -------------

#region V_Future

// I will be asking 
pattern V_Future
{
 aux1=Will_Shall
 aux2=ENG_BEVERB:BE{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 2 }


// You will not be asking 
pattern V_Future
{
 aux1=Will_Shall
 n=eng_particle:not{}
 aux2=ENG_BEVERB:BE{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 2 }

// They won't be asking
pattern V_Future
{
 aux1=Will_Shall_Not
 aux2=ENG_BEVERB:BE{ VERB_FORM:INF }
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 2 }


// They won't be being asked
pattern V_Future
{
 aux1=Will_Shall_Not
 aux2=ENG_BEVERB:BE{ VERB_FORM:INF }
 v=eng_beverb:*{ VERB_FORM:ING } :export{ TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS node:root_node VOICE:ACTIVE }
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }
: ngrams { 2 }



#endregion V_Future

/*
// ----------------
// passive voice
// ----------------

#region V_Future

// I will be being asked 
pattern V_Future export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=Will_Shall
 aux2=ENG_BEVERB:BE{ VERB_FORM:INF }
 aux3=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3 }
: ngrams { 1 }


// You will not be being asked 
pattern V_Future export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=Will_Shall
 n=eng_particle:not{}
 aux2=ENG_BEVERB:BE{ VERB_FORM:INF }
 aux3=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links {
           v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.
            <NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3
          }
: ngrams { 1 }


// They won't be being asked           
pattern V_Future export { (TRANSITIVITY)  (OBLIG_TRANSITIVITY) VERB_SLOTS VOICE node:root_node }
{
 aux1=Will_Shall_Not
 aux2=ENG_BEVERB:BE{ VERB_FORM:INF }
 aux3=ENG_BEVERB:BE{ verb_form:ing }
 v=VERB_PV( VERB_FORM:PP )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3 }
: ngrams { 1 }

#endregion V_Future
*/

// ********************************
// PRESENT PERFECT CONTINUOUS TENSE
// ********************************

// --------------
// active voice
// --------------

#region V_Present_1st_Singular
// I have been asking 
pattern V_Present_1st_Singular
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

// I have not been asking 
pattern V_Present_1st_Singular
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }

// I haven't been asking           
pattern V_Present_1st_Singular
{
 aux1=eng_verb:"haven't"{ VERB_FORM:INF }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

#endregion V_Present_1st_Singular


#region V_Present_3st_Singular
// She has been asking 
pattern V_Present_3st_Singular
{
 aux1=eng_verb:have{ VERB_FORM:S }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

// She has not been asking 
pattern V_Present_3st_Singular
{
 aux1=eng_verb:have{ VERB_FORM:S }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }

// She hasn't been asking           
pattern V_Present_3st_Singular
{
 aux1=eng_verb:"haven't"{ VERB_FORM:S }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

#endregion V_Present_3st_Singular


#region V_Present_Plural
// We have been asking 
pattern V_Present_Plural
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

// You have not been asking 
pattern V_Present_Plural
{
 aux1=eng_verb:have{ VERB_FORM:INF }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }

// They haven't been asking           
pattern V_Present_Plural
{
 aux1=eng_verb:"haven't"{ VERB_FORM:INF }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

#endregion V_Present_Plural


// ********************************
// PAST PERFECT CONTINUOUS TENSE
// ********************************

// ---------------
// active voice
// ---------------

#region V_Past_Singular
// I had been asking 
pattern V_Past_Singular
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

// She had not been asking 
pattern V_Past_Singular
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }

// It hadn't been asking           
pattern V_Past_Singular
{
 aux1=eng_verb:"haven't"{ VERB_FORM:ED }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

#endregion V_Past_Singular


#region V_Past_Plural
// We had been asking 
pattern V_Past_Plural
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

// You had not been asking 
pattern V_Past_Plural
{
 aux1=eng_verb:have{ VERB_FORM:ED }
 n=eng_particle:not{}
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.<NEXT_COLLOCATION_ITEM>aux2 }

// They hadn't been asking           
pattern V_Past_Plural
{
 aux1=eng_verb:"haven't"{ VERB_FORM:ED }
 aux2='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2 }

#endregion V_Past_Plural


// ********************************
// FUTURE PERFECT CONTINUOUS TENSE
// ********************************

// -------------
// active voice
// -------------

#region V_Future

// I will have been asking 
pattern V_Future
{
 aux1=Will_Shall
 aux2=eng_verb:have{ VERB_FORM:INF }
 aux3='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3 }


// She will have not been asking 
pattern V_Future
{
 aux1=Will_Shall
 aux2=eng_verb:have{ VERB_FORM:INF }
 n=eng_particle:not{}
 aux3='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.
               <NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3 }

// They will haven't been asking                  
pattern V_Future
{
 aux1=Will_Shall
 aux2=eng_verb:"haven't"{ VERB_FORM:INF }
 aux3='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3 }

// I will not have been asking
pattern V_Future
{
 aux1=Will_Shall
 n=eng_particle:not{}
 aux2=eng_verb:have{ VERB_FORM:INF }
 aux3='been'
 v=VERB_T_AV( VERB_FORM:ING )
} : links { v.<LEFT_AUX_VERB>aux1.<NEGATION_PARTICLE>n.
             <NEXT_COLLOCATION_ITEM>aux2.<NEXT_COLLOCATION_ITEM>aux3 }

#endregion V_Future
             


// ---------------
// MODAL VERBS
// ---------------

patterns V_Modal export { TRANSITIVITY VERB_SLOTS TENSE OBLIG_TRANSITIVITY node:root_node }

patterns EngModalVerb export { TRANSITIVITY VERB_SLOTS TENSE OBLIG_TRANSITIVITY node:root_node }


pattern EngModalVerb
{
 EngModalVerb0 : export { TRANSITIVITY VERB_SLOTS TENSE OBLIG_TRANSITIVITY node:root_node }
}


// You must work
//     ^^^^
pattern V_Modal
{
 aux=EngModalVerb : export { TRANSITIVITY VERB_SLOTS TENSE OBLIG_TRANSITIVITY node:root_node }
}

// You must not surrender
//     ^^^^^^^^
pattern V_Modal
{
 aux=EngModalVerb : export{ TRANSITIVITY VERB_SLOTS TENSE OBLIG_TRANSITIVITY node:root_node}
 n=eng_particle:not{}
}
: links { aux.<NEGATION_PARTICLE>n }
: ngrams { 1 }

