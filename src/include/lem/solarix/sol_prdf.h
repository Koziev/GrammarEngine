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
// LC->20.04.2009
// --------------

#ifndef SOL_PREDEF__H
 #define SOL_PREDEF__H

 namespace Solarix
 {
  // Индексы предопределенных классов.
  const int I_TYPES   = 0; // class TYPES
  const int I_BETH    = 1; // class BETH
  const int I_NUMWORD = 2; // класс для чисел во входных фразах.

  #define I_INT_index            0  // INT     of class TYPES
  #define I_FLAG_index           1  // FLAG    of class TYPES
  #define I_REFNAME_index        2  // REFNAME of class TYPES
  #define I_MULTY_index          3  // MULTYPLICATOR of class BETH
  #define I_NONEOF_index         4  // NONEOF of class BETH
  #define I_LOGIC_NOT_index      5
  #define I_LOGIC_AND_index      6
  #define I_LOGIC_OR_index       7
  #define I_LOGIC_IFTHEN_index   8
  #define I_BEGIN_index          9
  #define I_END_index            10
  #define I_BEGIN_FRAGMENT_index 11
  #define I_END_FRAGMENT_index   12
  #define I_INUMBER_index        13
  #define I_REPLACE_index        14

  const int SOL_SG_NPREDEF_ENTRIES = 15; // Число предопределённых статей.

  #define I_INT            GetPredefinedEntryKey(I_INT_index)
  #define I_FLAG           GetPredefinedEntryKey(I_FLAG_index)
  #define I_REFNAME        GetPredefinedEntryKey(I_REFNAME_index)
  #define I_MULTY          GetPredefinedEntryKey(I_MULTY_index)
  #define I_NONEOF         GetPredefinedEntryKey(I_NONEOF_index)
  #define I_LOGIC_NOT      GetPredefinedEntryKey(I_LOGIC_NOT_index)
  #define I_LOGIC_AND      GetPredefinedEntryKey(I_LOGIC_AND_index)
  #define I_LOGIC_OR       GetPredefinedEntryKey(I_LOGIC_OR_index)
  #define I_LOGIC_IFTHEN   GetPredefinedEntryKey(I_LOGIC_IFTHEN_index)
  #define I_BEGIN          GetPredefinedEntryKey(I_BEGIN_index)
  #define I_END            GetPredefinedEntryKey(I_END_index)
  #define I_BEGIN_FRAGMENT GetPredefinedEntryKey(I_BEGIN_FRAGMENT_index)
  #define I_END_FRAGMENT   GetPredefinedEntryKey(I_END_FRAGMENT_index)
  #define I_INUMBER        GetPredefinedEntryKey(I_INUMBER_index)
  #define I_REPLACE        GetPredefinedEntryKey(I_REPLACE_index)

  // Связки
  const int I_1          = 0; // enum net { _1
  const int I_2          = 1; //            _2
  const int I_3          = 2; //            _3 }

  const int I_OPERATOR   = 1; // enum operator{
  const int I_NET        = 0; //                net
  const int I_CONVOLVE   = 1; //                convolve
  const int I_MERGE      = 2; //                merge
  const int I_RND        = 3; //                rnd
  const int I_SYNGRAM    = 4; //                SynGram }
  const int I_CLASSCOORD = 2; // enum _CLASS_
  const int SOL_N_PREDEF_COORDS = 3; // Число предопределённых координат.
 } // namespace 'lem'

#endif
// ------------------------- End Of File [SOL_PRDF.H] --------------------------
