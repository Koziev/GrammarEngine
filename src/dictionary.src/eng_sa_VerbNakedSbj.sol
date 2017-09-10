// Идеоматические и сложившиеся сочетания существительного без артикля и глагола.

facts verb_naked_sbj language=English
{
 arity=2
 return=boolean
}


#define VerbNakedSbj(n,v) fact verb_naked_sbj { if context { eng_noun:n{} eng_verb:v{} } then return true }

VerbNakedSbj(night,fall) // Night fell.

/*
fact verb_naked_sbj
{
 if context { * * }
  then return false
}
*/