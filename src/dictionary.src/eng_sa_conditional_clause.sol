// --------------------------------
// Условные составные предложения.
// --------------------------------

// основной клоз - выполняется/имеет место быть при наступлении условия.
patterns ConditionalPrincipalClause { language=English } export { node:root_node }
pattern ConditionalPrincipalClause
{
 V_Clause : export { node:root_node }
}

// ---------------
// Клоз условия.
// ---------------

patterns ConditionalCondClause { language=English } export { node:root_node }
pattern ConditionalCondClause
{
 V_Clause : export { node:root_node }
}

// If Richard works hard, he will learn grammar.
pattern CompoundSentence
{
 if=eng_conj:if{}
 c1=ConditionalCondClause // condition clause
 comma=','
 c2=ConditionalPrincipalClause:export{node:root_node} // principal clause
} : links { c2.{ <ATTRIBUTE>if.<SUBCLAUSE>c1 <PUNCTUATION>comma } }


// If Richard works hard he will learn grammar.
pattern CompoundSentence
{
 if=eng_conj:if{}
 c1=ConditionalCondClause // condition clause
 c2=ConditionalPrincipalClause:export{node:root_node} // principal clause
} : links { c2.<ATTRIBUTE>if.<SUBCLAUSE>c1 }


// I will help him, if he asks me.
pattern CompoundSentence
{
 c2=ConditionalPrincipalClause:export{node:root_node} // principal clause
 comma=','
 if=eng_conj:if{}
 c1=ConditionalCondClause // condition clause
} : links { c2.{ <ATTRIBUTE>if.<SUBCLAUSE>c1 <PUNCTUATION>comma } }


// I will help him if he asks me.
pattern CompoundSentence
{
 c2=ConditionalPrincipalClause:export{node:root_node} // principal clause
 if=eng_conj:if{}
 c1=ConditionalCondClause // condition clause
} : links { c2.<ATTRIBUTE>if.<SUBCLAUSE>c1 }
