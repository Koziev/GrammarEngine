facts adj_prep_gerund language=English
{
 arity=2
 return=boolean
}

#define AdjPrepGerund(a,p) fact adj_prep_gerund { if context { eng_adjective:a{} eng_prep:p{} } then return true }

AdjPrepGerund(interested,in)
AdjPrepGerund(accustomed,to)
AdjPrepGerund(afraid,of)
AdjPrepGerund(angry,about)
AdjPrepGerund(ashamed,of)
AdjPrepGerund(astonished,at)
AdjPrepGerund(averse,to)
AdjPrepGerund(aware,of)
AdjPrepGerund(bad,at)
AdjPrepGerund(brilliant,at)
AdjPrepGerund(capable,of)
AdjPrepGerund(careful,about)
AdjPrepGerund(certain,of)
AdjPrepGerund(clever,at)
AdjPrepGerund(close,to)
AdjPrepGerund(concerned,about)
AdjPrepGerund(worried,about)
AdjPrepGerund(conscious,of)
AdjPrepGerund(content,with)
AdjPrepGerund(contented,with)
AdjPrepGerund(convenient,for)
AdjPrepGerund(dependent,on)
AdjPrepGerund(disappointed,at)
AdjPrepGerund(experienced,at)
AdjPrepGerund(expert,at)
AdjPrepGerund(famous,for)
AdjPrepGerund(fit,for)
AdjPrepGerund(fond,of)
AdjPrepGerund(good,at)
AdjPrepGerund(guilty,of)
AdjPrepGerund(happy,about)
AdjPrepGerund(hesitant,about)
AdjPrepGerund(hopeless,at)
AdjPrepGerund(intent,on)
AdjPrepGerund(interested,in)
AdjPrepGerund(keen,on)
AdjPrepGerund(mad,about)
AdjPrepGerund(mistaken,in)
AdjPrepGerund(prompt,at)
AdjPrepGerund(proud,of)
AdjPrepGerund(quick,at)
AdjPrepGerund(sad,about)
AdjPrepGerund(satisfied,with)
AdjPrepGerund(sensible,about)
AdjPrepGerund(shocked,at)
AdjPrepGerund(sick,of)
AdjPrepGerund(slow,in)
AdjPrepGerund(sure,of)
AdjPrepGerund(surprised,at)
AdjPrepGerund(thrilled,about)
AdjPrepGerund(tired,of)
AdjPrepGerund(worried,about)
AdjPrepGerund(worthy,of)

/*
fact adj_prep_gerund
{
 if context { * * }
  then return false
}
*/
