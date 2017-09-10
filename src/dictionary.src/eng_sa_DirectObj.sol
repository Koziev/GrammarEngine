
// ***********************
// DIRECT OBJECT
// ***********************


pattern DirectObj
{
 NounGroup : export { node:root_node }
}


pattern DirectObj
{
 AdjGroup : export { node:root_node }
}
: ngrams { -1 }


pattern DirectObj
{
 PronounGroup{ NOUN_FORM:BASIC CASE:PREPOSITIVE } : export { node:root_node }
}


// Fletcher exempted himself from the blanket pardon.
//                   ^^^^^^^
pattern DirectObj
{
 PronounGroup{ PRONOUN_FORM:REFLEXIVE } : export { node:root_node }
}


// -----------------------------------------------------------


// *************************************************************
// Прямое дополнение в "дательном" падеже - для многовалентных
// глаголов типа to tell в паттернах I told you the true.
// *************************************************************

patterns ActionTarget { language=English } export { node:root_node }

// I’m glad he gave us that heads up.
//                  ^^
pattern ActionTarget
{
 PronounGroup{ CASE:PREPOSITIVE } : export { node:root_node }
}


// I gave the ball a powerful kick.
//        ^^^^^^^^
pattern ActionTarget
{
 n=NounGroup : export { node:root_node }
}


// Did you offer Mary some chocolate?
//               ^^^^
pattern ActionTarget
{
 FAM_FirstName : export { node:root_node }
 //eng_noun:*{<в_класс>ThesaurusEntries:HypernymHumanName{}}: export { node:root_node }
}

// ------------------------------------------------------------


patterns RightDirectObj export { node:root_node }

// They easily forget what they've learned...
//                    ^^^^^^^^^^^^^^^^^^^^
// This causes what is called vacuum polarization.
//             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Everyone knows what the third word means.
//                ^^^^^^^^^^^^^^^^^^^^^^^^^
pattern RightDirectObj
{
 DirectObj : export { node:root_node }
} 


