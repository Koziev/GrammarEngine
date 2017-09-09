facts adj_obj_score language=Russian
{
 arity=2
 return=integer
}

// Стали известны подробности кровавой истории...
// ^^^^^ ^^^^^^^^
fact adj_obj_score
{
 if context { прилагательное:известный{} существительное:сталь{} }
  then return -100
}

// Стали видны шатры береговой стражи.
// ^^^^^^^^^^^
fact adj_obj_score
{
 if context { прилагательное:видный{} существительное:сталь{} }
  then return -100
}
