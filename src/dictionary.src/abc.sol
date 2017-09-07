// -----------------------------------------------------------------------------
// File ABC.SOL
//
// (c) Koziev Elijah
//
// Графическая Грамматика: РЕАЛИЗАЦИИ классов и так далее.
// -----------------------------------------------------------------------------
//
// CD->30.01.1997
// LC->07.02.2008
// --------------

automat gg
{
 enum VOWELNESS {
                 VOWEL     /* ГЛАСНАЯ    */
                 CONSONANT /* СОГЛАСНАЯ  */
                 SOUNDLESS /* БЕЗГЛАСНАЯ  */
                 SEMIVOWEL /* ПОЛУГЛАСНАЯ */
                }
                
 enum SIZE      { BIG SMALL }

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

 class NUMBER
}

