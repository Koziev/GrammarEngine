﻿// -----------------------------------------------------------------------------
// File RUS_VERBS_7084.SOL
//
// (c) Koziev Elijah
//
// Content:
// Лексикон - определения глаголов со спряжением по типу РАССЛАБИТЬСЯ
// Особенности описания глаголов и инфинитивов http://www.solarix.ru/russian_grammar_dictionary/russian-verbs.shtml
// Спряжение русских глаголов http://www.solarix.ru/for_developers/api/russian-verb-conjugation.shtml
// Словарные статьи http://www.solarix.ru/for_developers/docs/entries.shtml#words
//
// -----------------------------------------------------------------------------
//
// CD->13.09.2017
// LC->15.04.2018
// --------------

#include "sg_defs.h"

automat sg
{
 // ********************************************************************
 // Чтобы проще создавать статьи сразу с грамматической сетью - связью
 // от предиката к инфинитиву.
 // ********************************************************************
 #define v7084( Name ) \
  #begin
   extern entry Name : ИНФИНИТИВ
   entry Name : ГЛАГОЛ
   {
    paradigm Глагол_7084
    <в_инфинитив>ИНФИНИТИВ:Name{}
   }
  #end

 v7084( ПОКОСОБОЧИТЬСЯ )
 v7084( ВЗБЫЧИТЬСЯ )
 v7084( ВОЧЕЛОВЕЧИТЬСЯ )
 v7084( НАМОРОЧИТЬСЯ )
 v7084( ОБЕСКОЛПАЧИТЬСЯ )
 v7084( ОБМУЖИЧИТЬСЯ )
 v7084( ОБОЛЬШЕВИЧИТЬСЯ )
 v7084( ОБУЗБЕЧИТЬСЯ )
 v7084( ОЗЕМЛЯЧИТЬСЯ )
 v7084( ОКАТОЛИЧИТЬСЯ )
 v7084( ОМОРЯЧИТЬСЯ )
 v7084( ОМУЖИЧИТЬСЯ )
 v7084( ОСОБАЧИТЬСЯ )
 v7084( ОТСРОЧИТЬСЯ )
 v7084( ОТШАШЛЫЧИТЬСЯ )
 v7084( ОХОХЛЯЧИТЬСЯ )
 v7084( ПЕРЕКАЛЕЧИТЬСЯ )
 v7084( ПЕРЕКОСОБОЧИТЬСЯ )
 v7084( ПЕРЕРЕБЯЧИТЬСЯ )
 v7084( ПЕРЕСОБАЧИТЬСЯ )
 v7084( ПОБЫЧИТЬСЯ )
 v7084( ПОДЕВИЧИТЬСЯ )
 v7084( ПОИЗРЕБЯЧИТЬСЯ )
 v7084( ПОПУЧИТЬСЯ )
 v7084( ПОРАСПУЧИТЬСЯ )
 v7084( ПОРЕБЯЧИТЬСЯ )
 v7084( ПОРЫБАЧИТЬСЯ )
 v7084( ПОСОБАЧИТЬСЯ )
 v7084( ПОФЕЙСБУЧИТЬСЯ )
 v7084( ПРИАТТАЧИТЬСЯ )
 v7084( ПРИГЛЮЧИТЬСЯ )
 v7084( ПРИКОРЯЧИТЬСЯ )
 v7084( ПРОПАТЧИТЬСЯ )
 v7084( ПРОПЕСОЧИТЬСЯ )
 v7084( ПРОСОБАЧИТЬСЯ )
 v7084( ПРОСРОЧИТЬСЯ )
 v7084( РАЗМАЯЧИТЬСЯ )
 v7084( РАЗХЕРАЧИТЬСЯ )
 v7084( РАССОБАЧИТЬСЯ )
 v7084( РАССУРГУЧИТЬСЯ )
 v7084( РАСЧЕЛОВЕЧИТЬСЯ )
 v7084( РАСЧУДАЧИТЬСЯ )
 v7084( САМООБЕСПЕЧИТЬСЯ )
 v7084( САМООГРАНИЧИТЬСЯ )
 v7084( СКОНТАЧИТЬСЯ )
 v7084( УЧЕЛОВЕЧИТЬСЯ )
 v7084( НАХОМЯЧИТЬСЯ )
 v7084( НАШАШЛЫЧИТЬСЯ )
 v7084( ОБЕЗЗВУЧИТЬСЯ )
 v7084( ОБЕСКУРАЖИТЬСЯ )
 v7084( ОКИРПИЧИТЬСЯ )
 v7084( ОСВИНЯЧИТЬСЯ )
 v7084( ПЕРЕКОРЕЖИТЬСЯ )
 v7084( ПОПЫЖИТЬСЯ )
 v7084( ЗАСУТОЛОЧИТЬСЯ )

 v7084( выдрючиться )
 v7084( выкаблучиться )
 v7084( выкарячиться )
 v7084( додурачиться )
 v7084( дозабиячиться )
 v7084( докучиться )
 v7084( доребячиться )
 v7084( дособачиться )
 v7084( заблочиться )
 v7084( заначиться )
 v7084( заребячиться )
 v7084( засвинячиться )
 v7084( издурачиться )
 v7084( изребячиться )
 v7084( иссобачиться )
 v7084( исчудачиться )
 v7084( набатрачиться )
 v7084( назабиячиться )
 v7084( накорячиться )
 v7084( намастачиться )
 v7084( намужичиться )
 v7084( наребячиться )
 v7084( обесчеловечиться )
 v7084( обнемечиться )
 v7084( обрусачиться )
 v7084( обточиться )
 v7084( овосточиться )
 v7084( одурачиться )
 v7084( околпачиться )
 v7084( отребячиться )
 v7084( отюречиться )
 v7084( почудачиться )
 v7084( приконтачиться )
 v7084( присобачиться )
 v7084( продурачиться )
 v7084( прополячиться )
 v7084( разребячиться )
 v7084( расканючиться )
 v7084( раскулачиться )
 v7084( рассучиться )
 v7084( самовозвеличиться )
 v7084( самоназначиться )
 v7084( самораскулачиться )

}

