﻿// Правила для разбора причастных оборотов


// ************************
// ПРИЧАСТНЫЙ ОБОРОТ
// ************************

patterns Прич00 export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
pattern Прич00
{
 прилагательное:*{ ПРИЧАСТИЕ ~КРАТКИЙ ~СТРАД }
  :export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
}

// для страдательных причастий удалим прямую винительную валентность
// Осужденный свою вину признал полностью.
// ^^^^^^^^^^ ~~~~~~~~~
pattern Прич00
{
 прилагательное:*{ ПРИЧАСТИЕ ~КРАТКИЙ СТРАД }
  :export {
           РОД
           ПАДЕЖ
           ПАДЕЖВАЛ
           @remove(ПАДЕЖВАЛ:ВИН)
           @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
           МОДАЛЬНЫЙ
           ЧИСЛО
           ОДУШ
           СТРАД
           node:root_node
          }
}


// Особая разновидность "переходных" прилагательных
// никому не интересная желтая звезда
//           ^^^^^^^^^^
pattern Прич00
{
 прилагательное:*{ ~ПРИЧАСТИЕ ~КРАТКИЙ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ }
  :export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
} : ngrams { -3 }


// "Классические непереходные" прилагательные тоже могут образовывать
// квазипричастный оборот:
//
// Другие гонялись на мелководье за тварями, похожими на лягушек.
//                                           ^^^^^^^^
wordentry_set НеКакПрич=прилагательное:{
 этот, тот, любой, какой, который, каждый,
 весь // - Находитесь пока там все.
}
pattern Прич00
{
 прилагательное:*{ ~ПРИЧАСТИЕ ~КРАТКИЙ ~ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ~ТИП_ПРИЛ:ПРИТЯЖ ~ТИП_ПРИЛ:ПОРЯДК СТЕПЕНЬ:АТРИБ ~НеКакПрич }
  :export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
} : ngrams { -4 }


// -----------------------------------------------------------------


patterns Прич0 export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
pattern Прич0
{
 p=Прич00:export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
}




// разрубившей бы его пополам
// ^^^^^^^^^^^^^^
pattern Прич0
{
 p=Прич00:export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 x=частица:бы{}
} : links { p.<POSTFIX_PARTICLE>x }


pattern Прич0
{
 p=Прич00:export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 x=частица:ли{}
} : links { p.<POSTFIX_PARTICLE>x }


// Упавший же камень повредил покрытие
// ^^^^^^^^^^
pattern Прич0
{
 p=Прич00:export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 x=частица:же{}
} : links { p.<POSTFIX_PARTICLE>x }


// Бизнесмена, "заказавшего" свердловского депутата, осудили на 13 лет
//             ^^^^^^^^^^^^^
pattern Прич0
{
 q1=ОткрывающаяКавычка
 p=Прич0:export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 q2=ЗакрывающаяКавычка
} : links
{
 p.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}


// Отрицательная конструкция для причастия без изменения валентности:
//
// Не понимающий задачу ученик может задать уточняющий вопрос
// ^^^^^^^^^^^^^
pattern Прич0
{
 n=частица:не{}
 p=Прич0:export { РОД ПАДЕЖ ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
} : links { p.<NEGATION_PARTICLE>n }


// Смена падежной валентности при отрицании:
//
// Для склейки используйте не оставляющий следа клей
//                         ^^^^^^^^^^^^^^
pattern Прич0
{
 n=частица:не{}
 p=Прич0{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН }:export { РОД ПАДЕЖВАЛ:РОД ПАДЕЖ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
} : links { p.<NEGATION_PARTICLE>n }


// Противоборство в небе продолжалось со все нарастающим ожесточением.
//                                       ^^^^^^^^^^^^^^^
pattern Прич0
{
 x=частица:все{}
 p=Прич0{ ~ПАДЕЖВАЛ:ВИН }:export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
} : links { p.<PREFIX_PARTICLE>x }

pattern Прич0
{
 x=частица:все{}
 p=Прич0{ ПАДЕЖВАЛ:ВИН }:export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
} : links { p.<PREFIX_PARTICLE>x }
: ngrams { -2 }



// -----------------------------------------------------------------

// =======================================================
// ПРАВИЛА ВОСХОДЯЩЕГО РАЗБОРА ПРИЧАСТНОГО ОБОРОТА
// присоединяем элементы, находящиеся справа от причастия
// =======================================================

patterns ПричОборотВосх { bottomup  } export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }

pattern ПричОборотВосх
{
 v=Прич0 : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
}


// Попавший сюда воздух нарушил работу механизма
// ^^^^^^^^^^^^^
pattern ПричОборотВосх
{
 v=ПричОборотВосх : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 adv=Обст
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score( adv, v ) }


// Попавший в шестерни песок заклинил вал
// ^^^^^^^^^^^^^^^^^^^
pattern ПричОборотВосх
{
 v=ПричОборотВосх : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 pn=ПредлогИСущ{ гл_предл( v, _.prepos, _.n2 ) }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score( v, pn.prepos )
 ngram3( v, pn.prepos, pn.n2 )
}



// Задевший землю крылом самолет развалился на части
// ^^^^^^^^^^^^^^^^^^^^^
pattern ПричОборотВосх
{
 v=ПричОборотВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ } : export { РОД ПАДЕЖ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 obj=ГлДополнение{ =ПАДЕЖ->v:ПАДЕЖВАЛ } : export {
                                                  @except(v:ПАДЕЖВАЛ,ПАДЕЖ) // ??? неправильно
                                                  @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
                                                 }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }


// Объект в творительном падеже может выступать в роли обстоятельства способа,
// и поэтому даже отсутствие творительной валентности не мешает связать его с причастием:
//
// Им была предложена радиальная планировка улиц, расходящихся веером от Новгородского кремля.
//                                                ^^^^^^^^^^^^ ^^^^^^
pattern ПричОборотВосх
{
 v=ПричОборотВосх{ ~ПАДЕЖВАЛ:ТВОР } : export { РОД ПАДЕЖ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 obj=ГруппаСущ1{ ПАДЕЖ:ТВОР ОДУШ:НЕОДУШ } : export {
                                                    @except(v:ПАДЕЖВАЛ,ПАДЕЖ)
                                                    @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
                                                   }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -5
 v_obj_score(v,obj)
}



// Попавшая ему в глаз соринка заставила его остановиться
// ^^^^^^^^^^^^
pattern ПричОборотВосх
{
 v=ПричОборотВосх{ ~ПАДЕЖВАЛ:ДАТ } : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 obj=ДатОбъект
}
: links { v.<OBJECT>obj }
: ngrams { -10 }


// Ищем ключ, упавший, вероятно, в грязь
//            ^^^^^^^^^^^^^^^^^^
pattern ПричОборотВосх
{
 v=ПричОборотВосх : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 attr=ВводнАктант
} : links { v.<BEG_INTRO>attr }


pattern ПричОборотВосх
{
 v=ПричОборотВосх : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 attr=Детализатор
} : links { v.<DETAILS>attr }


// кот, знавший, что мышка не может спрятаться
//      ^^^^^^^^^^^....
pattern ПричОборотВосх export { РОД (ПАДЕЖВАЛ) ПАДЕЖ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) ЧИСЛО ОДУШ СТРАД node:root_node }
{
 v=ПричОборотВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН } : export { РОД ПАДЕЖ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 comma=','
 conj=СоединДляПридаточного
 p=ПридаточноеВОбороте
 comma2=@coalesce(',')
}
: ngrams { -1 }
: links
{
 v.<SUBORDINATE_CLAUSE>comma.
    <NEXT_COLLOCATION_ITEM>conj.
     <NEXT_COLLOCATION_ITEM>p.
      ~<PUNCTUATION>comma2
}



pattern ПричОборотВосх export { РОД (ПАДЕЖВАЛ) ПАДЕЖ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) ЧИСЛО ОДУШ СТРАД node:root_node }
{
 v=ПричОборотВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН } : export { РОД ПАДЕЖ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 p=БессоюзноеПридаточное
}
: links { v.<SUBORDINATE_CLAUSE>p }
: ngrams
{
 -2
 ВалентностьБессоюзнПридаточн(v)
}


patterns ПорядкЧислКакОбст export { node:root_node ЧИСЛО РОД }

// Экипаж, приехавший первым, получает дополнительные баллы.
//         ^^^^^^^^^^^^^^^^^
pattern ПричОборотВосх
{
 v=ПричОборотВосх : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 obj=ПорядкЧислКакОбст{ =V:ЧИСЛО =V:РОД }
}
: links { v.<OBJECT>obj }
: ngrams
{
 ВалентностьГлагола(v)
}




// Предложное дополнение с именительным падежом для именной части:
//
// Экипаж, выдвинувшийся в лидеры гонки, получает преимущество
//         ^^^^^^^^^^^^^^^^^^^^^^
pattern ПричОборотВосх export { РОД (ПАДЕЖВАЛ) ПАДЕЖ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) ЧИСЛО ОДУШ СТРАД node:root_node }
{
 v=ПричОборотВосх{ ГлагСДопВИмП } : export { РОД ПАДЕЖ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 prep=предлог:в{}
 obj=ГруппаСущ4{ ПАДЕЖ:ИМ одуш:одуш число:мн }
}
: links { v.<PREPOS_ADJUNCT>prep.<OBJECT>obj }
: ngrams { ngram3(v,prep,obj) }




// Некоторые связочные глаголы (см. множество ПритворитьсяТакимтоГл)
// присоединяют без штрафа прилагательное в качестве прямого дополнения
// в творительном падеже:
//
// Кот, притворившийся спящим, внимательно следил за гнездом.
//      ^^^^^^^^^^^^^^^^^^^^^
pattern ПричОборотВосх export { РОД (ПАДЕЖВАЛ) ПАДЕЖ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) ЧИСЛО ОДУШ СТРАД node:root_node }
{
 v=ПричОборотВосх{ ПритворитьсяТакимтоГл ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ТВОР } : export { РОД ПАДЕЖ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 obj=ГлДопПрил{ =V:ЧИСЛО =V:ЛИЦО }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }


// Модальная конструкция - причастие присоединяет инфинитив:
//
// Заставивший его дернуться звук повторился
// ^^^^^^^^^^^     ^^^^^^^^^
pattern ПричОборотВосх export { РОД (ПАДЕЖВАЛ) ПАДЕЖ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) ЧИСЛО ОДУШ СТРАД node:root_node }
{
 v=ПричОборотВосх{ МОДАЛЬНЫЙ } : export { РОД ПАДЕЖ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 inf=Инф2
} : links { v.<INFINITIVE>inf }


pattern ПричОборотВосх export { РОД (ПАДЕЖВАЛ) ПАДЕЖ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) ЧИСЛО ОДУШ СТРАД node:root_node }
{
 v=ПричОборотВосх{ ~МОДАЛЬНЫЙ } : export { РОД ПАДЕЖ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
 inf=Инф2
}
: links { v.<INFINITIVE>inf }
: ngrams { -10 }


// -----------------------------------------------------------------

// ТЕПЕРЬ НИСХОДЯЩИЙ РАЗБОР
// присоединяем элементы, находящиеся слева от причастия

patterns ПричОборотНисх export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }

pattern ПричОборотНисх
{
 v=ПричОборотВосх : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
}


// Сюда попавший воздух нарушит работу механизма
// ^^^^^^^^^^^^^
pattern ПричОборотНисх
{
 attr=ГруппаНареч2
 v=ПричОборотНисх : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
}
: links { v.<ATTRIBUTE>attr }
: ngrams
{
 -2
 adv_verb_score( attr, v )
 adv_adj_score( attr, v )
}

// Обычно так не говорим, но формально это допустимая конструкция:
//
// Отряд, к воротам устремившийся с криком, был поддержан нами.
//        ^^^^^^^^^^^^^^^^^^^^^^^
pattern ПричОборотНисх
{
 p=предлог:*{}
 n=ГлДополнение{ =p:ПАДЕЖ }
 v=ПричОборотНисх{ гл_предл( _, p, n ) } : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
}
: links { v.<PREPOS_ADJUNCT>p.<OBJECT>n }
: ngrams
{
 -2
 prepos_score( v, p )
 ngram3( v, p, n )
}



// Экипаж, первым добравшийся до базы, был неплохо поощрен.
//         ^^^^^^^^^^^^^^^^^^
pattern ПричОборотНисх
{
 obj=ПорядкЧислКакОбст
 v=ПричОборотНисх{ =obj:ЧИСЛО =obj:РОД } : export { РОД ПАДЕЖВАЛ ПАДЕЖ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
}
: links { v.<OBJECT>obj }
: ngrams { -1 }


// --------------------------------------------------

patterns ЛевПричОбъект export { node:root_node ПАДЕЖ }


pattern ЛевПричОбъект
{
 Сущ0 : export { node:root_node ПАДЕЖ }
}

// Нас заметивший стражник побежал
// ^^^
pattern ЛевПричОбъект
{
 местоимение:*{} : export { node:root_node ПАДЕЖ }
}

// Сочувственно взглянул на чем-то расстроенного приятеля.
//                          ^^^^^^
pattern ЛевПричОбъект
{
 ГруппаМестоимСущ : export { node:root_node ПАДЕЖ }
}


pattern ЛевПричОбъект
{
 ГруппаПрил1 : export { node:root_node ПАДЕЖ }
}



// Голодный хищник, добычу заметивший, немедленно нападёт.
//                  ^^^^^^^^^^^^^^^^^
pattern ПричОборотНисх
{
 obj=ЛевПричОбъект
 v=ПричОборотНисх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =ПАДЕЖВАЛ->obj:ПАДЕЖ }
     : export { 
               РОД ПАДЕЖ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node
               @except(ПАДЕЖВАЛ,obj:ПАДЕЖ) // ??? неправильно
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
              }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -2
 v_obj_score( v, obj )
}

// Объект в творительном падеже может выступать в роли обстоятельства способа,
// и поэтому даже отсутствие творительной валентности не мешает связать его с причастием:
//
// Им была предложена радиальная планировка улиц, веером расходящихся от Новгородского кремля.
//                                                ^^^^^^ ^^^^^^^^^^^^
pattern ПричОборотНисх
{
 obj=Сущ0{ ПАДЕЖ:ТВОР ОДУШ:НЕОДУШ }
 v=ПричОборотНисх{ ~ПАДЕЖВАЛ:ТВОР }
     : export { 
               РОД ПАДЕЖ МОДАЛЬНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node
               @except(ПАДЕЖВАЛ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
              }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -5
 v_obj_score( v, obj )
}

/*
// Инфинитив слева - очень редкая конструкция:

// Дождь, капать начавший еще утром, продолжился весь день
//        ^^^^^^^^^^^^^^^
pattern ПричОборотВосх export { РОД (ПАДЕЖВАЛ) ПАДЕЖ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) ЧИСЛО ОДУШ СТРАД node:root_node }
{
 inf=Инф2БезДоп
 v=ПричОборотВосх{ МОДАЛЬНЫЙ } : export { РОД ПАДЕЖ ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ ЧИСЛО ОДУШ СТРАД node:root_node }
}
: links { v.<INFINITIVE>inf }
: ngrams { -5 }
*/


// -----------------------------------------------------------------

// Стражник, левой рукой протянувший мне меч, повернулся и ушел.
//           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПричОборот0
{
 ПричОборотНисх : export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
}



// все вторгшиеся сюда наказываются
// ^^^^^^^^^^^^^^^^^^^
pattern ПричОборот0
{
 adj=прилагательное:весь{}
 a2=ПричОборот2{ =Adj:ЧИСЛО =Adj:ПАДЕЖ =Adj:РОД =Adj:ОДУШ } : export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
} : links { a2.<NEXT_ADJECTIVE>adj }


// -----------------------------------------------------------------


pattern ПричОборот2
{
 ПричОборот0:export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
}


// очень довольный покупками и верный своему слову ребенок молчал.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПричОборот2
{
 p1=ПричОборот0:export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
 conj=ЛогичСоюз 
 p2=ПричОборот0{ =p1:ЧИСЛО =p1:ПАДЕЖ =p1:РОД =p1:ОДУШ } 
} : links { p1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }


// континент   облаков,   разрываемых   и   скручиваемых   молниями.
pattern ПричОборот2
{
 p1=Прич0:export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
 conj=ЛогичСоюз
 p2=ПричОборот0{ =p1:ЧИСЛО =p1:ПАДЕЖ =p1:РОД =p1:ОДУШ } 
} : links { p1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }


// Он живёт в мире, отличающемся от нашего, но имеющем с ним ряд сходств.
pattern ПричОборот2
{
 p1=ПричОборот0:export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
 comma=','
 conj=ПротивитСоюз
 p2=ПричОборот0{ =p1:ЧИСЛО =p1:ПАДЕЖ =p1:РОД =p1:ОДУШ } 
} : links
{
 p1.<RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p2
}





// человек, разодетый в перья  и  носивший  отвратительную деревянную маску.
pattern ПричОборот2
{
 p1=ПравГруппаПрил2:export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
 conj=ЛогичСоюз 
 p2=ПричОборот0{ =p1:ЧИСЛО =p1:ПАДЕЖ =p1:РОД =p1:ОДУШ } 
} : links { p1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }

pattern ПричОборот2
{
 p1=ПричОборот0:export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }
 conj=ЛогичСоюз 
 p2=ПравГруппаПрил2{ =p1:ЧИСЛО =p1:ПАДЕЖ =p1:РОД =p1:ОДУШ } 
} : links { p1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }


