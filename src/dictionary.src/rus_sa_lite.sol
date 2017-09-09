

patterns Подлежащее00 export { ЛИЦО ЧИСЛО РОД node:root_node }

pattern Подлежащее00
{
 местоимение:я{ ПАДЕЖ:ИМ } : export { ЛИЦО ЧИСЛО РОД node:root_node }
}

pattern Подлежащее00
{
 существительное:*{ ПАДЕЖ:ИМ } : export { ЛИЦО:3 ЧИСЛО РОД node:root_node }
}

pattern Подлежащее00
{
 местоим_сущ:*{ ПАДЕЖ:ИМ } : export { ЛИЦО:3 ЧИСЛО РОД node:root_node }
}

/*
pattern Подлежащее00
{
 прилагательное:*{ ПАДЕЖ:ИМ } : export { ЛИЦО:3 ЧИСЛО РОД node:root_node }
} : ngrams { -4 }
*/

// ---------------------------------------------------------------

patterns ГлНастБуд00 export { ЛИЦО ЧИСЛО node:root_node }

pattern ГлНастБуд00
{
 глагол:*{ время:настоящее } : export { node:root_node ЛИЦО ЧИСЛО }
}

pattern ГлНастБуд00
{
 глагол:*{ время:будущее } : export { node:root_node ЛИЦО ЧИСЛО }
}


pattern ГлНастБуд00
{
 n=частица:не{}
 v=глагол:*{ время:настоящее } : export { node:root_node ЛИЦО ЧИСЛО }
} : links { v.<NEGATION_PARTICLE>n }

pattern ГлНастБуд00
{
 n=частица:не{}
 v=глагол:*{ время:будущее } : export { node:root_node ЛИЦО ЧИСЛО }
} : links { v.<NEGATION_PARTICLE>n }



// ---------------------------------------------------------------

patterns ГлПрош00 export { РОД ЧИСЛО node:root_node }

pattern ГлПрош00
{
 глагол:*{ время:прошедшее } : export { node:root_node РОД ЧИСЛО }
}

pattern ГлПрош00
{
 n=частица:не{}
 v=глагол:*{ время:прошедшее } : export { node:root_node РОД ЧИСЛО }
} : links { v.<NEGATION_PARTICLE>n }



// ---------------------------------------------------------------

patterns ГлИмператив00 export { ЛИЦО ЧИСЛО node:root_node }

pattern ГлИмператив00
{
 глагол:*{ наклонение:ПОБУД } : export { node:root_node ЛИЦО ЧИСЛО }
}

// Ты не печалься
pattern ГлИмператив00
{
 n=частица:не{}
 v=глагол:*{ наклонение:ПОБУД } : export { node:root_node ЛИЦО ЧИСЛО }
} : links { v.<NEGATION_PARTICLE>n }

// ---------------------------------------------------------------

patterns Предикат00 export { node:root_node }

// я вижу
pattern Предикат00
{
 sbj=Подлежащее00
 v=ГлНастБуд00{ =sbj:ЛИЦО =sbj:ЧИСЛО } : export { node:root_node }
} : links { v.<SUBJECT>sbj }

// я видел
pattern Предикат00
{
 sbj=Подлежащее00
 v=ГлПрош00{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
} : links { v.<SUBJECT>sbj }


// Вы оценивайте
pattern Предикат00
{
 sbj=Подлежащее00
 v=ГлИмператив00{ =sbj:ЛИЦО =sbj:ЧИСЛО } : export { node:root_node }
} : links { v.<SUBJECT>sbj }


pattern language=Russian
{
 beth:begin{}
 Предикат00
 beth:end{}
}



