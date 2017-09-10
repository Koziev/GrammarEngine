patterns WhereSubclause export { node:root_node }
pattern WhereSubclause
{
 V_Clause:export { node:root_node }
}

/*
pattern WhereSubclause
{
 CopulaClause:export { node:root_node }
}
*/

// -------------------------------------

// The pirates went to the island where the treasure was hidden
//                     ^^^^^^^^^^^^^^^^^^...
// This snake swims through the soil where it lives.
//                          ^^^^^^^^^^^^^^^...
pattern NounWithRightAdjunct
{
 n=NounGroup0:export{ node:root_node NUMBER }
 a=eng_adverb:where{}
 c=WhereSubclause
} : links { n.<ATTRIBUTE>a.<SUBORDINATE_CLAUSE>c }


