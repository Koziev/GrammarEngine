
tree_scorers PreposValency

// The seismograph showed a sharp spike in response to the temblor.
//                                      ^^^^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:in{}.<OBJECT>eng_noun:response{}.eng_prep:to{}.<OBJECT>*:*{} }
  then 5
}

// The child was standing in the middle of the crossfire, defenselessly.
//                        ^^^^^^^^^^^^^^^^...
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:in{}.<OBJECT>eng_noun:middle{}.eng_prep:to{}.<OBJECT>*:*{} }
  then 5
}


// In deep trouble
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:in{}.<OBJECT>eng_noun:trouble{} }
  then 5
}


// You can sit next to them
//             ^^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:to{}.<ATTRIBUTE>eng_adverb:next{} }
  then 5
}

// The class will start exactly at 9 o'clock
//                      ^^^^^^^^^^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:at{}.<ATTRIBUTE>eng_adverb:exactly{} }
  then 5
}

// She plastered warnings all over the wall.
//                        ^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:over{}.<ATTRIBUTE>eng_adverb:all{} }
  then 5
}

// Production of these machines evolved over time.
//                                      ^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:over{}.<OBJECT>eng_noun:time{} }
  then 5
}


// He left immediately after his short performance.
//         ^^^^^^^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:after{}.<ATTRIBUTE>eng_adverb:immediately{} }
  then 5
}



// See text for more details.
//          ^^^^^^^^^^^^^^^^



// At that time
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:at{}.'time'.'that' }
  then 8
}

// According to Spinoza, reality is perfection.
// ^^^^^^^^^^^^ ...
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:to{}.<ATTRIBUTE>eng_adverb:according{} }
  then 6
}

// Prior to 1700, the process of fossil formation was unknown.
// ^^^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:to{}.<ATTRIBUTE>eng_adverb:prior{} }
  then 6
}

// A chicken is running down a dirt road.
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:down{}.<OBJECT>eng_noun:road{} }
  then 6
}

// He is farther down the road
//       ^^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:down{}.<ATTRIBUTE>eng_adverb:far{ ADJ_FORM:COMPARATIVE } }
  then 2
}


// The continental crust floats on top of the mantle
//                              ^^^^^^^^^... 
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:on{}.<OBJECT>eng_noun:top{}.eng_prep:of{}.*:*{} }
  then 6
}

// Oil, coal, and natural gas are fossil fuels formed under what conditions?
//                                                    ^^^^^      ^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:under{}.<OBJECT>eng_noun:condition{} }
  then 6
}

// Marconi spoke fluent English in addition to Italian.
//                              ^^^^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:in{}.<OBJECT>eng_noun:addition{}.eng_prep:to{}.*:*{} }
  then 6
}

// I can't see him on horseback!
//                 ^^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:on{}.<OBJECT>eng_noun:horseback{} }
  then 6
}


// After breakfast
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:after{}.<OBJECT>eng_noun:breakfast{} }
  then 6
}


// Her rucksack bobbed gently on her back.
//                            ^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:on{}.<OBJECT>eng_noun:back{} }
  then 5
}

// The sentence is translated without regard to the context.
//                            ^^^^^^^^^^^^^^^^^...
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:without{}.<OBJECT>eng_noun:regard{}.eng_prep:to{}.*:*{} }
  then 5
}

// In the article Guest remarked:
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:in{}.<OBJECT>eng_noun:article{} }
  then 2
}

// After many years
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:after{}.<OBJECT>eng_noun:year{} }
  then 2
}

// After that failure
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:after{}.<OBJECT>eng_noun:failure{} }
  then 2
}


// The bus went down the street
tree_scorer PreposValency language=Russian
{
 if context { eng_prep:down{}.<OBJECT>eng_noun:street{} }
  then 2
}



tree_scorer PreposValency language=Russian generic
{
 if context { eng_prep:*{}.<OBJECT>ENG_PRONOUN:*{ NOUN_FORM:POSSESSIVE } }
  then -5
}


// It is 209 km long.
//       ^^^^^^^^^^^
tree_scorer PreposValency language=Russian
{
 if context { eng_postpos:long{}.<OBJECT>eng_noun:km{} }
  then 5
}
