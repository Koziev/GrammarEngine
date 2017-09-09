// -----------------------------------------------------------------------------
// File RUS_NOUNS_2026.SOL
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
// LC->02.10.2012
// --------------

#include "sg_defs.h"

automat sg
{
 #define FemaleName(x) \
  #begin
  entry x : СУЩЕСТВИТЕЛЬНОЕ
  { 
   РОД:ЖЕН
   ПЕРЕЧИСЛИМОСТЬ:НЕТ
   ОДУШ:ОДУШ
   CharCasing:FirstCapitalized
   paradigm Сущ_2026
  }
  
  link СУЩЕСТВИТЕЛЬНОЕ:x{ ОДУШ:ОДУШ } <в_класс> СУЩЕСТВИТЕЛЬНОЕ:ИМЯ {}
  #end 

 #define заглавн(Сущ) tag СУЩЕСТВИТЕЛЬНОЕ:Сущ { CharCasing:FirstCapitalized }

 entry ЛЕДИ : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:ОДУШ
  paradigm Сущ_2026
 }




 entry ЭВМ : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:НЕОДУШ
  CharCasing:Upper
  paradigm Сущ_2026
 }

 entry МАДАМ : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:ОДУШ
  paradigm Сущ_2026
 }

 entry МАДМУАЗЕЛЬ : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:ОДУШ
  paradigm Сущ_2026
 }

 entry МАДЕМУАЗЕЛЬ : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:ОДУШ
  paradigm Сущ_2026
 }

 entry МИСС : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:ОДУШ
  paradigm Сущ_2026
 }

 entry МИССИС : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:ОДУШ
  paradigm Сущ_2026
 }

 entry ЛВС : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:ОДУШ
  CharCasing:Upper
  paradigm Сущ_2026
 }

 entry ПАНИ : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:ОДУШ
  paradigm Сущ_2026
 }
 
 entry маман : СУЩЕСТВИТЕЛЬНОЕ
 {
  РОД:ЖЕН
  ПЕРЕЧИСЛИМОСТЬ:нет
  ОДУШ:ОДУШ
  paradigm Сущ_2026
 }
 
 
 FemaleName(ЭЛЕН)
 FemaleName(БЕТТИ)
 FemaleName(ЛЮСИ)
 FemaleName(МЕРИ)
 FemaleName(МЭРИ)
 FemaleName(ЛОРИ)
 FemaleName(ЭНН)
 FemaleName(ПЕГГИ)
 FemaleName(ХЕЛЕН)
 FemaleName(НЭНСИ)
 FemaleName(КАТРИН)
 FemaleName(МОЛЛИ)
 FemaleName(КЭТИ)
 FemaleName(МЭЛЛОРИ)
 FemaleName(ДОРОТИ)
 FemaleName(ПЕРРИ)
 FemaleName(СЬЮЗЕН)
 FemaleName(КОННИ)
 FemaleName(МАДЖ)
 FemaleName(КАРЕН)
 FemaleName(ГРЕТХЕН)
 FemaleName(ЭТЕЛЬ)
 FemaleName(БЕККИ)
 FemaleName(ХОЛЛИ)
 FemaleName(РОУЗ)
 FemaleName(ДЖУДИ)
 FemaleName(АЙРИН)
 FemaleName(РОЗИ)
 FemaleName(ЭМИЛИ)
 FemaleName(ЭСТЕР)
 FemaleName(РЕЙЧЕЛ)
 FemaleName(ЛИЛИТ)
 FemaleName(ДЖИНН)
 FemaleName(ТАИС)
 FemaleName(АННИ)
 FemaleName(СЭНДИ)
 FemaleName(МАДЛЕН)
 FemaleName(СЬЮ)
 FemaleName(ДОЛЛИ)
 FemaleName(ДЖОРИАН)
 FemaleName(НАТАЛИ)
 FemaleName(ЖЮЛИ)
 FemaleName(ЛЮСИЛЬ)
 FemaleName(РУТ)
 FemaleName(ЭЛЛИ)
 FemaleName(САЛЛИ)
 FemaleName(ТРЕЙСИ)
 FemaleName(НИКОЛЬ)
 FemaleName(ГВЕН)
 FemaleName(МАРИКО)
 FemaleName(ПИППИ)
 FemaleName(МЭМ)
 FemaleName(ЭЙРИС)
 FemaleName(НУРИ)
 FemaleName(АНДРЕА)
 FemaleName(ДЖИЛЛ)
 FemaleName(КЕЛЛИ)
 FemaleName(ИРЭН)
 FemaleName(КЛЭР)
 FemaleName(РЭЧЕЛ)
 FemaleName(ТРИЛЛИАН)
 FemaleName(КАРМЕН)
 FemaleName(ЖАНЕТ)
 FemaleName(СЮЗАН)
 FemaleName(ЛИЛИАН)
 FemaleName(ЖАКЛИН)
 FemaleName(айрис)
 FemaleName( КЭТ )
 FemaleName( аннабель )
 FemaleName( бонни )
 FemaleName( бриджит )
 FemaleName( вивиан )
 FemaleName( дебби )
 FemaleName( дезире )
 FemaleName( дженет )
 FemaleName( джил )
 FemaleName( джудит )
 FemaleName( джейн )
 FemaleName( долорес )
 FemaleName( ирен )
 FemaleName( иштар )
 FemaleName( китти )
 FemaleName( кортни )
 FemaleName( кэролайн )
 FemaleName( кэтти )
 FemaleName( линдсей )
 FemaleName( лоис )
 FemaleName( макбет )
 FemaleName( мардж )
 FemaleName( мариам )
 FemaleName( мередит )
 FemaleName( митчелл )
 FemaleName( мэган )
 FemaleName( наоми )
 FemaleName( никки )
 FemaleName( нинель )
 FemaleName( санди )
 FemaleName( скалли )
 FemaleName( сьюзи )
 FemaleName( сюзи )
 FemaleName( уитни )
 FemaleName( хиллари )
 FemaleName( шарон )
 FemaleName( шерил )
 FemaleName( элейн )
 FemaleName( элеонор )
 FemaleName( элин )
 FemaleName( эммануэль )
 FemaleName( стейси )
 FemaleName( джулиет )
 FemaleName( джинджер )
 FemaleName( беатрикс )
 FemaleName( беатрис )
 FemaleName( АННАБЕЛ )
 FemaleName( КРИСТИН )
 FemaleName( ЭВЕЛИН )
 FemaleName( ДЖИЛЛИАН )
 FemaleName( МЕЛАНИ )
 FemaleName( ДЖЕЙНИ )
 FemaleName( СИНДИ )
 FemaleName( ДЖЕНИС )
 FemaleName( ГЛЭДИС )
 FemaleName( ХИЛАРИ )
 FemaleName( ШЕЙЛ )
 FemaleName( ЛИНН )
 FemaleName( МЭНДИ )
 FemaleName( ЭДИТ )
 FemaleName( КЛЕО )
 FemaleName( КЭССИ )
 FemaleName( ИЛЭЙН )
 FemaleName( ЭЛИНОР )
 FemaleName( ДЖЕСС )
 FemaleName( ДЕЙЗИ )
 FemaleName( ЛИЗЗИ )
 FemaleName( КРИСТАБЕЛЬ )
 FemaleName( СИДНИ )
 FemaleName( ФЕЛИСИТИ )
 FemaleName( КЭРИ )
 FemaleName( КЕНДИ )
 FemaleName( АНН )
 FemaleName( ЭЛИЗ )
 FemaleName( ЛИЛЛИ )
 FemaleName( ДОРИС )
 FemaleName( МЭРИАН )
 FemaleName( АМЕЛИ )
 FemaleName( МЭРИЛИН )
 FemaleName( ДЖЕССИ )
 FemaleName( ЛИЗ )
 FemaleName( МЕГАН )
 FemaleName( ЭББИ )
 FemaleName( НАЙНИВ )
 FemaleName( ЭГВЕЙН )
 FemaleName( МЭЙ )
 FemaleName( ГРЕЙС )
 FemaleName( МОРЕЙН )
 FemaleName( ДЖИННИ )
 FemaleName( Кэрол )
 FemaleName( Эви )
 FemaleName( Коко )
 FemaleName( Гвинет )
 FemaleName( Одри )
 FemaleName( Харриет )
 FemaleName( Кристи )
 FemaleName( Флоренс )
 FemaleName( Эшли )
 FemaleName( астрид )
 FemaleName( агнес )
 FemaleName( бриджет )
 FemaleName( бриттани )
 FemaleName( дженнет )
 FemaleName( джилиан )
 FemaleName( джилли )
 FemaleName( джоанн )
 FemaleName( джоселин )
 FemaleName( джослин )
 FemaleName( джульет )
 FemaleName( жаннет )
 FemaleName( жюстин )
 FemaleName( кетрин )
 FemaleName( леонор )
 FemaleName( марджи )
 FemaleName( марджори )
 FemaleName( мейбл )
 FemaleName( мерри )
 FemaleName( митчел )
 FemaleName( модести )
 FemaleName( мэдди )
 FemaleName( мэделин )
 FemaleName( мэйбл )
 FemaleName( рапунцель )
 FemaleName( речел )
 FemaleName( сесиль )
 FemaleName( сибил )
 FemaleName( скарлетт )
 FemaleName( сэлли )
 FemaleName( фиби )
 FemaleName( элеанор )
 FemaleName( ясмин )
 FemaleName( беренис )
 FemaleName( валери )
 FemaleName( франсис )
 FemaleName( энджел )
 FemaleName( эллис )
 FemaleName( гвендолин )
 FemaleName( керолайн )
 
/* 
 FemaleName(  )
 FemaleName(  )
 FemaleName(  )
 FemaleName(  )
*/ 
}
