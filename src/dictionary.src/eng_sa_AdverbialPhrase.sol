// =======================================
// Разные наречные обороты
// =======================================

patterns AdverbialPhrase export { node:root_node }

/*
#define adv_p_n(_prep,_n) \
#begin
pattern AdverbialPhrase
{
 prep=eng_prep:_prep{} : export { node:root_node }
 n=eng_noun:_n{ number:single }
} : links { prep.<NEXT_COLLOCATION_ITEM>n }
#end


adv_p_n(in,reality) // She says she is nothing like that in reality.
adv_p_n(in,terror) // The horse reared in terror.
adv_p_n(until,yesterday) // They had never been late for school until yesterday.
adv_p_n(at,present) // I am learning English grammar at present
*/

patterns TimeWordWithCounter export { node:root_node }

pattern TimeWordWithCounter
{
 c=eng_numeral:*{}
 n=TimeWord : export { node:root_node }
}
: links { n.<ATTRIBUTE>c }

pattern TimeWordWithCounter
{
 det=eng_article:a{}
 n=eng_noun:*{ TimeWord number:single } : export { node:root_node }
}
: links { n.<ATTRIBUTE>det }

// He died less than a year later.
//         ^^^^^^^^^^^^^^^^^^^^^^
pattern TimeWordWithCounter
{
 comp=AdvComp : export { node:root_node }
 conj=eng_conj:than{}
 n=TimeWordWithCounter
}
: links { comp.<RIGHT_COMPARISON_Y>conj.<OBJECT>n }
: ngrams { 2 }


// He died six weeks later.
//         ^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 n=TimeWordWithCounter
 p=eng_postpos:*{} : export { node:root_node }
}
: links { p.<OBJECT>n }
: ngrams { 1 }






// The class did English three times a week last year
pattern AdverbialPhrase
{
 c=eng_numeral:*{}
 n1=eng_noun:time{} : export { node:root_node }
 det=eng_article:a{}
 n2=TimeWord{ number:single }
} : links
{
 n1.{
     <ATTRIBUTE>c
     <OBJECT>n2.<ATTRIBUTE>det
    }
}



// The arrow fell wide of the mark 
pattern AdverbialPhrase
{
 a=eng_adverb:wide{} : export { node:root_node }
 prep=eng_prep:of{}
 n=NounGroup{ number:single }
} : links { a.<OBJECT>prep.<NEXT_COLLOCATION_ITEM>n }


// We arrived together with our host.
pattern AdverbialPhrase
{
 a=eng_adverb:together{} : export { node:root_node }
 prep=eng_prep:with{}
 n=PreposObject
} : links { a.<OBJECT>prep.<NEXT_COLLOCATION_ITEM>n }


// Fortunately for you, I have it right here.
pattern AdverbialPhrase
{
 a1=eng_adverb:right{}
 a2=eng_adverb:here{} : export { node:root_node }
} : links { a2.<ATTRIBUTE>a1 }



// I went there only once or twice
pattern AdverbialPhrase
{
 w1=eng_adverb:only{}
 w2=eng_adverb:once{} : export { node:root_node }
 w3=eng_conj:or{}
 w4=eng_adverb:twice{}
} : links
{
 w2.{
     <ATTRIBUTE>w1
     <RIGHT_LOGIC_ITEM>w3.<NEXT_COLLOCATION_ITEM>w4
    }
}



wordentry_set NounForTimeAdv=eng_noun:{
 year,
 hour, // It lasted approximately an hour.
 day, // The caravan covered almost 100 miles each day.
 week, // He had immunity from eviction that week.
 time, // His sense of smell failed him this time.
 afternoon, // Mary is not coming to see us this afternoon
 morning, // The sun shone brightly this morning
 night, // He had been working all the night
 fall, // The bill will be considered when the Legislature reconvenes next Fall.
 second, // Then slowly exhale, over 5 seconds.
 minute, // The cinematic presentation lasts approximately 25 minutes.
 century, // Destructive earthquakes occur several times a century.
 month // I'll be going stateside next month!
}

// They haven't played football all afternoon
//                              ^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 n=NounGroup0{ NounForTimeAdv } : export { node:root_node }
}
: ngrams { AdverbialNounValency(n) }


// It lasted approximately an hour.
//           ^^^^^^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 a=eng_adverb:approximately{}
 n=NounGroup0{ NounForTimeAdv } : export { node:root_node }
} : links { n.<ATTRIBUTE>a }


// The cinematic presentation lasts approximately 25 minutes.
//                                  ^^^^^^^^^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 q=NumberGroup
 n=NounGroup0{ NounForTimeAdv } : export { node:root_node }
} : links { n.<ATTRIBUTE>q }




// Gates dropped out of Harvard at this time.
//                              ^^^^^^^^^^^^
pattern AdverbialPhrase
{
 p=eng_prep:*{} : export { node:root_node }
 n=NounGroup0{ NounForTimeAdv }
} : links { p.<OBJECT>n }


// By 1897–1898 teams of five became standard.
// ^^^^^^^^^^^^
pattern AdverbialPhrase
{
 p=eng_prep:by{} : export { node:root_node }
 n=NumberGroup
} : links { p.<OBJECT>n }



// Barry Bonds won the award three times.
//                           ^^^^^^^^^^^
pattern AdverbialPhrase
{
 c=NounEnumerator
 n=eng_noun:time{ =c:NUMBER } : export { node:root_node }
} : links { n.<ATTRIBUTE>c }
: ngrams { 1 }



wordentry_set AdjForPluralTime={eng_adjective:several{}, eng_adjective:many{}, eng_adjective:numerous{} }
// The novel has been adapted several times.
//                            ^^^^^^^^^^^^^
// The formula has been repeated many times.
//                               ^^^^^^^^^^
// The oath has been modified numerous times.
//                            ^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 c=AdjForPluralTime
 n=eng_noun:time{ NUMBER:PLURAL } : export { node:root_node }
} : links { n.<ATTRIBUTE>c }
: ngrams { 1 }


patterns TimeCounter export { node:root_node }

pattern TimeCounter
{
 AdjForPluralTime : export { node:root_node }
} 


// The PMAB meets three times a year.
//                ^^^^^^^^^^^^^^^^^^
pattern TimeCounter
{
 NounEnumerator : export { node:root_node }
} 

// Destructive earthquakes occur several times a century.
//                               ^^^^^^^^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 c=TimeCounter
 n=eng_noun:time{ NUMBER:PLURAL } : export { node:root_node }
 det=eng_article:a{}
 n2=NounForTimeAdv
}
: links { n.{ <ATTRIBUTE>c <NEXT_COLLOCATION_ITEM>n2.<ATTRIBUTE>det } }
: ngrams { 2 }



wordentry_set Once_Etc = eng_adverb:{ once, twice }
wordentry_set Noun_Once_Adv = eng_noun:{ day, month, year }

// Walk the dog twice a day.
pattern AdverbialPhrase
{
 a=Once_Etc : export { node:root_node }
 det=eng_article:a{}
 n=Noun_Once_Adv{ number:single }
} : links { a.<OBJECT>n.<ATTRIBUTE>det }
  : ngrams { 1 }



// I was learning English grammar a year ago
pattern AdverbialPhrase
{
 det=eng_article:a{}
 n='year'{ class:eng_noun }
 a='ago'{ class:eng_postpos } : export { node:root_node }
} : links { a.<ATTRIBUTE>n.<ATTRIBUTE>det }
  : ngrams { 1 }



// The band played all night long.
//                 ^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 a=eng_adjective:all{}
 n=eng_noun:day{}
 a2=eng_postpos:long{} : export { node:root_node }
} : links { a2.<OBJECT>n.<ATTRIBUTE>a }
  : ngrams { 1 }


// They ran the tapes over and over again.
pattern AdverbialPhrase
{
 w1=eng_adverb:over{} : export { node:root_node }
 conj=eng_conj:and{}
 w2=eng_adverb:over{}
 w3=eng_adverb:again{}
} : links
{ 
 w1.<RIGHT_LOGIC_ITEM>conj. 
     <NEXT_COLLOCATION_ITEM>w2.
      <ATTRIBUTE>w3
}
: ngrams { 1 }


/*
// --- ???? зачем здесь ing-паттерны?

pattern AdverbialPhrase
{
 prep=eng_prep:by{}:export { node:root_node }
 ing=eng_verb:*{ verb_form:ing }
} : links { prep.<NEXT_COLLOCATION_ITEM>ing }


// She told the whole story by singing it calmly
pattern AdverbialPhrase
{
 prep=eng_prep:by{}:export { node:root_node }
 ing=eng_verb:*{ verb_form:ing transitivity:transitive }
 obj=DirectObj
 adv=AdvGroup
} : links { prep.<NEXT_COLLOCATION_ITEM>ing.{
                                             <OBJECT>obj
                                             <ATTRIBUTE>adv
                                            } }

pattern AdverbialPhrase
{
 prep=eng_prep:by{}:export { node:root_node }
 ing=eng_verb:*{ verb_form:ing }
 adv=AdvGroup
} : links { prep.<NEXT_COLLOCATION_ITEM>ing.<ATTRIBUTE>adv }

pattern AdverbialPhrase
{
 prep=eng_prep:for{}:export { node:root_node }
 ing=eng_verb:*{ verb_form:ing}
} : links { prep.<NEXT_COLLOCATION_ITEM>ing }

// Is there a tool for cleaning the floor? 
pattern AdverbialPhrase
{
 prep=eng_prep:for{}:export { node:root_node }
 ing=eng_verb:*{ verb_form:ing transitivity:transitive }
 obj=DirectObj
} : links { prep.<NEXT_COLLOCATION_ITEM>ing.<OBJECT>obj }
*/



// ---------------------------------------------------------------------
// Наречные паттерны с семантикой времени
// ---------------------------------------------------------------------

wordentry_set DayOfWeek=
{
 eng_noun:Sunday{},
 eng_noun:Monday{},
 eng_noun:Tuesday{},
 eng_noun:Wednesday{},
 eng_noun:Thursday{},
 eng_noun:Friday{},
 eng_noun:Saturday{}
}


// He takes English lessons on Mondays and Fridays as well.
pattern AdverbialPhrase
{
 prep=eng_prep:on{} : export { node:root_node }
 n1=DayOfWeek{number:plural}
 conj=eng_conj:and{}
 n2=DayOfWeek{number:plural}
 as=eng_adverb:as{}
 well=eng_adverb:well{}
} : links
{
 prep.<OBJECT>n1.
       <RIGHT_LOGIC_ITEM>conj.
        <NEXT_COLLOCATION_ITEM>n2.
         <ATTRIBUTE>as.
          <NEXT_COLLOCATION_ITEM>well
}
: ngrams { 3 }



// I met George twenty years then.
pattern AdverbialPhrase
{
 c=eng_numeral:*{}
 y=eng_noun:year{}
 adv=eng_adverb:then{} : export { node:root_node }
} : links { adv.<ATTRIBUTE>y.<ATTRIBUTE>c }



wordentry_set AdjForTimeWord =
{
 eng_adjective:last{},
 eng_adjective:every{}, // The Executive Board normally meets every Tuesday.
 eng_adjective:next{},
 eng_adjective:previous{},
 eng_adjective:all{}, 
 eng_adjective:following{} // Newspapers reported his ennoblement the following morning.
}


// He dutifully visited his mother every Sunday.
//                                 ^^^^^^^^^^^^
pattern AdverbialPhrase
{
 a=AdjForTimeWord
 n=DayOfWeek : export { node:root_node }
}
: links { n.<ATTRIBUTE>a }
: ngrams { 1 }


wordentry_set TimePostfix=
{
 eng_noun:"a.m."{},
 eng_noun:"p.m."{}
}

// Let's meet at 8 P.M.
// Let's meet at 11 A.M.
pattern AdverbialPhrase
{
 prep=eng_prep:at{}:export { node:root_node }
 c=num_word:*{}
 x=TimePostfix
}
: links { prep.<OBJECT>x.<ATTRIBUTE>c }
: ngrams { 5 }



patterns OClock export { node:root_node }
pattern OClock
{
 c=eng_numeral:*{NUMERAL_FORM:CARDINAL} : export { node:root_node }
 n=eng_noun:"o'clock"{}
} : links { c.<NEXT_COLLOCATION_ITEM>n }


pattern OClock
{
 c=num_word:*{} : export { node:root_node }
 n=eng_noun:"o'clock"{}
} : links { c.<NEXT_COLLOCATION_ITEM>n }

// Предлоги, которые участвуют в паттернах с o'clock для образования
// наречного предложного оборота.
wordentry_set PreposOClock=eng_prep:{
 by, // She thinks she may finish her work by seven o'clock
 at, // She drinks the tea at five o'clock
 until // Richard slept until nine o'clock
}

// Richard slept until nine o'clock
// Richard slept until 9 o'clock
pattern AdverbialPhrase
{
 prep=PreposOClock:export { node:root_node }
 t=OClock
}
: links { prep.<OBJECT>t }
: ngrams { 1 }


/*
// You sang it last night
pattern AdverbialPhrase
{
 a=eng_adjective:last{}
 n=eng_noun:night{number:single}:export { node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }

// The girl comes here every day
pattern AdverbialPhrase
{
 a=eng_adjective:every{}
 n=eng_noun:day{number:single}:export { node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }


// I drink tea every morning
pattern AdverbialPhrase
{
 a=eng_adjective:every{}
 n=eng_noun:morning{number:single}:export { node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }
*/


/*
// He read a chapter every night before falling asleep.
pattern AdverbialPhrase
{
 a=eng_adjective:every{}
 n=eng_noun:night{number:single}:export { node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }
*/

/*
// I woke very early this morning
pattern AdverbialPhrase
{
 a=eng_adjective:this{}
 n=eng_noun:morning{number:single}:export { node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }



// They started with us last year
pattern AdverbialPhrase
{
 a=eng_adjective:last{}
 n=eng_noun:year{ number:single }:export { node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }
*/


// Try this one more time.
pattern AdverbialPhrase
{
 w1=eng_numeral:one{}:export { node:root_node }
 w2=eng_adverb:more{}
 n=eng_noun:time{ number:single }
} : links { w1.<NEXT_COLLOCATION_ITEM>w2.<NEXT_COLLOCATION_ITEM>n }







// The man with the hat chased the dog on Tuesday
pattern AdverbialPhrase
{
 prep=eng_prep:on{}:export{ node:root_node }
 d=DayOfWeek
} : links { prep.<OBJECT>d }



// I could see you at eight.
pattern AdverbialPhrase
{
 prep=eng_prep:at{}:export{ node:root_node }
 c=eng_numeral:*{NUMERAL_FORM:CARDINAL}
}
: links { prep.<OBJECT>c }
: ngrams { 1 }


// I have known him since 1968.
//                  ^^^^^^^^^^
pattern AdverbialPhrase
{
 prep=eng_prep:since{}:export{ node:root_node }
 n=num_word:*{}
}
: links { prep.<OBJECT>n }
: ngrams { 1 }

// I have known her since last year.
//                  ^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 prep=eng_prep:since{}:export{ node:root_node }
 a=eng_adjective:last{}
 n=eng_noun:year{ number:singLe }
} : links { prep.<NEXT_COLLOCATION_ITEM>n.<ATTRIBUTE>a }
  : ngrams { 2 }



// In the year 2072, the program was restarted
pattern AdverbialPhrase
{
 prep=eng_prep:in{}:export{ node:root_node }
 det=eng_article:the{}
 y=eng_noun:year{ number:single }
 c=num_word:*{}
} : links { prep.<NEXT_COLLOCATION_ITEM>y.{
                                           <NEXT_COLLOCATION_ITEM>c
                                           <ATTRIBUTE>det
                                          } }




// We have been the students for 6 years
//                           ^^^^^^^^^^^
pattern AdverbialPhrase
{
 prep=eng_prep:for{}:export{ node:root_node }
 c=NumberGroup
 y=TimeWord
} : links { prep.<OBJECT>y.<ATTRIBUTE>c }

pattern AdverbialPhrase
{
 prep=eng_prep:for{}:export{ node:root_node }
 c=eng_numeral:*{}
 y=TimeWord
} : links { prep.<NEXT_COLLOCATION_ITEM>y.<NEXT_COLLOCATION_ITEM>c }


pattern AdverbialPhrase
{
 prep1=eng_prep:for{}:export{ node:root_node }
 c1=num_word:*{}
 prep2=eng_prep:to{}
 c2=num_word:*{}
 y=TimeWord
} : links { prep1.<NEXT_COLLOCATION_ITEM>c1.<NEXT_COLLOCATION_ITEM>prep2.<NEXT_COLLOCATION_ITEM>c2.<NEXT_COLLOCATION_ITEM>y }


pattern AdverbialPhrase
{
 prep1=eng_prep:for{}:export{ node:root_node }
 c1=eng_numeral:*{}
 prep2=eng_prep:to{}
 c2=eng_numeral:*{}
 y=TimeWord
} : links { prep1.<NEXT_COLLOCATION_ITEM>c1.<NEXT_COLLOCATION_ITEM>prep2.<NEXT_COLLOCATION_ITEM>c2.<NEXT_COLLOCATION_ITEM>y }



// From 1945 through 1991
pattern AdverbialPhrase
{
 prep1=eng_prep:from{}:export{ node:root_node }
 c1=num_word:*{}
 prep2=eng_prep:through{}
 c2=num_word:*{}
} : links { prep1.<NEXT_COLLOCATION_ITEM>c1.<NEXT_COLLOCATION_ITEM>prep2.<NEXT_COLLOCATION_ITEM>c2 }


// Snowfall mainly occurs from December through March.
//                        ^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 prep1=eng_prep:from{}:export{ node:root_node }
 c1=MonthName
 prep2=eng_prep:through{}
 c2=MonthName
} : links { prep1.<NEXT_COLLOCATION_ITEM>c1.<NEXT_COLLOCATION_ITEM>prep2.<NEXT_COLLOCATION_ITEM>c2 }




// I went there all by myself
//              ^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 a=eng_adverb:all{}
 prep=eng_prep:by{}:export{ node:root_node }
 n=eng_pronoun:I{PRONOUN_FORM:REFLEXIVE}
} : links { prep.{
                  <ATTRIBUTE>a
                  <OBJECT>n
                 } }
  : ngrams { 1 }


// I can do it by myself
//             ^^^^^^^^^
pattern AdverbialPhrase
{
 prep=eng_prep:by{}:export{ node:root_node }
 n=eng_pronoun:I{PRONOUN_FORM:REFLEXIVE}
} : links { prep.<OBJECT>n }


// Each partition acts like a separate hard drive
// Their manes streamed like stiff black pennants in the wind.
// The book like this one
pattern AdverbialPhrase
{
 p=eng_conj:like{}:export{node:root_node}
 n=PreposObject
} : links { p.<NEXT_COLLOCATION_ITEM>n }


/*
// The girl like you 
pattern AdverbialPhrase
{
 p=eng_adverb:like{}:export{node:root_node}
 n=eng_pronoun:I{ case:prepositive }
} : links { p.<NEXT_COLLOCATION_ITEM>n }
*/

// Let us open these boxes one by one
pattern AdverbialPhrase
{
 x=eng_numeral:one{}:export{node:root_node}
 prep=eng_prep:by{}
 y=eng_numeral:one{}
} : links { x.<NEXT_COLLOCATION_ITEM>prep.<NEXT_COLLOCATION_ITEM>y }

// We were shown the process step by step.
pattern AdverbialPhrase
{
 x=eng_noun:step{}:export{node:root_node}
 prep=eng_prep:by{}
 y=eng_noun:step{}
} : links { x.<NEXT_COLLOCATION_ITEM>prep.<NEXT_COLLOCATION_ITEM>y }


/*
// His sense of direction leads us unerringly every time.
//                                            ^^^^^^^^^^
// Each time they performed perfectly.
// ^^^^^^^^^
pattern AdverbialPhrase
{
 a=eng_adjective:*{ adj_form:basic }
 n=eng_noun:time{}:export{node:root_node}
}
: links { n.<ATTRIBUTE>a }
: ngrams { 2 }
*/


// I see him twice a week.
//           ^^^^^^^^^^^^
pattern AdverbialPhrase
{
 c=eng_adverb:twice{}:export{node:root_node}
 det=eng_article:a{}
 n=eng_noun:week{ number:single }
} : links { c.<NEXT_COLLOCATION_ITEM>n.<ATTRIBUTE>det }




// It was still raining five minutes ago.
//                      ^^^^^^^^^^^^^^^^
// They died almost 400 million years ago.
//           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 c=NounEnumerator
 n=TimeWord
 a=eng_postpos:ago{}:export{node:root_node}
} : links { a.<OBJECT>n.<ATTRIBUTE>c }
  : ngrams { 1 }

/*
// It was still raining 5 minutes ago.
pattern AdverbialPhrase
{
 c=num_word:*{}:export{node:root_node}
 n=TimeWord
 a=eng_adverb:ago{}
} : links { c.<NEXT_COLLOCATION_ITEM>n.<NEXT_COLLOCATION_ITEM>a }
*/

// I solved the problem theoretically rather than practically.
pattern AdverbialPhrase
{
 a1=eng_adverb:*{}:export{node:root_node}
 a2=eng_adverb:rather{}
 conj=eng_conj:than{}
 a3=eng_adverb:*{}
} : links { a1.<NEXT_COLLOCATION_ITEM>a2.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>a3 }

// These days everyone can make a movie
pattern AdverbialPhrase
{
 a='these'
 n='days':export{node:root_node}
} : links { n.<ATTRIBUTE>a }


/*
// This evening I'm going to the movies
pattern AdverbialPhrase
{
 a='this'
 n=eng_noun:evening{number:single}:export{node:root_node}
} : links { n.<ATTRIBUTE>a }

// There is some bad news in the paper this morning
pattern AdverbialPhrase
{
 a='this'
 n=eng_noun:morning{number:single}:export{node:root_node}
} : links { n.<ATTRIBUTE>a }

// I hope you won't be feeling too tired after being up all night
pattern AdverbialPhrase
{
 a='all'
 n=eng_noun:night{number:single}:export{node:root_node}
} : links { n.<ATTRIBUTE>a }
*/


// We play the games all night long
pattern AdverbialPhrase
{
 a='all'
 n=eng_noun:night{number:single}:export{node:root_node}
 a2=eng_adverb:long{}
} : links { n.<ATTRIBUTE>a.<ATTRIBUTE>a2 }


/*
// The ore boat sailed upbound through the locks last week.
// The class did English three times a week last year
//                                          ^^^^^^^^^
// He's been digging in the garden all morning
//                                 ^^^^^^^^^^^
// His sense of direction lead us unerringly every time
//                                           ^^^^^^^^^^
// I'll be going stateside next month!  
//                         ^^^^^^^^^^
pattern AdverbialPhrase
{
 a=AdjForTimeWord
 n=TimeWord:export{node:root_node}
}
: links { n.<ATTRIBUTE>a }
: ngrams { 1 }
*/


// I run as fast as possible
pattern AdverbialPhrase
{
 conj1=eng_conj:as{}
 a1=eng_adverb:*{ ADJ_FORM:BASIC }:export{node:root_node}
 conj2=eng_conj:as{}
 a2=eng_adjective:possible{}
} : links {
           a1.{
               <PREFIX_CONJUNCTION>conj1
               <RIGHT_LOGIC_ITEM>conj2.<NEXT_COLLOCATION_ITEM>a2
              }
          }



// My pup likes to run as fast as he can
pattern AdverbialPhrase
{
 conj1=eng_conj:as{}
 a1=eng_adverb:*{ ADJ_FORM:BASIC }:export{node:root_node}
 conj2=eng_conj:as{}
 sbj=eng_pronoun:I{case:nominative}
 v=eng_auxverb:*{}
} : links {
           a1.{
               <PREFIX_CONJUNCTION>conj1
               <RIGHT_LOGIC_ITEM>conj2.<SUBORDINATE_CLAUSE>v.<SUBJECT>sbj
              }
          }





// The children sagged their bottoms down even more comfortably.
pattern AdverbialPhrase
{
 even=eng_adverb:even{}
 more='more'{class:eng_adverb}
 adv=eng_adverb:*{ adj_form:basic COMPARABILITY:ANALYTIC } : export { node:root_node }
} : links { adv.<ATTRIBUTE>more.<ATTRIBUTE>even }
  : ngrams { 2 }


// Her bad deed followed her and haunted her dreams all her life.
pattern AdverbialPhrase
{
 all=eng_adjective:all{}
 p=eng_pronoun:I{ NOUN_FORM:POSSESSIVE }
 life='life'{class:eng_noun} : export { node:root_node }
} : links
{
 life.{
       <ATTRIBUTE>p.
       <ATTRIBUTE>all
      }
}
: ngrams { 2 }

/*
// We ran the ad three times.
//               ^^^^^^^^^^^
pattern AdverbialPhrase
{
 c=NounEnumerator
 n=eng_noun:time{ =c:NUMBER } : export { node:root_node }
} : links { n.<ATTRIBUTE>c }
  : ngrams { 1 }
*/

// My birthday is on Thursday, the 15th of May.
pattern AdverbialPhrase
{
 prep=eng_prep:on{} : export { node:root_node }
 d=DayOfWeek{ number:single }
 comma=','
 det=eng_article:the{}
 c=@regex( "[0-9]+th" )
 prep2=eng_prep:of{}
 m=MonthName 
} : links
{
 prep.<OBJECT>d.
       <RIGHT_LOGIC_ITEM>comma.
                          <NEXT_COLLOCATION_ITEM>c.{
                                                    <ATTRIBUTE>det
                                                    <PREPOS_ADJUNCT>prep2.<OBJECT>m
                                                   }
}
 : ngrams { 2 }



// Паттерн с семантикой "со скоростью":
//
// A massive black hole is being ejected from its host galaxy at a speed of several million miles per hour.
//                                                            ^^^^^^^^^^^....
pattern AdverbialPhrase
{
 prep=eng_prep:at{} : export { node:root_node }
 det=eng_article:a{}
 n='speed'{ class:eng_noun }
 prep2=PreposPhrase
} : links { prep.<OBJECT>n.{
                                  <ATTRIBUTE>det
                                  <PREPOS_ADJUNCT>prep2
                                 } }
: ngrams { 2 }



// The religious scene in England has changed in the last century.
pattern AdverbialPhrase
{
 prep=eng_prep:in{} : export { node:root_node }
 det=eng_article:the{}
 a=eng_adjective:last{}
 n=TimeWord
} : links { prep.<OBJECT>n.{
                                  <ATTRIBUTE>det
                                  <ATTRIBUTE>a
                                 } }
: ngrams { 2 }

// Russell resigned on 26 June.
//                  ^^^^^^^^^^
pattern AdverbialPhrase
{
 prep=eng_prep:*{} : export { node:root_node }
 n=num_word:*{}
 m=MonthName
}
: links { prep.<OBJECT>m.<ATTRIBUTE>n }
: ngrams { 6 }


// It was established on 10 April 1997.
//                    ^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 prep=eng_prep:*{} : export { node:root_node }
 n=num_word:*{}
 m=MonthName
 y=num_word:*{}
}
: links { prep.<OBJECT>m.{ <ATTRIBUTE>n <ATTRIBUTE>y } }
: ngrams { 7 }


// Davis died on November 5, 2000.
//            ^^^^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 prep=eng_prep:*{} : export { node:root_node }
 m=MonthName
 n=num_word:*{}
 comma=','
 y=num_word:*{}
}
: links { prep.<OBJECT>m.{ <ATTRIBUTE>n <ATTRIBUTE>y.<PUNCTUATION>comma } }
: ngrams { 1 }


// It was cancelled in October, 1942.
//                  ^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 prep=eng_prep:*{} : export { node:root_node }
 m=MonthName
 comma=','
 y=num_word:*{}
}
: links { prep.<OBJECT>m.<ATTRIBUTE>y.<PUNCTUATION>comma }
: ngrams { 1 }


// They appear Monday through Saturday;
//             ^^^^^^^^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 n1=DayOfWeek : export { node:root_node }
 prep=eng_prep:through{}
 n2=DayOfWeek
}
: links { n1.<PREPOS_ADJUNCT>prep.<OBJECT>n2 }



// ----------------------------------
// Наречные паттерны со словом HOW
// ----------------------------------
patterns HOW_AdvPhrase { language=English } export { node:root_node }


patterns InfinitiveAction { language=English } export { node:root_node node:verb }

// John has learned how to write English
pattern HOW_AdvPhrase
{
 how=eng_adverb:how{} : export { node:root_node }
 inf=InfinitiveAction
} : links { how.<INFINITIVE>inf }


// --------------------------------------------------------

patterns AS_AdvPhrase export { node:root_node }

// When subjects didn't behave as predicted, he deleted them from the sample.
//                             ^^^^^^^^^^^^
// This plan didn't work as he forecasted.
//                       ^^^^^^^^^^^^^^^^
pattern AS_AdvPhrase
{
 how=eng_conj:as{} : export { node:root_node }
 clause=PredicateGroup
} : links { how.<SUBORDINATE_CLAUSE>clause }


// Our people will not sit back as silent spectators.
pattern AS_AdvPhrase
{
 how=eng_conj:as{} : export { node:root_node }
 n=NounGroup
} : links { how.<OBJECT>n }

// Add water as needed.
//           ^^^^^^^^^
pattern AS_AdvPhrase
{
 how=eng_conj:as{} : export { node:root_node }
 pp=PastParticipleGroup
} : links { how.<SUBORDINATE_CLAUSE>pp }


pattern AdverbialPhrase
{
 AS_AdvPhrase:export { node:root_node }
}


// --------------------------------------------------------

patterns ASIF_AdvPhrase export { node:root_node }

pattern ASIF_AdvPhrase
{
 as=eng_conj:as{} : export { node:root_node }
 if=eng_conj:if{}
 clause=V_Clause
} : links { as.<NEXT_COLLOCATION_ITEM>if.<SUBORDINATE_CLAUSE>clause }

/*
 // It's been raining for two days and it looks as if it would never stop
 pattern ASIF_AdvPhrase
 {
  as=eng_conj:as{} : export { node:root_node }
  if=eng_conj:if{}
  clause=VModal_Clause
 } : links { as.<NEXT_COLLOCATION_ITEM>if.<SUBORDINATE_CLAUSE>clause }
*/

pattern AdverbialPhrase
{
 ASIF_AdvPhrase:export { node:root_node }
}

// --------------------------------------------------------

// Наречная группа в виде придаточного предложения с WHEN:

patterns WHEN_AdvPhrase { language=English } export { node:root_node }

//patterns CopulaClause { language=English } export { node:root_node }

/*
// Tom spoke French when he was ten years old
pattern WHEN_AdvPhrase
{
 how=eng_adverb:when{} : export { node:root_node }
 subclause=CopulaClause
} : links { how.<SUBORDINATE_CLAUSE>subclause }
*/

// When he saw his axe, he smiled happily
pattern WHEN_AdvPhrase
{
 w=eng_adverb:when{} : export { node:root_node }
 subclause=V_Clause
} : links { w.<SUBORDINATE_CLAUSE>subclause }


// Minimize redesign when extending the database structure.
//                   ^^^^^^^^^^^^^^^...
pattern WHEN_AdvPhrase
{
 w=eng_adverb:when{} : export { node:root_node }
 subclause=Gerund
} : links { w.<SUBORDINATE_CLAUSE>subclause }

// When ordered to strip, he hesitated.
// ^^^^^^^^^^^^^^^^^^^^^^
pattern WHEN_AdvPhrase
{
 w=eng_adverb:when{} : export { node:root_node }
 subclause=PastParticipleGroup
} : links { w.<SUBORDINATE_CLAUSE>subclause }

// It was originally 793 carats when uncut.
pattern WHEN_AdvPhrase
{
 w=eng_adverb:when{} : export { node:root_node }
 subclause=AdjGroup
}
: links { w.<SUBORDINATE_CLAUSE>subclause }
: ngrams { -2 }


// --------------------------------------------------

// оборот со сравнительным наречием
// Light travels much faster than sound

patterns AdvCompPhrase { language=English } export { node:root_node }
pattern AdvCompPhrase
{
 adv=AdvComp:export{node:root_node}
 conj=eng_conj:than{}
 n=NounGrpWithoutArticle
} : links { adv.<ATTRIBUTE_EXC>conj.<NEXT_COLLOCATION_ITEM>n }


// --------------------------------------------------------

patterns AdverbialOfOpinion { language=English } export { node:root_node }

// He is by no means a wicked man.
//       ^^^^^^^^^^^
pattern AdverbialOfOpinion
{
 prep=eng_prep:by{}:export { node:root_node }
 no=eng_particle:no{}
 n=eng_noun:mean{ number:plural }
} : links { prep.<NEXT_COLLOCATION_ITEM>no.<NEXT_COLLOCATION_ITEM>n }


pattern AdverbialPhrase
{
 AdverbialOfOpinion:export { node:root_node }
}



// ---------------------------------------
// Наречные фразы с паттерном AS .... AS
// ---------------------------------------


patterns AS_AS_Subclause { language=English } export { node:root_node }

// He sings the song almost as loud as I do
pattern AS_AS_Subclause
{
 p=eng_pronoun:I{ noun_form:basic case:nominative person:1 NUMBER:SINGLE } 
 v=eng_verb:*{ verb_form:undef number:single person:1 } : export { node:root_node }
} : links { v.<SUBJECT>p }

// I sing the song almost as loud as he does
pattern AS_AS_Subclause
{
 p=eng_pronoun:I{ noun_form:basic case:nominative person:3 }
 v=eng_verb:*{ verb_form:undef number:single person:3 } : export { node:root_node }
} : links { v.<SUBJECT>p }

// I sing the song almost as loud as they do
pattern AS_AS_Subclause
{
 p=eng_pronoun:I{ noun_form:basic case:nominative number:plural }
 v=eng_verb:*{ verb_form:undef number:plural } : export { node:root_node }
} : links { v.<SUBJECT>p }

// I sang the song almost as loud as he did
pattern AS_AS_Subclause
{
 p=eng_pronoun:I{ noun_form:basic case:nominative }
 v=eng_verb:*{ verb_form:ed } : export { node:root_node }
} : links { v.<SUBJECT>p }



patterns AsAsModifier { language=English } export { node:root_node }

// I did it almost as quickly as he did
pattern AsAsModifier
{
 Adv_AS_AS_Modifier : export { node:root_node }
}

// almost nearly:
// I did it almost nearly as quickly as he did
pattern AsAsModifier
{
 a1=eng_adverb:almost{}
 a2=eng_adverb:nearly{} : export { node:root_node }
} : links { a2.<ATTRIBUTE>a1 }
  : ngrams { 1 }

// just about:
// I did it just about as quickly as he did
pattern AsAsModifier
{
 a1=eng_adverb:just{}
 a2=eng_adverb:about{} : export { node:root_node }
} : links { a2.<ATTRIBUTE>a1 }
  : ngrams { 1 }


// I did it three times as quickly as he did
pattern AsAsModifier
{
 c=eng_numeral:*{ numeral_form:cardinal }
 t=eng_noun:time{ number:plural } : export { node:root_node }
} : links { t.<ATTRIBUTE>c }
  : ngrams { 1 }


pattern AdverbialPhrase
{
 adv1=AsAsModifier:export{node:root_node}
 as1=eng_conj:as{}
 adv2=eng_adverb:*{}
 as2=eng_conj:as{}
 subclause=AS_AS_Subclause
} : links { adv1.<NEXT_COLLOCATION_ITEM>as1.<NEXT_COLLOCATION_ITEM>adv2.<NEXT_COLLOCATION_ITEM>as2.<SUBORDINATE_CLAUSE>subclause }
  : ngrams { 1 }


// He goes his own way  
//         ^^^^^^^^^^^
pattern AdverbialPhrase
{
 a1=eng_pronoun:*{ noun_form:possessive }
 a2=eng_adjective:own{}
 n=eng_noun:way{} : export { node:root_node }
}
: links { n.{ <ATTRIBUTE>a1 <ATTRIBUTE>a2 } }
  

//pattern AdvGroup export { node:root_node (MODIF_TYPE) (ADJ_FORM) }
//{ AdverbialPhrase:export { node:root_node } }


// If anything, this encouraged the rats.
// ^^^^^^^^^^^
pattern AdverbialPhrase
{
 c=eng_conj:while{} : export { node:root_node }
 obj=DirectObj
}
: links { c.<OBJECT>obj }
: ngrams { -1 }

// While there Solzhenitsyn had a tumor removed.
// ^^^^^^^^^^^
pattern AdverbialPhrase
{
 c=eng_conj:while{} : export { node:root_node }
 adv=eng_adverb:*{}
}
: links { c.<NEXT_COLLOCATION_ITEM>adv }
: ngrams { -1 }


// The telephone system functions, albeit imperfectly.
//                                 ^^^^^^^^^^^^^^^^^^
pattern AdverbialPhrase
{
 comma=','
 c=eng_conj:albeit{} : export { node:root_node }
 adv=eng_adverb:*{}
}
: links { c.{ <PUNCTUATION>comma <NEXT_COLLOCATION_ITEM>adv } }


// ------------------------------------------------------------



// A book is inspired when it inspires.
//                    ^^^^^^^^^^^^^^^^
pattern RightAdvPhrase
{
 WHEN_AdvPhrase : export { node:root_node }
}

// Add water as needed.
//           ^^^^^^^^^
pattern RightAdvPhrase
{
 AS_AdvPhrase : export { node:root_node }
}


// Harrison had been married three times previously.
//                           ^^^^^^^^^^^
// Treat firearms as if they are loaded.
//                ^^^^^^^^^^^^^^^^^^^^^
pattern RightAdvPhrase
{
 AdverbialPhrase : export { node:root_node }
}



