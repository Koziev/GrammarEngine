// -----------------------------------------------------------------------------
// File FR_LINK_GENERATORS.SOL
//
// (c) Elijah Koziev
//
// Content:
// Правила для автоматической генерации обратных связей
// -----------------------------------------------------------------------------
//
// CD->20.05.2006
// LC->17.12.2006
// --------------

#include "sg_defs.h"

automat sg
{
 // FRENCH-RUSSIAN

 link generator СУЩЕСТВИТЕЛЬНОЕ <to_french> FR_NOUN          -> <to_russian>
 link generator FR_NOUN         <to_russian> СУЩЕСТВИТЕЛЬНОЕ -> <to_french>


 link generator ПРИЛАГАТЕЛЬНОЕ <to_french> FR_ADJ          -> <to_russian>
 link generator FR_ADJ         <to_russian> ПРИЛАГАТЕЛЬНОЕ -> <to_french>

 link generator НАРЕЧИЕ         <to_french> FR_ADVERB          -> <to_russian>
 link generator FR_ADVERB       <to_russian> НАРЕЧИЕ           -> <to_french>

 link generator МЕСТОИМЕНИЕ      <to_french> FR_PRONOUN        -> <to_russian>
 link generator FR_PRONOUN       <to_russian> МЕСТОИМЕНИЕ      -> <to_french>

 link generator СОЮЗ         <to_french> FR_CONJ          -> <to_russian>
 link generator FR_CONJ       <to_russian> СОЮЗ           -> <to_french>

 link generator ПРЕДЛОГ         <to_french> FR_PREP          -> <to_russian>
 link generator FR_PREP       <to_russian> ПРЕДЛОГ           -> <to_french>

 link generator ИНФИНИТИВ         <to_french> FR_VERB          -> <to_russian>
 link generator FR_VERB       <to_russian> ИНФИНИТИВ           -> <to_french>

 link generator ГЛАГОЛ         <to_french> FR_VERB          -> <to_russian>
 link generator FR_VERB       <to_russian> ГЛАГОЛ           -> <to_french>

}
