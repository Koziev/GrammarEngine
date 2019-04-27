// Правила для русского синтаксического парсера
// LC->04.09.2014

#pragma floating off

#define _BEG beth:begin{}
#define _END beth:end{}

#define _запятая ','

patterns ПрямоеОбращение export { node:root_node }

// объявление для паттернов группы существительного с логическими конструкциями.
patterns ГруппаСущ4 export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }

patterns Предлож1 export { node:root_node }
patterns НеполнПредлож export { node:root_node }
patterns Предикат export { node:root_node }
 
wordentry_set СторонаСвета = существительное:{ юг, север, восток, запад }



// ----------------------------------------------------------------



wordentry_set ЧастицаЖе = { частица:же{}, частица:ж{} }
wordentry_set ЧастицаЖеУж=частица:{ же, ж, уж }

patterns ЭтоКакЧастица export { node:root_node }

// это вы во всем виноваты
// ^^^
pattern ЭтоКакЧастица
{
 частица:это{} : export { node:root_node }
}

// это же нечисть вытащила их из пожара!
// ^^^^^^
pattern ЭтоКакЧастица
{
 p=частица:это{} /*местоим_сущ:это{ падеж:им }*/ : export { node:root_node }
 x=ЧастицаЖе
} : links { p.<POSTFIX_PARTICLE>x }


// +++++++++++++++++++++++++++++++++++++++++++++++++++++


patterns ГруппаНареч1 export { node:root_node ТИП_МОДИФ }




// ---------------------------------------------------

// ######################
// СУПЕРЛАТИВ.
// ######################

// Может выступать в роли обычного атрибутирующего или предикативного прилагательного.
// Но может также присоединять предложное дополнение, то есть напоминает по синтаксической роли причастие.
patterns Суперлатив0 export { node:root_node РОД ЧИСЛО ПАДЕЖ ОДУШ }


// Ленивейший кот
// ^^^^^^^^^^
pattern Суперлатив0
{
 прилагательное:*{ степень:превосх } : export { node:root_node число род ПАДЕЖ ОДУШ }
}

// Аналитическая форма суперлатива - с вспомогательным прилагательным САМЫЙ:
// Мой кот - самый ленивый из всех котов
//           ^^^^^^^^^^^^^
pattern Суперлатив0
{
 a1=прилагательное:самый{}
 a2=прилагательное:*{ степень:атриб ~краткий =a1:падеж =a1:род =a1:число } : export { node:root_node число род падеж ОДУШ }
}
: ngrams { 2 }
: links { a2.<ATTRIBUTE>a1 }

// Это будет самое лучшее
//           ^^^^^^^^^^^^
pattern Суперлатив0
{
 a1=прилагательное:самый{}
 a2=прилагательное:хороший{ степень:превосх =a1:падеж =a1:род =a1:число } : export { node:root_node число род падеж ОДУШ }
}
: ngrams { 2 }
: links { a2.<ATTRIBUTE>a1 }


// И это было самое худшее.
//            ^^^^^^^^^^^^
pattern Суперлатив0
{
 a1=прилагательное:самый{}
 a2=прилагательное:плохой{ степень:превосх =a1:падеж =a1:род =a1:число } : export { node:root_node число род падеж ОДУШ }
}
: ngrams { 2 }
: links { a2.<ATTRIBUTE>a1 }


// Разрешим сочетать модификатор САМЫЙ с суперлативом.
pattern Суперлатив0
{
 a1=прилагательное:самый{}
 a2=прилагательное:*{ степень:превосх =a1:падеж =a1:род =a1:число } : export { node:root_node число род падеж ОДУШ }
}
: ngrams { -2 }
: links { a2.<ATTRIBUTE>a1 }



// Аналитическая форма суперлатива с вспомогательным "оценочным" наречием
// Мой кот - наиболее крупный из представленных
//           ^^^^^^^^^^^^^^^^
wordform_set СуперлативНареч=
{
 'наиболее'{ class:наречие степень:превосх },
 'наименее'{ class:наречие степень:превосх },
 максимально{ class:наречие },
 минимально{ class:наречие }
}

pattern Суперлатив0
{
 a1=СуперлативНареч
 a2=прилагательное:*{ степень:атриб ~краткий } : export { node:root_node число род падеж ОДУШ }
} : links { a2.<ATTRIBUTE>a1 }

// Отрицательная форма с вспомогательным прилагательным САМЫЙ
// не самый крупный из всех
// ^^^^^^^^^^^^^^^^
pattern Суперлатив0
{
 n=частица:не{}
 a1=прилагательное:самый{}
 a2=прилагательное:*{ степень:атриб ~краткий =a1:падеж =a1:род =a1:число } : export { node:root_node число род падеж ОДУШ }
} : links { a2.<ATTRIBUTE>a1.<NEGATION_PARTICLE>n }


// -----------------------------------------------------------
// Суперлатив допускает присоединение предложного дополнения:
// -----------------------------------------------------------

patterns СуперлативСПредлДоп export { node:root_node РОД ЧИСЛО ПАДЕЖ ОДУШ }

pattern СуперлативСПредлДоп
{
 Суперлатив0 : export { node:root_node число род падеж одуш }
}


patterns ПредлогИСущ { language=Russian } export { node:prepos node:n2 node:root_node }

// самый крупный из всех
//               ^^^^^^^
pattern СуперлативСПредлДоп
{
 a=Суперлатив0 : export { node:root_node число род падеж одуш }
 pn=ПредлогИСущ
} : links { a.<PREPOS_ADJUNCT>pn }



//------------------------------------------------------



wordentry_set УсилитНаречие0={ наречие:именно{}, наречие:только{}, наречие:лишь{} }

patterns УсилитНаречие export { node:root_node }

pattern УсилитНаречие
{
 ГруппаНареч1{УсилитНаречие0}:export { node:root_node }
}


// -----------------------------------------------------------------


patterns Обст { language=Russian } export { node:root_node }


// -------------------------------------------------------

tree_scorers ВалентностьГлагола
tree_scorers ВалентностьПредиката

// -------------------------------------------

patterns ПостфиксПрилСамОбъект export { node:root_node }

wordentry_set ПостфиксПрилСамОбъект0={
 частица:же{},
 частица:бы{},
 частица:ли{}
}

// На него на самого же показываешь?
//            ^^^^^^^^^
pattern ПостфиксПрилСамОбъект
{
 ПостфиксПрилСамОбъект0 : export { node:root_node }
}

// С самим-то справишься?
//   ^^^^^^^^
pattern ПостфиксПрилСамОбъект
{
 t='-' : export { node:root_node }
 p=частица:то{}
} : links { t.<NEXT_COLLOCATION_ITEM>p }

// На самого-ка напади!
//    ^^^^^^^^^
pattern ПостфиксПрилСамОбъект
{
 t='-' : export { node:root_node }
 p=частица:ка{}
} : links { t.<NEXT_COLLOCATION_ITEM>p }

// ----------------------------------------------------------

patterns ПрилСамОбъект export { ПАДЕЖ ЧИСЛО РОД node:root_node }

pattern ПрилСамОбъект
{
 a=прилагательное:сам{} : export { ПАДЕЖ ЧИСЛО РОД node:root_node }
}


// На самого-ка напади!
//    ^^^^^^^^^
pattern ПрилСамОбъект
{
 a=прилагательное:сам{} : export { ПАДЕЖ ЧИСЛО РОД node:root_node }
 p=ПостфиксПрилСамОбъект
} : links { a.<POSTFIX_PARTICLE>p }


// Не сам проверял?
// ^^^^^^
pattern ПрилСамОбъект
{
 p=частица:не{}
 a=ПрилСамОбъект : export { ПАДЕЖ ЧИСЛО РОД node:root_node }
} : links { a.<NEGATION_PARTICLE>p }

// Он и сам-то испугался
//    ^^^^^^^^
pattern ПрилСамОбъект
{
 p=частица:и{}
 a=ПрилСамОбъект : export { ПАДЕЖ ЧИСЛО РОД node:root_node }
} : links { a.<PREFIX_PARTICLE>p }


// ***********************************************
// Конструкция выступает в роли обстоятельства
// ***********************************************
patterns ОбстИнфСоюз export { node:root_node }

// перед тем как
pattern ОбстИнфСоюз
{
 prep=предлог:перед{} : export { node:root_node }
 n=местоим_сущ:то{ падеж:твор }
 conj='как'
} : links
{
 prep.<OBJECT>n.<NEXT_COLLOCATION_ITEM>conj
}

// вместо того чтобы
pattern ОбстИнфСоюз
{
 prep=предлог:вместо{} : export { node:root_node }
 n=местоим_сущ:то{ падеж:род }
 conj='чтобы'
} : links
{
 prep.<OBJECT>n.<NEXT_COLLOCATION_ITEM>conj
}

patterns ОбстИнф export { node:root_node }

patterns Инф2 export { node:root_node }

// Он валялся на диване, вместо того чтобы купить сливок
pattern ОбстИнф
{
 conj=ОбстИнфСоюз : export { node:root_node }
 inf=Инф2
} : links { conj.<INFINITIVE>inf }






patterns Инф2БезДоп export { ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node } 

patterns ГлНаст export { node:root_node ЛИЦО ЧИСЛО РОД ПЕРЕХОДНОСТЬ ПАДЕЖ ВРЕМЯ НАКЛОНЕНИЕ }


patterns Подлежащее export { ЛИЦО ЧИСЛО РОД node:root_node }
patterns ПодлежащееИнверс export { ЛИЦО ЧИСЛО РОД node:root_node }


wordentry_set НаречиеЛишьТолько=наречие:{ лишь, только }


// ----------------------------

patterns ДеепрОборот export { node:root_node }

patterns ДеепрИнфОборот export { node:root_node }
pattern ДеепрИнфОборот
{
 comma=','
 a=ОбстИнф : export { node:root_node }
} : links { a.<PUNCTUATION>comma }

pattern ДеепрИнфОборот
{
 ДеепрОборот : export { node:root_node }
}

// ---------------------------------------------

patterns ДеепрОборотПеред export { node:root_node }

patterns ДеепрИнфОборотПеред export { node:root_node }

pattern ДеепрИнфОборотПеред
{
 a=ОбстИнф : export { node:root_node }
 comma=','
} : links { a.<PUNCTUATION>comma }

pattern ДеепрИнфОборотПеред
{
 ДеепрОборотПеред : export { node:root_node }
}



// -------------------------------------------------------------
// ГЛАГОЛ + краткое прилагательное в роли атрибута подлежащего:
// вся долина стала видна.
// -------------------------------------------------------------

wordentry_set ГлагСТАТЬ_КрПрил=глагол:{
 стать, // вся долина стала видна.
 становиться, // весь мусор становится виден.
 остаться, // он остался доволен
 оставаться, // она всегда оставалась довольна
 оказаться, // коридор за дверью оказался пуст.
 бывать
}




// -----------------------------------------------------

patterns Сказуемое export { ЛИЦО ЧИСЛО РОД ВРЕМЯ node:root_node }

patterns НеполнСвязка export { node:root_node РОД ЧИСЛО ЛИЦО ВРЕМЯ }
patterns Связка export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
patterns ПредикатСвязка export { node:root_node }

// ++++++++++++++++++++++++++

patterns ПридаточноеВОбороте export { node:root_node }

// -----------------------------------
// Дополнение+Сказуемое+Подлежащее
// -----------------------------------

patterns ПредикатКтоИлиЧто export { node:root_node }

pattern ПредикатКтоИлиЧто
{
 ПридаточноеВОбороте : export { node:root_node }
}


// ##########################################################################


// ------------------------
// Сегодня пятое июня.
// ------------------------

wordentry_set ПорядкЧисл_ДеньМес=прилагательное:{
 первый, второй, третий, четвертый, пятый, шестой, 
 седьмой, восьмой, девятый, десятый, одиннадцатый, двенадцатый, тринадцатый, четырнадцатый,
 пятнадцатый, шестнадцатый, семнадцатый, восемнадцатый, девятнадцатый, двадцатый, тридцатый
}

wordentry_set ПорядкЧисл_ДеньМес10=числительное:
{ двадцать, тридцать }

patterns ЧислоМесяца export { node:root_node }

// Сегодня тридцать первое мая.
//         ^^^^^^^^^^^^^^^
pattern ЧислоМесяца
{
 c1=ПорядкЧисл_ДеньМес10
 c2=ПорядкЧисл_ДеньМес{ падеж:им род:ср число:ед } : export { node:root_node }
} : links { c2.<CONUMBER>c1 }

// Сегодня первое февраля.
//         ^^^^^^
pattern ЧислоМесяца
{
 ПорядкЧисл_ДеньМес{ падеж:им род:ср число:ед } : export { node:root_node }
}



patterns ДатаМесяца_ИМ export { node:root_node }
pattern ДатаМесяца_ИМ
{
 d=ЧислоМесяца
 m=НазваниеМесяца{ падеж:род } : export { node:root_node }
} : links { m.<ATTRIBUTE>d }


/*
// Сегодня первое апреля.
pattern ГлПредикат
{
 thema=НаречиеКакСвязкаНастВр : export { node:root_node }
 rhema=ДатаМесяца_ИМ
} : links { thema.<RHEMA>rhema }
*/

// -----------------------------------------------------------


patterns ИнфСДеепричОбор export { node:root_node }
patterns Инф export { ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node  }
patterns ИнфВин export { ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node  }
patterns НесовершИнф2 export { node:root_node }
patterns ИнфСВинДоп export { ПЕРЕХОДНОСТЬ ПАДЕЖ ВИД node:root_node  }


// *******************************************************************
// АНАЛИТИЧЕСКАЯ КОНСТРУКЦИЯ ДЛЯ ПРИЛАГАТЕЛЬНОГО - достаточная степень
// *******************************************************************

patterns ДостаточнаяСтепень export { КРАТКИЙ РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }

// достаточно сильный, чтобы победить
pattern ДостаточнаяСтепень
{
 adv=наречие:достаточно{}
 a=прилагательное:*{ ПАДЕЖ:ИМ } : export { РОД ПАДЕЖ ЧИСЛО ОДУШ КРАТКИЙ node:root_node }
 comma=','
 conj=СОЮЗ:чтобы{}
 inf=Инф
} : links
{
 a.{
    <ATTRIBUTE>adv
    <INFINITIVE>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>inf
   }
}

// --------------------------------------------

patterns Сказуемое0 export { ЛИЦО ЧИСЛО РОД ВРЕМЯ node:root_node }


// Он был очень занят , но успел закончить работу в срок .
//    ^^^^^^^^^^^^^^^
pattern Сказуемое0
{
 НеполнСвязка : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
}


// ************************************************
// связка со страдательным причастием
// ************************************************
patterns СтрадСвязкНареч export { node:root_node }
pattern СтрадСвязкНареч { наречие:*{}:export { node:root_node } } 





// -------------------------------------------

// ---------------------------------------------
// Союз ЗАТО и другие как вводная частица:
// ---------------------------------------------

wordentry_set СоюзКакВводн0={
 союз:чтобы{},
 союз:чтоб{}, // чтоб слышать друг друга.
 союз:ведь{}, // ведь опасно держать ее тут
 союз:зато{},
 союз:и{},
 союз:но{},
 союз:или{},
 союз:а{},
 союз:да{},
 союз:да и{}, // Да и других плюсов хватает.
 союз:если{},
 союз:прежде чем{},
 союз:поскольку{}, // поскольку умирать еще рано
 союз:либо{}, // либо пойти взглянуть?
 союз:то есть{}, // то есть спрятаться негде.
 частица:ну{} // ну хватит об этом
}

patterns СоюзКакВводн export { node:root_node }
pattern СоюзКакВводн
{
 СоюзКакВводн0 : export { node:root_node }
}

// Вот и осень пришла
// ^^^^^
pattern СоюзКакВводн
{
 x=частица:вот{}
 conj=союз:и{} : export { node:root_node }
}
: links { conj.<PREFIX_PARTICLE>x }
: ngrams { -1 }


// если бы ты любила меня!
// ^^^^^^^
pattern СоюзКакВводн
{
 conj=союз:если{} : export { node:root_node }
 x=ЧастицаБы
} : links { conj.<POSTFIX_PARTICLE>x }
: ngrams { 1 }

// вот если бы мы жили два часа спустя.
// ^^^^^^^^^^^
pattern СоюзКакВводн
{
 p=частица:вот{}
 conj=союз:если{} : export { node:root_node }
 x=ЧастицаБы
} : links { conj.{
                  <PREFIX_PARTICLE>p
                  <POSTFIX_PARTICLE>x
           } }
: ngrams { 1 }


// или же можно попытаться захватить еще один корабль.
// ^^^^^^
pattern СоюзКакВводн
{
 conj=союз:или{} : export { node:root_node }
 x=частица:же{}
} : links { conj.<POSTFIX_PARTICLE>x }
: ngrams { 1 }

wordentry_set ВводныеЧастицы={
 частица:о{}, частица:ах{}, частица:эх{},
 частица:ай{}, частица:ага{}, частица:угу{},
 частица:ишь{}, частица:фу{},
 частица:ох{}, частица:ух{}, частица:ого{},
 частица:ну{}, частица:эй{}, частица:ой{},
 частица:эге{}
}

// Ого, ты побрился!
// ^^^^
pattern СоюзКакВводн
{
 p=ВводныеЧастицы : export { node:root_node }
 comma=','
} : links { p.<PUNCTUATION>comma }


// Эх, а я не дождался
// ^^^^^
pattern СоюзКакВводн
{
 p=ВводныеЧастицы : export { node:root_node }
 comma=','
 w=СоюзКакВводн0
} : links { p.<PUNCTUATION>comma.<NEXT_COLLOCATION_ITEM>w }



// О, если бы кто-нибудь принес мне аленький цветочек...
// Ах, хорошо бы сейчас искупаться в Черном море!
pattern СоюзКакВводн
{
 p=ВводныеЧастицы : export { node:root_node }
 comma=','
 w1=союз:если{}
 w2=ЧастицаБы
} : links
{
 p.<PUNCTUATION>comma.
    <NEXT_COLLOCATION_ITEM>w1.<POSTFIX_PARTICLE>w2
}


// Слово ЭТО в качестве вводного в первой позиции:
//
// - Это вы подожгли вчера конюшню?
//   ^^^
pattern СоюзКакВводн
{
 p=частица:это{} : export { node:root_node }
} : ngrams { -2 }


// Ну а если взять предельный радиус действий самолетов?
// ^^^^^^^^^
pattern СоюзКакВводн
{
 p1=частица:ну{} : export { node:root_node }
 p2=союз:*{}
 p3=СоюзКакВводн
} : ngrams { -1 }
: links { p1.<NEXT_COLLOCATION_ITEM>p2.<NEXT_COLLOCATION_ITEM>p3 }


// ***********************
// ПРЕДЛОЖЕНИЕ
// ***********************

// ---------------------------
// Прямая речь.
// ---------------------------

// Упрощенные правила, без анализа императива и т.д.
patterns ПрямаяРечь export { node:root_node }

patterns ОткрКавычк export { node:root_node }
pattern ОткрКавычк { '«' : export { node:root_node } }
pattern ОткрКавычк { '"' : export { node:root_node } }
pattern ОткрКавычк { '“' : export { node:root_node } }

patterns ЗакрКавычк export { node:root_node }
pattern ЗакрКавычк { '»' : export { node:root_node } }
pattern ЗакрКавычк { '"' : export { node:root_node } }
pattern ЗакрКавычк { '”' : export { node:root_node } }


patterns СодержаниеРечи export { node:root_node }


word_set КонецПрямойРечи = { '?', '!', ',' }

patterns ПредложСТерм export { node:root_node }

// - А где ж твой отец-то?
//   ^^^^^^^^^^^^^^^^^^^^
pattern СодержаниеРечи
{
 s=ПредложСТерм : export { node:root_node }
 end=@optional(КонецПрямойРечи)
} : links { s.~<PUNCTUATION>end }

// - Сюда! - прокричал Дмитрий.
pattern СодержаниеРечи
{
 s=НеполнПредлож : export { node:root_node }
 end=@optional(КонецПрямойРечи)
} : links { s.~<PUNCTUATION>end }


// - Да, - сказал старик.
//   ^^
pattern СодержаниеРечи
{
 s=ЧАСТИЦА:ДА{} : export { node:root_node }
 end=@optional(КонецПрямойРечи)
} : links { s.~<PUNCTUATION>end }


patterns СложноПредлож export { node:root_node }


// "Боги прячут, человек находит", - говорили зодчие.
//  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern СодержаниеРечи
{
 s=СложноПредлож : export { node:root_node }
 end=@optional(КонецПрямойРечи)
} : links { s.~<PUNCTUATION>end }


patterns РазделительРечи export { node:root_node }

// - А дети-инвалиды находятся под надзором.
//        ~~~~
pattern РазделительРечи { '-'{ ~tokenizer_flag:word_conjunction }: export { node:root_node } }
pattern РазделительРечи { '–'{ ~tokenizer_flag:word_conjunction }: export { node:root_node } }

// — Я работаю, - сказал Вячеслав Викторович.
// ^
pattern РазделительРечи { '—'{ ~tokenizer_flag:word_conjunction }: export { node:root_node } }


// - А где ж твой отец-то?
pattern ПрямаяРечь
{
 a1=РазделительРечи
 p=СодержаниеРечи : export { node:root_node }
} : links { p.<PUNCTUATION>a1 }


patterns ГлПредикат export { node:root_node }

// - В чем заключается ваше возражение? - спросил представитель.
// - Орёл или решка? - спросил мальчик.
// - Сюда! - крикнул всадник.
// - Не вижу необходимости, - ворчливо возразил майор.
pattern ПрямаяРечь
{
 a1=РазделительРечи
 p2=СодержаниеРечи
 a2=РазделительРечи
 p=ГлПредикат : export { node:root_node }
} : links
{
 p.{
    <PUNCTUATION>a1
    <SPEECH>p2.<PUNCTUATION>a2
   }
}


// - Бабушка,  -  воскликнула  девочка, - возьми, возьми меня к себе!
pattern ПрямаяРечь
{
 a1=РазделительРечи
 p2=СодержаниеРечи
 a2=РазделительРечи
 p=ГлПредикат : export { node:root_node }
 comma=','
 a3=РазделительРечи
 p3=СодержаниеРечи
} : links
{
 p.{
    <PUNCTUATION>a1
    <SPEECH>p2.<PUNCTUATION>a2
    <PUNCTUATION>comma
    <PUNCTUATION>a3
    <SPEECH>p3
   }
}




// Он сказал нам: «Идите за мной»
// Капитан приказал: "Экипаж, спустить шлюпки на воду!"
// Мы попросили лесника: "Проводи нас, дедушка"
pattern ПрямаяРечь
{
 p=Предикат : export { node:root_node }
 colon=':'
 a1=ОткрКавычк
 p2=СодержаниеРечи
 a2=ЗакрКавычк
} : links
{
 p.{
    <SPEECH>colon.
     <NEXT_COLLOCATION_ITEM>p2.{
                                <PUNCTUATION>a1
                                <PUNCTUATION>a2
                               }
   }
}

// «Подождите меня», - попросил я
// «Подождите здесь», - сказал офицер
// "Боги прячут, человек находит", - говорили зодчие.
pattern ПрямаяРечь
{
 a1=ОткрКавычк
 p2=СодержаниеРечи
 a2=ЗакрКавычк
 comma=','
 t=ДефисКакСвязка
 p=Предикат : export { node:root_node }
} : links
{
 p.<SPEECH>p2.{
               <PUNCTUATION>a1
               <PUNCTUATION>a2
               <PUNCTUATION>comma.<PUNCTUATION>t
              }
}

// «Не думаешь ли ты, малыш, со мной в прятки играть?» - спросил я озорного мальчугана и повел его к дому
// «Куда идёт автобус?» - спросили мы у кондуктора
pattern ПрямаяРечь
{
 a1=ОткрКавычк
 p2=СодержаниеРечи
 a2=ЗакрКавычк
 t=ДефисКакСвязка
 p=Предикат : export { node:root_node }
} : links
{
 p.<SPEECH>p2.{
               <PUNCTUATION>a1
               <PUNCTUATION>a2
               <PUNCTUATION>t
              }
}



// ------------------------------------------------------


pattern Предлож1
{
 ПрямаяРечь : export { node:root_node }
}

// ------------------------------------------------------

patterns Предлож1_Состав export { node:root_node }

pattern Предлож1_Состав
{
 ПредикатСвязка : export { node:root_node }
}

pattern Предлож1_Состав
{
 ГлПредикат : export { node:root_node }
}

pattern Предлож1
{
 Предлож1_Состав : export { node:root_node }
}


patterns ВводнаяФраза export { node:root_node }

// Ну вот,  возьми билет
pattern Предлож1
{
 intro=ВводнаяФраза
 p=Предлож1_Состав : export { node:root_node }
} : links { p.<BEG_INTRO>intro }


// Да, но с чего же я начал?
// ^^^^^^
// Контрпример:
// Нет, так нельзя.
// ^^^^
pattern Предлож1
{
 intro=ВводнаяФраза
 @probe_left(',')
 conj=СоюзКакВводн0
 p=Предлож1_Состав : export { node:root_node }
} : links
{
 p.{
    <BEG_INTRO>intro
    <PREFIX_CONJUNCTION>conj
   }
}


// Кутить так кутить.
pattern Предлож1
{
 v1=инфинитив:*{} : export { node:root_node }
 conj=Союз:так{}
 v2=инфинитив:*{}
} : links { v1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }


// Завивает так завивает!
pattern Предлож1
{
 v1=глагол:*{} : export { node:root_node }
 conj=Союз:так{}
 v2=глагол:*{}
} : links { v1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>v2 }




// Предложения, начинающиеся с сочинительного союза:
// А ты умеешь плавать?
// ^
pattern Предлож1
{
 conj=Союз:а{}
 p=Предлож1_Состав : export { node:root_node }
} : links { p.<PREFIX_CONJUNCTION>conj }

pattern Предлож1
{
 intro=ВводнаяФраза
 p=Предлож1_Состав : export { node:root_node }
} : links { p.<BEG_INTRO>intro }


// зато близость наступает значительно быстрее.
// зато хорошенько изучил местность.
pattern Предлож1
{
 conj=СоюзКакВводн
 p=Предлож1_Состав : export { node:root_node }
} : links { p.<BEG_INTRO>conj }



word_set КонецПредлТокен = { ',', '!', '?', '.', '...', '!..', '?..', ':', '?!', '!!!', '…', ';' }

patterns КонецПредл export { node:root_node }

// - Костя, не спи, пожалуйста!..
//                            ^^^
pattern КонецПредл
{
 КонецПредлТокен : export { node:root_node }
}

// Ближайшее полное затмение москвичи увидят..
pattern КонецПредл
{
 a=КонецПредлТокен
 b=КонецПредл : export { node:root_node }
} : links { b.<PUNCTUATION>a }


// ты собираешься платить или как?
//                        ^^^^^^^^
pattern КонецПредл
{
 w1=союз:или{}
 w2=наречие:как{}
 t=пунктуатор:?{} : export { node:root_node }
}
: links { t.<SENTENCE_CLOSER>w1.<NEXT_COLLOCATION_ITEM>w2 }


wordentry_set ЧастицаТерминатор=
{
 частица:а{},
 частица:да{},
 частица:нет{},
 частица:так{}
}

// Давай их попробуем,  а?
//                   ^^^^^ 
// Учишь уроки, да?
//            ^^^^^
pattern КонецПредл
{
 w1=','
 w2=ЧастицаТерминатор
 t=КонецПредлТокен : export { node:root_node }
}
: links { t.<SENTENCE_CLOSER>w1.<NEXT_COLLOCATION_ITEM>w2 }


// можем мы узнать это или нет?
//                     ^^^^^^^^
pattern КонецПредл
{
 w1=союз:или{} : export { node:root_node }
 w2=частица:нет{}
 t=@optional(КонецПредлТокен)
}
: links {
  w1.
   <NEXT_COLLOCATION_ITEM>w2.
    ~<SENTENCE_CLOSER>t
}


// Он согласен, не так ли?
//            ^^^^^^^^^^^^
pattern КонецПредл
{
 comma=',' : export { node:root_node }
 w1=частица:не{}
 w2=наречие:так{}
 w3=частица:ли{}
 t=@optional(КонецПредлТокен)
}
: links {
  comma.
   <NEXT_COLLOCATION_ITEM>w1.
   <NEXT_COLLOCATION_ITEM>w2.
    <NEXT_COLLOCATION_ITEM>w3.
     ~<SENTENCE_CLOSER>t
}


// а вот получится такой фокус второй раз или же нет
//                                        ^^^^^^^^^^
pattern КонецПредл
{
 w1=союз:или{} : export { node:root_node }
 w2=частица:же{}
 w3=частица:нет{}
 t=@optional(КонецПредлТокен)
}
: links {
 w1.
  <NEXT_COLLOCATION_ITEM>w2.
   <NEXT_COLLOCATION_ITEM>w3.
    ~<SENTENCE_CLOSER>t
}

// они находились внутри дворца - или нет?
//                              ^^^^^^^^^^
pattern КонецПредл
{
 w1='-' : export { node:root_node }
 w2=союз:или{}
 w3=частица:нет{}
 t=@optional(КонецПредлТокен)
}
: links {
 w1.<NEXT_COLLOCATION_ITEM>w2.
     <NEXT_COLLOCATION_ITEM>w3.
      ~<SENTENCE_CLOSER>t
}


// незавершенное предложение:
// К ним тянутся вереницы паломников и...
//                                   ^^^^
// Контрпример:
// Себя любить принудила ты чем?
//                          ~~~~
pattern КонецПредл
{
 w1=союз:*{} : export { node:root_node }
 t=@optional(КонецПредлТокен)
 @noshift(BETH:END{})
}
: links { w1.~<SENTENCE_CLOSER>t }
: ngrams { -10 }


// Я оскорбил ее окончательно, но...
// 
pattern КонецПредл
{
 comma=','
 w1=союз:*{} : export { node:root_node }
 t=@optional(КонецПредлТокен)
 @noshift(BETH:END{})
}
: links { w1.{ <PUNCTUATION>comma ~<SENTENCE_CLOSER>t } }
: ngrams { -6 }



// незавершенное предложение:
// А как вы проводили выходные в...
//                             ^^^^
pattern КонецПредл
{
 w1=предлог:*{} : export { node:root_node }
 t=@optional(КонецПредлТокен)
 @noshift(BETH:END{})
} : links { w1.~<SENTENCE_CLOSER>t }
: ngrams { -7 }



// --------------------------------


pattern ПредложСТерм
{
 s=Предлож1 : export { node:root_node }
 fin=@optional(КонецПредл)
} : links { s.~<PUNCTUATION>fin }


// "Идите!"
pattern ПредложСТерм
{
 a1=ОткрКавычк
 s=Предлож1 : export { node:root_node }
 fin=@optional(КонецПредл)
 a2=ЗакрКавычк
} : links
{
 s.{
    <PUNCTUATION>a1
    ~<PUNCTUATION>fin
    <PUNCTUATION>a2
   }
}


// Союзы НО, ХОТЯ, А могут выступать в роли вводных для полного предложения:
// Но постепенно я привык к его странной внешности

wordentry_set ВводнСоюзЭлем=союз:{
 а, но, хотя, поскольку, если, "так как",
"то есть", "чтобы", "дабы", "ибо", "потому что", поэтому, или,
"а то", // А то тебе плохо станет.
"не то", // Вставай, не то опоздаем
"а не то" // Сядь, а не то упадешь
}

patterns ВводнСоюз export { node:root_node }
pattern ВводнСоюз
{
 ВводнСоюзЭлем : export { node:root_node }
}

// И если были подзорные трубы.
// ^^^^^^
pattern ВводнСоюз
{
 w1=союз:*{} : export { node:root_node }
 w2=ВводнСоюзЭлем
}
: links { w1.<NEXT_COLLOCATION_ITEM>w2 }
: ngrams { -2 }



wordentry_set ВводнСоюзЭлем2 = { союз:и{}, ВводнСоюзЭлем }

// И поэтому Звонаря надо найти и убить.
// ^^^^^^^^^
pattern ВводнСоюз
{
 w1=ВводнСоюзЭлем2 : export { node:root_node }
 w2=союз:поэтому{}
} : links { w1.<NEXT_COLLOCATION_ITEM>w2 }
: ngrams { -1 }


// И вот поэтому больных надо лечить
// ^^^^^^^^^^^^^
pattern ВводнСоюз
{
 w1=ВводнСоюзЭлем2 : export { node:root_node }
 p=частица:вот{}
 w2=союз:поэтому{}
} : links { w1.<NEXT_COLLOCATION_ITEM>w2.<PREFIX_PARTICLE>p }
: ngrams { -1 }




pattern ПредложСТерм
{
 intro=ВводнСоюз
 s=Предлож1 : export { node:root_node }
 fin=@optional(КонецПредл)
} : links
{
 s.{
    <BEG_INTRO>intro
    ~<PUNCTUATION>fin
   }
}
// некоторые союзы омонимичны наречиям, поэтому предпочитаем наречия:
// Поэтому метафорами стали заниматься профессионально.
// ^^^^^^^
: ngrams { -1 }


// - А дети-инвалиды участвуют?
// ^
pattern ПредложСТерм
{
 intro='-'
 s=ПредложСТерм : export { node:root_node }
} : links { s.<PUNCTUATION>intro }


pattern ПредложСТерм
{
 s=СложноПредлож : export { node:root_node }
 fin=@optional(КонецПредл)
} : links { s.~<PUNCTUATION>fin }


pattern ПредложСТерм
{
 s=НеполнПредлож : export { node:root_node }
 fin=@optional(КонецПредл)
} : links { s.~<PUNCTUATION>fin }
  : ngrams { -1 }



// Паттерн для разбора "научного названия" элемента флоры или фауны
// Кошка домашняя
// Лук репчатый, сладкий
patterns НаучнНазв export { node:root_node }


// для "научного названия" прилагательные не могут быть модифицированы наречиями или частицами НЕ.
// поэтому делаем отдельные паттерны.
patterns ГруппаПрилНазв export { РОД ЧИСЛО ОДУШ node:root_node }

pattern ГруппаПрилНазв
{
 прилагательное:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ИМ } :export { node:root_node РОД ЧИСЛО ОДУШ }
}

// сыр вкуснейший
pattern ГруппаПрилНазв
{
 прилагательное:* { ~КРАТКИЙ СТЕПЕНЬ:ПРЕВОСХ ПАДЕЖ:ИМ } :export { node:root_node РОД ЧИСЛО ОДУШ }
}


pattern ГруппаПрилНазв
{
 a1=прилагательное:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ИМ } :export { node:root_node РОД ЧИСЛО ОДУШ }
 comma=','
 a2=прилагательное:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ПАДЕЖ:ИМ =A1:РОД =A1:ЧИСЛО =A1:ОДУШ }
}


pattern НаучнНазв
{
 n=существительное:*{ падеж:им } : export { node:root_node }
 a=ГруппаПрилНазв{ =n:РОД =n:ЧИСЛО }
} : links { n.<ATTRIBUTE>a }

// Мороженое не плохое
pattern НаучнНазв
{
 n=существительное:*{ падеж:им } : export { node:root_node }
 neg=частица:не{}
 a=ГруппаПрилНазв{ =n:РОД =n:ЧИСЛО }
} : links { n.<ATTRIBUTE>a.<NEGATION_PARTICLE>neg }


// ******************************
// Паттерны краткого ответа

patterns КраткОтвет export { node:root_node }

patterns ГруппаСущ1 { language=Russian } export { РОД ПАДЕЖ ЧИСЛО ОДУШ МОДАЛЬНЫЙ CHARCASING ПАДЕЖВАЛ node:root_node }

wordentry_set ОтветСлово = { частица:да{}, частица:нет{}, наречие:конечно{}, наречие:разумеется{} }

// Да, мой повелитель.
// Нет, хозяин.
pattern КраткОтвет
{
 a=ОтветСлово : export { node:root_node }
 comma=','
 n=ГруппаСущ1
 fin=@optional(КонецПредл)
} : links
{
 a.{
    <APPEAL>n.<PUNCTUATION>comma
    ~<PUNCTUATION>fin
   }
}

// Да!
pattern КраткОтвет
{
 a=ОтветСлово : export { node:root_node }
 fin=@optional(КонецПредл)
} : links { a.~<PUNCTUATION>fin }
