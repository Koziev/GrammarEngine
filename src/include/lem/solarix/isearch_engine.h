#ifndef ISEARCH_ENGINE__H
#define ISEARCH_ENGINE__H
#pragma once

  #if defined __GNUC__
   #define FaindApiMethod(rettype,name) typedef rettype(*name)
  #else
   #define FaindApiMethod(rettype,name) typedef rettype(__stdcall *name)
  #endif  

  FaindApiMethod(int,sol_Free_func)( void* hEngine, void *Ptr );
  FaindApiMethod(int,sol_FindTaggedDocument_func)( void* hEngine, const wchar_t *Filename, const wchar_t *Location );
  FaindApiMethod(int,sol_GetDocumentTag_func)( void* hEngine, int Id_doc, const wchar_t *Tag, wchar_t **Value );
  FaindApiMethod(int,sol_AddTaggedDocument_func)( void* hEngine, const wchar_t *Filename, const wchar_t *Location );
  FaindApiMethod(int,sol_SetDocumentTag_func)( void* hEngine, int Id_doc, const wchar_t *Tag, const wchar_t *Value );

  struct ISearchEngine
  {
   void* hEngine;

   #if defined FAIND_IENGINES
   ISearchEngine(void);
   #endif

   sol_Free_func sol_Free;
   sol_FindTaggedDocument_func sol_FindTaggedDocument;
   sol_GetDocumentTag_func sol_GetDocumentTag;
   sol_AddTaggedDocument_func sol_AddTaggedDocument;
   sol_SetDocumentTag_func sol_SetDocumentTag;
  };

#endif
