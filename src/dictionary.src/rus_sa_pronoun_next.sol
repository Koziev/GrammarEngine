// -----------------------------------------------------------------------------
// File RUS_SA_PRONOUN_NEXT.SOL
//
// (c) Koziev Elijah
//
// Content:
// СИнтаксический анализатор: конструкции СНАЧАЛА Я, ПОТОМ ТЫ
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->15.09.2008
// LC->16.09.2008
// --------------

#include "aa_rules.inc"

#define _LOG_CLASS_    МЕСТОИМЕНИЕ
#define _LOG_CATEGORY_ LINK_PRONOUN_NEXT_1

#include "rus_sa_seq.inc"

automat sg
{
}



automat aa
{

 operator NextPronoun_10 : LINK_PRONOUN_NEXT_2
 {
  // СНАЧАЛА Я, ЗАТЕМ ТЫ
  if context { _След2_##_LOG_CLASS_.{ <CONDITION>*#a <CONSEQUENCE>*#b } }
     correlate { #a:ПАДЕЖ=#b }
   then
    context {
             МЕСТ_СЛЕД :set {
                              ЧИСЛО:МН
                              РОД=#a:РОД
                              ПАДЕЖ=#a:ПАДЕЖ
                             }
              .{ <CONDITION>#a <CONSEQUENCE>#b } }
 }

 operator NextPronoun_20 : LINK_PRONOUN_NEXT_2
 {
  // СНАЧАЛА Я, ЗАТЕМ ТЫ, НАКОНЕЦ МЫ
  if context { _След3_##_LOG_CLASS_.{ <CONDITION>*#a <CONSEQUENCE>*#b <CONSEQUENCE>*#c } }
     correlate { #a:ПАДЕЖ=#b }
   then
    context {
             МЕСТ_СЛЕД :set {
                              ЧИСЛО:МН
                              РОД=#a:РОД
                              ПАДЕЖ=#a:ПАДЕЖ
                             }
              .{ <CONDITION>#a <CONSEQUENCE>#b <CONSEQUENCE>#b } }
 }

}
