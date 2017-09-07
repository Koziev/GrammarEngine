// -----------------------------------------------------------------------------
// File SG_LINK_GENERATORS.SOL
//
// (c) Elijah Koziev
//
// Content:
// Правила для автоматической генерации обратных связей в тезаурусе, главным
// образом - переводы.
// -----------------------------------------------------------------------------
//
// CD->20.05.2006
// LC->18.12.2013
// --------------

#include "sg_defs.h"

automat sg
{

 // ENGLISH-RUSSIAN

 link generator СУЩЕСТВИТЕЛЬНОЕ <to_english> ENG_NOUN        -> <to_russian>
 link generator ENG_NOUN        <to_russian> СУЩЕСТВИТЕЛЬНОЕ -> <to_english>

 link generator ПРИЛАГАТЕЛЬНОЕ <to_english> ENG_ADJECTIVE    -> <to_russian>
 link generator ENG_ADJECTIVE  <to_russian> ПРИЛАГАТЕЛЬНОЕ   -> <to_english>

 link generator ИНФИНИТИВ <to_english> ENG_VERB              -> <to_russian>
 link generator ENG_VERB  <to_russian> ИНФИНИТИВ             -> <to_english>

 link generator ГЛАГОЛ <to_english> ENG_VERB               -> <to_russian>
 link generator ENG_VERB  <to_russian> ГЛАГОЛ              -> <to_english>

 link generator НАРЕЧИЕ <to_english> ENG_ADVERB              -> <to_russian>
 link generator ENG_ADVERB  <to_russian> НАРЕЧИЕ             -> <to_english>

 link generator СОЮЗ <to_english> ENG_CONJ                   -> <to_russian>
 link generator ENG_CONJ  <to_russian> СОЮЗ                  -> <to_english>

 link generator ПРЕДЛОГ <to_english> ENG_PREP                -> <to_russian>
 link generator ENG_PREP  <to_russian> ПРЕДЛОГ               -> <to_english>

 link generator НАРЕЧИЕ <to_english> ENG_ADJECTIVE                -> <to_russian>
 link generator ENG_ADJECTIVE  <to_russian> НАРЕЧИЕ               -> <to_english>


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


 // SPANISH-RUSSIAN

 link generator СУЩЕСТВИТЕЛЬНОЕ <to_spanish> ES_ROOT         -> <to_russian>
 link generator ES_ROOT         <to_russian> СУЩЕСТВИТЕЛЬНОЕ -> <to_spanish>

 link generator СУЩЕСТВИТЕЛЬНОЕ <to_spanish> ES_NOUN         -> <to_russian>
 link generator ES_NOUN         <to_russian> СУЩЕСТВИТЕЛЬНОЕ -> <to_spanish>


 // RUSSIAN-JAPANESE

 link generator JAP_NOUN <to_russian> СУЩЕСТВИТЕЛЬНОЕ -> <to_japanese>
 link generator JAP_VERB <to_russian> ИНФИНИТИВ -> <to_japanese>
 link generator JAP_ADJECTIVE <to_russian> ПРИЛАГАТЕЛЬНОЕ -> <to_japanese>
 link generator JAP_PRONOUN <to_russian> МЕСТОИМЕНИЕ -> <to_japanese>
 link generator JAP_ADVERB <to_russian> НАРЕЧИЕ -> <to_japanese>

 link generator СУЩЕСТВИТЕЛЬНОЕ <to_japanese> JAP_NOUN -> <to_russian>
 link generator ИНФИНИТИВ <to_japanese> JAP_VERB -> <to_russian>
 link generator ПРИЛАГАТЕЛЬНОЕ <to_japanese> JAP_ADJECTIVE -> <to_russian>
 link generator МЕСТОИМЕНИЕ <to_japanese> JAP_PRONOUN -> <to_russian>
 link generator НАРЕЧИЕ <to_japanese> JAP_ADVERB -> <to_russian>

 link generator { jap_noun:A <to_russian> существительное:B  jap_noun:A <to_kana> jap_noun:D } -> D <to_russian> B 
}
