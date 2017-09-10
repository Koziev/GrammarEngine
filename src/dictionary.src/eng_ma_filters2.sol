// LC->09.07.2012

#include "aa_rules.inc"

// После do not, don't, did not, didn't, cannot, can't can not, may, might, must, must not, mustn't,
// needn't, need not не может быть существительного или прилагательного
// ... 


// To be sure, he is no Einstein.
colloc_filter To_BE language=English
{
 if context { ['to'{class:eng_particle}] ['be'{class:eng_verb}] }
  then accept
}


// После 'll не может идти существительное
// we'll go to jail.
colloc_filter ENG_ArticleSingular2 language=English
{
 if context { "'ll" [eng_noun:*{}] }
  then reject
}






colloc_filter EngFilt_NEW language=English
{
 if context { [eng_verb:make{}] ['sence'{class:noun}] }
  then accept
}


// **************************************************************
// После артикля не должно идти инфинитива или -s форм глагола
// **************************************************************

colloc_filter Article_Verb_1 language=English
{
 if context { eng_article:a{} [eng_verb:*{ verb_form:inf }] }
  then reject
}

colloc_filter Article_Verb_2 language=English
{
 if context { eng_article:a{} [eng_verb:*{ verb_form:undef }] }
  then reject
}

colloc_filter Article_Verb_3 language=English
{
 if context { eng_article:the{} [eng_verb:*{ verb_form:inf }] }
  then reject
}

colloc_filter Article_Verb_4 language=English
{
 if context { eng_article:the{} [eng_verb:*{ verb_form:undef }] }
  then reject
}



// В начале предложения инфинитив перед IS не может стоять.
//
// Quarterback is the most important position on the team.
// ^^^^^^^^^^^
colloc_filter Inf_IS language=English
{
 if context { _НАЧ [eng_verb:*{ verb_form:inf }] 'is' }
  then reject
}


colloc_filter Inf_WAS language=English
{
 if context { _НАЧ [eng_verb:*{ verb_form:inf }] 'was' }
  then reject
}


colloc_filter Inf_WERE language=English
{
 if context { _НАЧ [eng_verb:*{ verb_form:inf }] 'were' }
  then reject
}



// Open it
// ^^^^^^^
colloc_filter ENG_NounPronoun language=English
{
 if context { _НАЧ [eng_noun:*{}] eng_pronoun:I{ NOUN_FORM:BASIC } }
  then reject
}




// They want to dance
//      ^^^^^^^^^^^^^
colloc_filter ENG_WantToDance language=English
{
 if context { eng_verb:want{} "to" [eng_noun:*{}] }
  then reject
}


colloc_filter ENG_ArticleSingular1 language=English
{
 if context { eng_article:a{} [eng_noun:*{number:plural}] eng_prep:*{} }
  then reject
}


colloc_filter Engprefilter_ToBeNot1 language=English
{
 if context { [ENG_NOUN:*{ NUMBER:PLURAL }] ENG_VERB:BE_NOT{ number:single } }
  then reject
}

colloc_filter Engprefilter_ToBeNot2 language=English
{
 if context { [ENG_NOUN:*{ NUMBER:SINGLE }] ENG_VERB:BE_NOT{ number:PLURAL } }
  then reject
}




// После to be может быть только PP-форма
// The boy wants to be asked
//               ^^^^^^^^^^^
colloc_filter EngPrefilter_ToBeAsked language=English
{
 if context { 'be' [eng_verb:*{ verb_form:ed }] }
  then reject
} 

colloc_filter EngPrefilter_ToBeSet1 language=English
{
 if context { 'be' [eng_verb:*{ verb_form:undef }] }
  then reject
} 

colloc_filter EngPrefilter_ToBeSet2 language=English
{
 if context { 'be' [eng_verb:*{ verb_form:inf }] }
  then reject
} 


// The boy had been asked
//         ^^^^^^^^^^^^^^
colloc_filter EngPrefilter_HaveBeenAsked language=English
{
 if context { eng_verb:have{} 'been' [eng_verb:*{ verb_form:ed }] }
  then reject
} 


// This parameter had been set
//                ^^^^^^^^^^^^
colloc_filter EngPrefilter_HaveBeenSet1 language=English
{
 if context { eng_verb:have{} 'been' [eng_verb:*{ verb_form:inf }] }
  then reject
} 


colloc_filter EngPrefilter_HaveBeenSet2 language=English
{
 if context { eng_verb:have{} 'been' [eng_verb:*{ verb_form:undef }] }
  then reject
} 


// *******************************************************************
// Для редких случаев фильтруем инфинитив после to be
//
// It had been set
//    ^^^^^^^^^^^^
// *******************************************************************
colloc_filter EngPrefilter_ToBeSet language=English
{
 if context { eng_verb:have{} 'been' [eng_verb:*{ verb_form:inf }] }
  then reject
} 



colloc_filter Engprefilter_Will1 language=English
{
 if context { [ENG_NOUN:WILL{}] ENG_VERB:*{} }
  then reject
} 

colloc_filter Engprefilter_Will2 language=English
{
 if context { [ENG_NOUN:WILL{}] ENG_ADVERB ENG_VERB }
  then reject
}




// В начале предложения, если первое слово - местоимение,
// глагол после него не может быть в pp форме.
colloc_filter ENG_I_Asked1 language=English
{
 if context { _НАЧ eng_pronoun:I{ NOUN_FORM:BASIC CASE:NOMINATIVE } [eng_verb:*{ verb_form:pp }] }
  then reject
}

// Если первое слово - существительное без вариантов, то аналогично предыдущему правилу.
colloc_filter ENG_Mary_Asked language=English
{
 if context { _НАЧ eng_noun:*{ 1 } [eng_verb:*{ verb_form:pp }] }
  then reject
}



// Усложнение предыдущих правил - если после местоимения
// идет однозначное наречие.
//
// He really messed up
//           ^^^^^^
colloc_filter ENG_I_Asked2 language=English
{
 if context { _НАЧ eng_pronoun:I{NOUN_FORM:BASIC CASE:NOMINATIVE} eng_adverb:*{1} [eng_verb:*{ verb_form:pp }] }
  then reject
}



// cats and dogs
colloc_filter ENG_And language=English
{
 if context { eng_noun:*{} [eng_verb:and{}] eng_noun:*{} }
  then reject
}



// I don't know it
colloc_filter ENG_Dont_Inf language=English
{
 if context { eng_verb:"don't"{} [eng_verb:*{verb_form:inf}] }
  then accept
}


// I don't always try it
colloc_filter ENG_Dont_Inf language=English
{
 if context { eng_verb:"don't"{} [eng_adverb:*{}] }
  then accept
}





// I don't like fish
// ^^^^^^^
colloc_filter ENG_PronounInf language=English
{
 if context { _НАЧ eng_pronoun:I{ NOUN_FORM:BASIC CASE:NOMINATIVE } [eng_verb:*{verb_form:inf}] }
  then
  {
   if context { * * [ModalCopulaVerbs] }
    then accept
   else if context { * * [ModalCopulaVerbsNot] }
    then accept
   else if context { * * [EngModalVerb] }
    then accept
  }
}




// Фильтр именительного падежа для оборотов в вопросах:
// ..., hasn't it?
// ..., don't you?
// ..., isn't he?
// ..., aren't we?
colloc_filter ENG_QuestTerminators language=English
{
 if context { ',' SpecialAuxVerbsED eng_pronoun:I{} '?' }
  then 
  {
   if context { * [*:*{ verb_form:undef }] [eng_pronoun:I{CASE:NOMINATIVE}] * }
    then accept
   else if context { * [*:*{ verb_form:ed }] [eng_pronoun:I{CASE:NOMINATIVE}] * }
    then accept
  }
}




// после WHEN не может быть undef-формы глагола (???)
// When subjects didn't behave as predicted, he deleted them from the sample.
colloc_filter ENG_When_VERB language=English
{
 if context { _НАЧ eng_adverb:when{} [eng_verb:*{ verb_form:undef }] }
  then reject
}



// ing-овые формы глагола, совпадающие с прилагательным,
// можно отфильтровать при наличии модификатора типа VERY:
// It is very amusing fact
//            ^^^^^^^
colloc_filter ENG_Very_ING language=English
{
 if context { eng_adverb:very{} [eng_verb:*{ verb_form:ing }] }
  then reject
}



// You and dad
colloc_filter ENG_And language=English
{
 if context { eng_pronoun:I{} eng_verb:and{} [eng_noun:*{}] }
  then reject
}


// оставляем только наречие:
// less interesting
// ^^^^
colloc_filter ENG_Less_Adj language=English
{
 if context { [eng_adjective:little{ adj_form:comparative }] eng_adjective:*{} }
  then reject
}

// оставляем только наречие:
// least interesting
// ^^^^^
colloc_filter ENG_Least_Adj language=English
{
 if context { [eng_adjective:little{ adj_form:superlative }] eng_adjective:*{} }
  then reject
}



// friend of mine
colloc_filter ENG_FriendOfMine language=English
{
 if context { ['friend'{class:eng_noun}] ['of'{class:eng_prep}] ['mine'{class:eng_pronoun}] }
  then accept
}

// friends of mine
colloc_filter ENG_FriendsOfMine language=English
{
 if context { ['friends'{class:eng_noun}] ['of'{class:eng_prep}] ['mine'{class:eng_pronoun}] }
  then accept
}



colloc_filter ENG_VeryBig language=English
{
 if context { ['very'{class:eng_adjective}] 'big' } // a very big dog
  then reject
}


colloc_filter Engprefilter_Gonna language=English
{
 if context { ENG_VERB:GONNA{} [ENG_NOUN] }
  then reject
}




// После ARE не может идти глагол в UNDEF:
colloc_filter Engprefilter_ARE_VERB language=English
{
 if context { "are" [eng_verb:*{ verb_form:undef }] }
  then reject
}




colloc_filter Engprefilter_THAT_IS language=English
{
 if context { [ENG_ADVERB:that{}] 'is' }
  then reject
}


// Чтобы не путать существительное BEING и вспомогательный глагол в паттернах типа I HAVE BEING ASKED
colloc_filter Engprefilter_Being_PP language=English
{
 if context { [eng_noun:being{}] eng_verb:*{ verb_form:pp } }
  then reject
}



// It's a living tree
// ^^^^^^
colloc_filter ENG_It_s1 language=English
{
 if context { 'it' ["'s"{ eng_verb:have{} }] eng_article:*{} }
  then reject
}


// Now it's awake.
colloc_filter ENG_It_s2 language=English
{
 if context { 'it' ["'s"{ eng_verb:have{} }] eng_adjective:*{} }
  then reject
}


colloc_filter ENG_It_s3 language=English
{
 if context { 'it' ["'s"{ eng_verb:have{} }] eng_noun:*{} }
  then reject
}


// It's written ideographically.
colloc_filter ENG_It_s4 language=English
{
 if context { 'it' ["'s"{ eng_verb:have{} }] eng_verb:*{ verb_form:pp } }
  then
  {
   if context { 'it' ["'s"{ eng_verb:have{} }] eng_verb:be{ verb_form:pp } }
    then accept
   else if context { 'it' ["'s"{ eng_verb:have{} }] * }
    then reject
  }
}


// It's an inherently better method
// ^^^^
colloc_filter ENG_It_s5 language=English
{
 if context { 'it' "'s"{ eng_verb:have{} } * }
  then
  {
   if context { * ["'s"] 'been' }
    then accept
   else if context { * ["'s"] * }
    then reject
  }
}






// Tell me the whole story
colloc_filter Whole_N language=English
{
 if context { ['whole'{class:eng_adjective}] ['story'{class:eng_noun}] }
  then accept
}


wordentry_set AuxVerb_TO=
{
 eng_verb:want{},
 eng_verb:need{},
 eng_verb:have{},
 eng_verb:like{}
}

colloc_filter AuxWant_To language=English
{
 if context { [AuxVerb_TO] [eng_particle:to{}] }
  then accept
}


// Do you know it?
colloc_filter Do_You language=English
{
 if context { [eng_verb:do{ verb_form:undef number:plural }] ['you'{CASE:NOMINATIVE}] }
  then accept
}



// We play the games all night long
//                   ^^^^^^^^^^^^^^
colloc_filter AllNightLong language=English
{
 if context { ['all'{class:eng_adjective}] ['night'{class:eng_noun}] ['long'{class:eng_adverb}] }
  then accept
}


// I like to dance
//   ^^^^^^^
colloc_filter LikeTo language=English
{
 if context { [eng_verb:like{}] ['to'{class:eng_particle}] }
  then accept
}


// Эвристика - после частицы TO, если нет варианта распознавания как предлог,
// может идти только инфинитив
colloc_filter ToDance1 language=English
{
 if context { 'to'{ 1 class:eng_particle } [eng_noun:*{}] }
  then reject
}

colloc_filter ToDance2 language=English
{
 if context { 'to'{ 1 class:eng_particle } [eng_adjective:*{}] }
  then reject
}



// You were very careless, weren't you?
//                         ^^^^^^^^^^^
colloc_filter ArntYou language=English
{
 if context { ["weren't"{class:eng_verb}] ['you'{NOUN_FORM:BASIC CASE:NOMINATIVE}] }
  then accept
}



// You are ready, aren't you?
//                ^^^^^^^^^^
colloc_filter ArntYou language=English
{
 if context { ["aren't"{class:eng_verb}] ['you'{NOUN_FORM:BASIC CASE:NOMINATIVE}] }
  then accept
}

// You sleep, don't you?
//            ^^^^^^^^^
colloc_filter DontYou language=English
{
 if context { ["don't"{class:eng_verb NUMBER:PLURAL }] ['you'{NOUN_FORM:BASIC CASE:NOMINATIVE}] }
  then accept
}

// You have answered the question, haven't you?
//                                 ^^^^^^^^^^^
colloc_filter HaventYou language=English
{
 if context { ["haven't"{class:eng_verb NUMBER:PLURAL }] ['you'{NOUN_FORM:BASIC CASE:NOMINATIVE}] }
  then accept
}

// You will return it, won't you?
//                     ^^^^^^^^^
colloc_filter HaventYou language=English
{
 if context { ["won't"{class:eng_verb}] ['you'{NOUN_FORM:BASIC CASE:NOMINATIVE}] }
  then accept
}

// England imports a great deal of oil.
//                 ^^^^^^^^^^^^
colloc_filter AGreatDealOf language=English
{
 if context { ['a'{class:eng_article}] ['great'{class:eng_adjective}] ['deal'{ class:eng_noun NOUN_FORM:BASIC}] }
  then accept
}

// I've got plenty of time.
colloc_filter PlentyOf language=English
{
 if context { ['plenty'{class:eng_noun}] ['of'{ class:eng_prep}] }
  then accept
}


// We saw a big black dog
//          ^^^^^^^^^
colloc_filter Black1 language=English
{
 if context { eng_adjective:*{} ['black'{class:eng_noun}] }
  then reject
}

colloc_filter Black2 language=English
{
 if context { eng_noun:*{} ['black'{class:eng_noun}] }
  then reject
}



// We did no work today.
colloc_filter Today1 language=English
{
 if context { eng_noun:*{} ['today'{class:eng_noun}] }
  then reject
}

colloc_filter Today2 language=English
{
 if context { eng_adjective:*{} ['today'{class:eng_noun}] }
  then reject
}

// I see so many dogs
colloc_filter SoMany language=English
{
 if context { ['so'{class:eng_adjective}] 'many' }
  then reject
}

// Very many old people live alone.
colloc_filter VeryOld language=English
{
 if context { 'many' ['old'{class:eng_noun}] }
  then reject
}

// your exercises
colloc_filter YourExercises language=English
{
 if context { ['your'{class:eng_pronoun NOUN_FORM:POSSESSIVE PERSON:2 NUMBER:SINGLE PRONOUN_FORM:PRE}] eng_noun:*{class:eng_noun} }
  then reject
}


colloc_filter HaveGotTo language=English
{
 if context { eng_verb:have{} 'got' ['to'{class:eng_prep}] }
  then reject
}



// They work much better now
//           ^^^^^^^^^^^
colloc_filter ENG_MuchBetter language=English
{
 if context { 'much' ['better'{ class:eng_noun }] }
  then reject
}

// It's an inherently better method
colloc_filter ENG_It_s_An language=English
{
 if context { "it" "'s" ["an"{class:eng_noun}] }
  then reject
}

// a new book
//   ^^^
colloc_filter ENG_ANewBook language=English
{
 if context { eng_article:*{} ['new'{class:eng_noun}] eng_noun:*{} }
  then reject
}

// The ancient city was staggeringly beautiful
// ^^^^^^^^^^^^^^^^
colloc_filter ENG_TheAncientCity language=English
{
 if context { eng_article:*{} ['ancient'{class:eng_noun}] eng_noun:*{} }
  then reject
}


// The storm downed several old trees along the highway
//                          ^^^^^^^^^
colloc_filter ENG_OldTrees language=English
{
 if context { ['old'{class:eng_noun}] eng_noun:*{} }
  then reject
}

// The inquiry had a wide remit
//                   ^^^^
colloc_filter ENG_AWideRemit language=English
{
 if context { eng_article:*{} ['wide'{class:eng_noun}] eng_noun:*{} }
  then reject
}


// Use a big hammer for those nails
//       ^^^
colloc_filter ENG_ABigHammer language=English
{
 if context { eng_article:*{} ['big'{class:eng_noun}] eng_noun:*{} }
  then reject
}

// We have a watch dog
//           ^^^^^
colloc_filter ENG_AWatchDog language=English
{
 if context { eng_article:*{} ['watch'{class:eng_verb}] eng_noun:*{} }
  then reject
}


// It has done the job, hasn't it?
//                             ^^ 
colloc_filter Hasnt_It language=English
{
 if context { "hasn't" ['it'{CASE:PREPOSITIVE}] '?' }
  then reject
}


// You love this game, don't you?
//                           ^^^
colloc_filter Dont_You language=English
{
 if context { "don't" 'you' '?' }
  then
  {
   if context { [eng_verb:*{verb_form:inf}] * * }
    then reject
   else if context { * ['it'{CASE:PREPOSITIVE}] * }
    then reject
  }
}


// There are horses and donkeys in the field
//                  ^^^
colloc_filter NOUN_And_NOUN language=English
{
 if context { eng_noun:*{ 1 } 'and' eng_noun:*{ 1 } }
  then
  {
   if context { * [~eng_conj:*{}] * }
    then reject
  }
}


// The view through the open window is very pretty
//                      ^^^^
colloc_filter ENG_TheOpenWindow language=English
{
 if context { eng_article:*{} ['open'{class:eng_noun}] eng_noun:*{} }
  then reject
}

// Only few products are really original
// ^^^^
colloc_filter ENG_OnlyFew language=English
{
 if context { ['only'{class:eng_adjective}] eng_adjective:*{} }
  then reject
}


// Rain tomorrow is possible, but I wouldn't bet on it
// ^^^^
// Считаем, что глагол to rain не употребляется в императиве.
colloc_filter ENG_Rain language=English
{
 if context { _НАЧ ['rain'{class:eng_verb}] }
  then reject
}


// She visits her mother weekly
//                       ^^^^^^
colloc_filter ENG_Weekly language=English
{
 if context { eng_noun:*{} ['weekly'{class:eng_noun}] }
  then reject
}

// Do answer my question now!
//                       ^^^
colloc_filter ENG_Now language=English
{
 if context { eng_noun:*{} ['now'{class:eng_noun}] }
  then reject
}


// I come to school every day
//        ^^^^^^^^^  
colloc_filter ENG_ComeTo language=English
{
 if context { eng_verb:come{} 'to' eng_verb:*{} }
  then
  {
   if context { * [eng_particle:to{}] [eng_verb:school{}] }
    then reject
  }
}


// I go to school
colloc_filter ENG_GoTo1 language=English
{
 if context { eng_verb:go{ verb_form:undef } ['to'{class:eng_particle}] }
  then reject
}


// I must go to school
colloc_filter ENG_GoTo2 language=English
{
 if context { eng_verb:go{ verb_form:inf } ['to'{class:eng_particle}] }
  then reject
}

// I must go to school
//              ^^^^^^
colloc_filter ENG_GoToSchool language=English
{
 if context { eng_verb:go{} 'to' ['school'{class:eng_verb}] }
  then reject
}



// --------------------------------------------
// I see the type and name of a variable
//                    ^^^^^^^
// --------------------------------------------

colloc_filter ENG_Verb_Of1 language=English
{
 if context { eng_verb:*{verb_form:undef} 'of' }
  then
  {
   if context { [~VerbCanBePostfixedBy_OF] * }
    then reject
  }
}

colloc_filter ENG_Verb_Of2 language=English
{
 if context { eng_verb:*{verb_form:inf} 'of' }
  then
  {
   if context { [~VerbCanBePostfixedBy_OF] * }
    then reject
  }
}





// Чтобы отсеять глагольное распознавание AND, используем постфиксный предлог
colloc_filter ENG_And_Prepos language=English
{
 if context { ['and'{class:eng_verb}] eng_prep:*{} }
  then reject
}

// You and me
colloc_filter ENG_And_Pronoun language=English
{
 if context { ['and'{class:eng_verb}] eng_pronoun:*{NOUN_FORM:BASIC} }
  then reject
}

// This is one of the most toxic substances
// ^^^^
colloc_filter ENG_ThisIs language=English
{
 if context { ['this'{class:eng_adverb}] 'is' }
  then reject
}


// They were supremely confident at the beginning of the season
colloc_filter ENG_AtThe language=English
{
 if context { ['at'{class:eng_noun}] 'the' }
  then reject
}

// Look at me
colloc_filter ENG_AtMe language=English
{
 if context { ['at'{class:eng_noun}] eng_pronoun:I{NOUN_FORM:BASIC CASE:PREPOSITIVE} }
  then reject
}


// Look at this very astronomical scene
colloc_filter ENG_AtThis1 language=English
{
 if context { ['at'{class:eng_noun}] eng_adjective:*{} }
  then reject
}

colloc_filter ENG_AtThis2 language=English
{
 if context { ['at'{class:eng_noun}] eng_adverb:*{} }
  then reject
}


// His place is farther down the road colloc_filter ENG_AtThe language=English
colloc_filter ENG_His language=English
{
 if context { _НАЧ ['his'{pronoun_form:post}] }
  then reject
}

// ****************************************************************************
// Некоторые существительные обычно не могут атрибутироваться прилагательным
// Также они позволяют однозначно отфильтровать частицу TO в препозиции.
// ****************************************************************************

#define ImmodifNoun(x) \
#begin
 colloc_filter ENG_Nothing1 language=English
 {
  if context { [eng_adjective:*{}] x }
   then reject
 }

 colloc_filter ENG_Nothing2 language=English
 {
  if context { ['to'{class:eng_particle}] x }
   then reject
 }
#end

ImmodifNoun( 'nothing' )
ImmodifNoun( 'everything' )
ImmodifNoun( 'noone' )
ImmodifNoun( 'nobody' )
ImmodifNoun( 'everyone' )
ImmodifNoun( 'everybody' )
ImmodifNoun( 'nobody' )
ImmodifNoun( 'anybody' )



// Ultimately, I have been studying Greek at evening classes.
//               ^^^^
colloc_filter ENG_IHaveBeen language=English
{
 if context { eng_pronoun:I{} [eng_verb:have{ verb_form:inf }] 'been' }
  then reject
}

// A fast train travels fast.
//   ^^^^
colloc_filter ENG_FastTrain language=English
{
 if context { ['fast'{class:eng_noun}] 'train' }
  then reject
}


// I have a lot of work to do.
colloc_filter ENG_A_Lot_Of language=English
{
 if context { ['a lot'{class:eng_adverb}] 'of' }
  then reject
}

// we need more paint
colloc_filter ENG_A_Lot_Of language=English
{
 if context { ['more'{ class:eng_adjective }] eng_noun:*{ ENG_MASS_NOUN NOUN_FORM:BASIC } }
  then accept
}

// we need some more paint
colloc_filter ENG_A_Lot_Of language=English
{
 if context { ['some'{ class:eng_adjective }] ['more'{ class:eng_adjective }] eng_noun:*{ ENG_MASS_NOUN NOUN_FORM:BASIC } }
  then accept
}

// from each other
colloc_filter ENG_A_Lot_Of language=English
{
 if context { eng_prep:from{} ['each'{class:eng_adjective}] ['other'{class:eng_adjective}] }
  then accept
}


// He is happy now
colloc_filter ENG_A_Lot_Of language=English
{
 if context { ['happy'{class:eng_adjective}] ['now'{class:eng_adverb}] }
  then accept
}

// the gout wanders through the entire body.
//                              ^^^^^^^^^^^
colloc_filter ENG_A_Lot_Of language=English
{
 if context { ['entire'{class:eng_adjective}] ['body'{class:eng_noun}] }
  then accept
}

