
// Отель не большой
// Ванная не очень большая
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { adj=прилагательное:*{}.n=<SUBJECT>существительное:*{} }
  then adj_noun_score(adj,n)
}



// Это мой карандаш
// Это наше дело
// Это царство жизни!
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { существительное:*{ ПАДЕЖ:ИМ 2 }.<SUBJECT>местоим_сущ:это{ падеж:им 1 } }
  then 10
}


// - А в чем дело? - обиделся исполнитель.
//     ^^^^^^^^^^
// В этом-то и дело.
// ^^^^^^^^^^^^^^^^
tree_scorer ВалентностьНульСвязки language=Russian
{
 if context { существительное:дело{ ПАДЕЖ:ИМ }.<PREPOS_ADJUNCT>предлог:в{}.*:*{ падеж:предл } }
  then 20
}


// Подавим деепричастия для нулевой связки:
// какая у нас скорость?
// ^^^^^
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { существительное:*{ ПАДЕЖ:ИМ }.деепричастие:*{} }
  then -10
}


// Пою я, что ли?
//        ~~~~~~
tree_scorer ВалентностьНульСвязки language=Russian
{
 if context { местоим_сущ:что{ ПАДЕЖ:ИМ }.частица:ли{} }
  then -10
}




// -------------------------------------------------

tree_scorers ОбстНульСвязки

tree_scorer ОбстНульСвязки language=Russian
{
 if context { наречие:*{} }
  then 1
}

tree_scorer ОбстНульСвязки language=Russian
{
 if context { предлог:*{} }
  then 1
}

tree_scorer ОбстНульСвязки language=Russian
{
 if context { деепричастие:*{} }
  then 1
}


// Клянусь вам, это правда.
//              ^^^
tree_scorer ОбстНульСвязки language=Russian
{
 if context { местоим_сущ:*{} }
  then 1
}


// - Здравствуйте, я Евгения.
//                ^^^
tree_scorer ОбстНульСвязки language=Russian
{
 if context { местоимение:*{} }
  then 1
}


// Подавим одиночное существительное в роли именной связки:
//
// - Ты обедал, Роналд?
//              ~~~~~~
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { существительное:*{ ПАДЕЖ:ИМ }.[not]ОбстНульСвязки }
  then -5
}


// Другое дело коммунисты
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { *:*{ ПАДЕЖ:ИМ }.<SUBJECT>существительное:дело{ ПАДЕЖ:ИМ ЧИСЛО:ЕД }.<ATTRIBUTE>'другое' }
  then 12
}

// Жуткое дело смотреть.
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { ПодлежащееДляИндуцМод{ ПАДЕЖ:ИМ }.<OBJECT>инфинитив:*{} }
  then 12
}



// -----------------------------------------------------------

// у тебя впереди серьезное дело
// у меня важные вести
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { существительное:*{ 2 ПАДЕЖ:ИМ }.{ <PREPOS_ADJUNCT>предлог:у{1} <ATTRIBUTE>прилагательное:*{ ПАДЕЖ:ИМ } } }
  then 13
}

// У нас два пути
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { существительное:*{ 2 ПАДЕЖ:РОД }.{ <ATTRIBUTE>ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } <PREPOS_ADJUNCT>предлог:у{1} } }
  then 7
}

// У нас 2 пути
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { существительное:*{ 2 ПАДЕЖ:РОД }.{ <ATTRIBUTE>num_word:*{} <PREPOS_ADJUNCT>предлог:у{1} } }
  then 7
}


// Особый учет для счетных наречий:
// у вас много работы
//       ^^^^^
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { существительное:*{ ПАДЕЖ:РОД }.<ATTRIBUTE>НАРЕЧИЕ:*{ ТИП_МОДИФ:СУЩ } }
  then 7
}

/*
// А мы простой народ
tree_scorer ВалентностьНульСвязки language=Russian generic
{
 if context { существительное:*{ 2 ПАДЕЖ:ИМ }.существительное:*{ 1 ПАДЕЖ:ИМ } }
  then 7
}
*/

// -----------------------------------------------------------

