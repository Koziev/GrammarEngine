// -----------------------------------------------------------------------------
// File SG_RUS_MAIN.SOL
//
// (c) Koziev Elijah
//
// Content:
// Лексикон - определения классов, координат для русского раздела Словаря.
// Russian language lexicon: classes declarations. File encoding must be utf-8.
//
// 26.11.2007 - добавил генерацию констант PERFECT_ru и IMPERFECT_ru для вида
//              глаголов.
// 29.08.2008 - добавлены координаты ПРИЧАСТИЕ и СТРАД для причастий
// 11.12.2008 - добавлен атрибут падежной валентности для глаголов и инфинитивов
// 17.12.2008 - добавлен тэг КВАЗИМОДАЛЬНЫЙ для глаголов
// 30.12.2008 - переделано определение коодинаты ПЕРЕХОДНОСТЬ
// 03.01.2009 - переделана парадигма наречия: обычная и сравнительная степени
//              теперь можно собирать в одной статьи (БЫСТРО-БЫСТРЕЕ) 
// 10.04.2009 - для существительных добавлен тэг Aa - имена собственные, фамилии
//              и прочее, начинающееся с заглавной буквы 
// 08.06.2009 - в парадигму безличных глаголов добавлен тег модальности,
//              чтобы учитывать комбинации типа НАДО ПОЕСТЬ
// 21.06.2011 - добавлены теги для семантики глагола СГД_Время и СГД_Направление
// 02.08.2011 - для безличного глагола добавлен признак language=Russian
// 19.12.2012 - добавлен класс ПОСЛЕЛОГ для слов СПУСТЯ, ВСЛЕД, НАВСТРЕЧУ,
//              НАПЕРЕРЕЗ.
// 29.12.2012 - добавлена координата СЕМАНТИКА для категоризации наречий
// 17.12.2013 - добавлена координата ПАДЕЖВАЛ для существительных
// 25.01.2015 - для части речи ЧАСТИЦА добавлен тэг ТИП_ЧАСТИЦЫ для пометки префиксов (НЕ,НИ)
//              и постфиксов (ЛИ,ЖЕ,...)
// 23.10.2015 - добавлена часть речи ПРЕФИКС_СОСТАВ_ПРИЛ
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->07.01.2017
// --------------

#include "sg_defs.h"

automat sg
{
 enum ЛИЦО as PERSON_ru {
                         1 as PERSON_1_ru
                         2 as PERSON_2_ru
                         3 as PERSON_3_ru
                        }

 enum ЧИСЛО as NUMBER_ru {
                                 ЕД as SINGULAR_NUMBER_ru
                                 МН as PLURAL_NUMBER_ru
                                }

 enum РОД as GENDER_ru {
                                 МУЖ as MASCULINE_GENDER_ru
                                 ЖЕН as FEMININE_GENDER_ru
                                 СР  as NEUTRAL_GENDER_ru
                                }

 enum ПЕРЕХОДНОСТЬ as TRANSITIVENESS_ru
 {
  НЕПЕРЕХОДНЫЙ as NONTRANSITIVE_VERB_ru
  ПЕРЕХОДНЫЙ as TRANSITIVE_VERB_ru
 } 

 enum ПРИЧАСТИЕ as PARTICIPLE_ru // тэг для прилагательных, которые являются причастиями
 enum СТРАД as PASSIVE_PARTICIPLE_ru // тэг для страдательных причастий (прилагательных)

 enum ВИД          as ASPECT_ru { СОВЕРШ as PERFECT_ru НЕСОВЕРШ as IMPERFECT_ru }
 enum ВОЗВРАТНОСТЬ
 enum НАКЛОНЕНИЕ as VERB_FORM_ru { ИЗЪЯВ as VB_INF_ru ПОБУД as VB_ORDER_ru }

 enum ВРЕМЯ        as TENSE_ru {
                                ПРОШЕДШЕЕ as PAST_ru
                                НАСТОЯЩЕЕ as PRESENT_ru
                                БУДУЩЕЕ   as FUTURE_ru
                               }

 enum КРАТКИЙ as SHORTNESS_ru

 enum НЕГАТИВ

 enum ПАДЕЖ        as CASE_ru {
                               { ИМ ЗВАТ as VOCATIVE_CASE_ru }           as NOMINATIVE_CASE_ru
                               { РОД ПАРТ as PARTITIVE_CASE_ru СЧЕТН }   as GENITIVE_CASE_ru
                               ТВОР                                   as INSTRUMENTAL_CASE_ru
                               ВИН                                    as ACCUSATIVE_CASE_ru 
                               ДАТ                                    as DATIVE_CASE_ru
                               { ПРЕДЛ ОТЛОЖ МЕСТ as LOCATIVE_CASE_ru }  as PREPOSITIVE_CASE_ru
                              }
                              
 enum ОДУШ         as FORM_ru {
                               ОДУШ    as ANIMATIVE_FORM_ru
                               НЕОДУШ  as INANIMATIVE_FORM_ru
                              }
                              
 enum ПЕРЕЧИСЛИМОСТЬ as COUNTABILITY_ru { ДА as COUNTABLE_ru  НЕТ as UNCOUNTABLE_ru }

 // Форма прилагательного, включая компаратив и суперлатив.
 enum СТЕПЕНЬ as COMPAR_FORM_ru {
                                 АТРИБ    as ATTRIBUTIVE_FORM_ru // спокойный
                                 СРАВН    as COMPARATIVE_FORM_ru // спокойнее
                                 ПРЕВОСХ  as SUPERLATIVE_FORM_ru // спокойнейший
                                 КОМПАРАТИВ2 as LIGHT_COMPAR_FORM_RU // поспокойнее
                                 СОКРАЩ as ABBREV_FORM_ru // "др."
                                }

 // Для работы с падежной валентностью в причастиях, у которых уже есть падеж
 enum ПадежВал as CASE_GERUND_ru = ПАДЕЖ

 // Признак (для инфинитивов и глаголов), что допускаются
 // конструкции типа 'РАЗРЕШИТЬ СПАТЬ'
 enum МОДАЛЬНЫЙ as MODAL_ru


 enum СГД_Время as VERBMODE_TENSE {
                 Начать // заиграть, запеть
                 Закончить // доиграть, дойти или доигрывать, дослуживать
                 Незакончить // недоделать, недоделывать
                 Немного // поиграть, попеть, отпить
                 Однократно // стукнуть, толкнуть, спросить
                 НеогрДолго // читать, спать
                 Заново // переигрывать, переиграть, переписывать
                 Полностью // пропылесосить, выпить
                }

 enum СГД_Направление as VERBMODE_DIRECTION
 {
  Наружу // выезжать, отъезжать
  Внутрь // влетать, влететь
 }

/*
 enum Глаг_Предл_Вал as VERB_PREP_VALENCY
 {
//  Гл_В_Предл
  Гл_В_Вин
//  Гл_НА_Предл
  Гл_НА_Вин
  Гл_С_Твор
  Гл_С_Род
  Гл_ОБ_предл
  Гл_ОБ_вин
  Гл_О_Вин
  Гл_О_предл
  Глаг_ПО_Вин
  Гл_К_Дат
  Гл_ДЛЯ_Род
 }
*/


 enum КАТЕГОРИЯ_ЧИСЛ as NUMERAL_CATEGORY
 {
  КОЛИЧ as CARDINAL // один, два, три
  СОБИР as COLLECTION // двое, трое
 }


 // обстоятельственные валентности
 enum ОБСТ_ВАЛ as ADV_SEMANTICS
 {
  МЕСТО              as S_LOCATION // тут
  НАПРАВЛЕНИЕ        as S_DIRECTION // туда
  НАПРАВЛЕНИЕ_ОТКУДА as S_DIRECTION_FROM // оттуда
  КОНЕЧНАЯ_ТОЧКА     as S_FINAL_POINT // докуда
  РАССТОЯНИЕ         as S_DISTANCE // рядом
  СКОРОСТЬ           as S_VELOCITY // быстро
  МОМЕНТ_ВРЕМЕНИ     as S_MOMENT // сейчас
  ДЛИТЕЛЬНОСТЬ       as S_DURATION // долго
  КРАТНОСТЬ          as S_TIME_DIVISIBILITY // многократно
  СОПОСТАВЛЕНИЕ      as S_ANALOG // по-английски
  МНОЖИТЕЛЬ          as S_FACTOR // вдвое, втрое
 }


 enum ТИП_ПРИЛ as ADJ_TYPE
 {
  ПРИТЯЖ as ADJ_POSSESSIVE // мой
  ПОРЯДК as ADJ_ORDINAL // первый, второй, ... двадцатый
 }

 enum ТИП_ПРЕДИКАТИВ
 {
  АВТОНОМ // хотелось ...
  БЫЛО_СВЯЗКА // жаль - было жаль ...
  БЫТЬ_СВЯЗКА // он был в состоянии ...
 }

 enum ТИП_МЕСТОИМЕНИЯ as PRONOUN_TYPE_ru
 {
  АВТОНОМ
  ПРЕДЛОЖН // ним, ней
 }

 
 enum ТИП_ГЛАГОЛА as VERB_TYPE_ru
 {
  СТАТИЧ
  ДВИЖ
  СВЯЗОЧН as COPULA_VERB_ru // Этим тегом пометим связочные глаголы типа СТАТЬ
 }
 
 // ------------------------------------------------------------------------

 // *******************************************************

 class СУЩЕСТВИТЕЛЬНОЕ as NOUN_ru
 {
  language Russian
  value=10  
  
  tags
  {
   МОДАЛЬНЫЙ   // модальность - для слов, могущий принимать участие в сочетаниях типа "желание учиться" или "возможность получить"
   CharCasing  // Слова, начинающиеся с заглавной буквы или целиком в верхнем регистре
   ПАДЕЖВАЛ    // Для пометки существительных, которые управляют объектом в дательном или творительном
               // падеже, например "управление машиной".
   OMONYM_RESOLUTION
  }

  attributes
  {
   ПЕРЕЧИСЛИМОСТЬ
   ОДУШ
   РОД
  }

  dimentions
  {
   ЧИСЛО
   ПАДЕЖ
  }
 }

 class МЕСТОИМ_СУЩ as PRONOUN2_ru
 {
  value=10
  closed

  language Russian  
  attributes { РОД   }
  dimentions { ПАДЕЖ }
 }

 class МЕСТОИМЕНИЕ as PRONOUN_ru
 {
  value=10
  closed

  dimentions { НЕГАТИВ }
  
  language Russian  
  dimentions
  {
   ЛИЦО
   ЧИСЛО
   РОД
   ПАДЕЖ
   ТИП_МЕСТОИМЕНИЯ
  }
 }


 class ПРИЛАГАТЕЛЬНОЕ as ADJ_ru
 {
  language Russian  
  value=10  

  tags
  {
   ПРИЧАСТИЕ
   СТРАД
   ПЕРЕХОДНОСТЬ
   ПадежВал // падежная валентность
   ВИД
   МОДАЛЬНЫЙ
   ВРЕМЯ
   ТИП_ПРИЛ
   OMONYM_RESOLUTION
   //Глаг_Предл_Вал
  }

  dimentions
  {
   РОД
   ЧИСЛО
   ПАДЕЖ
   ОДУШ
   СТЕПЕНЬ
   КРАТКИЙ
  }
 }



 class ЧИСЛИТЕЛЬНОЕ as NUMBER_CLASS_ru
 {
  language Russian  
  value=10  
  attributes
  {
   КАТЕГОРИЯ_ЧИСЛ
  }

  dimentions
  {
   РОД
   ЧИСЛО
   ПАДЕЖ
   ОДУШ
  }
 }



 class ИНФИНИТИВ as INFINITIVE_ru
 {
  language Russian  
  value=10  
  
  attributes
  {
   ВИД
   ВОЗВРАТНОСТЬ
  }

  tags
  {
   ПЕРЕХОДНОСТЬ
   ПАДЕЖ // падежная валентность
   МОДАЛЬНЫЙ
   ТИП_ГЛАГОЛА
   OMONYM_RESOLUTION
   //Глаг_Предл_Вал // предложная валентность
  }
 }



 class ГЛАГОЛ as VERB_ru
 {
  language Russian  
  value=10  

  attributes
  {
   ПЕРЕХОДНОСТЬ
   ПАДЕЖ=?
   //Глаг_Предл_Вал=?
   ВИД=НЕСОВЕРШ
   ВОЗВРАТНОСТЬ
   МОДАЛЬНЫЙ
  }

  tags
  {
   ТИП_ГЛАГОЛА
   OMONYM_RESOLUTION
  }


  import
  {
   ПЕРЕХОДНОСТЬ from ИНФИНИТИВ{ ВИД aux stress }
   ПАДЕЖ from ИНФИНИТИВ{ ВИД aux stress }
   ВИД from ИНФИНИТИВ{ ВИД aux stress }
   ВОЗВРАТНОСТЬ from ИНФИНИТИВ{ ВИД aux stress }
   МОДАЛЬНЫЙ from ИНФИНИТИВ{ ВИД aux stress }
   ТИП_ГЛАГОЛА from ИНФИНИТИВ{ ВИД aux stress }
   //OMONYM_RESOLUTION from ИНФИНИТИВ{ ВИД aux stress }
   //Глаг_Предл_Вал from ИНФИНИТИВ{ ВИД aux stress }
  }

  dimentions
  {
   ВРЕМЯ
   ЛИЦО
   РОД
   ЧИСЛО
   НАКЛОНЕНИЕ
  }
 }


 class ДЕЕПРИЧАСТИЕ as GERUND_2_ru
 {
  language Russian  
  value=10  

  attributes { ВИД }

  tags
  {
   ПЕРЕХОДНОСТЬ
   ПАДЕЖ // падежная валентность
   МОДАЛЬНЫЙ
   ТИП_ГЛАГОЛА
  }

/*
  import
  {
   ПЕРЕХОДНОСТЬ from ИНФИНИТИВ{ ВИД aux stress }
   ПАДЕЖ from ИНФИНИТИВ{ ВИД aux stress }
   ВИД from ИНФИНИТИВ{ ВИД aux stress }
   ВОЗВРАТНОСТЬ from ИНФИНИТИВ{ ВИД aux stress }
   МОДАЛЬНЫЙ from ИНФИНИТИВ{ ВИД aux stress }
   ТИП_ГЛАГОЛА from ИНФИНИТИВ{ ВИД aux stress }
  }
*/
 }

 class ПРЕДЛОГ as PREPOS_ru
 {
  language Russian  
  value=1
  closed
  attributes { ПАДЕЖ }
 }

 class БЕЗЛИЧ_ГЛАГОЛ as IMPERSONAL_VERB_ru
 {
  language Russian

  value=10
  closed

  attributes
  {
   ВИД
   ТИП_ПРЕДИКАТИВ   
  }

  tags
  {
   МОДАЛЬНЫЙ
   ПЕРЕХОДНОСТЬ
   ПАДЕЖ // падежная валентность
  }

  dimentions
  {
   ВРЕМЯ
  }
 }
 
 
 class ВОСКЛ_ГЛАГОЛ  // типа СТОП!  БРЫСЬ!
 {
  value=1
  closed
 }

 class СПЕЦ
 {
  closed
 }
 
 enum ТИП_ЧАСТИЦЫ as PARTICLE_TYPE
 {
  ПРЕФИКС as PREFIX_PARTICLE
  ПОСТФИКС as POSTFIX_PARTICLE
 }

 class ЧАСТИЦА    as PARTICLE_ru
 {
  language Russian
  value=1
  closed
  tags
  {
   ТИП_ЧАСТИЦЫ
  }
 } 
 
 class СОЮЗ       as CONJ_ru
 {
  language Russian
  value=1
  closed
 } 

 // Какие части речи может модифицировать наречие
 enum ТИП_МОДИФ as ADV_MODIF_TYPE
 {
  НАРЕЧ // наречия: ОЧЕНЬ БЫСТРО
  НАРЕЧ0 // атрибут модификатора наречия: УЖЕ ОЧЕНЬ БЫСТРО
  ПРИЛ  // прилагательные: ОЧЕНЬ БЫСТРЫЙ
  ГЛАГ  // глаголы: БЫСТРО БЕЖАТЬ
  СУЩ   // счетные для существительных в родительном падеже: МНОГО ЯБЛОК
  СУЩ2  // усилительные для существительных/местоимение в любом падеже: ТОЛЬКО ТЫ
  ПРЕДЛ // предлоги: ПРЯМО В ЯБЛОЧКО
 }

 class НАРЕЧИЕ    as ADVERB_ru
 {
  language Russian
  value=3

  dimentions
  {
   СТЕПЕНЬ
  }

  tags
  {
   ОБСТ_ВАЛ
   ТИП_МОДИФ
  }
 }  

 class ПУНКТУАТОР as PUNCTUATION_class
 {
  language Russian
  value=1
  closed
 } 
 
 class МОДАЛЬНОЕ
 {
  language Russian
  value=0
 } 

 class ВВОДНОЕ
 {
  language Russian
  value=0
  closed
 } 


 // метастатьи - инфинитив и производные от него, отглагольные части речи - глагол,
 // причастия, деепричастие.
 class rus_verbs
 {
  language Russian
 }

 // Для метастатей, объединяющих уменьшительные, нейтральные и увеличительные формы существительных
 class rus_nouns
 {
  language Russian
 }

 class ПОСЛЕЛОГ as POSTPOS_ru
 {
  language Russian  
  value=1  
  attributes { ПАДЕЖ }
  closed
 }

 // Слова: ее ее их
 class ПРИТЯЖ_ЧАСТИЦА as POSESS_PARTICLE
 {
  language Russian  
  closed
 }

 // Максимальная скорость движения транспорта составит 80 км/ч.
 //                                                       ^^^^
 class ЕДИНИЦА_ИЗМЕРЕНИЯ as MEASURE_UNIT
 {
  language Russian  
  closed
 }


 // Префиксы составных прилагательных:
 // индо-европейские языки
 // ^^^^
 class ПРЕФИКС_СОСТАВ_ПРИЛ as COMPOUND_ADJ_PREFIX
 {
  language Russian
 }


 // Префиксы составных существительных
 // "эти квази-обезьяны в белых халатах побегут к нам с бананами в руках"
 //      ^^^^^
 class ПРЕФИКС_СОСТАВ_СУЩ as COMPOUND_NOUN_PREFIX
 {
  language Russian
 }

}
