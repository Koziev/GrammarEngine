#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STEMMER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STEMMER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STEMMER_EXPORTS
#define STEMMER_API extern "C" __declspec(dllexport)
#else
#define STEMMER_API extern "C" __declspec(dllimport)
#endif

#if defined STEMMER_EXPORTS

 #include "lds_stemmer.h"

 struct LanguageStemmer
 {
  LDS_Stemmer x;
  std::string lang;
 }; 

 typedef LanguageStemmer* HSTEMMER; 
#else
 typedef void* HSTEMMER;
#endif


STEMMER_API HSTEMMER sol_CreateStemmerForLanguage( const char *lang2 );
STEMMER_API void sol_DeleteStemmer( HSTEMMER hStemmer );
STEMMER_API int  sol_Stem( HSTEMMER hStemmer, wchar_t *Word );
