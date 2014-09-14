// -----------------------------------------------------------------------------
// File UCSTRING_FUCTIONS.H
//
// (c) Koziev Elijah
//
// Content:
//
// -----------------------------------------------------------------------------
//
// CD->30.08.2006
// LC->04.12.2008
// --------------

#ifndef LEM_UCSTRING_FUNC__H
#define LEM_UCSTRING_FUNC__H
#pragma once

 #include <lem/ucstring.h>

 namespace lem
 {
  class Stream;
  extern void Save_Packed( const UCString &s, lem::Stream &bin );
  extern void Load_Packed( UCString *s, lem::Stream &bin );
 } // end of namespace 'lem'

#endif
