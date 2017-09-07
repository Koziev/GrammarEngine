// -----------------------------------------------------------------------------
// File SG_ENG_MAIN.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения классов, координат для английской секции Словаря.
//
// Подробнее о синтаксисе:
// http://www.solarix.ru/for_developers/docs/enums.shtml
// http://www.solarix.ru/for_developers/docs/classes.shtml
//
// 30.08.2009 - немного поправлены C-имена для состояний ADJ_FORM
// 02.04.2010 - для глаголов добавлен тег переходности
// 14.04.2012 - для прилагательных добавлен тег CharCasing.
// 13.10.2015 - убраны притяжательные формы для существительных, вместо них
//              введен признак [присоединяет притяжательный постфикс "'s"]
// 06.12.2015 - глагол BE выделен в отдельную часть речи ENG_BEVERB
// 07.12.2015 - модальные глаголы CAN, MAY etc выделены в новую часть речи ENG_AUXVERB
// -----------------------------------------------------------------------------
//
// CD->12.02.2005
// LC->07.12.2015
// --------------

#include "sg_defs.h"

automat sg
{
 enum TENSE as TENSE_en
 {
  PAST as PAST_en
  PRESENT as PRESENT_en
  FUTURE as FUTURE_en
  IMPERATIVE as IMPERATIVE_en
 }

 enum DURATION as DURATION_en { INDEFINITE as SIMPLE_en
                                CONTINUOUS as CONTINUOUS_en
                                PERFECT as PERFECT_en
                                PERFECT_CONTINUOUS as PERFECT_CONTINUOS_en
                              }

 // Пассивный (страдательный) и активный залог.
 enum VOICE as VOICE_en { PASSIVE as PASSIVE_en ACTIVE as ACTIVE_en }

 enum CASE as CASE_en
 {
  NOMINATIVE as NOMINATIVE_CASE_en
  PREPOSITIVE as PREPOSITIVE_CASE_en
 }

 enum NOUN_FORM as NOUN_FORM_en 
 {
  BASIC as BASIC_NOUN_FORM_en
  POSSESSIVE as POSSESSIVE_NOUN_FORM_en
 }

 enum HAS_POSSESSIVE_FORM as HAS_POSSESSIVE_FORM_en

 enum PRONOUN_FORM as PRONOUN_FORM_en
 {
  PRE /*this is MY book*/
  POST /* this book is MINE*/
  REFLEXIVE /*myself*/
 }
 
 enum ADJ_FORM as ADJ_FORM_en    { BASIC /*happy*/ as BASIC_ADJ_en COMPARATIVE /*happier*/ as COMPARATIVE_ADJ_en SUPERLATIVE /*happiest*/ as SUPERLATIVE_ADJ_en } 

 enum COMPARABILITY as COMPARABILITY_en {
                                         ANALYTIC  as ANALYTIC_en   // slowly - more slowly - most slowly
                                         SYNTHETIC as SYNTHETIC_en  // slowly - slowlier - slowliest
                                         COMPARABLE as COMPARABLE_en // присутствует или  ANALYTIC или SYNTHETIC
                                         NONCOMPARABLE as NONCOMPARABLE // неизменяемое прилагательное
                                        }

 enum VERB_FORM as VERB_FORM_en
 {
  UNDEF as UNDEF_VERBFORM_en // am-is-are
  S as S_VERBFORM_en      // writes
  ED as ED_VERBFORM_en    // wrote
  ING as ING_VERBFORM_en  // writing
  PP as PP_VERBFORM_en    // written (past participle)
  INF as INF_VEBFORM_en   // to write
 }


 enum ARTICLE_FORM as ARTICLE_FORM {
                                    1 as ARTICLE_FORM_1
									2 as ARTICLE_FORM_2
								   } // a-an

 enum NUMERAL_FORM as NUMERAL_FORM_en { CARDINAL as CARDINAL_en ORDINAL as ORDINAL_en }

 enum ENG_GENDER as GENDER_en {
                               MASCULINE as MASCULINE_en
                               FEMININE as FEMININE_en
                              }

 // Переходность глаголов
 enum TRANSITIVITY as TRANSITIVITY_en
 {
  INTRANSITIVE as INTRANSITIVE_VERB_en
  TRANSITIVE as TRANSITIVE_VERB_en // для глаголов с обязательной или опциональной транзитивностью
 }


 // Отдельный тег для глаголов, обязательно требующих прямое дополнение
 // в клозах типа
 //                The dog pushes the toy
 //
 enum OBLIG_TRANSITIVITY as OBLIG_TRANSITIVITY_en
 {
  0
  1
 }

 
 // ---------------------------------------------------------------------------- 

 enum VERB_SLOTS as VERB_SLOTS_en
 {
  // Дитранзитивные глаголы, присоединяющие второй (дательный) объект
  DITRANSITIVE as DITRANSITIVE_en
 
  // Связочные глаголы TO GET, TO BECOME, TO FEEL, TO SEEM
  COPULATIVE as COPULATIVE_en
 
  // Глаголы, которые могут присоединять ing-форму глагола
  // в качестве прямого дополнения: "to keep goind"
  GERUND as GERUND_en

  // Глаголы, присоединяющие группу PastParticiple
  PastParticiple as PastParticipleSlot_en

  ModalDirect as DIRECT_MODALITY_en // CAN DO
  ModalTo as TO_MODALITY_en         // HAVE TO DO 
  
  // Глаголы, которые могут присоединять прямое дополнение и
  // справа от него - предикативное прилагательное в качестве
  // намерения или качества.
  //
  // I find him stupid
  // Philosophers call such propositions "analytic."
  SeparateAttr
  

  // He asked me to come to his house
  AskedAction
 }
 
 enum ENG_PROPER_NOUN as PROPER_NOUN_en
 enum ENG_MASS_NOUN as MASS_NOUN_en
 enum ENG_MODAL_NOUN as MODAL_NOUN_en // для существительных, которые могут присоединять группу инфинитива

 enum HAS_APPOSITIVE_SLOT { 1 0 }
 
 // какие части речи модифицируются наречием:
 enum MODIF_TYPE
 {
  ADV
  COMPAR_ADV
  VERB
  ADJ
  NUMBER // "but" в "The roles are but three;"
 }


 // ------------------------------------------------------------------------

 class ENG_VERB as VERB_en
 {
  language English

  tags
  {
   DURATION
   TRANSITIVITY
   VERB_SLOTS
   OBLIG_TRANSITIVITY
   OMONYM_RESOLUTION
  }

  dimentions
  {
   VERB_FORM
  }
 }

 
 // Особая часть речи для глагола BE
 class ENG_BEVERB as BEVERB_en
 {
  language English

  tags
  {
   TRANSITIVITY
   VERB_SLOTS
   OBLIG_TRANSITIVITY
  }

  dimentions
  {
   TENSE
   NUMBER
   PERSON
   VERB_FORM
  }
 }

 // Модальные глаголы CAN, MAY и другие
 class ENG_AUXVERB as AUXVERB_en
 {
  language English

  tags
  {
   VERB_SLOTS
  }

  dimentions
  {
   VERB_FORM
  }
 }

 

 class ENG_NOUN as NOUN_en
 {
  language English

  tags
  {
   ENG_GENDER // для имен
   ENG_PROPER_NOUN // для имен собственных
   ENG_MASS_NOUN // для неисчислимых
   HAS_POSSESSIVE_FORM // возможна ли притяжательная форма с постфиксом 's
   ENG_MODAL_NOUN
   HAS_APPOSITIVE_SLOT // для "term" в "He used the term Hamitic.".
   CharCasing  // Слова, начинающиеся с заглавной буквы или целиком в верхнем регистре
  }

  dimentions
  {
   NUMBER
  }
 }


 class ENG_PRONOUN as PRONOUN_en
 {
  language English
  dimentions
   {
    NUMBER
    GENDER
    PERSON
    CASE  
    NOUN_FORM
    PRONOUN_FORM
   }
 }

 
 class ENG_ARTICLE as ARTICLE_en
 {
  language English
  dimentions
   {
    ARTICLE_FORM
   }
 }


 class ENG_PREP as PREP_en
 {
  language English
 }

 // Послелог later:
 // He died six weeks later.
 //                   ^^^^^
 class ENG_POSTPOS as POSTPOS_en
 {
  language English
 }
 
 class ENG_CONJ as CONJ_en
 { 
  language English
 }

 class ENG_ADVERB as ADV_en
 {
  language English
  
  dimentions
  {
   ADJ_FORM
  }
  
  tags
  {
   COMPARABILITY
   MODIF_TYPE
   CharCasing  // Слова, начинающиеся с заглавной буквы или целиком в верхнем регистре
  }
 }

 
 // ================================== 
 // Английские прилагательные
 // ================================== 
 
 enum ADJ_SLOTS
 {
  Modal // Прилагательные, присоединяющие инфинитивную группу, e.g. "ABLE TO..."
 }
 
 class ENG_ADJECTIVE as ADJ_en
 {
  language English

  tags
  {
   // Слова, начинающиеся с заглавной буквы или целиком в верхнем регистре, например названия языков English, Russian
   CharCasing
   ADJ_SLOTS
  }


  attributes
  {
   COMPARABILITY
  }

  dimentions
  {
   ADJ_FORM
  }
 }

 class ENG_PARTICLE as PARTICLE_en
 {
  language English
 }

 class ENG_NUMERAL as NUMERAL_en
 {
  language English
  dimentions
  {
   NUMERAL_FORM
  }
 }

 class ENG_INTERJECTION as INTERJECTION_en
 {
  language English
 }


 // Притяжательный постфикс 's выделим в отдельную часть речи
 class ENG_POSSESSION as POSSESSION_PARTICLE_en
 {
  language English

  dimentions
  {
   NUMBER
  }
 }

 
 // Префиксы составных существительных типа "quasi-cash"
 class ENG_COMPOUND_PRENOUN as COMPOUND_PRENOUN_en

 // Префиксы составных прилагательных и порядковых числительных типа "pre-Norse"
 class ENG_COMPOUND_PREADJ as COMPOUND_PREADJ_en

 // Префиксы составных глаголов типа "re-count"
 class ENG_COMPOUND_PREVERB as COMPOUND_PREVERB_en

 // Префиксы составных наречий типа 
 class ENG_COMPOUND_PREADV as COMPOUND_PREADV_en

 
}
