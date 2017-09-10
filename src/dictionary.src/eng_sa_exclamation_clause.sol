// Предложения-восклицания, без нормальной предикатной синтаксической структуры

patterns ExclamationClause export { node:root_node }

// How nice to see you again!
pattern ExclamationClause
{
 how=eng_adverb:how{}
 adv=eng_adverb:*{ adj_form:basic } : export { node:root_node }
 inf=InfinitiveAction
 fin='!'
} : links
{
 adv.{
      <ATTRIBUTE>how
      <INFINITIVE>inf
      <PUNCTUATION>fin
     }
}


// What a pity!
pattern ExclamationClause
{
 what=eng_adverb:what{}
 det=eng_article:a{}
 n=NounGroup{ NUMBER:SINGLE } : export { node:root_node }
 fin=@optional('!')
} : links
{
 n.{
    <ATTRIBUTE>what
    <ATTRIBUTE>det
    ~<PUNCTUATION>fin
   }
}


pattern Sentence
{
 ExclamationClause : export { node:root_node }
}

