// API information: http://www.solarix.ru/for_developers/api/lemmatizator_api.shtml

#ifndef LEMMATIZATOR_ENGINE__H
#define LEMMATIZATOR_ENGINE__H
#pragma once

#if defined DLL_EXPORTS
 #define LEMMA_EXPORTS
#else
 #define LEMMA_IMPORTS
#endif

#undef DLL_ENTRY

#if defined LEMMA_IMPORTS
 #if defined LEM_WINDOWS || defined _WIN32
  #define LEMMA_API(RetType) extern RetType __stdcall
 #else
  #define LEMMA_API(RetType) extern "C" RetType
 #endif
#elif defined LEMMA_EXPORTS
 #if defined LEM_WINDOWS || defined _WIN32
  #define LEMMA_API(RetType) __declspec(dllexport) RetType __stdcall
 #else
  #define LEMMA_API(RetType) extern "C" RetType __attribute__((visibility("default")))
 #endif
#else
 #error
#endif

typedef void* HLEM;
typedef void* HLEMMAS;

#include "LemmatizatorFlags.h"

// http://www.solarix.ru/api/en/sol_LoadLemmatizator.shtml
LEMMA_API(HLEM) sol_LoadLemmatizatorW( const wchar_t * filepath, int Flags );
LEMMA_API(HLEM) sol_LoadLemmatizatorA( const char * filepath, int Flags );
LEMMA_API(HLEM) sol_LoadLemmatizator8( const char * filepath, int Flags );

// http://www.solarix.ru/api/en/sol_DeleteLemmatizator.shtml
LEMMA_API(int) sol_DeleteLemmatizator( HLEM hEngine );

// http://www.solarix.ru/api/en/sol_GetLemma.shtml
LEMMA_API(int) sol_GetLemmaW( HLEM hEngine, const wchar_t *Word, wchar_t *Result, int BufSize );
LEMMA_API(int) sol_GetLemmaA( HLEM hEngine, const char *Word, char *Result, int BufSize );
LEMMA_API(int) sol_GetLemma8( HLEM hEngine, const char *WordUtf8, char *ResultUtf8, int BufSize );

// http://www.solarix.ru/api/en/sol_GetLemmas.shtml
LEMMA_API(HLEMMAS) sol_GetLemmasW( HLEM hEngine, const wchar_t *Word );
LEMMA_API(HLEMMAS) sol_GetLemmasA( HLEM hEngine, const char *Word );
LEMMA_API(HLEMMAS) sol_GetLemmas8( HLEM hEngine, const char *WordUtf8 );

// http://www.solarix.ru/api/en/sol_CountLemmas.shtml
LEMMA_API(int) sol_CountLemmas( HLEMMAS hList );

// http://www.solarix.ru/api/en/sol_GetLemmaString.shtml
LEMMA_API(int) sol_GetLemmaStringW( HLEMMAS hList, int Index, wchar_t *Result, int BufSize );
LEMMA_API(int) sol_GetLemmaStringA( HLEMMAS hList, int Index, char *Result, int BufSize );
LEMMA_API(int) sol_GetLemmaString8( HLEMMAS hList, int Index, char *Result, int BufSize );

// http://www.solarix.ru/api/en/sol_DeleteLemmas.shtml
LEMMA_API(int) sol_DeleteLemmas( HLEMMAS hList );


LEMMA_API(HLEMMAS) sol_LemmatizePhraseW( HLEM hEngine, const wchar_t *Sentence, int Flags, int WordSeparator );
LEMMA_API(HLEMMAS) sol_LemmatizePhraseA( HLEM hEngine, const char *Sentence, int Flags, int WordSeparator );
LEMMA_API(HLEMMAS) sol_LemmatizePhrase8( HLEM hEngine, const char *SentenceUtf8, int Flags, int WordSeparator );



#endif
