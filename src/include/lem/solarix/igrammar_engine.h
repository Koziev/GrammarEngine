#ifndef IGRAMMAR_ENGINE__H
#define IGRAMMAR_ENGINE__H
#pragma once

 #include <wchar.h>

  #if defined __GNUC__
   #define GrenApiMethod(rettype,name) typedef rettype(*name)
  #else
   #define GrenApiMethod(rettype,name) typedef rettype (__stdcall *name)
  #endif 
    

  GrenApiMethod(int,sol_Free_func)( void* hEngine, void *Ptr );

  GrenApiMethod(int,sol_MaxLexemLen_func)( void* hEngine );
  GrenApiMethod(int,sol_SeekWord_func)( void* hEngine, const wchar_t *word, bool Allow_Dynforms );

  GrenApiMethod(bool,sol_OCR_Available_func)( void* hEngine );
  GrenApiMethod(int,sol_OCR_RecognizeFileW_func)( void* hEngine, const wchar_t *Filename, wchar_t **Buffer );
  GrenApiMethod(int,sol_OCR_RecognizeDIB_func)( void* hEngine, void *hDib, wchar_t **Buffer );

  struct IGrammarEngine
  {
   void* hEngine;

   sol_Free_func sol_Free;

   sol_MaxLexemLen_func sol_MaxLexemLen;
   sol_SeekWord_func sol_SeekWord;

   sol_OCR_Available_func sol_OCR_Available;
   sol_OCR_RecognizeFileW_func sol_OCR_RecognizeFileW;
   sol_OCR_RecognizeDIB_func sol_OCR_RecognizeDIB;

   #if defined FAIND_IENGINES
   IGrammarEngine(void);
   #endif
  };

#endif
