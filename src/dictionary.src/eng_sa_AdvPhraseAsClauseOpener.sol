// Наречные фразы в начале клоза, без отбивки запятой.

collocation_set AdvPhraseAsClauseOpener=
{
 { At best }, // At best we'll lose only the money.
 { Just then }, // Just then the bugle sounded.
 { As late as yesterday }, // As late as yesterday she was fine.
 { At least }, // At least he survived.
 { At first }, // At first he didn't notice anything strange.
 { Last not least }, // Last not least he plays the saxophone.
 { Sooner or later }, // Sooner or later you will have to face the facts.
 { So far }, // So far he hasn't called.
 { At last }, // At last the hour arrived.
 { First of all }, // First of all you have to listen until you hear the silence.
 { For once }, // For once his wit failed him.
 { These days }, // These days everyone can make a movie
 { This evening }, // This evening I'm going to the movies
 { At worst } // At worst we'll go to jail.
}

// Паттерны для оформления вводных фраз и слов.
patterns SentenceBegin export { node:root_node }

pattern SentenceBegin
{
 AdvPhraseAsClauseOpener:export{node:root_node}
} : ngrams { -5 }


// ---------------------------------------------

// A year ago I was living in Ankara
pattern SentenceBegin
{
 d=eng_article:a{}
 y='year'{ class:eng_noun }
 a=eng_adverb:ago{} : export { node:root_node }
} : links { a.<ATTRIBUTE>y.<ATTRIBUTE>d }
 : ngrams { -5 }
 
// Sixty years ago my grandfather came to the U.S.
pattern SentenceBegin
{
 c=eng_numeral:*{ NUMERAL_FORM:CARDINAL }
 y=eng_noun:year{ noun_form:basic }
 a=eng_adverb:ago{} : export { node:root_node }
} : links { a.<ATTRIBUTE>y.<ATTRIBUTE>c }
 : ngrams { -5 }

// 60 years ago my grandfather came to the U.S.
pattern SentenceBegin
{
 c=num_word:*{}
 y=eng_noun:year{ noun_form:basic }
 a=eng_adverb:ago{} : export { node:root_node }
} : links { a.<ATTRIBUTE>y.<ATTRIBUTE>c }
 : ngrams { -5 }

// As regards his suggestion I was non-committal.
pattern SentenceBegin
{
 conj=eng_conj:as{} : export { node:root_node }
 v='regards'{ class:eng_verb }
 n=NounGroup{ NUMBER:SINGLE }
} : links { conj.<NEXT_COLLOCATION_ITEM>v.<NEXT_COLLOCATION_ITEM>n }
 : ngrams { -5 }

// Except for your presence I should be bored.
pattern SentenceBegin
{
 conj='except' : export { node:root_node }
 prep=eng_prep:for{}
 n=NounGroup{ NUMBER:SINGLE }
} : links { conj.<NEXT_COLLOCATION_ITEM>prep.<NEXT_COLLOCATION_ITEM>n }
 : ngrams { -5 }
 
