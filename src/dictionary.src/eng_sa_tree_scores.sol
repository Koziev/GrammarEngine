// LC->19.01.2016

tree_scorers CompleteSentence

// Союзное присоединение обычного глагола к модальному считаем неправильным:
// They cannot proselytize or convert among Muslims.
//      ^^^^^^             ~~~~~~~~~~
tree_scorer CompleteSentence language=English generic
{
 if context { eng_auxverb:*{}.<RIGHT_LOGIC_ITEM>eng_conj:*{}.eng_verb:*{} }
  then -5
}

/*
// Black walnut kernels are difficult to get out of the shell.
//                                           ^^^^^^
tree_scorer language=English
{
 if context { eng_verb:get{}.'out of'.eng_noun:*{} }
  then 1
}


// She trotted the horse home.
//     ^^^^^^^           ^^^^
tree_scorer language=English
{
 if context { eng_verb:trot{}.eng_adverb:home{} }
  then 1
}


// She knows this town inside out.
//     ^^^^^           ^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:know{}.eng_adverb:inside out{} }
  then 1
}


// She turned the shirt inside out.
tree_scorer language=English
{
 if context { eng_verb:turn{}.eng_adverb:inside out{} }
  then 1
}



// ************************
// a blue and white flag
// ************************

wordentry_set EngColors = eng_adjective:{
 blue, white, green, red, grey
}

tree_scorer language=English
{
 if context { EngColors.'and'.EngColors }
  then 1
}




// a small round table
tree_scorer language=English
{
 if context { eng_noun:table{}.eng_adjective:round{} }
  then 1
}


// Greenhouse gases
tree_scorer language=English
{
 if context { eng_noun:gas{}.eng_noun:Greenhouse{} }
  then 1
}


// The thrills of space travel
//                ^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:travel{}.eng_noun:space{} }
  then 1
}

// The children go to this school
//              ^^^^^
tree_scorer language=English
{
 if context { eng_verb:go{}.eng_prep:to{} }
  then 1
}


// The car drove around the corner.
//         ^^^^^^^^^^^^

// Считаем, что it's обычно соответствует все-таки it is
//
// It's a frightened child.
// ^^^^
tree_scorer language=English
{
 if context { "'s".<THEMA>"it" }
  then 1
}



// I managed his campaign for governor.
tree_scorer language=English
{
 if context { 'campaign'.'for'.'governor' }
  then 1
}


// He can win by moving faster
tree_scorer language=English
{
 if context { 'moving'{class:eng_verb}.'faster'{class:eng_adverb} }
  then 1
}


// Please accept my congratulations on your appointment.
//                  ^^^^^^^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:congratulation{}.eng_prep:on{} }
  then 1
}


// He had an influence on us.
//           ^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:influence{}.eng_prep:on{} }
  then 1
}


// Many readers have given feedback on the book.
//                         ^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:feedback{}.eng_prep:on{} }
  then 1
}

// Quantification in general is covered in the article on quantification.
//                                             ^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:article{}.eng_prep:on{} }
  then 1
}


// I have no complaints about the quality of his work, but I don't enjoy his company.
tree_scorer language=English
{
 if context { eng_noun:complaint{}.eng_prep:about{} }
  then 1
}


// I am tired
tree_scorer language=English
{
 if context { eng_verb:be{}."tired"{class:eng_adjective} }
  then 1
}



// Time flies like an arrow.
tree_scorer language=English
{
 if context { eng_verb:fly{}.<SUBJECT>eng_noun:time{} }
  then 1
}



// In this race, I managed to outrun everybody else.
//                                   ^^^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:everybody{}.eng_adjective:else{} }
  then 1
}


// I reached the station after the train had left.
//                                       ^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:have{}.eng_adverb:left{} }
  then -1
}


tree_scorer language=English
{
 if context { eng_verb:have{}."left"{ class:eng_verb } }
  then 1
}


// Hawaii's insular culture
tree_scorer language=English
{
 if context { eng_noun:culture{}."Hawaii's"{ class:eng_noun } }
  then 1
}


// He had learned English before he came to England
//        ^^^^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:learn{}.eng_noun:English{} }
  then 1
}


// I had already got home before it began to rain
//               ^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:get{}.eng_adverb:home{} }
  then -1
}


// Economics in its modern disciplinary sense
tree_scorer language=English
{
 if context { eng_prep:in{}.eng_noun:sense{}.eng_adjective:modern{} }
  then 1
}


// We always will keep this idea in our mind
//                ^^^^           ^^     ^^^^
tree_scorer language=English
{
 if context { eng_verb:keep{}.eng_prep:in{}.eng_noun:mind{} }
  then 1
}

// There isn't enough for all of us
//                        ^^^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:all{}.eng_prep:of{}."us"{ class:eng_pronoun } }
  then 1
}




// It moves much faster
tree_scorer language=English
{
 if context { "faster"{class:eng_adverb}.eng_adverb:much{} }
  then 1
}



// I chase rabbits in the field
tree_scorer language=English
{
 if context { eng_verb:chase{}.{ eng_prep:in{}.eng_noun:*{} } }
  then 1
}

// a return type
tree_scorer language=English
{
 if context { eng_noun:type{}.eng_adjective:return{} }
  then 1
}


// a void return type
tree_scorer language=English
{
 if context { eng_noun:type{}.eng_adjective:return{}.eng_adjective:void{} }
  then 1
}


// My brother's name is George
tree_scorer language=English
{
 if context { eng_noun:name{}.eng_noun:brother{}.{ ENG_POSSESSION:"'s"{} eng_pronoun:I{NOUN_FORM:POSSESSIVE PRONOUN_FORM:PRE} } }
  then 1
}


// Shuck oysters.
tree_scorer language=English
{
 if context { eng_verb:Shuck{}.eng_noun:oyster{} }
  then 1
}


// Add some extra plates to the dinner table.
// ^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:add{}.eng_adverb:some{} }
  then -1
}


// Hammer the nails in well
tree_scorer language=English
{
 if context { eng_verb:hammer{}.eng_prep:in{}.eng_noun:well{} }
  then 1
}


// Defoliate the trees with pesticides.
tree_scorer language=English
{
 if context { eng_verb:defoliate{}.eng_prep:with{}.eng_noun:pesticide{} }
  then 1
}


tree_scorer language=English
{
 if context { eng_verb:round{}.eng_prep:off{} }
  then -1
}

// Keep potatoes fresh.
tree_scorer language=English
{
 if context { eng_verb:keep{}.{ eng_noun:*{} eng_adjective:fresh{} } }
  then 1
}


// The editor improved the manuscript with his changes.
//            ^^^^^^^^                ^^^^     ^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:improve{}.eng_prep:with{}.eng_noun:change{} }
  then 1
}

// Her rudeness intensified his dislike for her.
tree_scorer language=English
{
 if context { eng_noun:dislike{}.eng_prep:for{}.eng_pronoun:I{ noun_form:basic case:prepositive } }
  then 1
}

// The weather improved toward evening.
tree_scorer language=English
{
 if context { eng_verb:improve{}.eng_prep:toward{}.eng_noun:evening{} }
  then 1
}


// She worked assiduously on the senior thesis.
//                               ^^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:thesis{}.eng_noun:senior{} }
  then 1
}


// The car gathers speed.
tree_scorer language=English
{
 if context { eng_verb:gather{}.eng_noun:speed{} }
  then 1
}


tree_scorer language=English
{
 if context { "moving"{class:eng_verb}."faster"{class:eng_adverb} }
  then 1
}

// This is the best of the three knives
//         ^^^^^^^^^^^
tree_scorer language=English
{
 if context { "best"{class:eng_adjective}.{ "the" "of" } }
  then 1
}

// Each partition acts like a separate hard drive
//                ^^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:act{}.eng_adverb:like{} }
  then 1
}


// I will work much better tomorrow
//        ^^^^      ^^^^^^
tree_scorer language=English
{
 if context { eng_verb:work{}."better"{ class:eng_adverb } }
  then 1
}


// He was visibly upset.
//    ^^^         ^^^^^
tree_scorer language=English
{
 if context { eng_verb:be{}.eng_adjective:upset{} }
  then 1
}


// The play was dramatically interesting
//          ^^^              ^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:be{}.eng_adjective:interesting{} }
  then 1
}

// My new supervisor knows how to outmaneuver the boss in most situations.
//                                ^^^^^^^^^^^          ^^^^^^^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:outmaneuver{}.eng_prep:in{}.eng_noun:situation{} }
  then 1
}



// He is playing football
tree_scorer language=English
{
 if context { eng_verb:play{}.eng_noun:football{} }
  then 1
}


// The fineness of her features
//                 ^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_pronoun:I{NOUN_FORM:POSSESSIVE}.eng_noun:feature{} }
  then 1
}



tree_scorer language=English
{
 if context { eng_verb:be{}.<RHEMA>eng_adjective:foggy{} }
  then 1
}


// She broke into the house
tree_scorer language=English
{
 if context { eng_verb:break{}.eng_prep:into{} }
  then 1
}

// This writer strikes a chord with young women.
tree_scorer language=English
{
 if context { eng_verb:strike{}.eng_prep:with{} }
  then 1
}


// The child suffocated herself with a plastic bag that the parents had left on the floor.
tree_scorer language=English
{
 if context { eng_verb:leave{}.eng_prep:on{} }
  then 1
}





// Возможен вариант распознавания to как предлога,
// но в паттерне с going отдаем преимущество частице с инфинитивом.
// We are going to stay in Athens
//        ^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:go{ verb_form:ing }.eng_particle:to{} }
  then 2
}


// I am still hoping that all will turn out well.
//            ^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:hope{}.eng_conj:that{} }
  then 1
}


// That iron gate is made of iron that came from England
//                                     ^^^^^^^^^
tree_scorer language=English
{
 if context { eng_verb:come{}.eng_prep:from{} }
  then 1
}


// Speckle the wall with tiny yellow spots.
tree_scorer language=English
{
 if context { eng_verb:speckle{}.eng_prep:with{} }
  then 1
}




// Panel the walls with wood.
tree_scorer language=English
{
 if context { eng_verb:panel{}.eng_prep:with{}.eng_noun:wood{} }
  then 1
}

// Dust the bread with flour.
tree_scorer language=English
{
 if context { eng_verb:dust{}.eng_prep:with{}.eng_noun:flour{} }
  then 1
}


// We say the bird come to the door.
tree_scorer language=English
{
 if context { eng_verb:come{}.eng_prep:to{}.eng_noun:*{} }
  then 1
}


// Tom felt his heart beat with excitement.
tree_scorer language=English
{
 if context { eng_verb:beat{}.eng_prep:with{}.eng_noun:excitement{} }
  then 1
}



// The sentence is translated without regard to the context.
//                            ^^^^^^^^^^^^^^^^^
tree_scorer language=English
{
 if context { eng_prep:without{}.eng_noun:regard{}.eng_prep:to{} }
  then 1
}


// They righted the sailboat that had capsized.
tree_scorer language=English
{
 if context { eng_noun:sailboat{}.eng_conj:that{}.eng_verb:capsize{ verb_form:pp } }
  then 1
}



// Looking Back at an Eclipsed Earth
tree_scorer language=English
{
 if context { eng_verb:look{}.eng_adverb:back{} }
  then 1
}


// She met up with her former lover.
tree_scorer language=English
{
 if context { eng_verb:meet{}.eng_adverb:up{} }
  then 1
}


// Wrap the baby before taking her out.
//                      ^^^^^^     ^^^
tree_scorer language=English
{
 if context { eng_verb:take{}.eng_adverb:out{} }
  then 1
}


// He got a bang on the head.
//          ^^^^^^^
tree_scorer language=English
{
 if context { eng_noun:bang{}.eng_prep:on{} }
  then 1
}

// The hour is getting late.
//             ^^^^^^^^^^^^
tree_scorer language=English
{
 if context { "getting".eng_adjective:*{} }
  then 1
}

// Pull the car over.
// ^^^^         ^^^^
tree_scorer language=English
{
 if context { eng_verb:pull{}.eng_noun:over{} }
  then -1
}
*/



/*
// Have you done it?
tree_scorer CompleteSentence language=English generic
{
 if context { eng_verb:*{ verb_form:inf }.'?' }
  then -5
}
*/


// ----------------------

#define TreeScore_PrepNum( prep, num ) \
#begin
 tree_scorer language=English
 {
  if context { eng_prep:prep{}.eng_numeral:num{} }
   then 1
 }
#end


// I could see you at two.
TreeScore_PrepNum(at,two)
TreeScore_PrepNum(at,three)
TreeScore_PrepNum(at,four)
TreeScore_PrepNum(at,five)
TreeScore_PrepNum(at,six)
TreeScore_PrepNum(at,seven)
TreeScore_PrepNum(at,eight)
TreeScore_PrepNum(at,nine)
TreeScore_PrepNum(at,ten)
TreeScore_PrepNum(at,eleven)

// -------------------------------------
// The prisoner's resistance weakened after seven days.

// ----------------------

#define TreeScore_NumNoun( num, noun ) \
#begin
 tree_scorer language=English
 {
  if context { eng_noun:noun{ number:plural }.eng_numeral:num{} }
   then 1
 }
#end

TreeScore_NumNoun(two,day)
TreeScore_NumNoun(three,day)
TreeScore_NumNoun(four,day)
TreeScore_NumNoun(five,day)
TreeScore_NumNoun(six,day)
TreeScore_NumNoun(seven,day)
TreeScore_NumNoun(eight,day)
TreeScore_NumNoun(nine,day)
TreeScore_NumNoun(ten,day)
TreeScore_NumNoun(eleven,day)

