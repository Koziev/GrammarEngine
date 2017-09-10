// **************************************
// Sentences: Subject + Predicate
// **************************************

// I ask
pattern V_Clause
{
 PredicateGroup{ SUBJ_LINKED:1 } : export { node:root_node }
}
