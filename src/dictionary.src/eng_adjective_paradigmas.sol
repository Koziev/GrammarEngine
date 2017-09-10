// -----------------------------------------------------------------------------
// File  ENG_ADJECTIVE_PARADIGMAS.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения наречий для английского раздела.
// -----------------------------------------------------------------------------
//
// CD->26.02.2005
// LC->22.03.2010
// --------------


#include "sg_defs.h"

automat sg
{
 // HAPPY-HAPPIER-HAPPIEST
 paradigm Happy :  ENG_ADJECTIVE for "(.+)Y"
 {
  ADJ_FORM { "" "%-1%+IER" "%-1%+IEST" }
 }

 // GREAT-GREATER-GREATEST
 paradigm Great :  ENG_ADJECTIVE for "(.+)\\@v\\@v\\@c"
 {
  ADJ_FORM { "" "%+ER" "%+EST" }
 }

 // BIG-BIGGER-BIGGEST
 paradigm Big :  ENG_ADJECTIVE for "(.+)[oiau]\\@c"
 {
  ADJ_FORM { "" "%D%+ER" "%D%+EST" }
 }


 // PALE-PALER-PALEST
 paradigm Pale :  ENG_ADJECTIVE for "(.+)E"
 {
  ADJ_FORM { "" "%+R" "%+ST" }
 }

 // LONG-LONGER-LONGEST
 paradigm Long :  ENG_ADJECTIVE for "(.+)"
 {
  ADJ_FORM { "" "%+ER" "%+EST" }
 }

 // For adjectives without comparative and superlative forms
 paradigm Adj_10001 :  ENG_ADJECTIVE
 {
  ADJ_FORM:BASIC { "" }
 }

 paradigm Adj_10002 :  ENG_ADJECTIVE
 {
  ADJ_FORM { "" "%+ER" "%+EST" }
 }

}

