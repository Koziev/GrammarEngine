
// ******************************************** 
// SUBJECTS
// ******************************************** 

patterns Sbj_1st_Singular { language=English }
patterns Sbj_1st_Plural { language=English }
patterns Sbj_2st_Singular { language=English }
patterns Sbj_2st_Plural { language=English }
patterns Sbj_3st_Singular { language=English }
patterns Sbj_3st_Plural { language=English }

 
pattern Sbj_1st_Singular export { node:root_node }
{ PronounGroup{ NOUN_FORM:BASIC CASE:NOMINATIVE PERSON:1 NUMBER:SINGLE }:export { node:root_node } }

pattern Sbj_1st_Plural export { node:root_node }
{ PronounGroup{ NOUN_FORM:BASIC CASE:NOMINATIVE PERSON:1 NUMBER:PLURAL }:export { node:root_node } }

pattern Sbj_2st_Singular export { node:root_node }
{ PronounGroup{ NOUN_FORM:BASIC CASE:NOMINATIVE PERSON:2 NUMBER:SINGLE }:export { node:root_node } }

pattern Sbj_2st_Plural export { node:root_node }
{ PronounGroup{ NOUN_FORM:BASIC CASE:NOMINATIVE PERSON:2 NUMBER:PLURAL }:export { node:root_node } }


// ******************************************************************

pattern Sbj_3st_Singular export { node:root_node }
{ PronounGroup{ NOUN_FORM:BASIC CASE:NOMINATIVE PERSON:3 NUMBER:SINGLE }:export { node:root_node } }

pattern Sbj_3st_Plural export { node:root_node }
{ PronounGroup{ NOUN_FORM:BASIC CASE:NOMINATIVE PERSON:3 NUMBER:PLURAL }:export { node:root_node } }



// Прилагательное в роли подлежащего.
// This can be experimentally determined.
// ^^^^
pattern Sbj_3st_Singular export { node:root_node }
{
 AdjGroup : export { node:root_node }
} : ngrams { -1 }




patterns SingularNounSbj { language=English } export { node:root_node }
patterns PluralNounSbj { language=English } export { node:root_node }


// The girl sings
pattern SingularNounSbj
{
 NounGroup{ NUMBER:SINGLE } : export{node:root_node}
}



// Japan's prime minister was furious with executives at a power company
// The type and name of a variable must be explained
// The name of any variable must be explained
// The name of variable in the function is explained here
// The name of variable in function is explained here
// The name of variable is explained here
// The boy with me is Richard
// the full purchase price
// an electric brassiere warmer


// ***************************************************************

// The girls sing
// ^^^^^^^^^
pattern PluralNounSbj
{
 NounGroup{ NUMBER:PLURAL }:export{node:root_node}
}


// The commas in the text are necessary
// The prophecies in Bible are not proved
// The beverages at five o'clock are necessary
// Some of these drugs have been derived from opium
// Father had to learn how to change the baby.
// The sound of rain on the roof
// Careful tinning of the ends of wires results in a better joint when you solder them.
// I am still hoping that all will turn out well.


patterns SingularOrPluralSbj { language=English } export { node:root_node }
pattern SingularOrPluralSbj { SingularNounSbj:export{node:root_node} }
pattern SingularOrPluralSbj { PluralNounSbj:export{node:root_node} }




// Some of the cakes have been eaten by the boys
// The princes themselves danced with Cinderella
// The men, apparently in a bad mood, were in the room.
// The front and the rear are hidden
// The type and name of a variable are declared
// Both men and domestic animals are allowed
// Either men or domestic animals are allowed
// Neither men nor domestic animals are allowed
// The men, the animals and the robots are allowed
// The men, but not domestic animals are allowed
// Both wolf and rabbit have been seen
// Either man or robot are allowed
// People universally agree on this.

// By the end of the day half of us were footsore.
//                       ^^^^^^^^^^
pattern PluralNounSbj
{
 n=eng_noun:half{} : export{node:root_node}
 p=eng_prep:of{}
 i=eng_pronoun:I{ number:plural NOUN_FORM:BASIC CASE:PREPOSITIVE }
} : links { n.<PREPOS_ADJUNCT>p.<OBJECT>i }



pattern Sbj_3st_Singular export { node:root_node }
{ SingularNounSbj:export { node:root_node } }

pattern Sbj_3st_Singular export { node:root_node }
{ eng_adverb:what{}:export { node:root_node } }

// this makes sence
pattern Sbj_3st_Singular export { node:root_node }
{ eng_adjective:this{}:export { node:root_node } }

// this one works better
pattern Sbj_3st_Singular export { node:root_node }
{
 a=eng_adjective:this{}
 n=eng_numeral:one{}:export { node:root_node }
} : links { n.<ATTRIBUTE>a }

pattern Sbj_3st_Plural export { node:root_node }
{ PluralNounSbj:export { node:root_node } }



patterns Sbj_Singular { language=English }
pattern Sbj_Singular export { node:root_node } { Sbj_1st_Singular:export { node:root_node } }
pattern Sbj_Singular export { node:root_node } { Sbj_2st_Singular:export { node:root_node } }
pattern Sbj_Singular export { node:root_node } { Sbj_3st_Singular:export { node:root_node } }

patterns Sbj_Plural { language=English }
pattern Sbj_Plural export { node:root_node } { Sbj_1st_Plural:export { node:root_node } }
pattern Sbj_Plural export { node:root_node } { Sbj_2st_Plural:export { node:root_node } }
pattern Sbj_Plural export { node:root_node } { Sbj_3st_Plural:export { node:root_node } } 


patterns Sbj { language=English }
pattern Sbj export { node:root_node } { Sbj_Singular:export { node:root_node } }
pattern Sbj export { node:root_node } { Sbj_Plural:export { node:root_node } }

// Knowing the self is enlightenment.
// ^^^^^^^^^^^^^^^^
pattern Sbj_3st_Singular export { node:root_node }
{
 Gerund : export { node:root_node }
}
