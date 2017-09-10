#include "aa_rules.inc"


// Паттерны для оформления концовки предложения.
patterns SentenceEnd export { node:root_node }

// паттерны для простого предложения с вводной частью и концовкой.
patterns SimpleSentence export { node:root_node }


// ---------------------------------------------------------

// And you know what?
// ^^^
pattern SentenceBegin
{
 eng_conj:*{} : export{node:root_node}
} : ngrams { -5 }





// -------------------
// COMPLETE SENTENCES.
// -------------------

pattern SimpleSentence
{
 intro_beg=SentenceBegin
 s=Sentence : export { node:root_node }
} : links { s.<BEG_INTRO>intro_beg }


pattern SimpleSentence
{
 intro_beg=SentenceBegin
 s=Sentence : export { node:root_node }
 e=SentenceEnd
} : links { s.{
               <BEG_INTRO>intro_beg
               <SENTENCE_CLOSER>e
              } }


pattern SimpleSentence
{
 s=Sentence : export { node:root_node }
 e=SentenceEnd
} : links { s.<SENTENCE_CLOSER>e }


pattern SimpleSentence
{
 Sentence : export { node:root_node }
}

// -------------------------------------------------------


pattern language=English
{
 _НАЧ
 core=SimpleSentence
 _КОН
} : ngrams { CompleteSentence(core) }
