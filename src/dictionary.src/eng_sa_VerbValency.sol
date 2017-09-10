

// He gave ten dollars to Mary.
//    ^^^^             ^^^^^^^
tree_scorer VerbValency language=English
{
 if context { eng_verb:give{}.<ATTRIBUTE>eng_prep:to{} }
  then 2
}


tree_scorer VerbValency language=English
{
 if context { eng_verb:go{ VERB_FORM:ING }.eng_particle:to{}.eng_verb:*{} }
  then 5
}


// The child strayed from the path and her parents lost sight of her.
//                                                 ^^^^^^^^^^^^^^^^^
tree_scorer VerbValency language=English
{
 if context { eng_verb:lose{}.{ <OBJECT>eng_noun:sight{} <ATTRIBUTE>eng_prep:of{}.<OBJECT>*:*{} } }
  then 5
}



// You are very tall!
// It isn't open.
tree_scorer VerbValency language=English generic
{
 if context { eng_beverb:*{2}.{<SUBJECT>*:*{1} <RHEMA>eng_adjective:*{3} } }
  then 1
}

tree_scorer VerbValency language=English generic
{
 if context { eng_verb:*{ VERB_SLOTS:COPULATIVE }.{<SUBJECT>*:*{} <RHEMA>eng_adjective:*{} } }
  then 1
}



// I may ask
tree_scorer VerbValency language=English
{
 if context { eng_auxverb:may{}.eng_verb:*{} }
  then 2
}


// This is a comparative definition
// ^^^^^^^...
tree_scorer VerbValency language=English
{
 if context { eng_beverb:be{ 2 }.{ <SUBJECT>AdjAsSingleNoun{ 1 } <RHEMA>*:*{ 3 } } }
  then 2
}

// Richard doesn't like ice-cream
//         ^^^^^^^^^^^^
tree_scorer VerbValency language=English
{
 if context { eng_verb:"don't"{}.eng_conj:like{} }
  then -2
}

tree_scorer VerbValency language=English
{
 if context { eng_verb:do{}.eng_conj:like{} }
  then -2
}



tree_scorer VerbValency language=English generic
{
 if context { eng_verb:do{}.{ <OBJECT>*:*{} <SECOND_VERB>eng_verb:*{} } }
  then -100
}


tree_scorer VerbValency language=English generic
{
 if context { eng_verb:*{ VERB_FORM:PP }.<LEFT_AUX_VERB>ENG_VERB:have{} }
  then 2
}

// On Earth, Mission Control continued to wait.
//                           ^^^^^^^^^^^^^^^^^
tree_scorer VerbValency language=English
{
 if context { eng_verb:continue{}.eng_particle:to{}.eng_verb:*{ verb_form:inf } }
  then 1
}

// These films were known as silent films.
//                  ^^^^^^^^...
tree_scorer VerbValency language=English
{
 if context { eng_verb:know{VERB_FORM:PP}.eng_conj:as{}.eng_noun:*{} }
  then 2
}

// Обычно прямое дополнение стоит сразу после глагола, а уже справа от него
// стоит предложное дополнение:
// Bellarmine wrote to heliocentrist Paolo Antonio Foscarini:
tree_scorer VerbValency language=English generic
{
 if context { eng_verb:*{1}.{ <PREPOS_ADJUNCT>*:*{2} <OBJECT>*:*{3} } }
  then -5
}

// Для глагола TO NEED маловероятно одновременное присоединение прямого дополнение
// и инфинитива, поэтому штрафуем.
tree_scorer VerbValency language=English
{
 if context { eng_verb:need{}.{ <OBJECT>*:*{} <SECOND_VERB>*:*{} } }
  then -5
}


