// CD->31.03.2012
// LC->05.11.2015


// -----------------------------------


facts verb_prep language=English
{
 arity=2
 return=boolean
 generic
}


// Очень немногие глаголы допускают связывание с предлогом of, в частности
// распространенный оборот make of smth.

fact verb_prep
{
 if context { Verbs_Linking_OF eng_prep:of{} }
  then return true
}


// По умолчанию запретим связывание всех глаголов с of+дополнение, к примеру:
//
// I know the name of variable
// I forget the author of that book
fact verb_prep
{
 if context { *:*{} eng_prep:of{} }
  then return false, -5
}


// ****************************************************************************
// По умолчанию запрещаем связывание глаголов с предлогом 'in', за исключением
// закрытого набора глагов.
// ****************************************************************************

// -----------------------------------------------------
// I live with animals in a house
//   ^^^^              ^^
// -----------------------------------------------------
fact verb_prep
{
 if context { Verbs_Linking_IN eng_prep:in{} }
  then return true
}


// -----------------------------------------------------
// I know the name of variable in the function
//   ^^^^                      ^^
// -----------------------------------------------------
fact verb_prep
{
 if context { *:*{} eng_prep:in{} }
  then return false,-1
}

// -------------------------------------------------------------------

// Дополнение с предлогом TO разрешаем только для ограниченного набора глаголов движения

fact verb_prep
{
 if context { Verbs_Linking_TO eng_prep:to{} }
  then return true
}


fact verb_prep
{
 if context { *:*{} eng_prep:to{} }
  then return false, -5
}





// ****************************************************************************
// По умолчанию запрещаем связывание глаголов с предлогом 'at', за исключением
// закрытого набора глагов.
// ****************************************************************************

fact verb_prep
{
 if context { Verbs_Linking_AT eng_prep:at{} }
  then return true
}

// I like the tea at five o'clock
fact verb_prep
{
 if context { *:*{} eng_prep:at{} }
  then return false,-5
}

// ----------------------------------------

// I play the game with you
//   ^^^^          ^^^^
fact verb_prep
{
 if context { Verbs_Linking_WITH eng_prep:with{} }
  then return true
}

fact verb_prep
{
 if context { *:*{} eng_prep:with{} }
  then return false,-5
}



wordentry_set Verbs_Linking_WITHOUT=
{
 eng_verb:translate{}, // The sentence is translated without regard to the context.
 eng_verb:sign{}, //  Don't sign a contract without reading the fine print.
 eng_beverb:be{} // Be here at five o'clock without fail
}

fact verb_prep
{
 if context { Verbs_Linking_WITHOUT eng_prep:without{} }
  then return true
}

// По дефолту запрещаем присодение дополнения через предлог WITHOUT
fact verb_prep
{
 if context { *:*{} eng_prep:without{} }
  then return false,-5
}


fact verb_prep
{
 if context { * * }
  then return true
}



// =======================================================

facts noun_prep language=English
{
 arity=2
 return=boolean
 generic
}



// По умолчанию разрешаем связывание существительных через предлог of.
fact noun_prep
{
 if context { eng_noun:*{} eng_prep:of{} }
  then return true
}



// По умолчанию разрешаем связывание существительных через предлог in.
fact noun_prep
{
 if context { * eng_prep:in{} }
  then return true
}



// a speed of several million miles per hour.
//                            ^^^^^ ^^^
fact noun_prep
{
 if context { eng_noun:*{} eng_prep:per{} }
  then return true
}



fact noun_prep
{
 if context { * eng_prep:with{} }
  then return true
}

fact noun_prep
{
 if context { * eng_prep:without{} }
  then return true
}


// ---------------------------------------------------------
// Существительные, допускающие правое предложное дополнение
// с предлогом TO
// ---------------------------------------------------------
wordentry_set Noun2Noun_TO=eng_noun:{
duty, // Duty on automobiles depends on their value.
right, // The right to equal treatment in the criminal justice system
regard, // The sentence is translated without regard to the context.	
home, // Alberta is home to many large carnivores.
quota, // There is no quota to South Korean citizens.
release, // Initial releases into Florida failed.
response, // Jejune responses to our problems.
way, // John will be speeding on his way to Paris
answer, // Find an answer to it.
solution, // Find a solution to it.
dislike, // Although he tried to hide it, the headmaster took a strong dislike to George and me. (сущ+предлог to)
threat, // The threats to computing science
trip, // He warmed to the idea of a trip to Antarctica.
contributor,
successor, // The successor to Delors was Jacques Santer.
limitation, // What is the MAJOR limitation to the use of robots?
approach, // Two approaches to synthesis are used commercially.
train // She hopped a train to Chicago.
}


fact noun_prep
{
 if context { Noun2Noun_TO eng_prep:to{} }
  then return true
}


// ---------------------------------------------------------
// Существительные, допускающие правое предложное дополнение
// с предлогом FOR
// ---------------------------------------------------------
/*
wordentry_set Noun2Noun_FOR=eng_noun:{
desire, // An extraordinary desire for approval.
chance, // He evaluated his chances for survival rather pessimistically.
dislike, // Her rudeness intensified his dislike for her.
liking, // my liking for it
ticket, // I got a ticket for speeding.
sympathy // our sympathy for you
}

fact noun_prep
{
 if context { Noun2Noun_FOR eng_prep:for{} }
  then return true
}
*/

// A gene for pink-colored flowers was recessive in one of the parents.
//   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
fact noun_prep
{
 if context { eng_noun:*:*{} eng_prep:for{} }
  then return true
}

// ------------------

// ---------------------------------------------------------
// Существительные, допускающие правое предложное дополнение
// с предлогом ON
// ---------------------------------------------------------
wordentry_set Noun2Noun_ON=eng_noun:{
work,
war, // A countywide war on drugs.
color, // The shimmer of colors on iridescent feathers.
bang, // He got a bang on the head.
footstep, //  He heard footsteps on the porch.
view, // Extreme views on integration.
opinion, // Radical opinions on education
congratulation, // Please accept my congratulations on your appointment.
influence, // He had an influence on us.
article, // Quantification in general is covered in the article on quantification.
feedback // Many readers have given feedback on the book.
}

fact noun_prep
{
 if context { Noun2Noun_ON eng_prep:on{} }
  then return true
}


// ------------------

// ---------------------------------------------------------
// Существительные, допускающие правое предложное дополнение
// с предлогом FROM
// ---------------------------------------------------------
wordentry_set Noun2Noun_FROM=eng_noun:{
escape, // They tried to stop the escape of gas from the damaged pipe.
music, // Shut our ears against the blasting music from his car radio.
freedom, // freedom from coarse unprincipled calumny.
danger // Redirect your attention to the danger from the fundamentalists.
}

fact noun_prep
{
 if context { Noun2Noun_FROM eng_prep:from{} }
  then return true
}

// ------------------

wordentry_set Noun2Noun_ABOUT= eng_noun:{
revolution,
complaint
}

// We have no complaints about the food.
fact noun_prep
{
 if context { Noun2Noun_ABOUT eng_prep:about{} }
  then return true
}

// ------------------


wordentry_set Noun2Noun_BY=eng_noun:{
adoption, // Its adoption by society
activation,  // Bradykinin increases because of less inactivation by ACE.
separation, // The separation of mail by postal zones
replacement // The replacement of lost blood by a transfusion of donor blood.
}

fact noun_prep
{
 if context { Noun2Noun_BY eng_prep:by{} }
  then return true
}


// ------------------

// He had an influence over us.
fact noun_prep
{
 if context { eng_noun:influence{} eng_prep:over{} }
  then return true
}


// He gradually increased his control over Valencia;
//                            ^^^^^^^^^^^^
fact noun_prep
{
 if context { eng_noun:control{} eng_prep:over{} }
  then return true
}


// --------------------------------------

wordentry_set Noun2Noun_BETWEEN=eng_noun:{
difference, // an important difference between rusticity and urbanity
space, // The space between his teeth
stage, // Adolescence is a transitional stage between childhood and adulthood.
dogfight,  // Their rancor dated from a political dogfight between them.
Comparison // Comparison between human and porcine pleasures
}

fact noun_prep
{
 if context { Noun2Noun_BETWEEN eng_prep:between{} }
  then return true
}





// -----------------------------------


// A full-scale campaign against nuclear power plants.
fact noun_prep
{
 if context { eng_noun:campaign{} eng_prep:against{} }
  then return true
}


// He gave a speech as part of his installation into the hall of fame.
//                                 ^^^^^^^^^^^^^^^^^
fact noun_prep
{
 if context { eng_noun:installation{} eng_prep:into{} }
  then return true
}


fact noun_prep
{
 if context { * * }
  then return false,-5
}




// -----------------------

facts adv_prep language=English
{
 arity=2
 return=boolean
 generic
}

#define AdvPrep(a,p) fact adv_prep { if context { eng_adverb:a{} eng_prep:p{} } then return true }

AdvPrep(soon,after) // Elizabeth died soon after their return home.
AdvPrep(immediately,after) // He left immediately after his short performance.
AdvPrep(all,over) // She plastered warnings all over the wall.
AdvPrep(next,to) // You can sit next to them
AdvPrep(strictly,to) // That term refers strictly to smaller birds
AdvPrep(proportionately,to) // Your salary will rise proportionately to your workload.
AdvPrep(clear,to) // Read the book clear to the end.
AdvPrep(contrary,to) // He acted contrary to my wishes.
AdvPrep(only,to) // A privilege was granted only to him.
AdvPrep(only,for)
AdvPrep(only,on) // He went upstairs into the best rooms only on rare occasions.
AdvPrep(straight,"ahead of") // The door will be straight ahead of you
AdvPrep(according,to) // According to Spinoza, reality is perfection.
AdvPrep(prior,to) // Prior to 1700, the process of fossil formation was unknown.
AdvPrep(far,down) // He is farther down the road

fact adv_prep
{
 if context { * * }
  then return false,-10
}
