// Скоринг для сочетания модальных глаголов и инфинитивов

facts v_inf_score language=Russian
{
 arity=2
 return=integer
}

#define vv(v,inf,w) \
#begin
fact adj_noun_score
{
 if context { rus_verbs:v{} инфинитив:inf{} }
  then return w
}
#end


vv(хотеть,знать,2)
vv(решить,остаться,2)
vv(дать,знать,5) // дать знать о себе
vv(устроиться,работать,5)
