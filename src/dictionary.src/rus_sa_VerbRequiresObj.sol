tree_scorers ВинРодОбъект

tree_scorer ВинРодОбъект language=Russian { if context { существительное:*{ падеж:вин } } then 1 }
tree_scorer ВинРодОбъект language=Russian { if context { местоимение:*{ падеж:вин } } then 1 }
tree_scorer ВинРодОбъект language=Russian { if context { местоим_сущ:*{ падеж:вин } } then 1 }
tree_scorer ВинРодОбъект language=Russian { if context { прилагательное:*{ падеж:вин } } then 1 }


// нужно много узнать
tree_scorer ВинРодОбъект language=Russian { if context { наречие:много{} } then 1 }
tree_scorer ВинРодОбъект language=Russian { if context { наречие:немного{} } then 1 }


// упомянул о намерении команды приобрести несколько новых футболистов
//                              ^^^^^^^^^^                 ^^^^^^^^^^^
tree_scorer ВинРодОбъект language=Russian { if context { существительное:*{ падеж:род } } then 1 }
tree_scorer ВинРодОбъект language=Russian { if context { местоимение:*{ падеж:род } } then 1 }
tree_scorer ВинРодОбъект language=Russian { if context { местоим_сущ:*{ падеж:род } } then 1 }
tree_scorer ВинРодОбъект language=Russian { if context { прилагательное:*{ падеж:род } } then 1 }


// Будем считать, что инфинитив заполняет валентность прямого винительного дополнения:
// Состояние подсобных помещений оставляет желать лучшего
tree_scorer ВинРодОбъект language=Russian
{
 if context { инфинитив:*{} }
  then 1
}

#define VerbRequiresObj(v) \
#begin
tree_scorer ВалентностьГлагола language=Russian
{
 if context { rus_verbs:v{}.[not]/*<OBJECT>*/ВинРодОбъект }
  then -1
}
#end

// когда метастатья не объявлена
#define VerbRequiresObj0(v,Aspect=NULL) \
#begin
tree_scorer ВалентностьГлагола language=Russian
{
 #if Aspect==NULL
 if context { глагол:v{}.[not]ВинРодОбъект } then -1
 #else
 if context { глагол:v{ ВИД:Aspect}.[not]<OBJECT>ВинРодОбъект } then -1
 #endif
}

tree_scorer ВалентностьГлагола language=Russian
{
 #if Aspect==NULL
 if context { инфинитив:v{}.[not]<OBJECT>ВинРодОбъект } then -1
 #else
 if context { инфинитив:v{ ВИД:Aspect}.[not]<OBJECT>ВинРодОбъект } then -1
 #endif
}
#end



VerbRequiresObj(покрывать)
VerbRequiresObj(спасти) // спасла их чистая случайность
VerbRequiresObj(назвать) // наверно мне стоит попросить назвать свое имя
VerbRequiresObj(сделать) // Как быстро сделать из таракана киборга
VerbRequiresObj(делать) // делать из таракана киборга
VerbRequiresObj(благословить) // Властелин благословит его сыновьями и дочерьми
VerbRequiresObj(благословлять)
VerbRequiresObj(вырвать)
VerbRequiresObj(вырывать)


// пусть широкая публика увидит их собственными глазами.
//                       ^^^^^^ ^^
VerbRequiresObj(видеть)
VerbRequiresObj(увидеть)

// через несколько миль они заметили впереди хижины.
//                          ^^^^^^^^         ^^^^^^
VerbRequiresObj(заметить)
VerbRequiresObj(замечать)

// Джим поискал глазами своего коня.
//      ^^^^^^^                ^^^^
VerbRequiresObj(поискать)


// он хочет всё узнать поскорее
//          ^^^ ^^^^^^
VerbRequiresObj(узнать)


// здесь они проводили последние минуты.
//           ^^^^^^^^^^^^^^^^^^^^^^^^^^
VerbRequiresObj0(проводить,НЕСОВЕРШ)
VerbRequiresObj0(проводить,СОВЕРШ)





// все силы разом ее оставили.
//                ^^^^^^^^^^^
VerbRequiresObj(оставить)

// Состояние подсобных помещений оставляет желать лучшего
VerbRequiresObj(оставлять)

// ведьма снова пронзила его взглядом.
//              ^^^^^^^^^^^^
VerbRequiresObj(пронзить)
VerbRequiresObj(пронзать)

// у ворот его задержал часовой.
//         ^^^^^^^^^^^^
VerbRequiresObj(задержать)
VerbRequiresObj(задерживать)

// Они бросали в воздух шапки
//     ^^^^^^^          ^^^^^
VerbRequiresObj(бросать)
VerbRequiresObj(бросить)

// Я тебя не просто уважаю, я тобой горжусь.
//   ^^^^           ^^^^^^
VerbRequiresObj(уважать)

// добавить статью в газету
// ^^^^^^^^^^^^^^^
VerbRequiresObj(добавить)
VerbRequiresObj(добавлять)

// он крутился по столу, сбивая на пол тарелки
//                       ^^^^^^        ^^^^^^^
VerbRequiresObj(сбить)
VerbRequiresObj(сбивать)

// Раз закинул старик в море сети.
//     ^^^^^^^               ^^^^
VerbRequiresObj(закинуть)
VerbRequiresObj(закидывать)

// прятать от детей лекарства в аптечке
// ^^^^^^^          ^^^^^^^^^
VerbRequiresObj(прятать)
VerbRequiresObj(спрятать)


// можете попытаться меня обмануть
//                   ^^^^^^^^^^^^^
VerbRequiresObj(обмануть)

VerbRequiresObj(сжимать)
VerbRequiresObj(сжать)
VerbRequiresObj(взять)
VerbRequiresObj(брать)
VerbRequiresObj(приобретать)
VerbRequiresObj(приобрести)
VerbRequiresObj(подталкивать) // Он медленно подталкивал ее локтем
VerbRequiresObj(подтолкнуть)


// меч чувствовал впереди врага.
//     ^^^^^^^^^^         ^^^^^
VerbRequiresObj(чувствовать)
VerbRequiresObj(почувствовать)

