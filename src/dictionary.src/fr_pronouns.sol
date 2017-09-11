// -----------------------------------------------------------------------------
// File FR_PRONOUNS.SOL
//
// (c) 2005 Elijah Koziev
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения местоимений для французского раздела словаря.
// -----------------------------------------------------------------------------
//
// CD->04.11.2005
// LC->13.07.2012
// --------------


#include "sg_defs.h"

automat sg
{
 entry JE : FR_PRONOUN
 {
  FR_PRONOUN_FORM:WEAK |{
                         FR_PERSON:1 FR_NOMBRE         { JE "J'" }
                         FR_PERSON:1 FR_NOMBRE:PLURIEL { NOUS }
 
                         FR_PERSON:2 FR_NOMBRE           { TU VOUS }
                         FR_PERSON:2 FR_NOMBRE:SINGULIER { "T'" }
 
                         FR_PERSON:3 FR_NOMBRE:SINGULIER FR_GENRE { IL  ELLE }
                         FR_PERSON:3 FR_NOMBRE:PLURIEL   FR_GENRE { ILS ELLES }
                       }

  FR_PRONOUN_FORM:STRONG |{
                           FR_PERSON:1 FR_NOMBRE:SINGULIER { MOI }
                           FR_PERSON:2 FR_NOMBRE:SINGULIER { TOI }
                           FR_PERSON:3 FR_NOMBRE:SINGULIER { LUI }
                           FR_PERSON:3 FR_NOMBRE:SINGULIER { ELLE }

                           FR_PERSON:1 FR_NOMBRE:PLURIEL { NOUS }
                           FR_PERSON:2 FR_NOMBRE:PLURIEL { VOUS }
                           FR_PERSON:3 FR_NOMBRE:PLURIEL { ILS }
                           FR_PERSON:3 FR_NOMBRE:PLURIEL { EUX }
                           FR_PERSON:3 FR_NOMBRE:PLURIEL { ELLES }
                          }
 }

}

