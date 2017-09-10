// -----------------------------------------------------------------------------
// File ENG_PARTICLES.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения частиц для английского раздела Словаря.
//
// 13.10.2015 - добавлена новая статья для притяжательного постфикса 's
// -----------------------------------------------------------------------------
//
// CD->12.07.2005
// LC->06.11.2015
// --------------


#include "sg_defs.h"

automat sg
{
 entry YES  : ENG_PARTICLE
 entry NO   : ENG_PARTICLE
 entry NOT  : ENG_PARTICLE
 entry OK   : ENG_PARTICLE
 entry OKAY : ENG_PARTICLE
 entry TO   : ENG_PARTICLE

 entry SELF  : ENG_PARTICLE

 entry O    : ENG_PARTICLE

 entry etc. : ENG_PARTICLE

 entry PLEASE : ENG_PARTICLE
 
 entry "'s" : ENG_POSSESSION
 {
  NUMBER { "'s" "'" }
 }
}

