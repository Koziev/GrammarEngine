//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml

// CD->26.03.2009
// LC->26.03.2009

#include "aa_rules.inc"

#pragma floating off

automat aa
{

 operator FastInfinitive_1 : RusSA_Instant_Infinitive
 { 
  if context { * Инфинитив * }
   then
    {
     // Начал читать
     // Начав читать
     // Начать читать

     if and(
            or(
               context { Глагол:*{ МОДАЛЬНЫЙ }        * * },
               context { Инфинитив:*{ МОДАЛЬНЫЙ }     * * },
               context { Деепричастие:*{ МОДАЛЬНЫЙ }  * * }
              ),
            or(
               context { * * _КОН },
               context { * * Инфинитив },
               context { * * Глагол },
               context { * * Деепричастие },
               context { * * Наречие },
               context { * * Местоимение },
               context { * * Местоим_сущ }
              )
          )
      then
       {
        context { 0.<COVERB>1 2 } 
       }       
    }    
 } 


}

#pragma floating on
