#ifndef SEARCH_ENGINE_CALLBACKS__H
#define SEARCH_ENGINE_CALLBACKS__H
#pragma once

 namespace Solarix
 {
  namespace Search_Engine
  { 

   // Очередной файл обрабатывается, либо другое событие обработки
   struct Progress_Callback
   {
    virtual void Start_File( const wchar_t *filename ) {}
    virtual void Start_Folder( const wchar_t *filename ) {}
    virtual void Success(
                         const wchar_t *filename,
                         const wchar_t *location,
                         const wchar_t *tmp
                        ) {}
   };


   // Продолжать ли сканирование
   struct Continue_Callback
   {
    virtual bool Ask(void) { return true; }
   };
  }
 } 

#endif

