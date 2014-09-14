<?php
// This file is generated 30.08.2014 10:31:20 by Ygres compiler ver. 13.23.11072 Standard Win32  (build date Aug 29 2014).
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


define( 'NUM_WORD_CLASS', 3 );                     // class num_word
define( 'NOUN_ru', 7 );                            // class СУЩЕСТВИТЕЛЬНОЕ
define( 'PRONOUN2_ru', 8 );                        // class МЕСТОИМ_СУЩ
define( 'PRONOUN_ru', 9 );                         // class МЕСТОИМЕНИЕ
define( 'ADJ_ru', 10 );                            // class ПРИЛАГАТЕЛЬНОЕ
define( 'NUMBER_CLASS_ru', 11 );                   // class ЧИСЛИТЕЛЬНОЕ
define( 'INFINITIVE_ru', 12 );                     // class ИНФИНИТИВ
define( 'VERB_ru', 13 );                           // class ГЛАГОЛ
define( 'GERUND_2_ru', 14 );                       // class ДЕЕПРИЧАСТИЕ
define( 'PREPOS_ru', 15 );                         // class ПРЕДЛОГ
define( 'IMPERSONAL_VERB_ru', 16 );                // class БЕЗЛИЧ_ГЛАГОЛ
define( 'PARTICLE_ru', 19 );                       // class ЧАСТИЦА
define( 'CONJ_ru', 20 );                           // class СОЮЗ
define( 'ADVERB_ru', 21 );                         // class НАРЕЧИЕ
define( 'PUNCTUATION_class', 22 );                 // class ПУНКТУАТОР
define( 'POSTPOS_ru', 27 );                        // class ПОСЛЕЛОГ
define( 'POSESS_PARTICLE', 28 );                   // class ПРИТЯЖ_ЧАСТИЦА
define( 'VERB_en', 29 );                           // class ENG_VERB
define( 'NOUN_en', 30 );                           // class ENG_NOUN
define( 'PRONOUN_en', 31 );                        // class ENG_PRONOUN
define( 'ARTICLE_en', 32 );                        // class ENG_ARTICLE
define( 'PREP_en', 33 );                           // class ENG_PREP
define( 'CONJ_en', 34 );                           // class ENG_CONJ
define( 'ADV_en', 35 );                            // class ENG_ADVERB
define( 'ADJ_en', 36 );                            // class ENG_ADJECTIVE
define( 'PARTICLE_en', 37 );                       // class ENG_PARTICLE
define( 'NUMERAL_en', 38 );                        // class ENG_NUMERAL
define( 'INTERJECTION_en', 39 );                   // class ENG_INTERJECTION
define( 'NUMERAL_fr', 40 );                        // class FR_NUMERAL
define( 'ARTICLE_fr', 41 );                        // class FR_ARTICLE
define( 'PREP_fr', 42 );                           // class FR_PREP
define( 'ADV_fr', 43 );                            // class FR_ADVERB
define( 'CONJ_fr', 44 );                           // class FR_CONJ
define( 'NOUN_fr', 45 );                           // class FR_NOUN
define( 'ADJ_fr', 46 );                            // class FR_ADJ
define( 'PRONOUN_fr', 47 );                        // class FR_PRONOUN
define( 'VERB_fr', 48 );                           // class FR_VERB
define( 'PARTICLE_fr', 49 );                       // class FR_PARTICLE
define( 'PRONOUN2_fr', 50 );                       // class FR_PRONOUN2
define( 'NOUN_es', 51 );                           // class ES_NOUN
define( 'ROOT_es', 52 );                           // class ES_ROOT
define( 'JAP_NOUN', 53 );                          // class JAP_NOUN
define( 'JAP_NUMBER', 54 );                        // class JAP_NUMBER
define( 'JAP_ADJECTIVE', 55 );                     // class JAP_ADJECTIVE
define( 'JAP_ADVERB', 56 );                        // class JAP_ADVERB
define( 'JAP_CONJ', 57 );                          // class JAP_CONJ
define( 'JAP_VERB', 58 );                          // class JAP_VERB
define( 'JAP_PRONOUN', 59 );                       // class JAP_PRONOUN
define( 'JAP_VERB_POSTFIX2', 62 );                 // class JAP_VERB_POSTFIX2
define( 'JAP_PARTICLE', 64 );                      // class JAP_PARTICLE
define( 'UNKNOWN_ENTRIES_CLASS', 75 );             // class UnknownEntries
// ------------------------------------------------------------


define( 'CharCasing', 5 );                         // enum CharCasing
// Coordiname CharCasing states:
define( 'DECAPITALIZED_CASED', 0 );                // CharCasing : Lower
define( 'FIRST_CAPITALIZED_CASED', 1 );            // CharCasing : FirstCapitalized
define( 'ALL_CAPITALIZED_CASED', 2 );              // CharCasing : Upper
define( 'EACH_LEXEM_CAPITALIZED_CASED', 3 );       // CharCasing : EachLexemCapitalized
define( 'PERSON_xx', 7 );                          // enum PERSON
// Coordiname PERSON states:
define( 'PERSON_1_xx', 0 );                        // PERSON : 1
define( 'PERSON_2_xx', 1 );                        // PERSON : 2
define( 'PERSON_3_xx', 2 );                        // PERSON : 3
define( 'NUMBER_xx', 8 );                          // enum NUMBER
// Coordiname NUMBER states:
define( 'SINGLE_xx', 0 );                          // NUMBER : SINGLE
define( 'PLURAL_xx', 1 );                          // NUMBER : PLURAL
define( 'GENDER_xx', 9 );                          // enum GENDER
// Coordiname GENDER states:
define( 'MASCULINE_xx', 0 );                       // GENDER : MASCULINE
define( 'FEMININE_xx', 1 );                        // GENDER : FEMININE
define( 'NEUTRAL_xx', 2 );                         // GENDER : NEUTRAL
define( 'SPEECH_STYLE_xx', 10 );                   // enum СтильРечи
// Coordiname СтильРечи states:
define( 'STRENGTH_xx', 11 );                       // enum РазмерСила
// Coordiname РазмерСила states:
define( 'PERSON_ru', 12 );                         // enum ЛИЦО
// Coordiname ЛИЦО states:
define( 'PERSON_1_ru', 0 );                        // ЛИЦО : 1
define( 'PERSON_2_ru', 1 );                        // ЛИЦО : 2
define( 'PERSON_3_ru', 2 );                        // ЛИЦО : 3
define( 'NUMBER_ru', 13 );                         // enum ЧИСЛО
// Coordiname ЧИСЛО states:
define( 'SINGULAR_NUMBER_ru', 0 );                 // ЧИСЛО : ЕД
define( 'PLURAL_NUMBER_ru', 1 );                   // ЧИСЛО : МН
define( 'GENDER_ru', 14 );                         // enum РОД
// Coordiname РОД states:
define( 'MASCULINE_GENDER_ru', 0 );                // РОД : МУЖ
define( 'FEMININE_GENDER_ru', 1 );                 // РОД : ЖЕН
define( 'NEUTRAL_GENDER_ru', 2 );                  // РОД : СР
define( 'TRANSITIVENESS_ru', 15 );                 // enum ПЕРЕХОДНОСТЬ
// Coordiname ПЕРЕХОДНОСТЬ states:
define( 'NONTRANSITIVE_VERB_ru', 0 );              // ПЕРЕХОДНОСТЬ : НЕПЕРЕХОДНЫЙ
define( 'TRANSITIVE_VERB_ru', 1 );                 // ПЕРЕХОДНОСТЬ : ПЕРЕХОДНЫЙ
define( 'PARTICIPLE_ru', 16 );                     // enum ПРИЧАСТИЕ
define( 'PASSIVE_PARTICIPLE_ru', 17 );             // enum СТРАД
define( 'ASPECT_ru', 18 );                         // enum ВИД
// Coordiname ВИД states:
define( 'PERFECT_ru', 0 );                         // ВИД : СОВЕРШ
define( 'IMPERFECT_ru', 1 );                       // ВИД : НЕСОВЕРШ
define( 'VERB_FORM_ru', 20 );                      // enum НАКЛОНЕНИЕ
// Coordiname НАКЛОНЕНИЕ states:
define( 'VB_INF_ru', 0 );                          // НАКЛОНЕНИЕ : ИЗЪЯВ
define( 'VB_ORDER_ru', 1 );                        // НАКЛОНЕНИЕ : ПОБУД
define( 'TENSE_ru', 21 );                          // enum ВРЕМЯ
// Coordiname ВРЕМЯ states:
define( 'PAST_ru', 0 );                            // ВРЕМЯ : ПРОШЕДШЕЕ
define( 'PRESENT_ru', 1 );                         // ВРЕМЯ : НАСТОЯЩЕЕ
define( 'FUTURE_ru', 2 );                          // ВРЕМЯ : БУДУЩЕЕ
define( 'SHORTNESS_ru', 22 );                      // enum КРАТКИЙ
define( 'CASE_ru', 24 );                           // enum ПАДЕЖ
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
define( 'FORM_ru', 25 );                           // enum ОДУШ
// Coordiname ОДУШ states:
define( 'ANIMATIVE_FORM_ru', 0 );                  // ОДУШ : ОДУШ
define( 'INANIMATIVE_FORM_ru', 1 );                // ОДУШ : НЕОДУШ
define( 'COUNTABILITY_ru', 26 );                   // enum ПЕРЕЧИСЛИМОСТЬ
// Coordiname ПЕРЕЧИСЛИМОСТЬ states:
define( 'COUNTABLE_ru', 0 );                       // ПЕРЕЧИСЛИМОСТЬ : ДА
define( 'UNCOUNTABLE_ru', 1 );                     // ПЕРЕЧИСЛИМОСТЬ : НЕТ
define( 'COMPAR_FORM_ru', 27 );                    // enum СТЕПЕНЬ
// Coordiname СТЕПЕНЬ states:
define( 'ATTRIBUTIVE_FORM_ru', 0 );                // СТЕПЕНЬ : АТРИБ
define( 'COMPARATIVE_FORM_ru', 1 );                // СТЕПЕНЬ : СРАВН
define( 'SUPERLATIVE_FORM_ru', 2 );                // СТЕПЕНЬ : ПРЕВОСХ
define( 'CASE_GERUND_ru', 28 );                    // enum ПадежВал
// Coordiname ПадежВал states:
define( 'MODAL_ru', 29 );                          // enum МОДАЛЬНЫЙ
define( 'VERBMODE_TENSE', 30 );                    // enum СГД_Время
// Coordiname СГД_Время states:
define( 'VERBMODE_DIRECTION', 31 );                // enum СГД_Направление
// Coordiname СГД_Направление states:
define( 'NUMERAL_CATEGORY', 32 );                  // enum КАТЕГОРИЯ_ЧИСЛ
// Coordiname КАТЕГОРИЯ_ЧИСЛ states:
define( 'CARDINAL', 0 );                           // КАТЕГОРИЯ_ЧИСЛ : КОЛИЧ
define( 'COLLECTION', 1 );                         // КАТЕГОРИЯ_ЧИСЛ : СОБИР
define( 'ADV_SEMANTICS', 33 );                     // enum ОБСТ_ВАЛ
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
define( 'ADJ_TYPE', 34 );                          // enum ТИП_ПРИЛ
// Coordiname ТИП_ПРИЛ states:
define( 'ADJ_POSSESSIVE', 0 );                     // ТИП_ПРИЛ : ПРИТЯЖ
define( 'ADJ_ORDINAL', 1 );                        // ТИП_ПРИЛ : ПОРЯДК
define( 'TENSE_en', 40 );                          // enum TENSE
// Coordiname TENSE states:
define( 'PAST_en', 0 );                            // TENSE : PAST
define( 'PRESENT_en', 1 );                         // TENSE : PRESENT
define( 'FUTURE_en', 2 );                          // TENSE : FUTURE
define( 'DURATION_en', 41 );                       // enum DURATION
// Coordiname DURATION states:
define( 'SIMPLE_en', 0 );                          // DURATION : INDEFINITE
define( 'CONTINUOUS_en', 1 );                      // DURATION : CONTINUOUS
define( 'PERFECT_en', 2 );                         // DURATION : PERFECT
define( 'PERFECT_CONTINUOS_en', 3 );               // DURATION : PERFECT_CONTINUOUS
define( 'VOICE_en', 42 );                          // enum VOICE
// Coordiname VOICE states:
define( 'PASSIVE_en', 0 );                         // VOICE : PASSIVE
define( 'ACTIVE_en', 1 );                          // VOICE : ACTIVE
define( 'CASE_en', 43 );                           // enum CASE
// Coordiname CASE states:
define( 'NOMINATIVE_CASE_en', 0 );                 // CASE : NOMINATIVE
define( 'PREPOSITIVE_CASE_en', 1 );                // CASE : PREPOSITIVE
define( 'NOUN_FORM_en', 44 );                      // enum NOUN_FORM
// Coordiname NOUN_FORM states:
define( 'BASIC_NOUN_FORM_en', 0 );                 // NOUN_FORM : BASIC
define( 'POSSESSIVE_NOUN_FORM_en', 1 );            // NOUN_FORM : POSSESSIVE
define( 'PRONOUN_FORM_en', 45 );                   // enum PRONOUN_FORM
// Coordiname PRONOUN_FORM states:
define( 'ADJ_FORM_en', 46 );                       // enum ADJ_FORM
// Coordiname ADJ_FORM states:
define( 'BASIC_ADJ_en', 0 );                       // ADJ_FORM : BASIC
define( 'COMPARATIVE_ADJ_en', 1 );                 // ADJ_FORM : COMPARATIVE
define( 'SUPERLATIVE_ADJ_en', 2 );                 // ADJ_FORM : SUPERLATIVE
define( 'COMPARABILITY_en', 47 );                  // enum COMPARABILITY
// Coordiname COMPARABILITY states:
define( 'ANALYTIC_en', 0 );                        // COMPARABILITY : ANALYTIC
define( 'SYNTHETIC_en', 1 );                       // COMPARABILITY : SYNTHETIC
define( 'COMPARABLE_en', 2 );                      // COMPARABILITY : COMPARABLE
define( 'NONCOMPARABLE', 3 );                      // COMPARABILITY : NONCOMPARABLE
define( 'VERB_FORM_en', 48 );                      // enum VERB_FORM
// Coordiname VERB_FORM states:
define( 'UNDEF_VERBFORM_en', 0 );                  // VERB_FORM : UNDEF
define( 'ED_VERBFORM_en', 1 );                     // VERB_FORM : ED
define( 'ING_VERBFORM_en', 2 );                    // VERB_FORM : ING
define( 'PP_VERBFORM_en', 3 );                     // VERB_FORM : PP
define( 'INF_VEBFORM_en', 4 );                     // VERB_FORM : INF
define( 'ARTICLE_FORM', 49 );                      // enum ARTICLE_FORM
// Coordiname ARTICLE_FORM states:
define( 'ARTICLE_FORM_1', 0 );                     // ARTICLE_FORM : 1
define( 'ARTICLE_FORM_2', 1 );                     // ARTICLE_FORM : 2
define( 'ENG_MODALITY', 50 );                      // enum ENG_MODALITY
// Coordiname ENG_MODALITY states:
define( 'DIRECT_MODALITY_en', 0 );                 // ENG_MODALITY : Direct
define( 'TO_MODALITY_en', 2 );                     // ENG_MODALITY : To
define( 'NUMERAL_FORM_en', 51 );                   // enum NUMERAL_FORM
// Coordiname NUMERAL_FORM states:
define( 'CARDINAL_en', 0 );                        // NUMERAL_FORM : CARDINAL
define( 'ORDINAL_en', 1 );                         // NUMERAL_FORM : ORDINAL
define( 'GENDER_en', 52 );                         // enum ENG_GENDER
// Coordiname ENG_GENDER states:
define( 'MASCULINE_en', 0 );                       // ENG_GENDER : MASCULINE
define( 'FEMININE_en', 1 );                        // ENG_GENDER : FEMININE
define( 'TRANSITIVITY_en', 53 );                   // enum TRANSITIVITY
// Coordiname TRANSITIVITY states:
define( 'INTRANSITIVE_VERB_en', 0 );               // TRANSITIVITY : INTRANSITIVE
define( 'TRANSITIVE_VERB_en', 1 );                 // TRANSITIVITY : TRANSITIVE
define( 'OBLIG_TRANSITIVITY_en', 54 );             // enum OBLIG_TRANSITIVITY
define( 'PROPER_NOUN_en', 55 );                    // enum ENG_PROPER_NOUN
define( 'MASS_NOUN_en', 56 );                      // enum ENG_MASS_NOUN
define( 'PERSON_fr', 57 );                         // enum FR_PERSON
// Coordiname FR_PERSON states:
define( 'PERSON_1_fr', 0 );                        // FR_PERSON : 1
define( 'PERSON_2_fr', 1 );                        // FR_PERSON : 2
define( 'PERSON_3_fr', 2 );                        // FR_PERSON : 3
define( 'NUMBER_fr', 58 );                         // enum FR_NOMBRE
// Coordiname FR_NOMBRE states:
define( 'SINGULAR_fr', 0 );                        // FR_NOMBRE : SINGULIER
define( 'PLURAL_fr', 1 );                          // FR_NOMBRE : PLURIEL
define( 'GENDER_fr', 59 );                         // enum FR_GENRE
// Coordiname FR_GENRE states:
define( 'MASCULINE_fr', 0 );                       // FR_GENRE : MASCULINE
define( 'FEMININE_fr', 1 );                        // FR_GENRE : FEMININE
define( 'FR_NUMERAL_FORM', 60 );                   // enum FR_NUMERAL_FORM
// Coordiname FR_NUMERAL_FORM states:
define( 'CARDINAL_fr', 0 );                        // FR_NUMERAL_FORM : CARDINAL
define( 'ORDINAL_fr', 1 );                         // FR_NUMERAL_FORM : ORDINAL
define( 'FR_PRONOUN_FORM', 61 );                   // enum FR_PRONOUN_FORM
// Coordiname FR_PRONOUN_FORM states:
define( 'FR_PRONOUN_WEAK', 0 );                    // FR_PRONOUN_FORM : WEAK
define( 'FR_PRONOUN_STRONG', 1 );                  // FR_PRONOUN_FORM : STRONG
define( 'TRANSITIVITY_fr', 62 );                   // enum FR_TRANSITIVITY
// Coordiname FR_TRANSITIVITY states:
define( 'INTRANSITIVE_VERB_fr', 0 );               // FR_TRANSITIVITY : INTRANSITIVE
define( 'TRANSITIVE_VERB_fr', 1 );                 // FR_TRANSITIVITY : TRANSITIVE
define( 'VERB_FORM_fr', 63 );                      // enum FR_VERB_FORM
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
define( 'JAP_FORM', 64 );                          // enum JAP_FORM
// Coordiname JAP_FORM states:
define( 'KANA_FORM', 0 );                          // JAP_FORM : KANA
define( 'KANJI_FORM', 1 );                         // JAP_FORM : KANJI
define( 'ROMAJI_FORM', 2 );                        // JAP_FORM : ROMAJI
define( 'JAP_VERB_BASE', 65 );                     // enum JAP_VERB_BASE
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
define( 'JAP_VERB_KIND', 66 );                     // enum JAP_VERB_KIND
// Coordiname JAP_VERB_KIND states:
define( 'JAP_PRESENT_FUTURE', 1 );                 // JAP_VERB_KIND : PRESENT_FUTURE
define( 'JAP_NEGATIVE_PRESENT_FUTURE', 3 );        // JAP_VERB_KIND : NEGATIVE_PRESENT_FUTURE
define( 'JAP_NEGATIVE_PAST', 4 );                  // JAP_VERB_KIND : NEGATIVE_PAST
define( 'JAP_IMPERATIVE', 5 );                     // JAP_VERB_KIND : IMPERATIVE
define( 'JAP_NEGATIVE_IMPERATIVE', 6 );            // JAP_VERB_KIND : NEGATIVE_IMPERATIVE
define( 'JAP_ADJ_BASE', 67 );                      // enum JAP_ADJ_BASE
// Coordiname JAP_ADJ_BASE states:
define( 'JAP_AB_I', 0 );                           // JAP_ADJ_BASE : I
define( 'JAP_AB_II', 1 );                          // JAP_ADJ_BASE : II
define( 'JAP_AB_III', 2 );                         // JAP_ADJ_BASE : III
define( 'JAP_AB_IV', 3 );                          // JAP_ADJ_BASE : IV
define( 'JAP_AB_V', 4 );                           // JAP_ADJ_BASE : V
define( 'JAP_AB_T', 5 );                           // JAP_ADJ_BASE : T
define( 'JAP_AB_PAST', 6 );                        // JAP_ADJ_BASE : PAST
define( 'JAP_ADJ_FORM2', 68 );                     // enum JAP_ADJ_FORM2
// Coordiname JAP_ADJ_FORM2 states:
define( 'JAP_NEGATIVE_PRESENT_ADJ', 0 );           // JAP_ADJ_FORM2 : NEGATIVE_PRESENT
define( 'JAP_NEGATIVE_PAST_ADJ', 1 );              // JAP_ADJ_FORM2 : NEGATIVE_PAST
define( 'JAP_TRANSITIVE', 69 );                    // enum JAP_TRANSITIVE
define( 'CASE_jap', 70 );                          // enum JAP_CASE
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
define( 'GENDER_jap', 71 );                        // enum JAP_GENDER
// Coordiname JAP_GENDER states:
define( 'MASCULINE_jap', 0 );                      // JAP_GENDER : MASCULINE
define( 'FEMININE_jap', 1 );                       // JAP_GENDER : FEMININE
define( 'PERSON_jap', 72 );                        // enum JAP_PERSON
// Coordiname JAP_PERSON states:
define( 'PERSON_1_jap', 0 );                       // JAP_PERSON : 1
define( 'PERSON_2_jap', 1 );                       // JAP_PERSON : 2
define( 'PERSON_3_jap', 2 );                       // JAP_PERSON : 3
define( 'NUMBER_jap', 73 );                        // enum JAP_NUMBER
// Coordiname JAP_NUMBER states:
define( 'SINGULAR_jap', 0 );                       // JAP_NUMBER : SINGULAR
define( 'PLURAL_jap', 1 );                         // JAP_NUMBER : PLURAL
define( 'JAP_PRONOUN_TYPE', 74 );                  // enum JAP_PRONOUN_TYPE
// Coordiname JAP_PRONOUN_TYPE states:
define( 'PERSONAL_jap', 0 );                       // JAP_PRONOUN_TYPE : PERSONAL
define( 'POINTING_jap', 1 );                       // JAP_PRONOUN_TYPE : POINTING
define( 'POSSESSIVE_jap', 2 );                     // JAP_PRONOUN_TYPE : POSSESSIVE
// ------------------------------------------------------------


define( 'OBJECT_link', 3 );
define( 'ATTRIBUTE_link', 4 );
define( 'CONDITION_link', 5 );
define( 'CONSEQUENCE_link', 6 );
define( 'SUBJECT_link', 7 );
define( 'RHEMA_link', 8 );
define( 'COVERB_link', 9 );
define( 'NUMBER2OBJ_link', 15 );
define( 'TO_VERB_link', 19 );
define( 'TO_INF_link', 20 );
define( 'TO_PERFECT', 21 );
define( 'TO_UNPERFECT', 22 );
define( 'TO_NOUN_link', 23 );
define( 'TO_ADJ_link', 24 );
define( 'TO_ADV_link', 25 );
define( 'TO_RETVERB', 26 );
define( 'TO_GERUND_2_link', 27 );
define( 'WOUT_RETVERB', 28 );
define( 'TO_ENGLISH_link', 29 );
define( 'TO_RUSSIAN_link', 30 );
define( 'TO_FRENCH_link', 31 );
define( 'SYNONYM_link', 32 );
define( 'SEX_SYNONYM_link', 33 );
define( 'CLASS_link', 34 );
define( 'MEMBER_link', 35 );
define( 'TO_SPANISH_link', 36 );
define( 'TO_GERMAN_link', 37 );
define( 'TO_CHINESE_link', 38 );
define( 'TO_POLAND_link', 39 );
define( 'TO_ITALIAN_link', 40 );
define( 'TO_PORTUGUAL_link', 41 );
define( 'ACTION_link', 42 );
define( 'ACTOR_link', 43 );
define( 'TOOL_link', 44 );
define( 'RESULT_link', 45 );
define( 'TO_JAPANESE_link', 46 );
define( 'TO_KANA_link', 47 );
define( 'TO_KANJI_link', 48 );
define( 'ANTONYM_link', 49 );
define( 'EXPLANATION_link', 50 );
define( 'WWW_link', 51 );
define( 'ACCENT_link', 52 );
define( 'YO_link', 53 );
define( 'TO_DIMINUITIVE_link', 54 );
define( 'TO_RUDE_link', 55 );
define( 'TO_BIGGER_link', 56 );
define( 'TO_NEUTRAL_link', 57 );
define( 'TO_SCOLARLY', 58 );
define( 'TO_SAMPLE_link', 59 );
define( 'USAGE_TAG_link', 60 );
define( 'PROPERTY_link', 61 );
define( 'TO_CYRIJI_link', 62 );
define( 'HABITANT_link', 63 );
define( 'CHILD_link', 64 );
define( 'PARENT_link', 65 );
define( 'UNIT_link', 66 );
define( 'SET_link', 67 );
define( 'TO_WEAKENED_link', 68 );
define( 'VERBMODE_BASIC_link', 69 );
define( 'NEGATION_PARTICLE_link', 70 );
define( 'NEXT_COLLOCATION_ITEM_link', 71 );
define( 'SUBORDINATE_CLAUSE_link', 72 );
define( 'RIGHT_GENITIVE_OBJECT_link', 73 );
define( 'ADV_PARTICIPLE_link', 74 );
define( 'POSTFIX_PARTICLE_link', 75 );
define( 'INFINITIVE_link', 76 );
define( 'NEXT_ADJECTIVE_link', 77 );
define( 'NEXT_NOUN_link', 78 );
define( 'THEMA_link', 79 );
define( 'RIGHT_PARTICLE_link', 80 );
define( 'RIGHT_AUX2INFINITIVE_link', 81 );
define( 'RIGHT_AUX2PARTICIPLE', 82 );
define( 'RIGHT_AUX2ADJ', 83 );
define( 'RIGHT_LOGIC_ITEM_link', 84 );
define( 'RIGHT_COMPARISON_Y_link', 85 );
define( 'RIGHT_NOUN_link', 86 );
define( 'RIGHT_INSTR_OBJECT_link', 87 );
define( 'RIGHT_DATIVE_OBJECT_link', 88 );
define( 'RIGHT_NAME_link', 89 );
define( 'ADJ_PARTICIPLE_link', 90 );
define( 'PUNCTUATION_link', 91 );
define( 'IMPERATIVE_SUBJECT_link', 92 );
define( 'IMPERATIVE_VERB2AUX_link', 93 );
define( 'AUX2IMPERATIVE_VERB', 94 );
define( 'PREFIX_PARTICLE_link', 95 );
define( 'PREFIX_CONJUNCTION_link', 96 );
define( 'LOGICAL_CONJUNCTION_link', 97 );
define( 'NEXT_CLAUSE_link', 98 );
define( 'LEFT_AUX_VERB_link', 99 );
define( 'BEG_INTRO_link', 100 );
define( 'RIGHT_PREPOSITION_link', 101 );
define( 'WH_SUBJECT_link', 102 );
define( 'IMPERATIVE_PARTICLE_link', 103 );
define( 'GERUND_link', 104 );
define( 'PREPOS_ADJUNCT_link', 105 );
define( 'DIRECT_OBJ_INTENTION_link', 106 );
define( 'COPULA_link', 107 );
define( 'DETAILS_link', 108 );
define( 'SENTENCE_CLOSER_link', 109 );
define( 'OPINION_link', 110 );
define( 'APPEAL_link', 111 );
define( 'TERM_link', 112 );
define( 'SPEECH_link', 113 );
define( 'QUESTION_link', 114 );
define( 'POLITENESS_link', 115 );
define( 'SEPARATE_ATTR_link', 116 );

?>
