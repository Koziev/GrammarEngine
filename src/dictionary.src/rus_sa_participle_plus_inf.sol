// -----------------------------------------------------------------------------
// File RUS_SA_PARTICIPLE_PLUS_INF.SOL
//
// (c) Koziev Elijah
//
// Content:
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->28.08.2008
// LC->28.08.2008
// --------------

#include "aa_rules.inc"

automat aa
{
 #pragma floating off

 operator ParticipleInf_10 : LINK_PARTICIPLE_PLUS_INF
 {
  // НАЧАВШИЙ ДУМАТЬ
  if context { ПРИЛАГАТЕЛЬНОЕ:*{ ПРИЧАСТИЕ }#a ИНФИНИТИВ#b }
   then
    context { #a.<COVERB>#b }
 }

 
 #pragma floating on
}

