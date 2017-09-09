// -----------------------------------------------------------------------------
// File RUS_SA_PRONOUN_BUT.SOL
//
// (c) Koziev Elijah
//
// Content:
// Русский Синтаксический анализатор - работа с местоимениями.
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->15.09.2008
// LC->10.08.2009
// --------------

#include "aa_rules.inc"


automat aa
{

 operator ButPronoun_10 : LINK_PRONOUN_BUT
 {
  // Я, НО НЕ ТЫ
  if context { МЕСТОИМЕНИЕ#a _Запятая СОЮЗ:НО{} МЕСТОИМЕНИЕ:*{НЕГАТИВ}#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context { #a.<BUT>convolution{ 3 center:#b:set НЕГАТИВ } }
 }

 operator ButPronoun_20 : LINK_PRONOUN_BUT
 {
  // Я, А НЕ ТЫ
  if context { МЕСТОИМЕНИЕ#a _Запятая СОЮЗ:А{} МЕСТОИМЕНИЕ:*{НЕГАТИВ}#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context { #a.<BUT>convolution{ 3 center:#b:set НЕГАТИВ } }
 }

 operator ButPronoun_30 : LINK_PRONOUN_BUT
 {
  // НЕ Я, А ТЫ
  if context { МЕСТОИМЕНИЕ:*{НЕГАТИВ}#a _Запятая СОЮЗ:А{} МЕСТОИМЕНИЕ#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context { convolution{ 0 center:#a:set НЕГАТИВ }.<BUT>#b }
 }

 operator ButPronoun_40 : LINK_PRONOUN_BUT
 {
  // НЕ Я, НО ТЫ
  if context { МЕСТОИМЕНИЕ:*{ НЕГАТИВ }#a _Запятая СОЮЗ:НО{} МЕСТОИМЕНИЕ#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context { convolution{ 0 center:#a:set НЕГАТИВ }.<BUT>#b }
 }

}
