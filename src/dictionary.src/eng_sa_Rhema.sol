
patterns PostposRhema { language=English } export { node:root_node }

// It is 209 km long.
//       ^^^^^^^^^^^
pattern PostposRhema
{
 obj=PreposObject
 p=eng_postpos:*{}:export { node:root_node }
}
: links { p.<OBJECT>obj }
: ngrams { -1 }


 

// -----------------------------------------------------------------

patterns NounRhema { language=English } export { node:root_node NUMBER }

// The cat is an animal
// This cat is a wild animal
// The boy is the best runner in the school
// He is a good enough player.
pattern NounRhema
{
 NounGroup:export { node:root_node NUMBER }
}

// ---------------------------------------------------------------------


patterns SingularRhema { language=English } export { node:root_node }

// He is a champion
pattern SingularRhema
{ NounRhema{ [-1]NUMBER:SINGLE }:export { node:root_node } } 

// I am happy
pattern SingularRhema
{ AdjRhema:export { node:root_node } }


// Группа инфинитива в роли ремы:
// The only treatment is to deliver the fetus.
//                       ^^^^^^^^^^^^^^^^^^^^
pattern SingularRhema
{
 InfinitiveGroup:export { node:root_node }
}


// Who I am?
// ^^^ 
pattern SingularRhema
{
 ENG_PRONOUN:who{NOUN_FORM:BASIC CASE:NOMINATIVE } : export { node:root_node }
}

pattern SingularRhema
{
 PostposRhema : export { node:root_node }
} 


patterns What_Subclause { language=English } export { node:root_node }

// The question is what caused the accident.
pattern SingularRhema
{
 What_Subclause:export { node:root_node }
} 



patterns PluralRhema { language=English } export { node:root_node }

// We are the champions
//        ^^^^^^^^^^^^^
// Peas are an annual plant.
//          ^^^^^^^^^^^^^^^
pattern PluralRhema
{ NounRhema{ [-1]NUMBER:PLURAL }:export { node:root_node } }

// We are happy
pattern PluralRhema
{ AdjRhema:export { node:root_node } }


pattern PluralRhema
{
 ENG_PRONOUN:who{NOUN_FORM:BASIC CASE:NOMINATIVE } : export { node:root_node }
}

pattern PluralRhema
{
 PostposRhema : export { node:root_node }
} 
 
// -----------------------------------------------
patterns RhemaGroup export { node:root_node }

pattern RhemaGroup
{
 SingularRhema : export { node:root_node }
}

pattern RhemaGroup
{
 PluralRhema : export { node:root_node }
}


