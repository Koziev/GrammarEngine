// Правила для быстрой свертки некоторых конструкций с участием наречия. 
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml

// CD->26.03.2009
// LC->12.08.2009

#include "aa_rules.inc"

#pragma floating off

automat aa
{
 operator FastAdverb_1 : RusSA_Instant_Adverb
 { 
  if context { * @and(Наречие:*{СТЕПЕНЬ:АТРИБ},@not("КАК")) * }
   then
    {
     // КОШКА БЫСТРО БЕГАЕТ
     // КОШКА НАЧАЛА БЫСТРО БЕГАТЬ
     // МЫ БЫСТРО БЕГАЕМ
     // ЭТО ПЛОХО ВЛИЯЕТ
     // НАЧАТЬ БЫСТРО БЕГАТЬ 
     // ВДОВОЛЬ ПОИГРАВ С МЫШКОЙ
     if and(
            or(
               context { Предлог         * * },
               context { Существительное * * },
               context { _НАЧ            * * },
               context { Глагол          * * },
               context { Инфинитив       * * },
               context { Деепричастие    * * },
               context { Местоимение     * * },
               context { Местоим_Сущ     * * },
               context { ЕСЛИ            * * },
               context { Прилагательное  * * }
              ),
            or(
               context { * * Глагол },
               context { * * Инфинитив },
               context { * * Прилагательное },
               context { * * Деепричастие }
              )
          )
      then
       {
        context { 0 2.<ATTRIBUTE>1 } 
       }       
    }    
 } 




 operator FastAdverb_2 : RusSA_Instant_Adverb
 { 
  // Лежа на полу, тихо спит
  if context { * * @and(Наречие:*{СТЕПЕНЬ:АТРИБ},@not("КАК")) * }
   then
    {
     if and(
            or(
               context { Существительное Пунктуатор * * },
               context { Прилагательное  Пунктуатор * * },
               context { Местоимение     Пунктуатор * * },
               context { Местоим_сущ     Пунктуатор * * },
               context { _НАЧ            Пунктуатор * * }
              ),
            or(
               context { * * * Глагол },
               context { * * * Инфинитив },
               context { * * * Прилагательное },
               context { * * * Деепричастие },
               context { * * * Наречие }
              )
          )
      then
       {
        context { 0 1 3.<ATTRIBUTE>2 } 
       }       
    }    
 } 

}

#pragma floating on
