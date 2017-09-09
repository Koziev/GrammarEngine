// -----------------------------------------------------------------------------
// File RUS_SA_SUBCLAUSE.SOL
//
// (c) Koziev Elijah
//
// Content:
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->25.06.2009
// LC->12.08.2009
// --------------

#include "aa_rules.inc"
#include "sg_defs.h"

automat aa
{
 #pragma floating off

 operator Subclause_10 : RusSA_SubClause
 {
  // Я знаю, что надо делать.
  if context { _НАЧ Глагол _Запятая Безлич_Глагол _КОН }
   then context { 0 1.<SUBCLAUSE>3 4 }
 }

 operator Subclause_20 : RusSA_SubClause
 {
  // Я знаю, что любит есть котик.
  if context { _НАЧ Глагол _Запятая Глагол _КОН }
   then context { 0 1.<SUBCLAUSE>3 4 }
 }

 operator Subclause_30 : RusSA_SubClause
 {
  // Я знаю, что кошка сильнее собаки.
  if context { _НАЧ Глагол _Запятая Существительное:*{ПАДЕЖ:ИМ}.Прилагательное:*{СТЕПЕНЬ:СРАВН} _КОН }
   then context { 0 1.<SUBCLAUSE>3 4 }
 }

 operator Subclause_40 : RusSA_SubClause
 {
  // Я знаю, что одна кошка сильнее собаки.
  if context { _НАЧ Глагол _Запятая Числительное:*{ПАДЕЖ:ИМ}.Прилагательное:*{СТЕПЕНЬ:СРАВН} _КОН }
   then context { 0 1.<SUBCLAUSE>3 4 }
 }

 operator Subclause_50 : RusSA_SubClause
 {
  // Я знаю, что она сильнее собаки.
  if context { _НАЧ Глагол _Запятая Местоимение:*{ПАДЕЖ:ИМ}.Прилагательное:*{СТЕПЕНЬ:СРАВН} _КОН }
   then context { 0 1.<SUBCLAUSE>3 4 }
 }
 
 #pragma floating on
}

