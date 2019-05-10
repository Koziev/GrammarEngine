// -----------------------------------------------------------------------------
// File SG_NET_LINKS.SOL
//
// (c) Koziev Elijah www.solarix.ru
//
// Объявления типой связей для всех тезаурусов
//
// 20.09.2006 - убраны связки "в_без_ся", в_причастие, в_предикат.
//              в_предикат_сов, в_предикат_несов
//
// 28.09.2006 - введены веса (проводимости) связок
// 14.11.2007 - введена связка <член_класса>
// 07.08.2008 - введена связка sex_synonym для связей типа КОТ-КОШКА, БРАЗИЛЕЦ-БРАЗИЛЬЯНКА
// 03.03.2009 - добавлена связка to_japanese
// 25.03.2009 - добавлены связки to_kana и to_kanji для японского тезауруса
// 06.05.2009 - добавлены связи для тезауруса - antonym и expl
// 25.06.2009 - добавлены связи AFTER, BEFORE, INSTEAD_OF, IN_ORDER_TO, SUBCLAUSE
// 13.11.2009 - добавлены связи уменьш_ласк, груб, увелич, нейтрал
// 19.11.2009 - добавлена связь sample
// 04.12.2009 - добавлена связь usage_tag
// 02.01.2010 - добавлена связь double_letters
// 23.02.2010 - добавлена связь property
// 01.04.2010 - добавлена связь to_cyriji
// 07.04.2010 - добавлены связи habitant и ngram_etalon
// 07.09.2011 - добавлена связь SUBSTITUTION
// 05.10.2011 - начал добавлять типы связей для нового синтаксического
//              анализатора.
// 16.06.2012 - большая чистка списка типов, убрал LEFT_xxx и RIGHT_xxx
// 22.08.2014 - большая чистка
// 02.05.2019 - добавлена связь cognate для однокоренных слов
// -----------------------------------------------------------------------------
//
// CD->02.08.2005
// LC->02.05.2019
// --------------

#include "sg_defs.h"

automat sg
{
 enum net {
           OBJECT as OBJECT_link // прямое дополнение: читаю книгу

           ATTRIBUTE as ATTRIBUTE_link
           CONDITION as CONDITION_link // The Conditional: If Richard works hard, he will learn grammar.
                                       //                  ^^^^^^^^^^^^^^^^^^^^^^
           CONSEQUENCE as CONSEQUENCE_link
           SUBJECT as SUBJECT_link
		   RHEMA as RHEMA_link
           COVERB as COVERB_link // для привязки второго предиката в УМЕТЬ ЖИТЬ
           PREPEND_QUOTE // " перед словом
           APPEND_QUOTE  // " после слова
           PREPEND_APOSTROPHE // ' после слова      
           APPEND_APOSTROPHE // ' после слова      
           CONUMBER // группа числительных 
           NUMBER2OBJ as NUMBER2OBJ_link // связь числительного и существительного
           CONOUN // АППОЗИЦИЯ - группа существительных типа ГОСПОДИН ПРЕЗИДЕНТ, ЧЕЛОВЕК-ПАУК (аппозитив)
           SUBCLAUSE // связи с подчиненным предложением "я понял, что любит есть котик"
           ATTRIBUTE_EXC   // "бегает быстрее, чем"
          }

 // Для организации Грамматической Сети...
 enum net as NET_LINKS {
           в_предикат      =0 as TO_VERB_link
           в_инфинитив     =0 as TO_INF_link 
           в_сов           =0 as TO_PERFECT         
           в_несов         =0 as TO_UNPERFECT
           в_сущ           =0 as TO_NOUN_link
           в_прил          =0 as TO_ADJ_link
           в_наречие       =0 as TO_ADV_link 
           в_ся            =0 as TO_RETVERB
           в_деепричастие as TO_GERUND_2_link
           без_ся          as WOUT_RETVERB
           to_english      as TO_ENGLISH_link
           to_russian      as TO_RUSSIAN_link 
           to_french       as TO_FRENCH_link 
           synonym         as SYNONYM_link
           sex_synonym as SEX_SYNONYM_link  // пары слов типа ПОВАР-ПОВАРИХА
           в_класс         as CLASS_link // связь с гипернимом КОШКА-ЗВЕРЬ
           член_класса     as MEMBER_link // связь с гипонимом ЗВЕРЬ-КОШКА
           to_spanish      as TO_SPANISH_link 
           to_german       as TO_GERMAN_link 
           to_chinese      as TO_CHINESE_link 
           to_poland       as TO_POLAND_link  
           to_italian      as TO_ITALIAN_link
           to_portugual    as TO_PORTUGUAL_link  
            
           action          as ACTION_link
           actor           as ACTOR_link
           tool            as TOOL_link
           result          as RESULT_link

           to_japanese     as TO_JAPANESE_link
           to_kana         as TO_KANA_link  // японский: канджи в кану
           to_kanji        as TO_KANJI_link // японский: кана в канджи

           antonym         as ANTONYM_link // антонимы

           expl            as EXPLANATION_link // толкования и объяснения 
		   www             as WWW_link // ссылки на интернет-страницу с толкованием слова и пр.
           accent          as ACCENT_link // информация об ударении в слове 		   
		   yo              as YO_link // информация о правописании слов с ё
           
           уменьш_ласк     as TO_DIMINUITIVE_link // кошка-кошечка
           груб            as TO_RUDE_link        // андрей-андрюха
           увелич          as TO_BIGGER_link      // кошечка-кошка 
           нейтрал         as TO_NEUTRAL_link     // кошечка-кошка, злобушка-злоба
           книжн           as TO_SCOLARLY         // змей-змий, судьба-фортуна, разброс-дисперсия

           sample          as TO_SAMPLE_link // пример использования словарной статьи
           usage_tag       as USAGE_TAG_link  // метки употребления - например, "поэтич", "книжн", "груб", "нецензур"
           property        as PROPERTY_link  // для связи с характерными свойствами ХИТРЕЦ <property> ХИТРОСТЬ 
           to_cyriji       as TO_CYRIJI_link // для киридзи-записи японских слов
           habitant        as HABITANT_link // обитатель ШАХТЕР-ШАХТА КИТАЕЦ-КИТАЙ
           child_of        as CHILD_link
           parent_of       as PARENT_link
           unit_of         as UNIT_link
           set_of          as SET_link 
           to_weakened     as TO_WEAKENED_link // слабый-слабоватый
           verbmode_basic  as VERBMODE_BASIC_link // приоткрыть-открыть
          }


 enum net {
           NEGATION_PARTICLE     as NEGATION_PARTICLE_link
           NEXT_COLLOCATION_ITEM as NEXT_COLLOCATION_ITEM_link
           SUBORDINATE_CLAUSE    as SUBORDINATE_CLAUSE_link
           RIGHT_GENITIVE_OBJECT as RIGHT_GENITIVE_OBJECT_link // обложка книги
           ADV_PARTICIPLE        as ADV_PARTICIPLE_link // кот гуляет, расчитывая поймать мышь
           POSTFIX_PARTICLE      as POSTFIX_PARTICLE_link // купил ли ты хлеб
		   INFINITIVE            as INFINITIVE_link // буду --> петь
           NEXT_ADJECTIVE        as NEXT_ADJECTIVE_link // (следующее прилагательное в группе согласованных) большой жирный кот
           NEXT_NOUN             as NEXT_NOUN_link // (следующее существительное в группе согласованных) кошка и собака
           THEMA                 as THEMA_link // >>кошка<< - хищник
           RIGHT_AUX2INFINITIVE  as RIGHT_AUX2INFINITIVE_link // начал -> петь
           RIGHT_AUX2PARTICIPLE  as RIGHT_AUX2PARTICIPLE // был --> запущен
           RIGHT_AUX2ADJ         as RIGHT_AUX2ADJ // был --> зол   
           RIGHT_LOGIC_ITEM      as RIGHT_LOGIC_ITEM_link // много -> , но не часто
           RIGHT_COMPARISON_Y    as RIGHT_COMPARISON_Y_link // собака сильнее --> кошки
           RIGHT_NOUN            as RIGHT_NOUN_link // Планета --> Юпитер
           RIGHT_NAME            as RIGHT_NAME_link // Корпорация --> SynGen
           ADJ_PARTICIPLE        as ADJ_PARTICIPLE_link
           PUNCTUATION           as PUNCTUATION_link
           IMPERATIVE_SUBJECT    as IMPERATIVE_SUBJECT_link // подлежащее в императиве: Коля, спи
           IMPERATIVE_VERB2AUX   as IMPERATIVE_VERB2AUX_link // доп. глагол в императиве: Давай <-- ешь!
           AUX2IMPERATIVE_VERB   as AUX2IMPERATIVE_VERB // в паттерне: Давайте --> поедим
           PREFIX_PARTICLE       as PREFIX_PARTICLE_link // частицы, стоящие справа: а ну <-- давай спи!
           PREFIX_CONJUNCTION    as PREFIX_CONJUNCTION_link // и <-- кошка, и собака
           LOGICAL_CONJUNCTION   as LOGICAL_CONJUNCTION_link // ??? кошка и <-- собака
           NEXT_CLAUSE           as NEXT_CLAUSE_link // присоединенное предложение
           LEFT_AUX_VERB         as LEFT_AUX_VERB_link // I was <-- asked
           BEG_INTRO             as BEG_INTRO_link // Вводная конструкция: First of all, I need a book.
           RIGHT_PREPOSITION     as RIGHT_PREPOSITION_link // Where did you came --> from?
           WH_SUBJECT            as WH_SUBJECT_link // Who <-- am I?
           IMPERATIVE_PARTICLE   as IMPERATIVE_PARTICLE_link // Связь частиц вежливости для императива: Please don't interrupt me.
           GERUND                as GERUND_link // в присоединяемый герундий
           PREPOS_ADJUNCT        as PREPOS_ADJUNCT_link // предложное дополнение look --> at me
           DIRECT_OBJ_INTENTION  as DIRECT_OBJ_INTENTION_link // прилагательное в паттерне "KEEP POTATOES FRESH."
           COPULA                as COPULA_link
           DETAILS               as DETAILS_link // детализация и пояснения, например ЖИВОТНЫЕ: КОШКИ, СОБАКИ, ХОМЯКИ
           SENTENCE_CLOSER       as SENTENCE_CLOSER_link // концовка предложения, в том числе финальная точка или какой-то оборот типа , doesn't it?
           OPINION               as OPINION_link // обороты, которые выражают отношение говорящего к сообщению, в том числе концовки типа: It might be unpleasant, though.
           APPEAL                as APPEAL_link // Обращение: А вы, >>>друзья<<<, ...
           TERM                  as TERM_link // связи в арифметических выражениях "два <-- плюс --> три"
           SPEECH                as SPEECH_link // прямая речь "Он сказал --> : Поехали!"
           QUESTION              as QUESTION_link // к вопросительному слову: Как <-- сварить квас?
           POLITENESS            as POLITENESS_link // Разные обороты вежливости: Налей, пожалуйста, еще чаю.
           SEPARATE_ATTR         as SEPARATE_ATTR_link // обособленные группы прилагательных в предикате
		   POSSESSION_POSTFIX    as POSSESSION_POSTFIX_link // Притяжательный постфикс 's в английских существительных
           COMPOUND_PREFIX       as COMPOUND_PREFIX_link // присоединяем префикс составного слова типа "quasi-cash"
           UNKNOWN_SLOT          as UNKNOWN_SLOT_link // Прикрепленные произвольные слова, не вписавшиеся в нормальные синтаксические отношения
           SECOND_VERB as SECOND_VERB_link // прикрепленный второй (смысловой) глагол в конструкциях с обратным порядком сказуемое-подлежащее
          }
		  
 enum net { cognate } // 02.05.2019 связь для однокоренных слов
 		  
}
