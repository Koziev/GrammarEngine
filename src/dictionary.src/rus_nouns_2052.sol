// -----------------------------------------------------------------------------
// File RUS_NOUNS_2052.SOL
//
// (c) Koziev Elijah
//
// Лексикон - определения имен существительных для русского языка.
//
// Русские существительные http://www.solarix.ru/for_developers/api/russian-noun-declension.shtml
// Особенности описания существительных http://www.solarix.ru/russian_grammar_dictionary/russian-noun-declension.shtml
// Словарные статьи http://www.solarix.ru/for_developers/docs/entries.shtml#words
//
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->08.10.2011
// --------------

#include "sg_defs.h"

automat sg
{
 #define заглавн(Сущ) tag СУЩЕСТВИТЕЛЬНОЕ:Сущ { CharCasing:FirstCapitalized }

 #define имя(x) entry x : СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 
 #define n2053(x) entry x : СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 }

 n2053( хвастунья )
 n2053( сватья )
 n2053( петуния )
 n2053( лгунья )
 n2053( пердунья )
 n2053( врунья )
 n2053( прыгунья )
 n2053( горбунья )
 n2053( потаскунья )
 n2053( резвунья )
 n2053( хавронья )
 n2053( бегунья )
 n2053( шалунья )
 n2053( собаченция )
 n2053( бабенция )
 n2053( бабуленция )

 entry Авдотья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Агафья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Агния: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Азалия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Аксинья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Амалия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Анастасия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Анисья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Аполлинария: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Апраксия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Валерия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Виктория: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Виргиния: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Виталия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Гликерия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Гортензия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Дарья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Денисия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Евгения: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Евдокия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Евдоксия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Евлалия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Евлампия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Евпраксия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Евстолия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Евфимия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Евфросиния: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Епистимия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Ефимия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Ефросиния: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Ефросинья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Зиновия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Ия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Калерия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Клавдия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Конкордия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Констанция: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Корнелия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Ксения: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Леокадия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Лидия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Лилия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Лия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Лукерья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Лукреция: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Малания: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Маланья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Мария: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Марья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Мелания: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Настасия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Настасья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Наталия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Наталья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Оливия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Олимпия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Поликсения: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Прасковья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Пульхерия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Розалия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Сильвия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Соломония: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry София: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Стефания: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Таисия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Таисья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Устиния: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Устинья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Феврония: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Февронья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Федосия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Федосья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Федотия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Федотья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Фелиция: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Феодосия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Феодотия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Феофания: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Фетиния: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Фетинья: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2053 CharCasing:FirstCapitalized }
 entry Хаврония: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Цецилия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Эмилия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Юлиания: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Юлия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry Джулия: СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }
 entry офелия : СУЩЕСТВИТЕЛЬНОЕ { paradigm Сущ_2052 CharCasing:FirstCapitalized }

 
 имя( СИНТИЯ )
 имя( Лавиния )
 имя( ДЕЛИЯ )
 имя( КЛОДИЯ )
 имя( ОНОРИЯ )
 имя( Амелия )
 
/* 
 имя(  )
 имя(  )
 имя(  )
 имя(  )
 имя(  )
 имя(  )
*/ 
}
