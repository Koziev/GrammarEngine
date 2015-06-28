// This file is generated 26.01.2015 14:35:25 by Ygres compiler ver. 13.34.11134 Standard Win32  (build date Jan 25 2015).
// Languages
const int RUSSIAN_LANGUAGE = 2;                    // language Russian
const int ENGLISH_LANGUAGE = 3;                    // language English
const int FRENCH_LANGUAGE = 4;                     // language French
const int SPANISH_LANGUAGE = 5;                    // language Spanish
const int CHINESE_LANGUAGE = 6;                    // language Chinese
const int JAPANESE_LANGUAGE = 7;                   // language Japanese
const int GERMAN_LANGUAGE = 8;                     // language German
const int THESAURUS_LANGUAGE = 9;                  // language ThesaurusLanguage
// ------------------------------------------------------------


const int NUM_WORD_CLASS = 3;                      // class num_word
const int NOUN_ru = 7;                             // class СУЩЕСТВИТЕЛЬНОЕ
const int PRONOUN2_ru = 8;                         // class МЕСТОИМ_СУЩ
const int PRONOUN_ru = 9;                          // class МЕСТОИМЕНИЕ
const int ADJ_ru = 10;                             // class ПРИЛАГАТЕЛЬНОЕ
const int NUMBER_CLASS_ru = 11;                    // class ЧИСЛИТЕЛЬНОЕ
const int INFINITIVE_ru = 12;                      // class ИНФИНИТИВ
const int VERB_ru = 13;                            // class ГЛАГОЛ
const int GERUND_2_ru = 14;                        // class ДЕЕПРИЧАСТИЕ
const int PREPOS_ru = 15;                          // class ПРЕДЛОГ
const int IMPERSONAL_VERB_ru = 16;                 // class БЕЗЛИЧ_ГЛАГОЛ
const int PARTICLE_ru = 19;                        // class ЧАСТИЦА
const int CONJ_ru = 20;                            // class СОЮЗ
const int ADVERB_ru = 21;                          // class НАРЕЧИЕ
const int PUNCTUATION_class = 22;                  // class ПУНКТУАТОР
const int POSTPOS_ru = 27;                         // class ПОСЛЕЛОГ
const int POSESS_PARTICLE = 28;                    // class ПРИТЯЖ_ЧАСТИЦА
const int MEASURE_UNIT = 29;                       // class ЕДИНИЦА_ИЗМЕРЕНИЯ
const int VERB_en = 30;                            // class ENG_VERB
const int NOUN_en = 31;                            // class ENG_NOUN
const int PRONOUN_en = 32;                         // class ENG_PRONOUN
const int ARTICLE_en = 33;                         // class ENG_ARTICLE
const int PREP_en = 34;                            // class ENG_PREP
const int CONJ_en = 35;                            // class ENG_CONJ
const int ADV_en = 36;                             // class ENG_ADVERB
const int ADJ_en = 37;                             // class ENG_ADJECTIVE
const int PARTICLE_en = 38;                        // class ENG_PARTICLE
const int NUMERAL_en = 39;                         // class ENG_NUMERAL
const int INTERJECTION_en = 40;                    // class ENG_INTERJECTION
const int NUMERAL_fr = 41;                         // class FR_NUMERAL
const int ARTICLE_fr = 42;                         // class FR_ARTICLE
const int PREP_fr = 43;                            // class FR_PREP
const int ADV_fr = 44;                             // class FR_ADVERB
const int CONJ_fr = 45;                            // class FR_CONJ
const int NOUN_fr = 46;                            // class FR_NOUN
const int ADJ_fr = 47;                             // class FR_ADJ
const int PRONOUN_fr = 48;                         // class FR_PRONOUN
const int VERB_fr = 49;                            // class FR_VERB
const int PARTICLE_fr = 50;                        // class FR_PARTICLE
const int PRONOUN2_fr = 51;                        // class FR_PRONOUN2
const int NOUN_es = 52;                            // class ES_NOUN
const int ROOT_es = 53;                            // class ES_ROOT
const int JAP_NOUN = 54;                           // class JAP_NOUN
const int JAP_NUMBER = 55;                         // class JAP_NUMBER
const int JAP_ADJECTIVE = 56;                      // class JAP_ADJECTIVE
const int JAP_ADVERB = 57;                         // class JAP_ADVERB
const int JAP_CONJ = 58;                           // class JAP_CONJ
const int JAP_VERB = 59;                           // class JAP_VERB
const int JAP_PRONOUN = 60;                        // class JAP_PRONOUN
const int JAP_VERB_POSTFIX2 = 63;                  // class JAP_VERB_POSTFIX2
const int JAP_PARTICLE = 65;                       // class JAP_PARTICLE
const int UNKNOWN_ENTRIES_CLASS = 76;              // class UnknownEntries
// ------------------------------------------------------------



const int CharCasing = 5;                          // enum CharCasing
// Coordiname CharCasing states:
const int DECAPITALIZED_CASED = 0;                 // CharCasing : Lower
const int FIRST_CAPITALIZED_CASED = 1;             // CharCasing : FirstCapitalized
const int ALL_CAPITALIZED_CASED = 2;               // CharCasing : Upper
const int EACH_LEXEM_CAPITALIZED_CASED = 3;        // CharCasing : EachLexemCapitalized

const int PERSON_xx = 7;                           // enum PERSON
// Coordiname PERSON states:
const int PERSON_1_xx = 0;                         // PERSON : 1
const int PERSON_2_xx = 1;                         // PERSON : 2
const int PERSON_3_xx = 2;                         // PERSON : 3

const int NUMBER_xx = 8;                           // enum NUMBER
// Coordiname NUMBER states:
const int SINGLE_xx = 0;                           // NUMBER : SINGLE
const int PLURAL_xx = 1;                           // NUMBER : PLURAL

const int GENDER_xx = 9;                           // enum GENDER
// Coordiname GENDER states:
const int MASCULINE_xx = 0;                        // GENDER : MASCULINE
const int FEMININE_xx = 1;                         // GENDER : FEMININE
const int NEUTRAL_xx = 2;                          // GENDER : NEUTRAL

const int SPEECH_STYLE_xx = 10;                    // enum СтильРечи
// Coordiname СтильРечи states:

const int STRENGTH_xx = 11;                        // enum РазмерСила
// Coordiname РазмерСила states:

const int PERSON_ru = 12;                          // enum ЛИЦО
// Coordiname ЛИЦО states:
const int PERSON_1_ru = 0;                         // ЛИЦО : 1
const int PERSON_2_ru = 1;                         // ЛИЦО : 2
const int PERSON_3_ru = 2;                         // ЛИЦО : 3

const int NUMBER_ru = 13;                          // enum ЧИСЛО
// Coordiname ЧИСЛО states:
const int SINGULAR_NUMBER_ru = 0;                  // ЧИСЛО : ЕД
const int PLURAL_NUMBER_ru = 1;                    // ЧИСЛО : МН

const int GENDER_ru = 14;                          // enum РОД
// Coordiname РОД states:
const int MASCULINE_GENDER_ru = 0;                 // РОД : МУЖ
const int FEMININE_GENDER_ru = 1;                  // РОД : ЖЕН
const int NEUTRAL_GENDER_ru = 2;                   // РОД : СР

const int TRANSITIVENESS_ru = 15;                  // enum ПЕРЕХОДНОСТЬ
// Coordiname ПЕРЕХОДНОСТЬ states:
const int NONTRANSITIVE_VERB_ru = 0;               // ПЕРЕХОДНОСТЬ : НЕПЕРЕХОДНЫЙ
const int TRANSITIVE_VERB_ru = 1;                  // ПЕРЕХОДНОСТЬ : ПЕРЕХОДНЫЙ

const int PARTICIPLE_ru = 16;                      // enum ПРИЧАСТИЕ

const int PASSIVE_PARTICIPLE_ru = 17;              // enum СТРАД

const int ASPECT_ru = 18;                          // enum ВИД
// Coordiname ВИД states:
const int PERFECT_ru = 0;                          // ВИД : СОВЕРШ
const int IMPERFECT_ru = 1;                        // ВИД : НЕСОВЕРШ

const int VERB_FORM_ru = 20;                       // enum НАКЛОНЕНИЕ
// Coordiname НАКЛОНЕНИЕ states:
const int VB_INF_ru = 0;                           // НАКЛОНЕНИЕ : ИЗЪЯВ
const int VB_ORDER_ru = 1;                         // НАКЛОНЕНИЕ : ПОБУД

const int TENSE_ru = 21;                           // enum ВРЕМЯ
// Coordiname ВРЕМЯ states:
const int PAST_ru = 0;                             // ВРЕМЯ : ПРОШЕДШЕЕ
const int PRESENT_ru = 1;                          // ВРЕМЯ : НАСТОЯЩЕЕ
const int FUTURE_ru = 2;                           // ВРЕМЯ : БУДУЩЕЕ

const int SHORTNESS_ru = 22;                       // enum КРАТКИЙ

const int CASE_ru = 24;                            // enum ПАДЕЖ
// Coordiname ПАДЕЖ states:
const int NOMINATIVE_CASE_ru = 0;                  // ПАДЕЖ : ИМ
const int VOCATIVE_CASE_ru = 1;                    // ЗВАТ
const int GENITIVE_CASE_ru = 2;                    // ПАДЕЖ : РОД
const int PARTITIVE_CASE_ru = 3;                   // ПАРТ
const int INSTRUMENTAL_CASE_ru = 5;                // ПАДЕЖ : ТВОР
const int ACCUSATIVE_CASE_ru = 6;                  // ПАДЕЖ : ВИН
const int DATIVE_CASE_ru = 7;                      // ПАДЕЖ : ДАТ
const int PREPOSITIVE_CASE_ru = 8;                 // ПАДЕЖ : ПРЕДЛ
const int LOCATIVE_CASE_ru = 10;                   // МЕСТ

const int FORM_ru = 25;                            // enum ОДУШ
// Coordiname ОДУШ states:
const int ANIMATIVE_FORM_ru = 0;                   // ОДУШ : ОДУШ
const int INANIMATIVE_FORM_ru = 1;                 // ОДУШ : НЕОДУШ

const int COUNTABILITY_ru = 26;                    // enum ПЕРЕЧИСЛИМОСТЬ
// Coordiname ПЕРЕЧИСЛИМОСТЬ states:
const int COUNTABLE_ru = 0;                        // ПЕРЕЧИСЛИМОСТЬ : ДА
const int UNCOUNTABLE_ru = 1;                      // ПЕРЕЧИСЛИМОСТЬ : НЕТ

const int COMPAR_FORM_ru = 27;                     // enum СТЕПЕНЬ
// Coordiname СТЕПЕНЬ states:
const int ATTRIBUTIVE_FORM_ru = 0;                 // СТЕПЕНЬ : АТРИБ
const int COMPARATIVE_FORM_ru = 1;                 // СТЕПЕНЬ : СРАВН
const int SUPERLATIVE_FORM_ru = 2;                 // СТЕПЕНЬ : ПРЕВОСХ
const int LIGHT_COMPAR_FORM_RU = 3;                // СТЕПЕНЬ : КОМПАРАТИВ2

const int CASE_GERUND_ru = 28;                     // enum ПадежВал
// Coordiname ПадежВал states:

const int MODAL_ru = 29;                           // enum МОДАЛЬНЫЙ

const int VERBMODE_TENSE = 30;                     // enum СГД_Время
// Coordiname СГД_Время states:

const int VERBMODE_DIRECTION = 31;                 // enum СГД_Направление
// Coordiname СГД_Направление states:

const int NUMERAL_CATEGORY = 32;                   // enum КАТЕГОРИЯ_ЧИСЛ
// Coordiname КАТЕГОРИЯ_ЧИСЛ states:
const int CARDINAL = 0;                            // КАТЕГОРИЯ_ЧИСЛ : КОЛИЧ
const int COLLECTION = 1;                          // КАТЕГОРИЯ_ЧИСЛ : СОБИР

const int ADV_SEMANTICS = 33;                      // enum ОБСТ_ВАЛ
// Coordiname ОБСТ_ВАЛ states:
const int S_LOCATION = 0;                          // ОБСТ_ВАЛ : МЕСТО
const int S_DIRECTION = 1;                         // ОБСТ_ВАЛ : НАПРАВЛЕНИЕ
const int S_DIRECTION_FROM = 2;                    // ОБСТ_ВАЛ : НАПРАВЛЕНИЕ_ОТКУДА
const int S_FINAL_POINT = 3;                       // ОБСТ_ВАЛ : КОНЕЧНАЯ_ТОЧКА
const int S_DISTANCE = 4;                          // ОБСТ_ВАЛ : РАССТОЯНИЕ
const int S_VELOCITY = 5;                          // ОБСТ_ВАЛ : СКОРОСТЬ
const int S_MOMENT = 6;                            // ОБСТ_ВАЛ : МОМЕНТ_ВРЕМЕНИ
const int S_DURATION = 7;                          // ОБСТ_ВАЛ : ДЛИТЕЛЬНОСТЬ
const int S_TIME_DIVISIBILITY = 8;                 // ОБСТ_ВАЛ : КРАТНОСТЬ
const int S_ANALOG = 9;                            // ОБСТ_ВАЛ : СОПОСТАВЛЕНИЕ
const int S_FACTOR = 10;                           // ОБСТ_ВАЛ : МНОЖИТЕЛЬ

const int ADJ_TYPE = 34;                           // enum ТИП_ПРИЛ
// Coordiname ТИП_ПРИЛ states:
const int ADJ_POSSESSIVE = 0;                      // ТИП_ПРИЛ : ПРИТЯЖ
const int ADJ_ORDINAL = 1;                         // ТИП_ПРИЛ : ПОРЯДК

const int PARTICLE_TYPE = 36;                      // enum ТИП_ЧАСТИЦЫ
// Coordiname ТИП_ЧАСТИЦЫ states:
const int PREFIX_PARTICLE = 0;                     // ТИП_ЧАСТИЦЫ : ПРЕФИКС
const int POSTFIX_PARTICLE = 1;                    // ТИП_ЧАСТИЦЫ : ПОСТФИКС

const int TENSE_en = 43;                           // enum TENSE
// Coordiname TENSE states:
const int PAST_en = 0;                             // TENSE : PAST
const int PRESENT_en = 1;                          // TENSE : PRESENT
const int FUTURE_en = 2;                           // TENSE : FUTURE

const int DURATION_en = 44;                        // enum DURATION
// Coordiname DURATION states:
const int SIMPLE_en = 0;                           // DURATION : INDEFINITE
const int CONTINUOUS_en = 1;                       // DURATION : CONTINUOUS
const int PERFECT_en = 2;                          // DURATION : PERFECT
const int PERFECT_CONTINUOS_en = 3;                // DURATION : PERFECT_CONTINUOUS

const int VOICE_en = 45;                           // enum VOICE
// Coordiname VOICE states:
const int PASSIVE_en = 0;                          // VOICE : PASSIVE
const int ACTIVE_en = 1;                           // VOICE : ACTIVE

const int CASE_en = 46;                            // enum CASE
// Coordiname CASE states:
const int NOMINATIVE_CASE_en = 0;                  // CASE : NOMINATIVE
const int PREPOSITIVE_CASE_en = 1;                 // CASE : PREPOSITIVE

const int NOUN_FORM_en = 47;                       // enum NOUN_FORM
// Coordiname NOUN_FORM states:
const int BASIC_NOUN_FORM_en = 0;                  // NOUN_FORM : BASIC
const int POSSESSIVE_NOUN_FORM_en = 1;             // NOUN_FORM : POSSESSIVE

const int PRONOUN_FORM_en = 48;                    // enum PRONOUN_FORM
// Coordiname PRONOUN_FORM states:

const int ADJ_FORM_en = 49;                        // enum ADJ_FORM
// Coordiname ADJ_FORM states:
const int BASIC_ADJ_en = 0;                        // ADJ_FORM : BASIC
const int COMPARATIVE_ADJ_en = 1;                  // ADJ_FORM : COMPARATIVE
const int SUPERLATIVE_ADJ_en = 2;                  // ADJ_FORM : SUPERLATIVE

const int COMPARABILITY_en = 50;                   // enum COMPARABILITY
// Coordiname COMPARABILITY states:
const int ANALYTIC_en = 0;                         // COMPARABILITY : ANALYTIC
const int SYNTHETIC_en = 1;                        // COMPARABILITY : SYNTHETIC
const int COMPARABLE_en = 2;                       // COMPARABILITY : COMPARABLE
const int NONCOMPARABLE = 3;                       // COMPARABILITY : NONCOMPARABLE

const int VERB_FORM_en = 51;                       // enum VERB_FORM
// Coordiname VERB_FORM states:
const int UNDEF_VERBFORM_en = 0;                   // VERB_FORM : UNDEF
const int ED_VERBFORM_en = 1;                      // VERB_FORM : ED
const int ING_VERBFORM_en = 2;                     // VERB_FORM : ING
const int PP_VERBFORM_en = 3;                      // VERB_FORM : PP
const int INF_VEBFORM_en = 4;                      // VERB_FORM : INF

const int ARTICLE_FORM = 52;                       // enum ARTICLE_FORM
// Coordiname ARTICLE_FORM states:
const int ARTICLE_FORM_1 = 0;                      // ARTICLE_FORM : 1
const int ARTICLE_FORM_2 = 1;                      // ARTICLE_FORM : 2

const int ENG_MODALITY = 53;                       // enum ENG_MODALITY
// Coordiname ENG_MODALITY states:
const int DIRECT_MODALITY_en = 0;                  // ENG_MODALITY : Direct
const int TO_MODALITY_en = 2;                      // ENG_MODALITY : To

const int NUMERAL_FORM_en = 54;                    // enum NUMERAL_FORM
// Coordiname NUMERAL_FORM states:
const int CARDINAL_en = 0;                         // NUMERAL_FORM : CARDINAL
const int ORDINAL_en = 1;                          // NUMERAL_FORM : ORDINAL

const int GENDER_en = 55;                          // enum ENG_GENDER
// Coordiname ENG_GENDER states:
const int MASCULINE_en = 0;                        // ENG_GENDER : MASCULINE
const int FEMININE_en = 1;                         // ENG_GENDER : FEMININE

const int TRANSITIVITY_en = 56;                    // enum TRANSITIVITY
// Coordiname TRANSITIVITY states:
const int INTRANSITIVE_VERB_en = 0;                // TRANSITIVITY : INTRANSITIVE
const int TRANSITIVE_VERB_en = 1;                  // TRANSITIVITY : TRANSITIVE

const int OBLIG_TRANSITIVITY_en = 57;              // enum OBLIG_TRANSITIVITY

const int PROPER_NOUN_en = 58;                     // enum ENG_PROPER_NOUN

const int MASS_NOUN_en = 59;                       // enum ENG_MASS_NOUN

const int PERSON_fr = 60;                          // enum FR_PERSON
// Coordiname FR_PERSON states:
const int PERSON_1_fr = 0;                         // FR_PERSON : 1
const int PERSON_2_fr = 1;                         // FR_PERSON : 2
const int PERSON_3_fr = 2;                         // FR_PERSON : 3

const int NUMBER_fr = 61;                          // enum FR_NOMBRE
// Coordiname FR_NOMBRE states:
const int SINGULAR_fr = 0;                         // FR_NOMBRE : SINGULIER
const int PLURAL_fr = 1;                           // FR_NOMBRE : PLURIEL

const int GENDER_fr = 62;                          // enum FR_GENRE
// Coordiname FR_GENRE states:
const int MASCULINE_fr = 0;                        // FR_GENRE : MASCULINE
const int FEMININE_fr = 1;                         // FR_GENRE : FEMININE

const int FR_NUMERAL_FORM = 63;                    // enum FR_NUMERAL_FORM
// Coordiname FR_NUMERAL_FORM states:
const int CARDINAL_fr = 0;                         // FR_NUMERAL_FORM : CARDINAL
const int ORDINAL_fr = 1;                          // FR_NUMERAL_FORM : ORDINAL

const int FR_PRONOUN_FORM = 64;                    // enum FR_PRONOUN_FORM
// Coordiname FR_PRONOUN_FORM states:
const int FR_PRONOUN_WEAK = 0;                     // FR_PRONOUN_FORM : WEAK
const int FR_PRONOUN_STRONG = 1;                   // FR_PRONOUN_FORM : STRONG

const int TRANSITIVITY_fr = 65;                    // enum FR_TRANSITIVITY
// Coordiname FR_TRANSITIVITY states:
const int INTRANSITIVE_VERB_fr = 0;                // FR_TRANSITIVITY : INTRANSITIVE
const int TRANSITIVE_VERB_fr = 1;                  // FR_TRANSITIVITY : TRANSITIVE

const int VERB_FORM_fr = 66;                       // enum FR_VERB_FORM
// Coordiname FR_VERB_FORM states:
const int INFINITIVE_fr = 0;                       // FR_VERB_FORM : INFINITIVE
const int PRESENT_VF_fr = 1;                       // FR_VERB_FORM : PRESENT
const int FUTURE_VF_fr = 2;                        // FR_VERB_FORM : FUTURE
const int IMPERFECT_VB_fr = 3;                     // FR_VERB_FORM : IMPERFECT
const int SIMPLE_PAST_fr = 4;                      // FR_VERB_FORM : SIMPLE_PAST
const int PRESENT_PARTICIPLE_fr = 5;               // FR_VERB_FORM : PRESENT_PARTICIPLE
const int PAST_PARTICIPLE_fr = 6;                  // FR_VERB_FORM : PAST_PARTICIPLE
const int SUBJUNCTIVE_PRESENT_fr = 7;              // FR_VERB_FORM : SUBJUNCTIVE_PRESENT
const int SUBJUNCTIVE_IMPERFECT_fr = 8;            // FR_VERB_FORM : SUBJUNCTIVE_IMPERFECT
const int CONDITIONAL_fr = 9;                      // FR_VERB_FORM : CONDITIONAL
const int IMPERATIVE_fr = 10;                      // FR_VERB_FORM : IMPERATIVE

const int JAP_FORM = 67;                           // enum JAP_FORM
// Coordiname JAP_FORM states:
const int KANA_FORM = 0;                           // JAP_FORM : KANA
const int KANJI_FORM = 1;                          // JAP_FORM : KANJI
const int ROMAJI_FORM = 2;                         // JAP_FORM : ROMAJI

const int JAP_VERB_BASE = 68;                      // enum JAP_VERB_BASE
// Coordiname JAP_VERB_BASE states:
const int JAP_VB_I = 0;                            // JAP_VERB_BASE : I
const int JAP_VB_II = 1;                           // JAP_VERB_BASE : II
const int JAP_VB_III = 2;                          // JAP_VERB_BASE : III
const int JAP_VB_IV = 3;                           // JAP_VERB_BASE : IV
const int JAP_VB_V = 4;                            // JAP_VERB_BASE : V
const int JAP_VB_PAST = 5;                         // JAP_VERB_BASE : PAST
const int JAP_VB_PARTICIPLE = 6;                   // JAP_VERB_BASE : PARTICIPLE
const int JAP_VB_POTENTIAL = 7;                    // JAP_VERB_BASE : POTENTIAL
const int JAP_VB_CONDITIONAL = 8;                  // JAP_VERB_BASE : CONDITIONAL
const int JAP_VB_CAUSATIVE = 9;                    // JAP_VERB_BASE : CAUSATIVE

const int JAP_VERB_KIND = 69;                      // enum JAP_VERB_KIND
// Coordiname JAP_VERB_KIND states:
const int JAP_PRESENT_FUTURE = 1;                  // JAP_VERB_KIND : PRESENT_FUTURE
const int JAP_NEGATIVE_PRESENT_FUTURE = 3;         // JAP_VERB_KIND : NEGATIVE_PRESENT_FUTURE
const int JAP_NEGATIVE_PAST = 4;                   // JAP_VERB_KIND : NEGATIVE_PAST
const int JAP_IMPERATIVE = 5;                      // JAP_VERB_KIND : IMPERATIVE
const int JAP_NEGATIVE_IMPERATIVE = 6;             // JAP_VERB_KIND : NEGATIVE_IMPERATIVE

const int JAP_ADJ_BASE = 70;                       // enum JAP_ADJ_BASE
// Coordiname JAP_ADJ_BASE states:
const int JAP_AB_I = 0;                            // JAP_ADJ_BASE : I
const int JAP_AB_II = 1;                           // JAP_ADJ_BASE : II
const int JAP_AB_III = 2;                          // JAP_ADJ_BASE : III
const int JAP_AB_IV = 3;                           // JAP_ADJ_BASE : IV
const int JAP_AB_V = 4;                            // JAP_ADJ_BASE : V
const int JAP_AB_T = 5;                            // JAP_ADJ_BASE : T
const int JAP_AB_PAST = 6;                         // JAP_ADJ_BASE : PAST

const int JAP_ADJ_FORM2 = 71;                      // enum JAP_ADJ_FORM2
// Coordiname JAP_ADJ_FORM2 states:
const int JAP_NEGATIVE_PRESENT_ADJ = 0;            // JAP_ADJ_FORM2 : NEGATIVE_PRESENT
const int JAP_NEGATIVE_PAST_ADJ = 1;               // JAP_ADJ_FORM2 : NEGATIVE_PAST

const int JAP_TRANSITIVE = 72;                     // enum JAP_TRANSITIVE

const int CASE_jap = 73;                           // enum JAP_CASE
// Coordiname JAP_CASE states:
const int VOCATIVE_jap = 0;                        // JAP_CASE : VOCATIVE
const int NOMINATIVE_THEM_jap = 1;                 // JAP_CASE : NOMINATIVE_THEM
const int NOMINATIVE_RHEM_jap = 2;                 // JAP_CASE : NOMINATIVE_RHEM
const int ACCUSATIVE_jap = 3;                      // JAP_CASE : ACCUSATIVE
const int GENITIVE_jap = 4;                        // JAP_CASE : GENITIVE
const int DATIVE_jap = 5;                          // JAP_CASE : DATIVE
const int ALLATIVE_jap = 6;                        // JAP_CASE : ALLATIVE
const int INSTRUMENTATIVE_jap = 7;                 // JAP_CASE : INSTRUMENTATIVE
const int ELATIVE_jap = 8;                         // JAP_CASE : ELATIVE
const int LIMITIVE_jap = 9;                        // JAP_CASE : LIMITIVE
const int COMPARATIVE_jap = 10;                    // JAP_CASE : COMPARATIVE
const int COMITATIVE_jap = 11;                     // JAP_CASE : COMITATIVE
const int SOCIATIVE_jap = 12;                      // JAP_CASE : SOCIATIVE

const int GENDER_jap = 74;                         // enum JAP_GENDER
// Coordiname JAP_GENDER states:
const int MASCULINE_jap = 0;                       // JAP_GENDER : MASCULINE
const int FEMININE_jap = 1;                        // JAP_GENDER : FEMININE

const int PERSON_jap = 75;                         // enum JAP_PERSON
// Coordiname JAP_PERSON states:
const int PERSON_1_jap = 0;                        // JAP_PERSON : 1
const int PERSON_2_jap = 1;                        // JAP_PERSON : 2
const int PERSON_3_jap = 2;                        // JAP_PERSON : 3

const int NUMBER_jap = 76;                         // enum JAP_NUMBER
// Coordiname JAP_NUMBER states:
const int SINGULAR_jap = 0;                        // JAP_NUMBER : SINGULAR
const int PLURAL_jap = 1;                          // JAP_NUMBER : PLURAL

const int JAP_PRONOUN_TYPE = 77;                   // enum JAP_PRONOUN_TYPE
// Coordiname JAP_PRONOUN_TYPE states:
const int PERSONAL_jap = 0;                        // JAP_PRONOUN_TYPE : PERSONAL
const int POINTING_jap = 1;                        // JAP_PRONOUN_TYPE : POINTING
const int POSSESSIVE_jap = 2;                      // JAP_PRONOUN_TYPE : POSSESSIVE
// ------------------------------------------------------------


const int OBJECT_link = 3;
const int ATTRIBUTE_link = 4;
const int CONDITION_link = 5;
const int CONSEQUENCE_link = 6;
const int SUBJECT_link = 7;
const int RHEMA_link = 8;
const int COVERB_link = 9;
const int NUMBER2OBJ_link = 15;
const int TO_VERB_link = 19;
const int TO_INF_link = 20;
const int TO_PERFECT = 21;
const int TO_UNPERFECT = 22;
const int TO_NOUN_link = 23;
const int TO_ADJ_link = 24;
const int TO_ADV_link = 25;
const int TO_RETVERB = 26;
const int TO_GERUND_2_link = 27;
const int WOUT_RETVERB = 28;
const int TO_ENGLISH_link = 29;
const int TO_RUSSIAN_link = 30;
const int TO_FRENCH_link = 31;
const int SYNONYM_link = 32;
const int SEX_SYNONYM_link = 33;
const int CLASS_link = 34;
const int MEMBER_link = 35;
const int TO_SPANISH_link = 36;
const int TO_GERMAN_link = 37;
const int TO_CHINESE_link = 38;
const int TO_POLAND_link = 39;
const int TO_ITALIAN_link = 40;
const int TO_PORTUGUAL_link = 41;
const int ACTION_link = 42;
const int ACTOR_link = 43;
const int TOOL_link = 44;
const int RESULT_link = 45;
const int TO_JAPANESE_link = 46;
const int TO_KANA_link = 47;
const int TO_KANJI_link = 48;
const int ANTONYM_link = 49;
const int EXPLANATION_link = 50;
const int WWW_link = 51;
const int ACCENT_link = 52;
const int YO_link = 53;
const int TO_DIMINUITIVE_link = 54;
const int TO_RUDE_link = 55;
const int TO_BIGGER_link = 56;
const int TO_NEUTRAL_link = 57;
const int TO_SCOLARLY = 58;
const int TO_SAMPLE_link = 59;
const int USAGE_TAG_link = 60;
const int PROPERTY_link = 61;
const int TO_CYRIJI_link = 62;
const int HABITANT_link = 63;
const int CHILD_link = 64;
const int PARENT_link = 65;
const int UNIT_link = 66;
const int SET_link = 67;
const int TO_WEAKENED_link = 68;
const int VERBMODE_BASIC_link = 69;
const int NEGATION_PARTICLE_link = 70;
const int NEXT_COLLOCATION_ITEM_link = 71;
const int SUBORDINATE_CLAUSE_link = 72;
const int RIGHT_GENITIVE_OBJECT_link = 73;
const int ADV_PARTICIPLE_link = 74;
const int POSTFIX_PARTICLE_link = 75;
const int INFINITIVE_link = 76;
const int NEXT_ADJECTIVE_link = 77;
const int NEXT_NOUN_link = 78;
const int THEMA_link = 79;
const int RIGHT_AUX2INFINITIVE_link = 80;
const int RIGHT_AUX2PARTICIPLE = 81;
const int RIGHT_AUX2ADJ = 82;
const int RIGHT_LOGIC_ITEM_link = 83;
const int RIGHT_COMPARISON_Y_link = 84;
const int RIGHT_NOUN_link = 85;
const int RIGHT_NAME_link = 86;
const int ADJ_PARTICIPLE_link = 87;
const int PUNCTUATION_link = 88;
const int IMPERATIVE_SUBJECT_link = 89;
const int IMPERATIVE_VERB2AUX_link = 90;
const int AUX2IMPERATIVE_VERB = 91;
const int PREFIX_PARTICLE_link = 92;
const int PREFIX_CONJUNCTION_link = 93;
const int LOGICAL_CONJUNCTION_link = 94;
const int NEXT_CLAUSE_link = 95;
const int LEFT_AUX_VERB_link = 96;
const int BEG_INTRO_link = 97;
const int RIGHT_PREPOSITION_link = 98;
const int WH_SUBJECT_link = 99;
const int IMPERATIVE_PARTICLE_link = 100;
const int GERUND_link = 101;
const int PREPOS_ADJUNCT_link = 102;
const int DIRECT_OBJ_INTENTION_link = 103;
const int COPULA_link = 104;
const int DETAILS_link = 105;
const int SENTENCE_CLOSER_link = 106;
const int OPINION_link = 107;
const int APPEAL_link = 108;
const int TERM_link = 109;
const int SPEECH_link = 110;
const int QUESTION_link = 111;
const int POLITENESS_link = 112;
const int SEPARATE_ATTR_link = 113;
