// Группа числительного

patterns NounEnumerator export { NUMBER node:root_node }

word_set Enumerator1={ 'one', '1' }

pattern NounEnumerator
{
 NumberGroup{ Enumerator1 } : export { NUMBER:SINGLE node:root_node }
}


pattern NounEnumerator
{
 q=NumberGroup{ ~Enumerator1 } : export { NUMBER:PLURAL node:root_node }
}

// They died almost 400 million years ago.
//                  ^^^^^^^^^^^
pattern NounEnumerator
{
 q=NumberGroup{ ~Enumerator1 }
 n=NumberNoun : export { NUMBER:PLURAL node:root_node }
} : links { n.<ATTRIBUTE>q }




// -------------------------------------------------------------
// Порядковые числительные в целом похожи на прилагательные, в частности
// могут появляться в разном месте цепочки прилагательных перед существительным.

patterns OrdinalNumber export { node:root_node }


// She was his first love.
pattern OrdinalNumber
{
 n1=eng_numeral:*{ NUMERAL_FORM:ORDINAL } : export { node:root_node }
}

wordentry_set Or_And_Ordinal={
 eng_conj:or{},
 eng_conj:and{}
}

pattern OrdinalNumber
{
 n1=eng_numeral:*{ NUMERAL_FORM:ORDINAL } : export { node:root_node }
 conj=Or_And_Ordinal
 n2=eng_numeral:*{ NUMERAL_FORM:ORDINAL }
} : links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }

