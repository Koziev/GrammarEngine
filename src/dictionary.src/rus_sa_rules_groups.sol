// -----------------------------------------------------------------------------
// File RUS_SA_RULES_GROUPS.SOL
//
// (c) Koziev Elijah
//
// Content:
// Объявления категорий правил для русского анализатора
//
// Подробнее о правилах: http://www.solarix.ru/for_developers/docs/rules.shtml
// -----------------------------------------------------------------------------
//
// CD->29.09.2004
// LC->09.05.2011
// --------------

automat aa
{
 rulegroup AA_RULES_FILTER // начальная фильтрация вариаторов


 // Для вводных фраз
 rulegroup AA_RULES_INTRO
 rulegroup AA_RULES_INTRO_2

 // Предварительная конвертация грамматических конструкций
 // "у него есть пистолет" --> "он имеет пистолет"
 rulegroup AA_RULES_CONVERT

 rulegroup LINK_PREPOSITIONS // предлоги с существительными или местоимениями

 // Перестановки
 rulegroup AA_RULES_TRANSMUTE

 // Идиомы, замены на базовые синонимы
 rulegroup AA_RULES_IDIOM_1
 rulegroup AA_RULES_IDIOM_N

 // Грамматические свертки (предлог с существительным и т.д.)
 rulegroup AA_RULES_CONV


 rulegroup LINK_NI // ОТРИЦАТЕЛЬНАЯ ЧАСТИЦА НИ с разными частями речи


 rulegroup LINK_ADVERB_PLUS_ADVERB // ОЧЕНЬ СИЛЬНО


 rulegroup AA_LINK_5

 rulegroup AA_LINK_10       // СИЛЬНО И БЫСТРО
 rulegroup AA_LINK_10_2
 rulegroup AA_LINK_10_3

 rulegroup AA_LINK_11       // СИЛЬНО ИЛИ БЫСТРО
 rulegroup AA_LINK_11_2
 rulegroup AA_LINK_11_3
 rulegroup OrAdverb3
 rulegroup OrAdverb3_2
 rulegroup OrAdverb3_3



 rulegroup AA_LINK_25       // БОЛЕЕ ЯРКИЙ - МЕНЕЕ ЯРКИЙ

 rulegroup LINK_ADVERB_2_ADJ   // ОЧЕНЬ СИЛЬНЫЙ

 rulegroup LINK_COMPARATIVE_ADJ_2_NOUN // СИЛЬНЕЕ КОШКИ
 rulegroup LINK_COMPARATIVE_ADV_2_VERB // бегает быстрее, чем кошка
 rulegroup LINK_COMPARATIVE_ADV_2_DEEPR // бегая быстрее, чем кошка
 rulegroup LINK_COMPARATIVE_ADV_2_INF // бегая быстрее, чем кошка


 rulegroup AA_LINK_40
 rulegroup LINK_DEEPR_PLUS_OBJECT    // ИГРАЯ В МЯЧИК
 
 rulegroup AA_DEEPR         // ДЕЕПРИЧАСТНЫЙ ОБОРОТ
 rulegroup AA_LINK_70
 
 rulegroup AA_LINK_75       // ЗАСНУВ И ПРОСНУВШИСЬ
 rulegroup AA_LINK_75_2
 rulegroup AA_LINK_75_3

 rulegroup AA_LINK_76       // ЗАСНУВ ИЛИ ПРОСНУВШИСЬ
 rulegroup AA_LINK_76_2
 rulegroup AA_LINK_76_3
 rulegroup OrDeepr3
 rulegroup OrDeepr3_2
 rulegroup OrDeepr3_3


 rulegroup AA_PRICH         // ПРИЧАСТНЫЙ ОБОРОТ 


 rulegroup AA_LINK_106      // ТЕПЛЫЙ И МЯГКИЙ
 rulegroup AA_LINK_106_2
 rulegroup AA_LINK_106_3

 rulegroup AA_LINK_1062      // ТЕПЛЫЙ ИЛИ МЯГКИЙ
 rulegroup AA_LINK_1062_2
 rulegroup AA_LINK_1062_3
 rulegroup OrAdj3
 rulegroup OrAdj3_2
 rulegroup OrAdj3_3


 rulegroup LINK_ADJ_2_NOUN  // БОЛЬШОЙ ЧЕЛОВЕК

 rulegroup LINK_CONOUN       // ЧЕЛОВЕК-ПАУК
 rulegroup LINK_NOUN_2_NOUN  // несколько существительных, одно из которых управляет остальными ПАРТИЯ ЛЮБИТЕЛЕЙ ПИВА
 rulegroup LINK_NOUN_2_INF   // есть небольшое кол-во модальный существительных "УМЕНИЕ ЛЕТАТЬ", "НАСТРОЙ СОЗДАВАТЬ"

 rulegroup AA_LINK_110      // КОШКА И СОБАКА
 rulegroup AA_LINK_110_2
 rulegroup AA_LINK_110_3

 rulegroup AA_LINK_111      // КОШКА ИЛИ СОБАКА
 rulegroup AA_LINK_111_2
 rulegroup AA_LINK_111_3
 rulegroup OrNoun3
 rulegroup OrNoun3_2
 rulegroup OrNoun3_3

 
 rulegroup AA_LINK_120

 rulegroup LINK_VERB_PLUS_OBJECT // ВИДИТ МЫШКУ
 rulegroup LINK_INF_PLUS_OBJECT // ВИДЕТЬ МЫШКУ
 rulegroup LINK_PARTICIPLE_PLUS_OBJECT // ВИДЯЩИЙ МЫШКУ
 rulegroup LINK_INF_PLUS_SUBJECT // МНЕ БЫ ПОСПАТЬ

 rulegroup LINK_NUMBER_PLUS_NUMBER // сто двадцать шесть
 rulegroup LINK_NUMBER_PLUS_NOUN // сто кошек
 rulegroup LINK_ONE_OF // один из нас

 rulegroup AA_LINK_130      // СПАТЬ И БЕГАТЬ 
 rulegroup AA_LINK_130_2
 rulegroup AA_LINK_130_3

 rulegroup AA_LINK_131      // СПАТЬ ИЛИ БЕГАТЬ 
 rulegroup AA_LINK_131_2
 rulegroup AA_LINK_131_3
 rulegroup OrInf3
 rulegroup OrInf3_2
 rulegroup OrInf3_3



 rulegroup LINK_VERB_PLUS_INF // НАЧАЛ ЧИТАТЬ
 rulegroup LINK_DEEPR_PLUS_INF // НАЧАВ ЧИТАТЬ
 rulegroup LINK_PARTICIPLE_PLUS_INF // НАЧАВШИЙ ЧИТАТЬ
 rulegroup LINK_ADJ_PLUS_INF // СПОСОБЕН ЧИТАТЬ


 rulegroup LINK_SUBJECT_VERB // подлежащее и сказуемое

 rulegroup AA_LINK_160      // СПИТ И ВИДИТ
 rulegroup AA_LINK_160_2
 rulegroup AA_LINK_160_3
 rulegroup LINK_VERB_AND    // НАДО СПАТЬ И ОН СПИТ
  
 rulegroup AA_LINK_161      // СПИТ ИЛИ ВИДИТ
 rulegroup AA_LINK_161_2
 rulegroup AA_LINK_161_3
 rulegroup OrVerb3
 rulegroup OrVerb3_2
 rulegroup OrVerb3_3


 rulegroup AA_LINK_FACT // СОКРАТ ЯВЛЯТСЯ ЧЕЛОВЕКОМ

  
 // Условный оборот ЕСЛИ ... ТО ...
 rulegroup AA_RULES_CONDITION

 // Кошка думает, что она сильнее собаки
 rulegroup AA_RULES_THAT

 // Кошка спит, потому что она вкусно поела
 rulegroup AA_RULES_BECAUSE0
 rulegroup AA_RULES_BECAUSE


 // Псевдко-"причастные обороты"
 // КОШКА, КОТОРАЯ СПИТ
 rulegroup LINK_NOUN_WHICH


 rulegroup LINK_ADJ_2_NUMBER

 rulegroup AA_QUOTES

 rulegroup LINK_MULTIWORD_PARTICIPLE


 // снежный, то есть белый
 rulegroup LINK_THAT_IS_1
 rulegroup LINK_THAT_IS_2


 // ни кошка, ни собака
 rulegroup LINK_DEEPR_NI_NI
 rulegroup LINK_PRONOUN_NI_NI
 rulegroup LINK_INF_NI_NI
 rulegroup LINK_VERB_NI_NI
 rulegroup LINK_NOUN_NI_NI
 rulegroup LINK_ADVERB_NI_NI
 rulegroup LINK_ADJ_NI_NI
 rulegroup LINK_NUMBER_NI_NI
  
 // то кошка, то собака
 rulegroup LINK_DEEPR_TO_TO
 rulegroup LINK_PRONOUN_TO_TO
 rulegroup LINK_INF_TO_TO
 rulegroup LINK_VERB_TO_TO
 rulegroup LINK_NOUN_TO_TO
 rulegroup LINK_ADVERB_TO_TO
 rulegroup LINK_ADJ_TO_TO
 rulegroup LINK_NUMBER_TO_TO

 // белый, но не прозрачный
 rulegroup LINK_ADJ_BUT
 rulegroup LINK_DEEPR_BUT
 rulegroup LINK_PRONOUN_BUT
 rulegroup LINK_INF_BUT
 rulegroup LINK_VERB_BUT
 rulegroup LINK_NOUN_BUT
 rulegroup LINK_ADVERB_BUT
 rulegroup LINK_NUMBER_BUT


 // сначала кошка, потом собака
 rulegroup LINK_ADJ_NEXT_1
 rulegroup LINK_ADJ_NEXT_2
 rulegroup LINK_DEEPR_NEXT_1
 rulegroup LINK_DEEPR_NEXT_2
 rulegroup LINK_PRONOUN_NEXT_1
 rulegroup LINK_PRONOUN_NEXT_2
 rulegroup LINK_INF_NEXT_1
 rulegroup LINK_INF_NEXT_2
 rulegroup LINK_VERB_NEXT_1
 rulegroup LINK_VERB_NEXT_2
 rulegroup LINK_NOUN_NEXT_1
 rulegroup LINK_NOUN_NEXT_2
 rulegroup LINK_ADVERB_NEXT_1
 rulegroup LINK_ADVERB_NEXT_2
 rulegroup LINK_NUMBER_NEXT_1
 rulegroup LINK_NUMBER_NEXT_2


 // КОГДА - ТОГДА
 rulegroup AA_WHEN_THEN

 // Прологовские предикаты
 rulegroup AA_RULES_PROLOG

 // Вопросы
 rulegroup AA_RULES_QUEST


 // Data mining
 rulegroup AA_RULES_KNOWLEDGES
 rulegroup AA_RULES_KNOWLEDGES_2

 rulegroup AA_RULES_TIME0

 rulegroup LINK_ADJ_2_ADJ


 rulegroup RusSA_Instant_AdjNoun
 rulegroup RusSA_Instant_Adverb
 rulegroup RusSA_Instant_Infinitive
 rulegroup RusSA_Instant_Noun
 rulegroup RusSA_Instant_Object

 rulegroup AA_RULES_INSTEAD_OF0
 rulegroup AA_RULES_INSTEAD_OF
 
 rulegroup AA_RULES_BEFORE0
 rulegroup AA_RULES_BEFORE

 rulegroup AA_RULES_AFTER0
 rulegroup AA_RULES_AFTER

 rulegroup AA_RULES_IN_ORDER_TO0
 rulegroup AA_RULES_IN_ORDER_TO

 rulegroup RusSA_SubClause

}

