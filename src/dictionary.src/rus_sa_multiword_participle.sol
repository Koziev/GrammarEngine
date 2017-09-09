// -----------------------------------------------------------------------------
// File RUS_SA_MULTIWORD_PARTICIPLE.SOL
//
// (c) Koziev Elijah
//
// Content:
// Синтаксический анализатор: связь предлогов с существительными и местоимениями
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->03.09.2008
// LC->03.09.2008
// --------------

#include "aa_rules.inc"


automat aa
{
 #pragma floating off


 operator To_Be_Plus_Participle_1 : LINK_MULTIWORD_PARTICIPLE
 {
  // БЫЛ СЪЕДЕН
  if context { ГЛАГОЛ:БЫТЬ { ВРЕМЯ:ПРОШЕДШЕЕ }#a ПРИЛАГАТЕЛЬНОЕ:* { КРАТКИЙ ПРИЧАСТИЕ } #b }
     correlate { РОД ЧИСЛО }
   then context { convolution{ center:#a #b } }
 }

 operator To_Be_Plus_Participle_2 : LINK_MULTIWORD_PARTICIPLE
 {
  // БУДЕТ СЪЕДЕН
  if context { ГЛАГОЛ:БЫТЬ { ВРЕМЯ:БУДУЩЕЕ }#a ПРИЛАГАТЕЛЬНОЕ:* { КРАТКИЙ ПРИЧАСТИЕ } #b }
     correlate { РОД ЧИСЛО }
   then context { convolution{ center:#a #b } }
 }

 #pragma floating on
}

