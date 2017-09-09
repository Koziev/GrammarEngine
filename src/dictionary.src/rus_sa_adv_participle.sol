// ***********************
// ДЕЕПРИЧАСТНЫЙ ОБОРОТ
// ***********************
//
// LC->10.07.2014

// ------------------------------------------------------------

// Обстоятельство для деепричастия: нам надо исключить
// из вариантов сборки обстоятельства деепричастие.
//
// широко и обнадеживающе улыбаясь, Артём поднялся.
// ^^^^^^^^^^^^^^^^^^^^^^


wordentry_set НаречДляДеепр = наречие: { только, даже, лишь, именно }


patterns ОбстДляДееприч0 export { node:root_node }

pattern ОбстДляДееприч0
{
 ГруппаНареч2 { ~НеМожетМодифГлаг } : export { node:root_node }
}


// спросил я, удивившись еще более.
//                       ^^^^^^^^^
pattern ОбстДляДееприч0
{
 ГруппаНареч2 { НеМожетМодифГлаг } : export { node:root_node }
}
: ngrams { -3 }



pattern ОбстДляДееприч0
{
 НаречДляДеепр : export { node:root_node }
} : ngrams { -1 }


pattern ОбстДляДееприч0
{
 ГруппаСрНареч2 { ~НеМожетМодифГлаг } : export { node:root_node }
}

pattern ОбстДляДееприч0
{
 ПредлогИСущ : export { node:root_node }
} : ngrams { -1 }


patterns ОбстФраза0 export { node:root_node }

pattern ОбстДляДееприч0
{
 ОбстФраза0:export { node:root_node }
}

// -------------------------------------

patterns ОбстДляДеепричВосх { bottomup } export { node:root_node }
patterns ОбстДляДеепричНисх export { node:root_node }

pattern ОбстДляДееприч
{
 ОбстДляДеепричНисх : export { node:root_node }
}



pattern ОбстДляДеепричВосх
{
 adv=ОбстДляДееприч0 : export { node:root_node }
}


pattern ОбстДляДеепричВосх
{
 adv=ОбстДляДеепричВосх : export { node:root_node }
 comma=','
 pn=ОбстДляДееприч0
 @noshift(ПравыйОграничительОборота)
 comma2=@coalesce(',')
} : links
{
 adv.<RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>pn.
        ~<PUNCTUATION>comma2
}

// ---------------------------------------

patterns СоединитОбст export { node:root_node }

pattern СоединитОбст
{
 ПротивитСоюз : export { node:root_node }
}

// Читая вслух разные  книги  для  ее  развлеченья,  а  иногда для ее усыпленья
//                            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern СоединитОбст
{
 conj=ПротивитСоюз : export { node:root_node }
 mod=ГруппаНареч1
} : links { conj.<ATTRIBUTE>mod }

// Лежа обычно на полу, но иногда и на подоконнике
//             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern СоединитОбст
{
 conj=ПротивитСоюз : export { node:root_node }
 mod=ГруппаНареч1
 conj2=союз:и{}
} : links { conj.<ATTRIBUTE>mod.<NEXT_COLLOCATION_ITEM>conj2 }


// ---------------------------------------------------------------

pattern ОбстДляДеепричВосх
{
 adv=ОбстДляДеепричВосх : export { node:root_node }
 comma=','
 conj=СоединитОбст
 pn=ОбстДляДееприч0
} : links
{
 adv.<RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>pn
}


pattern ОбстДляДеепричВосх
{
 adv=ОбстДляДеепричВосх : export { node:root_node }
 comma=','
 conj=ЛогичСоюз
 pn=ОбстДляДееприч0
} : links
{
 adv.<RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>pn
}


// Ложась во дворе или дома, ты ничем не рискуешь
//        ^^^^^^^^^^^^^^^^^
pattern ОбстДляДеепричВосх
{
 adv=ОбстДляДеепричВосх : export { node:root_node }
 conj=ЛогичСоюз
 pn=ОбстДляДееприч0
} : links
{
 adv.<RIGHT_LOGIC_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>pn
}


pattern ОбстДляДеепричВосх
{
 adv=ОбстДляДеепричВосх : export { node:root_node }
 q2=ЗакрывающаяКавычка
}
: links { adv.<APPEND_QUOTE>q2 }
: ngrams { -1 }



// ---------------------------------------------------------

pattern ОбстДляДеепричНисх
{
 ОбстДляДеепричВосх : export { node:root_node }
}


pattern ОбстДляДеепричНисх
{
 conj1=ЛогичСоюз2
 p1=ОбстДляДеепричНисх : export { node:root_node }
 comma2=','
 conj2=ЛогичСоюз2
 p2=ОбстДляДееприч0
} : links
{
 p1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma2.<NEXT_COLLOCATION_ITEM>conj2.
      <NEXT_COLLOCATION_ITEM>p2
    }
}
: ngrams { 5 }


// высказываясь не  только  о  героях  этих  творений, но даже и от их имени
//              ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ОбстДляДеепричНисх
{
 conj1=СочинительныйСоюз1
 adv=ОбстДляДеепричНисх : export { node:root_node }
 comma=','
 conj2=СочинительныйСоюз2
 pn=ОбстДляДееприч0
} : links
{
 adv.{
      <PREFIX_CONJUNCTION>conj1
      <RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>pn
     }
}
: ngrams { 5 }






// Отдыхая как дома, так и на лужайке
//         ^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ОбстДляДеепричНисх
{
 conj1=Соедин2Обст1
 adv=ОбстДляДеепричНисх : export { node:root_node }
 comma=','
 conj2=Соедин2Обст2
 pn=ОбстДляДееприч0
} : links
{
 adv.{
      <PREFIX_CONJUNCTION>conj1
      <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>conj2.
        <NEXT_COLLOCATION_ITEM>pn
     }
}
: ngrams { 7 }



pattern ОбстДляДеепричНисх
{
 q1=ОткрывающаяКавычка
 adv=ОбстДляДеепричНисх : export { node:root_node }
}
: links { adv.<PREPEND_QUOTE>q1 }
: ngrams { -1 }




// ------------------------------------------

patterns Деепр0 export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }

// Выдвигаясь в лидеры
pattern Деепр0
{
 деепричастие:*{} : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
}


// Вернувшись же, я застал здесь...
// ^^^^^^^^^^^^^
pattern Деепр0
{
 v=деепричастие:*{} : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
 p=частица:же{}
} : links { v.<POSTFIX_PARTICLE>p }


// Делая ли обычную работу или творя что-то новое
// ^^^^^^^^
pattern Деепр0
{
 v=деепричастие:*{} : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
 p=частица:ли{}
} : links { v.<POSTFIX_PARTICLE>p }


// Взяв-то эту ладью
// ^^^^^^^
pattern Деепр0
{
 v=деепричастие:*{} : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
 t='-'
 p=частица:то{}
} : links { v.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>p }


// Не попадая в лидеры общего зачета
// ^^^^^^^^^^
pattern Деепр0
{
 n=частица:не{}
 v=Деепр0 : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
} : links { v.<NEGATION_PARTICLE>n }

// Я шел быстро, все ускоряя  шаги.
//               ^^^^^^^^^^^
pattern Деепр0
{
 n=частица:всё{}
 v=деепричастие:*{} : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
}
: links { v.<PREFIX_PARTICLE>n }
: ngrams { -1 }



// Смена валентности для отрицательной формы:
//
// руководство решило, не продумав последствий
//                     ^^^^^^^^^^^^^^^^^^^^^^^
pattern Деепр0
{
 not=частица:не{}
 a=Деепр0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН } : export { node:root_node ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД МОДАЛЬНЫЙ }
} : links { a.<NEGATION_PARTICLE>not }


// Так никого и не встретив, он свернул с дороги
//            ^^^^^^^^^^^^^
pattern Деепр0
{
 p=частица:и{}
 not=частица:не{}
 a=Деепр0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН } : export { node:root_node ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:РОД МОДАЛЬНЫЙ }
} : links
{
 A.{
    <PREFIX_PARTICLE>p
    <NEGATION_PARTICLE>not
   }
}
: ngrams { -1 }


// Юноши, и умирая, пели.
//        ^^^^^^^^
pattern Деепр0
{
 p=частица:и{}
 a=Деепр0 : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
}
: links { A.<PREFIX_PARTICLE>p }
: ngrams { -1 }


// Дефолтное правило - разрешаем прикреплять к деепричастию
// любые частицы с большим штрафом.
pattern Деепр0
{
 p=частица:*{}
 v=Деепр0 : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
}
: links { v.<PREFIX_PARTICLE>p }
: ngrams { -10 }

// -----------------------------------------------------------------------

patterns Деепр export { node:root_node }


// став главным, Коля не перестал удивлять
pattern Деепр
{
 a=Деепр0{ ПритворитьсяТакимтоГл } : export { node:root_node }
 obj=ГруппаПрил2{ ПАДЕЖ:ТВОР }
} : links { a.<OBJECT>obj }
: ngrams
{
 ВалентностьГлагола(a)
}


// став сильнее самого себя
pattern Деепр
{
 a=Деепр0{ Выглядеть_ПРИЛ } : export { node:root_node }
 obj=ГруппаСравнПрил
} : links { a.<ATTRIBUTE>obj }
: ngrams
{
 ВалентностьГлагола(a)
}



// приехав тридцать первым, Коля не стал горевать
pattern Деепр
{
 a=Деепр0 : export { node:root_node }
 obj=ПорядкЧислКакОбст
} : links { a.<OBJECT>obj }


// закончив работу третьей, она спокойно пошла домой
pattern Деепр
{
 a=Деепр0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН } : export { node:root_node }
 obj1=ГлДополнение{ ПАДЕЖ:ВИН }
 obj2=ПорядкЧислКакОбст
} : links
{
 a.{
    <OBJECT>obj1
    <OBJECT>obj2
   }
}
: ngrams
{
 ВалентностьГлагола(a)
}



// Они поели холодного мяса и сухарей, посчитав опасным разводить огонь.
pattern Деепр
{
 a=деепричастие:посчитав{} : export { node:root_node }
 adj=прилагательное:*{ ПАДЕЖ:ТВОР ~КРАТКИЙ РОД:СР ЧИСЛО:ЕД }
 obj=Инф2
} : links
{
 A.{
    <ATTRIBUTE>adj
    <OBJECT>obj
   }
}
: ngrams
{
 ВалентностьГлагола(a)
}



wordentry_set ПритворяясьТакимто = деепричастие:{ притворившись, притворяясь, становясь, став}

// притворяясь больным
pattern Деепр
{
 adv=@optional(ГруппаНареч2)
 a=ПритворяясьТакимто : export { node:root_node }
 adj=ГруппаПрил2{ ПАДЕЖ:ТВОР }
} : links
{
 A.{
    ~<ATTRIBUTE>adv
    <OBJECT>adj
   }
}
: ngrams
{
 ВалентностьГлагола(a)
}



// ============================================================

patterns ДеепрВосх { bottomup  } export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }

pattern ДеепрВосх
{
 Деепр0 : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
}

pattern ДеепрВосх
{
 v=ДеепрВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ } : export { node:root_node МОДАЛЬНЫЙ }
 obj=ГлДополнение{ =v:ПАДЕЖ } : export {
                                        @except(v:ПАДЕЖ,ПАДЕЖ)
                                        @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
                                       }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }


pattern ДеепрВосх
{
 v=ДеепрВосх : export { node:root_node МОДАЛЬНЫЙ }
 obj=ГлДополнение{ !=v:ПАДЕЖ } : export {
                                        @except(v:ПАДЕЖ,ПАДЕЖ)
                                        @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
                                       }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -11
 v_obj_score(v,obj)
}



// сев дракону на спину
pattern ДеепрВосх
{
 v=ДеепрВосх{ ~ПАДЕЖ:ДАТ } : export { node:root_node МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ }
 obj=ГлДополнение{ ПАДЕЖ:ДАТ }
}
: links { v.<OBJECT>obj }
: ngrams { -10 }

// Объект в творительном падеже присоединяем с небольшим штрафом, если
// у глагола нет творительной валентности:
//
// Дверь, сложившись гармошкой, открылась
//        ^^^^^^^^^^^^^^^^^^^^
pattern ДеепрВосх
{
 v=ДеепрВосх{ ~ПАДЕЖ:ТВОР } : export { node:root_node МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ }
 obj=ГлДополнение{ ПАДЕЖ:ТВОР }
}
: links { v.<OBJECT>obj }
: ngrams { -5 }



// зная, что он прав
//     ^^^^^^^^^^^^^
// она остановилась, чувствуя, как сильно заколотилось в груди сердце
//                           ^^^^^
pattern ДеепрВосх export { node:root_node ПЕРЕХОДНОСТЬ (ПАДЕЖ) (МОДАЛЬНЫЙ) }
{
 v=ДеепрВосх : export { node:root_node ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
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

// понимая, о ком он говорил
pattern ДеепрВосх export { node:root_node ПЕРЕХОДНОСТЬ (ПАДЕЖ) (МОДАЛЬНЫЙ) }
{
 v=ДеепрВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН } : export { node:root_node ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ }
 p=БессоюзноеПридаточное
}
: links { v.<SUBORDINATE_CLAUSE>p }
: ngrams
{
 -1
 ВалентностьБессоюзнПридаточн(v)
}



pattern ДеепрВосх
{
 v=ДеепрВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
 adv=ОбстДляДееприч
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score( adv, v ) }


pattern ДеепрВосх
{
 v=ДеепрВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
 adv=ВводнАктант
} : links { v.<BEG_INTRO>adv }


pattern ДеепрВосх
{
 v=ДеепрВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
 d=Детализатор
} : links { v.<DETAILS>d }


// Начиная плясать, он прижимал руки
pattern ДеепрВосх export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ (МОДАЛЬНЫЙ) }
{
 v=ДеепрВосх{ МОДАЛЬНЫЙ } : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 inf=Инф2
}
: links { v.<INFINITIVE>inf }
: ngrams { v_inf_score(v,inf) }


pattern ДеепрВосх export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ (МОДАЛЬНЫЙ) }
{
 v=ДеепрВосх{ ~МОДАЛЬНЫЙ } : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 inf=Инф2
}
: links { v.<INFINITIVE>inf }
: ngrams
{
 -10
 v_inf_score(v,inf)
}



pattern ДеепрВосх
{
 v=ДеепрВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
 pn=ПредлогИСущ{ гл_предл( v, _.prepos, _.n2 ) }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score( v, pn.prepos )
 ngram3( v, pn.prepos, pn.n2 )
}

// Выдвигаясь в лидеры
pattern ДеепрВосх export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ (МОДАЛЬНЫЙ) }
{
 v=ДеепрВосх{ ГлагСДопВИмП } : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ }
 prep=предлог:в{}
 obj=ГруппаСущ4{ ПАДЕЖ:ИМ ОДУШ:ОДУШ ЧИСЛО:МН }
}
: links { v.<PREPOS_ADJUNCT>prep.<OBJECT>obj }
: ngrams
{
 prepos_score( v, prep )
 ngram3( v, prep, obj )
}


pattern ДеепрВосх
{
 v=ДеепрВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
 q2=ЗакрывающаяКавычка
}
: links { v.<APPEND_QUOTE>q2 }
: ngrams { -1 }




// --------------------------------------------------------

patterns ДеепрНисх export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }

pattern ДеепрНисх
{
 ДеепрВосх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
}

pattern ДеепрНисх
{
 adv=ОбстДляДееприч
 v=ДеепрНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
} 
: links
{
 v.<ATTRIBUTE>adv
}
: ngrams
{
 adv_verb_score( adv, v )
}



pattern ДеепрНисх
{
 intro=ВводнАктант
 v=ДеепрНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
} 
: links { v.<BEG_INTRO>intro }


pattern ДеепрНисх
{
 intro=Детализатор
 v=ДеепрНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
} 
: links { v.<DETAILS>intro }


pattern ДеепрНисх
{
 pn=ПредлогИСущ
 v=ДеепрНисх { гл_предл(_,pn.prepos,pn.n2) } : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
} 
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 -1
 prepos_score( v, pn.prepos )
 ngram3( v, pn.prepos, pn.n2 )
}



pattern ДеепрНисх
{
 obj=ГлДополнение
 v=ДеепрНисх { ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =Obj:ПАДЕЖ }
     : export { 
               node:root_node МОДАЛЬНЫЙ
               @except(ПАДЕЖ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -1 // обычно дополнения ставятся ПОСЛЕ деепричастия
 v_obj_score( v, obj )
}


pattern ДеепрНисх
{
 obj=ГлДополнение
 v=ДеепрНисх { !=Obj:ПАДЕЖ }
     : export { 
               node:root_node МОДАЛЬНЫЙ
               @except(ПАДЕЖ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -11
 v_obj_score( v, obj )
}


// дракону на спину сев
pattern ДеепрНисх
{
 obj=ГлДополнение{ ПАДЕЖ:ДАТ }
 v=ДеепрНисх { ~ПАДЕЖ:ДАТ } : export { node:root_node МОДАЛЬНЫЙ ПАДЕЖ ПЕРЕХОДНОСТЬ }
}
: links { v.<OBJECT>obj }
: ngrams { -10 }


pattern ДеепрНисх
{
 q1=ОткрывающаяКавычка
 v=ДеепрНисх : export { node:root_node ПЕРЕХОДНОСТЬ ПАДЕЖ МОДАЛЬНЫЙ }
}
: links { v.<PREPEND_QUOTE>q1 }
: ngrams { -1 }


// -------------------------------------------

pattern Деепр
{
 v=ДеепрНисх : export { node:root_node }
}
: ngrams
{
 ВалентностьГлагола(v)
}

// ============================================================

// Союзные паттерны для деепричастий
patterns Деепр2 export { node:root_node }


// ---------------------------------------------------------------

patterns ДеепрГруппаВосх { bottomup } export { node:root_node }


pattern Деепр2
{
 ДеепрГруппаВосх:export { node:root_node }
}



pattern ДеепрГруппаВосх
{
 Деепр : export { node:root_node }
}

// Коля решил вернуться домой, купив молока и заплатив за телефон
//                             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ДеепрГруппаВосх
{
 p1=ДеепрГруппаВосх:export { node:root_node }
 conj=ЛогичСоюз
 p2=Деепр
} : links { p1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }



// Поужинав жареным мясом, а затем напившись вина и водки, караванщики разошлись спать.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ДеепрГруппаВосх
{
 p1=ДеепрГруппаВосх:export { node:root_node }
 comma=','
 conj=ПротивитСоюз
 p2=Деепр
} : links
{
 p1.<RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p2
}



// Коля решил вернуться домой, купив молока, заплатив за телефон и выгуляв собаку
//                             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^....
pattern ДеепрГруппаВосх
{
 p1=ДеепрГруппаВосх:export { node:root_node }
 comma=','
 p2=Деепр
} : links
{
 p1.<RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>p2
}




// Люди становятся богатыми, или заработав денег, или получив наследство
//                           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ДеепрГруппаВосх
{
 conj1=СочинительныйСоюз1
 p1=ДеепрГруппаВосх:export { node:root_node }
 comma2=','
 conj2=СочинительныйСоюз2
 p2=Деепр
} : links
{
 p1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma2.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>p2
    }
}




// Цель игры состоит в том, чтобы получить как можно больше очков, расстреливая астероиды и летающие тарелки, и избегая при этом столкновения с обломками. 
//                                                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ДеепрГруппаВосх
{
 p1=ДеепрГруппаВосх:export { node:root_node }
 comma2=','
 conj=ЛогичСоюз
 p2=Деепр
} : links
{
 p1.{
     <RIGHT_LOGIC_ITEM>comma2.
      <NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>p2
    }
}


/*
// Леденея от горя, сгорая от гнева, он шатал взад-вперед по запертой палате.
pattern Деепр2
{
 p1=Деепр:export { node:root_node }
 comma2=','
 p2=Деепр
} : links
{
 p1.{
     <RIGHT_LOGIC_ITEM>comma2.
      <NEXT_COLLOCATION_ITEM>p2
    }
}
*/

// ----------------------------------------




// Коля решил вернуться домой, купив молока
//                           ^^^^^^^^^^^^^^
pattern ДеепрОборот
{
 comma1=','
 p=Деепр2:export { node:root_node }
 @noshift(ПравыйОграничительОборота)
 comma2=@coalesce(',')
} : links
{
 p.{
    <PUNCTUATION>comma1
    ~<PUNCTUATION>comma2
   }
}

// Иногда запятые ошибочно пропущены. Из-за большого
// количества таких случаев, делаем отдельное правило с большим штрафом:
//
// кто по лесу ходит задрав нос?
//                   ^^^^^^^^^^
pattern ДеепрОборот
{
 p=Деепр2:export { node:root_node }
}
: ngrams { -10 }



/*
// Одиночное деепричастие может выступать в роли обстоятельства:
// Они развалясь сидели за летними столиками, поедая гамбургеры и запивая их пивом.
//     ^^^^^^^^^
pattern Обст
{
 деепричастие:*{} : export { node:root_node }
} : ngrams { -5 }
*/
// -----------------------------------

// Купив молока, Коля решил вернуться домой
// ^^^^^^^^^^^^^
pattern ДеепрОборотПеред
{
 @probe_left(ЛевыйОграничительОборота)
 comma1=@optional(',')
 p=Деепр2:export { node:root_node }
 comma2=','
} : links
{
 p.{
    ~<PUNCTUATION>comma1
    <PUNCTUATION>comma2
   }
}


// Теперь можем записать паттерн для инфинитива с деепричастным оборотом:
// пытаюсь не уснуть, выпивая много крепкого кофе
//         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ИнфСДеепричОбор
{
 inf=Инф2:export { node:root_node }
 p=ДеепрОборот
} : links { inf.<ADV_PARTICIPLE>p }
