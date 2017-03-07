// -----------------------------------------------------------------------------
// File SOL_PRDF.H
//
// (c) Koziev Elijah
//
// Content:
// Solaris predefined classes, entries, coordinates, etc., for internal use
// only.
// -----------------------------------------------------------------------------
//
// CD->27.05.1997
// LC->18.07.2015
// --------------

#ifndef SOL_PREDEF__H
 #define SOL_PREDEF__H

 namespace Solarix
 {
  const int I_NET = 0;
  const int I_CLASSCOORD = 1; // enum _CLASS_


  const int I_BETH    = 0;
  const int I_NUMWORD = 1;

  #define I_BEGIN_index          0
  #define I_END_index            1
  #define I_BEGIN_FRAGMENT_index 2
  #define I_END_FRAGMENT_index   3
  #define I_INUMBER_index        4

  const int SOL_SG_NPREDEF_ENTRIES = 5;
  #define I_BEGIN          GetPredefinedEntryKey(I_BEGIN_index)
  #define I_END            GetPredefinedEntryKey(I_END_index)
  #define I_BEGIN_FRAGMENT GetPredefinedEntryKey(I_BEGIN_FRAGMENT_index)
  #define I_END_FRAGMENT   GetPredefinedEntryKey(I_END_FRAGMENT_index)
  #define I_INUMBER        GetPredefinedEntryKey(I_INUMBER_index)

 }

#endif
