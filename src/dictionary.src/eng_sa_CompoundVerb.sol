patterns CompoundVerb export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }

pattern CompoundVerb
{
 eng_verb:*{} : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}


// Networks become under-utilized and flooded by turns. 
//                 ^^^^^
pattern CompoundVerb
{
 p=ENG_COMPOUND_PREVERB:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 v=eng_verb:*{} : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
} : links { v.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }


// Для страдательного причастия бывает такой паттерн:
// Hawke was consensus-driven;
//           ^^^^^^^^^^^^^^^^
pattern CompoundVerb
{
 p=ENG_NOUN:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 v=eng_verb:*{} : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
} : links { v.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }

// A gene for pink-colored flowers was recessive in one of the parents.
//            ^^^^^^^^^^^^
pattern CompoundVerb
{
 p=ENG_ADJECTIVE:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 v=eng_verb:*{} : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>p }
: ngrams { -1 }


// Logical disjunction is usually short-circuited;
//                                ^^^^^^^^^^^^^^^
pattern CompoundVerb
{
 a=ENG_ADVERB:*{}
 t='-'{ [-5]tokenizer_flag:word_conjunction }
 v=eng_verb:*{} : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
}
: links { v.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>a }
: ngrams
{
 eng_adv_v_score(a,v)
 eng_verb_adv_score(v,a)
}



// Skipping levels is not allowed/feasible.
//                        ^^^^^^^^^^^^^^^^
pattern CompoundVerb
{
 v=eng_verb:*{ VERB_FORM:PP } : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
 t='/'
 a=ENG_ADJECTIVE:*{}
}
: links { v.<COMPOUND_PREFIX>t.<NEXT_COLLOCATION_ITEM>a }



pattern CompoundVerb
{
 q1=OpeningQuote
 n=CompoundVerb : export { node:root_node VERB_FORM TRANSITIVITY OBLIG_TRANSITIVITY VERB_SLOTS }
 q2=ClosingQuote
} : links
{
 n.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}
