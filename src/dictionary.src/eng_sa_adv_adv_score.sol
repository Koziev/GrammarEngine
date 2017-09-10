facts eng_adv_adv_score language=English
{
 arity=2
 return=integer
}

#define aa(m,a,w) \
#begin
fact eng_adv_adv_score
{
 if context { eng_adverb:m{} eng_adverb:a{} }
  then return w
}
#end

aa(exactly,"on time",5) // The train left exactly on time.
aa(shortly,thereafter,5) // She was guillotined shortly thereafter.
aa(seriously,ill,5) // In 1659, Pascal fell seriously ill.
aa(significantly,more,5) // The written language can be significantly more precise.
aa( straight, back, 2 ) // Go straight back
