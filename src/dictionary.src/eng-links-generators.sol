// -----------------------------------------------------------------------------
// File ENG-LINKS-GENERATORS.SOL
//
// (c) Elijah Koziev
//
// Content:
// Правила для автоматической генерации обратных связей для английского
// тезауруса.
// -----------------------------------------------------------------------------
//
// CD->20.05.2006
// LC->09.02.2011
// --------------

#include "sg_defs.h"

automat sg
{

 // ***************************************************************************
 //        Объявления для генераторов обратных связей в тезаурусе
 // ***************************************************************************

 // Несколько правил автогенерации обратных связок
 link generator ENG_ADJECTIVE <в_предикат> ENG_VERB -> <в_прил>
 link generator ENG_VERB <в_прил> ENG_ADJECTIVE -> <в_предикат>
 link generator ENG_VERB <в_сущ> ENG_NOUN -> <в_предикат>
 link generator ENG_NOUN <в_предикат> ENG_VERB -> <в_сущ>
 link generator ENG_NOUN <в_прил> ENG_ADJECTIVE -> <в_сущ>

 link generator ENG_NOUN <synonym> ENG_NOUN -> <synonym>
 link generator ENG_ADJECTIVE <synonym> ENG_ADJECTIVE -> <synonym>
 link generator ENG_VERB <synonym> ENG_VERB -> <synonym>
 link generator ENG_ADVERB <synonym> ENG_ADVERB -> <synonym>

 link generator ENG_ADJECTIVE <antonym> ENG_ADJECTIVE -> <antonym>
 link generator ENG_NOUN <antonym> ENG_NOUN -> <antonym>
 link generator ENG_ADVERB <antonym> ENG_ADVERB -> <antonym>
 link generator ENG_VERB <antonym> ENG_VERB -> <antonym>
 
}
