// Сочетаемость подлежащего и глагольного сказуемого
facts eng_sbj_verb_score language=English
{
 arity=2
 return=integer
}

#define sv(n,v,w) \
#begin
fact eng_sbj_verb_score
{
 if context { eng_noun:n{} eng_verb:v{} }
  then return w
}
#end

sv( Parliament, repeal, 5 ) // Parliament repealed the Townshend Acts in 1770.
sv( earthquake, occur, 5 )
sv( evidence, emerge, 5 )
sv( theory, explain, 5 )
sv( cost, increase, 5 )
sv( plant, wilt, 5 )
sv( mass, decrease, 5 )
sv( size, decrease, 5 )
sv( magma, solidify, 5 )
sv( process, continue, 5 )
sv( work, begin, 5 ) // Work on this film began in 1976.
sv( train, leave, 2 ) // I reached the station after the train had left.
sv( analogy, illustrate, 5 )
sv( volcano, erupt, 5 )
sv( leaf, fall, 5 )
sv( intensity, decrease, 5 )
sv( Evaporation, increase, 5 )
sv( temperature, increase, 5 )
sv( statement, explain, 5 )
sv( amount, decrease, 5 )
sv( Population, increase, 5 )
sv( population, decrease, 5 )
sv( tree, grow, 2 )
sv(car,collide,2)
sv(water,evaporate,2)
sv(statement,describe,2)
sv(requirement,differ,2) // The requirement for such dress codes differ.
sv(researcher,work,2) // Researchers work in teams to make cars more fuel efficient.
sv(Lanthanum,oxidize,5)
sv(temperature,drop,5) // Frost occurs when the temperatures drop below.
sv(mutation,occur,2)
sv(organism,reproduce,2)
sv(time,fly,2) // Time flies like an arrow.
sv(prediction,prove,2) // His prediction proved quite accurate.
sv(fur,bristle,2) // The dog's fur bristled.
sv(nose,yaw,2) // The plane's nose yawed.
sv(eye,water,2) // His eyes watered.
sv(price,skyrocket,2) // Prices skyrocketed.
sv(rate,increase,2)
sv(disease,spread,2) // the season in which the disease spreads
sv(field,deflect,2)
sv(snow,lay,2) // Snow lay thick on the ground
sv( ice, melt, 5 )

