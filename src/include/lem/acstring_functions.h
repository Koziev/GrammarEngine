// -----------------------------------------------------------------------------
// File ACSTRING_FUCTIONS.H
//
// (c) Koziev Elijah
//
// Content:
//
// -----------------------------------------------------------------------------
//
// CD->30.08.2006
// LC->15.10.2009
// --------------

#ifndef LEM_ACSTRING_FUNC__H
#define LEM_ACSTRING_FUNC__H
#pragma once
 
 #include <lem/acstring.h>

 namespace lem
 {
  class Stream;
  extern void Save_Packed( const CString &s, Stream &bin );
  extern void Load_Packed( CString *s, Stream &bin );
 } // end of namespace 'lem'

#endif
