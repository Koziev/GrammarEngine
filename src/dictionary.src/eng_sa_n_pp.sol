// Устойчивые сочетания существительного и страдательного причастия после него
// в роли атрибута.

facts n_pp language=English
{
 arity=2
 return=boolean
}

// This device is byte oriented
fact n_pp
{
 if context { eng_noun:byte{} eng_verb:orient{} }
  then return true
}


/*
fact n_pp
{
 if context { * * }
  then return false
}
*/

