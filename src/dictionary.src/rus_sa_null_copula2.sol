// Восходяще-нисходящий разбор конструкций с нулевой связкой
// с именным сказуемым, согласующимся по числу с темой-подлежащим.


// -------------------------------------------------------

patterns ИменноеСказуемоеВосх { bottomup } export { node:root_node РОД ЛИЦО ЧИСЛО }

// Ты настоящий герой
//    ^^^^^^^^^^^^^^^
pattern ИменноеСказуемоеВосх
{
 ГруппаСущ4{ ПАДЕЖ:ИМ } : export { ЧИСЛО РОД ЛИЦО:3 node:root_node }
}

// Это я!
//    ^^^
pattern ИменноеСказуемоеВосх
{
 ГруппаМест{ ПАДЕЖ:ИМ } : export { ЧИСЛО РОД ЛИЦО:3 node:root_node }
}


// Она умная и красивая
//     ^^^^^^^^^^^^^^^^
pattern ИменноеСказуемоеВосх
{
 ГруппаПрил2{ ПАДЕЖ:ИМ } : export { РОД ЛИЦО:3 ЧИСЛО node:root_node }
} : ngrams { -2 }


pattern ИменноеСказуемоеВосх
{
 ГруппаМест{ ПАДЕЖ:ИМ } : export { РОД ЛИЦО ЧИСЛО node:root_node }
} : ngrams { -4 }


// ------------------------------------------

// ты кто?
//    ^^^

patterns КтоСказуемое export { node:root_node РОД }
pattern КтоСказуемое
{
 n=местоим_сущ:*{ РОД:МУЖ ПАДЕЖ:ИМ } : export { РОД node:root_node }
}

// Ты-то кто же?
//       ^^^^^^
pattern КтоСказуемое
{
 n=местоим_сущ:*{ РОД:МУЖ ПАДЕЖ:ИМ } : export { РОД node:root_node }
 p=ЧастицаЖе
}
: links { n.<POSTFIX_PARTICLE>p }
: ngrams { 1 }


pattern ИменноеСказуемоеВосх export { (ЧИСЛО) ЛИЦО РОД node:root_node }
{
 КтоСказуемое : export { ЛИЦО:3 РОД node:root_node }
}

// ------------------------------------------

// без нее ты ничто
//            ^^^^^

patterns ЧтоСказуемое export { РОД node:root_node }

// Это что?
//     ^^^
pattern ЧтоСказуемое
{
 n=местоим_сущ:*{ род:ср падеж:им } : export { РОД node:root_node }
}

pattern ЧтоСказуемое
{
 n=местоим_сущ:*{ род:ср падеж:им } : export { РОД node:root_node }
 p=ЧастицаЖе
}
: links { n.<POSTFIX_PARTICLE>p }
: ngrams { 1 }

pattern ИменноеСказуемоеВосх
{
 ЧтоСказуемое : export { ЧИСЛО:ЕД ЛИЦО:3 РОД node:root_node }
}


// -----------------------------------

// Кто это?
pattern ИменноеСказуемоеВосх
{
 местоим_сущ:это{ ПАДЕЖ:ИМ } : export { ЧИСЛО:ЕД РОД:СР ЛИЦО:3 node:root_node }
}


// ------------------------------------------

pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 obj=ГлДополнение{ ~ПАДЕЖ:ИМ ~ПАДЕЖ:ПРЕДЛ }
}
: links { v.<OBJECT>obj }
: ngrams { -8 }


// ты предатель теперь
pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 adv=Обст
}
: links { v.<ATTRIBUTE>adv }


// Вопрос тут срочный и до утра ждать не может.
pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 conj=СочинитСоюзПредикат
 v2=Сказуемое{ =v:РОД =v:ЧИСЛО =v:ЛИЦО }
 @noshift(ПравыйОграничительОборота)
}
: links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }

// Дело срочное, до утра ждать не может.
pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 comma=','
 v2=Сказуемое{ =v:РОД =v:ЧИСЛО =v:ЛИЦО }
 @noshift(ПравыйОграничительОборота)
}
: links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }


// Дело срочное, но до утра подождет.
pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 comma=','
 conj=СочинитСоюзПредикат
 v2=Сказуемое{ =v:РОД =v:ЧИСЛО =v:ЛИЦО }
 @noshift(ПравыйОграничительОборота)
}
: links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// Она умница, конечно.
pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 adv=ВводнАктант
} : links { v.<BEG_INTRO>adv }


pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 d=Детализатор
} : links { v.<DETAILS>d }


pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 pn=ПредлогИСущ
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams { -5 }

// кто же она такая?
//            ^^^^^
pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 attr=ОбособленныйАтрибут
}
: links { v.<SEPARATE_ATTR>attr }
: ngrams { -5 }

// Обособленный атрибут в иминительном падеже, согласующийся
// со сказуемым по числу:
//
// Кто ты такой?
//        ^^^^^
pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 attr=ГруппаПрил2{ ПАДЕЖ:ИМ =v:ЧИСЛО }
}
: links { v.<SEPARATE_ATTR>attr }
: ngrams { -2 }

// так кто вы такой?
//            ^^^^^
pattern ИменноеСказуемоеВосх
{
 v=ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО node:root_node }
 attr=ГруппаПрил2{ ПАДЕЖ:ИМ }
}
: links { v.<SEPARATE_ATTR>attr }
: ngrams { -3 }


// --------------------------------------------------------

patterns ИменноеСказуемоеНисх export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY node:root_node }

pattern ИменноеСказуемоеНисх
{
 ИменноеСказуемоеВосх : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY:1 node:root_node }
}

// Ты теперь начальник
pattern ИменноеСказуемоеНисх
{
 adv=Обст
 v=ИменноеСказуемоеНисх : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY node:root_node }
}
: links { v.<ATTRIBUTE>adv }
: ngrams { -1 }


// Конечно, ты начальник.
pattern ИменноеСказуемоеНисх
{
 intro=ВводнАктант
 v=ИменноеСказуемоеНисх : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY node:root_node }
} 
: links { v.<BEG_INTRO>intro }


pattern ИменноеСказуемоеНисх
{
 intro=Детализатор
 v=ИменноеСказуемоеНисх : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY node:root_node }
} 
: links { v.<DETAILS>intro }


// На работе ты босс.
pattern ИменноеСказуемоеНисх
{
 pn=ПредлогИСущ
 v=ИменноеСказуемоеНисх : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY node:root_node }
} 
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams { -5 }



pattern ИменноеСказуемоеНисх
{
 obj=ГлДополнение{ ~ПАДЕЖ:ИМ ~ПАДЕЖ:ПРЕДЛ }
 v=ИменноеСказуемоеНисх : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY node:root_node }
}
: links { v.<OBJECT>obj }
: ngrams { -8 }


// Обособленное определение:
// хороший ты человек
// ^^^^^^^
pattern ИменноеСказуемоеНисх
{
 attr=ГруппаПрил2{ ПАДЕЖ:ИМ }
 v=ИменноеСказуемоеНисх{ =attr:ЧИСЛО } : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY node:root_node }
}
: links { v.<SEPARATE_ATTR>attr }
: ngrams { -2 }

// Хороший Вы человек.
// ^^^^^^^
pattern ИменноеСказуемоеНисх
{
 attr=ГруппаПрил2{ ПАДЕЖ:ИМ }
 v=ИменноеСказуемоеНисх : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY node:root_node }
}
: links { v.<SEPARATE_ATTR>attr }
: ngrams { -3 }



// Прикрепляем подлежащее
pattern ИменноеСказуемоеНисх
{
 sbj=Подлежащее
 v=ИменноеСказуемоеНисх{ THEMA_VALENCY:1 =sbj:ЧИСЛО } : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY:0 node:root_node }
}
: links { v.<SUBJECT>sbj }


// Наше дело тракторы.
wordentry_set ПодлежащееДляСвязкиКакМнож = существительное:{ дело }
pattern ИменноеСказуемоеНисх
{
 sbj=Подлежащее{ ПодлежащееДляСвязкиКакМнож ЧИСЛО:ЕД }
 v=ИменноеСказуемоеНисх{ THEMA_VALENCY:1 ЧИСЛО:МН } : export { ЧИСЛО РОД ЛИЦО THEMA_VALENCY:0 node:root_node }
}
: links { v.<SUBJECT>sbj }


// --------------------------------------------------------------------
// Местоимение ВЫ согласуется с именным сказуемым в единственном числе:
//
// вы гость
pattern ИменноеСказуемоеНисх
{
 sbj=ГруппаМест{ ЛИЦО:2 ЧИСЛО:МН ПАДЕЖ:ИМ } : export { ЛИЦО РОД } 
 v=ИменноеСказуемоеНисх{ THEMA_VALENCY:1 ЧИСЛО:ЕД } : export { ЧИСЛО THEMA_VALENCY:0 node:root_node }
}
: links { v.<SUBJECT>sbj }



// --------------------------------------------------

// Местоимение ЭТО в роли подлежащего, без согласования по числу:

patterns Это_Тема export { node:root_node }

// это два разных воспоминания
// ^^^
pattern Это_Тема
{
 n=местоим_сущ:это{ ПАДЕЖ:ИМ } : export { node:root_node }
}


// это же дракон!
// ^^^^^^
pattern Это_Тема
{
 n=местоим_сущ:это{ ПАДЕЖ:ИМ } : export { node:root_node }
 p=ЧастицаЖе
} : links { n.<POSTFIX_PARTICLE>p }

// Это-то я понял
// ^^^^^^
pattern Это_Тема
{
 n=местоим_сущ:это{ ПАДЕЖ:ИМ } : export { node:root_node }
 t='-'
 p=частица:то{}
} : links { n.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>p }


// это мои слова
// ^^^
pattern ИменноеСказуемоеНисх
{
 sbj=Это_Тема : export { ЛИЦО:3 РОД:СР }
 v=ИменноеСказуемоеНисх{ THEMA_VALENCY:1 } : export { ЧИСЛО THEMA_VALENCY:0 node:root_node }
}
: links { v.<SUBJECT>sbj }


// -------------------------------------------------


// -------------------------------------------------

patterns КтоПодлежащее export { node:root_node }
pattern КтоПодлежащее
{
 n=местоим_сущ:кто{ ПАДЕЖ:ИМ } : export { node:root_node }
}

// кто же хозяин этих птиц?
// ^^^^^^
pattern КтоПодлежащее
{
 n=местоим_сущ:кто{ ПАДЕЖ:ИМ } : export { node:root_node }
 p=ЧастицаЖе
} : links { n.<POSTFIX_PARTICLE>p }
: ngrams { 1 }


// Да кто же вы?
pattern ИменноеСказуемоеНисх
{
 sbj=КтоПодлежащее : export { ЛИЦО:3 РОД:МУЖ }
 v=ИменноеСказуемоеНисх{ THEMA_VALENCY:1 } : export { ЧИСЛО THEMA_VALENCY:0 node:root_node }
}
: links { v.<SUBJECT>sbj }


// ============================================================

// Вопрос тут серьезный
// ^^^^^^^^^^^^^^^^^^^^
pattern ПредикатСвязка
{
 t=ИменноеСказуемоеНисх{ THEMA_VALENCY:0 } : export { node:root_node }
}
: ngrams
{
 -7
 ВалентностьНульСвязки(t)
}

