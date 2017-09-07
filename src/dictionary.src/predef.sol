// -----------------------------------------------------------------------------
// File PREDEF.SOL
//
// (c) Koziev Elijah
//
// Файл с реализациями предопределенных связок, классов и статей, используемых
// Системой. Последовательность объявлений не менять!
// -----------------------------------------------------------------------------
//
// CD->12.11.1996
// LC->18.07.2015
// --------------

#include "predef.inc"
#include "sg_defs.h"

automat sg
{
 enum net {}
 enum _CLASS_ {}

 class beth
 class num_word as NUM_WORD_CLASS

 entry begin          : beth     { flag:shadow_entry, I_BEGIN_index }
 entry end            : beth     { flag:shadow_entry, I_END_index }
 entry begin_fragment : beth     { flag:shadow_entry, I_BEGIN_FRAGMENT_index }
 entry end_fragment   : beth     { flag:shadow_entry, I_END_FRAGMENT_index }
 entry number_        : num_word { flag:shadow_entry, I_INUMBER_index }
}
