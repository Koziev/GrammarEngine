// -----------------------------------------------------------------------------
// File SG_QUAN.SOL
//
// Copyright:    Koziev Elijah
//
// Project name: SOLARIX INTELLECTRONICS
//
// Определения грамматических кванторов.
// -----------------------------------------------------------------------------
//
// CD->09.01.2005
// LC->15.08.2010
// --------------

#include "sg_defs.h"

automat sg
{

 class UnknownEntries as UNKNOWN_ENTRIES_CLASS

 quantor UnknownEntry : UnknownEntries
 {
  flag:quantor_entry
 }
}

