// Разбор финализатора неполного перечисления:
//
// испытуемые видели людей, зверей и т. п.
//                                 ^^^^^^^

patterns ЗамыкательПеречисления export { node:root_node }

word_set ЧастицыПеречисления0 = { 'т.д.', 'т.п.', 'т. д.', 'т. п.' }

patterns ЧастицыПеречисления export { node:root_node }

pattern ЧастицыПеречисления
{
 ЧастицыПеречисления0 : export { node:root_node }
}

pattern ЧастицыПеречисления
{
 a1=наречие:так{}
 a2='далее' : export { node:root_node }
} : links { a2.<ATTRIBUTE>a1 }

pattern ЧастицыПеречисления
{
 a1='тому'{ class:местоим_сущ }
 a2='подобное' : export { node:root_node }
} : links { a2.<OBJECT>a1 }


// -------------------------------------------------------------------

// Там лежали груши, яблоки, апельсины и т.д.
//                                     ^^^^^^
pattern ЗамыкательПеречисления
{
 conj=союз:и{} : export { node:root_node }
 etc=ЧастицыПеречисления
} : links { conj.<NEXT_COLLOCATION_ITEM>etc }

// и т.д. и т.п.
pattern ЗамыкательПеречисления
{
 conj=союз:и{} : export { node:root_node }
 etc=ЧастицыПеречисления
 conj2=союз:и{}
 etc2=ЧастицыПеречисления
} : links
{
 conj.<NEXT_COLLOCATION_ITEM>etc.
  <RIGHT_LOGIC_ITEM>conj2.
   <NEXT_COLLOCATION_ITEM>etc2
}



// Мы видели вспышки, гром, крупный град, ну и т.д.
//                                        ^^^^^^^^^
pattern ЗамыкательПеречисления
{
 p=частица:ну{}
 etc=ЗамыкательПеречисления : export { node:root_node }
} : links { etc.<PREFIX_PARTICLE>p }

pattern ЗамыкательПеречисления
{
 comma=','
 etc=ЗамыкательПеречисления : export { node:root_node }
} : links { etc.<PUNCTUATION>comma }

