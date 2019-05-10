﻿// +++++++++++++++++++++++++++++++++++

// ???
// вместо одного дракона ты привел двоих.
//                                 ^^^^^
pattern ГлДополнение
{
 ЧИСЛИТЕЛЬНОЕ:*{ ЧИСЛО:МН КАТЕГОРИЯ_ЧИСЛ:СОБИР } : export{ ПАДЕЖ node:root_node }
} : ngrams { -1 }



// самим бы унести ноги.
// ^^^^^^^^
wordentry_set СамКакОбъект={ прилагательное:сам{} }
pattern ГлДополнение
{
 ПрилСамОбъект : export { ПАДЕЖ node:root_node }
} : ngrams { -5 }




// ты видишь этих пятерых?
//           ^^^^^^^^^^^^
pattern ГлДополнение
{
 a=прилагательное:этот{}
 c=ЧИСЛИТЕЛЬНОЕ:*{ ЧИСЛО:МН КАТЕГОРИЯ_ЧИСЛ:СОБИР =a:ПАДЕЖ =a:ЧИСЛО } : export{ ПАДЕЖ node:root_node }
}
: links { c.<ATTRIBUTE>a }
: ngrams { -1 }


// +++++++++++++++++++++++++++++++++++

// ЧЕГО выступает в роли винительного дополнения:
// а теперь скажи сразу : чего ты хочешь от нас?
//                        ^^^^
pattern ГлДополнение
{
 'чего' : export{ ПАДЕЖ:ВИН node:root_node }
} : ngrams { -2 }


// мало ли чего она могла!
// ^^^^^^^^^^^^
pattern ГлДополнение
{
 adv=наречие:мало{}
 p=частица:ли{}
 n='чего' : export{ ПАДЕЖ:ВИН node:root_node }
}
: links { n.<ATTRIBUTE>adv.<POSTFIX_PARTICLE>p }
: ngrams { 1 }


// не могут ничего с этим поделать
//          ^^^^^^
pattern ГлДополнение
{
 'ничего' : export{ ПАДЕЖ:ВИН node:root_node }
} : ngrams { -2 }


// +++++++++++++++++++++++++

wordentry_set УказМестКтоЧто={ местоим_сущ:кто{}, местоим_сущ:что{} }

// +++++++++++++++++++++++++

// Слова, записанные латиницей, считаем существительным в винительном падеже:
// Коля купил iPhone 5
pattern ГлДополнение
{
 ИнострСлово : export{ ПАДЕЖ:ВИН node:root_node }
} : ngrams { -5 }



// Коля купил новый iPhone
//            ^^^^^^^^^^^^
pattern ГлДополнение
{
 a=ГруппаПрил2 : export { ПАДЕЖ }
 n1=ИнострСлово : export{ node:root_node }
}
: links { n1.<ATTRIBUTE>a }
: ngrams { -2 }

// возьми себе другую жену.
//        ^^^^
pattern ГлДополнение
{
 n=местоим_сущ:себя{ ПАДЕЖ:ДАТ }  : export { ПАДЕЖ:ДАТ node:root_node }
}

// ты можешь себе-то представить?
//           ^^^^^^^
pattern ГлДополнение
{
 n=местоим_сущ:себя{ ПАДЕЖ:ДАТ }  : export { ПАДЕЖ:ДАТ node:root_node }
 t='-'
 p=частица:то{}
}
: links { n.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>p }
: ngrams { 1 }


// ничего этого у нас нет.
// ^^^^^^^^^^^^
pattern ГлДополнение
{
 n1=местоим_сущ:ничто{ ПАДЕЖ:РОД }  : export { ПАДЕЖ:РОД node:root_node }
 n2=местоим_сущ:это{ ПАДЕЖ:РОД }
} : links { n1.<NEXT_COLLOCATION_ITEM>n2 }
 : ngrams { 1 }


// сообщение заняло собой весь экран.
//                  ^^^^^
pattern ГлДополнение
{
 местоим_сущ:себя{ ПАДЕЖ:ТВОР }  : export { ПАДЕЖ:ТВОР node:root_node }
}


// Там я видел кое-кого из знакомых.
//             ^^^^^^^^^^^^^^^^^^^^
//
// никого из них дома нет
// ^^^^^^^^^^^^^

wordentry_set УказМестДляРодДоп=местоим_сущ:{ 'кое-кто', 'никто', 'кто-либо', 'кто-то' }

pattern ГлДополнение
{
 n=УказМестДляРодДоп : export { ПАДЕЖ node:root_node }
 p=предлог:из{}
 o=ГлДополнение{ падеж:род }
} : links
{
 n.<PREPOS_ADJUNCT>p.<NEXT_COLLOCATION_ITEM>o
}
: ngrams { 1 }




// он мало что видел
//    ^^^^^^^^
pattern ГлДополнение
{
 a=наречие:мало{}
 n=местоим_сущ:что{}  : export { ПАДЕЖ node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 2 }


// Дополнение МНОГО + род.п. ведет себя как винительный падеж:
//
// сосед нам много чего рассказал.
//           ^^^^^^^^^^
pattern ГлДополнение
{
 a=наречие:много{}
 n=местоим_сущ:что{ падеж:род }  : export { ПАДЕЖ:ВИН node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 2 }

// сосед нам много интересного рассказал
//           ^^^^^^^^^^^^^^^^^
pattern ГлДополнение
{
 a=наречие:много{}
 n=ГруппаПрил1{ падеж:род число:ед род:ср }  : export { ПАДЕЖ:ВИН node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { -2 }



// люди остались ждать неведомо чего.
//                     ^^^^^^^^^^^^^
pattern ГлДополнение
{
 a=прилагательное:*{ краткий род:ср число:ед }
 n=местоим_сущ:что{ падеж:род }  : export { ПАДЕЖ node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }




// я много чем горжусь
//   ^^^^^^^^^
pattern ГлДополнение
{
 a=наречие:много{}
 n=местоим_сущ:что{}  : export { ПАДЕЖ node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }


// +++++++++++++++++++++++++++++++++++++++

patterns ПравАтрибНеопрМест export { node:root_node }

// могут обмануть кого угодно.
//                ^^^^^^^^^^^
pattern ГлДополнение
{
 n=местоим_сущ:кто{}  : export { ПАДЕЖ node:root_node }
 a=ПравАтрибНеопрМест
} : links { n.<ATTRIBUTE>a }
  : ngrams { 2 }

// Он ест что попало
//        ^^^^^^^^^^
pattern ГлДополнение
{
 n=местоим_сущ:что{}  : export { ПАДЕЖ node:root_node }
 a=ПравАтрибНеопрМест
} : links { n.<ATTRIBUTE>a }
  : ngrams { 2 }

// +++++++++++++++++++++++++++++++++++++++


// Словосочетание ВСЁ ЭТО в роли прямого и именной части косвенного дополнения:
// мне тошно от всего этого
// он заболел от всего этого
pattern ГлДополнение
{
 n1=местоим_сущ:всё{} : export{ ПАДЕЖ node:root_node }
 n2=местоим_сущ:это{ число:ед =n1:падеж }
} : links { n1.<ATTRIBUTE>n2 }
  : ngrams { 1 }


// всем нам придет конец.
// ^^^^^^^^
pattern ГлДополнение
{
 a=прилагательное:весь{ число:мн }
 n=местоимение:я{ число:мн =a:падеж } : export{ ПАДЕЖ node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }


// обоих их ожидала страшная участь
// ^^^^^^^^
pattern ГлДополнение
{
 a=прилагательное:оба{ число:мн }
 n=местоимение:я{ число:мн =a:падеж } : export{ ПАДЕЖ node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }

// рад видеть вас обоих.
//            ^^^^^^^^^
pattern ГлДополнение
{
 n=местоимение:я{ число:мн } : export{ ПАДЕЖ node:root_node }
 a=прилагательное:оба{ число:мн =n:падеж }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }


// ----------------------------------------------

patterns СамПрефикс export { node:root_node ПАДЕЖ }

// свечи вспыхнули словно сами собой.
//                        ^^^^
pattern СамПрефикс
{
 a=прилагательное:сам{} : export { node:root_node ПАДЕЖ }
}

// стыд перед самим же собой
//            ^^^^^^^^
pattern СамПрефикс
{
 a=прилагательное:сам{} : export { node:root_node ПАДЕЖ }
 p=частица:же{}
} : links { a.<POSTFIX_PARTICLE>p }

// ------------------------------------------------------------------

// САМ СЕБЯ в роли прямого дополнения:
// раб ненавидит самого себя.
//               ^^^^^^^^^^^
pattern ГлДополнение
{
 a=СамПрефикс
 n=местоим_сущ:себя{ =a:падеж } : export { ПАДЕЖ node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }

// Вариант прямого дополнения САМ СЕБЕ, но первое слово не согласуется по падежу, а стоит в именительном.
// Гарри кивнул сам себе.
//              ^^^^^^^^
// вы увидите самих себя.
//            ^^^^^^^^^^
pattern ГлДополнение
{
 a=СамПрефикс
 n=местоим_сущ:себя{ =a:ПАДЕЖ } : export{ ПАДЕЖ node:root_node }
} : links { n.<ATTRIBUTE>a }
  : ngrams { 1 }



// как можно больше витаминов
pattern ГлДополнение
{
 adv1=наречие:как{}
 w='можно'
 adv2=наречие:много{ степень:сравн }
 n=СущСПредложДоп{ ПАДЕЖ:РОД }:export{ ПАДЕЖ:ВИН node:root_node }
} : links
{
 n.<ATTRIBUTE>adv1.<ATTRIBUTE>adv2.<NEXT_COLLOCATION_ITEM>w
}


// он мне отвечал тем же (самым)
pattern ГлДополнение
{
 obj=местоим_сущ:то{ падеж:твор }:export{ падеж node:root_node }
 p=частица:же{}
 a=@optional(прилагательное:самый{ падеж:твор число:ед род:ср })
} : links
{
 obj.{
      <POSTFIX_PARTICLE>p
      ~<ATTRIBUTE>a
     }
}


// Паттерны с НИ ОДНОГО род.п.
// Ни одного звука не слышу, ни одна травинка не шелохнется
pattern ГлДополнение
{
 p=частица:ни{}
 a=прилагательное:один{ число:ед }
 n=СущСПредложДоп{ =A:РОД =A:ПАДЕЖ }:export{ ПАДЕЖ node:root_node }
} : links
{
 n.<ATTRIBUTE>a.<NEGATION_PARTICLE>p
}
: ngrams { 1 }


// У него не было ни друзей, ни денег.
//                ^^^^^^^^^^^^^^^^^^^
pattern ГлДополнение
{
 p1=частица:ни{}
 n1=ГруппаСущ1{ ПАДЕЖ:РОД }:export{ ПАДЕЖ node:root_node }
 comma=','
 p2=частица:ни{}
 n2=ГруппаСущ1{ ПАДЕЖ:РОД }
} : links
{
 n1.{
     <NEGATION_PARTICLE>p1
     <RIGHT_LOGIC_ITEM>comma.<OBJECT>n2.<NEGATION_PARTICLE>p2
    }
}
: ngrams { 1 }



wordentry_set ПрилНеГлДоп=прилагательное:{ сам }

// --- Прилагательное в роли прямого дополнения
// предпочитаем форму среднего рода, но и другие доже допустимы.
// дождаться сладкого
// ждать интересного
// довольствоваться малым
pattern ГлДополнение
{
 ГруппаПрил2{ род:ср число:ед ~ПрилНеГлДоп } : export{ падеж node:root_node }
} : ngrams { -2 }


// Ему достаточно было просто потребовать большего.
//                                        ^^^^^^^^
pattern ГлДополнение
{
 'большего'{ПАДЕЖ:РОД} : export{ node:root_node ПАДЕЖ:РОД }
} : ngrams { -1 }



// ничего подобного у нас нет.
// ^^^^^^^^^^^^^^^^
pattern ГлДополнение
{
 n=местоим_сущ:ничто{} : export{ падеж node:root_node }
 a=прилагательное:*{ ~краткий степень:атриб род:ср число:ед ~ПрилНеГлДоп =n:падеж }
} : links { n.<ATTRIBUTE>a }




pattern ГлДополнение
{
 ГруппаПрил2{ число:мн ~ПрилНеГлДоп } : export{ падеж node:root_node }
} : ngrams { -4 }

pattern ГлДополнение
{
 ГруппаПрил2{ род:муж ~ПрилНеГлДоп } : export{ падеж node:root_node }
} : ngrams { -4 }

pattern ГлДополнение
{
 ГруппаПрил2{ род:жен ~ПрилНеГлДоп } : export{ падеж node:root_node }
} : ngrams { -4 }


// Мы бы взяли и деревянную.
//             ^^^^^^^^^^^^
pattern ГлДополнение
{
 p=частица:и{}
 n=ГруппаПрил2{ ~ПрилНеГлДоп } : export { ПАДЕЖ node:root_node }
}
: ngrams { -7 }
: links { n.<PREFIX_PARTICLE>p }


patterns ПричОборот0 export { РОД ПАДЕЖ ЧИСЛО ОДУШ node:root_node }

// Я нашел подаренный мне
//         ^^^^^^^^^^^^^^
pattern ГлДополнение
{
 n=ПричОборот0{ ~ПрилНеГлДоп } : export { ПАДЕЖ node:root_node }
}
: ngrams { -4 }


// Я бы увидел и отданный тебе
//             ^^^^^^^^^^^^^^^
pattern ГлДополнение
{
 p=частица:и{}
 n=ПричОборот0{ ~ПрилНеГлДоп } : export{ падеж node:root_node }
}
: ngrams { -7 }
: links { n.<PREFIX_PARTICLE>p }


// Группа прилагательного из 2х слов в роли прямого дополнения:
// предоставляться любому желающему
//                 ^^^^^^^^^^^^^^^^

wordentry_set ПрилКакМодифПрил = прилагательное:{
каждый, любой, первый, последний,
весь // предлагаться всем желающим
 }

pattern ГлДополнение
{
 a1=ПрилКакМодифПрил
 a2=прилагательное:*{ =a1:РОД =a1:ЧИСЛО =a1:ПАДЕЖ =a1:ОДУШ ~КРАТКИЙ СТЕПЕНЬ:АТРИБ ~ПрилНеГлДоп } : export{ падеж node:root_node }
}
: links { a2.<ATTRIBUTE>a1 }
: ngrams { -1 }



// -----------------------
// Прямое дополнение
// -----------------------

patterns ГлДополнение0 export { ПАДЕЖ node:root_node }

pattern ГлДополнение
{
 obj1=ГлДополнение0 : export { ПАДЕЖ node:root_node }
}

// возьми мой платок и прикройся  им,  как  маской.
//                                ^^^^^^^^^^^^^^^^
pattern ГлДополнение
{
 obj1=ГлДополнение0 : export { ПАДЕЖ node:root_node }
 comma1=@optional(',')
 conj=союз:как{}
 obj2=ГлДополнение0{ =obj1:ПАДЕЖ } 
 @noshift(ПравыйОграничительОборота)
 comma2=@coalesce(',')
} : links
{
 obj1.<RIGHT_LOGIC_ITEM>conj.
      {
       ~<PUNCTUATION>comma1
       <NEXT_COLLOCATION_ITEM>obj2
       ~<PUNCTUATION>comma2
      }
}
: ngrams { 1 }



// вижу мышь
pattern ГлДополнение0
{
 ГруппаСущ4 : export { ПАДЕЖ node:root_node }
}



// Прямое дополнение в партитиве без проблем заполняет
// родительную валентность глагола:
//
// Не зная броду, не суйся в воду
//         ^^^^^
pattern ГлДополнение0
{
 ГруппаСущ4{ ПАДЕЖ:ПАРТ } : export { ПАДЕЖ:РОД node:root_node }
}





// Одиночное числительное в роли объекта:
// - Я кладу себе три.
//                ^^^
pattern ГлДополнение0
{
 ГруппаЧисл : export { ПАДЕЖ node:root_node }
} : ngrams { -2 }





// нельзя терять ни минуты!
//               ^^^^^^^^^
pattern ГлДополнение
{
 n=частица:ни{}
 p=ГруппаСущ4 : export { ПАДЕЖ node:root_node }
} : links { p.<NEGATION_PARTICLE>n }


// Я вижу тебя
//        ^^^^
pattern ГлДополнение0
{
 ГруппаМест : export { ПАДЕЖ node:root_node }
}



// теперь и тебя вылечат
//        ^^^^^^
pattern ГлДополнение0
{
 p=частица:и{}
 n=ГруппаМест : export { ПАДЕЖ node:root_node }
}
: links { n.<PREFIX_PARTICLE>p }
: ngrams { -3 }




// вижу всех
pattern ГлДополнение
{
 прилагательное:весь{ число:мн падеж:вин одуш:одуш } : export { ПАДЕЖ node:root_node }
}

// =============================================================



// --------------------------------------------

word_set ЕгоЕеИх=
{
 'его',
 'ее',
 'их'
}

patterns ГлДопПрил export { node:root_node ЧИСЛО РОД ПАДЕЖ }

// Кот притворяется спящим
//                  ^^^^^^
pattern ГлДопПрил
{
 ГруппаПрил2{ ПАДЕЖ:ТВОР ~ЕгоЕеИх } : export { node:root_node ЧИСЛО РОД ПАДЕЖ }
}

// та оказалась самой слабой.
pattern ГлДопПрил
{
 Суперлатив0{ ПАДЕЖ:ТВОР } : export { node:root_node ЧИСЛО РОД ПАДЕЖ }
}


// ---------------------------------------------------

// Они решат его сами.
//           ^^^
pattern ГлДополнение0
{
 n=ГруппаМест : export { ПАДЕЖ node:root_node }
}

// ------------------------------------------------------


// ++++++++++++

patterns РодДополнение export { node:root_node ПАДЕЖ }

// У этого предприятия нет никакой будущности!
//                         ^^^^^^^^^^^^^^^^^^
pattern РодДополнение
{
 ГлДополнение{ ПАДЕЖ:РОД } : export { node:root_node ПАДЕЖ }
}

// проходу от них нету!
// ^^^^^^^
pattern РодДополнение
{
 ГлДополнение{ ПАДЕЖ:ПАРТ } : export { node:root_node ПАДЕЖ }
}

