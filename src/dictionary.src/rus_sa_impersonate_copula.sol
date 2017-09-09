
// ----------------------------------------------

// их здесь было вполне достаточно
// через минуту их уже стало больше.

wordform_set БезличСвязк0=
{
 'становилось'{ class:безлич_глагол },
 'осталось'{ class:безлич_глагол },
 'останется'{ class:безлич_глагол },
 'становится'{ class:безлич_глагол },
 'стало'{ class:безлич_глагол },
 'было'{ class:глагол },
 'будет'{ class:глагол }
}



patterns БезличСвязк export { node:root_node }

pattern БезличСвязк
{
 БезличСвязк0 : export { node:root_node }
}



wordentry_set VerbPostfix=частица:{ бы, б, же, ж, ли, ль }
// Вас стало бы семеро!
//     ^^^^^^^^
pattern БезличСвязк
{
 v=БезличСвязк0 : export { node:root_node }
 p=VerbPostfix
} : links { v.<POSTFIX_PARTICLE>p }



// Его  нигде  не  было  видно.
//             ^^^^^^^^
pattern БезличСвязк
{
 n=частица:не{}
 v=БезличСвязк : export { node:root_node }
} : links { v.<NEGATION_PARTICLE>n }

// --------------

patterns СталоВосх { bottomup  } export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }

// Их было пятеро.
pattern СталоВосх
{
 БезличСвязк : export { node:root_node ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД }
}

// Волков осталось там трое
pattern СталоВосх
{
 v=СталоВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 adv=Обст
} : links
{
 v.<ATTRIBUTE>adv
}
: ngrams
{
 adv_verb_score( adv, v )
}


// ------------

patterns ImpersCopulaSubject export { node:root_node }


// всего их было шестеро
//               ^^^^^^^
pattern ImpersCopulaSubject
{
 СобирЧислит{ ПАДЕЖ:ИМ } : export { node:root_node }
}


// -------------------------------------

// всего их было тринадцать
//               ^^^^^^^^^^
pattern ImpersCopulaSubject
{
 ГруппаЧисл{ ПАДЕЖ:ИМ } : export { node:root_node }
}


// -------------------------------------

// У меня было три любимых игрушки
//             ^^^^^^^^^^^^^^^^^^^
pattern ImpersCopulaSubject
{
 ЧислСущ{ ПАДЕЖ:ИМ } : export { node:root_node }
}

// -----------------------

// теперь нас осталось шестеро
//                     ^^^^^^^
pattern СталоВосх
{
 v=СталоВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 q=ImpersCopulaSubject
} : links
{
 v.<ATTRIBUTE>q
}


// Их осталось в первой каюте трое
pattern СталоВосх
{
 v=СталоВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 pn=ПредлогИСущ{ гл_предл( v, _.prepos, _.n2 ) }
} : links
{
 v.<PREPOS_ADJUNCT>pn
}
: ngrams
{
 prepos_score( v, pn.prepos )
 ngram3( v, pn.prepos, pn.n2 )
}


// --------------------------------------------------------

patterns СталоНисх export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }

pattern СталоНисх
{
 СталоВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
}

// Тут их было четверо.
pattern СталоНисх
{
 adv=Обст
 v=СталоНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
} 
: links
{
 v.<ATTRIBUTE>adv
}
: ngrams
{
 adv_verb_score( adv, v )
}

// всего их было шестеро
// ^^^^^
pattern СталоНисх
{
 adv=наречие:всего{}
 v=СталоНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
} : links { v.<ATTRIBUTE>adv }

pattern СталоНисх
{
 pn=ПредлогИСущ
 v=СталоНисх { гл_предл(_,pn.prepos,pn.n2) } : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
} 
: links
{
 v.<PREPOS_ADJUNCT>pn
}
: ngrams
{
 -1
 prepos_score( v, pn.prepos )
}


patterns МножРодДоп0 export { ПАДЕЖ node:root_node }
pattern МножРодДоп0
{
 местоимение:*{ число:мн } : export { ПАДЕЖ node:root_node }
}

pattern МножРодДоп0
{
 ГруппаСущ4{ число:мн } : export { ПАДЕЖ node:root_node }
}

pattern МножРодДоп0
{
 ГруппаПрил2{ число:мн } : export { ПАДЕЖ node:root_node }
} : ngrams { -2 }


patterns МножРодДоп export { node:root_node }

/*
pattern МножРодДоп
{
 МножРодДоп0{ ПАДЕЖ:ВИН } : export { node:root_node }
}
*/

pattern МножРодДоп
{
 МножРодДоп0{ ПАДЕЖ:РОД } : export { node:root_node }
} //: ngrams { -1 }


pattern СталоНисх export { node:root_node ПЕРЕХОДНОСТЬ (ПАДЕЖ) }
{
 obj=МножРодДоп
 v=СталоНисх { ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ }
     : export { node:root_node ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
} : links { v.<OBJECT>obj }
: ngrams
{
 v_obj_score( v, obj )
}

// -------------------------------------------

pattern ГлПредикат
{
 v=СталоНисх : export { node:root_node }
}
: ngrams
{
 //-1 // немного придавим, чтобы не конфликтовать с "внутри палатки было очень тихо"
 ВалентностьГлагола(v)
}

// -----------------------------------------


// На этой же стороне никакого тяготения не было.
