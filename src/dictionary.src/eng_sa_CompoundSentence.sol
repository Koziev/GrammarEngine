#include "aa_rules.inc"

// ----------------------
// COMPOUND SENTENCES
// ----------------------

patterns CompoundSentence0 export { node:root_node }
patterns CompoundSentenceTail export { node:root_node }

pattern CompoundSentence0
{ SentenceClause:export{node:root_node} }

pattern CompoundSentenceTail
{ PredicateGroup0{ SUBJ_LINKED:1 ~TENSE:IMPERATIVE }:export{node:root_node} }

patterns CompoundSentence export { node:root_node }

// ---------------------------------------------------------------


// I hope it won't rain.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 s2=CompoundSentenceTail
}
: links { s1.<SUBORDINATE_CLAUSE>s2 }
: ngrams { -8 }


// Предложения связаны через союз THAT
// Cleo liked the bear that Ray drew.
//                     ^^^^
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=eng_conj:that{}
 s2=CompoundSentenceTail
}
: links { s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2 }



// ---------------------------------------------------------------

wordentry_set TimeSequenceConjs=
{
 eng_conj:since{},
 eng_conj:after{},
 eng_conj:before{}
}

// The dog has had that bed since he was just a pup
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=TimeSequenceConjs
 s2=CompoundSentenceTail
} : links {
           s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2
          }


// Before he could duck, another stone struck him.
pattern CompoundSentence
{
 conj=TimeSequenceConjs
 s2=CompoundSentence0
 comma=','
 s1=CompoundSentenceTail:export{node:root_node}
} : links {
           s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2.<PUNCTUATION>comma
          }


// --------------------------------------------

// Союз AND
// The child strayed from the path and her parents lost sight of her.
//                                 ^^^
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=eng_conj:and{}
 s2=CompoundSentenceTail
} : links { s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2 }


// I put the questions, and she answered them placidly.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 comma=','
 conj=eng_conj:and{}
 s2=CompoundSentenceTail
} : links { s1.<SUBORDINATE_CLAUSE>conj.{
                                         <PUNCTUATION>comma
                                         <NEXT_COLLOCATION_ITEM>s2
                                        } }


// --------------------------------------------

/*
// My younger brother often tagged along when I went out with my friends.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 when=eng_adverb:when{}
 s2=CompoundSentenceTail
} : links { s1.<SUBORDINATE_CLAUSE>when.<NEXT_COLLOCATION_ITEM>s2 }
*/

/*
// When Pinocchio lies, his nose grows.
pattern CompoundSentence
{
 when=eng_adverb:when{}
 s1=CompoundSentence0
 comma=','
 s2=CompoundSentenceTail:export{node:root_node}
} : links { s2.<SUBORDINATE_CLAUSE>when.{
                                         <PUNCTUATION>comma
                                         <NEXT_COLLOCATION_ITEM>s1
                                        } }
*/

// --------------------------------------------

// Greenspan's fraud: how two decades of his policies have undermined the global economy
pattern CompoundSentence
{
 s1=NounGroup:export{node:root_node}
 conj=':'
 adv=eng_adverb:how{}
 s2=Sentence
} : links {
           s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>adv.<NEXT_COLLOCATION_ITEM>s2
          }


pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=':'
 adv=eng_adverb:how{}
 s2=CompoundSentence0
} : links {
           s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>adv.<NEXT_COLLOCATION_ITEM>s2
          }





// Rain tomorrow is possible, but I wouldn't bet on it
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 comma=','
 conj=eng_conj:but{}
 s2=CompoundSentence0
} : links { s1.<SUBORDINATE_CLAUSE>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>s2 }




// The two specimens are actually different from each other but the differences are almost indistinguishable.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=eng_conj:but{}
 s2=CompoundSentence0
} : links {
           s1.<NEXT_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2
          }


// She did her work, but she did so complainingly.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 comma=','
 conj=eng_conj:but{}
 s2=CompoundSentence0
} : links {
           s1.<NEXT_CLAUSE>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>s2
          }



// -------------------------------------------------------------
// --- Сложносочиненное предложение с BECAUSE:

// This makes sense because many devices are byte oriented
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=eng_conj:because{}
 s2=CompoundSentence0
} : links {
           s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2
          }

// Because he hadn't worked hard, Richard didn't pass his examination.
pattern CompoundSentence
{
 conj=eng_conj:because{}
 s2=CompoundSentence0
 comma=','
 s1=CompoundSentence0:export{node:root_node}
} : links {
           s1.<SUBORDINATE_CLAUSE>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>s2
          }


// -------------------------------------------------------------
// --- Сложносочиненное предложение с ALTHOUGH:
// Although they tried hard, they did not succeed.
pattern CompoundSentence
{
 a=eng_conj:Although{}
 s1=CompoundSentence0
 comma=','
 s2=CompoundSentence0:export{node:root_node}
} : links {
           s2.<SUBORDINATE_CLAUSE>a.<NEXT_COLLOCATION_ITEM>s1.<PUNCTUATION>comma
          }

// Her plays are underperformed, although they are very good.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 comma=','
 a=eng_conj:Although{}
 s2=CompoundSentence0
} : links {
           s1.<SUBORDINATE_CLAUSE>comma.<NEXT_COLLOCATION_ITEM>a.<NEXT_COLLOCATION_ITEM>s2
          }

// -------------------------------------------------------------


// Сложносочиненное предложение с WHILE:
// She did the thinking while he did the writing.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=eng_conj:while{}
 s2=CompoundSentence0
} : links { s1.<NEXT_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2 }


// --------------------------------------------------------------

// Сложноподчиненное предложение через SINCE:
// Nothing interesting has happened since we parted.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=eng_conj:since{}
 s2=CompoundSentence0
} : links { s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2 }


// --------------------------------------------------------------

// Сложноподчиненное предложение через SO:
// He piggybacked her child so she could see the show.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=eng_conj:so{}
 s2=CompoundSentence0
} : links { s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2 }


// It was late, so we went home.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 comma=','
 conj=eng_conj:so{}
 s2=CompoundSentence0
} : links { s1.<SUBORDINATE_CLAUSE>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>s2 }


// The candidate reinvented the concept of national health care so that he would get elected.
pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj1=eng_conj:so{}
 conj2=eng_conj:that{}
 s2=CompoundSentence0
} : links { s1.<SUBORDINATE_CLAUSE>conj1.{
                                          <NEXT_COLLOCATION_ITEM>conj2
                                          <NEXT_COLLOCATION_ITEM>s2
                                         } }


// --------------------------------------------------------------

// Сложносочиненное предложение через THOUGH:
// I respect him though I don't like him.

pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=eng_conj:though{}
 s2=CompoundSentence0
} : links { s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2 }


// ---------------------------------------------------

// Сложносочиненное предложение через UNLESS:
// I shan't come, unless you really want me to. 

pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 comma=','
 conj=eng_conj:unless{}
 s2=CompoundSentence0
} : links { s1.<SUBORDINATE_CLAUSE>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>s2 }


// --------------------------------------------------------------

// Сложносочиненное предложение через союз UNTIL:
// The conditional sale will not be complete until the full purchase price is paid.

pattern CompoundSentence
{
 s1=CompoundSentence0:export{node:root_node}
 conj=eng_conj:until{}
 s2=CompoundSentence0
} : links { s1.<SUBORDINATE_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>s2 }

// --------------------------------------------------------------

/*
// When he saw his axe, he smiled happily
pattern CompoundSentence
{
 opener=WHEN_AdvPhrase
 comma=','
 clause=SentenceClause:export{node:root_node}
} : links { clause.<SUBORDINATE_CLAUSE>opener.<PUNCTUATION>comma }


// When he saw the police car he froze.
pattern CompoundSentence
{
 opener=WHEN_AdvPhrase
 clause=SentenceClause:export{node:root_node}
} : links { clause.<SUBORDINATE_CLAUSE>opener }
*/

// --------------------------------------------------------------

patterns CompoundFirstClause export { node:root_node }

// As far as I can judge this is correct.
pattern CompoundFirstClause
{
 w1=eng_conj:as{}
 w2=eng_adverb:far{}
 w3=eng_conj:as{}
 opener_sbj=Sbj
 opener_v=V_Modal:export{ node:root_node }
} : links
{
 opener_v.{
           <SUBJECT>opener_sbj
           <ATTRIBUTE>w1.<NEXT_COLLOCATION_ITEM>w2.<NEXT_COLLOCATION_ITEM>w3
          }
}

pattern CompoundSentence
{
 opener=CompoundFirstClause
 clause=SentenceClause:export{node:root_node}
} : links { clause.<SUBORDINATE_CLAUSE>opener }

// --------------------------------------------------------------

patterns CompoundSentence2 export { node:root_node }

pattern CompoundSentence2
{
 b=SentenceBegin
 s=CompoundSentence : export { node:root_node }
 e=SentenceEnd
} : links { s.{
               <BEG_INTRO>b
               ~<PUNCTUATION>e
              } }


pattern CompoundSentence2
{
 s=CompoundSentence : export { node:root_node }
 e=SentenceEnd
} : links { s.<PUNCTUATION>e }


pattern CompoundSentence2
{
 s=CompoundSentence : export { node:root_node }
}


// ----------------------------

pattern language=English
{
 _НАЧ
 CompoundSentence2
 _КОН
}

