wordentry_set ЛогичСоюз2_Элем = 
{
 союз:хоть{},
 союз:то{},
 союз:или{},
 союз:и{},
 союз:либо{},
 союз:ни{}
}

patterns ЛогичСоюз2 export { node:root_node }
pattern ЛогичСоюз2
{
 ЛогичСоюз2_Элем : export { node:root_node }
}


// приехать не то из Омска, не то из Барнаула
//          ^^^^^           ^^^^^
pattern ЛогичСоюз2
{
 n=частица:не{}
 c=союз:то{} : export { node:root_node }
}
: links { c.<NEGATION_PARTICLE>n }
: ngrams { 2 }

// ---------------------------------

patterns СочинительныйСоюз1 export { node:root_node }





pattern СочинительныйСоюз1
{
 ЛогичСоюз2 : export { node:root_node }
}

wordentry_set НаречиеСледования1=наречие:{ сначала, поначалу, сперва }

pattern СочинительныйСоюз1
{
 НаречиеСледования1 : export { node:root_node }
}

// хотя и очень больной, но довольно сильный человек
wordentry_set СоюзноеНаречиеХотя={ союз:хотя{}, союз:хоть{} }

pattern СочинительныйСоюз1
{
 w1=СоюзноеНаречиеХотя{} : export { node:root_node }
 w2=союз:и{}
} : links { w1.<NEXT_COLLOCATION_ITEM>w2 }

collocation_set СоюзноеСловосочет1=
{
 "не только"
}

pattern СочинительныйСоюз1
{
 СоюзноеСловосочет1 : export { node:root_node }
}

// ++++++++++++++++++++++++++

patterns СочинительныйСоюз2 export { node:root_node }



collocation_set СоюзноеСловосочет2=
{
 "НО ДАЖЕ И"
}

pattern СочинительныйСоюз2
{
 СоюзноеСловосочет2 : export { node:root_node }
}



wordentry_set НаречиеСледования2=наречие:{ затем, потом, наконец, напоследок, после }
pattern СочинительныйСоюз2
{
 НаречиеСледования2 : export { node:root_node }
}

pattern СочинительныйСоюз2
{
 ЛогичСоюз2 : export { node:root_node }
}

pattern СочинительныйСоюз2
{
 союз:но{} : export { node:root_node }
}

// не только спастись от плена, но и заставить бежать своих преследователей
//                              ^^^^
pattern СочинительныйСоюз2
{
 conj1=союз:но{} : export { node:root_node }
 conj2=союз:и{}
} : links { conj1.<NEXT_COLLOCATION_ITEM>conj2 }

pattern СочинительныйСоюз2
{
 союз:да{} : export { node:root_node }
}

collocation_set ОборотСледования2=
{
 "а затем",
 "но затем",
 "а потом",
 "но потом",
 "но потом и",
 "ну а затем",
 "ну а затем и",
 "но затем и",
 "а затем и",
 "ну и",
 "но в конце концов",
 "но в итоге"
}


pattern СочинительныйСоюз2
{
 ОборотСледования2 : export { node:root_node }
}

// -----------------------------------------

patterns ПротивитСоюз export { node:root_node }

pattern ПротивитСоюз
{
 ПротивитСоюз0 :  export { node:root_node }
}


// Мы будем не только петь песни, но и танцевать зажигательные танцы
//                                ^^^^
pattern ПротивитСоюз
{
 conj1=союз:но{} :  export { node:root_node }
 conj2=союз:и{}
} : links { conj1.<NEXT_COLLOCATION_ITEM>conj2 }

// не только петь, но даже и плясать
//                 ^^^^^^^^^
pattern ПротивитСоюз
{
 conj1=союз:но{} :  export { node:root_node }
 p=частица:даже{}
 conj2=союз:и{}
} : links { conj1.<NEXT_COLLOCATION_ITEM>p.<NEXT_COLLOCATION_ITEM>conj2 }

// -----------------------------------------------------
// Соединители в паттерне ЕСЛИ ...., ТО ....
patterns ЕслиСоедГолова export { node:root_node }

pattern ЕслиСоедГолова
{
 h=союз:если{} : export { node:root_node }
}

wordentry_set ЧастицыДляЕсли = частица:{ же, ж, бы, б, уж } 
pattern ЕслиСоедГолова
{
 h=союз:если{} : export { node:root_node }
 p=ЧастицыДляЕсли
} : links { h.<POSTFIX_PARTICLE>p }


patterns ЕслиСоедХвост export { node:root_node }

pattern ЕслиСоедХвост
{
 h=союз:то{} : export { node:root_node }
}

pattern ЕслиСоедХвост
{
 h=союз:так{} : export { node:root_node }
}
