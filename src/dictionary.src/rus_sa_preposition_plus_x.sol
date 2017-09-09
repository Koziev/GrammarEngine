// -----------------------------------------------------------------------------
// File RUS_SA_PREPOSITION_PLUS_X.SOL
//
// (c) Koziev Elijah
//
// Content:
// Синтаксический анализатор: связь предлогов с существительными и местоимениями
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->09.01.2009
// --------------

#include "aa_rules.inc"


automat aa
{
 #pragma floating off


 operator Preposition_1 : LINK_PREPOSITIONS
 {
  // 'ПО ЛЕСУ' - свертка предлога и объекта.
  if context { ПРЕДЛОГ#a СУЩЕСТВИТЕЛЬНОЕ#b }
     correlate { ПАДЕЖ } // ПРЕДЛОГИ ТРЕБУЮТ СОГЛАСОВАНИЯ ПО ПАДЕЖУ.
   then context { convolution{ #a center:#b } }
 }

 operator Preposition_2 : LINK_PREPOSITIONS
 {
  // 'ПО ТЕБЕ' - свертка предлога и объекта.
  if context { ПРЕДЛОГ#a МЕСТОИМЕНИЕ:Я{}#b }
     correlate { ПАДЕЖ } // ПРЕДЛОГИ ТРЕБУЮТ СОГЛАСОВАНИЯ ПО ПАДЕЖУ.
   then context { convolution{ #a center:#b } }
 }


 operator Preposition_3 : LINK_PREPOSITIONS
 {
  // У КОГО
  if context { ПРЕДЛОГ#a МЕСТОИМ_СУЩ:*{}#b }
     correlate { ПАДЕЖ } // ПРЕДЛОГИ ТРЕБУЮТ СОГЛАСОВАНИЯ ПО ПАДЕЖУ.
   then context { convolution{ #a center:#b } }
 }

 operator Preposition_4 : LINK_PREPOSITIONS
 {
  // У СЕМИ НЯНЕК
  if context { ПРЕДЛОГ#a ЧИСЛИТЕЛЬНОЕ:*{}#b }
     correlate { ПАДЕЖ } // ПРЕДЛОГИ ТРЕБУЮТ СОГЛАСОВАНИЯ ПО ПАДЕЖУ.
   then context { convolution{ #a center:#b } }
 }

 operator Preposition_5 : LINK_PREPOSITIONS
 {
  // У 7 НЯНЕК
  if context { ПРЕДЛОГ#a NUMBER_#b }
   then context { convolution{ #a center:#b } }
 }




 operator Preposition_10 : LINK_PREPOSITIONS
 {
  // ДЛЯ ВСЕЙ ВСЕЛЕННОЙ
  if context { ПРЕДЛОГ#a ПРИЛАГАТЕЛЬНОЕ:*{ ~КРАТКИЙ }#c СУЩЕСТВИТЕЛЬНОЕ#b }
     correlate { ПАДЕЖ 1:РОД=2 1:ЧИСЛО=2 }
   then context { convolution{ #a center:#b }.<ATTRIBUTE>#c }
 }

 operator Preposition_11 : LINK_PREPOSITIONS
 {
  // ДЛЯ ВСЕЙ НАШЕЙ ВСЕЛЕННОЙ
  if context { ПРЕДЛОГ#a ПРИЛАГАТЕЛЬНОЕ:*{ ~КРАТКИЙ }#c ПРИЛАГАТЕЛЬНОЕ:*{ ~КРАТКИЙ }#d СУЩЕСТВИТЕЛЬНОЕ#b }
     correlate { ПАДЕЖ 1:РОД=2 1:ЧИСЛО=2 1:РОД=3 1:ЧИСЛО=3 }
   then context { convolution{ #a center:#b }.{ <ATTRIBUTE>#c <ATTRIBUTE>#d } }
 }

 operator Preposition_12 : LINK_PREPOSITIONS
 {
  // ДЛЯ ВСЕЙ НАШЕЙ НЕОБЪЯТНОЙ ВСЕЛЕННОЙ
  if context { ПРЕДЛОГ#a ПРИЛАГАТЕЛЬНОЕ:*{ ~КРАТКИЙ }#c ПРИЛАГАТЕЛЬНОЕ:*{ ~КРАТКИЙ }#d ПРИЛАГАТЕЛЬНОЕ:*{ ~КРАТКИЙ }#e СУЩЕСТВИТЕЛЬНОЕ#b }
     correlate { ПАДЕЖ 1:РОД=2 1:ЧИСЛО=2 1:РОД=3 1:ЧИСЛО=3 1:РОД=4 1:ЧИСЛО=4 }
   then context { convolution{ #a center:#b }.{ <ATTRIBUTE>#c <ATTRIBUTE>#d  <ATTRIBUTE>#e } }
 }

 operator Preposition_13 : LINK_PREPOSITIONS
 {
  // ДЛЯ ОЧЕНЬ БОЛЬШОЙ ВСЕЛЕННОЙ
  if context { ПРЕДЛОГ#a НАРЕЧИЕ#f ПРИЛАГАТЕЛЬНОЕ:*{ ~КРАТКИЙ }#c СУЩЕСТВИТЕЛЬНОЕ#b }
     correlate { ПАДЕЖ 1:РОД=2 1:ЧИСЛО=2 }
   then context { convolution{ #a center:#b }.<ATTRIBUTE>#c.<ATTRIBUTE>#f }
 }



 // Исключительный случай - дательная валентость для предлога 'НА' убрана, а
 // отдельные случаи сочетания с дательным падежом рассматриваются тут.
 operator Preposition_20 : LINK_PREPOSITIONS
 {
  // НА БЕРЕГУ
  if context { ПРЕДЛОГ:НА{}#a СУЩЕСТВИТЕЛЬНОЕ:БЕРЕГ{ ПАДЕЖ:ДАТ }#b }
   then context { convolution{ #a center:#b } }
 }


 #pragma floating on
}

