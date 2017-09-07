// -----------------------------------------------------------------------------
// File SG_MAIN.SOL
//
// (c) Koziev Elijah
//
// Content:
// Лексикон - определения общих классов для Словаря.
//
// Подробнее о синтаксисе:
// http://www.solarix.ru/for_developers/docs/enums.shtml
// http://www.solarix.ru/for_developers/docs/classes.shtml
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->08.04.2010
// --------------

#include "sg_defs.h"

automat sg
{

 class NOUN
 {
 }

 enum VOWELNESS {
                 VOWEL     /* ГЛАСНАЯ    */
                 CONSONANT /* СОГЛАСНАЯ  */
                 SOUNDLESS /* БЕЗГЛАСНАЯ  */
                 SEMIVOWEL /* ПОЛУГЛАСНАЯ */
                }
                
 enum SIZE      { BIG SMALL }

 // Tag for words with first capitalized letter (e.q. Russia)
 enum CharCasing as CharCasing
 {
  Lower                as DECAPITALIZED_CASED          // e.g. force
  FirstCapitalized     as FIRST_CAPITALIZED_CASED      // e.g. Russia
  Upper                as ALL_CAPITALIZED_CASED        // e.g. USA
  EachLexemCapitalized as EACH_LEXEM_CAPITALIZED_CASED // e.g. New York
 }

 class LETTER
 {
  attributes
  {
   VOWELNESS
  }

  dimentions
  {
   SIZE
  }
 }
}

