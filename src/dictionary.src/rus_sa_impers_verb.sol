
// НЕМОДАЛЬНЫЕ КОНСТРУКЦИИ С БЕЗЛИЧНЫМ ГЛАГОЛОМ (ПРЕДИКАТИВОМ)

patterns БезличГлаг0 export { ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }

pattern БезличГлаг0
{
 БЕЗЛИЧ_ГЛАГОЛ:*{}:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
}







// Порой мне случается видеть будущее.
//           ^^^^^^^^^
pattern БезличГлаг0
{
 глагол:*{ ВРЕМЯ:НАСТОЯЩЕЕ ЧИСЛО:ЕД ЛИЦО:3 }
  :export { ТИП_ПРЕДИКАТИВ:АВТОНОМ МОДАЛЬНЫЙ @add(МОДАЛЬНЫЙ) ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
} : ngrams { -5 }


pattern БезличГлаг0
{
 глагол:*{ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР }
  :export { ТИП_ПРЕДИКАТИВ:АВТОНОМ МОДАЛЬНЫЙ @add(МОДАЛЬНЫЙ) ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
} : ngrams { -5 }


// Связочные глаголы ОКАЗАЛОСЬ/БЫЛО/СТАЛО/... приобретают родительную валентность 
// в безличной конструкции:
//
// но и этого оказалось недостаточно 
//      ^^^^^
//
// Контрпример:
// Теперь ее содержание стало понятно.
//        ~~            ^^^^^
pattern БезличГлаг0
export { ТИП_ПРЕДИКАТИВ (МОДАЛЬНЫЙ) ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
{
 v=СвязочныйГлагол{ ВРЕМЯ:ПРОШЕДШЕЕ РОД:СР ЧИСЛО:ЕД } : export { ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД ТИП_ПРЕДИКАТИВ:БЫЛО_СВЯЗКА node:root_node }
}


// -----------------------------------

patterns БезличГлаг export { ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }

pattern БезличГлаг
{
 БезличГлаг0:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
}


// из космоса можно и нужно осваивать землю
//            ^^^^^^^^^^^^^
pattern БезличГлаг
{
 v1=БезличГлаг0:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
 conj=ЛогичСоюз
 v2=БезличГлаг0
} : links { v1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// Этому рыцарю пришлось-таки снять доспехи.
//              ^^^^^^^^^^^^^
pattern БезличГлаг
{
 v=БезличГлаг0:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
 t='-'
 p=частица:таки{}
} : links { v.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>p }



// следует ли подать в отставку
pattern БезличГлаг
{
 v=БезличГлаг0:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
 p=частица:ли{}
} : links { v.<POSTFIX_PARTICLE>p }


// нельзя же вечно прятаться между деревьями
// ^^^^^^^^^
// нельзя ж так
// ^^^^^^^^
pattern БезличГлаг
{
 v=БезличГлаг0:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
 p=ЧастицаЖе
} : links { v.<POSTFIX_PARTICLE>p }

// лучше уж мне умереть
// ^^^^^^^^
pattern БезличГлаг
{
 v=БезличГлаг0:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
 p=частица:уж{}
} : links { v.<POSTFIX_PARTICLE>p }

// мне пришлось бы сделать именно так.
//     ^^^^^^^^^^^
pattern БезличГлаг
{
 v=БезличГлаг0:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
 p=ЧастицаБы
} : links { v.<POSTFIX_PARTICLE>p }



// К ней заходить не хотелось бы.
//                ^^^^^^^^^^^^^^
pattern БезличГлаг
{
 n=частица:не{}
 v=БезличГлаг:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
} : links
{
 v.<NEGATION_PARTICLE>n
}



// - Им и не нужно осаждать замок.
//      ^^^^^^^^^^
pattern БезличГлаг
{
 n=частица:и{}
 v=БезличГлаг:export{ ТИП_ПРЕДИКАТИВ МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ node:root_node }
}
: links { v.<PREFIX_PARTICLE>n }
: ngrams { -5 }



// -----------------------------------

// Теперь восходящая сборка с немодальными безличными

patterns ГлБезличВосх { bottomup  }
 export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }

// Мне жаль
pattern ГлБезличВосх export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ (THEMA_VALENCY) }
{
 БезличГлаг : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ @add(THEMA_VALENCY:1) }
}


// Жаль мне тебя
//      ^^^
pattern ГлБезличВосх
{
 v=ГлБезличВосх{THEMA_VALENCY:1} : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY:0 }
 sbj=БезличПодлежащее{ ПАДЕЖ:ДАТ }
} : links { v.<SUBJECT>sbj }

wordform_set БезличСвязка0=
{
 'было'{ class:ГЛАГОЛ },
 'будет'{ class:ГЛАГОЛ },
 'стало'{ class:ГЛАГОЛ },
 'станет'{ class:ГЛАГОЛ },
 'становилось'{ class:ГЛАГОЛ },
 'становится'{ class:ГЛАГОЛ },
 'бывало'{ class:ГЛАГОЛ }
}

patterns БезличСвязка export { node:root_node }

pattern БезличСвязка
{
 v=БезличСвязка0 : export { node:root_node }
}

// Мне было бы жаль их
//     ^^^^^^^
pattern БезличСвязка
{
 v=БезличСвязка0 : export { node:root_node }
 p=ЧастицаБы
} : links { v.<POSTFIX_PARTICLE>p }


// Мне жаль стало их
//          ^^^^^
pattern ГлБезличВосх
{
 v=ГлБезличВосх{ТИП_ПРЕДИКАТИВ:БЫЛО_СВЯЗКА} : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
 aux=БезличСвязка
} : links { v.<LEFT_AUX_VERB>aux }



// Мне жаль тебя
//          ^^^^
pattern ГлБезличВосх
{
 v=ГлБезличВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ } : export { node:root_node ТИП_ПРЕДИКАТИВ THEMA_VALENCY }
 obj=ГлДополнение{ =v:ПАДЕЖ } : export {
                                        @except(v:ПАДЕЖ,ПАДЕЖ)
                                        @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
                                       }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }



// Мне жаль слегка
//          ^^^^^^
pattern ГлБезличВосх
{
 v=ГлБезличВосх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
 adv=Обст
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score( adv, v ) }


pattern ГлБезличВосх
{
 v=ГлБезличВосх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
 attr=ОбособленныйАтрибут
} : links { v.<SEPARATE_ATTR>attr }

pattern ГлБезличВосх
{
 v=ГлБезличВосх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
 attr=ВводнАктант
} : links { v.<BEG_INTRO>attr }

pattern ГлБезличВосх
{
 v=ГлБезличВосх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
 attr=Детализатор
} : links { v.<DETAILS>attr }

// Мне жаль тебя, Николай!
//              ^^^^^^^^^
pattern ГлБезличВосх
{
 v=ГлБезличВосх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
 x=ПрямоеОбращение
} : links { v.<APPEAL>x }


pattern ГлБезличВосх
{
 v=ГлБезличВосх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
 pn=ПредлогИСущ{ гл_предл( v, _.prepos, _.n2 ) }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score( v, pn.prepos )
 ngram3( v, pn.prepos, pn.n2 )
}



// Мне жаль, что пришлось уходить
pattern ГлБезличВосх export { ТИП_ПРЕДИКАТИВ (ПАДЕЖ) ПЕРЕХОДНОСТЬ THEMA_VALENCY node:root_node }
{
 v=ГлБезличВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН } : export { ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ THEMA_VALENCY node:root_node }
 comma=','
 conj=СоединДляПридаточного
 p=ПридаточноеВОбороте
 comma2=@coalesce(',')
} : links
{
 v.<SUBORDINATE_CLAUSE>comma.
    <NEXT_COLLOCATION_ITEM>conj.
     <NEXT_COLLOCATION_ITEM>p.
      ~<PUNCTUATION>comma2
}


/*
pattern ГлБезличВосх export { ЛИЦО ЧИСЛО (ПАДЕЖ) (МОДАЛЬНЫЙ) ПЕРЕХОДНОСТЬ ВРЕМЯ node:root_node }
{
 v=ГлБезличВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН } : export { ЛИЦО ЧИСЛО ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ВРЕМЯ node:root_node }
 p=БессоюзноеПридаточное
}
: links { v.<SUBORDINATE_CLAUSE>p }
: ngrams { -1 }
*/

// --------------------------------------------------------

patterns ГлБезличНисх export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }

pattern ГлБезличНисх
{
 ГлБезличВосх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
}

// Мне очень жалко
pattern ГлБезличНисх
{
 adv=Обст
 v=ГлБезличНисх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score( adv, v ) }

patterns ЛевАтрибутСказуем export { node:root_node }

// Тебе что, плохо живется?
//      ^^^^
pattern ГлБезличНисх
{
 adv=ЛевАтрибутСказуем
 v=ГлБезличНисх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
}
: links { v.<ATTRIBUTE>adv }
: ngrams { -1 }


// Мне жаль тебя
// ^^^
pattern ГлБезличНисх
{
 sbj=БезличПодлежащее{ ПАДЕЖ:ДАТ }
 v=ГлБезличНисх{THEMA_VALENCY:1} : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY:0 }
} : links { v.<SUBJECT>sbj }

// Мне было жаль их
//     ^^^^^
pattern ГлБезличНисх
{
 aux=БезличСвязка
 v=ГлБезличНисх{ТИП_ПРЕДИКАТИВ:БЫЛО_СВЯЗКА} : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
} : links { v.<LEFT_AUX_VERB>aux }



pattern ГлБезличНисх
{
 attr=ОбособленныйАтрибут
 v=ГлБезличНисх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
} : links { v.<SEPARATE_ATTR>attr }

pattern ГлБезличНисх
{
 attr=ВводнАктант
 v=ГлБезличНисх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
} : links { v.<BEG_INTRO>attr }


pattern ГлБезличНисх
{
 attr=Детализатор
 v=ГлБезличНисх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
} : links { v.<DETAILS>attr }


// Николай, мне жаль его!
pattern ГлБезличНисх
{
 x=ПрямоеОбращение
 v=ГлБезличНисх : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
} : links { v.<APPEAL>x }


// Сразу на душе стало легче.
//       ^^^^^^^^^^^^^
pattern ГлБезличНисх
{
 pn=ПредлогИСущ
 v=ГлБезличНисх { гл_предл(_,pn.prepos,pn.n2) } : export { node:root_node ТИП_ПРЕДИКАТИВ ПЕРЕХОДНОСТЬ ПАДЕЖ THEMA_VALENCY }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score( v, pn.prepos )
 ngram3( v, pn.prepos, pn.n2 )
}


// Мне вас жаль!
//     ^^^
pattern ГлБезличНисх
{
 obj=ГлДополнение
 v=ГлБезличНисх { ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =Obj:ПАДЕЖ }
     : export { 
               node:root_node
               ТИП_ПРЕДИКАТИВ
               THEMA_VALENCY
               @except(ПАДЕЖ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score( v, obj ) }


// -------------------------------------------

pattern ГлПредикат
{
 v=ГлБезличНисх : export { node:root_node }
} : ngrams { ВалентностьГлагола(v) }

