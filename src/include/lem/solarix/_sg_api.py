# -*- coding: utf-8
# This file is generated 28.01.2017 15:23:49 by Ygres compiler ver. 14.14.11192 Standard Win64  (build date Sep 21 2016).
# Languages
RUSSIAN_LANGUAGE = 2                               # language Russian
ENGLISH_LANGUAGE = 3                               # language English
FRENCH_LANGUAGE = 4                                # language French
SPANISH_LANGUAGE = 5                               # language Spanish
CHINESE_LANGUAGE = 6                               # language Chinese
JAPANESE_LANGUAGE = 7                              # language Japanese
GERMAN_LANGUAGE = 8                                # language German
THESAURUS_LANGUAGE = 9                             # language ThesaurusLanguage
# ------------------------------------------------------------


NUM_WORD_CLASS = 2                                 # class num_word
NOUN_ru = 6                                        # class СУЩЕСТВИТЕЛЬНОЕ
PRONOUN2_ru = 7                                    # class МЕСТОИМ_СУЩ
PRONOUN_ru = 8                                     # class МЕСТОИМЕНИЕ
ADJ_ru = 9                                         # class ПРИЛАГАТЕЛЬНОЕ
NUMBER_CLASS_ru = 10                               # class ЧИСЛИТЕЛЬНОЕ
INFINITIVE_ru = 11                                 # class ИНФИНИТИВ
VERB_ru = 12                                       # class ГЛАГОЛ
GERUND_2_ru = 13                                   # class ДЕЕПРИЧАСТИЕ
PREPOS_ru = 14                                     # class ПРЕДЛОГ
IMPERSONAL_VERB_ru = 15                            # class БЕЗЛИЧ_ГЛАГОЛ
PARTICLE_ru = 18                                   # class ЧАСТИЦА
CONJ_ru = 19                                       # class СОЮЗ
ADVERB_ru = 20                                     # class НАРЕЧИЕ
PUNCTUATION_class = 21                             # class ПУНКТУАТОР
POSTPOS_ru = 26                                    # class ПОСЛЕЛОГ
POSESS_PARTICLE = 27                               # class ПРИТЯЖ_ЧАСТИЦА
MEASURE_UNIT = 28                                  # class ЕДИНИЦА_ИЗМЕРЕНИЯ
COMPOUND_ADJ_PREFIX = 29                           # class ПРЕФИКС_СОСТАВ_ПРИЛ
COMPOUND_NOUN_PREFIX = 30                          # class ПРЕФИКС_СОСТАВ_СУЩ
VERB_en = 31                                       # class ENG_VERB
BEVERB_en = 32                                     # class ENG_BEVERB
AUXVERB_en = 33                                    # class ENG_AUXVERB
NOUN_en = 34                                       # class ENG_NOUN
PRONOUN_en = 35                                    # class ENG_PRONOUN
ARTICLE_en = 36                                    # class ENG_ARTICLE
PREP_en = 37                                       # class ENG_PREP
POSTPOS_en = 38                                    # class ENG_POSTPOS
CONJ_en = 39                                       # class ENG_CONJ
ADV_en = 40                                        # class ENG_ADVERB
ADJ_en = 41                                        # class ENG_ADJECTIVE
PARTICLE_en = 42                                   # class ENG_PARTICLE
NUMERAL_en = 43                                    # class ENG_NUMERAL
INTERJECTION_en = 44                               # class ENG_INTERJECTION
POSSESSION_PARTICLE_en = 45                        # class ENG_POSSESSION
COMPOUND_PRENOUN_en = 46                           # class ENG_COMPOUND_PRENOUN
COMPOUND_PREADJ_en = 47                            # class ENG_COMPOUND_PREADJ
COMPOUND_PREVERB_en = 48                           # class ENG_COMPOUND_PREVERB
COMPOUND_PREADV_en = 49                            # class ENG_COMPOUND_PREADV
NUMERAL_fr = 50                                    # class FR_NUMERAL
ARTICLE_fr = 51                                    # class FR_ARTICLE
PREP_fr = 52                                       # class FR_PREP
ADV_fr = 53                                        # class FR_ADVERB
CONJ_fr = 54                                       # class FR_CONJ
NOUN_fr = 55                                       # class FR_NOUN
ADJ_fr = 56                                        # class FR_ADJ
PRONOUN_fr = 57                                    # class FR_PRONOUN
VERB_fr = 58                                       # class FR_VERB
PARTICLE_fr = 59                                   # class FR_PARTICLE
PRONOUN2_fr = 60                                   # class FR_PRONOUN2
NOUN_es = 61                                       # class ES_NOUN
ROOT_es = 62                                       # class ES_ROOT
JAP_NOUN = 63                                      # class JAP_NOUN
JAP_NUMBER = 64                                    # class JAP_NUMBER
JAP_ADJECTIVE = 65                                 # class JAP_ADJECTIVE
JAP_ADVERB = 66                                    # class JAP_ADVERB
JAP_CONJ = 67                                      # class JAP_CONJ
JAP_VERB = 68                                      # class JAP_VERB
JAP_PRONOUN = 69                                   # class JAP_PRONOUN
JAP_VERB_POSTFIX2 = 72                             # class JAP_VERB_POSTFIX2
JAP_PARTICLE = 74                                  # class JAP_PARTICLE
UNKNOWN_ENTRIES_CLASS = 85                         # class UnknownEntries
# ------------------------------------------------------------


CharCasing = 4                                     # enum CharCasing
# Coordiname CharCasing states:
DECAPITALIZED_CASED = 0                            # CharCasing : Lower
FIRST_CAPITALIZED_CASED = 1                        # CharCasing : FirstCapitalized
ALL_CAPITALIZED_CASED = 2                          # CharCasing : Upper
EACH_LEXEM_CAPITALIZED_CASED = 3                   # CharCasing : EachLexemCapitalized
PERSON_xx = 6                                      # enum PERSON
# Coordiname PERSON states:
PERSON_1_xx = 0                                    # PERSON : 1
PERSON_2_xx = 1                                    # PERSON : 2
PERSON_3_xx = 2                                    # PERSON : 3
NUMBER_xx = 7                                      # enum NUMBER
# Coordiname NUMBER states:
SINGLE_xx = 0                                      # NUMBER : SINGLE
PLURAL_xx = 1                                      # NUMBER : PLURAL
GENDER_xx = 8                                      # enum GENDER
# Coordiname GENDER states:
MASCULINE_xx = 0                                   # GENDER : MASCULINE
FEMININE_xx = 1                                    # GENDER : FEMININE
NEUTRAL_xx = 2                                     # GENDER : NEUTRAL
SPEECH_STYLE_xx = 9                                # enum СтильРечи
# Coordiname СтильРечи states:
STRENGTH_xx = 10                                   # enum РазмерСила
# Coordiname РазмерСила states:
PERSON_ru = 27                                     # enum ЛИЦО
# Coordiname ЛИЦО states:
PERSON_1_ru = 0                                    # ЛИЦО : 1
PERSON_2_ru = 1                                    # ЛИЦО : 2
PERSON_3_ru = 2                                    # ЛИЦО : 3
NUMBER_ru = 28                                     # enum ЧИСЛО
# Coordiname ЧИСЛО states:
SINGULAR_NUMBER_ru = 0                             # ЧИСЛО : ЕД
PLURAL_NUMBER_ru = 1                               # ЧИСЛО : МН
GENDER_ru = 29                                     # enum РОД
# Coordiname РОД states:
MASCULINE_GENDER_ru = 0                            # РОД : МУЖ
FEMININE_GENDER_ru = 1                             # РОД : ЖЕН
NEUTRAL_GENDER_ru = 2                              # РОД : СР
TRANSITIVENESS_ru = 30                             # enum ПЕРЕХОДНОСТЬ
# Coordiname ПЕРЕХОДНОСТЬ states:
NONTRANSITIVE_VERB_ru = 0                          # ПЕРЕХОДНОСТЬ : НЕПЕРЕХОДНЫЙ
TRANSITIVE_VERB_ru = 1                             # ПЕРЕХОДНОСТЬ : ПЕРЕХОДНЫЙ
PARTICIPLE_ru = 31                                 # enum ПРИЧАСТИЕ
PASSIVE_PARTICIPLE_ru = 32                         # enum СТРАД
ASPECT_ru = 33                                     # enum ВИД
# Coordiname ВИД states:
PERFECT_ru = 0                                     # ВИД : СОВЕРШ
IMPERFECT_ru = 1                                   # ВИД : НЕСОВЕРШ
VERB_FORM_ru = 35                                  # enum НАКЛОНЕНИЕ
# Coordiname НАКЛОНЕНИЕ states:
VB_INF_ru = 0                                      # НАКЛОНЕНИЕ : ИЗЪЯВ
VB_ORDER_ru = 1                                    # НАКЛОНЕНИЕ : ПОБУД
TENSE_ru = 36                                      # enum ВРЕМЯ
# Coordiname ВРЕМЯ states:
PAST_ru = 0                                        # ВРЕМЯ : ПРОШЕДШЕЕ
PRESENT_ru = 1                                     # ВРЕМЯ : НАСТОЯЩЕЕ
FUTURE_ru = 2                                      # ВРЕМЯ : БУДУЩЕЕ
SHORTNESS_ru = 37                                  # enum КРАТКИЙ
CASE_ru = 39                                       # enum ПАДЕЖ
# Coordiname ПАДЕЖ states:
NOMINATIVE_CASE_ru = 0                             # ПАДЕЖ : ИМ
VOCATIVE_CASE_ru = 1                               # ЗВАТ
GENITIVE_CASE_ru = 2                               # ПАДЕЖ : РОД
PARTITIVE_CASE_ru = 3                              # ПАРТ
INSTRUMENTAL_CASE_ru = 5                           # ПАДЕЖ : ТВОР
ACCUSATIVE_CASE_ru = 6                             # ПАДЕЖ : ВИН
DATIVE_CASE_ru = 7                                 # ПАДЕЖ : ДАТ
PREPOSITIVE_CASE_ru = 8                            # ПАДЕЖ : ПРЕДЛ
LOCATIVE_CASE_ru = 10                              # МЕСТ
FORM_ru = 40                                       # enum ОДУШ
# Coordiname ОДУШ states:
ANIMATIVE_FORM_ru = 0                              # ОДУШ : ОДУШ
INANIMATIVE_FORM_ru = 1                            # ОДУШ : НЕОДУШ
COUNTABILITY_ru = 41                               # enum ПЕРЕЧИСЛИМОСТЬ
# Coordiname ПЕРЕЧИСЛИМОСТЬ states:
COUNTABLE_ru = 0                                   # ПЕРЕЧИСЛИМОСТЬ : ДА
UNCOUNTABLE_ru = 1                                 # ПЕРЕЧИСЛИМОСТЬ : НЕТ
COMPAR_FORM_ru = 42                                # enum СТЕПЕНЬ
# Coordiname СТЕПЕНЬ states:
ATTRIBUTIVE_FORM_ru = 0                            # СТЕПЕНЬ : АТРИБ
COMPARATIVE_FORM_ru = 1                            # СТЕПЕНЬ : СРАВН
SUPERLATIVE_FORM_ru = 2                            # СТЕПЕНЬ : ПРЕВОСХ
LIGHT_COMPAR_FORM_RU = 3                           # СТЕПЕНЬ : КОМПАРАТИВ2
ABBREV_FORM_ru = 4                                 # СТЕПЕНЬ : СОКРАЩ
CASE_GERUND_ru = 43                                # enum ПадежВал
# Coordiname ПадежВал states:
MODAL_ru = 44                                      # enum МОДАЛЬНЫЙ
VERBMODE_TENSE = 45                                # enum СГД_Время
# Coordiname СГД_Время states:
VERBMODE_DIRECTION = 46                            # enum СГД_Направление
# Coordiname СГД_Направление states:
NUMERAL_CATEGORY = 47                              # enum КАТЕГОРИЯ_ЧИСЛ
# Coordiname КАТЕГОРИЯ_ЧИСЛ states:
CARDINAL = 0                                       # КАТЕГОРИЯ_ЧИСЛ : КОЛИЧ
COLLECTION = 1                                     # КАТЕГОРИЯ_ЧИСЛ : СОБИР
ADV_SEMANTICS = 48                                 # enum ОБСТ_ВАЛ
# Coordiname ОБСТ_ВАЛ states:
S_LOCATION = 0                                     # ОБСТ_ВАЛ : МЕСТО
S_DIRECTION = 1                                    # ОБСТ_ВАЛ : НАПРАВЛЕНИЕ
S_DIRECTION_FROM = 2                               # ОБСТ_ВАЛ : НАПРАВЛЕНИЕ_ОТКУДА
S_FINAL_POINT = 3                                  # ОБСТ_ВАЛ : КОНЕЧНАЯ_ТОЧКА
S_DISTANCE = 4                                     # ОБСТ_ВАЛ : РАССТОЯНИЕ
S_VELOCITY = 5                                     # ОБСТ_ВАЛ : СКОРОСТЬ
S_MOMENT = 6                                       # ОБСТ_ВАЛ : МОМЕНТ_ВРЕМЕНИ
S_DURATION = 7                                     # ОБСТ_ВАЛ : ДЛИТЕЛЬНОСТЬ
S_TIME_DIVISIBILITY = 8                            # ОБСТ_ВАЛ : КРАТНОСТЬ
S_ANALOG = 9                                       # ОБСТ_ВАЛ : СОПОСТАВЛЕНИЕ
S_FACTOR = 10                                      # ОБСТ_ВАЛ : МНОЖИТЕЛЬ
ADJ_TYPE = 49                                      # enum ТИП_ПРИЛ
# Coordiname ТИП_ПРИЛ states:
ADJ_POSSESSIVE = 0                                 # ТИП_ПРИЛ : ПРИТЯЖ
ADJ_ORDINAL = 1                                    # ТИП_ПРИЛ : ПОРЯДК
PRONOUN_TYPE_ru = 51                               # enum ТИП_МЕСТОИМЕНИЯ
# Coordiname ТИП_МЕСТОИМЕНИЯ states:
VERB_TYPE_ru = 52                                  # enum ТИП_ГЛАГОЛА
# Coordiname ТИП_ГЛАГОЛА states:
COPULA_VERB_ru = 2                                 # ТИП_ГЛАГОЛА : СВЯЗОЧН
PARTICLE_TYPE = 53                                 # enum ТИП_ЧАСТИЦЫ
# Coordiname ТИП_ЧАСТИЦЫ states:
PREFIX_PARTICLE = 0                                # ТИП_ЧАСТИЦЫ : ПРЕФИКС
POSTFIX_PARTICLE = 1                               # ТИП_ЧАСТИЦЫ : ПОСТФИКС
ADV_MODIF_TYPE = 54                                # enum ТИП_МОДИФ
# Coordiname ТИП_МОДИФ states:
TENSE_en = 55                                      # enum TENSE
# Coordiname TENSE states:
PAST_en = 0                                        # TENSE : PAST
PRESENT_en = 1                                     # TENSE : PRESENT
FUTURE_en = 2                                      # TENSE : FUTURE
IMPERATIVE_en = 3                                  # TENSE : IMPERATIVE
DURATION_en = 56                                   # enum DURATION
# Coordiname DURATION states:
SIMPLE_en = 0                                      # DURATION : INDEFINITE
CONTINUOUS_en = 1                                  # DURATION : CONTINUOUS
PERFECT_en = 2                                     # DURATION : PERFECT
PERFECT_CONTINUOS_en = 3                           # DURATION : PERFECT_CONTINUOUS
VOICE_en = 57                                      # enum VOICE
# Coordiname VOICE states:
PASSIVE_en = 0                                     # VOICE : PASSIVE
ACTIVE_en = 1                                      # VOICE : ACTIVE
CASE_en = 58                                       # enum CASE
# Coordiname CASE states:
NOMINATIVE_CASE_en = 0                             # CASE : NOMINATIVE
PREPOSITIVE_CASE_en = 1                            # CASE : PREPOSITIVE
NOUN_FORM_en = 59                                  # enum NOUN_FORM
# Coordiname NOUN_FORM states:
BASIC_NOUN_FORM_en = 0                             # NOUN_FORM : BASIC
POSSESSIVE_NOUN_FORM_en = 1                        # NOUN_FORM : POSSESSIVE
HAS_POSSESSIVE_FORM_en = 60                        # enum HAS_POSSESSIVE_FORM
PRONOUN_FORM_en = 61                               # enum PRONOUN_FORM
# Coordiname PRONOUN_FORM states:
ADJ_FORM_en = 62                                   # enum ADJ_FORM
# Coordiname ADJ_FORM states:
BASIC_ADJ_en = 0                                   # ADJ_FORM : BASIC
COMPARATIVE_ADJ_en = 1                             # ADJ_FORM : COMPARATIVE
SUPERLATIVE_ADJ_en = 2                             # ADJ_FORM : SUPERLATIVE
COMPARABILITY_en = 63                              # enum COMPARABILITY
# Coordiname COMPARABILITY states:
ANALYTIC_en = 0                                    # COMPARABILITY : ANALYTIC
SYNTHETIC_en = 1                                   # COMPARABILITY : SYNTHETIC
COMPARABLE_en = 2                                  # COMPARABILITY : COMPARABLE
NONCOMPARABLE = 3                                  # COMPARABILITY : NONCOMPARABLE
VERB_FORM_en = 64                                  # enum VERB_FORM
# Coordiname VERB_FORM states:
UNDEF_VERBFORM_en = 0                              # VERB_FORM : UNDEF
S_VERBFORM_en = 1                                  # VERB_FORM : S
ED_VERBFORM_en = 2                                 # VERB_FORM : ED
ING_VERBFORM_en = 3                                # VERB_FORM : ING
PP_VERBFORM_en = 4                                 # VERB_FORM : PP
INF_VEBFORM_en = 5                                 # VERB_FORM : INF
ARTICLE_FORM = 65                                  # enum ARTICLE_FORM
# Coordiname ARTICLE_FORM states:
ARTICLE_FORM_1 = 0                                 # ARTICLE_FORM : 1
ARTICLE_FORM_2 = 1                                 # ARTICLE_FORM : 2
NUMERAL_FORM_en = 66                               # enum NUMERAL_FORM
# Coordiname NUMERAL_FORM states:
CARDINAL_en = 0                                    # NUMERAL_FORM : CARDINAL
ORDINAL_en = 1                                     # NUMERAL_FORM : ORDINAL
GENDER_en = 67                                     # enum ENG_GENDER
# Coordiname ENG_GENDER states:
MASCULINE_en = 0                                   # ENG_GENDER : MASCULINE
FEMININE_en = 1                                    # ENG_GENDER : FEMININE
TRANSITIVITY_en = 68                               # enum TRANSITIVITY
# Coordiname TRANSITIVITY states:
INTRANSITIVE_VERB_en = 0                           # TRANSITIVITY : INTRANSITIVE
TRANSITIVE_VERB_en = 1                             # TRANSITIVITY : TRANSITIVE
OBLIG_TRANSITIVITY_en = 69                         # enum OBLIG_TRANSITIVITY
# Coordiname OBLIG_TRANSITIVITY states:
VERB_SLOTS_en = 70                                 # enum VERB_SLOTS
# Coordiname VERB_SLOTS states:
DITRANSITIVE_en = 0                                # VERB_SLOTS : DITRANSITIVE
COPULATIVE_en = 1                                  # VERB_SLOTS : COPULATIVE
GERUND_en = 2                                      # VERB_SLOTS : GERUND
PastParticipleSlot_en = 3                          # VERB_SLOTS : PastParticiple
DIRECT_MODALITY_en = 4                             # VERB_SLOTS : ModalDirect
TO_MODALITY_en = 5                                 # VERB_SLOTS : ModalTo
PROPER_NOUN_en = 71                                # enum ENG_PROPER_NOUN
MASS_NOUN_en = 72                                  # enum ENG_MASS_NOUN
MODAL_NOUN_en = 73                                 # enum ENG_MODAL_NOUN
PERSON_fr = 77                                     # enum FR_PERSON
# Coordiname FR_PERSON states:
PERSON_1_fr = 0                                    # FR_PERSON : 1
PERSON_2_fr = 1                                    # FR_PERSON : 2
PERSON_3_fr = 2                                    # FR_PERSON : 3
NUMBER_fr = 78                                     # enum FR_NOMBRE
# Coordiname FR_NOMBRE states:
SINGULAR_fr = 0                                    # FR_NOMBRE : SINGULIER
PLURAL_fr = 1                                      # FR_NOMBRE : PLURIEL
GENDER_fr = 79                                     # enum FR_GENRE
# Coordiname FR_GENRE states:
MASCULINE_fr = 0                                   # FR_GENRE : MASCULINE
FEMININE_fr = 1                                    # FR_GENRE : FEMININE
FR_NUMERAL_FORM = 80                               # enum FR_NUMERAL_FORM
# Coordiname FR_NUMERAL_FORM states:
CARDINAL_fr = 0                                    # FR_NUMERAL_FORM : CARDINAL
ORDINAL_fr = 1                                     # FR_NUMERAL_FORM : ORDINAL
FR_PRONOUN_FORM = 81                               # enum FR_PRONOUN_FORM
# Coordiname FR_PRONOUN_FORM states:
FR_PRONOUN_WEAK = 0                                # FR_PRONOUN_FORM : WEAK
FR_PRONOUN_STRONG = 1                              # FR_PRONOUN_FORM : STRONG
TRANSITIVITY_fr = 82                               # enum FR_TRANSITIVITY
# Coordiname FR_TRANSITIVITY states:
INTRANSITIVE_VERB_fr = 0                           # FR_TRANSITIVITY : INTRANSITIVE
TRANSITIVE_VERB_fr = 1                             # FR_TRANSITIVITY : TRANSITIVE
VERB_FORM_fr = 83                                  # enum FR_VERB_FORM
# Coordiname FR_VERB_FORM states:
INFINITIVE_fr = 0                                  # FR_VERB_FORM : INFINITIVE
PRESENT_VF_fr = 1                                  # FR_VERB_FORM : PRESENT
FUTURE_VF_fr = 2                                   # FR_VERB_FORM : FUTURE
IMPERFECT_VB_fr = 3                                # FR_VERB_FORM : IMPERFECT
SIMPLE_PAST_fr = 4                                 # FR_VERB_FORM : SIMPLE_PAST
PRESENT_PARTICIPLE_fr = 5                          # FR_VERB_FORM : PRESENT_PARTICIPLE
PAST_PARTICIPLE_fr = 6                             # FR_VERB_FORM : PAST_PARTICIPLE
SUBJUNCTIVE_PRESENT_fr = 7                         # FR_VERB_FORM : SUBJUNCTIVE_PRESENT
SUBJUNCTIVE_IMPERFECT_fr = 8                       # FR_VERB_FORM : SUBJUNCTIVE_IMPERFECT
CONDITIONAL_fr = 9                                 # FR_VERB_FORM : CONDITIONAL
IMPERATIVE_fr = 10                                 # FR_VERB_FORM : IMPERATIVE
JAP_FORM = 84                                      # enum JAP_FORM
# Coordiname JAP_FORM states:
KANA_FORM = 0                                      # JAP_FORM : KANA
KANJI_FORM = 1                                     # JAP_FORM : KANJI
ROMAJI_FORM = 2                                    # JAP_FORM : ROMAJI
JAP_VERB_BASE = 85                                 # enum JAP_VERB_BASE
# Coordiname JAP_VERB_BASE states:
JAP_VB_I = 0                                       # JAP_VERB_BASE : I
JAP_VB_II = 1                                      # JAP_VERB_BASE : II
JAP_VB_III = 2                                     # JAP_VERB_BASE : III
JAP_VB_IV = 3                                      # JAP_VERB_BASE : IV
JAP_VB_V = 4                                       # JAP_VERB_BASE : V
JAP_VB_PAST = 5                                    # JAP_VERB_BASE : PAST
JAP_VB_PARTICIPLE = 6                              # JAP_VERB_BASE : PARTICIPLE
JAP_VB_POTENTIAL = 7                               # JAP_VERB_BASE : POTENTIAL
JAP_VB_CONDITIONAL = 8                             # JAP_VERB_BASE : CONDITIONAL
JAP_VB_CAUSATIVE = 9                               # JAP_VERB_BASE : CAUSATIVE
JAP_VERB_KIND = 86                                 # enum JAP_VERB_KIND
# Coordiname JAP_VERB_KIND states:
JAP_PRESENT_FUTURE = 1                             # JAP_VERB_KIND : PRESENT_FUTURE
JAP_NEGATIVE_PRESENT_FUTURE = 3                    # JAP_VERB_KIND : NEGATIVE_PRESENT_FUTURE
JAP_NEGATIVE_PAST = 4                              # JAP_VERB_KIND : NEGATIVE_PAST
JAP_IMPERATIVE = 5                                 # JAP_VERB_KIND : IMPERATIVE
JAP_NEGATIVE_IMPERATIVE = 6                        # JAP_VERB_KIND : NEGATIVE_IMPERATIVE
JAP_ADJ_BASE = 87                                  # enum JAP_ADJ_BASE
# Coordiname JAP_ADJ_BASE states:
JAP_AB_I = 0                                       # JAP_ADJ_BASE : I
JAP_AB_II = 1                                      # JAP_ADJ_BASE : II
JAP_AB_III = 2                                     # JAP_ADJ_BASE : III
JAP_AB_IV = 3                                      # JAP_ADJ_BASE : IV
JAP_AB_V = 4                                       # JAP_ADJ_BASE : V
JAP_AB_T = 5                                       # JAP_ADJ_BASE : T
JAP_AB_PAST = 6                                    # JAP_ADJ_BASE : PAST
JAP_ADJ_FORM2 = 88                                 # enum JAP_ADJ_FORM2
# Coordiname JAP_ADJ_FORM2 states:
JAP_NEGATIVE_PRESENT_ADJ = 0                       # JAP_ADJ_FORM2 : NEGATIVE_PRESENT
JAP_NEGATIVE_PAST_ADJ = 1                          # JAP_ADJ_FORM2 : NEGATIVE_PAST
JAP_TRANSITIVE = 89                                # enum JAP_TRANSITIVE
CASE_jap = 90                                      # enum JAP_CASE
# Coordiname JAP_CASE states:
VOCATIVE_jap = 0                                   # JAP_CASE : VOCATIVE
NOMINATIVE_THEM_jap = 1                            # JAP_CASE : NOMINATIVE_THEM
NOMINATIVE_RHEM_jap = 2                            # JAP_CASE : NOMINATIVE_RHEM
ACCUSATIVE_jap = 3                                 # JAP_CASE : ACCUSATIVE
GENITIVE_jap = 4                                   # JAP_CASE : GENITIVE
DATIVE_jap = 5                                     # JAP_CASE : DATIVE
ALLATIVE_jap = 6                                   # JAP_CASE : ALLATIVE
INSTRUMENTATIVE_jap = 7                            # JAP_CASE : INSTRUMENTATIVE
ELATIVE_jap = 8                                    # JAP_CASE : ELATIVE
LIMITIVE_jap = 9                                   # JAP_CASE : LIMITIVE
COMPARATIVE_jap = 10                               # JAP_CASE : COMPARATIVE
COMITATIVE_jap = 11                                # JAP_CASE : COMITATIVE
SOCIATIVE_jap = 12                                 # JAP_CASE : SOCIATIVE
GENDER_jap = 91                                    # enum JAP_GENDER
# Coordiname JAP_GENDER states:
MASCULINE_jap = 0                                  # JAP_GENDER : MASCULINE
FEMININE_jap = 1                                   # JAP_GENDER : FEMININE
PERSON_jap = 92                                    # enum JAP_PERSON
# Coordiname JAP_PERSON states:
PERSON_1_jap = 0                                   # JAP_PERSON : 1
PERSON_2_jap = 1                                   # JAP_PERSON : 2
PERSON_3_jap = 2                                   # JAP_PERSON : 3
NUMBER_jap = 93                                    # enum JAP_NUMBER
# Coordiname JAP_NUMBER states:
SINGULAR_jap = 0                                   # JAP_NUMBER : SINGULAR
PLURAL_jap = 1                                     # JAP_NUMBER : PLURAL
JAP_PRONOUN_TYPE = 94                              # enum JAP_PRONOUN_TYPE
# Coordiname JAP_PRONOUN_TYPE states:
PERSONAL_jap = 0                                   # JAP_PRONOUN_TYPE : PERSONAL
POINTING_jap = 1                                   # JAP_PRONOUN_TYPE : POINTING
POSSESSIVE_jap = 2                                 # JAP_PRONOUN_TYPE : POSSESSIVE
# ------------------------------------------------------------


OBJECT_link = 0
ATTRIBUTE_link = 1
CONDITION_link = 2
CONSEQUENCE_link = 3
SUBJECT_link = 4
RHEMA_link = 5
COVERB_link = 6
NUMBER2OBJ_link = 12
TO_VERB_link = 16
TO_INF_link = 17
TO_PERFECT = 18
TO_UNPERFECT = 19
TO_NOUN_link = 20
TO_ADJ_link = 21
TO_ADV_link = 22
TO_RETVERB = 23
TO_GERUND_2_link = 24
WOUT_RETVERB = 25
TO_ENGLISH_link = 26
TO_RUSSIAN_link = 27
TO_FRENCH_link = 28
SYNONYM_link = 29
SEX_SYNONYM_link = 30
CLASS_link = 31
MEMBER_link = 32
TO_SPANISH_link = 33
TO_GERMAN_link = 34
TO_CHINESE_link = 35
TO_POLAND_link = 36
TO_ITALIAN_link = 37
TO_PORTUGUAL_link = 38
ACTION_link = 39
ACTOR_link = 40
TOOL_link = 41
RESULT_link = 42
TO_JAPANESE_link = 43
TO_KANA_link = 44
TO_KANJI_link = 45
ANTONYM_link = 46
EXPLANATION_link = 47
WWW_link = 48
ACCENT_link = 49
YO_link = 50
TO_DIMINUITIVE_link = 51
TO_RUDE_link = 52
TO_BIGGER_link = 53
TO_NEUTRAL_link = 54
TO_SCOLARLY = 55
TO_SAMPLE_link = 56
USAGE_TAG_link = 57
PROPERTY_link = 58
TO_CYRIJI_link = 59
HABITANT_link = 60
CHILD_link = 61
PARENT_link = 62
UNIT_link = 63
SET_link = 64
TO_WEAKENED_link = 65
VERBMODE_BASIC_link = 66
NEGATION_PARTICLE_link = 67
NEXT_COLLOCATION_ITEM_link = 68
SUBORDINATE_CLAUSE_link = 69
RIGHT_GENITIVE_OBJECT_link = 70
ADV_PARTICIPLE_link = 71
POSTFIX_PARTICLE_link = 72
INFINITIVE_link = 73
NEXT_ADJECTIVE_link = 74
NEXT_NOUN_link = 75
THEMA_link = 76
RIGHT_AUX2INFINITIVE_link = 77
RIGHT_AUX2PARTICIPLE = 78
RIGHT_AUX2ADJ = 79
RIGHT_LOGIC_ITEM_link = 80
RIGHT_COMPARISON_Y_link = 81
RIGHT_NOUN_link = 82
RIGHT_NAME_link = 83
ADJ_PARTICIPLE_link = 84
PUNCTUATION_link = 85
IMPERATIVE_SUBJECT_link = 86
IMPERATIVE_VERB2AUX_link = 87
AUX2IMPERATIVE_VERB = 88
PREFIX_PARTICLE_link = 89
PREFIX_CONJUNCTION_link = 90
LOGICAL_CONJUNCTION_link = 91
NEXT_CLAUSE_link = 92
LEFT_AUX_VERB_link = 93
BEG_INTRO_link = 94
RIGHT_PREPOSITION_link = 95
WH_SUBJECT_link = 96
IMPERATIVE_PARTICLE_link = 97
GERUND_link = 98
PREPOS_ADJUNCT_link = 99
DIRECT_OBJ_INTENTION_link = 100
COPULA_link = 101
DETAILS_link = 102
SENTENCE_CLOSER_link = 103
OPINION_link = 104
APPEAL_link = 105
TERM_link = 106
SPEECH_link = 107
QUESTION_link = 108
POLITENESS_link = 109
SEPARATE_ATTR_link = 110
POSSESSION_POSTFIX_link = 111
COMPOUND_PREFIX_link = 112
UNKNOWN_SLOT_link = 113
SECOND_VERB_link = 114
