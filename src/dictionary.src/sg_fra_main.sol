// -----------------------------------------------------------------------------
// File SG_FRA_MAIN.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения классов, координат для французской секции Словаря.
// French lexicon: grammatical classes declarations
//
// 28.04.2011 - переработано объявление французского глагола
//
// Подробнее о синтаксисе описания морфологии:
// http://www.solarix.ru/for_developers/docs/enums.shtml
// http://www.solarix.ru/for_developers/docs/classes.shtml
// -----------------------------------------------------------------------------
//
// CD->12.07.2005
// LC->17.07.2012
// --------------

#include "sg_defs.h"

automat sg
{
 enum FR_PERSON as PERSON_fr    { 1 as PERSON_1_fr 2 as PERSON_2_fr 3 as PERSON_3_fr }
 enum FR_NOMBRE as NUMBER_fr    { SINGULIER as SINGULAR_fr PLURIEL as PLURAL_fr }
 enum FR_GENRE as GENDER_fr { MASCULINE as MASCULINE_fr FEMININE as FEMININE_fr }
 enum FR_NUMERAL_FORM as FR_NUMERAL_FORM { CARDINAL as CARDINAL_fr ORDINAL as ORDINAL_fr }

 enum FR_PRONOUN_FORM as FR_PRONOUN_FORM {
                                          WEAK as FR_PRONOUN_WEAK                // je, tu, nous ...
                                          STRONG as FR_PRONOUN_STRONG            // moi, toi, lui ...
                                         }
 
 enum FR_TRANSITIVITY as TRANSITIVITY_fr
 {
  INTRANSITIVE as INTRANSITIVE_VERB_fr
  TRANSITIVE as TRANSITIVE_VERB_fr
 } 

 enum FR_VERB_FORM as VERB_FORM_fr
 {
  INFINITIVE as INFINITIVE_fr
  PRESENT as PRESENT_VF_fr
  FUTURE as FUTURE_VF_fr
  IMPERFECT as IMPERFECT_VB_fr
  SIMPLE_PAST as SIMPLE_PAST_fr
  PRESENT_PARTICIPLE as PRESENT_PARTICIPLE_fr
  PAST_PARTICIPLE as PAST_PARTICIPLE_fr
  SUBJUNCTIVE_PRESENT as SUBJUNCTIVE_PRESENT_fr
  SUBJUNCTIVE_IMPERFECT as SUBJUNCTIVE_IMPERFECT_fr
  CONDITIONAL as CONDITIONAL_fr
  IMPERATIVE as IMPERATIVE_fr
 }
 
 // ------------------------------------------------------------------------

 class FR_NUMERAL as NUMERAL_fr
 {
  language French

  dimentions
   {
    FR_GENRE
    FR_NUMERAL_FORM
   }
 } 

 class FR_ARTICLE as ARTICLE_fr
 {
  language French
   
  dimentions
   {
    FR_NOMBRE FR_GENRE
   }
 }


 class FR_PREP as PREP_fr
 {
  language French
 }


 class FR_ADVERB as ADV_fr
 {
  language French
 }

 class FR_CONJ as CONJ_fr
 {
  language French
 }


 class FR_NOUN as NOUN_fr : NOUN
 {
  language French

  tags
   {
    CharCasing  // Слова, начинающиеся с заглавной буквы или целиком в верхнем регистре
   }
  
  attributes
   {
    FR_GENRE
   }

  dimentions
   {
    FR_NOMBRE
   }
 }

 class FR_ADJ as ADJ_fr : NOUN
 {
  language French
   
  dimentions
   {
    FR_GENRE
    FR_NOMBRE
   }
 }



 class FR_PRONOUN as PRONOUN_fr
 {
  language French
   
  dimentions
   {
    FR_PERSON FR_NOMBRE FR_GENRE FR_PRONOUN_FORM
   }
 }


 class FR_VERB as VERB_fr
 {
  language French
  
  attributes
  {
   // FR_TRANSITIVITY
  }
  
  dimentions
  {
   FR_VERB_FORM
   FR_PERSON
   FR_NOMBRE
   FR_GENRE
  }
 }

 // Частицы типа ne, se
 class FR_PARTICLE as PARTICLE_fr
 {
  language French
 }

 // Указательные местоимения
 class FR_PRONOUN2 as PRONOUN2_fr
 {
  language French
 }


}

