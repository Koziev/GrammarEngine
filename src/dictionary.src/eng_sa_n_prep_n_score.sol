facts eng_n_prep_n_score language=English
{
 arity=3
 return=integer
}

#define npn(n1,p,n2,w) \
#begin
fact eng_n_prep_n_score
{
 if context { eng_noun:n1{} eng_prep:p{} eng_noun:n2{} }
  then return w
}
#end

npn( cloud, of, dust, 5 )
npn( gradation, in, color, 5 ) // Subtle gradations in color.
npn( layer, of, rock, 5 )
npn( explosion, of, star, 5 )
npn( birth, of, star, 5 )
npn( collapse, of, star, 5 )
npn( type, of, galaxy, 5 )
npn( sheet, of, paper, 5 )
npn( threat, to, wildlife, 5 )
npn( level, of, radiation, 5 )
npn( wavelength, of, radiation, 5 )
npn( result, of, experiment, 5 )
npn( change, in, state, 5 )
npn( change, of, state, 5 )
npn( layer, of, shale, 5 )
npn( beam, of, light, 5 )
npn( chance, of, survival, 5 )
npn( remain, of, animal, 5 )
npn( environment, of, Earth, 5 )
npn(change,in,mass,2) // there is a slight change in mass and the release of a large amount of energy.
npn(release,of,energy,2)
npn(movement,of,blood,2)
npn(movement,through,body,2)
npn(competition,for,resource,2) // increased competition for resources
npn( force, of, gravity, 2 )
npn( amount, of, energy, 2 )
npn(validity,of,datum,2)
npn(root,of,tree,5)
npn( flow, of, water, 5 )
npn( unit, of, measurement, 5 )

// The good friend of mine comes today
//          ^^^^^^^^^^^^^^
fact eng_n_prep_n_score
{
 if context { eng_noun:friend{} eng_prep:of{} eng_pronoun:I{} }
  then return 2
}
