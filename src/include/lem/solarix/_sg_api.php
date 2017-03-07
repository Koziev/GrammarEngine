<?php
// This file is generated 28.01.2017 15:23:49 by Ygres compiler ver. 14.14.11192 Standard Win64  (build date Sep 21 2016).
namespace Solarix;
// Languages
define( 'RUSSIAN_LANGUAGE', 2 );                   // language Russian
define( 'ENGLISH_LANGUAGE', 3 );                   // language English
define( 'FRENCH_LANGUAGE', 4 );                    // language French
define( 'SPANISH_LANGUAGE', 5 );                   // language Spanish
define( 'CHINESE_LANGUAGE', 6 );                   // language Chinese
define( 'JAPANESE_LANGUAGE', 7 );                  // language Japanese
define( 'GERMAN_LANGUAGE', 8 );                    // language German
define( 'THESAURUS_LANGUAGE', 9 );                 // language ThesaurusLanguage
// ------------------------------------------------------------


define( 'NUM_WORD_CLASS', 2 );                     // class num_word
define( 'NOUN_ru', 6 );                            // class СУЩЕСТВИТЕЛЬНОЕ
define( 'PRONOUN2_ru', 7 );                        // class МЕСТОИМ_СУЩ
define( 'PRONOUN_ru', 8 );                         // class МЕСТОИМЕНИЕ
define( 'ADJ_ru', 9 );                             // class ПРИЛАГАТЕЛЬНОЕ
define( 'NUMBER_CLASS_ru', 10 );                   // class ЧИСЛИТЕЛЬНОЕ
define( 'INFINITIVE_ru', 11 );                     // class ИНФИНИТИВ
define( 'VERB_ru', 12 );                           // class ГЛАГОЛ
define( 'GERUND_2_ru', 13 );                       // class ДЕЕПРИЧАСТИЕ
define( 'PREPOS_ru', 14 );                         // class ПРЕДЛОГ
define( 'IMPERSONAL_VERB_ru', 15 );                // class БЕЗЛИЧ_ГЛАГОЛ
define( 'PARTICLE_ru', 18 );                       // class ЧАСТИЦА
define( 'CONJ_ru', 19 );                           // class СОЮЗ
define( 'ADVERB_ru', 20 );                         // class НАРЕЧИЕ
define( 'PUNCTUATION_class', 21 );                 // class ПУНКТУАТОР
define( 'POSTPOS_ru', 26 );                        // class ПОСЛЕЛОГ
define( 'POSESS_PARTICLE', 27 );                   // class ПРИТЯЖ_ЧАСТИЦА
define( 'MEASURE_UNIT', 28 );                      // class ЕДИНИЦА_ИЗМЕРЕНИЯ
define( 'COMPOUND_ADJ_PREFIX', 29 );               // class ПРЕФИКС_СОСТАВ_ПРИЛ
define( 'COMPOUND_NOUN_PREFIX', 30 );              // class ПРЕФИКС_СОСТАВ_СУЩ
define( 'VERB_en', 31 );                           // class ENG_VERB
define( 'BEVERB_en', 32 );                         // class ENG_BEVERB
define( 'AUXVERB_en', 33 );                        // class ENG_AUXVERB
define( 'NOUN_en', 34 );                           // class ENG_NOUN
define( 'PRONOUN_en', 35 );                        // class ENG_PRONOUN
define( 'ARTICLE_en', 36 );                        // class ENG_ARTICLE
define( 'PREP_en', 37 );                           // class ENG_PREP
define( 'POSTPOS_en', 38 );                        // class ENG_POSTPOS
define( 'CONJ_en', 39 );                           // class ENG_CONJ
define( 'ADV_en', 40 );                            // class ENG_ADVERB
define( 'ADJ_en', 41 );                            // class ENG_ADJECTIVE
define( 'PARTICLE_en', 42 );                       // class ENG_PARTICLE
define( 'NUMERAL_en', 43 );                        // class ENG_NUMERAL
define( 'INTERJECTION_en', 44 );                   // class ENG_INTERJECTION
define( 'POSSESSION_PARTICLE_en', 45 );            // class ENG_POSSESSION
define( 'COMPOUND_PRENOUN_en', 46 );               // class ENG_COMPOUND_PRENOUN
define( 'COMPOUND_PREADJ_en', 47 );                // class ENG_COMPOUND_PREADJ
define( 'COMPOUND_PREVERB_en', 48 );               // class ENG_COMPOUND_PREVERB
define( 'COMPOUND_PREADV_en', 49 );                // class ENG_COMPOUND_PREADV
define( 'NUMERAL_fr', 50 );                        // class FR_NUMERAL
define( 'ARTICLE_fr', 51 );                        // class FR_ARTICLE
define( 'PREP_fr', 52 );                           // class FR_PREP
define( 'ADV_fr', 53 );                            // class FR_ADVERB
define( 'CONJ_fr', 54 );                           // class FR_CONJ
define( 'NOUN_fr', 55 );                           // class FR_NOUN
define( 'ADJ_fr', 56 );                            // class FR_ADJ
define( 'PRONOUN_fr', 57 );                        // class FR_PRONOUN
define( 'VERB_fr', 58 );                           // class FR_VERB
define( 'PARTICLE_fr', 59 );                       // class FR_PARTICLE
define( 'PRONOUN2_fr', 60 );                       // class FR_PRONOUN2
define( 'NOUN_es', 61 );                           // class ES_NOUN
define( 'ROOT_es', 62 );                           // class ES_ROOT
define( 'JAP_NOUN', 63 );                          // class JAP_NOUN
define( 'JAP_NUMBER', 64 );                        // class JAP_NUMBER
define( 'JAP_ADJECTIVE', 65 );                     // class JAP_ADJECTIVE
define( 'JAP_ADVERB', 66 );                        // class JAP_ADVERB
define( 'JAP_CONJ', 67 );                          // class JAP_CONJ
define( 'JAP_VERB', 68 );                          // class JAP_VERB
define( 'JAP_PRONOUN', 69 );                       // class JAP_PRONOUN
define( 'JAP_VERB_POSTFIX2', 72 );                 // class JAP_VERB_POSTFIX2
define( 'JAP_PARTICLE', 74 );                      // class JAP_PARTICLE
define( 'UNKNOWN_ENTRIES_CLASS', 85 );             // class UnknownEntries
// ------------------------------------------------------------


define( 'CharCasing', 4 );                         // enum CharCasing
// Coordiname CharCasing states:
define( 'DECAPITALIZED_CASED', 0 );                // CharCasing : Lower
define( 'FIRST_CAPITALIZED_CASED', 1 );            // CharCasing : FirstCapitalized
define( 'ALL_CAPITALIZED_CASED', 2 );              // CharCasing : Upper
define( 'EACH_LEXEM_CAPITALIZED_CASED', 3 );       // CharCasing : EachLexemCapitalized
define( 'PERSON_xx', 6 );                          // enum PERSON
// Coordiname PERSON states:
define( 'PERSON_1_xx', 0 );                        // PERSON : 1
define( 'PERSON_2_xx', 1 );                        // PERSON : 2
define( 'PERSON_3_xx', 2 );                        // PERSON : 3
define( 'NUMBER_xx', 7 );                          // enum NUMBER
// Coordiname NUMBER states:
define( 'SINGLE_xx', 0 );                          // NUMBER : SINGLE
define( 'PLURAL_xx', 1 );                          // NUMBER : PLURAL
define( 'GENDER_xx', 8 );                          // enum GENDER
// Coordiname GENDER states:
define( 'MASCULINE_xx', 0 );                       // GENDER : MASCULINE
define( 'FEMININE_xx', 1 );                        // GENDER : FEMININE
define( 'NEUTRAL_xx', 2 );                         // GENDER : NEUTRAL
define( 'SPEECH_STYLE_xx', 9 );                    // enum СтильРечи
// Coordiname СтильРечи states:
define( 'STRENGTH_xx', 10 );                       // enum РазмерСила
// Coordiname РазмерСила states:
define( 'PERSON_ru', 27 );                         // enum ЛИЦО
// Coordiname ЛИЦО states:
define( 'PERSON_1_ru', 0 );                        // ЛИЦО : 1
define( 'PERSON_2_ru', 1 );                        // ЛИЦО : 2
define( 'PERSON_3_ru', 2 );                        // ЛИЦО : 3
define( 'NUMBER_ru', 28 );                         // enum ЧИСЛО
// Coordiname ЧИСЛО states:
define( 'SINGULAR_NUMBER_ru', 0 );                 // ЧИСЛО : ЕД
define( 'PLURAL_NUMBER_ru', 1 );                   // ЧИСЛО : МН
define( 'GENDER_ru', 29 );                         // enum РОД
// Coordiname РОД states:
define( 'MASCULINE_GENDER_ru', 0 );                // РОД : МУЖ
define( 'FEMININE_GENDER_ru', 1 );                 // РОД : ЖЕН
define( 'NEUTRAL_GENDER_ru', 2 );                  // РОД : СР
define( 'TRANSITIVENESS_ru', 30 );                 // enum ПЕРЕХОДНОСТЬ
// Coordiname ПЕРЕХОДНОСТЬ states:
define( 'NONTRANSITIVE_VERB_ru', 0 );              // ПЕРЕХОДНОСТЬ : НЕПЕРЕХОДНЫЙ
define( 'TRANSITIVE_VERB_ru', 1 );                 // ПЕРЕХОДНОСТЬ : ПЕРЕХОДНЫЙ
define( 'PARTICIPLE_ru', 31 );                     // enum ПРИЧАСТИЕ
define( 'PASSIVE_PARTICIPLE_ru', 32 );             // enum СТРАД
define( 'ASPECT_ru', 33 );                         // enum ВИД
// Coordiname ВИД states:
define( 'PERFECT_ru', 0 );                         // ВИД : СОВЕРШ
define( 'IMPERFECT_ru', 1 );                       // ВИД : НЕСОВЕРШ
define( 'VERB_FORM_ru', 35 );                      // enum НАКЛОНЕНИЕ
// Coordiname НАКЛОНЕНИЕ states:
define( 'VB_INF_ru', 0 );                          // НАКЛОНЕНИЕ : ИЗЪЯВ
define( 'VB_ORDER_ru', 1 );                        // НАКЛОНЕНИЕ : ПОБУД
define( 'TENSE_ru', 36 );                          // enum ВРЕМЯ
// Coordiname ВРЕМЯ states:
define( 'PAST_ru', 0 );                            // ВРЕМЯ : ПРОШЕДШЕЕ
define( 'PRESENT_ru', 1 );                         // ВРЕМЯ : НАСТОЯЩЕЕ
define( 'FUTURE_ru', 2 );                          // ВРЕМЯ : БУДУЩЕЕ
define( 'SHORTNESS_ru', 37 );                      // enum КРАТКИЙ
define( 'CASE_ru', 39 );                           // enum ПАДЕЖ
// Coordiname ПАДЕЖ states:
define( 'NOMINATIVE_CASE_ru', 0 );                 // ПАДЕЖ : ИМ
define( 'VOCATIVE_CASE_ru', 1 );                   # ЗВАТ
define( 'GENITIVE_CASE_ru', 2 );                   // ПАДЕЖ : РОД
define( 'PARTITIVE_CASE_ru', 3 );                  # ПАРТ
define( 'INSTRUMENTAL_CASE_ru', 5 );               // ПАДЕЖ : ТВОР
define( 'ACCUSATIVE_CASE_ru', 6 );                 // ПАДЕЖ : ВИН
define( 'DATIVE_CASE_ru', 7 );                     // ПАДЕЖ : ДАТ
define( 'PREPOSITIVE_CASE_ru', 8 );                // ПАДЕЖ : ПРЕДЛ
define( 'LOCATIVE_CASE_ru', 10 );                  # МЕСТ
define( 'FORM_ru', 40 );                           // enum ОДУШ
// Coordiname ОДУШ states:
define( 'ANIMATIVE_FORM_ru', 0 );                  // ОДУШ : ОДУШ
define( 'INANIMATIVE_FORM_ru', 1 );                // ОДУШ : НЕОДУШ
define( 'COUNTABILITY_ru', 41 );                   // enum ПЕРЕЧИСЛИМОСТЬ
// Coordiname ПЕРЕЧИСЛИМОСТЬ states:
define( 'COUNTABLE_ru', 0 );                       // ПЕРЕЧИСЛИМОСТЬ : ДА
define( 'UNCOUNTABLE_ru', 1 );                     // ПЕРЕЧИСЛИМОСТЬ : НЕТ
define( 'COMPAR_FORM_ru', 42 );                    // enum СТЕПЕНЬ
// Coordiname СТЕПЕНЬ states:
define( 'ATTRIBUTIVE_FORM_ru', 0 );                // СТЕПЕНЬ : АТРИБ
define( 'COMPARATIVE_FORM_ru', 1 );                // СТЕПЕНЬ : СРАВН
define( 'SUPERLATIVE_FORM_ru', 2 );                // СТЕПЕНЬ : ПРЕВОСХ
define( 'LIGHT_COMPAR_FORM_RU', 3 );               // СТЕПЕНЬ : КОМПАРАТИВ2
define( 'ABBREV_FORM_ru', 4 );                     // СТЕПЕНЬ : СОКРАЩ
define( 'CASE_GERUND_ru', 43 );                    // enum ПадежВал
// Coordiname ПадежВал states:
define( 'MODAL_ru', 44 );                          // enum МОДАЛЬНЫЙ
define( 'VERBMODE_TENSE', 45 );                    // enum СГД_Время
// Coordiname СГД_Время states:
define( 'VERBMODE_DIRECTION', 46 );                // enum СГД_Направление
// Coordiname СГД_Направление states:
define( 'NUMERAL_CATEGORY', 47 );                  // enum КАТЕГОРИЯ_ЧИСЛ
// Coordiname КАТЕГОРИЯ_ЧИСЛ states:
define( 'CARDINAL', 0 );                           // КАТЕГОРИЯ_ЧИСЛ : КОЛИЧ
define( 'COLLECTION', 1 );                         // КАТЕГОРИЯ_ЧИСЛ : СОБИР
define( 'ADV_SEMANTICS', 48 );                     // enum ОБСТ_ВАЛ
// Coordiname ОБСТ_ВАЛ states:
define( 'S_LOCATION', 0 );                         // ОБСТ_ВАЛ : МЕСТО
define( 'S_DIRECTION', 1 );                        // ОБСТ_ВАЛ : НАПРАВЛЕНИЕ
define( 'S_DIRECTION_FROM', 2 );                   // ОБСТ_ВАЛ : НАПРАВЛЕНИЕ_ОТКУДА
define( 'S_FINAL_POINT', 3 );                      // ОБСТ_ВАЛ : КОНЕЧНАЯ_ТОЧКА
define( 'S_DISTANCE', 4 );                         // ОБСТ_ВАЛ : РАССТОЯНИЕ
define( 'S_VELOCITY', 5 );                         // ОБСТ_ВАЛ : СКОРОСТЬ
define( 'S_MOMENT', 6 );                           // ОБСТ_ВАЛ : МОМЕНТ_ВРЕМЕНИ
define( 'S_DURATION', 7 );                         // ОБСТ_ВАЛ : ДЛИТЕЛЬНОСТЬ
define( 'S_TIME_DIVISIBILITY', 8 );                // ОБСТ_ВАЛ : КРАТНОСТЬ
define( 'S_ANALOG', 9 );                           // ОБСТ_ВАЛ : СОПОСТАВЛЕНИЕ
define( 'S_FACTOR', 10 );                          // ОБСТ_ВАЛ : МНОЖИТЕЛЬ
define( 'ADJ_TYPE', 49 );                          // enum ТИП_ПРИЛ
// Coordiname ТИП_ПРИЛ states:
define( 'ADJ_POSSESSIVE', 0 );                     // ТИП_ПРИЛ : ПРИТЯЖ
define( 'ADJ_ORDINAL', 1 );                        // ТИП_ПРИЛ : ПОРЯДК
define( 'PRONOUN_TYPE_ru', 51 );                   // enum ТИП_МЕСТОИМЕНИЯ
// Coordiname ТИП_МЕСТОИМЕНИЯ states:
define( 'VERB_TYPE_ru', 52 );                      // enum ТИП_ГЛАГОЛА
// Coordiname ТИП_ГЛАГОЛА states:
define( 'COPULA_VERB_ru', 2 );                     // ТИП_ГЛАГОЛА : СВЯЗОЧН
define( 'PARTICLE_TYPE', 53 );                     // enum ТИП_ЧАСТИЦЫ
// Coordiname ТИП_ЧАСТИЦЫ states:
define( 'PREFIX_PARTICLE', 0 );                    // ТИП_ЧАСТИЦЫ : ПРЕФИКС
define( 'POSTFIX_PARTICLE', 1 );                   // ТИП_ЧАСТИЦЫ : ПОСТФИКС
define( 'ADV_MODIF_TYPE', 54 );                    // enum ТИП_МОДИФ
// Coordiname ТИП_МОДИФ states:
define( 'TENSE_en', 55 );                          // enum TENSE
// Coordiname TENSE states:
define( 'PAST_en', 0 );                            // TENSE : PAST
define( 'PRESENT_en', 1 );                         // TENSE : PRESENT
define( 'FUTURE_en', 2 );                          // TENSE : FUTURE
define( 'IMPERATIVE_en', 3 );                      // TENSE : IMPERATIVE
define( 'DURATION_en', 56 );                       // enum DURATION
// Coordiname DURATION states:
define( 'SIMPLE_en', 0 );                          // DURATION : INDEFINITE
define( 'CONTINUOUS_en', 1 );                      // DURATION : CONTINUOUS
define( 'PERFECT_en', 2 );                         // DURATION : PERFECT
define( 'PERFECT_CONTINUOS_en', 3 );               // DURATION : PERFECT_CONTINUOUS
define( 'VOICE_en', 57 );                          // enum VOICE
// Coordiname VOICE states:
define( 'PASSIVE_en', 0 );                         // VOICE : PASSIVE
define( 'ACTIVE_en', 1 );                          // VOICE : ACTIVE
define( 'CASE_en', 58 );                           // enum CASE
// Coordiname CASE states:
define( 'NOMINATIVE_CASE_en', 0 );                 // CASE : NOMINATIVE
define( 'PREPOSITIVE_CASE_en', 1 );                // CASE : PREPOSITIVE
define( 'NOUN_FORM_en', 59 );                      // enum NOUN_FORM
// Coordiname NOUN_FORM states:
define( 'BASIC_NOUN_FORM_en', 0 );                 // NOUN_FORM : BASIC
define( 'POSSESSIVE_NOUN_FORM_en', 1 );            // NOUN_FORM : POSSESSIVE
define( 'HAS_POSSESSIVE_FORM_en', 60 );            // enum HAS_POSSESSIVE_FORM
define( 'PRONOUN_FORM_en', 61 );                   // enum PRONOUN_FORM
// Coordiname PRONOUN_FORM states:
define( 'ADJ_FORM_en', 62 );                       // enum ADJ_FORM
// Coordiname ADJ_FORM states:
define( 'BASIC_ADJ_en', 0 );                       // ADJ_FORM : BASIC
define( 'COMPARATIVE_ADJ_en', 1 );                 // ADJ_FORM : COMPARATIVE
define( 'SUPERLATIVE_ADJ_en', 2 );                 // ADJ_FORM : SUPERLATIVE
define( 'COMPARABILITY_en', 63 );                  // enum COMPARABILITY
// Coordiname COMPARABILITY states:
define( 'ANALYTIC_en', 0 );                        // COMPARABILITY : ANALYTIC
define( 'SYNTHETIC_en', 1 );                       // COMPARABILITY : SYNTHETIC
define( 'COMPARABLE_en', 2 );                      // COMPARABILITY : COMPARABLE
define( 'NONCOMPARABLE', 3 );                      // COMPARABILITY : NONCOMPARABLE
define( 'VERB_FORM_en', 64 );                      // enum VERB_FORM
// Coordiname VERB_FORM states:
define( 'UNDEF_VERBFORM_en', 0 );                  // VERB_FORM : UNDEF
define( 'S_VERBFORM_en', 1 );                      // VERB_FORM : S
define( 'ED_VERBFORM_en', 2 );                     // VERB_FORM : ED
define( 'ING_VERBFORM_en', 3 );                    // VERB_FORM : ING
define( 'PP_VERBFORM_en', 4 );                     // VERB_FORM : PP
define( 'INF_VEBFORM_en', 5 );                     // VERB_FORM : INF
define( 'ARTICLE_FORM', 65 );                      // enum ARTICLE_FORM
// Coordiname ARTICLE_FORM states:
define( 'ARTICLE_FORM_1', 0 );                     // ARTICLE_FORM : 1
define( 'ARTICLE_FORM_2', 1 );                     // ARTICLE_FORM : 2
define( 'NUMERAL_FORM_en', 66 );                   // enum NUMERAL_FORM
// Coordiname NUMERAL_FORM states:
define( 'CARDINAL_en', 0 );                        // NUMERAL_FORM : CARDINAL
define( 'ORDINAL_en', 1 );                         // NUMERAL_FORM : ORDINAL
define( 'GENDER_en', 67 );                         // enum ENG_GENDER
// Coordiname ENG_GENDER states:
define( 'MASCULINE_en', 0 );                       // ENG_GENDER : MASCULINE
define( 'FEMININE_en', 1 );                        // ENG_GENDER : FEMININE
define( 'TRANSITIVITY_en', 68 );                   // enum TRANSITIVITY
// Coordiname TRANSITIVITY states:
define( 'INTRANSITIVE_VERB_en', 0 );               // TRANSITIVITY : INTRANSITIVE
define( 'TRANSITIVE_VERB_en', 1 );                 // TRANSITIVITY : TRANSITIVE
define( 'OBLIG_TRANSITIVITY_en', 69 );             // enum OBLIG_TRANSITIVITY
// Coordiname OBLIG_TRANSITIVITY states:
define( 'VERB_SLOTS_en', 70 );                     // enum VERB_SLOTS
// Coordiname VERB_SLOTS states:
define( 'DITRANSITIVE_en', 0 );                    // VERB_SLOTS : DITRANSITIVE
define( 'COPULATIVE_en', 1 );                      // VERB_SLOTS : COPULATIVE
define( 'GERUND_en', 2 );                          // VERB_SLOTS : GERUND
define( 'PastParticipleSlot_en', 3 );              // VERB_SLOTS : PastParticiple
define( 'DIRECT_MODALITY_en', 4 );                 // VERB_SLOTS : ModalDirect
define( 'TO_MODALITY_en', 5 );                     // VERB_SLOTS : ModalTo
define( 'PROPER_NOUN_en', 71 );                    // enum ENG_PROPER_NOUN
define( 'MASS_NOUN_en', 72 );                      // enum ENG_MASS_NOUN
define( 'MODAL_NOUN_en', 73 );                     // enum ENG_MODAL_NOUN
define( 'PERSON_fr', 77 );                         // enum FR_PERSON
// Coordiname FR_PERSON states:
define( 'PERSON_1_fr', 0 );                        // FR_PERSON : 1
define( 'PERSON_2_fr', 1 );                        // FR_PERSON : 2
define( 'PERSON_3_fr', 2 );                        // FR_PERSON : 3
define( 'NUMBER_fr', 78 );                         // enum FR_NOMBRE
// Coordiname FR_NOMBRE states:
define( 'SINGULAR_fr', 0 );                        // FR_NOMBRE : SINGULIER
define( 'PLURAL_fr', 1 );                          // FR_NOMBRE : PLURIEL
define( 'GENDER_fr', 79 );                         // enum FR_GENRE
// Coordiname FR_GENRE states:
define( 'MASCULINE_fr', 0 );                       // FR_GENRE : MASCULINE
define( 'FEMININE_fr', 1 );                        // FR_GENRE : FEMININE
define( 'FR_NUMERAL_FORM', 80 );                   // enum FR_NUMERAL_FORM
// Coordiname FR_NUMERAL_FORM states:
define( 'CARDINAL_fr', 0 );                        // FR_NUMERAL_FORM : CARDINAL
define( 'ORDINAL_fr', 1 );                         // FR_NUMERAL_FORM : ORDINAL
define( 'FR_PRONOUN_FORM', 81 );                   // enum FR_PRONOUN_FORM
// Coordiname FR_PRONOUN_FORM states:
define( 'FR_PRONOUN_WEAK', 0 );                    // FR_PRONOUN_FORM : WEAK
define( 'FR_PRONOUN_STRONG', 1 );                  // FR_PRONOUN_FORM : STRONG
define( 'TRANSITIVITY_fr', 82 );                   // enum FR_TRANSITIVITY
// Coordiname FR_TRANSITIVITY states:
define( 'INTRANSITIVE_VERB_fr', 0 );               // FR_TRANSITIVITY : INTRANSITIVE
define( 'TRANSITIVE_VERB_fr', 1 );                 // FR_TRANSITIVITY : TRANSITIVE
define( 'VERB_FORM_fr', 83 );                      // enum FR_VERB_FORM
// Coordiname FR_VERB_FORM states:
define( 'INFINITIVE_fr', 0 );                      // FR_VERB_FORM : INFINITIVE
define( 'PRESENT_VF_fr', 1 );                      // FR_VERB_FORM : PRESENT
define( 'FUTURE_VF_fr', 2 );                       // FR_VERB_FORM : FUTURE
define( 'IMPERFECT_VB_fr', 3 );                    // FR_VERB_FORM : IMPERFECT
define( 'SIMPLE_PAST_fr', 4 );                     // FR_VERB_FORM : SIMPLE_PAST
define( 'PRESENT_PARTICIPLE_fr', 5 );              // FR_VERB_FORM : PRESENT_PARTICIPLE
define( 'PAST_PARTICIPLE_fr', 6 );                 // FR_VERB_FORM : PAST_PARTICIPLE
define( 'SUBJUNCTIVE_PRESENT_fr', 7 );             // FR_VERB_FORM : SUBJUNCTIVE_PRESENT
define( 'SUBJUNCTIVE_IMPERFECT_fr', 8 );           // FR_VERB_FORM : SUBJUNCTIVE_IMPERFECT
define( 'CONDITIONAL_fr', 9 );                     // FR_VERB_FORM : CONDITIONAL
define( 'IMPERATIVE_fr', 10 );                     // FR_VERB_FORM : IMPERATIVE
define( 'JAP_FORM', 84 );                          // enum JAP_FORM
// Coordiname JAP_FORM states:
define( 'KANA_FORM', 0 );                          // JAP_FORM : KANA
define( 'KANJI_FORM', 1 );                         // JAP_FORM : KANJI
define( 'ROMAJI_FORM', 2 );                        // JAP_FORM : ROMAJI
define( 'JAP_VERB_BASE', 85 );                     // enum JAP_VERB_BASE
// Coordiname JAP_VERB_BASE states:
define( 'JAP_VB_I', 0 );                           // JAP_VERB_BASE : I
define( 'JAP_VB_II', 1 );                          // JAP_VERB_BASE : II
define( 'JAP_VB_III', 2 );                         // JAP_VERB_BASE : III
define( 'JAP_VB_IV', 3 );                          // JAP_VERB_BASE : IV
define( 'JAP_VB_V', 4 );                           // JAP_VERB_BASE : V
define( 'JAP_VB_PAST', 5 );                        // JAP_VERB_BASE : PAST
define( 'JAP_VB_PARTICIPLE', 6 );                  // JAP_VERB_BASE : PARTICIPLE
define( 'JAP_VB_POTENTIAL', 7 );                   // JAP_VERB_BASE : POTENTIAL
define( 'JAP_VB_CONDITIONAL', 8 );                 // JAP_VERB_BASE : CONDITIONAL
define( 'JAP_VB_CAUSATIVE', 9 );                   // JAP_VERB_BASE : CAUSATIVE
define( 'JAP_VERB_KIND', 86 );                     // enum JAP_VERB_KIND
// Coordiname JAP_VERB_KIND states:
define( 'JAP_PRESENT_FUTURE', 1 );                 // JAP_VERB_KIND : PRESENT_FUTURE
define( 'JAP_NEGATIVE_PRESENT_FUTURE', 3 );        // JAP_VERB_KIND : NEGATIVE_PRESENT_FUTURE
define( 'JAP_NEGATIVE_PAST', 4 );                  // JAP_VERB_KIND : NEGATIVE_PAST
define( 'JAP_IMPERATIVE', 5 );                     // JAP_VERB_KIND : IMPERATIVE
define( 'JAP_NEGATIVE_IMPERATIVE', 6 );            // JAP_VERB_KIND : NEGATIVE_IMPERATIVE
define( 'JAP_ADJ_BASE', 87 );                      // enum JAP_ADJ_BASE
// Coordiname JAP_ADJ_BASE states:
define( 'JAP_AB_I', 0 );                           // JAP_ADJ_BASE : I
define( 'JAP_AB_II', 1 );                          // JAP_ADJ_BASE : II
define( 'JAP_AB_III', 2 );                         // JAP_ADJ_BASE : III
define( 'JAP_AB_IV', 3 );                          // JAP_ADJ_BASE : IV
define( 'JAP_AB_V', 4 );                           // JAP_ADJ_BASE : V
define( 'JAP_AB_T', 5 );                           // JAP_ADJ_BASE : T
define( 'JAP_AB_PAST', 6 );                        // JAP_ADJ_BASE : PAST
define( 'JAP_ADJ_FORM2', 88 );                     // enum JAP_ADJ_FORM2
// Coordiname JAP_ADJ_FORM2 states:
define( 'JAP_NEGATIVE_PRESENT_ADJ', 0 );           // JAP_ADJ_FORM2 : NEGATIVE_PRESENT
define( 'JAP_NEGATIVE_PAST_ADJ', 1 );              // JAP_ADJ_FORM2 : NEGATIVE_PAST
define( 'JAP_TRANSITIVE', 89 );                    // enum JAP_TRANSITIVE
define( 'CASE_jap', 90 );                          // enum JAP_CASE
// Coordiname JAP_CASE states:
define( 'VOCATIVE_jap', 0 );                       // JAP_CASE : VOCATIVE
define( 'NOMINATIVE_THEM_jap', 1 );                // JAP_CASE : NOMINATIVE_THEM
define( 'NOMINATIVE_RHEM_jap', 2 );                // JAP_CASE : NOMINATIVE_RHEM
define( 'ACCUSATIVE_jap', 3 );                     // JAP_CASE : ACCUSATIVE
define( 'GENITIVE_jap', 4 );                       // JAP_CASE : GENITIVE
define( 'DATIVE_jap', 5 );                         // JAP_CASE : DATIVE
define( 'ALLATIVE_jap', 6 );                       // JAP_CASE : ALLATIVE
define( 'INSTRUMENTATIVE_jap', 7 );                // JAP_CASE : INSTRUMENTATIVE
define( 'ELATIVE_jap', 8 );                        // JAP_CASE : ELATIVE
define( 'LIMITIVE_jap', 9 );                       // JAP_CASE : LIMITIVE
define( 'COMPARATIVE_jap', 10 );                   // JAP_CASE : COMPARATIVE
define( 'COMITATIVE_jap', 11 );                    // JAP_CASE : COMITATIVE
define( 'SOCIATIVE_jap', 12 );                     // JAP_CASE : SOCIATIVE
define( 'GENDER_jap', 91 );                        // enum JAP_GENDER
// Coordiname JAP_GENDER states:
define( 'MASCULINE_jap', 0 );                      // JAP_GENDER : MASCULINE
define( 'FEMININE_jap', 1 );                       // JAP_GENDER : FEMININE
define( 'PERSON_jap', 92 );                        // enum JAP_PERSON
// Coordiname JAP_PERSON states:
define( 'PERSON_1_jap', 0 );                       // JAP_PERSON : 1
define( 'PERSON_2_jap', 1 );                       // JAP_PERSON : 2
define( 'PERSON_3_jap', 2 );                       // JAP_PERSON : 3
define( 'NUMBER_jap', 93 );                        // enum JAP_NUMBER
// Coordiname JAP_NUMBER states:
define( 'SINGULAR_jap', 0 );                       // JAP_NUMBER : SINGULAR
define( 'PLURAL_jap', 1 );                         // JAP_NUMBER : PLURAL
define( 'JAP_PRONOUN_TYPE', 94 );                  // enum JAP_PRONOUN_TYPE
// Coordiname JAP_PRONOUN_TYPE states:
define( 'PERSONAL_jap', 0 );                       // JAP_PRONOUN_TYPE : PERSONAL
define( 'POINTING_jap', 1 );                       // JAP_PRONOUN_TYPE : POINTING
define( 'POSSESSIVE_jap', 2 );                     // JAP_PRONOUN_TYPE : POSSESSIVE
// ------------------------------------------------------------


define( 'OBJECT_link', 0 );
define( 'ATTRIBUTE_link', 1 );
define( 'CONDITION_link', 2 );
define( 'CONSEQUENCE_link', 3 );
define( 'SUBJECT_link', 4 );
define( 'RHEMA_link', 5 );
define( 'COVERB_link', 6 );
define( 'NUMBER2OBJ_link', 12 );
define( 'TO_VERB_link', 16 );
define( 'TO_INF_link', 17 );
define( 'TO_PERFECT', 18 );
define( 'TO_UNPERFECT', 19 );
define( 'TO_NOUN_link', 20 );
define( 'TO_ADJ_link', 21 );
define( 'TO_ADV_link', 22 );
define( 'TO_RETVERB', 23 );
define( 'TO_GERUND_2_link', 24 );
define( 'WOUT_RETVERB', 25 );
define( 'TO_ENGLISH_link', 26 );
define( 'TO_RUSSIAN_link', 27 );
define( 'TO_FRENCH_link', 28 );
define( 'SYNONYM_link', 29 );
define( 'SEX_SYNONYM_link', 30 );
define( 'CLASS_link', 31 );
define( 'MEMBER_link', 32 );
define( 'TO_SPANISH_link', 33 );
define( 'TO_GERMAN_link', 34 );
define( 'TO_CHINESE_link', 35 );
define( 'TO_POLAND_link', 36 );
define( 'TO_ITALIAN_link', 37 );
define( 'TO_PORTUGUAL_link', 38 );
define( 'ACTION_link', 39 );
define( 'ACTOR_link', 40 );
define( 'TOOL_link', 41 );
define( 'RESULT_link', 42 );
define( 'TO_JAPANESE_link', 43 );
define( 'TO_KANA_link', 44 );
define( 'TO_KANJI_link', 45 );
define( 'ANTONYM_link', 46 );
define( 'EXPLANATION_link', 47 );
define( 'WWW_link', 48 );
define( 'ACCENT_link', 49 );
define( 'YO_link', 50 );
define( 'TO_DIMINUITIVE_link', 51 );
define( 'TO_RUDE_link', 52 );
define( 'TO_BIGGER_link', 53 );
define( 'TO_NEUTRAL_link', 54 );
define( 'TO_SCOLARLY', 55 );
define( 'TO_SAMPLE_link', 56 );
define( 'USAGE_TAG_link', 57 );
define( 'PROPERTY_link', 58 );
define( 'TO_CYRIJI_link', 59 );
define( 'HABITANT_link', 60 );
define( 'CHILD_link', 61 );
define( 'PARENT_link', 62 );
define( 'UNIT_link', 63 );
define( 'SET_link', 64 );
define( 'TO_WEAKENED_link', 65 );
define( 'VERBMODE_BASIC_link', 66 );
define( 'NEGATION_PARTICLE_link', 67 );
define( 'NEXT_COLLOCATION_ITEM_link', 68 );
define( 'SUBORDINATE_CLAUSE_link', 69 );
define( 'RIGHT_GENITIVE_OBJECT_link', 70 );
define( 'ADV_PARTICIPLE_link', 71 );
define( 'POSTFIX_PARTICLE_link', 72 );
define( 'INFINITIVE_link', 73 );
define( 'NEXT_ADJECTIVE_link', 74 );
define( 'NEXT_NOUN_link', 75 );
define( 'THEMA_link', 76 );
define( 'RIGHT_AUX2INFINITIVE_link', 77 );
define( 'RIGHT_AUX2PARTICIPLE', 78 );
define( 'RIGHT_AUX2ADJ', 79 );
define( 'RIGHT_LOGIC_ITEM_link', 80 );
define( 'RIGHT_COMPARISON_Y_link', 81 );
define( 'RIGHT_NOUN_link', 82 );
define( 'RIGHT_NAME_link', 83 );
define( 'ADJ_PARTICIPLE_link', 84 );
define( 'PUNCTUATION_link', 85 );
define( 'IMPERATIVE_SUBJECT_link', 86 );
define( 'IMPERATIVE_VERB2AUX_link', 87 );
define( 'AUX2IMPERATIVE_VERB', 88 );
define( 'PREFIX_PARTICLE_link', 89 );
define( 'PREFIX_CONJUNCTION_link', 90 );
define( 'LOGICAL_CONJUNCTION_link', 91 );
define( 'NEXT_CLAUSE_link', 92 );
define( 'LEFT_AUX_VERB_link', 93 );
define( 'BEG_INTRO_link', 94 );
define( 'RIGHT_PREPOSITION_link', 95 );
define( 'WH_SUBJECT_link', 96 );
define( 'IMPERATIVE_PARTICLE_link', 97 );
define( 'GERUND_link', 98 );
define( 'PREPOS_ADJUNCT_link', 99 );
define( 'DIRECT_OBJ_INTENTION_link', 100 );
define( 'COPULA_link', 101 );
define( 'DETAILS_link', 102 );
define( 'SENTENCE_CLOSER_link', 103 );
define( 'OPINION_link', 104 );
define( 'APPEAL_link', 105 );
define( 'TERM_link', 106 );
define( 'SPEECH_link', 107 );
define( 'QUESTION_link', 108 );
define( 'POLITENESS_link', 109 );
define( 'SEPARATE_ATTR_link', 110 );
define( 'POSSESSION_POSTFIX_link', 111 );
define( 'COMPOUND_PREFIX_link', 112 );
define( 'UNKNOWN_SLOT_link', 113 );
define( 'SECOND_VERB_link', 114 );

?>
