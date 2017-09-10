
pattern PreposObject
{
 NounGroup : export { node:root_node }
} 


// Give it to me
//            ^^
pattern PreposObject
{
 PronounGroup{ [-4]NOUN_FORM:BASIC [-4]CASE:PREPOSITIVE } : export { node:root_node }
} 


// The video was available on Adams's.
//                            ^^^^^^^
pattern PreposObject
{
 NounAdjunct1{ NOUN_FORM:POSSESSIVE } : export { node:root_node }
}


// the risk of being redundant
pattern PreposObject
{
 Gerund : export { node:root_node }
} : ngrams { -1 }


/*
pattern PreposObject
{
 NounEnumerator : export { node:root_node }
} 
*/

pattern PreposObject
{
 AdjGroup : export { node:root_node }
} 
: ngrams { -2 }

// ???
pattern PreposObject
{
 d=eng_article:*{}
 a=AdjGroup : export { node:root_node }
}
: links { a.<ATTRIBUTE>d }
: ngrams { -2 }



// The restaurant was closed down in 2001
//                                   ^^^^
pattern PreposObject
{
 num_word:*{} : export { node:root_node }
} : ngrams { -1 }


pattern PreposObject
{
 eng_particle:*{} : export { node:root_node }
} : ngrams { -10 }

pattern PreposObject
{
 eng_conj:*{} : export { node:root_node }
} : ngrams { -10 }

pattern PreposObject
{
 eng_prep:*{} : export { node:root_node }
} : ngrams { -10 }


pattern PreposObject
{
 eng_verb:*{} : export { node:root_node }
} : ngrams { -10 }


pattern PreposObject
{
 eng_adverb:*{} : export { node:root_node }
} : ngrams { -10 }


pattern PreposObject
{
 unknownentries:*{} : export { node:root_node }
} : ngrams { -10 }


// Предикат с WH-словом в роли объекта для предложной группы
// It is unknown from whom he descended;
//                    ^^^^^^^^^^^^^^^^^
pattern PreposObject
{
 @noshift( eng_pronoun:who{ CASE:PREPOSITIVE } )
 PredicateGroup : export { node:root_node }
}


