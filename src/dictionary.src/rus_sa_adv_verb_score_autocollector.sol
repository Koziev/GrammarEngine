// Вечером|поиграл => 1
tree_scorer language=Russian
{
 if context { "поиграл"{ class:ГЛАГОЛ }.<ATTRIBUTE>"Вечером"{ class:НАРЕЧИЕ } }
  then 1
}


