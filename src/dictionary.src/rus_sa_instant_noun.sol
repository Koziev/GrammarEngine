//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml

// CD->26.03.2009
// LC->18.04.2009

#include "aa_rules.inc"

#pragma floating off

automat aa
{

 operator FastNoun_1 : RusSA_Instant_Noun
 { 
  if context { СУЩЕСТВИТЕЛЬНОЕ СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД } * }
   then
    {
     if or(
           context { * * _КОН },
           context { * * Глагол },
           context { * * Местоимение }
          )
      then
       {
        context { 0.1 2 } 
       }       
    }    
 } 



 operator FastNoun_2 : RusSA_Instant_Noun
 { 
  if context { СУЩЕСТВИТЕЛЬНОЕ СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД } СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД } * }
   then
    {
     if or(
           context { * * * _КОН },
           context { * * * Глагол },
           context { * * * Местоимение }
          )
      then
       {
        context { 0.1.2 3 } 
       }       
    }    
 } 


 operator FastNoun_3 : RusSA_Instant_Noun
 { 
  if context { СУЩЕСТВИТЕЛЬНОЕ СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД } СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД } СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД } * }
   then
    {
     if or(
           context { * * * * _КОН },
           context { * * * * Глагол },
           context { * * * * Местоимение }
          )
      then
       {
        context { 0.1.2.3 4 } 
       }       
    }    
 } 

}

#pragma floating on
