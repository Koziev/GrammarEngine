facts adv_noun_score language=Russian
{
 arity=2
 return=integer
}

#define AdvNoun(adv,n,w) \
#begin
fact adv_noun_score
{
 if context { наречие:adv{} существительное:n{} }
  then return w
}
#end

#define NounAdv(n,adv,w) \
#begin
fact adv_noun_score
{
 if context { существительное:n{} наречие:adv{} }
  then return w
}
#end

NounAdv(возвращение,домой,10)
