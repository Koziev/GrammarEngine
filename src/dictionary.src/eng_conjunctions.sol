// -----------------------------------------------------------------------------
// File ENG_CONJUNCTIONS.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения союзов для английского раздела.
// -----------------------------------------------------------------------------
//
// CD->26.02.2005
// LC->19.01.2016
// --------------


#include "sg_defs.h"

automat sg
{
 entry BOTH     : ENG_CONJ
 entry AND      : ENG_CONJ
 entry BUT      : ENG_CONJ
 entry OR       : ENG_CONJ
 entry NOR      : ENG_CONJ
 entry EITHER   : ENG_CONJ
 entry NEITHER  : ENG_CONJ
 entry IF       : ENG_CONJ
 entry THEN     : ENG_CONJ
 entry WHERE    : ENG_CONJ
 entry AS       : ENG_CONJ
 entry SINCE    : ENG_CONJ
 entry WHILE    : ENG_CONJ
 entry WHILEST  : ENG_CONJ
 entry TILL     : ENG_CONJ
 entry UNTIL    : ENG_CONJ
 entry WHEREVER : ENG_CONJ
 entry WHETHER  : ENG_CONJ
 entry BECAUSE  : ENG_CONJ
 entry THAN     : ENG_CONJ
 entry THOUGH   : ENG_CONJ
 entry LEST     : ENG_CONJ // Lest you forget Чтобы Вы не забыли
 entry THAT     : ENG_CONJ
 entry plus : eng_conj // Spinoza’s second knowledge involves reasoning plus emotions.

 entry before : eng_conj
 entry after  : eng_conj
 entry rather than : eng_conj
 entry although : eng_conj
 entry so : eng_conj
 entry unless : eng_conj

 entry like : eng_conj
 
 entry "vs." : eng_conj
 entry versus : eng_conj // Stock buybacks versus wage increases.
 entry vs : eng_conj // Steel structure vs reinforced concrete.

 entry albeit : eng_conj // The telephone system functions, albeit imperfectly.

}

