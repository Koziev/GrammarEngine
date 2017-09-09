// ***********************
// ИНФИНИТИВЫ
// ***********************

#define _запятая ','



pattern Инф0
{
 инфинитив:*{}:export { ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
}

// заставить же ее было невозможно
// ^^^^^^^^^^^^
pattern Инф0
{
 i=инфинитив:*{}:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 p=частица:же{}
} : links { i.<POSTFIX_PARTICLE>p }
: ngrams { 1 }



// С  кем  судиться-то?
//         ^^^^^^^^^^^
pattern Инф0
{
 i=инфинитив:*{}:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 t='-'
 p=частица:то{}
}
: links { i.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>p }
: ngrams { 1 }



// послать ли моих волков?
// ^^^^^^^^^^
pattern Инф0
{
 i=инфинитив:*{}:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 p=частица:ли{}
}
: links { i.<POSTFIX_PARTICLE>p }
: ngrams { 1 }


// выпить бы сейчас
// ^^^^^^^^^
pattern Инф0
{
 i=инфинитив:*{}:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 p=частица:бы{}
}
: links { i.<POSTFIX_PARTICLE>p }
: ngrams { 1 }

pattern Инф0
{
 n=частица:не{}
 inf=инфинитив:*{}:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
} : links { inf.<NEGATION_PARTICLE>n }


// Смена прямой винительной валентности при отрицании:
// за деревьями леса не видеть
pattern Инф0 export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД (МОДАЛЬНЫЙ) node:root_node }
{
 n=частица:не{}
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД @add(ПАДЕЖ:РОД) node:root_node }
} : links { inf.<NEGATION_PARTICLE>n }


// я могу и не продать его.
//        ^^^^^^^^^^^^
// Лучшего места и не придумать.
//               ^^^^^^^^^^^^^^
pattern Инф0 export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД (МОДАЛЬНЫЙ) node:root_node }
{
 p=частица:и{}
 inf=Инф0:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
}
: links { inf.<PREFIX_PARTICLE>p }
: ngrams { -1 }


// Не опоздать бы
pattern Инф0
{
 n=частица:не{}
 inf=инфинитив:*{}:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 x=частица:бы{}
} : links
{
 inf.{
      <NEGATION_PARTICLE>n
      <POSTFIX_PARTICLE>x
     }
}

// А не спросить ли  его о картине?
//   ^^^^^^^^^^^^^^
pattern Инф0
{
 n=частица:не{}
 inf=инфинитив:*{}:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 x=частица:ли{}
} : links
{
 inf.{
      <NEGATION_PARTICLE>n
      <POSTFIX_PARTICLE>x
     }
}


pattern Инф0
{
 n=частица:не{}
 inf=инфинитив:*{}:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 x=частица:же{}
} : links
{
 inf.{
      <NEGATION_PARTICLE>n
      <POSTFIX_PARTICLE>x
     }
}



// Регулировать или нет цены на российский газ в Литве?
// ^^^^^^^^^^^^^^^^^^^^
pattern Инф0
{
 inf=инфинитив:*{}:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 conj=союз:или{}
 n=частица:нет{}
} : links
{
 inf.<RIGHT_LOGIC_ITEM>conj.<NEGATION_PARTICLE>n
}
: ngrams { -2 }


// Куда хочет "вернуться" Япония?
//            ^^^^^^^^^^^
pattern Инф0
{
 q1=ОткрывающаяКавычка
 v=Инф0:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 q2=ЗакрывающаяКавычка
} : links
{
 v.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}


pattern Инф0
{
 p=частица:*{}
 i=Инф0:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
}
: links { i.<PREFIX_PARTICLE>p }
: ngrams { -10 }


pattern Инф0
{
 i=инфинитив:*{}:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 attr=Детализатор
} : links { i.<DETAILS>attr }
: ngrams { -20 }



// Так она же и знать не будет!
//            ^^^^^^^
pattern Инф0
{
 p=частица:и{}
 i=инфинитив:*{}:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
} : links { i.<PREFIX_PARTICLE>p }
: ngrams { -5 }


// =================================================================

// ее нужно научить дышать
pattern Инф
{
 v=Инф0{ МОДАЛЬНЫЙ }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 inf=Инф2
} : links
{
 v.<INFINITIVE>inf
}
: ngrams
{
 -1
 v_inf_score( v, inf )
}


pattern Инф
{
 v=Инф0{ ~МОДАЛЬНЫЙ }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 inf=Инф2
} : links
{
 v.<INFINITIVE>inf
}
: ngrams
{
 -10
 v_inf_score( v, inf )
}




// Оба явления должны были быть хорошо заметны
//                         ^^^^^^^^^^^^^^^^^^^
pattern Инф
{
 inf=инфинитив:быть{}:export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ПАДЕЖ ВИД node:root_node }
 adj=КраткПрил2
} : links { inf.<ATTRIBUTE>adj }
: ngrams
{
 ВалентностьГлагола(inf)
}


// быть опасно больным
pattern Инф
{
 inf=инфинитив:быть{}:export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ПАДЕЖ ВИД node:root_node }
 adj=ГруппаПрил2{ ПАДЕЖ:ТВОР ~CanAdjModifByAdv }
} : links
{
 inf.<ATTRIBUTE>adj
}
: ngrams
{
 1
 ВалентностьГлагола(inf)
}

// время посадки должно быть строго согласовано с местными климатическими условиями
pattern Инф
{
 inf=инфинитив:быть{}:export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ПАДЕЖ ВИД node:root_node }
 adj=СтрадПрич
} : links
{
 inf.<RIGHT_AUX2PARTICIPLE>adj
}
: ngrams { 1 }

// ему должно быть стыдно
pattern Инф
{
 inf=инфинитив:быть{}:export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ПАДЕЖ ВИД node:root_node }
 adv=ГруппаНареч2
} : links
{
 inf.<ATTRIBUTE>adv
}
: ngrams
{
 1
 adv_verb_score( adv, inf )
 ВалентностьГлагола(inf)
}

// она должна быть сразу за углом
pattern Инф
{
 inf=инфинитив:быть{}:export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ПАДЕЖ ВИД node:root_node }
 adv=ГруппаНареч2
 pn=ПредлогИСущ
} : links
{
 inf.{
      <ATTRIBUTE>adv
      <PREPOS_ADJUNCT>pn
     }
}
: ngrams
{
 adv_verb_score( adv, inf )
 ngram3( inf, pn.prepos, pn.n2 )
 prepos_score( inf, pn.prepos )
 ВалентностьГлагола(inf)
}


// ты должен приехать первым
pattern Инф export{ ПЕРЕХОДНОСТЬ (ПАДЕЖ) ВИД node:root_node }
{
 v=Инф0 : export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ВИД node:root_node }
 obj=ПорядкЧислКакОбст{ =V:ЧИСЛО }
} : links { v.<OBJECT>obj }


// она должна закончить работу третьей
pattern Инф export{ ПЕРЕХОДНОСТЬ (ПАДЕЖ) ВИД node:root_node }
{
 v=Инф0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН } : export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ВИД node:root_node }
 obj1=ВинОбъект
 obj2=ПорядкЧислКакОбст{ =V:ЧИСЛО }
} : links
{
 v.{
    <OBJECT>obj1
    <OBJECT>obj2
   }
}


// притворяться спящим
pattern Инф
{
 v=Инф0{ ПритворитьсяТакимтоГл } : export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 obj=ГруппаПрил2{ ПАДЕЖ:ТВОР =V:ЧИСЛО }
} : links { v.<OBJECT>obj }
: ngrams
{
 ВалентностьГлагола(v)
}


// ???
// разговор должен получиться интересный
//                 ^^^^^^^^^^^^^^^^^^^^^
pattern Инф
{
 adv=@optional(ГруппаНареч2)
 v=инфинитив:получиться{} : export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 obj=ГруппаПрил2{ ПАДЕЖ:ИМ =V:ЧИСЛО }
} : links
{
 v.{
    ~<ATTRIBUTE>adv
    <ATTRIBUTE>obj
   }
}
: ngrams
{
 adv_verb_score( adv, v )
 ВалентностьГлагола(v)
}


// приходится держать ставни закрытыми.
pattern Инф
{
 v=Инф0{ ПритворитьсяТакимтоГл ПАДЕЖ:ВИН } : export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 obj1=ВинОбъект
 obj2=ГруппаПрил2{ ПАДЕЖ:ТВОР =obj1:ЧИСЛО =obj1:РОД }
}
: links
{
 v.{
    <OBJECT>obj1
    <OBJECT>obj2
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}


// он должен показаться тебе странным
pattern Инф
{
 v=Инф0{ ПритворитьсяТакимтоГл ПАДЕЖ:ДАТ } : export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 obj1=ДатОбъект
 obj2=ГруппаПрил2{ ПАДЕЖ:ТВОР =V:ЧИСЛО }
}
: links
{
 v.{
    <OBJECT>obj1
    <OBJECT>obj2
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}


// Предложное дополнение с именительным падежом для именной части:
// выдвигать в кандидаты
pattern Инф
{
 v=Инф0{ ГлагСДопВИмП } : export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 prep=предлог:в{}
 obj=ГруппаСущ4{ ПАДЕЖ:ИМ ОДУШ:ОДУШ }
} : links { v.<PREPOS_ADJUNCT>prep.<OBJECT>obj }
: ngrams
{
 ngram3(v,prep,obj)
 ВалентностьГлагола(v)
}


// посвящать кого-либо в рыцари
pattern Инф
{
 v=Инф0{ ГлагСДопВИмП ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН } : export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 n=ВинОбъект
 prep=предлог:в{}
 obj=ГруппаСущ4{ ПАДЕЖ:ИМ ОДУШ:ОДУШ }
} : links
{
 v.{
    <OBJECT>n
    <PREPOS_ADJUNCT>prep.<OBJECT>obj
   }
}
: ngrams
{
 v_obj_score( v, n )
 ngram3( v, prep, obj )
 ВалентностьГлагола(v)
}



// ???
// стать сильнее тебя
pattern Инф
{
 adv=@optional(Обст)
 v=инфинитив:*{ Выглядеть_ПРИЛ } : export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 obj=ГруппаСравнПрил
} : links
{
 v.{
    ~<ATTRIBUTE>adv 
    <ATTRIBUTE>obj
   }
}
: ngrams
{
 adv_verb_score( adv, v )
 ВалентностьГлагола(v)
}






// притвориться больным
wordentry_set ПритворитьсяТакимтоИнф =
{
 инфинитив:притвориться{},
 инфинитив:притворяться{},
 инфинитив:становиться{},
 инфинитив:стать{}
}

pattern Инф
{
 adv=@optional(ГруппаНареч2)
 v=ПритворитьсяТакимтоИнф:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 obj=ГлДопПрил
} : links
{
 v.{
    ~<ATTRIBUTE>adv 
    <OBJECT>obj
   }
}
: ngrams
{
 adv_verb_score( adv, v )
 ВалентностьГлагола(v)
}



// ничего не делать
pattern Инф export{ ПЕРЕХОДНОСТЬ (ПАДЕЖ) ВИД node:root_node }
{
 obj='ничего'{ class:местоим_сущ }
 n=частица:не{}
 inf=инфинитив:*{ переходность:переходный падеж:вин } : export { ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ВИД node:root_node }
} : links
{
 inf.{
      <NEGATION_PARTICLE>n
      <OBJECT>obj
     }
}
: ngrams
{
 ВалентностьГлагола(inf)
}


// заставить бежать своих преследователей
pattern Инф export { ПЕРЕХОДНОСТЬ (ПАДЕЖ) (ВИД) node:root_node  }
{
 mod=инфинитив:*{ МОДАЛЬНЫЙ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ }:export { node:root_node ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
 inf=Инф2
 obj=ГлОбъект{ =mod:ПАДЕЖ }
} : links
{
 mod.{
      <INFINITIVE>inf
      <OBJECT>obj
     }
}
: ngrams
{
 -1
 ВалентностьГлагола(mod)
}


// надо учить ее плавать
pattern Инф export { ПЕРЕХОДНОСТЬ (ПАДЕЖ) ВИД node:root_node  }
{
 mod=инфинитив:*{ МОДАЛЬНЫЙ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export { ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ВИД node:root_node }
 obj=ВинОбъект
 inf=Инф2
} : links
{
 mod.{
      <OBJECT>obj
      <INFINITIVE>inf
     }
}
: ngrams
{
 ВалентностьГлагола(mod)
}


// тебе придется заставить их съесть собственную шляпу.
//               ^^^^^^^^^^^^^^^^^^^....
// приказывать секретарше принести кофе
pattern Инф export { ПЕРЕХОДНОСТЬ (ПАДЕЖ) (ВИД) node:root_node  }
{
 mod=инфинитив:*{ МОДАЛЬНЫЙ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ДАТ }:export { node:root_node }
 obj=ДатОбъект
 inf=Инф2:export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
} : links {
 mod.{
      <OBJECT>obj
      <INFINITIVE>inf
     }
}
: ngrams
{
 v_obj_score( mod, obj )
 v_inf_score( mod, inf )
 ВалентностьГлагола(inf)
}




// не решаться есть суп
pattern Инф export { ПЕРЕХОДНОСТЬ (ПАДЕЖ) (ВИД) node:root_node  }
{
 n=частица:не{}
 mod=инфинитив:*{ МОДАЛЬНЫЙ }:export { node:root_node }
 inf=Инф2:export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
} : links
{
 mod.{
      <NEGATION_PARTICLE>n
      <INFINITIVE>inf
     }
}


// отрицание модального глагола меняет валентность инфинитива:
// Ни одна из предложенных на сегодняшний день моделей не может воспроизвести разнообразия ответных реакций и функций.
//                                                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
// Для упрощения разбора разрешим присоединять родительное дополнение
// с некоторым штрафом.
pattern Инф export{ ПЕРЕХОДНОСТЬ (ПАДЕЖ) ВИД node:root_node }
{
 v=Инф0{ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ВИД node:root_node }
 obj=РодОбъект
} : links
{
 v.{
    <OBJECT>obj
   }
}
: ngrams
{
 -4
 v_obj_score(v.root_node,obj.root_node)
 ВалентностьГлагола(v)
}


// ты должен мне помочь его осуществить
pattern Инф
{
 obj=ДатОбъект
 adv1=@optional(ГруппаНареч2)
 v=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ДАТ МОДАЛЬНЫЙ }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 inf=Инф2
} : links
{
 v.{
    <OBJECT>obj
    ~<ATTRIBUTE>adv1
    <INFINITIVE>inf
   }
}
: ngrams
{
 v_obj_score(v,obj)
 v_inf_score(v,inf)
 adv_verb_score( adv1, v )
 ВалентностьГлагола(v)
}


// --------------------------------------------------------------------
// Далее идут правила для разбора регулярных конструкций с инфинитивом.
// --------------------------------------------------------------------

patterns ИнфВосх { bottomup  } export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ }

pattern ИнфВосх
{
 Инф0 : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ }
}




pattern ИнфВосх
{
 v=ИнфВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ } : export { node:root_node ВИД МОДАЛЬНЫЙ }
 obj=ГлОбъект{ =v:ПАДЕЖ } : export {
                                         @except(v:ПАДЕЖ,ПАДЕЖ)
                                         @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
                                        }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }


// Нарушенная валентность
pattern ИнфВосх
{
 v=ИнфВосх : export { node:root_node ВИД МОДАЛЬНЫЙ }
 obj=ГлОбъект : export {
                                         @except(v:ПАДЕЖ,ПАДЕЖ)
                                         @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
                                        }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -10
 v_obj_score(v,obj)
}




// Присоединение обращения к инфинитиву тут сильно штрафуем, так
// как обычно (но не всегда) это обращение возникает при использовании
// инфинитива как полного предложения со значением "НУЖНО":
//
// - Приготовить чай, мамочка?
pattern ИнфВосх
{
 v=ИнфВосх : export { node:root_node ВИД МОДАЛЬНЫЙ ПЕРЕХОДНОСТЬ ПАДЕЖ }
 x=ПрямоеОбращение
}
: links { v.<APPEAL>x }
: ngrams { -5 }


pattern ИнфВосх
{
 v=ИнфВосх : export { node:root_node ВИД МОДАЛЬНЫЙ ПЕРЕХОДНОСТЬ ПАДЕЖ }
 sbj=Подлежащее
}
: links { v.<SUBJECT>sbj }
: ngrams
{
 -14
 sbj_v_score( sbj, v )
}


/*
// Несогласованная речь: присоединяем справа объект, для которого
// у глагола нет свободного слота:
//
// я любить вишня
//   ^^^^^^^^^^^^ 
pattern ИнфВосх
{
 v=ИнфВосх : export { node:root_node ВИД МОДАЛЬНЫЙ }
 obj=ГлОбъект{ !=v:ПАДЕЖ } : export {
                                     @except(v:ПАДЕЖ,ПАДЕЖ)
                                     @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
                                    }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -10
 v_obj_score(v,obj)
}
*/

// дательное дополнение+предложное премыкание НА/В+предл:
//
// сесть на спину второму
// ^^^^^          ^^^^^^^
pattern ИнфВосх
{
 v=ИнфВосх{ ~ПАДЕЖ:ДАТ } : export { node:root_node ВИД МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ }
 obj=ДатОбъект
}
: links { v.<OBJECT>obj }
: ngrams
{
 -9
 v_obj_score(v,obj)
}




pattern ИнфВосх
{
 v=ИнфВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ }
 adv=Обст
} : links
{
 v.<ATTRIBUTE>adv
}
: ngrams
{
 adv_verb_score( adv, v )
}

// +++++++++++

// Бессоюзное правое придаточное:
// разобрать, что бормотал лектор
pattern ИнфВосх export{ ПЕРЕХОДНОСТЬ ВИД (МОДАЛЬНЫЙ) (ПАДЕЖ) node:root_node }
{
 v=ИнфВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН } : export { node:root_node ВИД ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
 p=БессоюзноеПридаточное
}
: links { v.<SUBORDINATE_CLAUSE>p }
: ngrams
{
 -1
 ВалентностьБессоюзнПридаточн(v)
}


// я хочу понять, почему кошка сильнее собаки
pattern ИнфВосх
{
 inf=ИнфВосх:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 comma=','
 conj=СоединДляПридаточного
 p=ПридаточноеВОбороте
 comma2=@coalesce(',')
} : links
{
 inf.<SUBORDINATE_CLAUSE>comma.
      <NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>p.~<PUNCTUATION>comma2
}
: ngrams { 1 }

// +++



pattern ИнфВосх export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД (МОДАЛЬНЫЙ) }
{
 v=ИнфВосх{ МОДАЛЬНЫЙ } : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД }
 inf=Инф2
}
: links { v.<INFINITIVE>inf }
: ngrams { v_inf_score( v, inf ) }




pattern ИнфВосх
{
 v=ИнфВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ }
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


// Висящий одиночный предлог
pattern ИнфВосх
{
 v=ИнфВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ }
 p=предлог:*{}
} : links { v.<ATTRIBUTE>p }
: ngrams { -6 }



pattern ИнфВосх
{
 v=ИнфВосх : export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ node:root_node }
 q2=ЗакрывающаяКавычка
}
: links { v.<APPEND_QUOTE>q2 }
: ngrams { -1 }



// Петь мне, что ли?
//         ^^^^^^^^
pattern ИнфВосх
{
 v=ИнфВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД МОДАЛЬНЫЙ }
 attr=ВводнАктант
} : links
{
 v.<BEG_INTRO>attr
}



// --------------------------------------------------------

patterns ИнфНисх export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД }

pattern ИнфНисх
{
 ИнфВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД }
}

pattern ИнфНисх
{
 adv=Обст
 v=ИнфНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД }
} 
: links
{
 v.<ATTRIBUTE>adv
}
: ngrams
{
 adv_verb_score( adv, v )
}


pattern ИнфНисх
{
 pn=ПредлогИСущ
 v=ИнфНисх { гл_предл(_,pn.prepos,pn.n2) } : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД }
} 
: links
{
 v.<PREPOS_ADJUNCT>pn
}
: ngrams
{
 -1
 prepos_score( v, pn.prepos )
 ngram3( v, pn.prepos, pn.n2 )
}



pattern ИнфНисх
{
 obj=ГлОбъект
 v=ИнфНисх { ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =Obj:ПАДЕЖ }
     : export { 
               node:root_node ВИД
               @except(ПАДЕЖ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
} : links { v.<OBJECT>obj }
: ngrams
{
 -1
 v_obj_score( v, obj )
}

// Прямое дополнение в родительном падеже может заполнять винительный слот глагола:
// Ничего определенного вспомнить не удалось.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ИнфНисх
{
 obj=ГлОбъект{ ПАДЕЖ:РОД }
 v=ИнфНисх { ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }
     : export { 
               node:root_node ВИД
               ПАДЕЖ @remove(ПАДЕЖ:ВИН)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -2
 v_obj_score( v, obj )
}


// Присоединение несогласованного объекта
pattern ИнфНисх
{
 obj=ГлОбъект
 v=ИнфНисх { !=Obj:ПАДЕЖ }
     : export { 
               node:root_node ВИД
               @except(ПАДЕЖ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
} : links { v.<OBJECT>obj }
: ngrams
{
 -11
 v_obj_score( v, obj )
}



// Присоединение обращения к инфинитиву тут сильно штрафуем, так
// как обычно (но не всегда) это обращение возникает при использовании
// инфинитива как полного предложения со значением "НУЖНО":
//
// Господа, немедленно покинуть помещение!
pattern ИнфНисх
{
 x=ПрямоеОбращение
 v=ИнфНисх : export { node:root_node ВИД ПАДЕЖ ПЕРЕХОДНОСТЬ }
}
: links { v.<APPEAL>x }
: ngrams { -5 }



// Несогласованная речь:
//
// Я работать хорошо!
pattern ИнфНисх
{
 sbj=Подлежащее
 v=ИнфНисх : export { node:root_node ВИД ПАДЕЖ ПЕРЕХОДНОСТЬ }
}
: links { v.<SUBJECT>sbj }
: ngrams
{
 -10
 sbj_v_score( sbj, v )
}




// Объект в дательном падеже прикрепляется даже в случаях, когда
// у глагола нет нужной валентности:
//
// на спину дракону сесть
//          ^^^^^^^
// Глазу зацепиться не за что.
// ^^^^^
pattern ИнфНисх
{
 obj=ДатОбъект
 v=ИнфНисх { ~ПАДЕЖ:ДАТ } : export { node:root_node ВИД ПАДЕЖ ПЕРЕХОДНОСТЬ }
}
: links { v.<OBJECT>obj }
: ngrams { -5 }


pattern ИнфНисх
{
 q1=ОткрывающаяКавычка
 v=ИнфНисх : export { node:root_node ВИД ПАДЕЖ ПЕРЕХОДНОСТЬ }
}
: links { v.<PREPEND_QUOTE>q1 }
: ngrams { -1 }



// к чему, однако, ломать голову?
//       ^^^^^^^^^
pattern ИнфНисх
{
 attr=ВводнАктант
 v=ИнфНисх : export { node:root_node ВИД ПАДЕЖ ПЕРЕХОДНОСТЬ }
}
: links { v.<BEG_INTRO>attr }



// -------------------------------------------

pattern Инф
{
 v=ИнфНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД }
}
: ngrams
{
 ВалентностьГлагола(v)
}


// ===============================================================================
// Винительная падежность остается свободной:

pattern ИнфВин
{
 Инф0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
}

pattern ИнфВин
{
 adv=Обст
 v=Инф0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
} : links
{ v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score(adv.root_node,v.root_node) }


// его нужно будет взять живым.
//                 ^^^^^ ^^^^^
pattern ИнфВин
{
 adv=@optional(Обст)
 v=Инф0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ВИД node:root_node }
 obj=ТворОбъект
} : links
{
 v.{
    ~<ATTRIBUTE>adv
    <OBJECT>obj
   }
}
: ngrams { v_obj_score(v.root_node,obj.root_node) }


// Книгу надо вернуть в библиотеку
//            ^^^^^^^^^^^^^^^^^^^^
pattern ИнфВин
{
 v=Инф0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 adv=ПредлогИСущ{ гл_предл( v.root_node, _.prepos, _.n2 ) }
} : links { v.<PREPOS_ADJUNCT>adv }
: ngrams
{
 ngram3( v.root_node, adv.prepos, adv.n2 )
}

// меня можно только защищать до смерти
pattern ИнфВин
{
 adv=Обст
 v=Инф0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 pn=ПредлогИСущ{ гл_предл( v.root_node, _.prepos, _.n2 ) }
} : links
{
 v.{
    <ATTRIBUTE>adv
    <PREPOS_ADJUNCT>pn
   }
}
: ngrams
{
 ngram3( v.root_node, adv.prepos, adv.n2 )
}



// чужаков положено убивать сразу.
pattern ИнфВин
{
 v=Инф0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 adv=Обст
} : links { v.<PREPOS_ADJUNCT>adv }
: ngrams
{
 adv_verb_score( adv, v )
}


// Эту работу надо обязательно сделать сегодня.
pattern ИнфВин
{
 adv1=Обст
 v=Инф0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 adv2=Обст
} : links
{
 v.{
    <PREPOS_ADJUNCT>adv1
    <PREPOS_ADJUNCT>adv2
   }
}
: ngrams
{
 adv_verb_score( adv1, v )
 adv_verb_score( adv2, v )
}





// ==============================================================


// с деепричастным оборотом

pattern ИнфСДеепричОбор { Инф:export { node:root_node } }

// ------------------------------------------------------------

// ###################################
// Союзные паттерны с инфинитивами
// ###################################

patterns Инф2_Хвост export { node:root_node }
pattern Инф2_Хвост
{
 Инф : export { node:root_node }
}


patterns Инф2Восх { bottomup } export { node:root_node }


pattern Инф2Восх
{
 Инф : export { node:root_node }
}

// мы начали двигаться и подниматься
//           ^^^^^^^^^^^^^^^^^^^^^^^
pattern Инф2Восх
{
 v1=Инф2Восх:export { node:root_node }
 conj=ЛогичСоюз
 v2=Инф2_Хвост
} : links
{ v1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// если не писать, так читать
pattern Инф2Восх
{
 conj1=ЕслиСоедГолова
 v1=Инф2Восх:export { node:root_node }
 comma=','
 conj2=ЕслиСоедХвост
 v2=Инф2_Хвост
} : links
{ v1.{
      <PREFIX_CONJUNCTION>conj1
      <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>conj2.
        <NEXT_COLLOCATION_ITEM>v2
     }
}

// Если не съесть, тогда понадкусать
pattern Инф2Восх
{
 conj1=ЕслиСоедГолова
 v1=Инф2Восх:export { node:root_node }
 comma=','
 v2=Инф2_Хвост
} : links
{ v1.{
      <PREFIX_CONJUNCTION>conj1
      <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>v2
     }
}



// Перестановки должны внести струю, ускорить развитие
//                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern Инф2Восх
{
 v1=Инф2Восх:export { node:root_node }
 comma=','
 v2=Инф2_Хвост
} : links
{ v1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }


// создавать внутри своей вселенной пузыри, а затем творить миры.
//                                        ^^^^^^^^^
pattern Инф2Восх
{
 v1=Инф2Восх:export { node:root_node }
 comma=','
 conj=ЛогичСоюз
 v2=Инф2_Хвост
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2
}

pattern Инф2Восх
{
 v1=Инф2Восх:export { node:root_node }
 comma=','
 conj=ПротивитСоюз
 v2=Инф2_Хвост
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2
}



// Пропущена запятая:
// Вам же надо и грести и смотреть...
//             ^^^^^^^^^^^^^^^^^^^
pattern Инф2Восх
{
 conj1=ЛогичСоюз2
 v1=Инф2Восх:export { node:root_node }
 conj2=ЛогичСоюз2
 v2=Инф2_Хвост
} : links
{
 v1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>conj2.
      <NEXT_COLLOCATION_ITEM>v2
    }
}
: ngrams { -1 }




// они хотят петь, плясать и т.д.
//           ^^^^^^^^^^^^^^^^^^^^
pattern Инф2Восх
{
 inf=Инф2Восх:export { node:root_node }
 etc=ЗамыкательПеречисления
} : links { inf.<NEXT_COLLOCATION_ITEM>etc }


/*
// не только спастись от плена, но и заставить бежать своих преследователей
pattern Инф2
{
 v1=Инф:export { node:root_node }
 comma=','
 conj=союз:но{}
 conj2=союз:и{}
 v2=Инф
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>v2
}
*/

/*
// Перестановки должны внести струю , ускорить развитие
pattern Инф2
{
 v1=Инф:export { node:root_node }
 comma1=_запятая
 v2=Инф
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma1.
     <NEXT_COLLOCATION_ITEM>v2
}
*/


/*
// мы собираемся добыть, сохранить, собрать воедино россыпи народного искусства
pattern Инф2
{
 v1=Инф:export { node:root_node }
 comma1=_запятая
 v2=Инф
 comma2=_запятая
 v3=Инф
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma1.
     <NEXT_COLLOCATION_ITEM>v2.
      <RIGHT_LOGIC_ITEM>comma2.
       <NEXT_COLLOCATION_ITEM>v3
}

// гости будут пить кофе, кушать торт и беззаботно болтать про нашу жизнь
pattern Инф2
{
 v1=Инф:export { node:root_node }
 comma=_запятая
 v2=Инф
 conj=ЛогичСоюз
 v3=Инф
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>v2.
      <RIGHT_LOGIC_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>v3
}
*/

/*
// я буду сначала петь песни, затем танцевать вальс
pattern Инф2
{
 adv1='сначала'
 v1=Инф:export { node:root_node }
 comma=_запятая
 adv2='затем'
 v2=Инф
} : links
{
 v1.{
     <ATTRIBUTE>adv1
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>v2.
       <ATTRIBUTE>adv2
    }
}
*/

/*
// девушки хотят или петь песни, или немного потанцевать
pattern Инф2
{
 conj1=ЛогичСоюз
 v1=Инф:export { node:root_node }
 comma=_запятая
 conj2=ЛогичСоюз
 v2=Инф
} : links
{
 v1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>v2
    }
}
*/

/*
// мы не могли бы ни пить, ни дышать.
//                ^^^^^^^^^^^^^^^^^^
pattern Инф2
{
 conj1=союз:ни{}
 v1=Инф:export { node:root_node }
 comma=_запятая
 conj2=союз:ни{}
 v2=Инф
} : links
{
 v1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>v2
    }
}
*/


/*
// коллеги планируют не терять время на подготовку, а сразу начать работать
pattern Инф2
{
 n=частица:не{}
 v1=Инф:export { node:root_node }
 comma=_запятая
 conj=союз:а{}
 v2=Инф
} : links
{
 v1.{
     <NEGATION_PARTICLE>n
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>v2
    }
}
*/

/*
// для модальных
// начать есть суп
// начать есть суп и пить кофе
pattern Инф export { ПЕРЕХОДНОСТЬ (ПАДЕЖ) (ВИД) node:root_node  }
{
 mod=инфинитив:*{ МОДАЛЬНЫЙ }:export { node:root_node ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
 inf=Инф2
} : links
{
 mod.<INFINITIVE>inf
}
: ngrams
{
 ВалентностьГлагола(mod)
}
*/


pattern Инф2
{
 Инф2Восх:export { node:root_node }
}



// Ни есть, ни пить.
pattern Инф2
{
 conj1=ЛогичСоюз2
 v1=Инф2:export { node:root_node }
 comma=','
 conj2=ЛогичСоюз2
 v2=Инф2
} : links
{
 v1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>v2
    }
}


// девушки хотят или петь песни, или немного потанцевать
//               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern Инф2
{
 conj1=СочинительныйСоюз1
 v1=Инф2:export { node:root_node }
 comma=_запятая
 conj2=СочинительныйСоюз2
 v2=Инф2
} : links
{
 v1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>v2
    }
}


// ---------------------------------------------------------------------
// для паттернов с будущим временем через вспомогательный глагол БЫТЬ
// ---------------------------------------------------------------------

pattern НесовершИнф2
{
 Инф{ВИД:НЕСОВЕРШ}:export { node:root_node }
}

// мы будем продолжать служить нашему народу
pattern НесовершИнф2
{
 inf=инфинитив:*{ ВИД:НЕСОВЕРШ МОДАЛЬНЫЙ }:export { node:root_node }
 inf2=Инф2
} : links { inf.<INFINITIVE>inf2 }

// будем учить ее плавать
//       ^^^^^^^^^^^^^^^^
pattern НесовершИнф2
{
 mod=инфинитив:*{ ВИД:НЕСОВЕРШ МОДАЛЬНЫЙ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export { node:root_node }
 obj=ВинОбъект
 inf=Инф2
} : links
{
 mod.{
      <OBJECT>obj
      <INFINITIVE>inf
     }
}


// ---------------------------------------------------



/*
// я буду петь частушки и танцевать вальс
pattern НесовершИнф2
{
 v1=Инф{ВИД:НЕСОВЕРШ}:export { node:root_node }
 conj=ЛогичСоюз
 v2=Инф{ВИД:НЕСОВЕРШ}
} : links { v1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// я буду сначала петь частушки, затем танцевать вальс
pattern НесовершИнф2
{
 adv1='сначала'
 v1=Инф{ВИД:НЕСОВЕРШ}:export { node:root_node }
 comma=_запятая
 adv2='затем'
 v2=Инф{ВИД:НЕСОВЕРШ}
} : links
{
 v1.{
     <ATTRIBUTE>adv1
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>v2.
       <ATTRIBUTE>adv2
    }
}

// гости будут пить кофе, есть торт и болтать про жизнь
pattern НесовершИнф2
{
 v1=Инф{ВИД:НЕСОВЕРШ}:export { node:root_node }
 comma=_запятая
 v2=Инф{ВИД:НЕСОВЕРШ}
 conj=ЛогичСоюз
 v3=Инф{ВИД:НЕСОВЕРШ}
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>v2.
      <RIGHT_LOGIC_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>v3
}
*/


patterns НесовершИнф2_Хвост export { node:root_node }
pattern НесовершИнф2_Хвост
{
 Инф{ВИД:НЕСОВЕРШ} : export { node:root_node }
}


patterns НесовершИнф2Восх { bottomup } export { node:root_node }


pattern НесовершИнф2Восх
{
 Инф{ВИД:НЕСОВЕРШ} : export { node:root_node }
}

// они будут петь, плясать и т.д.
//           ^^^^^^^^^^^^^^^^^^^^
pattern НесовершИнф2Восх
{
 inf=НесовершИнф2Восх:export { node:root_node }
 etc=ЗамыкательПеречисления
} : links { inf.<NEXT_COLLOCATION_ITEM>etc }

// мы будем подниматься и спускаться
//          ^^^^^^^^^^^^^^^^^^^^^^^^
pattern НесовершИнф2Восх
{
 v1=НесовершИнф2Восх:export { node:root_node }
 conj=ЛогичСоюз
 v2=НесовершИнф2_Хвост
} : links
{ v1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// Перестановки будут вносить свежую струю, ускорять развитие
//                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern НесовершИнф2Восх
{
 v1=НесовершИнф2Восх:export { node:root_node }
 comma=','
 v2=НесовершИнф2_Хвост
} : links
{ v1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }


// будем создавать внутри своей вселенной пузыри, а затем творить миры.
//                                              ^^^^^^^^^
pattern НесовершИнф2Восх
{
 v1=НесовершИнф2Восх:export { node:root_node }
 comma=','
 conj=ЛогичСоюз
 v2=НесовершИнф2_Хвост
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2
}

pattern НесовершИнф2Восх
{
 v1=НесовершИнф2Восх:export { node:root_node }
 comma=','
 conj=ПротивитСоюз
 v2=НесовершИнф2_Хвост
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2
}

// девушки будут или петь песни, или немного потанцевать
pattern НесовершИнф2Восх
{
 conj1=СочинительныйСоюз1
 v1=НесовершИнф2Восх:export { node:root_node }
 comma=_запятая
 conj2=СочинительныйСоюз2
 v2=НесовершИнф2_Хвост
} : links
{
 v1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>v2
    }
}


// Пропущена запятая:
// Вам же надо и грести и смотреть...
//             ^^^^^^^^^^^^^^^^^^^
pattern НесовершИнф2Восх
{
 conj1=ЛогичСоюз2
 v1=НесовершИнф2Восх:export { node:root_node }
 conj2=ЛогичСоюз2
 v2=НесовершИнф2_Хвост
} : links
{
 v1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>conj2.
      <NEXT_COLLOCATION_ITEM>v2
    }
}
: ngrams { -1 }



pattern НесовершИнф2
{
 НесовершИнф2Восх:export { node:root_node }
}

// -----------------------------------------------------


// кошки своими шершавыми языками будут меня лизать
pattern ИнфСВинДоп
{
 obj=ВинОбъект
 v=Инф0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
} : links
{
 v.{
    <OBJECT>obj
   }
}


// ==============================================================


/*
// его успели выкинуть
//            ^^^^^^^^
pattern Инф2БезДоп
{
 Инф:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
}


// TODO: после переделки на восходящий парсинг убрать
pattern Инф2БезДоп
{
 v1=Инф:export{ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 conj=ЛогичСоюз
 v2=Инф
}
: links { v1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }
*/



patterns Инф2БезДоп_Хвост export { ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
pattern Инф2БезДоп_Хвост
{
 Инф : export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
}


patterns Инф2БезДопВосх { bottomup } export { ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }

// Я буду контролировать тебя
//        ^^^^^^^^^^^^^^^^^^^
pattern Инф2БезДопВосх
{
 Инф : export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
}


// они будут петь, плясать и т.д.
//           ^^^^^^^^^^^^^^^^^^^^
pattern Инф2БезДопВосх
{
 inf=Инф2БезДопВосх : export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 etc=ЗамыкательПеречисления
} : links { inf.<NEXT_COLLOCATION_ITEM>etc }



// Мы будем петь и плясать
//          ^^^^^^^^^^^^^^
pattern Инф2БезДопВосх
{
 v1=Инф2БезДопВосх:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 conj=ЛогичСоюз
 v2=Инф2БезДоп_Хвост
} : links
{ v1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// Перестановки будут вносить свежую струю, ускорять развитие
//                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern Инф2БезДопВосх
{
 v1=Инф2БезДопВосх:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 comma=','
 v2=Инф2БезДоп_Хвост
} : links
{ v1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }


// Мы будем создавать внутри своей вселенной пузыри, а затем творить миры.
//          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   
pattern Инф2БезДопВосх
{
 v1=Инф2БезДопВосх:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 comma=','
 conj=ЛогичСоюз
 v2=Инф2БезДоп_Хвост
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2
}

// Мы будем не только петь песни, но и танцевать зажигательные танцы
//          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern Инф2БезДопВосх
{
 v1=Инф2БезДопВосх:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 comma=','
 conj=ПротивитСоюз
 v2=Инф2БезДоп_Хвост
} : links
{
 v1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2
}

// ------------------------------------------

pattern Инф2БезДоп
{
 Инф2БезДопВосх:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
}



// девушки будут или петь песни, или танцевать
//               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern Инф2БезДоп
{
 conj1=СочинительныйСоюз1
 v1=Инф2БезДоп:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 comma=_запятая
 conj2=СочинительныйСоюз2
 v2=Инф2БезДоп
} : links
{
 v1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>v2
    }
}


// Пропущена запятая:
// мы будем и грести и смотреть...
//          ^^^^^^^^^^^^^^^^^^^
pattern Инф2БезДоп
{
 conj1=ЛогичСоюз2
 v1=Инф2БезДоп:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 conj2=ЛогичСоюз2
 v2=Инф2БезДоп
} : links
{
 v1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>conj2.
      <NEXT_COLLOCATION_ITEM>v2
    }
}
: ngrams { -1 }


// мы будем если не писать, так читать
//          ^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern Инф2БезДоп
{
 conj1=ЕслиСоедГолова
 v1=Инф2БезДоп:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 comma=','
 conj2=ЕслиСоедХвост
 v2=Инф2БезДоп
} : links
{ v1.{
      <PREFIX_CONJUNCTION>conj1
      <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>conj2.
        <NEXT_COLLOCATION_ITEM>v2
     }
}

// буду если уж не есть, тогда надкусывать
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern Инф2БезДоп
{
 conj1=ЕслиСоедГолова
 v1=Инф2БезДоп:export{ ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node }
 comma=','
 v2=Инф2БезДоп
} : links
{ v1.{
      <PREFIX_CONJUNCTION>conj1
      <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>v2
     }
}

