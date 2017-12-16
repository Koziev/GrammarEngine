// Предлог НАДО употребляется очень редко, в исключительных
// случаях:
// птицы кружились надо мной
// но:
// мне надо им помочь
colloc_filter надо1 language=Russian
{
 if context { ['надо'{ class:предлог }] *:*{ число:мн } }
  then reject
}

colloc_filter надо2 language=Russian
{
 if context { ['надо'{ class:предлог }] *:*{ лицо:3 } }
  then reject
}

colloc_filter надо3 language=Russian
{
 if context { ['надо'{ class:предлог }] *:*{ лицо:2 } }
  then reject
}


// ... о том, что ...
//    ^^^
colloc_filter о_том_что1 language=Russian
{
 if context { ['о'{ class:предлог }] 'том' }
  then accept
}


colloc_filter о_чем_то language=Russian
{
 if context { ['о'{ class:предлог }] местоим_сущ:*{ падеж:предл } }
  then accept
}

colloc_filter о_тебе language=Russian
{
 if context { ['о'{ class:предлог }] местоимение:*{ падеж:предл } }
  then accept
}


colloc_filter о_чем_то2 language=Russian
{
 if context { 'о' [*:*{ падеж:твор }] }
  then reject
}



// Подавляем вариант П^ИСАТЬ
colloc_filter писать_о1 language=Russian
{
 if context { ['писать'{class:глагол ~падеж:вин }] предлог:о{} }
  then reject
}




// После предлогов типа ПОД употребляется только форма местоимения НЕГО, НЕЁ, НИХ
// что позволяет снять омонимию с прилагательным.
// Но некоторые предлоги не вызывают появления этого эвфонического Н.
//
// Под его глазами легли морщины.
// ^^^^^^^

#define PreposPronoun( prepos ) \
#begin

colloc_filter предлог_его language=Russian
{
 if context { предлог:prepos{ 1 } ['его'{ class:прилагательное }] }
  then accept
}

colloc_filter предлог_ее1 language=Russian
{
 if context { предлог:prepos{ 1 } ['ее'{ class:прилагательное }] }
  then accept
}

colloc_filter предлог_ее2 language=Russian
{
 if context { предлог:prepos{ 1 } ['её'{ class:прилагательное }] }
  then accept
}

colloc_filter предлог_их language=Russian
{
 if context { предлог:prepos{ 1 } ['их'{ class:прилагательное }] }
  then accept
}

#end

PreposPronoun( "перед" )
PreposPronoun( "в" )
PreposPronoun( "об" )
PreposPronoun( "без" )
PreposPronoun( "под" )
PreposPronoun( "в сравнении с" )
PreposPronoun( "вместе с" )
PreposPronoun( "рядом с" )
PreposPronoun( "в обнимку с" )
PreposPronoun( "недалеко от" )
PreposPronoun( "неподалеку от" )
PreposPronoun( "из" )
PreposPronoun( "к" )
//PreposPronoun( "над" )
PreposPronoun( "наряду с" )
PreposPronoun( "наравне с" )
PreposPronoun( "от" )
PreposPronoun( "по сравнению с" )
PreposPronoun( "пред" )
PreposPronoun( "с" )
PreposPronoun( "согласно с" )
PreposPronoun( "сравнительно с" )
PreposPronoun( "слева от" )
PreposPronoun( "справа от" )
PreposPronoun( "сверху над" )
PreposPronoun( "снизу под" )
PreposPronoun( "вдали от" )
PreposPronoun( "применительно к" )
PreposPronoun( "напару с" )
PreposPronoun( "параллельно с" )
PreposPronoun( "вкупе с" )
PreposPronoun( "в связи с" )
PreposPronoun( "одновременно с" )
PreposPronoun( "пополам с" )
PreposPronoun( "прямо в" )
PreposPronoun( "вплотную к" )
PreposPronoun( "впритык к" )
PreposPronoun( "прямо к" )
//PreposPronoun( "в отличие от" )
PreposPronoun( "отдельно от" )
PreposPronoun( "невдалеке от" )
PreposPronoun( "вблизи от" )
PreposPronoun( "размером с" )
PreposPronoun( "независимо от" )
PreposPronoun( "прямо с" )
PreposPronoun( "прямиком с" )
//PreposPronoun( "благодаря" )
PreposPronoun( "близ" )
PreposPronoun( "в области" )
//PreposPronoun( "в течение" )
PreposPronoun( "вдоль" )
//PreposPronoun( "включая" )
PreposPronoun( "вместо" )
PreposPronoun( "заместо" )
//PreposPronoun( "вне" )
PreposPronoun( "внутри" )
//PreposPronoun( "внутрь" )
PreposPronoun( "возле" )
PreposPronoun( "вокруг" )
//PreposPronoun( "вопреки" )
PreposPronoun( "впереди" )
//PreposPronoun( "вроде" )
PreposPronoun( "навроде" )
PreposPronoun( "вслед" )
//PreposPronoun( "вследствие" )
PreposPronoun( "выше" )
PreposPronoun( "для" )
PreposPronoun( "до" )
PreposPronoun( "за" )
PreposPronoun( "из - за" )
PreposPronoun( "из - под" )
PreposPronoun( "кроме" )
PreposPronoun( "окромя" )
PreposPronoun( "меж" )
PreposPronoun( "между" )
PreposPronoun( "мимо" )
PreposPronoun( "на основании" )
PreposPronoun( "на" )
PreposPronoun( "навстречу" )
PreposPronoun( "наперекор" )
PreposPronoun( "напротив" )
PreposPronoun( "насчет" )
//PreposPronoun( "несмотря на" )
//PreposPronoun( "ниже" ) // --> она ниже его
PreposPronoun( "о" )
PreposPronoun( "около" )
//PreposPronoun( "по мере" )
PreposPronoun( "по причине" )
PreposPronoun( "по" )
PreposPronoun( "по - за" )
PreposPronoun( "по - над" )
PreposPronoun( "подле" )
PreposPronoun( "позади" )
PreposPronoun( "помимо" )
PreposPronoun( "поперек" )
PreposPronoun( "посереди" )
PreposPronoun( "после" )
PreposPronoun( "по прошествии" )
PreposPronoun( "посреди" )
PreposPronoun( "посредине" )
PreposPronoun( "прежде" )
PreposPronoun( "при" )
PreposPronoun( "про" )
PreposPronoun( "промеж" )
PreposPronoun( "промежду" )
PreposPronoun( "против" )
PreposPronoun( "супротив" )
//PreposPronoun( "путем" )
PreposPronoun( "ради" )
PreposPronoun( "с целью" )
PreposPronoun( "свыше" )
PreposPronoun( "сзади" )
PreposPronoun( "сквозь" )
//PreposPronoun( "согласно" )
PreposPronoun( "соответственно" )
PreposPronoun( "спереди" )
PreposPronoun( "среди" )
PreposPronoun( "средь" )
PreposPronoun( "у" )
PreposPronoun( "через" )
PreposPronoun( "чрез" )
//PreposPronoun( "наподобие" )
PreposPronoun( "вслед за" )
PreposPronoun( "следом за" )
PreposPronoun( "сродни" )
PreposPronoun( "в угоду" )
//PreposPronoun( "посредством" )
//PreposPronoun( "с помощью" )
//PreposPronoun( "подобно" )
PreposPronoun( "без оглядки на" )
PreposPronoun( "с оглядкой на" )
//PreposPronoun( "в отношении" )
//PreposPronoun( "относительно" )
PreposPronoun( "подстать" )
PreposPronoun( "касаемо" )
PreposPronoun( "незадолго до" )
PreposPronoun( "вскоре после" )
PreposPronoun( "верхом на" )
PreposPronoun( "превыше" )
//PreposPronoun( "касательно" )
PreposPronoun( "на потребу" )
PreposPronoun( "задолго до" )
PreposPronoun( "накануне" )
PreposPronoun( "вглубь" )
//PreposPronoun( "вплоть до" )
PreposPronoun( "прямо через" )
PreposPronoun( "прямо на" )
PreposPronoun( "почти до" )
//PreposPronoun( "снаружи" )
//PreposPronoun( "посередине" ) // --> Посередине ее на короткой траве  лежали  разбросанные кости женщины-человека.
PreposPronoun( "сбоку" )
PreposPronoun( "вблизи" )
PreposPronoun( "параллельно" )
//PreposPronoun( "поверх" )
PreposPronoun( "наверху" )
//PreposPronoun( "сверх" )
PreposPronoun( "спустя" )
//PreposPronoun( "вперед" ) // --> Она подошла к  краю  вперед  его
//PreposPronoun( "раньше" )
PreposPronoun( "наперерез" )
//PreposPronoun( "изнутри" )
PreposPronoun( "на поводу у" )
PreposPronoun( "впервые в" )
PreposPronoun( "вниз" )
PreposPronoun( "вверх" )
PreposPronoun( "взамен" )





colloc_filter над_его1 language=Russian
{
 if context { 'над'{ class:предлог } ['его'{ class:прилагательное }] }
  then accept
}

colloc_filter над_ее1 language=Russian
{
 if context { 'над'{ class:предлог } ['ее'{ class:прилагательное }] }
  then accept
}

colloc_filter над_ее2 language=Russian
{
 if context { 'над'{ class:предлог } ['её'{ class:прилагательное }] }
  then accept
}

colloc_filter над_их language=Russian
{
 if context { 'над'{ class:предлог } ['их'{ class:прилагательное }] }
  then accept
}

// ------------------------------------------------

// только хочу попросить об одном
// ^^^^^^
colloc_filter только_союз_1 language=Russian
{
 if context { beth:begin{} ['только'{ class:союз }] }
  then reject
}


// на пустыре стояли дома, которые были обозначены на карте
//                                 ^^^^^^^^^^^^^^^
colloc_filter были_гл_1 language=Russian
{
 if context { ['были'{ class:глагол }] прилагательное:*{ краткий } }
  then accept
}


// он встал во главе небольшой группы солдат
//          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
colloc_filter под_предлог_1 language=Russian
{
 if context { предлог:в{} ['главе'{ одуш:неодуш }] }
  then accept
}


// сможет его увидеть
//        ^^^
colloc_filter его_1 language=Russian
{
 if context { глагол:*{} ['его'{ class:местоимение }] инфинитив:*{} }
  then accept
}



// сможет ее увидеть
//        ^^
colloc_filter его_1 language=Russian
{
 if context { глагол:*{} ['ее'{ class:местоимение }] инфинитив:*{} }
  then accept
}

// сможешь их увидеть
//         ^^
colloc_filter его_1 language=Russian
{
 if context { глагол:*{} ['их'{ class:местоимение }] инфинитив:*{} }
  then accept
}




// Снимаем омонимию ЛЁТ-ЛЕТО.
// Он прожил до ста лет.
//              ^^^^^^^
colloc_filter столько_то_лет language=Russian
{
 if context { числительное:*{} ['лет'{ род:ср падеж:род }] }
  then accept
}


// жажда мести овладела ими.
colloc_filter месть_1 language=Russian
{
 if context { существительное:жажда{} ['мести'{class:существительное падеж:род}] }
  then accept
}


// толкать перед собой
//         ^^^^^^^^^^^
colloc_filter перед_предлог_1 language=Russian
{
 if context { ['перед'{ class:предлог }] 'собой' }
  then accept
}


// Если после НА идет существительное, которое распознано ТОЛЬКО как предложный падеж,
// то берем вариант предлог:на, а частица:на отбрасываем.
//
// на месте
// ^^^^^^^^
colloc_filter на_предлог_1 language=Russian
{
 if context { ['на'{ class:предлог }] существительное:*{ падеж:предл 1 } }
  then accept
}


// благодаря месту
colloc_filter благодаря_предлог_1 language=Russian
{
 if context { ['благодаря'{ class:предлог }] существительное:*{ падеж:дат 1 } }
  then accept
}




// на протяжении всей жизни исследователя
// ^^
colloc_filter на_протяжении_1 language=Russian
{
 if context { ['на'{ class:предлог }] 'протяжении' }
  then accept
}


// Словосочетание НА ПРОТЯЖЕНИИ фактически играет роль предолога. После него вероятность
// увидеть иной падеж, кроме РОД, исчезающе мала:
//
// на протяжении всей жизни исследователя
colloc_filter на_протяжении_2 language=Russian
{
 if context { 'на' 'протяжении' [*:*{ падеж:род }] }
  then accept
}



// ветры подхватили следом клубы пыли.
//       ^^^^^^^^^^^^^^^^^
colloc_filter следом_1 language=Russian
{
 if context { глагол:*{} ['следом'{ class:наречие }] }
  then accept
}

colloc_filter следом_2 language=Russian
{
 if context { инфинитив:*{} ['следом'{ class:наречие }] }
  then accept
}




// зарядка с легкими гантелями
//           ^^^^^^^^^^^^^^^^^
colloc_filter легкие_1 language=Russian
{
 if context { ['легкими'{class:прилагательное}] существительное:*{ падеж:твор } }
  then accept
}


// Эта смесь взрывается от легкого давления
//                         ^^^^^^^
colloc_filter легкие_2 language=Russian
{
 if context { ['легкого'{class:прилагательное}] существительное:*{ падеж:род род:ср } }
  then accept
}


// Эта смесь взрывается от легкого нагрева
//                         ^^^^^^^
colloc_filter легкие_3 language=Russian
{
 if context { ['легкого'{class:прилагательное}] существительное:*{ падеж:род род:муж } }
  then accept
}


// С Новым Годом
colloc_filter новый_1 language=Russian
{
 if context { 'с' ['новым'{падеж:твор род:муж}] 'годом' }
  then accept
}

// день рожденья
colloc_filter день_рожденья language=Russian
{
 if context { [существительное:день{}] ['рожденья'{число:ед падеж:род}] }
  then accept
}



// присядь около дома
//         ^^^^^
colloc_filter около_1 language=Russian
{
 if context { ['около'{class:предлог}] существительное:*{ падеж:род } }
  then accept
}


// Посадить деревья вдоль аллеи
//                  ^^^^^
colloc_filter вдоль_1 language=Russian
{
 if context { ['вдоль'{class:предлог}] существительное:*{ падеж:род } }
  then accept
}

// распилить поперек волокон
//           ^^^^^^^
colloc_filter поперек_1 language=Russian
{
 if context { ['поперек'{class:предлог}] существительное:*{ падеж:род } }
  then accept
}


// уведомлять после закрытия
//            ^^^^^
colloc_filter после_1 language=Russian
{
 if context { инфинитив:*{} ['после'{class:предлог}] существительное:*{} }
  then accept
}

// уведомлять после второго сбоя
//            ^^^^^
colloc_filter после_2 language=Russian
{
 if context { инфинитив:*{} ['после'{class:предлог}] прилагательное:*{} }
  then accept
}



// уведоми после закрытия
//         ^^^^^
colloc_filter после_3 language=Russian
{
 if context { глагол:*{} ['после'{class:предлог}] существительное:*{} }
  then accept
}


// уведоми после полного закрытия
//         ^^^^^
colloc_filter после_4 language=Russian
{
 if context { глагол:*{} ['после'{class:предлог}] прилагательное:*{} }
  then accept
}


// уведомив после закрытия
//          ^^^^^
colloc_filter после_5 language=Russian
{
 if context { деепричастие:*{} ['после'{class:предлог}] существительное:*{} }
  then accept
}


// уведомив после полного закрытия
//          ^^^^^
colloc_filter после_6 language=Russian
{
 if context { деепричастие:*{} ['после'{class:предлог}] прилагательное:*{} }
  then accept
}



// Он ничего не понимает
//    ^^^^^^
colloc_filter ничего_1 language=Russian
{
 if context { ['ничего'{class:наречие}] 'не' }
  then reject
}

// Он не понимает ничего
//                ^^^^^^
colloc_filter ничего_2 language=Russian
{
 if context { глагол:*{} ['ничего'{class:наречие}] }
  then reject
}


// Я не мог из него выжать ничего.
colloc_filter ничего_2 language=Russian
{
 if context { инфинитив:*{} ['ничего'{class:наречие}] }
  then reject
}




// Вора поймали на месте преступления.
//              ^^^^^^^^^^^^^^^^^^^^^
colloc_filter на_месте_преступления language=Russian
{
 if context { ['на'{class:предлог}] ['месте'{ падеж:предл }] ['преступления'{ падеж:род} ] }
  then accept
}



// Я люблю слушать музыку по радио.
//                        ^^^^^^^^
colloc_filter по_радио language=Russian
{
 if context { ['по'{class:предлог}] ['радио'{ падеж:дат число:ед }] }
  then accept
}




// Обычно 'эта' является все-таки прилагательным, а не названием
// греческой буквы:
//
// Эта коробка сделана из непрочного материала.
// ^^^^^^^^^^^
colloc_filter эта_коробка language=Russian
{
 if context { ['эта'{class:прилагательное падеж:им}] существительное:*{род:жен падеж:им} }
  then accept
}


/*
// Роберт улыбнулся этой мысли.
//                  ^^^^^^^^^^
colloc_filter этой_1 language=Russian
{
 if context { ['этой'{class:прилагательное падеж:дат}] существительное:*{род:жен падеж:дат} }
  then accept
}

// Я не мог снести этой обиды.
//                 ^^^^^^^^^^
colloc_filter этой_1 language=Russian
{
 if context { ['этой'{class:прилагательное падеж:род}] существительное:*{род:жен падеж:род} }
  then accept
}


colloc_filter этой_2 language=Russian
{
 if context { ['этой'{class:прилагательное падеж:твор}] существительное:*{род:жен падеж:твор} }
  then accept
}
*/



// Решение задачи заняло четыре часа.
//                       ^^^^^^^^^^^
colloc_filter часы language=Russian
{
 if context { [числительное:*{ род:муж}] существительное:час{} }
  then accept
}



// Профессор читает лекции по истории немецкой философии.
//           ^^^^^^^^^^^^^
colloc_filter читать_лекции language=Russian
{
 if context { глагол:читать{} 'лекции'{ падеж:вин } }
  then accept
}



// Уберем у существительного УРОК вариант распознавания "УРКА"
// Девочка не пошла на урок физкультуры
colloc_filter урок language=Russian
{
 if context { ['урок'{число:мн}] существительное:*{падеж:род} }
  then reject
}

// Убираем распознавание НА как частицы после глаголов, инфинитивов и деепричастий:
// Продавать на eBay
// ~~~~~~~~~ ^^
colloc_filter частица_НА1 language=Russian
{
 if context { глагол:*{} ['на'{class:частица}] }
  then reject
}

colloc_filter частица_НА2 language=Russian
{
 if context { инфинитив:*{} ['на'{class:частица}] }
  then reject
}

colloc_filter частица_НА3 language=Russian
{
 if context { деепричастие:*{} ['на'{class:частица}] }
  then reject
}





colloc_filter два_1 language=Russian
{
 if context { ['два'{class:числительное род:муж}] существительное:*{род:муж} }
  then accept
}

// два ведра
colloc_filter два_1 language=Russian
{
 if context { ['два'{class:числительное род:ср}] существительное:*{род:ср} }
  then accept
}


// между тем грохот достиг уже последнего этажа.
//                  ^^^^^^^^^^
colloc_filter уже_1 language=Russian
{
 if context {  глагол:достичь{} ['уже'{степень:атриб}] }
  then accept
}



// Я уже сплю.
colloc_filter уже_2 language=Russian
{
 if context { ['уже'{степень:атриб}] глагол:*{} }
  then accept
}

// Давай уже спать.
colloc_filter уже_3 language=Russian
{
 if context { ['уже'{степень:атриб}] инфинитив:*{} }
  then accept
}

// Дождь идет уже несколько дней подряд
colloc_filter уже_4 language=Russian
{
 if context { ['уже'{степень:атриб}] наречие:*{} }
  then accept
}

// уже способен
colloc_filter уже_5 language=Russian
{
 if context { ['уже'{степень:атриб}] прилагательное:*{ краткий } }
  then accept
}

// это был уже настоящий бой!
colloc_filter уже_6 language=Russian
{
 if context { ['уже'{степень:сравн}] *:*{} }
  then
  {
   if context { ['уже'{степень:сравн}] *:*{ падеж:им } }
    then reject
   else if context { ['уже'{степень:сравн}] *:*{ падеж:вин } }
    then reject
   else if context { ['уже'{степень:сравн}] *:*{ падеж:твор } }
    then reject
   else if context { ['уже'{степень:сравн}] *:*{ падеж:дат } }
    then reject
   else if context { ['уже'{степень:сравн}] *:*{ падеж:предл } }
    then reject
   else if context { ['уже'{степень:сравн}] *:*{ падеж:мест } }
    then reject
  }
}



// все вокруг были заняты своими делами
//            ^^^^

// вокруг света
colloc_filter вокруг_1 language=Russian
{
 if context { ['вокруг'{class:предлог}] существительное:*{ падеж:род ~БылиКакСущ } }
  then accept
}

// его люди должны были искать его.
//          ^^^^^^^^^^^
colloc_filter должны_1 language=Russian
{
 if context { 'должны' ['были'{class:глагол}] }
  then accept
}


// Были ли Вы в Токио?
// ^^^^^^^
colloc_filter были_ли_1 language=Russian
{
 if context { ['были'{class:глагол}] ['ли'{class:частица}] }
  then accept
}


// 30-ые годы прошлого века
//            ^^^^^^^^^^^^^
colloc_filter но_и language=Russian
{
 if context { прилагательное:прошлый{} [существительное:веко{}] }
  then reject
}


// пюре было не только вкусное, но и питательное
colloc_filter но_и language=Russian
{
 if context { ['но'{class:союз}] ['и'{class:союз}] }
  then accept
}


// пюре было вкусное, хотя и питательное
colloc_filter хотя_и language=Russian
{
 if context { ['хотя'{class:союз}] ['и'{class:союз}] }
  then accept
}


// пюре было вкусное, пусть и вчерашнее
colloc_filter пусть_и language=Russian
{
 if context { ['пусть'{class:союз}] ['и'{class:союз}] }
  then accept
}


colloc_filter уже_готов language=Russian
{
 if context { "уже" "готов" }
  then
  {
   if context { [*{ class:наречие степень:атриб }] [*{ class:прилагательное }] }
    then accept
   }
}


// Антонио не стало легче
colloc_filter кому_то_не_стало language=Russian
{
 if context { существительное:*{} @or(частица:не{},'уже') "стало" }
  then
  {
   if context { [существительное:*{падеж:дат}] * [безлич_глагол] }
    then accept
   }
}

/*
// Антонио стало немного легче
colloc_filter кому_то_стало language=Russian
{
 if context { существительное:*{} "стало" }
  then
  {
   if context { [существительное:*{падеж:дат}] [безлич_глагол] }
    then accept
  }
}
*/


// разрешение омонимии для 'уже' - может быть наречием 'уже' или сравнительной степенью наречия 'узко'
colloc_filter уже_сплю language=Russian
{
 if context { "уже" глагол:*{} }
  then
  {
   if context { [*{ class:существительное }] * }
    then reject
   else if context { [*{ class:прилагательное }] * }
    then reject
  }
}



colloc_filter кушать_пюре language=Russian
{
 if context {
             @or(
                 глагол:кушать{},
                 инфинитив:кушать{},
                 глагол:*{ <synonym>глагол:кушать{} },
                 инфинитив:*{ <synonym>глагол:кушать{} },
                 деепричастие:кушая{},
                 прилагательное:кушавший{},
                 прилагательное:кушающий{}
                )
             ["пюре" { ~падеж:вин }]
            }
  then reject
}



colloc_filter тереть_виски language=Russian
{
 if context { глагол:тереть{} ["виски"{ существительное:виски{} }] } // убираем омоним "виски" (алк. напиток)
  then reject
}

colloc_filter ктото_ел language=Russian
{
 if context { существительное:*{ одуш:одуш } ["ели"{ class:существительное падеж:род }] } // гости ели
  then reject
}





colloc_filter пить_виски language=Russian
{
 if context { глагол:пить{} ["виски" { род:муж }] } // --> висок
  then reject
}



wordentry_set ЧеловекГотов=
{
 существительное:король{}, существительное:вождь{}, существительное:предводитель{}
}


colloc_filter кто_то_готов language=Russian
{
 if context { существительное:*{ род:муж число:ед } "готов" }
  then
  if context { ~ЧеловекГотов ["готов"{ class:существительное }] }
   then reject
}





colloc_filter кошка_села language=Russian
{
 if context { "кошка" ["села"{ class:существительное }] }
  then reject
}


colloc_filter кот_сел language=Russian
{
 if context { "кот" ["сел"{ class:существительное }] }
  then reject
}



colloc_filter кошка_спала language=Russian
{
 if context { "кошка" ["спала" { вид:несоверш }] }
  then accept
}

colloc_filter кот_спал language=Russian
{
 if context { "кот" ["спал" { вид:соверш }] }
  then reject
}

colloc_filter напряжение_спало language=Russian
{
 if context { "напряжение" ["спало" { вид:соверш }] }
  then accept
}

colloc_filter напряжение_немного_спало language=Russian
{
 if context { "напряжение" наречие:*{} ["спало" { вид:соверш }] }
  then accept
}



// убираем творительный падеж у несклоняемого сущ. "кофе"
colloc_filter пить_кофе language=Russian
{
 if context { глагол:пить{} ["кофе"{ падеж:вин }] }
  then accept
}


// 10 минут
colloc_filter N_минут language=Russian
{
 if context { num_word:*{} ["минут"{ class:глагол }] }
  then reject
}

// десять минут
colloc_filter N_минут language=Russian
{
 if context { числительное:*{} ["минут"{ class:глагол }] }
  then reject
}

/**/
