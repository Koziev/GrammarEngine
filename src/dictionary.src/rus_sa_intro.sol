// ******************************
// Вводные слова и фразы
// ******************************





collocation_set ВводныеСловосочетания_ЧТО = 
{
 "Нет никаких сомнений, что",
 "Можно считать, что",
 "Будем надеяться, что"
}






// Конечно, мы прочитаем эти книги
// ^^^^^^^^
pattern ВводнаяФраза
{
 @probe_left(ЛевыйОграничительОборота)
 w=ВВОДНОЕ:*{} : export { node:root_node }
 comma=','
}
: links { w.<PUNCTUATION>comma }
: ngrams { 2 }


// - А по-моему, это очень нетрудно понять.
//   ^^^^^^^^^^
pattern ВводнаяФраза
{
 @probe_left(ВводнСоюз)
 w=ВВОДНОЕ:*{} : export { node:root_node }
 comma=','
}
: links { w.<PUNCTUATION>comma }
: ngrams { 2 }



// однако ж увидел перед глазами именно эти знаки.
// ^^^^^^^^
pattern ВводнаяФраза
{
 w=ВВОДНОЕ:*{} : export { node:root_node }
 p=@optional(ЧастицаЖе)
}
: links { w.~<POSTFIX_PARTICLE>p }
: ngrams { -1 } // все-таки обычно вводное слово отбивается запятой.


// Ты, кажется, москвич?
//   ^^^^^^^^^^
pattern ВводнаяФраза
{
 comma1=','
 w=ВВОДНОЕ:*{} : export { node:root_node }
 comma2=','
} : links { w.{ <PUNCTUATION>comma1 <PUNCTUATION>comma2 } }


patterns МодальнСловосочет export { node:root_node }

// С позволения сказать, я бы поел.
// ^^^^^^^^^^^^^^^^^^^^^
pattern ВводнаяФраза
{
 z=МодальнСловосочет : export { node:root_node }
 comma2=','
}
: links { z.<PUNCTUATION>comma2 }
: ngrams { -3 }


// О господи, помоги мне!
// ^^^^^^^^^^
pattern ВводнаяФраза
{
 p=частица:о{}
 z=СущСПредложДоп{ ПАДЕЖ:ЗВАТ } : export { node:root_node }
 comma2=','
}
: links { z.{ <PREFIX_PARTICLE>p <PUNCTUATION>comma2 } }
: ngrams { -1 }

// О боги, помоги же ему!
// ^^^^^^^
pattern ВводнаяФраза
{
 p=частица:о{}
 z=СущСПредложДоп{ ПАДЕЖ:ИМ } : export { node:root_node }
 comma2=','
}
: links { z.{ <PREFIX_PARTICLE>p <PUNCTUATION>comma2 } }
: ngrams { -3 }




pattern ВводнаяФраза
{
 ВводныеСловосочетания : export { node:root_node }
} : ngrams { -2 }


// нет сомнений, что ...
pattern ВводнаяФраза
{
 x=ВводныеСловосочетания_ЧТО
 comma=','
 conj=союз:что{} : export { node:root_node }
} : links
{
 conj.{
       <SUBORDINATE_CLAUSE>x
       <PUNCTUATION>comma
      }
}


// Предложный оборот может выступать в роли opener'а:
// По данным надзорного органа, речь идет о мясных пирогах и пирожках
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ВводнаяФраза
{
 pn=ПредлогИСущ : export { node:root_node }
 comma=','
} : links { pn.<PUNCTUATION>comma }
  : ngrams { -3 }



// Кроме того, вряд ли властители доверяли своим "благодетелям".
// ^^^^^^^^^^^
pattern ВводнаяФраза
{
 p=предлог:кроме{} : export { node:root_node }
 n=местоим_сущ:то{ падеж:род }
 comma=','
} : links { p.{ <OBJECT>n <PUNCTUATION>comma } }
  : ngrams { 22 }



// ---------------------------------------------------------

// Частица ДА и НЕТ в роли вводного:
wordentry_set ЧастицаКакВводное=
{
 частица:да{}, частица:нет{}, /*частица:ну{},*/ частица:а{} }


// Да, в недостатке самоуверенности тебя не обвинишь
// ^^^
// Нет, я не понял твоих последних слов...
// ^^^^
pattern ВводнаяФраза
{
 pn=ЧастицаКакВводное : export { node:root_node }
 comma=','
} : links { pn.<PUNCTUATION>comma }


// - О, извини тогда.
//   ^^
pattern ВводнаяФраза
{
 pn=ВводныеЧастицы : export { node:root_node }
 comma=','
} : links { pn.<PUNCTUATION>comma }

// - Да, да, разумеется!
//   ^^^^^^^
pattern ВводнаяФраза
{
 pn=ЧастицаКакВводное : export { node:root_node }
 comma=','
 p2=ЧастицаКакВводное
 comma2=','
} : links
{
 pn.<PUNCTUATION>comma.<NEXT_COLLOCATION_ITEM>p2.<PUNCTUATION>comma2
}


// - Да-да, идем.
//   ^^^^^^
pattern ВводнаяФраза
{
 pn=ЧастицаКакВводное : export { node:root_node }
 t='-'
 p2=ЧастицаКакВводное
 comma=','
} : links
{
 pn.{
     <NEXT_COLLOCATION_ITEM>t.<NEXT_COLLOCATION_ITEM>p2
     <PUNCTUATION>comma
    }
}

// ---------------------------------------------------------


// Да нет, не ерунди.
// ^^^^^^^
pattern ВводнаяФраза
{
 pn=частица:да{} : export { node:root_node }
 p2=частица:нет{}
 comma=','
} : links { pn.<NEXT_COLLOCATION_ITEM>p2.<PUNCTUATION>comma }


// - Нет уж, увольте.
//   ^^^^^^^
pattern ВводнаяФраза
{
 pn=частица:нет{} : export { node:root_node }
 p2=наречие:уж{}
 comma=','
} : links { pn.<NEXT_COLLOCATION_ITEM>p2.<PUNCTUATION>comma }

// - Ну как, нравится?
//   ^^^^^^^
pattern ВводнаяФраза
{
 pn=частица:ну{} : export { node:root_node }
 p2=наречие:как{}
 comma=','
} : links { pn.<NEXT_COLLOCATION_ITEM>p2.<PUNCTUATION>comma }

// - Ну что, пойдем?
//   ^^^^^^^
pattern ВводнаяФраза
{
 pn=частица:ну{} : export { node:root_node }
 p2=наречие:что{}
 comma=','
}
: links { pn.<NEXT_COLLOCATION_ITEM>p2.<PUNCTUATION>comma }
: ngrams { 5 }


// - Ну-ка посмотрим.
//   ^^^^^
pattern ВводнаяФраза
{
 pn=частица:ну{} : export { node:root_node }
 t='-'
 p2=частица:ка{}
} : links { pn.<POSTFIX_PARTICLE>t.<NEXT_COLLOCATION_ITEM>p2 }


// - Что, не узнаешь?
//   ^^^^
pattern ВводнаяФраза
{
 pn=местоим_сущ:что{} : export { node:root_node }
 comma=','
}
: links { pn.<PUNCTUATION>comma }
: ngrams { -5 }

// - Ну и что вы ответили?
//   ^^^^
pattern ВводнаяФраза
{
 pn=частица:ну{} : export { node:root_node }
 conj=СоюзКакВводн
} : links { pn.<NEXT_COLLOCATION_ITEM>conj }


// о моя прекрасная земля!
pattern ВводнаяФраза
{
 pn=частица:о{} : export { node:root_node }
}
: ngrams { -8 }


// - Спасибо, я не курю.
//   ^^^^^^^^
pattern ВводнаяФраза
{
 @probe_left(ЛевыйОграничительОборота)
 pn=частица:спасибо{} : export { node:root_node }
 comma=','
} 
: links { pn.<PUNCTUATION>comma }
: ngrams { 1 }


wordentry_set ДаНет=частица:{ да, нет }

// - Нет уж, поеду.
//   ^^^^^^
pattern ВводнаяФраза
{
 @probe_left(ЛевыйОграничительОборота)
 pn=ДаНет : export { node:root_node }
 p=частица:уж{}
 comma=','
} 
: links { pn.{ <NEXT_COLLOCATION_ITEM>p <PUNCTUATION>comma } }
: ngrams { 1 }


// - Ну да, растерялся!
//   ^^^^^
pattern ВводнаяФраза
{
 @probe_left(ЛевыйОграничительОборота)
 pn=частица:ну{} : export { node:root_node }
 p=ДаНет
 comma=','
} 
: links { pn.{ <NEXT_COLLOCATION_ITEM>p <PUNCTUATION>comma } }

// Ах да, я забыл.
// ^^^^^
pattern ВводнаяФраза
{
 pn=частица:ах{} : export { node:root_node }
 p=ДаНет
 comma=','
} 
: links { pn.{ <NEXT_COLLOCATION_ITEM>p <PUNCTUATION>comma } }


// О да, я помню.
// ^^^^
pattern ВводнаяФраза
{
 pn=частица:о{} : export { node:root_node }
 p=ДаНет
 comma=','
} 
: links { pn.{ <NEXT_COLLOCATION_ITEM>p <PUNCTUATION>comma } }


// - Ишь ты, разошелся.
//   ^^^^^^
pattern ВводнаяФраза
{
 pn=частица:ишь{} : export { node:root_node }
 p='ты'
 comma=','
} 
: links { pn.{ <NEXT_COLLOCATION_ITEM>p <PUNCTUATION>comma } }
: ngrams { 1 }


