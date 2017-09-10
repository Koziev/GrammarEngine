// Идиоматические и употребимые сочетания существительных (первое в качестве adjunct)


#define TreeScore_NounNoun( n_adjunct, n_head ) \
#begin
 tree_scorer language=English
 {
  if context { eng_noun:n_head{}.eng_noun:n_adjunct{} }
   then 1
 }
#end


TreeScore_NounNoun(catering,facility) // catering facilities
TreeScore_NounNoun(Shooting,gallery)
TreeScore_NounNoun(Writing,material)
TreeScore_NounNoun(city,center)
TreeScore_NounNoun(silk,tie) // a blue and white silk tie
TreeScore_NounNoun(Greenhouse,gas)
TreeScore_NounNoun(Disk,drive)
TreeScore_NounNoun(space,travel)
TreeScore_NounNoun(Motor,nerve)
TreeScore_NounNoun(air,route)
TreeScore_NounNoun(mountain,pass)
TreeScore_NounNoun(lamp,post)
TreeScore_NounNoun(building,material) // Her company developed a new kind of building material that withstands all kinds of weather.
TreeScore_NounNoun(interest,rate)


// Release the holdings in the dictator's bank account.
//                             ^^^^^^^^^^      ^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:account{}."dictator's"{ class:eng_noun } }
  then 1
}
