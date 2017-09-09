// Предикаты со страдательным причастием в краткой форме или краткой формой
// прилагательного в роли именного сказуемого.
//
// CD->01.09.2013
// LC->25.10.2015


patterns ВспомСтрадГлагол export { ЛИЦО ЧИСЛО РОД ВРЕМЯ node:root_node }

// - Будьте осторожны, дядя!
//   ^^^^^^
pattern ВспомСтрадГлагол
{
 СвязочныйГлагол : export { ЛИЦО ЧИСЛО РОД время node:root_node }
}

// ++++

patterns СтрадПрич0 export { ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }

// Я рад вам помочь
//   ^^^
pattern СтрадПрич0
{
 прилагательное:*{ КРАТКИЙ МОДАЛЬНЫЙ }
   : export { ЧИСЛО РОД ПЕРЕХОДНОСТЬ ПАДЕЖВАЛ МОДАЛЬНЫЙ node:root_node }
}


pattern СтрадПрич0 export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ ПАДЕЖВАЛ (МОДАЛЬНЫЙ) node:root_node }
{
 КраткПрил2{ ПРИЧАСТИЕ СТРАД } : export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ ПАДЕЖВАЛ @add(ПАДЕЖВАЛ:ТВОР) node:root_node }
}


// Антонио был молод, да мудр
//             ^^^^^^^^^^^^^^
pattern СтрадПрич0 export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ (ПАДЕЖВАЛ) (МОДАЛЬНЫЙ) node:root_node }
{
 КраткПрил2{ ~ПРИЧАСТИЕ ~ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ } : export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ node:root_node }
}



// ему было приятно ее присутствие
//          ^^^^^^^
// она не менее сильна
//     ^^^^^^^^^^^^^^^
// каждая секунда была дорога
//                     ^^^^^^
pattern СтрадПрич0 export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ ПАДЕЖВАЛ (МОДАЛЬНЫЙ) node:root_node }
{
 КраткПрил2{ ~СТРАД ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ } : export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ ПАДЕЖВАЛ node:root_node }
}

wordentry_set ПричСВинДоп=прилагательное:{ должный }

// ты им деньги был должен
//                  ^^^^^^
// Но она никому ничего не должна
//                      ^^^^^^^^^
pattern СтрадПрич0 export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ (ПАДЕЖВАЛ) МОДАЛЬНЫЙ node:root_node }
{
 ne=частица:не{}
 a=ПричСВинДоп{ КРАТКИЙ }
  : export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН @add(ПАДЕЖВАЛ:РОД) @add(ПАДЕЖВАЛ:ПАРТ) @add(ПАДЕЖВАЛ:ДАТ) МОДАЛЬНЫЙ node:root_node }
}
: links { a.<NEGATION_PARTICLE>ne }


// Она должна денег?
//     ^^^^^^
pattern СтрадПрич0 export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ (ПАДЕЖВАЛ) МОДАЛЬНЫЙ node:root_node }
{
 a=ПричСВинДоп{ КРАТКИЙ }
  : export { РОД ЧИСЛО ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН @add(ПАДЕЖВАЛ:РОД) @add(ПАДЕЖВАЛ:ПАРТ) @add(ПАДЕЖВАЛ:ДАТ) МОДАЛЬНЫЙ node:root_node }
}
: ngrams { -2 }


// +++++++++++++++++++++
// Добавляем частицы

patterns СтрадПрич1 export { ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
pattern СтрадПрич1
{
 СтрадПрич0 : export { ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}


wordentry_set ПостфиксыДляПрич=частица:{ ли, же }

pattern СтрадПрич1
{
 p=СтрадПрич0 : export { ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 x=ПостфиксыДляПрич
} : links { p.<POSTFIX_PARTICLE>x }


// удивлен-то я был сильно
// ^^^^^^^^^^
pattern СтрадПрич1
{
 p=СтрадПрич0 : export { ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 t='-'
 x=частица:то{}
} : links { p.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>x }


// она была старше меня
pattern СтрадПрич1 export { (ЧИСЛО) (РОД) (ПАДЕЖВАЛ) ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) node:root_node }
{
 СравнРема : export { ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ node:root_node }
} : ngrams { 2 }



// не должен же он выделяться
// ^^^^^^^^^^^^
pattern СтрадПрич1
{
 n=частица:не{}
 p=СтрадПрич1 : export { ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { p.<NEGATION_PARTICLE>n }

// Я  и  должен  был идти по нему до Оби.
//    ^^^^^^^^^
pattern СтрадПрич1
{
 n=частица:и{}
 p=СтрадПрич1 : export { ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}
: links { p.<PREFIX_PARTICLE>n }
: ngrams { -2 }


// +++++++++++++++++++++++++++

patterns СтрадПричДополнение export { node:root_node ПАДЕЖ }

pattern СтрадПричДополнение
{
 ГлДополнение{ ПАДЕЖ:ТВОР } : export { node:root_node ПАДЕЖ }
}

pattern СтрадПричДополнение
{
 ГлДополнение{ ПАДЕЖ:ДАТ } : export { node:root_node ПАДЕЖ }
}

pattern СтрадПричДополнение
{
 ГлДополнение{ ПАДЕЖ:РОД } : export { node:root_node ПАДЕЖ }
}

pattern СтрадПричДополнение
{
 ГлДополнение{ ПАДЕЖ:ПАРТ } : export { node:root_node ПАДЕЖ }
}

// +++++++++++++++++++++++++++


// Сборка неполной связки - без подлежащего. Этот паттерн может выступать
// в роли элементарного сказуемого в сложном сказуемом.


// ---------------------------------------
// Восходящая сборка

patterns СтрадСвязкаВосх { bottomup } export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }

pattern СтрадСвязкаВосх export { AUX_VERB_REQUIRED (ВРЕМЯ) (ЛИЦО) ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
{
 СтрадПрич1 : export { AUX_VERB_REQUIRED:1 ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}


pattern СтрадСвязкаВосх export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД (ПАДЕЖВАЛ) (ПЕРЕХОДНОСТЬ) (МОДАЛЬНЫЙ) node:root_node }
{
 v=СтрадСвязкаВосх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД node:root_node }
 comma1=','
 conj=союз:что{}
 p=ПридаточноеВОбороте
 comma2=@coalesce(',')
} : links
{
 v.<SUBORDINATE_CLAUSE>comma1.
    <NEXT_COLLOCATION_ITEM>conj.
    <NEXT_COLLOCATION_ITEM>p.
     ~<PUNCTUATION>comma2
}


// прикрепляем дополнение:
// он был допрошен полицией
//                 ^^^^^^^^
pattern СтрадСвязкаВосх
{
 v=СтрадСвязкаВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ } : export { node:root_node ВРЕМЯ AUX_VERB_REQUIRED ЛИЦО ЧИСЛО РОД МОДАЛЬНЫЙ }
 obj=СтрадПричДополнение{ =ПАДЕЖ->v:ПАДЕЖВАЛ } : export {
                                                  @except(v:ПАДЕЖВАЛ,ПАДЕЖ)
                                                  @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
                                                 }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }


pattern СтрадСвязкаВосх
{
 v=СтрадСвязкаВосх{ ПричСВинДоп ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН } : export { node:root_node ВРЕМЯ AUX_VERB_REQUIRED ЛИЦО ЧИСЛО РОД МОДАЛЬНЫЙ }
 obj=ГлДополнение{ ПАДЕЖ:ВИН } : export {
                                         @except(v:ПАДЕЖВАЛ,ПАДЕЖ)
                                         @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
                                        }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }


// Глагольное обстоятельство:
// Оно было исправлено вчера
//                     ^^^^^
pattern СтрадСвязкаВосх
{
 v=СтрадСвязкаВосх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 adv=Обст
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score( adv, v ) }


// Инфинитив для модальной страдательной конструкции:
// Мы вынуждены были уступить ему
//                   ^^^^^^^^^^^^
pattern СтрадСвязкаВосх export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) node:root_node }
{
 v=СтрадСвязкаВосх{ МОДАЛЬНЫЙ } : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ node:root_node } inf=Инф2
}
: links { v.<INFINITIVE>inf }
: ngrams { v_inf_score( v, inf ) }




// Прикрепляем вспомогательный глагол в личной форме:
// Ты вынужден будешь отказаться
//             ^^^^^^
pattern СтрадСвязкаВосх
{
 v=СтрадСвязкаВосх{ AUX_VERB_REQUIRED:1 } : export { AUX_VERB_REQUIRED:0 ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 aux=ВспомСтрадГлагол{ =v:РОД =v:ЧИСЛО } : export { РОД ЛИЦО ЧИСЛО ВРЕМЯ } 
}
: links { v.<LEFT_AUX_VERB>aux }






// Предложное дополнение:
// Допрошен он был в отделении полиции
//                 ^^^^^^^^^^^^^^^^^^^
pattern СтрадСвязкаВосх
{
 v=СтрадСвязкаВосх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 pn=ПредлогИСущ{ гл_предл(v,_.prepos,_.n2) }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score(v,pn.prepos)
 ngram3( v, pn.prepos, pn.n2 )
}

// Обособленный атрибут:
// Она была, столь талантливая, принята в группу
//           ^^^^^^^^^^^^^^^^^
pattern СтрадСвязкаВосх
{
 v=СтрадСвязкаВосх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 attr=ОбособленныйАтрибут
} : links { v.<SEPARATE_ATTR>attr }


// Она была, без сомнения, понята слушателями.
//         ^^^^^^^^^^^^^^^
pattern СтрадСвязкаВосх
{
 v=СтрадСвязкаВосх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 attr=ВводнАктант
} : links { v.<BEG_INTRO>attr }


// Уточнитель:
//
// Ситуация исправлена (в необходмой степени)
//                     ^^^^^^^^^^^^^^^^^^^^^^
pattern СтрадСвязкаВосх
{
 v=СтрадСвязкаВосх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 attr=Детализатор
} : links { v.<DETAILS>attr }


// Прямое обращение:
//
// Я был понят, Николай Васильевич, неправильно
//            ^^^^^^^^^^^^^^^^^^^^^
pattern СтрадСвязкаВосх
{
 v=СтрадСвязкаВосх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 x=ПрямоеОбращение
} : links { v.<APPEAL>x }


// ------------------------------------------------------
// Теперь нисходящие правила.

patterns СтрадСвязкаНисх export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }

pattern СтрадСвязкаНисх
{
 СтрадСвязкаВосх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}


// прикрепляем дополнение:
// он был допрошен полицией
//                 ^^^^^^^^
pattern СтрадСвязкаНисх
{
 obj=СтрадПричДополнение
 v=СтрадСвязкаНисх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =ПАДЕЖВАЛ->obj:ПАДЕЖ }
     : export { 
               node:root_node AUX_VERB_REQUIRED ВРЕМЯ РОД ЛИЦО ЧИСЛО МОДАЛЬНЫЙ
               @except(ПАДЕЖВАЛ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
              }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }



pattern СтрадСвязкаНисх
{
 obj=ГлДополнение{ ПАДЕЖ:ВИН }
 v=СтрадСвязкаНисх{ ПричСВинДоп ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН }
     : export { 
               node:root_node AUX_VERB_REQUIRED ВРЕМЯ РОД ЛИЦО ЧИСЛО МОДАЛЬНЫЙ
               @except(ПАДЕЖВАЛ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
              }
}
: links { v.<OBJECT>obj }

// Дательная валентность - разрешаем для всех с большим штрафом:
//
// Ботинки ему малы
//         ^^^
pattern СтрадСвязкаНисх
{
 obj=ГлДополнение{ ПАДЕЖ:ДАТ }
 v=СтрадСвязкаНисх{ ~ПАДЕЖВАЛ:ДАТ }
     : export { 
               node:root_node AUX_VERB_REQUIRED ВРЕМЯ РОД ЛИЦО ЧИСЛО МОДАЛЬНЫЙ
               @except(ПАДЕЖВАЛ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
              }
}
: links { v.<OBJECT>obj }
: ngrams { -5 }

// Глагольное обстоятельство:
// Оно вчера исправлено
//     ^^^^^
pattern СтрадСвязкаНисх
{
 adv=Обст
 v=СтрадСвязкаНисх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score( adv, v ) }


// Инфинитив для модальной страдательной конструкции:
// Мы  уступить ему вынуждены были
//     ^^^^^^^^^^^^
pattern СтрадСвязкаНисх export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) node:root_node }
{
 inf=Инф2
 v=СтрадСвязкаНисх{ МОДАЛЬНЫЙ } : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ node:root_node }
}
: links { v.<INFINITIVE>inf }
: ngrams
{
 -1 // необычный порядок слов
 v_inf_score( v, inf )
}

// Прикрепляем вспомогательный глагол в личной форме
// Я был вынужден отказаться
//       ^^^^^^^^
pattern СтрадСвязкаНисх
{
 aux=ВспомСтрадГлагол : export { ЛИЦО РОД ЧИСЛО ВРЕМЯ } 
 v=СтрадСвязкаНисх{ AUX_VERB_REQUIRED:1 =aux:РОД =aux:ЧИСЛО } : export { AUX_VERB_REQUIRED:0 ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}
: links { v.<LEFT_AUX_VERB>aux }



// Предложное дополнение:
//
// В отделении полиции был допрошен
// ^^^^^^^^^^^^^^^^^^^
pattern СтрадСвязкаНисх
{
 pn=ПредлогИСущ
 v=СтрадСвязкаНисх{ гл_предл(_,pn.prepos,pn.n2) } : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score(v,pn.prepos)
 ngram3( v, pn.prepos, pn.n2 )
}

// Обособленный атрибут:
//
// столь талантливая, была принята в группу
// ^^^^^^^^^^^^^^^^^
pattern СтрадСвязкаНисх
{
 attr=ОбособленныйАтрибут
 v=СтрадСвязкаНисх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<SEPARATE_ATTR>attr }


// была, без сомнения, понята слушателями.
//     ^^^^^^^^^^^^^^^
pattern СтрадСвязкаНисх
{
 attr=ВводнАктант
 v=СтрадСвязкаНисх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<BEG_INTRO>attr }


// Уточнитель:
//
// Ситуация (в необходмой степени) была исправлена 
//          ^^^^^^^^^^^^^^^^^^^^^^
pattern СтрадСвязкаНисх
{
 attr=Детализатор
 v=СтрадСвязкаНисх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<DETAILS>attr }


// Прямое обращение:
//
// Николай Васильевич, была неправильно понята!
// ^^^^^^^^^^^^^^^^^^^
pattern СтрадСвязкаНисх
{
 x=ПрямоеОбращение
 v=СтрадСвязкаНисх : export { AUX_VERB_REQUIRED ВРЕМЯ ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<APPEAL>x }

// +++++++++++++++++++++++++++++

patterns СтрадПрич export { node:root_node }
pattern СтрадПрич
{
 v=СтрадСвязкаНисх : export { node:root_node }
} : ngrams { ВалентностьГлагола(v) } 


// +++++++++++++++++++++++++++++



// +++++++++++++++++++++++++++++

tree_scorers ВалентностьСвязки

// Давим попытки трактовать некоторые формы как полноценное именное сказуемое:
//
// Пело жалобно, печально
//               ~~~~~~~~
// изготавливает быстро, точно, дешево
//                       ^^^^^^^^^^^^^
tree_scorer ВалентностьСвязки language=Russian generic
{
 if context { прилагательное:*{ род:ср число:ед }.[not]<SUBJECT>*:*{ падеж:им род:ср } }
  then -4
}


// Немного понизим достоверность остальных вариантов связки без подлежащего,
// чтобы оторвавшаяся группа именного сказуемого была наказана:
//
// он был и быстр, и силён
//        ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьСвязки language=Russian generic
{
 if context { прилагательное:*{ ~род:ср }.[not]<SUBJECT>*:*{ падеж:им } }
  then -2
}


// Большие отели
tree_scorer ВалентностьСвязки language=Russian
{
 if context { прилагательное:больший{ падеж:им } }
  then -10
}



tree_scorers ОбъектКомпаратива

tree_scorer ОбъектКомпаратива language=Russian
{
 if context { местоим_сущ:кто{} }
  then 1
}

tree_scorer ОбъектКомпаратива language=Russian
{
 if context { местоимение:*{} }
  then 1
}


tree_scorer ОбъектКомпаратива language=Russian
{
 if context { существительное:*{} }
  then 1
}

// Бывает и хуже.
//        ^^^^^^
tree_scorer ВалентностьСвязки language=Russian generic
{
 if context { прилагательное:*{ СТЕПЕНЬ:СРАВН }.[not]ОбъектКомпаратива }
  then -4
}


// +++++++++++++++++++++++++++++

// Страдательное причастие в роли именного сказуемого:
pattern Сказуемое0
{
 v=СтрадСвязкаНисх : export { ЛИЦО ЧИСЛО РОД ВРЕМЯ node:root_node }
}
: ngrams
{
 ВалентностьСвязки(v)
 ВалентностьГлагола(v)
}


// =======================================================================
// Полный предикат - конструкции со страдательным причастием и подлежащим:
//
// Мы поражены эффектом
//
// =======================================================================

patterns СтрадСказВосх { bottomup }
export
{
 THEMA_VALENCY
 AUX_VERB_REQUIRED
 KEYFEATURE_DETECTED // если составной вспомогательный глагол, то станет=1, например в "Можешь быть уверен"
 KEYFEATURE_REQUIRED // если прикреплен модальный глагол для инфинитива БЫТЬ
 ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ
 node:root_node
}

pattern СтрадСказВосх export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED (ЛИЦО) ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
{
 СтрадПрич1 : export {
                      THEMA_VALENCY:1 // подлежащее необходимо и еще не подцеплено
                      AUX_VERB_REQUIRED:1 // вспомогательный глагол может быть, но не обязателен
                      KEYFEATURE_DETECTED:0
                      KEYFEATURE_REQUIRED:0
                      ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node
                     }
}

// я удивлен, что вы еще работаете!
pattern СтрадСказВосх export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД (ПАДЕЖВАЛ) (ПЕРЕХОДНОСТЬ) (МОДАЛЬНЫЙ) node:root_node }
{
 v=СтрадСказВосх : export { AUX_VERB_REQUIRED THEMA_VALENCY KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД node:root_node }
 comma1=','
 conj=союз:что{}
 p=ПридаточноеВОбороте
 comma2=@coalesce(',')
} : links
{
 v.<SUBORDINATE_CLAUSE>comma1.
    <NEXT_COLLOCATION_ITEM>conj.
    <NEXT_COLLOCATION_ITEM>p.
     ~<PUNCTUATION>comma2
}


// Подлежащее справа:
//
// В лесу было поймано оно
//                     ^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх{ THEMA_VALENCY:1 } : export { THEMA_VALENCY:0 AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 sbj=Подлежащее{ =v:РОД =v:ЧИСЛО =v:ЛИЦО }
}
: links { v.<SUBJECT>sbj }



// прикрепляем дополнение:
// он был допрошен полицией
//                 ^^^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ } : export { node:root_node THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД МОДАЛЬНЫЙ }
 obj=СтрадПричДополнение{ =ПАДЕЖ->v:ПАДЕЖВАЛ } : export {
                                                  @except(v:ПАДЕЖВАЛ,ПАДЕЖ)
                                                  @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
                                                 }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) } // ??? нужно также пробовать sbj_verb!!! ПОЛИЦИЯ ДОПРАСИЛА = ДОПРОШЕН ПОЛИЦИЕЙ



// Дательная валентность для всех с большим штрафом:
// Ботинки малы ему
//              ^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх{ ~ПАДЕЖВАЛ:ДАТ } : export { node:root_node THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД МОДАЛЬНЫЙ }
 obj=СтрадПричДополнение{ ПАДЕЖ:ДАТ } : export {
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




pattern СтрадСказВосх
{
 v=СтрадСказВосх{ ПричСВинДоп ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН } : export { node:root_node THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД МОДАЛЬНЫЙ }
 obj=ГлДополнение{ ПАДЕЖ:ВИН } : export {
                                         @except(v:ПАДЕЖВАЛ,ПАДЕЖ)
                                         @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖВАЛ)
                                        }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }



// Глагольное обстоятельство:
// Оно было исправлено вчера
//                     ^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 adv=Обст
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score( adv, v ) }


// Инфинитив для модальной страдательной конструкции:
// Мы вынуждены были уступить ему
//                   ^^^^^^^^^^^^
pattern СтрадСказВосх export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) node:root_node }
{
 v=СтрадСказВосх{ МОДАЛЬНЫЙ }  : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ node:root_node }
 inf=Инф2
}
: links { v.<INFINITIVE>inf }
: ngrams { v_inf_score( v, inf ) }

// Инфинитив может прикрепляться к немодальному сказуемому:
// Они воспитаны погибать.
pattern СтрадСказВосх export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) node:root_node }
{
 v=СтрадСказВосх{ ~МОДАЛЬНЫЙ }  : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ node:root_node }
 inf=Инф2
}
: links { v.<INFINITIVE>inf }
: ngrams
{
 -4
 v_inf_score( v, inf )
}



// Прикрепляем вспомогательный глагол в личной форме
// Ты вынужден будешь отказаться
//             ^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх{ AUX_VERB_REQUIRED:1 KEYFEATURE_DETECTED:0 } : export { THEMA_VALENCY AUX_VERB_REQUIRED:0 KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 aux=ВспомСтрадГлагол{ =v:РОД =v:ЧИСЛО } : export { ЛИЦО ЧИСЛО РОД } 
}
: links { v.<LEFT_AUX_VERB>aux }



// Могу ли я уверен быть?
//                  ^^^^
pattern СтрадСказВосх export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED (ЛИЦО) (ЧИСЛО) (РОД) ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) node:root_node }
{
 v=СтрадСказВосх{ /*AUX_VERB_REQUIRED:1*/ KEYFEATURE_DETECTED:0 } : export { THEMA_VALENCY AUX_VERB_REQUIRED:0 KEYFEATURE_REQUIRED KEYFEATURE_DETECTED:1 ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 aux=инфинитив:быть{}
}
: ngrams { -2 }
: links { v.<LEFT_AUX_VERB>aux }


// Быть уверен я могу?
//               ^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх{ KEYFEATURE_REQUIRED:0 } : export { THEMA_VALENCY AUX_VERB_REQUIRED:0 KEYFEATURE_DETECTED ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 aux=Гл0{ МОДАЛЬНЫЙ =v:РОД =v:ЧИСЛО } : export { KEYFEATURE_REQUIRED:1 ЛИЦО ЧИСЛО РОД }
}
: ngrams { -1 }
: links { v.<LEFT_AUX_VERB>aux }











// Предложное дополнение:
// Допрошен он был в отделении полиции
//                 ^^^^^^^^^^^^^^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 pn=ПредлогИСущ{ гл_предл(v,_.prepos,_.n2) }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score(v,pn.prepos)
 ngram3( v, pn.prepos, pn.n2 )
}

// Обособленный атрибут:
// Она была, столь талантливая, принята в группу
//           ^^^^^^^^^^^^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 attr=ОбособленныйАтрибут
} : links { v.<SEPARATE_ATTR>attr }


// Она была, без сомнения, понята слушателями.
//         ^^^^^^^^^^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 attr=ВводнАктант
} : links { v.<BEG_INTRO>attr }


// Уточнитель:
//
// Ситуация исправлена (в необходмой степени)
//                     ^^^^^^^^^^^^^^^^^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 attr=Детализатор
} : links { v.<DETAILS>attr }


// Прямое обращение:
//
// Я был понят, Николай Васильевич, неправильно
//            ^^^^^^^^^^^^^^^^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 x=ПрямоеОбращение
} : links { v.<APPEAL>x }

// ----------------------------------------------------------

// Союзные конструкции - объединение нескольких страдательных причастий:
// TODO: переделать на восходящий разбор!
//
// Она была удивлена, польщена и смущена.
//          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 comma=','
 v2=СтрадСвязкаНисх{ =v:РОД =v:ЧИСЛО =v:ЛИЦО }
} : links { v.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>v2 }

// Она была удивлена и польщена
//                   ^^^^^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 conj=ЛогичСоюз2
 v2=СтрадСвязкаНисх{ =v:РОД =v:ЧИСЛО =v:ЛИЦО }
} : links { v.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }

// Она была смущена, но немного польщена.
//                 ^^^^^^^^^^^^^^^^^^^^^
pattern СтрадСказВосх
{
 v=СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 comma=','
 conj=ПротивитСоюз
 v2=СтрадСвязкаНисх{ =v:РОД =v:ЧИСЛО =v:ЛИЦО }
} : links
{
 v.<RIGHT_LOGIC_ITEM>comma.
   <NEXT_COLLOCATION_ITEM>conj.
    <NEXT_COLLOCATION_ITEM>v2
}


// ------------------------------------------------------
// Теперь нисходящие правила.

patterns СтрадСказНисх
export
{
 THEMA_VALENCY
 AUX_VERB_REQUIRED // прикреплен ли вспомогательный связочный глагол
 KEYFEATURE_REQUIRED // если прикреплен модальный глагол для инфинитива БЫТЬ
 KEYFEATURE_DETECTED // если составной вспомогательный глагол, то станет=1, например в "Можешь быть уверен"
 ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ
 node:root_node
}

pattern СтрадСказНисх
{
 СтрадСказВосх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}

// Подлежащее слева:
// Она была смущена
// ^^^
pattern СтрадСказНисх
{
 sbj=Подлежащее: export { ЛИЦО РОД ЧИСЛО }
 v=СтрадСказНисх{ THEMA_VALENCY:1 =sbj:РОД =sbj:ЧИСЛО =sbj:ЛИЦО } : export { THEMA_VALENCY:0 AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<SUBJECT>sbj }


// Никакой серьезной техники обнаружено не было.
//                                      ^^^^^^^
// Вообще, надо выставлять и пробрасывать по цепочке специальный флаг "отрицание" для НЕ БЫЛО.
// Но пока попробуем обойтись без больших переделок.
pattern СтрадСказНисх
{
 sbj=ГлДополнение{ ПАДЕЖ:РОД } : export { ЛИЦО РОД ЧИСЛО }
 v=СтрадСказНисх{ THEMA_VALENCY:1 РОД:СР ЧИСЛО:ЕД } : export { THEMA_VALENCY:0 AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<SUBJECT>sbj }
: ngrams { -1 }





// прикрепляем дополнение:
// он был допрошен полицией
//                 ^^^^^^^^
pattern СтрадСказНисх
{
 obj=СтрадПричДополнение
 v=СтрадСказНисх{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =ПАДЕЖВАЛ->obj:ПАДЕЖ }
     : export {
               node:root_node THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED РОД ЛИЦО ЧИСЛО МОДАЛЬНЫЙ
               @except(ПАДЕЖВАЛ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }



// Дательное дополнение может прикрепляться даже без свободной
// дательной валентности у предиката:
//
// Но поликлиникам работа будет оплачена.
//    ^^^^^^^^^^^^              ^^^^^^^^
pattern СтрадСказНисх
{
 obj=СтрадПричДополнение{ ПАДЕЖ:ДАТ }
 v=СтрадСказНисх{ ~ПАДЕЖВАЛ:ДАТ }
     : export {
               node:root_node THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED РОД ЛИЦО ЧИСЛО МОДАЛЬНЫЙ
               ПАДЕЖВАЛ
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
}
: links { v.<OBJECT>obj }
: ngrams
{
 -5
 v_obj_score(v,obj)
}





pattern СтрадСказНисх
{
 obj=ГлДополнение{ ПАДЕЖ:ВИН }
 v=СтрадСказНисх{ ПричСВинДоп ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ВИН }
     : export {
               node:root_node THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED РОД ЛИЦО ЧИСЛО МОДАЛЬНЫЙ
               @except(ПАДЕЖВАЛ,obj:ПАДЕЖ)
               @if_exported(ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ,ПАДЕЖ)
              }
}
: links { v.<OBJECT>obj }
: ngrams { v_obj_score(v,obj) }

// Глагольное обстоятельство:
// Оно вчера исправлено
//     ^^^^^
pattern СтрадСказНисх
{
 adv=Обст
 v=СтрадСказНисх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score( adv, v ) }


// Инфинитив для модальной страдательной конструкции:
// Мы  уступить ему вынуждены были
//     ^^^^^^^^^^^^
pattern СтрадСказНисх export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) node:root_node }
{
 inf=Инф2
 v=СтрадСказНисх{ МОДАЛЬНЫЙ }  : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ node:root_node }
}
: links { v.<INFINITIVE>inf }
: ngrams
{
 -1 // необычный порядок слов
 v_inf_score( v, inf )
}

// Прикрепляем вспомогательный глагол в личной форме:
//
// Я был вынужден отказаться
//   ^^^
pattern СтрадСказНисх
{
 aux=ВспомСтрадГлагол : export { ЛИЦО РОД ЧИСЛО } 
 v=СтрадСказНисх{ /*AUX_VERB_REQUIRED:1 =aux:РОД =aux:ЧИСЛО*/ } : export { THEMA_VALENCY AUX_VERB_REQUIRED:0 KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}
: links { v.<LEFT_AUX_VERB>aux }


// Вспомогательный глагол может быть представлен сочетанием
// инфинитива БЫТЬ и еще одного вспомогательного глагола:
//
// Можешь быть уверен
//        ^^^^^
pattern СтрадСказНисх export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED (ЛИЦО) (ЧИСЛО) (РОД) ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ (МОДАЛЬНЫЙ) node:root_node }
{
 aux=инфинитив:быть{} : export { KEYFEATURE_DETECTED:1 }
 v=СтрадСказНисх{ /*AUX_VERB_REQUIRED:1*/ KEYFEATURE_DETECTED:0 =aux:РОД =aux:ЧИСЛО } : export { THEMA_VALENCY AUX_VERB_REQUIRED:0 KEYFEATURE_REQUIRED ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}
: links { v.<LEFT_AUX_VERB>aux }


// Можешь быть уверен
// ^^^^^^
pattern СтрадСказНисх
{
 aux=Гл0{ МОДАЛЬНЫЙ } : export { KEYFEATURE_REQUIRED:1 ЛИЦО ЧИСЛО РОД }
 v=СтрадСказНисх{ =aux:РОД =aux:ЧИСЛО } : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}
: links { v.<LEFT_AUX_VERB>aux }








// Индуцированная валентность:
// Будь любезен заглянуть в мою спальню.
pattern СтрадСказНисх
{
 aux=ВспомСтрадГлагол : export { ЛИЦО РОД ЧИСЛО } 
 v=СтрадСказНисх{ AUX_VERB_REQUIRED:1 ~МОДАЛЬНЫЙ =aux:РОД =aux:ЧИСЛО } : export { THEMA_VALENCY AUX_VERB_REQUIRED:0 KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
 inf=Инф2
}
: ngrams { -1 }
: links
{
 v.{
    <LEFT_AUX_VERB>aux
    <INFINITIVE>inf
   }
}



// Предложное дополнение:
//
// В отделении полиции был допрошен
// ^^^^^^^^^^^^^^^^^^^
pattern СтрадСказНисх
{
 pn=ПредлогИСущ
 v=СтрадСказНисх{ гл_предл(_,pn.prepos,pn.n2) } : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score(v,pn.prepos)
 ngram3( v, pn.prepos, pn.n2 )
}

// Обособленный атрибут:
//
// столь талантливая, была принята в группу
// ^^^^^^^^^^^^^^^^^
pattern СтрадСказНисх
{
 attr=ОбособленныйАтрибут
 v=СтрадСказНисх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<SEPARATE_ATTR>attr }


// была, без сомнения, понята слушателями.
//     ^^^^^^^^^^^^^^^
pattern СтрадСказНисх
{
 attr=ВводнАктант
 v=СтрадСказНисх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<BEG_INTRO>attr }


// Уточнитель:
//
// Ситуация (в необходмой степени) была исправлена 
//          ^^^^^^^^^^^^^^^^^^^^^^
pattern СтрадСказНисх
{
 attr=Детализатор
 v=СтрадСказНисх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<DETAILS>attr }


// Прямое обращение:
//
// Николай Васильевич, была неправильно понята!
// ^^^^^^^^^^^^^^^^^^^
pattern СтрадСказНисх
{
 x=ПрямоеОбращение
 v=СтрадСказНисх : export { THEMA_VALENCY AUX_VERB_REQUIRED KEYFEATURE_DETECTED KEYFEATURE_REQUIRED ЛИЦО ЧИСЛО РОД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ МОДАЛЬНЫЙ node:root_node }
} : links { v.<APPEAL>x }



// -----------------------------------

// Ну, будь готов!
//     ^^^^^^^^^^
pattern ПредикатСвязка
{
 v=СтрадСказНисх{ KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED:0 [-1]THEMA_VALENCY:0 } : export { node:root_node }
}
: ngrams
{
 ВалентностьСвязки(v)
 ВалентностьГлагола(v)
 ВалентностьПредиката(v)
}


// ты должна быть уверена
pattern ПредикатСвязка
{
 v=СтрадСказНисх{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:1 [-1]THEMA_VALENCY:0 } : export { node:root_node }
}
: ngrams
{
 ВалентностьСвязки(v)
 ВалентностьГлагола(v)
 ВалентностьПредиката(v)
}




// Свободный слот подлежащего
pattern Сказуемое0
{
 v=СтрадСказНисх{ KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED:0 THEMA_VALENCY:1 }:export { РОД ЧИСЛО ЛИЦО:3 ВРЕМЯ:НАСТОЯЩЕЕ node:root_node }
}
: ngrams
{
 ВалентностьСвязки(v)
 ВалентностьГлагола(v)
}


pattern Сказуемое0
{
 v=СтрадСказНисх{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:1 THEMA_VALENCY:1 }:export { РОД ЧИСЛО ЛИЦО:3 ВРЕМЯ:НАСТОЯЩЕЕ node:root_node }
}
: ngrams
{
 ВалентностьСвязки(v)
 ВалентностьГлагола(v)
}





// --------------------------------

// ==============================================
// Модальные прилагательные управляют инфинитивом
// ==============================================

patterns МодалПрил export { РОД ЧИСЛО node:root_node }

// ты должен остановиться
pattern МодалПрил
{
 прилагательное:*{ МОДАЛЬНЫЙ КРАТКИЙ } : export { РОД ЧИСЛО node:root_node }
}

// вы должны бы это знать
//    ^^^^^^^^^
pattern МодалПрил
{
 a=прилагательное:*{ МОДАЛЬНЫЙ КРАТКИЙ } : export { РОД ЧИСЛО node:root_node }
 p=частица:бы{}
} : links { a.<POSTFIX_PARTICLE>p }


pattern МодалПрил
{
 a=прилагательное:*{ МОДАЛЬНЫЙ КРАТКИЙ } : export { РОД ЧИСЛО node:root_node }
 p=частица:ли{}
} : links { a.<POSTFIX_PARTICLE>p }

// ты не должен спать
pattern МодалПрил
{
 n=частица:не{}
 a=прилагательное:*{ МОДАЛЬНЫЙ КРАТКИЙ } : export { РОД ЧИСЛО node:root_node }
} : links { a.<NEGATION_PARTICLE>n }

// ++++

// решение должен принять мой начальник!
pattern НеполнСвязка export { node:root_node РОД ЧИСЛО (ЛИЦО) ВРЕМЯ }
{
 obj=ГлДополнение
 v=МодалПрил : export { node:root_node РОД ЧИСЛО ВРЕМЯ:НАСТОЯЩЕЕ }
 inf=Инф2БезДоп{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =obj:ПАДЕЖ }
} : links
{
 v.<INFINITIVE>inf.<OBJECT>obj
}

// мне ты должен подчиняться!
pattern ГлПредикат
{
 obj=ГлДополнение
 N=Подлежащее
 v=МодалПрил{ =n:РОД =n:ЧИСЛО } : export { node:root_node }
 inf=Инф2БезДоп{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =obj:ПАДЕЖ }
} : links
{
 v.{
    <SUBJECT>n
    <INFINITIVE>inf.<OBJECT>obj
   }
}

// ты их должен уничтожить
pattern НеполнСвязка export { node:root_node РОД ЧИСЛО (ЛИЦО) ВРЕМЯ }
{
 obj=ГлДополнение
 v=МодалПрил : export { node:root_node РОД ЧИСЛО ВРЕМЯ:ПРОШЕДШЕЕ }
 inf=Инф2БезДоп{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =obj:ПАДЕЖ }
} : links
{
 v.{
    <INFINITIVE>inf.<OBJECT>obj
   }
}

// у него должны быть инструменты
pattern НеполнСвязка export { node:root_node РОД ЧИСЛО (ЛИЦО) ВРЕМЯ }
{
 pn=ПредлогИСущ
 v=МодалПрил : export { node:root_node РОД ЧИСЛО ВРЕМЯ:НАСТОЯЩЕЕ }
 inf=Инф2БезДоп{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ }
} : links
{
 v.<INFINITIVE>inf.<PREPOS_ADJUNCT>pn
}


// ???
// второй забег он должен пропустить
pattern ГлПредикат
{
 obj=ГлДополнение{ПАДЕЖ:ВИН}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }
 adv2=@optional(Обст)
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}




// вторую пару он должен отдать девушке левой рукой
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ВИН}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ ПАДЕЖ:ТВОР }
 adv2=@optional(Обст)
 obj2=ГлДополнение{ПАДЕЖ:ДАТ}
 obj3=ГлДополнение{ПАДЕЖ:ТВОР}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     <OBJECT>obj3
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}


// вторую пару он должен отдать левой рукой девушке
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ВИН}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ ПАДЕЖ:ТВОР }
 adv2=@optional(Обст)
 obj2=ГлДополнение{ПАДЕЖ:ТВОР}
 obj3=ГлДополнение{ПАДЕЖ:ДАТ}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     <OBJECT>obj3
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}


// левой рукой он должен отдать вторую пару девушке
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ТВОР}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ ПАДЕЖ:ТВОР }
 adv2=@optional(Обст)
 obj2=ГлДополнение{ПАДЕЖ:ВИН}
 obj3=ГлДополнение{ПАДЕЖ:ДАТ}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     <OBJECT>obj3
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}


// левой рукой он должен отдать девушке вторую пару
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ТВОР}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ ПАДЕЖ:ТВОР }
 adv2=@optional(Обст)
 obj2=ГлДополнение{ПАДЕЖ:ДАТ}
 obj3=ГлДополнение{ПАДЕЖ:ВИН}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     <OBJECT>obj3
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}


// левой рукой девушке он должен отдать вторую пару
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ТВОР}
 obj2=ГлДополнение{ПАДЕЖ:ДАТ}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ ПАДЕЖ:ТВОР }
 adv2=@optional(Обст)
 obj3=ГлДополнение{ПАДЕЖ:ВИН}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     <OBJECT>obj3
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}


// первой девушке левой рукой он должен отдать вторую пару
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ДАТ}
 obj2=ГлДополнение{ПАДЕЖ:ТВОР}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ ПАДЕЖ:ТВОР }
 adv2=@optional(Обст)
 obj3=ГлДополнение{ПАДЕЖ:ВИН}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     <OBJECT>obj3
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}



// вторую пару он должен протянуть девушке
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ВИН}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ }
 adv2=@optional(Обст)
 obj2=ГлДополнение{ПАДЕЖ:ДАТ}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}


// второй меч он должен взять левой рукой
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ВИН}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ТВОР }
 adv2=@optional(Обст)
 obj2=ГлДополнение{ПАДЕЖ:ТВОР}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}


// левой рукой он должен взять второй меч
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ТВОР}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ТВОР }
 adv2=@optional(Обст)
 obj2=ГлДополнение{ПАДЕЖ:ВИН}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}

// девушке он должен протянуть вторую пару
pattern ГлПредикат
{
 obj1=ГлДополнение{ПАДЕЖ:ДАТ}
 sbj=Подлежащее
 v=МодалПрил{ =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ПАДЕЖ:ДАТ }
 adv2=@optional(Обст)
 obj2=ГлДополнение{ПАДЕЖ:ВИН}
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.{
                     <OBJECT>obj1
                     <OBJECT>obj2
                     ~<ATTRIBUTE>adv2
                    }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}

// Директором должен быть инженер.
pattern ГлПредикат
{
 obj=ГлДополнение{ПАДЕЖ:ТВОР}
 v=МодалПрил : export { node:root_node }
 inf=инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ТВОР }
 sbj=Подлежащее{ =v:РОД =v:ЧИСЛО }
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf.<OBJECT>obj
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьГлагола(inf)
 ВалентностьПредиката(v)
}



// ----------------------------

patterns МодальнКраткПрил export { node:root_node РОД ЧИСЛО }

pattern МодальнКраткПрил
{
 прилагательное:*{ МОДАЛЬНЫЙ КРАТКИЙ } : export { node:root_node РОД ЧИСЛО }
}

// ведь должны были сразу привести ее сюда.
// ^^^^^^^^^^^
pattern МодальнКраткПрил
{
 adv=Обст{ ~CannotAdvModifAdj }
 a=прилагательное:*{ МОДАЛЬНЫЙ КРАТКИЙ } : export { node:root_node РОД ЧИСЛО }
} : links { a.<ATTRIBUTE>adv }



// их должны были приготовить для меня.
pattern НеполнСвязка
{
 obj=ГлДополнение
 a=МодальнКраткПрил : export { node:root_node РОД ЧИСЛО }
 V=ВспомСтрадГлагол{ =a:РОД =a:ЧИСЛО } : export { ЛИЦО ВРЕМЯ }
 inf=Инф2БезДоп{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =obj:ПАДЕЖ }
} : links
{
 a.{
    <LEFT_AUX_VERB>v
    <INFINITIVE>inf.<OBJECT>obj
   }
}
: ngrams
{
 -1
 ВалентностьГлагола(v)
}

/*
// ведь ты нужен был там!
//         ^^^^^^^^^^^^^^
pattern НеполнСвязка
{
 a=КраткПрилРема
 V=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ =a:РОД =a:ЧИСЛО } : export { node:root_node РОД ЧИСЛО ЛИЦО ВРЕМЯ }
 adv=Обст
} : links
{
 a.{
    <LEFT_AUX_VERB>v
    <ATTRIBUTE>adv
   }
}
: ngrams
{
 -1
 ВалентностьГлагола(v)
}
*/

/*
// убить готов был временами
pattern НеполнСвязка
{
 inf=Инф2
 a=МодальнКраткПрил
 V=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ =a:РОД =a:ЧИСЛО } : export { node:root_node РОД ЧИСЛО ЛИЦО ВРЕМЯ }
 adv=Обст
} : links
{
 v.{
    <RHEMA>a.<INFINITIVE>inf
    <ATTRIBUTE>adv
   }
}
: ngrams
{
 -2
}


// был готов убивать
pattern НеполнСвязка
{
 V=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node РОД ЧИСЛО ЛИЦО ВРЕМЯ }
 a=МодальнКраткПрил { =v:РОД =v:ЧИСЛО }
 inf=Инф2
} : links
{
 v.<RHEMA>a.<INFINITIVE>inf
}
: ngrams
{
 ВалентностьГлагола(v)
}


// рад был вам помочь
pattern НеполнСвязка
{
 a=МодальнКраткПрил
 V=Связка{ =a:РОД =a:ЧИСЛО ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node РОД ЧИСЛО ЛИЦО ВРЕМЯ }
 inf=Инф2
} : links
{
 v.<RHEMA>a.<INFINITIVE>inf
}
: ngrams
{
 ВалентностьГлагола(v)
}
*/


// его возраст невозможно было определить
pattern НеполнСвязка
{
 obj=ГлДополнение
 a=КраткПрилРема{ РОД:СР ЧИСЛО:ЕД } : export { node:root_node РОД ЧИСЛО }
 V='было'{ class:ГЛАГОЛ } : export { ЛИЦО ВРЕМЯ }
 inf=Инф2БезДоп{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =obj:ПАДЕЖ }
} : links
{
 a.{
    <LEFT_AUX_VERB>v
    <INFINITIVE>inf.<OBJECT>obj
   }
}
: ngrams
{
 ВалентностьГлагола(inf)
 ВалентностьГлагола(v)
}

// издалека ее легко было принять за мальчика
pattern НеполнСвязка
{
 adv=Обст
 obj=ГлДополнение
 a=КраткПрилРема{ РОД:СР ЧИСЛО:ЕД } : export { node:root_node РОД ЧИСЛО }
 V='было'{ class:ГЛАГОЛ } : export { ЛИЦО ВРЕМЯ }
 inf=Инф2БезДоп{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ =obj:ПАДЕЖ }
} : links
{
 a.{
    <LEFT_AUX_VERB>v
    <ATTRIBUTE>adv
    <INFINITIVE>inf.<OBJECT>obj
   }
}
: ngrams
{
 adv_verb_score(adv,v)
 ВалентностьГлагола(inf)
 ВалентностьГлагола(v)
}

