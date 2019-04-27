// LC->24.10.2015

tree_scorers ОдушОбъект

tree_scorer ОдушОбъект language=Russian
{
 if context { местоим_сущ:кто{} }
  then 1
}

tree_scorer ОдушОбъект language=Russian
{
 if context { местоим_сущ:кто-нибудь{} }
  then 1
}

tree_scorer ОдушОбъект language=Russian
{
 if context { местоим_сущ:кто-то{} }
  then 1
}


tree_scorer ОдушОбъект language=Russian
{
 if context { местоим_сущ:кто-либо{} }
  then 1
}

tree_scorer ОдушОбъект language=Russian
{
 if context { существительное:*{ одуш:одуш } }
  then 1
}

tree_scorer ОдушОбъект language=Russian
{
 if context { местоимение:я{ род:муж } }
  then 1
}

tree_scorer ОдушОбъект language=Russian
{
 if context { местоимение:я{ род:жен } }
  then 1
}


// друзья должны были дождаться нас у леса
//                              ^^^
tree_scorer ОдушОбъект language=Russian
{
 if context { местоимение:я{ лицо:1 } }
  then 1
}

// Я дождусь вас
//           ^^^
tree_scorer ОдушОбъект language=Russian
{
 if context { местоимение:я{ лицо:2 } }
  then 1
}


tree_scorer ОдушОбъект language=Russian
{
 if context { 'себе' }
  then 1
}

tree_scorers НеодушОбъект

tree_scorer НеодушОбъект language=Russian
{
 if context { существительное:*{ одуш:неодуш } }
  then 1
}

tree_scorer НеодушОбъект language=Russian
{
 if context { местоим_сущ:что-то{} }
  then 1
}

tree_scorer НеодушОбъект language=Russian
{
 if context { местоимение:я{ род:ср } }
  then 1
}

tree_scorer НеодушОбъект language=Russian
{
 if context { местоим_сущ:что{} }
  then 1
}

tree_scorer НеодушОбъект language=Russian
{
 if context { местоим_сущ:что-нибудь{} }
  then 1
}

tree_scorer НеодушОбъект language=Russian
{
 if context { местоим_сущ:что-либо{} }
  then 1
}

// ------------------------------------

/*
function int CheckVerbSubjectConcord( tree v, tree sbj )
{
 int res_score=0;

 // Для безличных глаголов проверять не надо.
 if( eq( wordform_class(v),ГЛАГОЛ) )
  then
  {
   int sbj_number = wordform_get_coord( sbj, ЧИСЛО );
   if( eq(sbj_number,-1) )
    then
    {
     // Подлежащим может оказаться часть речи без категории числа.
     // У нас есть кое-что общее.
     //            ^^^^^^^
     if( eq( wordform_class( sbj ), МЕСТОИМ_СУЩ ) )
      then sbj_number = ЧИСЛО:ЕД;
     else if( eq( wordform_class( sbj ), ИНФИНИТИВ ) )
      then sbj_number = ЧИСЛО:ЕД;
    }
 
   int v_number = wordform_get_coord( v, ЧИСЛО );
 
   // согласование по числу выполняется в любом времени
   if( neq( sbj_number, v_number ) )
    then res_score=-10; // рассогласование по числу
    else
    {
     int v_tense = wordform_get_coord( v, ВРЕМЯ );
     if( eq( v_tense, ВРЕМЯ:ПРОШЕДШЕЕ ) )
      then
      {
       if( eq( v_number, ЧИСЛО:ЕД ) )
        then
        {
         // В прошедшем времени надо сопоставить род.
         // Если подлежащее - местоимение Я в первом или втором лице, то род 
         // проверять не надо:
         // А я и не слышала.
         //  ^^^     ^^^^^^^
         if( log_and(
                     eq( wordform_class(sbj), МЕСТОИМЕНИЕ ),
                     one_of( wordform_get_coord(sbj,ЛИЦО), ЛИЦО:1, ЛИЦО:2 )
                    ) )
          then
          {
           // nothing to check
          }
         else
          { 
           int sbj_gender = wordform_get_coord( sbj, РОД );
           int v_gender = wordform_get_coord( v, РОД );
           if( neq( sbj_gender, v_gender ) )
            then res_score=-10; // рассогласование по роду
          }
        }
      }
      else
      {
       // в настоящем и будущем времени надо сопоставить число и лицо
       // особый случай - глагол ЕСТЬ (форма глагола БЫТЬ настоящего времени),
       // она не имеет признака лица.
 
       int sbj_person = wordform_get_coord( sbj, ЛИЦО );
       if( eq( sbj_person, -1 ) )
        then sbj_person=ЛИЦО:3;
 
       if( log_not( eqi( wordform_lexem(v), 'есть' ) ) ) 
        then
        {
         int v_person = wordform_get_coord( v, ЛИЦО );
         if( neq( sbj_person, v_person ) )
          then res_score=-10; // рассогласование по лицу
        }
      }
    }
  }

 return res_score;
}


// Обычный предикат с глаголом в личной форме:
// Я буду читать сказку
// ^^^^^^^^^^^^^
//
// Безличная конструкция:
// от этого мне было жаль отказываться
//          ^^^      ^^^^ ^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { инфинитив:*{}.{ v=<LEFT_AUX_VERB>глагол:*{} sbj=<SUBJECT>*:*{} } }
  then CheckVerbSubjectConcord(v,sbj)
}

// Суд вынес решение
// ^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { v=глагол:*{}.sbj=<SUBJECT>*:*{} }
  then CheckVerbSubjectConcord(v,sbj)
}
*/

// ------------------------------------


// В предложении БЕЖАТЬ НА УРОК понижаем достоверность распознавания УРОК как формы слова УРКА,
// предпочитая неодушевленные объекты.
tree_scorer language=Russian
{
 if context { rus_verbs:бежать{}.предлог:на{}.ОдушОбъект  }
  then -1
}

// пойти на урок
// ^^^^^
tree_scorer language=Russian
{
 if context { rus_verbs:пойти{}.предлог:на{}.ОдушОбъект  }
  then -1
}





// давно хотел взять его рабочий телефон.
// --> неодушевленные обычно не хотят
tree_scorer language=Russian { if context { rus_verbs:хотеть{}.<SUBJECT>НеодушОбъект } then -2 }
tree_scorer language=Russian { if context { rus_verbs:захотеть{}.<SUBJECT>НеодушОбъект } then -2 }
//+tree_scorer language=Russian { if context { rus_verbs:перехотеть{}.<SUBJECT>НеодушОбъект } then -2 }



// ------------------------------------------------------

// Чтобы подавить связывание глагола с предложным паттерном в конструкции:
// завтракать яичницей с беконом
// ^^^^^^^^^^          ^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:завтракать{}.предлог:с{}.существительное:*{ одуш:неодуш <в_класс>существительное:еда{} } }
  then -10
}

tree_scorer language=Russian
{
 if context { существительное:*{ одуш:неодуш <в_класс>существительное:еда{} }
               .предлог:с{}.существительное:*{ одуш:неодуш <в_класс>существительное:еда{} падеж:твор }
            }
  then 2
}





// Обычно ЯВЛЯТЬСЯ можно кому-то, а не чему-то
// Цена является денежным выражением стоимости.
//      ^^^^^^^^                     ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:являться{}.<OBJECT>существительное:*{ падеж:дат одуш:неодуш } }
  then -10
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:явиться{}.<OBJECT>существительное:*{ падеж:дат одуш:неодуш } }
  then -10
}



// обрушивать на головы врагов
// ^^^^^^^^^^           ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обрушивать{}.<OBJECT>существительное:*{ одуш:одуш падеж:вин} }
  then -10
}


// Мы подали им руку помощи.
//    ^^^^^^ ^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:подать{}.<OBJECT>местоимение:я{ падеж:дат } }
  then 2
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:подать{}.<OBJECT>существительное:*{ одуш:одуш падеж:дат } }
  then 2
}

// Белки прячутся в дупле
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:прятаться{}.<SUBJECT>ОдушОбъект }
  then 2
}


// им пришлось идти боком.
// ^^ ^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:пришлось{}.<SUBJECT>*:*{ падеж:дат } }
  then 2
}


// старик прав : все имеет свою цену.
// ^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { прилагательное:правый{ краткий число:ед род:муж }.<SUBJECT>*:*{ падеж:им род:муж число:ед } }
  then 2
}


// тем временем надо приготовить лодки.
//                   ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:приготовить{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}


// Мы выбрали его секретарём нашей организации.
//    ^^^^^^^ ^^^ ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:выбрать{}.{
                                   <OBJECT>*:*{ падеж:вин }
                                   <OBJECT>существительное:*{ падеж:твор }
                                  } }
  then 3
}

// При жизни его не ценили.
//           ^^^    ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ценить{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}

// разгрести в задачах залежи
// ^^^^^^^^^           ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:разгрести{}.<OBJECT>существительное:*{ одуш:неодуш падеж:вин } }
  then 2
}





// император осторожно коснулся пальцами белой перчатки.
//                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:коснуться{}.{
                                     <OBJECT>*:*{ падеж:твор }
                                     <OBJECT>*:*{ падеж:род }
                                    } }
  then 4
}


// именно поэтому она собиралась предложить им очень простой выбор.
//                               ^^^^^^^^^^ ^^               ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:предложить{}.{
                                      <OBJECT>*:*{ падеж:дат }
                                      <OBJECT>*:*{ падеж:вин }
                                     } }
  then 1
}


// девушка смутно ощущала тепло.
//                ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ощущать{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}

// Томас внимательно рассматривал дома.
//                   ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:рассматривать{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}


// Ричард обвел глазами окрестности.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обвести{}.{
                                   <OBJECT>*:*{ падеж:твор }
                                   <OBJECT>*:*{ падеж:вин }
                                  } }
  then 4
}


// император осторожно коснулся пальцами белой перчатки.
//                     ^^^^^^^^          ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:коснуться{}.*:*{ падеж:род } }
  then 1
}



// собирать щеткой крошки со стола
// ^^^^^^^^        ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:собирать{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}


// Глагол ТРУБИТЬ обычно не присоединяет одушевленное прямое дополнение:
// трубить о поимке разбойников
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:трубить{}.<OBJECT>*:*{ одуш:одуш } }
  then -10
}


// Глагол СЛАГАТЬ обычно не присоединяет одушевленное прямое дополнение:
// слагать о подвигах викингов
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:слагать{}.<OBJECT>*:*{ одуш:одуш } }
  then -10
}




// семья арендовала домик у владельца
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:арендовать{}.предлог:у{}.*:*{ падеж:род одуш:одуш } }
  then 2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:арендовать{}.предлог:у{}.местоимение:*{ падеж:род } }
  then 2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:арендовать{}.предлог:у{}.местоим_сущ:*{ падеж:род } }
  then 2
}






// укрыться от маньяка в доме
// ^^^^^^^^            ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:укрыться{}.предлог:в{}.*:*{ падеж:предл } }
  then 2
}


// уединяться с подругой в доме
// ^^^^^^^^^^            ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:уединяться{}.предлог:в{}.*:*{ падеж:предл } }
  then 2
}



// Дни стали короче.
//     ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:стать{}.прилагательное:*{ степень:сравн } }
  then 2
}


// Чтобы устранить вариант с творительным падежом:
// причинить животным страдания
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:причинить{}.{
                                     <OBJECT>*:*{ падеж:вин }
                                     <OBJECT>*:*{ падеж:дат }
                                    } }
  then 4
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:причинять{}.{
                                     <OBJECT>*:*{ падеж:вин }
                                     <OBJECT>*:*{ падеж:дат }
                                    } }
  then 4
}




// запах реки сделался сильнее.
//            ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:сделаться{}.прилагательное:*{ степень:сравн } }
  then 2
}

// У вас есть чистый лист бумаги и конверт?
// ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:быть{ время:настоящее }.предлог:у{}.*:*{ падеж:род } }
  then 2
}


// знакомая опасность казалась страшнее.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:казаться{}.прилагательное:*{ степень:сравн } }
  then 2
}


// день будет становиться короче и немного тоскливее
//            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:становиться{}.прилагательное:*{ степень:сравн } }
  then 2
}


// Снимаем омонимию кратких форм ЗАМЕТНЫЙ-ЗАМЕТЕННЫЙ:
// Юпитер заметен невооруженным взглядом
//        ^^^^^^^
tree_scorer language=Russian
{
 if context { прилагательное:заметный{}.<OBJECT>'взглядом' }
  then 2
}

/*
// Студентка села за стол и начала читать журнал.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:начать{}.инфинитив:*{ вид:несоверш } }
  then 2
}
*/


// Село должно отпраздновать окончание страды
//      ^^^^^^^^^^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { прилагательное:должный{ КРАТКИЙ }.инфинитив:*{} }
  then 2
}




// ПОРА с инфинитивом обычно является безличным глаголом:
// пора учиться мыслить шире.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { безлич_глагол:пора{}.инфинитив:*{} }
  then 2
}


// Быть сильным в чем-то неодушевленном:
// Он не силён в математике.
//       ^^^^^^^^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { прилагательное:сильный{КРАТКИЙ}.'в'.существительное:*{ одуш:неодуш } }
  then 2
}



// дождаться сладкого
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:дождаться{}.<OBJECT>НеодушОбъект{ падеж:род } }
  then 2
}


// ---------------------------------------------------------------------------

// Дать+местоимение - обычно местоимение в дательном падеже:
// Я не дам им ничего
//      ^^^^^^
// просто они дали выход злости.
//            ^^^^       ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:дать{}.{ <OBJECT>*:*{ падеж:вин } <OBJECT>*:*{ падеж:дат } } }
  then 5
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:дать{}.{ <OBJECT>*:*{ падеж:вин } <OBJECT>*:*{ падеж:дат } } }
  then 5
}



// Артиллерии дам много.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:дать{}.{ <OBJECT>*:*{ ПАДЕЖ:РОД } наречие:много{} } }
  then 6
}

// ---------------------------------------------------------------------------






// Подавим вариант с Генри/твор.п./
// Генри уловил кусочек фразы.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:уловить{}.<OBJECT>*:*{ одуш:одуш падеж:твор } }
  then -5
}


// высокие колеса подняли тучи пыли.
//                ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:поднять{}.<OBJECT>существительное:туча{ падеж:вин }.'пыли' }
  then 3
}


// причинить животным страдания
// ^^^^^^^^^          ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:причинить{}.<OBJECT>'страдания'{ падеж:вин } }
  then 2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:причинять{}.<OBJECT>'страдания'{ падеж:вин } }
  then 2
}


// Зачерпывать пюре большой ложкой
// ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:зачерпывать{}.<OBJECT>существительное:*{ одуш:неодуш падеж:вин } }
  then 1
}


// причинить животным страдания
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:причинять{}.<OBJECT>существительное:*{ одуш:неодуш падеж:вин } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:причинять{}.<OBJECT>существительное:*{ одуш:одуш падеж:дат } }
  then 1
}




// ТРЕБОВАТЬ обычно присоединяет неодушевленные в родительном падеже:
// наша честь требует свободы.
//            ^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:требовать{}.<OBJECT>существительное:*{ одуш:неодуш падеж:род } }
  then 1
}


// Предпочтительно такое связывание, чтобы подлежащее для ПРИВЫКНУТЬ было обушевленным,
// либо было прямое дополнение в виде неодуш. объекта
// мечом привык решать любой спор.
//       ^^^^^^              ^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:привыкнуть{}.<SUBJECT>существительное:*{ одуш:неодуш } }
  then -2
}


// всем нужно спать на мягкой кровати
// ^^^^^^^^^^
tree_scorer language=Russian
{
 if context { 'нужно'.'всем'{ падеж:дат } }
  then 1
}


// Для модального глагола, к которому прикреплен инфинитив, нежелательно
// прикреплять еще и прямое дополнение:
//
// хочу все это понять
// ^^^^ ^^^     ^^^^^^ 

tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:хотеть{}.{
                               <INFINITIVE>*:*{}
                               <OBJECT>*:*{} } }
  then -1
}


// чрезвычайная эмоциональная живость и легкомысленность партнера может меня обижать
//                                                                      ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обижать{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}


// происходящее теряет всякое значение.
//              ^^^^^^        ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:терять{}.<OBJECT>существительное:значение{ падеж:вин } }
  then 2
}



// пытаюсь не уснуть, выпивая много крепкого кофе, и заедая его шоколадом
//                                                   ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:заедать{}.{
                                   <OBJECT>*:*{ падеж:вин }
                                   <OBJECT>*:*{ падеж:твор }
                                  } }
  then 2
}



// Чтобы подавить распознавание БЫЛИ как существительного:
//
// Обвиняемые были освобождены в зале суда
//            ^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { 'были'{ class:глагол }.{
                                      <SUBJECT>прилагательное:*{ число:мн }
                                      <RHEMA>прилагательное:*{ краткий страд число:мн }
                                     } }
  then 1
}



// кот спит и видит мышей во сне
//            ^^^^^       ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:видеть{}.предлог:в{}.существительное:*{ падеж:предл } }
  then 1
}


// Одушевленные субъекты обычно СПЯТ, а не СПАДАЮТ
// кенгуру, свернувшись клубком, спал
// ^^^^^^^                       ^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:спать{}.<SUBJECT>существительное:*{ одуш:одуш падеж:им } }
  then 1
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:спасть{}.<SUBJECT>существительное:*{ одуш:одуш падеж:им } }
  then -4
}


// ГРЕТЬ ожидает прямое дополнение в вин.п.:
// Я хочу попить чаю, греющего душу
//                    ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:греть{}.<OBJECT>существительное:*{ одуш:неодуш падеж:вин } }
  then 1
}


// Кошки пили сливки несколько дней подряд
//       ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пить{}.<OBJECT>существительное:*{ падеж:вин <в_класс>существительное:напиток{} } }
  then 1
}




// Глагол БЫТЬ предпочинает паттер В+сущ в предл. падеже, а не в винительном:
// машина была в пути
//        ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:быть{}.предлог:в{}.*:*{ падеж:предл } }
  then 1
}


// настоящий смех приносит облегчение.
//                ^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:приносить{}.<OBJECT>существительное:облегчение{падеж:вин} }
  then 2
}


// дважды раздался пронзительный свист.
//        ^^^^^^^^               ^^^^^

wordentry_set То_Что_Раздается_Как_Звук=существительное:{
 шум, свист, стук, звук, сигнал, рев, крик, бормотание, слово, фраза, гул, хохот, плач,
 визг, хор, треск, смех, скрип, вопль, звон, выстрел
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:раздаться{}.<SUBJECT>То_Что_Раздается_Как_Звук }
  then 1
}


// Обычно одушевленный субъект чешет неодушевленный предмет:
//
// Гарри почесал кончик носа.
// ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:почесать{}.{
                                    <SUBJECT>существительное:*{ падеж:им одуш:одуш }
                                    <OBJECT>существительное:*{ падеж:вин одуш:неодуш }
                                   } }
  then 1
}



// цветок придал девушке уверенности.
//        ^^^^^^         ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:придать{}.<OBJECT>существительное:*{ одуш:неодуш падеж:род } }
  then 1
}

// глухой рев наполнил окрестности.
//            ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:наполнить{}.<OBJECT>существительное:*{ одуш:неодуш падеж:вин } }
  then 1
}


// неторопливо допил прохладный сок.
//             ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:допить{}.<OBJECT>существительное:*{ одуш:неодуш падеж:вин <в_класс>существительное:напиток{} } }
  then 1
}



/*
// Мы помогли ему влезть в лодку.
//    ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:помочь{}.{
                                   <OBJECT>*:*{ падеж:дат }
                                   инфинитив:*{}
                                  } }
  then 5
}
*/


/*
// Разрешите вас пригласить?
// ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пригласить{}.<OBJECT>*:*{ падеж:вин } }
  then 1
}
*/

// неторопливо допил прохладный сок.
//             ^^^^^            ^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:допить{}.<OBJECT>существительное:*{ падеж:вин одуш:неодуш <в_класс>существительное:напиток{} } }
  then 1
}


// Он научил меня играть в шахматы.
//    ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:научить{}.{
                                   <OBJECT>*:*{ падеж:вин }
                                   инфинитив:*{}
                                  } }
  then 5
}



// Миша допил чай
//      ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:допить{}.существительное:*{ падеж:вин одуш:неодуш } }
  then 1
}


// Миша выпил чай
//      ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:выпить{}.существительное:*{ падеж:вин одуш:неодуш } }
  then 1
}


// Он смотрит на вещи просто.
//    ^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смотреть{}.предлог:на{}.существительное:*{ падеж:вин } }
  then 1
}

// Оставь книгу у Лены.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:оставить{}.предлог:у{}.существительное:*{ одуш:одуш } }
  then 1
}


// кенгуру наловил детенышам мышей своими лапами
//         ^^^^^^^           ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:наловить{}.<OBJECT>*:*{ падеж:род } }
  then 1
}



// Автор воскресил героя из небытия
//       ^^^^^^^^^       ^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:воскресить{}.предлог:из{}.'небытия' }
  then 1
}

// Коля вызвался помочь с математикой
//               ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:помочь{}.предлог:с{}.существительное:*{ одуш:неодуш } }
  then 1
}

// Поищите это слово в словаре.
// ^^^^^^^           ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:поискать{}.предлог:в{}.существительное:*{ одуш:неодуш падеж:предл } }
  then 1
}


// Всё это нашло отражение в его книге.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:найти{}.<OBJECT>существительное:отражение{}.предлог:в{} }
  then 3
}




// Я никого не встретил
//   ^^^^^^^^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { глагол:*{}.{ <NEGATION_PARTICLE>'не' 'никого'{падеж:вин} } }
  then 1
}


// Никого не встретить
tree_scorer language=Russian
{
 if context { инфинитив:*{}.{ <NEGATION_PARTICLE>'не' 'никого'{падеж:вин} } }
  then 1
}

// Он никого не видел там кроме неё.
//    ^^^^^^ ^^ ^^^^^
tree_scorer language=Russian
{
 if context { глагол:*{}.{ <NEGATION_PARTICLE>'не' 'никого'{падеж:вин} } }
  then 1
}


// напасть на спящих
// ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:напасть{}.предлог:на{}.*:*{ падеж:вин } }
  then 1
}


// Мы с Мишей читали сказку
tree_scorer language=Russian
{
 if context { местоимение:я{}.предлог:с{}.существительное:*{ падеж:твор одуш:одуш } }
  then 1
}


// Мы с ней сидели за одной партой.
// ^^^^^^^^
tree_scorer language=Russian
{
 if context { местоимение:я{}.предлог:с{}.местоимение:я{ падеж:твор } }
  then 1
}

// Мы с ним были на концерте.
tree_scorer language=Russian
{
 if context { местоимение:я{}.предлог:с{}.'ним'{ род:муж } }
  then 1
}







// Он относится к бедному товарищу с горячим участием.
//    ^^^^^^^^^                    ^^^^^^^^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { глагол:*{}.'с'.'участием' }
  then 1
}

tree_scorer language=Russian
{
 if context { инфинитив:*{}.'с'.'участием' }
  then 1
}

tree_scorer language=Russian
{
 if context { деепричастие:*{}.'с'.'участием' }
  then 1
}

tree_scorer language=Russian
{
 if context { прилагательное:*{ причастие }.'с'.'участием' }
  then 1
}


// Она оправдала неявку на занятия болезнью.
//     ^^^^^^^^^                   ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:оправдать{}.<OBJECT>*{ падеж:твор } }
  then 1
}


// жаждать мести
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:жаждать{}.<OBJECT>'мести'{ падеж:род } }
  then 1
}

// Он доводится мальчику дядей
//    ^^^^^^^^^          ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:доводиться{}.<OBJECT>*:*{ падеж:твор } }
  then 1
}


// принести в дом бездомного щенка
// ^^^^^^^^                  ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:принести{}.<OBJECT>*:*{ падеж:вин } }
  then 1
}



// всадить пулю в сердце
// ^^^^^^^      ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:всадить{}.предлог:в{}.существительное:*{ падеж:вин } }
  then 1
}



// Усиленная работа отразилась на его здоровье.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:отразиться{}.предлог:на{}.существительное:здоровье{ падеж:предл } }
  then 1
}

#define PreferAccusObject(v) \
#begin
tree_scorer ВалентностьГлагола language=Russian { if context { инфинитив:v{}.<OBJECT>*:*{ падеж:вин } } then 1 }
tree_scorer ВалентностьГлагола language=Russian { if context { глагол:v{}.<OBJECT>*:*{ падеж:вин } } then 1 }
#end


// Поэты воспели в этой оде героев
PreferAccusObject(воспеть)

// встретить в классе старого приятеля (встретить+вин.п.)
PreferAccusObject(встретить)


// встречать в лесу голодного медведя (встречать+вин.п.)
PreferAccusObject(встречать)

// выписать из деревни нового скакуна
PreferAccusObject(выписать)

// регулярная армия вытесняет из пригородов повстанцев
PreferAccusObject(вытеснять)

// выводить с одежды пятна (вводить + вин.п.)
PreferAccusObject(выводить)

// выжать максимум из машины (выжать + вин.п.)
PreferAccusObject(выжать)


// собраться в аудитории
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:собраться{}.предлог:в{}.существительное:*{ одуш:неодуш падеж:предл <в_класс>существительное:помещение{} } }
  then 1
}


// Глагол БОЯТЬСЯ обычно используется с прямым дополнением, причем одушевленное
// дополнение стоит в винительном падеже, а неодушевленное - в родительном.

// они должны научиться бояться нас.
//                      ^^^^^^^^^^^
// Дело мастера боится.
//      ^^^^^^^ ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:бояться{}.<OBJECT>ОдушОбъект{ падеж:вин } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:бояться{}.<OBJECT>НеодушОбъект{ падеж:род } }
  then 1
}







// сказал Холмс, снимая крышку с курицы
//               ^^^^^^        ^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:снимать{}.предлог:с{}.*:*{ падеж:род } }
  then 2
}


// Я послал книги по почте.
//   ^^^^^^       ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:послать{}.предлог:по{}.'почте' }
  then 2
}


// Он разложил книги по всему столу.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:разложить{}.предлог:по{}.существительное:*{} }
  then 1
}


// Мы покормили белок.
//    ^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:покормить{}.существительное:*{ падеж:вин одуш:одуш } }
  then 2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:покормить{}.существительное:*{ падеж:вин одуш:одуш } }
  then 2
}




// писатель пишет повести
//          ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:писать{ aux stress="пис^ать" }.существительное:*{ одуш:неодуш падеж:вин } }
  then 1
}


// Резкий порывистый ветер валит прохожих с ног.
//                         ^^^^^          ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:валить{}.предлог:с{}.'ног' }
  then 1
}

// Резкий порывистый ветер свалит тебя с ног.
//                         ^^^^^^      ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:свалить{}.предлог:с{}.'ног' }
  then 1
}





// блоггер, написавший про детский приют
tree_scorer language=Russian
{
 if context { прилагательное:написавший{ aux stress="напис^авший" }.предлог:про{} }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:написать{ aux stress="напис^ать" }.предлог:про{} }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:написать{ aux stress="напис^ать" }.предлог:про{} }
  then 1
}



// Учительница ищет в карманах шпаргалки
//             ^^^^            ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:искать{}.существительное:*{ падеж:вин } }
  then 1
}




// заметившими косулю медведицами
// ^^^^^^^^^^^        ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:заметить{}.<OBJECT>существительное:*{ падеж:твор одуш:одуш } }
  then -2
}




// стирать белье в реке
// ^^^^^^^       ^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:стирать{}.предлог:в{}.существительное:*{ одуш:неодуш падеж:предл } }
  then 1
}






tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:купить{}.предлог:у{}.существительное:*{ одуш:одуш } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:купить{}.предлог:у{}.местоимение:*{} }
  then 2
}



// стирать прошлое из памяти
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:стирать{}.предлог:из{}.существительное:память{} }
  then 1
}




// Боль исказила его лицо.
//      ^^^^^^^^     ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:исказить{}.<OBJECT>существительное:лицо{ одуш:неодуш } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:искажать{}.<OBJECT>существительное:лицо{ одуш:неодуш } }
  then 1
}




// Подавим по возможности связывание глагола ЕСТЬ с предложным дополнением ИЗ
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:есть{}.предлог:из{}.существительное:*{ <в_класс>существительное:овощ{} } }
  then -1
}



// Винительное дополнение:
// считать деньги
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:считать{}.*:*{падеж:вин} }
  then 1
}




// Мы согласовали наши законы с беларусским законодательством
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:согласовать{ вид:соверш }.предлог:с{} }
  then 1
}




// Я иду в кино.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:идти{}.{
                                'в'.'кино'{ падеж:вин }
                                <SUBJECT>местоимение:*{}
                               } }
  then 1
}





// Он купил игрушки для детей.
//    ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:купить{}.*:*{ падеж:вин } }
  then 1
}


// Он занял деньги под большие проценты.
//    ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:занять{}.'деньги'{ падеж:вин } }
  then 1
}




// его осторожность взяла верх над его жадностью
//                  ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:взять{}.существительное:верх{}.предлог:над{} }
  then 1
}


// Студенты долго ломали голову над задачей.
//                ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ломать{}.{
                                  'голову'
                                  предлог:над{} } }
  then 1
}




// Я не хотел вас обидеть.
//            ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обидеть{}.*:*{ падеж:вин } }
  then 2
}


// Я нашёл толк в этом деле.
//   ^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:найти{}.{
                                 'толк'
                                 предлог:в{}.существительное:*:*{ падеж:предл }
                                } }
  then 1
}




// Я всюду искал письмо, но нигде не мог его найти.
//                                       ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:найти{}.*:*{ падеж:вин } }
  then 2
}


// Я вовсе не хотел её оскорбить.
//                  ^^ ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:оскорбить{}.*:*{ падеж:вин } }
  then 2
}



// Мы перебили врагов в бою.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:перебить{}.'в'.'бою' }
  then 1
}


// Этот мотор делает 600 оборотов в минуту.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:делать{}.существительное:оборот{}.num_word:*{} }
  then 3
}



// для ВЫУЧИТЬ желательно дополнение в винительном падеже
// Он выучил меня играть в шахматы.
//    ^^^^^^ ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:выучить{}.*:*{ падеж:вин } }
  then 2
}



// Будем считать, что ЭТО в роли подлежащего имеет приоритет:
// Это внесло разнообразие в мою жизнь.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:*{ время:прошедшее число:ед род:ср }.<SUBJECT>'это' }
  then 1
}





// Я принёс эту книгу для вас.
//   ^^^^^^           ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:принести{}.предлог:для{}.местоимение:*{} }
  then 1
}



// Глагол ИЗБРАТЬ обычно требует прямое дополнение в винительном падеже:
// Академия наук избрала его почётным членом.
//               ^^^^^^^ ^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:избрать{}.*:*{ падеж:вин } }
  then 1
}


// Глагол ПРИСЫЛАТЬ обычно требует прямое дополнение
// Он присылал к должнику своих головорезов
//    ^^^^^^^^                  ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:присылать{}.<OBJECT>существительное:*{ падеж:вин } }
  then 1
}



// Я никого не встретил
//   ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{}.{ частица:не{} 'никого'{ падеж:род } } }
  then 1
}


// они затопили корабли в гавани
//     ^^^^^^^^         ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:затопить{}.предлог:в{}.*:*{ падеж:предл } }
  then 1
}





// Составьте предложение из этих слов.
// ^^^^^^^^^             ^^      ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:составить{}.предлог:из{}.существительное:*{ одуш:неодуш падеж:род } }
  then 1
}


// Согрейте руки у огня.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:согреть{}.предлог:у{}.существительное:*{ одуш:неодуш падеж:род } }
  then 1
}




// Не оставь товарища в опасности.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:оставить{}.предлог:в{}.существительное:*{ падеж:предл } }
  then 1
}


// Я принёс книгу с собой.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { Гл_С_Твор.'с'.'собой' }
  then 1
}




// Наш пароход держал курс прямо на север.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:держать{}.<OBJECT>существительное:курс{ падеж:вин } }
  then 1
}





// Антонио ни с кем не говорил
//         ^^^^^^^^^^^^^^^^^^^

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{}.{
                          'не'
                          'с'.{ 'ни' 'кем' }
                         } }
  then 1
}









// Я был знаком с вашим дядей.
//       ^^^^^^^^
tree_scorer language=Russian
{
 if context { 'был'.{ прилагательное:знакомый{ краткий } предлог:с{}.существительное:*{ одуш:одуш } } }
  then 3
}

tree_scorer language=Russian
{
 if context { 'был'.{ прилагательное:знакомый{ краткий } предлог:с{}.местоимение:*{} } }
  then 3
}









// Подавим родительную валентность для местоимения.
// Вас требует заведующий.
// ^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{ ПАДЕЖ:ВИН }.<OBJECT>'вас'{падеж:вин} }
  then 1
}




// Я научил его английскому языку.
//   ^^^^^^ ^^^             ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:научить{}.{ <OBJECT>местоимение:я{падеж:вин} <OBJECT>*:*{падеж:дат} } }
  then 1
}


// Я учу его английскому языку.
//   ^^^ ^^^             ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:учить{}.{ <OBJECT>местоимение:я{падеж:вин} <OBJECT>*:*{падеж:дат} } }
  then 1
}



// Я велел ему прийти через час.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:велеть{}.{ <OBJECT>местоимение:я{ падеж:дат } инфинитив:*{} } }
  then 1
}


// Дождь помешал нам прийти.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:помешать{}.{ <OBJECT>местоимение:я{ падеж:дат } инфинитив:*{} } }
  then 1
}


// Ведь вы сами посоветовали мне так сделать.
//              ^^^^^^^^^^^^^^^^     ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:посоветовать{}.{ <OBJECT>местоимение:я{ падеж:дат } инфинитив:*{} } }
  then 1
}


// Антонио разрешил нам рассказать об этом
//         ^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:разрешить{}.{ <OBJECT>местоимение:я{ падеж:дат } инфинитив:*{} } }
  then 1
}


// кенгуру наловил детенышам мышей своими лапами
//         ^^^^^^^           ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:наловить{}.<OBJECT>*:*{ падеж:род } }
  then 1
}





// Характер писателя лучше всего выражается в его произведениях.
//                   ^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { наречие:всего{}.'лучше'{ class:наречие } }
  then 1
}





// Этот город находится к западу от Москвы.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:находиться{ вид:несоверш }.<SUBJECT>существительное:*{} }
  then 1
}


// Он находится в весьма неприятном положении.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:находиться{ вид:несоверш }.предлог:*{} }
  then 1
}





// Подавим родительный падеж:
// Прошу вас.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:просить{}.местоимение:я{ падеж:вин } }
  then 1
}


// Природа наградила его разнообразными способностями.
//         ^^^^^^^^^ ^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:наградить{}.местоимение:я{ падеж:вин } }
  then 1
}


// Природа одарила его прекрасными способностями.
//         ^^^^^^^ ^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:одарить{}.местоимение:я{ падеж:вин } }
  then 1
}



// Предпочтём винительный падеж местоимения, а не родительный.
// Вас спрашивает какой-то человек.
// ^^^ ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:спрашивать{}.'вас'{падеж:вин} }
  then 1
}



// Примите мой искренний привет!
// ^^^^^^^                     ^
tree_scorer language=Russian
{
 if context { 'примите'{ наклонение:побуд }.'!' }
  then 1
}



// Напишите фамилию полностью.
// ^^^^^^^^         ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:написать{aux stress="напис^ать"}.наречие:полностью{} }
  then 1
}



// Она обозвала его дураком.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обозвать{}.{
                                    *:*{ падеж:вин }
                                    *:*{ падеж:твор }
                                   } }
  then 1
}





// Понизим достоверность распознавания УРКА:
// Девочка вообще не пошла на урок
//                   ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пойти{}.предлог:на{}.'урок'{ одуш:неодуш } }
  then 1
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:идти{}.предлог:на{}.'урок'{ одуш:неодуш } }
  then 1
}






// Выбираем винительный падеж:
// Время работает на нас.
//       ^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:работать{}.'на'.'нас'{падеж:вин} }
  then 1
}





// Мы пришли к заключению, что он прав.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:придти{}.'к'.'заключению' }
  then 1
}





/*
tree_scorer language=Russian
{
 if context { 'два'{ class:числительное род:муж }.существительное:*{род:жен} }
  then -1
}

tree_scorer language=Russian
{
 if context { 'два'{ class:числительное род:муж }.существительное:*{род:ср} }
  then -1
}

tree_scorer language=Russian
{
 if context { 'два'{ class:числительное род:ср }.существительное:*{род:муж} }
  then -1
}

tree_scorer language=Russian
{
 if context { 'два'{ class:числительное род:ср }.существительное:*{род:жен} }
  then -1
}



tree_scorer language=Russian
{
 if context { числительное:два{род:жен}.существительное:*{род:жен} }
  then 1
}


tree_scorer language=Russian
{
 if context { числительное:два{род:ср}.существительное:*{род:ср} }
  then 1
}
*/


// Уберем вариант СТАТЬ для:
//
// Он написал статью на русском языке.
//            ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:написать{ aux stress="напис^ать" }.<OBJECT>'статью'{ падеж:вин } }
  then 1
}


// Антонио подарил ведьмёнышам пюре
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:подарить{}.{
                                    <OBJECT>существительное:*{ падеж:вин одуш:неодуш }
                                    <OBJECT>существительное:*{ падеж:дат одуш:одуш }
                                   } }
  then 1
}



// Дайте мне хлеба.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:дать{}.<OBJECT>существительное:хлеб{ падеж:вин } }
  then -1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:дать{}.<OBJECT>существительное:хлеб{ падеж:род } }
  then 1
}


/*
wordentry_set НаречВремСуток=наречие:{ утром, вечером, днем, ночью }
// она вечером будет есть пюре
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:быть{}.{
                             НаречВремСуток
                             инфинитив:*{}
                            } }
  then 1
}
*/



// Глаголы с семантикой поедания, присоединяющие прямое дополнение в вин. падеже
wordentry_set ГлаголыПоедания_Вин=
{
 глагол:есть{}, инфинитив:есть{}
}


// Антонио ест пюре
tree_scorer ВалентностьГлагола language=Russian
{
 if context { ГлаголыПоедания_Вин.<OBJECT>'пюре'{падеж:вин} }
  then 1
}

/*
// она утром будет есть пюре
tree_scorer ВалентностьГлагола language=Russian
{
 if context { ГлаголыПоедания_Вин.<ATTRIBUTE>наречие:утром{} }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { ГлаголыПоедания_Вин.'утром'{ class:существительное } }
  then -1
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { ГлаголыПоедания_Вин.'днем'{ class:существительное } }
  then -1
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { ГлаголыПоедания_Вин.'вечером'{ class:существительное } }
  then -1
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { ГлаголыПоедания_Вин.'ночью'{ class:существительное } }
  then -1
}



tree_scorer ВалентностьГлагола language=Russian
{
 if context { ГлаголыПоедания_Вин.<ATTRIBUTE>наречие:днем{} }
  then 1
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { ГлаголыПоедания_Вин.<ATTRIBUTE>наречие:вечером{} }
  then 1
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { ГлаголыПоедания_Вин.<ATTRIBUTE>наречие:ночью{} }
  then 1
}
*/


// желая стать космонавтом
//       ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:стать{}.<OBJECT>существительное:*{ падеж:твор одуш:одуш } }
  then 1
}

// Царя над окрестностями
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:царить{}.'над'.'окрестностями' }
  then 1
}


// Планета Юпитер не видна днём
//                   ^^^^^^^^^^
tree_scorer language=Russian
{
 if context { прилагательное:видный{ краткий }.<ATTRIBUTE>'днем'{} }
  then 1
}




// Подавим распознавание ПОТОМ как существительного:
// вы едите пюре или суп, потом пьете чай
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{}.<OBJECT>'потом'{падеж:твор} }
  then -100
}



tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{}.<OBJECT>'потом'{падеж:твор} }
  then -100
}


// Для глагола ЛОВИТЬ подавляем прямое дополнение в творительном падеже, если
// оно соответствует одушевленному:
// Антонио опять ловит мышь несколько ночей подряд
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ловить{}.<OBJECT>существительное:*{ падеж:твор одуш:одуш } }
  then -1
}


// продавать книги
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:продавать{}.<OBJECT>существительное:*{ падеж:вин } }
  then 1
}


// мы не увидели тебя
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:увидеть{}.<OBJECT>местоимение:*{ падеж:вин } }
  then 1
}


// Винительная валентность глагола ГОВОРИТЬ используется
// только с неодушевленным дополнением.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:говорить{}.<OBJECT>*{ падеж:вин } }
  then -1
}



// кот не видит ее
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:видеть{}.<OBJECT>местоимение:я{ падеж:вин } }
  then 1
}





// кот увидел кенгуру на полу
//     ^^^^^^ ^^^^^^^
// Подавим вариант творительного падежа для любых дополнение, за исключением ГЛАЗ
// а неодушевленные пусть будут "увидел своими глазами"
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:увидеть{}.<OBJECT>существительное:глаз{ падеж:твор } }
  then 2
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:видеть{}.<OBJECT>существительное:глаз{ падеж:твор } }
  then 2
}



tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:увидеть{}.<OBJECT>существительное:*{ падеж:твор } }
  then -1
}


// Дмитрий Иванович Менделеев увидел периодическую таблицу элементов во сне
//                            ^^^^^^                                 ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:увидеть{}.'во'.'сне' }
  then 1
}



// аналогично для:
// кот видит кенгуру на полу
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:видеть{}.<OBJECT>существительное:*{ падеж:твор } }
  then -1
}


// Для глагола ВСТРЕТИТЬ подавим прямое дополнение в творительном падеже, если
// оно - одушевленный объект:
// ведьмёныш встретил Антонио
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:встретить{}.<OBJECT>существительное:*{ падеж:твор одуш:одуш } }
  then -1
}

// Аналогично: ведьмёныш встречал Антонио веселым криком
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:встречать{}.<OBJECT>существительное:*{ падеж:твор одуш:одуш } }
  then -1
}




wordentry_set ЧтоМожноДелатьСЧаем=
{
 инфинитив:налить{},
 глагол:налить{}
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { ЧтоМожноДелатьСЧаем.<OBJECT>'чаю'{падеж:парт} }
  then 1
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:ловить{}.предлог:в{}.существительное:*{ падеж:предл } }
  then 1
}


// мыть руки с мылом
tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:мыть{}.'с'.'мылом' }
  then 1
}

// Я мою руки с мылом
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:мыть{}.'с'.'мылом' }
  then 1
}


// кошки собираются ловить хозяину в амбаре мышь
tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:ловить{}.'в'.'амбаре' }
  then 1
}



// Мы боремся все доступными средствами с ошибками в программе
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:бороться{}.'с'.'ошибками' }
  then 1
}




// большой злой пират и его отчаянные помощники высадились на необитаемом острове для поиска зарытых сокровищ
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:высадиться{}.'для'.'поиска' }
  then 1
}



// стипендия студента университета дружбы народов, живших в союзных республиках бывшего СССР
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:живший{}.предлог:в{}.существительное:*{ падеж:предл } }
  then 1
}


// студенты университета, построенного в СССР
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:построенный{}.предлог:в{}.существительное:*{ падеж:предл } }
  then 1
}


// группа студентов университета дружбы народов, основанного в СССР
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:основанный{}.предлог:в{}.существительное:*{ падеж:предл } }
  then 1
}


// группа студентов университета дружбы народов, активно пропагандировавшейся в СССР
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:пропагандировавшийся{}.предлог:в{}.существительное:*{ падеж:предл } }
  then 1
}




tree_scorer ВалентностьГлагола language=Russian
{
 if context { 'сыплет'{class:глагол}.<SUBJECT>существительное:дождь{ падеж:им } }
  then 1
}





tree_scorer language=Russian
{
 if context { безлич_глагол:стало{}.'всем'{ class:прилагательное падеж:дат} }
  then 1
}


// давай-ка выпей молока
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:выпить{}.'молока'{class:существительное} }
  then 1
}



// лежащий на полу
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:лежащий{}.предлог:на{}.'полу'{падеж:мест} }
  then 1
}

// Подавим распознавание ДНЁМ как существительного в творительном падеже.
//
// кошки днем обычно ели и дремали
//       ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:есть{}.<OBJECT>существительное:день{ падеж:твор } }
  then -1
}

// Несмотря на появляющуюся родительную валентность в отрицательной форме глагола,
// местоимения её и его надо брать только в аккузативе.
// она её не съест
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:съесть{}.'ее'{ падеж:вин } }
  then 1
}

/*
// Планета Марс видна утром
tree_scorer language=Russian
{
 if context { прилагательное:видный{}.наречие:утром{} }
  then 1
}
*/

/*
// Повысим достоверность безличного глагола.
//
// Грести стало труднее
//        ^^^^^
tree_scorer language=Russian
{
 if context { 'стало'{class:безлич_глагол} }
  then 1
}
*/

// Для глагола КУПИТЬ надо подавлять связывание с прямым дополнением в родительным падеже
// для живых существ.
// Ну же, купите слона!
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:купить{}.<OBJECT>существительное:*{ ОДУШ:ОДУШ падеж:род } }
  then -1
}


// купи кефиру
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:купить{}.<OBJECT>существительное:*{ ОДУШ:НЕОДУШ падеж:парт } }
  then 4
}


// налей мне воды
// ^^^^^     ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:налить{}.<OBJECT>'воды'{ падеж:род } }
  then 2
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:лежать{}.'в'.'углу' }
  then 1
}


// ОСВЕТИТЬ можно обычно КОМУ-ТО, а не чему-то:
// отблеск молнии осветил часового.
//                ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:осветить{}.существительное:*{ падеж:дат одуш:неодуш } }
  then -10
}




// Он ездит на работу на автобусе.
//    ^^^^^           ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ездить{}.предлог:на{}.существительное:*{ падеж:предл одуш:неодуш <в_класс>существительное:транспорт{} } }
  then 2
}


// Его успех доставил ей радость.
//           ^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:доставить{}.{ <OBJECT>ОдушОбъект{ падеж:дат } <OBJECT>НеодушОбъект{ падеж:вин } } }
  then 2
}



/*
// Предотвращаем отрыв слова ЭТОТ, ЭТОЙ и т.д. от существительного.
// Роберт улыбнулся этой мысли.
//                  ^^^^^^^^^^
tree_scorer language=Russian
{
 if context { существительное:*{}.<ATTRIBUTE>прилагательное:этот{} }
  then 2
}
*/





// Речки разлились и дороги стали непроходимы.
//                          ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:стать{}.прилагательное:*{ краткий } }
  then 1
}


// укрыться от дождя под навесом
// ^^^^^^^^          ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:укрыться{}.предлог:под{}.НеодушОбъект }
  then 2
}




// Мул - помесь осла и лошади.
//       ^^^^^^^^^^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { существительное:помесь{}.существительное:*{}.союз:и{} }
  then 1
}


// Олег обвел взглядом окрестности.
//      ^^^^^          ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обвести{}.<OBJECT>*:*{ падеж:вин } }
  then 1
}

// Олег хмуро окинул взглядом убитого.
//            ^^^^^^          ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:окинуть{}.<OBJECT>*:*{ падеж:вин } }
  then 1
}

// мои предки построили его собственными руками.
//            ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:построить{}.<OBJECT>НеодушОбъект{ падеж:вин } }
  then 5
}


// иначе им грозит беда.
//       ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:грозить{}.<OBJECT>*:*{ падеж:дат } }
  then 1
}


// Джим поискал глазами своего коня.
//      ^^^^^^^         ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:поискать{}.<OBJECT>ОдушОбъект{ падеж:вин } }
  then 1
}


// вера дает им силу.
//      ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:давать{}.<OBJECT>*:*{ падеж:дат } }
  then 1
}

// им дорого обойдется сегодняшний бой.
// ^^        ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обойтись{}.<OBJECT>*:*{ падеж:дат } }
  then 1
}

// киммериец молча пожал ей руку.
//                 ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пожать{}.{ <OBJECT>ОдушОбъект{ падеж:дат } <OBJECT>НеодушОбъект{ падеж:вин } } }
  then 1
}

// ей ответил пронзительный яростный визг.
// ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ответить{2}.<OBJECT>местоимение:я{ 1 падеж:дат } }
  then 1
}

// Он ответил Джо
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ответить{1}.<OBJECT>ОдушОбъект{ 2 падеж:дат } }
  then 2
}



// зачем давать им пустую надежду.
//       ^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пожать{}.{ <OBJECT>ОдушОбъект{ падеж:дат } <OBJECT>НеодушОбъект{ падеж:вин } } }
  then 2
}

// тебе следовало оставить ей записку.
//                ^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:оставить{}.{ <OBJECT>ОдушОбъект{ падеж:дат } <OBJECT>НеодушОбъект{ падеж:вин } } }
  then 2
}


// маленький желтый череп улыбнулся ей.
//                        ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:улыбнуться{1}.<OBJECT>ОдушОбъект{ 2 падеж:дат } }
  then 2
}


// Томас швырнул ей птицу.
//       ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:швырнуть{1}.{ <OBJECT>ОдушОбъект{ 2 падеж:дат } <OBJECT>*:*{ падеж:вин } } }
  then 2
}



// дом чрезвычайно понравился ей.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:понравиться{}.<OBJECT>ОдушОбъект{ падеж:дат } }
  then 2
}

// меч им явно нравился.
//     ^^      ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:нравиться{}.<OBJECT>ОдушОбъект{ падеж:дат } }
  then 2
}


// некоторым действительно нравится моя работа.
// ^^^^^^^^^               ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:нравиться{}.<OBJECT>прилагательное:*{ падеж:дат число:мн ~краткий } }
  then 4
}


// лунный свет помогал им.
//             ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:помогать{}.<OBJECT>*:*{ падеж:дат } }
  then 3
}


// им необходимо было помочь.
// ^^                 ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:помочь{}.<OBJECT>ОдушОбъект{ падеж:дат } }
  then 2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:помогать{}.<OBJECT>ОдушОбъект{ падеж:дат } }
  then 2
}


// мой отец убит им. 
//          ^^^^^^^
tree_scorer language=Russian
{
 if context { прилагательное:убитый{}.<OBJECT>*:*{ падеж:твор } }
  then 1
}


// ей надо уйти отсюда.
// ^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:надо{}.{ ОдушОбъект{ падеж:дат } инфинитив:*{} } }
  then 1
}

// ей вдруг захотелось уйти.
// ^^^      ^^^^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:захотелось{}.{ ОдушОбъект{ падеж:дат } инфинитив:*{} } }
  then 1
}


// капитан пожал им руки.
//         ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пожать{}.{ <OBJECT>*:*{ падеж:дат } <OBJECT>НеодушОбъект{ падеж:вин } } }
  then 2
}


// хозяин жеребца снова закричал. (закричать можно ЧТО-ТО, но не КОГО-ТО)
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:закричать{}.<OBJECT>ОдушОбъект{ падеж:вин } }
  then -100
}

// ей явно понравился ответ.
// ^^      ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:понравиться{}.<OBJECT>ОдушОбъект{ падеж:дат } }
  then 1
}

// остальным предстояло помогать им.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:помогать{}.<OBJECT>ОдушОбъект{ падеж:дат } }
  then 1
}

// им стало вдруг зябко.
// ^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:стало{}.ОдушОбъект{ падеж:дат } }
  then 1
}

// нам стало жалко бедного котенка
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:жалко{}.ОдушОбъект{ падеж:дат } }
  then 2
}


// император осторожно коснулся пальцами белой перчатки.
//                     ^^^^^^^^          ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:коснуться{}.<OBJECT>*:*{ падеж:род } }
  then 1
}


// обычно ПРОТЯНУТЬ кому-то, а не чему-то:
// тот протянул руку помощи.
//     ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:протянуть{}.<OBJECT>НеодушОбъект{ падеж:дат } }
  then -5
}


// возле всякой двери тебя ждала такая же ловушка.
//                    ^^^^^^^^^^
// однако сперва ее ждало глубокое разочарование.
//               ^^ ^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:ждать{}.<OBJECT>местоимение:я{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:подождать{}.<OBJECT>местоимение:я{ падеж:вин } } then 2 }


// однако ему удалось открыть нечто интересное.
//                    ^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:открыть{}.<OBJECT>НеодушОбъект{ падеж:вин } }
  then 1
}

// однако название мне удалось прочитать.
//        ^^^^^^^^             ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:прочитать{}.<OBJECT>НеодушОбъект{ падеж:вин } }
  then 1
}

// пройти можно ЧТО-ТО:
// ты уже прошел его так много раз.
//        ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пройти{}.<OBJECT>ОдушОбъект{ падеж:вин } }
  then -1
}

/*
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пройти{}.<OBJECT>НеодушОбъект{ падеж:вин } }
  then 1
}
*/

// злость прошла довольно давно.
// ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пройти{}.<SUBJECT>НеодушОбъект }
  then 1
}







// затем стал внимательно изучать глаз юноши.
//                        ^^^^^^^ ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:изучать{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}


// комната ожидания полна народу.
//                  ^^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { прилагательное:полный{ краткий }.существительное:*{ падеж:род } }
  then 1
}

tree_scorer language=Russian
{
 if context { прилагательное:полный{ краткий }.существительное:*{ падеж:парт } }
  then 1
}


// развалиться на части
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:развалиться{}.'на'.'части'{ падеж:вин } }
  then 2
}


// ВЗЯТЬ можно КОМУ-ТО, а не ЧЕМУ-ТО:
// полковник взял микрофон внутренней связи.
//           ^^^^                     ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:взять{}.<OBJECT>НеодушОбъект{ падеж:дат } }
  then -5
}


// оставался единственный способ проверить корабль.
//                               ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:проверить{}.<OBJECT>*:*{ падеж:вин } }
  then 1
}

// ТРЕБОВАТЬ можно кому-то, а не чему-то:
// моя месть требует радости охоты.
//           ^^^^^^^ ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:требовать{}.<OBJECT>НеодушОбъект{ падеж:дат } }
  then -5
}


// ПРОДОЛЖИТЬ можно ЧТО-ТО неодушевленное:
// вскоре отряд продолжил путь.
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:продолжить{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:продолжить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then -1 }


// Ломать душу
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:ломать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:ломать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 1 }


// я доволен им
//   ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:довольный{ краткий }.<OBJECT>*:*{ падеж:твор } }
  then 2
}


// Обычно получить можно кому-то, а не чему-то:
// поэтому хотим получить максимум информации.
//               ^^^^^^^^          ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:получить{}.<OBJECT>НеодушОбъект{ падеж:дат } }
  then -2
}



// пришла пора сделать следующий шаг.
// ^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:прийти{}.<SUBJECT>существительное:пора{}.инфинитив:*{} }
  then 1
}

// убить КОГО-ТО:
// ты должен его убить!
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:убить{}.<OBJECT>НеодушОбъект{ падеж:вин } } then -1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:убивать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then -1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:убить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:убивать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }


// мне едва удалось его спасти.
// ^^^      ^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:удалось{}.<SUBJECT>ОдушОбъект{ падеж:дат } }
  then 2
}

// им удалось вытащить его из озера.
// ^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:удалось{}.<SUBJECT>*:*{ падеж:дат } }
  then 1
}


// ЕДА не может быть продавцом:
// В булочной продают хлеб, булки, печенье.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:продавать{}.<SUBJECT>существительное:*{ <в_класс>существительное:еда{} } }
  then -100
}




// ОБЪЯСНИТЬ можно обычно кому-то:
// происхождение информации объясню позднее.
//               ~~~~~~~~~~ ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:объяснить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:объяснить{}.<OBJECT>ОдушОбъект{ падеж:дат } } then 1 }



#region СОЗДАВАТЬ
// если получатель действия находится слева от глагола, то штрафуем:
// банки памяти создавали самую большую проблему.
//       ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:создавать{ 2 }.<OBJECT>*:*{ падеж:дат 1 } }
  then -1
}

// Но компенсируем предыдущее правило, если получатель - одушевленный:
// нам создали тепличные условия
// ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:создавать{ 2 }.<OBJECT>ОдушОбъект{ падеж:дат 1 } }
  then 1
}
#endregion СОЗДАВАТЬ


// Обычно ПОКАЗАТЬСЯ можно КОМУ-ТО:
// показалась машина местной полиции.
// ^^^^^^^^^^                ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:показаться{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:показаться{}.<OBJECT>ОдушОбъект{ падеж:дат } } then 1 }


// БЕЖАТЬ можно чем-то неодушевленным, например - БЕРЕГОМ:
// бегущим по берегу псом
// ^^^^^^^           ^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:бежать{}.<OBJECT>ОдушОбъект{ падеж:твор } } then -100 }


// Чтобы подавить распознавание существительным "БЫЛЬ":
// "Обвиняемые были освобождены в зале суда"
//  ^^^^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:быть{ 2 }.<SUBJECT>прилагательное:*{ падеж:им ~краткий степень:атриб 1 } }
  then 2
}

// ПОИСКАТЬ обычно можно КОМУ-ТО:
// Давайте поищем примеры реализации этой функции
//         ^^^^^^         ~~~~~~~~~~      ~~~~~~~
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:поискать{}.<OBJECT>НеодушОбъект{ падеж:дат } }
  then -1
}


// Обычно ПРИХОДИТ КОМУ-ТО, а неодушевленный реципиент возможет лишь в
// особых оборотах типа КОНЕЦ ПРИШЕЛ ЭТОЙ АФЕРЕ.
// неизвестно откуда пришло вдруг чувство опасности.
//                   ^^^^^^               ~~~~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:прийти{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -3 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:придти{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -3 }


// советую вам исправить свою ошибку.
// ^^^^^^^ ^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:советовать{}.<OBJECT>ОдушОбъект{ падеж:дат } }
  then 2
}


// Подавим связывание ПРИШЛО и ПОЗАБОТИТЬСЯ исходя из того, что обычно
// только одушевленные субъекты приходят сделать что-то:
// однако пришло время позаботиться о собственной безопасности.
//        ^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:придти{}.{ <SUBJECT>НеодушОбъект инфинитив:*{} } } then -1 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:прийти{}.{ <SUBJECT>НеодушОбъект инфинитив:*{} } } then -1 }


// Зайти можно КОМУ-ТО
// сам зашел снаружи конструкции противника.
//     ^^^^^         ~~~~~~~~~~~
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:зайти{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }



// обычно глагол ЗАНЯТЬ идет с винительным дополнением:
// эти приготовления заняли целый день.
//                   ^^^^^^ ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:занять{}.<OBJECT>*:*{ падеж:вин } } then 1 }


// Сжать обычно можно КОМУ-ТО:
// Олег изо всех сил сжал челюсти.
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:сжать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }




// после начала битвы прошли считанные секунды.
//                    ^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:пройти{}.<SUBJECT>ИнтервалВремени{ ПАДЕЖ:ИМ } }
  then 1
}


// желаю тебе найти принца.
// ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:желать{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ } }
  then 1
}

// Он рекомендовал мне сделать это.
//    ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:рекомендовать{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ } }
  then 1
}

// Он угрожал мне бросить работу.
//    ^^^^^^^ ^^^ ~~~~~~~
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:угрожать{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ } }
  then 1
}


// позволю себе напомнить историю вопроса.
// ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:позволить{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ } }
  then 1
}

// Олег хмуро окинул взглядом убитого.
//            ^^^^^^ ^^^^^^^^ ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:окинуть{}.{ <OBJECT>*:*{ ПАДЕЖ:ВИН } <OBJECT>'взглядом' } }
  then 1
}


// где же моя благодарность?
// ^^^^^^     ^^^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { наречие:где{}.{ частица:же{} существительное:*{ падеж:им } } }
  then 1
}


// кому хочется есть
// ^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:хочется{}.<SUBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ } }
  then 1
}



// нам нужно только доставить его туда.
// ^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:нужно{}.<SUBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ } }
  then 2
}



// ТОРЖЕСТВОВАТЬ можно ЧТО-ТО неодушевленное:
// Весь  день и весь вечер шумел и торжествовал народ по всему королевству
//                                 ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:торжествовать{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ВИН } }
  then -100
}


// МЕШАТЬ кому-то ДЕЛАТЬ что-то
// страх мешал ей плакать.
//       ^^^^^ ^^ ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:мешать{}.{ <OBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ } инфинитив:*{} } }
  then 2
}



// ПОВТОРИТЬ можно обычно КОМУ-ТО, а не ЧЕМУ-ТО
// мастер песни повторил вопрос.
//        ~~~~~ ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:повторить{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } }
  then -10
}


// вскоре подошел поезд метро.
//        ^^^^^^^       ~~~~~
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:подойти{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } }
  then -10
}

// ОТКРЫВАТЬСЯ можно обычно КОМУ-ТО
// новый мир открывался после каждой мили пути.
//           ^^^^^^^^^^                   ~~~~
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:открываться{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } }
  then -10
}


// Обычно СЛОЙ покрывает что-то, даже если порядок слов обратный нормальному:
// пол покрывал толстый слой пыли.
//     ^^^^^^^^         ^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:покрывать{}.{ <SUBJECT>существительное:слой{} НеодушОбъект{ ПАДЕЖ:ВИН } } }
  then 2
}




// Ей нравится ходить туда.
// ^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:нравилось{}.<SUBJECT>*:*{ ПАДЕЖ:ДАТ } }
  then 2
}




// оставался единственный способ проверить корабль.
//                               ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:проверить{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } }
  then 2
}



// кому вы отдали его?
// ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:*{}.<OBJECT>'кому'{ падеж:дат class:местоим_сущ } }
  then 2
}


// кому может понадобиться старая чужая лодка?
// ^^^^       ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:*{}.<OBJECT>'кому'{ падеж:дат class:местоим_сущ } }
  then 2
}




// Не смей мне врать!
//         ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:врать{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ } }
  then 2
}




// меня все здесь боятся!
// ^^^^           ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:бояться{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ВИН } }
  then 1
}



// Он мучает её своим бесчувствием.
//    ^^^^^^ ^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:мучить{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } }
  then 1
}




// почему ты позволил им упасть?
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:позволить{}.<OBJECT>*:*{ падеж:дат } }
  then 2
}


// разве обычные люди могут читать мысли?
//                          ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:читать{}.<OBJECT>НеодушОбъект{ падеж:вин } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:читать{}.<OBJECT>ОдушОбъект{ падеж:дат } }
  then 1
}





// НАЗЫВАТЬ обычно идет с винительным дополнением:
// все его называют сегодня мальчиком.
//     ^^^ ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:называть{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}


// Подавляем присоединение послелогов к существительным:
// недалеко от него лежал человек лицом вниз.
//                        ~~~~~~~ ^^^^^^^^^^
tree_scorer language=Russian { if context { существительное:*{}.послелог:вниз{} } then -10 }
tree_scorer language=Russian { if context { существительное:*{}.послелог:вверх{} } then -10 }
tree_scorer language=Russian { if context { существительное:*{}.послелог:вперед{} } then -10 }




// Показывать на одушевленного (вин) - это важно, если объект несклоняемый:
// Вадим показал на Элен
//       ^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:показать{}.предлог:на{}.ОдушОбъект{ падеж:вин } }
  then 1
}




// пора им всем возвращаться домой.
//      ~~~~~~~ ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:возвращаться{}.ОдушОбъект{ падеж:твор } }
  then -10
}


// мама души не чаяла в своих детях
// ~~~~ ^^^^ ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:чаять{}.<OBJECT>существительное:душа{} }
  then 30
}

// Комар носа не подточит.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:подточить{}.{ частица:не{} <OBJECT>существительное:нос{} } }
  then 30
}


/*
// с тех пор ты видел его всего несколько раз.
//                        ^^^^^^^^^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { наречие:всего{}.наречие:несколько{}.существительное:раз{} }
  then 2
}
*/


// Руперт вопреки себе улыбнулся.
//        ^^^^^^^      ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{}.предлог:вопреки{} }
  then 2
}


// вам следует проверить Марину согласно инструкции.
//             ^^^^^^^^^        ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic { if context { глагол:*{}.предлог:согласно{} } then 2 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { инфинитив:*{}.предлог:согласно{} } then 2 }




// убийство для них естественно.
tree_scorer language=Russian { if context { прилагательное:естественный{}.предлог:для{} } then 2 }


// Пусть предложное дополнение с У присоединяется к глаголу, а не к существительному:
// ноги у меня болели.
//      ^      ^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic { if context { глагол:*{}.предлог:у{} } then 2 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { инфинитив:*{}.предлог:у{} } then 2 }



// Антон ее так назвал.
//       ^^     ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:назвать{}.<OBJECT>*:*{ падеж:вин } }
  then 1
}





// Наречие ЧАСТО служит косвенным признаком изъявительной, а не императивной формы глагола:
// ты часто ешь хлеб
//          ^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{ наклонение:побуд }.наречие:часто{} }
  then -2
}


// Наречие ОЧЕНЬ служит косвенным признаком изъявительной, а не императивной формы глагола:
// вы очень любите ягоды
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{ наклонение:побуд }.наречие:очень{} }
  then -2
}




// несколько дней спустя путников ожидал приятный сюрприз.
//                       ^^^^^^^^ ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ожидать{}.ОдушОбъект{ ПАДЕЖ:ВИН } }
  then 1
}


// ПРИВЛЕЧЬ обычно можно КОГО-ТО одушевленного:
// Его привлекли к ответственности за нарушение порядка.
// ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:привлечь{}.ОдушОбъект{ ПАДЕЖ:ВИН } }
  then 1
}


// Его целый год держали в тюрьме.
// ^^^           ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:держать{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } }
  then 4
}







// ОБЕЩАТЬ КОМУ-ТО СДЕЛАТЬ что-то:
// ты обещал мне показать корабль!
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обещать{}.{ <OBJECT>ОдушОбъект{ПАДЕЖ:ДАТ} инфинитив:*{} } }
  then 2
}

// чиновник приказал ему открыть два кожаных мешка.
//          ^^^^^^^^ ^^^ ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:приказать{}.{ <OBJECT>ОдушОбъект{ПАДЕЖ:ДАТ} инфинитив:*{} } }
  then 5
}

// ++++++++++++++++++++++++++++++++++++++++

// мне обещали все вернуть назад
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обещать{}.{ <OBJECT>ОдушОбъект{ПАДЕЖ:ДАТ} инфинитив:*{} } }
  then 5
}

// ++++++++++++++++++++++++++++++++++++++++

// мне обещали все вернуть назад

// Его гордость не позволяла ему просить об одолжении.
//                 ^^^^^^^^^ ^^^ ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:позволять{}.{ <OBJECT>ОдушОбъект{ПАДЕЖ:ДАТ} инфинитив:*{} } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:позволить{}.{ <OBJECT>ОдушОбъект{ПАДЕЖ:ДАТ} инфинитив:*{} } } then 2 }




// такое устройство для моих целей бесполезно.
//       ~~~~~~~~~~ ^^^            ^^^^^^^^^^
tree_scorer language=Russian { if context { прилагательное:бесполезный{}.предлог:для{} } then 2 }



// ДАТЬ отчет можно обычно КОМУ-ТО, а не чему-то:
// Он дал подробный отчёт о своей поездке.
//    ^^^           ^^^^^         ~~~~~~~
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:дать{}.{ <OBJECT>существительное:отчет{} <OBJECT>НеодушОбъект{ПАДЕЖ:ДАТ} } }
  then -10
}


// отстегнуть маме денег
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:отстегнуть{}.{ <OBJECT>НеодушОбъект{ падеж:род } <OBJECT>ОдушОбъект{ПАДЕЖ:ДАТ} } }
  then 5
}




// все вас боятся
// ~~~~~~~
tree_scorer language=Russian
{
 if context { 'вас'.'все'{class:прилагательное} }
  then -100
}


// Я работаю учителем в сельской школе
//   ^^^^^^^          ^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:работать{}.предлог:в{}.*:*{падеж:предл} } then 2 }





// небеса для меня закрыты.
//        ^^^      ^^^^^^^^
tree_scorer language=Russian { if context { прилагательное:закрытый{}.предлог:для{} } then 2 }


// Это такое трудное слово, что он не может его запомнить.
//                                          ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:запомнить{}.<OBJECT>*:*{ падеж:вин } } then 2 }



// Его утомляла долгая ходьба.
// ^^^ ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:утомлять{}.ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:утомить{}.ОдушОбъект{ падеж:вин } } then 2 }


// но где удалось его добыть?
//                ^^^ ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:добыть{}.НеодушОбъект{ падеж:вин } } then 2
}




// кладбище от моря довольно далеко
// ~~~~~~~~ ^^               ^^^^^^
tree_scorer language=Russian { if context { прилагательное:далекий{}.предлог:от{} } then 2 }




// мы внедряем в жизнь идеи великих ученых
//    ^^^^^^^^         ^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:внедрять{}.<OBJECT>НеодушОбъект{ПАДЕж:ВИН} } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:внедрить{}.<OBJECT>НеодушОбъект{ПАДЕж:ВИН} } then 2 }

// неужели разговор его окончательно сломал?
//                  ^^^              ^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сломать{}.<OBJECT>*:*{ПАДЕж:ВИН} } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:ломать{}.<OBJECT>*:*{ПАДЕж:ВИН} } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:поломать{}.<OBJECT>*:*{ПАДЕж:ВИН} } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:переломать{}.<OBJECT>*:*{ПАДЕж:ВИН} } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:обломать{}.<OBJECT>*:*{ПАДЕж:ВИН} } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:обламывать{}.<OBJECT>*:*{ПАДЕж:ВИН} } then 2 }

// Критика должна составлять душу журнала.
//                ^^^^^^^^^^ ^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:составлять{1}.<OBJECT>НеодушОбъект{ 2 ПАДЕж:ВИН} } then 1 }



// ПОРАЗИТЬ обычно можно КОГО-ТО, а не чего-то:
// однако его глубоко поразило одно событие.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:поразить{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ВИН } }
  then 2
}

// такое положение вещей его вполне устраивает.
//                       ^^^        ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:устраивать{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:устроить{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }



// Обычно ПОИСКАТЬ можно КОМУ-ТО, а не чему-то:
// Давайте поищем примеры реализации этой функции
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:поискать{}.<OBJECT>НеодушОбъект{ПАДЕж:ДАТ} } then -1 }




// Давать КОМУ-ТО ЧЕГО-ТО:
// Рита дает девочке хлеба.
//      ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:давать{}.{
                                  <OBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ }
                                  <OBJECT>НеодушОбъект{ ПАДЕЖ:РОД }
                                 }
            }
  then 5
}

// Я дам им чаю
//   ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:дать{}.{
                                <OBJECT>*:*{ ПАДЕЖ:ДАТ }
                                <OBJECT>*:*{ ПАДЕЖ:ПАРТ }
                               }
            }
  then 5
}


// попросил передать управление станции.
//          ^^^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:передать{}.{
                                    <OBJECT>*:*{ ПАДЕЖ:ВИН }
                                    <OBJECT>*:*{ ПАДЕЖ:ДАТ }
                                   }
            }
  then 5
}



// ЕСТЬ могут обычно только одушевленные:
// Антонио ест суп и пюре
// ^^^^^^^ ^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:есть{}.{ <SUBJECT>ОдушОбъект{} <OBJECT>*:*{ падеж:вин } } }
  then 1
}

/*
// есть несколько возможных вариантов.
tree_scorer language=Russian
{
 if context { rus_verbs:быть{}.наречие:несколько{}.существительное:*{} }
  then 1
}
*/


// Мы можем использовать эти сюжеты в молитвах.
//          ^^^^^^^^^^^^            ^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:использовать{}.предлог:в{}.*:*{ падеж:предл } }
  then 2
}


// ЛУЧШЕ+инфинитив является очень частотным паттерном, в отличие от использования ЛУЧШЕ в качестве
// простого атрибута глагола (как в СТАРАЙСЯ ЛУЧШЕ!)
// лучше избавиться от обезьяны
// ^^^^^ ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { безлич_глагол:лучше{1}.инфинитив:*{2} } then 2
}


// ПОКОРМИТЬ можно кого-то одушевленного:
// Мы покормили белок.
//    ^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:покормить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:кормить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:накормить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 1 }


// СЛУШАТЬСЯ кого-то/вин:
// слушаться родителей
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:слушаться{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:послушаться{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 1 }


// ПОЛОЖИТЬ кого-то/вин/:
// Нам придётся положить его в больницу.
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:положить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:ложить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 1 }


// ХОТЕТЬ кому-то одуш
// хочу кофе
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:хотеть{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }

// КАК обычно является наречием, модифицирующим глаголы и инфинитивы
// однако как остановить профессора?
//        ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic { if context { инфинитив:*{2}.<ATTRIBUTE>наречие:как{1}.[not]*:*{} } then 2 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { глагол:*{2}.<ATTRIBUTE>наречие:как{1}.[not]*:*{} } then 2 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { безлич_глагол:*{2}.<ATTRIBUTE>наречие:как{1}.[not]*:*{} } then 2 }

// кроме того, КАК может атрибутировать наречия:
tree_scorer language=Russian { if context { наречие:*{ степень:атриб }.<ATTRIBUTE>наречие:как{} } then 1 }

// как будто они нас понимают
// ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic { if context { инфинитив:*{}.<ATTRIBUTE>наречие:как будто{} } then 7 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { глагол:*{}.<ATTRIBUTE>наречие:как будто{} } then 7 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { прилагательное:*{ причастие краткий }.<ATTRIBUTE>наречие:как будто{} } then 7 }

// внутри все выглядело как всегда
//                      ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic { if context { инфинитив:*{}.<ATTRIBUTE>наречие:как всегда{} } then 7 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { глагол:*{}.<ATTRIBUTE>наречие:как всегда{} } then 7 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { прилагательное:*{ причастие краткий }.<ATTRIBUTE>наречие:как всегда{} } then 7 }


// сегодня все было как обычно
//                  ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic { if context { инфинитив:*{}.<ATTRIBUTE>наречие:как обычно{} } then 7 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { глагол:*{}.<ATTRIBUTE>наречие:как обычно{} } then 7 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { прилагательное:*{ причастие краткий }.<ATTRIBUTE>наречие:как обычно{} } then 7 }


/*
// наречие КАК обычно не стоит справа от глагола в одиночку.
// убью как собаку.
//      ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{1}.<ATTRIBUTE>наречие:как{2}.[not]*:*{} }
  then -10
}
*/


// Олег вытянул вперед руки
//      ^^^^^^^        ^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:вытянуть{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:вытягивать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }


// теперь она могла его толком рассмотреть.
//                      ^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic { if context { инфинитив:*{}.<ATTRIBUTE>наречие:толком{} } then 2 }
tree_scorer ВалентностьГлагола language=Russian generic { if context { глагол:*{}.<ATTRIBUTE>наречие:толком{} } then 2 }


// они быстро пересекли плато
//            ^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:пересечь{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:пересекать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }

// Как вызвать такси?
//     ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:вызвать{}.<OBJECT>*:*{ падеж:вин } } then 1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:вызывать{}.<OBJECT>*:*{ падеж:вин } } then 1 }

// наверху их охватил морской ветер.
//         ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:охватить{}.<OBJECT>*:*{ падеж:вин } } then 2 }





// Чиновник уже пообещал, что не будет покрывать своего родственника
//                                     ^^^^^^^^^        ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:покрывать{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } }
  then 2
}

// Толстые линии показывают связи между участками коры
//               ^^^^^^^^^^ ~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:показывать{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:показывать{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ДАТ } } then 2 }

// Олег хмуро окинул взглядом убитого.
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:окинуть{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }

// по левой стороне груди текла кровь.
//                  ~~~~~ ^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:течь{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } } then -2 }

// это может лишить наше общество работы
//           ^^^^^^               ^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:лишить{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:РОД } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:лишать{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:РОД } } then 2 }

// сбивая их сильной струей воды с надводной растительности
// ^^^^^^ ^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сбивать{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сбить{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }

// Лидеры организации хасидов заявили, что деньги их не интересуют
//                                                ^^    ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:интересовать{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }

// как радостно за руку ее схватили!
//                      ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:схватить{}.<OBJECT>местоимение:я{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:хватать{}.<OBJECT>местоимение:я{ ПАДЕЖ:ВИН } } then 2 }

// Антон поднес ладони к горлу
//       ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:поднести{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:подносить{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }


// оставшиеся вынуждены по очереди помогать ей двигаться вперед
//            ^^^^^^^^^            ^^^^^^^^
tree_scorer language=Russian { if context { прилагательное:вынужденный{}.инфинитив:*{} } then 2 }



// Артур погладил по носу старого коня
//       ^^^^^^^^                 ^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:погладить{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:гладить{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }

// ты можешь нас туда провести?
//           ^^^      ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:провести{}.<OBJECT>местоимение:я{ ПАДЕЖ:ВИН } } then 1 }

// провожают обычно одушевленные объекты, 
tree_scorer ВалентностьГлагола language=Russian { if context { глагол:проводить{ вид:соверш }.<OBJECT>НеодушОбъект{ падеж:вин } } then -5 }
tree_scorer ВалентностьГлагола language=Russian { if context { инфинитив:проводить{ вид:соверш }.<OBJECT>НеодушОбъект{ падеж:вин } } then -5 }

tree_scorer ВалентностьГлагола language=Russian { if context { глагол:проводить{ вид:несоверш }.<OBJECT>ОдушОбъект{ падеж:вин } } then -5 }
tree_scorer ВалентностьГлагола language=Russian { if context { инфинитив:проводить{ вид:несоверш }.<OBJECT>ОдушОбъект{ падеж:вин } } then -5 }

// у ворот всадников проводили жесткие темные глаза стражи
tree_scorer ВалентностьГлагола language=Russian { if context { глагол:проводить{ вид:соверш }.<OBJECT>ОдушОбъект{ падеж:вин } } then 1 }



// но это мешало им
//        ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:мешать{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:помешать{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:препятствовать{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }



// его можно предотвратить
// ^^^       ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:предотвратить{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:предотвращать{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:предотвратить{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ВИН } } then -10 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:предотвращать{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ВИН } } then -10 }

// им хорошо платят
// ^^        ^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:платить{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:заплатить{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }

// Гарри взял
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:взять{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:РОД } } then -1 }


// сигареты у него забрали
tree_scorer ВалентностьПредиката language=Russian { if context { rus_verbs:забрать{}.<SUBJECT>НеодушОбъект } then -1 }
tree_scorer ВалентностьПредиката language=Russian { if context { rus_verbs:брать{}.<SUBJECT>НеодушОбъект } then -1 }
tree_scorer ВалентностьПредиката language=Russian { if context { rus_verbs:забирать{}.<SUBJECT>НеодушОбъект } then -1 }

// тот принял ее мертвой рукой.
//     ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:принять{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:принимать{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }

// В США миллионера осудили за попытку продать Ирану детали для ракет ПВО
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:осудить{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:осуждать{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }


// Африканский союз позвал войска НАТО в Мали
//                  ^^^^^^             ^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:позвать{}.предлог:в{}.*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:звать{}.предлог:в{}.*:*{ падеж:вин } } then 2 }


// вряд ли это им понравится.
//             ^^ ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:понравиться{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }

// слушайся меня
// ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:слушаться{}.<OBJECT>*:*{ ПАДЕЖ:РОД } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:послушаться{}.<OBJECT>*:*{ ПАДЕЖ:РОД } } then 2 }

// все это ее непосредственно касалось.
//         ^^                 ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:коснуться{}.<OBJECT>*:*{ ПАДЕЖ:РОД } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:касаться{}.<OBJECT>*:*{ ПАДЕЖ:РОД } } then 2 }

// а громадный глаз подмигнул им
//                  ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:подмигнуть{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:подмигивать{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }


// ты мог бы им помочь.
//           ^^ ^^^^^^
//tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:помочь{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }
//tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:помогать{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } } then 2 }


// воины окружили их кольцом.
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:окружить{}.{ <OBJECT>*:*{ ПАДЕЖ:ВИН } <OBJECT>НеодушОбъект{ ПАДЕЖ:ТВОР } } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:окружать{}.{ <OBJECT>*:*{ ПАДЕЖ:ВИН } <OBJECT>НеодушОбъект{ ПАДЕЖ:ТВОР } } } then 2 }

// кому теперь нужны новые программы?
// ^^^^        ^^^^^
tree_scorer language=Russian { if context { прилагательное:нужный{}.<OBJECT>местоим_сущ:кто{ ПАДЕЖ:ДАТ } } then 2 }



// именно твое мнение для нас крайне важно.
//                    ^^^            ^^^^^
tree_scorer language=Russian { if context { прилагательное:важный{}.предлог:для{} } then 2 }


// от него ждали реакции.
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:ждать{}.{ <OBJECT>НеодушОбъект{ ПАДЕЖ:РОД } предлог:от{} } } then 2 }

// протер от пыли глаза.
// ^^^^^^         ^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:протереть{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:притирать{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } } then 2 }



// ты предпочел камни моей жизни.
// предпочесть ЧТО-ТО ЧЕМУ-ТО
tree_scorer ВалентностьГлагола language=Russian
{
 if context {
             rus_verbs:предпочесть{}.{
                                      <OBJECT>*:*{ падеж:вин }
                                      <OBJECT>*:*{ падеж:дат }
                                     }
            } then 2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context {
             rus_verbs:предпочитать{}.{
                                       <OBJECT>*:*{ падеж:вин }
                                       <OBJECT>*:*{ падеж:дат }
                                      }
            } then 2
}


// мы вынуждены просить вашей помощи.
//              ^^^^^^^       ~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:просить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:запросить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }

// Наречие ТАК обычно не модифицирует наречия места и времени:
// так где ты был?
tree_scorer language=Russian { if context { наречие:*{ ОБСТ_ВАЛ:МЕСТО }.наречие:так{} } then -100 }
tree_scorer language=Russian { if context { наречие:*{ ОБСТ_ВАЛ:НАПРАВЛЕНИЕ }.наречие:так{} } then -100 }
tree_scorer language=Russian { if context { наречие:*{ ОБСТ_ВАЛ:НАПРАВЛЕНИЕ_ОТКУДА }.наречие:так{} } then -100 }
tree_scorer language=Russian { if context { наречие:*{ ОБСТ_ВАЛ:МОМЕНТ_ВРЕМЕНИ }.наречие:так{} } then -100 }
tree_scorer language=Russian { if context { наречие:*{ ОБСТ_ВАЛ:КРАТНОСТЬ }.наречие:так{} } then -100 }




// равнина напоминала поле битвы.
//         ^^^^^^^^^^ ~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:напоминать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:напомнить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }


// Дети угостили белок орешками.
// УГОСТИТЬ можно КОГО-ТО
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:угостить{}.<OBJECT>НеодушОбъект{ падеж:вин } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:угощать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:угостить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:угощать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }

// хочешь кофе?
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:хотеть{}.<OBJECT>существительное:*{ падеж:род <в_класс>существительное:напиток{} } }
  then 1
}

// мы встретили охотника, способного догнать и поймать кенгуру
//                                             ^^^^^^^ ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:поймать{}.<OBJECT>*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:ловить{}.<OBJECT>*:*{ падеж:вин } } then 2 }

// протестующие начали собираться на площади
//                     ^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:собираться{}.предлог:на{}.*:*{ падеж:предл } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:собраться{}.предлог:на{}.*:*{ падеж:предл } }
  then 1
}


// Когда он вошел, все стаканы попадали с полки.
//                             ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:падать{}.предлог:с{}.*:*{ падеж:род } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:попадать{}.предлог:с{}.*:*{ падеж:род } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:упасть{}.предлог:с{}.*:*{ падеж:род } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:свалиться{}.предлог:с{}.*:*{ падеж:род } } then 2 }




// подруга Иды не пришла на урок
//                ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:придти{}.предлог:на{}.*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:прийти{}.предлог:на{}.*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:приходить{}.предлог:на{}.*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:зайти{}.предлог:на{}.*:*{ падеж:вин } } then 2 }

// Английская традиция акварели оказала сильное влияние на русских художников
//                     ~~~~~~~~ ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:оказать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:оказывать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then -2 }

// одна из женщин показалась ему знакомой.
//                ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:показаться{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }


// две женщины вывели из темноты раненого.
//             ^^^^^^            ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:вывести{}.*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:выводить{}.*:*{ падеж:вин } } then 2 }

// она часто просила меня рассказывать истории.
//                        ^^^^^^^^^^^^ ~~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:рассказать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:рассказывать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }

// Мы рассказывали о тех, кто менял мир
//    ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:рассказывать{}.предлог:о{}.*:*{ падеж:вин } } then -10
}


// к вечеру жара спала.
//          ^^^^ ~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { глагол:спать{}.<SUBJECT>НеодушОбъект } then -2 }





// Доллар снова сдает позиции
//              ^^^^^ ~~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сдавать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сдать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }

// жена полковника смотрела им вслед
//                 ^^^^^^^^    ^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:смотреть{}.послелог:вслед{} } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:посмотреть{}.послелог:вслед{} } then 2 }

// можно попытаться заменить собой стражу.
//                  ^^^^^^^^       ^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:заменить{}.<OBJECT>*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:заменять{}.<OBJECT>*:*{ падеж:вин } } then 2 }

// двое крестьян схватили за руки своего господина.
//               ^^^^^^^^                ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:схватить{}.<OBJECT>*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:хватить{}.<OBJECT>*:*{ падеж:вин } } then 2 }

// тебя вызывает начальник станции.
//      ^^^^^^^^           ~~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:вызывать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:вызвать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }


// тот молча сунул ей два факела.
//           ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сунуть{}.<OBJECT>*:*{ падеж:дат } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:совать{}.<OBJECT>*:*{ падеж:дат } } then 2 }

// Михаил зажал себе ладонью рот.
//        ^^^^^              ^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:зажать{}.<OBJECT>*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:зажимать{}.<OBJECT>*:*{ падеж:вин } } then 2 }

// им оставалось преодолеть около тридцати футов.
// ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { 'оставалось'{2 class:безлич_глагол}.<OBJECT>*:*{ 1 падеж:дат } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { 'остается'{2 class:безлич_глагол}.<OBJECT>*:*{ 1 падеж:дат } } then 2 }

// ей приходилось идти очень медленно.
// ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { 'приходилось'{ 2 class:безлич_глагол }.<OBJECT>*:*{ 1 падеж:дат } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { 'приходится'{2 class:безлич_глагол}.<OBJECT>*:*{ 1 падеж:дат } } then 2 }


// кого интересует мнение машины?
// ^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:интересовать{}.<OBJECT>ОдушОбъект{ падеж:дат } } then 2 }

// Газета сообщает об открытии сессии парламента.
//        ^^^^^^^^             ~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сообщать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сообщить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сообщать{}.<OBJECT>ОдушОбъект{ падеж:дат } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сообщить{}.<OBJECT>ОдушОбъект{ падеж:дат } } then 2 }

// ей довелось увидеть только последствия.
// ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { 'довелось'{2}.<OBJECT>*:*{ 1 падеж:дат } } then 2 }


// Геолог недавно открыл залежи руды.
//                ^^^^^^ ~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:открыть{}.<OBJECT>*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:открывать{}.<OBJECT>*:*{ падеж:вин } } then 2 }


// Дети не дают матери покоя.
//      ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context {
             rus_verbs:давать{}.{
                                 частица:не{}
                                 <OBJECT>*:*{ падеж:дат }
                                 <OBJECT>*:*{ падеж:род }
                                }
            } then 2
}


// Директор заявил, что уходит на пенсию.
//          ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:заявить{}.союз:что{} } then 2
}

// Люди провозгласили его гениальным писателем.
//      ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:провозгласить{}.<OBJECT>*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:провозглашать{}.<OBJECT>*:*{ падеж:вин } } then 2 }

// они создали магию крови.
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:создать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:создавать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }

// они боятся меня теперь.
//     ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:бояться{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }

// они называли ее железной.
//     ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:называть{}.<OBJECT>*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:назвать{}.<OBJECT>*:*{ падеж:вин } } then 2 }

// он отнес коробку к дедушке
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:отнести{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:относить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:отнести{}.<OBJECT>*:*{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:относить{}.<OBJECT>*:*{ падеж:вин } } then 2 }




// какой вес имеют эти вещи искусства?
//           ^^^^^     ~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:иметь{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -100 }

// но прежде нам необходимо найти тело
//           ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context {
             безлич_глагол:необходимо{}.{ 
                                         <SUBJECT>*:*{ падеж:дат }
                                         <INFINITIVE>инфинитив:*{}
                                        }
            } then 2
}


// вы можете предоставить ему другую работу?
//           ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:предоставить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:предоставлять{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:предоставить{}.<OBJECT>ОдушОбъект{ падеж:дат } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:предоставлять{}.<OBJECT>ОдушОбъект{ падеж:дат } } then 2 }




// Никто из присутствующих при этом не пострадал.
// ^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer language=Russian { if context { местоим_сущ:никто{}.предлог:из{} } then 5 }



// она протянула к огню руки.
//     ^^^^^^^^^        ^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:протянуть{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:протягивать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }

// почему она ему поверила?
//            ^^^ ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:поверить{1}.<OBJECT>ОдушОбъект{ 2 падеж:дат } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:верить{1}.<OBJECT>ОдушОбъект{ 2 падеж:дат } } then 2 }




// человек впервые показал эмоции.
//                 ^^^^^^^ ~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:показать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:показывать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }



// хочешь передать ему новость?
//        ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:передать{1}.<OBJECT>ОдушОбъект{ 2 падеж:дат } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:передавать{1}.<OBJECT>ОдушОбъект{ 2 падеж:дат } } then 2 }


// они зашли за угол крепости.
//     ^^^^^         ~~~~~~~~
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:зайти{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:заходить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }


// ты достаточно заплатил ему?
//               ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:заплатить{1}.<OBJECT>ОдушОбъект{ 2 падеж:дат } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:платить{1}.<OBJECT>ОдушОбъект{ 2 падеж:дат } } then 2 }

// их тоже стало меньше?
// ^^      ^^^^^
tree_scorer language=Russian { if context { 'стало'.<OBJECT>*:*{ падеж:род } } then 1 }
tree_scorer language=Russian { if context { 'станет'.<OBJECT>*:*{ падеж:род } } then 1 }

// ему хотелось выпить все озеро.
// ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { безлич_глагол:хочется{}.<SUBJECT>ОдушОбъект{ падеж:дат } } then 2 }


// как им хочется меня убить!
//     ^^^^^^^^^^      ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { безлич_глагол:хочется{}.{ <SUBJECT>ОдушОбъект{ падеж:дат } инфинитив:*{} } }
  then 2
}



// нам следует передать им это дело
// ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { безлич_глагол:следует{}.<SUBJECT>ОдушОбъект{ падеж:дат } } then 2 }


// все данные у него есть.
//            ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { 'есть'{ class:глагол 2 }.предлог:у{ 1 } } then 2 }


// сколько уверенности принесли они мне.
//                     ^^^^^^^^     ^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:принести{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:приносить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }

// возьмут ли меня туда?
// ^^^^^^^    ^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:взять{}.<OBJECT>местоимение:я{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:брать{}.<OBJECT>местоимение:я{ падеж:вин } } then 2 }

// она обхватила его руками за шею.
//     ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:обхватить{}.<OBJECT>местоимение:я{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:обхватывать{}.<OBJECT>местоимение:я{ падеж:вин } } then 2 }

// один из гномов ткнул его палкой.
//                ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:ткнуть{}.<OBJECT>местоимение:я{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:тыкать{}.<OBJECT>местоимение:я{ падеж:вин } } then 2 }

// такое обращение может его сильно обидеть.
//                       ^^^        ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:обидеть{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:обижать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:обидеть{}.<OBJECT>НеодушОбъект{ падеж:вин } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:обижать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then -2 }


// дай мне прикончить его!
//         ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:прикончить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:приканчивать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }


// теперь она может выслушать его.
//                  ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:выслушать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:выслушивать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }

// внешность этой женщины поразила его.
//                        ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:поразить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:поражать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }

// ты его недавно сделал?
//    ^^^         ^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:сделать{}.<OBJECT>местоимение:*{ падеж:вин } } then 2 }




// не смей вовлекать его в свои делишки
//         ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:вовлекать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:вовлечь{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }



// дилер выгодно продал акции
//               ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:продать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:продавать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }

// мы выдали ему костюм
// --> выдать обычно можно кому-то
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:выдать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:выдать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:выдать{}.<OBJECT>ОдушОбъект{ падеж:дат } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:выдавать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:выдавать{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:выдавать{}.<OBJECT>ОдушОбъект{ падеж:дат } } then 2 }



// я доверяю ему в этих вопросах
//   ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:доверять{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:доверить{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:доверять{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:доверить{}.<OBJECT>НеодушОбъект{ падеж:вин } } then 2 }

// Она хотела побыстрее его женить
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:женить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }


// его избили
// --> ИЗБИТЬ КОГО-ТО
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:избить{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:избивать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 2 }





// собственные слова тут же показались верхом глупости.
// ПОКАЗАТЬСЯ можно КОМУ-ТО, а не ЧЕМУ-ТО
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:показаться{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:казаться{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }


// мы продолжали поднимать тяжести
//               ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:поднимать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }




// Круче не придумаешь
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:придумать{}.<OBJECT>НеодушОбъект{ падеж:дат } } then -1 }


// Ключевая валютная пара останется волатильной
//                        ^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:остаться{}.прилагательное:*{ падеж:дат } } then -1 }
tree_scorer ВалентностьГлагола language=Russian { if context { rus_verbs:оставаться{}.прилагательное:*{ падеж:дат } } then -1 }



// остальные были заняты тем же
tree_scorer language=Russian { if context { прилагательное:занятый{ краткий }.*:*{ падеж:твор } } then 2 }





// записи мы посмотрим потом
// ^^^^^^    ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:посмотреть{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } } then -1
}



// целенаправленно обеспечивали его свежей продуктовой массой
//                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:обеспечивать{}.{
                              <OBJECT>*:*{ ПАДЕЖ:ВИН }
                              <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                             }
  } then 1
}

// Олег потрогал его ногой
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:потрогать{}.{
                           <OBJECT>*:*{ ПАДЕЖ:ВИН }
                           <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                          }
  } then 1
}

// хозяин пнул его ногой
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:пнуть{}.{
                       <OBJECT>*:*{ ПАДЕЖ:ВИН }
                       <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                      }
  } then 1
}

// Иван отодвинул его рукой
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:отодвинуть{}.{
                            <OBJECT>*:*{ ПАДЕЖ:ВИН }
                            <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                           }
  } then 1
}

// слуга вновь наполнил его вином
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:наполнить{}.{
                           <OBJECT>*:*{ ПАДЕЖ:ВИН }
                           <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                          }
  } then 1
}


// многие горожане сочли его попыткой скрыть преступление под давлением евреев
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:счесть{}.{
                        <OBJECT>*:*{ ПАДЕЖ:ВИН }
                        <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                       }
  } then 1
}


// Суд признал его виновным.
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:признать{}.{
                          <OBJECT>*:*{ ПАДЕЖ:ВИН }
                          <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                         }
  } then 1
}

// отец остановил ее жестом руки.
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:остановить{}.{
                            <OBJECT>*:*{ ПАДЕЖ:ВИН }
                            <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                           }
  } then 1
}


// молодой человек оттолкнул его взглядом!
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:оттолкнуть{}.{
                            <OBJECT>*:*{ ПАДЕЖ:ВИН }
                            <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                           }
  } then 1
}


// тот ловко подхватил его левой рукой.
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:подхватить{}.{
                            <OBJECT>*:*{ ПАДЕЖ:ВИН }
                            <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                           }
  } then 1
}


// младший толкнул его ногой
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:толкнуть{}.{
                          <OBJECT>*:*{ ПАДЕЖ:ВИН }
                          <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                         }
  } then 1
}


// капитан прикрыл ладонью глаза
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:прикрыть{}.{
                          <OBJECT>*:*{ ПАДЕЖ:ВИН }
                          <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                         }
  } then 1
}




// Пол удивленно поднял брови.
//               ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:поднять{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } }
  then -1
}

// ты должна ненавидеть ее всей душой
//           ^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context
  { rus_verbs:ненавидеть{}.{
                            <OBJECT>*:*{ ПАДЕЖ:ВИН }
                            <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                           }
  } then 1
}



tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:попытаться{}.<OBJECT>*:*{ ПАДЕЖ:ДАТ } }
  then -1
}






// кенгуру не умеет петь песни
//                  ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:петь{}.<OBJECT>НеодушОбъект{ падеж:дат } }
  then -1
}


// они называли ее железной.
// ^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:называть{}.{
                                    <OBJECT>*:*{ падеж:вин }
                                    <OBJECT>*:*{ падеж:твор }
                                   }
            }
  then 1
}


// Ударил ли Артур копьем дракона?
// тогда ударил ее кулаком по голове
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ударить{}.{
                                   <OBJECT>*:*{ падеж:вин }
                                   <OBJECT>*:*{ падеж:твор }
                                  }
            }
  then 2
}


// УДАРИТЬ можно либо что-то, либо по чему-то:
// тот ударил по ней кулаком
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ударить{}.{
                                   <OBJECT>*:*{ падеж:вин }
                                   <PREPOS_ADJUNCT>предлог:по{}
                                  }
            }
  then -5
}

// +++++++++++++++++++++++++++++++++++++++++++++++++=

// Самый западный и самый большой полуостров Азии - Аравийский
//                  ^^^^^^^^^^^^^
tree_scorer language=Russian
{
 if context { прилагательное:самый{}.прилагательное:*{} }
  then 1
}



// Даже сторонники экс-премьера не смогли поприветствовать своего кумира
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смочь{}.{
                                 <OBJECT>*:*{ падеж:вин }
                                 инфинитив:*{}.<OBJECT>*:*{ падеж:вин }
                                }
            }
  then -1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смочь{}.{
                                 <OBJECT>*:*{ падеж:род }
                                 инфинитив:*{}.<OBJECT>*:*{ падеж:вин }
                                }
            }
  then -1
}


// ресницы ее начали опускаться
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:начать{}.{
                                  <OBJECT>*:*{ падеж:вин }
                                  инфинитив:*{}
                                 }
            }
  then -1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:начать{}.{
                                  <OBJECT>*:*{ падеж:род }
                                  инфинитив:*{}
                                 }
            }
  then -1
}


// Завершаем 83-й женевский автосалон масштабным обзором новинок в лидирующих сегментах автопрома
// ^^^^^^^^^                ^^^^^^^^^            ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:завершать{}.{
                                     <OBJECT>*:*{ падеж:вин }
                                     <OBJECT>*:*{ падеж:твор }
                                    }
            }
  then 2
}

/*
// В День Воли белорусов призвали побороть страх и лень
//             ^^^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:призвать{}.{
                                    ОдушОбъект{ падеж:вин }
                                    инфинитив:*{}
                                   }
            }
  then 5
}

// РФ призывает США воздержаться от линии силового давления на Дамаск.
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:призывать{}.{
                                     <OBJECT>*:*{ падеж:вин }
                                     инфинитив:*{}
                                    }
            }
  then 5
}
*/




// Он не произнёс ни слова.
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{}.{
                           частица:не{}
                           существительное:*{ падеж:род }.частица:ни{}
                          }
            }
  then 5
}


// США хотят нормализовать отношения с Россией
tree_scorer ВалентностьПредиката language=Russian 
{
 if context { rus_verbs:хотеть{}.{
                                  <SUBJECT>*:*{}
                                  инфинитив:*{}
                                 }
            }
  then 1
}


// их стали  делать
//    ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { глагол:стать{1}.инфинитив:*{ вид:несоверш } }
  then 2
}

// Понизим достоверность связывания ПООБЕЩАТЬ с дательным падежом слева, чтобы не
// возникала ошибка в предложениях типа:
// Президент Ингушетии пообещал ...
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:пообещать{2}.{
                                      <OBJECT>*:*{ 1 падеж:дат }
                                     }
            }
  then -1
}

// ========================================================================
// Некоторые модальные глаголы не могут присоединять прямое дополнение в
// винительном падеже, если присоединен инфинитив:
//
// Я ничего не смог из него выжать
//   ^^^^^^    ~~~~
// Я яблоко ему не смог отдать
//   ^^^^^^        ~~~~

wordentry_set МодальнБезДоп={
 rus_verbs:советовать{}, // Общество потребителей советует аккуратно использовать банковские карты
 rus_verbs:рекомендовать{},
 rus_verbs:мочь{}, // Комментарии можете оставить при себе
 rus_verbs:позволять{}, // Островное положение города позволяет смягчить колебания температур
 rus_verbs:требовать{}, // долг чести требовал освободить ее.
 rus_verbs:продолжать{}, // глаза его продолжали оставаться широко раскрытыми.
 rus_verbs:захотеть{}, // он споры захочет решать мечом
 rus_verbs:смочь{}, // ты сможешь ее удержать?
 rus_verbs:начинать{}, // голос ее начинал дрожать
 rus_verbs:принуждать{}, // Полицейских принуждают покупать лотерейные билеты
 rus_verbs:продолжить{}, // США продолжат распространять демократию по всему миру
 rus_verbs:позволить{}, // Курс нового Советского правительства на индустриализацию страны позволил создать мощную промышленную базу
 rus_verbs:закончить{}, // Я только что закончил писать письмо.
 rus_verbs:заканчивать{},
 rus_verbs:начать{},
 rus_verbs:пробовать{},
 rus_verbs:попробовать{},
 rus_verbs:дозволять{},
 rus_verbs:дозволить{},
 rus_verbs:разрешать{},
 rus_verbs:разрешить{},
 rus_verbs:запрещать{},
 rus_verbs:запретить{},
 rus_verbs:предписывать{},
 rus_verbs:предписать{},
 rus_verbs:присоветывать{},
 rus_verbs:обожать{},
 rus_verbs:поручать{},
 rus_verbs:поручить{},
 rus_verbs:предпочитать{},
 rus_verbs:предпочесть{},
 rus_verbs:бояться{},
 rus_verbs:побояться{},
 rus_verbs:бросать{},
 rus_verbs:бросить{},
 rus_verbs:давать{},
 rus_verbs:дать{},
 rus_verbs:доверять{},
 rus_verbs:доверить{},
 rus_verbs:желать{},
 rus_verbs:хотеть{},
 rus_verbs:забывать{},
 rus_verbs:забыть{},
 rus_verbs:задумывать{},
 rus_verbs:задумать{},
 rus_verbs:кончать{},
 rus_verbs:кончить{},
 rus_verbs:любить{},
 rus_verbs:полюбить{},
 rus_verbs:мешать{},
 rus_verbs:помешать{},
 rus_verbs:ожидать{},
 rus_verbs:планировать{},
 rus_verbs:запланировать{},
 rus_verbs:предлагать{},
 rus_verbs:предложить{},
 rus_verbs:пытаться{},
 rus_verbs:попытаться{},
 rus_verbs:рассчитывать{},
 rus_verbs:посоветовать{},
 rus_verbs:потребовать{},
 rus_verbs:уметь{},
 rus_verbs:суметь{},
 rus_verbs:успевать{},
 rus_verbs:успеть{},
 rus_verbs:решать{},
 rus_verbs:решить{},
 rus_verbs:напоминать{},
 rus_verbs:напомнить{},
 rus_verbs:обещать{},
 rus_verbs:пообещать{},
 rus_verbs:прекращать{},
 rus_verbs:прекратить{},
 rus_verbs:указывать{},
 rus_verbs:указать{}
}

// Попробуй ты ее успокоить
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { МодальнБезДоп.{ <OBJECT>*:*{ падеж:вин } инфинитив:*{} } }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian 
{
 if context { МодальнБезДоп.{ <OBJECT>*:*{ падеж:род } инфинитив:*{} } }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{}.<LEFT_AUX_VERB>МодальнБезДоп.<OBJECT>*:*{ падеж:вин } }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{}.<LEFT_AUX_VERB>МодальнБезДоп.<OBJECT>*:*{ падеж:род } }
  then -100
}


// ========================================================================


// ===========================================================================================
// Некоторые модальные глаголы обычно требуют присоединения и прямого дополнения, и инфинитива
// ===========================================================================================

#define МодальнСВинДоп(v) \
#begin
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{3 }.{ <OBJECT>*:*{ падеж:вин 2 } rus_verbs:v{1} } }
  then 4
}
#end

МодальнСВинДоп(заставить) // путь заставит тебя принять это
МодальнСВинДоп(заставлять) // оно заставляет меня вспоминать
МодальнСВинДоп(выучить) // Он выучил меня играть в шахматы.
МодальнСВинДоп(учить)
МодальнСВинДоп(научить)
МодальнСВинДоп(попросить)
МодальнСВинДоп(просить)
МодальнСВинДоп(умолять)
МодальнСВинДоп(упрашивать)
МодальнСВинДоп(упросить)


// ==========================================================



// или научились ей пользоваться
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:научиться{}.{
                                     <OBJECT>*:*{}
                                     инфинитив:*{}
                                    }
            }
  then -10
}

tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:научиться{}.{
                                    <OBJECT>*:*{}
                                    инфинитив:*{}
                                   }
            }
  then -10
}



// Чтобы причастие или прилагательное, прикрепленное к БЫТЬ,
// было согласовано с подлежащим по роду:
//
// а сегодняшний день обещал быть именно таким
// лето должно быть именно таким
/*
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { *:*{ модальный }.{
                                <SUBJECT>*:*{ род:муж число:ед }
                                инфинитив:быть{}.прилагательное:*{ род:муж число:ед }
                               } }
  then 1
}

tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { *:*{ модальный }.{
                                <SUBJECT>*:*{ род:ср число:ед }
                                инфинитив:быть{}.прилагательное:*{ род:ср число:ед }
                               } }
  then 1
}

tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { *:*{ модальный }.{
                                <SUBJECT>*:*{ род:жен число:ед }
                                инфинитив:быть{}.прилагательное:*{ род:жен число:ед }
                               } }
  then 1
}

tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { *:*{ модальный }.{
                                <SUBJECT>*:*{ число:мн }
                                инфинитив:быть{}.прилагательное:*{ число:мн }
                               } }
  then 1
}
*/


// --------------------------------------------------


// подавляем присоединение одновременно прямого дополнения и инфинитива:
// Я ХОЧУ ЭТО СДЕЛАТЬ
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:хотеть{}.{
                                  инфинитив:*{}
                                  <OBJECT>*:*{ падеж:вин }
                                 }
            }
  then -100
}

// приказывать секретарше принести кофе
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:приказывать{}.{
                                       <OBJECT>*:*{ падеж:дат }
                                       инфинитив:*{}
                                      }
            }
  then 2
}

// руководитель приказал пилоту начать снижение
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:приказать{}.{
                                     <OBJECT>*:*{ падеж:дат }
                                     инфинитив:*{}
                                    }
            }
  then 10
}

// посоветовал ему купить лопату
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:посоветовать{}.{
                                        <OBJECT>*:*{ падеж:дат }
                                        инфинитив:*{}
                                       }
            }
  then 10
}


// позволять другим найти ход
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:позволять{}.{
                                     <OBJECT>*:*{ падеж:дат }
                                     инфинитив:*{}
                                    }
            }
  then 2
}

// позволить компьютеру найти решение
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:позволять{}.{
                                     <OBJECT>*:*{ падеж:дат }
                                     инфинитив:*{}
                                    }
            }
  then 2
}


// лицо незнакомца было покрыто потом
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:покрытый{}.<OBJECT>НеодушОбъект{ падеж:твор } }
  then 2
}

// Но последний -- тот, кого называли Табююзом -- прошел через врата на Землю.
//                      ^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:называть{}.{
                                    <OBJECT>*:*{ падеж:вин }
                                    <OBJECT>*:*{ падеж:твор }
                                   }
            }
  then 2
}


// В рядах оппозиции нашли «агентов Кремля»
// На обломках метеорита нашли скрюченных пришельцев
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:найти{}.<OBJECT>ОдушОбъект{ падеж:род } }
  then -10
}

// их нашли уже через час
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:найти{}.<OBJECT>местоимение:я{ падеж:род } }
  then -10
}

// Российские ученые нашли челюсти чудовища на дне ледяного озера
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:найти{}.<OBJECT>НеодушОбъект{ падеж:дат } }
  then -2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:найти{}.<OBJECT>НеодушОбъект{ падеж:род } }
  then -1
}



// скоро она начнет искать меня
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:искать{}.<OBJECT>ОдушОбъект{ падеж:род } }
  then -10
}

// мне придется искать помощи
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:искать{}.<OBJECT>НеодушОбъект{ падеж:род } }
  then -2
}


// родителям пришлось искать его в одной из соседних станиц
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:искать{}.<OBJECT>местоимение:*{ падеж:род } }
  then -10
}


// Подавим появление императива для НАСЛАТЬ, когда к нему прикреплен В+предл
// В рядах оппозиции нашли «агентов Кремля»
tree_scorer ВалентностьГлагола language=Russian
{ if context { глагол:наслать{ наклонение:побуд }.предлог:в{}.*:*{ падеж:предл } } then -10 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { глагол:наслать{ наклонение:побуд }.предлог:на{}.*:*{ падеж:предл } } then -10 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { глагол:наслать{ наклонение:побуд }.предлог:у{} } then -10 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { глагол:наслать{ наклонение:побуд }.предлог:под{} } then -10 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { глагол:наслать{ наклонение:побуд }.предлог:над{} } then -10 }

// ИНТЕРЕСОВАТЬ - обычно кого-то, а не что-то
// Наравне с литературой его интересует и живопись.
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:интересовать{}.<OBJECT>НеодушОбъект } then -2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:интересовать{}.<OBJECT>ОдушОбъект{ падеж:род } } then -10 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:интересовать{}.<OBJECT>ОдушОбъект{ падеж:вин } } then 1 }


// Модальный ХОТЕТЬ, присоединив инфинитив, уже не может
// присоединять некоторые предложные дополнения:
// она хотела освободиться от меня
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:хотеть{}.{
                               <INFINITIVE>*:*{}
                               предлог:от{} }
            }
  then -100
}

// Обычно КОМУ-ТО идет ОДЕЖДА.
// по всему берегу шла работа
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:идти{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } } then -10 }


// Подавим присоединение наречия КАК справа к БЫТЬ:
// это было как волшебство
//     ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:быть{1}.наречие:как{2} } then -10 }


// Для ПАХНУТЬ - либо ОТ+род, либо КТО-ТО.
// а от вас слишком уж пахнет
tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:пахнуть{ вид:несоверш }.{
                                              <SUBJECT>*:*{}
                                              предлог:от{}
                                             }
            }
  then -100
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:пахнуть{ вид:соверш }.{
                                              <SUBJECT>*:*{}
                                              предлог:от{}
                                             }
            }
  then -100
}

// Обычно время суток не может являться именным сказуемым (вместе со связкой)
// где ж ты был прошлой ночью?
//          ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:быть{}.<RHEMA>ЧастьСуток{ ПАДЕЖ:ТВОР } }
  then -2
}


// обычно ГОВОРЯТ КОМУ-ТО:
// пару минут пытался говорить.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:говорить{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } }
  then -2
}


// вещи мы забрали без шума
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:забрать{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } }
  then -10
}

// их кони шли легким шагом
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:идти{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } }
  then -10
}


// послушай лучше меня!
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:послушать{ наклонение:побуд }.{
                                                    <ATTRIBUTE>'лучше'{ class:наречие }
                                                    <OBJECT>*:*{ ПАДЕЖ:ВИН }
                                                   }
            }
  then 5
}




// нет больше вашего дракона
tree_scorer language=Russian
{
 if context { частица:нет{}.{
                             <ATTRIBUTE>'больше'{ class:наречие }
                             существительное:*{ падеж:род }
                            }
            }
  then 5
}

// обычно КЕМ-ТО не едят:
// Антонио ел пюре каждый день
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:есть{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:ТВОР } }
  then -10
}


// только как это сделать?
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:сделать{}.{
                                   <ATTRIBUTE>наречие:как{}.[not]*:*{}
                                   <OBJECT>НеодушОбъект{ ПАДЕЖ:ВИН }
                                  } }
  then 1
}

// Мозг этих существ сходен по  размерам с мозгом динозавра
//                   ^^^^^^              ^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:сходный{}.предлог:с{}.*:*{ падеж:твор } }
  then 2
}

// Я пришёл сюда раньше его
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:придти{}.предлог:раньше{}.*:*{ падеж:род } }
  then 2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:прийти{}.предлог:раньше{}.*:*{ падеж:род } }
  then 2
}

// В США миллионера осудили за попытку продать Ирану детали для ракет ПВО
//                                     ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:продать{}.{
                                   <OBJECT>*:*{ падеж:дат }
                                   <OBJECT>*:*{ падеж:вин }
                                  } }
  then 2
}


// ты можешь отдать его своему другу.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:отдать{}.{
                                  <OBJECT>*:*{ падеж:вин }
                                  <OBJECT>*:*{ падеж:дат }
                                 } }
  then 2
}

// тратить время на пустяки
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:тратить{}.{
                                   <OBJECT>НеодушОбъект{ падеж:вин }
                                   предлог.*:*{ падеж:вин }
                                  } }
  then 2
}

// а каким же образом о нем узнали вы?
//                    ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:узнать{}.предлог:о{}.*:*{ падеж:предл } }
  then 2
}


// еще четверо тащили под руки своих раненых
//             ^^^^^^          ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:тащить{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}


// некоторые из них тащили за собой платформы
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:тащить{}.{
                                  предлог:из{}
                                  предлог:за{}
                                 } }
  then -10
}


// ты можешь узнать подробности у нее
// Узнав его, они закричали
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:узнать{}.<OBJECT>*:*{ падеж:род } }
  then -1
}


// мне бы хотелось узнать о судьбе своего кота.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:узнать{}.{
                                  предлог:о{}
                                  <OBJECT>ОдушОбъект{ падеж:вин }
                                 } }
  then -100
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:узнать{}.{
                                  предлог:об{}
                                  <OBJECT>ОдушОбъект{ падеж:вин }
                                 } }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:знать{}.{
                                  предлог:о{}
                                  <OBJECT>ОдушОбъект{ падеж:вин }
                                 } }
  then -100
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:знать{}.{
                                  предлог:об{}
                                  <OBJECT>ОдушОбъект{ падеж:вин }
                                 } }
  then -100
}


// меня называли прекрасным человеком
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:называть{}.{
                                    <OBJECT>*:*{ падеж:дат }
                                    <OBJECT>*:*{ падеж:твор }
                                   } }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:назвать{}.{
                                   <OBJECT>*:*{ падеж:дат }
                                   <OBJECT>*:*{ падеж:твор }
                                  } }
  then -100
}


// Мы выбрали его секретарём нашей организации.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:выбрать{}.{
                                   <OBJECT>ОдушОбъект{ падеж:вин }
                                   <OBJECT>ОдушОбъект{ падеж:твор }
                                  } }
  then 2
}


// отдал бы пару лет жизни
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:узнать{}.<OBJECT>НеодушОбъект{ падеж:дат } }
  then -1
}


// Предпочитаем одушевленный объект в конструкции:
//
// Узнать от соседей
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:узнать{}.<PREPOS_ADJUNCT>предлог:от{}.<OBJECT>НеодушОбъект{ падеж:род } }
  then -2
}





// Общее правило для побудительного наклонения: явный субъект не
// может быть в "сослагательном наклонении", то есть иметь частицу БЫ:
//
// меня бы непременно нашли
//      ^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{ наклонение:побуд }.<SUBJECT>*:*{}.частица:бы{} }
  then -100
}


// -----------------------------------------------------------------

// Некоторые наречия не сочетаются с императивом, и это позволяет
// снимать омонимию:
//
// где мой револьвер?
// ^^^ ~~~

wordentry_set СловаНеДляИмператива=
{
 наречие:где{},
 наречие:когда{},
 наречие:почему{},
 наречие:зачем{},
 наречие:отчего{},
 местоим_сущ:кто{},
 местоим_сущ:кто-то{},
 местоим_сущ:что{},
 местоим_сущ:что-то{}
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{ наклонение:побуд }.СловаНеДляИмператива }
  then -10
}

// -----------------------------------------------------------------

// она ждала от него совсем другого
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:ждать{}.наречие:совсем{} }
  then -100
}

// теперь было совсем другое дело
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:быть{}.наречие:совсем{} }
  then -100
}


// она могла вполне оказаться правой
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:оказаться{}.наречие:вполне{} }
  then -100
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:оказаться{}.наречие:совсем{} }
  then -100
}

// Для отрицательной формы переходного глагола
// подавим родительный падеж для прямого одушевленного дополнения:
// Самого богатого француза не пустили в Бельгию
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }.{
                                                             частица:не{}
                                                             <OBJECT>ОдушОбъект{ ПАДЕЖ:РОД }
                                                            } }
  then -2
}


// Придавим вариант прошедшего времени для несовершенного глагола, если
// есть наречие настоящего или будущего времени:
// уж больно ты сейчас слаб
//              ^^^^^^^^^^^

wordentry_set НаречиеНастБуд=наречие:{ сейчас, завтра, послезавтра }

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:слабнуть{ ВРЕМЯ:ПРОШЕДШЕЕ }.{
                                                  НаречиеНастБуд
                                                 } }
  then -1
}





// Подавляем наречие ДОСТАТОЧНО справа от БЫТЬ:
// она была достаточно влажной
// есть достаточно благополучные северные территории
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:быть{}.наречие:достаточно{} }
  then -10
}

// нам всем очень жаль тебя
tree_scorer ВалентностьГлагола language=Russian
{
 if context { безлич_глагол:жаль{}.<OBJECT>ОдушОбъект{ ПАДЕЖ:РОД } }
  then -2
}



// извивалась под его длинными усами
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:извиваться{}.предлог:под{}.*:*{ падеж:вин } }
  then -100
}


// а результаты могли быть куда хуже
//              ^^^^^      ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:мочь{1}.наречие:куда{2} }
  then -2
}


// модальный глагол МОЧЬ обычно не присоединяет предложное дополнение:
// мы можем без купюр поговорить
//    ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:мочь{}.предлог:*{} }
  then -1
}



// когда мне смотреть новости?
//           ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смотреть{}.<OBJECT>существительное:*{ падеж:дат одуш:неодуш } }
  then -2
}


// знаешь холм позади лагеря?
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:знать{}.предлог:позади{} }
  then -2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:знать{}.предлог:впереди{} }
  then -2
}

// шли вчера по тропинке
// ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { 'шли'{ наклонение:побуд }.наречие:вчера{} }
  then -2
}


// кругом была полная тишина
//        ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { 
             глагол:быть{1}.
                            {
                             прилагательное:*{ ~краткий падеж:им 2 }
                             существительное:*{ падеж:им 3 }
                            }
            }
  then -10
}

// Если ПОДОШЕЛ кому-то, то запрещаем предложное дополнение "К ЧЕМУ-ТО"
// Вольф широким шагом подошел к ним
tree_scorer ВалентностьГлагола language=Russian
{
 if context { 
             rus_verbs:подойти{}.
                                 {
                                  <OBJECT>*:*{ ПАДЕЖ:ДАТ }
                                  предлог:к{}
                                 }
            }
  then -100
}



/*
// ------------------------------------------
// некоторые связочные глаголы требуют, чтобы объект был согласован с 
// подлежащим по роду и числу:
// Он оказался сломанным
#define СвязочнГлагол(v) \
#begin
tree_scorer ВалентностьГлагола language=Russian
{
 if context { 
             глагол:v{}.
                        {
                         sbj=<SUBJECT>*:*{}
                         obj=<OBJECT>прилагательное:*{ падеж:твор }
                        }
            }
    //constraints { НесогласСущПрил(sbj,obj) }
    //constraints { sbj:РОД!=obj:РОД }
  then -100
}
#end

СвязочнГлагол(оказаться)
оставаться
остаться
оказываться
стать
становиться
притворяться
притвориться
прикинуться
прикидываться

*/


// а результаты могли быть куда хуже
//                    ^^^^ ~~~~
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:быть{}.наречие:куда{} }
  then -2
}


// ОКАЗАТЬСЯ надо подавлять справа любые наречия, кроме ГДЕ и КОГДА:
//
// Засада оказалась наполовину успешной
//
// все оказалось гораздо хуже
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:оказаться{1}.наречие:*{ 2 ~ОБСТ_ВАЛ:МЕСТО ~ОБСТ_ВАЛ:МОМЕНТ_ВРЕМЕНИ ~СТЕПЕНЬ:СРАВН } }
  then -2
}

// объединение их в единую работающую систему составляет сверхзадачу построения искусственного интеллекта.
//                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:составлять{}.{
                                      предлог:в{}.*:*{ падеж:вин }
                                      <OBJECT>*:*{ падеж:вин }
                                     } }
  then -2
}


wordentry_set ПритяжМестТворЗапрет=притяж_частица:{ ее, его, их }

// прилагательные ЕЁ, ЕГО, ИХ обычно не употребляются в качестве дополнения
// творительного падежа:
// силы явно оставляли ее
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{}.<OBJECT>ПритяжМестТворЗапрет }
  then -5
}


// вы же ее давно знаете!
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:знать{}.<OBJECT>местоимение:я{ падеж:род } }
  then -2
}


// вы делаете из мухи слона
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:делать{1}.{
                                   предлог:из{2}
                                   <OBJECT>*:*{ 3 падеж:вин }
                                  } }
  then 1
}

// Британец, спасший от акулы детей в Австралии, потерял работу (СПАСШИЙ ОТ КОГО-ТО КОГО-ТО)
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:спасти{1}.{
                                   предлог:от{2}
                                   <OBJECT>*:*{ 3 падеж:вин }
                                  } }
  then 1
}


// небольшой штраф за родительное дополнение:
// мы оба знали правила игры.
//        ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:знать{}.<OBJECT>*:*{ падеж:род } }
  then -1
}


// Придаточное ", ЧТО ..." конкурирует за ту же валентность, что и прямое винительное/родительное
// дополнение, поэтому гасим одновременное наличие.
// Маленький квадратик на линии между блоком оценки награды и блоком выбора действия показывает, что эта связь модулирует значимость действия
//                                                                          ~~~~~~~~ ^^^^^^^^^^^^^^^^

tree_scorers ВинРодДопГл
tree_scorer ВинРодДопГл language=Russian { if context { *:*{ падеж:вин } } then 1 }
tree_scorer ВинРодДопГл language=Russian { if context { *:*{ падеж:род } } then 1 }


tree_scorer ВалентностьСложнСказ language=Russian generic
{
 if context { *:*{}.{
                     <OBJECT>ВинРодДопГл
                     <NEXT_CLAUSE>','.союз:что{}
                    }
            }
  then -5
}


wordentry_set Прелог_О_Об={ предлог:о{}, предлог:об{} }
 
// Универсальный принцип: косвенное дополнение О+чем-то заполняет тот же слот, что
// и вин/род дополнение:
// О появлении свежей лавы свидетельствует мощная подсветка в вершинном кратере вулкана
// ^^^^^^^^^^^ ~~~~~~~~~~~
tree_scorer ВалентностьСложнСказ language=Russian generic
{
 if context { *:*{}.{
                     <OBJECT>ВинРодДопГл
                     Прелог_О_Об.*:*{ падеж:предл }
                    }
            }
  then -10
}



// их даже стали из бумаги делать
tree_scorer ВалентностьСложнСказ language=Russian
{
 if context { rus_verbs:делать{}.{
                                  <OBJECT>ВинРодДопГл
                                  предлог:из{}
                                 }
            }
  then 1
}


// только пустое пространство - космос
tree_scorer ВалентностьСложнСказ language=Russian generic
{
 if context { '-'.<ATTRIBUTE>наречие:только{} }
  then -2
}


// Подавим присоединение одушевленного родительного дополнения
// к глаголам в случае, если глагол может присоединить винительное:
// Я хочу тебя
//        ^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{ переходность:переходный падеж:вин падеж:род }.
               ОдушОбъект{ падеж:род }
            }
  then -1
}


// Дмитрий сказал ей об этом
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:сказать{}.<OBJECT>местоимение:я{ падеж:твор } }
  then -2
}






// пожелать спортсменам удачи
// ^^^^^^^^             ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пожелать{}.<OBJECT>*:*{ падеж:род одуш:неодуш } }
  then 1
}


// пожелать спортсменам удачи
// ^^^^^^^^ ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пожелать{}.<OBJECT>*:*{ падеж:дат одуш:одуш } }
  then 1
}

// желать спортсменам удачи
// ^^^^^^             ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:желать{}.<OBJECT>*:*{ падеж:род одуш:неодуш } }
  then 1
}

// желать спортсменам удачи
// ^^^^^^ ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:желать{}.<OBJECT>*:*{ падеж:дат одуш:одуш } }
  then 1
}





// Мама налила чай
//      ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:налить{}.<OBJECT>существительное:*{ падеж:вин <в_класс>существительное:напиток{} } }
  then 1
}


// Оля съела пюре
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:съесть{}.<OBJECT>существительное:*{ падеж:вин <в_класс>существительное:еда{} } }
  then 1
}



// испросить разрешения
// ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:испросить{}.<OBJECT>*:*{ падеж:род одуш:неодуш } }
  then 3
}




// наделать в решении ошибок
// ^^^^^^^^           ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:наделать{}.<OBJECT>существительное:*{ падеж:род } }
  then 2
}


// дракон смотрит вслед человеку.
//        ^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смотреть{}.предлог:вслед{}.*:*{ падеж:дат } }
  then 1
}


// нажимать на все кнопки
// ^^^^^^^^ ^^     ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:нажимать{}.предлог:на{}.существительное:*{ одуш:неодуш падеж:вин } }
  then 1
}


// предикатив МОЖНО обычно присоединяет только одушевленный дательный агенс:
// на этой удивительно четкой фотографии можно увидеть рассеянное скопление
//                            ~~~~~~~~~~ ^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:можно{}.<SUBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ } }
  then -2
}

// поэтому - очень легкий спуск
tree_scorer ВалентностьПредиката language=Russian
{
 if context { '-'.<ATTRIBUTE>наречие:очень{} }
  then -10
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { '–'.<ATTRIBUTE>наречие:очень{} }
  then -10
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { '—'.<ATTRIBUTE>наречие:очень{} }
  then -10
}


// Мужчина, взявший в заложники пожарных в США, убит при штурме
//          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьСложнСказ language=Russian
{
 if context { rus_verbs:взять{}.{
                                 <OBJECT>*:*{ падеж:вин }
                                 предлог:в{}.*:*{ падеж:им }
                                }
            }
  then 2
}


// отчего же получается такая разница?
tree_scorer ВалентностьСложнСказ language=Russian
{
 if context { глагол:получаться{1}.{
                                    прилагательное:*{2 падеж:им }
                                    <SUBJECT>*:*{ 3 }
                                   }
            }
  then -2
}

// отчего же получилась такая разница?
tree_scorer ВалентностьСложнСказ language=Russian
{
 if context { глагол:получиться{1}.{
                                    прилагательное:*{2 падеж:им }
                                    <SUBJECT>*:*{ 3 }
                                   }
            }
  then -2
}


// черный кожаный костюм делал его почти невидимым
tree_scorer ВалентностьСложнСказ language=Russian
{
 if context { rus_verbs:делать{}.{
                                  <OBJECT>*:*{ падеж:вин }
                                  прилагательное:*{ падеж:твор }
                                 }
            }
  then 1
}


// Общее правило для глаголов - два наречия подряд прикрепляются
// достаточно редко.
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{}.@sequence_pos(НАРЕЧИЕ) }
  then -1
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{}.@sequence_pos(НАРЕЧИЕ) }
  then -1
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { деепричастие:*{}.@sequence_pos(НАРЕЧИЕ) }
  then -1
}

// как это все объяснить?
// ^^^^^^^^^^^
tree_scorer language=Russian generic
{
 if context { наречие:как{1}.местоим_сущ:все{} }
  then -1
}

tree_scorer language=Russian
{
 if context { наречие:как{1}.местоим_сущ:это{} }
  then -1
}

// *******************************************************************************
// Подавляем одновременное присоединение винительного и родительного дополнения
//
// я буду ждать результаты проверки
//        ^^^^^^^^^^^^^^^^^^^^^^^^^
// *******************************************************************************
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{}.{
                     <OBJECT>*:*{ падеж:вин }
                     <OBJECT>*:*{ падеж:род }
                    }
            }
  then -10
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{}.{
                     <OBJECT>*:*{ падеж:вин }
                     <OBJECT>*:*{ падеж:парт }
                    }
            }
  then -10
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{}.{
                     <OBJECT>*:*{ падеж:род }
                     <OBJECT>*:*{ падеж:парт }
                    }
            }
  then -10
}

// ------------------------------------------------------

// Немного придавим использование прилагательного в роли
// творительного дополнения:
// нога жреца коснулась первой ступеньки.
//                      ^^^^^^

wordentry_set ГлаголыСвязки=
{
 rus_verbs:остаться{}, // вроде бы их количество осталось прежним.
 rus_verbs:оставить{}, // дверь туда оставим открытой.
 rus_verbs:оставлять{},
 rus_verbs:оставаться{},
 rus_verbs:становиться{},
 rus_verbs:стать{},
 rus_verbs:представляться{}, // оно всегда представлялось ей пронзительно голубым.
 rus_verbs:притвориться{},
 rus_verbs:притворяться{},
 rus_verbs:прикинуться{},
 rus_verbs:прикидываться{},
 rus_verbs:делаться{},
 rus_verbs:объявить{},
 rus_verbs:объявлять{},
 rus_verbs:назвать{},
 rus_verbs:называть{},
 rus_verbs:являться{},
 rus_verbs:казаться{},
 rus_verbs:оказаться{},
 rus_verbs:показаться{}, 
 rus_verbs:быть{},
 rus_verbs:бывать{},
 rus_verbs:найти{}, // Он был найден виновным.
 rus_verbs:сделаться{}
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{ ~ГлаголыСвязки }.<OBJECT>прилагательное:*{ падеж:твор } }
  then -2
}

// Желать вам всем удачи
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{ ~ГлаголыСвязки }.<OBJECT>местоим_сущ:всё{ падеж:твор } }
  then -2
}


// ------------------------------------------------------

// забористый бас Константина делал его легко узнаваемым
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:делать{}.<OBJECT>прилагательное:*{ падеж:дат }
            }
  then -2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:сделать{}.<OBJECT>прилагательное:*{ падеж:дат }
            }
  then -2
}

// ------------------------------------------------------

// злодей схватил нож и несколько раз всадил его оппоненту в спину
//                                    ^^^^^^ ^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:всадить{}.{
                                   <OBJECT>НеодушОбъект{ ПАДЕЖ:ВИН}
                                   <OBJECT>*:*{ ПАДЕЖ:ДАТ }
                                  }
            }
  then 1
}

// ------------------------------------------------------

// Обычно глагол не может одновременно присоединять и винительный,
// и родительный падеж, но некоторые глаголы - могут:
// это может лишить наше общество работы
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:лишить{}.{
                                  <OBJECT>*:*{ ПАДЕЖ:ВИН }
                                  <OBJECT>НеодушОбъект{ ПАДЕЖ:РОД }
                                 }
            }
  then 12
}

// ------------------------------------------------------

// она обхватила его руками за шею
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обхватить{}.{
                                     <OBJECT>*:*{ ПАДЕЖ:ВИН }
                                     <OBJECT>*:*{ ПАДЕЖ:ТВОР }
                                    }
            }
  then 1
}

// ------------------------------------------------------

// Подавляем для модального ХОТЕТЬ присоединение дополнений,
// когда присоединен инфинитив:
// ты это хотел мне рассказать?
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:хотеть{}.{ <OBJECT>*:*{ падеж:дат } инфинитив:*{} } } then -10 }

// ------------------------------------------------------

// Однако их  ярость уступила место страху
tree_scorer ВалентностьСложнСказ language=Russian
{
 if context { rus_verbs:уступить{}.{
                                    <OBJECT>*:*{ падеж:вин }
                                    <OBJECT>*:*{ падеж:дат }
                                   }
            }
  then 1
}


// --------------------------------------------------------------

// глагол ПОМОЧЬ обычно присоединяет дательную валентность.
// мне надо им помочь
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:помочь{}.[not]<OBJECT>*:*{ падеж:дат } } then -2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:помогать{}.[not]<OBJECT>*:*{ падеж:дат } } then -2 }


// -------------------------------

// злодей схватил нож и несколько раз всадил его оппоненту в спину
tree_scorer ВалентностьСложнСказ language=Russian
{
 if context { rus_verbs:всадить{}.{
                                    <OBJECT>НеодушОбъект{ падеж:вин }
                                    <OBJECT>ОдушОбъект{ падеж:дат }
                                   }
            }
  then 1
}


// ------------------------------------

// за деревьями леса не видеть
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:видеть{}.{
                                  частица:не{}
                                  <OBJECT>*:*{ падеж:род }
                                 }
            }
  then 1
}

// ------------------------------------

// Подавляем компаратив наречия справа от ОКАЗАТЬСЯ, если
// у глагола есть прямое дополнение:
// эта задача оказалась гораздо легче первой.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:оказаться{}.{
                                     наречие:*{ степень:сравн }
                                     *:*{ падеж:твор }
                                    }
            }
  then -10
}

// ----------------------------------------------
// Обычно рассказывают либо ЧТО-ТО, либо о ЧЕМ-ТО
// Набив рот, он попросил ее рассказать о вторжении.
//                        ^^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:рассказать{}.{
                                      *:*{ падеж:вин }
                                      предлог:о{}
                                     }
            }
  then -5
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:рассказать{}.{
                                      *:*{ падеж:род }
                                      предлог:о{}
                                     }
            }
  then -5
}


// Набив рот, он попросил ее рассказать о вторжении.
//               ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:попросить{}.{
                                     инфинитив:*{}
                                     предлог:о{}
                                    }
            }
  then -5
}



// Предприниматели ФРГ выступают за добычу сланцевого газа
//                 ^^^ ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:выступать{2}.<OBJECT>*:*{ 1 падеж:твор } } then -2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:выступать{}.<OBJECT>*:*{ падеж:твор <в_класс>существительное:страна{} } } then -2 }


// Обычно ВОСПОЛЬЗОВАТЬСЯ имеет заполненный слот творительного дополнения:
// этим мгновением надо было воспользоваться
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:воспользоваться{}.<OBJECT>*:*{ падеж:твор } } then 2 }


// откуда ее черт принес?
// Откуда её ветер принёс?
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:принести{}.{
                                    <SUBJECT>*:*{}
                                    <OBJECT>*:*{ падеж:вин }
                                   }
            }
  then 1
}

// ей доводилось встречать эти существа
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:доводилось{}.{
                                          <SUBJECT>*:*{ падеж:дат }
                                          инфинитив:*{}
                                         }
            }
  then 3
}


// Есть у нас в лесу место
tree_scorer ВалентностьГлагола language=Russian
{
 if context { 'есть'{ class:инфинитив }.предлог:у{} }
  then -5
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:заняться{}.<OBJECT>*:*{ падеж:твор } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:заниматься{}.<OBJECT>*:*{ падеж:твор } }
  then 1
}


// Майкл способен попасть в кольцо с десятиметровой дистанции пять раз подряд
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:попасть{}.предлог:с{}.*:*{ ПАДЕж:РОД } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:попадать{}.предлог:с{}.*:*{ ПАДЕж:РОД } } then 2 }

// Я спустил собаку с цепи.
//   ^^^^^^^        ^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:спустить{}.предлог:с{}.*:*{ ПАДЕж:РОД } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:спускать{}.предлог:с{}.*:*{ ПАДЕж:РОД } } then 2 }

// Гоша опустил ногу со стола.
//      ^^^^^^^      ^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:опустить{}.предлог:с{}.*:*{ ПАДЕж:РОД } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:опускать{}.предлог:с{}.*:*{ ПАДЕж:РОД } } then 2 }


// тебе доводилось использовать силы магии против другого человека?
tree_scorer ВалентностьГлагола language=Russian
{ if context { глагол:использовать{ вид:соверш }.предлог:против{} } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { глагол:использовать{ вид:несоверш }.предлог:против{} } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { инфинитив:использовать{ вид:соверш }.предлог:против{} } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { инфинитив:использовать{ вид:несоверш }.предлог:против{} } then 2 }


// лесом от него пахло
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:пахнуть{ вид:несоверш }.предлог:от{} }
  then 2
}

// Дождь должен смыть всю пыль с листьев.
//              ^^^^^          ^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:смыть{}.предлог:с{}.*:*{ падеж:род} } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:смывать{}.предлог:с{}.*:*{ падеж:род} } then 2 }

// он смел крошки со стола
//    ^^^^        ^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:смести{}.предлог:с{}.*:*{ падеж:род} } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:сметать{}.предлог:с{}.*:*{ падеж:род} } then 2 }

// Мальчики съехали на санках с горы.
//          ^^^^^^^           ^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:съехать{}.предлог:с{}.*:*{ падеж:род } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:съезжать{}.предлог:с{}.*:*{ падеж:род } } then 2 }

// Дети бросались в воду с моста
//      ^^^^^^^^^        ^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:броситься{}.предлог:с{}.*:*{ падеж:род } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:бросаться{}.предлог:с{}.*:*{ падеж:род } } then 2 }


// отнестись к животным с сочуствием
// ^^^^^^^^^            ^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:отнестись{}.предлог:с{}.*:*{ падеж:твор } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:относиться{}.предлог:с{}.*:*{ падеж:твор } } then 2 }


// Элис разинула от удивления рот.
//      ^^^^^^^^              ^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:разинуть{}.НеодушОбъект{ падеж:вин } } then 2 }


// --------------------------------------
// ВЛЮБЛЯТЬСЯ В КОГО-ТО
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:влюбляться{}.предлог:в{}.*:*{ падеж:вин } } then 1 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:влюбляться{}.предлог:в{}.существительное:*{ одуш:одуш падеж:вин } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:влюбляться{}.предлог:в{}.существительное:*{ падеж:вин <в_класс>существительное:имя{} } } then 3 }


// --------------------------------------
// ВЛЮБИТЬСЯ В КОГО-ТО
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:влюбиться{}.предлог:в{}.*:*{ падеж:вин } } then 1 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:влюбиться{}.предлог:в{}.существительное:*{ одуш:одуш падеж:вин } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:влюбиться{}.предлог:в{}.существительное:*{ падеж:вин <в_класс>существительное:имя{} } } then 3 }

// --------------------------------------
// ВТЮРИТЬСЯ В КОГО-ТО
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:втюриться{}.предлог:в{}.*:*{ падеж:вин } } then 1 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:втюриться{}.предлог:в{}.существительное:*{ одуш:одуш падеж:вин } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:втюриться{}.предлог:в{}.существительное:*{ падеж:вин <в_класс>существительное:имя{} } } then 3 }


// ------------------------------------------------
// **** Глаголы перемещения с топонимами ****

tree_scorers ЛюбойТопонимНеизв

// для неизвестных топонимов
tree_scorer ЛюбойТопонимНеизв language=Russian
{
 if context { существительное:???{ charcasing:FirstCapitalized } }
  then 1
}

tree_scorer ЛюбойТопонимНеизв language=Russian
{
 if context { существительное:*{ <в_класс>существительное:страна{} } }
  then 1
}

tree_scorer ЛюбойТопонимНеизв language=Russian
{
 if context { существительное:*{ <в_класс>существительное:город{} } }
  then 1
}

// +++++

// для слов типа ТАКСИ

tree_scorers ЛюбойТранспорт

tree_scorer ЛюбойТранспорт language=Russian
{
 if context { существительное:*{ <в_класс>существительное:транспорт{} } }
  then 1
}

// +++++

tree_scorers ЛюбойЧеловек

tree_scorer ЛюбойЧеловек language=Russian
{
 if context { существительное:*{ <в_класс>существительное:профессия{} } }
  then 1
}

tree_scorer ЛюбойЧеловек language=Russian
{
 if context { существительное:*{ <в_класс>существительное:имя{} } }
  then 1
}

// +++++

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:улететь{}.предлог:в{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:улететь{}.предлог:в{}.ЛюбойТранспорт{ падеж:предл } } then 2 }

// ++++

// он уехал в Токио
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:уехать{}.предлог:в{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

// он уехал в такси
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:уехать{}.предлог:в{}.ЛюбойТранспорт{ падеж:предл } } then 2 }

// ++++

// Мы эмигрировали в США
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:эмигрировать{}.предлог:в{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

// ++++

// Виктор перебрался в Токио
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:перебраться{}.предлог:в{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

// ++++

// Мафиози сбежали из Токио
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:сбежать{}.предлог:в{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

// ++++

// Они едут в Токио
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:ехать{}.предлог:в{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

// мы ехали в такси
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:ехать{}.предлог:в{}.ЛюбойТранспорт{ падеж:предл } } then 2 }

// ++++

// туристы поехали в Киото
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:поехать{}.предлог:в{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:поехать{}.предлог:в{}.ЛюбойТопонимНеизв{ падеж:предл } } then -10 }

// группа туристов поехала в такси
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:поехать{}.предлог:в{}.ЛюбойТранспорт{ падеж:предл } } then 2 }

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:поехать{}.предлог:в{}.ЛюбойТранспорт{ падеж:вин } } then -10 }

// ++++

// Люси отправилась в Токио
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:отправиться{}.предлог:в{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

// ++++

// Мы посетили Киото
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:посетить{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

// ++++

// путешественники посещали Киото
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:посещать{}.ЛюбойТопонимНеизв{ падеж:вин } } then 2 }

// ++++

// Мы спросили Людмилу Ивановну
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:спросить{}.ЛюбойЧеловек{ падеж:вин } } then 2 }

// Дети спросили совет у учителя
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:спросить{}.предлог:у{}.ЛюбойЧеловек{ падеж:род } } then 2 }

// ++++

// Дети спрашивают медсестру
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:спрашивать{}.ЛюбойЧеловек{ падеж:вин } } then 2 }

// Дети спрашивают совет у учителя
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:спрашивать{}.предлог:у{}.ЛюбойЧеловек{ падеж:род } } then 2 }

// ++++

// мы поинтересовались ответом у учительницы
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:поинтересоваться{}.предлог:у{}.ЛюбойЧеловек{ падеж:род } } then 2 }

// ++++

// Вдалеке мы увидели Токио
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:увидеть{}.*:*{ падеж:вин }  } then 1 }

// ++++

// Справа вы видите Киото
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:видеть{}.*:*{ падеж:вин }  } then 1 }

// ++++

//
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:построить{}.НеодушОбъект{ падеж:вин }  } then 1 }

// ++++

//
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:строить{}.НеодушОбъект{ падеж:вин }  } then 1 }

// ++++

//
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:создать{}.НеодушОбъект{ падеж:вин }  } then 1 }

// ++++

//
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:создавать{}.НеодушОбъект{ падеж:вин }  } then 1 }

// ++++

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:обмениваться{}.*:*{ падеж:твор }  } then 1 }

// ++++

tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:обменяться{}.*:*{ падеж:твор }  } then 1 }

// +++++

// Элис разинула от удивления рот.
//      ^^^^^^^^              ^^^
tree_scorer ВалентностьГлагола language=Russian
{ if context { rus_verbs:разинуть{}.НеодушОбъект{ падеж:вин }  } then 1 }

// ++++++

// Я  покажу  тебе, как надо мной смеяться!
//                           ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смеяться{}.местоимение:*{ падеж:твор }  }
  then -5
}

// ++++++++++

// плыть ей пришлось долго.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:пришлось{}.{
                                        <SUBJECT>*:*{ падеж:дат }
                                        инфинитив:*{}
                                       }
            }
  then 2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:плыть{}.местоимение:*{ падеж:твор }  }
  then -5
}

// ++++++++++

// все остальное тебе тоже удалось устроить?
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:удалось{}.{
                                       <SUBJECT>*:*{ падеж:дат }
                                       инфинитив:*{}
                                      }
            }
  then 2
}

// +++++++++++++++

// Это событие является одним из элементов широко задуманной акции.

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:являться{}.'одним'{ падеж:твор }.'из'  }
  then 2
}

// +++++++++++++++

// вот кого мне нужно было искать!
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:нужно{}.{
                                     <SUBJECT>*:*{ падеж:дат }
                                     инфинитив:*{}
                                    }
            }
  then 2
}

// +++++++++++++++++

// им надо видеть движение.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:надо{}.{
                                     <SUBJECT>*:*{ падеж:дат }
                                     инфинитив:*{}
                                    }
            }
  then 2
}

// +++++++++++++++++

// но прежде нам необходимо найти тело
tree_scorer ВалентностьПредиката language=Russian
{
 if context { безлич_глагол:необходимо{2}.{
                                          <SUBJECT>*:*{ падеж:дат 1 }
                                          инфинитив:*{3}
                                         }
            }
  then 4
}

// +++++++++++++++++

// мимо тебя пройти невозможно
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:пройти{}.{
                                  наречие:мимо{}
                                  <OBJECT>*:*{ падеж:вин }
                                 }
            }
  then -10
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:пройти{}.{
                                  наречие:мимо{}
                                  <OBJECT>*:*{ падеж:род }
                                 }
            }
  then -10
}

// +++++++++++++++++

// Сегодня я буду читать дома
//                ^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:читать{}.{
                                  <OBJECT>существительное:*{ <в_класс> СУЩЕСТВИТЕЛЬНОЕ:СТРОЕНИЕ{} }
                                 }
            }
  then -10
}

// +++++++++++++++++

// Она ослепила его своей красотой.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:ослепить{}.{
                                    <OBJECT>*:*{ падеж:вин }
                                    <OBJECT>*:*{ падеж:твор }
                                   }
            }
  then 2
}

// +++++++++++++++++++

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:слышать{}.<OBJECT>существительное:*{ <в_класс>существительное:звук{} } }
  then 2
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:слышать{}.<SUBJECT>существительное:*{ <в_класс>существительное:звук{} } }
  then -5
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:услышать{}.<OBJECT>существительное:*{ <в_класс>существительное:звук{} } }
  then 2
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:услышать{}.<SUBJECT>существительное:*{ <в_класс>существительное:звук{} } }
  then -5
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:расслышать{}.<OBJECT>существительное:*{ <в_класс>существительное:звук{} } }
  then 2
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:расслышать{}.<SUBJECT>существительное:*{ <в_класс>существительное:звук{} } }
  then -5
}

// +++++++++++++++++++++++++

/*
// пища помогла мне окончательно прогнать сон
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:помочь{}.{
                                  <SUBJECT>*:*{}
                                  <OBJECT>*:*{ падеж:дат }
                                  инфинитив:*{}
                                 }
            }
  then 5
}
*/

// +++++++++++++++++

// Немного повысим достоверность императива в случае,
// когда предложение оканчивается восклицательным знаком:
// держите ее за ноги!
tree_scorer language=Russian
{
 if context { глагол:*{ наклонение:побуд }.'!' }
  then 1
}

// - А яичницу любите?
tree_scorer language=Russian
{
 if context { глагол:*{ наклонение:побуд }.'?' }
  then -4
}


// +++++++++++++++++

// Страх охватил Грегори
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:охватить{}.{
                                    <SUBJECT>существительное:*{ одуш:неодуш <в_класс>существительное:эмоция{} }
                                    <OBJECT>*:*{ падеж:вин }
                                   }
            }
  then 5
}

// ++++++++++++++++++

// какие тут могут быть секреты?
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:мочь{}.{
                             инфинитив:*{}
                             <OBJECT>*:*{ падеж:вин }
                            }
            }
  then -100
}

// +++++++++++++++++

// В Ульяновской области детей обстреляли из пневматики
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обстрелять{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}

// +++++++++++++++++

// теперь вы все знаете
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:знать{}.<OBJECT>'все'{ падеж:вин } }
  then 2
}

// +++++++++++++++++

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:предложить{}.{ <OBJECT>*:*{ падеж:дат } инфинитив:*{} } }
  then 6
}


// +++++++++++++++++

// Мы велели ей убраться из комнаты
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:велеть{}.{ <OBJECT>*:*{ падеж:дат } инфинитив:*{} } }
  then 6
}

// +++++++++++++++++

// Обычно глагол БЫТЬ не присоединяет прямое дополнение в винительном падеже:
// Это будет аварийный запас.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:быть{}.<OBJECT>*:*{ падеж:вин } }
  then -5
}

// в этом кафе будут они
tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:быть{}.{
                             <SUBJECT>местоимение:*{ падеж:им }
                             <RHEMA>*:*{ одуш:неодуш падеж:им }
                            }
            }
  then -3
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:быть{}.{
                             <RHEMA>местоимение:*{ падеж:им }
                             <SUBJECT>существительное:*{ одуш:неодуш падеж:им }
                            }
            }
  then -3
}

// Компаратив наречия для БЫТЬ/БЫВАТЬ подавляем
// она была старше меня
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:быть{}.<RHEMA>наречие:*{ степень:сравн } }
  then -5
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:бывать{}.<RHEMA>наречие:*{ степень:сравн } }
  then -5
}


// +++++++++++++++++

// Глаголы, синонимичные ЗАПЕРЕТЬ - подавляем вариант, когда подлежащим становится
// существительное из класса ЗДАНИЕ:
// запер  сарай
// ^^^^^^^^^^^^

#define ЗаперетьЗдание(v) \
#begin
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:v{}.<SUBJECT>существительное:*{ <в_класс>существительное:здание{} } }
  then -100
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:v{}.<SUBJECT>существительное:*{ <в_класс>существительное:здание{} } }
  then -100
}
#end

ЗаперетьЗдание(запереть)
ЗаперетьЗдание(запирать)
ЗаперетьЗдание(закрыть)
ЗаперетьЗдание(закрывать)
ЗаперетьЗдание(открыть)
ЗаперетьЗдание(открывать)

// +++++++++++++++++

// она несла на плечах  своего мужа.
//     ^^^^^            ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:нести{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } }
  then 1
}

// +++++++++++++++++++++

// И была опасность,  что  когда-нибудь  откажет  дыхательный  аппарат.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:отказать{}.<OBJECT>*:*{ ПАДЕЖ:ВИН } }
  then -2
}

// ++++++++++++++++++++++

// Ты знаешь, что на следующий день должен был приехать мой муж.
//            ^^^                   ^^^^^^     ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:должный{}.{
                                        <OBJECT>*:*{ ПАДЕЖ:ВИН }
                                        инфинитив:*{}
                                       }
            }
  then -100
}

// Двое  гонцов  из  Мурманска  должны  были  прибыть  ночным  поездом.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { прилагательное:должный{}.{
                                        <OBJECT>*:*{ ПАДЕЖ:РОД }
                                        инфинитив:*{}
                                       }
            }
  then -100
}


// ++++++++++++++++++++++

// чувашскими законотворцами был взят проект Федерального закона
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { прилагательное:*{ КРАТКИЙ СТРАД ПРИЧАСТИЕ }.<OBJECT>*:*{ падеж:род } }
  then -5
}


// ++++++++++++++++++++++

// ружье его было тут
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { глагол:быть{}.'его'{ class:прилагательное } }
  then -5
}

tree_scorer ВалентностьГлагола language=Russian 
{
 if context { глагол:быть{}.'ее'{ class:прилагательное } }
  then -5
}

tree_scorer ВалентностьГлагола language=Russian 
{
 if context { глагол:быть{}.'их'{ class:прилагательное } }
  then -5
}

// +++++++++++++++++++++++++++

// его отучают пить из-под крана
tree_scorer language=Russian 
{
 if context { инфинитив:*{}.
               <LEFT_AUX_VERB>глагол:отучать{}.
                ОдушОбъект{ ПАДЕж:ВИН } }
  then 2
}


// +++++++++++++++++++++++++++++++

// Смелость города берёт
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:брать{}.<OBJECT>существительное:*{ падеж:вин } }
  then 1
}

// --------------------------------

// это открытие его удивило
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:удивить{}.<OBJECT>ОдушОбъект{ падеж:вин } }
  then 2
}


// ++++++++++++++++++++++++++++++++++++++++++++


// Ветерок был приятным
// ^^^^^^^     ^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { глагол:быть{}.{
                             thema=<SUBJECT>*:*{}
                             rhema=<RHEMA>прилагательное:*{}
                            }
            }
  then adj_noun_score(rhema,thema)
}


// Выбор фруктов слаб
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { a=прилагательное:*{ КРАТКИЙ}.n=<SUBJECT>СУЩЕСТВИТЕЛЬНОЕ:*{}
            }
  then adj_noun_score(a,n)
}




// Воздух становился всё холоднее
// ^^^^^^                ^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { глагол:становиться{}.{
                                    thema=<SUBJECT>*:*{}
                                    rhema=прилагательное:*{}
                                   }
            }
  then adj_noun_score(rhema,thema)
}

tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { глагол:стать{}.{
                              thema=<SUBJECT>*:*{}
                              rhema=прилагательное:*{}
                             }
            }
  then adj_noun_score(rhema,thema)
}

// -----------------------------------

#define VerbInstr(v,w) \
#begin
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:v{}.<OBJECT>существительное:*{ падеж:твор } }
  then w
}
#end

VerbInstr(ограничиться,2)
VerbInstr(интересоваться,2)
VerbInstr(заинтересоваться,2)
VerbInstr(поинтересоваться,2)
VerbInstr(пренебрегать,2)
VerbInstr(пренебречь,2)
VerbInstr(увенчаться,2)

// ----------------------------------

// Все звали  ее  Верочкой...
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:звать{}.{
                              <OBJECT>ОдушОбъект{ ПАДЕЖ:ВИН }
                              <OBJECT>существительное:*{ ПАДЕЖ:ТВОР }
                             }
            }
  then 2
}

// ----------------------------------

/*
wordentry_set ПредлогНаправления = предлог:{ на, в, под, через }

// дракону на спину сел
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{ ~ПАДЕЖ:ДАТ }.{
                          <OBJECT>*:*{ ПАДЕЖ:ДАТ }
                          <PREPOS_ADJUNCT>ПредлогНаправления.*:*{ ПАДЕЖ:ВИН }
                         }
            }
  then 8
}


tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{ ~ПАДЕЖ:ДАТ }.{
                                         <OBJECT>*:*{ ПАДЕЖ:ДАТ }
                                         <PREPOS_ADJUNCT>ПредлогНаправления.*:*{ ПАДЕЖ:ВИН }
                                        }
            }
  then 8
}
*/

// -----------------------------------

// Официант денег не взял.
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:взять{}.{
                                 частица:не{}
                                 <OBJECT>НеодушОбъект{ ПАДЕЖ:РОД }
                                }
            }
  then 2
}

// ----------------------------------

// эти последние энергично пошли им навстречу.
//                         ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:пойти{}.послелог:навстречу{}.*:*{ падеж:дат } }
  then 5
}

// Он сделал шаг ей навстречу.
//    ^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:сделать{}.{ <OBJECT>НеодушОбъект{ ПАДЕЖ:ВИН } послелог:навстречу{}.*:*{ падеж:дат } } }
  then 5
}


// ---------------------------------

tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:объявить{}.{
                                    <OBJECT>*:*{ падеж:вин }
                                    предлог:о{}
                                   }
            }
  then -100
}


// ----------------------------------

// именно поэтому она собиралась предложить им очень простой выбор.
//                               ^^^^^^^^^^ ^^               ^^^^^
tree_scorer ВалентностьГлагола language=Russian 
{
 if context { rus_verbs:предложить{}.{
                                      <OBJECT>*:*{ падеж:дат }
                                      <OBJECT>*:*{ падеж:вин }
                                     }
            }
  then 5
}


// -----------------------------------------------

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:править{}.<OBJECT>существительное:*{ <в_класс>существительное:страна{} ПАДЕЖ:ТВОР } }
  then 5
}

// ----------------------------------

// мы уже начали за вас волноваться.
//               ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:волноваться{}.предлог:за{}.*:*{ падеж:вин } }
  then 5
}

// ----------------------------------

// ей следовало бы проверить зрение.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { безлич_глагол:следует{}.{ *:*{ падеж:дат } инфинитив:*{} } }
  then 2
}

// ----------------------------------

// как легко превратить в кляксу живого человека
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:превратить{}.{ <OBJECT>*:*{ падеж:вин } предлог:в{}.*:*{ падеж:вин } } }
  then 2
}

// ----------------------------------

// мне надо было встать
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{}.{
                             БезличСвязка0
                             безлич_глагол:*{ ~ТИП_ПРЕДИКАТИВ:БЫЛО_СВЯЗКА }
                            }
            }
  then -5
}


// ----------------------------------

// Уточняем согласование подлежащего и
// атрибута для связочных глаголов:
//
wordentry_set СвязочныеГлаголы=
{
 rus_verbs:стать{},
 rus_verbs:становиться{},
 rus_verbs:быть{},
 rus_verbs:бывать{},
 rus_verbs:оказаться{},
 rus_verbs:оказываться{},
 rus_verbs:получиться{},
 rus_verbs:получаться{}
}

// Он может стать главным
// ^^             ^^^^^^^   
tree_scorer ВалентностьПредиката language=Russian
{
 if context { СвязочныеГлаголы.{
                                sbj=<SUBJECT>*:*{ ЧИСЛО:ЕД }
                                прилагательное:*{ ПАДЕЖ:ТВОР ЧИСЛО:ЕД ~КРАТКИЙ !=sbj:РОД }
                               } }
  then -2
}

// Ты можешь стать главным
// ^^              ^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { СвязочныеГлаголы.{
                                sbj=<SUBJECT>местоимение:я{ ЧИСЛО:ЕД ~лицо:3 }
                                прилагательное:*{ ПАДЕЖ:ТВОР ЧИСЛО:ЕД ~КРАТКИЙ РОД:СР }
                               } }
  then -2
}


// ----------------------------------

#define НеГлагРодЕд(v,n,w) \
#begin
tree_scorer ВалентностьГлагола language=Russian
{
 if context {
             rus_verbs:v{}.{
                            частица:не{}
                            <OBJECT>существительное:n{ падеж:род число:ед }
                           }
            } then w
}
#end

// Америка не имеет права вмешиваться во внутренние дела России
//         ^^^^^^^^^^^^^^
НеГлагРодЕд(иметь,право,2)

// Ни  один  прокурор такого разрешения не  даст.
НеГлагРодЕд(дать,разрешение,8)

// ----------------------------------

// Надежде  приходилось,  чтобы  успеть  вставить  свои ответы между его репликами, произносить слова со  скоростью  пулеметной  очереди.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { безлич_глагол:приходится{}.инфинитив:*{ вид:несоверш } }
  then 2
}

// ----------------------------------


// Мы внедрили в его организацию соглядатая
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:внедрить{}.существительное:*{ падеж:вин } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:внедрять{}.существительное:*{ падеж:вин } }
  then 1
}

// ----------------------------------


// Основание качнулось, зажатое манипуляторами.
// ^^^^^^^^^            ^^^^^^^
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { глагол:*{}.{
                          n3=<SUBJECT>*:*{}
                          <SEPARATE_ATTR>*:*{ ПАДЕЖ:ИМ =n3:РОД =n3:ЧИСЛО }
                         } }
  then 2
}


// День выдался ненастный.
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { *:*{}.{ sbj=<SUBJECT>существительное:*{} attr=<SEPARATE_ATTR>прилагательное:*{ ПАДЕЖ:ИМ =sbj:РОД =sbj:ЧИСЛО } } }
  then adj_noun_score(attr,sbj)
}


// Такое было удовольствие!
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { глагол:быть{}.{
                             n3=<SUBJECT>*:*{}
                             attr=<SEPARATE_ATTR>*:*{ ПАДЕЖ:ИМ =n3:РОД =n3:ЧИСЛО }
                            } }
  then adj_noun_score(attr,n3)
}






// Ответы я давал самые несуразные.
// ^^^^^^               ^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { глагол:*{}.{
                          n3=<OBJECT>*:*{}
                          <SEPARATE_ATTR>*:*{ =n3:ПАДЕЖ =n3:РОД =n3:ЧИСЛО }
                         } }
  then 2
}

// ------------------------------------------------------------------


// Некоторые модальные редко употребляются без инфинитива:
// Разве можно в такую погоду как следует настроиться на мысль о  преступлении?
//       ^^^^^
wordentry_set МодальныеТребуютИнф=
{
 безлич_глагол:можно{},
 безлич_глагол:хочется{},
 безлич_глагол:захотелось{},
 глагол:мочь{},
 глагол:смочь{}
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{}.<LEFT_AUX_VERB>МодальныеТребуютИнф }
  then 7
}


// -------------------------------------------

// а им уже приходилось умирать вместе
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{}.{ <SUBJECT>местоимение:*{ падеж:дат } безлич_глагол:*{ МОДАЛЬНЫЙ } } }
  then 1
}

// Ей вдруг захотелось закричать от разочарования.
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{}.{ <OBJECT>"ей"{ падеж:твор } безлич_глагол:*{ МОДАЛЬНЫЙ } } }
  then -2
}

// Ей было приятно думать об этом.
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{}.{ <OBJECT>"ей"{ падеж:твор } } }
  then -1
}



// ------------------------------------------------------

// им давно пора уходить.

wordentry_set БезличнМодальн=безлич_глагол:{ пора, надо, нужно }

tree_scorer ВалентностьПредиката language=Russian generic
{
 if context { инфинитив:*{}.{ *:*{ падеж:дат } БезличнМодальн } }
  then 1
}

// -------------------------------------------------------

// у нас мало времени!
tree_scorer ВалентностьПредиката language=Russian
{
 if context { СчетнСвязка.{ предлог:у{} существительное:время{ падеж:род } } }
  then 10
}


// ----------------------------------------------

// ЕСЛИ не сочетается с императивом:
// - Не объясняйте, если не хотите.
//                  ^^^^    ^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{ наклонение:побуд }.'если' }
  then -10
}

// --------------------------------------------

// Частица НЕТ не всегда выполняет роль предикатива, иногда
// она выступает в роли вводной частицы, аналогично ДА:
// - Нет, вы не понимаете.
//   ^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { частица:нет{}.[not]<OBJECT>*:*{} }
  then -2
}


// ---------------------------------------------

// Позади никого не было.
//        ^^^^^^^^^^^^^^
// Пыли не было
// ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:быть{ наклонение:изъяв число:ед род:ср время:прошедшее }.{ частица:не{} <OBJECT>*:*{ ПАДЕЖ:РОД } } }
  then 4
}


// Радости не было предела
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:быть{ наклонение:изъяв число:ед род:ср время:прошедшее }.
               {
                частица:не{}
                <OBJECT>НеодушОбъект{ ПАДЕЖ:ДАТ }
                <OBJECT>'предела'{ ПАДЕЖ:РОД }
               }
            }
  then 6
}


// ---------------------------------------------

wordentry_set ОтрицМестоим = местоим_сущ:{ никто, ничто }

// Местоимение НИЧТО и НИКТО в косвенных падежах обычно прикрепляются
// только к глаголу с частией НЕ:
//
// Стояла ничем не нарушаемая тишина.
// ~~~~~~ ^^^^^ ^^ ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{}.{ [not]частица:не{} <OBJECT>ОтрицМестоим{} } }
  then -5
}

// -------------------------------------------------------

// Я имею на это право.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:иметь{}.{ <OBJECT>существительное:право{ ПАДЕЖ:ВИН } <PREPOS_ADJUNCT>предлог:на{}.*:*{ ПАДЕЖ:ВИН } } }
  then 1
}


// Они, должно быть, спустились с горы.
//                   ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:спуститься{}.предлог:с{}.*:*{ падеж:вин } }
  then -5
}

// ------------------------------------------------------------

// наконец усталость дала о себе знать.
//                   ^^^^        ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:знать{}.rus_verbs:дать{} }
  then 2
}

// ------------------------------------------------------------

// Но никто не обращал на них внимания.
//             ^^^^^^^^^^^^^^^^^^^^^^^

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:обращать{}.предлог:на{}.*:*{ ПАДЕЖ:ПРЕДЛ } }
  then -1
}



// распространяться по территории штата
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:распространяться{}.предлог:по{}.*:*{ ПАДЕЖ:ВИН } }
  then -1
}


// я собираюсь с тобой в прятки поиграть
//             ^^^^^^^          ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:поиграть{}.предлог:в{}.'прятки'{ ПАДЕЖ:ВИН } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:играть{}.предлог:в{}.'прятки'{ ПАДЕЖ:ВИН } }
  then 1
}

// бежать, повалявшись в снегу, обратно в тепло
// ^^^^^^                               ^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:бежать{}.предлог:в{}.*:*{ ПАДЕЖ:ВИН ОДУШ:НЕОДУШ } }
  then 1
}


// Ты сама ко мне лезла!
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:лезть{}.предлог:к{}.*:*{ ПАДЕЖ:ДАТ } }
  then 1
}

// В действительности же дело обстояло не так.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:обстоять{}.<SUBJECT>существительное:дело{} }
  then 1
}

// Тем дело пока и кончилось.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:кончиться{}.{ <SUBJECT>существительное:дело{} <OBJECT>*:*{ ПАДЕЖ:ТВОР } } }
  then 1
}

// На этом дело и кончилось.
//         ^^^^   ^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:кончиться{}.<SUBJECT>существительное:дело{} }
  then 1
}

// В действительности же дело обстояло не так.
//                       ^^^^ ^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:обстоять{}.<SUBJECT>существительное:дело{} }
  then 1
}


// Озеленение на этом не закончится.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:закончиться{}.предлог:на{}.*:*{ ПАДЕЖ:ПРЕДЛ } }
  then 1
}

// Ты что-то от меня скрываешь?
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:скрывать{}.предлог:от{}.ОдушОбъект{ ПАДЕЖ:РОД } }
  then 1
}


// мы будем атаковать
//    ^^^^^^^^^^^^^^^
tree_scorer ГлагИнф language=Russian generic
{
 if context { инфинитив:*{ ВИД:СОВЕРШ }.МодальныеТолькоНесоверш }
  then -100
}


// Ужин  был  подан,  и  все  сели  за  стол.
//                            ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:сесть{}.предлог:за{}.существительное:стол{} }
  then 1
}


// Ты совсем отстал от жизни.
//           ^^^^^^ ^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:отстать{}.предлог:от{} }
  then 2
}

// Тут есть над чем задуматься
//          ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:задуматься{}.предлог:над{} }
  then 2
}


// Пора было положить этому конец.
//           ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:положить{}.{ <OBJECT>существительное:конец{ ПАДЕЖ:ВИН } <OBJECT>*:*{ ПАДЕЖ:ДАТ }  } }
  then 2
}

// Задержать преступников по горячим следам милиционерам не удалось.
// ^^^^^^^^^              ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:задержать{}."по"."горячим"."следам" }
  then 4
}

// ----------------------------

// Особо обрабатываем ситуацию с появлением РОДИТЕЛЬНОЙ валентности в случае,
// когда модальный глагол стоит в отрицательной форме:
//
// Ломать вы ничего не хотите.
// ^^^^^^    ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН }
              .{
                <LEFT_AUX_VERB>глагол:*{}.<NEGATION_PARTICLE>частица:не{}
                <OBJECT>*:*{ ПАДЕЖ:РОД }
               }
            }
  then 3
}

// ----------------------------------------

// Они не хотят ее знать.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:знать{}.{ <LEFT_AUX_VERB>глагол:хотеть{} } }
  then 5
}


// Никому до тебя нет дела
tree_scorer ВалентностьПредиката language=Russian
{
 if context { частица:нет{}.{ <OBJECT>'дела'{ падеж:род } <PREPOS_ADJUNCT>предлог:до{} } }
  then 5
}

// Я не удостоил Ее ответом.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:удостоить{}.{ <OBJECT>*:*{ ПАДЕЖ:ДАТ } <OBJECT>'ответом' } }
  then 2
}

// -----------------------------------------------


// Горю родителей нет предела.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { частица:нет{}.{ <OBJECT>'предела'{ падеж:род } *:*{ ПАДЕЖ:ДАТ } } }
  then 5
}

// -----------------------------------------
// Он весь день провел со мной!
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:провести{}.{ <OBJECT>'день'.'весь' <PREPOS_ADJUNCT>предлог:с{}.*:*{ падеж:твор } } }
  then 4
}



// Рабочие день и ночь трудятся.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:трудиться{}.<ATTRIBUTE>'день'.'и'.'ночь' }
  then 2
}


wordentry_set СчетныеНаречия=наречие:{ мало, немало, много, немного, маловато, многовато }

// Но и этого будет мало.
//      ^^^^^^^^^^^^^^^^
// Контрпример:
// Несколько мгновений все было тихо.
// ~~~~~~~~~               ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:быть{}.{ <OBJECT>*:*{ падеж:род } <ATTRIBUTE>СчетныеНаречия } }
  then 5
}


// Шуму было много, однако гора родила мышь.
// ^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:быть{}.{ <OBJECT>*:*{ падеж:парт } <ATTRIBUTE>СчетныеНаречия } }
  then 5
}


// Я не удостоил Ее ответом.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:удостоить{}.{ <OBJECT>*:*{ падеж:вин } <OBJECT>'ответом' } }
  then 2
}

word_set ЕеЕгоИхОбъект = { 'ее', 'его', 'их' }

// Аня неумело стиснула ее зубами.
//             ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖ:ВИН ~ПАДЕЖ:ТВОР }.
              {
               <OBJECT>ЕеЕгоИхОбъект{ падеж:вин }
               <OBJECT>*:*{ падеж:твор }
              }
            }
  then 2
}


// Орлиц в поле зрения не оказалось.
//       ^^^^^^^^^^^^^    ^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { rus_verbs:оказаться{}.<PREPOS_ADJUNCT>предлог:в{}.'поле'{ РОД:СР ПАДЕЖ:ПРЕДЛ }.'зрения' }
  then 2
}


// Я пересекла двор и села рядом с ней.
//                    ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:сесть{}.<PREPOS_ADJUNCT>предлог:с{}.<ATTRIBUTE>наречие:рядом{} }
  then 2
}


// Я всегда стою, обучая кого-то.
// ^^       ^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:стоить{}.<SUBJECT>местоимение:я{ лицо:1 } }
  then -2
}

// Окончив первый, принялся за второй.
//                 ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:приняться{}.<PREPOS_ADJUNCT>предлог:за{}.*:*{ ПАДЕЖ:ТВОР } }
  then -2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:приниматься{}.<PREPOS_ADJUNCT>предлог:за{}.*:*{ ПАДЕЖ:ТВОР } }
  then -2
}


// Оставшихся в живых они же заперли в резервациях.
// ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:остаться{}.<PREPOS_ADJUNCT>предлог:в{}.'живых' }
  then 2
}

// Ворованные автомобили злоумышленники разбирали на запчасти и продавали.
//                                      ^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:разбирать{}.<PREPOS_ADJUNCT>предлог:на{}.существительное:*{ падеж:вин одуш:неодуш } }
  then 2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:разобрать{}.<PREPOS_ADJUNCT>предлог:на{}.существительное:*{ падеж:вин одуш:неодуш } }
  then 2
}

// Белолобый неприязненно смерил его взглядом.
//                        ^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смерить{}.{ <OBJECT>*:*{ падеж:вин } <OBJECT>'взглядом' } }
  then 2
}


// Безмерно нибелунги о Зигфриде грустили.
//                    ^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:грустить{}.<PREPOS_ADJUNCT>предлог:о{}.<OBJECT>*:*{ падеж:предл } }
  then 1
}


// Блондин потащил девчонку к двери;
//                 ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:потащить{}.<PREPOS_ADJUNCT>предлог:к{} }
  then 1
}


// Сняв шляпу, Рэнналф прибавил шагу.
//                     ^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:прибавить{}.<OBJECT>'шагу'{ падеж:парт } }
  then 3
}


// Хвалю я ее за это?
// ^^^^^      ^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:хвалить{}.<PREPOS_ADJUNCT>предлог:за{}.<OBJECT>*:*{ падеж:вин } }
  then 2
}

// Александр улыбнулся, пожирая её глазами.
//                      ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пожирать{}.{ <OBJECT>*:*{ ПАДЕЖ:ВИН } 'глазами' } }
  then 2
}


// мне будет сорок один год
tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:быть{ число:ед лицо:3 время:будущее }.
              {
               <SUBJECT>существительное:год{}.числительное:*{}
               <OBJECT>*:*{ падеж:дат }
              }
            }
  then 2
}

// Мне было двадцать три года.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { глагол:быть{ число:ед род:ср время:прошедшее }.
              {
               <SUBJECT>существительное:год{}.числительное:*{}
               <OBJECT>*:*{ падеж:дат }
              }
            }
  then 2
}

// Устойчивый оборот: принять участие в чем-то:
//
// В экспедиции приняли участие много иностранцев.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:принять{}.{ <OBJECT>существительное:участие{ ПАДЕЖ:ВИН } <PREPOS_ADJUNCT>предлог:в{}.*:*{ падеж:предл } } }
  then 1
}

// Женщина и ребенок с ног валились.
//                   ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:валиться{}.'с'.'ног' }
  then 2
}


// Ведет оседлый и полуоседлый образ жизни.
// ^^^^^                       ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:вести{}.<OBJECT>'образ'.'жизни' }
  then 2
}


// Я обещался в точности исполнить поручение.
//            ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:исполнить{}.'в'.'точности'{ падеж:предл } }
  then 2
}



// Впрочем, может быть и меньше.
//                       ~~~~~~
tree_scorer ВалентностьПредиката language=Russian
{
 if context { СчетнСвязка.[not]<OBJECT>*:*{} }
  then -3
}


// Проехали километра два.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:проехать{}.<OBJECT>существительное:километр{} }
  then 4
}

// Прошли пять километров
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пройти{}.<OBJECT>существительное:километр{} }
  then 4
}

// Пройдет много лет.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:пройти{}.<SUBJECT>'лет'.'много' }
  then 4
}

// Ничего не видит.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:видеть{}.<SUBJECT>'ничего' }
  then -4
}

// Ничего не знает.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:знать{}.<SUBJECT>'ничего' }
  then -4
}

// Ничего не боится.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:бояться{}.<SUBJECT>'ничего' }
  then -4
}

// Взяли в клещи.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:взять{}.'в'.'клещи'{ ПАДЕЖ:ВИН} }
  then 2
}

// К вам пришли!
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:придти{}.'к'.*:*{ ПАДЕЖ:ДАТ } }
  then 1
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:прийти{}.'к'.*:*{ ПАДЕЖ:ДАТ } }
  then 1
}

// Сергиенко воспользовался моментом.
//           ^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:воспользоваться{}.[not]<OBJECT>*:*{ ПАДЕЖ:ТВОР } }
  then -1
}




// Готовиться времени нет.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { частица:нет{}.'времени'.<INFINITIVE>инфинитив:*{} }
  then 4
}

// Дал время подумать.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:дать{}.<OBJECT>существительное:время{ падеж:вин }.<INFINITIVE>инфинитив:*{} }
  then 4
}

// -------------------------------------------------------------------------------

// Ночь выдается беспокойная.
// ^^^^^^^^^^^^^
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:выдаваться{}.<SUBJECT>СущСоЗначВремКакОбст1{ ПАДЕЖ:ИМ } }
  then 4
}

tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:выдаться{}.<SUBJECT>СущСоЗначВремКакОбст1{ ПАДЕЖ:ИМ } }
  then 4
}


tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:выдаваться{}.<ATTRIBUTE>СущСоЗначВремКакОбст1{} }
  then -10
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:выдаться{}.<ATTRIBUTE>СущСоЗначВремКакОбст1{} }
  then -10
}


// -------------------------------------------------------------------------------


// Что говорит свинец?
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:говорить{}.<SUBJECT>местоим_сущ:что{} }
  then -3
}


// В детях эта программа усиливается во много раз.
//                                   ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:усиливаться{}."во"."раз"."много" }
  then 5
}


// Я посмотрел на часы.
//   ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:посмотреть{}."на".*{ ПАДЕЖ:ВИН } }
  then 3
}

// К вам пришли!
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:придти{}."к".ОдушОбъект }
  then 3
}

// Он бросил взгляд на часы. (БРОСИТЬ ВЗГЛЯД НА что-то)
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:бросить{}.{ <OBJECT>"взгляд"{ ПАДЕЖ:ВИН } <PREPOS_ADJUNCT>"на".*:*{ ПАДЕЖ:ВИН } } }
  then 3
}

// Женщина и ребенок с ног валились. (ВАЛИТЬСЯ С НОГ)
//                   ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:валиться{}."с"."ног" }
  then 3
}

// стыдно ребятам в глаза смотреть. (СМОТРЕТЬ В ГЛАЗА)
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смотреть{}."в"."глаза"{ ПАДЕЖ:ВИН } }
  then 3
}

// Надежнее иметь дело со взрослыми. (ИМЕТЬ ДЕЛО С кем-то/чем-то)
//          ^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:иметь{}.{ <OBJECT>существительное:дело{ падеж:вин } <PREPOS_ADJUNCT>предлог:с{}.*:*{ ПАДЕЖ:ТВОР } } }
  then 3
}

// Вдохновлял он ее и на поэмы. (ВДОХНОВЛЯТЬ/ВДОХНОВИТЬ НА что-то)
// ^^^^^^^^^^       ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:вдохновлять{}.<PREPOS_ADJUNCT>предлог:на{}.*:*{ ПАДЕЖ:ВИН } }
  then 3
}


// Оставшихся в живых они же заперли в резервациях. (ОСТАТЬСЯ В ЖИВЫХ)
// ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:остаться{}.<PREPOS_ADJUNCT>предлог:в{}.'живых' }
  then 3
}


// Я стояла, провожая его взглядом. (ПРОВОЖАТЬ кого-то/что-то ВЗГЛЯДОМ)
//           ^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:провожать{}.{ <OBJECT>*:*{ ПАДЕЖ:ВИН } 'взглядом' } }
  then 3
}


// Эпидемии гриппа не ожидается
tree_scorer ВалентностьГлагола language=Russian
{
 if context { "ожидается".{ <OBJECT>*:*{ ПАДЕЖ:РОД } 'не' } }
  then 3
}

// --------------------------------------------------------------------------

// Прикажи дать коньяку.
//         ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:дать{}.<OBJECT>*:*{ ПАДЕЖ:ПАРТ <в_класс>СУЩЕСТВИТЕЛЬНОЕ:НАПИТОК{} } }
  then 6
}

// Там дела важнее.
//     ^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { 'дела'.<ATTRIBUTE>НАРЕЧИЕ:*{ СТЕПЕНЬ:СРАВН } }
  then -10
}

// --------------------------------------------------------------------

// Что делает Танасчишин?
// ~~~~~~~~~~
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:делать{}.<SUBJECT>местоим_сущ:что{} }
  then -3
}

// -------------------------------------------------------
// Нельзя допустить атрофии.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { инфинитив:допустить{}.{ <LEFT_AUX_VERB>безлич_глагол:Нельзя{} <OBJECT>*:*{ падеж:род } } }
  then 3
}

// --------------------------------------------------------
// Надо Дорошенко сказать.
//      ^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:сказать{}.<OBJECT>существительное:*{ ОДУШ:ОДУШ ПАДЕЖ:ТВОР } }
  then -5
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:сказать{}.<OBJECT>существительное:*{ ОДУШ:ОДУШ ПАДЕЖ:ВИН } }
  then -5
}

// --------------------------------------------------------------
// Тем не менее досталось всем.
//              ^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:достаться{}.<ATTRIBUTE>'всем'{ ПАДЕЖ:ТВОР } }
  then -20
}


// Наконец достигли вершины.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:достичь{}.<OBJECT>НеодушОбъект{ ПАДЕЖ:РОД } }
  then 3
}



// --------------------------------------------------------------
// Возглавляет его мэр.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:возглавлять{}.[not]<OBJECT>*:*{ ПАДЕЖ:ВИН } }
  then -3
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:возглавлять{}.<OBJECT>существительное:*{ ПАДЕЖ:ВИН } }
  then -3
}

/*
// Засыпаю его вопросами.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:засыпать{ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ }.{ <OBJECT>*:*{ ПАДЕЖ:ВИН } <OBJECT>'вопросами' } }
  then 2
}
*/




// Разбудила его Надя.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:разбудить{}.{ <OBJECT>*:*{ ПАДЕЖ:ВИН } <SUBJECT>*:*{} } }
  then 2
}

// Прошло две недели.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { 'прошло'.<SUBJECT>СущСоЗначВрем{ ПАДЕЖ:РОД }.числительное:*{} }
  then 2
}


// Я просидел дома весь день
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:просидеть{}.<ATTRIBUTE>'день'{ ПАДЕЖ:ВИН }.<ATTRIBUTE>'весь'{ ПАДЕЖ:ВИН } }
  then 2
}
 
// Сегодня я весь день читал.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:читать{}.<ATTRIBUTE>'день'{ ПАДЕЖ:ВИН }.<ATTRIBUTE>'весь'{ ПАДЕЖ:ВИН } }
  then 2
}

// я буду работать весь день
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:работать{}.<ATTRIBUTE>'день'{ ПАДЕЖ:ВИН }.<ATTRIBUTE>'весь'{ ПАДЕЖ:ВИН } }
  then 2
}

// вместе они шли весь день.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:идти{}.<ATTRIBUTE>'день'{ ПАДЕЖ:ВИН }.<ATTRIBUTE>'весь'{ ПАДЕЖ:ВИН } }
  then 2
}

// бой продолжался весь день.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:продолжаться{}.<ATTRIBUTE>'день'{ ПАДЕЖ:ВИН }.<ATTRIBUTE>'весь'{ ПАДЕЖ:ВИН } }
  then 2
}


// битва длилась весь день.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:длиться{}.<ATTRIBUTE>'день'{ ПАДЕЖ:ВИН }.<ATTRIBUTE>'весь'{ ПАДЕЖ:ВИН } }
  then 2
}

// мы играли во дворе целый день
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:играть{}.<ATTRIBUTE>'день'{ ПАДЕЖ:ВИН }.<ATTRIBUTE>'целый'{ ПАДЕЖ:ВИН } }
  then 2
}

// У меня к тебе дело
//        ~~~~~~~~~~~
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:деть{ род:ср }.предлог:к{}.*:*{ падеж:дат } }
  then -10
}


// дайте им три часа.
// ^^^^^    ^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:дать{}.<OBJECT>существительное:час{}.числительное:*{} }
  then 5
}


// Важное значение имеет и нестационарность Метагалактики.
// ^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:иметь{}.<OBJECT>существительное:значение{}.'важное' }
  then 10
}



// Я не теряю надежды.
//   ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:терять{}.{ <NEGATION_PARTICLE>частица:не{} <OBJECT>существительное:надежда{ падеж:род число:ед } } }
  then 1
}


// Вы не знаете Дезире?
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:знать{}.<OBJECT>существительное:*{ одуш:одуш падеж:твор } }
  then -5
}

// Я целую Викторию...
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:целовать{}.<OBJECT>существительное:*{ одуш:одуш падеж:дат } }
  then -5
}

// Благоустройство кладбища продолжалось и летом.
//                          ^^^^^^^^^^^^   ^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:продолжаться{}.<ATTRIBUTE>существительное:лето{ падеж:твор } }
  then 5
}

// ----------------------------------------------------------------

// Ей нужен был отдых.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { прилагательное:нужный{ краткий }.'ей'{ падеж:твор } }
  then -5
}


tree_scorer ВалентностьПредиката language=Russian
{
 if context { прилагательное:нужный{ краткий }.'им'{ падеж:твор } }
  then -5
}


// - Я тебе дам знать .
tree_scorer ВалентностьГлагола language=Russian
{
 if context { инфинитив:знать{}.rus_verbs:дать{} }
  then 5
}

// Для отправителя они не представляли опасности.
//                     ^^^^^^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:представлять{}.'опасности'{ ПАДЕЖ:РОД } }
  then 5
}

// К вам это не имело отношения.
//           ^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:иметь{}.'отношения'{ ЧИСЛО:МН } }
  then -1
}

// ты встала на его пути
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:встать{}.'на'.'пути'{ ПАДЕЖ:ВИН } }
  then -2
}


// Она хотела стать моей
//     ^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:хотеть{}.<OBJECT>существительное:стать{} }
  then -10
}


// откуда нам это знать?
tree_scorer ВалентностьПредиката language=Russian
{
 if context { инфинитив:знать{}.{ <ATTRIBUTE>наречие:откуда{} <OBJECT>*:*{ падеж:дат } } }
  then 2
}


// друид встал на их пути
//       ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:встать{}.<PREPOS_ADJUNCT>предлог:на{}.<OBJECT>существительное:путь{ падеж:вин } }
  then -2
}

// «Мы вытолкнули Украину из Русского мира»
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:вытолкнуть{}.<PREPOS_ADJUNCT>предлог:из{} }
  then 2
}

// Владимир Путин объявил финансовые пирамиды вне закона
//                ^^^^^^^                     ^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:объявить{}.<PREPOS_ADJUNCT>предлог:вне{} }
  then 2
}


// Содержание их было однообразно.  
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rhema=прилагательное:*{ КРАТКИЙ ЧИСЛО:ЕД РОД:СР }.{ thema=<SUBJECT>существительное:*{ ЧИСЛО:ЕД РОД:СР } } }
  then adj_noun_score(rhema,thema)
}

// Отдам краснохвостого сома в хорошие руки
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:отдать{}.предлог:в{}.'руки'.'хорошие' }
  then 5
}

// ----------------------------------------------------------------

// Приобретает массовый характер Стахановское движение.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:приобретать{}.<OBJECT>существительное:характер{}.<ATTRIBUTE>прилагательное:массовый{} }
  then 5
}

// Фашистские стрелки открывают ответный огонь.
tree_scorer ВалентностьПредиката language=Russian
{
 if context { rus_verbs:открывать{}.{ <SUBJECT>существительное:стрелок{} <OBJECT>существительное:огонь{} } }
  then 5
}

// Документы эти разрабатывались соответствующими начальниками.
// Старый хрыч обернулся добродушным дедулей.
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{}.<ATTRIBUTE>существительное:*{ падеж:твор одуш:одуш } }
  then -2
}


// Он смотрел на танцующих вытаращенными глазами.
//    ^^^^^^^^^^^^^^^^^^^^
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смотреть{}.предлог:на{}.прилагательное:*{ падеж:предл } }
  then -5
}

// Ей в глаза смотрела дама червей.
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:смотреть{}.{ предлог:в{} "ей"{падеж:твор} } }
  then -5
}


// ----------------------------------------------------------------

#define vap(v,adv,p,w) \
#begin
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:v{}.<PREPOS_ADJUNCT>ПРЕДЛОГ:p{}.<ATTRIBUTE>НАРЕЧИЕ:adv{} }
  then w
}
#end

vap(стоять,впритык,к,1) // Шкаф стоит впритык к столу.
vap(стоять,вплотную,к,1) // Шкаф стоит вплотную к столу.
vap(бежать,следом,за,2) // она как раз начала бежать следом за ним
vap(быть,рядом,с,2) // он был рядом с дверью
vap(пойти,следом,за,2) // Катя пошла следом за ними.

// Я приехал в Москву одновременно с братом.
//   ^^^^^^^          ^^^^^^^^^^^^^^
vap(приехать,одновременно,с,1)
vap(прийти,одновременно,с,1)
vap(прибыть,одновременно,с,1)
vap(появиться,одновременно,с,1)

// Петя положил яблоки вместе с картошкой.
//      ^^^^^^^        ^^^^^^^^
vap(положить,вместе,с,1)
vap(ложить,вместе,с,1)
vap(положить,слева,от,2) // Положи книгу слева от тетради

vap(глядеть,прямо,в,5) // глядя прямо в ее круглые карие глаза, произнес
vap(посмотреть,прямо,в,5)
vap(смотреть,прямо,в,5)
vap(заглянуть,прямо,в,5)
vap(швырнуть,прямо,в,5) // Он подлетает к башне и... сейчас кибер швырнет нашего  гладиатора прямо в ее пустую утробу.
vap(швырять,прямо,в,5)
vap(кинуть,прямо,в,5)
vap(кидать,прямо,в,5)
