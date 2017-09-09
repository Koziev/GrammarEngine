// Восходяще-нисходящий разбор конструкций с нулевой связкой,
// для случаев, когда сказуемое выражено обстоятельственными
// членами предоложения.
// Для случаев, когда рема является именным сказуемым,
// см. другой набор правил в rus_sa_null_copula2.sol




// -------------------------------------------------------

patterns ТемаВосх { bottomup } export { node:root_node }

pattern ТемаВосх
{
 ГлДополнение{ [-2]ПАДЕЖ:ИМ } : export { node:root_node }
}


// В этом-то и дело.
//           ^^^^^^
pattern ТемаВосх
{
 p=частица:и{}
 n=ГруппаСущ4{ ПАДЕЖ:ИМ } : export { node:root_node }
}
: ngrams { -2 }
: links { n.<PREFIX_PARTICLE>p }



// -----------------------

patterns ЧтоТема export { node:root_node }
pattern ЧтоТема
{
 n=местоим_сущ:что{ падеж:им } : export { node:root_node }
}

pattern ЧтоТема
{
 n=местоим_сущ:что{ падеж:им } : export { node:root_node }
 p=ЧастицаЖе
} : links { n.<POSTFIX_PARTICLE>p }
: ngrams { 1 }


// Что такое теперь?
// ^^^^^^^^^
pattern ТемаВосх
{
 p=ЧтоТема : export { node:root_node }
 a=прилагательное:такой{ падеж:им число:ед род:ср }
} : links { p.<ATTRIBUTE>a }

// ------------------------

pattern ТемаВосх
{
 v=ТемаВосх : export { node:root_node }
 obj=ГлДополнение{ ~ПАДЕЖ:ИМ ~ПАДЕЖ:ПРЕДЛ }
}
: links { v.<OBJECT>obj }
: ngrams { -8 }


pattern ТемаВосх
{
 v=ТемаВосх : export { node:root_node }
 adv=Обст
}
: links { v.<ATTRIBUTE>adv }
: ngrams { -1 }


pattern ТемаВосх
{
 v=ТемаВосх : export { node:root_node }
 adv=ВводнАктант
} : links { v.<BEG_INTRO>adv }


pattern ТемаВосх
{
 v=ТемаВосх : export { node:root_node }
 d=Детализатор
} : links { v.<DETAILS>d }

pattern ТемаВосх
{
 v=ТемаВосх : export { node:root_node }
 pn=ПредлогИСущ
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams { -5 }


pattern ТемаВосх
{
 v=ТемаВосх : export { node:root_node }
 pn=ОбособленныйАтрибут
}
: links { v.<SEPARATE_ATTR>pn }
: ngrams { -8 }


// --------------------------------------------------------

patterns ТемаНисх export { node:root_node }

pattern ТемаНисх
{
 ТемаВосх : export { node:root_node }
}

// Тут сырость!
pattern ТемаНисх
{
 adv=Обст
 v=ТемаНисх : export { node:root_node }
}
: links { v.<ATTRIBUTE>adv }
: ngrams { -1 }


// Конечно, я тут
// ^^^^^^^^
pattern ТемаНисх
{
 intro=ВводнАктант
 v=ТемаНисх : export { node:root_node }
} 
: links { v.<BEG_INTRO>intro }


pattern ТемаНисх
{
 intro=Детализатор
 v=ТемаНисх : export { node:root_node }
} 
: links { v.<DETAILS>intro }


// У него грипп
pattern ТемаНисх
{
 pn=ПредлогИСущ
 v=ТемаНисх : export { node:root_node }
} 
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams { -5 }



pattern ТемаНисх
{
 obj=ГлДополнение{ ~ПАДЕЖ:ИМ ~ПАДЕЖ:ПРЕДЛ }
 v=ТемаНисх : export { node:root_node }
}
: links { v.<OBJECT>obj }
: ngrams { -8 }


// Обособленный атрибут, согласующийся с именным сказуемым по числу:
//
// такие у нас правила
// ^^^^^
pattern ТемаНисх
{
 attr=ГруппаПрил2{ ПАДЕЖ:ИМ }
 v=ТемаНисх : export { node:root_node }
}
: links { v.<SEPARATE_ATTR>attr }
: ngrams { -5 }


// ============================================================

tree_scorers ВалентностьНульСвязки

// Пусть разберутся, в чем дело.
//                   ^^^^^^^^^^
pattern ПредикатСвязка
{
 p=ТемаНисх : export { node:root_node }
}
: ngrams
{
 -5
 ВалентностьНульСвязки(p)
}


// Ванную огромная
pattern ПредикатСвязка
{
 sbj=ГлДополнение{ [-2]ПАДЕЖ:ИМ } : export { node:root_node }
 attr=ГруппаПрил2{ [-2]ПАДЕЖ:ИМ =sbj:РОД =sbj:ЧИСЛО }
}
: links { sbj.<ATTRIBUTE>attr }
: ngrams
{
 -7
 ВалентностьНульСвязки(sbj)
}
