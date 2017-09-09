// -----------------------------------------------------------------------------
// File RUS_SA_PRONOUN_NI_NI.SOL
//
// (c) Koziev Elijah
//
// Content:
// СИнтаксический анализатор: конструкции НИ Я, НИ ТЫ
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->09.09.2008
// LC->18.08.2009
// --------------

#include "aa_rules.inc"

automat aa
{

 operator NiNiPronoun_10 : LINK_PRONOUN_NI_NI
 {
  // НИ Я НИ ТЫ
  if context { СОЮЗ:НИ{} МЕСТОИМЕНИЕ{}#a СОЮЗ:НИ{} МЕСТОИМЕНИЕ{}#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context {
             МЕСТ_НИ_НИ :set {
                              ЧИСЛО:МН
                              РОД=#a:РОД
                              ПАДЕЖ=#a:ПАДЕЖ
                             }
              .{ <LOGIC_ITEM>#a <LOGIC_ITEM>#b } }
 }


 operator NiNiPronoun_20 : LINK_PRONOUN_NI_NI
 {
  // НИ Я, НИ ТЫ
  if context { СОЮЗ:НИ{} МЕСТОИМЕНИЕ{}#a _Запятая СОЮЗ:НИ{} МЕСТОИМЕНИЕ{}#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context {
             МЕСТ_НИ_НИ :set {
                              ЧИСЛО:МН
                              РОД=#a:РОД
                              ПАДЕЖ=#a:ПАДЕЖ
                             }
             .{ <LOGIC_ITEM>#a <LOGIC_ITEM>#b } }
 }

 operator NiNiPronoun_30 : LINK_PRONOUN_NI_NI
 {
  // НИ Я, НИ ТЫ, НИ ОН
  if context { СОЮЗ:НИ{} МЕСТОИМЕНИЕ{}#a _Запятая СОЮЗ:НИ{} МЕСТОИМЕНИЕ{}#b  _Запятая СОЮЗ:НИ{} МЕСТОИМЕНИЕ{}#c }
     correlate { #a:ПАДЕЖ=#b #a:ПАДЕЖ=#c }
   then
    context {
             МЕСТ_НИ_НИ :set {
                              ЧИСЛО:МН
                              РОД=#a:РОД
                              ПАДЕЖ=#a:ПАДЕЖ
                             }
             .{ <LOGIC_ITEM>#a <LOGIC_ITEM>#b <LOGIC_ITEM>#c } }
 }

}
