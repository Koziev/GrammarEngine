// -----------------------------------------------------------------------------
// File SG_JAP_MAIN.SOL
//
// (c) Koziev Elijah
//
// Content:
// Лексикон - определения классов, координат для японского раздела Словаря.
//
// 28.04.2011 - добавлена потенциальная форма глагола
//
// Подробнее о синтаксисе:
// http://www.solarix.ru/for_developers/docs/enums.shtml
// http://www.solarix.ru/for_developers/docs/classes.shtml
// -----------------------------------------------------------------------------
//
// CD->27.02.2009
// LC->14.05.2011
// --------------

#include "sg_defs.h"

automat sg
{
 enum JAP_FORM as JAP_FORM {
                            KANA as KANA_FORM
                            KANJI as KANJI_FORM
                            ROMAJI as ROMAJI_FORM  
                           }

 enum JAP_VERB_BASE as JAP_VERB_BASE { 
                                      I as JAP_VB_I
                                      II as JAP_VB_II
                                      III as JAP_VB_III
                                      IV as JAP_VB_IV
                                      V as JAP_VB_V // VOLITIONAL
                                      PAST as JAP_VB_PAST // форма прошедшего времени
                                      PARTICIPLE as JAP_VB_PARTICIPLE // деепричастие
									  POTENTIAL as JAP_VB_POTENTIAL // форма "мочь сделать что-то"
                                      CONDITIONAL as JAP_VB_CONDITIONAL
                                      CAUSATIVE as JAP_VB_CAUSATIVE
                                     }   
                                      
 enum JAP_VERB_KIND as JAP_VERB_KIND {
                                      Undefined
                                      PRESENT_FUTURE as JAP_PRESENT_FUTURE                   // настояще-будущее время
                                      PRESENT_CONTINUOUS                                     // длительное время: форма глагола на -te + いる 
                                      NEGATIVE_PRESENT_FUTURE as JAP_NEGATIVE_PRESENT_FUTURE // отрицание для настояще-будущего времени
									  NEGATIVE_PAST as JAP_NEGATIVE_PAST                     // отрицание для прошедшего времени
                                      IMPERATIVE as JAP_IMPERATIVE                           // побудительная форма 
                                      NEGATIVE_IMPERATIVE as JAP_NEGATIVE_IMPERATIVE         // отрицание побудительной формы
                                     }

      
 enum JAP_ADJ_BASE as JAP_ADJ_BASE {
                                    I as JAP_AB_I
                                    II as JAP_AB_II
                                    III as JAP_AB_III
                                    IV as JAP_AB_IV
                                    V as JAP_AB_V
                                    T as JAP_AB_T // серединная форма
                                    PAST as JAP_AB_PAST // прошедшее время для прилагательного в роли сказуемого
                                   }
                                   

 // дополнительный классификатор форм прилагательных
 enum JAP_ADJ_FORM2 as JAP_ADJ_FORM2 {
                                      NEGATIVE_PRESENT as JAP_NEGATIVE_PRESENT_ADJ // отрицание для настояще-будущего времени
									  NEGATIVE_PAST as JAP_NEGATIVE_PAST_ADJ       // отрицание для прошедшего времени
                                     }

 enum JAP_TRANSITIVE as JAP_TRANSITIVE

 enum JAP_CASE as CASE_jap
 {
  VOCATIVE        as VOCATIVE_jap 
  NOMINATIVE_THEM as NOMINATIVE_THEM_jap
  NOMINATIVE_RHEM as NOMINATIVE_RHEM_jap
  ACCUSATIVE      as ACCUSATIVE_jap
  GENITIVE        as GENITIVE_jap
  DATIVE          as DATIVE_jap           // дательный, место при глаголах состояния, цель, превратительный
  ALLATIVE        as ALLATIVE_jap         // направление
  INSTRUMENTATIVE as INSTRUMENTATIVE_jap
  ELATIVE         as ELATIVE_jap          // исходный 
  LIMITIVE        as LIMITIVE_jap         // предельный
  COMPARATIVE     as COMPARATIVE_jap
  COMITATIVE      as COMITATIVE_jap       // совместность   
  SOCIATIVE       as SOCIATIVE_jap        // присоединительный  
 }


 // Грамматический род - для личных местоимений
 enum JAP_GENDER as GENDER_jap
 {
  MASCULINE as MASCULINE_jap
  FEMININE as FEMININE_jap
 }


 // Лицо - для местоимений
 enum JAP_PERSON as PERSON_jap
 {
  1 as PERSON_1_jap
  2 as PERSON_2_jap
  3 as PERSON_3_jap
 }


 // Число
 enum JAP_NUMBER as NUMBER_jap
 {
  SINGULAR as SINGULAR_jap
  PLURAL as PLURAL_jap
 }

 // Виды местоимении
 enum JAP_PRONOUN_TYPE as JAP_PRONOUN_TYPE
 {
  PERSONAL as PERSONAL_jap
  POINTING as POINTING_jap
  POSSESSIVE as POSSESSIVE_jap
 }


 class JAP_NOUN as JAP_NOUN
 {
  language Japanese

  attributes
  { 
   JAP_FORM
  }

  dimentions
  {
   JAP_CASE
  }
 }


 class JAP_NUMBER as JAP_NUMBER
 {
  language Japanese

  dimentions
  { 
   JAP_FORM
  }
 }


 class JAP_ADJECTIVE as JAP_ADJECTIVE
 {
  language Japanese

  attributes
  { 
   JAP_FORM
  }

  dimentions
  {
   JAP_ADJ_BASE

   JAP_ADJ_FORM2 // задается постфиксами
  }    
 }


 class JAP_ADVERB as JAP_ADVERB
 {
  language Japanese

  attributes
  { 
   JAP_FORM
  }
 }

 class JAP_CONJ as JAP_CONJ
 {
  language Japanese

  attributes
  { 
   JAP_FORM
  }

 }


 class JAP_VERB as JAP_VERB
 {
  language Japanese

  attributes
  { 
   JAP_FORM
   JAP_TRANSITIVE
  }

  dimentions
  {
   JAP_VERB_BASE
   JAP_VERB_KIND // от постфикса
  }
 }


 class JAP_PRONOUN as JAP_PRONOUN
 {
  language Japanese

  attributes
  {
   JAP_PRONOUN_TYPE
  }

  dimentions
  {
   JAP_GENDER
   JAP_NUMBER
   JAP_PERSON
   JAP_CASE
  }
 } 

 // ***************************************************
 // Суффиксы для образования падежа существительного
 // ***************************************************
 class JAP_CASE_SUFFIX
 { 
  language Japanese

  attributes
  {
   JAP_CASE
  }
 }

 class JAP_VERB_POSTFIX
 {
  language Japanese
  attributes { JAP_VERB_KIND }
 }


 class JAP_VERB_POSTFIX2 as JAP_VERB_POSTFIX2
 {
  language Japanese
 }

 
 paradigm 9900 : JAP_NOUN
 {
  JAP_CASE:VOCATIVE { "" }
/*
  JAP_CASE:NOMINATIVE_THEM { "%+は" }
  JAP_CASE:NOMINATIVE_RHEM { "%+が" }
  JAP_CASE:ACCUSATIVE { "%+を" }
  JAP_CASE:GENITIVE { "%+の" }
  JAP_CASE:DATIVE { "%+に" }
  JAP_CASE:ALLATIVE { "%+へ" }
  JAP_CASE:INSTRUMENTATIVE { "%+で" }
  JAP_CASE:ELATIVE { "%+から" }
  JAP_CASE:LIMITIVE { "%+まで" }
  JAP_CASE:COMPARATIVE { "%+より" }
  JAP_CASE:COMITATIVE { "%+と" }
  JAP_CASE:SOCIATIVE { "%+も" }
*/
 }


 // ******************
 // Счетные суффиксы
 // ******************
 class JAP_COUNTING_SUFFIX  
 { 
  language Japanese
 }


 // ********************************************************************
 // Различные частицы, в том числе оформляющие грамматические свойства.
 // Послелоги.
 // ********************************************************************
 class JAP_PARTICLE as JAP_PARTICLE
 {
  language Japanese
 }

 // Специфические японские разделители типа 。 
 class JAP_DELIMITER
 {
  language Japanese
 }

 entry _JDATE : num_word { flag:nonterminal_entry }
 entry _JTIME : num_word {flag:nonterminal_entry }
 
}
