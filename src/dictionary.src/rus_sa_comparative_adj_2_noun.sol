// -----------------------------------------------------------------------------
// File RUS_SA_COMPARATIVEADJ_2_NOUN.SOL
//
// (c) Koziev Elijah
//
// Content:
// Синтаксический анализатор: связь сравнительных прилагательных
// с существительными
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->23.06.1995
// LC->12.08.2009
// --------------

#include "aa_rules.inc"

#pragma floating off

automat aa
{
 operator Comparative2Noun_1 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее, ЧЕМ СОБАКА'
  if context {
              @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } )
			  _Запятая
			  СОЮЗ:ЧЕМ{}
			  СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ }
			 }
   then
    context { 0 .<ATTRIBUTE> 3 }
 }

 operator Comparative2Noun_2 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее, ЧЕМ ОДНА СОБАКА'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) _Запятая СОЮЗ:ЧЕМ{} ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } }
   then
    context { 0 .<ATTRIBUTE> 3 }
 }

 operator Comparative2Noun_3 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее, ЧЕМ 1 СОБАКА'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) _Запятая СОЮЗ:ЧЕМ{} NUMBER_ }
   then
    context { 0 .<ATTRIBUTE> 3 }
 }

 operator Comparative2Noun_4 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее, ЧЕМ ОНА'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) _Запятая СОЮЗ:ЧЕМ{} МЕСТОИМЕНИЕ:*{ ПАДЕЖ:ИМ } }
   then
    context { 0 .<ATTRIBUTE> 3 }
 }

 operator Comparative2Noun_20 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее ЧЕМ СОБАКА'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) СОЮЗ:ЧЕМ{} СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } }
   then
    context { 0 .<ATTRIBUTE> 2 }
 }

 operator Comparative2Noun_21 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее ЧЕМ ОДНА СОБАКА'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) СОЮЗ:ЧЕМ{} ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } }
   then
    context { 0 .<ATTRIBUTE> 2 }
 }

 operator Comparative2Noun_22 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее ЧЕМ 1 СОБАКА'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) СОЮЗ:ЧЕМ{} NUMBER_ }
   then
    context { 0 .<ATTRIBUTE> 2 }
 }

 operator Comparative2Noun_23 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее ЧЕМ ОНА'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) СОЮЗ:ЧЕМ{} МЕСТОИМЕНИЕ:*{ ПАДЕЖ:ИМ } }
   then
    context { 0 .<ATTRIBUTE> 2 }
 }

 operator Comparative2Noun_30 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее СОБАКИ'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД } }
   then
    context { 0 .<ATTRIBUTE> 1 }
 }

 operator Comparative2Noun_31 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее ОДНОЙ СОБАКИ'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД } }
   then
    context { 0 .<ATTRIBUTE> 1 }
 }

 operator Comparative2Noun_32 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее 1 СОБАКИ'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) NUMBER_ }
   then
    context { 0 .<ATTRIBUTE> 1 }
 }


 operator Comparative2Noun_33 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА сильнее МЕНЯ'
  if context { @or( ПРИЛАГАТЕЛЬНОЕ:* { СТЕПЕНЬ:СРАВН }, Наречие:* { СТЕПЕНЬ:СРАВН } ) МЕСТОИМЕНИЕ:*{ ПАДЕЖ:РОД } }
   then
    context { 0 .<ATTRIBUTE> 1 }
 }



 // Формально далее описываются не сравнительные формы прилагательных, но семантика у них
 // именно такая.

 operator Comparative2Noun_40 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАК ЖЕ СИЛЬНА, КАК СОБАКА'
  if context {
              СОЮЗ:ТАК ЖЕ{}
              @or( ПРИЛАГАТЕЛЬНОЕ:* { КРАТКИЙ СТЕПЕНЬ:АТРИБ }, НАРЕЧИЕ )
              _Запятая
              СОЮЗ:КАК{}
              СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ }
             }
   then
    context { 1 .<ATTRIBUTE_LIKE> 4 }
 }

 operator Comparative2Noun_41 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАК ЖЕ СИЛЬНА, КАК ОДНА СОБАКА'
  if context { СОЮЗ:ТАК ЖЕ{} @or( ПРИЛАГАТЕЛЬНОЕ:* { КРАТКИЙ СТЕПЕНЬ:АТРИБ }, НАРЕЧИЕ ) _Запятая СОЮЗ:КАК{} ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } }
   then
    context { 1 .<ATTRIBUTE_LIKE> 4 }
 }

 operator Comparative2Noun_42 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАК ЖЕ СИЛЬНА, КАК 1 СОБАКА'
  if context { СОЮЗ:ТАК ЖЕ{} @or( ПРИЛАГАТЕЛЬНОЕ:* { КРАТКИЙ СТЕПЕНЬ:АТРИБ }, НАРЕЧИЕ ) _Запятая СОЮЗ:КАК{} NUMBER_ }
   then
    context { 1 .<ATTRIBUTE_LIKE> 4 }
 }

 operator Comparative2Noun_43 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАК ЖЕ СИЛЬНА, КАК МЫ'
  if context { СОЮЗ:ТАК ЖЕ{} @or( ПРИЛАГАТЕЛЬНОЕ:* { КРАТКИЙ СТЕПЕНЬ:АТРИБ }, НАРЕЧИЕ ) _Запятая СОЮЗ:КАК{} МЕСТОИМЕНИЕ:*{ ПАДЕЖ:ИМ } }
   then
    context { 1 .<ATTRIBUTE_LIKE> 4 }
 }




 operator Comparative2Noun_50 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК СОБАКА'
  if context { ТАКАЯ ЖЕ ПРИЛАГАТЕЛЬНОЕ:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ } _Запятая СОЮЗ:КАК{} СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } }
     correlate { 0:РОД=2 0:ЧИСЛО=2 0:ПАДЕЖ=2 }
   then
    context { 2 .<ATTRIBUTE_LIKE> 5 }
 }

 operator Comparative2Noun_51 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК ОДНА СОБАКА'
  if context { ТАКАЯ ЖЕ ПРИЛАГАТЕЛЬНОЕ:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ } _Запятая СОЮЗ:КАК{} ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } }
     correlate { 0:РОД=2 0:ЧИСЛО=2 0:ПАДЕЖ=2 }
   then
    context { 2 .<ATTRIBUTE_LIKE> 5 }
 }

 operator Comparative2Noun_52 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК 1 СОБАКА'
  if context { ТАКАЯ ЖЕ ПРИЛАГАТЕЛЬНОЕ:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ } _Запятая СОЮЗ:КАК{} NUMBER_ }
     correlate { 0:РОД=2 0:ЧИСЛО=2 0:ПАДЕЖ=2 }
   then
    context { 2 .<ATTRIBUTE_LIKE> 5 }
 }

 operator Comparative2Noun_53 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК МЫ'
  if context { ТАКАЯ ЖЕ ПРИЛАГАТЕЛЬНОЕ:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ } _Запятая СОЮЗ:КАК{} МЕСТОИМЕНИЕ:*{ ПАДЕЖ:ИМ } }
     correlate { 0:РОД=2 0:ЧИСЛО=2 0:ПАДЕЖ=2 }
   then
    context { 2 .<ATTRIBUTE_LIKE> 5 }
 }




 operator Comparative2Noun_60 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И СОБАКА'
  if context { ТАКАЯ ЖЕ ПРИЛАГАТЕЛЬНОЕ:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ } _Запятая СОЮЗ:КАК{} СОЮЗ:И{} СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } }
     correlate { 0:РОД=2 0:ЧИСЛО=2 0:ПАДЕЖ=2 }
   then
    context { 2 .<ATTRIBUTE_LIKE> 6 }
 }

 operator Comparative2Noun_61 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И ОДНА СОБАКА'
  if context { ТАКАЯ ЖЕ ПРИЛАГАТЕЛЬНОЕ:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ } _Запятая СОЮЗ:КАК{} СОЮЗ:И{} ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } }
     correlate { 0:РОД=2 0:ЧИСЛО=2 0:ПАДЕЖ=2 }
   then
    context { 2 .<ATTRIBUTE_LIKE> 6 }
 }

 operator Comparative2Noun_62 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И 1 СОБАКА'
  if context { ТАКАЯ ЖЕ ПРИЛАГАТЕЛЬНОЕ:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ } _Запятая СОЮЗ:КАК{} СОЮЗ:И{} NUMBER_ }
     correlate { 0:РОД=2 0:ЧИСЛО=2 0:ПАДЕЖ=2 }
   then
    context { 2 .<ATTRIBUTE_LIKE> 6 }
 }

 operator Comparative2Noun_63 : LINK_COMPARATIVE_ADJ_2_NOUN
 {
  // 'КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И МЫ'
  if context { ТАКАЯ ЖЕ ПРИЛАГАТЕЛЬНОЕ:* { ~КРАТКИЙ СТЕПЕНЬ:АТРИБ } _Запятая СОЮЗ:КАК{} СОЮЗ:И{} МЕСТОИМЕНИЕ:*{ ПАДЕЖ:ИМ } }
     correlate { 0:РОД=2 0:ЧИСЛО=2 0:ПАДЕЖ=2 }
   then
    context { 2 .<ATTRIBUTE_LIKE> 6 }
 }

}

