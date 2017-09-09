// ПОСЛЕЛОГИ для существительных

facts postfix_score language=Russian
{
 arity=2
 return=integer
}


// человек упал лицом вниз.
//              ^^^^^^^^^^
fact postfix_score
{
 if context { существительное:лицо{ одуш:неодуш } послелог:вниз{} }
  then return 2
}

// Аркадий перевернул руки ладонями вверх.
//                         ^^^^^^^^^^^^^^
fact postfix_score
{
 if context { существительное:ладонь{} послелог:вверх{} }
  then return 2
}


