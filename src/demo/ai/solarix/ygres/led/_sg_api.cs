// This file is generated 01.03.2009 18:22:29 by Ygres compiler ver. 5.42.5602 Personal Win64  (build date Feb 28 2009).
namespace SolarixGrammarEngineNET
{
 public class GrammarEngineAPI
 {
// Languages
 public const int RUSSIAN_LANGUAGE = 1;            // language Russian
 public const int ENGLISH_LANGUAGE = 2;            // language English
 public const int FRENCH_LANGUAGE = 3;             // language French
 public const int SPANISH_LANGUAGE = 4;            // language Spanish
 public const int CHINESE_LANGUAGE = 5;            // language Chinese
 public const int JAPANESE_LANGUAGE = 6;           // language Japanese
 public const int GERMAN_LANGUAGE = 7;             // language German
// ------------------------------------------------------------


 public const int NOUN_ru = 7;                     // class ясыеярбхрекэмне
 public const int PRONOUN_ru = 9;                  // class леярнхлемхе
 public const int ADJ_ru = 10;                     // class опхкюцюрекэмне
 public const int NUMBER_CLASS_ru = 11;            // class вхякхрекэмне
 public const int INFINITIVE_ru = 12;              // class хмтхмхрхб
 public const int VERB_ru = 13;                    // class цкюцнк
 public const int GERUND_2_ru = 14;                // class дееопхвюярхе
 public const int PREPOS_ru = 15;                  // class опедкнц
 public const int PARTICLE_ru = 19;                // class вюярхжю
 public const int CONJ_ru = 20;                    // class янчг
 public const int ADVERB_ru = 21;                  // class мюпевхе
 public const int VERB_en = 28;                    // class ENG_VERB
 public const int NOUN_en = 29;                    // class ENG_NOUN
 public const int PRONOUN_en = 30;                 // class ENG_PRONOUN
 public const int ARTICLE_en = 31;                 // class ENG_ARTICLE
 public const int PREP_en = 32;                    // class ENG_PREP
 public const int CONJ_en = 33;                    // class ENG_CONJ
 public const int ADV_en = 34;                     // class ENG_ADVERB
 public const int ADJ_en = 35;                     // class ENG_ADJECTIVE
 public const int PARTICLE_en = 36;                // class ENG_PARTICLE
 public const int NUMERAL_en = 37;                 // class ENG_NUMERAL
 public const int INTERJECTION_en = 38;            // class ENG_INTERJECTION
 public const int ARTICLE_fr = 39;                 // class FR_ARTICLE
 public const int PREP_fr = 40;                    // class FR_PREP
 public const int ADV_fr = 41;                     // class FR_ADVERB
 public const int CONJ_fr = 42;                    // class FR_CONJ
 public const int NOUN_fr = 43;                    // class FR_NOUN
 public const int ADJ_fr = 44;                     // class FR_ADJ
 public const int PRONOUN_fr = 45;                 // class FR_PRONOUN
 public const int VERB_fr = 46;                    // class FR_VERB
 public const int NOUN_es = 47;                    // class ES_NOUN
 public const int ROOT_es = 48;                    // class ES_ROOT
// ------------------------------------------------------------



 public const int PERSON_xx = 5;                   // enum PERSON
// Coordiname PERSON states:
 public const int PERSON_1_xx = 0;                 // PERSON : 1
 public const int PERSON_2_xx = 1;                 // PERSON : 2
 public const int PERSON_3_xx = 2;                 // PERSON : 3

 public const int NUMBER_xx = 6;                   // enum NUMBER
// Coordiname NUMBER states:
 public const int SINGLE_xx = 0;                   // NUMBER : SINGLE
 public const int PLURAL_xx = 1;                   // NUMBER : PLURAL

 public const int GENDER_xx = 7;                   // enum GENDER
// Coordiname GENDER states:
 public const int MASCULINE_xx = 0;                // GENDER : MASCULINE
 public const int FEMININE_xx = 1;                 // GENDER : FEMININE
 public const int NEUTRAL_xx = 2;                  // GENDER : NEUTRAL

 public const int PERSON_ru = 8;                   // enum кхжн
// Coordiname кхжн states:
 public const int PERSON_1_ru = 0;                 // кхжн : 1
 public const int PERSON_2_ru = 1;                 // кхжн : 2
 public const int PERSON_3_ru = 2;                 // кхжн : 3

 public const int NUMBER_ru = 9;                   // enum вхякн
// Coordiname вхякн states:
 public const int SINGULAR_NUMBER_ru = 0;          // вхякн : ед
 public const int PLURAL_NUMBER_ru = 1;            // вхякн : лм

 public const int GENDER_ru = 10;                  // enum пнд
// Coordiname пнд states:
 public const int MASCULINE_GENDER_ru = 0;         // пнд : лсф
 public const int FEMININE_GENDER_ru = 1;          // пнд : фем
 public const int NEUTRAL_GENDER_ru = 2;           // пнд : яп

 public const int TRANSITIVENESS_ru = 11;          // enum оепеундмнярэ
// Coordiname оепеундмнярэ states:
 public const int NONTRANSITIVE_VERB_ru = 0;       // оепеундмнярэ : меоепеундмши
 public const int TRANSITIVE_VERB_ru = 1;          // оепеундмнярэ : оепеундмши

 public const int PARTICIPLE_ru = 12;              // enum опхвюярхе

 public const int PASSIVE_PARTICIPLE_ru = 13;      // enum ярпюд

 public const int ASPECT_ru = 14;                  // enum бхд
// Coordiname бхд states:
 public const int PERFECT_ru = 0;                  // бхд : янбепь
 public const int IMPERFECT_ru = 1;                // бхд : меянбепь

 public const int TENSE_ru = 17;                   // enum бпелъ
// Coordiname бпелъ states:
 public const int PAST_ru = 0;                     // бпелъ : опньедьее
 public const int PRESENT_ru = 1;                  // бпелъ : мюярнъыее
 public const int FUTURE_ru = 2;                   // бпелъ : асдсыее

 public const int SHORTNESS_ru = 18;               // enum йпюрйхи

 public const int CASE_ru = 22;                    // enum оюдеф
// Coordiname оюдеф states:
 public const int NOMINATIVE_CASE_ru = 0;          // оюдеф : хл
 public const int GENITIVE_CASE_ru = 2;            // оюдеф : пнд
 public const int INSTRUMENTAL_CASE_ru = 5;        // оюдеф : рбнп
 public const int ACCUSATIVE_CASE_ru = 6;          // оюдеф : бхм
 public const int DATIVE_CASE_ru = 7;              // оюдеф : дюр
 public const int PREPOSITIVE_CASE_ru = 8;         // оюдеф : опедк

 public const int FORM_ru = 23;                    // enum ндсь
// Coordiname ндсь states:
 public const int ANIMATIVE_FORM_ru = 0;           // ндсь : ндсь
 public const int INANIMATIVE_FORM_ru = 1;         // ндсь : мендсь

 public const int COMPAR_FORM_ru = 25;             // enum яреоемэ
// Coordiname яреоемэ states:
 public const int ATTRIBUTIVE_FORM_ru = 0;         // яреоемэ : юрпха
 public const int COMPARATIVE_FORM_ru = 1;         // яреоемэ : япюбм
 public const int SUPERLATIVE_FORM_ru = 2;         // яреоемэ : опебняу

 public const int CASE_GERUND_ru = 26;             // enum оЮДЕФбЮК
// Coordiname оЮДЕФбЮК states:

 public const int MODAL_ru = 27;                   // enum лндюкэмши

 public const int TENSE_en = 28;                   // enum TENSE
// Coordiname TENSE states:
 public const int PAST_en = 0;                     // TENSE : PAST
 public const int PRESENT_en = 1;                  // TENSE : PRESENT
 public const int FUTURE_en = 2;                   // TENSE : FUTURE

 public const int DURATION_en = 29;                // enum DURATION
// Coordiname DURATION states:
 public const int SIMPLE_en = 0;                   // DURATION : INDEFINITE
 public const int CONTINUOUS_en = 1;               // DURATION : CONTINUOUS
 public const int PERFECT_en = 2;                  // DURATION : PERFECT
 public const int PERFECT_CONTINUOS_en = 3;        // DURATION : PERFECT_CONTINUOUS

 public const int VOICE_en = 30;                   // enum VOICE
// Coordiname VOICE states:
 public const int PASSIVE_en = 0;                  // VOICE : PASSIVE
 public const int ACTIVE_en = 1;                   // VOICE : ACTIVE

 public const int CASE_en = 31;                    // enum CASE
// Coordiname CASE states:

 public const int ADJ_FORM_en = 34;                // enum ADJ_FORM
// Coordiname ADJ_FORM states:
 public const int BASIC_ADJ_en = 0;                // ADJ_FORM : BASIC
 public const int CPMPARATIVE_ADJ_en = 1;          // ADJ_FORM : COMPARATIVE
 public const int SUPERLATIVE_en = 2;              // ADJ_FORM : SUPERLATIVE

 public const int VERB_FORM_en = 35;               // enum VERB_FORM
// Coordiname VERB_FORM states:
 public const int UNDEF_VERBFORM_en = 0;           // VERB_FORM : UNDEF
 public const int ED_VERBFORM_en = 1;              // VERB_FORM : ED
 public const int ING_VERBFORM_en = 2;             // VERB_FORM : ING
 public const int PP_VERBFORM_en = 3;              // VERB_FORM : PP
 public const int INF_VEBFORM_en = 4;              // VERB_FORM : INF

 public const int NUMERAL_FORM_en = 38;            // enum NUMERAL_FORM
// Coordiname NUMERAL_FORM states:
 public const int CARDINAL_en = 0;                 // NUMERAL_FORM : CARDINAL
 public const int ORDINAL_en = 1;                  // NUMERAL_FORM : ORDINAL

 public const int GENDER_en = 39;                  // enum ENG_GENDER
// Coordiname ENG_GENDER states:
 public const int MASCULINE_en = 0;                // ENG_GENDER : MASCULINE
 public const int FEMININE_en = 1;                 // ENG_GENDER : FEMININE
// ------------------------------------------------------------


 public const int LOGIC_ITEM_link = 7;
 public const int SUBJECT_link = 8;
 public const int NUMBER2OBJ_link = 15;
 public const int TENSE_VERB_link = 25;
 public const int TO_VERB_link = 27;
 public const int TO_INF_link = 28;
 public const int TO_PERFECT = 29;
 public const int TO_UNPERFECT = 30;
 public const int TO_NOUN_link = 31;
 public const int TO_ADJ_link = 32;
 public const int TO_ADV_link = 33;
 public const int TO_RETVERB = 34;
 public const int TO_GERUND_2_link = 35;
 public const int WOUT_RETVERB = 36;
 public const int TO_ENGLISH_link = 37;
 public const int TO_RUSSIAN_link = 38;
 public const int TO_FRENCH_link = 39;
 public const int SYNONYM_link = 40;
 public const int SEX_SYNONYM_link = 41;
 public const int CLASS_link = 42;
 public const int MEMBER_link = 43;
 public const int TO_SPANISH_link = 44;
 public const int TO_GERMAN_link = 45;
 public const int TO_CHINESE_link = 46;
 public const int TO_POLAND_link = 47;
 public const int TO_ITALIAN_link = 48;
 public const int TO_PORTUGUAL_link = 49;
 public const int ACTION_link = 50;
 public const int ACTOR_link = 51;
 public const int TOOL_link = 52;
 public const int RESULT_link = 53;

  };
 }
