// ---------------------------------------------------------
// Предлог и подчиненный объект (обычно существительное, но
// может быть прилагательное или наречие)
// ---------------------------------------------------------



// Некоторые предлоги могут модифицироваться наречиями или частицами,
// кроме того предлоги могут участвовать в союзных конструкциях. Поэтому
// делаем отдельный нетерминал для представления предлога с возможными
// модификаторами/дополнениями.

patterns Предлог0 export { node:root_node ПАДЕЖ }

pattern Предлог0
{
 предлог:*{} : export { node:root_node ПАДЕЖ }
}

wordentry_set ПрефиксДляПредлога={ частица:вот{}, частица:аж{}, частица:уж{} }

// вот ради чего стоило сражаться
// ^^^^^^^^
pattern Предлог0
{
 p=ПрефиксДляПредлога
 n=предлог:*{} : export { node:root_node ПАДЕЖ }
} : links { n.<PREFIX_PARTICLE>p }

// Кроме докладов имел два приема до и после завтрака.
//                                ^^^^^^^^^^
// внутри и снаружи аксона химический состав жидкостей различен
// ^^^^^^^^^^^^^^^^^^^^^^^
//
// небольшой штраф нужен, чтобы предотвратить неверный разбор в случае:
// возвращайся назад с помощью или со знаниями
//                   ^^^^^^^^^^^^^^^^
pattern Предлог0
{
 n1=предлог:*{} : export { node:root_node }
 conj=ЛогичСоюз
 n2=предлог:*{} : export { ПАДЕЖ }
}
: links
{
 n1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>n2
}
: ngrams { -3 }



// Не вмешивайся не в своё дело!
//               ^^^^
pattern Предлог0
{
 p=частица:не{}
 n=предлог:*{} : export { ПАДЕЖ node:root_node }
} : links { n.<NEGATION_PARTICLE>p }


// По дороге я заглянул и к нему.
//                      ^^^^^^^^
pattern Предлог0
{
 p=частица:и{}
 n=предлог:*{} : export { ПАДЕЖ node:root_node }
} : links { n.<PREFIX_PARTICLE>p }
  : ngrams { -5 }


// --------------------------------------------------------------

// Некоторые наречия модифицируют предлоги
patterns Prefix4Prepos0 export { node:root_node }

pattern Prefix4Prepos0
{
 наречие:*{ ТИП_МОДИФ:ПРЕДЛ } : export { node:root_node }
}	


// Я стоял совсем недалеко от них, опираясь на костыль.
//         ^^^^^^^^^^^^^^^
pattern Prefix4Prepos0
{
 mod=МодифНареч
 adv=наречие:*{ ТИП_МОДИФ:ПРЕДЛ } : export { node:root_node }
} : links { adv.<ATTRIBUTE>mod }



patterns Prefix4Prepos export { node:root_node }

pattern Prefix4Prepos
{
 p1=Prefix4Prepos0 : export { node:root_node }
}

// Воины распределились справа и слева от колонны.
//                      ^^^^^^^^^^^^^^
pattern Prefix4Prepos
{
 p1=Prefix4Prepos0 : export { node:root_node }
 conj=ЛогичСоюз
 p2=Prefix4Prepos0
}
: links { p1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2 }
: ngrams { 1 }



// Надо идти только на юг
//           ^^^^^^^^^
// даже от колдуна может быть польза
// ^^^^^^^
// тепло исходит только от наших тел
//               ^^^^^^^^^
pattern Предлог0
{
 p=Prefix4Prepos
 n=Предлог0 : export { node:root_node ПАДЕЖ }
}
: links { n.<ATTRIBUTE>p }
: ngrams
{
 -1
 adv_prepos_score(p,n)
}


// только вот к чему она стремится?
// ^^^^^^^^^^^^
pattern Предлог0
{
 p=Prefix4Prepos
 p2=частица:вот{}
 n=Предлог0 : export { node:root_node ПАДЕЖ }
}
: links { n.{ <PREFIX_PARTICLE>p <PREFIX_PARTICLE>p2 } }
: ngrams { adv_prepos_score(p,n) }


// --------------------------------------------------------------

// Формально этот паттерн очень похож на чисто наречные обороты с предложным дополнением,
// например "Мы живём далеко от вокзала.". Но тут все-таки сохраняется главная роль предлога:
//
// он подал лимузин прямо к подъезду

wordentry_set НаречДля_К = наречие:{ /*прямо,*/ точно, непосредственно, прямиком }

pattern Предлог0
{
 adv=НаречДля_К
 p=предлог:к{}:export{ node:root_node ПАДЕЖ:ДАТ }
} : links
{
 p.<ATTRIBUTE>adv
}
: ngrams
{
 1 // чтобы по возможности подавить прикрепление второй части к глаголу
}





// Это не нуждается ни в каком объяснении
//                  ^^^^
pattern Предлог0
{
 p=частица:ни{}
 n=предлог:*{} : export { node:root_node ПАДЕЖ }
} : links { n.<NEGATION_PARTICLE>p }




// Наречная конструкция для предложного паттерна
// Арбузы растут теперь не только на юге.
//                      ^^^^^^^^^^^^
// Ноги разъезжаются не только на льду
//                   ^^^^^^^^^^^^
pattern Предлог0
{
 neg=частица:не{}
 adv=наречие:только{}
 n=предлог:*{} : export { node:root_node ПАДЕЖ }
}
: links { n.<ATTRIBUTE>adv.<NEGATION_PARTICLE>neg }
: ngrams { 1 }



pattern Предлог0
{
 q1=ОткрывающаяКавычка
 p=Предлог0 : export{ node:root_node ПАДЕЖ }
 q2=ЗакрывающаяКавычка
} : links
{
 p.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}


// -----------------------------------------------------

patterns ПредлогИСущ0 export { node:prepos node:root_node node:n2 }

// корм для кошки или собаки, кенгуру или канарейки
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущ0
{
 prepos=Предлог0:export{ node:root_node->prepos node:root_node }
 n=ГлДополнение{ =Prepos:Падеж }:export{ node:root_node->n2 }
}
: links { prepos.<OBJECT>n }
: ngrams { ВалентностьПредлога(prepos) }


// На большее его не хватило.
// ^^^^^^^^^^
pattern ПредлогИСущ0
{
 prepos=Предлог0:export{ node:root_node->prepos node:root_node }
 n=прилагательное:*{ падеж:вин степень:сравн }  :export{ node:root_node->n2 }
}
: links { prepos.<OBJECT>n }
: ngrams { -3 ВалентностьПредлога(prepos) }


// Дефолтное правило - связь предлога с любой формой существительного
pattern ПредлогИСущ0
{
 prepos=Предлог0:export{ node:root_node->prepos node:root_node }
 n=ГлДополнение{ !=Prepos:Падеж } : export{ node:root_node->n2 }
}
: links { prepos.<OBJECT>n }
: ngrams
{
 -10
 ВалентностьПредлога(prepos)
}

// Изредка встречается присоединение наречия в качестве объекта,
// хотя в норме такие устойчивые словосочетания должны быть наречиями
// в лексиконе по аналогии с "до завтра":
//
// Брат окончил школу на отлично.
//                    ^^^^^^^^^^
pattern ПредлогИСущ0
{
 prepos=Предлог0:export{ node:root_node->prepos node:root_node }
 n=наречие:*{ СТЕПЕНЬ:АТРИБ } : export{ node:root_node->n2 }
}
: links { prepos.<OBJECT>n }
: ngrams
{
 -8
 ВалентностьПредлога(prepos)
}


// Дефолтные правила для связи предлога с прочими словами:
pattern ПредлогИСущ0
{
 prepos=Предлог0:export{ node:root_node->prepos node:root_node }
 n=*:*{} : export{ node:root_node->n2 }
}
: links { prepos.<OBJECT>n }
: ngrams
{
 -12
 ВалентностьПредлога(prepos)
}



/* ???
// через две - институт
// ^^^^^^^^^
pattern ПредлогИСущ
{
 prepos=Предлог0:export{ node:root_node->prepos node:root_node }
 n=числительное:*{ =Prepos:Падеж }:export{ node:root_node->n2 }
}
: links { prepos.<OBJECT>n }
: ngrams { -5 } // штраф за неполноту
*/


/* ???
// Американские геи теперь борются и за разводы
//                                 ^^^^
pattern ПредлогИСущ
{
 p=частица:и{}
 prepos=предлог:*{}:export{ node:prepos node:root_node }
 n=ГруппаСущ4{ =Prepos:Падеж }:export{ node:root_node->n2 }
}
: links {
 prepos.{
         <OBJECT>n
         <PREFIX_PARTICLE>p
        }
}
: ngrams { -3 }
*/




patterns ИнострСлово0 export { node:root_node }
pattern ИнострСлово0
{
 @and( @regex("[a-z]+[0-9]*") : export { node:root_node }, @not(beth:*{}) )
}

patterns ИнострСловоЧисло0 export { node:root_node }
pattern ИнострСловоЧисло0
{ @and( @regex("[a-z]+[0-9]*") : export { node:root_node }, @not(beth:*{}) ) }

pattern ИнострСловоЧисло0
{ num_word:*{} : export { node:root_node } }


// Враги пробрались и в государственную компанию Lietuvos energijа.
//                                                        ^^^^^^^^
pattern ИнострСловоЧисло0
{ *:*{} : export { node:root_node } }
: ngrams { -8 }


// Он ушел в Google
//           ^^^^^^
pattern ИнострСлово
{
 ИнострСлово0 : export { node:root_node }
}

// Он ушел в Google Corporation
//           ^^^^^^^^^^^^^^^^^^
pattern ИнострСлово
{
 n1=ИнострСлово0 : export { node:root_node }
 n2=ИнострСловоЧисло0
} : links { n1.<NEXT_COLLOCATION_ITEM>n2 }




// Он ушел в Nakamura International Corporation
//           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ИнострСлово
{
 n1=ИнострСлово0 : export { node:root_node }
 n2=ИнострСловоЧисло0
 n3=ИнострСловоЧисло0
} : links { n1.<NEXT_COLLOCATION_ITEM>n2.<NEXT_COLLOCATION_ITEM>n3 }



// Английские слова, точнее всё, записанное латиницей, считаем существительными, если
// такое слово стоит после предлога:
// выложить ролик на youtube
pattern ПредлогИСущ0
{
 prepos=Предлог0:export{ node:root_node->prepos node:root_node }
 n=ИнострСлово:export{ node:root_node->n2 }
} : links { prepos.<OBJECT>n }


/* ???
// о тебе
pattern ПредлогИСущ
{
 Prepos1=Предлог0:export{ node:root_node->prepos node:root_node }
 n=местоимение:я{ =Prepos1:Падеж }:export{ node:n2 }
} : links { prepos1.<OBJECT>n }
*/


// вся ответственность лежит на тебе лично
//                           ^^^^^^^^^^^^^
pattern ПредлогИСущ0
{
 Prepos1=Предлог0:export{ node:root_node->prepos node:root_node }
 n=местоимение:я{ =Prepos1:Падеж }:export{ node:n2 }
 adv=НаречДляМест
}
: links { prepos1.<OBJECT>n.<ATTRIBUTE>adv }



// ------------------------------------------------------------------

// у них у самих осталось очень мало
//       ^^^^^^^
pattern ПредлогИСущ0
{
 Prepos1=Предлог0:export{ node:root_node->prepos node:root_node }
 n=ПрилСамОбъект{ =Prepos1:Падеж }:export { node:root_node->n2 }
}
: links { prepos1.<OBJECT>n }
: ngrams { -1 }


// -------------------------------------------



wordentry_set КтоЧто = местоим_сущ:{ кто, что }


// я кое с кем встретился
//   ^^^^^^^^^
pattern ПредлогИСущ
{
 a='кое'
 p=предлог:*{}:export{ node:prepos node:root_node }
 n=КтоЧто{ =p:Падеж }:export{ node:n2 }
} : links
{
 p.<OBJECT>n.<ATTRIBUTE>a
}



// особо - локатив с участием прилагательного, так как прилагательные не имеют
// отдельной формы локатива, она у них всегда совпадает с предложным падежом

// на песчаном берегу
pattern ПредлогИСущ0
{
 Prepos=Предлог0{ ПАДЕЖ:МЕСТ }:export{ node:root_node->prepos node:root_node }
 a=ГруппаПрил2{ ПАДЕЖ:ПРЕДЛ }
 n=существительное:*{ ПАДЕЖ:МЕСТ =A:РОД =A:ЧИСЛО =A:ОДУШ }:export{ node:n2 }
} : links { prepos.<OBJECT>n.<ATTRIBUTE>a }




// Паттерны ДРУГ xxx ДРУГ, предлог находится внутри
// Мы часто бываем друг у друга.
pattern ПредлогИСущ0
{
 n1=существительное:друг{ падеж:им }
 prep=предлог:*{}:export{ node:prepos node:root_node }
 n2=существительное:друг{ =prep:Падеж }:export{ node:n2 }
} : links
{
 prep.{
       <OBJECT>n1
       <OBJECT>n2
      }
}
: ngrams { 1 }


// они ждали помощи только друг от друга
//                  ^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущ0
{
 mod=Prefix4Prepos
 n1=существительное:друг{ падеж:им }
 prep=предлог:*{}:export{ node:prepos node:root_node }
 n2=существительное:друг{ =prep:Падеж }:export{ node:n2 }
} : links
{
 prep.{
       <ATTRIBUTE>mod
       <OBJECT>n1
       <OBJECT>n2
      }
}
: ngrams { 1 }



// Мы говорим об одном и том же
//            ^^^^^^^^^^^^^^^^^
pattern ПредлогИСущ0
{
 prep=Предлог0:export{ node:root_node->prepos node:root_node }
 a1=прилагательное:один{ род:ср число:ед } : export { node:n2 }
 conj=союз:и{}
 a2=прилагательное:тот{ род:ср число:ед =a1:падеж }
 p=частица:же{}
} : links { prep.<OBJECT>a1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>a2.<POSTFIX_PARTICLE>p }
  : ngrams { 2 }



// ни о чём
pattern ПредлогИСущ
{
 местоим_сущ:ничто{ ПАДЕЖ:ПРЕДЛ } : export { node:prepos node:n2 node:root_node }
}


// ни о ком
pattern ПредлогИСущ
{
 местоим_сущ:никто{ ПАДЕЖ:ПРЕДЛ } : export { node:prepos node:n2 node:root_node }
}

// от 8,5% годовых
wordentry_set ПредлогиОтДо = { предлог:от{}, предлог:до{} }
pattern ПредлогИСущ0
{
 prepos=Предлог0{ПредлогиОтДо}:export{ node:root_node->prepos node:root_node }
 n=@regex("[[:digit:]],[[:digit:]]%"):export{ node:n2 }
 a=прилагательное:годовой{ число:мн падеж:род }
} : links { prepos.<OBJECT>n.<ATTRIBUTE>a }
: ngrams
{
 ВалентностьПредлога(prepos)
}



// Паттерны с предлогом МЕЖДУ, который может управлять двумя именными частями:
// расположиться между диваном и стеной
pattern ПредлогИСущ0
{
 p=предлог:между{}:export{ node:prepos node:root_node }
 n1=ГлДополнение{ =p:Падеж }:export{ node:root_node->n2 }
 conj=союз:и{}
 n2=ГлДополнение{ =p:Падеж }
} : links
{
 p.<OBJECT>n1.
    <RIGHT_LOGIC_ITEM>conj.
     <OBJECT>n2
}
: ngrams
{
 1
 ВалентностьПредлога(p)
} // чтобы по возможности подавить прикрепление второй части к глаголу


// рукоятью вперед полетел меч.
// ^^^^^^^^^^^^^^^
// Чего ради щадить убийцу?
// ^^^^^^^^^
pattern ПредлогИСущ
{
 n=ГлДополнение:export{ node:root_node->n2 }
 p=послелог:*{ =n:падеж }:export{ node:prepos node:root_node }
}
: links { p.<OBJECT>n }
: ngrams
{
 1
 postfix_score( n, p )
 ВалентностьПредлога(p)
}


// Трагедия произошла около недели назад.
//                    ^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущ
{
 mod=ГруппаНареч1
 n=ГлДополнение:export{ node:root_node->n2 }
 p=послелог:*{ =n:падеж }:export{ node:prepos node:root_node }
}
: links { p.{ <ATTRIBUTE>mod <OBJECT>n } }
: ngrams
{
 1
 postfix_score( n, p )
 ВалентностьПредлога(p)
}



// отказаться от самого себя.
//            ^^^^^^^^^^^^^^
pattern ПредлогИСущ0
{
 prepos=Предлог0:export{ node:root_node->prepos node:root_node }
 a=прилагательное:сам{}
 n=местоим_сущ:себя{ =a:падеж }:export{ node:n2 }
} : links { prepos.<OBJECT>n.<ATTRIBUTE>a }
: ngrams
{
 ВалентностьПредлога(prepos)
}



wordentry_set ПредлогНачалоДиапазона=предлог:{ с, от }
wordentry_set ПредлогКонецДиапазона=предлог:{ по, до }

// В результате взрыва выбиты стекла квартир со второго по пятый этажи.
//                                           ^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущ0
{
 prepos=ПредлогНачалоДиапазона:export{ node:root_node->prepos node:root_node }
 a1=ГруппаПрил2{ =prepos:ПАДЕЖ }:export{ node:root_node->n2 }
 p2=ПредлогКонецДиапазона
 a2=ГруппаПрил2{ =p2:ПАДЕЖ }
 n=СущСПредложДоп{ ПАДЕЖ:ВИН }
} : links
{
 prepos.<OBJECT>a1.
         <PREPOS_ADJUNCT>p2.
          <OBJECT>n.
           <ATTRIBUTE>a2 
}




// -----------------------------------------------------------
// СОЧИНИТЕЛЬНЫЕ/СОЮЗНЫЕ КОНСТРУКЦИИ С ПРЕДЛОЖНЫМИ ПАТТЕРНАМИ
// -----------------------------------------------------------


// ------------------------------------------------------------------------

patterns ПредлогИСущВосх { bottomup } export { node:root_node node:prepos node:n2 }


// Мы смотрим на неё
//            ^^^^^^
pattern ПредлогИСущВосх
{
 p1=ПредлогИСущ0 : export{ node:prepos node:n2 node:root_node }
}


// обратиться к делегатам конференции и к их гостям
//            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущВосх
{
 p1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 conj=ЛогичСоюз
 p2=ПредлогИСущ0
} : links
{
 p1.<RIGHT_LOGIC_ITEM>conj.<NEXT_COLLOCATION_ITEM>p2
}
: ngrams
{
 -1 // надо проверять смысловую совместимость частей
}


// Девчушка (как же ее звали?) шла по улице, как по своей жизни.
//                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущВосх
{
 p1=ПредлогИСущ0:export{ node:prepos node:root_node node:n2 }
 comma=','
 conj=союз:как{}
 p2=Предлог0
 n2=ГлДополнение{ =p2:ПАДЕЖ }
} : links
{
 p1.{
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>p2.<OBJECT>n2
    }
}
: ngrams
{
 -1 // надо проверять смысловую совместимость частей
}

// Сейчас он вернулся назад на родную Землю, в свою больницу.
//                          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущВосх
{
 p1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 comma=','
 p2=ПредлогИСущ0
 @noshift(ПравыйОграничительОборота)
} : links
{
 p1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>p2
}
: ngrams
{
 -1 // надо проверять смысловую совместимость частей
}


pattern ПредлогИСущВосх
{
 p1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 comma=','
 p2=ПредлогИСущ0
} : links
{
 p1.<RIGHT_LOGIC_ITEM>comma.<NEXT_COLLOCATION_ITEM>p2
}
: ngrams
{
 -2
}


// посмотреть на экран, в монитор и т.д.
//            ^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущВосх
{
 p1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 conj=союз:и{}
 etc=ЧастицыПеречисления
} : links
{
 p1.<RIGHT_LOGIC_ITEM>conj.
     <NEXT_COLLOCATION_ITEM>etc
}

/*
// Спокойствие царствует в воздухе, в воде, в траве
//                       ^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущВосх
{
 p1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 comma1=','
 p2=ПредлогИСущ0
 comma2=','
 p3=ПредлогИСущ0
} : links
{
 p1.<RIGHT_LOGIC_ITEM>comma1.
     <NEXT_COLLOCATION_ITEM>p2.
      <RIGHT_LOGIC_ITEM>comma2.
       <NEXT_COLLOCATION_ITEM>p3
}
: ngrams
{
 //-1 // надо проверять смысловую совместимость частей
}
*/


/*
// поговорили о работе, о друзьях и о недругах
//            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущ
{
 prepos1=ПредлогИСущ0:export{ node:prepos node:root_node node:n2 }
 comma=','
 Prepos2=ПредлогИСущ0
 conj=ЛогичСоюз
 Prepos3=ПредлогИСущ0
} : links
{
 prepos1.<RIGHT_LOGIC_ITEM>comma.
          <NEXT_COLLOCATION_ITEM>prepos2.
            <RIGHT_LOGIC_ITEM>conj.
             <NEXT_COLLOCATION_ITEM>prepos3
}
*/


/*
// они поболтали о работе, о друзьях, о семье и о домашних животных
//               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущ
{
 prepos1=ПредлогИСущ0:export{ node:prepos node:root_node node:n2 }
 comma1=','
 Prepos2=ПредлогИСущ0
 comma2=','
 Prepos3=ПредлогИСущ0
 conj=ЛогичСоюз
 Prepos4=ПредлогИСущ0
} : links
{
 prepos1.<RIGHT_LOGIC_ITEM>comma1.
          <NEXT_COLLOCATION_ITEM>prepos2.
           <RIGHT_LOGIC_ITEM>comma2.
             <NEXT_COLLOCATION_ITEM>prepos3.
              <RIGHT_LOGIC_ITEM>conj.
               <NEXT_COLLOCATION_ITEM>prepos4
}
*/

// взрывы слышны как в центре Триполи, так и на его окраинах
//               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущВосх
{
 conj1=Соедин2Обст1
 prepos1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 comma=','
 conj2=Соедин2Обст2
 prepos2=ПредлогИСущВосх
} : links
{
 prepos1.{
          <PREFIX_CONJUNCTION>conj1
          <RIGHT_LOGIC_ITEM>comma.
           <NEXT_COLLOCATION_ITEM>conj2.
            <NEXT_COLLOCATION_ITEM>prepos2
         }
}



// Он идёт не по дороге, а по траве.
//         ^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущВосх
{
 ne=частица:не{}
 prepos1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 comma=','
 conj2=ПротивитСоюз
 Prepos2=ПредлогИСущ0
} : links
{
 prepos1.{
          <NEGATION_PARTICLE>ne
          <RIGHT_LOGIC_ITEM>comma.
           <NEXT_COLLOCATION_ITEM>prepos2.
            <PREFIX_CONJUNCTION>conj2
         }
}





wordentry_set ПротивительныйСоюз=союз:{ а, но }

// увидится сначала с доктором, а затем с психотерапевтом
//          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущВосх
{
 adv1=наречие:*{}
 p1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 comma=','
 conj=ПротивительныйСоюз
 adv2=наречие:*{}
 p2=ПредлогИСущ0
} : links
{
 p1.<ATTRIBUTE>adv1.
     <RIGHT_LOGIC_ITEM>comma.
      <NEXT_COLLOCATION_ITEM>conj.
       <NEXT_COLLOCATION_ITEM>p2.
        <ATTRIBUTE>adv2
}
: ngrams
{
 -1 // надо проверять смысловую совместимость частей
}




pattern ПредлогИСущВосх
{
 conj1=СочинительныйСоюз1
 p1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 comma=','
 conj2=СочинительныйСоюз2
 p2=ПредлогИСущ0
} : links
{
 p1.{
      <PREFIX_CONJUNCTION>conj1
      <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>conj2.
        <NEXT_COLLOCATION_ITEM>p2
     }
}


// Они просочились либо через второй блок-пост, либо через подземные коммуникации
//                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
pattern ПредлогИСущВосх
{
 conj1=ЛогичСоюз2
 p1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 comma=','
 conj2=СочинительныйСоюз2
 p2=ЛогичСоюз2
} : links
{
 p1.{
      <PREFIX_CONJUNCTION>conj1
      <RIGHT_LOGIC_ITEM>comma.
       <NEXT_COLLOCATION_ITEM>conj2.
        <NEXT_COLLOCATION_ITEM>p2
     }
}


/*
// Их разум опирается на логику, а не на похоть и желания.
//                    ^^^^^^^^^^^^^^^^^^...
pattern ПредлогИСущВосх
{
 p1=ПредлогИСущВосх:export{ node:prepos node:root_node node:n2 }
 comma=','
 conj=ПротивительныйСоюз
 p=частица:не{}
 p2=ПредлогИСущ0
} : links
{
 p1.<RIGHT_LOGIC_ITEM>comma.
     <NEXT_COLLOCATION_ITEM>conj.
      <NEXT_COLLOCATION_ITEM>p2.
       <NEGATION_PARTICLE>p
}
: ngrams
{
 -1 // надо проверять смысловую совместимость частей
}
*/


// ---------------------------------------------------------

// Мы смотрим на неё
//            ^^^^^^
pattern ПредлогИСущ
{
 ПредлогИСущВосх : export{ node:prepos node:n2 node:root_node }
}

// - Замолчите, ради бога!
//            ^^^^^^^^^^^
pattern ПредлогИСущ
{
 comma=','
 pn=ПредлогИСущВосх : export{ node:prepos node:n2 node:root_node }
 comma2=@coalesce(',')
 @noshift(ПравыйОграничительОборота)
}
: links
{
 pn.{
     <PUNCTUATION>comma
     ~<PUNCTUATION>comma2
    }
}
: ngrams { -2 }

// -----------------------------------------------------------------------

// "по заказу" проходить лицензирование
// ^^^^^^^^^^^
pattern ПредлогИСущ
{
 q1=ОткрывающаяКавычка
 p=ПредлогИСущ : export{ node:prepos node:n2 node:root_node }
 q2=ЗакрывающаяКавычка
} : links
{
 p.{
    <PREPEND_QUOTE>q1
    <APPEND_QUOTE>q2
   }
}

// -------------------------------------------------------

wordentry_set НаречиеПодобныеВчера =
{ наречие:вчера{}, наречие:сегодня{}, наречие:позавчера{}, наречие:послезавтра{} }

// Со вчера осталось.
// ^^^^^^^^
pattern ПредлогИСущ0
{
 prepos=Предлог0:export{ node:root_node->prepos node:root_node }
 n=НаречиеПодобныеВчера:export{ node:n2 }
}
: links { prepos.<OBJECT>n }
: ngrams
{
 -2
 ВалентностьПредлога(prepos)
}
