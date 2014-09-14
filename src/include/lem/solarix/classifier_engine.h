// API information: http://www.solarix.ru/for_developers/api/classifier_api.shtml

#ifndef CLASSIFIER_ENGINE__H
#define CLASSIFIER_ENGINE__H
#pragma once

#if defined DLL_EXPORTS
 #define CLASSY_EXPORTS
#else
 #define CLASSY_IMPORTS
#endif

#undef DLL_ENTRY

#if defined CLASSY_IMPORTS
 #if defined LEM_WINDOWS || defined _WIN32
  #define CLASSY_API(RetType) extern RetType __stdcall
 #else
  #define CLASSY_API(RetType) extern "C" RetType
 #endif
#elif defined CLASSY_EXPORTS
 #if defined LEM_WINDOWS || defined _WIN32
  #define CLASSY_API(RetType) __declspec(dllexport) RetType __stdcall
 #else
  #define CLASSY_API(RetType) extern "C" RetType __attribute__((visibility("default")))
 #endif
#else
 #error
#endif

typedef void* HCLASSY;
typedef void* HCLSRES;
typedef void* HCLSOPT;


CLASSY_API(HCLASSY) sol_LoadClassifierW( const wchar_t *filepath, const wchar_t *dictionary_xml );
CLASSY_API(HCLASSY) sol_LoadClassifierA( const char *filepath, const char *dictionary_xml );
CLASSY_API(HCLASSY) sol_LoadClassifier8( const char *filepath, const char *dictionary_xml );
CLASSY_API(void) sol_DeleteClassifier( HCLASSY hEngine );

CLASSY_API(HCLSOPT) sol_CreateClassifierParams( HCLASSY hEngine );
CLASSY_API(int) sol_SetClassifierParamW( HCLASSY hEngine, HCLSOPT hOpt, const wchar_t *Param, const wchar_t *Value );
CLASSY_API(int) sol_SetClassifierParamA( HCLASSY hEngine, HCLSOPT hOpt, const char *Param, const char *Value );
CLASSY_API(int) sol_SetClassifierParam8( HCLASSY hEngine, HCLSOPT hOpt, const char *Param, const char *Value );
CLASSY_API(void) sol_DeleteClassifierParams( HCLSOPT hOpt );

CLASSY_API(HCLSRES) sol_ClassifyTextW( HCLASSY hEngine, const wchar_t *Text, int LanguageId, HCLSOPT Flags );
CLASSY_API(HCLSRES) sol_ClassifyTextA( HCLASSY hEngine, const char *Text, int LanguageId, HCLSOPT Flags );
CLASSY_API(HCLSRES) sol_ClassifyText8( HCLASSY hEngine, const char *Text, int LanguageId, HCLSOPT Flags );

CLASSY_API(const wchar_t*) sol_GetBestTopicNameW( HCLASSY hEngine, HCLSRES hCls, const wchar_t *Category );
CLASSY_API(const char*)    sol_GetBestTopicNameA( HCLASSY hEngine, HCLSRES hCls, const char *Category );
CLASSY_API(const char*)    sol_GetBestTopicName8( HCLASSY hEngine, HCLSRES hCls, const char *Category );

CLASSY_API(double) sol_GetBestTopicScoresW( HCLASSY hEngine, HCLSRES hCls, const wchar_t *Category );
CLASSY_API(double)    sol_GetBestTopicScoresA( HCLASSY hEngine, HCLSRES hCls, const char *Category );
CLASSY_API(double)    sol_GetBestTopicScores8( HCLASSY hEngine, HCLSRES hCls, const char *Category );

CLASSY_API(int) sol_DeleteClassification( HCLSRES hCls );


#endif
