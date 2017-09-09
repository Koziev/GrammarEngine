// -----------------------------------------------------------------------------
// File RUS_SA_COMPARATIVE_ADV.SOL
//
// (c) Koziev Elijah
//
// Content:
// Синтаксический анализатор: связь сравнительных наречий с глаголами
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->14.09.2008
// LC->11.08.2009
// --------------

#include "aa_rules.inc"

#pragma floating off

automat aa
{
 operator Comparative2Verb_1 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'бегает быстрее, ЧЕМ СОБАКА'
  if context {
              @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  _Запятая
			  СОЮЗ:ЧЕМ{}
			  СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ }
			 }
   then
    context { 0 .<ATTRIBUTE_EXC> 3 }
 }

 operator Comparative2Verb_2 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'бегает быстрее, ЧЕМ одна СОБАКА'
  if context {
              @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  _Запятая
			  СОЮЗ:ЧЕМ{}
			  ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ }
			 }
   then
    context { 0 .<ATTRIBUTE_EXC> 3 }
 }

 operator Comparative2Verb_3 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'бегает быстрее, ЧЕМ 1 СОБАКА'
  if context {
              @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  _Запятая
			  СОЮЗ:ЧЕМ{}
			  NUMBER_
			 }
   then
    context { 0 .<ATTRIBUTE_EXC> 3 }
 }


 operator Comparative2Verb_4 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'бегает быстрее, ЧЕМ она'
  if context {
              @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  _Запятая
			  СОЮЗ:ЧЕМ{}
			  МЕСТОИМЕНИЕ:*{ ПАДЕЖ:ИМ }
			 }
   then
    context { 0 .<ATTRIBUTE_EXC> 3 }
 }




 operator Comparative2Verb_10 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'бегает быстрее собаки'
  if context {
              @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД }
			 }
   then
    context { 0 .<ATTRIBUTE_EXC> 1 }
 }

 operator Comparative2Verb_11 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'бегает быстрее одной собаки'
  if context {
              @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:РОД }
			 }
   then
    context { 0 .<ATTRIBUTE_EXC> 1 }
 }

 operator Comparative2Verb_12 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'бегает быстрее 2 собак'
  if context { @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН}) NUMBER_ }
   then
    context { 0 .<ATTRIBUTE_EXC> 1 }
 }


 operator Comparative2Verb_13 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'бегает быстрее меня'
  if context { @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН}) МЕСТОИМЕНИЕ:*{ ПАДЕЖ:РОД } }
   then
    context { 0 .<ATTRIBUTE_EXC> 1 }
 }






 // Формально далее описываются не сравнительные формы наречий, но семантика у них именно такая.

 operator Comparative2Verb_40 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'КОШКА бегает так же быстро, КАК СОБАКА'
  if context {
              СОЮЗ:ТАК ЖЕ{}
			  @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  _Запятая СОЮЗ:КАК{}
			  СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ }
			 }
   then
    context { 1 .<ATTRIBUTE_LIKE> 4 }
 }

 operator Comparative2Verb_41 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'КОШКА бегает так же быстро, КАК одна СОБАКА'
  if context {
              СОЮЗ:ТАК ЖЕ{}
			  @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  _Запятая
			  СОЮЗ:КАК{}
			  ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ }
			 }
   then
    context { 1 .<ATTRIBUTE_LIKE> 4 }
 }

 operator Comparative2Verb_42 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'КОШКА бегает так же быстро, КАК 1 СОБАКА'
  if context {
              СОЮЗ:ТАК ЖЕ{}
			  @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  _Запятая
			  СОЮЗ:КАК{}
			  NUMBER_
			 }
   then
    context { 1 .<ATTRIBUTE_LIKE> 4 }
 }

 operator Comparative2Verb_43 : LINK_COMPARATIVE_ADV_2_VERB
 {
  // 'КОШКА бегает так же быстро, КАК мы'
  if context {
              СОЮЗ:ТАК ЖЕ{}
			  @or(НАРЕЧИЕ:*{ /*СТЕПЕНЬ:СРАВН*/ },ПРИЛАГАТЕЛЬНОЕ:*{СТЕПЕНЬ:СРАВН})
			  _Запятая
			  СОЮЗ:КАК{}
			  МЕСТОИМЕНИЕ:*{ ПАДЕЖ:ИМ }
			 }
   then
    context { 1 .<ATTRIBUTE_LIKE> 4 }
 }

}
