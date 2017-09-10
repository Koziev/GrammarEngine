//
// CD->25.12.2008
// LC->22.06.2011
// --------------

#include "predef.inc"
#include "pm_doac.h"
#include "aa_rules.inc"

automat va
{

 iterator MainIterator language=English
 {
  {
   iterate
    {
     REPLACE VA_SYNTH_SUBJECT
     REPLACE VA_SYNTH_TENSE
     REPLACE VA_SYNTH_ARTICLE
     REPLACE VA_SYNTH_ADV
     REPLACE VA_SYNTH_ADJ
     iter_end // Удаляем вариаторы, которые породили новые.
    } 

   pass_default // Вызываем расшивку-уплощение для точек вариатора.
   iter_end // Удаляем вариаторы, которые породили новые.
  }
 }


 // ********************************************
 // ПРИЛАГАТЕЛЬНОЕ+СУЩЕСТВИТЕЛЬНОЕ
 // ********************************************
 operator AdjNoun_1 : VA_SYNTH_ADJ
 {
  if context { ENG_NOUN:*{}#a.{ ENG_ADJECTIVE:*{}#b }  }
   then context {
                 #b : clear *   // wild
                 #a : cut #b    // cat
                }
 }

 operator AdjNoun_2 : VA_SYNTH_ADJ
 {
  if context { ENG_NOUN:*{}#a.{ ENG_ADJECTIVE:*{}#b ENG_ADJECTIVE:*{}#c } }
   then context {
                 #b : clear *         // big
                 #c : clear *         // wild
                 #a : cut #b : cut #c // cat
                }
 }


 // ***************************************
 // ГЛАГОЛ+НАРЕЧИЕ
 // ***************************************
 operator AdvVerb_1 : VA_SYNTH_ADV
 {
  if context { ENG_VERB:*{}#a.{ ENG_ADVERB:*{}#b } }
   then context {
                 #b : clear *   // silently
                 #a : cut #b     // sleeps
                }
 }


 // ***************************************
 // НАРЕЧИЕ+НАРЕЧИЕ
 // ***************************************
 operator AdvAdv_1 : VA_SYNTH_ADV
 {
  if context { ENG_ADVERB:*{}#a.{ ENG_ADVERB:*{}#b } }
   then context {
                 #b // very
                 #a : cut #b // silently
                }
 }


 // ********************************************
 // АРТИКЛЬ + СУЩЕСТВИТЕЛЬНОЕ
 // ********************************************
 operator Article_1 : VA_SYNTH_ARTICLE
 {
  if context { [ ENG_ARTICLE:*{}#a center:ENG_NOUN:*{}#b ]#c }
   then context {
                 #a : clear * // THE/A/AN
                 impart { #b #c } // существительное и его атрибуты (к примеру - прилагательные)
                }
 }



 // **********************************
 // *** Сложные Глагольные Времена ***
 // **********************************

 operator PresentContinuos_1 : VA_SYNTH_TENSE
 {
  if context { [ center:ENG_VERB:BE{}#a ENG_VERB:*{}#b ] { Duration:Continuous }#c }
   then context {
                 #a : clear DURATION:* : clear VOICE:* // служебный глагол IS
                 impart { #b : clear * : set { VERB_FORM:ING } #c } // ing-овая форма смыслового глагола + все ветки (типа наречий)
                }
 }




 operator Subject_1 : VA_SYNTH_SUBJECT
 {
  if context { ENG_VERB:*{}#a.{ <SUBJECT>*:*{}#b } }
   then context {
                 #b           // the cat
                 #a : cut #b  // sleeps
                }
 }

}

