// ===========================
// СОСТАВНЫЕ ПРЕДЛОЖЕНИЯ
// ===========================

// TODO: переделать на восходящую сборку.


wordentry_set СоедСоюзДляСложнПредл=
{
 союз:хотя{}, // Он мчался к перекрестку, хотя на светофоре горел красный свет.
 союз:так как{}, // Массивность ворона не удивила  Вольфа,  так  как  он  повидал  немало довольно громадных существ.
 союз:так что{}, // никого нет, так что некому жаловаться
 союз:что{}, // я думаю, что дождь скоро прекратится
 союз:чтобы{}, // я хочу, чтобы птица начала петь
 союз:с тем чтобы{},
 союз:поэтому{}, // лето было жаркое, поэтому трава выгорела
 союз:и{}, // Опустел сад, и осыпались листья
 союз:однако{}, // Он уже старик, однако он так бодр душой
 союз:да и{}, // Я его любила, да и он мне отвечал тем же
 союз:зато{}, // Васёк был разиня, зато он умел песни петь
 союз:когда{}, // Опустел сад, когда осыпались листья
 союз:а{}, // собака - животное, а капуста - растение
 союз:но{}, // Акула - рыба, но кит - млекопитающее
 союз:потому что{}, // Все чувствовали себя свободно, потому что никто не старался занимать гостей
 союз:как{},  // Сегодня я была счастлива, как я никогда не была счастлива до этого
 союз:да{}, // блестели разноцветные гирлянды, да горели яркие огоньки
 союз:ибо{}, // И не благодарите меня, ибо меньшим злом я искупаю зло большее!
 союз:не то{}, // Вставай, не то опоздаем
 союз:а не то{},
 союз:а то{}
}


// Но тебе никогда не удастся вернуться в прерии, потому что мы будем ждать тебя!
pattern СложноПредлож
{
 opener=СоюзКакВводн
 s=СложноПредлож : export { node:root_node }
} : links { s.<BEG_INTRO>opener }



// Нет, он тоже спал, но его рот и глаза были открыты.
pattern СложноПредлож
{
 intro=ВводнаяФраза
 p=СложноПредлож : export { node:root_node }
} : links { p.<BEG_INTRO>intro }


// всем  известно, что политиков делают имиджмейкеры
pattern СложноПредлож
{
 p1=КраткПрилРема{ РОД:СР ЧИСЛО:ЕД } : export { node:root_node }
 comma=','
 conj=СоедСоюзДляСложнПредл
 p2=Предикат
} : links
{
 p1.<NEXT_CLAUSE>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p2
}



// мы танцевали - ты смотрел
pattern СложноПредлож
{
 p1=КраткПрилРема{ РОД:СР ЧИСЛО:ЕД } : export { node:root_node }
 t=ДефисКакСвязка
 p2=Предикат
}
: links { p1.<NEXT_CLAUSE>t.<NEXT_COLLOCATION_ITEM>p2 }
: ngrams { -2 }




// Если бред полностью овладевает сознанием, то такое состояние называют острым бредом
pattern СложноПредлож
{
 conj1=союз:если{}
 v=Предикат:export{ node:root_node }
 comma=','
 conj2=союз:то{}
 v2=Сказуемое0{ =V:ЛИЦО =V:ЧИСЛО =V:РОД}
}
: links
{
 v.{
    <PREFIX_CONJUNCTION>conj1
    <RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj2.<SUBORDINATE_CLAUSE>v2
   }
}
: ngrams { -1 }


// ---------------------------------------------

tree_scorers ВалентностьСложнСказ


// -------------------------------------------------

patterns ЭлементСложногоПредлож export { node:root_node }

pattern ЭлементСложногоПредлож
{
 Предикат : export { node:root_node }
}

/*
pattern ЭлементСложногоПредлож
{
 ПредикатИмператив : export { node:root_node }
}
*/

// никого нет, так что некому жаловаться
//                     ^^^^^^^^^^^^^^^^^
pattern ЭлементСложногоПредлож
{
 Инф2 : export { node:root_node }
} : ngrams { -5 }



pattern ЭлементСложногоПредлож
{
 Сказуемое : export { node:root_node }
} : ngrams { -5 }


// Группа наречия в роли элемента сложного предложения:
// - Ой больно, отпусти! - завизжал Алёша.
//   ^^^^^^^^^
pattern ЭлементСложногоПредлож
{
 ГруппаНареч2 : export { node:root_node }
} : ngrams { -10 }


// -------------------------------------------------

patterns ХвостСложногоПредлож export { node:root_node }

pattern ХвостСложногоПредлож
{
 ЭлементСложногоПредлож : export { node:root_node }
}

pattern ХвостСложногоПредлож
{
 СложноПредлож : export { node:root_node }
}



// Вот просто перестала, и все.
//                       ^^^^^
pattern ХвостСложногоПредлож
{
 w1=частица:всё{} : export { node:root_node }
 @noshift(ПравыйОграничительОборота)
}

// Вот чувствовал - и все тут...
//                    ^^^^^^^
pattern ХвостСложногоПредлож
{
 w1=частица:всё{} : export { node:root_node }
 w2=наречие:тут{}
 @noshift(ПравыйОграничительОборота)
}
: links { w1.<NEXT_COLLOCATION_ITEM>w2 }



// -------------------------------------------------


// Чем дальше ехали на юг, тем становилось жарче.
// ^^^ ~~~~~~            ^^^^^
pattern СложноПредлож
{
 conj1=союз:чем{}
 @noshift(ГруппаСрНареч1)
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma1=','
 conj2='тем'
 p2=ХвостСложногоПредлож
} : links
{
 p1.{
     <PREFIX_CONJUNCTION>conj1
     <NEXT_CLAUSE>comma1.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>p2
    }
}

// --------------------------------------------------


// я думаю, что дождь скоро прекратится
// Повод не затягивай, и все будет  как надо.
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma=','
 conj=СоедСоюзДляСложнПредл
 p2=ХвостСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p2
}
: ngrams
{
 ВалентностьСложнСказ(p1)
 1
}



// А темно в коридоре было потому, что Джордж Уэбер - жуткий скряга.
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 conj=союз:"потому,что"{}
 p2=ХвостСложногоПредлож
}
: links { p1.<NEXT_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>p2 }
: ngrams { 1 }






wordentry_set ПротивСоюз=союз:{ но, а }

// Они  подняли  головы  и  самец  зарычал,  а   самка завизжала.
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 conj=союз:и{}
 p2=ЭлементСложногоПредлож
 comma=','
 conj2=ПротивСоюз
 p3=ХвостСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>conj.
     <NEXT_COLLOCATION_ITEM>p2.
      <NEXT_CLAUSE>comma.
       <NEXT_COLLOCATION_ITEM>conj2.
        <NEXT_COLLOCATION_ITEM>p3
}


// Они проехали его, воздух стал немного чище, но серая дымка снова оказалась впереди. 
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma1=','
 p2=ЭлементСложногоПредлож
 comma2=','
 conj2=ПротивСоюз
 p3=ХвостСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>comma1.
     <NEXT_COLLOCATION_ITEM>p2.
      <NEXT_CLAUSE>comma2.
       <NEXT_COLLOCATION_ITEM>conj2.
        <NEXT_COLLOCATION_ITEM>p3
}



// ей перестали доверять или это общая смена курса?
// На ёлке блестели разноцветные гирлянды и горели яркие огоньки
// Другие входы тоже изрыгали вспышки пламени или же их защита  сгорела.
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 conj=ЛогичСоюз
 p2=ХвостСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>p2
}
: ngrams { -1 } // делаю штраф, так как вообще-то в таком предложении нужна запятая.


// Если в разбираемом предложении фактически два, разделенные точкой.
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 conj='.'
 p2=ХвостСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>p2
}



// А что если она заметит его?
//   ^^^^^^^^...
pattern СложноПредлож
{
 p1=местоим_сущ:что{ падеж:им } : export { node:root_node }
 conj=союз:если{}
 p2=ХвостСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>conj.<NEXT_COLLOCATION_ITEM>p2
}
: ngrams { 4 }



// Желтые клювы хищно раскрылись, когти импульсивно сжались, а крылья и тела затрепетали.
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma1=','
 p2=ЭлементСложногоПредлож
 comma2=','
 conj=союз:а{}
 p3=ХвостСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>comma1.
     <NEXT_COLLOCATION_ITEM>p2.
      <NEXT_CLAUSE>comma2.<NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>p3
}


// -----------------------------------

/*
// *******************************************************
// Сложносочиненное предложение, первый клоз - императив,
// второй - поясняющее высказывание.
// *******************************************************

// Не задерживайте, я очень тороплюсь.
pattern СложноПредлож
{
 p1=ПредикатИмператив : export { node:root_node }
 comma=','
 p2=Предикат
} : links
{
 p1.<NEXT_CLAUSE>comma.
      <NEXT_COLLOCATION_ITEM>p2
}
*/


/*
pattern СложноПредлож
{
 p1=ПредикатИмператив : export { node:root_node }
 comma=','
 conj=ЛогичСоюз
 p2=Предикат
} : links
{
 p1.<NEXT_CLAUSE>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p2
}
*/




// ----------------------------------



word_set СочинПредложТокенЭлем=
{
 ';', // Его грудь побелела от пены; он дрожал и задыхался.
 ':', // скуластое лицо Егорки сияло радостью: он научился ездить верхом
 ',' // Его грудь побелела от пены, он дрожал и задыхался.
}

patterns СочинПредложТокен export { node:root_node }
pattern СочинПредложТокен
{
 СочинПредложТокенЭлем : export { node:root_node }
}



// Использование тире в качестве разделителя в сложном предложении вносит
// путаницу в распознавание паттернов нулевой связки ТЕМА - РЕМА. Поэтому
// делаем большой штраф.
//
// девушка улыбнулась - блеснули ровные белые зубы
// Я точно знал — буду программистом.

word_set СоединитПредложТире={ '-', '—', '–' }

pattern СочинПредложТокен
{
 СоединитПредложТире : export { node:root_node }
} : ngrams { -12 }



/*
// Второе предложение представлено только сказуемым:
// Преступник отказался от дачи показаний, ему назначили психиатрическую экспертизу.
// она вновь почувствовала - за ней наблюдают
pattern СложноПредлож
{
 p1=ГлПредикат : export { node:root_node }
 conj=СочинПредложТокен
 p2=Сказуемое
} : links
{
 p1.<NEXT_CLAUSE>conj.
     <NEXT_COLLOCATION_ITEM>p2
}
: ngrams { -2 }
*/

// могу сказать точно - она была счастлива
// Вскоре им предстояло выяснить: способны ли кони выдержать такой рывок и не оступится ли кто-нибудь из них на ходу.
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 conj=СочинПредложТокен
 p2=ХвостСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>conj.
     <NEXT_COLLOCATION_ITEM>p2
}
//: ngrams { -1 }



// Конец лестницы отодвинулся от края отверстия, а потом ее вообще убрали.
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma=','
 conj=союз:а{}
 p2=ХвостСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>comma.<NEXT_COLLOCATION_ITEM>conj.
     <NEXT_COLLOCATION_ITEM>p2
}
: ngrams { -2 }




// если кошка догонит мышку, то она ее съест
pattern СложноПредлож
{
 conj1=союз:если{}
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma=','
 conj2=союз:то{}
 p2=ХвостСложногоПредлож
} : links
{
 p1.{
     <PREFIX_CONJUNCTION>conj1
     <NEXT_CLAUSE>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>p2
    }
}

// так как лето было жаркое, то трава выгорела
pattern СложноПредлож
{
 conj1=союз:так как{}
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma=','
 conj2=союз:то{}
 p2=ХвостСложногоПредлож
} : links
{
 p1.{
     <PREFIX_CONJUNCTION>conj1
     <NEXT_CLAUSE>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>p2
    }
}


/*
// Когда наступил поздний вечер, в небе зажглись неяркие звёзды
pattern СложноПредлож
{
 conj=союз:когда{}
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma=','
 p2=ХвостСложногоПредлож
} : links
{
 p1.{
     <PREFIX_CONJUNCTION>conj
     <NEXT_CLAUSE>comma.
      <NEXT_COLLOCATION_ITEM>p2
    }
}
:ngrams{1}
*/


/*
// сначала кошка догонит мышку, затем она ее съест
pattern СложноПредлож
{
 adv1=наречие:сначала{}
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma=','
 conj=@optional(союз:а{})
 adv2=наречие:затем{}
 p2=ХвостСложногоПредлож
} : links
{
 p1.{
     <ATTRIBUTE>adv1
     <NEXT_CLAUSE>comma.{
                         ~<PREFIX_CONJUNCTION>conj
                         <NEXT_COLLOCATION_ITEM>p2.<ATTRIBUTE>adv2
                        }
     
    }
}
*/



// То снег идет, то мелкий дождь сыплет
pattern СложноПредлож
{
 conj1=союз:то{}
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma=','
 conj2=союз:то{}
 p2=ХвостСложногоПредлож
} : links
{
 p1.{
     <PREFIX_CONJUNCTION>conj1
     <NEXT_CLAUSE>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>p2
    }
}
: ngrams { 1 } // чтобы подавить вариант то=местоим_сущ


// Ни одного звука не слышу, ни одна травинка не шелохнется
pattern СложноПредлож
{
 conj1=союз:ни{}
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma=','
 conj2=союз:ни{}
 p2=ХвостСложногоПредлож
} : links
{
 p1.{
     <PREFIX_CONJUNCTION>conj1
     <NEXT_CLAUSE>comma.
      <NEXT_COLLOCATION_ITEM>conj2.
       <NEXT_COLLOCATION_ITEM>p2
    }
}

/*
// ??? нужно ли правило?
// а теперь скажи : где ты научился так драться?
pattern СложноПредлож
{
 p1=ПредикатИмператив : export { node:root_node }
 conj=':'
 p2=Предикат
} : links
{
 p1.<NEXT_CLAUSE>conj.
     <NEXT_COLLOCATION_ITEM>p2
}
*/


// скуластое лицо Егорки сияло радостью: он научился ездить верхом
// а теперь скажи : где ты научился так драться?
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 junc=СочинПредложТокен
 p2=ХвостСложногоПредлож
} : links { p1.<NEXT_CLAUSE>junc.<NEXT_COLLOCATION_ITEM>p2 }




// Оборот вежливости "СПАСИБО, ЧТО ... " не является вводной
// конструкцией, его надо бы разбирать как составное предложение:
//
// - Спасибо, что приехали.
//   ^^^^^^^^^^^^
pattern СложноПредлож
{
 @probe_left(ЛевыйОграничительОборота)
 p0=существительное:спасибо{ падеж:им } : export { node:root_node }
 comma=','
 junc=союз:что{}
 p2=ХвостСложногоПредлож
} 
: links { p0.<NEXT_CLAUSE>comma.<NEXT_COLLOCATION_ITEM>junc.<NEXT_COLLOCATION_ITEM>p2 }
: ngrams { 2 }




/* ---ПРОВЕРИТЬ РАЗБОР---
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma1=','
 p2=ЭлементСложногоПредлож
 comma2=','
 p3=ЭлементСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>comma1.
     <NEXT_COLLOCATION_ITEM>p2.
      <NEXT_CLAUSE>comma2.
       <NEXT_COLLOCATION_ITEM>p3
}

// ---ПРОВЕРИТЬ РАЗБОР---
// Густеют хлопья, тают слухи, густеют слухи, тает снег
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma1=','
 p2=ЭлементСложногоПредлож
 comma2=','
 p3=ЭлементСложногоПредлож
 comma3=','
 p4=ЭлементСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>comma1.
     <NEXT_COLLOCATION_ITEM>p2.
      <NEXT_CLAUSE>comma2.
       <NEXT_COLLOCATION_ITEM>p3.
        <NEXT_CLAUSE>comma3.
         <NEXT_COLLOCATION_ITEM>p4
}
*/

/*---ПРОВЕРИТЬ РАЗБОР---
// Всюду цветут луговые цветы, трезвонят птицы и стрекочут кузнечики
pattern СложноПредлож
{
 p1=ЭлементСложногоПредлож : export { node:root_node }
 comma=','
 p2=ЭлементСложногоПредлож
 conj=союз:и{}
 p3=ЭлементСложногоПредлож
} : links
{
 p1.<NEXT_CLAUSE>comma.
     <NEXT_COLLOCATION_ITEM>p2.
      <NEXT_CLAUSE>conj.
       <NEXT_COLLOCATION_ITEM>p3
}
*/

/*
// ??? нужны ли правила
// Нью-Йорк: финансовая столица США
pattern СложноПредлож
{
 p1=ГруппаСущ4{ПАДЕЖ:ИМ} : export { node:root_node }
 colon=':'
 p2=ГруппаСущ4{ПАДЕЖ:ИМ}
}:links { p1.<NEXT_CLAUSE>colon.<NEXT_COLLOCATION_ITEM>p2 }
*/


// язык газетных заголовков:
//
// Синоптики: в четверг возможны дожди, град и грозы
pattern СложноПредлож
{
 p1=ГруппаСущ4{ПАДЕЖ:ИМ} : export { node:root_node }
 colon=':'
 p2=ХвостСложногоПредлож
}:links { p1.<NEXT_CLAUSE>colon.<NEXT_COLLOCATION_ITEM>p2 }


// Таджикистан и Узбекистан: конфронтация или движение друг к другу?
pattern СложноПредлож
{
 p1=ГруппаСущ4{ПАДЕЖ:ИМ} : export { node:root_node }
 colon=':'
 p2=ГруппаСущ4{ПАДЕЖ:ИМ}
} : links { p1.<NEXT_CLAUSE>colon.<NEXT_COLLOCATION_ITEM>p2 }

// --------------------------------------------------------



/*
// ??? нужно ли правило?
// мне кажется, что дождь скоро прекратится
pattern СложноПредлож
{
 sbj=БезличПодлежащее{ПАДЕЖ:ДАТ}
 v=БЕЗЛИЧ_ГЛАГОЛ:*{} : export { node:root_node }
 comma=','
 conj=союз:что{}
 p=Предикат
} : links
{
 v.{
    <SUBJECT>sbj
    <SUBORDINATE_CLAUSE>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p
   }
}


// ??? нужно ли правило?
// мне хотелось, чтобы птица начала петь
pattern СложноПредлож
{
 sbj=БезличПодлежащее{ПАДЕЖ:ДАТ}
 v=БЕЗЛИЧ_ГЛАГОЛ:*{} : export { node:root_node }
 comma=','
 conj=союз:чтобы{}
 p=Предикат
} : links
{
 v.{
    <SUBJECT>sbj
    <SUBORDINATE_CLAUSE>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p
   }
}


// ??? нужно ли правило?
// мне хотелось бы, чтобы птица начала петь
pattern СложноПредлож
{
 sbj=БезличПодлежащее{ПАДЕЖ:ДАТ}
 v=БЕЗЛИЧ_ГЛАГОЛ:хочется{ время:прошедшее } : export { node:root_node }
 z=ЧАСТИЦА:БЫ{}
 comma=','
 conj=союз:чтобы{}
 p=Предикат
} : links
{
 v.{
    <SUBJECT>sbj
    <POSTFIX_PARTICLE>z
    <SUBORDINATE_CLAUSE>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p
   }
}
*/

// -------------------------------------------------

/* ---ПРОВЕРИТЬ РАЗБОР---
// Ни одного звука не слышу, ни одна травинка не шелохнется
pattern СложноПредлож
{
 v=Сказуемое0{ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 } : export { node:root_node }
 comma=','
 p2=Предикат
} : links { v.<NEXT_CLAUSE>comma.<NEXT_COLLOCATION_ITEM>p2 }
*/

