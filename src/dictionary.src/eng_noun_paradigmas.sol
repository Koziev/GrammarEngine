// -----------------------------------------------------------------------------
// File ENG_NOUN_PARADIGMAS.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения существительных для английского раздела Словаря.
// 13.10.2015 - убраны притяжательные формы
// -----------------------------------------------------------------------------
//
// CD->19.02.2005
// LC->13.10.2015
// --------------

#include "sg_defs.h"

automat sg
{
 // FOX-FOXES
 paradigm Fox : ENG_NOUN for "(.+)X"
 {
  NUMBER { "" "%+ES" }
 }

 // DAY-DAYS
 paradigm Day : ENG_NOUN for "(.+)\\@vY"
 {
  NUMBER { "" "%+S" }
 }


 // COPY-COPIES
 paradigm Copy : ENG_NOUN for "(.+)Y"
 {
  NUMBER { "" "%-1%+IES" }
 }


 // PASS-PASSES
 // BUZZ-BUZZES
 paradigm Pass : ENG_NOUN for "(.+)[SZ]"
 {
  NUMBER { "" "%+ES" }
 }

 // BUSH-BUSHES
 paradigm Bush : ENG_NOUN for "(.+)SH"
 {
  NUMBER { "" "%+ES" }
 }

 // SPEECH-SPEECHES
 paradigm Speech : ENG_NOUN for "(.+)CH"
 {
  NUMBER { "" "%+ES" }
 }

 // DEPTH-DEPTHS
 paradigm Depth : ENG_NOUN for "(.+)TH"
 {
  NUMBER { "" "%+S" }
 }


 // SUITE-SUITES
 paradigm Suite : ENG_NOUN for "(.+)E"
 {
  NUMBER { "" "%+S" }
 }


 // POTATO - POTATOES
 paradigm Potato : ENG_NOUN for "(.+)O"
 {
  NUMBER { "" "%+ES"  }
 }

 // QUESTION - QUESTIONS
 paradigm Question : ENG_NOUN for "(.+)"
 {
  NUMBER { "" "%+S"  }
 }


 // Парадигма для существительных без множественного числа, но с притяжательной формой
 paradigm Noun_8000 : ENG_NOUN
 {
  NUMBER:SINGLE { "" }
 }

 // Без множественного числа и притяжательной формы
 paradigm Noun_8002 : ENG_NOUN
 {
  NUMBER:SINGLE { "" }
 }

 // Для существительных типа CLOTH, которые образуют множественное число
 // присоединением окончания S, и не имеют притяжательных форм.
 paradigm Noun_Cloth : ENG_NOUN
 {
  NUMBER { "" "%+S" } // cloth cloths
 }

 // Существительные типа FISH с альтернативными формами множественного числа fish-fishes
 paradigm Noun_Fish : ENG_NOUN
 {
  NUMBER { "" "" } // fish fish
 }
 
 // **********************************************************************
 // Для неправильных существительных, в которых суффикс -man или -woman 
 // **********************************************************************
 paradigm Noun_8004 : ENG_NOUN
 {
  NUMBER { "" "%-2%+en"  }
 }

 //**************************************************************************************
 // Для существительных, у которых множественное число образуется простым присоединением
 // S, а притяжательной формы нет.
 //**************************************************************************************
 paradigm Noun_8005 : ENG_NOUN
 {
  NUMBER { "" "%+S"  }
 }

 // *******************************************************
 // Для статей, в которых множественное число образуется
 // двояко окончанием S и ES, например VETO-VETOS-VETOES
 // *******************************************************
 paradigm Noun_8006 : ENG_NOUN
 {
  NUMBER { "" "%+S"  }
 }
 

 // exemplum - exempla
 paradigm Noun_UM : ENG_NOUN
 {
  NUMBER { "" "%-2%+a"  }
 }

 // hamulus - hamuli
 paradigm Noun_US : ENG_NOUN
 {
  NUMBER { "" "%-2%+i"  }
 }

 // analysis - analyses
 paradigm Noun_IS : ENG_NOUN
 {
  NUMBER { "" "%-2%+es"  }
 }
 
}
