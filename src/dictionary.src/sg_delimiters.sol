// -----------------------------------------------------------------------------
// File SG_DELIMITERS.SOL
//
// Copyright (c) Koziev Elijah
//
// Project name: SOLARIS INTELLECTRONICS
//
// Лексикон - пунктуаторы.
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->26.01.2016
// --------------

#include "sg_defs.h"

automat sg
{
 entry "…" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$?.."   : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$!.."   : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$?"   : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$?!"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$!!!" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$."   : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$,"   : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$!"   : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$-"   : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$:"   : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$;"   : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$\"" : ПУНКТУАТОР  { flag:terminal_silent_noexport }
 entry "$\'" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "«" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "»" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "${"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$}"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$("  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$)"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$["  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$]"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$~"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$`"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$@"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$#"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$$"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$%"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$^"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$&"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$*"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$_"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$+"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$="  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$|"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$\\" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$/"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$<"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$>"  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "$..."  : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "—" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "–" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "“" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "”" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "„" : ПУНКТУАТОР { flag:terminal_silent_noexport }
 entry "‹" : ПУНКТУАТОР { flag:terminal_silent_noexport }
}
