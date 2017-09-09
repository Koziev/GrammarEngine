
// сколько у тебя братьев?
// ^^^^^^^

patterns СчетнПредикатив export { node:root_node }

wordentry_set СчетнСвязка=
{
 наречие:достаточно{},
 наречие:недостаточно{}, // у меня недостаточно данных.
 наречие:несколько{},
 наречие:сколько-то{},
 наречие:сколько{},
 наречие:много{},
 наречие:многовато{},
 наречие:маловато{},
 наречие:полно{},
 наречие:полным-полно{},
 наречие:мало{}
}

pattern СчетнПредикатив
{
 СчетнСвязка:export { node:root_node }
}

pattern СчетнПредикатив
{
 v=СчетнСвязка:export { node:root_node }
 p=частица:же{}
} : links { v.<POSTFIX_PARTICLE>p }

pattern СчетнПредикатив
{
 v=СчетнСвязка:export { node:root_node }
 p=частица:ли{}
} : links { v.<POSTFIX_PARTICLE>p }


// ++++++++++++

patterns СчетнВосх { bottomup  } export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }

pattern СчетнВосх
{
 СчетнПредикатив : export { node:root_node ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД @add(ПАДЕЖ:ДАТ) }
}

pattern СчетнВосх
{
 v=СчетнВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД } : export { node:root_node }
 obj=РодДополнение : export {
                             @except(v:ПАДЕЖ,ПАДЕЖ)
                             @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
                            }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }


pattern СчетнВосх
{
 v=СчетнВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ДАТ } : export { node:root_node }
 obj=ГлДополнение{ ПАДЕЖ:ДАТ } : export {
                                         @except(v:ПАДЕЖ,ПАДЕЖ)
                                         @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
                                        }
}
: links { v.<OBJECT>obj }
: ngrams { -5 }



pattern СчетнВосх
{
 v=СчетнВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 adv=Обст
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score( adv, v ) }


pattern СчетнВосх
{
 v=СчетнВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 attr=ОбособРодАтрибут
} : links { v.<SEPARATE_ATTR>attr }


pattern СчетнВосх
{
 v=СчетнВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 attr=ВводнАктант
} : links { v.<BEG_INTRO>attr }

pattern СчетнВосх
{
 v=СчетнВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 attr=Детализатор
} : links { v.<DETAILS>attr }

pattern СчетнВосх
{
 v=СчетнВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 x=ПрямоеОбращение
} : links { v.<APPEAL>x }

pattern СчетнВосх
{
 v=СчетнВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 pn=ПредлогИСущ{ гл_предл( v, _.prepos, _.n2 ) }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score( v, pn.prepos )
 ngram3( v, pn.prepos, pn.n2 )
}

// --------------------------------------------------------

patterns СчетнНисх export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }

pattern СчетнНисх
{
 СчетнВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
}

pattern СчетнНисх
{
 adv=Обст
 v=СчетнНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
} 
: links { v.<ATTRIBUTE>adv }
: ngrams
{
 -1
 adv_verb_score( adv, v )
}



pattern СчетнНисх
{
 attr=ОбособРодАтрибут
 v=СчетнНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
} : links { v.<SEPARATE_ATTR>attr }

pattern СчетнНисх
{
 attr=ВводнАктант
 v=СчетнНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
} : links { v.<BEG_INTRO>attr }


pattern СчетнНисх
{
 attr=Детализатор
 v=СчетнНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
} : links { v.<DETAILS>attr }


pattern СчетнНисх
{
 x=ПрямоеОбращение
 v=СчетнНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
} 
: links { v.<APPEAL>x }

pattern СчетнНисх
{
 pn=ПредлогИСущ
 v=СчетнНисх { гл_предл(_,pn.prepos,pn.n2) } : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
} 
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 -2
 prepos_score( v, pn.prepos )
 ngram3( v, pn.prepos, pn.n2 )
}



pattern СчетнНисх
{
 obj=РодДополнение
 v=СчетнНисх { ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД }
     : export { 
               node:root_node
               @except(ПАДЕЖ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -1
 v_obj_score( v, obj )
}


pattern СчетнНисх
{
 obj=ГлДополнение{ ПАДЕЖ:ДАТ }
 v=СчетнНисх { ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ДАТ }
     : export { 
               node:root_node
               @except(ПАДЕЖ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
}
: links { v.<OBJECT>obj }
: ngrams { -5 }


// -------------------------------------------

pattern ГлПредикат
{
 v=СчетнНисх : export { node:root_node }
}
: ngrams
{
 ВалентностьПредиката(v)
}
