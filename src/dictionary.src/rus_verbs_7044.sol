﻿// -----------------------------------------------------------------------------
// File RUS_VERBS_7044.SOL
//
// (c) Koziev Elijah
//
// Content:
// Лексикон - определения предикатов, причастий и прочая (глаголов) для Словаря.
// Особенности описания глаголов и инфинитивов http://www.solarix.ru/russian_grammar_dictionary/russian-verbs.shtml
// Спряжение русских глаголов http://www.solarix.ru/for_developers/api/russian-verb-conjugation.shtml
// Словарные статьи http://www.solarix.ru/for_developers/docs/entries.shtml#words
//
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->15.04.2018
// --------------

#include "sg_defs.h"

automat sg
{
 // ********************************************************************
 // Чтобы проще создавать статьи сразу с грамматической сетью - связью
 // от предиката к инфинитиву.
 // ********************************************************************
 #define v7044( Name ) \
  #begin
   extern entry Name : ИНФИНИТИВ
   entry Name : ГЛАГОЛ
   {
    paradigm Глагол_7044
    <в_инфинитив>ИНФИНИТИВ:Name{}
   }
  #end

 v7044( СМИРиться )
 v7044( ПРИМИРиться )
 v7044( ПОКОРиться )
 v7044( УДОВЛЕТВОРиться )
 v7044( РАСТВОРиться )
 v7044( ПРОВЕТРиться )
 v7044( СВАРИТЬСЯ )
 v7044( ВЫГОВОРИТЬСЯ )
 v7044( ИСХИТРИТЬСЯ )
 v7044( ОТГОВОРИТЬСЯ )
 v7044( ПОСМОТРеТЬСЯ )
 v7044( ЗАТВОРИТЬСЯ )
 v7044( ВСМОТРеТЬСЯ )
 v7044( ЗАСМОТРеТЬСЯ )
 v7044( УГОВОРИТЬСЯ )
 v7044( НАКУРИТЬСЯ )
 v7044( ОБКУРИТЬСЯ )
 v7044( ЗАГОВОРИТЬСЯ )
 v7044( РАСЩЕДРИТЬСЯ )
 v7044( ОЗАРИТЬСЯ )
 v7044( УМОРИТЬСЯ )
 v7044( ИЗНУРИТЬСЯ )
 v7044( ОТДАРИТЬСЯ )
 v7044( ВОДВОРИТЬСЯ )
 v7044( ПОДБОДРИТЬСЯ )
 v7044( НАВОСТРИТЬСЯ )
 v7044( ПООСМОТРеТЬСЯ )
 v7044( ОБВАРИТЬСЯ )
 v7044( ОХМУРИТЬСЯ )
 v7044( ОБОДРИТЬСЯ )
 v7044( НАПУДРИТЬСЯ )
 v7044( ПОПУДРИТЬСЯ )
 v7044( УКУПОРИТЬСЯ )
 v7044( ЗАТИХАРИТЬСЯ )
 v7044( ПОМАТЕРИТЬСЯ )
 v7044( ВЫМАТЕРИТЬСЯ )
 v7044( НАПУЗЫРИТЬСЯ )
 v7044( ВЫЯСНИТЬСЯ )
 v7044( ПРИТВОРИТЬСЯ )
 v7044( СВАЛИТЬСЯ )
 v7044( РАСПРОСТРАНИТЬСЯ )
 v7044( РАЗГОВОРИТЬСЯ )
 v7044( РАЗЪЯРИТЬСЯ )
 v7044( ВОЦАРИТЬСЯ )
 v7044( РАЗОРИТЬСЯ )
 v7044( УДАЛИТЬСЯ )
 v7044( УКОРЕНИТЬСЯ )
 v7044( УМУДРИТЬСЯ )
 v7044( УСОМНИТЬСЯ )
 v7044( ДОГОВОРИТЬСЯ )
 v7044( ЗАТРУДНИТЬСЯ )
 v7044( ИЗМЕНИТЬСЯ )
 v7044( НАГОВОРИТЬСЯ )
 v7044( НАКЛОНИТЬСЯ )
 v7044( ОТКЛОНИТЬСЯ )
 v7044( ПОВТОРИТЬСЯ )
 v7044( ПОКЛОНИТЬСЯ )
 v7044( ПРЕКЛОНИТЬСЯ )
 v7044( ПРИСОЕДИНИТЬСЯ )
 v7044( ПРОГОВОРИТЬСЯ )
 v7044( ПРОЯСНИТЬСЯ )
 v7044( РАЗЪЯСНИТЬСЯ )
 v7044( СГОВОРИТЬСЯ )
 v7044( СКЛОНИТЬСЯ )
 v7044( УКЛОНИТЬСЯ )
 v7044( УЯСНИТЬСЯ )
 v7044( НАКРЕНИТЬСЯ )
 v7044( ВЗБОДРИТЬСЯ )
 v7044( ВНЕДРИТЬСЯ )
 v7044( ВОЗГОРДИТЬСЯ )
 v7044( ВОЗРОДИТЬСЯ )
 v7044( ВСПОМНИТЬСЯ )
 v7044( ВЫПОЛНИТЬСЯ )
 v7044( ЗАПОЛОНИТЬСЯ )
 v7044( ЗАРОДИТЬСЯ )
 v7044( ЗАСТОПОРИТЬСЯ )
 v7044( НАПОЛНИТЬСЯ )
 v7044( ОБОСТРИТЬСЯ )
 v7044( ОБЪЕДИНИТЬСЯ )
 v7044( ОГОВОРИТЬСЯ )
 v7044( ОТДЕЛИТЬСЯ )
 v7044( ПЕРЕМЕНИТЬСЯ )
 v7044( ПЕРЕПОЛНИТЬСЯ )
 v7044( ПОДЧИНИТЬСЯ )
 v7044( ПОЖЕНИТЬСЯ )
 v7044( ПОПОЛНИТЬСЯ )
 v7044( ПОСТОРОНИТЬСЯ )
 v7044( ПРЕИСПОЛНИТЬСЯ )
 v7044( ПРИМЕНИТЬСЯ )
 v7044( ПРОВАЛИТЬСЯ )
 v7044( РАЗВАЛИТЬСЯ )
 v7044( СМЕНИТЬСЯ )
 v7044( СОБЛАЗНИТЬСЯ )
 v7044( СОЕДИНИТЬСЯ )
 v7044( УДЛИНИТЬСЯ )
 v7044( УМИЛИТЬСЯ )
 v7044( УСЛОЖНИТЬСЯ )
 v7044( УСТРАНИТЬСЯ )
 v7044( УХИТРИТЬСЯ )
 v7044( протыриться )
 v7044( отабориться )
 v7044( приговориться )
 v7044( передариться )
 v7044( одобриться )
 v7044( вбуриться )
 v7044( воскуриться )
 v7044( полуотвориться )
 v7044( сдобриться )
 v7044( закуклиться )
 v7044( причислиться )
 v7044( обнулиться )
 v7044( вызволиться )
 v7044( выхвалиться )
 v7044( самоисцелиться )
 v7044( провеселиться )
 v7044( уделиться )
 v7044( увеселиться )
 v7044( подзакалиться )
 v7044( разрулиться )
 v7044( переопределиться )
 v7044( подразделиться )
 v7044( вычислиться )
 v7044( застелиться )
 v7044( скруглиться )
 v7044( наделиться )
 v7044( подразвалиться )
 v7044( взрыхлиться )
 v7044( начислиться )
 v7044( самоопылиться )
 v7044( козлиться )
 v7044( высветлиться )
 v7044( полуразвалиться )
 v7044( полупровалиться )
 v7044( предохраниться )
 v7044( отъединиться )
 v7044( подмениться )
 v7044( самовоспламениться )
 v7044( самосохраниться )
 v7044( захорониться )
 v7044( сочиниться )
 v7044( усредниться )
 v7044( оброниться )
 v7044( поясниться )
 v7044( затениться )
 v7044( взаимодополниться )
 v7044( перевыполниться )
 v7044( вычлениться )
 v7044( доуточниться )
 v7044( недооцениться )
 
 v7044( ЗАМГЛИТЬСЯ )
 v7044( НАСТРОПАЛИТЬСЯ )
 v7044( ОЛИЦЕТВОРИТЬСЯ )
 v7044( ОТБЕЛИТЬСЯ )
 v7044( ОТМАТЕРИТЬСЯ )
 v7044( ОТРЕСПАУНИТЬСЯ )
 v7044( ОТТЕНИТЬСЯ )
 v7044( ПЕРЕОСМЫСЛИТЬСЯ )
 v7044( ПОДЗАСОРИТЬСЯ )
 v7044( ПОДНАВАЛИТЬСЯ )
 v7044( ПОДСТЕЛИТЬСЯ )
 v7044( ПОЗАВАЛИТЬСЯ )
 v7044( ПОИСПАРИТЬСЯ )
 v7044( ПОНАПЫЛИТЬСЯ )
 v7044( ПОНАСОРИТЬСЯ )
 v7044( ПОПАЛИТЬСЯ )
 v7044( ПОУДОБРИТЬСЯ )
 v7044( ПРИОТВЕРНУТЬСЯ )
 v7044( ПРОМАТЕРИТЬСЯ )
 v7044( ПРОСВЕТЛИТЬСЯ )
 v7044( ПРОСИНИТЬСЯ )
 v7044( РАЗВЕТРИТЬСЯ )
 v7044( РАЗДУПЛИТЬСЯ )
 v7044( РАЗМАХРИТЬСЯ )
 v7044( РАСПРУЖИНИТЬСЯ )
 v7044( РАСЩЕЛИТЬСЯ )
 v7044( ПОДОБОСРАТЬСЯ )
 v7044( ПОМАНИТЬСЯ )
 v7044( ПОНАЖРАТЬСЯ )
 v7044( ПРООРАТЬСЯ )
 v7044( РАЗОСРАТЬСЯ )
 v7044( РАСКРЫЛИТЬСЯ )
 
 v7044( дободриться )
 v7044( выдуриться )
 v7044( добуриться )
 v7044( добурлиться )
 v7044( довеселиться )
 v7044( додуриться )
 v7044( доостриться )
 v7044( дохандриться )
 v7044( дохвалиться )
 v7044( дохрабриться )
 v7044( дохулиться )
 v7044( захрабриться )
 v7044( защедриться )
 v7044( заяриться )
 v7044( изволдыриться )
 v7044( изголиться )
 v7044( измудриться )
 v7044( испузыриться )
 v7044( наблагодариться )
 v7044( набодриться )
 v7044( назубриться )
 v7044( намудриться )
 v7044( намямлиться )
 v7044( начифириться )
 v7044( нашевелиться )
 v7044( нашустриться )
 v7044( обматериться )
 v7044( объякориться )
 v7044( ополлитриться )
 v7044( осеребриться )
 v7044( отблагодариться )
 v7044( переговориться )
 v7044( передоговориться )
 v7044( перематериться )
 v7044( поискриться )
 v7044( покадриться )
 v7044( полураствориться )
 v7044( пообветриться )
 v7044( поопериться )
 v7044( попроветриться )
 v7044( поразговориться )
 v7044( поувариться )
 v7044( поудалиться )
 v7044( поукорениться )
 v7044( поумалиться )
 v7044( пофрайериться )
 v7044( почмориться )
 v7044( присестриться )
 v7044( прихрабриться )
 v7044( причиниться )
 v7044( приякориться )
 v7044( пробуриться )
 v7044( просахариться )
 v7044( самоудовлетвориться )
 v7044( удочериться )
 v7044( взвалиться )
 v7044( втулиться )
 v7044( выхохлиться )
 v7044( доделиться )
 v7044( додразниться )
 v7044( доопределиться )
 v7044( досверлиться )
 v7044( досемениться )
 v7044( дочислиться )
 v7044( заделиться )
 v7044( закислиться )
 v7044( закозлиться )
 v7044( замыслиться )
 v7044( запечатлиться )
 v7044( запулиться )
 v7044( захохлиться )
 v7044( зашалиться )
 v7044( изъюлиться )
 v7044( исчислиться )
 v7044( набурлиться )
 v7044( нагуглиться )
 v7044( нарулиться )
 v7044( насверлиться )
 v7044( осмыслиться )
 v7044( отдуплиться )
 v7044( отяжелиться )
 v7044( очиниться )
 v7044( отчлениться )
 v7044( переопылиться )
 v7044( подзапылиться )
 v7044( подкислиться )
 v7044( подмаслиться )
 v7044( подпалиться )
 v7044( полувывалиться )
 v7044( полунаклониться )
 v7044( полуперевалиться )
 v7044( полуприслониться )
 v7044( поутолиться )
 v7044( приумалиться )
 v7044( промолиться )
 v7044( разутеплиться )
 v7044( разуплотниться )
 v7044( самовыпилиться )
 v7044( самовытесниться )
 v7044( самозастрелиться )
 v7044( самоотделиться )
 v7044( самоудалиться )
 v7044( самоуясниться )
 v7044( возомниться )
 v7044( вызелениться )
 v7044( вырониться )
 v7044( забелениться )
 v7044( зачерниться )
 v7044( надразниться )
 v7044( назвониться )
 v7044( накобениться )
 v7044( налениться )
 v7044( настепениться )
 v7044( нацениться )
 v7044( обедниться )
 v7044( обтабуниться )
 v7044( огосударственниться )
 v7044( ополониться )
 v7044( открениться )
 v7044( отслониться )
 v7044( переувлажниться )
 v7044( полусклониться )
 v7044( поопомниться )
 v7044( расщениться )
 v7044( самовоссоединиться )
 v7044( самоизмениться )
 v7044( самоискорениться )
 v7044( самоупраздниться )
 v7044( стабуниться )
 
}
