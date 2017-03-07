namespace SolarixGrammarEngineNET
{
 public sealed class GrammarEngineAPI
 {
  public const string VERSION_MARK="This file is generated 28.01.2017 15:23:49 by Ygres compiler ver. 14.14.11192 Standard Win64  (build date Sep 21 2016).";
// Languages
 public const int RUSSIAN_LANGUAGE = 2;            // language Russian
 public const int ENGLISH_LANGUAGE = 3;            // language English
 public const int FRENCH_LANGUAGE = 4;             // language French
 public const int SPANISH_LANGUAGE = 5;            // language Spanish
 public const int CHINESE_LANGUAGE = 6;            // language Chinese
 public const int JAPANESE_LANGUAGE = 7;           // language Japanese
 public const int GERMAN_LANGUAGE = 8;             // language German
 public const int THESAURUS_LANGUAGE = 9;          // language ThesaurusLanguage
// ------------------------------------------------------------


 public const int NUM_WORD_CLASS = 2;              // class num_word
 public const int NOUN_ru = 6;                     // class СУЩЕСТВИТЕЛЬНОЕ
 public const int PRONOUN2_ru = 7;                 // class МЕСТОИМ_СУЩ
 public const int PRONOUN_ru = 8;                  // class МЕСТОИМЕНИЕ
 public const int ADJ_ru = 9;                      // class ПРИЛАГАТЕЛЬНОЕ
 public const int NUMBER_CLASS_ru = 10;            // class ЧИСЛИТЕЛЬНОЕ
 public const int INFINITIVE_ru = 11;              // class ИНФИНИТИВ
 public const int VERB_ru = 12;                    // class ГЛАГОЛ
 public const int GERUND_2_ru = 13;                // class ДЕЕПРИЧАСТИЕ
 public const int PREPOS_ru = 14;                  // class ПРЕДЛОГ
 public const int IMPERSONAL_VERB_ru = 15;         // class БЕЗЛИЧ_ГЛАГОЛ
 public const int PARTICLE_ru = 18;                // class ЧАСТИЦА
 public const int CONJ_ru = 19;                    // class СОЮЗ
 public const int ADVERB_ru = 20;                  // class НАРЕЧИЕ
 public const int PUNCTUATION_class = 21;          // class ПУНКТУАТОР
 public const int POSTPOS_ru = 26;                 // class ПОСЛЕЛОГ
 public const int POSESS_PARTICLE = 27;            // class ПРИТЯЖ_ЧАСТИЦА
 public const int MEASURE_UNIT = 28;               // class ЕДИНИЦА_ИЗМЕРЕНИЯ
 public const int COMPOUND_ADJ_PREFIX = 29;        // class ПРЕФИКС_СОСТАВ_ПРИЛ
 public const int COMPOUND_NOUN_PREFIX = 30;       // class ПРЕФИКС_СОСТАВ_СУЩ
 public const int VERB_en = 31;                    // class ENG_VERB
 public const int BEVERB_en = 32;                  // class ENG_BEVERB
 public const int AUXVERB_en = 33;                 // class ENG_AUXVERB
 public const int NOUN_en = 34;                    // class ENG_NOUN
 public const int PRONOUN_en = 35;                 // class ENG_PRONOUN
 public const int ARTICLE_en = 36;                 // class ENG_ARTICLE
 public const int PREP_en = 37;                    // class ENG_PREP
 public const int POSTPOS_en = 38;                 // class ENG_POSTPOS
 public const int CONJ_en = 39;                    // class ENG_CONJ
 public const int ADV_en = 40;                     // class ENG_ADVERB
 public const int ADJ_en = 41;                     // class ENG_ADJECTIVE
 public const int PARTICLE_en = 42;                // class ENG_PARTICLE
 public const int NUMERAL_en = 43;                 // class ENG_NUMERAL
 public const int INTERJECTION_en = 44;            // class ENG_INTERJECTION
 public const int POSSESSION_PARTICLE_en = 45;     // class ENG_POSSESSION
 public const int COMPOUND_PRENOUN_en = 46;        // class ENG_COMPOUND_PRENOUN
 public const int COMPOUND_PREADJ_en = 47;         // class ENG_COMPOUND_PREADJ
 public const int COMPOUND_PREVERB_en = 48;        // class ENG_COMPOUND_PREVERB
 public const int COMPOUND_PREADV_en = 49;         // class ENG_COMPOUND_PREADV
 public const int NUMERAL_fr = 50;                 // class FR_NUMERAL
 public const int ARTICLE_fr = 51;                 // class FR_ARTICLE
 public const int PREP_fr = 52;                    // class FR_PREP
 public const int ADV_fr = 53;                     // class FR_ADVERB
 public const int CONJ_fr = 54;                    // class FR_CONJ
 public const int NOUN_fr = 55;                    // class FR_NOUN
 public const int ADJ_fr = 56;                     // class FR_ADJ
 public const int PRONOUN_fr = 57;                 // class FR_PRONOUN
 public const int VERB_fr = 58;                    // class FR_VERB
 public const int PARTICLE_fr = 59;                // class FR_PARTICLE
 public const int PRONOUN2_fr = 60;                // class FR_PRONOUN2
 public const int NOUN_es = 61;                    // class ES_NOUN
 public const int ROOT_es = 62;                    // class ES_ROOT
 public const int JAP_NOUN = 63;                   // class JAP_NOUN
 public const int JAP_NUMBER = 64;                 // class JAP_NUMBER
 public const int JAP_ADJECTIVE = 65;              // class JAP_ADJECTIVE
 public const int JAP_ADVERB = 66;                 // class JAP_ADVERB
 public const int JAP_CONJ = 67;                   // class JAP_CONJ
 public const int JAP_VERB = 68;                   // class JAP_VERB
 public const int JAP_PRONOUN = 69;                // class JAP_PRONOUN
 public const int JAP_VERB_POSTFIX2 = 72;          // class JAP_VERB_POSTFIX2
 public const int JAP_PARTICLE = 74;               // class JAP_PARTICLE
 public const int UNKNOWN_ENTRIES_CLASS = 85;      // class UnknownEntries
// ------------------------------------------------------------



 public const int CharCasing = 4;                  // enum CharCasing
// Coordiname CharCasing states:
 public const int DECAPITALIZED_CASED = 0;         // CharCasing : Lower
 public const int FIRST_CAPITALIZED_CASED = 1;     // CharCasing : FirstCapitalized
 public const int ALL_CAPITALIZED_CASED = 2;       // CharCasing : Upper
 public const int EACH_LEXEM_CAPITALIZED_CASED = 3;  // CharCasing : EachLexemCapitalized

 public const int PERSON_xx = 6;                   // enum PERSON
// Coordiname PERSON states:
 public const int PERSON_1_xx = 0;                 // PERSON : 1
 public const int PERSON_2_xx = 1;                 // PERSON : 2
 public const int PERSON_3_xx = 2;                 // PERSON : 3

 public const int NUMBER_xx = 7;                   // enum NUMBER
// Coordiname NUMBER states:
 public const int SINGLE_xx = 0;                   // NUMBER : SINGLE
 public const int PLURAL_xx = 1;                   // NUMBER : PLURAL

 public const int GENDER_xx = 8;                   // enum GENDER
// Coordiname GENDER states:
 public const int MASCULINE_xx = 0;                // GENDER : MASCULINE
 public const int FEMININE_xx = 1;                 // GENDER : FEMININE
 public const int NEUTRAL_xx = 2;                  // GENDER : NEUTRAL

 public const int SPEECH_STYLE_xx = 9;             // enum СтильРечи
// Coordiname СтильРечи states:

 public const int STRENGTH_xx = 10;                // enum РазмерСила
// Coordiname РазмерСила states:

 public const int PERSON_ru = 27;                  // enum ЛИЦО
// Coordiname ЛИЦО states:
 public const int PERSON_1_ru = 0;                 // ЛИЦО : 1
 public const int PERSON_2_ru = 1;                 // ЛИЦО : 2
 public const int PERSON_3_ru = 2;                 // ЛИЦО : 3

 public const int NUMBER_ru = 28;                  // enum ЧИСЛО
// Coordiname ЧИСЛО states:
 public const int SINGULAR_NUMBER_ru = 0;          // ЧИСЛО : ЕД
 public const int PLURAL_NUMBER_ru = 1;            // ЧИСЛО : МН

 public const int GENDER_ru = 29;                  // enum РОД
// Coordiname РОД states:
 public const int MASCULINE_GENDER_ru = 0;         // РОД : МУЖ
 public const int FEMININE_GENDER_ru = 1;          // РОД : ЖЕН
 public const int NEUTRAL_GENDER_ru = 2;           // РОД : СР

 public const int TRANSITIVENESS_ru = 30;          // enum ПЕРЕХОДНОСТЬ
// Coordiname ПЕРЕХОДНОСТЬ states:
 public const int NONTRANSITIVE_VERB_ru = 0;       // ПЕРЕХОДНОСТЬ : НЕПЕРЕХОДНЫЙ
 public const int TRANSITIVE_VERB_ru = 1;          // ПЕРЕХОДНОСТЬ : ПЕРЕХОДНЫЙ

 public const int PARTICIPLE_ru = 31;              // enum ПРИЧАСТИЕ

 public const int PASSIVE_PARTICIPLE_ru = 32;      // enum СТРАД

 public const int ASPECT_ru = 33;                  // enum ВИД
// Coordiname ВИД states:
 public const int PERFECT_ru = 0;                  // ВИД : СОВЕРШ
 public const int IMPERFECT_ru = 1;                // ВИД : НЕСОВЕРШ

 public const int VERB_FORM_ru = 35;               // enum НАКЛОНЕНИЕ
// Coordiname НАКЛОНЕНИЕ states:
 public const int VB_INF_ru = 0;                   // НАКЛОНЕНИЕ : ИЗЪЯВ
 public const int VB_ORDER_ru = 1;                 // НАКЛОНЕНИЕ : ПОБУД

 public const int TENSE_ru = 36;                   // enum ВРЕМЯ
// Coordiname ВРЕМЯ states:
 public const int PAST_ru = 0;                     // ВРЕМЯ : ПРОШЕДШЕЕ
 public const int PRESENT_ru = 1;                  // ВРЕМЯ : НАСТОЯЩЕЕ
 public const int FUTURE_ru = 2;                   // ВРЕМЯ : БУДУЩЕЕ

 public const int SHORTNESS_ru = 37;               // enum КРАТКИЙ

 public const int CASE_ru = 39;                    // enum ПАДЕЖ
// Coordiname ПАДЕЖ states:
 public const int NOMINATIVE_CASE_ru = 0;          // ПАДЕЖ : ИМ
 public const int VOCATIVE_CASE_ru = 1;            // ЗВАТ
 public const int GENITIVE_CASE_ru = 2;            // ПАДЕЖ : РОД
 public const int PARTITIVE_CASE_ru = 3;           // ПАРТ
 public const int INSTRUMENTAL_CASE_ru = 5;        // ПАДЕЖ : ТВОР
 public const int ACCUSATIVE_CASE_ru = 6;          // ПАДЕЖ : ВИН
 public const int DATIVE_CASE_ru = 7;              // ПАДЕЖ : ДАТ
 public const int PREPOSITIVE_CASE_ru = 8;         // ПАДЕЖ : ПРЕДЛ
 public const int LOCATIVE_CASE_ru = 10;           // МЕСТ

 public const int FORM_ru = 40;                    // enum ОДУШ
// Coordiname ОДУШ states:
 public const int ANIMATIVE_FORM_ru = 0;           // ОДУШ : ОДУШ
 public const int INANIMATIVE_FORM_ru = 1;         // ОДУШ : НЕОДУШ

 public const int COUNTABILITY_ru = 41;            // enum ПЕРЕЧИСЛИМОСТЬ
// Coordiname ПЕРЕЧИСЛИМОСТЬ states:
 public const int COUNTABLE_ru = 0;                // ПЕРЕЧИСЛИМОСТЬ : ДА
 public const int UNCOUNTABLE_ru = 1;              // ПЕРЕЧИСЛИМОСТЬ : НЕТ

 public const int COMPAR_FORM_ru = 42;             // enum СТЕПЕНЬ
// Coordiname СТЕПЕНЬ states:
 public const int ATTRIBUTIVE_FORM_ru = 0;         // СТЕПЕНЬ : АТРИБ
 public const int COMPARATIVE_FORM_ru = 1;         // СТЕПЕНЬ : СРАВН
 public const int SUPERLATIVE_FORM_ru = 2;         // СТЕПЕНЬ : ПРЕВОСХ
 public const int LIGHT_COMPAR_FORM_RU = 3;        // СТЕПЕНЬ : КОМПАРАТИВ2
 public const int ABBREV_FORM_ru = 4;              // СТЕПЕНЬ : СОКРАЩ

 public const int CASE_GERUND_ru = 43;             // enum ПадежВал
// Coordiname ПадежВал states:

 public const int MODAL_ru = 44;                   // enum МОДАЛЬНЫЙ

 public const int VERBMODE_TENSE = 45;             // enum СГД_Время
// Coordiname СГД_Время states:

 public const int VERBMODE_DIRECTION = 46;         // enum СГД_Направление
// Coordiname СГД_Направление states:

 public const int NUMERAL_CATEGORY = 47;           // enum КАТЕГОРИЯ_ЧИСЛ
// Coordiname КАТЕГОРИЯ_ЧИСЛ states:
 public const int CARDINAL = 0;                    // КАТЕГОРИЯ_ЧИСЛ : КОЛИЧ
 public const int COLLECTION = 1;                  // КАТЕГОРИЯ_ЧИСЛ : СОБИР

 public const int ADV_SEMANTICS = 48;              // enum ОБСТ_ВАЛ
// Coordiname ОБСТ_ВАЛ states:
 public const int S_LOCATION = 0;                  // ОБСТ_ВАЛ : МЕСТО
 public const int S_DIRECTION = 1;                 // ОБСТ_ВАЛ : НАПРАВЛЕНИЕ
 public const int S_DIRECTION_FROM = 2;            // ОБСТ_ВАЛ : НАПРАВЛЕНИЕ_ОТКУДА
 public const int S_FINAL_POINT = 3;               // ОБСТ_ВАЛ : КОНЕЧНАЯ_ТОЧКА
 public const int S_DISTANCE = 4;                  // ОБСТ_ВАЛ : РАССТОЯНИЕ
 public const int S_VELOCITY = 5;                  // ОБСТ_ВАЛ : СКОРОСТЬ
 public const int S_MOMENT = 6;                    // ОБСТ_ВАЛ : МОМЕНТ_ВРЕМЕНИ
 public const int S_DURATION = 7;                  // ОБСТ_ВАЛ : ДЛИТЕЛЬНОСТЬ
 public const int S_TIME_DIVISIBILITY = 8;         // ОБСТ_ВАЛ : КРАТНОСТЬ
 public const int S_ANALOG = 9;                    // ОБСТ_ВАЛ : СОПОСТАВЛЕНИЕ
 public const int S_FACTOR = 10;                   // ОБСТ_ВАЛ : МНОЖИТЕЛЬ

 public const int ADJ_TYPE = 49;                   // enum ТИП_ПРИЛ
// Coordiname ТИП_ПРИЛ states:
 public const int ADJ_POSSESSIVE = 0;              // ТИП_ПРИЛ : ПРИТЯЖ
 public const int ADJ_ORDINAL = 1;                 // ТИП_ПРИЛ : ПОРЯДК

 public const int PRONOUN_TYPE_ru = 51;            // enum ТИП_МЕСТОИМЕНИЯ
// Coordiname ТИП_МЕСТОИМЕНИЯ states:

 public const int VERB_TYPE_ru = 52;               // enum ТИП_ГЛАГОЛА
// Coordiname ТИП_ГЛАГОЛА states:
 public const int COPULA_VERB_ru = 2;              // ТИП_ГЛАГОЛА : СВЯЗОЧН

 public const int PARTICLE_TYPE = 53;              // enum ТИП_ЧАСТИЦЫ
// Coordiname ТИП_ЧАСТИЦЫ states:
 public const int PREFIX_PARTICLE = 0;             // ТИП_ЧАСТИЦЫ : ПРЕФИКС
 public const int POSTFIX_PARTICLE = 1;            // ТИП_ЧАСТИЦЫ : ПОСТФИКС

 public const int ADV_MODIF_TYPE = 54;             // enum ТИП_МОДИФ
// Coordiname ТИП_МОДИФ states:

 public const int TENSE_en = 55;                   // enum TENSE
// Coordiname TENSE states:
 public const int PAST_en = 0;                     // TENSE : PAST
 public const int PRESENT_en = 1;                  // TENSE : PRESENT
 public const int FUTURE_en = 2;                   // TENSE : FUTURE
 public const int IMPERATIVE_en = 3;               // TENSE : IMPERATIVE

 public const int DURATION_en = 56;                // enum DURATION
// Coordiname DURATION states:
 public const int SIMPLE_en = 0;                   // DURATION : INDEFINITE
 public const int CONTINUOUS_en = 1;               // DURATION : CONTINUOUS
 public const int PERFECT_en = 2;                  // DURATION : PERFECT
 public const int PERFECT_CONTINUOS_en = 3;        // DURATION : PERFECT_CONTINUOUS

 public const int VOICE_en = 57;                   // enum VOICE
// Coordiname VOICE states:
 public const int PASSIVE_en = 0;                  // VOICE : PASSIVE
 public const int ACTIVE_en = 1;                   // VOICE : ACTIVE

 public const int CASE_en = 58;                    // enum CASE
// Coordiname CASE states:
 public const int NOMINATIVE_CASE_en = 0;          // CASE : NOMINATIVE
 public const int PREPOSITIVE_CASE_en = 1;         // CASE : PREPOSITIVE

 public const int NOUN_FORM_en = 59;               // enum NOUN_FORM
// Coordiname NOUN_FORM states:
 public const int BASIC_NOUN_FORM_en = 0;          // NOUN_FORM : BASIC
 public const int POSSESSIVE_NOUN_FORM_en = 1;     // NOUN_FORM : POSSESSIVE

 public const int HAS_POSSESSIVE_FORM_en = 60;     // enum HAS_POSSESSIVE_FORM

 public const int PRONOUN_FORM_en = 61;            // enum PRONOUN_FORM
// Coordiname PRONOUN_FORM states:

 public const int ADJ_FORM_en = 62;                // enum ADJ_FORM
// Coordiname ADJ_FORM states:
 public const int BASIC_ADJ_en = 0;                // ADJ_FORM : BASIC
 public const int COMPARATIVE_ADJ_en = 1;          // ADJ_FORM : COMPARATIVE
 public const int SUPERLATIVE_ADJ_en = 2;          // ADJ_FORM : SUPERLATIVE

 public const int COMPARABILITY_en = 63;           // enum COMPARABILITY
// Coordiname COMPARABILITY states:
 public const int ANALYTIC_en = 0;                 // COMPARABILITY : ANALYTIC
 public const int SYNTHETIC_en = 1;                // COMPARABILITY : SYNTHETIC
 public const int COMPARABLE_en = 2;               // COMPARABILITY : COMPARABLE
 public const int NONCOMPARABLE = 3;               // COMPARABILITY : NONCOMPARABLE

 public const int VERB_FORM_en = 64;               // enum VERB_FORM
// Coordiname VERB_FORM states:
 public const int UNDEF_VERBFORM_en = 0;           // VERB_FORM : UNDEF
 public const int S_VERBFORM_en = 1;               // VERB_FORM : S
 public const int ED_VERBFORM_en = 2;              // VERB_FORM : ED
 public const int ING_VERBFORM_en = 3;             // VERB_FORM : ING
 public const int PP_VERBFORM_en = 4;              // VERB_FORM : PP
 public const int INF_VEBFORM_en = 5;              // VERB_FORM : INF

 public const int ARTICLE_FORM = 65;               // enum ARTICLE_FORM
// Coordiname ARTICLE_FORM states:
 public const int ARTICLE_FORM_1 = 0;              // ARTICLE_FORM : 1
 public const int ARTICLE_FORM_2 = 1;              // ARTICLE_FORM : 2

 public const int NUMERAL_FORM_en = 66;            // enum NUMERAL_FORM
// Coordiname NUMERAL_FORM states:
 public const int CARDINAL_en = 0;                 // NUMERAL_FORM : CARDINAL
 public const int ORDINAL_en = 1;                  // NUMERAL_FORM : ORDINAL

 public const int GENDER_en = 67;                  // enum ENG_GENDER
// Coordiname ENG_GENDER states:
 public const int MASCULINE_en = 0;                // ENG_GENDER : MASCULINE
 public const int FEMININE_en = 1;                 // ENG_GENDER : FEMININE

 public const int TRANSITIVITY_en = 68;            // enum TRANSITIVITY
// Coordiname TRANSITIVITY states:
 public const int INTRANSITIVE_VERB_en = 0;        // TRANSITIVITY : INTRANSITIVE
 public const int TRANSITIVE_VERB_en = 1;          // TRANSITIVITY : TRANSITIVE

 public const int OBLIG_TRANSITIVITY_en = 69;      // enum OBLIG_TRANSITIVITY
// Coordiname OBLIG_TRANSITIVITY states:

 public const int VERB_SLOTS_en = 70;              // enum VERB_SLOTS
// Coordiname VERB_SLOTS states:
 public const int DITRANSITIVE_en = 0;             // VERB_SLOTS : DITRANSITIVE
 public const int COPULATIVE_en = 1;               // VERB_SLOTS : COPULATIVE
 public const int GERUND_en = 2;                   // VERB_SLOTS : GERUND
 public const int PastParticipleSlot_en = 3;       // VERB_SLOTS : PastParticiple
 public const int DIRECT_MODALITY_en = 4;          // VERB_SLOTS : ModalDirect
 public const int TO_MODALITY_en = 5;              // VERB_SLOTS : ModalTo

 public const int PROPER_NOUN_en = 71;             // enum ENG_PROPER_NOUN

 public const int MASS_NOUN_en = 72;               // enum ENG_MASS_NOUN

 public const int MODAL_NOUN_en = 73;              // enum ENG_MODAL_NOUN

 public const int PERSON_fr = 77;                  // enum FR_PERSON
// Coordiname FR_PERSON states:
 public const int PERSON_1_fr = 0;                 // FR_PERSON : 1
 public const int PERSON_2_fr = 1;                 // FR_PERSON : 2
 public const int PERSON_3_fr = 2;                 // FR_PERSON : 3

 public const int NUMBER_fr = 78;                  // enum FR_NOMBRE
// Coordiname FR_NOMBRE states:
 public const int SINGULAR_fr = 0;                 // FR_NOMBRE : SINGULIER
 public const int PLURAL_fr = 1;                   // FR_NOMBRE : PLURIEL

 public const int GENDER_fr = 79;                  // enum FR_GENRE
// Coordiname FR_GENRE states:
 public const int MASCULINE_fr = 0;                // FR_GENRE : MASCULINE
 public const int FEMININE_fr = 1;                 // FR_GENRE : FEMININE

 public const int FR_NUMERAL_FORM = 80;            // enum FR_NUMERAL_FORM
// Coordiname FR_NUMERAL_FORM states:
 public const int CARDINAL_fr = 0;                 // FR_NUMERAL_FORM : CARDINAL
 public const int ORDINAL_fr = 1;                  // FR_NUMERAL_FORM : ORDINAL

 public const int FR_PRONOUN_FORM = 81;            // enum FR_PRONOUN_FORM
// Coordiname FR_PRONOUN_FORM states:
 public const int FR_PRONOUN_WEAK = 0;             // FR_PRONOUN_FORM : WEAK
 public const int FR_PRONOUN_STRONG = 1;           // FR_PRONOUN_FORM : STRONG

 public const int TRANSITIVITY_fr = 82;            // enum FR_TRANSITIVITY
// Coordiname FR_TRANSITIVITY states:
 public const int INTRANSITIVE_VERB_fr = 0;        // FR_TRANSITIVITY : INTRANSITIVE
 public const int TRANSITIVE_VERB_fr = 1;          // FR_TRANSITIVITY : TRANSITIVE

 public const int VERB_FORM_fr = 83;               // enum FR_VERB_FORM
// Coordiname FR_VERB_FORM states:
 public const int INFINITIVE_fr = 0;               // FR_VERB_FORM : INFINITIVE
 public const int PRESENT_VF_fr = 1;               // FR_VERB_FORM : PRESENT
 public const int FUTURE_VF_fr = 2;                // FR_VERB_FORM : FUTURE
 public const int IMPERFECT_VB_fr = 3;             // FR_VERB_FORM : IMPERFECT
 public const int SIMPLE_PAST_fr = 4;              // FR_VERB_FORM : SIMPLE_PAST
 public const int PRESENT_PARTICIPLE_fr = 5;       // FR_VERB_FORM : PRESENT_PARTICIPLE
 public const int PAST_PARTICIPLE_fr = 6;          // FR_VERB_FORM : PAST_PARTICIPLE
 public const int SUBJUNCTIVE_PRESENT_fr = 7;      // FR_VERB_FORM : SUBJUNCTIVE_PRESENT
 public const int SUBJUNCTIVE_IMPERFECT_fr = 8;    // FR_VERB_FORM : SUBJUNCTIVE_IMPERFECT
 public const int CONDITIONAL_fr = 9;              // FR_VERB_FORM : CONDITIONAL
 public const int IMPERATIVE_fr = 10;              // FR_VERB_FORM : IMPERATIVE

 public const int JAP_FORM = 84;                   // enum JAP_FORM
// Coordiname JAP_FORM states:
 public const int KANA_FORM = 0;                   // JAP_FORM : KANA
 public const int KANJI_FORM = 1;                  // JAP_FORM : KANJI
 public const int ROMAJI_FORM = 2;                 // JAP_FORM : ROMAJI

 public const int JAP_VERB_BASE = 85;              // enum JAP_VERB_BASE
// Coordiname JAP_VERB_BASE states:
 public const int JAP_VB_I = 0;                    // JAP_VERB_BASE : I
 public const int JAP_VB_II = 1;                   // JAP_VERB_BASE : II
 public const int JAP_VB_III = 2;                  // JAP_VERB_BASE : III
 public const int JAP_VB_IV = 3;                   // JAP_VERB_BASE : IV
 public const int JAP_VB_V = 4;                    // JAP_VERB_BASE : V
 public const int JAP_VB_PAST = 5;                 // JAP_VERB_BASE : PAST
 public const int JAP_VB_PARTICIPLE = 6;           // JAP_VERB_BASE : PARTICIPLE
 public const int JAP_VB_POTENTIAL = 7;            // JAP_VERB_BASE : POTENTIAL
 public const int JAP_VB_CONDITIONAL = 8;          // JAP_VERB_BASE : CONDITIONAL
 public const int JAP_VB_CAUSATIVE = 9;            // JAP_VERB_BASE : CAUSATIVE

 public const int JAP_VERB_KIND = 86;              // enum JAP_VERB_KIND
// Coordiname JAP_VERB_KIND states:
 public const int JAP_PRESENT_FUTURE = 1;          // JAP_VERB_KIND : PRESENT_FUTURE
 public const int JAP_NEGATIVE_PRESENT_FUTURE = 3;  // JAP_VERB_KIND : NEGATIVE_PRESENT_FUTURE
 public const int JAP_NEGATIVE_PAST = 4;           // JAP_VERB_KIND : NEGATIVE_PAST
 public const int JAP_IMPERATIVE = 5;              // JAP_VERB_KIND : IMPERATIVE
 public const int JAP_NEGATIVE_IMPERATIVE = 6;     // JAP_VERB_KIND : NEGATIVE_IMPERATIVE

 public const int JAP_ADJ_BASE = 87;               // enum JAP_ADJ_BASE
// Coordiname JAP_ADJ_BASE states:
 public const int JAP_AB_I = 0;                    // JAP_ADJ_BASE : I
 public const int JAP_AB_II = 1;                   // JAP_ADJ_BASE : II
 public const int JAP_AB_III = 2;                  // JAP_ADJ_BASE : III
 public const int JAP_AB_IV = 3;                   // JAP_ADJ_BASE : IV
 public const int JAP_AB_V = 4;                    // JAP_ADJ_BASE : V
 public const int JAP_AB_T = 5;                    // JAP_ADJ_BASE : T
 public const int JAP_AB_PAST = 6;                 // JAP_ADJ_BASE : PAST

 public const int JAP_ADJ_FORM2 = 88;              // enum JAP_ADJ_FORM2
// Coordiname JAP_ADJ_FORM2 states:
 public const int JAP_NEGATIVE_PRESENT_ADJ = 0;    // JAP_ADJ_FORM2 : NEGATIVE_PRESENT
 public const int JAP_NEGATIVE_PAST_ADJ = 1;       // JAP_ADJ_FORM2 : NEGATIVE_PAST

 public const int JAP_TRANSITIVE = 89;             // enum JAP_TRANSITIVE

 public const int CASE_jap = 90;                   // enum JAP_CASE
// Coordiname JAP_CASE states:
 public const int VOCATIVE_jap = 0;                // JAP_CASE : VOCATIVE
 public const int NOMINATIVE_THEM_jap = 1;         // JAP_CASE : NOMINATIVE_THEM
 public const int NOMINATIVE_RHEM_jap = 2;         // JAP_CASE : NOMINATIVE_RHEM
 public const int ACCUSATIVE_jap = 3;              // JAP_CASE : ACCUSATIVE
 public const int GENITIVE_jap = 4;                // JAP_CASE : GENITIVE
 public const int DATIVE_jap = 5;                  // JAP_CASE : DATIVE
 public const int ALLATIVE_jap = 6;                // JAP_CASE : ALLATIVE
 public const int INSTRUMENTATIVE_jap = 7;         // JAP_CASE : INSTRUMENTATIVE
 public const int ELATIVE_jap = 8;                 // JAP_CASE : ELATIVE
 public const int LIMITIVE_jap = 9;                // JAP_CASE : LIMITIVE
 public const int COMPARATIVE_jap = 10;            // JAP_CASE : COMPARATIVE
 public const int COMITATIVE_jap = 11;             // JAP_CASE : COMITATIVE
 public const int SOCIATIVE_jap = 12;              // JAP_CASE : SOCIATIVE

 public const int GENDER_jap = 91;                 // enum JAP_GENDER
// Coordiname JAP_GENDER states:
 public const int MASCULINE_jap = 0;               // JAP_GENDER : MASCULINE
 public const int FEMININE_jap = 1;                // JAP_GENDER : FEMININE

 public const int PERSON_jap = 92;                 // enum JAP_PERSON
// Coordiname JAP_PERSON states:
 public const int PERSON_1_jap = 0;                // JAP_PERSON : 1
 public const int PERSON_2_jap = 1;                // JAP_PERSON : 2
 public const int PERSON_3_jap = 2;                // JAP_PERSON : 3

 public const int NUMBER_jap = 93;                 // enum JAP_NUMBER
// Coordiname JAP_NUMBER states:
 public const int SINGULAR_jap = 0;                // JAP_NUMBER : SINGULAR
 public const int PLURAL_jap = 1;                  // JAP_NUMBER : PLURAL

 public const int JAP_PRONOUN_TYPE = 94;           // enum JAP_PRONOUN_TYPE
// Coordiname JAP_PRONOUN_TYPE states:
 public const int PERSONAL_jap = 0;                // JAP_PRONOUN_TYPE : PERSONAL
 public const int POINTING_jap = 1;                // JAP_PRONOUN_TYPE : POINTING
 public const int POSSESSIVE_jap = 2;              // JAP_PRONOUN_TYPE : POSSESSIVE
// ------------------------------------------------------------


 public const int OBJECT_link = 0;
 public const int ATTRIBUTE_link = 1;
 public const int CONDITION_link = 2;
 public const int CONSEQUENCE_link = 3;
 public const int SUBJECT_link = 4;
 public const int RHEMA_link = 5;
 public const int COVERB_link = 6;
 public const int NUMBER2OBJ_link = 12;
 public const int TO_VERB_link = 16;
 public const int TO_INF_link = 17;
 public const int TO_PERFECT = 18;
 public const int TO_UNPERFECT = 19;
 public const int TO_NOUN_link = 20;
 public const int TO_ADJ_link = 21;
 public const int TO_ADV_link = 22;
 public const int TO_RETVERB = 23;
 public const int TO_GERUND_2_link = 24;
 public const int WOUT_RETVERB = 25;
 public const int TO_ENGLISH_link = 26;
 public const int TO_RUSSIAN_link = 27;
 public const int TO_FRENCH_link = 28;
 public const int SYNONYM_link = 29;
 public const int SEX_SYNONYM_link = 30;
 public const int CLASS_link = 31;
 public const int MEMBER_link = 32;
 public const int TO_SPANISH_link = 33;
 public const int TO_GERMAN_link = 34;
 public const int TO_CHINESE_link = 35;
 public const int TO_POLAND_link = 36;
 public const int TO_ITALIAN_link = 37;
 public const int TO_PORTUGUAL_link = 38;
 public const int ACTION_link = 39;
 public const int ACTOR_link = 40;
 public const int TOOL_link = 41;
 public const int RESULT_link = 42;
 public const int TO_JAPANESE_link = 43;
 public const int TO_KANA_link = 44;
 public const int TO_KANJI_link = 45;
 public const int ANTONYM_link = 46;
 public const int EXPLANATION_link = 47;
 public const int WWW_link = 48;
 public const int ACCENT_link = 49;
 public const int YO_link = 50;
 public const int TO_DIMINUITIVE_link = 51;
 public const int TO_RUDE_link = 52;
 public const int TO_BIGGER_link = 53;
 public const int TO_NEUTRAL_link = 54;
 public const int TO_SCOLARLY = 55;
 public const int TO_SAMPLE_link = 56;
 public const int USAGE_TAG_link = 57;
 public const int PROPERTY_link = 58;
 public const int TO_CYRIJI_link = 59;
 public const int HABITANT_link = 60;
 public const int CHILD_link = 61;
 public const int PARENT_link = 62;
 public const int UNIT_link = 63;
 public const int SET_link = 64;
 public const int TO_WEAKENED_link = 65;
 public const int VERBMODE_BASIC_link = 66;
 public const int NEGATION_PARTICLE_link = 67;
 public const int NEXT_COLLOCATION_ITEM_link = 68;
 public const int SUBORDINATE_CLAUSE_link = 69;
 public const int RIGHT_GENITIVE_OBJECT_link = 70;
 public const int ADV_PARTICIPLE_link = 71;
 public const int POSTFIX_PARTICLE_link = 72;
 public const int INFINITIVE_link = 73;
 public const int NEXT_ADJECTIVE_link = 74;
 public const int NEXT_NOUN_link = 75;
 public const int THEMA_link = 76;
 public const int RIGHT_AUX2INFINITIVE_link = 77;
 public const int RIGHT_AUX2PARTICIPLE = 78;
 public const int RIGHT_AUX2ADJ = 79;
 public const int RIGHT_LOGIC_ITEM_link = 80;
 public const int RIGHT_COMPARISON_Y_link = 81;
 public const int RIGHT_NOUN_link = 82;
 public const int RIGHT_NAME_link = 83;
 public const int ADJ_PARTICIPLE_link = 84;
 public const int PUNCTUATION_link = 85;
 public const int IMPERATIVE_SUBJECT_link = 86;
 public const int IMPERATIVE_VERB2AUX_link = 87;
 public const int AUX2IMPERATIVE_VERB = 88;
 public const int PREFIX_PARTICLE_link = 89;
 public const int PREFIX_CONJUNCTION_link = 90;
 public const int LOGICAL_CONJUNCTION_link = 91;
 public const int NEXT_CLAUSE_link = 92;
 public const int LEFT_AUX_VERB_link = 93;
 public const int BEG_INTRO_link = 94;
 public const int RIGHT_PREPOSITION_link = 95;
 public const int WH_SUBJECT_link = 96;
 public const int IMPERATIVE_PARTICLE_link = 97;
 public const int GERUND_link = 98;
 public const int PREPOS_ADJUNCT_link = 99;
 public const int DIRECT_OBJ_INTENTION_link = 100;
 public const int COPULA_link = 101;
 public const int DETAILS_link = 102;
 public const int SENTENCE_CLOSER_link = 103;
 public const int OPINION_link = 104;
 public const int APPEAL_link = 105;
 public const int TERM_link = 106;
 public const int SPEECH_link = 107;
 public const int QUESTION_link = 108;
 public const int POLITENESS_link = 109;
 public const int SEPARATE_ATTR_link = 110;
 public const int POSSESSION_POSTFIX_link = 111;
 public const int COMPOUND_PREFIX_link = 112;
 public const int UNKNOWN_SLOT_link = 113;
 public const int SECOND_VERB_link = 114;

  };
 }
