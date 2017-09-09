// уголовный|дело => 3
fact adj_noun_score
{
 if context { ПРИЛАГАТЕЛЬНОЕ:уголовный{} СУЩЕСТВИТЕЛЬНОЕ:дело{} }
  then return 2
}


// ложный|вызов => 3
fact adj_noun_score
{
 if context { ПРИЛАГАТЕЛЬНОЕ:ложный{} СУЩЕСТВИТЕЛЬНОЕ:вызов{} }
  then return 2
}


// остальной|уголь => 1
fact adj_noun_score
{
 if context { ПРИЛАГАТЕЛЬНОЕ:остальной{} СУЩЕСТВИТЕЛЬНОЕ:уголь{} }
  then return 1
}


// такой|данные => 1
fact adj_noun_score
{
 if context { ПРИЛАГАТЕЛЬНОЕ:такой{} СУЩЕСТВИТЕЛЬНОЕ:данные{} }
  then return 1
}


// добрый|день => 1
fact adj_noun_score
{
 if context { ПРИЛАГАТЕЛЬНОЕ:добрый{} СУЩЕСТВИТЕЛЬНОЕ:день{} }
  then return 1
}


// высший|образование => 1
fact adj_noun_score
{
 if context { ПРИЛАГАТЕЛЬНОЕ:высший{} СУЩЕСТВИТЕЛЬНОЕ:образование{} }
  then return 1
}


