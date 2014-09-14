// -----------------------------------------------------------------------------
// File SOME_STRINGS.H
//
// (c) Koziev Elijah
//
// Content:
// Some characters including special control chars. ASCII and UNICODE.
// Also UNICODE strings with key words, tokens and so on.
// -----------------------------------------------------------------------------
//
// CD->06.09.1997
// LC->22.08.2011
// --------------

#ifndef SOL_SSSS__H
#define SOL_SSSS__H
#pragma once

 #include <lem/config.h>

 #if defined LEM_MSC
  #include <wchar.h>
 #endif

 namespace Solarix
 {
  extern const wchar_t* SOL_UNKNOWN_ENTRY_NAME;
  extern const wchar_t* SOL_UNKNOWN_ENTRY2;
  extern const wchar_t* SOL_MAIN_ITERATOR_NAME;
  extern const wchar_t* SOL_FRENCHING_ITERATOR_NAME;
  extern const wchar_t* SOL_VOICECONTEXTS_ITERATOR_NAME;
 }

#endif
