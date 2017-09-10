#include "aa_rules.inc"

// *************************
// Incomplete sentences
// *************************


patterns IncompleteSentence0 { language=English } export { node:root_node }
patterns IncompleteSentence { language=English } export { node:root_node }

pattern IncompleteSentence0 { PronounGroup : export{ node:root_node } } : ngrams { -7 }

//pattern IncompleteSentence0 { eng_verb:*{}:export{ node:root_node } } : ngrams { -1 }
//pattern IncompleteSentence0 { eng_adverb:*{}:export{ node:root_node } } : ngrams { -2 }
//pattern IncompleteSentence0 { *:*{}:export{ node:root_node } } : ngrams { -10 }

pattern IncompleteSentence0
{ NounGroup:export{ node:root_node } } : ngrams { -3 }

// Strategically important decisions.
pattern IncompleteSentence0
{
 mod=eng_adverb:*{}
 a=eng_adjective:*{ ADJ_FORM:BASIC }
 n=eng_noun:*{} : export { node:root_node }
} : links { n.<ATTRIBUTE>a.<ATTRIBUTE>mod }
: ngrams 
{
 -2
 eng_adj_noun_score(a,n)
 eng_adv_adj_score(mod,a)
}


pattern IncompleteSentence0
{
 mod=eng_adverb:*{}
 pp=eng_verb:*{ VERB_FORM:PP TRANSITIVITY:TRANSITIVE }
 n=eng_noun:*{} : export { node:root_node }
} : links { n.<ATTRIBUTE>pp.<ATTRIBUTE>mod }
: ngrams 
{
 -2
 eng_adv_v_score(mod,pp)
 eng_adj_noun_score(pp,n)
 eng_v_obj_score(pp,n)
}


pattern IncompleteSentence0
{ AdjGroup:export{ node:root_node } } : ngrams { -6 }

pattern IncompleteSentence
{ PreposPhrase:export{ node:root_node } } : ngrams { -4 }

// Голый герундий (без предлога) в роли полного предложения,
// прежде всего для тестирования по эталонам.
// Looking Back at an Eclipsed Earth
pattern IncompleteSentence0
{ Gerund:export{ node:root_node } } : ngrams { -6 }

pattern IncompleteSentence
{ GerundAdvPhrase:export{ node:root_node } } : ngrams { -6 }


// -----------------------------------------------------


patterns FinalPunkt export { node:root_node }

word_set FinalPunkt0 = { '.', '?', '!', '...' }

pattern FinalPunkt
{
 FinalPunkt0 : export { node:root_node }
} 

pattern FinalPunkt
{
 ПУНКТУАТОР:*{} : export { node:root_node }
} : ngrams { -5 }


// -----------------------------------------------------

pattern IncompleteSentence
{
 x=IncompleteSentence0 : export{ node:root_node }
} : ngrams { -1 }

pattern IncompleteSentence
{
 x=IncompleteSentence0 : export{ node:root_node }
 fin=FinalPunkt
} : links { x.<PUNCTUATION>fin }

// ----------------------------------------------------------------

pattern language=English { _НАЧ IncompleteSentence _КОН }

