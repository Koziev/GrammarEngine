// -----------------------------------------------------------------------------
// File RUS_NOUNS_1067.SOL
//
// (c) Koziev Elijah
//
// Лексикон - определения имен существительных для русского языка.
//
// Русские существительные http://www.solarix.ru/for_developers/api/russian-noun-declension.shtml
// Особенности описания существительных http://www.solarix.ru/russian_grammar_dictionary/russian-noun-declension.shtml
// Словарные статьи http://www.solarix.ru/for_developers/docs/entries.shtml#words
//
// -----------------------------------------------------------------------------
//
// CD->30.04.2006
// LC->21.03.2011
// --------------

#include "sg_defs.h"

automat sg
{
 #define noun1067( Name ) entry Name :  СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_1067  }

 #define заглавн(Сущ) tag СУЩЕСТВИТЕЛЬНОЕ:Сущ { CharCasing:FirstCapitalized }

 // -------------------------------------------------------------

 entry КРИК : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }

 entry ТОК : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }

 entry ШОРОХ : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }

 entry ЛУК : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }

 entry СОК : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }

 entry ТРЕСК : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }


 entry ВОСТОРГ : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }


 entry ДУХ : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }

 entry МИГ : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }


 entry СРОК : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }


 entry СТРАХ : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }


 entry ПРОК :  СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }

 entry ВИЗГ : СУЩЕСТВИТЕЛЬНОЕ
 {
  paradigm Сущ_1067
 }

}

