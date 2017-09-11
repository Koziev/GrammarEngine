// -----------------------------------------------------------------------------
// File FR_ARTICTES.SOL
//
// (c) 2005 Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения артиклей для французского раздела Словаря.
// -----------------------------------------------------------------------------
//
// CD->04.11.2005
// LC->13.07.2012
// --------------


#include "sg_defs.h"

automat sg
{
 entry UN : FR_ARTICLE
 {
  FR_NOMBRE:SINGULIER  FR_GENRE { UN UNE }
  FR_NOMBRE:PLURIEL             { DES    }
 }

 entry LA : FR_ARTICLE
 {
  FR_NOMBRE:SINGULIER  FR_GENRE { LE LA }
  FR_NOMBRE:SINGULIER           { "L'"  }
  FR_NOMBRE:PLURIEL             { LES   }
 }
 
}

