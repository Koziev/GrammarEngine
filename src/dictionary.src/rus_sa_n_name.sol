facts n_name language=Russian
{
 arity=2
 return=integer
 generic
}


// Корпорация Microsoft
fact n_name
{
 if context { существительное:корпорация{} 'Microsoft' }
  then return 1
}
