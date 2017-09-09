// ***********************
// МЕСТОИМЕНИЕ
// ***********************

// Правила для разбора прилагательного с постфиксами:
//
// Она же сама пришла!
// ^^^^^^^^^^^
// ты уж меня извини
// ^^^^^

patterns МестоимСПостфиксом export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }

pattern МестоимСПостфиксом
{
 местоимение:я{} : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}

wordentry_set ПостфиксМестоим=частица:{ же, ж, бы, б, ли, ль, уж }

// вас же опять возьмут под контроль
// ^^^^^^
// мне ли об этом говорить?
// ^^^^^^
// нас бы просто уничтожили
// ^^^^^^
pattern МестоимСПостфиксом
{
 n=местоимение:я{} : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 p=ПостфиксМестоим
} : links { n.<POSTFIX_PARTICLE>p }

// тебя-то
pattern МестоимСПостфиксом
{
 n=местоимение:я{} : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 t='-'
 p=частица:то{}
} : links { n.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>p }
: ngrams { 1 }


pattern МестоимСПостфиксом
{
 n=местоимение:я{} : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 t='-'
 p=частица:ка{}
} : links { n.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>p }
: ngrams { 1 }


// Он-де извинился
// ^^^^^
pattern МестоимСПостфиксом
{
 n=местоимение:я{} : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 t='-'
 p=частица:де{}
} : links { n.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>p }



// -----------------------------------------------------

patterns МестоимСПравПрил export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }

// Я же предупреждал вас
// ^^^^
pattern МестоимСПравПрил
{
 n=МестоимСПостфиксом : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}

// Я вижу его одного!
//        ^^^^^^^^^^
pattern МестоимСПравПрил
{
 n=МестоимСПостфиксом{ число:ед } : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 p=числительное:один{ =n:ПАДЕЖ }
}
: links { n.<ATTRIBUTE>p }


// здесь мы все трое обречены.
//       ^^^^^^^^^^^
pattern МестоимСПравПрил
{
 n=МестоимСПостфиксом{ ПАДЕЖ:ИМ ЧИСЛО:МН }: export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 p=прилагательное:весь{ ПАДЕЖ:ИМ ЧИСЛО:МН }
 q=числительное:*{ ПАДЕЖ:ИМ КАТЕГОРИЯ_ЧИСЛ:СОБИР }
} : links { n.<ATTRIBUTE>q.<ATTRIBUTE>p }
  : ngrams { 2 }



// Специальные прилагательные-кванторы для правого или левого атрибута местоимения:
//
// мы оба кинулись к ней.
//    ^^^
//
// все вы правы
// ^^^^^^
patterns КванторДляМестоимЕд export { node:root_node РОД ПАДЕЖ ЧИСЛО ОДУШ }
patterns КванторДляМестоимМнож export { node:root_node РОД ПАДЕЖ ЧИСЛО ОДУШ }

wordentry_set КванторДляМестоимЕд0=прилагательное:{ весь, сам }

pattern КванторДляМестоимЕд
{
 ГруппаПрил1{ КванторДляМестоимЕд0 ЧИСЛО:ЕД } : export { node:root_node РОД ПАДЕЖ ЧИСЛО ОДУШ }
}

// Я и сам об этом не знал.
//   ^^^^^
pattern КванторДляМестоимЕд
{
 p=частица:и{}
 a=прилагательное:сам{ ЧИСЛО:ЕД } : export { node:root_node РОД ПАДЕЖ ЧИСЛО ОДУШ }
} : links { a.<PREFIX_PARTICLE>p }


wordentry_set КванторДляМестоимМн0_1=прилагательное:{ весь, оба }
wordentry_set КванторДляМестоимМн0_2=прилагательное:{ сам }

pattern КванторДляМестоимМнож
{
 ГруппаПрил1{ КванторДляМестоимМн0_1 ЧИСЛО:МН } : export { node:root_node РОД ПАДЕЖ ЧИСЛО ОДУШ }
} : ngrams { -1 }

// Ну, вы сами понимаете ...
//     ^^^^^^^
pattern КванторДляМестоимМнож
{
 ГруппаПрил1{ КванторДляМестоимМн0_2 ЧИСЛО:МН } : export { node:root_node РОД ПАДЕЖ ЧИСЛО ОДУШ }
}

pattern КванторДляМестоимМнож
{
 p=частица:и{}
 a=прилагательное:сам{ ЧИСЛО:МН } : export { node:root_node РОД ПАДЕЖ ЧИСЛО ОДУШ }
} : links { a.<PREFIX_PARTICLE>p }


// я вся горю
// ^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ лицо:1 число:ед ~ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=КванторДляМестоимЕд{ ~род:ср =P:ПАДЕЖ }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }

// Сам я не справлюсь
// ^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимЕд{ ~род:ср ~ПАДЕЖ:ВИН }
 p=МестоимСПостфиксом{ лицо:1 число:ед =adj:ПАДЕЖ } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }



// ты вся горишь
// ^^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ лицо:2 число:ед ~ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=КванторДляМестоимЕд{ ~род:ср =P:ПАДЕЖ }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }


// Весь ты испачкался
// ^^^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимЕд{ ~род:ср ~ПАДЕЖ:ВИН }
 p=МестоимСПостфиксом{ лицо:2 число:ед =adj:ПАДЕЖ } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }


// она вся горит
// ^^^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ лицо:3 число:ед ~ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=КванторДляМестоимЕд{ =P:род =P:ПАДЕЖ }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }


// Само оно не рассосётся
// ^^^^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимЕд{ ~ПАДЕЖ:ВИН }
 p=МестоимСПостфиксом{ лицо:3 число:ед =adj:род =adj:ПАДЕЖ } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }


// вы все сгорите!
// ^^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ число:мн ~ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=КванторДляМестоимМнож{ =P:ПАДЕЖ ~род:ср }
} : links { p.<ATTRIBUTE>adj }

// Все вы сдохните!
// ^^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимМнож{ ~ПАДЕЖ:ВИН ~род:ср }
 p=МестоимСПостфиксом{ число:мн =adj:ПАДЕЖ } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }


// обе они оказались из серебра.
// ^^^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимМнож{ ~ПАДЕЖ:ВИН ~род:ср }
 p=МестоимСПостфиксом{ число:мн =adj:ПАДЕЖ } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }



// --------------------------------------------------
// отдельно для винительного падежа, чтобы
// правильно связывать: "тебя же весь город знает!"
// --------------------------------------------------

// Они облили меня всего
//            ^^^^^^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ лицо:1 число:ед ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=КванторДляМестоимЕд{ ~род:ср ПАДЕЖ:ВИН ОДУШ:ОДУШ }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }

// Всего меня облили зеленкой.
// ^^^^^^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимЕд{ ~род:ср ПАДЕЖ:ВИН ОДУШ:ОДУШ }
 p=МестоимСПостфиксом{ лицо:1 число:ед ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }


// Я вижу тебя всего
//        ^^^^^^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ лицо:2 число:ед ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=КванторДляМестоимЕд{ ~род:ср ПАДЕЖ:ВИН ОДУШ:ОДУШ }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }

// Я вижу всего тебя насквозь
//        ^^^^^^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимЕд{ ~род:ср ПАДЕЖ:ВИН ОДУШ:ОДУШ }
 p=МестоимСПостфиксом{ лицо:2 число:ед ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }



// Я вижу её всю
//        ^^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ лицо:3 число:ед ПАДЕЖ:ВИН род:жен } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=КванторДляМестоимЕд{ =P:род ПАДЕЖ:ВИН }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }

// Я вижу всю её.
//        ^^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимЕд{ ПАДЕЖ:ВИН РОД:ЖЕН }
 p=МестоимСПостфиксом{ лицо:3 число:ед ПАДЕЖ:ВИН род:жен } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }


// Я вижу его всего
//        ^^^^^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ лицо:3 число:ед ПАДЕЖ:ВИН род:муж } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=КванторДляМестоимЕд{ =P:род ПАДЕЖ:ВИН ОДУШ:ОДУШ }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { 1 }

// Я вижу всего его.
//        ^^^^^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимЕд{ род:муж ПАДЕЖ:ВИН ОДУШ:ОДУШ }
 p=МестоимСПостфиксом{ лицо:3 число:ед ПАДЕЖ:ВИН род:муж } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }



// я вижу вас всех!
//        ^^^^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ число:мн ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=КванторДляМестоимМнож{ ПАДЕЖ:ВИН ОДУШ:ОДУШ }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { -1 }

// Мы всех вас выведем на чистую воду.
//    ^^^^^^^^
pattern МестоимСПравПрил
{
 adj=КванторДляМестоимМнож{ ПАДЕЖ:ВИН ОДУШ:ОДУШ }
 p=МестоимСПостфиксом{ число:мн ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adj }
  : ngrams { -1 }


// можем попытаться отыскать их всех до одного.
//                           ^^^^^^^^^^^^^^^^^
pattern МестоимСПравПрил
{
 p=МестоимСПостфиксом{ число:мн ПАДЕЖ:ВИН } : export{ ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adj=прилагательное:весь{ ЧИСЛО:МН ПАДЕЖ:ВИН ОДУШ:ОДУШ }
 prep=предлог:до{}
 adj2=прилагательное:*{ ПАДЕЖ:РОД ЧИСЛО:ЕД РОД:МУЖ }
} : links { p.<ATTRIBUTE>adj.<PREPOS_ADJUNCT>prep.<OBJECT>adj2 }
  : ngrams { -1 }


// но ему нельзя видеть нас двоих вместе!
//                      ^^^^^^^^^
pattern МестоимСПравПрил
{
 n=МестоимСПостфиксом{ число:мн } : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 p=числительное:*{ =n:ПАДЕЖ }
}
: links { n.<ATTRIBUTE>p }


// Ты, высокий, подойди сюда быстро!
// ^^^^^^^^^^^^
pattern МестоимСПравПрил
{
 n=МестоимСПостфиксом : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 comma1=','
 a=ГруппаПрил2{ =n:ЧИСЛО =n:ПАДЕЖ =n:РОД }
 comma2=@coalesce(',')
} : links
{
 n.<ATTRIBUTE>a.{
                 <PUNCTUATION>comma1
                 ~<PUNCTUATION>comma2
                }
}





// -----------------------------------------------------

// Правила для сборки местоимения с префиксами и постфиксами:
//
// И не вам бы говорить это!
//   ^^^^^^^^^


pattern МестоимСПрефиксом
{
 МестоимСПравПрил : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}

// Ты должен хранить верность не нам.
//                            ^^^^^^
pattern МестоимСПрефиксом
{
 p=частица:не{}
 n=МестоимСПрефиксом : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { n.<NEGATION_PARTICLE>p }


// даже мне это известно
// ^^^^^^^^
pattern МестоимСПрефиксом
{
 p=частица:даже{}
 n=МестоимСПрефиксом : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { n.<PREFIX_PARTICLE>p }
  : ngrams { -2 }

// вот тебя там ждут
// ^^^^^^^^
pattern МестоимСПрефиксом
{
 p=частица:вот{}
 n=МестоимСПрефиксом : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { n.<PREFIX_PARTICLE>p }

// Поймете и вы.
//         ^^^^
pattern МестоимСПрефиксом
{
 p=частица:и{}
 n=МестоимСПрефиксом : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}
: links { n.<PREFIX_PARTICLE>p }
: ngrams { -5 }

// - Ишь ты, заговорил!
//   ^^^^^^
pattern МестоимСПрефиксом
{
 p=частица:*{}
 n=местоимение:*{} : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}
: links { n.<PREFIX_PARTICLE>p }
: ngrams { -6 }



// Она любит одного тебя...
//           ^^^^^^^^^^^
pattern МестоимСПравПрил
{
 p=числительное:один{}
 n=МестоимСПостфиксом{ =p:число =p:падеж } : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}
: links { n.<ATTRIBUTE>p }


// Я хочу всю тебя.
//        ^^^^^^^^
pattern МестоимСПравПрил
{
 p=прилагательное:весь{}
 n=МестоимСПостфиксом{ =p:число =p:падеж } : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}
: links { n.<ATTRIBUTE>p }




// -----------------------------------------------------

patterns МестоимЯдро export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }

// тебя
pattern МестоимЯдро
{
 МестоимСПрефиксом : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}

wordentry_set НаречДляМест=наречие:{ лично, персонально }

// этот результат нужен мне лично
//                      ^^^^^^^^^
pattern МестоимЯдро
{
 p=МестоимСПрефиксом : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 adv=НаречДляМест
} : links { p.<ATTRIBUTE>adv }


// этот результат нужен персонально мне
//                      ^^^^^^^^^^^^^^^
pattern МестоимЯдро
{
 adv=НаречДляМест
 p=МестоимЯдро : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : links { p.<ATTRIBUTE>adv }


// лететь должны именно вы
//               ^^^^^^^^^
pattern МестоимЯдро
{
 mod=УсилитНаречие
 p=МестоимЯдро : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}
: links { p.<ATTRIBUTE>mod }



// -------------------------------------------------

patterns ГруппаМестВосх1 { bottomup } export { KEYFEATURE_REQUIRED KEYFEATURE_DESIRABLE ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }


pattern ГруппаМестВосх1
{
 p=МестоимЯдро : export { KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:0 ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}


// И противник, и мы устаем.
//   ^^^^^^^^^
pattern ГруппаМестВосх1
{
 p=СущСПредложДоп : export { KEYFEATURE_REQUIRED:1 KEYFEATURE_DESIRABLE:0 ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}



// тебя и нас пригласили
// ^^^^^^^^^^
pattern ГруппаМестВосх1
{
 p=ГруппаМестВосх1 : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 conj=ЛогичСоюз : export { KEYFEATURE_DESIRABLE:1 }
 p2=МестоимЯдро{ =P:ПАДЕЖ } : export { KEYFEATURE_REQUIRED:0 }
} : links { p.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }


// Ты, и только ты способен на это.
// ^^^^^^^^^^^^^^^
pattern ГруппаМестВосх1
{
 p=ГруппаМестВосх1 : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 comma=','
 conj=ЛогичСоюз : export { KEYFEATURE_DESIRABLE:1 }
 p2=МестоимЯдро{ =P:ПАДЕЖ } : export { KEYFEATURE_REQUIRED:0 }
} : links { p.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }


// я тебя, дурака, пальцем тронула?
//   ^^^^^^^^^^^^^
pattern ГруппаМестВосх1
{
 p=ГруппаМестВосх1 : export{ KEYFEATURE_REQUIRED KEYFEATURE_DESIRABLE ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 comma1=','
 det=ГруппаСущ4{ =p:ЧИСЛО =p:ПАДЕЖ }
 @noshift(ПравыйОграничительОборота)
 comma2=@coalesce(',')
}
: links
{
 p.{
    <PUNCTUATION>comma1
    <DETAILS>det
    ~<PUNCTUATION>comma2
   }
}
: ngrams { -5 }


// Я и Саша пойдём в кино.
// ^^^^^^^^
pattern ГруппаМестВосх1
{
 p=ГруппаМестВосх1 : export{ KEYFEATURE_REQUIRED ПАДЕЖ ЧИСЛО:МН РОД ЛИЦО node:root_node }
 conj=ЛогичСоюз : export { KEYFEATURE_DESIRABLE:1 }
 n2=ГлДополнение{ =p:ПАДЕЖ }
} : links
{
 p.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2
}

// -------------------------------------------------

patterns ГруппаМестНисх1
export
{
 KEYFEATURE_DETECTED // если обнаружено перечисление или союзный паттерн
 KEYFEATURE_REQUIRED
 KEYFEATURE_DESIRABLE
 ПАДЕЖ ЧИСЛО РОД ЛИЦО
 node:root_node
}


pattern ГруппаМестНисх1
{
 p=ГруппаМестВосх1 : export { KEYFEATURE_DETECTED:0 KEYFEATURE_REQUIRED KEYFEATURE_DESIRABLE ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}


// неуемная натура его осложняет  жизнь  и ему, и мне.
//                                       ^^^^^^^^^^^^
pattern ГруппаМестНисх1
{
 conj1=СочинительныйСоюз1
 p=ГруппаМестНисх1 : export{ KEYFEATURE_REQUIRED KEYFEATURE_DESIRABLE ПАДЕЖ ЧИСЛО:МН РОД ЛИЦО node:root_node }
 comma=','
 conj2=СочинительныйСоюз2 : export { KEYFEATURE_DETECTED:1 }
 n2=ГлДополнение{ =p:ПАДЕЖ }
} : links
{
 p.{
    <PREFIX_CONJUNCTION>conj1
    <RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>conj2.
      <NEXT_COLLOCATION_ITEM>n2
   }
}


// И мы, и противник устаем
pattern ГруппаМестНисх1
{
 conj1=ЛогичСоюз
 p=ГруппаМестНисх1 : export { KEYFEATURE_REQUIRED:0 ПАДЕЖ ЧИСЛО:МН РОД ЛИЦО node:root_node }
 comma=','
 conj2=ЛогичСоюз : export { KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 n2=ГлДополнение{ =p:ПАДЕЖ }
} : links
{
 p.{
    <PREFIX_CONJUNCTION>conj1
    <RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>conj2.
      <NEXT_COLLOCATION_ITEM>n2
   }
}




// - А почему пехота и мы идем куда-то?
//            ^^^^^^^^^^^
pattern ГруппаМестНисх1
{
 n2=СущСПредложДоп : export{ ПАДЕЖ ЧИСЛО:МН node:root_node }
 conj=ЛогичСоюз : export { KEYFEATURE_DETECTED:1 KEYFEATURE_DESIRABLE:1 }
 p=ГруппаМестНисх1{ =n2:ПАДЕЖ } : export{ РОД ЛИЦО KEYFEATURE_REQUIRED }
} : links
{
 n2.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p
}

// Пехота, мы и кавалерия пойдем в обход
// ^^^^^^^^^^^^^^^^^^^^^^
pattern ГруппаМестНисх1
{
 n2=СущСПредложДоп : export{ ПАДЕЖ ЧИСЛО:МН node:root_node }
 comma=',' : export { KEYFEATURE_DETECTED:1 }
 p=ГруппаМестНисх1{ =n2:ПАДЕЖ } : export { РОД ЛИЦО KEYFEATURE_REQUIRED KEYFEATURE_DESIRABLE }
} : links
{
 n2.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>p
}


// -------------------------------------------------

// Одиночное местоимение, без союзного паттерна:
// Толя, мы идем в кино.
//       ^^
pattern ГруппаМест
{
 МестоимЯдро : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}


// Союзная смесь из местоимений и существительных:
// Я и Коля идем в кино.
// ^^^^^^^^
pattern ГруппаМест
{
 ГруппаМестНисх1{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:1 } : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
}


wordentry_set НеГоловаМестГруппы=
{
 местоим_сущ:что{} // Ты что, меня забыла?
}


// В случае, если в конструкцию не вошел союз, то налагаем небольшой штраф:
//
// Толя, мы уходим.
// ~~~~~~~~
pattern ГруппаМест
{
 ГруппаМестНисх1{ KEYFEATURE_DETECTED:1 KEYFEATURE_REQUIRED:0 KEYFEATURE_DESIRABLE:0 ~НеГоловаМестГруппы } : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
} : ngrams { -2 }



// -------------------------------------------------


// ????
// тебя с ней
pattern ГруппаМест
{
 p=МестоимЯдро : export { ПАДЕЖ ЧИСЛО РОД ЛИЦО node:root_node }
 conj=предлог:с{}
 p2=МестоимЯдро{ ПАДЕЖ:ТВОР }
} : links { p.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }


// -------------------------------------------------


// При виде меня она вздрагивает
//          ^^^^
pattern РодОбъектСущ
{
 ГруппаМест{ ПАДЕЖ:РОД } : export { node:root_node }
} : ngrams { -6 }
