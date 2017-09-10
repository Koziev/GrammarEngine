// Dependency Parser for English language
// CD->05.06.2009
// LC->05.01.2016



// Sentence допускает префиксацию с помощью одиночного наречия из множества AdvAsClausePrefix
// или предварение целым наречным оборотом (a.k.a. opener) с отбивкой запятой.
patterns Sentence export { node:root_node }
patterns SentenceClause export { node:root_node }


// The study was almost worthless.
pattern Sentence
{
 SentenceClause:export{node:root_node}
}


// --------------------------------------------------------------

// You know what I mean
//          ^^^^^^^^^^^
pattern What_Subclause
{
 w=eng_noun:what{}
 v=PredicateGroup0{ TRANSITIVITY:TRANSITIVE OBJ_LINKED:0 } : export { node:root_node }
} : links { v.<OBJECT>w }


// Do you know what to say?
//             ^^^^^^^^^^^
pattern What_Subclause
{
 w=eng_noun:what{}
 to=eng_particle:to{} : export { node:root_node }
 inf=BareInfinitive{ TRANSITIVITY:TRANSITIVE OBJ_LINKED:0 }
} : links { to.<INFINITIVE>inf.<OBJECT>w }


// No one knows what happens
//              ^^^^^^^^^^^^
pattern What_Subclause
{
 w=eng_noun:what{}
 v=PredicateGroup0{ PERSON:3 NUMBER:SINGLE SUBJ_LINKED:0 } : export { node:root_node }
} : links { v.<OBJECT>w }

pattern What_Subclause
{
 w=eng_noun:what{}
 v=PredicateGroup0{ NUMBER:PLURAL SUBJ_LINKED:0 } : export { node:root_node }
} : links { v.<OBJECT>w }



pattern DirectObj
{
 What_Subclause : export { node:root_node}
}

 