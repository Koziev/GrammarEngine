// LC->18.01.2016

tree_scorers NounValency
tree_scorers AdverbialNounValency

// Запретим одиночному существительному выступать в роли обстоятельства времени:
// On the third day he rose again;
//              ^^^
tree_scorer AdverbialNounValency language=English generic
{
 if context { eng_noun:*{}.[not]*:*{} }
  then -10
}

// I woke very early this morning
//                   ^^^^^^^^^^^^
tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:morning{}.eng_adjective:this{} }
  then 5
}


// I write a chapter every night before falling asleep.
//                   ^^^^^^^^^^^
tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:night{}.eng_adjective:every{} }
  then 5
}

// He has been digging in the garden all morning
//                                   ^^^^^^^^^^^
tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:morning{}.eng_adjective:all{} }
  then 5
}


tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:day{}.eng_adjective:these{} }
  then 5
}



// He had immunity from eviction that week.
//                               ^^^^^^^^^
tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:week{}.eng_adjective:that{} }
  then 5
}

// He wrote a letter last week
//                   ^^^^^^^^^
tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:week{}.eng_adjective:last{} }
  then 5
}

// He only came to Ruthenia next month.
//                          ^^^^^^^^^^
tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:month{}.eng_adjective:next{} }
  then 5
}

// He paid the bill last month.
//                  ^^^^^^^^^^
tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:month{}.eng_adjective:last{} }
  then 5
}


// It displays a different theme every summer.
//                               ^^^^^^^^^^^^
tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:summer{}.eng_adjective:every{} }
  then 5
}


// It rains every day
//          ^^^^^^^^^
tree_scorer AdverbialNounValency language=English
{
 if context { eng_noun:day{}.eng_adjective:every{} }
  then 5
}


// ---------------------------------------------------------------

tree_scorer NounValency language=English
{
 if context { 'states'.{ <ATTRIBUTE>'united' 'of'.'America' } }
  then 5
}


// Influence on Hellenistic medicine.
// ^^^^^^^^^^^^
tree_scorer NounValency language=English
{
 if context { eng_noun:influence{}.eng_prep:on{} }
  then 2
}

// Sources disagree on the meaning of the word.
//                         ^^^^^^^^^^
tree_scorer NounValency language=English
{
 if context { eng_noun:meaning{}.eng_prep:of{}.<OBJECT>*:*{} }
  then 5
}

// The artist wrote Chinese characters on a big piece of white paper.
//                                              ^^^^^^^^...
tree_scorer NounValency language=English
{
 if context { eng_noun:piece{}.eng_prep:of{}.<OBJECT>*:*{} }
  then 5
}


// Color is required by a majority of games.
//                        ^^^^^^^^^^^
tree_scorer NounValency language=English
{
 if context { eng_noun:meaning{}.eng_prep:of{}.<OBJECT>*:*{} }
  then 5
}

// a dog's bark
//   ^^^^^^^^^^
tree_scorer NounValency language=English
{
 if context { eng_noun:bark{}.<ATTRIBUTE>eng_noun:dog{}.<POSSESSION_POSTFIX>"'s" }
  then 5
}

// Marco's book
tree_scorer NounValency language=English
{
 if context { eng_noun:book{}.<ATTRIBUTE>eng_noun:*{ ENG_PROPER_NOUN }.<POSSESSION_POSTFIX>"'s" }
  then 5
}

// a day's rest
tree_scorer NounValency language=English
{
 if context { eng_noun:rest{}.<ATTRIBUTE>eng_noun:rest{}.<POSSESSION_POSTFIX>"'s" }
  then 5
}

// I make a lot of mistakes.
//        ^^^^^^^^
tree_scorer NounValency language=English
{
 if context { eng_noun:lot{}.{ <ATTRIBUTE>eng_article:a{} <PREPOS_ADJUNCT>eng_prep:of{}.<OBJECT>*:*{} } }
  then 5
}


// I've got plenty of time.
//          ^^^^^^^^^^^^^^
tree_scorer NounValency language=English
{
 if context { eng_noun:plenty{}.{ <PREPOS_ADJUNCT>eng_prep:of{}.<OBJECT>*:*{} } }
  then 5
}

// The prisoner's resistance weakened after seven days.
//                                          ^^^^^^^^^^
tree_scorer NounValency language=English
{
 if context { eng_noun:day{ NUMBER:PLURAL }.ENG_NUMERAL:*{} }
  then 2
}

// Nothing обычно не атрибутируется прилагательными или местоимениями:
// Presley left her nothing in his will.
//              ~~~ ^^^^^^^
tree_scorer NounValency language=English
{
 if context { eng_noun:nothing{}.<ATTRIBUTE>ENG_PRONOUN:*{} }
  then -10
}

tree_scorer NounValency language=English
{
 if context { eng_noun:nothing{}.<ATTRIBUTE>ENG_ADJECTIVE:*{} }
  then -10
}
