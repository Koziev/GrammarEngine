// -----------------------------------------------------------------------------
// File ENG_VERB_PARADIGMAS.SOL
//
// (c) Koziev Elijah
// Solarix Intellectronix project   http://www.solarix.ru
//
// Content:
// Лексикон - определения глаголов для английского раздела Словаря.
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->06.05.2012
// --------------


#include "sg_defs.h"

automat sg
{
 paradigm to_pooh_pooh : ENG_VERB for ".+\\@vh"
 {
  VERB_FORM:S   { "%+S" } // pooh-pooh pooh-pooh pooh-poohs
  VERB_FORM:ED  { "%+ED"  } // pooh-poohed
  VERB_FORM:PP  { "%+ED"  } // pooh-poohed
  VERB_FORM:ING { "%+ING" } // pooh-poohing
  VERB_FORM:INF { ""      } // pooh-pooh
 }

 paradigm to_ship : ENG_VERB for "\\@ch\\@v\\@c"
 {
  VERB_FORM:S   { "%+S"  } // ship ship ships
  VERB_FORM:ED  { "%D%+ED"     } // shipped
  VERB_FORM:PP  { "%D%+ED"     } // shipped
  VERB_FORM:ING { "%D%+ING"    } // shipping
  VERB_FORM:INF { ""           } // ship
 }
 

 // ********************************************
 // 3-буквенные слова
 // SUM-SUMS-SUMMED-SUMMING
 // ********************************************
 paradigm to_sum : ENG_VERB for "\\@c\\@v\\@c"
 {
  VERB_FORM:S { "%+S"  } // SUM SUM SUMS
  VERB_FORM:ED                         { "%D%+ED"     } // SUMMED
  VERB_FORM:PP                         { "%D%+ED"     } // SUMMED
  VERB_FORM:ING                        { "%D%+ING"    } // SUMMING
  VERB_FORM:INF                        { ""           } // SUM
 }


 paradigm to_hum : ENG_VERB for "h\\@v\\@c"
 {
  VERB_FORM:S { "%+S"  } // HUM HUM HUMS
  VERB_FORM:ED                         { "%D%+ED"     } // HUMMED
  VERB_FORM:PP                         { "%D%+ED"     } // HUMMED
  VERB_FORM:ING                        { "%D%+ING"    } // HUMMING
  VERB_FORM:INF                        { ""           } // HUM
 }


 paradigm to_remember : ENG_VERB for "(.+)[eoy]r"
 {
  VERB_FORM:S { "%+S" } // REMEMBER REMEMBER REMEMBERS
  VERB_FORM:ED                         { "%+ED"      } // REMEMBERED
  VERB_FORM:PP                         { "%+ED"      } // REMEMBERNED
  VERB_FORM:ING                        { "%+ING"     } // REMEMBERNING
  VERB_FORM:INF                        { ""          } // REMEMBER
 }


 // ********************************************
 // С удвоением последней согласной
 // SCAN-SCANS-SCANNED-SCANNING
 // ********************************************
 paradigm to_scan : ENG_VERB for "(.+)\\@c[aiou]\\@c"
 {
  VERB_FORM:S { "%+S"  } // SCAN SCAN SCANS
  VERB_FORM:ED                         { "%D%+ED"     } // SCANNED
  VERB_FORM:PP                         { "%D%+ED"     } // SCANNED
  VERB_FORM:ING                        { "%D%+ING"    } // SCANNING
  VERB_FORM:INF                        { ""           } // SCAN
 }



 // ********************************************
 // PASS-PASSES
 // BUZZ-BUZZES
 // ********************************************
 paradigm to_pass : ENG_VERB for "(.+)[SZXS]"
 {
  VERB_FORM:S { "%+ES" } // PASS PASS PASSES
  VERB_FORM:ED                         { "%+ED"       } // PASSED
  VERB_FORM:PP                         { "%+ED"       } // PASSED (for regular verbs same as -ed)
  VERB_FORM:ING                        { "%+ING"      } // PASSING
  VERB_FORM:INF                        { ""           } // PASS
 }


 // ************************************
 // PEE-PEES-PEED-PEEING
 // ************************************
 paradigm to_pee : ENG_VERB for "(.+)EE"
 {
  VERB_FORM:S { "%+S" } // PEE PEE PEES
  VERB_FORM:ED                         { "%+D"       } // PEED
  VERB_FORM:PP                         { "%+D"       } // PEED
  VERB_FORM:ING                        { "%+ING"     } // PEEING
  VERB_FORM:INF                        { ""          } // PEE
 }

 // ************************************
 // С исчезающей немой в конце 'e'
 // MUTE-MUTES-MUTED-MUTING
 // ************************************
 paradigm to_mute : ENG_VERB for "(.+)E"
 {
  VERB_FORM:S { "%+S" } // MUTE MUTE MUTES
  VERB_FORM:ED                         { "%+D"       } // MUTED
  VERB_FORM:PP                         { "%+D"       } // MUTED
  VERB_FORM:ING                        { "%-1%+ING"  } // MUTING
  VERB_FORM:INF                        { ""          } // MUTE
 }


 // PLAY, DESTROY
 paradigm to_play : ENG_VERB for "(.+)[AOE]Y"
 {
  VERB_FORM:S { "%+S"    } // PLAY PLAY PLAYS
  VERB_FORM:ED                         { "%+ED"         } // PLAYED
  VERB_FORM:PP                         { "%+ED"         } // PLAYED
  VERB_FORM:ING                        { "%+ING"        } // PLAYING
  VERB_FORM:INF                        { ""             } // PLAY
 }


 // COPY-COPIES-COPIED-COPYING
 paradigm to_copy : ENG_VERB for "(.+)Y"
 {
  VERB_FORM:S { "%-1%+IES"  } // COPY COPY COPIES
  VERB_FORM:ED                         { "%-1%+IED"        } // COPIED
  VERB_FORM:PP                         { "%-1%+IED"        } // COPIED
  VERB_FORM:ING                        { "%+ING"           } // COPYING
  VERB_FORM:INF                        { ""                } // COPY
 }

 paradigm to_dye : ENG_VERB for "(.+)YE"
 {
  VERB_FORM:S { "%-1%+IES"  } // DYE DYE DIES
  VERB_FORM:ED                         { "%-2%+IED"        } // DIED
  VERB_FORM:PP                         { "%-2%+IED"        } // DIED
  VERB_FORM:ING                        { "%-1%+ING"        } // DYING
  VERB_FORM:INF                        { ""                } // DYE
 }

 // *******************************************
 // WEIGH-WEIGHS-WEIGHED-WEIGHING
 // BATH-BATHS-BATHED-BATHING
 // TRIUMPH-TRIUMPHS-TRIUMPHED-TRIUMPHING
 // *******************************************
 paradigm to_weight : ENG_VERB for "(.+)[GTP]H"
 {
  VERB_FORM:S { "%+S" }  // WEIGH WEIGH WEIGHS
  VERB_FORM:ED                         { "%+ED"       } // WEIGHED
  VERB_FORM:PP                         { "%+ED"       } // WEIGHED
  VERB_FORM:ING                        { "%+ING"      } // WEIGHING
  VERB_FORM:INF                        { ""           } // WEIGH
 }


 // FETCH-FETCHES-FETCHED-FETCHING
 // CLASH-CLASHES-CLASHED-CLASHING
 paradigm to_fetch : ENG_VERB for "(.+)H"
 {
  VERB_FORM:S { "%+ES" } // FETCH FETCH FETCHES
  VERB_FORM:ED                         { "%+ED"       } // FETCHED
  VERB_FORM:PP                         { "%+ED"       } // FETCHED
  VERB_FORM:ING                        { "%+ING"      } // FETCHING
  VERB_FORM:INF                        { ""           } // FETCH
 }


 // VETO-VETOES-VETOED-VETOING
 paradigm to_veto : ENG_VERB for "(.+)O"
 {
  VERB_FORM:S { "%+ES" } // VETO VETO VETOES
  VERB_FORM:ED                         { "%+ED"       } // VETOED
  VERB_FORM:PP                         { "%+ED"       } // VETOED
  VERB_FORM:ING                        { "%+ING"      } // VETOING
  VERB_FORM:INF                        { ""           } // VETO
 }


 // ASK-ASKS-ASKED-ASKING
 paradigm to_ask : ENG_VERB for "(.+)"
 {
  VERB_FORM:S { "%+S"  } // ASK ASK ASKS
  VERB_FORM:ED                         { "%+ED"       } // ASKED
  VERB_FORM:PP                         { "%+ED"       } // ASKED (for regular verbs same as -ed)
  VERB_FORM:ING                        { "%+ING"      } // ASKING
  VERB_FORM:INF                        { ""           } // ASK
 }


 // ***********************************************************************************
 // Особые случаи - когда последняя согласная не должна удваиватся, хотя по формальным
 // признакам подходит парадигма с удвоением.
 // ***********************************************************************************
 paradigm Verb_1200 : ENG_VERB
 {
  VERB_FORM:S { "%+S"  } // EDIT EDIT EDITS
  VERB_FORM:ED                         { "%+ED"       } // EDITED
  VERB_FORM:PP                         { "%+ED"       } // EDITED
  VERB_FORM:ING                        { "%+ING"      } // EDITING
  VERB_FORM:INF                        { ""           } // EDIT
 }


 paradigm Verb_1201 : ENG_VERB
 {
  VERB_FORM:S { "%+ES" } // synthesis synthesis synthesisS
  VERB_FORM:ED                         { "%+ED"       } // synthesisED
  VERB_FORM:PP                         { "%+ED"       } // synthesisED
  VERB_FORM:ING                        { "%+ING"      } // synthesisING
  VERB_FORM:INF                        { ""           } // synthesis
 }

 // Для явного описания глаголов с удвоением последней согласной
 paradigm Verb_1202 : ENG_VERB
 {
  VERB_FORM:S { "%+S"  } // SCAN SCAN SCANS
  VERB_FORM:ED                         { "%D%+ED"     } // SCANNED
  VERB_FORM:PP                         { "%D%+ED"     } // SCANNED
  VERB_FORM:ING                        { "%D%+ING"    } // SCANNING
  VERB_FORM:INF                        { ""           } // SCAN
 }

 // Некоторые глаголы могут иметь отличия в удвоении последней согласной для
 // us- и uk-вариантов, например:
 // quarrel-quarrelling UK
 // quarrel-quarreling US
 paradigm Verb_1202us : ENG_VERB
 {
  VERB_FORM:S { "%+S"  } // quarrel quarrel quarrelS
  VERB_FORM:ED                         { "%D%+ED"     } // quarrelled
  VERB_FORM:ED                         { "%+ED"       } // quarreled
  VERB_FORM:PP                         { "%D%+ED"     } // quarrelled
  VERB_FORM:PP                         { "%+ED"       } // quarreled
  VERB_FORM:ING                        { "%D%+ING"    } // quarrelling
  VERB_FORM:ING                        { "%+ING"      } // quarreling
  VERB_FORM:INF                        { ""           } // quarrel
 }
 
 
 
 paradigm Verb_1203 : ENG_VERB
 {
  VERB_FORM:S { "%+ES"  } // posses posses posseseS
  VERB_FORM:ED                         { "%D%+ED"      } // possesED
  VERB_FORM:PP                         { "%D%+ED"      } // possesED
  VERB_FORM:ING                        { "%D%+ING"     } // possesING
  VERB_FORM:INF                        { ""            } // posses
 }

 
 // VETO-VETOS/VETOES-VETOED-VETOING
 paradigm Verb_VETO : ENG_VERB
 {
  VERB_FORM:S { "%+ES" } // VETO VETO VETOES
  VERB_FORM:S {       "%+S"  } // VETOS
  VERB_FORM:ED                           { "%+ED"       } // VETOED
  VERB_FORM:PP                           { "%+ED"       } // VETOED
  VERB_FORM:ING                          { "%+ING"      } // VETOING
  VERB_FORM:INF                          { ""           } // VETO
 }

 
}
