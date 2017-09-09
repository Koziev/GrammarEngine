// ***********************
// СВЯЗКИ
// ***********************



// ----------------------------------

// кот БЫЛ котенком
pattern Связка
{
 v=СвязочныйГлагол{ НАКЛОНЕНИЕ:ИЗЪЯВ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
 p=@optional(ЧастицаБы)
} : links { v.~<POSTFIX_PARTICLE>p }



// - Это оно и есть?
//           ^^^^^^
pattern Связка
{
 p=частица:и{}
 v=СвязочныйГлагол{ НАКЛОНЕНИЕ:ИЗЪЯВ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
}
: links { v.<POSTFIX_PARTICLE>p }
: ngrams { -3 }


// Ваша  мама  была же красавица!
//             ^^^^^^^
pattern Связка
{
 v=СвязочныйГлагол{ НАКЛОНЕНИЕ:ИЗЪЯВ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
 p=ЧастицаЖе
} : links { v.<POSTFIX_PARTICLE>p }

// было ли это знание новым?
// ^^^^^^^
pattern Связка
{
 v=СвязочныйГлагол{ НАКЛОНЕНИЕ:ИЗЪЯВ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
 p=ЧастицаЛи
} : links { v.<POSTFIX_PARTICLE>p }
: ngrams { 1 }

// кот не был щенком
pattern Связка
{
 n=частица:не{}
 v=СвязочныйГлагол{ НАКЛОНЕНИЕ:ИЗЪЯВ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
 p=@optional('бы')
} : links
{
 v.{
    <NEGATION_PARTICLE>n
    ~<POSTFIX_PARTICLE>p
   }
}

// не было ли это знание тайным?
// ^^^^^^^^^^
pattern Связка
{
 n=частица:не{}
 v=СвязочныйГлагол{ НАКЛОНЕНИЕ:ИЗЪЯВ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
 p=частица:ли{}
} : links
{
 v.{
    <NEGATION_PARTICLE>n
    <POSTFIX_PARTICLE>p
   }
}


// Я есть Грут.
//   ^^^^
pattern Связка
{
 'есть'{ ВРЕМЯ:НАСТОЯЩЕЕ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
}


// Ведь ты и есть мечта Оливии.
//         ^^^^^^
pattern Связка
{
 p=частица:и{}
 v='есть'{ ВРЕМЯ:НАСТОЯЩЕЕ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
}
: links { v.<PREFIX_PARTICLE>p }
: ngrams { -1 }



/*
// кот никогда не был щенком
pattern Связка
{
 adv=наречие:*{}
 n=частица:не{}
 v=глагол:быть{ НАКЛОНЕНИЕ:ИЗЪЯВ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
} : links
{
 v.{
    <ATTRIBUTE>adv
    <NEGATION_PARTICLE>n
   }
}
*/

/*
// кот недавно БЫЛ котенком
pattern Связка
{
 adv=Обст
 v=глагол:быть{ НАКЛОНЕНИЕ:ИЗЪЯВ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
 p=@optional('бы')
} : links
{
 v.{
    <ATTRIBUTE>adv
    ~<POSTFIX_PARTICLE>p
   }
}
: ngrams
{
 adv_verb_score( adv, v )
}
*/


/*
// Все это было попросту слишком неожиданно и чуждо для меня
//         ^^^^^^^^^^^^^
pattern Связка
{
 v=глагол:быть{ НАКЛОНЕНИЕ:ИЗЪЯВ } : export { РОД ЧИСЛО ЛИЦО ВРЕМЯ node:root_node }
 p=@optional('бы')
 adv=Обст
} : links
{
 v.{
    <ATTRIBUTE>adv
    ~<POSTFIX_PARTICLE>p
   }
}
: ngrams
{
 -1 // штраф за наречие после БЫТЬ
 adv_verb_score( adv, v )
}
*/


// ---------------------------------------------------

patterns СвязкаСказВосх { bottomup  } export { node:root_node ЛИЦО ЧИСЛО РОД THEMA_VALENCY RHEMA_VALENCY }

pattern СвязкаСказВосх
{
 Связка : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY:1 RHEMA_VALENCY:1 }
}


/*
// Был ли это твой голос?
// ^^^^^^ ^^^
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ THEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
 sbj=ЭТО_Местоим
}
: links { v.<SUBJECT>sbj }
//: ngrams { 1 }
*/



pattern СвязкаСказВосх
{
 v=СвязкаСказВосх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
 adv=Обст
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score(v,adv) }


// Он был в кровати, уставший и голодный
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
 attr=ОбособленныйАтрибут{ =v:РОД =v:ЧИСЛО }
}
: links { v.<SEPARATE_ATTR>attr }
: ngrams { -1 }


// результаты будут в этой графе
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
 pn=ПредлогИСущ{ гл_предл(v,_.prepos,_.n2) }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score(v,pn.prepos)
 ngram3( v, pn.prepos, pn.n2 )
}

pattern СвязкаСказВосх
{
 v=СвязкаСказВосх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
 intro=ВводнАктант
}
: links { v.<BEG_INTRO>intro }


pattern СвязкаСказВосх
{
 v=СвязкаСказВосх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
 attr=Детализатор
} : links { v.<DETAILS>attr }

pattern СвязкаСказВосх
{
 v=СвязкаСказВосх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
 x=ПрямоеОбращение
} : links { v.<APPEAL>x }


// Она была ласковой и заботливой
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 rhema=ГруппаПрил2{ ПАДЕЖ:ТВОР =v:ЧИСЛО =v:РОД }
}
: links { v.<RHEMA>rhema }




// В комнате больше никого не было.
//           ^^^^^^ ~~~~~~
wordentry_set НеПрисоедКомпаратив=
{
 местоим_сущ:ничто{},
 местоим_сущ:нечто{}, // Здесь нам делать больше нечего.
 местоим_сущ:некто{},
 местоим_сущ:никто{}
}

// Компаратив прилагательного в роли именного сказуемого со связочным глаголом:
//
// купол выглядел темнее стен
//                ^^^^^^ ^^^^
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 adj=ГруппаСравнПрил{ /*~ИсклСравнПрил*/ }
 obj=РодДополнение{ ~НеПрисоедКомпаратив }
}
: links { v.<RHEMA>adj.<OBJECT>obj }




// Она была ласковая и заботливая
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 rhema=ГруппаПрил2{ ПАДЕЖ:ИМ =v:ЧИСЛО =v:РОД }
}
: links { v.<RHEMA>rhema }

/*
// Вы были правы
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 rhema=КраткПрилРема{ =v:ЧИСЛО =v:РОД }
}
: links { v.<RHEMA>rhema }
*/


// Он будет победителем
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 rhema=ГлДополнение{ ПАДЕЖ:ТВОР }
}
: links { v.<RHEMA>rhema }


// Он был солдат
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 rhema=ГруппаСущ4{ ПАДЕЖ:ИМ [-1]ОДУШ:ОДУШ =v:ЧИСЛО =v:РОД }
}
: links { v.<RHEMA>rhema }





// Это была она
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 rhema=ГруппаМест{ ПАДЕЖ:ИМ =v:ЧИСЛО =v:ЛИЦО =v:РОД }
}
: links { v.<RHEMA>rhema }
: ngrams { -2 }

/* ???
// Это был он
//         ^^
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 rhema=Подлежащее{ =v:ЧИСЛО =v:ЛИЦО =v:РОД }
}
: links { v.<RHEMA>rhema }
*/


// был ли это такой голос?
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 sbj=ЭТО_Местоим
}
: links { v.<SUBJECT>sbj }
: ngrams { 1 }







patterns КтоПодлеж2 export { node:root_node } 
pattern КтоПодлеж2
{
 n=местоим_сущ:кто{} : export { node:root_node }
 p=@optional(частица:же{})
} : links { n.~<POSTFIX_PARTICLE>p }

// она была кто?
//     ^^^^^^^^
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
 rhema=КтоПодлеж2
}
: links { v.<RHEMA>rhema }
: ngrams { -1 }

// Без тебя я была никто.
//            ^^^^^^^^^^
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY:0 RHEMA_VALENCY }
 sbj=местоим_сущ{ ПАДЕЖ:ИМ }
}
: links { v.<RHEMA>sbj }
: ngrams { -2 }


// Тут был он
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ THEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY:0 RHEMA_VALENCY }
 sbj=Подлежащее{ =v:ЧИСЛО =v:РОД =v:ЛИЦО }
}
: links { v.<SUBJECT>sbj }





patterns ВремяКакПодлежащее export { node:root_node }
pattern ВремяКакПодлежащее
{
 adv=Наречия_Лишь
 n=ЧислСущ{ПАДЕЖ:ИМ} : export { node:root_node }
} : links { n.<ATTRIBUTE>adv }




// Теперь было лишь три часа ночи
pattern СвязкаСказВосх
{
 v=СвязкаСказВосх{ ЧИСЛО:ЕД РОД:СР THEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY:0 RHEMA_VALENCY:0 }
 sbj=ВремяКакПодлежащее
}
: links { v.<RHEMA>sbj }




// +++++++++++++++++++++++++++++++++++++++++++++

patterns СвязкаСказНисх export { node:root_node ЛИЦО ЧИСЛО РОД THEMA_VALENCY RHEMA_VALENCY }

// Если валентность подлежащего (темы) осталась незаполненной,
// то наложим небольшой штраф.
pattern СвязкаСказНисх
{
 СвязкаСказВосх{ THEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
} : ngrams { -1 }


// Какой же будет ее цена?
pattern СвязкаСказНисх
{
 СвязкаСказВосх{ THEMA_VALENCY:0 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
}



// кто были мои помощники?
pattern СвязкаСказНисх
{
 sbj=КтоПодлеж2
 v=СвязкаСказНисх{ THEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY:0 RHEMA_VALENCY }
} : links { v.<SUBJECT>sbj }
: ngrams { 1 }

/*
// Это был он
pattern СвязкаСказНисх
{
 sbj=ЭТО_Местоим
 v=СвязкаСказНисх{ THEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY:0 RHEMA_VALENCY }
}
: links { v.<SUBJECT>sbj }
: ngrams { 1 }
*/


// Это была чисто деловая беседа.
// Это был он
pattern СвязкаСказНисх
{
 sbj=ЭТО_Местоим
 v=СвязкаСказНисх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
}
: links { v.<SUBJECT>sbj }
//: ngrams { 1 }



// Он был тут
pattern СвязкаСказНисх
{
 sbj=Подлежащее
 v=СвязкаСказНисх{ THEMA_VALENCY:1 =sbj:ЛИЦО =sbj:РОД =sbj:ЧИСЛО } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY:0 RHEMA_VALENCY }
}
: links { v.<SUBJECT>sbj }
: ngrams { 1 }


// кто же она была?
pattern СвязкаСказНисх
{
 rhema=ГруппаМест{ ПАДЕЖ:ИМ }
 v=СвязкаСказНисх{ RHEMA_VALENCY:1 =rhema:ЛИЦО =rhema:РОД =rhema:ЧИСЛО } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
}
: links { v.<RHEMA>rhema }
: ngrams { -2 }


// Ласковой и заботливой она была 
pattern СвязкаСказНисх
{
 rhema=ГруппаПрил2{ ПАДЕЖ:ТВОР }
 v=СвязкаСказНисх{ =rhema:ЧИСЛО =rhema:РОД RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
}
: links { v.<RHEMA>rhema }


/*
// Вы правы были
pattern СвязкаСказНисх
{
 rhema=КраткПрилРема
 v=СвязкаСказНисх{ =rhema:ЧИСЛО =rhema:РОД RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
}
: links { v.<RHEMA>rhema }
*/

// Победителем будет он
pattern СвязкаСказНисх
{
 rhema=ГлДополнение{ ПАДЕЖ:ТВОР }
 v=СвязкаСказНисх{ RHEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY:0 }
}
: links { v.<RHEMA>rhema }



// Тут был я
pattern СвязкаСказНисх
{
 adv=Обст
 v=СвязкаСказНисх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
}
: links { v.<ATTRIBUTE>adv }
: ngrams { adv_verb_score(adv,v) }


// -----------------------------------

// уставший и голодный, в кровати он был
pattern СвязкаСказВосх
{
 attr=ОбособленныйАтрибут
 v=СвязкаСказВосх{ =attr:РОД =attr:ЧИСЛО } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
}
: links { v.<SEPARATE_ATTR>attr }
: ngrams { -1 }



// На сцене были они
pattern СвязкаСказНисх
{
 pn=ПредлогИСущ
 v=СвязкаСказНисх{ гл_предл(_,pn.prepos,pn.n2) } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
}
: links { v.<PREPOS_ADJUNCT>pn }
: ngrams
{
 prepos_score(v,pn.prepos)
 ngram3(v,pn.prepos,pn.n2)
}

pattern СвязкаСказНисх
{
 intro=ВводнАктант
 v=СвязкаСказНисх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
}
: links { v.<BEG_INTRO>intro }

pattern СвязкаСказНисх
{
 d=Детализатор
 v=СвязкаСказНисх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
}
: links { v.<DETAILS>d }


pattern СвязкаСказНисх
{
 x=ПрямоеОбращение
 v=СвязкаСказНисх : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY RHEMA_VALENCY }
}
: links { v.<APPEAL>x }


// Три часа ночи было на часах
pattern СвязкаСказНисх
{
 sbj=ВремяКакПодлежащее
 v=СвязкаСказНисх{ /*ВРЕМЯ:ПРОШЕДШЕЕ*/ ЧИСЛО:ЕД РОД:СР THEMA_VALENCY:1 } : export { node:root_node РОД ЛИЦО ЧИСЛО THEMA_VALENCY:0 RHEMA_VALENCY:0 }
}
: links { v.<SUBJECT>sbj }
: ngrams { 1 }


// +++++++++++++++++++++++++++++

pattern ПредикатСвязка
{
 v=СвязкаСказНисх : export { node:root_node }
}
: ngrams
{
 ВалентностьГлагола(v)
 ВалентностьПредиката(v)
}

// +++++++++++++++++++++++++++++

// Прочие паттерны связок, не вписавшиеся в восходяще-нисходящий алгоритм

// а мне этот человек нужен был живым.
pattern ПредикатСвязка
{
 obj=ГлДополнение{ ПАДЕЖ:ДАТ }
 sbj=Подлежащее
 a=прилагательное:*{ КРАТКИЙ ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ ПАДЕЖВАЛ:ДАТ =sbj:РОД =sbj:ЧИСЛО }
 V=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ =a:РОД =a:ЧИСЛО } : export { node:root_node }
 adj=ГруппаПрил2{ ПАДЕЖ:ТВОР =sbj:РОД =sbj:ЧИСЛО }
} : links
{
 v.{
    <SUBJECT>sbj
    <RHEMA>a.{
              <OBJECT>obj
              <ATTRIBUTE>adj
             }
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}

/*
// Редкий случай - связка настоящего времени, в качестве
// которой выступает форма 'ЕСТЬ':
//
// ты сейчас есть бледный отблеск самого себя.
//           ^^^^
pattern ПредикатСвязка
{
 N=Подлежащее
 adv1=@coalesce(Обст)
 v='есть'{ ВРЕМЯ:НАСТОЯЩЕЕ } : export { node:root_node }
 rhema=ГруппаСущ4{ ПАДЕЖ:ИМ =N:ЧИСЛО }
} : links
{
 v.{
    <SUBJECT>N
    ~<ATTRIBUTE>adv1
    <RHEMA>rhema
   }
}
: ngrams
{
 adv_verb_score(adv1,v)
}
*/



// Рема в виде последовательного прилагательного и существительного в родительном падеже:
// песок был странного цвета
pattern НеполнСвязка export { node:root_node РОД ЧИСЛО (ЛИЦО) ВРЕМЯ }
{
 adv=@optional(Обст)
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node РОД ЧИСЛО ВРЕМЯ }
 a=ГруппаПрил2{ ПАДЕЖ:РОД }
 r=существительное:*{ ПАДЕЖ:РОД =a:ЧИСЛО =a:РОД }
} : links
{
 v.{
    ~<ATTRIBUTE>adv
    <RHEMA>r.<ATTRIBUTE>a
   }
}
: ngrams
{
 -1
 adj_noun_score(a,r)
 adv_verb_score(adv,v)
}





// все были ему врагами
pattern НеполнСвязка export { node:root_node РОД ЧИСЛО (ЛИЦО) ВРЕМЯ }
{
 adv=@coalesce(Обст)
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node РОД ЧИСЛО ВРЕМЯ }
 obj=ГлДополнение{ ПАДЕЖ:ДАТ }
 r=ГруппаСущ4{ ПАДЕЖ:ТВОР }
} : links
{
 v.{
    ~<ATTRIBUTE>adv
    <OBJECT>obj
    <RHEMA>r
   }
}
: ngrams
{
 -1
 adv_verb_score(adv,v)
 ВалентностьГлагола(v)
}


// ты был мне другом!
pattern НеполнСвязка export { node:root_node РОД ЧИСЛО (ЛИЦО) ВРЕМЯ }
{
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node РОД ЧИСЛО ВРЕМЯ }
 obj=ГлДополнение{ ПАДЕЖ:ДАТ }
 r=ГруппаСущ4{ ПАДЕЖ:ТВОР }
} : links
{
 v.{
    <RHEMA>r
    <OBJECT>obj
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}

// ты другом мне был!
pattern НеполнСвязка export { node:root_node РОД ЧИСЛО (ЛИЦО) ВРЕМЯ }
{
 r=ГруппаСущ4{ ПАДЕЖ:ТВОР }
 obj=ГлДополнение{ ПАДЕЖ:ДАТ }
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ } : export { node:root_node РОД ЧИСЛО ВРЕМЯ }
} : links
{
 v.{
    <RHEMA>r
    <OBJECT>obj
   }
}
: ngrams
{
 -1 // за необычный порядок слов
 ВалентностьГлагола(v)
}






// кот был достаточно умен, чтобы поймать мышь
pattern ПредикатСвязка
{
 adv=@coalesce(Обст)
 @mark(Подлежащее,N)
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ =N:ЧИСЛО =N:РОД } : export { node:root_node }
 r=ДостаточнаяСтепень{ КРАТКИЙ =N:РОД =N:ЧИСЛО}
} : links
{
 v.{
    <SUBJECT>N
    <RHEMA>r
    ~<ATTRIBUTE>adv
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}

// кот был достаточно умный, чтобы поймать мышь
pattern ПредикатСвязка
{
 adv=@coalesce(Обст)
 @mark(Подлежащее,N)
 v=Связка{ ВРЕМЯ:ПРОШЕДШЕЕ =N:ЧИСЛО =N:РОД } : export { node:root_node }
 r=ДостаточнаяСтепень{ ~КРАТКИЙ =N:РОД =N:ЧИСЛО}
} : links
{
 v.{
    <SUBJECT>N
    <RHEMA>r
    ~<ATTRIBUTE>adv
   }
}
: ngrams
{
 ВалентностьГлагола(v)
}

