// -----------------------------------------------------------------------------
// File RUS_SA_PRONOUN_TO_TO.SOL
//
// (c) Koziev Elijah
//
// Content:
// СИнтаксический анализатор: конструкции TO Я, TO ТЫ
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

 operator ToToPronoun_10 : LINK_PRONOUN_TO_TO
 {
  // TO Я TO ТЫ
  if context { СОЮЗ:ТО{} МЕСТОИМЕНИЕ{}#a СОЮЗ:ТО{} МЕСТОИМЕНИЕ{}#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context {
             МЕСТОИМЕНИЕ:МЕСТ_ТО_ТО{} :set {
                              ЧИСЛО:МН
                              РОД=#a:РОД
                              ПАДЕЖ=#a:ПАДЕЖ
                             }
              .{ <LOGIC_ITEM>#a <LOGIC_ITEM>#b } }
 }


 operator ToToPronoun_20 : LINK_PRONOUN_TO_TO
 {
  // TO Я, TO ТЫ
  if context { СОЮЗ:ТО{} МЕСТОИМЕНИЕ{}#a _Запятая СОЮЗ:ТО{} МЕСТОИМЕНИЕ{}#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context {
             МЕСТОИМЕНИЕ:МЕСТ_ТО_ТО{} :set {
                              ЧИСЛО:МН
                              РОД=#a:РОД
                              ПАДЕЖ=#a:ПАДЕЖ
                             }
             .{ <LOGIC_ITEM>#a <LOGIC_ITEM>#b } }
 }

 operator ToToPronoun_25 : LINK_PRONOUN_TO_TO
 {
  // ИНОГДА Я, ИНОГДА ТЫ
  if context { НАРЕЧИЕ:ИНОГДА{} МЕСТОИМЕНИЕ{}#a _Запятая НАРЕЧИЕ:ИНОГДА{} МЕСТОИМЕНИЕ{}#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context {
             МЕСТОИМЕНИЕ:МЕСТ_ТО_ТО{} :set {
                              ЧИСЛО:МН
                              РОД=#a:РОД
                              ПАДЕЖ=#a:ПАДЕЖ
                             }
             .{ <LOGIC_ITEM>#a <LOGIC_ITEM>#b } }
 }

 operator ToToPronoun_30 : LINK_PRONOUN_TO_TO
 {
  // TO Я, TO ТЫ, TO ОН
  if context { СОЮЗ:ТО{} МЕСТОИМЕНИЕ{}#a _Запятая СОЮЗ:ТО{} МЕСТОИМЕНИЕ{}#b  _Запятая СОЮЗ:ТО{} МЕСТОИМЕНИЕ{}#c }
     correlate { #a:ПАДЕЖ=#b #a:ПАДЕЖ=#c }
   then
    context {
             МЕСТОИМЕНИЕ:МЕСТ_ТО_ТО{} :set {
                              ЧИСЛО:МН
                              РОД=#a:РОД
                              ПАДЕЖ=#a:ПАДЕЖ
                             }
             .{ <LOGIC_ITEM>#a <LOGIC_ITEM>#b <LOGIC_ITEM>#c } }
 }

}
