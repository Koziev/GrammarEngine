// -----------------------------------------------------------------------------
// File SG_ESP_MAIN.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения классов, координат для испанской секции Словаря.
// Подробнее о синтаксисе:
// http://www.solarix.ru/for_developers/docs/enums.shtml
// http://www.solarix.ru/for_developers/docs/classes.shtml
//
// -----------------------------------------------------------------------------
//
// CD->06.05.2006
// LC->08.04.2010
// --------------

#include "sg_defs.h"

automat sg
{
 class ES_NOUN as NOUN_es : NOUN
 {
  language Spanish

  tags
   {
    CharCasing
   }

  attributes
   {
    GENDER
   }

  dimentions
   {
    NUMBER
   }

 }




 class ES_ROOT as ROOT_es
 {
  language Spanish

  tags
   {
    CharCasing
   }
 }

}
