


// ++++ паттерн возраста ++++

patterns ПодлежащВозраст export { node:root_node }
patterns СказуемоеВозраст export { node:root_node }

// мне уже тридцать один год
// ^^^
pattern ПодлежащВозраст
{
 ГруппаМест{ падеж:дат } : export { node:root_node }
}

// Людмиле уже пятнадцать
// ^^^^^^^
pattern ПодлежащВозраст
{
 ГруппаСущ1{ падеж:дат одуш:одуш } : export { node:root_node }
}


wordentry_set СущВозраста=существительное:{ лето, год, месяц, день, неделя }

// мне тридцать два года
//     ^^^^^^^^^^^^^^^^^
pattern СказуемоеВозраст
{
 ЧислСущ{ ПАДЕЖ:ИМ СущВозраста } : export { node:root_node }
}

// мне тогда было пять
//                ^^^^
pattern СказуемоеВозраст
{
 ГруппаЧисл{ ПАДЕЖ:ИМ } : export { node:root_node }
}


// Ему тогда было 26
//                ^^
pattern СказуемоеВозраст
{
 ЧислоЦифрами : export { node:root_node }
}


// мне уже тридцать один год
//     ^^^^^^^^^^^^^^^^^^^^^
pattern СказуемоеВозраст
{
 adv=ГруппаНареч1
 q=ЧислСущ{ ПАДЕЖ:ИМ СущВозраста } : export { node:root_node }
}
: links { q.<ATTRIBUTE>adv }
: ngrams { -1 }

// --------------------------------------------

// ей почти двадцать два года.
pattern ПредикатСвязка
{
 sbj=ПодлежащВозраст
 v=СказуемоеВозраст : export { node:root_node }
} : links
{
 v.<SUBJECT>sbj
}

patterns СвязкаВозраста export { node:root_node }
pattern СвязкаВозраста
{
 'было'{ class:глагол } : export { node:root_node }
}

// мне тогда было двадцать два года
//     ^^^^^^^^^^
pattern СвязкаВозраста
{
 adv=Обст
 v='было'{ class:глагол } : export { node:root_node }
} : links { v.<ATTRIBUTE>adv }
: ngrams
{
 adv_verb_score( adv, v )
}

// мне было тогда шесть лет
//     ^^^^^^^^^^
pattern СвязкаВозраста
{
 v='было'{ class:глагол } : export { node:root_node }
 adv=Обст
} : links { v.<ATTRIBUTE>adv }
: ngrams
{
 adv_verb_score( adv, v )
}


pattern СвязкаВозраста
{
 'будет'{ class:глагол } : export { node:root_node }
}


// ему было двадцать пять лет
//     ^^^^^^^^^^^^^^^^^^^^^^
pattern ПредикатСвязка
{
 sbj=ПодлежащВозраст
 aux=СвязкаВозраста
 v=СказуемоеВозраст : export { node:root_node }
} : links
{
 v.{
    <SUBJECT>sbj
    <LEFT_AUX_VERB>aux
   }
}
