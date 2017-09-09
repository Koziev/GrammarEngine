// -----------------------------------------------------------------------------
// File RUS_SA_PARTICIPLE_AND.SOL
//
// (c) Koziev Elijah
//
// Content:
// Для компилятора YGRES.
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->29.06.2003
// LC->08.01.2009
// --------------

#include "aa_rules.inc"

automat sg
{
 entry ПРИЧ_И : ПРИЧАСТИЕ
 {
  ВИД : СОВЕРШ

  СТЕПЕНЬ:АТРИБ
   КРАТКИЙ ЗАЛОГ:ДЕЙСТВ ВРЕМЯ:НАСТОЯЩЕЕ
   ПАДЕЖ:(ИМ) ЧИСЛО:ЕД РОД:МУЖ { ПРИЧ_И }
 }
}


#define _LOG_CLASS_    ПРИЧАСТИЕ
#define _LOG_CATEGORY_ AA_LINK_105

#include "rus_sa_base_and.sol"


automat aa
{
 operator AndParticiple_10 : AA_LINK_105_2
 {
  // 'зовущий и поющий'
  if context { ПРИЧАСТИЕ{}#a _And ПРИЧАСТИЕ{}#b }
     correlate { #a:ПАДЕЖ=#b }
   then
    context { _И.{ #a #b } }
 }

 operator AndParticiple_20 : AA_LINK_105_2
 {
  // 'зовущий, свистящий и поющий'
  if context { ПРИЧАСТИЕ{}#a _And ПРИЧАСТИЕ{}#b  _And ПРИЧАСТИЕ{}#c }
     correlate { #a:ПАДЕЖ=#b  #a:ПАДЕЖ=#c }
   then
    context { _И.{ #a #b #c } }
 }



 operator Tran_AndParticiple_10 : AA_LINK_105_3
 {
  if context { _И.{ ПРИЧАСТИЕ#a ПРИЧАСТИЕ#b } }
   then
    context {
             ПРИЧ_И :set {
                          ЧИСЛО=#a:ЧИСЛО
                          РОД=#a:РОД
                          ПАДЕЖ=#a:ПАДЕЖ
                          ВИД=#a:ВИД
                         }
              .{ <LOGIC_ITEM>#a <LOGIC_ITEM>#b }
            }
 }

 operator Tran_AndParticiple_20 : AA_LINK_105_3
 {
  if context { _И.{ ПРИЧАСТИЕ#a ПРИЧАСТИЕ#b ПРИЧАСТИЕ#c } }
   then
    context {
             ПРИЧ_И :set {
                          ЧИСЛО=#a:ЧИСЛО
                          РОД=#a:РОД
                          ПАДЕЖ=#a:ПАДЕЖ
                          ВИД=#a:ВИД
                         }
              .{ <LOGIC_ITEM>#a <LOGIC_ITEM>#b <LOGIC_ITEM>#c }
            }
 }


}


