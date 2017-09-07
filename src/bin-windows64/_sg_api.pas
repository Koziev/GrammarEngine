{ This file is generated 07.09.2017 17:25:21 by Ygres compiler ver. 14.15.11192 Standard Win64  (build date Sep  7 2017). }
unit _sg_api;
interface
{ Languages }
 const RUSSIAN_LANGUAGE: integer = 2;              { language Russian }
 const ENGLISH_LANGUAGE: integer = 3;              { language English }
 const FRENCH_LANGUAGE: integer = 4;               { language French }
 const SPANISH_LANGUAGE: integer = 5;              { language Spanish }
 const CHINESE_LANGUAGE: integer = 6;              { language Chinese }
 const JAPANESE_LANGUAGE: integer = 7;             { language Japanese }
 const GERMAN_LANGUAGE: integer = 8;               { language German }
 const THESAURUS_LANGUAGE: integer = 9;            { language ThesaurusLanguage }
{ ------------------------------------------------------------ }


 const NUM_WORD_CLASS: integer = 2;                { class num_word }
 const NOUN_ru: integer = 6;                       { class —”Ÿ≈—“¬»“≈À‹ÕŒ≈ }
 const PRONOUN2_ru: integer = 7;                   { class Ã≈—“Œ»Ã_—”Ÿ }
 const PRONOUN_ru: integer = 8;                    { class Ã≈—“Œ»Ã≈Õ»≈ }
 const ADJ_ru: integer = 9;                        { class œ–»À¿√¿“≈À‹ÕŒ≈ }
 const NUMBER_CLASS_ru: integer = 10;              { class ◊»—À»“≈À‹ÕŒ≈ }
 const INFINITIVE_ru: integer = 11;                { class »Õ‘»Õ»“»¬ }
 const VERB_ru: integer = 12;                      { class √À¿√ŒÀ }
 const GERUND_2_ru: integer = 13;                  { class ƒ≈≈œ–»◊¿—“»≈ }
 const PREPOS_ru: integer = 14;                    { class œ–≈ƒÀŒ√ }
 const IMPERSONAL_VERB_ru: integer = 15;           { class ¡≈«À»◊_√À¿√ŒÀ }
 const PARTICLE_ru: integer = 18;                  { class ◊¿—“»÷¿ }
 const CONJ_ru: integer = 19;                      { class —Œﬁ« }
 const ADVERB_ru: integer = 20;                    { class Õ¿–≈◊»≈ }
 const PUNCTUATION_class: integer = 21;            { class œ”Õ “”¿“Œ– }
 const POSTPOS_ru: integer = 26;                   { class œŒ—À≈ÀŒ√ }
 const POSESS_PARTICLE: integer = 27;              { class œ–»“ﬂ∆_◊¿—“»÷¿ }
 const MEASURE_UNIT: integer = 28;                 { class ≈ƒ»Õ»÷¿_»«Ã≈–≈Õ»ﬂ }
 const COMPOUND_ADJ_PREFIX: integer = 29;          { class œ–≈‘» —_—Œ—“¿¬_œ–»À }
 const COMPOUND_NOUN_PREFIX: integer = 30;         { class œ–≈‘» —_—Œ—“¿¬_—”Ÿ }
 const VERB_en: integer = 31;                      { class ENG_VERB }
 const BEVERB_en: integer = 32;                    { class ENG_BEVERB }
 const AUXVERB_en: integer = 33;                   { class ENG_AUXVERB }
 const NOUN_en: integer = 34;                      { class ENG_NOUN }
 const PRONOUN_en: integer = 35;                   { class ENG_PRONOUN }
 const ARTICLE_en: integer = 36;                   { class ENG_ARTICLE }
 const PREP_en: integer = 37;                      { class ENG_PREP }
 const POSTPOS_en: integer = 38;                   { class ENG_POSTPOS }
 const CONJ_en: integer = 39;                      { class ENG_CONJ }
 const ADV_en: integer = 40;                       { class ENG_ADVERB }
 const ADJ_en: integer = 41;                       { class ENG_ADJECTIVE }
 const PARTICLE_en: integer = 42;                  { class ENG_PARTICLE }
 const NUMERAL_en: integer = 43;                   { class ENG_NUMERAL }
 const INTERJECTION_en: integer = 44;              { class ENG_INTERJECTION }
 const POSSESSION_PARTICLE_en: integer = 45;       { class ENG_POSSESSION }
 const COMPOUND_PRENOUN_en: integer = 46;          { class ENG_COMPOUND_PRENOUN }
 const COMPOUND_PREADJ_en: integer = 47;           { class ENG_COMPOUND_PREADJ }
 const COMPOUND_PREVERB_en: integer = 48;          { class ENG_COMPOUND_PREVERB }
 const COMPOUND_PREADV_en: integer = 49;           { class ENG_COMPOUND_PREADV }
 const NUMERAL_fr: integer = 50;                   { class FR_NUMERAL }
 const ARTICLE_fr: integer = 51;                   { class FR_ARTICLE }
 const PREP_fr: integer = 52;                      { class FR_PREP }
 const ADV_fr: integer = 53;                       { class FR_ADVERB }
 const CONJ_fr: integer = 54;                      { class FR_CONJ }
 const NOUN_fr: integer = 55;                      { class FR_NOUN }
 const ADJ_fr: integer = 56;                       { class FR_ADJ }
 const PRONOUN_fr: integer = 57;                   { class FR_PRONOUN }
 const VERB_fr: integer = 58;                      { class FR_VERB }
 const PARTICLE_fr: integer = 59;                  { class FR_PARTICLE }
 const PRONOUN2_fr: integer = 60;                  { class FR_PRONOUN2 }
 const NOUN_es: integer = 61;                      { class ES_NOUN }
 const ROOT_es: integer = 62;                      { class ES_ROOT }
 const JAP_NOUN: integer = 63;                     { class JAP_NOUN }
 const JAP_NUMBER: integer = 64;                   { class JAP_NUMBER }
 const JAP_ADJECTIVE: integer = 65;                { class JAP_ADJECTIVE }
 const JAP_ADVERB: integer = 66;                   { class JAP_ADVERB }
 const JAP_CONJ: integer = 67;                     { class JAP_CONJ }
 const JAP_VERB: integer = 68;                     { class JAP_VERB }
 const JAP_PRONOUN: integer = 69;                  { class JAP_PRONOUN }
 const JAP_VERB_POSTFIX2: integer = 72;            { class JAP_VERB_POSTFIX2 }
 const JAP_PARTICLE: integer = 74;                 { class JAP_PARTICLE }
 const UNKNOWN_ENTRIES_CLASS: integer = 85;        { class UnknownEntries }
{ ------------------------------------------------------------ }


 const CharCasing: integer = 4;                    { enum CharCasing }
{ Coordiname CharCasing states: }
const DECAPITALIZED_CASED: integer = 0;            // CharCasing : Lower
const FIRST_CAPITALIZED_CASED: integer = 1;        // CharCasing : FirstCapitalized
const ALL_CAPITALIZED_CASED: integer = 2;          // CharCasing : Upper
const EACH_LEXEM_CAPITALIZED_CASED: integer = 3;   // CharCasing : EachLexemCapitalized
 const PERSON_xx: integer = 6;                     { enum PERSON }
{ Coordiname PERSON states: }
const PERSON_1_xx: integer = 0;                    // PERSON : 1
const PERSON_2_xx: integer = 1;                    // PERSON : 2
const PERSON_3_xx: integer = 2;                    // PERSON : 3
 const NUMBER_xx: integer = 7;                     { enum NUMBER }
{ Coordiname NUMBER states: }
const SINGLE_xx: integer = 0;                      // NUMBER : SINGLE
const PLURAL_xx: integer = 1;                      // NUMBER : PLURAL
 const GENDER_xx: integer = 8;                     { enum GENDER }
{ Coordiname GENDER states: }
const MASCULINE_xx: integer = 0;                   // GENDER : MASCULINE
const FEMININE_xx: integer = 1;                    // GENDER : FEMININE
const NEUTRAL_xx: integer = 2;                     // GENDER : NEUTRAL
 const SPEECH_STYLE_xx: integer = 9;               { enum —ÚËÎ¸–Â˜Ë }
{ Coordiname —ÚËÎ¸–Â˜Ë states: }
 const STRENGTH_xx: integer = 10;                  { enum –‡ÁÏÂ—ËÎ‡ }
{ Coordiname –‡ÁÏÂ—ËÎ‡ states: }
 const PERSON_ru: integer = 27;                    { enum À»÷Œ }
{ Coordiname À»÷Œ states: }
const PERSON_1_ru: integer = 0;                    // À»÷Œ : 1
const PERSON_2_ru: integer = 1;                    // À»÷Œ : 2
const PERSON_3_ru: integer = 2;                    // À»÷Œ : 3
 const NUMBER_ru: integer = 28;                    { enum ◊»—ÀŒ }
{ Coordiname ◊»—ÀŒ states: }
const SINGULAR_NUMBER_ru: integer = 0;             // ◊»—ÀŒ : ≈ƒ
const PLURAL_NUMBER_ru: integer = 1;               // ◊»—ÀŒ : ÃÕ
 const GENDER_ru: integer = 29;                    { enum –Œƒ }
{ Coordiname –Œƒ states: }
const MASCULINE_GENDER_ru: integer = 0;            // –Œƒ : Ã”∆
const FEMININE_GENDER_ru: integer = 1;             // –Œƒ : ∆≈Õ
const NEUTRAL_GENDER_ru: integer = 2;              // –Œƒ : —–
 const TRANSITIVENESS_ru: integer = 30;            { enum œ≈–≈’ŒƒÕŒ—“‹ }
{ Coordiname œ≈–≈’ŒƒÕŒ—“‹ states: }
const NONTRANSITIVE_VERB_ru: integer = 0;          // œ≈–≈’ŒƒÕŒ—“‹ : Õ≈œ≈–≈’ŒƒÕ€…
const TRANSITIVE_VERB_ru: integer = 1;             // œ≈–≈’ŒƒÕŒ—“‹ : œ≈–≈’ŒƒÕ€…
 const PARTICIPLE_ru: integer = 31;                { enum œ–»◊¿—“»≈ }
 const PASSIVE_PARTICIPLE_ru: integer = 32;        { enum —“–¿ƒ }
 const ASPECT_ru: integer = 33;                    { enum ¬»ƒ }
{ Coordiname ¬»ƒ states: }
const PERFECT_ru: integer = 0;                     // ¬»ƒ : —Œ¬≈–ÿ
const IMPERFECT_ru: integer = 1;                   // ¬»ƒ : Õ≈—Œ¬≈–ÿ
 const VERB_FORM_ru: integer = 35;                 { enum Õ¿ ÀŒÕ≈Õ»≈ }
{ Coordiname Õ¿ ÀŒÕ≈Õ»≈ states: }
const VB_INF_ru: integer = 0;                      // Õ¿ ÀŒÕ≈Õ»≈ : »«⁄ﬂ¬
const VB_ORDER_ru: integer = 1;                    // Õ¿ ÀŒÕ≈Õ»≈ : œŒ¡”ƒ
 const TENSE_ru: integer = 36;                     { enum ¬–≈Ãﬂ }
{ Coordiname ¬–≈Ãﬂ states: }
const PAST_ru: integer = 0;                        // ¬–≈Ãﬂ : œ–Œÿ≈ƒÿ≈≈
const PRESENT_ru: integer = 1;                     // ¬–≈Ãﬂ : Õ¿—“ŒﬂŸ≈≈
const FUTURE_ru: integer = 2;                      // ¬–≈Ãﬂ : ¡”ƒ”Ÿ≈≈
 const SHORTNESS_ru: integer = 37;                 { enum  –¿“ »… }
 const CASE_ru: integer = 39;                      { enum œ¿ƒ≈∆ }
{ Coordiname œ¿ƒ≈∆ states: }
const NOMINATIVE_CASE_ru: integer = 0;             // œ¿ƒ≈∆ : »Ã
const VOCATIVE_CASE_ru: integer = 1;               // «¬¿“
const GENITIVE_CASE_ru: integer = 2;               // œ¿ƒ≈∆ : –Œƒ
const PARTITIVE_CASE_ru: integer = 3;              // œ¿–“
const INSTRUMENTAL_CASE_ru: integer = 5;           // œ¿ƒ≈∆ : “¬Œ–
const ACCUSATIVE_CASE_ru: integer = 6;             // œ¿ƒ≈∆ : ¬»Õ
const DATIVE_CASE_ru: integer = 7;                 // œ¿ƒ≈∆ : ƒ¿“
const PREPOSITIVE_CASE_ru: integer = 8;            // œ¿ƒ≈∆ : œ–≈ƒÀ
const LOCATIVE_CASE_ru: integer = 10;              // Ã≈—“
 const FORM_ru: integer = 40;                      { enum Œƒ”ÿ }
{ Coordiname Œƒ”ÿ states: }
const ANIMATIVE_FORM_ru: integer = 0;              // Œƒ”ÿ : Œƒ”ÿ
const INANIMATIVE_FORM_ru: integer = 1;            // Œƒ”ÿ : Õ≈Œƒ”ÿ
 const COUNTABILITY_ru: integer = 41;              { enum œ≈–≈◊»—À»ÃŒ—“‹ }
{ Coordiname œ≈–≈◊»—À»ÃŒ—“‹ states: }
const COUNTABLE_ru: integer = 0;                   // œ≈–≈◊»—À»ÃŒ—“‹ : ƒ¿
const UNCOUNTABLE_ru: integer = 1;                 // œ≈–≈◊»—À»ÃŒ—“‹ : Õ≈“
 const COMPAR_FORM_ru: integer = 42;               { enum —“≈œ≈Õ‹ }
{ Coordiname —“≈œ≈Õ‹ states: }
const ATTRIBUTIVE_FORM_ru: integer = 0;            // —“≈œ≈Õ‹ : ¿“–»¡
const COMPARATIVE_FORM_ru: integer = 1;            // —“≈œ≈Õ‹ : —–¿¬Õ
const SUPERLATIVE_FORM_ru: integer = 2;            // —“≈œ≈Õ‹ : œ–≈¬Œ—’
const LIGHT_COMPAR_FORM_RU: integer = 3;           // —“≈œ≈Õ‹ :  ŒÃœ¿–¿“»¬2
const ABBREV_FORM_ru: integer = 4;                 // —“≈œ≈Õ‹ : —Œ –¿Ÿ
 const CASE_GERUND_ru: integer = 43;               { enum œ‡‰ÂÊ¬‡Î }
{ Coordiname œ‡‰ÂÊ¬‡Î states: }
 const MODAL_ru: integer = 44;                     { enum ÃŒƒ¿À‹Õ€… }
 const VERBMODE_TENSE: integer = 45;               { enum —√ƒ_¬ÂÏˇ }
{ Coordiname —√ƒ_¬ÂÏˇ states: }
 const VERBMODE_DIRECTION: integer = 46;           { enum —√ƒ_Õ‡Ô‡‚ÎÂÌËÂ }
{ Coordiname —√ƒ_Õ‡Ô‡‚ÎÂÌËÂ states: }
 const NUMERAL_CATEGORY: integer = 47;             { enum  ¿“≈√Œ–»ﬂ_◊»—À }
{ Coordiname  ¿“≈√Œ–»ﬂ_◊»—À states: }
const CARDINAL: integer = 0;                       //  ¿“≈√Œ–»ﬂ_◊»—À :  ŒÀ»◊
const COLLECTION: integer = 1;                     //  ¿“≈√Œ–»ﬂ_◊»—À : —Œ¡»–
 const ADV_SEMANTICS: integer = 48;                { enum Œ¡—“_¬¿À }
{ Coordiname Œ¡—“_¬¿À states: }
const S_LOCATION: integer = 0;                     // Œ¡—“_¬¿À : Ã≈—“Œ
const S_DIRECTION: integer = 1;                    // Œ¡—“_¬¿À : Õ¿œ–¿¬À≈Õ»≈
const S_DIRECTION_FROM: integer = 2;               // Œ¡—“_¬¿À : Õ¿œ–¿¬À≈Õ»≈_Œ“ ”ƒ¿
const S_FINAL_POINT: integer = 3;                  // Œ¡—“_¬¿À :  ŒÕ≈◊Õ¿ﬂ_“Œ◊ ¿
const S_DISTANCE: integer = 4;                     // Œ¡—“_¬¿À : –¿——“ŒﬂÕ»≈
const S_VELOCITY: integer = 5;                     // Œ¡—“_¬¿À : — Œ–Œ—“‹
const S_MOMENT: integer = 6;                       // Œ¡—“_¬¿À : ÃŒÃ≈Õ“_¬–≈Ã≈Õ»
const S_DURATION: integer = 7;                     // Œ¡—“_¬¿À : ƒÀ»“≈À‹ÕŒ—“‹
const S_TIME_DIVISIBILITY: integer = 8;            // Œ¡—“_¬¿À :  –¿“ÕŒ—“‹
const S_ANALOG: integer = 9;                       // Œ¡—“_¬¿À : —ŒœŒ—“¿¬À≈Õ»≈
const S_FACTOR: integer = 10;                      // Œ¡—“_¬¿À : ÃÕŒ∆»“≈À‹
 const ADJ_TYPE: integer = 49;                     { enum “»œ_œ–»À }
{ Coordiname “»œ_œ–»À states: }
const ADJ_POSSESSIVE: integer = 0;                 // “»œ_œ–»À : œ–»“ﬂ∆
const ADJ_ORDINAL: integer = 1;                    // “»œ_œ–»À : œŒ–ﬂƒ 
 const PRONOUN_TYPE_ru: integer = 51;              { enum “»œ_Ã≈—“Œ»Ã≈Õ»ﬂ }
{ Coordiname “»œ_Ã≈—“Œ»Ã≈Õ»ﬂ states: }
 const VERB_TYPE_ru: integer = 52;                 { enum “»œ_√À¿√ŒÀ¿ }
{ Coordiname “»œ_√À¿√ŒÀ¿ states: }
const COPULA_VERB_ru: integer = 2;                 // “»œ_√À¿√ŒÀ¿ : —¬ﬂ«Œ◊Õ
 const PARTICLE_TYPE: integer = 53;                { enum “»œ_◊¿—“»÷€ }
{ Coordiname “»œ_◊¿—“»÷€ states: }
const PREFIX_PARTICLE: integer = 0;                // “»œ_◊¿—“»÷€ : œ–≈‘» —
const POSTFIX_PARTICLE: integer = 1;               // “»œ_◊¿—“»÷€ : œŒ—“‘» —
 const ADV_MODIF_TYPE: integer = 54;               { enum “»œ_ÃŒƒ»‘ }
{ Coordiname “»œ_ÃŒƒ»‘ states: }
 const TENSE_en: integer = 55;                     { enum TENSE }
{ Coordiname TENSE states: }
const PAST_en: integer = 0;                        // TENSE : PAST
const PRESENT_en: integer = 1;                     // TENSE : PRESENT
const FUTURE_en: integer = 2;                      // TENSE : FUTURE
const IMPERATIVE_en: integer = 3;                  // TENSE : IMPERATIVE
 const DURATION_en: integer = 56;                  { enum DURATION }
{ Coordiname DURATION states: }
const SIMPLE_en: integer = 0;                      // DURATION : INDEFINITE
const CONTINUOUS_en: integer = 1;                  // DURATION : CONTINUOUS
const PERFECT_en: integer = 2;                     // DURATION : PERFECT
const PERFECT_CONTINUOS_en: integer = 3;           // DURATION : PERFECT_CONTINUOUS
 const VOICE_en: integer = 57;                     { enum VOICE }
{ Coordiname VOICE states: }
const PASSIVE_en: integer = 0;                     // VOICE : PASSIVE
const ACTIVE_en: integer = 1;                      // VOICE : ACTIVE
 const CASE_en: integer = 58;                      { enum CASE }
{ Coordiname CASE states: }
const NOMINATIVE_CASE_en: integer = 0;             // CASE : NOMINATIVE
const PREPOSITIVE_CASE_en: integer = 1;            // CASE : PREPOSITIVE
 const NOUN_FORM_en: integer = 59;                 { enum NOUN_FORM }
{ Coordiname NOUN_FORM states: }
const BASIC_NOUN_FORM_en: integer = 0;             // NOUN_FORM : BASIC
const POSSESSIVE_NOUN_FORM_en: integer = 1;        // NOUN_FORM : POSSESSIVE
 const HAS_POSSESSIVE_FORM_en: integer = 60;       { enum HAS_POSSESSIVE_FORM }
 const PRONOUN_FORM_en: integer = 61;              { enum PRONOUN_FORM }
{ Coordiname PRONOUN_FORM states: }
 const ADJ_FORM_en: integer = 62;                  { enum ADJ_FORM }
{ Coordiname ADJ_FORM states: }
const BASIC_ADJ_en: integer = 0;                   // ADJ_FORM : BASIC
const COMPARATIVE_ADJ_en: integer = 1;             // ADJ_FORM : COMPARATIVE
const SUPERLATIVE_ADJ_en: integer = 2;             // ADJ_FORM : SUPERLATIVE
 const COMPARABILITY_en: integer = 63;             { enum COMPARABILITY }
{ Coordiname COMPARABILITY states: }
const ANALYTIC_en: integer = 0;                    // COMPARABILITY : ANALYTIC
const SYNTHETIC_en: integer = 1;                   // COMPARABILITY : SYNTHETIC
const COMPARABLE_en: integer = 2;                  // COMPARABILITY : COMPARABLE
const NONCOMPARABLE: integer = 3;                  // COMPARABILITY : NONCOMPARABLE
 const VERB_FORM_en: integer = 64;                 { enum VERB_FORM }
{ Coordiname VERB_FORM states: }
const UNDEF_VERBFORM_en: integer = 0;              // VERB_FORM : UNDEF
const S_VERBFORM_en: integer = 1;                  // VERB_FORM : S
const ED_VERBFORM_en: integer = 2;                 // VERB_FORM : ED
const ING_VERBFORM_en: integer = 3;                // VERB_FORM : ING
const PP_VERBFORM_en: integer = 4;                 // VERB_FORM : PP
const INF_VEBFORM_en: integer = 5;                 // VERB_FORM : INF
 const ARTICLE_FORM: integer = 65;                 { enum ARTICLE_FORM }
{ Coordiname ARTICLE_FORM states: }
const ARTICLE_FORM_1: integer = 0;                 // ARTICLE_FORM : 1
const ARTICLE_FORM_2: integer = 1;                 // ARTICLE_FORM : 2
 const NUMERAL_FORM_en: integer = 66;              { enum NUMERAL_FORM }
{ Coordiname NUMERAL_FORM states: }
const CARDINAL_en: integer = 0;                    // NUMERAL_FORM : CARDINAL
const ORDINAL_en: integer = 1;                     // NUMERAL_FORM : ORDINAL
 const GENDER_en: integer = 67;                    { enum ENG_GENDER }
{ Coordiname ENG_GENDER states: }
const MASCULINE_en: integer = 0;                   // ENG_GENDER : MASCULINE
const FEMININE_en: integer = 1;                    // ENG_GENDER : FEMININE
 const TRANSITIVITY_en: integer = 68;              { enum TRANSITIVITY }
{ Coordiname TRANSITIVITY states: }
const INTRANSITIVE_VERB_en: integer = 0;           // TRANSITIVITY : INTRANSITIVE
const TRANSITIVE_VERB_en: integer = 1;             // TRANSITIVITY : TRANSITIVE
 const OBLIG_TRANSITIVITY_en: integer = 69;        { enum OBLIG_TRANSITIVITY }
{ Coordiname OBLIG_TRANSITIVITY states: }
 const VERB_SLOTS_en: integer = 70;                { enum VERB_SLOTS }
{ Coordiname VERB_SLOTS states: }
const DITRANSITIVE_en: integer = 0;                // VERB_SLOTS : DITRANSITIVE
const COPULATIVE_en: integer = 1;                  // VERB_SLOTS : COPULATIVE
const GERUND_en: integer = 2;                      // VERB_SLOTS : GERUND
const PastParticipleSlot_en: integer = 3;          // VERB_SLOTS : PastParticiple
const DIRECT_MODALITY_en: integer = 4;             // VERB_SLOTS : ModalDirect
const TO_MODALITY_en: integer = 5;                 // VERB_SLOTS : ModalTo
 const PROPER_NOUN_en: integer = 71;               { enum ENG_PROPER_NOUN }
 const MASS_NOUN_en: integer = 72;                 { enum ENG_MASS_NOUN }
 const MODAL_NOUN_en: integer = 73;                { enum ENG_MODAL_NOUN }
 const PERSON_fr: integer = 77;                    { enum FR_PERSON }
{ Coordiname FR_PERSON states: }
const PERSON_1_fr: integer = 0;                    // FR_PERSON : 1
const PERSON_2_fr: integer = 1;                    // FR_PERSON : 2
const PERSON_3_fr: integer = 2;                    // FR_PERSON : 3
 const NUMBER_fr: integer = 78;                    { enum FR_NOMBRE }
{ Coordiname FR_NOMBRE states: }
const SINGULAR_fr: integer = 0;                    // FR_NOMBRE : SINGULIER
const PLURAL_fr: integer = 1;                      // FR_NOMBRE : PLURIEL
 const GENDER_fr: integer = 79;                    { enum FR_GENRE }
{ Coordiname FR_GENRE states: }
const MASCULINE_fr: integer = 0;                   // FR_GENRE : MASCULINE
const FEMININE_fr: integer = 1;                    // FR_GENRE : FEMININE
 const FR_NUMERAL_FORM: integer = 80;              { enum FR_NUMERAL_FORM }
{ Coordiname FR_NUMERAL_FORM states: }
const CARDINAL_fr: integer = 0;                    // FR_NUMERAL_FORM : CARDINAL
const ORDINAL_fr: integer = 1;                     // FR_NUMERAL_FORM : ORDINAL
 const FR_PRONOUN_FORM: integer = 81;              { enum FR_PRONOUN_FORM }
{ Coordiname FR_PRONOUN_FORM states: }
const FR_PRONOUN_WEAK: integer = 0;                // FR_PRONOUN_FORM : WEAK
const FR_PRONOUN_STRONG: integer = 1;              // FR_PRONOUN_FORM : STRONG
 const TRANSITIVITY_fr: integer = 82;              { enum FR_TRANSITIVITY }
{ Coordiname FR_TRANSITIVITY states: }
const INTRANSITIVE_VERB_fr: integer = 0;           // FR_TRANSITIVITY : INTRANSITIVE
const TRANSITIVE_VERB_fr: integer = 1;             // FR_TRANSITIVITY : TRANSITIVE
 const VERB_FORM_fr: integer = 83;                 { enum FR_VERB_FORM }
{ Coordiname FR_VERB_FORM states: }
const INFINITIVE_fr: integer = 0;                  // FR_VERB_FORM : INFINITIVE
const PRESENT_VF_fr: integer = 1;                  // FR_VERB_FORM : PRESENT
const FUTURE_VF_fr: integer = 2;                   // FR_VERB_FORM : FUTURE
const IMPERFECT_VB_fr: integer = 3;                // FR_VERB_FORM : IMPERFECT
const SIMPLE_PAST_fr: integer = 4;                 // FR_VERB_FORM : SIMPLE_PAST
const PRESENT_PARTICIPLE_fr: integer = 5;          // FR_VERB_FORM : PRESENT_PARTICIPLE
const PAST_PARTICIPLE_fr: integer = 6;             // FR_VERB_FORM : PAST_PARTICIPLE
const SUBJUNCTIVE_PRESENT_fr: integer = 7;         // FR_VERB_FORM : SUBJUNCTIVE_PRESENT
const SUBJUNCTIVE_IMPERFECT_fr: integer = 8;       // FR_VERB_FORM : SUBJUNCTIVE_IMPERFECT
const CONDITIONAL_fr: integer = 9;                 // FR_VERB_FORM : CONDITIONAL
const IMPERATIVE_fr: integer = 10;                 // FR_VERB_FORM : IMPERATIVE
 const JAP_FORM: integer = 84;                     { enum JAP_FORM }
{ Coordiname JAP_FORM states: }
const KANA_FORM: integer = 0;                      // JAP_FORM : KANA
const KANJI_FORM: integer = 1;                     // JAP_FORM : KANJI
const ROMAJI_FORM: integer = 2;                    // JAP_FORM : ROMAJI
 const JAP_VERB_BASE: integer = 85;                { enum JAP_VERB_BASE }
{ Coordiname JAP_VERB_BASE states: }
const JAP_VB_I: integer = 0;                       // JAP_VERB_BASE : I
const JAP_VB_II: integer = 1;                      // JAP_VERB_BASE : II
const JAP_VB_III: integer = 2;                     // JAP_VERB_BASE : III
const JAP_VB_IV: integer = 3;                      // JAP_VERB_BASE : IV
const JAP_VB_V: integer = 4;                       // JAP_VERB_BASE : V
const JAP_VB_PAST: integer = 5;                    // JAP_VERB_BASE : PAST
const JAP_VB_PARTICIPLE: integer = 6;              // JAP_VERB_BASE : PARTICIPLE
const JAP_VB_POTENTIAL: integer = 7;               // JAP_VERB_BASE : POTENTIAL
const JAP_VB_CONDITIONAL: integer = 8;             // JAP_VERB_BASE : CONDITIONAL
const JAP_VB_CAUSATIVE: integer = 9;               // JAP_VERB_BASE : CAUSATIVE
 const JAP_VERB_KIND: integer = 86;                { enum JAP_VERB_KIND }
{ Coordiname JAP_VERB_KIND states: }
const JAP_PRESENT_FUTURE: integer = 1;             // JAP_VERB_KIND : PRESENT_FUTURE
const JAP_NEGATIVE_PRESENT_FUTURE: integer = 3;    // JAP_VERB_KIND : NEGATIVE_PRESENT_FUTURE
const JAP_NEGATIVE_PAST: integer = 4;              // JAP_VERB_KIND : NEGATIVE_PAST
const JAP_IMPERATIVE: integer = 5;                 // JAP_VERB_KIND : IMPERATIVE
const JAP_NEGATIVE_IMPERATIVE: integer = 6;        // JAP_VERB_KIND : NEGATIVE_IMPERATIVE
 const JAP_ADJ_BASE: integer = 87;                 { enum JAP_ADJ_BASE }
{ Coordiname JAP_ADJ_BASE states: }
const JAP_AB_I: integer = 0;                       // JAP_ADJ_BASE : I
const JAP_AB_II: integer = 1;                      // JAP_ADJ_BASE : II
const JAP_AB_III: integer = 2;                     // JAP_ADJ_BASE : III
const JAP_AB_IV: integer = 3;                      // JAP_ADJ_BASE : IV
const JAP_AB_V: integer = 4;                       // JAP_ADJ_BASE : V
const JAP_AB_T: integer = 5;                       // JAP_ADJ_BASE : T
const JAP_AB_PAST: integer = 6;                    // JAP_ADJ_BASE : PAST
 const JAP_ADJ_FORM2: integer = 88;                { enum JAP_ADJ_FORM2 }
{ Coordiname JAP_ADJ_FORM2 states: }
const JAP_NEGATIVE_PRESENT_ADJ: integer = 0;       // JAP_ADJ_FORM2 : NEGATIVE_PRESENT
const JAP_NEGATIVE_PAST_ADJ: integer = 1;          // JAP_ADJ_FORM2 : NEGATIVE_PAST
 const JAP_TRANSITIVE: integer = 89;               { enum JAP_TRANSITIVE }
 const CASE_jap: integer = 90;                     { enum JAP_CASE }
{ Coordiname JAP_CASE states: }
const VOCATIVE_jap: integer = 0;                   // JAP_CASE : VOCATIVE
const NOMINATIVE_THEM_jap: integer = 1;            // JAP_CASE : NOMINATIVE_THEM
const NOMINATIVE_RHEM_jap: integer = 2;            // JAP_CASE : NOMINATIVE_RHEM
const ACCUSATIVE_jap: integer = 3;                 // JAP_CASE : ACCUSATIVE
const GENITIVE_jap: integer = 4;                   // JAP_CASE : GENITIVE
const DATIVE_jap: integer = 5;                     // JAP_CASE : DATIVE
const ALLATIVE_jap: integer = 6;                   // JAP_CASE : ALLATIVE
const INSTRUMENTATIVE_jap: integer = 7;            // JAP_CASE : INSTRUMENTATIVE
const ELATIVE_jap: integer = 8;                    // JAP_CASE : ELATIVE
const LIMITIVE_jap: integer = 9;                   // JAP_CASE : LIMITIVE
const COMPARATIVE_jap: integer = 10;               // JAP_CASE : COMPARATIVE
const COMITATIVE_jap: integer = 11;                // JAP_CASE : COMITATIVE
const SOCIATIVE_jap: integer = 12;                 // JAP_CASE : SOCIATIVE
 const GENDER_jap: integer = 91;                   { enum JAP_GENDER }
{ Coordiname JAP_GENDER states: }
const MASCULINE_jap: integer = 0;                  // JAP_GENDER : MASCULINE
const FEMININE_jap: integer = 1;                   // JAP_GENDER : FEMININE
 const PERSON_jap: integer = 92;                   { enum JAP_PERSON }
{ Coordiname JAP_PERSON states: }
const PERSON_1_jap: integer = 0;                   // JAP_PERSON : 1
const PERSON_2_jap: integer = 1;                   // JAP_PERSON : 2
const PERSON_3_jap: integer = 2;                   // JAP_PERSON : 3
 const NUMBER_jap: integer = 93;                   { enum JAP_NUMBER }
{ Coordiname JAP_NUMBER states: }
const SINGULAR_jap: integer = 0;                   // JAP_NUMBER : SINGULAR
const PLURAL_jap: integer = 1;                     // JAP_NUMBER : PLURAL
 const JAP_PRONOUN_TYPE: integer = 94;             { enum JAP_PRONOUN_TYPE }
{ Coordiname JAP_PRONOUN_TYPE states: }
const PERSONAL_jap: integer = 0;                   // JAP_PRONOUN_TYPE : PERSONAL
const POINTING_jap: integer = 1;                   // JAP_PRONOUN_TYPE : POINTING
const POSSESSIVE_jap: integer = 2;                 // JAP_PRONOUN_TYPE : POSSESSIVE
{ ------------------------------------------------------------ }


 const OBJECT_link: integer = 0;
 const ATTRIBUTE_link: integer = 1;
 const CONDITION_link: integer = 2;
 const CONSEQUENCE_link: integer = 3;
 const SUBJECT_link: integer = 4;
 const RHEMA_link: integer = 5;
 const COVERB_link: integer = 6;
 const NUMBER2OBJ_link: integer = 12;
 const TO_VERB_link: integer = 16;
 const TO_INF_link: integer = 17;
 const TO_PERFECT: integer = 18;
 const TO_UNPERFECT: integer = 19;
 const TO_NOUN_link: integer = 20;
 const TO_ADJ_link: integer = 21;
 const TO_ADV_link: integer = 22;
 const TO_RETVERB: integer = 23;
 const TO_GERUND_2_link: integer = 24;
 const WOUT_RETVERB: integer = 25;
 const TO_ENGLISH_link: integer = 26;
 const TO_RUSSIAN_link: integer = 27;
 const TO_FRENCH_link: integer = 28;
 const SYNONYM_link: integer = 29;
 const SEX_SYNONYM_link: integer = 30;
 const CLASS_link: integer = 31;
 const MEMBER_link: integer = 32;
 const TO_SPANISH_link: integer = 33;
 const TO_GERMAN_link: integer = 34;
 const TO_CHINESE_link: integer = 35;
 const TO_POLAND_link: integer = 36;
 const TO_ITALIAN_link: integer = 37;
 const TO_PORTUGUAL_link: integer = 38;
 const ACTION_link: integer = 39;
 const ACTOR_link: integer = 40;
 const TOOL_link: integer = 41;
 const RESULT_link: integer = 42;
 const TO_JAPANESE_link: integer = 43;
 const TO_KANA_link: integer = 44;
 const TO_KANJI_link: integer = 45;
 const ANTONYM_link: integer = 46;
 const EXPLANATION_link: integer = 47;
 const WWW_link: integer = 48;
 const ACCENT_link: integer = 49;
 const YO_link: integer = 50;
 const TO_DIMINUITIVE_link: integer = 51;
 const TO_RUDE_link: integer = 52;
 const TO_BIGGER_link: integer = 53;
 const TO_NEUTRAL_link: integer = 54;
 const TO_SCOLARLY: integer = 55;
 const TO_SAMPLE_link: integer = 56;
 const USAGE_TAG_link: integer = 57;
 const PROPERTY_link: integer = 58;
 const TO_CYRIJI_link: integer = 59;
 const HABITANT_link: integer = 60;
 const CHILD_link: integer = 61;
 const PARENT_link: integer = 62;
 const UNIT_link: integer = 63;
 const SET_link: integer = 64;
 const TO_WEAKENED_link: integer = 65;
 const VERBMODE_BASIC_link: integer = 66;
 const NEGATION_PARTICLE_link: integer = 67;
 const NEXT_COLLOCATION_ITEM_link: integer = 68;
 const SUBORDINATE_CLAUSE_link: integer = 69;
 const RIGHT_GENITIVE_OBJECT_link: integer = 70;
 const ADV_PARTICIPLE_link: integer = 71;
 const POSTFIX_PARTICLE_link: integer = 72;
 const INFINITIVE_link: integer = 73;
 const NEXT_ADJECTIVE_link: integer = 74;
 const NEXT_NOUN_link: integer = 75;
 const THEMA_link: integer = 76;
 const RIGHT_AUX2INFINITIVE_link: integer = 77;
 const RIGHT_AUX2PARTICIPLE: integer = 78;
 const RIGHT_AUX2ADJ: integer = 79;
 const RIGHT_LOGIC_ITEM_link: integer = 80;
 const RIGHT_COMPARISON_Y_link: integer = 81;
 const RIGHT_NOUN_link: integer = 82;
 const RIGHT_NAME_link: integer = 83;
 const ADJ_PARTICIPLE_link: integer = 84;
 const PUNCTUATION_link: integer = 85;
 const IMPERATIVE_SUBJECT_link: integer = 86;
 const IMPERATIVE_VERB2AUX_link: integer = 87;
 const AUX2IMPERATIVE_VERB: integer = 88;
 const PREFIX_PARTICLE_link: integer = 89;
 const PREFIX_CONJUNCTION_link: integer = 90;
 const LOGICAL_CONJUNCTION_link: integer = 91;
 const NEXT_CLAUSE_link: integer = 92;
 const LEFT_AUX_VERB_link: integer = 93;
 const BEG_INTRO_link: integer = 94;
 const RIGHT_PREPOSITION_link: integer = 95;
 const WH_SUBJECT_link: integer = 96;
 const IMPERATIVE_PARTICLE_link: integer = 97;
 const GERUND_link: integer = 98;
 const PREPOS_ADJUNCT_link: integer = 99;
 const DIRECT_OBJ_INTENTION_link: integer = 100;
 const COPULA_link: integer = 101;
 const DETAILS_link: integer = 102;
 const SENTENCE_CLOSER_link: integer = 103;
 const OPINION_link: integer = 104;
 const APPEAL_link: integer = 105;
 const TERM_link: integer = 106;
 const SPEECH_link: integer = 107;
 const QUESTION_link: integer = 108;
 const POLITENESS_link: integer = 109;
 const SEPARATE_ATTR_link: integer = 110;
 const POSSESSION_POSTFIX_link: integer = 111;
 const COMPOUND_PREFIX_link: integer = 112;
 const UNKNOWN_SLOT_link: integer = 113;
 const SECOND_VERB_link: integer = 114;
implementation
end.
