// Сборка группы краткого прилагательного:
//
// Теперь она будет свободна, молода, прекрасна.
//                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^

#define _запятая ','

// =============================================

patterns КраткПрил2Восх { bottomup } export { node:root_node РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ }
 

// Гости были довольны
//            ^^^^^^^^
pattern КраткПрил2Восх
{
 КраткПрил1:export{ node:root_node РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ }
}

// Антонио был строг и справедлив
//                   ^^^^^^^^^^^^
// вы живы или мертвы?
//         ^^^^^^^^^^
pattern КраткПрил2Восх
{
 a1=КраткПрил2Восх:export{ node:root_node РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ }
 conj=ЛогичСоюз
 a2=КраткПрил1{ =A1:РОД =A1:ЧИСЛО }
} : links { a1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }


// Антонио был строг, но справедлив
//                  ^^^^^^^^^^^^^^^
pattern КраткПрил2Восх
{
 A1=КраткПрил2Восх:export{ node:root_node РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ }
 comma=_запятая
 conj=ПротивитСоюз
 a2=КраткПрил1{=A1:РОД =A1:ЧИСЛО}
} : links { a1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }

// Антонио был молод, да мудр
//                  ^^^^^^^^^
pattern КраткПрил2Восх
{
 A1=КраткПрил2Восх:export{ node:root_node РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ }
 conj=СоединПрилМнож1
 A2=КраткПрил1{=A1:РОД =A1:ЧИСЛО }
} : links { a1.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2 }


// Она  была  кротка,  послушна
//            ^^^^^^^^^^^^^^^^^
pattern КраткПрил2Восх
{
 A1=КраткПрил2Восх:export{ node:root_node РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ }
 comma=_запятая
 a2=КраткПрил1{=A1:РОД =A1:ЧИСЛО }
} : links { a1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>a2 }

// ---------------------------------------------------------

pattern КраткПрил2
{
 КраткПрил2Восх : export { node:root_node РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ }
}

// он был и быстр, и силён
//               ^^^^^^^^^
// он был либо глуп, либо наивен
pattern КраткПрил2
{
 conj1=ЛогичСоюз2
 a1=КраткПрил2:export{ node:root_node РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ }
 comma=_запятая
 conj2=ЛогичСоюз2
 A2=КраткПрил2{=A1:РОД =A1:ЧИСЛО}
} : links
{
 A1.{
     <PREFIX_CONJUNCTION>conj1
     <RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>conj2.<NEXT_COLLOCATION_ITEM>A2
    }
}
: ngrams { 3 }


// Антонио был хоть и строг, но справедлив
pattern КраткПрил2
{
 conj1=СочинительныйСоюз1
 A1=КраткПрил2Восх:export{ node:root_node РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ }
 comma=_запятая
 conj2=СочинительныйСоюз2
 A2=КраткПрил2Восх{=A1:РОД =A1:ЧИСЛО}
} : links
{
 A1.{
     <PREFIX_CONJUNCTION>conj1.
      <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>conj2.
        <NEXT_COLLOCATION_ITEM>A2
    }
}
: ngrams { 1 }



// ===============================================================


patterns МодалКраткПрил0 export { РОД ЧИСЛО node:root_node }
pattern МодалКраткПрил0
{
 a=прилагательное:*{ КРАТКИЙ МОДАЛЬНЫЙ }:export{ РОД ЧИСЛО node:root_node }
}


// Должна же быть какая-нибудь причина
// ^^^^^^^^^
pattern МодалКраткПрил0
{
 a=прилагательное:*{ КРАТКИЙ МОДАЛЬНЫЙ }:export{ РОД ЧИСЛО node:root_node }
 p=ЧастицаЖе
} : links { a.<POSTFIX_PARTICLE>p }


// Должна ли она вернуться?
// ^^^^^^^^^
pattern МодалКраткПрил0
{
 a=прилагательное:*{ КРАТКИЙ МОДАЛЬНЫЙ }:export{ РОД ЧИСЛО node:root_node }
 p=ЧастицаЛи
} : links { a.<POSTFIX_PARTICLE>p }


pattern МодалКраткПрил0
{
 n=частица:не{}
 a=МодалКраткПрил0:export{ РОД ЧИСЛО node:root_node }
} : links { a.<NEGATION_PARTICLE>n }





// TODO: переделать на КраткПрил1
// способен летать недалеко от земли
pattern КраткПрил2
{
 adj=МодалКраткПрил0:export{ РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ node:root_node }
 inf=Инф2
} : links { adj.<INFINITIVE>inf }


// уже способен летать недалеко от земли
pattern КраткПрил2
{
 adv=наречие:*{ СТЕПЕНЬ:АТРИБ }
 adj=МодалКраткПрил0:export{ РОД ЧИСЛО ПРИЧАСТИЕ СТРАД ПАДЕЖВАЛ ПЕРЕХОДНОСТЬ node:root_node }
 inf=Инф2
} : links
{
 adj.{
      <ATTRIBUTE>adv
      <INFINITIVE>inf
     }
}

// -------------------------------------------

// этот вариант допускает наличие присоединенных к причастию прямых дополнений
patterns КраткПрилРема export { node:root_node РОД ЧИСЛО }

// --------------------------------------------

pattern КраткПрилРема
{
 КраткПрил2 : export { РОД ЧИСЛО node:root_node }
}



// весь мусор становится виден на голой земле.
//                       ^^^^^^^^^^^^^^^^^^^^
pattern КраткПрилРема
{
 a=КраткПрил1 : export { РОД ЧИСЛО node:root_node }
 obj=ПредлогИСущ{ гл_предл( a.root_node, _.prepos, _.n2 ) } 
}
: links { a.<PREPOS_ADJUNCT>obj }
: ngrams
{
 ВалентностьПрил(a)
}


// Треть авиарейсов может быть отменена в аэропортах Парижа из-за снегопада
pattern КраткПрилРема
{
 a=КраткПрил1 : export { РОД ЧИСЛО node:root_node }
 obj=ПредлогИСущ{ гл_предл( a.root_node, _.prepos, _.n2 ) } 
 obj2=ПредлогИСущ{ гл_предл( a.root_node, _.prepos, _.n2 ) } 
} : links
{
 a.{
    <PREPOS_ADJUNCT>obj
    <PREPOS_ADJUNCT>obj2
   }
}
: ngrams
{
 ВалентностьПрил(a)
}

// Они оказались достаточно  умны,  чтобы  вырваться  из  моей темницы
pattern КраткПрилРема
{
 a=КраткПрил1 : export { РОД ЧИСЛО node:root_node }
 adv=Обст
} : links
{
 a.{
    <ATTRIBUTE>adv
   }
}
: ngrams
{
 -1
 adv_adj_score(adv,a)
 ВалентностьПрил(a)
}



// Гостиница расположена глубоко в горах.
pattern КраткПрилРема
{
 a=КраткПрил1 : export { РОД ЧИСЛО node:root_node }
 adv=Обст
 obj=ПредлогИСущ{ гл_предл( a.root_node, _.prepos, _.n2 ) } 
} : links
{
 a.{
    <ATTRIBUTE>adv
    <PREPOS_ADJUNCT>obj
   }
}
: ngrams
{
 adv_adj_score(adv,a)
 ngram3( a, obj.prepos, obj.n2 )
 ВалентностьПрил(a)
}

// результаты будут оглашены на планерке сегодня
//                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern КраткПрилРема
{
 a=КраткПрил1 : export { РОД ЧИСЛО node:root_node }
 obj=ПредлогИСущ{ гл_предл( a.root_node, _.prepos, _.n2 ) } 
 adv=Обст
} : links
{
 a.{
    <PREPOS_ADJUNCT>obj
    <ATTRIBUTE>adv
   }
}
: ngrams
{
 adv_adj_score(adv,a)
 ngram3( a, obj.prepos, obj.n2 )
 ВалентностьПрил(a)
}
