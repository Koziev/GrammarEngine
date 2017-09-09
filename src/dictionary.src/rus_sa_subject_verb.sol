// -----------------------------------------------------------------------------
// File RUS_SA_SUBJECT_VERB.SOL
//
// (c) Koziev Elijah
//
// Content:
// Синтаксический анализатор: связь подлежащих со сказуемыми
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->13.08.2009
// --------------

#include "aa_rules.inc"


automat aa
{
 #pragma floating off


 // *********************************
 // **** ПРОШЕДШЕЕ/БУДУЩЕЕ ВРЕМЯ ****
 // *********************************

 operator SubjectVerb_10 : LINK_SUBJECT_VERB
 {
  // КУРТКА БЫЛА КРАСИВА
  // КОШКА БЫЛА ХИТРАЯ
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРЕДИКАТ:БЫТЬ{ ВРЕМЯ:ПРОШЕДШЕЕ }
              ПРИЛАГАТЕЛЬНОЕ{ /*КРАТКИЙ*/ ПАДЕЖ:ИМ }
             }
     correlate { РОД ЧИСЛО }
   then context { 0.<ATTRIBUTE>2.1  }
 }

 operator SubjectVerb_11 : LINK_SUBJECT_VERB
 {
  // ОДНА КУРТКА БЫЛА КРАСИВА
  // ОДНА КОШКА БЫЛА ХИТРАЯ
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРЕДИКАТ:БЫТЬ{ ВРЕМЯ:ПРОШЕДШЕЕ }
              ПРИЛАГАТЕЛЬНОЕ{ /*КРАТКИЙ*/ ПАДЕЖ:ИМ }
             }
     correlate { РОД }
   then context { 0.<ATTRIBUTE>2.1  }
 }


 operator SubjectVerb_20 : LINK_SUBJECT_VERB
 {
  // ОНА БЫЛА КРАСИВА
  // ОНА БЫЛА ХИТРАЯ
  if context {
              МЕСТОИМЕНИЕ:Я {ПАДЕЖ:ИМ}
              ПРЕДИКАТ:БЫТЬ{ ВРЕМЯ:ПРОШЕДШЕЕ }
              ПРИЛАГАТЕЛЬНОЕ{ /*КРАТКИЙ*/ ПАДЕЖ:ИМ }
             }
     correlate { РОД ЧИСЛО }
   then context { 0.<ATTRIBUTE>2.1  }
 }

 operator SubjectVerb_50 : LINK_SUBJECT_VERB
 {
  // БЫЛА КУРТКА КРАСИВА
  // БЫЛА КОШКА ХИТРАЯ
  if context {
              ПРЕДИКАТ:БЫТЬ{ ВРЕМЯ:ПРОШЕДШЕЕ }
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ /*КРАТКИЙ*/ ПАДЕЖ:ИМ }
             }
     correlate { РОД ЧИСЛО }
   then context { 1.<ATTRIBUTE>2.<TENSE_VERB>0  }
 }

 operator SubjectVerb_51 : LINK_SUBJECT_VERB
 {
  // БЫЛА ОДНА КУРТКА КРАСИВА
  // БЫЛА ОДНА КОШКА ХИТРАЯ
  if context {
              ПРЕДИКАТ:БЫТЬ{ ВРЕМЯ:ПРОШЕДШЕЕ }
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ /*КРАТКИЙ*/ ПАДЕЖ:ИМ }
             }
     correlate { РОД ЧИСЛО }
   then context { 1.<ATTRIBUTE>2.<TENSE_VERB>0  }
 }

 operator SubjectVerb_60 : LINK_SUBJECT_VERB
 {
  // БЫЛА ОНА КРАСИВА
  // БЫЛА ОНА ХИТРАЯ
  if context {
              ПРЕДИКАТ:БЫТЬ{ ВРЕМЯ:ПРОШЕДШЕЕ }
              МЕСТОИМЕНИЕ:Я{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ /*КРАТКИЙ*/ ПАДЕЖ:ИМ }
             }
     correlate { РОД ЧИСЛО }
   then context { 1.<ATTRIBUTE>2.<TENSE_VERB>0  }
 }


 operator SubjectVerb_70 : LINK_SUBJECT_VERB
 {
  // КОШКА БЫЛА БЕЛОЙ
  // КОШКА СТАЛА БЕЛОЙ
  // КОШКА ОКАЗАЛАСЬ БЕЛОЙ 
  // СОБАКА БЫВАЛА КУСАЧЕЙ
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРЕДИКАТ:*{ ВРЕМЯ:ПРОШЕДШЕЕ }
              ПРИЛАГАТЕЛЬНОЕ{ /*~КРАТКИЙ*/ ПАДЕЖ:ТВОР }
             }
     correlate { РОД ЧИСЛО }
   then context { 0.<ATTRIBUTE>2 : set ПАДЕЖ:ИМ . 1 }
 }

 operator SubjectVerb_71 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА БЫЛА БЕЛОЙ
  // ОДНА КОШКА СТАЛА БЕЛОЙ
  // ОДНА КОШКА ОКАЗАЛАСЬ БЕЛОЙ 
  // ОДНА СОБАКА БЫВАЛА КУСАЧЕЙ
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРЕДИКАТ:*{ ВРЕМЯ:ПРОШЕДШЕЕ }
              ПРИЛАГАТЕЛЬНОЕ{ /*~КРАТКИЙ*/ ПАДЕЖ:ТВОР }
             }
     correlate { РОД ЧИСЛО }
   then context { 0.<ATTRIBUTE>2 : set ПАДЕЖ:ИМ . 1 }
 }

 operator SubjectVerb_80 : LINK_SUBJECT_VERB
 {
  // ОНА БЫЛА БЕЛОЙ
  // ОНА СТАЛА БЕЛОЙ
  // ОНА ОКАЗАЛАСЬ БЕЛОЙ 
  if context {
              МЕСТОИМЕНИЕ:Я{ПАДЕЖ:ИМ}
              ПРЕДИКАТ:*{ ВРЕМЯ:ПРОШЕДШЕЕ }
              ПРИЛАГАТЕЛЬНОЕ{ /*~КРАТКИЙ*/ ПАДЕЖ:ТВОР }
             }
     correlate { РОД ЧИСЛО }
   then context { 0.<ATTRIBUTE>2 : set ПАДЕЖ:ИМ . 1 }
 }



 operator SubjectVerb_110 : LINK_SUBJECT_VERB
 {
  // БЫЛА КОШКА БЕЛОЙ
  // СТАЛА КОШКА БЕЛОЙ
  // ОКАЗАЛАСЬ КОШКА БЕЛОЙ 
  if context {
              ПРЕДИКАТ:*{ ВРЕМЯ:ПРОШЕДШЕЕ }
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ /*~КРАТКИЙ*/ ПАДЕЖ:ТВОР }
             }
     correlate { РОД ЧИСЛО }
   then context { 1.<ATTRIBUTE>2 : set ПАДЕЖ:ИМ .<TENSE_VERB> 0 }
 }

 operator SubjectVerb_111 : LINK_SUBJECT_VERB
 {
  // БЫЛА ОДНА КОШКА БЕЛОЙ
  // СТАЛА ОДНА КОШКА БЕЛОЙ
  // ОКАЗАЛАСЬ КОШКА БЕЛОЙ 
  if context {
              ПРЕДИКАТ:*{ ВРЕМЯ:ПРОШЕДШЕЕ }
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ /*~КРАТКИЙ*/ ПАДЕЖ:ТВОР }
             }
     correlate { РОД ЧИСЛО }
   then context { 1.<ATTRIBUTE>2 : set ПАДЕЖ:ИМ .<TENSE_VERB> 0 }
 }


 operator SubjectVerb_120 : LINK_SUBJECT_VERB
 {
  // БЫЛА ОНА БЕЛОЙ
  // СТАЛА ОНА БЕЛОЙ
  // ОКАЗАЛАСЬ ОНА БЕЛОЙ 
  if context {
              ПРЕДИКАТ:*{ ВРЕМЯ:ПРОШЕДШЕЕ }
              МЕСТОИМЕНИЕ:Я{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ /*~КРАТКИЙ*/ ПАДЕЖ:ТВОР }
             }
     correlate { РОД ЧИСЛО }
   then context { 1.<ATTRIBUTE>2 : set ПАДЕЖ:ИМ .<TENSE_VERB> 0 }
 }






 // ************************* 
 // **** НАСТОЯЩЕЕ ВРЕМЯ ****
 // ************************* 

 operator SubjectVerb_200 : LINK_SUBJECT_VERB
 {
  // КОШКА СИЛЬНЕЕ СОБАКИ
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ  { СТЕПЕНЬ:СРАВН }
             }
   then context { 0.<ATTRIBUTE>1 /*: set ПАДЕЖ:ИМ*/ }
 }

 operator SubjectVerb_201 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА СИЛЬНЕЕ СОБАКИ
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ  { СТЕПЕНЬ:СРАВН }
             }
   then context { 0.<ATTRIBUTE>1 /*: set ПАДЕЖ:ИМ*/ }
 }


 operator SubjectVerb_210 : LINK_SUBJECT_VERB
 {
  // ОНА СИЛЬНЕЕ СОБАКИ
  if context {
              МЕСТОИМЕНИЕ:Я { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ  { СТЕПЕНЬ:СРАВН }
             }
   then context { 0.<ATTRIBUTE>1 /*: set ПАДЕЖ:ИМ*/ }
 }



 operator SubjectVerb_310 : LINK_SUBJECT_VERB
 {
  // КОШКА - БЕЛАЯ.
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              _Дефис
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _КОН
             }
     correlate { 0:РОД=2 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 3 }
 }

 operator SubjectVerb_311 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА - БЕЛАЯ.
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              _Дефис
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _КОН
             }
     correlate { 0:РОД=2 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 3 }
 }

 operator SubjectVerb_320 : LINK_SUBJECT_VERB
 {
  // ОНА - БЕЛАЯ.
  if context {
              МЕСТОИМЕНИЕ:Я {ПАДЕЖ:ИМ}
              _Дефис
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _КОН
             }
     correlate { 0:РОД=2 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 3 }
 }

 operator SubjectVerb_322 : LINK_SUBJECT_VERB
 {
  // КТО-ТО - БЕЛЫЙ.
  if context {
              МЕСТОИМ_СУЩ:* {ПАДЕЖ:ИМ}
              _Дефис
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _КОН
             }
     correlate { 0:РОД=2 }
   then context { 0.<ATTRIBUTE>2 3 }
 }

 operator SubjectVerb_330 : LINK_SUBJECT_VERB
 {
  // КОШКА - БЕЛАЯ, ...
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              _Дефис
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _Запятая
             }
     correlate { 0:РОД=2 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 3 }
 }

 operator SubjectVerb_331 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА - БЕЛАЯ, ...
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              _Дефис
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _Запятая
             }
     correlate { 0:РОД=2 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 3 }
 }

 operator SubjectVerb_340 : LINK_SUBJECT_VERB
 {
  // ОНА - БЕЛАЯ, ...
  if context {
              МЕСТОИМЕНИЕ:Я {ПАДЕЖ:ИМ}
              _Дефис
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _Запятая
             }
     correlate { 0:РОД=2 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 3 }
 }

 operator SubjectVerb_342 : LINK_SUBJECT_VERB
 {
  // КТО-ТО - БЕЛЫЙ, ...
  if context {
              МЕСТОИМ_СУЩ:* {ПАДЕЖ:ИМ }
              _Дефис
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _Запятая
             }
     correlate { 0:РОД=2 }
   then context { 0.<ATTRIBUTE>2 3 }
 }

 operator SubjectVerb_350 : LINK_SUBJECT_VERB
 {
  // КОШКА БЕЛАЯ.
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _КОН
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }

 operator SubjectVerb_351 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА БЕЛАЯ.
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _КОН
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }

 operator SubjectVerb_360 : LINK_SUBJECT_VERB
 {
  // ОНА БЕЛАЯ.
  if context {
              МЕСТОИМЕНИЕ:Я {ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _КОН
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }

 operator SubjectVerb_362 : LINK_SUBJECT_VERB
 {
  // КТО-ТО БЕЛЫЙ.
  if context {
              МЕСТОИМ_СУЩ:* {ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _КОН
             }
     correlate { 0:РОД=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }

 operator SubjectVerb_370 : LINK_SUBJECT_VERB
 {
  // КОШКА БЕЛАЯ, ...
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _Запятая
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }

 operator SubjectVerb_371 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА БЕЛАЯ, ...
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _Запятая
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }


 operator SubjectVerb_372 : LINK_SUBJECT_VERB
 {
  // КОШКА БЕЛАЯ ПОСТОЛЬКУ, ПОСКОЛЬКУ ...
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              СОЮЗ:ПОСТОЛЬКУ,ПОСКОЛЬКУ{}
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }

 operator SubjectVerb_373 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА БЕЛАЯ ПОСТОЛЬКУ, ПОСКОЛЬКУ ...
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              СОЮЗ:ПОСТОЛЬКУ,ПОСКОЛЬКУ{}
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }


 operator SubjectVerb_380 : LINK_SUBJECT_VERB
 {
  // ОНА БЕЛАЯ ПОСТОЛЬКУ, ПОСКОЛЬКУ
  if context {
              МЕСТОИМЕНИЕ:Я {ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              СОЮЗ:ПОСТОЛЬКУ,ПОСКОЛЬКУ{}
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }


 operator SubjectVerb_381 : LINK_SUBJECT_VERB
 {
  // ОНА БЕЛАЯ, ...
  if context {
              МЕСТОИМЕНИЕ:Я {ПАДЕЖ:ИМ}
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _Запятая
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }


 operator SubjectVerb_382 : LINK_SUBJECT_VERB
 {
  // КТО-ТО БЕЛЫЙ, ...
  if context {
              МЕСТОИМ_СУЩ:* {ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              _Запятая
             }
     correlate { 0:РОД=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }

 operator SubjectVerb_383 : LINK_SUBJECT_VERB
 {
  // КТО-ТО БЕЛЫЙ ПОСТОЛЬКУ, ПОСКОЛЬКУ
  if context {
              МЕСТОИМ_СУЩ:* {ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ{ ПАДЕЖ:ИМ }
              СОЮЗ:ПОСТОЛЬКУ,ПОСКОЛЬКУ{}
             }
     correlate { 0:РОД=1 }
   then context { 0.<ATTRIBUTE>1 2 }
 }



 // ********************************************
 //          <X> ТАКОЙ ЖЕ КАК <Y>
 // ********************************************

 operator SubjectVerb_500 : LINK_SUBJECT_VERB
 {
  // КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК СОБАКА.
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1.{ 2 5 } }
 }

 operator SubjectVerb_501 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК СОБАКА.
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1.{ 2 5 } }
 }

 operator SubjectVerb_502 : LINK_SUBJECT_VERB
 {
  // КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК ОДНА СОБАКА.
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1.{ 2 5 } }
 }

 operator SubjectVerb_503 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК ОДНА СОБАКА.
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1.{ 2 5 } }
 }

 operator SubjectVerb_510 : LINK_SUBJECT_VERB
 {
  // ОНА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК СОБАКА.
  if context {
              МЕСТОИМЕНИЕ:Я { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1.{ 2 5 } }
 }

 operator SubjectVerb_511 : LINK_SUBJECT_VERB
 {
  // ОНА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК ОДНА СОБАКА.
  if context {
              МЕСТОИМЕНИЕ:Я { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1.{ 2 5 } }
 }

 operator SubjectVerb_520 : LINK_SUBJECT_VERB
 {
  // КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК МЫ.
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              МЕСТОИМЕНИЕ:Я { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1.{ 2 5 } }
 }

 operator SubjectVerb_521 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК МЫ.
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              МЕСТОИМЕНИЕ:Я { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1.{ 2 5 } }
 }


 operator SubjectVerb_530 : LINK_SUBJECT_VERB
 {
  // КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И СОБАКА.
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СОЮЗ:И{} 
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1. { 2 6 } }
 }

 operator SubjectVerb_531 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И СОБАКА.
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СОЮЗ:И{} 
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1. { 2 6 } }
 }

 operator SubjectVerb_532 : LINK_SUBJECT_VERB
 {
  // КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И ДВЕ СОБАКИ.
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СОЮЗ:И{} 
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1. { 2 6 } }
 }

 operator SubjectVerb_533 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И ОДНА СОБАКА.
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СОЮЗ:И{} 
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1. { 2 6 } }
 }

 operator SubjectVerb_540 : LINK_SUBJECT_VERB
 {
  // ОНА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И СОБАКА.
  if context {
              МЕСТОИМЕНИЕ:Я { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СОЮЗ:И{} 
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1. { 2 6 } }
 }

 operator SubjectVerb_541 : LINK_SUBJECT_VERB
 {
  // ОНА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И ОДНА СОБАКА.
  if context {
              МЕСТОИМЕНИЕ:Я { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СОЮЗ:И{} 
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1. { 2 6 } }
 }


 operator SubjectVerb_550 : LINK_SUBJECT_VERB
 {
  // КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И ОН.
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СОЮЗ:И{} 
              МЕСТОИМЕНИЕ:Я { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1. { 2 6 } }
 }

 operator SubjectVerb_551 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА ТАКАЯ ЖЕ СИЛЬНАЯ, КАК И ОН.
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ:ТАКОЙ { ПАДЕЖ:ИМ }
              ПРИЛАГАТЕЛЬНОЕ
              _Запятая
              СОЮЗ:КАК{}  
              СОЮЗ:И{} 
              МЕСТОИМЕНИЕ:Я { ПАДЕЖ:ИМ }
             }
     correlate { 0:РОД=1 0:ЧИСЛО=1 }
   then context { 0.<ATTRIBUTE>1. { 2 6 } }
 }



 // **************************************************************


 operator SubjectVerb_1400 : LINK_SUBJECT_VERB
 {
  // 'СВИНЬЯ МОЛЧАЛА'
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ } #b
             }
     correlate { РОД }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }

 operator SubjectVerb_1401 : LINK_SUBJECT_VERB
 {
  // 'ОДНА СВИНЬЯ МОЛЧАЛА'
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ } #b
             }
     correlate { РОД }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }


 operator SubjectVerb_1420 : LINK_SUBJECT_VERB
 {
  // 'СВИНЬЯ ЗАМОЛЧИТ'
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 } #b
             }
     correlate { ЧИСЛО }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }

 operator SubjectVerb_1421 : LINK_SUBJECT_VERB
 {
  // 'ОДНА СВИНЬЯ ЗАМОЛЧИТ'
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 } #b
             }
     correlate { ЧИСЛО }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }



 operator SubjectVerb_1430 : LINK_SUBJECT_VERB
 {
  // 'СВИНЬЯ МОЛЧИТ'
  if context {
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 } #b
             }
     correlate { ЧИСЛО }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }

 operator SubjectVerb_1431 : LINK_SUBJECT_VERB
 {
  // 'ОДНА СВИНЬЯ МОЛЧИТ'
  if context {
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 } #b
             }
     correlate { ЧИСЛО }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }


 operator SubjectVerb_1440 : LINK_SUBJECT_VERB
 {
  // 'МОЛЧАЛА СВИНЬЯ'
  if context {
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ } #b
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ  }  #a
             }
     correlate { РОД ЧИСЛО }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }

 operator SubjectVerb_1441 : LINK_SUBJECT_VERB
 {
  // 'МОЛЧАЛА ОДНА СВИНЬЯ'
  if context {
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ } #b
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ  }  #a
             }
     correlate { РОД ЧИСЛО }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }


 operator SubjectVerb_1460 : LINK_SUBJECT_VERB
 {
  // 'ЗАМОЛЧИТ СВИНЬЯ'
  if context {
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 } #b
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
             }
     correlate { ЧИСЛО }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }

 operator SubjectVerb_1461 : LINK_SUBJECT_VERB
 {
  // 'ЗАМОЛЧИТ ОДНА СВИНЬЯ'
  if context {
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 } #b
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
             }
     correlate { ЧИСЛО }
   then context { <ATTRIBUTE>#b.<SUBJECT>#a }
 }

 operator SubjectVerb_1470 : LINK_SUBJECT_VERB
 {
  // 'МОЛЧИТ СВИНЬЯ'
  if context {
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 } #b
              СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
             }
     correlate { ЧИСЛО }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_1471 : LINK_SUBJECT_VERB
 {
  // 'МОЛЧИТ ОДНА СВИНЬЯ'
  if context {
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 } #b
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ }  #a
             }
     correlate { ЧИСЛО }
   then context { #b.<SUBJECT>#a }
 }



 operator SubjectVerb_1480 : LINK_SUBJECT_VERB
 {
  // 'ОНА УМЕРЛА'
  if context {
              МЕСТОИМЕНИЕ { ПАДЕЖ:ИМ }                       #a
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ }  #b
             }
     correlate { РОД ЧИСЛО }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_1490 : LINK_SUBJECT_VERB
 {
  // 'ОНА УМРЕТ'
  if context {
              МЕСТОИМЕНИЕ { ПАДЕЖ:ИМ }                     #a
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ }  #b
             }
     correlate { ЛИЦО ЧИСЛО }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_1500 : LINK_SUBJECT_VERB
 {
  // 'ОНА УМИРАЕТ'
  if context {
              МЕСТОИМЕНИЕ { ПАДЕЖ:ИМ }                       #a
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ }  #b
             }
     correlate { ЛИЦО ЧИСЛО }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_1510 : LINK_SUBJECT_VERB
 {
  // 'УМЕРЛА ОНА'
  if context {
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ }  #b
              МЕСТОИМЕНИЕ { ПАДЕЖ:ИМ }                       #a
             }
     correlate { РОД ЧИСЛО }
   then context { #b.<SUBJECT>#a }
 }


 operator SubjectVerb_1520 : LINK_SUBJECT_VERB
 {
  // 'УМРЕТ ОНА'
  if context {
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ }  #b
              МЕСТОИМЕНИЕ { ПАДЕЖ:ИМ }                     #a
             }
     correlate { ЛИЦО ЧИСЛО }
   then context { #b.<SUBJECT>#a }
 }



 operator SubjectVerb_1530 : LINK_SUBJECT_VERB
 {
  // 'УМИРАЕТ ОНА'
  if context {
              ПРЕДИКАТ { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ }  #b
              МЕСТОИМЕНИЕ { ПАДЕЖ:ИМ }                       #a
             }
     correlate { ЛИЦО ЧИСЛО }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_1600 : LINK_SUBJECT_VERB
 {
  // 'НЕКТО УМРЕТ'
  if context {
              МЕСТОИМ_СУЩ:*{ падеж:им } #a
              ПРЕДИКАТ { ЧИСЛО:ЕД НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 } #b
             }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_1602 : LINK_SUBJECT_VERB
 {
  // 'НЕКТО УМЕР'
  if context {
              МЕСТОИМ_СУЩ:*{ падеж:им } #a
              ПРЕДИКАТ { ЧИСЛО:ЕД НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:МУЖ } #b
             }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_1604 : LINK_SUBJECT_VERB
 {
  // 'НЕКТО УМИРАЕТ'
  if context {
              МЕСТОИМ_СУЩ:*{ падеж:им } #a
              ПРЕДИКАТ { ЧИСЛО:ЕД НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 } #b
             }
   then context { #b.<SUBJECT>#a }
 }


 operator SubjectVerb_1610 : LINK_SUBJECT_VERB
 {
  // 'УМРЕТ НЕКТО'
  if context {
              ПРЕДИКАТ { ЧИСЛО:ЕД НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 } #b
              МЕСТОИМ_СУЩ:*{ падеж:им } #a
             }
   then context { #b.<SUBJECT>#a }
 }


 operator SubjectVerb_1614 : LINK_SUBJECT_VERB
 {
  // 'УМЕР НЕКТО'
  if context {
              ПРЕДИКАТ { ЧИСЛО:ЕД НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ РОД:МУЖ } #b
              МЕСТОИМ_СУЩ:*{ падеж:им } #a
             }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_1618 : LINK_SUBJECT_VERB
 {
  // 'УМИРАЕТ НЕКТО'
  if context {
              ПРЕДИКАТ { ЧИСЛО:ЕД НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 } #b
              МЕСТОИМ_СУЩ:*{ падеж:им } #a
             }
   then context { #b.<SUBJECT>#a }
 }

 // "у него есть пистолет" --> "он имеет пистолет"
 operator SubjectVerb_1620 : LINK_SUBJECT_VERB
 {
  if   context {
                ПРЕДЛОГ:У{}
                МЕСТОИМЕНИЕ:Я { ПАДЕЖ:РОД }            #a
                ПРЕДИКАТ:БЫТЬ { ЛИЦО:3 ЧИСЛО:ЕД }      #b
                СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ВИН }         #c
               }
  then context {
                ПРЕДИКАТ:ИМЕТЬ { ЛИЦО:1 ЧИСЛО:ЕД ВРЕМЯ:НАСТОЯЩЕЕ } : set { ЛИЦО=#a:ЛИЦО ЧИСЛО=#a:ЧИСЛО ВРЕМЯ=#b:ВРЕМЯ }
                .{
                  <SUBJECT>#a /*:set { ПАДЕЖ:ИМ }*/
                  <OBJECT>#c
                 }
               }
 }



 // ЭТО БЫЛА ТВОЯ ИГРУШКА
 operator SubjectVerb_1630 : LINK_SUBJECT_VERB
 {
  if   context {
                МЕСТОИМ_СУЩ:ЭТО{ Падеж:Им } #a
                ПРЕДИКАТ:БЫТЬ { }             #b
                СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } #c
               }
       correlate { 1:ЧИСЛО=2 1:РОД=2 }
  then context { #b.{ <SUBJECT>#a <OBJECT>#c } }
 }

 operator SubjectVerb_1631 : LINK_SUBJECT_VERB
 {
  if   context {
                МЕСТОИМ_СУЩ:ЭТО{ Падеж:Им } #a
                ПРЕДИКАТ:БЫТЬ { } #b
                ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } #c
               }
       correlate { 1:ЧИСЛО=2 1:РОД=2 }
  then context { #b.{ <SUBJECT>#a <OBJECT>#c } }
 }


 // БЫЛА ЛИ ЭТО ТВОЯ ИГРУШКА
 operator SubjectVerb_1632 : LINK_SUBJECT_VERB
 {
  if   context {
                ПРЕДИКАТ:БЫТЬ { }             #b
//                ЧАСТИЦА:ЛИ{}
                МЕСТОИМ_СУЩ:ЭТО{ Падеж:Им } #a
                СУЩЕСТВИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } #c
               }
       correlate { 0:ЧИСЛО=2 0:РОД=2 }
  then context { #b.{ <SUBJECT>#a <OBJECT>#c } }
 }

 operator SubjectVerb_1633 : LINK_SUBJECT_VERB
 {
  if   context {
                ПРЕДИКАТ:БЫТЬ { }             #b
//                ЧАСТИЦА:ЛИ{}
                МЕСТОИМ_СУЩ:ЭТО{ Падеж:Им }#a
                ЧИСЛИТЕЛЬНОЕ:*{ ПАДЕЖ:ИМ } #c
               }
       correlate { 0:ЧИСЛО=2 0:РОД=2 }
  then context { #b.{ <SUBJECT>#a <OBJECT>#c } }
 }

 // ****************************************************************************
 // Далее идут конструкции, которые обычно встречаются в вопросах.
 // ****************************************************************************

 operator SubjectVerb_2000 : LINK_SUBJECT_VERB
 {
  // КТО ЕСТЬ ЧЕЛОВЕК?
  if context {
              МЕСТОИМ_СУЩ{ПАДЕЖ:ИМ}#a
              ПРЕДИКАТ:БЫТЬ{ ВРЕМЯ:НАСТОЯЩЕЕ НАКЛОНЕНИЕ:ИЗЪЯВ } #c
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2010 : LINK_SUBJECT_VERB
 {
  // КТО БЫЛ ЧЕЛОВЕКОМ?
  // КТО БУДЕТ ЧЕЛОВЕКОМ?
  if context {
              МЕСТОИМ_СУЩ{ПАДЕЖ:ИМ}#a
              ПРЕДИКАТ:БЫТЬ{ НАКЛОНЕНИЕ:ИЗЪЯВ } #c
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ТВОР}#b
             }
   then context { #a.<ATTRIBUTE>#b:set {ПАДЕЖ:ИМ} }
 }


 operator SubjectVerb_2020 : LINK_SUBJECT_VERB
 {
  // КТО - ЧЕЛОВЕК?
  if context {
              МЕСТОИМ_СУЩ{ПАДЕЖ:ИМ}#a
              _Дефис
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2030 : LINK_SUBJECT_VERB
 {
  // ЧЕЛОВЕК - ЭТО КТО?
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
              _Дефис
              МЕСТОИМ_СУЩ:ЭТО{ПАДЕЖ:ИМ}
              МЕСТОИМ_СУЩ{ПАДЕЖ:ИМ}#a
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2031 : LINK_SUBJECT_VERB
 {
  // ДВА ДРУГА - ЭТО КТО?
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
              _Дефис
              МЕСТОИМ_СУЩ:ЭТО{ПАДЕЖ:ИМ}
              МЕСТОИМ_СУЩ{ПАДЕЖ:ИМ}#a
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2040 : LINK_SUBJECT_VERB
 {
  // ЧЕЛОВЕК - КТО ЭТО?
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
              _Дефис
              МЕСТОИМ_СУЩ{ПАДЕЖ:ИМ}#a
              МЕСТОИМ_СУЩ:ЭТО{ПАДЕЖ:ИМ}
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2041 : LINK_SUBJECT_VERB
 {
  // ДВА ДРУГА - КТО ЭТО?
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
              _Дефис
              МЕСТОИМ_СУЩ{ПАДЕЖ:ИМ}#a
              МЕСТОИМ_СУЩ:ЭТО{ПАДЕЖ:ИМ}
             }
   then context { #a.<ATTRIBUTE>#b }
 }




 operator SubjectVerb_2110 : LINK_SUBJECT_VERB
 {
  // КТО ЧЕЛОВЕК?
  if context { МЕСТОИМ_СУЩ:КТО{ПАДЕЖ:ИМ} СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b }
   then context { 0.<ATTRIBUTE>#b }
 }



 operator SubjectVerb_2130 : LINK_SUBJECT_VERB
 {
  // КТО МОЖЕТ БЫТЬ ЧЕЛОВЕКОМ?
  if context {
              МЕСТОИМ_СУЩ:КТО{ПАДЕЖ:ИМ}
              МОЖЕТ
              ИНФИНИТИВ:БЫТЬ{}
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ТВОР}#b
             }
   then context { 0.<ATTRIBUTE>#b:set{ПАДЕЖ:ИМ} }
 }

 operator SubjectVerb_2131 : LINK_SUBJECT_VERB
 {
  // КТО МОЖЕТ БЫТЬ ОДНИМ ЧЕЛОВЕКОМ?
  if context {
              МЕСТОИМ_СУЩ:КТО{ПАДЕЖ:ИМ}
              МОЖЕТ
              ИНФИНИТИВ:БЫТЬ{}
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ТВОР}#b
             }
   then context { 0.<ATTRIBUTE>#b:set{ПАДЕЖ:ИМ} }
 }

 operator SubjectVerb_2152 : LINK_SUBJECT_VERB
 {
  // НЕКТО - ЧЕЛОВЕК.
  if context {
              МЕСТОИМ_СУЩ{ПАДЕЖ:ИМ}#a
              _Дефис
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2160 : LINK_SUBJECT_VERB
 {
  // КОШКА - ЗВЕРЬ
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
              _Дефис
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2161 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА - ЗВЕРЬ
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
              _Дефис
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2162 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА - ОДИН ЗВЕРЬ
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
              _Дефис
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2170 : LINK_SUBJECT_VERB
 {
  // КОШКА - ЭТО ЗВЕРЬ
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
               _Дефис
              МЕСТОИМ_СУЩ:ЭТО{ПАДЕЖ:ИМ}
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2171 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА - ЭТО ЗВЕРЬ
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
               _Дефис
              МЕСТОИМ_СУЩ:ЭТО{ПАДЕЖ:ИМ}
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2172 : LINK_SUBJECT_VERB
 {
  // КОШКА - ЭТО ОДИН ЗВЕРЬ
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
               _Дефис
              МЕСТОИМ_СУЩ:ЭТО{ПАДЕЖ:ИМ}
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }


 operator SubjectVerb_2173 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА - ЭТО ОДИН ЗВЕРЬ
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
               _Дефис
              МЕСТОИМ_СУЩ:ЭТО{ПАДЕЖ:ИМ}
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2174 : LINK_SUBJECT_VERB
 {
  // КОШКА - ЗВЕРЬ
  if context { СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ } _Дефис СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ } }
     correlate { 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 }
 }

 operator SubjectVerb_2175 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА - ЗВЕРЬ
  if context { ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ } _Дефис СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ } }
     correlate { 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 }
 }

 operator SubjectVerb_2176 : LINK_SUBJECT_VERB
 {
  // КОШКА - ОДИН ЗВЕРЬ
  if context { СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ } _Дефис ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ } }
     correlate { 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 }
 }

 operator SubjectVerb_2177 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА - ОДИН ЗВЕРЬ
  if context { ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ } _Дефис ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ } }
     correlate { 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 }
 }


 operator SubjectVerb_2178 : LINK_SUBJECT_VERB
 {
  // КОШКА ЭТО ЗВЕРЬ
  if context { СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ } МЕСТОИМ_СУЩ:ЭТО{ Падеж:Им } СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ } }
     correlate { 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 }
 }

 operator SubjectVerb_2179 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА ЭТО ЗВЕРЬ
  if context { ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ } МЕСТОИМ_СУЩ:ЭТО{ Падеж:Им } СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ } }
     correlate { 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 }
 }

 operator SubjectVerb_2180 : LINK_SUBJECT_VERB
 {
  // КОШКА ЭТО ОДИН ЗВЕРЬ
  if context { СУЩЕСТВИТЕЛЬНОЕ { ПАДЕЖ:ИМ } МЕСТОИМ_СУЩ:ЭТО{ Падеж:Им } ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ } }
     correlate { 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 }
 }

 operator SubjectVerb_2181 : LINK_SUBJECT_VERB
 {
  // ОДНА КОШКА ЭТО ОДИН ЗВЕРЬ
  if context { ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ } МЕСТОИМ_СУЩ:ЭТО{ Падеж:Им } ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:ИМ } }
     correlate { 0:ЧИСЛО=2 }
   then context { 0.<ATTRIBUTE>2 }
 }



 operator SubjectVerb_2182 : LINK_SUBJECT_VERB
 {
  // ЗВЕРЬ ЛИ КОШКА
    if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
              ЧАСТИЦА:ЛИ{}
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2183 : LINK_SUBJECT_VERB
 {
  // ОДИН ЗВЕРЬ ЛИ КОШКА
    if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
              ЧАСТИЦА:ЛИ{}
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
             }
   then context { #a.<ATTRIBUTE>#b }
 }

 operator SubjectVerb_2184 : LINK_SUBJECT_VERB
 {
  // ЗВЕРЬ ЛИ ОДНА КОШКА
    if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
              ЧАСТИЦА:ЛИ{}
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#a
             }
   then context { #a.<ATTRIBUTE>#b }
 }


 operator SubjectVerb_3000 : LINK_SUBJECT_VERB
 {
  // КОТУ НАДО СПАТЬ
  if context {
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ДАТ}#a
              БЕЗЛИЧ_ГЛАГОЛ{}#b
             }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_3010 : LINK_SUBJECT_VERB
 {
  // ОДНОМУ КОТУ НАДО СПАТЬ
  if context {
              ЧИСЛИТЕЛЬНОЕ{ПАДЕЖ:ДАТ}#a
              БЕЗЛИЧ_ГЛАГОЛ{}#b
             }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_3020 : LINK_SUBJECT_VERB
 {
  // ЕМУ НАДО СПАТЬ
  if context {
              МЕСТОИМЕНИЕ{ПАДЕЖ:ДАТ}#a
              БЕЗЛИЧ_ГЛАГОЛ{}#b
             }
   then context { #b.<SUBJECT>#a }
 }




 operator SubjectVerb_3030 : LINK_SUBJECT_VERB
 {
  // БЫЛО ВЫПИТО МНОГО ВИНА
  if context {
              ГЛАГОЛ:БЫТЬ { ВРЕМЯ:ПРОШЕДШЕЕ РОД:СР }
              ПРИЛАГАТЕЛЬНОЕ:* { ПРИЧАСТИЕ СТРАД КРАТКИЙ РОД:СР }
              СУЩЕСТВИТЕЛЬНОЕ:* { ПАДЕЖ:РОД }
             }
     correlate { ЧИСЛО }
   then context { 2.<ATTRIBUTE>1.0  }
 }

 operator SubjectVerb_3040 : LINK_SUBJECT_VERB
 {
  // БЫЛО СЪЕДЕНО ДВА КИЛОГРАММА САЛА
  if context {
              ГЛАГОЛ:БЫТЬ { ВРЕМЯ:ПРОШЕДШЕЕ РОД:СР }
              ПРИЛАГАТЕЛЬНОЕ:* { ПРИЧАСТИЕ СТРАД КРАТКИЙ РОД:СР }
              ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:РОД }
             }
     correlate { ЧИСЛО }
   then context { 2.<ATTRIBUTE>1.0  }
 }

 operator SubjectVerb_3050 : LINK_SUBJECT_VERB
 {
  // ДВА КИЛОГРАММА САЛА БЫЛО СЪЕДЕНО
  if context {
              ЧИСЛИТЕЛЬНОЕ:* { ПАДЕЖ:РОД }
              ГЛАГОЛ:БЫТЬ { ВРЕМЯ:ПРОШЕДШЕЕ РОД:СР }
              ПРИЛАГАТЕЛЬНОЕ:* { ПРИЧАСТИЕ СТРАД КРАТКИЙ РОД:СР }
             }
     correlate { ЧИСЛО }
   then context { 0.<ATTRIBUTE>2.1  }
 }



 operator SubjectVerb_4000 : LINK_SUBJECT_VERB
 {
  // ОН - ЧЕЛОВЕК.
  if context {
              МЕСТОИМЕНИЕ{ПАДЕЖ:ИМ}#a
              _Дефис
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
              _КОН 
             }
   then context { #a.<ATTRIBUTE>#b 3 }
 }


 operator SubjectVerb_4010 : LINK_SUBJECT_VERB
 {
  // ОН - ЧЕЛОВЕК,
  if context {
              МЕСТОИМЕНИЕ{ПАДЕЖ:ИМ}#a
              _Дефис
              СУЩЕСТВИТЕЛЬНОЕ{ПАДЕЖ:ИМ}#b
              _Запятая
             }
   then context { #a.<ATTRIBUTE>#b 3 }
 }




 operator SubjectVerb_4020 : LINK_SUBJECT_VERB
 {
  // БЫЛО СЪЕДЕНО ДВА ЯБЛОКА
  if context {
              [center:Глагол:Быть{} Прилагательное] { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ Род:Ср Число:Ед } #b
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:Им } #a
             }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_4030 : LINK_SUBJECT_VERB
 {
  // БЫЛО СЪЕДЕНО ЯБЛОКО
  if context {
              [center:Глагол:Быть{} Прилагательное] { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ Род:Ср Число:Ед } #b
              Существительное { ПАДЕЖ:Им } #a
             }
   then context { #b.<SUBJECT>#a }
 }


 operator SubjectVerb_4040 : LINK_SUBJECT_VERB
 {
  // БЫЛИ СЪЕДЕНЫ ДВА ЯБЛОКА
  if context {
              [center:Глагол:Быть{} Прилагательное] { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ Число:Мн } #b
              ЧИСЛИТЕЛЬНОЕ { ПАДЕЖ:Им } #a
             }
   then context { #b.<SUBJECT>#a }
 }

 operator SubjectVerb_4050 : LINK_SUBJECT_VERB
 {
  // БЫЛИ СЪЕДЕНЫ ЯБЛОКИ
  if context {
              [center:Глагол:Быть{} Прилагательное] { НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ Число:Мн } #b
              Существительное { ПАДЕЖ:Им } #a
             }
   then context { #b.<SUBJECT>#a }
 }


 #pragma floating on
}

