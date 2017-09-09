// -----------------------------------------------------------------------------
// File RUS_SA_CONOUN.SOL
//
// (c) Koziev Elijah
//
// Content:
// Правила для синтаксического анализатора:
// связи существительных в группе
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->26.04.2009
// --------------

#include "aa_rules.inc"

automat aa
{
 #pragma floating off

 operator CoNoun_10 : LINK_CONOUN
 {
  // ГОСПОДИН ПРОКУРОР
  // ДОКТОР СМЕРТЬ
  if context { СУЩЕСТВИТЕЛЬНОЕ:*{}#a СУЩЕСТВИТЕЛЬНОЕ:*{}#b }
     correlate { ЧИСЛО ПАДЕЖ }
   then context { #a.<CONOUN>#b }
 }

/*
 operator CoNoun_20 : LINK_CONOUN
 {
  // ЧЕЛОВЕК-ПАУК
  // ЧЕРЕПАШКИ-НИНДЗЯ
  if context { СУЩЕСТВИТЕЛЬНОЕ:*{}#a _Дефис СУЩЕСТВИТЕЛЬНОЕ:*{}#b }
     correlate { 0:ЧИСЛО=2 0:ПАДЕЖ=2 }
   then context { #a.<CONOUN>#b }
 }
*/

 #pragma floating on
}

