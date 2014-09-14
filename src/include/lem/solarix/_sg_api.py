# -*- coding: utf-8
# This file is generated 30.08.2014 10:31:20 by Ygres compiler ver. 13.23.11072 Standard Win32  (build date Aug 29 2014).
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


NUM_WORD_CLASS = 3                                 # class num_word
NOUN_ru = 7                                        # class СУЩЕСТВИТЕЛЬНОЕ
PRONOUN2_ru = 8                                    # class МЕСТОИМ_СУЩ
PRONOUN_ru = 9                                     # class МЕСТОИМЕНИЕ
ADJ_ru = 10                                        # class ПРИЛАГАТЕЛЬНОЕ
NUMBER_CLASS_ru = 11                               # class ЧИСЛИТЕЛЬНОЕ
INFINITIVE_ru = 12                                 # class ИНФИНИТИВ
VERB_ru = 13                                       # class ГЛАГОЛ
GERUND_2_ru = 14                                   # class ДЕЕПРИЧАСТИЕ
PREPOS_ru = 15                                     # class ПРЕДЛОГ
IMPERSONAL_VERB_ru = 16                            # class БЕЗЛИЧ_ГЛАГОЛ
PARTICLE_ru = 19                                   # class ЧАСТИЦА
CONJ_ru = 20                                       # class СОЮЗ
ADVERB_ru = 21                                     # class НАРЕЧИЕ
PUNCTUATION_class = 22                             # class ПУНКТУАТОР
POSTPOS_ru = 27                                    # class ПОСЛЕЛОГ
POSESS_PARTICLE = 28                               # class ПРИТЯЖ_ЧАСТИЦА
VERB_en = 29                                       # class ENG_VERB
NOUN_en = 30                                       # class ENG_NOUN
PRONOUN_en = 31                                    # class ENG_PRONOUN
ARTICLE_en = 32                                    # class ENG_ARTICLE
PREP_en = 33                                       # class ENG_PREP
CONJ_en = 34                                       # class ENG_CONJ
ADV_en = 35                                        # class ENG_ADVERB
ADJ_en = 36                                        # class ENG_ADJECTIVE
PARTICLE_en = 37                                   # class ENG_PARTICLE
NUMERAL_en = 38                                    # class ENG_NUMERAL
INTERJECTION_en = 39                               # class ENG_INTERJECTION
NUMERAL_fr = 40                                    # class FR_NUMERAL
ARTICLE_fr = 41                                    # class FR_ARTICLE
PREP_fr = 42                                       # class FR_PREP
ADV_fr = 43                                        # class FR_ADVERB
CONJ_fr = 44                                       # class FR_CONJ
NOUN_fr = 45                                       # class FR_NOUN
ADJ_fr = 46                                        # class FR_ADJ
PRONOUN_fr = 47                                    # class FR_PRONOUN
VERB_fr = 48                                       # class FR_VERB
PARTICLE_fr = 49                                   # class FR_PARTICLE
PRONOUN2_fr = 50                                   # class FR_PRONOUN2
NOUN_es = 51                                       # class ES_NOUN
ROOT_es = 52                                       # class ES_ROOT
JAP_NOUN = 53                                      # class JAP_NOUN
JAP_NUMBER = 54                                    # class JAP_NUMBER
JAP_ADJECTIVE = 55                                 # class JAP_ADJECTIVE
JAP_ADVERB = 56                                    # class JAP_ADVERB
JAP_CONJ = 57                                      # class JAP_CONJ
JAP_VERB = 58                                      # class JAP_VERB
JAP_PRONOUN = 59                                   # class JAP_PRONOUN
JAP_VERB_POSTFIX2 = 62                             # class JAP_VERB_POSTFIX2
JAP_PARTICLE = 64                                  # class JAP_PARTICLE
UNKNOWN_ENTRIES_CLASS = 75                         # class UnknownEntries
# ------------------------------------------------------------


CharCasing = 5                                     # enum CharCasing
# Coordiname CharCasing states:
DECAPITALIZED_CASED = 0                            # CharCasing : Lower
FIRST_CAPITALIZED_CASED = 1                        # CharCasing : FirstCapitalized
ALL_CAPITALIZED_CASED = 2                          # CharCasing : Upper
EACH_LEXEM_CAPITALIZED_CASED = 3                   # CharCasing : EachLexemCapitalized
PERSON_xx = 7                                      # enum PERSON
# Coordiname PERSON states:
PERSON_1_xx = 0                                    # PERSON : 1
PERSON_2_xx = 1                                    # PERSON : 2
PERSON_3_xx = 2                                    # PERSON : 3
NUMBER_xx = 8                                      # enum NUMBER
# Coordiname NUMBER states:
SINGLE_xx = 0                                      # NUMBER : SINGLE
PLURAL_xx = 1                                      # NUMBER : PLURAL
GENDER_xx = 9                                      # enum GENDER
# Coordiname GENDER states:
MASCULINE_xx = 0                                   # GENDER : MASCULINE
FEMININE_xx = 1                                    # GENDER : FEMININE
NEUTRAL_xx = 2                                     # GENDER : NEUTRAL
SPEECH_STYLE_xx = 10                               # enum СтильРечи
# Coordiname СтильРечи states:
STRENGTH_xx = 11                                   # enum РазмерСила
# Coordiname РазмерСила states:
PERSON_ru = 12                                     # enum ЛИЦО
# Coordiname ЛИЦО states:
PERSON_1_ru = 0                                    # ЛИЦО : 1
PERSON_2_ru = 1                                    # ЛИЦО : 2
PERSON_3_ru = 2                                    # ЛИЦО : 3
NUMBER_ru = 13                                     # enum ЧИСЛО
# Coordiname ЧИСЛО states:
SINGULAR_NUMBER_ru = 0                             # ЧИСЛО : ЕД
PLURAL_NUMBER_ru = 1                               # ЧИСЛО : МН
GENDER_ru = 14                                     # enum РОД
# Coordiname РОД states:
MASCULINE_GENDER_ru = 0                            # РОД : МУЖ
FEMININE_GENDER_ru = 1                             # РОД : ЖЕН
NEUTRAL_GENDER_ru = 2                              # РОД : СР
TRANSITIVENESS_ru = 15                             # enum ПЕРЕХОДНОСТЬ
# Coordiname ПЕРЕХОДНОСТЬ states:
NONTRANSITIVE_VERB_ru = 0                          # ПЕРЕХОДНОСТЬ : НЕПЕРЕХОДНЫЙ
TRANSITIVE_VERB_ru = 1                             # ПЕРЕХОДНОСТЬ : ПЕРЕХОДНЫЙ
PARTICIPLE_ru = 16                                 # enum ПРИЧАСТИЕ
PASSIVE_PARTICIPLE_ru = 17                         # enum СТРАД
ASPECT_ru = 18                                     # enum ВИД
# Coordiname ВИД states:
PERFECT_ru = 0                                     # ВИД : СОВЕРШ
IMPERFECT_ru = 1                                   # ВИД : НЕСОВЕРШ
VERB_FORM_ru = 20                                  # enum НАКЛОНЕНИЕ
# Coordiname НАКЛОНЕНИЕ states:
VB_INF_ru = 0                                      # НАКЛОНЕНИЕ : ИЗЪЯВ
VB_ORDER_ru = 1                                    # НАКЛОНЕНИЕ : ПОБУД
TENSE_ru = 21                                      # enum ВРЕМЯ
# Coordiname ВРЕМЯ states:
PAST_ru = 0                                        # ВРЕМЯ : ПРОШЕДШЕЕ
PRESENT_ru = 1                                     # ВРЕМЯ : НАСТОЯЩЕЕ
FUTURE_ru = 2                                      # ВРЕМЯ : БУДУЩЕЕ
SHORTNESS_ru = 22                                  # enum КРАТКИЙ
CASE_ru = 24                                       # enum ПАДЕЖ
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
FORM_ru = 25                                       # enum ОДУШ
# Coordiname ОДУШ states:
ANIMATIVE_FORM_ru = 0                              # ОДУШ : ОДУШ
INANIMATIVE_FORM_ru = 1                            # ОДУШ : НЕОДУШ
COUNTABILITY_ru = 26                               # enum ПЕРЕЧИСЛИМОСТЬ
# Coordiname ПЕРЕЧИСЛИМОСТЬ states:
COUNTABLE_ru = 0                                   # ПЕРЕЧИСЛИМОСТЬ : ДА
UNCOUNTABLE_ru = 1                                 # ПЕРЕЧИСЛИМОСТЬ : НЕТ
COMPAR_FORM_ru = 27                                # enum СТЕПЕНЬ
# Coordiname СТЕПЕНЬ states:
ATTRIBUTIVE_FORM_ru = 0                            # СТЕПЕНЬ : АТРИБ
COMPARATIVE_FORM_ru = 1                            # СТЕПЕНЬ : СРАВН
SUPERLATIVE_FORM_ru = 2                            # СТЕПЕНЬ : ПРЕВОСХ
CASE_GERUND_ru = 28                                # enum ПадежВал
# Coordiname ПадежВал states:
MODAL_ru = 29                                      # enum МОДАЛЬНЫЙ
VERBMODE_TENSE = 30                                # enum СГД_Время
# Coordiname СГД_Время states:
VERBMODE_DIRECTION = 31                            # enum СГД_Направление
# Coordiname СГД_Направление states:
NUMERAL_CATEGORY = 32                              # enum КАТЕГОРИЯ_ЧИСЛ
# Coordiname КАТЕГОРИЯ_ЧИСЛ states:
CARDINAL = 0                                       # КАТЕГОРИЯ_ЧИСЛ : КОЛИЧ
COLLECTION = 1                                     # КАТЕГОРИЯ_ЧИСЛ : СОБИР
ADV_SEMANTICS = 33                                 # enum ОБСТ_ВАЛ
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
ADJ_TYPE = 34                                      # enum ТИП_ПРИЛ
# Coordiname ТИП_ПРИЛ states:
ADJ_POSSESSIVE = 0                                 # ТИП_ПРИЛ : ПРИТЯЖ
ADJ_ORDINAL = 1                                    # ТИП_ПРИЛ : ПОРЯДК
TENSE_en = 40                                      # enum TENSE
# Coordiname TENSE states:
PAST_en = 0                                        # TENSE : PAST
PRESENT_en = 1                                     # TENSE : PRESENT
FUTURE_en = 2                                      # TENSE : FUTURE
DURATION_en = 41                                   # enum DURATION
# Coordiname DURATION states:
SIMPLE_en = 0                                      # DURATION : INDEFINITE
CONTINUOUS_en = 1                                  # DURATION : CONTINUOUS
PERFECT_en = 2                                     # DURATION : PERFECT
PERFECT_CONTINUOS_en = 3                           # DURATION : PERFECT_CONTINUOUS
VOICE_en = 42                                      # enum VOICE
# Coordiname VOICE states:
PASSIVE_en = 0                                     # VOICE : PASSIVE
ACTIVE_en = 1                                      # VOICE : ACTIVE
CASE_en = 43                                       # enum CASE
# Coordiname CASE states:
NOMINATIVE_CASE_en = 0                             # CASE : NOMINATIVE
PREPOSITIVE_CASE_en = 1                            # CASE : PREPOSITIVE
NOUN_FORM_en = 44                                  # enum NOUN_FORM
# Coordiname NOUN_FORM states:
BASIC_NOUN_FORM_en = 0                             # NOUN_FORM : BASIC
POSSESSIVE_NOUN_FORM_en = 1                        # NOUN_FORM : POSSESSIVE
PRONOUN_FORM_en = 45                               # enum PRONOUN_FORM
# Coordiname PRONOUN_FORM states:
ADJ_FORM_en = 46                                   # enum ADJ_FORM
# Coordiname ADJ_FORM states:
BASIC_ADJ_en = 0                                   # ADJ_FORM : BASIC
COMPARATIVE_ADJ_en = 1                             # ADJ_FORM : COMPARATIVE
SUPERLATIVE_ADJ_en = 2                             # ADJ_FORM : SUPERLATIVE
COMPARABILITY_en = 47                              # enum COMPARABILITY
# Coordiname COMPARABILITY states:
ANALYTIC_en = 0                                    # COMPARABILITY : ANALYTIC
SYNTHETIC_en = 1                                   # COMPARABILITY : SYNTHETIC
COMPARABLE_en = 2                                  # COMPARABILITY : COMPARABLE
NONCOMPARABLE = 3                                  # COMPARABILITY : NONCOMPARABLE
VERB_FORM_en = 48                                  # enum VERB_FORM
# Coordiname VERB_FORM states:
UNDEF_VERBFORM_en = 0                              # VERB_FORM : UNDEF
ED_VERBFORM_en = 1                                 # VERB_FORM : ED
ING_VERBFORM_en = 2                                # VERB_FORM : ING
PP_VERBFORM_en = 3                                 # VERB_FORM : PP
INF_VEBFORM_en = 4                                 # VERB_FORM : INF
ARTICLE_FORM = 49                                  # enum ARTICLE_FORM
# Coordiname ARTICLE_FORM states:
ARTICLE_FORM_1 = 0                                 # ARTICLE_FORM : 1
ARTICLE_FORM_2 = 1                                 # ARTICLE_FORM : 2
ENG_MODALITY = 50                                  # enum ENG_MODALITY
# Coordiname ENG_MODALITY states:
DIRECT_MODALITY_en = 0                             # ENG_MODALITY : Direct
TO_MODALITY_en = 2                                 # ENG_MODALITY : To
NUMERAL_FORM_en = 51                               # enum NUMERAL_FORM
# Coordiname NUMERAL_FORM states:
CARDINAL_en = 0                                    # NUMERAL_FORM : CARDINAL
ORDINAL_en = 1                                     # NUMERAL_FORM : ORDINAL
GENDER_en = 52                                     # enum ENG_GENDER
# Coordiname ENG_GENDER states:
MASCULINE_en = 0                                   # ENG_GENDER : MASCULINE
FEMININE_en = 1                                    # ENG_GENDER : FEMININE
TRANSITIVITY_en = 53                               # enum TRANSITIVITY
# Coordiname TRANSITIVITY states:
INTRANSITIVE_VERB_en = 0                           # TRANSITIVITY : INTRANSITIVE
TRANSITIVE_VERB_en = 1                             # TRANSITIVITY : TRANSITIVE
OBLIG_TRANSITIVITY_en = 54                         # enum OBLIG_TRANSITIVITY
PROPER_NOUN_en = 55                                # enum ENG_PROPER_NOUN
MASS_NOUN_en = 56                                  # enum ENG_MASS_NOUN
PERSON_fr = 57                                     # enum FR_PERSON
# Coordiname FR_PERSON states:
PERSON_1_fr = 0                                    # FR_PERSON : 1
PERSON_2_fr = 1                                    # FR_PERSON : 2
PERSON_3_fr = 2                                    # FR_PERSON : 3
NUMBER_fr = 58                                     # enum FR_NOMBRE
# Coordiname FR_NOMBRE states:
SINGULAR_fr = 0                                    # FR_NOMBRE : SINGULIER
PLURAL_fr = 1                                      # FR_NOMBRE : PLURIEL
GENDER_fr = 59                                     # enum FR_GENRE
# Coordiname FR_GENRE states:
MASCULINE_fr = 0                                   # FR_GENRE : MASCULINE
FEMININE_fr = 1                                    # FR_GENRE : FEMININE
FR_NUMERAL_FORM = 60                               # enum FR_NUMERAL_FORM
# Coordiname FR_NUMERAL_FORM states:
CARDINAL_fr = 0                                    # FR_NUMERAL_FORM : CARDINAL
ORDINAL_fr = 1                                     # FR_NUMERAL_FORM : ORDINAL
FR_PRONOUN_FORM = 61                               # enum FR_PRONOUN_FORM
# Coordiname FR_PRONOUN_FORM states:
FR_PRONOUN_WEAK = 0                                # FR_PRONOUN_FORM : WEAK
FR_PRONOUN_STRONG = 1                              # FR_PRONOUN_FORM : STRONG
TRANSITIVITY_fr = 62                               # enum FR_TRANSITIVITY
# Coordiname FR_TRANSITIVITY states:
INTRANSITIVE_VERB_fr = 0                           # FR_TRANSITIVITY : INTRANSITIVE
TRANSITIVE_VERB_fr = 1                             # FR_TRANSITIVITY : TRANSITIVE
VERB_FORM_fr = 63                                  # enum FR_VERB_FORM
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
JAP_FORM = 64                                      # enum JAP_FORM
# Coordiname JAP_FORM states:
KANA_FORM = 0                                      # JAP_FORM : KANA
KANJI_FORM = 1                                     # JAP_FORM : KANJI
ROMAJI_FORM = 2                                    # JAP_FORM : ROMAJI
JAP_VERB_BASE = 65                                 # enum JAP_VERB_BASE
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
JAP_VERB_KIND = 66                                 # enum JAP_VERB_KIND
# Coordiname JAP_VERB_KIND states:
JAP_PRESENT_FUTURE = 1                             # JAP_VERB_KIND : PRESENT_FUTURE
JAP_NEGATIVE_PRESENT_FUTURE = 3                    # JAP_VERB_KIND : NEGATIVE_PRESENT_FUTURE
JAP_NEGATIVE_PAST = 4                              # JAP_VERB_KIND : NEGATIVE_PAST
JAP_IMPERATIVE = 5                                 # JAP_VERB_KIND : IMPERATIVE
JAP_NEGATIVE_IMPERATIVE = 6                        # JAP_VERB_KIND : NEGATIVE_IMPERATIVE
JAP_ADJ_BASE = 67                                  # enum JAP_ADJ_BASE
# Coordiname JAP_ADJ_BASE states:
JAP_AB_I = 0                                       # JAP_ADJ_BASE : I
JAP_AB_II = 1                                      # JAP_ADJ_BASE : II
JAP_AB_III = 2                                     # JAP_ADJ_BASE : III
JAP_AB_IV = 3                                      # JAP_ADJ_BASE : IV
JAP_AB_V = 4                                       # JAP_ADJ_BASE : V
JAP_AB_T = 5                                       # JAP_ADJ_BASE : T
JAP_AB_PAST = 6                                    # JAP_ADJ_BASE : PAST
JAP_ADJ_FORM2 = 68                                 # enum JAP_ADJ_FORM2
# Coordiname JAP_ADJ_FORM2 states:
JAP_NEGATIVE_PRESENT_ADJ = 0                       # JAP_ADJ_FORM2 : NEGATIVE_PRESENT
JAP_NEGATIVE_PAST_ADJ = 1                          # JAP_ADJ_FORM2 : NEGATIVE_PAST
JAP_TRANSITIVE = 69                                # enum JAP_TRANSITIVE
CASE_jap = 70                                      # enum JAP_CASE
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
GENDER_jap = 71                                    # enum JAP_GENDER
# Coordiname JAP_GENDER states:
MASCULINE_jap = 0                                  # JAP_GENDER : MASCULINE
FEMININE_jap = 1                                   # JAP_GENDER : FEMININE
PERSON_jap = 72                                    # enum JAP_PERSON
# Coordiname JAP_PERSON states:
PERSON_1_jap = 0                                   # JAP_PERSON : 1
PERSON_2_jap = 1                                   # JAP_PERSON : 2
PERSON_3_jap = 2                                   # JAP_PERSON : 3
NUMBER_jap = 73                                    # enum JAP_NUMBER
# Coordiname JAP_NUMBER states:
SINGULAR_jap = 0                                   # JAP_NUMBER : SINGULAR
PLURAL_jap = 1                                     # JAP_NUMBER : PLURAL
JAP_PRONOUN_TYPE = 74                              # enum JAP_PRONOUN_TYPE
# Coordiname JAP_PRONOUN_TYPE states:
PERSONAL_jap = 0                                   # JAP_PRONOUN_TYPE : PERSONAL
POINTING_jap = 1                                   # JAP_PRONOUN_TYPE : POINTING
POSSESSIVE_jap = 2                                 # JAP_PRONOUN_TYPE : POSSESSIVE
# ------------------------------------------------------------


OBJECT_link = 3
ATTRIBUTE_link = 4
CONDITION_link = 5
CONSEQUENCE_link = 6
SUBJECT_link = 7
RHEMA_link = 8
COVERB_link = 9
NUMBER2OBJ_link = 15
TO_VERB_link = 19
TO_INF_link = 20
TO_PERFECT = 21
TO_UNPERFECT = 22
TO_NOUN_link = 23
TO_ADJ_link = 24
TO_ADV_link = 25
TO_RETVERB = 26
TO_GERUND_2_link = 27
WOUT_RETVERB = 28
TO_ENGLISH_link = 29
TO_RUSSIAN_link = 30
TO_FRENCH_link = 31
SYNONYM_link = 32
SEX_SYNONYM_link = 33
CLASS_link = 34
MEMBER_link = 35
TO_SPANISH_link = 36
TO_GERMAN_link = 37
TO_CHINESE_link = 38
TO_POLAND_link = 39
TO_ITALIAN_link = 40
TO_PORTUGUAL_link = 41
ACTION_link = 42
ACTOR_link = 43
TOOL_link = 44
RESULT_link = 45
TO_JAPANESE_link = 46
TO_KANA_link = 47
TO_KANJI_link = 48
ANTONYM_link = 49
EXPLANATION_link = 50
WWW_link = 51
ACCENT_link = 52
YO_link = 53
TO_DIMINUITIVE_link = 54
TO_RUDE_link = 55
TO_BIGGER_link = 56
TO_NEUTRAL_link = 57
TO_SCOLARLY = 58
TO_SAMPLE_link = 59
USAGE_TAG_link = 60
PROPERTY_link = 61
TO_CYRIJI_link = 62
HABITANT_link = 63
CHILD_link = 64
PARENT_link = 65
UNIT_link = 66
SET_link = 67
TO_WEAKENED_link = 68
VERBMODE_BASIC_link = 69
NEGATION_PARTICLE_link = 70
NEXT_COLLOCATION_ITEM_link = 71
SUBORDINATE_CLAUSE_link = 72
RIGHT_GENITIVE_OBJECT_link = 73
ADV_PARTICIPLE_link = 74
POSTFIX_PARTICLE_link = 75
INFINITIVE_link = 76
NEXT_ADJECTIVE_link = 77
NEXT_NOUN_link = 78
THEMA_link = 79
RIGHT_PARTICLE_link = 80
RIGHT_AUX2INFINITIVE_link = 81
RIGHT_AUX2PARTICIPLE = 82
RIGHT_AUX2ADJ = 83
RIGHT_LOGIC_ITEM_link = 84
RIGHT_COMPARISON_Y_link = 85
RIGHT_NOUN_link = 86
RIGHT_INSTR_OBJECT_link = 87
RIGHT_DATIVE_OBJECT_link = 88
RIGHT_NAME_link = 89
ADJ_PARTICIPLE_link = 90
PUNCTUATION_link = 91
IMPERATIVE_SUBJECT_link = 92
IMPERATIVE_VERB2AUX_link = 93
AUX2IMPERATIVE_VERB = 94
PREFIX_PARTICLE_link = 95
PREFIX_CONJUNCTION_link = 96
LOGICAL_CONJUNCTION_link = 97
NEXT_CLAUSE_link = 98
LEFT_AUX_VERB_link = 99
BEG_INTRO_link = 100
RIGHT_PREPOSITION_link = 101
WH_SUBJECT_link = 102
IMPERATIVE_PARTICLE_link = 103
GERUND_link = 104
PREPOS_ADJUNCT_link = 105
DIRECT_OBJ_INTENTION_link = 106
COPULA_link = 107
DETAILS_link = 108
SENTENCE_CLOSER_link = 109
OPINION_link = 110
APPEAL_link = 111
TERM_link = 112
SPEECH_link = 113
QUESTION_link = 114
POLITENESS_link = 115
SEPARATE_ATTR_link = 116
