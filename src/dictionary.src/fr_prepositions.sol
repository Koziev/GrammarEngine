// -----------------------------------------------------------------------------
// File FR_PREPOSITIONS.SOL
//
// (c) 2005 Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения предлогов для французского раздела.
// -----------------------------------------------------------------------------
//
// CD->04.11.2005
// LC->13.07.2012
// --------------


#include "sg_defs.h"

automat sg
{
 entry DE      : FR_PREP
 {
  { "de" }
  { "d'" }
 }

 entry CHEZ    : FR_PREP
 entry SUR     : FR_PREP
 entry AVEC    : FR_PREP
 entry SANS    : FR_PREP
 entry MOINS   : FR_PREP
 entry DEVANT  : FR_PREP
 entry SOUS    : FR_PREP
 entry POUR    : FR_PREP
}

