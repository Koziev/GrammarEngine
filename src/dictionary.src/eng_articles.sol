// -----------------------------------------------------------------------------
// File ENG_ARTICTES.SOL
//
// (c) 2005 Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения артиклей для английского раздела Словаря.
// -----------------------------------------------------------------------------
//
// CD->26.02.2005
// LC->12.07.2005
// --------------


#include "sg_defs.h"

automat sg
{
 entry A : ENG_ARTICLE
 {
  ARTICLE_FORM { A AN }
 }

 entry THE : ENG_ARTICLE
 
}

