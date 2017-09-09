// -------------------------------------------


patterns ПредлогИСущ_Обст export { node:root_node }

// -----------------------------------------

// вот это была бы удача!
// ^^^^^^^
pattern ЭТО_Местоим
{
 p=частица:вот{}
 n=местоим_сущ:это{падеж:им} : export { node:root_node }
} : links { n.<PREFIX_PARTICLE>p }

// это же такое создание
// ^^^^^^
pattern ЭТО_Местоим
{
 sbj=местоим_сущ:это{ падеж:им } : export { node:root_node }
 p=ЧастицаЖе
} : links { sbj.<POSTFIX_PARTICLE>p }

// это уж такое создание
// ^^^^^^
pattern ЭТО_Местоим
{
 sbj=местоим_сущ:это{ падеж:им } : export { node:root_node }
 p=частица:уж{}
} : links { sbj.<POSTFIX_PARTICLE>p }




// ++++++++++++++++++++++++++++++++++++++++

// кот это хитрое и коварное животное
pattern ПредикатСвязка
{
 sbj=Подлежащее
 v=местоим_сущ:это{ падеж:им } : export { node:root_node }
 r=ГруппаСущ4{ ПАДЕЖ:ИМ }
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r
   }
}


// --------------------------------------------------


wordentry_set МодифДляМного=наречие:{ очень, слишком, чересчур, чрезвычайно, запредельно, чрезмерно }


// --------------------------------------------

/*
// я совершенно с вами согласен.
pattern НеполнСвязка export { node:root_node РОД ЧИСЛО (ЛИЦО) ВРЕМЯ }
{
 adv1=Обст
 pn=ПредлогИСущ
 r=КраткПрилРема : export { node:root_node РОД ЧИСЛО ВРЕМЯ:НАСТОЯЩЕЕ }
 adv2=@optional(Обст)
} : links
{
 r.{
    <ATTRIBUTE>adv1
    <PREPOS_ADJUNCT>pn
    ~<ATTRIBUTE>adv2
   }
}


// это явление иногда видно утром
pattern НеполнСвязка export { node:root_node РОД ЧИСЛО (ЛИЦО) ВРЕМЯ }
{
 adv1=Обст
 r=КраткПрилРема : export { node:root_node РОД ЧИСЛО ВРЕМЯ:НАСТОЯЩЕЕ }
 adv2=@optional(Обст)
} : links
{
 r.{
    <ATTRIBUTE>adv1
    ~<ATTRIBUTE>adv2
   }
}
: ngrams
{
 adv_adj_score( adv1, r )
 adv_adj_score( adv2, r )
}



// связаны ли его руки?
// вам нужна только наша семья!
pattern ПредикатСвязка
{
 r=КраткПрилРема : export { node:root_node }
 adv1=@coalesce(Обст)
 N=Подлежащее{ =r:РОД =r:ЧИСЛО }
 adv2=@optional(Обст)
} : links
{
 r.{
    <SUBJECT>N
    ~<ATTRIBUTE>adv1
    ~<ATTRIBUTE>adv2
   }
}
: ngrams
{
 ВалентностьПрил(r)
 ВалентностьПредиката(r)
}

// сейчас мне нужна твоя кровь до капли
pattern ПредикатСвязка
{
 adv1=@coalesce(Обст)
 r=КраткПрилРема : export { node:root_node }
 adv2=@coalesce(Обст)
 N=Подлежащее{ =r:РОД =r:ЧИСЛО }
 pn=ПредлогИСущ{ гл_предл( r, _.prepos, _.n2 ) }
} : links
{
 r.{
    <SUBJECT>N
    ~<ATTRIBUTE>adv1
    ~<ATTRIBUTE>adv2
    <PREPOS_ADJUNCT>pn
   }
}
: ngrams
{
 ВалентностьПрил(r)
 ВалентностьПредиката(r)
}



// зачем нужен вам этот нож?
pattern ПредикатСвязка
{
 adv=Обст
 r=КраткПрилРема : export { node:root_node }
 N=Подлежащее{ =r:РОД =r:ЧИСЛО }
 adv2=@optional(Обст)
} : links
{
 r.{
    <SUBJECT>N
    <ATTRIBUTE>adv
    ~<ATTRIBUTE>adv2
   }
}
: ngrams
{
 -1
 adv_adj_score( adv, r )
 ВалентностьПрил(r)
 ВалентностьПредиката(r)
}

// для жизни одних существ всегда нужна смерть других
pattern ПредикатСвязка
{
 pn=ПредлогИСущ
 adv=Обст
 r=КраткПрилРема : export { node:root_node }
 N=Подлежащее{ =r:РОД =r:ЧИСЛО }
 adv2=@optional(Обст)
} : links
{
 r.{
    <SUBJECT>N
    <PREPOS_ADJUNCT>pn
    <ATTRIBUTE>adv
    ~<ATTRIBUTE>adv2
   }
}
: ngrams
{
 -1
 adv_adj_score( adv, r )
 ВалентностьПрил(r)
 ВалентностьПредиката(r)
}

// тогда зачем нужна память о нем?
pattern ПредикатСвязка
{
 adv1=Обст
 adv2=Обст
 r=КраткПрилРема : export { node:root_node }
 N=Подлежащее{ =r:РОД =r:ЧИСЛО }
 adv3=@optional(Обст)
} : links
{
 r.{
    <SUBJECT>N
    <ATTRIBUTE>adv1
    <ATTRIBUTE>adv2
    ~<ATTRIBUTE>adv3
   }
}
: ngrams
{
 -2
 adv_adj_score( adv1, r )
 adv_adj_score( adv2, r )
 adv_adj_score( adv3, r )
 ВалентностьПрил(r)
 ВалентностьПредиката(r)
}




// Здесь все национальности равноправны.
pattern ПредикатСвязка
{
 adv1=Обст
 N=Подлежащее
 r=НеполнСвязка{ =N:РОД =N:ЧИСЛО } : export { node:root_node }
} : links
{
 r.{
    <SUBJECT>N
    <ATTRIBUTE>adv1
   }
}
: ngrams
{
 ВалентностьПредиката(r)
}



// к этому они готовы
pattern ПредикатСвязка
{
 adv1=ПредлогИСущ
 N=Подлежащее
 r=НеполнСвязка{ =N:РОД =N:ЧИСЛО } : export { node:root_node }
} : links
{
 r.{
    <SUBJECT>N
    <ATTRIBUTE>adv1
   }
}
: ngrams
{
 ВалентностьПредиката(r)
}


// просто теперь мы должны быть осторожнее
pattern ПредикатСвязка
{
 adv1=Обст
 adv2=Обст
 N=Подлежащее
 r=НеполнСвязка{ =N:РОД =N:ЧИСЛО } : export { node:root_node }
} : links
{
 r.{
    <SUBJECT>N
    <ATTRIBUTE>adv1
    <ATTRIBUTE>adv2
   }
}
: ngrams
{
 -1
 ВалентностьПредиката(r)
}




// где бы поспать?
pattern ПредикатСвязка
{
 a=наречие:где{} : export { node:root_node }
 p=ЧастицаБы
 inf=Инф2
} : links
{
 a.{
    <INFINITIVE>inf
    <POSTFIX_PARTICLE>p
   }
}

// где бы мне поесть?
pattern ПредикатСвязка
{
 a=наречие:где{} : export { node:root_node }
 p=ЧастицаБы
 sbj=БезличПодлежащее{ ПАДЕж:ДАТ }
 inf=Инф2
} : links
{
 a.{
    <SUBJECT>sbj
    <INFINITIVE>inf
    <POSTFIX_PARTICLE>p
   }
}



patterns ГдеЖе export { node:root_node }
pattern ГдеЖе
{
 наречие:где{} : export { node:root_node }
}

pattern ГдеЖе
{
 a=наречие:где{} : export { node:root_node }
 p=ЧастицаЖе
} : links { a.<POSTFIX_PARTICLE>p }



// где мне их смотреть?
// где же теперь ее искать?
pattern ПредикатСвязка
{
 a=ГдеЖе : export { node:root_node }
 adv=@coalesce(Обст)
 sbj=БезличПодлежащее{ ПАДЕж:ДАТ }
 inf=Инф2
} : links
{
 a.{
    <SUBJECT>sbj
    ~<ATTRIBUTE>adv
    <INFINITIVE>inf
   }
}




// Это лекарство бесполезно для него
pattern ПредикатСвязка
{
 N=Подлежащее
 r=КраткПрил2{ =N:РОД =N:ЧИСЛО } : export { node:root_node }
 adv=ПредлогИСущ{ гл_предл( r.root_node, _.prepos, _.n2 ) }
} : links
{
 r.{
    <SUBJECT>N
    <ATTRIBUTE>adv
   }
}






// кот достаточно умен, чтобы поймать мышь
pattern ПредикатСвязка
{
 @mark(Подлежащее,N) : export { node:root_node }
 r=ДостаточнаяСтепень{ КРАТКИЙ =N:РОД =N:ЧИСЛО }
} : links { n.<RHEMA>r }

// кот достаточно умный, чтобы поймать мышь
pattern ПредикатСвязка
{
 @mark(Подлежащее,N) : export { node:root_node }
 r=ДостаточнаяСтепень{ ~КРАТКИЙ =N:РОД =N:ЧИСЛО }
} : links { n.<RHEMA>r }

// собаки сильнее змей
pattern ПредикатСвязка
{
 @mark(Подлежащее,N)
 v=ГруппаСравнПрил : export { node:root_node }
 r=ГруппаСущ4{ ПАДЕЖ:РОД }
} : links
{
 v.{
    <SUBJECT>n
    <RHEMA>r
   }
}

// собаки сильнее, чем змеи
pattern ПредикатСвязка
{
 @mark(Подлежащее,N)
 v=прилагательное:*{ СТЕПЕНЬ:СРАВН } : export { node:root_node }
 comma=','
 conj=союз:чем{}
 r=ГруппаСущ4{ ПАДЕЖ:ИМ }
} : links
{
 v.{
    <SUBJECT>n
    <RHEMA>comma.<NEXT_COLLOCATION_ITEM>conj.<NEXT_COLLOCATION_ITEM>r
   }
}
*/

patterns Это_То_Тема export { ПАДЕЖ РОД node:root_node }

// это же был дракон!
// ^^^^^^
pattern Это_То_Тема
{
 n=местоим_сущ:это{} : export { node:root_node ПАДЕЖ РОД }
 p=ЧастицаЖе
} : links { n.~<POSTFIX_PARTICLE>p }

pattern Это_То_Тема
{
 местоим_сущ:то{} : export { node:root_node ПАДЕЖ РОД }
}

pattern ПредлогИСущ_Обст
{
 ПредлогИСущ : export { node:root_node }
}

pattern ПредлогИСущ_Обст
{
 Обст : export { node:root_node }
}

// это был кенгуру
// это была она
// для молодого человека это была удача
pattern ПредикатСвязка
{
 adv=@optional(ПредлогИСущ_Обст)
 sbj=Это_То_Тема{ падеж:им }
 copula=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 r=Подлежащее{ =Copula:РОД =Copula:ЧИСЛО }
} : links
{
 copula.{
         <SUBJECT>sbj
         <RHEMA>r
         ~<ATTRIBUTE>adv
        }
}
: ngrams
{
 ВалентностьГлагола(copula)
 ВалентностьПредиката(copula)
}


// это была действительно она
pattern ПредикатСвязка
{
 sbj=Это_То_Тема{ падеж:им род:ср }
 copula=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 adv=Обст
 r=Подлежащее{ =Copula:РОД =Copula:ЧИСЛО }
} : links
{
 copula.{
         <SUBJECT>sbj
         <RHEMA>r
         <ATTRIBUTE>adv
        }
}
: ngrams
{
 ВалентностьГлагола(copula)
 ВалентностьПредиката(copula)
}



// это была битва по правилам дикарей
pattern ПредикатСвязка
{
 sbj=Это_То_Тема{ падеж:им род:ср }
 copula=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 r=Подлежащее{ =Copula:РОД =Copula:ЧИСЛО }
 pn=ПредлогИСущ
} : links
{
 copula.{
         <SUBJECT>sbj
         <RHEMA>r.<PREPOS_ADJUNCT>pn
        }
}
: ngrams
{
 ВалентностьГлагола(copula)
 ВалентностьПредиката(copula)
}



// неужели то была она?
// неужто это был ты?
pattern ПредикатСвязка
{
 adv=Обст
 sbj=Это_То_Тема{ падеж:им род:ср }
 copula=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 r=Подлежащее{ =Copula:РОД =Copula:ЧИСЛО }
} : links
{
 copula.{
         <SUBJECT>sbj
         <RHEMA>r
         <ATTRIBUTE>adv
        }
}
: ngrams
{
 ВалентностьГлагола(copula)
 ВалентностьПредиката(copula)
}


// это - кенгуру
// это - я
pattern ПредикатСвязка
{
 sbj=местоим_сущ:это{ падеж:им род:ср }
 v=ДефисКакСвязка : export { node:root_node }
 r=Подлежащее
}:links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r
   }
}


// это будет кенгуру
pattern ПредикатСвязка
{
 sbj=Это_То_Тема{ падеж:им }
 copula=Связка{ ВРЕМЯ:БУДУЩЕЕ } : export { node:root_node }
 r=ГруппаСущ4{ ПАДЕЖ:ИМ =Copula:ЧИСЛО }
} : links
{
 copula.{
         <SUBJECT>sbj
         <RHEMA>r
        }
}
: ngrams
{
 ВалентностьГлагола(copula)
 ВалентностьПредиката(copula)
}



// Это же не море...
pattern ПредикатСвязка
{
 sbj=Это_То_Тема{ падеж:им }
 r=Подлежащее : export { node:root_node }
}
: links { r.<SUBJECT>sbj }
: ngrams { -1 }




// Что это за  химический комбинат, который указан в вашем списке?
// ^^^^^^^^^^....
pattern ПредикатСвязка
{
 w1=местоим_сущ:что{ падеж:им }
 sbj=ЭТО_Местоим : export { node:root_node }
 w3=частица:за{}
 rhema=ГруппаСущ4{ ПАДЕЖ:ВИН }
} : links
{
 sbj.{
      <NEXT_COLLOCATION_ITEM>w1
      <NEXT_COLLOCATION_ITEM>w3
      <RHEMA>rhema
     }
}
: ngrams { 11 }

// Что это за зверь?
pattern ПредикатСвязка
{
 w1=местоим_сущ:что{ падеж:им }
 sbj=ЭТО_Местоим : export { node:root_node }
 w3=частица:за{}
 rhema=ГруппаСущ4{ ПАДЕЖ:ИМ }
} : links
{
 sbj.{
      <NEXT_COLLOCATION_ITEM>w1
      <PREFIX_PARTICLE>w3
      <RHEMA>rhema
     }
}
: ngrams { 12 }





// Было бы корыто, а свиньи будут.
// ^^^^^^^^^^^^^^
pattern ПредикатСвязка
{
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 r=ГруппаСущ4{ ПАДЕЖ:ИМ =V:РОД =V:ЧИСЛО}
} : links { v.<RHEMA>r }




// одиночная связка как ответ на вопрос:
// Ты там был? Был.
pattern ПредикатСвязка
{
 Связка : export { node:root_node }
} : ngrams { -2 }


// Чтение - вот лучшее учение!
pattern ПредикатСвязка
{
 sbj=ГруппаСущ4{ падеж:им }
 v=ДефисКакСвязка : export { node:root_node }
 v2='вот'
 r=ГруппаСущ4{ падеж:им }
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>r.<ATTRIBUTE>v2
   }
}

// Инфинитив в качестве ремы
// Задача фольклорного ансамбля - добыть, сохранить, собрать воедино россыпи народного искусства
pattern ПредикатСвязка
{
 sbj=ГруппаСущ4{ падеж:им }
 v=ДефисКакСвязка : export { node:root_node }
 p=@optional( 'это'{ class:местоим_сущ ПАДЕЖ:ИМ } )
 inf=Инф2
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>inf
    ~<NEXT_COLLOCATION_ITEM>p
   }
}

// ------------------------------------------------------------------

// Для удобства разбора сделаем правило для связывания предлогов В и НА с
// существительным в предложном падеже.
wordentry_set Предлог_В_НА=предлог:{
                                    в, // в кармане
                                    на, // на счету
                                    при // У Коли при себе было пять банок тушенки
                                   }
patterns В_НА_Предл export { node:root_node }
pattern В_НА_Предл
{
 prep=Предлог_В_НА : export { node:root_node }
 obj=ГлДополнение{ падеж:предл }
} : links { prep.<OBJECT>obj }


// Предложные паттерны, в которых именная часть НЕ стоит в предложном падеже
patterns ПредлогСущ_НЕ_ПРЕДЛ export { node:root_node }
pattern ПредлогСущ_НЕ_ПРЕДЛ
{
 prep=предлог:*{} : export { node:root_node }
 obj=ГлДополнение{ =prep:падеж ~падеж:предл }
} : links { prep.<OBJECT>obj }

// ------------------------------------------------------


// ***************************************************
// Наречие в предикативной роли (отсутствие БЫЛО/ЕСТЬ)
// ***************************************************


// предложное обстоятельство В+предл.падеж:
// мне тесно в этой дыре
// мне удобно на стуле
pattern ПредикатСвязка
{
 sbj=ГлДополнение{ падеж:дат }
 v=ГруппаНареч1 : export { node:root_node }
 p=В_НА_Предл
} : links
{
 v.{
    <SUBJECT>sbj
    <PREPOS_ADJUNCT>p
   }
}


// Вариант предложного обстоятельства с локативом:
// Тебе страшно в лесу?
pattern ПредикатСвязка
{
 sbj=ГлДополнение{ падеж:дат }
 v=ГруппаНареч1 : export { node:root_node }
 p=предлог:в{}
 obj=ГлДополнение{ падеж:мест }
} : links
{
 v.{
    <SUBJECT>sbj
    <PREPOS_ADJUNCT>p.<OBJECT>obj
   }
}


// Прочие предлоги:
// мне тоскливо от такой погоды
// мне стыдно за свои слова
pattern ПредикатСвязка
{
 sbj=ГлДополнение{ падеж:дат }
 v=ГруппаНареч1 : export { node:root_node }
 p=предлог:*{ ~Предлог_В_НА }
 obj=ГлДополнение{ =p:падеж }
} : links
{
 v.{
    <SUBJECT>sbj
    <PREPOS_ADJUNCT>p.<OBJECT>obj
   }
}



wordentry_set СчетнНаречРОД=наречие:{ много, немало, немного, маловато, многовато, мало }

// предл_сущ + счетное_наречие + род_п:
// В его статье много воды.
// В этой книге слишком мало конкретики
pattern ПредикатСвязка
{
 p=Предлог_В_НА
 obj=ГлДополнение{ падеж:предл }
 v=ГруппаНареч1{ СчетнНаречРОД } : export { node:root_node }
 sbj=ГлДополнение{ падеж:род }
} : links
{
 v.{
    <SUBJECT>sbj
    <PREPOS_ADJUNCT>p.<OBJECT>obj
   }
}


/*
// предл_сущ + наречие + инф:
// С ним трудно сговориться.
pattern ПредикатСвязка
{
 adv=@optional(Обст)
 p=предлог:*{}
 obj=ГлДополнение{ =p:падеж }
 v=ГруппаНареч1 : export { node:root_node }
 inf=инфинитив:*{ гл_предл( _, p, obj.root_node ) }
} : links
{
 v.{
    ~<ATTRIBUTE>adv
    <PREPOS_ADJUNCT>p.<OBJECT>obj
    <INFINITIVE>inf
   }
}
*/


wordentry_set КраткНеМожетБытьСказ={ прилагательное:нужный{}, прилагательное:необходимый{},
прилагательное:положенный{}, прилагательное:положеный{} }

// дат_п + кратк_прил + инф:
// Вам легко говорить это!
pattern ПредикатСвязка
{
 obj=ГлДополнение{ падеж:дат }
 v=КраткПрил2{ род:ср число:ед ~КраткНеМожетБытьСказ } : export { node:root_node }
 inf=Инф
} : links
{
 v.{
    <SUBJECT>obj
    <INFINITIVE>inf
   }
}




// **********************************
// инверсный порядок слов для связки
// **********************************

patterns СвязкаКрПрил export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }

// в лесу найден НЛО
pattern СвязкаКрПрил export { РОД ЧИСЛО (ЛИЦО) ВРЕМЯ node:root_node }
{
 прилагательное:*{ КРАТКИЙ СТРАД }:export{ РОД ЧИСЛО ВРЕМЯ:НАСТОЯЩЕЕ node:root_node }
}

// в лесу был найден НЛО
pattern СвязкаКрПрил export { РОД ЧИСЛО (ЛИЦО) ВРЕМЯ node:root_node }
{
 v=глагол:быть{ время:прошедшее }:export{ РОД ЧИСЛО ВРЕМЯ }
 a=прилагательное:*{ КРАТКИЙ СТРАД =V:РОД =V:ЧИСЛО }:export{ node:root_node }
} : links { a.<LEFT_AUX_VERB>v }

// на площади будет установлен монумент воинам, погибшим в вообруженных конфликтах
pattern СвязкаКрПрил export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
{
 v=глагол:быть{ время:будущее }:export{ ЛИЦО РОД ЧИСЛО ВРЕМЯ }
 a=прилагательное:*{ КРАТКИЙ СТРАД =V:РОД =V:ЧИСЛО }:export{ node:root_node }
} : links { a.<LEFT_AUX_VERB>v }


pattern ПредикатСвязка
{
 adv1=Обст
 v=СвязкаКрПрил{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =V:род =V:ЧИСЛО }
 adv2=@optional(ПредлогИСущ)
} : links
{
 v.{
    <RHEMA>r
    <ATTRIBUTE>adv1
    ~<ATTRIBUTE>adv2
   }
}


// На обложке была размещена биография
pattern ПредикатСвязка
{
 adv1=ПредлогИСущ
 v=СвязкаКрПрил{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =V:род =V:ЧИСЛО }
} : links
{
 v.{
    <RHEMA>r
    <ATTRIBUTE>adv1
   }
}




pattern ПредикатСвязка
{
 adv1=Обст
 v=СвязкаКрПрил{ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 } : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =V:род =V:ЧИСЛО }
 adv2=@optional(ПредлогИСущ)
} : links
{
 v.{
    <RHEMA>r
    <ATTRIBUTE>adv1
    ~<ATTRIBUTE>adv2
   }
}


// Здесь уничтожена культурная пропасть между городом и деревней.
pattern ПредикатСвязка
{
 adv1=Обст
 v=СвязкаКрПрил{ ВРЕМЯ:НАСТОЯЩЕЕ } : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =V:род =V:ЧИСЛО }
 adv2=@optional(ПредлогИСущ)
} : links
{
 v.{
    <ATTRIBUTE>adv1
    <RHEMA>r
    ~<ATTRIBUTE>adv2
   }
}


// В нашей стране уничтожена культурная пропасть между городом и деревней.
pattern ПредикатСвязка
{
 adv1=ПредлогИСущ
 v=СвязкаКрПрил{ ВРЕМЯ:НАСТОЯЩЕЕ гл_предл( _.root_node, adv1.prepos, adv1.n2 ) } : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =V:род =V:ЧИСЛО }
} : links
{
 v.{
    <ATTRIBUTE>adv1
    <RHEMA>r
   }
}

// По всей линии уже положены шпалы и рельсы
pattern ПредикатСвязка
{
 adv1=ПредлогИСущ
 adv2=Обст
 v=СвязкаКрПрил{ ВРЕМЯ:НАСТОЯЩЕЕ гл_предл( _.root_node, adv1.prepos, adv1.n2 ) } : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =V:род =V:ЧИСЛО }
} : links
{
 v.{
    <ATTRIBUTE>adv1
    <ATTRIBUTE>adv2
    <RHEMA>r
   }
}





patterns КраткПрилДляСвязки export { РОД ЧИСЛО node:root_node }
pattern КраткПрилДляСвязки
{
 прилагательное:*{ краткий ~ПРИЧАСТИЕ } : export { РОД ЧИСЛО node:root_node }
}

// вот каков твой истинный план!
// ^^^^^^^^^
pattern КраткПрилДляСвязки
{
 p=частица:вот{}
 a=прилагательное:*{краткий  ~ПРИЧАСТИЕ} : export { РОД ЧИСЛО node:root_node }
} : links { a.<PREFIX_PARTICLE>p }


// каков же твой следующий шаг?
// ^^^^^^^^
pattern КраткПрилДляСвязки
{
 a=прилагательное:*{краткий ~ПРИЧАСТИЕ} : export { РОД ЧИСЛО node:root_node }
 p=частица:же{}
} : links { a.<POSTFIX_PARTICLE>p }

// таков уж закон природы.
// ^^^^^^^^
pattern КраткПрилДляСвязки
{
 a=прилагательное:*{краткий ~ПРИЧАСТИЕ} : export { РОД ЧИСЛО node:root_node }
 p=частица:уж{}
} : links { a.<POSTFIX_PARTICLE>p }


// Еще нулевая связка, инверсный порядок слов.
// закрыто движение транспорта
pattern ПредикатСвязка
{
 a=КраткПрилДляСвязки : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =A:род =A:ЧИСЛО }
 adv=@optional(ПредлогИСущ)
} : links
{
 a.{
    <RHEMA>r
    ~<ATTRIBUTE>adv
   }
}
: ngrams
{
 ВалентностьПрил(a)
 ВалентностьПредиката(a)
}



wordentry_set ЗапретПрилСвязка=наречие:{ уж }

// плохо тогда мое дело.
pattern ПредикатСвязка
{
 a=КраткПрилДляСвязки : export { node:root_node }
 adv1=наречие:*{ ~ЗапретПрилСвязка } // ??? наречия времени ???
 r=ГруппаСущ4{ падеж:им =A:род =A:ЧИСЛО }
 adv=@optional(ПредлогИСущ)
} : links
{
 a.{
    <RHEMA>r
    <ATTRIBUTE>adv1
    ~<ATTRIBUTE>adv
   }
}
: ngrams
{
 ВалентностьПрил(a)
 ВалентностьПредиката(a)
}


// таков уж у гномов характер.
pattern ПредикатСвязка
{
 a=КраткПрилДляСвязки : export { node:root_node }
 adv=ПредлогИСущ
 r=ГруппаСущ4{ падеж:им =A:род =A:ЧИСЛО }
} : links
{
 a.{
    <RHEMA>r
    <ATTRIBUTE>adv
   }
}
: ngrams
{
 ВалентностьПрил(a)
 ВалентностьПредиката(a)
}




// в четверг возможны дожди, град и грозы
pattern ПредикатСвязка
{
 adv1=Обст
 a=КраткПрилДляСвязки : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =A:род =A:ЧИСЛО }
 adv2=@optional(ПредлогИСущ)
} : links
{
 a.{
    <ATTRIBUTE>adv1
    <RHEMA>r
    ~<PREPOS_ADJUNCT>adv2
   }
}
: ngrams
{
 ВалентностьПрил(a)
 ВалентностьПредиката(a)
}


// теперь ясно виден огонь
pattern ПредикатСвязка
{
 adv0=Обст
 adv1=Обст
 a=КраткПрилДляСвязки : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =A:род =A:ЧИСЛО }
 adv2=@optional(ПредлогИСущ)
} : links
{
 a.{
    <ATTRIBUTE>adv0
    <ATTRIBUTE>adv1
    <RHEMA>r
    ~<PREPOS_ADJUNCT>adv2
   }
}
: ngrams
{
 -1
 ВалентностьПрил(a)
 ВалентностьПредиката(a)
}



// На всякое дело нужна привычка
pattern ПредикатСвязка
{
 adv1=ПредлогИСущ
 a=КраткПрилДляСвязки : export { node:root_node }
 r=ГруппаСущ4{ падеж:им =A:род =A:ЧИСЛО }
} : links
{
 a.{
    <PREPOS_ADJUNCT>adv1
    <RHEMA>r
   }
}
: ngrams
{
 ВалентностьПрил(a)
 ВалентностьПредиката(a)
}


patterns ПодлежащИнв export { РОД ЧИСЛО node:root_node }

// единственным звуком был топот копыт их коней.
//                         ^^^^^^^^^^^^^^^^^^^^
pattern ПодлежащИнв
{
 ГруппаСущ4{ ПАДЕЖ:ИМ }:export{ РОД ЧИСЛО node:root_node }
}

pattern ПодлежащИнв export { (РОД) ЧИСЛО node:root_node }
{
 n1=ГруппаСущ1{ ПАДЕЖ:ИМ }:export{ ЧИСЛО:МН node:root_node }
 conj=союз:и{}
 n2=ГруппаСущ1{ ПАДЕЖ:ИМ }
} : links { n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2 }



// Единственным президентом СССР был Михаил Сергеевич Горбачов
// очень приятным сюрпризом была новая добыча
// там источником страха была опасность
pattern ПредикатСвязка
{
 adv0=@coalesce(Обст)
 r=ГруппаСущ4{ПАДЕЖ:ТВОР}
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 sbj=ПодлежащИнв{=V:РОД =V:ЧИСЛО}
} : links
{
 v.{
    ~<ATTRIBUTE>adv0
    <SUBJECT>sbj
    <RHEMA>r
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьПредиката(v)
}


// моей целью были только горы
pattern ПредикатСвязка
{
 adv0=@coalesce(Обст)
 r=ГруппаСущ4{ПАДЕЖ:ТВОР}
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 adv=Обст
 sbj=ПодлежащИнв{=V:РОД =V:ЧИСЛО}
} : links
{
 v.{
    ~<ATTRIBUTE>adv0
    <SUBJECT>sbj
    <RHEMA>r
    <ATTRIBUTE>adv
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьПредиката(v)
}

// для них живой реальностью было человечество
pattern ПредикатСвязка
{
 adv0=@optional(Обст)
 pn=ПредлогИСущ
 r=ГруппаСущ4{ПАДЕЖ:ТВОР}
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node }
 sbj=ПодлежащИнв{=V:РОД =V:ЧИСЛО}
} : links
{
 v.{
    ~<ATTRIBUTE>adv0
    <SUBJECT>sbj
    <RHEMA>r
    <PREPOS_ADJUNCT>pn
   }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьПредиката(v)
}


// #####################
// БЕЗЛИЧНЫЕ ГЛАГОЛЫ
// #####################


// сравнительное прилагательное в роли предикатива с присоединенным инфинитивом:
// тебе проще сказать правду
//      ^^^^^
pattern ГлПредикат
{
 sbj=ГлДополнение{ ПАДЕЖ:ДАТ }
 v=ГруппаСравнПрил : export { node:root_node }
 inf=Инф2
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}









// Предикатив НИ ПРИ ЧЁМ:
// чары здесь ни при чем
pattern ГлПредикат
{
 sbj=Подлежащее
 adv=Обст
 v=безлич_глагол:ни при чем{} : export { node:root_node }
} : links
{
 v.{
    <SUBJECT>sbj
    <ATTRIBUTE>adv
   }
}

// только деньги здесь ни при чем
pattern ГлПредикат
{
 adv1=ГруппаНареч1
 sbj=Подлежащее
 adv=Обст
 v=безлич_глагол:ни при чем{} : export { node:root_node }
} : links
{
 v.{
    <ATTRIBUTE>adv1
    <SUBJECT>sbj
    <ATTRIBUTE>adv
   }
}


// мне есть о чем писать
pattern ГлПредикат
{
 sbj=БезличПодлежащее{ПАДЕЖ:ДАТ}
 v='есть'{ class:глагол } : export { node:root_node }
 inf=Инф2
} : links
{
 v.{
    <SUBJECT>sbj
    <INFINITIVE>inf
   }
}



// тут есть о чем подумать!
pattern ГлПредикат
{
 adv=Обст
 v='есть'{ class:глагол } : export { node:root_node }
 inf=Инф2
} : links
{
 v.{
    <ATTRIBUTE>adv
    <INFINITIVE>inf
   }
}

// здесь еще есть над чем поработать
pattern ГлПредикат
{
 adv=Обст
 adv2=Обст
 v='есть'{ class:глагол } : export { node:root_node }
 inf=Инф2
} : links
{
 v.{
    <ATTRIBUTE>adv
    <ATTRIBUTE>adv2
    <INFINITIVE>inf
   }
}
: ngrams { -1 }



// у нас есть о чем послушать
pattern ГлПредикат
{
 adv=ПредлогИСущ
 v='есть'{ class:глагол } : export { node:root_node }
 inf=Инф2
} : links
{
 v.{
    <ATTRIBUTE>adv
    <INFINITIVE>inf
   }
}
: ngrams { -1 }


// есть о чем говорить!
pattern ГлПредикат
{
 v='есть'{ class:глагол } : export { node:root_node }
 inf=Инф2
} : links { v.<INFINITIVE>inf }
: ngrams { -1 }



// дети тут совершенно ни при чем
pattern ГлПредикат
{
 sbj=Подлежащее
 adv=Обст
 adv2=Обст
 v=безлич_глагол:ни при чем{} : export { node:root_node }
} : links
{
 v.{
    <SUBJECT>sbj
    <ATTRIBUTE>adv
    <ATTRIBUTE>adv2
   }
}








wordentry_set НаречияТипаНемалоДляБезлич = { наречие:немало{}, наречие:много{} }

// немало горьких слез было пролито вчера
pattern ГлПредикат
{
 adv1=НаречияТипаНемалоДляБезлич
 obj=СущСПредложДоп{ ПАДЕЖ:РОД }
 v='было' : export { node:root_node }
 a=прилагательное:*{ КРАТКИЙ СТРАД ПРИЧАСТИЕ РОД:СР }
 adv2=@optional(Обст)
 adv3=@optional(ГруппаНареч2)
} : links
{
 v.{
    <OBJECT>obj.<ATTRIBUTE>adv1 
    <RIGHT_AUX2PARTICIPLE>a.{
                             ~<ATTRIBUTE>adv2
                             ~<ATTRIBUTE>adv3
                            }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}


// немало горьких слез пролито сегодня
pattern ГлПредикат
{
 adv1=НаречияТипаНемалоДляБезлич
 obj=СущСПредложДоп{ ПАДЕЖ:РОД }
 a=прилагательное:*{ КРАТКИЙ СТРАД ПРИЧАСТИЕ РОД:СР } : export { node:root_node }
 adv2=@optional(Обст)
 adv3=@optional(ГруппаНареч2)
} : links
{
 a.{
    <OBJECT>obj.<ATTRIBUTE>adv1 
    ~<ATTRIBUTE>adv2
    ~<ATTRIBUTE>adv3
   }
}


// немало горьких слез будет пролито завтра
pattern ГлПредикат
{
 adv1=НаречияТипаНемалоДляБезлич
 obj=СущСПредложДоп{ ПАДЕЖ:РОД }
 v='будет' : export { node:root_node }
 a=прилагательное:*{ КРАТКИЙ СТРАД ПРИЧАСТИЕ РОД:СР }
 adv2=@optional(Обст)
 adv3=@optional(ГруппаНареч2)
} : links
{
 v.{
    <OBJECT>obj.<ATTRIBUTE>adv1 
    <RIGHT_AUX2PARTICIPLE>a.{
                             ~<ATTRIBUTE>adv2
                             ~<ATTRIBUTE>adv3
                            }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}




// *********************************
// Паттерн с уточнением слова ВСЁ
// *********************************

// А сейчас всё потускнело: и цветы, и травы
pattern ГлПредикат
{
 adv=@optional(Обст)
 sbj=местоим_сущ:все{падеж:им}
 v=ГлНаст{ ВРЕМЯ:ПРОШЕДШЕЕ РОД:СР ЧИСЛО:ЕД } : export { node:root_node }
 colon=':'
 nx=ПеречислСущИм
} : links
{
 v.{
    <SUBJECT>sbj.<DETAILS>colon.<RIGHT_NOUN>nx
    <ATTRIBUTE>adv
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}




// Сквозь листву деревьев видно было, как за рекой садилось солнце
pattern ГлПредикат
{
 adv=Обст
 a=прилагательное:*{ краткий род:ср }
 v=глагол:быть{ род:ср время:прошедшее } : export { node:root_node }
 comma=','
 conj=союз:как{}
 p=Предикат
} : links
{
 v.{
    <ATTRIBUTE>adv
    <RIGHT_AUX2ADJ>a.
     <SUBORDINATE_CLAUSE>comma.
      <NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>p
   }
}

// Сквозь листву деревьев было видно, как за рекой садилось солнце
pattern ГлПредикат
{
 adv=Обст
 v=глагол:быть{ род:ср время:прошедшее } : export { node:root_node }
 a=прилагательное:*{ краткий род:ср }
 comma=','
 conj=союз:как{}
 p=Предикат
} : links
{
 v.{
    <ATTRIBUTE>adv
    <RIGHT_AUX2ADJ>a.
     <SUBORDINATE_CLAUSE>comma.
      <NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>p
   }
}



// **************************
// АРИФМЕТИКА
// **************************

patterns АрифмТерм export { node:root_node }
pattern АрифмТерм { числительное:*{ падеж:им /*род:муж*/ } : export { node:root_node } }
pattern АрифмТерм { num_word:*{} : export { node:root_node } }

patterns ПлюсМинус export { node:root_node }
pattern ПлюсМинус { существительное:плюс{ падеж:им } : export { node:root_node } }
pattern ПлюсМинус { существительное:минус{ падеж:им } : export { node:root_node } }
pattern ПлюсМинус { союз:да{} : export { node:root_node } }

patterns АрифмРавно export { node:root_node }
pattern АрифмРавно { прилагательное:равный{ краткий род:ср } : export { node:root_node } }
pattern АрифмРавно { местоим_сущ:это{ падеж:им } : export { node:root_node } }
pattern АрифмРавно { глагол:быть{ время:будущее лицо:3 число:ед } : export { node:root_node } }

patterns АрифмЛевЧасть export { node:root_node }

// три плюс два
pattern АрифмЛевЧасть
{
 t1=АрифмТерм
 a=ПлюсМинус : export { node:root_node }
 t2=АрифмТерм
} : links
{
 a.{
    <TERM>t1
    <TERM>t2
   }
}

patterns АрифмУмножПоделить export { node:root_node }

pattern АрифмУмножПоделить { инфинитив:умножить{} : export { node:root_node } }
pattern АрифмУмножПоделить { инфинитив:помножить{} : export { node:root_node } }
pattern АрифмУмножПоделить { инфинитив:делить{} : export { node:root_node } }
pattern АрифмУмножПоделить { инфинитив:разделить{} : export { node:root_node } }
pattern АрифмУмножПоделить { инфинитив:поделить{} : export { node:root_node } }

// три помножить на три
pattern АрифмЛевЧасть
{
 t1=АрифмТерм
 a=АрифмУмножПоделить : export { node:root_node }
 prep=предлог:на{}
 t2=АрифмТерм
} : links
{
 a.{
    <TERM>t1
    <TERM>prep.<OBJECT>t2
   }
}

wordentry_set ФакторАрифм = 
{
 наречие:дважды{},
 наречие:трижды{},
 наречие:четырежды{},
 наречие:пятью{},
 наречие:шестью{},
 наречие:семью{},
 наречие:восемью{},
 наречие:девятью{},
 наречие:десятью{} // ...
}


// трижды пять будет пятнадцать
pattern АрифмЛевЧасть
{
 f=ФакторАрифм
 t=АрифмТерм : export { node:root_node }
} : links { t.<ATTRIBUTE>f }

patterns АрифмВыражение export { node:root_node }

// три плюс два равно пять
pattern АрифмВыражение
{
 t1=АрифмЛевЧасть
 a=АрифмРавно : export { node:root_node }
 t2=АрифмТерм
} : links
{
 a.{
    <TERM>t1
    <TERM>t2
   }
}


patterns РавноАрифм export { node:root_node }

pattern РавноАрифм { прилагательное:равный{ краткий род:ср } : export { node:root_node } }
pattern РавноАрифм { глагол:равняться { время:настоящее число:ед лицо:3 } : export { node:root_node } }
pattern РавноАрифм { местоим_сущ:это {} : export { node:root_node } }

// Чему равно три умножить на два
pattern АрифмВыражение
{
 t1='чему'
 a=РавноАрифм : export { node:root_node }
 t2=АрифмЛевЧасть
} : links
{
 a.{
    <TERM>t1
    <TERM>t2
   }
}

pattern ГлПредикат { АрифмВыражение : export { node:root_node } }

// Сколько будет шесть делить на три
pattern ГлПредикат
{
 q='сколько'
 v='будет' : export { node:root_node }
 t=АрифмЛевЧасть
} : links
{
 v.{
    <TERM>q
    <TERM>t
   }
}


// -------------------------------------------

// безличные с придаточным:
// мне завидно, что ты это знаешь
pattern ГлПредикат
{
 sbj=ГлДополнение{ ПАДЕЖ:ДАТ }
 v=ГруппаНареч2 : export { node:root_node }
 comma=','
 conj=союз:что{}
 p=ПридаточноеВОбороте
} : links
{
 v.{
    <SUBJECT>sbj
    <SUBORDINATE_CLAUSE>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p
   }
}

// Экипаж, спустить шлюпки на воду!
pattern ГлПредикат
{
 n=существительное:*{падеж:им}
 comma=','
 inf=Инф2 : export { node:root_node }
 excl='!'
} : links
{
 inf.{
      <APPEAL>n.<PUNCTUATION>comma 
      <PUNCTUATION>excl
     }
}



// Частица ЭТО перед глагольным предикатом:
// это они спасли его
// ^^^
pattern ГлПредикат
{
 p=ЭтоКакЧастица
 n=ГлПредикат:export { node:root_node }
} : links { n.<PREFIX_PARTICLE>p }
  : ngrams { -6 }



// ---------

patterns Инф_Предикат export { node:root_node }

patterns ИнфПредикатНаречие export { node:root_node }

// как мне называть тебя?
// ^^^
pattern ИнфПредикатНаречие
{
 наречие:*{} : export { node:root_node }
}

// как же мне называть тебя?
// ^^^^^^
pattern ИнфПредикатНаречие
{
 a=наречие:*{} : export { node:root_node }
 p=частица:же{}
} : links { a.<POSTFIX_PARTICLE>p }

// а вот каково человеку стать драконом?
// ^^^^^^^^^^^^
pattern ИнфПредикатНаречие
{
 p=частица:вот{}
 a=наречие:*{} : export { node:root_node }
} : links { a.<PREFIX_PARTICLE>p }


// долго ли нам еще плыть?
// ^^^^^^^^
pattern ИнфПредикатНаречие
{
 a=наречие:*{} : export { node:root_node }
 p=частица:ли{}
} : links { a.<POSTFIX_PARTICLE>p }


// куда б тебе спрятаться?
// ^^^^^^
pattern ИнфПредикатНаречие
{
 a=наречие:*{} : export { node:root_node }
 p=ЧастицаБы
} : links { a.<POSTFIX_PARTICLE>p }


patterns ВопросКак export { node:root_node }
pattern ВопросКак
{
 наречие:как{} : export { node:root_node }
}

// как бы этим воспользоваться?
// ^^^^^^
pattern ВопросКак
{
 a=наречие:как{} : export { node:root_node }
 p=частица:бы{}
} : links { a.<POSTFIX_PARTICLE>p }

// как же этим воспользоваться?
// ^^^^^^
pattern ВопросКак
{
 a=наречие:как{} : export { node:root_node }
 p=частица:же{}
} : links { a.<POSTFIX_PARTICLE>p }



// безсубъектные предикаты с инфинитивным оборотом:
// Как сделать квас?
pattern Инф_Предикат
{
 how=ВопросКак
 V= Инф2 : export { node:root_node }
} : links { v.<QUESTION>how }


// как мне его теперь звать?
pattern Инф_Предикат
{
 how=ИнфПредикатНаречие
 sbj=ГлДополнение{ ПАДЕЖ:ДАТ }
 V= Инф2 : export { node:root_node }
} : links
{
 v.{
    <QUESTION>how
    <SUBJECT>sbj
   }
}
: ngrams
{
 -2
 ВалентностьГлагола(v)
}


// для чего вам убивать других?
pattern Инф_Предикат
{
 adv=ПредлогИСущ
 sbj=ГлДополнение{ ПАДЕЖ:ДАТ }
 V= Инф2 : export { node:root_node }
} : links
{
 v.{
    <PREPOS_ADJUNCT>adv
    <SUBJECT>sbj
   }
}
: ngrams
{
 -2
 ВалентностьГлагола(v)
}


// Марине некуда пойти
pattern Инф_Предикат
{
 sbj = ГлДополнение{ ПАДЕЖ:ДАТ }
 adv = ИнфПредикатНаречие
 V = Инф2 : export { node:root_node }
} : links
{
 v.{
    <ATTRIBUTE>adv
    <SUBJECT>sbj
   }
}
: ngrams
{
 -2
 adv_verb_score( adv, v )
 ВалентностьГлагола(v)
}

// -----------------------------------------------

// прочие безглагольные конструкции, выражающие законченную мысль
patterns Безглаг_Предикат export { node:root_node }


// вот берег подземного озера
// Вот же дьявол!
// (-): - Вот мы и пришли!
pattern Безглаг_Предикат
{
 v=частица:вот{} : export { node:root_node }
 p=@optional(частица:же{})
 what=ГлДополнение{ ПАДЕЖ:ИМ }
} : links
{
 v.{
    ~<POSTFIX_PARTICLE>p
    <SUBJECT>what
   }
}
: ngrams { -5 }




// вот вам моя веревка
pattern Безглаг_Предикат
{
 v=частица:вот{} : export { node:root_node }
 to=ГлДополнение{ ПАДЕЖ:ДАТ }
 what=ГлДополнение{ ПАДЕЖ:ИМ }
} : links
{
 v.{
    <OBJECT>to
    <SUBJECT>what
   }
}

// -------------------------------

pattern Предикат { ПредикатСвязка : export { node:root_node } }
pattern Предикат { ГлПредикат : export { node:root_node } }
pattern ГлПредикат { Безглаг_Предикат : export { node:root_node } }

pattern Предикат
{
 Инф_Предикат : export { node:root_node }
} : ngrams { -2 }

